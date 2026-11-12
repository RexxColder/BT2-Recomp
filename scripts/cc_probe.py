#!/usr/bin/env python3
"""Identifies the original compiler: compiles probe functions with every ee-gcc build under tools/ and a set of
flag combinations, and prints how many functions each combination matches.

Usage: scripts/cc_probe.py src/probe/*.c [--flags "-O2" --flags "-O2 -fopt-stack" ...] [--cc KEY ...]

Write 3-5 probe functions first, matched by hand against ONE compiler if needed (fdiff.py shows the diffs):
a float leaf, a leaf with a loop, a function saving two or more callee-saved registers, a C++ member. A leaf
alone cannot tell compilers apart: the frame layout (save slot size, sd vs sq, order) is what differs most.

What it found on the first two games (see docs/METHOD.md):
  BT3 (Spike, 2007):              Sony ee-gcc 2.96, -O2 -fno-strict-aliasing
  Downhill Jam (Neversoft, 2007): SN ProDG ee-gcc 2.95.3-136, -O2 -fopt-stack
"""

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fdiff  # noqa: E402
from gamecfg import ALT_CC  # noqa: E402

DEFAULT_FLAGS = [
    "-O2",
    "-O2 -fno-strict-aliasing",
    "-O2 -fopt-stack",
    "-O1",
    "-O3",
    "-Os",
    "-O2 -G0",
]


def main():
    args = sys.argv[1:]
    flags, only = [], []
    while "--cc" in args:
        i = args.index("--cc")
        only.append(args[i + 1])
        del args[i:i + 2]
    while "--flags" in args:
        i = args.index("--flags")
        flags.append(args[i + 1])
        del args[i:i + 2]
    if not args:
        sys.exit(__doc__)
    flags = flags or DEFAULT_FLAGS
    known = fdiff.targets()
    keys = only or ["default", *ALT_CC]
    rows = []
    for key in keys:
        for f in flags:
            fdiff.FLAGS_OVERRIDE = f + " -Iinclude"
            ok = total = bad = 0
            for src in args:
                obj = fdiff.compile_src(src, key)
                if obj is None:
                    total = -1
                    break
                nbad, _, lines = fdiff.evaluate(obj, [], known)
                bad += nbad
                ok += sum(1 for line in lines if ": OK" in line)
                total += sum(1 for line in lines if not line.startswith(" "))
            if total > 0:
                rows.append((ok, -bad, key, f, total))
                print(f"{ok}/{total} OK  {bad:4} instructions differ  {key:24} {f}", flush=True)
    rows.sort(reverse=True)
    if rows:
        ok, bad, key, f, total = rows[0]
        print(f"\nbest: {key} {f} ({ok}/{total} functions OK)")


if __name__ == "__main__":
    main()
