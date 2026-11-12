#!/usr/bin/env python3
"""Compiles one C/C++ file and compares each of its functions against the original binary.

Usage: scripts/fdiff.py [--cc KEY|--all-cc] src/sys/heap.c [function ...]

Relocated fields (jump targets, %hi/%lo/%gp_rel immediates) are masked out, so a function can be
checked before the file is linked in. The linked build's byte comparison is the final word.
Target addresses come from the symbol files in config/, so a newly added name works without
re-running configure. The original bytes are read from disc/, not from build/.

--flags "..." replaces the compiler flags of game.toml (for sweeping -O/-f options while
identifying the original's).

Compiler: the one config/cc_<key>.txt assigns to the file, else the default `cc` of game.toml.
--cc KEY forces one (`default` or a key of [toolchain.alt_cc]); --all-cc tries every compiler and
keeps the closest (what RE Outbreak needed: modules were built with three ee-gcc versions).
"""

import os
import re
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import (ROOT, BINUTILS, CC, CC_FLAGS, CXX_FLAGS, ALT_CC, STRIP_PAD, CC_AS_FLAGS, TARGETS,  # noqa: E402
                     alt_cc_files, gflag, as_gflag, target_for)

# Bits of an instruction word that a relocation fills in.
RELOC_MASK = {
    "R_MIPS_26": 0x03FFFFFF,
    "R_MIPS_HI16": 0xFFFF,
    "R_MIPS_LO16": 0xFFFF,
    "R_MIPS_GPREL16": 0xFFFF,
    "R_MIPS_LITERAL": 0xFFFF,
}


def sh(*cmd):
    return subprocess.run(cmd, cwd=ROOT, check=True, capture_output=True, text=True).stdout


def scratch(src, key):
    """Per-source scratch folder, so several runs can go in parallel."""
    return ROOT / "build" / "fdiff" / ("_".join(Path(src).with_suffix("").parts) + f"_{key}")


FLAGS_OVERRIDE = None


def compile_src(src, key):
    out = scratch(src, key + ("_f" if FLAGS_OVERRIDE else "")) / Path(src).with_suffix(".o").name
    out.parent.mkdir(parents=True, exist_ok=True)
    asm = out.with_suffix(".s")
    # a failed compile must not leave the previous run's object to be compared (it reported a stale result)
    out.unlink(missing_ok=True)
    asm.unlink(missing_ok=True)
    cc = CC if key == "default" else ALT_CC[key]
    flags = FLAGS_OVERRIDE or (CXX_FLAGS if Path(src).suffix == ".cpp" else CC_FLAGS)
    r = subprocess.run(cc.split() + flags.split() + [gflag(src), "-S", str(src), "-o", str(asm)],
                       cwd=ROOT, capture_output=True, text=True, env=dict(os.environ, WINEDEBUG="-all"))
    if r.returncode:
        print(f"# {key}: compile failed\n{r.stderr}", file=sys.stderr)
        return None
    if r.stderr:
        print(r.stderr, file=sys.stderr)
    if key in STRIP_PAD:
        subprocess.run([sys.executable, str(Path(__file__).parent / "strip_func_pad.py"), str(asm)], check=True)
    sh(BINUTILS + "as", *CC_AS_FLAGS.split(), as_gflag(src), "include/gcc_prelude.inc", str(asm), "-o", str(out))
    return out


def functions(obj):
    """name -> (offset, size) for functions defined in the object's .text."""
    funcs = {}
    for line in sh(BINUTILS + "readelf", "-sW", str(obj)).splitlines():
        p = line.split()
        if len(p) == 8 and p[3] == "FUNC" and p[6] != "UND":
            funcs[p[7]] = (int(p[1], 16), int(p[2]))
    return funcs


def reloc_masks(obj):
    """.text offset -> mask of relocated bits."""
    masks = {}
    in_text = False
    for line in sh(BINUTILS + "readelf", "-rW", str(obj)).splitlines():
        if line.startswith("Relocation section"):
            in_text = "'.rel.text'" in line
            continue
        p = line.split()
        if in_text and len(p) >= 3 and p[2] in RELOC_MASK:
            masks[int(p[0], 16)] = RELOC_MASK[p[2]]
    return masks


def text_bytes(obj):
    raw = obj.parent / "text.bin"
    sh(BINUTILS + "objcopy", "-O", "binary", "-j", ".text", str(obj), str(raw))
    return raw.read_bytes()


