#!/usr/bin/env python3
"""Points a C file's calls and data references at the addresses the original uses.

Usage: scripts/fix_targets.py FILE.c START [--write] [--keep-unknown]

BT2 has several copies of some helpers (the VU0 matrix routines, Vec4_*/Mtx_*), and each module calls its own copy.
C taken from BT3, or written against a name, can compile to the right instructions (fdiff masks jal targets and
%hi/%lo/%gp_rel) and still link against the wrong copy: the gate then finds the bytes differ. This tool compiles
FILE.c, resolves every relocation of its .text against the original bytes as if the file were linked at START
(scripts/integrate_xfer.resolve), and for each symbol whose single resolved address is not the address that name
has, adds at the top of the file

    #define Name name_at_that_address   /* fix_targets: the original calls 0x... here */

so the header prototype and every use follow (a define before the includes renames the declaration too). The
name at an address comes from the linked ELF (build/SLUS_214.41.elf: real names and splat's func_/D_ labels).
A symbol resolved to two addresses in one file is reported and left alone (the file needs a hand edit).
Exit 0 when nothing had to change or --write applied the changes; 1 when changes are needed (no --write) or some
symbol is ambiguous.
"""

import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import BINUTILS, ROOT, TARGETS  # noqa: E402
import fdiff  # noqa: E402
import integrate_xfer  # noqa: E402

MARK = "/* fix_targets */"


def names_by_address():
    out = subprocess.run([str(ROOT / (BINUTILS + "nm")), str(ROOT / TARGETS[0]["elf_out"])],
                         capture_output=True, text=True).stdout
    by_addr, by_name = {}, {}
    for line in out.splitlines():
        p = line.split()
        if len(p) != 3 or "." in p[2] or p[2].startswith("$") or p[1] not in "TtDdBbRrSsA" or p[2].endswith(".NON_MATCHING") or "_ROM_" in p[2] \
                or p[2].endswith(("_START", "_END")):
            continue
        a = int(p[0], 16)
        by_name.setdefault(p[2], a)
        # Prefer a real name over splat's auto label at one address.
        if a not in by_addr or re.fullmatch(r"(func|D|jtbl)_[0-9A-F]{8}", by_addr[a]):
            by_addr[a] = p[2]
    # Without a linked ELF (a failed build) and for anything it lacks: the symbol files, then splat's auto names
    # (func_ for a function start of port/funcmap.csv, D_ otherwise) for what is still in asm.
    for name, a in fdiff.targets().items():
        by_name.setdefault(name, a)
        if a not in by_addr or re.fullmatch(r"(func|D|jtbl)_[0-9A-F]{8}", by_addr[a]):
            if not re.fullmatch(r"(func|D|jtbl)_[0-9A-F]{8}", name):
                by_addr[a] = name
    starts = {int(r.split(",")[1], 16) for r in (ROOT / "port/funcmap.csv").read_text().splitlines()[1:]}
    by_addr = AutoNames(by_addr, starts)
    return by_addr, by_name


class AutoNames(dict):
    def __init__(self, d, starts):
        super().__init__(d)
        self.starts = starts

    def get(self, a, default=None):
        if a in self:
            return self[a]
        return f"func_{a:08X}" if a in self.starts else f"D_{a:08X}"


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    src, start, write = Path(sys.argv[1]), int(sys.argv[2], 16), "--write" in sys.argv
    # A name no symbol file has yet is one the caller is about to define (integrate_xfer.py): leave it alone.
    keep_unknown = "--keep-unknown" in sys.argv
    text = src.read_text()
    obj = fdiff.compile_src(src, "default")
    if obj is None:
        sys.exit(f"{src}: does not compile")
    defined = set(fdiff.functions(obj))
    resolved = defaultdict(set)
    integrate_xfer.resolve(obj, start, resolved)
    by_addr, by_name = names_by_address()
    known = fdiff.targets()
    fixes, ambiguous = {}, []
    for sym, addrs in sorted(resolved.items()):
        if sym in defined:
            continue
        if len(addrs) != 1:
            ambiguous.append(f"{sym} -> {', '.join(f'{a:#x}' for a in sorted(addrs))}")
            continue
        addr = next(iter(addrs))
        have = known.get(sym, by_name.get(sym))
        if have == addr or (have is None and keep_unknown):
            continue
        target = by_addr.get(addr)
        if not target:
            ambiguous.append(f"{sym} -> {addr:#x} (no name there)")
            continue
        if target != sym:
            fixes[sym] = (target, addr)
    for sym, (target, addr) in fixes.items():
        print(f"{src}: {sym} -> {target} (the original uses {addr:#x})")
    for a in ambiguous:
        print(f"{src}: AMBIGUOUS {a}")
    if fixes and write:
        lines = "".join(f"#define {s} {t}  {MARK} /* the original uses {a:#x} here */\n"
                        for s, (t, a) in sorted(fixes.items()))
        src.write_text(lines + text)
        # The rename must not break the file (a local prototype can clash with the header's): recheck with fdiff,
        # and put the file back as it was if it no longer compiles to OK.
        r = subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), str(src)], cwd=ROOT,
                           capture_output=True, text=True)
        verdicts = [l for l in r.stdout.splitlines() if re.match(r"\w+: ", l)]
        if r.returncode or not verdicts or any(": OK" not in l for l in verdicts):
            src.write_text(text)
            print(f"{src}: retargeting breaks the file, reverted")
            return 1
    return 1 if ambiguous or (fixes and not write) else 0


if __name__ == "__main__":
    sys.exit(main())
