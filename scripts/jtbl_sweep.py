#!/usr/bin/env python3
"""Decompiles the functions that m2c_sweep.py skipped for a jump table, with the table in m2c's input.

Usage: scripts/jtbl_sweep.py [--only 0x00103CB0,...] [--limit N] [--jobs 4]

The rows of scratch/m2c_sweep/status.csv marked `jump table` are the input. For each one:
 1. the `jtbl_XXXXXXXX` tables its `lw ..., %lo(jtbl_...)` reads are found in scratch/asm_snap/data/**/*.s (the
    `.word` entries of each dlabel..enddlabel block up to the last `.L` label); the labels must be in the text;
 2. scratch/jtbl/asm/<ADDR8>.s holds the function (`jlabel .L...` written as `.L...:`) and a .rodata section with
    the tables, so m2c rebuilds the `switch`;
 3. m2c_sweep.py's option variants (its attempt(): the m2c call, callee-arity relaxation, scripts/m2c_fixsp.py)
    and its pointer-step fix are used; the C is scratch/jtbl/src/jt_<ADDR6>.c and must match with fdiff.py;
 4. scripts/data_split.py must place the C's own .rodata (the table) at the original, else `data_split failed`.
A pass is written at once to scratch/jtbl/ok.txt (`0xSTART 0xEND jt_<ADDR6>`) and its data_split lines to
scratch/jtbl/data.txt. Every function gets a row in scratch/jtbl/status.csv (addr,name,status).
Nothing outside scratch/jtbl/ is written; m2c_sweep.py and the other scripts are only imported.
"""

import argparse
import csv
import re
import subprocess
import sys
import threading
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402
import m2c_sweep as ms  # noqa: E402
import fdiff  # noqa: E402
import integrate_xfer  # noqa: E402

WORK = ROOT / "scratch" / "jtbl"
ASM_SNAP = ROOT / "scratch" / "asm_snap"
SWEEP_STATUS = ROOT / "scratch" / "m2c_sweep" / "status.csv"
TABLE_RE = re.compile(r"%lo\((jtbl_[0-9A-Fa-f]+)\)")
LOCK = threading.Lock()


