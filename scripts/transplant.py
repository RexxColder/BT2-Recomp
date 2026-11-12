#!/usr/bin/env python3
"""Tries the reference decomp's C (BT3-Decompiled) for the BT2 functions xmatch.py paired with it.

Usage: scripts/transplant.py [--ref DIR] [--only src/sys/heap.c] [--jobs 6]

For every reference .c that holds a function xmatch.py found in BT2 (config/xmatch_bt3.csv), writes
scratch/xfer/<same path> = that file with
  - every function definition that is not a BT2 match reduced to its prototype (callers still see it),
  - the matched ones kept, renamed to their BT2 names,
  - reference auto names (func_/D_XXXXXXXX, which encode BT3 addresses) of known pairs renamed to BT2's,
and runs scripts/fdiff.py on it (relocations masked: the check does not need the data symbols yet).
Names: config/symbols/bt3_funcs.txt gets `bt3name = 0xBT2ADDR` for every exact pair whose BT2 function still has
an auto name, so fdiff and later splat know them.

Result: config/xfer_results.csv  bt2_addr,name,ref_src,status (OK | DIFF n/m | NOCOMPILE).
"""

import argparse
import csv
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402

AUTO = re.compile(r"\b(func|D)_([0-9A-F]{8})\b")
DEF = re.compile(r"^(?!\s)(?!typedef|struct|union|enum|extern|#)([A-Za-z_][\w \t\*]*?\b(\w+)\s*\(([^;{}]*)\))\s*\{",
                 re.M)


def split_functions(text):
    """[(name, sig_start, body_start, end)] of the top-level function definitions (brace matching)."""
    out = []
    for m in DEF.finditer(text):
        i, depth = m.end() - 1, 0
        while i < len(text):
            c = text[i]
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0:
                    break
            elif c == '"' or c == "'":
                j = i + 1
                while j < len(text) and text[j] != c:
                    j += 2 if text[j] == "\\" else 1
                i = j
            elif text.startswith("/*", i):
                i = text.find("*/", i) + 1
            elif text.startswith("//", i):
                i = text.find("\n", i)
            i += 1
        out.append((m.group(2), m.start(), m.start(1) + len(m.group(1)), i + 1))
    return out


class Names(dict):
    """reference name -> BT2 name, plus the reference->BT2 address map for auto names."""
    addr_map = {}


def load_names(csv_path, write=False):
    rows = list(csv.DictReader(open(csv_path)))
    pairs, seen = [], set()
    # Names BT2 already has (SDK signatures): a reference name used there for another address cannot move.
    taken = set()
    for path in (ROOT / "config/symbols").glob("*.txt"):
        if path.name.startswith("bt3_"):
            continue
        taken |= set(re.findall(r"^(\w+) = ", path.read_text(), re.M))
    for r in rows:
        if r["kind"] != "exact" or not r["ref_src"] or int(r["bt2_addr"], 16) >= 0x3B3100:
            continue
        # One name, one address: when BT2 has the same code twice, only the first copy takes the reference C.
        if r["ref_name"] in seen or (r["ref_name"] in taken and r["ref_name"] != r["bt2_name"]):
            continue
        seen.add(r["ref_name"])
        pairs.append(r)
    names, sym_lines = Names(), []
    names.addr_map = {int(r["ref_addr"], 16): int(r["bt2_addr"], 16) for r in rows if r["kind"] == "exact"}
    for r in pairs:
        ref, bt2 = r["ref_name"], r["bt2_name"]
        if AUTO.fullmatch(ref):
            names[ref] = f"func_{int(r['bt2_addr'], 16):08X}"
        elif AUTO.fullmatch(bt2) or bt2.startswith("game_"):
            names[ref] = ref
            sym_lines.append(f"{ref} = {r['bt2_addr']}; // type:func")
        else:
            names[ref] = bt2   # BT2 already has a name for it (SDK): keep ours
    names.pairs = pairs  # the first copies, the ones the names are for
    if write:
        (ROOT / "config/symbols/bt3_funcs.txt").write_text("\n".join(sorted(set(sym_lines))) + "\n")
        return names, pairs
    return names


