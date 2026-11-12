#!/usr/bin/env python3
"""First look at a PS2 executable: sections, $gp, source-file strings and the compiler of each region.

Usage: elf_survey.py ELF [--yaml] [--regions]

  (default)   report: sections, program header, $gp, prologue styles, source-file strings
  --yaml      print a splat `segments:` block with one subsegment per allocated section
  --regions   print the address runs that share one prologue style (one per line)

The compiler is told apart by how a function prologue saves callee-saved registers:

  sd8    `sd $s0,0($sp); sd $ra,8($sp)`         Sony ee-gcc 2.96 (decompme `ee-gcc2.96`) OR SN ProDG
                                                2.95.3-136 with -fopt-stack (Tony Hawk's Downhill Jam)
  sd16   `sd $s0,0($sp); sd $ra,0x10($sp)`      Sony ee-gcc 2.9-ee-991111
  sq     `sq $s0,0($sp); ... sd/sq $ra`         SN Systems ProDG EE GCC 2.95.x
  sw     32-bit `sw` saves                       Metrowerks / other (not ee-gcc)

Only functions that save at least two registers can be classified; leaves are `-`. The prologue only narrows
the family down: cc_probe.py on a few hand-written probe functions settles the exact build and flags.
"""

import collections
import re
import struct
import sys

SHT_NOBITS = 8
SHT_MIPS_REGINFO = 0x70000006
SHF_ALLOC = 2

SAVED = set(range(16, 24)) | {28, 30, 31}  # s0-s7, gp, fp, ra
OP_SD, OP_SQ, OP_SW = 0x3F, 0x1F, 0x2B


def read_elf(path):
    data = open(path, "rb").read()
    if data[:4] != b"\x7fELF":
        sys.exit(f"{path}: not an ELF")
    entry, phoff, shoff = struct.unpack_from("<III", data, 24)
    phentsize, phnum, shentsize, shnum, shstrndx = struct.unpack_from("<HHHHH", data, 42)
    phdrs = [struct.unpack_from("<8I", data, phoff + i * 32) for i in range(phnum)]
    sections = []
    if shnum:
        raw = [struct.unpack_from("<10I", data, shoff + i * 40) for i in range(shnum)]
        strtab = raw[shstrndx][4]
        for name, typ, flags, addr, off, size, *_rest, align, _es in raw:
            sname = data[strtab + name:].split(b"\0", 1)[0].decode()
            sections.append(dict(name=sname, type=typ, flags=flags, addr=addr, off=off, size=size, align=align))
    return data, entry, phdrs, sections


def load_phdr(phdrs):
    """The first PT_LOAD program header (BT3's ELF lists a REGINFO header first)."""
    return next(p for p in phdrs if p[0] == 1)


def load_span(phdrs):
    """(first vaddr, end of file data, end of memory) over every PT_LOAD header: the flat image is
    [first vaddr, end of file data) and the program occupies up to end of memory (BT3 has two LOADs)."""
    loads = [p for p in phdrs if p[0] == 1 and p[5]]  # BT3 also has an empty LOAD at 0
    return (min(p[2] for p in loads), max(p[2] + p[4] for p in loads), max(p[2] + p[5] for p in loads))


def image_size(phdrs):
    """Bytes of the flat image: up to the end of the file data, rounded up to 128 the way BT3-Decompiled's
    ROM_PAD_TO was (splat cannot emit a data segment ending off a word boundary, e.g. BT3's last string)."""
    base, fend, _ = load_span(phdrs)
    return (fend - base + 127) & ~127


def gp_value(data, sections):
    for s in sections:
        if s["name"] == ".reginfo" and s["size"] >= 24:
            return struct.unpack_from("<I", data, s["off"] + 20)[0]
    return None


