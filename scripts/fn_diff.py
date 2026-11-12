#!/usr/bin/env python3
"""Checks C versions of functions against the original, one call at a time, inside PCSX2.

Usage: scripts/fn_diff.py --list FILE [--ram-lo 0x100000 --ram-hi 0x2000000] [--wait 8]
  FILE: lines `0xADDR` (candidates built by scripts/port_inplace.py into build_port/obj/<ADDR>/f.bin)

The original executable runs the attract-mode demo fight; a base state is saved there once (slot 1). For each
function F: from the base state, stop at F's entry on a real call (breakpoint), save that moment (slot 2), let the
original code run until F returns to its caller (breakpoint on ra with sp equal, so a recursive or other-thread
call does not count), read v0/v1/f0 and the RAM; load slot 2 again, write F's C version over it, run to the same
return, read again and compare. EQUAL = same result registers and the same RAM; DIFF lists the first differing
addresses; NOT REACHED = F did not run within --wait seconds of the demo. Results: build_port/fn_diff.csv
(append; a cut run resumes).

Timing noise: interrupts during F (VSync, DMA) land at other points when the C takes another number of cycles;
a DIFF made only of such writes shows up as differences far from F's data. Recheck DIFFs with --recheck before
believing them.
"""

import argparse
import json
import socket
import struct
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402
import pine  # noqa: E402

PCSX2 = "/mnt/datos/Herramientas/pcsx2-src/build/bin/pcsx2-qt"
ISO = ROOT / "DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).iso"
OUT = ROOT / "build_port"


class Dbg:
    """PCSX2 DebugServer: one JSON object per line."""

    def __init__(self):
        self.s = socket.create_connection(("127.0.0.1", 21512), timeout=30)
        self.f = self.s.makefile("rw")

    def __call__(self, **cmd):
        self.f.write(json.dumps(cmd) + "\n")
        self.f.flush()
        return json.loads(self.f.readline())

    def status(self):
        return self(cmd="status")["data"]

    def regs(self):
        d = self(cmd="read_registers", cpu="ee")["data"]
        out = {}
        for cat in d.values():
            if isinstance(cat, dict) and "regs" in cat:
                for r in cat["regs"]:
                    out[r["name"]] = int(r["value"], 16)
        return out

    def read(self, addr, n):
        buf = bytearray()
        while n > 0:
            k = min(n, 65536)
            buf += bytes.fromhex(self(cmd="read_memory", cpu="ee", address=addr, length=k)["hex"])
            addr += k
            n -= k
        return bytes(buf)

    def write(self, addr, data):
        self(cmd="write_memory", cpu="ee", address=addr, data=data.hex())

    def wait_pause(self, pc=None, timeout=8):
        t = time.time()
        while time.time() - t < timeout:
            st = self.status()
            if st["paused"] and (pc is None or int(st["pc"], 16) == pc):
                return True
            time.sleep(0.05)
        return False


def load_ret():
    """address -> return type from scratch/protos/ctx.h (void / s32 / f32)."""
    import re
    import fdiff
    by_name = fdiff.targets()
    out = {}
    path = ROOT / "scratch/protos/ctx.h"
    if path.exists():
        for line in path.read_text().splitlines():
            m = re.match(r"(\w+)\s+(\w+)\(", line)
            if m:
                name = m.group(2)
                addr = by_name.get(name)
                if addr is None and re.fullmatch(r"func_[0-9A-F]{8}", name):
                    addr = int(name[5:], 16)
                if addr is not None:
                    out[addr] = m.group(1)
    return out


RET = load_ret()
FAR = 0x00090000  # scripts/port_inplace.py --far links there: free EE RAM below the game


def pine_state(p, op, slot):
    p._call(struct.pack("<BB", op, slot))


