#!/usr/bin/env python3
"""Finds the C++ vtables of a g++ 2.9x game and names their methods by class.

Usage: scripts/vtables.py [--report] [--min 2]

g++ 2.9x without -fvtable-thunks lays a vtable out as 8-byte entries {short delta; short index; void *pfn},
the first one empty (the RTTI slot, zero when built with -fno-rtti). A vtable is an address the code
materialises with `lui/addiu` (constructors and destructors store it into the object) that starts with that
empty entry and has --min or more entries pointing at function starts of the split. Each vtable is a class;
the functions that materialise its address are its constructors and destructors (named `_Ctor` here: the
two are told apart by reading them).

Naming: a class takes the prefix of a method that already has a `Class_Method` name in the symbol files
(e.g. CCutsceneData from CCutsceneData_UnloadMainPakFile); otherwise `C<VTABLE ADDRESS>`. Methods are named
`<Class>_Virtual<N>` (slot N, from 1), constructors/destructors `<Class>_Ctor`; already named functions keep their names; a
function in several vtables (an inherited, not overridden, method) is named after the first only.
Prints symbol_addrs lines (// guess) for config/symbols/vtables.txt; --report prints the classes instead.
"""

import collections
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT, TARGETS  # noqa: E402
import elf_survey  # noqa: E402


def function_starts():
    starts = {}
    csv = ROOT / "port" / "funcmap.csv"
    if csv.exists():
        for line in csv.read_text().splitlines()[1:]:
            name, start = line.split(",")[:2]
            starts[int(start, 16)] = name
    for path in sorted((ROOT / "asm").rglob("*.s")):
        if "data" in path.parts:
            continue
        for m in re.finditer(r"^glabel (\w+)\n(?:.*\n){0,3}?\s+/\* [0-9A-F]+ ([0-9A-F]{8}) ", path.read_text(), re.M):
            starts.setdefault(int(m.group(2), 16), m.group(1))
    return starts


def named():
    out = {}
    for path in sorted((ROOT / "config").glob("symbol_addrs*.txt")) + sorted((ROOT / "config/symbols").glob("*.txt")):
        if path.name == "vtables.txt":
            continue
        for line in path.read_text().splitlines():
            m = re.match(r"(\w+) = 0x([0-9A-Fa-f]+);", line)
            if m:
                out[int(m.group(2), 16)] = m.group(1)
    return out


def main():
    args = sys.argv[1:]
    min_entries = int(args[args.index("--min") + 1]) if "--min" in args else 2
    t = TARGETS[0]
    image = (ROOT / t["original"]).read_bytes()
    base = t["image"][0]
    data, _, phdrs, sections = elf_survey.read_elf(ROOT / t["elf"])
    starts = function_starts()
    names = named()
    word = lambda a: struct.unpack_from("<I", image, a - base)[0]  # noqa: E731

    data_secs = [(s["addr"], s["addr"] + s["size"]) for s in sections
                 if s["name"] in (".data", ".rodata") and s["type"] != elf_survey.SHT_NOBITS]

    def slots_at(a):
        """The vtable's slots if a looks like one: an empty RTTI entry, then valid {delta, index, pfn} entries."""
        end = next((hi for lo, hi in data_secs if lo <= a < hi), None)
        if end is None or a % 8 or word(a) or word(a + 4):
            return None
        slots, b = [], a + 8
        while b + 8 <= end:
            hdr, pfn = word(b), word(b + 4)
            if hdr & 0xFFFF0000 not in (0, 0xFFFF0000) or (pfn and pfn not in starts) or (not pfn and hdr):
                break
            if not pfn and slots and not slots[-1]:
                break
            slots.append(pfn)
            b += 8
        while slots and not slots[-1]:
            slots.pop()
        return slots if sum(1 for p in slots if p) >= min_entries else None

    # A vtable is an address the code materialises (lui %hi + addiu %lo: constructors and destructors store it
    # into the object). Scanning data alone mistakes the empty RTTI entry for padding.
    vtables, ctors = {}, collections.defaultdict(set)
    text = [s for s in sections if s["name"] == ".text"][0]
    hi = {}
    order = sorted(starts)
    import bisect
    for off in range(0, text["size"], 4):
        ins = word(text["addr"] + off)
        op, rs, rt, imm = ins >> 26, (ins >> 21) & 31, (ins >> 16) & 31, ins & 0xFFFF
        if op == 0x0F:
            hi[rt] = imm << 16
        elif op == 0x09 and rs in hi:
            addr = (hi[rs] + (imm - 0x10000 if imm & 0x8000 else imm)) & 0xFFFFFFFF
            if addr not in vtables:
                sl = slots_at(addr)
                if sl is None:
                    continue
                vtables[addr] = sl
            at = text["addr"] + off
            k = bisect.bisect_right(order, at) - 1
            if k >= 0:
                ctors[addr].add(order[k])

    out, used = [], set(names.values())
    report = []
    for vt, slots in sorted(vtables.items()):
        cls = None
        for p in slots:
            n = names.get(p, "")
            m = re.match(r"(C[A-Z]\w*?)_[A-Z]\w*$", n)
            if m and not n.startswith("CFunc_"):
                cls = m.group(1)
                break
        cls = cls or f"C{vt:06X}"
        report.append(f"{vt:#010x} {cls:<28} {len(slots)} slots, ctors: "
                      + ", ".join(starts.get(c, hex(c)) for c in sorted(ctors[vt])))
        out.append(f"// {cls}: vtable at {vt:#010x} ({len(slots)} slots); scripts/vtables.py")
        vname = f"{cls}_vtable"
        if vname not in used:
            out.append(f"{vname} = 0x{vt:08X}; // size:0x{8 + 8 * len(slots):X}")
            used.add(vname)
        for i, p in enumerate(slots):
            if not p or p in names or starts.get(p, "").startswith("_"):
                continue
            n = f"{cls}_Virtual{i + 1}"
            if n in used:
                continue
            names[p] = n
            used.add(n)
            out.append(f"{n} = 0x{p:08X}; // type:func // guess")
        for c in sorted(ctors[vt]):
            if c in names:
                continue
            n = f"{cls}_Ctor" if f"{cls}_Ctor" not in used else f"{cls}_Ctor_{c:06X}"
            names[c] = n
            used.add(n)
            out.append(f"{n} = 0x{c:08X}; // type:func // guess")
    if "--report" in args:
        print(f"{len(vtables)} vtables")
        print("\n".join(report))
    else:
        print("\n".join(out))


if __name__ == "__main__":
    main()