def targets():
    """name -> address from the symbol files, falling back to the linked ELFs' symbols."""
    found = {}
    files = sorted((ROOT / "config").glob("symbol_addrs*.txt")) + \
        sorted((ROOT / "config" / "symbols").glob("*.txt"))
    for path in files:
        for line in path.read_text().splitlines():
            m = re.match(r"(\w+) = 0x([0-9A-Fa-f]+);", line)
            if m:
                found[m.group(1)] = int(m.group(2), 16)
    for t in TARGETS:
        if not (ROOT / t["elf_out"]).exists():
            continue
        # A build in progress can be rewriting the ELF: then only the other sources count.
        nm = subprocess.run([BINUTILS + "nm", t["elf_out"]], cwd=ROOT, capture_output=True, text=True).stdout
        for line in nm.splitlines():
            p = line.split()
            if len(p) == 3 and p[1] in "Tt":
                found.setdefault(p[2], int(p[0], 16))
    # splat's own names for the functions still in asm, without a linked ELF (a build in progress or failed).
    fmap = ROOT / "port/funcmap.csv"
    if fmap.exists():
        for row in fmap.read_text().splitlines()[1:]:
            a = int(row.split(",")[1], 16)
            found.setdefault(f"func_{a:08X}", a)
    return found


def disasm(elf_or_obj, start, size, extra=()):
    out = sh(BINUTILS + "objdump", "-d", "-z", *extra, f"--start-address={start:#x}",
             f"--stop-address={start + size:#x}", str(elf_or_obj))
    lines = []
    for line in out.splitlines():
        if "\t" in line and ":" in line.split("\t")[0]:
            lines.append(" ".join(line.split("\t")[2:]))
    return lines


# Original images are read from disc/ so the tool does not depend on the state of build/
# (another process may be relinking).
def original_words(addr, size):
    t = target_for(addr)
    with open(ROOT / t["original"], "rb") as f:
        f.seek(addr - t["image"][0])
        data = f.read(size)
    return struct.unpack(f"<{len(data) // 4}I", data)


def original_disasm(addr, size):
    t = target_for(addr)
    return disasm(ROOT / t["original"], addr, size,
                  ("-D", "-b", "binary", "-m", "mips:5900", "-EL", f"--adjust-vma={t['image'][0]:#x}"))


def evaluate(obj, wanted, known):
    """(differing instructions, all OK, report lines) for every function in obj."""
    funcs = functions(obj)
    masks = reloc_masks(obj)
    text = text_bytes(obj)
    lines, nbad, ok = [], 0, True
    for name, (off, size) in sorted(funcs.items(), key=lambda kv: kv[1]):
        if wanted and name not in wanted:
            continue
        if name not in known:
            lines.append(f"{name}: no symbol with this name in the original; add it to the symbol files")
            ok = False
            nbad += size // 4
            continue
        addr = known[name]
        mine = struct.unpack(f"<{size // 4}I", text[off:off + size])
        orig = original_words(addr, size)
        bad = [i for i, (m, o) in enumerate(zip(mine, orig))
               if (m ^ o) & ~masks.get(off + i * 4, 0) & 0xFFFFFFFF]
        if not bad:
            lines.append(f"{name}: OK ({size:#x} bytes)")
            continue
        ok = False
        nbad += len(bad)
        lines.append(f"{name}: {len(bad)} of {size // 4} instructions differ")
        a = original_disasm(addr, size)
        b = disasm(obj, off, size)
        for i in range(max(len(a), len(b))):
            left = a[i] if i < len(a) else ""
            right = b[i] if i < len(b) else ""
            mark = "!" if i in bad else " "
            lines.append(f"  {mark} {i * 4:4x}  {left:<34} | {right}")
    return nbad, ok, lines


def main():
    global FLAGS_OVERRIDE
    args = sys.argv[1:]
    keys = None
    if args[:1] == ["--flags"]:
        FLAGS_OVERRIDE, args = args[1], args[2:]
    if args[:1] == ["--all-cc"]:
        keys, args = ["default", *ALT_CC], args[1:]
    elif args[:1] == ["--cc"]:
        keys, args = [args[1]], args[2:]
    if not args:
        sys.exit(__doc__)
    src = Path(args[0])
    wanted = args[1:]
    if keys is None:
        keys = [alt_cc_files().get(str(src), "default")]
    known = targets()

    best = None
    for key in keys:
        obj = compile_src(src, key)
        if obj is None:
            continue
        nbad, ok, lines = evaluate(obj, wanted, known)
        if best is None or nbad < best[0]:
            best = (nbad, key, lines, ok)
        if ok:
            break
    if best is None:
        sys.exit(f"could not compile {src}")
    if len(keys) > 1:
        print(f"# compiler: {best[1]}" + ("" if best[3] else " (fewest differences)"))
    print("\n".join(best[2]))
    sys.exit(0 if best[3] else 1)


if __name__ == "__main__":
    main()