def snapshot(d, lo, hi):
    r = d.regs()
    res = {k: r.get(k, 0) for k in ("v0", "v1", "f0")}
    return res, d.read(lo, hi - lo)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--list", type=Path, required=True)
    ap.add_argument("--ram-lo", type=lambda x: int(x, 0), default=0x100000)
    ap.add_argument("--ram-hi", type=lambda x: int(x, 0), default=0x2000000)
    ap.add_argument("--wait", type=float, default=8)
    ap.add_argument("--coverage", type=float, help="only list which functions run within this many seconds")
    ap.add_argument("--far", action="store_true", help="C linked at 0x90000 (scripts/port_inplace.py --far, "
                    "build_port/obj_far): written there, with a jump to it at F's entry")
    ap.add_argument("--csv", type=Path, default=OUT / "fn_diff.csv", help="results file (append; a cut run resumes)")
    a = ap.parse_args()
    res_csv = a.csv
    done = {l.split(",")[0] for l in res_csv.read_text().splitlines()} if res_csv.exists() else set()
    # A function whose check killed PCSX2 (the C version crashes it, or never gives control back) is recorded
    # as CRASH by the next run instead of being retried forever.
    marker = res_csv.with_suffix(".inprogress")
    if marker.exists():
        dead = marker.read_text().strip()
        if dead and dead not in done:
            with open(res_csv, "a") as out:
                out.write(f"{dead},CRASH\n")
            done.add(dead)
        marker.unlink()
    todo = [int(x, 16) for x in a.list.read_text().split() if f"0x{int(x, 16):08X}" not in done]
    print(f"{len(todo)} functions to check", flush=True)

    proc = subprocess.Popen([PCSX2, "-batch", "-fastboot", "-unlimited", "-nofullscreen", "-logfile",
                             str(ROOT / "scratch/pcsx2_fndiff.log"), "-elf", str(ROOT / "disc/SLUS_214.41"), "--",
                             str(ISO)], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    try:
        p = None
        t0 = time.time()
        while time.time() - t0 < 300:
            try:
                p = p or pine.Pine()
                if p.read32(0x00387700):
                    break
            except OSError:
                p = None
            time.sleep(2)
        time.sleep(3)
        d = Dbg()
        d(cmd="pause")
        d.wait_pause()
        pine_state(p, 9, 1)  # base state in the demo fight
        time.sleep(2)
        if a.coverage:
            covered = coverage(d, todo, a.coverage)
            a.list.with_suffix(".covered").write_text("\n".join(f"0x{x:08X}" for x in sorted(covered)) + "\n")
            print(f"{len(covered)} of {len(todo)} run within {a.coverage:.0f} s", flush=True)
            return
        with open(res_csv, "a") as out:
            for f in todo:
                code = (OUT / ("obj_far" if a.far else "obj") / f"{f:08X}" / "f.bin").read_bytes()
                marker.write_text(f"0x{f:08X}")
                verdict = check(d, p, f, code, a)
                marker.unlink()
                out.write(f"0x{f:08X},{verdict}\n")
                out.flush()
                print(f"0x{f:08X} {verdict}", flush=True)
    finally:
        proc.terminate()


def coverage(d, funcs, seconds):
    """Which of funcs run within `seconds` of the demo: a breakpoint on each, removed at its first hit."""
    for f in funcs:
        d(cmd="set_breakpoint", cpu="ee", address=f, temporary=False)
    left, hit, t = set(funcs), set(), time.time()
    d(cmd="resume")
    while time.time() - t < seconds and left:
        st = d.status()
        if st["paused"]:
            pc = int(st["pc"], 16)
            if pc in left:
                hit.add(pc)
                left.discard(pc)
                d(cmd="remove_breakpoint", cpu="ee", address=pc)
            d(cmd="resume")
        else:
            time.sleep(0.01)
    for f in left:
        d(cmd="remove_breakpoint", cpu="ee", address=f)
    return hit


def run_to_return(d, sp, ra, wait):
    d(cmd="set_breakpoint", cpu="ee", address=ra, condition=f"sp=={sp:#x}", temporary=False)
    d(cmd="resume")
    ok = d.wait_pause(ra, wait)
    d(cmd="remove_breakpoint", cpu="ee", address=ra)
    return ok


def check(d, p, f, code, a):
    pine_state(p, 0xA, 1)
    time.sleep(1)
    d(cmd="set_breakpoint", cpu="ee", address=f, temporary=False)
    d(cmd="resume")
    hit = d.wait_pause(f, a.wait)
    d(cmd="remove_breakpoint", cpu="ee", address=f)
    if not hit:
        d(cmd="pause")
        d.wait_pause()
        return "NOT REACHED"
    r = d.regs()
    sp, ra = r["sp"] & 0xFFFFFFFF, r["ra"] & 0xFFFFFFFF
    pine_state(p, 9, 2)
    time.sleep(1)
    if not run_to_return(d, sp, ra, a.wait):
        return "NO RETURN (original)"
    res_a, ram_a = snapshot(d, a.ram_lo, a.ram_hi)
    # The same call with the C version.
    d(cmd="set_breakpoint", cpu="ee", address=f, temporary=False)
    pine_state(p, 0xA, 2)
    time.sleep(1)
    d.wait_pause(f, a.wait)
    d(cmd="remove_breakpoint", cpu="ee", address=f)
    if a.far:
        # the C at FAR; F's entry jumps there (j FAR; nop), the rest of F's original code stays
        d.write(FAR, code)
        d.write(f, struct.pack("<II", 0x08000000 | (FAR >> 2), 0))
    else:
        d.write(f, code)
    if not run_to_return(d, sp, ra, a.wait):
        return "NO RETURN (C)"
    res_b, ram_b = snapshot(d, a.ram_lo, a.ram_hi)
    # Not differences: F's own code (the C is written there) and the stack below the caller's sp (F's frame:
    # the C may lay out its spills differently, and nothing reads them after the return).
    skip = [(f, f + (8 if a.far else len(code))), (sp - 0x8000, sp)]
    diffs = [a.ram_lo + i for i in range(0, len(ram_a), 4) if ram_a[i:i + 4] != ram_b[i:i + 4]
             and not any(x <= a.ram_lo + i < y for x, y in skip)]
    # Only the result register the function's callers read (scripts/infer_protos.py): v0 or f0, or none.
    kind = RET.get(f, "s32")
    regs_ok = kind == "void" or (res_a["f0"] == res_b["f0"] if kind == "f32" else
                                 (res_a["v0"] & 0xFFFFFFFF) == (res_b["v0"] & 0xFFFFFFFF))
    if regs_ok and not diffs:
        return "EQUAL"
    return f"DIFF regs={'ok' if regs_ok else 'differ'} ram_words={len(diffs)} first={' '.join(hex(x) for x in diffs[:4])}"


if __name__ == "__main__":
    main()
