#!/usr/bin/env python3
"""Turns M2C_ERROR functions into top-level __asm__ C files (the BT3 way) and checks them with fdiff.

  scripts/vu0_wrap.py --classify                 which instruction kinds the M2C_ERROR functions contain
  scripts/vu0_wrap.py --addr 0x00112818 ...      generate + check the given functions
  scripts/vu0_wrap.py --all [--vu0-only]         generate + check every M2C_ERROR function (--vu0-only: those
                                                 with at least one VU0 / COP2 / LQC2 / SQC2 instruction)
  options: --jobs N (default 4, max 4), --out DIR (default scratch/vu0/src), --ok FILE (default scratch/vu0/ok.txt)

Input is scratch/m2c_sweep/<ADDR8>.s (one line per instruction: `/* off addr WORD */ mnemonic operands`, WORD is
little endian) and scratch/m2c_sweep/status.csv for names and sizes. Each function becomes one file,
scratch/vu0/src/vu0_<ADDR6>.c, holding the whole function as a top-level __asm__ block: the same mnemonics,
branch targets as labels, symbols by name (%hi/%lo/%gp_rel/jal stay symbolic). Every name used must be a symbol
of config/symbols/*.txt or config/symbol_addrs.txt, or a glabel/alabel/dlabel/jlabel of scratch/asm_snap/.
A function is OK only if fdiff prints `NAME: OK`; the OK list is written to --ok as `0xSTART 0xEND vu0_<ADDR6>`.

Not done here: mixed functions (level b, m2c on a copy with inline asm statements) and anything that needs C.
"""
import argparse
import csv
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SWEEP = ROOT / "scratch/m2c_sweep"
SNAP = ROOT / "scratch/asm_snap"
SYM_FILES = sorted((ROOT / "config/symbols").glob("*.txt")) + [ROOT / "config/symbol_addrs.txt"]

INS_RE = re.compile(r"^\s*/\* ([0-9A-Fa-f]+) ([0-9A-Fa-f]{8}) ([0-9A-Fa-f]{8}) \*/\s?(.*)$")
SYM_DEF_RE = re.compile(r"^([A-Za-z_][\w.]*)\s*=\s*0x[0-9A-Fa-f]+")
LABEL_RE = re.compile(r"^\s*(glabel|alabel|dlabel|jlabel)\s+([A-Za-z_][\w.]*)")
IDENT_RE = re.compile(r"(?<![\$\w.%])[A-Za-z_][\w.]*")
RESERVED = {"hi", "lo", "gp_rel", "ACC"}
ADDR_NAME_RE = re.compile(r"^(func|D)_([0-9A-Fa-f]+)$")
VU0_KINDS = ("COP2", "LQC2", "SQC2", "QMFC2", "QMTC2", "CFC2", "CTC2", "BC2")


def word_of(hexbytes):
    return int.from_bytes(bytes.fromhex(hexbytes), "little")


def kind_of(word, mnem):
    """Coarse kind of one instruction word, for --classify."""
    op, rs, fn = word >> 26, (word >> 21) & 31, word & 63
    if op == 0x12:
        if rs & 16:
            return "VU0_MACRO"                 # COP2 with CO set: vmadd*, vmul*, vftoi*, vcallms, ...
        return {1: "QMFC2", 5: "QMTC2", 2: "CFC2", 6: "CTC2", 8: "BC2"}.get(rs, "COP2_OTHER")
    if op == 0x36:
        return "LQC2"
    if op == 0x3E:
        return "SQC2"
    if op == 0x32:
        return "LWC2"
    if op == 0x3A:
        return "SWC2"
    if op == 0x11:
        return "FPU"
    if op in (0x31, 0x39):
        return "FPU_MEM"
    if op == 0x10:
        return "COP0"
    if op == 0 and fn == 0x0C:
        return "SYSCALL"
    if op == 0 and fn == 0x0D:
        return "BREAK"
    if op == 0 and fn == 0x0F:
        return "SYNC"
    return None