def build_file(ref_root, src, wanted, names):
    """The reference file `src` with only the `wanted` functions defined (renamed), the rest as prototypes."""
    text = (ref_root / src).read_text(errors="replace")
    out, pos = [], 0
    for name, start, body, end in split_functions(text):
        out.append(text[pos:start])
        if name in wanted:
            out.append(re.sub(rf"\b{re.escape(name)}\b", names[name], text[start:end], count=1))
        else:
            out.append(text[start:body] + ";")
        pos = end
    out.append(text[pos:])
    # Top-level __asm__ blocks define functions too (BT3's VU0 helpers): keep a block only when the function it
    # defines is wanted, renamed; otherwise every piece of the file would define it again.
    def asm_block(m):
        g = re.search(r'\.globl (\w+)', m.group(0))
        if not g:
            return m.group(0)
        if g.group(1) not in wanted:
            return ""
        return re.sub(rf"\b{re.escape(g.group(1))}\b", names[g.group(1)], m.group(0))
    out = [re.sub(r'^__asm__\(\s*\n(?:\s*"[^\n]*\n)*?\s*\);', asm_block, "".join(out), flags=re.M)]
    # A macro that defines a function (BT3's STG_LIST_GETTER(Name, ...)): kept only where Name is wanted, like a
    # definition; data macros (LIT4_WORD, RODATA_ALIGN16) and ASM_STUB_* are left as they are.
    def macro_def(m):
        if m.group(1) in ("LIT4_WORD", "RODATA_ALIGN16", "ASM_STUB_BEGIN", "ASM_STUB_END") or \
                m.group(1).startswith("INCLUDE_"):
            return m.group(0)
        if m.group(2) not in wanted:
            return ""
        return m.group(0).replace(m.group(2), names[m.group(2)], 1)
    out = [re.sub(r"^([A-Z][A-Z0-9_]+)\((\w+)\b[^\n]*$", macro_def, out[0], flags=re.M)]
    # INCLUDE_ASM/INCLUDE_RODATA point at the reference's asm/ tree: drop them (prototypes stay).
    body = re.sub(r"^\s*INCLUDE_(ASM|RODATA)\([^)]*\);?[ \t]*$", "", "".join(out), flags=re.M)

    def sub(m):
        new = names.addr_map.get(int(m.group(2), 16))
        return f"{m.group(1)}_{new:08X}" if new is not None and m.group(1) == "func" else m.group(0)
    body = AUTO.sub(sub, body)
    for ref, new in names.items():
        if ref != new and not AUTO.fullmatch(ref):
            body = re.sub(rf"\b{re.escape(ref)}\b", new, body)
    return body


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--ref", type=Path, default=Path.home() / "Proyectos/BT3-Decompiled")
    ap.add_argument("--only")
    ap.add_argument("--jobs", type=int, default=6)
    ap.add_argument("--csv", type=Path, default=ROOT / "config/xmatch_bt3.csv")
    a = ap.parse_args()

    names, pairs = load_names(a.csv, write=True)
    by_src = {}
    for r in pairs:
        by_src.setdefault(r["ref_src"], []).append(r)
    if a.only:
        by_src = {k: v for k, v in by_src.items() if k == a.only}

    jobs = []
    for src, items in sorted(by_src.items()):
        trial = ROOT / "scratch/xfer" / src
        trial.parent.mkdir(parents=True, exist_ok=True)
        trial.write_text(build_file(a.ref, src, {r["ref_name"] for r in items}, names))
        jobs.append((trial, items))

    def run(job):
        trial, items = job
        p = subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), str(trial.relative_to(ROOT)),
                            *[names[r["ref_name"]] for r in items]],
                           cwd=ROOT, capture_output=True, text=True)
        status = {}
        for line in p.stdout.splitlines():
            m = re.match(r"(\w+): (OK|(\d+) of (\d+) instructions differ|no symbol)", line)
            if m:
                status[m.group(1)] = "OK" if m.group(2) == "OK" else \
                    ("NOSYM" if m.group(2) == "no symbol" else f"DIFF {m.group(3)}/{m.group(4)}")
        res = []
        for r in items:
            n = names[r["ref_name"]]
            res.append((r["bt2_addr"], n, r["ref_src"], status.get(n, "NOCOMPILE")))
        if not status:
            (trial.parent / (trial.name + ".err")).write_text(p.stdout + p.stderr)
        return res

    results = []
    with ThreadPoolExecutor(a.jobs) as pool:
        for res in pool.map(run, jobs):
            results.extend(res)
    out = ROOT / "config/xfer_results.csv"
    with open(out, "w") as f:
        f.write("bt2_addr,name,ref_src,status\n")
        for r in sorted(results):
            f.write(",".join(r) + "\n")
    count = lambda s: sum(1 for r in results if r[3].startswith(s))  # noqa: E731
    print(f"{len(jobs)} files, {len(results)} functions: OK {count('OK')}, DIFF {count('DIFF')}, "
          f"NOCOMPILE {count('NOCOMPILE')}, NOSYM {count('NOSYM')} -> {out.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
