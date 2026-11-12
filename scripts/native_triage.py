#!/usr/bin/env python3
"""Finds the native C functions that break the hybrid build, run after run, and writes them to a skip file.

Usage: scripts/native_triage.py [--seconds 240] [--rounds 30] [--skip build_port/native_bad.txt]

Each round runs port/build/native/bt2 (all natives on, minus the skip file) under xvfb for --seconds.
- crash: the core's backtrace names the culprit (frame nat_<name> / native_<ADDR>): added to the skip file;
- frozen guest (the watch's EE cycle counter stops; the base build stalls only after ~500 s): halved with
  BT2_NATIVE_LIMIT until the first bad function is found, then added;
- clean run: done.
The skip file is what the test build's launcher passes as BT2_NATIVE_SKIP_FILE.
"""
import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LIST = ROOT / "port/build/gen/native_list.txt"


def run(seconds, skip, limit=None, tag="t"):
    d = ROOT / "scratch" / "triage"
    d.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, BT2_NATIVE="1", PS2X_IDENTITY_RDRAM="1", BT2_SKIP_MOVIES="1", BT2_WATCH="15",
               BT2_NATIVE_SKIP_FILE=str(skip))
    if limit is not None:
        env["BT2_NATIVE_LIMIT"] = str(limit)
    log = d / f"{tag}.log"
    with open(log, "w") as f:
        r = subprocess.run(["timeout", str(seconds), str(ROOT / "scripts/capped.sh"), "6G", "xvfb-run", "-a",
                            str(ROOT / "port/build/native/bt2"), "gamedata/SLUS_214.41", "gamedata.iso"],
                           cwd=ROOT, env=env, stdout=f, stderr=subprocess.STDOUT)
    text = log.read_text(errors="replace")
    if r.returncode not in (124, 0):
        bt = subprocess.run(["coredumpctl", "-1", "info"], capture_output=True, text=True).stdout
        m = re.search(r"native_([0-9A-F]{8})", bt)
        if m:
            return "crash", int(m.group(1), 16)
        m = re.search(r"nat_(\w+) \(bt2", bt)
        return "crash", m.group(1) if m else None
    if "FATAL" in text:
        m = re.search(r"FATAL: (0x[0-9a-f]+)", text)
        return "crash", int(m.group(1), 16) if m else None
    cycles = re.findall(r"\[watch \d+s\] cycle (\d+)", text)
    if len(cycles) >= 3 and cycles[-1] == cycles[-2] == cycles[-3]:
        return "frozen", None
    return "ok", None


def name_to_addr(name):
    for line in (ROOT / "port/build/gen/native_wrappers.cpp").read_text().splitlines():
        m = re.search(rf"nat_{re.escape(name)}\(", line)
        if m:
            break
    for line in (ROOT / "port/build/gen/native_wrappers.cpp").read_text().splitlines():
        m = re.match(r".*void native_([0-9A-F]{8})\(.*nat_" + re.escape(name) + r"\(", line)
        if m:
            return int(m.group(1), 16)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--seconds", type=int, default=240)
    ap.add_argument("--rounds", type=int, default=30)
    ap.add_argument("--skip", type=Path, default=ROOT / "build_port/native_bad.txt")
    a = ap.parse_args()
    a.skip.touch()
    order = [int(x, 16) for x in LIST.read_text().split()]
    for rnd in range(a.rounds):
        bad = {int(x, 16) for x in a.skip.read_text().split()}
        kind, who = run(a.seconds, a.skip, tag=f"r{rnd}")
        print(f"round {rnd}: {kind} {who if not isinstance(who, int) else hex(who)} (skipped {len(bad)})", flush=True)
        if kind == "ok":
            print("clean run", flush=True)
            return
        if isinstance(who, str):
            who = name_to_addr(who)
        if who is None:
            # frozen (or a crash with no native frame): halve the active list
            active = [x for x in order if x not in bad]
            lo, hi = 0, len(active)
            while hi - lo > 1:
                mid = (lo + hi) // 2
                # limit counts list positions, so convert the active index to a list position
                pos = order.index(active[mid - 1]) + 1
                k, _ = run(a.seconds, a.skip, limit=pos, tag=f"r{rnd}_h{mid}")
                print(f"  first {mid} active: {k}", flush=True)
                if k == "ok":
                    lo = mid
                else:
                    hi = mid
            who = active[lo]
        with open(a.skip, "a") as f:
            f.write(f"0x{who:08X}\n")
        print(f"  -> skip 0x{who:08X}", flush=True)


if __name__ == "__main__":
    main()