def load_sweep_status():
    """All rows of status.csv; the target set is the rows with M2C_ERROR in the status column."""
    with open(SWEEP / "status.csv") as f:
        return list(csv.DictReader(f))


def parse_listing(path):
    """Returns (name, [(offset, word, text), ...]) for one sweep .s, text with comments removed."""
    name, insns = None, []
    for line in path.read_text().splitlines():
        m = INS_RE.match(line)
        if m:
            text = m.group(4)
            text = re.sub(r"\s*/\*.*?\*/\s*$", "", text)     # trailing /* handwritten instruction */
            if text.lstrip().startswith(".word"):
                text = re.sub(r"\s+#.*$", "", text)          # .word 0x... # disassembly comment
            insns.append((m.group(2), word_of(m.group(3)), text.strip()))
            continue
        s = line.strip()
        if s.startswith("glabel ") and name is None:
            name = s.split()[1]
        elif s.startswith("alabel "):
            insns.append(("label", None, s.split()[1] + ":"))
        elif re.match(r"^\.L[0-9A-Fa-f]+:$", s):
            insns.append(("label", None, s))
        elif s.startswith(".align"):
            insns.append(("align", None, s))
    return name, insns


def known_symbols():
    names = set()
    for p in SYM_FILES:
        if p.exists():
            for line in p.read_text(errors="replace").splitlines():
                m = SYM_DEF_RE.match(line.strip())
                if m:
                    names.add(m.group(1))
    for p in list(SNAP.rglob("*.s")):
        for line in p.read_text(errors="replace").splitlines():
            m = LABEL_RE.match(line)
            if m:
                names.add(m.group(2))
    return names


def build_asm(name, insns, known):
    """Returns (asm lines, set of unknown names). Labels local to the function are defined in-file."""
    local = {t[:-1] for _, _, t in insns if t.endswith(":") and t != "label"}
    lines, unknown = [], set()
    for off, word, text in insns:
        if off == "label":
            lines.append(text)
            continue
        if off == "align":
            lines.append(text)
            continue
        mnem, _, ops = text.partition(" ")
        if mnem in (".set", ".include", ".section", "endlabel", "endlabel_"):
            continue
        if ops:
            def fix(m):
                ident = m.group(0)
                if ident in RESERVED or ident in local or ident == name or ident in known:
                    return ident
                a = ADDR_NAME_RE.match(ident)
                if a:                        # func_/D_ name with no label anywhere: its link address as a literal
                    return f"0x{int(a.group(2), 16):08X}"
                unknown.add(ident)
                return ident
            text = text.split(" ", 1)[0] + " " + IDENT_RE.sub(fix, ops)
        lines.append(text)
    return lines, unknown


def c_file(name, lines):
    out = ["#include \"common.h\"", "", "__asm__(",
           "    \".text\\n\"",
           "    \".align 3\\n\"",
           f"    \".globl {name}\\n\"",
           f"    \".type {name}, @function\\n\"",
           "    \".set push\\n\"",
           "    \".set noreorder\\n\"",
           "    \".set noat\\n\"",
           f"    \"{name}:\\n\""]
    for ln in lines:
        if ln.endswith(":") and not ln.startswith(" "):
            out.append(f"    \"{ln}\\n\"")
        else:
            out.append(f"    \"    {ln}\\n\"")
    out += ["    \".set pop\\n\"", ");", ""]
    return "\n".join(out)


def check(path, name):
    r = subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), str(path), name],
                       cwd=ROOT, capture_output=True, text=True)
    return r.returncode == 0 and re.search(rf"^{re.escape(name)}: OK\b", r.stdout, re.M) is not None, \
        (r.stdout + r.stderr).strip()


