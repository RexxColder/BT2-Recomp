#!/usr/bin/env python3
"""Remove the redundant `.p2align` that ee-gcc 2.9 emits right after `.end NAME`.

The 2.96 output does not have it, and the original image packs functions back to
back (Ghidra's sizes include that trailing padding), so a C chunk must not carry
it.  The alignment before the *next* function (emitted by the compiler as a
leading `.p2align`) already reproduces the original layout.
"""
import re
import sys

PAD = re.compile(r"^\s*\.p2align\b")
END = re.compile(r"^\s*\.end\b")


def main(path):
    with open(path) as f:
        lines = f.readlines()
    out = []
    for i, line in enumerate(lines):
        if END.match(line) and i + 1 < len(lines) and PAD.match(lines[i + 1]):
            out.append(line)
            continue  # drop lines[i+1] on the next iteration
        out.append(line)
    # The loop above appends the `.end` and then also the `.p2align`; drop those.
    cleaned = []
    for i, line in enumerate(out):
        if PAD.match(line) and cleaned and END.match(cleaned[-1]):
            continue
        cleaned.append(line)
    with open(path, "w") as f:
        f.writelines(cleaned)


if __name__ == "__main__":
    main(sys.argv[1])
