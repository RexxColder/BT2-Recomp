#!/usr/bin/env python3
"""Call graph of the game, and which functions native C may call back into the recompiled code.

Usage: scripts/callgraph.py [--check FILE]   (FILE: lines 0xADDR; prints the ones that never block)
Output: build_port/callgraph.csv  (addr,callees,blocking,why)

In the hybrid build (port/tools/gen_native.py) a native C function calls a game function through a bridge that
runs the recompiled code to its return inside the C call. The runtime's guest threads are cooperative: a thread
that blocks (WaitSema, VSync, a sleeping syscall stub) throws EeDispatcherTransfer up to the dispatcher and is
resumed later from ctx->pc, which a C frame can not be. So a callee is safe only when nothing it can reach
blocks. Blocking (conservative):
  - it has a `syscall`;
  - it makes an indirect call (jalr) or jumps through a register other than ra outside its own range (the
    target is unknown);
  - it is a runtime stub (port/build/recomp/ps2_recompiled_stubs.h: HLE in C++, may wait; not the native ones);
  - it calls or tail-jumps to a blocking function (fixed point over the graph).
"""

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402
from infer_protos import disasm  # noqa: E402


def build():
    funcs = [(int(r.split(",")[1], 16), int(r.split(",")[2], 16)) for r in
             (ROOT / "port/funcmap.csv").read_text().splitlines()[1:]]
    starts = {s for s, _ in funcs}
    ins = disasm(ROOT / "disc/SLUS_214.41")
    stubs = {int(m, 16) for m in re.findall(r"_0x([0-9a-f]+)\(", (ROOT / "port/build/recomp/ps2_recompiled_stubs.h").read_text())}
    # the functions already native are listed there too (scripts/recomp.py skips them): they are C, not HLE
    nat = ROOT / "port/build/gen/native_list.txt"
    stubs -= {int(x, 16) for x in nat.read_text().split()} if nat.exists() else set()
    callees, why = {}, {}
    for s, e in funcs:
        out = set()
        if s in stubs:
            why[s] = "stub"
        for a in range(s, e, 4):
            mn, ops = ins.get(a, ("", []))
            if mn == "syscall":
                why.setdefault(s, f"syscall@{a:x}")
            elif mn == "jalr":
                why.setdefault(s, f"jalr@{a:x}")
            elif mn == "jr" and ops and ops[0] not in ("ra", "$ra"):
                pass  # jump table inside the function (switch); m2c and the recompiler both resolve it
            elif mn in ("jal", "j") and ops:
                t = int(ops[0].replace("0x", ""), 16)
                if mn == "jal" or (t in starts and not s <= t < e):
                    out.add(t)
        callees[s] = out
    # fixed point: a caller of a blocking function blocks
    changed = True
    while changed:
        changed = False
        for s, out in callees.items():
            if s not in why:
                bad = next((t for t in out if t in why or t not in callees), None)
                if bad is not None:
                    why[s] = f"calls {bad:x}"
                    changed = True
    return callees, why


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", type=Path)
    a = ap.parse_args()
    callees, why = build()
    with open(ROOT / "build_port/callgraph.csv", "w") as f:
        f.write("addr,callees,blocking,why\n")
        for s in sorted(callees):
            f.write(f"0x{s:08X},{' '.join(f'{t:x}' for t in sorted(callees[s]))},{int(s in why)},{why.get(s, '')}\n")
    print(f"{len(callees)} functions, {len(why)} blocking", file=sys.stderr)
    if a.check:
        for x in a.check.read_text().split():
            s = int(x, 16)
            if s in callees and s not in why:  # its own code and everything it reaches never blocks
                print(f"0x{s:08X}")


if __name__ == "__main__":
    main()
