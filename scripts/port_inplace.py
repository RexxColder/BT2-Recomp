#!/usr/bin/env python3
"""Builds a full-C test executable: the original SLUS_214.41 with non-matching C written over functions in place.

Usage: scripts/port_inplace.py [--only FILE] [--exclude FILE] [--max N] [--out build_port/SLUS_214.41]

Step 1 of the PC-port plan (docs/PORT_LOG.md §17): before C replaces the whole game on PC, every C version of a
function must behave like the original. Here each candidate (an m2c draft that compiles but does not match byte for
byte: scratch/m2c_sweep/status.csv `differs`) whose code is not larger than the original function is linked AT the
original address (against the matching build's symbols, build/SLUS_214.41.elf) and written over it, the rest of
the original slot filled with nops. Every address stays where it was (data, pointer tables, the DBZP overlay that
calls the executable at fixed addresses), so the result boots on PCSX2 with the original disc, and any subset of
functions can be switched on or off to find the one that breaks the game (--only / --exclude: files of
addresses, one per line).

Left out: drafts with data of their own (they would need room for it), larger than the slot, or with names no
symbol gives an address. The executable is written to --out; the list of patched functions next to it (.list).
"""

import argparse
import csv
import re
import struct
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import BINUTILS, LINKER, ROOT, TARGETS  # noqa: E402
import fdiff  # noqa: E402
import integrate_xfer  # noqa: E402

DRAFTS = Path("scratch") / "m2c_sweep"  # relative: fdiff keys its scratch dirs on the path
WORK = ROOT / "build_port" / "obj"
DATA = (".rodata", ".data", ".sdata", ".lit4", ".lit8", ".bss", ".sbss")


def elf_symbols(elf):
    out = subprocess.run([str(ROOT / (BINUTILS + "nm")), str(elf)], capture_output=True, text=True).stdout
    syms = {}
    for line in out.splitlines():
        p = line.split()
        if len(p) == 3:
            syms.setdefault(p[2], int(p[0], 16))
    return syms


def in_c_ranges():
    rng = sorted((int(l.split()[0], 16), int(l.split()[1], 16))
                 for l in (ROOT / "config/c_files.txt").read_text().splitlines() if l.strip())
    return lambda a: any(x <= a < y for x, y in rng)


FAR = 0x00090000  # --far: free EE RAM below the game (0x82000-0xFFFFF is unused); fn_diff jumps here from F


def build_one(job, syms, far=False):
    addr, name, size = job[:3]
    src = job[3] if len(job) > 3 else DRAFTS / f"m2c_{addr:06X}.c"
    obj = fdiff.compile_src(src, "default")
    if obj is None:
        return addr, name, None, "compile"
    sizes = integrate_xfer.section_sizes(obj)
    if any(sizes.get(s, 0) for s in DATA):
        return addr, name, None, "own data"
    funcs = fdiff.functions(obj)
    if name not in funcs or len(funcs) != 1:
        return addr, name, None, "functions"
    if sizes.get(".text", 0) > size and not far:
        return addr, name, None, "larger"
    # Undefined names: the matching build's symbols, or the address an auto name spells.
    nm = subprocess.run([str(ROOT / (BINUTILS + "nm")), "-u", str(obj)], capture_output=True, text=True).stdout
    defs = []
    for u in nm.split():
        if u == "U":
            continue
        if u in syms:
            defs.append(f"{u} = 0x{syms[u]:08X};")
        elif (m := re.fullmatch(r"(?:func|D)_([0-9A-F]{8})", u)):
            defs.append(f"{u} = 0x{int(m.group(1), 16):08X};")
        else:
            return addr, name, None, f"no address for {u}"
    out = (WORK.parent / "obj_far" if far else WORK) / f"{addr:08X}"
    out.mkdir(parents=True, exist_ok=True)
    gp = syms.get("_gp", 0x0038BDF0)
    (out / "syms.ld").write_text("\n".join(defs + [f"_gp = 0x{gp:08X};"]) + "\n")
    elf = out / "f.elf"
    base = FAR if far else addr
    r = subprocess.run([LINKER, "-EL", "-Ttext", f"0x{base:08X}", "-e", f"0x{base:08X}", "-T", str(out / "syms.ld"),
                        str(obj), "-o", str(elf)], capture_output=True, text=True, cwd=ROOT)
    if r.returncode:
        return addr, name, None, "link: " + r.stderr.strip().splitlines()[-1][:80]
    binf = out / "f.bin"
    subprocess.run([str(ROOT / (BINUTILS + "objcopy")), "-O", "binary", "-j", ".text", str(elf), str(binf)], check=True)
    code = binf.read_bytes()
    if far:
        return addr, name, code, "OK" if len(code) <= 0x70000 else "too large for the far area"
    if len(code) > size:
        return addr, name, None, "larger"
    return addr, name, code + b"\0" * (size - len(code)), "OK"


