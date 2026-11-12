#!/usr/bin/env python3
"""Reports how much of the game's own code is decompiled to C, from the last linked build.

Counts bytes of .text that come from compiled C/C++ objects (build/src/**), minus functions those
files still pull in from assembly with INCLUDE_ASM. Library code (Sony SDK, middleware, libc,
libgcc) is excluded from the denominator: each target's `game_ranges` in game.toml says where the
game's own code is (elf_survey.py's compiler runs are a first hint).
"""

import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT, TARGETS  # noqa: E402


def in_ranges(addr, ranges):
    return any(lo <= addr < hi for lo, hi in ranges)


def c_text(map_path):
    """(address, size, object) of every .text contribution from a compiled C object."""
    out = []
    for m in re.finditer(r"^ \.text\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(build/src/\S+\.o)$",
                         map_path.read_text(), re.M):
        out.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3)))
    return out


def source_of(obj):
    stem = ROOT / "src" / Path(obj).relative_to("build/src").with_suffix("")
    return next((stem.with_suffix(s) for s in (".c", ".cpp") if stem.with_suffix(s).exists()), None)


def included_asm_bytes(obj):
    """Bytes of functions a C file still includes from asm/**/nonmatchings/."""
    src = source_of(obj)
    if src is None:
        return 0
    total = 0
    for folder, name in re.findall(r"^INCLUDE_ASM\(\"([^\"]+)\",\s*(\w+)\);", src.read_text(), re.M):
        path = ROOT / folder / f"{name}.s"
        m = re.search(r"^nonmatching \w+, 0x([0-9A-F]+)", path.read_text(), re.M) if path.exists() else None
        total += int(m.group(1), 16) if m else 0
    return total


def function_counts(target, ranges):
    """(named, total, included) game functions still in assembly: those in the assembly subsegments the yaml
    lists now (older split files stay on disk and are ignored) plus the INCLUDE_ASM lines of the linked C files."""
    yaml = (ROOT / target["yaml"]).read_text()
    asm_dir = ROOT / "asm" / target["subdir"] if target["subdir"] else ROOT / "asm"
    labels = []
    for sub in re.findall(r"\[0x[0-9A-Fa-f]+, asm, \"?([\w/]+)\"?\]", yaml):
        path = asm_dir / f"{sub}.s"
        if not path.exists():
            continue
        for m in re.finditer(r"^glabel (\w+)\n\s+/\* [0-9A-F]+ ([0-9A-F]{8})", path.read_text(), re.M):
            labels.append((m.group(1), int(m.group(2), 16)))
    game = {n for n, a in labels if in_ranges(a, ranges)}
    included = 0
    for kind, sub in re.findall(r"\[0x[0-9A-Fa-f]+, (c|cpp), \"?([\w/]+)\"?\]", yaml):
        src = ROOT / "src" / f"{sub}.{kind}"
        if src.exists():
            included += len(re.findall(r"^INCLUDE_ASM\(", src.read_text(), re.M))
    return sum(1 for n in game if not n.startswith("func_")), len(game), included


def main():
    for t in TARGETS:
        name = t["name"]
        ranges = [tuple(r) for r in t.get("game_ranges", [t["image"]])]
        map_path = ROOT / f"{t['elf_out']}.map"
        if not map_path.exists():
            print(f"{name}: no {map_path.relative_to(ROOT)}, run ninja first")
            continue
        total = sum(hi - lo for lo, hi in ranges)
        done = 0
        for addr, size, obj in c_text(map_path):
            if in_ranges(addr, ranges):
                done += size - included_asm_bytes(obj)
        named, count, included = function_counts(t, ranges)
        print(f"{name}: {done:#x} / {total:#x} bytes of game code in C ({100 * done / total:.2f}%)")
        print(f"    functions still in assembly: {count} in assembly files ({named} of them named), "
              f"{included} INCLUDE_ASM in linked C files")


if __name__ == "__main__":
    main()
