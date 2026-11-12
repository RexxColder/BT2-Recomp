#!/usr/bin/env python3
"""Finds the native function that breaks the hybrid build's run, by halving (no rebuild: BT2_NATIVE_SKIP).

Usage: scripts/native_bisect.py --log RUN.LOG [--seconds 420]
  RUN.LOG: a failing run with BT2_NATIVE_LOG=1 (its "[native] first call" lines are the suspects).
A run is good when its last screenshots are not one flat image (the stuck loading screen: stddev ~0) and the
process did not crash. Each run: port/build/native/bt2 with the suspects outside the tested half skipped.
"""
import argparse, os, re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def run(skip, seconds, tag):
    d = ROOT / "scratch" / "nbisect" / tag
    d.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, BT2_NATIVE="1", BT2_SKIP_MOVIES="1", PS2X_IDENTITY_RDRAM="1", BT2_WATCH="30",
               BT2_SHOT=str(d / "s"), BT2_NATIVE_SKIP=",".join(f"0x{x:08x}" for x in skip))
    with open(d / "run.log", "w") as log:
        r = subprocess.run(["timeout", str(seconds), str(ROOT / "scripts/capped.sh"), "6G", "xvfb-run", "-a",
                            str(ROOT / "port/build/native/bt2"), "gamedata/SLUS_214.41", "gamedata.iso"],
                           cwd=ROOT, env=env, stdout=log, stderr=subprocess.STDOUT)
    if r.returncode != 124:
        return False, f"rc={r.returncode}"
    shots = sorted(d.glob("s_frame_*.ppm"), key=lambda p: int(re.findall(r"\d+", p.name)[-1]))[-3:-1]
    sd = [float(subprocess.run(["magick", str(p), "-format", "%[standard-deviation]", "info:"],
                               capture_output=True, text=True).stdout or 0) for p in shots]
    return min(sd, default=0) > 500, f"stddev={sd}"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--log", type=Path, required=True)
    ap.add_argument("--seconds", type=int, default=420)
    a = ap.parse_args()
    called = [int(x, 16) for x in re.findall(r"first call 0x([0-9a-f]+)", a.log.read_text())]
    installed = [int(x, 16) for x in (ROOT / "port/build/gen/native_list.txt").read_text().split()]
    uncalled = [x for x in installed if x not in called]
    sus, step = called, 0
    while len(sus) > 1:
        half = sus[:len(sus) // 2]
        rest = [x for x in sus if x not in half]
        ok, why = run(uncalled + rest, a.seconds, f"r{step}")   # only `half` native
        print(f"round {step}: {len(half)} native of {len(sus)} -> {'good' if ok else 'BAD'} ({why})", flush=True)
        sus = rest if ok else half
        step += 1
    print(f"culprit: 0x{sus[0]:08X}" if sus else "no culprit", flush=True)


if __name__ == "__main__":
    main()