def words(data, sec):
    raw = data[sec["off"]:sec["off"] + sec["size"]]
    return struct.unpack(f"<{len(raw) // 4}I", raw[:len(raw) // 4 * 4])


def code_sections(data, phdrs, sections):
    """Executable sections; a flattened ELF (one RWE section, e.g. RE Outbreak) is scanned whole."""
    text = [s for s in sections if s["name"].startswith(".text") and s["type"] != SHT_NOBITS]
    if text:
        return text
    p = load_phdr(phdrs)
    return [dict(name="LOAD", addr=p[2], off=p[1], size=p[4])]


def prologues(data, sec):
    """[(addr, style)] for every `addiu $sp,$sp,-N` in the section."""
    w = words(data, sec)
    out = []
    for i, ins in enumerate(w):
        if ins >> 16 != 0x27BD or not ins & 0x8000:
            continue
        saves = []
        for j in range(i + 1, min(i + 24, len(w))):
            x = w[j]
            if x == 0x03E00008:  # jr $ra
                break
            op, base, rt, off = x >> 26, (x >> 21) & 31, (x >> 16) & 31, x & 0xFFFF
            if base == 29 and rt in SAVED and op in (OP_SD, OP_SQ, OP_SW):
                saves.append((op, rt, off))
        out.append((sec["addr"] + i * 4, classify(saves)))
    return out


def classify(saves):
    if not saves:
        return "-"
    ops = {op for op, rt, _ in saves}
    gpr = [(op, off) for op, rt, off in saves if rt != 31]
    if OP_SQ in {op for op, _ in gpr}:
        return "sq"
    if ops == {OP_SW}:
        return "sw"
    offs = sorted(off for op, rt, off in saves if op == OP_SD)
    if len(offs) < 2:
        return "-"
    steps = {b - a for a, b in zip(offs, offs[1:])}
    if 8 in steps:
        return "sd8"
    if steps == {16}:
        return "sd16"
    return "-"


def regions(found, min_run=3):
    """Merge consecutive classified functions into runs of one style (unclassified ones join the run)."""
    runs = []
    for addr, style in found:
        if style == "-":
            continue
        if runs and runs[-1][2] == style:
            runs[-1][1] = addr
            runs[-1][3] += 1
        else:
            runs.append([addr, addr, style, 1])
    return [r for r in runs if r[3] >= min_run or len(runs) == 1]


SOURCE_RE = re.compile(rb"[\w./\\-]{2,80}\.(?:c|cc|cpp|cxx|h|hpp)\b")


def report(path):
    data, entry, phdrs, sections = read_elf(path)
    print(f"{path}: entry {entry:#x}  e_flags {struct.unpack_from('<I', data, 0x24)[0]:#x}")
    for p in phdrs:
        if p[0] == 1 and p[5]:
            print(f"  LOAD off {p[1]:#x} vaddr {p[2]:#x} filesz {p[4]:#x} memsz {p[5]:#x}")
    print("\nsections (allocated):")
    for s in sections:
        if s["flags"] & SHF_ALLOC or s["name"].startswith(".DVP"):
            kind = "NOBITS" if s["type"] == SHT_NOBITS else "data"
            print(f"  {s['name']:<22} {s['addr']:#010x} size {s['size']:#8x} align {s['align']:3} {kind}")
    names = {s["name"] for s in sections}
    print(f"\n$gp = {gp_value(data, sections) or 0:#x}"
          f"   small data: {'yes' if names & {'.sdata', '.lit4', '.lit8'} else 'no (.sdata/.lit4 absent: probably -G0)'}")
    print(f"symbols: {'present' if '.symtab' in names else 'stripped'}"
          f"   C++ EH: {'yes' if '.gcc_except_table' in names or '.eh_frame' in names else 'no'}")

    text = code_sections(data, phdrs, sections)
    found = [x for s in text for x in prologues(data, s)]
    hist = collections.Counter(style for _, style in found)
    print(f"\nprologues: {len(found)} frames  " + "  ".join(f"{k}={v}" for k, v in hist.most_common()))
    print("compiler guess: " + {
        "sd8": "Sony ee-gcc 2.96 or SN ProDG 2.95.3-136 -fopt-stack (tell apart with cc_probe.py)", "sd16": "Sony ee-gcc 2.9-ee-991111",
        "sq": "SN ProDG EE GCC 2.95.x", "sw": "not ee-gcc (Metrowerks?)"}.get(
        next((k for k, _ in hist.most_common() if k != "-"), "-"), "unknown"))
    rs = regions(found)
    styles = collections.Counter(r[2] for r in rs)
    print(f"style runs (>=3 functions): {len(rs)}  " + "  ".join(f"{k}={v}" for k, v in styles.items()))
    for lo, hi, style, n in rs:
        if style != hist.most_common(1)[0][0] or len(rs) < 12:
            print(f"    {lo:#010x}-{hi:#010x} {style:5} {n} functions")

    srcs = collections.Counter(m.decode() for m in SOURCE_RE.findall(data))
    print(f"\nsource-file strings: {len(srcs)}")
    for s, _ in sorted(srcs.items())[:60]:
        print(f"    {s}")


def yaml_segments(path):
    """splat segments: one subsegment per allocated section, the way BT3-Decompiled started."""
    data, entry, phdrs, sections = read_elf(path)
    base, fend, mend = load_span(phdrs)
    filesz = image_size(phdrs)
    lines = ["segments:", "  - name: cod", "    type: code", "    start: 0x000000", f"    vram: {base:#010x}",
             f"    bss_size: {sum(s['size'] for s in sections if s['type'] == SHT_NOBITS and s['flags'] & SHF_ALLOC and fend <= s['addr'] < mend):#X}",
             "    subalign: null", "    align: 128", "    subsegments:"]
    kinds = {".text": "asm", ".vutext": "textbin", ".rodata": "rodata", ".lit4": "lit4", ".lit8": "lit8",
             ".sdata": "sdata"}
    lines = ["segments:", "  - name: cod", "    type: code", "    start: 0x000000", f"    vram: {base:#010x}",
             f"    bss_size: {sum(s['size'] for s in sections if s['type'] == SHT_NOBITS and s['flags'] & SHF_ALLOC and s['addr'] >= base + filesz):#X}",
             "    subalign: null", "    align: 128", "    subsegments:"]
    rodata_seen = False
    for s in sorted(sections, key=lambda s: s["addr"]):
        if not s["flags"] & SHF_ALLOC or s["addr"] < base or s["type"] == SHT_MIPS_REGINFO:
            continue
        off = s["addr"] - base
        if s["type"] == SHT_NOBITS:
            if s["size"] and s["addr"] < mend:
                kind = "sbss" if s["name"] == ".sbss" else "bss"
                lines.append(f"      - {{ type: {kind}, vram: {s['addr']:#010X}, name: cod/{s['addr']:08X} }} # {s['name']}")
            continue
        if not s["size"]:
            continue
        # splat links by type (.text, .data, .rodata, .bss): a data section placed after .rodata in the
        # original (e.g. .gcc_except_table) must be typed rodata to keep its address. Small data sections
        # between the code and .data (BT2: .text_nop, .ctors, .dtors, .reginfo after .vutext) would move to the
        # data part: they stay in the code as one textbin up to the next code or .data section.
        if s["name"] not in (".text", ".vutext") and lines[-1].split(", ")[1] in ("asm", "textbin") \
                and not rodata_seen and not s["name"] in (".data", ".rodata"):
            if lines[-1].split(", ")[1] == "textbin" and "(stay in code)" in lines[-1]:
                continue
            lines.append(f"      - [{off:#08X}, textbin, cod/{off:06X}] # {s['name']} and what follows up to .data"
                         " (stay in code)")
            continue
        kind = kinds.get(s["name"], "rodata" if rodata_seen else "data")
        rodata_seen = rodata_seen or s["name"] == ".rodata"
        lines.append(f"      - [{off:#08X}, {kind}, cod/{off:06X}] # {s['name']}")
    lines.append(f"  - [{filesz:#X}]")
    return "\n".join(lines).replace("0X", "0x")


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    path = sys.argv[1]
    if "--yaml" in sys.argv:
        print(yaml_segments(path))
    elif "--regions" in sys.argv:
        data, _, phdrs, sections = read_elf(path)
        text = code_sections(data, phdrs, sections)
        for lo, hi, style, n in regions([x for s in text for x in prologues(data, s)]):
            print(f"{lo:#010x} {hi:#010x} {style} {n}")
    else:
        report(path)


if __name__ == "__main__":
    main()