def run_one(row, out_dir, known):
    addr = int(row["addr"], 16)
    a6 = f"{addr:08x}"[-6:]  # ADDR6: the low six hex digits
    name, insns = parse_listing(SWEEP / f"{addr:08X}.s")
    if name is None:
        return row, False, "no glabel", None
    lines, unknown = build_asm(name, insns, known)
    if unknown:
        return row, False, "unknown symbols: " + " ".join(sorted(unknown)), None
    path = out_dir / f"vu0_{a6}.c"
    path.write_text(c_file(name, lines))
    ok, msg = check(path.relative_to(ROOT), name)   # fdiff derives its build folder from a relative path
    return row, ok, msg, name


def classify(rows):
    cats = {}
    per = {}
    for r in rows:
        addr = int(r["addr"], 16)
        _, insns = parse_listing(SWEEP / f"{addr:08X}.s")
        kinds = set()
        for _, word, text in insns:
            if word is None:
                continue
            k = kind_of(word, text.split(" ")[0])
            if k:
                kinds.add(k)
        per[r["addr"]] = kinds
        for k in kinds:
            cats[k] = cats.get(k, 0) + 1
    return cats, per


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--addr", action="append", default=[], help="function address, e.g. 0x00112818")
    ap.add_argument("--all", action="store_true", help="every M2C_ERROR function")
    ap.add_argument("--vu0-only", action="store_true", help="with --all: only functions containing VU0 instructions")
    ap.add_argument("--classify", action="store_true", help="print instruction kinds found in M2C_ERROR functions")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--out", default=str(ROOT / "scratch/vu0/src"))
    ap.add_argument("--ok", default=str(ROOT / "scratch/vu0/ok.txt"))
    args = ap.parse_args()

    rows = load_sweep_status()
    if args.classify:
        target = [r for r in rows if "M2C_ERROR" in r["status"]]
        cats, _ = classify(target)
        print(f"{len(target)} M2C_ERROR functions; functions containing each kind:")
        for k, v in sorted(cats.items(), key=lambda kv: -kv[1]):
            print(f"  {k}: {v}")
        return 0

    if args.all:
        sel = [r for r in rows if "M2C_ERROR" in r["status"]]
    else:
        want = {int(a, 16) for a in args.addr}
        sel = [r for r in rows if int(r["addr"], 16) in want]
        missing = want - {int(r["addr"], 16) for r in sel}
        if missing:
            print("not in status.csv:", ", ".join(f"0x{m:08X}" for m in sorted(missing)), file=sys.stderr)
    if args.vu0_only:
        _, per = classify(sel)
        sel = [r for r in sel if any(k.startswith("VU0") or k in VU0_KINDS for k in per[r["addr"]])]
    if not sel:
        print("nothing to do", file=sys.stderr)
        return 1

    out_dir = Path(args.out).resolve()
    out_dir.mkdir(parents=True, exist_ok=True)
    known = known_symbols()
    jobs = max(1, min(args.jobs, 4))
    with ThreadPoolExecutor(max_workers=jobs) as ex:
        results = list(ex.map(lambda r: run_one(r, out_dir, known), sel))

    ok_rows = []
    for row, ok, msg, name in results:
        status = "OK" if ok else "FAIL"
        print(f"{row['addr']} {row['name']}: {status}" + ("" if ok else f" ({msg.splitlines()[-1] if msg else ''})"))
        if ok:
            start = int(row["addr"], 16)
            size = int(row["size"], 16)
            ok_rows.append((start, start + size, "vu0_" + f"{start:08x}"[-6:]))
    ok_path = Path(args.ok).resolve()
    ok_path.parent.mkdir(parents=True, exist_ok=True)
    # Merge with previous OK entries so that separate runs add up.
    prev = {}
    if ok_path.exists():
        for line in ok_path.read_text().splitlines():
            p = line.split()
            if len(p) == 3:
                prev[p[2]] = line
    for s, e, tag in ok_rows:
        prev[tag] = f"0x{s:08X} 0x{e:08X} {tag}"
    ok_path.write_text("\n".join(sorted(prev.values())) + "\n")
    total = sum(e - s for s, e, _ in ok_rows)
    print(f"OK this run: {len(ok_rows)} functions, {total} bytes; total in {ok_path}: {len(prev)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