def functions(path):
    """(name, address, size, head, lines) per function of a splat .s file (as m2c_sweep.functions)."""
    head, cur, size = [], None, 0
    for line in path.read_text().splitlines():
        if cur is None:
            if line.startswith("nonmatching "):
                p = line.split(",")
                size = int(p[1], 16) if len(p) > 1 else 0
            elif line.startswith("glabel "):
                cur = [line]
            elif not head or line.startswith((".include", ".set", ".section")):
                head.append(line)
            continue
        cur.append(line)
        if line.startswith("endlabel"):
            m = re.search(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ", cur[1]) if len(cur) > 1 else None
            if m and size:
                yield cur[0].split()[1], int(m.group(1), 16), size, head, cur
            cur = None


def index_tables():
    """jtbl name -> its entries (`.L...` labels, or other words) up to the last `.L` label."""
    tables = {}
    for path in sorted((ASM_SNAP / "data").rglob("*.s")):
        cur = None
        for line in path.read_text().splitlines():
            m = re.match(r"\s*dlabel (jtbl_\w+)", line)
            if m:
                cur = m.group(1)
                tables.setdefault(cur, [])
                continue
            if line.startswith("enddlabel"):
                cur = None
                continue
            m = re.search(r"\.word\s+(\S+)", line)
            if cur and m:
                tables[cur].append(m.group(1))
    out = {}
    for name, words in tables.items():
        n = max((i + 1 for i, w in enumerate(words) if w.startswith(".L")), default=0)
        out[name] = words[:n]
    return out


def sweep_jobs():
    """(addr, name) of every status.csv row that m2c_sweep skipped for a jump table."""
    with SWEEP_STATUS.open() as f:
        return [(int(r["addr"], 16), r["name"]) for r in csv.DictReader(f) if r["status"].startswith("jump table")]


def build_asm(head, lines, tables):
    """The .s for m2c: the function (jlabels as plain labels) and the rodata of its tables."""
    body = [re.sub(r"^\s*jlabel (\.L\w+)", r"\1:", l) for l in lines]
    rodata = ["", '.section .rodata, "a"', ".align 2"]
    for t, words in tables:
        rodata.append(f"{t}:")
        rodata += [f"    .word {w}" for w in words]
    return "\n".join([*head, "", *body, "", *rodata]) + "\n"


def insert_in_body(text, decl):
    """decl after the opening brace of the function (the first column-0 line ending in `) {`)."""
    m = re.search(r"^[^\s#][^;\n]*\)\s*\{\n", text, re.M)
    return text[:m.end()] + decl + text[m.end():] if m else text


def fix_all(text, asm, sub_f32):
    """Compile fixes for m2c's draft: f64 typedef, the `sp` stack buffer, undeclared spNN locals and
    subroutine_argN parameters (m2c's name for an argument register the signature does not list)."""
    out = text
    if re.search(r"\bf64\b", out) and "typedef double f64;" not in out:
        out = out.replace('#include "m2c_macros.h"\n', '#include "m2c_macros.h"\ntypedef double f64;\n', 1)
    # scripts/m2c_fixsp.py refuses when `sp` is only used (`x = sp;`); here only a real declaration counts.
    if re.search(r"\bsp\b", out) and not re.search(r"^\s+\w[\w ]*?\*?\s*\bsp\b(\[\w*\])?;", out, re.M):
        offs = [int(x, 16) for x in re.findall(r"^\s+[\w ]+?\*?\s*sp([0-9A-F]+)(?:\[\w+\])?;", out, re.M)]
        saves = [int(x, 16) for x in re.findall(
            r"\b(?:sd|sq|sw|swc1)\s+\$(?:s\d|ra|fp|f2\d|f3\d), (0x[0-9A-F]+)\(\$sp\)", asm)]
        n = max(1, min(offs + saves + [0x100]) // 4)
        out = insert_in_body(out, f"    s32 sp[{n}];\n")
    # m2c's unknown stack slots (unkspNN) are locals like spNN.
    used = set(re.findall(r"\b((?:unk)?sp[0-9A-F]+)\b", out))
    declared = set(re.findall(r"^\s+[\w ]+?\*?\s*\b((?:unk)?sp[0-9A-F]+)(?:\[\w+\])?;", out, re.M))
    if used - declared:
        out = insert_in_body(out, "".join(f"    s32 {x};\n" for x in sorted(used - declared)))
    args = sorted({int(x) for x in re.findall(r"\bsubroutine_arg(\d+)\b", out)})
    m = re.search(r"^([^\n;]*?\b\w+)\(([^)\n]*)\) \{$", out, re.M)
    if args and m:
        ps = [] if m.group(2).strip() in ("", "void") else [p.strip() for p in m.group(2).split(",")]
        names = [re.findall(r"\w+$", p)[0] if re.findall(r"\w+$", p) else "" for p in ps]
        # An argument register the signature already names: the same value under m2c's other name.
        for k in args:
            if f"arg{k}" in names:
                out = re.sub(rf"\bsubroutine_arg{k}\b", f"arg{k}", out)
        args = [k for k in args if f"arg{k}" not in names]
        if args:
            new = list(ps)
            for k in range(len(ps), max(args) + 1):
                new.append(f"{'f32' if sub_f32 else 's32'} subroutine_arg{k}" if k in args else f"s32 arg{k}")
            m = re.search(r"^([^\n;]*?\b\w+)\(([^)\n]*)\) \{$", out, re.M)
            out = out[:m.start(2)] + ", ".join(new) + out[m.end(2):]
    return out


def check(name, c):
    """(status, n_differing) of the C in c, as scripts/m2c_sweep.attempt reports it."""
    v = ms.fdiff_run(c.relative_to(ROOT), name)
    if re.search(rf"^{re.escape(name)}: OK", v.stdout, re.M):
        return "OK", 0
    m = re.search(r"(\d+) of (\d+) instructions differ", v.stdout)
    return (f"differs {m.group(1)}/{m.group(2)}", int(m.group(1))) if m else ("compile", 1 << 29)


def run_one(addr, name, size, head, lines, tables_index):
    """(status, ok_line or None, data_lines) for one function; the files are left in scratch/jtbl/."""
    body = "\n".join(lines)
    names = sorted(set(TABLE_RE.findall(body)))
    if not names:
        return "no jtbl reference", None, []
    missing = [t for t in names if t not in tables_index]
    if missing:
        return f"no table {missing[0]}", None, []
    tables = [(t, tables_index[t]) for t in names]
    text_labels = set(re.findall(r"\.L\w+", body))
    if any(w not in text_labels for _, ws in tables for w in ws):
        return "labels missing", None, []

    s = WORK / "asm" / f"{addr:08X}.s"
    c = WORK / "src" / f"jt_{addr:06X}.c"
    s.parent.mkdir(parents=True, exist_ok=True)
    c.parent.mkdir(parents=True, exist_ok=True)
    s.write_text(build_asm(head, lines, tables))

    best = None

    def consider(st, nn, txt, prefer=False):
        # prefer: a fixed draft replaces an equal one (when nothing compiles, the last fix attempt is kept).
        nonlocal best
        if best is None or nn < best[1] or (prefer and nn == best[1]):
            best = (st, nn, txt)

    asm_text = s.read_text()
    for opts in ms.VARIANTS:
        status, n = ms.attempt(name, s, c, opts)
        txt = c.read_text() if c.exists() else ""
        consider(status, n, txt)
        if n == 0 or status.startswith("m2c"):
            break
        if status == "compile" and txt:
            # The draft does not compile: apply the compile fixes (then re-check each one).
            for sub_f32 in ((False, True) if re.search(r"\bsubroutine_arg\d", txt) else (False,)):
                fixed = fix_all(txt, asm_text, sub_f32)
                if fixed == txt:
                    continue
                c.write_text(fixed)
                st2, n2 = check(name, c)
                consider(st2, n2, fixed, prefer=True)
                if n2 == 0:
                    break
            if best[1] == 0:
                break
    status, n, out = best
    if n and out:
        # m2c steps a typed pointer by bytes: in elements (as m2c_sweep.try_one).
        sizes = {"s8": 1, "u8": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "f32": 4, "s64": 8, "u64": 8,
                 "M2C_UNK": 4, "void *": 4}
        ptrs = {m.group(2): sizes[m.group(1)] for m in re.finditer(
            r"^\s+(s8|u8|s16|u16|s32|u32|f32|s64|u64|M2C_UNK|void \*) ?\*(\w+);$", out, re.M)}

        def step(m):
            k = int(m.group(3), 0)
            sz = ptrs.get(m.group(1), 1)
            return m.group(0) if sz == 1 or k % sz else f"{m.group(1)} {m.group(2)}= {k // sz};"
        fixed = re.sub(r"\b(\w+) ([+-])= (0x[0-9A-Fa-f]+|\d+);", step, out)
        if fixed != out:
            c.write_text(fixed)
            v = ms.fdiff_run(c.relative_to(ROOT), name)
            if re.search(rf"^{re.escape(name)}: OK", v.stdout, re.M):
                status, n, out = "OK", 0, fixed
    if out:
        c.write_text(out)
    if status != "OK":
        if "switch (" not in out:
            status = f"m2c no switch ({status})"
        return status, None, []

    rel = c.relative_to(ROOT)
    obj = fdiff.compile_src(rel, "default")
    sec = integrate_xfer.section_sizes(obj)
    if sec.get(".sbss_init", 0) or sec.get(".bss", 0) or sec.get(".sbss", 0):
        return "bss", None, []
    r = subprocess.run([sys.executable, str(ROOT / "scripts/data_split.py"), str(rel), f"0x{addr:08X}"],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        return "data_split failed", None, []
    data = [l for l in r.stdout.splitlines() if l.strip()]
    ok = f"0x{addr:08X} 0x{addr + size:08X} jt_{addr:06X}"
    return "OK", ok, data


def status_row(addr, name, status):
    """addr,name,status,diff: status without commas, diff = n/m of a `differs` result (else empty)."""
    m = re.search(r"differs (\d+/\d+)", status)
    return f"0x{addr:08X},{name},{status.replace(',', ';')},{m.group(1) if m else ''}"


def write_near():
    """scratch/jtbl/near.txt: the 40 `differs` drafts with the smallest n/m (m <= 200), closest first."""
    rows = []
    p = WORK / "status.csv"
    for line in (p.read_text().splitlines()[1:] if p.exists() else []):
        f = line.split(",")
        if len(f) < 4 or not f[3]:
            continue
        n, m = (int(x) for x in f[3].split("/"))
        if m <= 200:
            rows.append((n / m, n, f[0], f[1], f[3]))
    rows.sort()
    (WORK / "near.txt").write_text("".join(f"{a} {b} {d}\n" for _, _, a, b, d in rows[:40]))


def record(addr, name, status, ok_line, data_lines):
    """Writes one function's result to the scratch/jtbl files at once (under LOCK)."""
    with LOCK:
        WORK.mkdir(parents=True, exist_ok=True)
        tag = f"jt_{addr:06X}"
        rows = {}
        p = WORK / "status.csv"
        if p.exists():
            for line in p.read_text().splitlines()[1:]:
                if line.strip():
                    a = int(line.split(",")[0], 16)
                    # Rows from before the diff column: the status text is everything after the second comma.
                    rest = line.split(",", 2)[2]
                    st = rest.rsplit(",", 1)[0] if re.search(r",(\d+/\d+)?$", rest) else rest
                    rows[a] = status_row(a, line.split(",")[1], st)
        rows[addr] = status_row(addr, name, status)
        p.write_text("addr,name,status,diff\n" + "\n".join(rows[k] for k in sorted(rows)) + "\n")
        for fname, new in (("ok.txt", [ok_line] if ok_line else []), ("data.txt", data_lines)):
            p = WORK / fname
            keep = []
            if p.exists():
                keep = [l for l in p.read_text().splitlines() if l.strip() and not l.split()[-1].endswith(tag)]
            keep += new
            col = 0 if fname == "ok.txt" else 1
            keep.sort(key=lambda l: int(l.split()[col], 16))
            p.write_text("\n".join(keep) + ("\n" if keep else ""))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--only", help="comma-separated function addresses (0x...) to run")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--retry", help="comma-separated status prefixes of scratch/jtbl/status.csv to run again "
                                    "(e.g. 'compile,m2c no switch')")
    ap.add_argument("--near", action="store_true", help="only rewrite scratch/jtbl/near.txt")
    a = ap.parse_args()
    if a.near:
        write_near()
        return

    if a.retry:
        prefixes = tuple(p.strip() for p in a.retry.split(","))
        with (WORK / "status.csv").open() as f:
            jobs = [(int(r["addr"], 16), r["name"]) for r in csv.DictReader(f, restkey="x")
                    if r["status"].startswith(prefixes)]
    else:
        jobs = sweep_jobs()
    if a.only:
        want = {int(x, 16) for x in a.only.split(",")}
        jobs = [j for j in jobs if j[0] in want]
    if a.limit:
        jobs = jobs[: a.limit]
    wanted = {addr for addr, _ in jobs}

    found = {}
    for path in sorted((ASM_SNAP / "cod").glob("*.s")):
        for name, addr, size, head, lines in functions(path):
            if addr in wanted:
                found[addr] = (name, size, head, lines)
    tables_index = index_tables()
    print(f"{len(jobs)} functions to try, {len(tables_index)} jump tables indexed", flush=True)

    def job(item):
        addr, name = item
        if addr not in found:
            record(addr, name, "not in asm_snap", None, [])
            return addr, "not in asm_snap", None
        fname, size, head, lines = found[addr]
        status, ok_line, data = run_one(addr, fname, size, head, lines, tables_index)
        record(addr, fname, status, ok_line, data)
        return addr, status, size if ok_line else None

    oks, why = [], {}
    with ThreadPoolExecutor(a.jobs) as ex:
        for i, (addr, status, size) in enumerate(ex.map(job, jobs)):
            key = status.split(" (")[0].split(" 0x")[0].split(" jt_")[0]
            why[key] = why.get(key, 0) + 1
            if size is not None:
                oks.append(size)
            print(f"  {i + 1}/{len(jobs)} 0x{addr:08X}: {status}", flush=True)
    write_near()
    print(f"OK: {len(oks)} functions ({sum(oks):#x} bytes); {why}")


if __name__ == "__main__":
    main()
