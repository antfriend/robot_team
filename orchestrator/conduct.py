# conduct.py — the laptop conducts the hero's-arc song through the V4-A bridge.
#
# One serial session, opened WITHOUT the DTR/RTS reset (V4-A holds the baton; a reset
# would depose the very conductor we're driving). Play/stop are sent per node because
# the bridge does not rebroadcast CMD_PLAY/STOP (it only sets its own flag); scene
# changes are broadcast (only the conductor applies, and it's V4-A on this very port).
# Each send uses a fresh ms-resolution toot_seq so the radio dedup at the far nodes
# never mistakes consecutive commands for replays.
import sys
import time
import struct

sys.path.insert(0, r"c:\git\robot_team\orchestrator")
import companion as C

PORT = "COM6"
BAUD = 115200
NODES = ["v4a_bridge", "v4b_relay", "v4c_edge", "tdeck_1"]

# (scene_id, name, hold_seconds) — 120 BPM: a 16-step bar is 2 s, a melody loop 8 s.
PROGRAM = [
    (0, "ALONE",  8),   # 4 bars of V4-A's kick by itself
    (1, "ALLY",   8),   # backbeat joins
    (2, "GROOVE", 8),   # hats complete it — no pitched voice yet
    (3, "ORDEAL", 12),  # let the heartbeat sit
    (4, "RETURN", 16),  # two loops of the harmony
    (5, "FINALE", 24),  # three loops of Ode to Joy
]

_seq = int(time.time() * 1000) & 0x7FFFFFFF


def fresh_seq():
    global _seq
    _seq = (_seq + 1) & 0x7FFFFFFF
    return _seq


def send_cmd(ser, reader, op, target, args=b"", rto0=0.4, attempts=3):
    payload = bytes([op]) + struct.pack("<I", target) + args
    seq = fresh_seq()
    frame = C.encode_toot(C.CMD, C.ORCHESTRATOR_ID, seq, payload,
                          flags=C.FLAG_WANT_ACK)
    return C.send_reliable(ser, reader, frame, target, seq,
                           rto0=rto0, attempts=attempts)


def stamp():
    return time.strftime("%H:%M:%S")


def main():
    reader = C.SerialFrameReader()
    ser = C.open_serial_no_reset(PORT, BAUD)
    try:
        time.sleep(2.0)
        ser.reset_input_buffer()

        # Curtain up: make sure the chart is at the top of the tale before any voice
        # is enabled, so nobody blasts a leftover scene.
        acked = send_cmd(ser, reader, C.CMD_SET_SCENE, C.NODE_BROADCAST,
                         struct.pack("<H", 0), attempts=4)
        print(f"[{stamp()}] set-scene 0 ALONE: "
              f"{'ACK attempt %d' % acked if acked else 'NO ACK'}")

        # Cue every voice. A playing node often misses its play-ACK window (toneI2S
        # blocks) — that is the known false negative, so report but never abort.
        for n in NODES:
            a = send_cmd(ser, reader, C.CMD_PLAY, C.NODE_IDS[n], attempts=2)
            print(f"[{stamp()}] play -> {n}: "
                  f"{'ACK' if a else 'no ACK (fine if it is sounding)'}")

        # The tale. Scene 0 is already set; just let it run, then walk onward.
        print(f"[{stamp()}] --- ALONE (scene 0) for {PROGRAM[0][2]} s ---")
        time.sleep(PROGRAM[0][2])
        for sid, name, hold in PROGRAM[1:]:
            a = send_cmd(ser, reader, C.CMD_SET_SCENE, C.NODE_BROADCAST,
                         struct.pack("<H", sid), attempts=4)
            print(f"[{stamp()}] --- {name} (scene {sid}) for {hold} s: "
                  f"{'ACK attempt %d' % a if a else 'NO ACK'} ---")
            time.sleep(hold)

        # Curtain down: stop every voice, then reset the tale for the next telling.
        for n in NODES:
            a = send_cmd(ser, reader, C.CMD_STOP, C.NODE_IDS[n], attempts=2)
            print(f"[{stamp()}] stop -> {n}: {'ACK' if a else 'no ACK'}")
        a = send_cmd(ser, reader, C.CMD_SET_SCENE, C.NODE_BROADCAST,
                     struct.pack("<H", 0), attempts=4)
        print(f"[{stamp()}] set-scene 0 (reset the tale): "
              f"{'ACK attempt %d' % a if a else 'NO ACK'}")
        print(f"[{stamp()}] performance complete.")
    finally:
        ser.close()


if __name__ == "__main__":
    main()