def elf_segments(data):
    """[(vaddr, offset, filesz)] of the PT_LOAD segments of a 32-bit little-endian ELF."""
    phoff, = struct.unpack_from("<I", data, 0x1C)
    phentsize, phnum = struct.unpack_from("<HH", data, 0x2A)
    segs = []
    for i in range(phnum):
        p_type, p_off, p_vaddr, _, p_filesz = struct.unpack_from("<IIIII", data, phoff + i * phentsize)
        if p_type == 1:
            segs.append((p_vaddr, p_off, p_filesz))
    return segs


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--only")
    ap.add_argument("--exclude")
    ap.add_argument("--max", type=int)
    ap.add_argument("--far", action="store_true", help="link each C at 0x90000 (for C larger than the original "
                    "slot); writes build_port/obj_far/<ADDR>/f.bin and <out>.far.list, patches nothing")
    ap.add_argument("--src-dir", type=Path, help="C files <ADDR6>.c (relative, e.g. port/eq) instead of the m2c drafts")
    ap.add_argument("--jobs", type=int, default=6)
    ap.add_argument("--out", type=Path, default=ROOT / "build_port" / "SLUS_214.41")
    a = ap.parse_args()
    t = TARGETS[0]
    syms = elf_symbols(ROOT / t["elf_out"])
    taken = in_c_ranges()
    only = {int(x, 16) for x in Path(a.only).read_text().split()} if a.only else None
    excl = {int(x, 16) for x in Path(a.exclude).read_text().split()} if a.exclude else set()
    jobs = []
    for r in csv.DictReader(open(ROOT / DRAFTS / "status.csv")):
        addr = int(r["addr"], 16)
        # With --src-dir any status counts: the C there was written by hand, the m2c draft's status is irrelevant.
        if (not a.src_dir and not r["status"].startswith("differs")) or taken(addr) or addr >= 0x3B3100 or addr in excl:
            continue
        if only is not None and addr not in only:
            continue
        if a.src_dir:
            src = a.src_dir / f"{addr:06X}.c"
            if (ROOT / src).exists():
                jobs.append((addr, r["name"], int(r["size"], 16), src))
            continue
        jobs.append((addr, r["name"], int(r["size"], 16)))
    if a.max:
        jobs = jobs[:a.max]
    with ThreadPoolExecutor(a.jobs) as ex:
        res = list(ex.map(lambda j: build_one(j, syms, a.far), jobs))
    if a.far:
        ok = [f"0x{addr:08X} {name} 0x{len(code):X}" for addr, name, code, reason in res if code is not None]
        Path(str(a.out) + ".far.list").write_text("\n".join(ok) + "\n")
        print(f"{len(jobs)} candidates; {len(ok)} linked at 0x{FAR:X} -> {a.out}.far.list")
        return
    why = {}
    for _, _, _, reason in res:
        k = reason.split(":")[0]
        why[k] = why.get(k, 0) + 1
    data = bytearray((ROOT / t["elf"]).read_bytes())
    segs = elf_segments(data)
    patched = []
    for addr, name, code, reason in res:
        if code is None:
            continue
        seg = next(((v, o, n) for v, o, n in segs if v <= addr and addr + len(code) <= v + n), None)
        if seg is None:
            continue
        off = seg[1] + addr - seg[0]
        data[off:off + len(code)] = code
        patched.append(f"0x{addr:08X} {name} 0x{len(code):X}")
    a.out.parent.mkdir(parents=True, exist_ok=True)
    a.out.write_bytes(bytes(data))
    Path(str(a.out) + ".list").write_text("\n".join(patched) + "\n")
    print(f"{len(jobs)} candidates: {why}; patched {len(patched)} functions "
          f"({sum(int(p.split()[2], 16) for p in patched) // 1024} KB) -> {a.out}")


if __name__ == "__main__":
    main()
