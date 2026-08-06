#!/usr/bin/env python3
"""fleet_ui.py — one window over the whole fleet, over ONE held serial connection.

Why this exists, and why it is not just buttons that shell out to `companion.py`:
every `companion.py` invocation opens the port with DTR/RTS asserted, which REBOOTS
the cabled node ([[looping-companion-py-resets-bridge]] — a shell loop of probes once
fabricated a two-node outage out of nothing but its own resets). A UI that polls has
to hold ONE connection open for its whole life, so that is the shape here: a `Link`
owns a port on its own thread and everything — polling, commands, pulls — is a job on
that thread.

The wire format, the parsers and the reliable-send rules all come from `companion.py`;
nothing about the protocol is re-implemented here. Outside libraries: tkinter (stdlib)
and pyserial, which `companion.py` already requires. Nothing else.

    python orchestrator/fleet_ui.py [--bridge COM6] [--aux COM10] [--no-connect]

Panels
  LINKS   the V4-A bridge USB link, plus one optional second USB link (any node on
          its own cable), each with live state, frame counters and reply age.
  FLEET   every node: energy, heat, room to think, its own worst loop pass, the band
          it hears, its clock. Double-click a row to start/stop polling it.
  MAP     the same fleet as a picture, laid out from master/positions.md if that
          belief exists (SP2), otherwise a ring.
  LANES   the selected node's TTDB lanes with their caps, and the Clear button — the
          one control here that destroys something, so it asks first and quotes what
          the destruction costs.
  LOG     what actually went over the wire.
"""

import argparse
import contextlib
import math
import os
import queue
import re
import struct
import sys
import threading
import time
import tkinter as tk
from tkinter import filedialog, messagebox, ttk

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import companion as C  # noqa: E402  (path fixed above so this runs from anywhere)

try:
    import serial                      # noqa: F401  pyserial
    from serial.tools import list_ports
except ImportError:                                            # pragma: no cover
    sys.exit("pyserial not installed. Run: pip install -r orchestrator/requirements.txt")

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# --- Cadence -----------------------------------------------------------------
# One node per tick, so a command the operator just pressed waits at most one probe
# window instead of a whole fleet round.
POLL_PERIOD_S = 0.15        # gap between probes
PROBE_WINDOW_S = 0.60       # listen window per probed node
FRESH_S, STALE_S = 12.0, 45.0   # row colouring thresholds
UI_TICK_MS = 200

BRIDGE_NODE = "v4a_bridge"
DEFAULT_POLL = [s for s in C.DEFAULT_FLEET.split(",") if s]
ALL_NODES = list(C.NODE_IDS)
ID_TO_NAME = {i: n for n, i in C.NODE_IDS.items()}

# --- Lanes -------------------------------------------------------------------
# lat -> (label, cap, clear_lane, warning). `clear_lane` is the byte CMD_CLEAR_PERCEPTS
# takes; None means the firmware refuses to prune it by any path (LaneGenNode.h keeps
# that guard narrow on purpose, so this table must not invent a way around it).
# Caps are the firmware constants, not guesses:
#   TIMESTREAM_MAX_LANE 16 · PERCEPTLEARN_MAX_CLAIMS 8 · PERCEPTLEARN_MAX_LANE 24
#   MOTIONPERCEPT_MAX_TRANSITION_LANE 32 · {ACOUSTIC,MOTION,ENTITY,LINK}PERCEPT_MAX_LANE 48
#   LANEGEN_MAX_LANE 32
LANES = {
    90: ("timeline (@LAT90)", 16, 90,
         "Pruning the TIMELINE lane is the named path lanegen::pruneTimeline — the\n"
         "stream ids it explained ride forward into the @LAT100 boundary, so records\n"
         "stamped with a stream that later lost stay interpretable.\n\nPrune it?"),
    91: ("beliefs (@LAT91)", 8, None, None),
    92: ("outcomes (@LAT92)", 24, 92,
         "⚠ THIS IS DESTRUCTIVE BEYOND ITS OWN LANE.\n\n"
         "Reconciler is a PURE FUNCTION of @LAT92, so emptying the outcome lane\n"
         "returns EVERY @LAT91 belief to baseline on the next Dream Cycle. That is\n"
         "the design — a belief is only as strong as the evidence retained — but it\n"
         "is not the routine cleanup that 94..97 is. The @LAT100 boundary record\n"
         "(**OUTCOMES-CARRIED** + one **BELIEF-AT-BOUNDARY** line per belief) is the\n"
         "only thing that will say what was here.\n\nPrune it?"),
    93: ("transitions (@LAT93)", 32, None, None),
    94: ("acoustic (@LAT94)", 48, 94, None),
    95: ("motion (@LAT95)", 48, 95, None),
    96: ("entity (@LAT96)", 48, 96,
         "@LAT96 carries the Jaccard baseline that semantic positioning Part 2\n"
         "measures its drift threshold against.\n\nPrune it?"),
    97: ("link rssi (@LAT97)", 48, 97, None),
    98: ("adopted beliefs (@LAT98)", None, None, None),
    99: ("sync log (@LAT99)", None, None, None),
    100: ("lane gens (@LAT100)", 32, None, None),
}
CLEAR_ALL_WARN = (
    "Clear ALL percept lanes (94, 95, 96, 97) on {node}?\n\n"
    "⚠ This includes @LAT96, whose Jaccard baseline semantic positioning Part 2\n"
    "needs. If you only meant the link lane, name it: pick @LAT97 and Clear.\n\n"
    "@LAT100 records the boundary, so ordinal citations into the pruned lanes stay\n"
    "readable as history."
)

# A clear rewrites flash, and a node busy rewriting flash can miss the ACK window —
# that is a false negative, not a failed command ([[band-play-ack-false-negative]]),
# so give it more attempts than the CLI default of 4 before believing it.
CLEAR_ATTEMPTS = 8

RECORD_RE = re.compile(r"^@LAT(-?\d+)LON(\d+)\b")


def lane_inventory(text):
    """A TTDB's records grouped by lane -> {lat: {"n": count, "last_lon": int,
    "bytes": int}}. A record is a header line `@LAT<lat>LON<lon> | ...` and everything
    under it until the next one (companion.py `_records`)."""
    inv = {}
    cur = None
    for line in text.splitlines(keepends=True):
        m = RECORD_RE.match(line)
        if m:
            lat, lon = int(m.group(1)), int(m.group(2))
            cur = inv.setdefault(lat, {"n": 0, "last_lon": -1, "bytes": 0})
            cur["n"] += 1
            cur["last_lon"] = max(cur["last_lon"], lon)
        if cur is not None:
            cur["bytes"] += len(line)
    return inv


