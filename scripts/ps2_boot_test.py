#!/usr/bin/env python3
"""Boots an executable on PCSX2 with the BT2 disc and reports whether the game reaches the attract-mode demo fight.

Usage: scripts/ps2_boot_test.py ELF [--timeout 300] [--alive 30] [--keep]

PCSX2 (the local build with PINE on TCP 28011) runs ELF at unlimited speed with the original disc for data. PASS:
gBtlScene (0x00387700) becomes non-zero within --timeout seconds (the CPU-vs-CPU demo the title screen starts by
itself) and the battle memory keeps changing for --alive more seconds. FAIL: a timeout, frozen memory, or
PCSX2 exiting. One line of status every 10 s; exit 0 on PASS.
"""

import argparse
import hashlib
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402
import pine  # noqa: E402

PCSX2 = "/mnt/datos/Herramientas/pcsx2-src/build/bin/pcsx2-qt"
ISO = ROOT / "DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).iso"
SCENE = 0x00387700


def debug_samples(n=6):
    """PCs of the stuck game (DebugServer, TCP 21512): pc and every backtrace frame's pc/entry, sampled n times."""
    import json
    import socket
    pcs = set()
    try:
        sk = socket.create_connection(("127.0.0.1", 21512), timeout=5)
        f = sk.makefile("rw")
        for _ in range(n):
            for cmd in ({"cmd": "pause"}, {"cmd": "get_backtrace", "cpu": "ee"}, {"cmd": "resume"}):
                f.write(json.dumps(cmd) + "\n")
                f.flush()
                reply = f.readline()
                if cmd["cmd"] == "get_backtrace":
                    for v in __import__("re").findall(r'"(?:pc|entry)"\s*:\s*"0x([0-9A-Fa-f]+)"', reply):
                        pcs.add(int(v, 16))
            time.sleep(1)
        sk.close()
    except OSError:
        pass
    return sorted(pcs)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("elf", type=Path)
    ap.add_argument("--timeout", type=int, default=300)
    ap.add_argument("--alive", type=int, default=30)
    ap.add_argument("--keep", action="store_true", help="leave PCSX2 running")
    a = ap.parse_args()
    log = ROOT / "scratch" / f"pcsx2_{a.elf.name}.log"
    proc = subprocess.Popen([PCSX2, "-batch", "-fastboot", "-unlimited", "-nofullscreen", "-logfile", str(log),
                             "-elf", str(a.elf.resolve()), "--", str(ISO)],
                            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    t0, p, verdict = time.time(), None, "FAIL timeout"
    try:
        while time.time() - t0 < a.timeout:
            if proc.poll() is not None:
                verdict = "FAIL pcsx2 exited"
                break
            try:
                p = p or pine.Pine()
                scene = p.read32(SCENE)
            except OSError:
                p = None
                time.sleep(2)
                continue
            if scene:
                # The fight runs: its memory must keep changing.
                seen, last, still = set(), None, 0
                t1 = time.time()
                while time.time() - t1 < a.alive:
                    h = hashlib.md5(p.block(0x00387000, 0x1000)).hexdigest()
                    still = still + 1 if h == last else 0
                    last = h
                    seen.add(h)
                    if still >= 5:
                        break
                    time.sleep(2)
                verdict = "PASS" if still < 5 and len(seen) > 3 else "FAIL frozen in fight"
                print(f"{time.time() - t0:5.0f}s demo fight started (scene {scene:#x}); {verdict}", flush=True)
                break
            if int(time.time() - t0) % 10 < 2:
                print(f"{time.time() - t0:5.0f}s waiting (scene 0)", flush=True)
            time.sleep(2)
        if verdict != "PASS" and proc.poll() is None:
            print("SUSPECT_PCS " + " ".join(f"0x{x:08X}" for x in debug_samples()), flush=True)
    finally:
        if not a.keep:
            proc.terminate()
            try:
                proc.wait(10)
            except subprocess.TimeoutExpired:
                proc.kill()
    print(verdict)
    return 0 if verdict == "PASS" else 1


if __name__ == "__main__":
    sys.exit(main())
