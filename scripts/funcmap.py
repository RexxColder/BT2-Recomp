#!/usr/bin/env python3
"""Writes the function map PS2Recomp reads (`ghidra_output`: CSV `Name,Start,End,Size`) from the splat split.

Usage: scripts/funcmap.py [OUT.csv]        (default port/funcmap.csv)

The functions are the `glabel`s of asm/**/*.s (splat/spimdisasm found them; no Ghidra needed) plus the
functions already in C (from the linked rebuild's symbols and the symbol files). Each one ends where the next one
starts, clamped to the end of its section; trailing alignment nops stay inside, as in the original layout.
Names are the project's current names, so the translated code reads like the decomp.
"""

import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT, TARGETS  # noqa: E402
import elf_survey  # noqa: E402

GLABEL = re.compile(r"^glabel (\w+)\n(?:.*\n){0,3}?\s+/\* [0-9A-F]+ ([0-9A-F]{8}) ", re.M)
# Code addresses taken with lui/addiu (%hi/%lo): splat writes them as `alabel D_XXXXXXXX` inside .text.
ALABEL = re.compile(r"^\s*alabel D_([0-9A-F]{8})\b", re.M)
# ... or as an offset into a function splat merged it into: `%lo(func_XXXXXXXX + 0xN)`.
FUNC_OFFSET = re.compile(r"%lo\((\w+) \+ 0x([0-9A-F]+)\)")


def symbol_names():
    out = {}
    for path in sorted((ROOT / "config").glob("symbol_addrs*.txt")) + sorted((ROOT / "config/symbols").glob("*.txt")):
        for line in path.read_text().splitlines():
            m = re.match(r"(\w+) = 0x([0-9A-Fa-f]+);.*type:func", line)
            if m:
                out[int(m.group(2), 16)] = m.group(1)
    return out


def main():
    out = Path(sys.argv[1]) if len(sys.argv) > 1 else ROOT / "port" / "funcmap.csv"
    t = TARGETS[0]
    data, _, phdrs, sections = elf_survey.read_elf(ROOT / t["elf"])
    code = [(s["addr"], s["addr"] + s["size"]) for s in elf_survey.code_sections(data, phdrs, sections)
            if s["name"] != ".vutext"]
    starts = {}
    for path in sorted((ROOT / "asm").rglob("*.s")):
        if "data" in path.parts or "nonmatchings" in path.parts:
            continue
        for m in GLABEL.finditer(path.read_text()):
            starts[int(m.group(2), 16)] = m.group(1)
    # Functions already in C have no glabel: take them from the linked rebuild (ninja must have run).
    elf_out = ROOT / t["elf_out"]
    if elf_out.exists():
        import subprocess
        from gamecfg import BINUTILS
        nm = subprocess.run([str(ROOT / (BINUTILS + "nm")), str(elf_out)], capture_output=True, text=True).stdout
        for line in nm.splitlines():
            p = line.split()
            if len(p) == 3 and p[1] in "Tt" and not p[2].startswith((".", "$")):
                addr = int(p[0], 16)
                if any(lo <= addr < hi for lo, hi in code):
                    starts.setdefault(addr, p[2])
    # Functions reached only through pointers in data (C++ static initialisers in the .ctors list, vtable
    # slots, callback tables) are invisible to splat when no `jal` targets them: it merges them into the
    # function before. A data word pointing into code at a frame-allocating prologue (`addiu $sp,$sp,-N`)
    # or right after a `jr $ra` + delay slot is taken as a function start. So is a word sitting in a vtable:
    # g++ 2.9x lays slots out as {delta, function} pairs, so a neighbour 4 or 8 bytes away pointing at a known
    # function start marks the table (leaf methods have no prologue to recognise). Jump tables do not match:
    # their entries point inside one function, never at function starts. Other {name, function} tables can
    # still point mid-function by coincidence, so a vtable hit also needs the alignment `nop` that SN's
    # assembler puts before every function.
    import struct
    image = (ROOT / t["original"]).read_bytes()
    base = t["image"][0]

    def word(addr):
        off = addr - base
        return struct.unpack_from("<I", image, off)[0] if 0 <= off <= len(image) - 4 else None

    data_secs = [(s["addr"], s["addr"] + s["size"]) for s in sections
                 if s["name"] in (".data", ".rodata", ".sdata", ".ctors", ".dtors") and s["type"] != 8]
    added = 0
    known = set(starts)
    for lo, hi in data_secs:
        for a in range(lo, hi - 3, 4):
            p = word(a)
            if p is None or p % 4 or p in starts or not any(clo <= p < chi for clo, chi in code):
                continue
            ins = word(p)
            prologue = ins is not None and ins >> 16 == 0x27BD and ins & 0x8000
            after_return = word(p - 8) == 0x03E00008
            in_vtable = word(p - 4) == 0 and any(word(a + d) in known for d in (-8, -4, 4, 8))
            if prologue or after_return or in_vtable:
                starts[p] = f"func_{p:08X}"
                added += 1
    print(f"{added} function starts found through data pointers")
    # Function pointers built in code (`lui/addiu` of a .text address, e.g. a callback stored in an object):
    # splat marks the target `alabel`. Taken as a function start when the alignment nop precedes it; the others
    # are labels inside a function (libgcc exception landing pads).
    taken = 0
    for path in sorted((ROOT / "asm").rglob("*.s")):
        if "data" in path.parts or "nonmatchings" in path.parts:
            continue
        text = path.read_text()
        targets = [int(m.group(1), 16) for m in ALABEL.finditer(text)]
        by_name = {name: addr for addr, name in starts.items()}
        targets += [by_name[m.group(1)] + int(m.group(2), 16) for m in FUNC_OFFSET.finditer(text) if m.group(1) in by_name]
        for p in targets:
            if p not in starts and any(lo <= p < hi for lo, hi in code) and word(p - 4) == 0:
                starts[p] = f"func_{p:08X}"
                taken += 1
    print(f"{taken} function starts found through code references (lui/addiu)")
    names = symbol_names()
    for addr, name in names.items():
        if any(lo <= addr < hi for lo, hi in code):
            starts[addr] = name
    for addr in list(starts):
        starts[addr] = names.get(addr, starts[addr])
    # A start outside every code section (a stale symbol, a data label that looks like a function) is not a
    # function: reported and left out.
    stray = sorted(a for a in starts if not any(lo <= a < hi for lo, hi in code))
    if stray:
        print(f"{len(stray)} starts outside the code sections left out: "
              + ", ".join(f"{starts[a]}@0x{a:08X}" for a in stray[:8]))
    order = sorted(a for a in starts if a not in stray)
    rows = ["Name,Start,End,Size"]
    for i, addr in enumerate(order):
        sec_end = next(hi for lo, hi in code if lo <= addr < hi)
        end = min(order[i + 1] if i + 1 < len(order) else sec_end, sec_end)
        rows.append(f"{starts[addr]},0x{addr:08X},0x{end:08X},{end - addr}")
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text("\n".join(rows) + "\n")
    print(f"{len(order)} functions -> {out.relative_to(ROOT) if out.is_relative_to(ROOT) else out}")


if __name__ == "__main__":
    main()