def fmt_uptime(s):
    if s is None:
        return "-"
    if s >= 3600:
        return f"{s // 3600}h{(s % 3600) // 60:02d}m"
    return f"{s // 60}m{s % 60:02d}s"


@contextlib.contextmanager
def tee_stdout(sink):
    """Route a companion.py function's prints into the UI log. companion's long ops
    (request_ttdb's gap re-requests) report progress on stdout and there is no hook —
    so borrow stdout rather than fork the function. One at a time: two links pulling
    at once would interleave their lines, which the lock prevents."""
    with _STDOUT_LOCK:
        class _W:
            def write(self, s):
                for line in s.splitlines():
                    if line.strip():
                        sink(line.rstrip())

            def flush(self):
                pass
        old = sys.stdout
        sys.stdout = _W()
        try:
            yield
        finally:
            sys.stdout = old


_STDOUT_LOCK = threading.Lock()


def fmt_age(t):
    if not t:
        return "never"
    d = time.time() - t
    if d < 1:
        return "now"
    if d < 100:
        return f"{d:.0f}s"
    return f"{d / 60:.0f}m"


def fmt_ago(t):
    if not t:
        return "never"
    return "just now" if time.time() - t < 1.5 else f"{fmt_age(t)} ago"


def esp32_ports():
    """Every serial port, with the ESP32-S3 native-USB ones marked. The VID/PID is
    (0x303A, 0x1001) — the only reliable way to spot these boards, since COM numbers
    move between plug-ins. It does NOT say WHICH board: the three V4s are identical
    from the outside and only their app image tells them apart (CLAUDE.md)."""
    out = []
    for p in list_ports.comports():
        s3 = (p.vid, p.pid) == (0x303A, 0x1001)
        out.append((p.device, f"{p.device}  {'ESP32-S3' if s3 else (p.description or '')[:28]}",
                    s3))
    return out


# --- The link ----------------------------------------------------------------

class Link:
    """One serial port, owned by one thread for the port's whole open life.

    The thread alternates between (a) draining the job queue — commands and pulls the
    operator asked for — and (b) round-robin probing the fleet. Every reply that
    arrives is attributed by its header src, including ones we did not ask for: the
    V4-A bridge relays PERCEPT/ACK/TTDB_DATA/BELIEF/TIME_RESP from the mesh, so a node
    can appear in the table without ever being polled.
    """

    def __init__(self, name, out_q):
        self.name = name
        self.out = out_q
        self.jobs = queue.Queue()
        self.poll_nodes = []            # replaced wholesale by the UI thread (atomic)
        self.port = None
        self.baud = 115200
        self.reset_on_open = False
        self.declared = None            # which node the operator says this cable is
        self.connected = False
        self.tx = self.rx = 0
        self.last_rx_t = 0.0
        self._thread = None
        self._stop = threading.Event()

    # -- UI thread side --
    def connect(self, port, baud, reset_on_open=False, declared=None):
        if self._thread and self._thread.is_alive():
            return
        self.port, self.baud = port, int(baud)
        self.reset_on_open = reset_on_open
        self.declared = declared
        self._stop.clear()
        self.tx = self.rx = 0
        self._thread = threading.Thread(target=self._run, name=f"link-{self.name}",
                                        daemon=True)
        self._thread.start()

    def disconnect(self):
        self._stop.set()

    def submit(self, label, fn):
        """Run fn(ser, reader, post) on the link thread. Ignored if not connected, so
        a button press on a dead link says so rather than silently doing nothing."""
        if not self.connected:
            self.post("log", f"[{self.name}] not connected — '{label}' ignored")
            return False
        self.jobs.put((label, fn))
        return True

    # -- link thread side --
    def post(self, kind, *args):
        self.out.put((kind, self.name) + args)

    def _run(self):
        try:
            if self.reset_on_open:
                # The reset costs the node its RAM clock offset and ~2.5 s of boot, but
                # it is the only way to read a node's console — the S3's USB CDC only
                # transmits while the host asserts DTR (companion.md §6).
                ser = serial.Serial(self.port, self.baud, timeout=0.05)
                time.sleep(2.5)
            else:
                ser = C.open_serial_no_reset(self.port, self.baud)
                ser.timeout = 0.05
            ser.reset_input_buffer()
        except Exception as e:                                   # pragma: no cover
            self.connected = False
            self.post("state")
            self.post("log", f"[{self.name}] open {self.port} FAILED: {e}")
            return

        self.connected = True
        self.post("state")
        self.post("log", f"[{self.name}] open {self.port} @{self.baud} "
                         f"({'reset+settle' if self.reset_on_open else 'no-reset'})")
        reader = C.SerialFrameReader()
        idx = 0
        next_poll = 0.0
        try:
            while not self._stop.is_set():
                try:
                    label, fn = self.jobs.get_nowait()
                except queue.Empty:
                    label = None
                if label:
                    self.post("busy", label)
                    try:
                        fn(ser, reader, self.post)
                    except Exception as e:
                        self.post("log", f"[{self.name}] {label}: ERROR {e}")
                    self.post("busy", None)
                    continue

                nodes = self.poll_nodes
                if nodes and time.time() >= next_poll:
                    name = nodes[idx % len(nodes)]
                    idx += 1
                    self._probe(ser, reader, name)
                    next_poll = time.time() + POLL_PERIOD_S
                else:
                    self._absorb(ser, reader, 0.1)
        finally:
            try:
                ser.close()
            except Exception:
                pass
            self.connected = False
            self.post("state")
            self.post("log", f"[{self.name}] closed {self.port}")

    def _write(self, ser, frame):
        C.write_serial_frame(ser, frame)
        self.tx += 1

    def _absorb(self, ser, reader, window_s):
        """Read for `window_s` and turn every decodable PERCEPT into a sample. Returns
        the set of node ids heard from."""
        heard = set()
        deadline = time.time() + window_s
        while time.time() < deadline:
            data = ser.read(512)
            if not data:
                continue
            self.last_rx_t = time.time()
            for fr in reader.feed(data):
                t = C.decode_toot(fr)
                if not t:
                    continue
                self.rx += 1
                if t["type"] != C.PERCEPT:
                    continue
                p = t["payload"]
                # The payload type is distinguished by LENGTH — 15/43/45 STATUS,
                # 21 INTERO, 24 GPS — a payload convention over one toot type, which
                # is what lets the bridge forward all three without knowing any of it.
                sample = None
                b = C.parse_intero(p)
                if b is not None:
                    sample = ("intero", b)
                elif len(p) == C.GPS_PERCEPT_PAYLOAD_LEN:
                    g = C.parse_gps(p)
                    if g:
                        sample = ("gps", g)
                else:
                    st = C.parse_status(p)
                    if st:
                        pulse = C.parse_status_pulse(p)
                        if pulse:
                            st["pulse"] = pulse
                        sample = ("status", st)
                if sample:
                    heard.add(t["src"])
                    self.post("sample", t["src"], sample[0], sample[1])
        return heard

    def _probe(self, ser, reader, node_name):
        """One node, one window: ask for its STATUS and its INTEROCEPTION together and
        listen once. Fresh ms-resolution seqs per probe, or the radio dedup drops the
        repeat ([[dedup-radio-only]] — the USB link is not deduped, the air path is)."""
        tid = C.NODE_IDS.get(node_name)
        if tid is None:
            return
        base = int(time.time() * 1000) & 0x7FFFFFFF
        for k, op in enumerate((C.CMD_GET_STATUS, C.CMD_GET_INTERO)):
            payload = bytes([op]) + struct.pack("<I", tid)
            self._write(ser, C.encode_toot(C.CMD, C.ORCHESTRATOR_ID,
                                           (base + k) & 0x7FFFFFFF, payload))
        self._absorb(ser, reader, PROBE_WINDOW_S)


