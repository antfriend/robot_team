"""Poll one node's INTERO PERCEPT repeatedly over a SINGLE serial connection.

`companion.py intero` opens the port per invocation, and opening it resets the node — so
repeated invocations can never observe a loop-profiler window past the ~8 s settle, and
`worst loop pass` reads 0 forever. One open, many probes, is the only way to watch a
number that is published on a 10 s window.

  python intero_watch.py COM6 v4a_bridge 12 10
"""
import sys, os, time

sys.path.insert(0, r"c:\git\robot_team\orchestrator")
import serial
import companion as c

port, node, count, every = sys.argv[1], sys.argv[2], int(sys.argv[3]), float(sys.argv[4])
target = c.NODE_IDS[node]
reader = c.SerialFrameReader()

with serial.Serial(port, 115200, timeout=0.1) as ser:
    time.sleep(8.0)                   # the reset this open just caused
    ser.reset_input_buffer()
    print(f"watching {node} on {port}: {count} probes, {every}s apart")
    for i in range(count):
        b = c.intero_probe(ser, reader, target)
        if b is None:
            print(f"  {i:2d}  no reply", flush=True)
        else:
            print(f"  {i:2d}  up {b['uptime_s']:5d}s  lp {b['worst_loop_ms']:5d}ms  "
                  f"bat {b['bat_mv']}mV  die {b['die_c']:.1f}C  "
                  f"maxalloc {b['maxalloc_kb']}K  cond 0x{b['conductor_id']:08X}  "
                  f"voicing={b['voicing']}", flush=True)
        time.sleep(every)