# --- Jobs (run on a link thread) ---------------------------------------------

def send_reliable_quiet(ser, reader, frame, target, seq, log, rto0=0.5, attempts=4):
    """companion.send_reliable's retransmit rule, logging to the UI instead of stdout.
    Retransmits reuse the original (src,seq) so the receiver's dedup re-ACKs the
    duplicate (TTN-RFC-0007 §5). Returns the 1-based attempt ACKed, or 0."""
    rto = rto0
    for attempt in range(1, attempts + 1):
        C.write_serial_frame(ser, frame)
        deadline = time.time() + rto
        while time.time() < deadline:
            data = ser.read(256)
            if not data:
                continue
            for fr in reader.feed(data):
                t = C.decode_toot(fr)
                if not t or t["type"] != C.ACK:
                    continue
                if target != C.NODE_BROADCAST and t["src"] != target:
                    continue
                pa = C.parse_ack(t)
                if pa and pa[0] == C.ORCHESTRATOR_ID and pa[1] == seq and pa[2] == 0:
                    return attempt
        log(f"  no ACK within {rto:.2f}s (attempt {attempt}/{attempts})")
        rto *= 2
    return 0


def job_cmd(node_name, op_name, args=b"", detail="", attempts=4, rto0=0.5):
    """A want_ack CMD to one node (or broadcast), confirmed by its ACK."""
    target = (C.NODE_BROADCAST if node_name == "broadcast" else C.NODE_IDS[node_name])
    opcode = C.CMD_OPS[op_name]     # KeyError here is a UI bug, not operator input

    def run(ser, reader, post):
        log = lambda s: post("log", s)  # noqa: E731
        payload = bytes([opcode]) + struct.pack("<I", target) + args
        seq = int(time.time() * 1000) & 0x7FFFFFFF
        frame = C.encode_toot(C.CMD, C.ORCHESTRATOR_ID, seq, payload,
                              flags=C.FLAG_WANT_ACK)
        log(f"cmd {op_name}{detail} -> {node_name} (0x{target:08X})")
        acked = send_reliable_quiet(ser, reader, frame, target, seq, log,
                                    rto0=rto0, attempts=attempts)
        if acked:
            log(f"  ACK from {node_name} on attempt {acked} — APPLIED")
        else:
            log(f"  no ACK after {attempts} attempts — UNCONFIRMED. A slow op (a flash "
                f"rewrite, a blocking tone) can eat its own ACK window: ping the node, "
                f"then re-read rather than assuming it did nothing.")
        post("cmd_done", node_name, op_name, bool(acked))
    return run


def job_pull(node_name, out_path, via_bridge_warn):
    """Pull a node's whole TTDB and hand the lane inventory back to the UI."""
    target = C.NODE_IDS[node_name]

    def run(ser, reader, post):
        log = lambda s: post("log", s)  # noqa: E731
        if via_bridge_warn:
            log("  ⚠ pulling THROUGH the bridge: on a grown TTDB this is intermittent "
                "and can return truncated or silently stitched data. The node's own "
                "cable is the byte-exact path (CLAUDE.md).")
        log(f"pull whole TTDB from {node_name} (0x{target:08X}) ...")
        t0 = time.time()
        with tee_stdout(lambda s: log("  " + s.strip())):
            data = C.request_ttdb(ser, reader, target, timeout=25.0,
                                  mode=C.TTDB_REQ_WHOLE)
        if not data:
            log("  no data received — check the node is powered and on this link")
            post("lanes", node_name, None, None, None)
            return
        os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
        with open(out_path, "wb") as f:
            f.write(data)
        text = data.decode("utf-8", "replace")
        log(f"  {len(data)} B in {time.time() - t0:.1f}s -> {out_path}")
        post("lanes", node_name, lane_inventory(text), len(data), out_path)
    return run


def job_clear(node_name, lane):
    """CMD_CLEAR_PERCEPTS with an explicit lane byte, then re-pull so the lane counts
    on screen are read back off flash rather than assumed."""
    target = C.NODE_IDS[node_name]
    label = f"lane {lane}" if lane else "ALL percept lanes (94-97)"

    def run(ser, reader, post):
        log = lambda s: post("log", s)  # noqa: E731
        payload = (bytes([C.CMD_CLEAR_PERCEPTS]) + struct.pack("<I", target)
                   + bytes([lane]))
        seq = int(time.time() * 1000) & 0x7FFFFFFF
        frame = C.encode_toot(C.CMD, C.ORCHESTRATOR_ID, seq, payload,
                              flags=C.FLAG_WANT_ACK)
        log(f"clear-percepts {label} -> {node_name} (0x{target:08X})")
        acked = send_reliable_quiet(ser, reader, frame, target, seq, log,
                                    rto0=0.6, attempts=CLEAR_ATTEMPTS)
        if acked:
            log(f"  ACK on attempt {acked} — pruned. Re-pull to see the new counts and "
                f"the @LAT100 boundary record.")
        else:
            log("  no ACK — a prune REWRITES FLASH and can be busy through its own ACK "
                "window, so this is unconfirmed, NOT proof it did nothing. Re-pull.")
        post("cmd_done", node_name, "clear-percepts", bool(acked))
    return run


# --- The window ---------------------------------------------------------------

class FleetUI(tk.Tk):
    def __init__(self, bridge_port=None, aux_port=None, autoconnect=True):
        super().__init__()
        self.title("robot_team — fleet console")
        self.geometry("1360x860")
        self.minsize(1100, 700)

        self.events = queue.Queue()
        self.links = {"bridge": Link("bridge", self.events),
                      "aux": Link("aux", self.events)}
        self.busy = {"bridge": None, "aux": None}
        # node name -> merged live view
        self.nodes = {n: {"name": n, "id": i, "poll": n in DEFAULT_POLL,
                          "last_t": 0.0, "link": "", "status": None, "intero": None,
                          "gps": None}
                      for n, i in C.NODE_IDS.items()}
        self.lane_inv = {}          # node -> {lat: {...}}
        self.lane_meta = {}         # node -> (path, bytes, when)
        self.selected = tk.StringVar(value=BRIDGE_NODE)

        self._build()
        self._refresh_ports()
        if bridge_port and autoconnect:
            self.bridge_port.set(bridge_port)
            self._toggle_link("bridge")
        if aux_port and autoconnect:
            self.aux_port.set(aux_port)
            self._toggle_link("aux")
        self.after(UI_TICK_MS, self._tick)
        self.protocol("WM_DELETE_WINDOW", self._quit)

    # ---- layout ----
    def _build(self):
        style = ttk.Style(self)
        try:
            style.theme_use("clam")
        except tk.TclError:
            pass
        style.configure("Treeview", rowheight=21)
        style.configure("Hdr.TLabel", font=("Segoe UI", 9, "bold"))

        root = ttk.Frame(self, padding=6)
        root.pack(fill="both", expand=True)
        root.columnconfigure(0, weight=1)
        root.rowconfigure(1, weight=3)
        root.rowconfigure(2, weight=2)

        self._build_links(root).grid(row=0, column=0, sticky="ew", pady=(0, 6))

        mid = ttk.PanedWindow(root, orient="horizontal")
        mid.grid(row=1, column=0, sticky="nsew")
        mid.add(self._build_fleet(mid), weight=3)
        mid.add(self._build_map(mid), weight=2)

        bot = ttk.PanedWindow(root, orient="horizontal")
        bot.grid(row=2, column=0, sticky="nsew", pady=(6, 0))
        bot.add(self._build_lanes(bot), weight=2)
        right = ttk.Frame(bot)
        right.rowconfigure(1, weight=1)
        right.columnconfigure(0, weight=1)
        self._build_controls(right).grid(row=0, column=0, sticky="ew")
        self._build_log(right).grid(row=1, column=0, sticky="nsew", pady=(6, 0))
        bot.add(right, weight=3)

    def _build_links(self, parent):
        f = ttk.LabelFrame(parent, text="links", padding=6)
        f.columnconfigure(9, weight=1)

        # -- the bridge: the fleet's front door, and the one link worth its own row --
        ttk.Label(f, text="V4-A BRIDGE", style="Hdr.TLabel").grid(row=0, column=0,
                                                                  sticky="w")
        self.bridge_port = tk.StringVar()
        self.bridge_combo = ttk.Combobox(f, textvariable=self.bridge_port, width=26,
                                         state="readonly")
        self.bridge_combo.grid(row=0, column=1, padx=4)
        self.bridge_baud = tk.StringVar(value="115200")
        ttk.Entry(f, textvariable=self.bridge_baud, width=7).grid(row=0, column=2)
        self.bridge_reset = tk.BooleanVar(value=False)
        ttk.Checkbutton(f, text="reset on open", variable=self.bridge_reset).grid(
            row=0, column=3, padx=4)
        self.bridge_btn = ttk.Button(f, text="Connect",
                                     command=lambda: self._toggle_link("bridge"))
        self.bridge_btn.grid(row=0, column=4, padx=2)
        self.bridge_dot = tk.Canvas(f, width=14, height=14, highlightthickness=0)
        self.bridge_dot.grid(row=0, column=5, padx=(6, 2))
        self.bridge_state = ttk.Label(f, text="disconnected")
        self.bridge_state.grid(row=0, column=6, sticky="w")

        # -- the second cable, whatever it happens to be today --
        ttk.Label(f, text="AUX USB", style="Hdr.TLabel").grid(row=1, column=0,
                                                              sticky="w", pady=(4, 0))
        self.aux_port = tk.StringVar()
        self.aux_combo = ttk.Combobox(f, textvariable=self.aux_port, width=26,
                                      state="readonly")
        self.aux_combo.grid(row=1, column=1, padx=4, pady=(4, 0))
        self.aux_baud = tk.StringVar(value="115200")
        ttk.Entry(f, textvariable=self.aux_baud, width=7).grid(row=1, column=2,
                                                               pady=(4, 0))
        self.aux_declared = tk.StringVar(value="v4b_relay")
        ttk.Combobox(f, textvariable=self.aux_declared, width=12, state="readonly",
                     values=ALL_NODES).grid(row=1, column=3, padx=4, pady=(4, 0))
        self.aux_btn = ttk.Button(f, text="Connect",
                                  command=lambda: self._toggle_link("aux"))
        self.aux_btn.grid(row=1, column=4, padx=2, pady=(4, 0))
        self.aux_dot = tk.Canvas(f, width=14, height=14, highlightthickness=0)
        self.aux_dot.grid(row=1, column=5, padx=(6, 2), pady=(4, 0))
        self.aux_state = ttk.Label(f, text="disconnected")
        self.aux_state.grid(row=1, column=6, sticky="w", pady=(4, 0))

        ttk.Button(f, text="Rescan ports", command=self._refresh_ports).grid(
            row=0, column=7, padx=6)
        self.ports_label = ttk.Label(f, text="", foreground="#555")
        self.ports_label.grid(row=1, column=7, columnspan=3, sticky="w", padx=6,
                              pady=(4, 0))
        # The one thing a port cannot tell you, stated where the choice is made.
        ttk.Label(f, foreground="#8a5a00",
                  text="a reply on a port does not prove which board it is — the three "
                       "V4s are identical from outside\nand a reply can arrive over the "
                       "air; the aux node is DECLARED, not detected").grid(
            row=0, column=8, rowspan=2, sticky="w", padx=10)
        return f

    def _build_fleet(self, parent):
        f = ttk.LabelFrame(parent, text="fleet — double-click a row to poll / stop "
                                        "polling it", padding=4)
        cols = ("poll", "node", "id", "link", "seen", "bat", "pct", "die", "mem",
                "up", "lp", "bpm", "cond", "band", "temp", "cursor")
        widths = (34, 88, 74, 52, 48, 54, 42, 48, 54, 62, 46, 42, 60, 96, 48, 74)
        heads = ("·", "node", "id", "via", "seen", "volts", "%", "die C", "mem KB",
                 "up", "lp ms", "bpm", "conductor", "band/clock", "temp", "cursor")
        self.tree = ttk.Treeview(f, columns=cols, show="headings", selectmode="browse")
        for c, w, h in zip(cols, widths, heads):
            self.tree.heading(c, text=h)
            self.tree.column(c, width=w, anchor="w" if c in ("node", "cond", "band")
                             else "center", stretch=False)
        for name in ALL_NODES:
            self.tree.insert("", "end", iid=name, values=self._row_values(name))
        self.tree.tag_configure("fresh", background="#e8f6e8")
        self.tree.tag_configure("stale", background="#fdf6e3")
        self.tree.tag_configure("dead", background="#f4f4f4", foreground="#909090")
        self.tree.bind("<<TreeviewSelect>>", self._on_select)
        self.tree.bind("<Double-1>", self._on_toggle_poll)
        vs = ttk.Scrollbar(f, orient="vertical", command=self.tree.yview)
        hs = ttk.Scrollbar(f, orient="horizontal", command=self.tree.xview)
        self.tree.configure(yscrollcommand=vs.set, xscrollcommand=hs.set)
        f.rowconfigure(0, weight=1)
        f.columnconfigure(0, weight=1)
        self.tree.grid(row=0, column=0, sticky="nsew")
        vs.grid(row=0, column=1, sticky="ns")
        hs.grid(row=1, column=0, sticky="ew")
        self.tree.selection_set(BRIDGE_NODE)
        return f

    def _build_map(self, parent):
        f = ttk.LabelFrame(parent, text="global view", padding=4)
        self.canvas = tk.Canvas(f, background="#ffffff", highlightthickness=0)
        self.canvas.pack(fill="both", expand=True)
        self.map_note = ttk.Label(f, text="", foreground="#555")
        self.map_note.pack(anchor="w")
        self._load_positions()
        return f

    def _build_lanes(self, parent):
        f = ttk.LabelFrame(parent, text="lanes", padding=4)
        top = ttk.Frame(f)
        top.pack(fill="x")
        self.lane_head = ttk.Label(top, text="(no TTDB pulled)", style="Hdr.TLabel")
        self.lane_head.pack(side="left")
        ttk.Label(top, text="  via ").pack(side="left")
        self.pull_via = tk.StringVar(value="bridge")
        ttk.Combobox(top, textvariable=self.pull_via, width=7, state="readonly",
                     values=["bridge", "aux"]).pack(side="left")
        ttk.Button(top, text="Pull TTDB", command=self._do_pull).pack(side="left",
                                                                      padx=4)
        ttk.Button(top, text="Open file…", command=self._load_lane_file).pack(
            side="left")

        cols = ("lane", "what", "n", "cap", "use", "bytes")
        self.lanes_tree = ttk.Treeview(f, columns=cols, show="headings", height=9,
                                       selectmode="browse")
        for c, w, h, a in (("lane", 48, "lane", "center"), ("what", 150, "what", "w"),
                           ("n", 46, "recs", "center"), ("cap", 46, "cap", "center"),
                           ("use", 128, "fill", "w"), ("bytes", 66, "bytes", "e")):
            self.lanes_tree.heading(c, text=h)
            self.lanes_tree.column(c, width=w, anchor=a, stretch=(c == "use"))
        self.lanes_tree.tag_configure("full", background="#fde8e8")
        self.lanes_tree.tag_configure("high", background="#fdf6e3")
        self.lanes_tree.tag_configure("locked", foreground="#909090")
        self.lanes_tree.pack(fill="both", expand=True, pady=4)

        row = ttk.Frame(f)
        row.pack(fill="x")
        self.clear_btn = ttk.Button(row, text="Clear selected lane",
                                    command=self._do_clear_selected)
        self.clear_btn.pack(side="left")
        ttk.Button(row, text="Clear ALL 94–97",
                   command=lambda: self._do_clear(0)).pack(side="left", padx=4)
        self.lane_note = ttk.Label(f, foreground="#555",
                                   text="98/99 are unreachable by any path; 91/93/100 "
                                        "have no prune path in firmware")
        self.lane_note.pack(anchor="w")
        return f

    def _build_controls(self, parent):
        f = ttk.LabelFrame(parent, text="controls — act on the selected node", padding=6)
        r = ttk.Frame(f)
        r.pack(fill="x")
        ttk.Button(r, text="Ping", command=lambda: self._cmd("ping")).pack(side="left")
        ttk.Button(r, text="Intero now", command=self._probe_now).pack(side="left",
                                                                       padx=3)
        ttk.Separator(r, orient="vertical").pack(side="left", fill="y", padx=6)
        ttk.Label(r, text="beep").pack(side="left")
        self.freq = tk.StringVar(value="880")
        ttk.Entry(r, textvariable=self.freq, width=6).pack(side="left", padx=2)
        self.dur = tk.StringVar(value="200")
        ttk.Entry(r, textvariable=self.dur, width=5).pack(side="left")
        ttk.Button(r, text="Beep", command=self._do_beep).pack(side="left", padx=3)
        ttk.Separator(r, orient="vertical").pack(side="left", fill="y", padx=6)
        self.rgb = tk.StringVar(value="FF0000")
        ttk.Entry(r, textvariable=self.rgb, width=8).pack(side="left")
        ttk.Button(r, text="LED", command=self._do_led).pack(side="left", padx=2)
        ttk.Button(r, text="LED off",
                   command=lambda: self._cmd("clear-led")).pack(side="left")

        r2 = ttk.Frame(f)
        r2.pack(fill="x", pady=(6, 0))
        ttk.Label(r2, text="band:").pack(side="left")
        ttk.Button(r2, text="Play", command=lambda: self._cmd("play")).pack(side="left",
                                                                            padx=2)
        ttk.Button(r2, text="Stop", command=lambda: self._cmd("stop")).pack(side="left")
        ttk.Label(r2, text="  scene").pack(side="left")
        self.scene = tk.StringVar(value="0")
        ttk.Spinbox(r2, textvariable=self.scene, from_=0, to=99, width=4).pack(
            side="left", padx=2)
        # Only the CONDUCTOR owns the chart, so broadcast is the safe address here:
        # exactly one node answers ([[pulse-chart-scene]]), and it avoids resetting a
        # cabled node to reach it.
        ttk.Button(r2, text="Set scene (broadcast)",
                   command=self._do_scene).pack(side="left", padx=3)
        ttk.Separator(r2, orient="vertical").pack(side="left", fill="y", padx=6)
        ttk.Label(r2, text="sense ms").pack(side="left")
        self.interval = tk.StringVar(value="300")
        ttk.Entry(r2, textvariable=self.interval, width=6).pack(side="left", padx=2)
        ttk.Button(r2, text="Set interval",
                   command=self._do_interval).pack(side="left")
        return f

    def _build_log(self, parent):
        f = ttk.LabelFrame(parent, text="log", padding=4)
        self.log = tk.Text(f, height=9, wrap="word", font=("Consolas", 9),
                           state="disabled", background="#fbfbfb")
        vs = ttk.Scrollbar(f, orient="vertical", command=self.log.yview)
        self.log.configure(yscrollcommand=vs.set)
        self.log.pack(side="left", fill="both", expand=True)
        vs.pack(side="right", fill="y")
        return f

    # ---- helpers ----
    def _say(self, text):
        self.log.configure(state="normal")
        self.log.insert("end", f"{time.strftime('%H:%M:%S')} {text}\n")
        if float(self.log.index("end-1c").split(".")[0]) > 800:
            self.log.delete("1.0", "200.0")
        self.log.see("end")
        self.log.configure(state="disabled")

    def _refresh_ports(self):
        ports = esp32_ports()
        vals = [lbl for _, lbl, _ in ports]
        self._port_map = {lbl: dev for dev, lbl, _ in ports}
        self.bridge_combo.configure(values=vals)
        self.aux_combo.configure(values=vals)
        n_s3 = sum(1 for _, _, s3 in ports if s3)
        self.ports_label.configure(
            text=f"{len(ports)} port(s), {n_s3} ESP32-S3 (VID_303A&PID_1001)")

    def _dev(self, var):
        v = var.get()
        return self._port_map.get(v, v.split()[0] if v else "")

    def sel_node(self):
        s = self.tree.selection()
        return s[0] if s else BRIDGE_NODE

    def link_for(self, node_name, prefer=None):
        """Which link should carry traffic for this node. The aux cable wins for the
        node it is declared to be — that is the byte-exact path for a pull — otherwise
        the bridge, which is how the mesh is reached at all."""
        aux, br = self.links["aux"], self.links["bridge"]
        if prefer == "aux" and aux.connected:
            return aux, (aux.declared != node_name)
        if prefer == "bridge" and br.connected:
            return br, (node_name != BRIDGE_NODE)
        if aux.connected and aux.declared == node_name:
            return aux, False
        if br.connected:
            return br, (node_name != BRIDGE_NODE)
        if aux.connected:
            return aux, True
        return None, False

    # ---- link buttons ----
    def _toggle_link(self, which):
        link = self.links[which]
        if link.connected:
            link.disconnect()
            return
        if which == "bridge":
            dev, baud, reset = (self._dev(self.bridge_port), self.bridge_baud.get(),
                                self.bridge_reset.get())
            declared = BRIDGE_NODE
        else:
            dev, baud, reset = self._dev(self.aux_port), self.aux_baud.get(), False
            declared = self.aux_declared.get()
        if not dev:
            messagebox.showwarning("no port", "Pick a serial port first.")
            return
        link.connect(dev, baud, reset_on_open=reset, declared=declared)
        self._repoll()

    def _repoll(self):
        """Split the polled nodes between the links: the aux cable polls only the node
        it is declared to be (its own board, no air hop), the bridge polls the rest."""
        aux, br = self.links["aux"], self.links["bridge"]
        if aux.connected:
            aux.declared = self.aux_declared.get()   # the operator may have re-declared
        want = [n for n in ALL_NODES if self.nodes[n]["poll"]]
        aux_list = [n for n in want if aux.connected and aux.declared == n]
        aux.poll_nodes = aux_list
        br.poll_nodes = [n for n in want if n not in aux_list] if br.connected else []
        if not br.connected and aux.connected:
            aux.poll_nodes = want

    # ---- command buttons ----
    def _dispatch(self, node_name, label, job, prefer=None):
        link, _ = self.link_for(node_name, prefer or self.pull_via.get())
        if link is None:
            messagebox.showwarning("no link", "Connect the bridge or an aux cable first.")
            return None
        link.submit(label, job)
        return link

    def _cmd(self, op, node=None, args=b"", detail=""):
        node = node or self.sel_node()
        self._dispatch(node, f"{op} {node}", job_cmd(node, op, args, detail))

    def _do_beep(self):
        try:
            f, d = int(self.freq.get()), int(self.dur.get())
        except ValueError:
            return messagebox.showwarning("beep", "freq and duration must be integers")
        self._cmd("beep", args=struct.pack("<HH", f & 0xFFFF, d & 0xFFFF),
                  detail=f" {f}Hz/{d}ms")

    def _do_led(self):
        try:
            rgb = bytes.fromhex(self.rgb.get())
            assert len(rgb) == 3
        except Exception:
            return messagebox.showwarning("led", "colour must be 6 hex digits, RRGGBB")
        self._cmd("set-led", args=rgb, detail=f" #{self.rgb.get()}")

    def _do_interval(self):
        try:
            ms = int(self.interval.get())
        except ValueError:
            return messagebox.showwarning("interval", "must be an integer (ms)")
        self._cmd("set-interval", args=struct.pack("<H", ms & 0xFFFF), detail=f" {ms}ms")

    def _do_scene(self):
        try:
            s = int(self.scene.get())
        except ValueError:
            return messagebox.showwarning("scene", "must be an integer")
        self._dispatch(self.sel_node(), f"set-scene {s}",
                       job_cmd("broadcast", "set-scene", struct.pack("<H", s & 0xFFFF),
                               f" scene {s}"))
        self._say(f"set-scene {s} sent to broadcast — only the CONDUCTOR applies it; "
                  f"every other node learns the scene from the next beacon")

    def _probe_now(self):
        """Jump the round-robin for the selected node instead of waiting for its turn."""
        node = self.sel_node()
        link, _ = self.link_for(node, self.pull_via.get())
        if link is None:
            return messagebox.showwarning("no link", "Connect a link first.")

        def run(ser, reader, post):
            link._probe(ser, reader, node)
            link._absorb(ser, reader, 0.6)   # a second helping for a slow air path
        link.submit(f"probe {node}", run)

    # ---- lanes ----
    def _do_pull(self):
        node = self.sel_node()
        out = os.path.join(REPO, "master", "ui", f"{node}.md")
        link, bridged = self.link_for(node, self.pull_via.get())
        if link is None:
            return messagebox.showwarning("no link", "Connect a link first.")
        link.submit(f"pull {node}", job_pull(node, out, bridged))

    def _load_lane_file(self):
        """Read lanes out of an already-pulled TTDB — the right move when the node is
        under measurement, since opening its own port restarts its 60 s window."""
        path = filedialog.askopenfilename(
            initialdir=os.path.join(REPO, "master"),
            filetypes=[("TTDB markdown", "*.md"), ("all", "*.*")])
        if not path:
            return
        with open(path, "rb") as f:
            data = f.read()
        node = self.sel_node()
        self._set_lanes(node, lane_inventory(data.decode("utf-8", "replace")),
                        len(data), path)

    def _set_lanes(self, node, inv, nbytes, path):
        self.lane_inv[node] = inv
        self.lane_meta[node] = (path, nbytes, time.time())
        if node == self.sel_node():
            self._render_lanes()

    def _render_lanes(self):
        if not hasattr(self, "lanes_tree"):
            return          # a selection event can beat the panel into existence
        node = self.sel_node()
        self.lanes_tree.delete(*self.lanes_tree.get_children())
        inv = self.lane_inv.get(node)
        meta = self.lane_meta.get(node)
        if inv is None:
            self.lane_head.configure(text=f"{node}: (no TTDB pulled)")
            return
        path, nbytes, when = meta
        self.lane_head.configure(
            text=f"{node}: {nbytes} B, {sum(v['n'] for v in inv.values())} records, "
                 f"read {fmt_ago(when)}")
        # Every lane the firmware knows about, whether or not it has records yet — an
        # empty percept lane is a fact about the node, not an absence of information.
        lats = sorted(set(LANES) | set(inv))
        for lat in lats:
            label, cap, clear, _ = LANES.get(lat, ("records (identity/beliefs)",
                                                   None, None, None))
            n = inv.get(lat, {}).get("n", 0)
            b = inv.get(lat, {}).get("bytes", 0)
            if lat < 90 and lat not in LANES:
                label = "node records"
            tags = []
            if cap:
                frac = n / cap
                fill = "█" * int(round(frac * 12)) + "·" * (12 - int(round(frac * 12)))
                use = f"{fill} {n * 100 // cap}%"
                if n >= cap:
                    tags.append("full")
                elif frac >= 0.75:
                    tags.append("high")
            else:
                use = ""
            if clear is None:
                tags.append("locked")
                # Say so only for lanes the firmware HAS an opinion about — the
                # identity/belief records below @LAT90 were never prunable material.
                if lat in LANES:
                    label += "  (no prune path)"
            self.lanes_tree.insert("", "end", iid=str(lat),
                                   values=(lat, label, n, cap or "-", use, b),
                                   tags=tuple(tags))

    def _do_clear_selected(self):
        sel = self.lanes_tree.selection()
        if not sel:
            return messagebox.showinfo("clear", "Pick a lane row first, or use "
                                                "'Clear ALL 94–97'.")
        lat = int(sel[0])
        entry = LANES.get(lat)
        if not entry or entry[2] is None:
            return messagebox.showwarning(
                "clear", f"@LAT{lat} has no prune path in firmware.\n\n"
                         "LaneGenNode.h keeps that guard narrow deliberately — 98/99 "
                         "stay unreachable by any path, and 91/93/100 are written as "
                         "consequences of other lanes rather than pruned directly.")
        self._do_clear(entry[2])

    def _do_clear(self, lane):
        node = self.sel_node()
        if lane == 0:
            msg = CLEAR_ALL_WARN.format(node=node)
        else:
            label, _, _, warn = LANES[lane]
            msg = f"Clear {label} on {node}?\n\n" + (warn or
                  "@LAT100 records the boundary this prune creates, so the ordinal "
                  "citations into the pruned lane stay readable as history.")
        if not messagebox.askyesno("confirm prune", msg, icon="warning"):
            return
        link, _ = self.link_for(node, self.pull_via.get())
        if link is None:
            return messagebox.showwarning("no link", "Connect a link first.")
        link.submit(f"clear {lane} {node}", job_clear(node, lane))

    # ---- fleet table + map ----
    def _row_values(self, name):
        d = self.nodes[name]
        b, st = d["intero"], d["status"]
        pulse = (st or {}).get("pulse") or {}
        cond_id = (b or {}).get("conductor_id") or pulse.get("conductor_id") or 0
        cond = ID_TO_NAME.get(cond_id, f"0x{cond_id:08X}" if cond_id else "-")
        if b and b.get("conductor"):
            cond += " *"
        band = ""
        if b:
            band = ("clk+" if b["synced"] else "clk-")
            if b["playing"]:
                band += " chart"
            if b["voicing"]:
                band += " SING"
        elif pulse:
            band = ("chart " if pulse.get("playing") else "") + f"beat {pulse.get('beat_in_bar', '-')}"
        bpm = ""
        if b and b.get("beat_period_ms"):
            bpm = 60000 // b["beat_period_ms"]
        elif pulse.get("period_ms"):
            bpm = 60000 // pulse["period_ms"]
        volts = f"{b['bat_mv'] / 1000:.3f}" if b and b.get("bat_mv") else ("0.000" if b else "")
        pct = "" if not b else ("--" if b["bat_pct"] is None else f"{b['bat_pct']}%")
        if b and b.get("bat_trend"):
            pct += {1: "↑", -1: "↓"}.get(b["bat_trend"], "")
        return (
            "✓" if d["poll"] else "·",
            name,
            f"0x{d['id']:08X}",
            d["link"],
            fmt_age(d["last_t"]),
            volts,
            pct,
            f"{b['die_c']:.1f}" if b else "",
            b["maxalloc_kb"] if b else "",
            fmt_uptime(b["uptime_s"]) if b else "",
            b["worst_loop_ms"] if b else "",
            bpm,
            cond if (b or pulse) else "",
            band,
            f"{st['temp_c']:.1f}" if st else "",
            f"@L{st['cursor'][0]}L{st['cursor'][1]}" if st else "",
        )

    def _render_fleet(self):
        now = time.time()
        for name in ALL_NODES:
            d = self.nodes[name]
            age = now - d["last_t"] if d["last_t"] else 1e9
            tag = "fresh" if age < FRESH_S else ("stale" if age < STALE_S else "dead")
            self.tree.item(name, values=self._row_values(name), tags=(tag,))

    def _load_positions(self):
        """The map's frame: SP2 position beliefs if the fleet has embedded itself,
        else nothing and we fall back to a ring."""
        self.positions, self.edges = {}, {}
        p = os.path.join(REPO, "master", "positions.md")
        q = os.path.join(REPO, "master", "proximity.md")
        try:
            if os.path.exists(p):
                self.positions = C._parse_positions_full(p)
            if os.path.exists(q):
                self.edges = C._parse_proximity(q)
        except Exception as e:                                     # pragma: no cover
            self._say(f"positions.md/proximity.md unreadable: {e}")

    def _render_map(self):
        cv = self.canvas
        cv.delete("all")
        W = max(cv.winfo_width(), 60)
        H = max(cv.winfo_height(), 60)
        now = time.time()
        shown = [n for n in ALL_NODES
                 if self.nodes[n]["poll"] or self.nodes[n]["last_t"]]
        if not shown:
            shown = DEFAULT_POLL
        pos = {n: (self.positions[n]["x_m"], self.positions[n]["y_m"])
               for n in shown if n in self.positions}
        # Anything with no position belief still has to be somewhere: park it on a ring
        # around the believed cloud, drawn hollow so it never reads as a measurement.
        placed = dict(pos)
        if pos:
            xs = [v[0] for v in pos.values()]
            ys = [v[1] for v in pos.values()]
            cx, cy = (min(xs) + max(xs)) / 2, (min(ys) + max(ys)) / 2
            ring = max(max(xs) - min(xs), max(ys) - min(ys), 1.0) * 0.75
        else:
            cx = cy = 0.0
            ring = 1.0
        unplaced = [n for n in shown if n not in placed]
        for k, n in enumerate(unplaced):
            a = 2 * math.pi * k / max(len(unplaced), 1)
            placed[n] = (cx + math.cos(a) * ring, cy + math.sin(a) * ring)
        if not placed:
            return

        # Fit the WHOLE cast — believed and merely drawn — inside the canvas, so a
        # ring node can never be clipped off the edge and read as absent.
        xs = [v[0] for v in placed.values()]
        ys = [v[1] for v in placed.values()]
        x0, y0 = min(xs), min(ys)
        span = max(max(xs) - x0, max(ys) - y0, 0.5)
        pad = 46
        sc = min(W - 2 * pad, H - 2 * pad) / span

        def to_px(x, y):
            return (pad + (x - x0) * sc + (W - 2 * pad - span * sc) / 2,
                    H - pad - (y - y0) * sc - (H - 2 * pad - span * sc) / 2)

        px = {n: to_px(*placed[n]) for n in placed}
        for pair, e in self.edges.items():
            a, b = tuple(pair)
            if a in px and b in px:
                cv.create_line(*px[a], *px[b], fill="#d8d8d8")
                mx, my = (px[a][0] + px[b][0]) / 2, (px[a][1] + px[b][1]) / 2
                cv.create_text(mx, my, text=f"{e['dist_est_m']:.0f}m", fill="#b0b0b0",
                               font=("Segoe UI", 7))
        for n, (x, y) in px.items():
            d = self.nodes[n]
            age = now - d["last_t"] if d["last_t"] else 1e9
            fill = "#3fa34d" if age < FRESH_S else ("#d9a441" if age < STALE_S
                                                    else "#c8c8c8")
            r = 13
            believed = n in pos
            cv.create_oval(x - r, y - r, x + r, y + r, fill=fill,
                           outline="#404040" if believed else "#c0c0c0",
                           dash=() if believed else (3, 3))
            b = d["intero"]
            if b and b.get("bat_pct") is not None:
                # A battery ring, so charge is readable without reading a number.
                cv.create_arc(x - r - 5, y - r - 5, x + r + 5, y + r + 5,
                              start=90, extent=-359.9 * b["bat_pct"] / 100.0,
                              style="arc", outline="#2b6cb0", width=3)
            if b and b.get("conductor"):
                cv.create_text(x, y - r - 14, text="★ baton", fill="#8a5a00",
                               font=("Segoe UI", 8, "bold"))
            label = C.FLEET_FRIENDLY.get(n, n)
            cv.create_text(x, y, text=label, fill="#ffffff",
                           font=("Segoe UI", 8, "bold"))
            sub = fmt_age(d["last_t"])
            if b:
                sub += f" · {b['worst_loop_ms']}ms"
                if b.get("bat_pct") is not None:
                    sub += f" · {b['bat_pct']}%"
            cv.create_text(x, y + r + 11, text=sub, fill="#555",
                           font=("Segoe UI", 8))
        self.map_note.configure(
            text=("frame: relative SP2 embedding (master/positions.md) — solid = a "
                  "position belief, dashed = placed for display only"
                  if pos else
                  "no master/positions.md — laid out on a ring, which is drawing, not "
                  "belief"))

    # ---- events ----
    def _on_select(self, _evt=None):
        self._render_lanes()

    def _on_toggle_poll(self, evt):
        row = self.tree.identify_row(evt.y)
        if not row:
            return
        self.nodes[row]["poll"] = not self.nodes[row]["poll"]
        self._repoll()
        self._render_fleet()

    def _tick(self):
        drained = 0
        while drained < 400:
            try:
                ev = self.events.get_nowait()
            except queue.Empty:
                break
            drained += 1
            kind, link = ev[0], ev[1]
            if kind == "log":
                self._say(ev[2])
            elif kind == "busy":
                self.busy[link] = ev[2]
            elif kind == "state":
                self._repoll()
            elif kind == "cmd_done":
                pass
            elif kind == "lanes":
                node, inv, nbytes, path = ev[2], ev[3], ev[4], ev[5]
                if inv is not None:
                    self._set_lanes(node, inv, nbytes, path)
            elif kind == "sample":
                src, what, data = ev[2], ev[3], ev[4]
                name = ID_TO_NAME.get(src)
                if name is None:
                    continue
                d = self.nodes[name]
                d[what] = data
                d["last_t"] = time.time()
                d["link"] = link
        self._render_links()
        self._render_fleet()
        self._render_map()
        self.after(UI_TICK_MS, self._tick)

    def _render_links(self):
        for which, dot, lbl, btn in (
                ("bridge", self.bridge_dot, self.bridge_state, self.bridge_btn),
                ("aux", self.aux_dot, self.aux_state, self.aux_btn)):
            link = self.links[which]
            dot.delete("all")
            if link.connected:
                node = link.declared
                seen = self.nodes.get(node, {}).get("last_t", 0)
                # A port that is open is not the same as a node that is answering, so
                # the dot reports the ANSWER, and the text reports the port.
                answering = seen and (time.time() - seen) < STALE_S
                colour = "#3fa34d" if answering else "#d9a441"
                heard = f"{node} replied {fmt_ago(seen)}" if seen \
                    else f"{node} has not replied"
                txt = f"{link.port} open · tx {link.tx} rx {link.rx} · {heard}"
                if self.busy[which]:
                    txt += f" · BUSY: {self.busy[which]}"
                btn.configure(text="Disconnect")
            else:
                colour = "#c8c8c8"
                txt = "disconnected"
                btn.configure(text="Connect")
            dot.create_oval(2, 2, 12, 12, fill=colour, outline="#707070")
            lbl.configure(text=txt)

    def _quit(self):
        for link in self.links.values():
            link.disconnect()
        time.sleep(0.15)
        self.destroy()


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--bridge", default=None, help="serial port of the V4-A bridge")
    ap.add_argument("--aux", default=None, help="serial port of a second USB node")
    ap.add_argument("--no-connect", action="store_true", dest="no_connect",
                    help="preselect the ports but don't open them")
    a = ap.parse_args()
    FleetUI(a.bridge, a.aux, autoconnect=not a.no_connect).mainloop()


if __name__ == "__main__":
    main()
