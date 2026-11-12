#!/usr/bin/env python3
"""Rewrites a function's sweep assembly so m2c can decompile it, then checks the C with fdiff.

  scripts/m2c_prefix.py --addr 0x00101608 [--addr ...]      one or more functions
  scripts/m2c_prefix.py --all [--jobs 4]                     every M2C_ERROR function of scratch/m2c_sweep/status.csv

Two rewrites before m2c (scratch/m2c_sweep/<ADDR8>.s is the input, unchanged):
 1. `.word 0x..  # mnemonic operands` lines (instructions the sweep could not disassemble) become `mnemonic operands`,
    taken from the comment, so m2c sees the instruction it was meant to see.
 2. Instructions that read and write no general register but that m2c does not know become a placeholder
    `jal __m2c_mark_N` + `nop`: sync, sync.p, syscall, break, and the COP2 macro ops (CO bit set, VF/ACC only).
    m2c emits the placeholder as a call statement; afterwards it is replaced by
    `__asm__ volatile(".word 0x........" ::: "memory");`, which assembles to the original word.
    Loads, stores through a base register, COP0 and the GPR-moving COP2 ops (qmfc2, cfc2, ...) are not marked.

After m2c: M2C_ macros other than the sweep's allowed set reject the try; m2c_fixsp declares an undeclared `sp`;
the result is checked with scripts/fdiff.py. Options (the same five as m2c_sweep) are tried in turn.

Output: scratch/vu0/c/m2cx_<ADDR6>.c (the draft, kept whether or not it matches), scratch/vu0/c/c_status.csv
(addr,name,status), and scratch/vu0/ok_c.txt (`0xSTART 0xEND m2cx_<ADDR6>`, matches only).
Prefixed .s files go to scratch/vu0/c/pre/.
"""

import argparse
import csv
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import m2c_fixsp  # noqa: E402

SWEEP = ROOT / "scratch/m2c_sweep"
OUT = ROOT / "scratch/vu0/c"
PRE = OUT / "pre"
ALLOWED = {"M2C_FIELD", "M2C_UNK", "M2C_UNK8", "M2C_UNK16", "M2C_UNK32", "M2C_UNK64", "M2C_BITWISE"}
VARIANTS = [[], ["--reg-vars", "saved"], ["--descending-regs"], ["--no-andor"],
            ["--reg-vars", "saved", "--descending-regs"]]
BIG = 1 << 30

INS_RE = re.compile(r"^\s*/\* ([0-9A-Fa-f]+) ([0-9A-Fa-f]{8}) ([0-9A-Fa-f]{8}) \*/\s?(.*)$")
WORD_CMT_RE = re.compile(r"\.word\s+0x[0-9A-Fa-f]+\s+#\s*([^#<]+?)\s*(?:#|<|$)")
MARK_RE = re.compile(r"__m2c_mark_(\d+)\b")


def strip_comments(text):
    return re.sub(r"\s*/\*.*?\*/\s*$", "", text).strip()


def is_marker(word, mnem):
    if mnem in ("sync", "sync.p", "syscall", "break"):
        return True
    return word >> 26 == 0x12 and (word >> 21) & 16 != 0      # COP2 macro op (CO set)


def function_lines(s_text):
    """The glabel..endlabel part of a sweep .s, plus its glabel name."""
    keep, name, on = [], None, False
    for ln in s_text.splitlines():
        if ln.startswith("glabel ") and name is None:
            name, on = ln.split()[1], True
        if on:
            keep.append(ln)
        if ln.startswith("endlabel"):
            break
    return name, keep


def prefix(lines, name=None):
    """Returns (rewritten lines, {marker number: original word})."""
    out, markers = [], {}
    # m2c cannot branch to the function's own glabel: such a branch goes to a local label on the first line.
    self_lbl = None
    if name and any(re.search(rf"\b(b\w*|j)\s.*\b{re.escape(name)}\b", ln) for ln in lines):
        self_lbl = f".L{name.lower().replace('func_', '')}"
    for ln in lines:
        if self_lbl and ln.startswith("glabel "):
            out.append(ln)
            out.append(f"{self_lbl}:")
            continue
        if self_lbl and not INS_RE.match(ln):
            out.append(ln)
            continue
        m = INS_RE.match(ln)
        if not m:
            out.append(ln)
            continue
        if self_lbl:
            ln = re.sub(rf"\b{re.escape(name)}\b", self_lbl, ln)
            m = INS_RE.match(ln)
        word = int.from_bytes(bytes.fromhex(m.group(3)), "little")
        text = strip_comments(m.group(4))
        if text.startswith(".word"):
            c = WORD_CMT_RE.search(text)
            out.append(f"    {c.group(1).strip()}" if c else ln)
            continue
        mnem = text.split()[0] if text else ""
        if mnem and is_marker(word, mnem):
            n = len(markers)
            markers[n] = word
            out.append(f"    jal __m2c_mark_{n}")
            out.append("    nop")
            continue
        out.append(ln)
    return out, markers


# Unaligned pairs: (first mnemonic, second mnemonic, offset of the first line relative to the second, replacement
# mnemonic, size in bytes). ldl/ldr and sdl/sdr are doublewords; lwl/lwr and swl/swr words.
PAIRS = {"ldl": ("ldr", 7, "ld", 8), "sdl": ("sdr", 7, "sd", 8), "lwl": ("lwr", 3, "lw", 4), "swl": ("swr", 3, "sw", 4)}
OPND_RE = re.compile(r"^(\$\w+),\s*(-?(?:0x[0-9A-Fa-f]+|\d+))\((\$\w+)\)$")


def plain_insn(ln):
    """(mnemonic, operands) of one assembly line, sweep format or plain, or None for a non-instruction."""
    m = INS_RE.match(ln)
    text = strip_comments(m.group(4)) if m else ln.strip()
    if not text or text.startswith((".", "/*", "nop")) and not text.startswith(".word"):
        return None
    mn, _, ops = text.partition(" ")
    return mn, ops.strip()


def group_rewrite(lines):
    """Unaligned pairs on the same register and base (offsets OFF+k and OFF) become one aligned load or store at OFF,
    the first line a nop. The second line may be a branch delay slot.
    Returns (lines, {size: set of offsets}) for the groups found."""
    out, groups, used = list(lines), {}, set()
    for i in range(len(lines)):
        p = plain_insn(lines[i])
        if i in used or p is None or p[0] not in PAIRS:
            continue
        mo = OPND_RE.match(p[1])
        if not mo:
            continue
        second, k, repl, size = PAIRS[p[0]]
        reg, off, base = mo.group(1), int(mo.group(2), 0), mo.group(3)
        for j in (i + 1, i + 2):
            if j >= len(lines) or j in used:
                continue
            q = plain_insn(lines[j])
            if q is None or q[0] != second:
                continue
            mo2 = OPND_RE.match(q[1])
            if mo2 and mo2.group(1) == reg and mo2.group(3) == base and int(mo2.group(2), 0) == off - k:
                out[i] = "    nop"
                out[j] = f"    {repl} {reg}, {off - k}({base})"
                used |= {i, j}
                groups.setdefault(size, set()).add(off - k)
                break
    return out, groups


def retype(text, groups):
    """Types the accesses of the unaligned groups as the struct they copy: every s64 becomes U8x8 (casts dropped),
    and the word copies at the offsets of lwl/lwr groups become U8x4 copies."""
    if 8 in groups:
        text = re.sub(r"\(s64\)\s*(?=M2C_FIELD)", "", text)
        text = re.sub(r"\bs64\b", "U8x8", text)
    if 4 in groups:
        offs = "|".join(str(o) for o in groups[4]) or "x"
        text = re.sub(rf"M2C_FIELD\((\w+), s32 \*, ({offs})\) = \(s32\) M2C_FIELD\((\w+), s32 \*, (\d+)\);",
                      lambda m: f"M2C_FIELD({m.group(1)}, U8x4 *, {m.group(2)}) = M2C_FIELD({m.group(3)}, U8x4 *, {m.group(4)});",
                      text)
    return text


COPY_T_RE = re.compile(r"^(\s*)M2C_FIELD\((\w+), U8x(\d+) \*, (-?\w+)\) = M2C_FIELD\((\w+), U8x\d+ \*, (-?\w+)\);$")


def merge_copies(text):
    """Two struct copies at stride, the second starting where the first ends (8+8 or 8+4), are one copy of the sum:
    the original loads every half before it stores, which only a single struct copy gives."""
    lines, out, i = text.split("\n"), [], 0
    while i < len(lines):
        m = COPY_T_RE.match(lines[i])
        m2 = COPY_T_RE.match(lines[i + 1]) if i + 1 < len(lines) else None
        if m and m2:
            ind, d, n1, o, src, q = m.groups()
            _, d2, n2, o2, src2, q2 = m2.groups()
            n1, n2, o, o2, q, q2 = int(n1), int(n2), int(o, 0), int(o2, 0), int(q, 0), int(q2, 0)
            total = n1 + n2
            if d == d2 and src == src2 and o2 == o + n1 and q2 == q + n1 and total in (12, 16):
                out.append(f"{ind}M2C_FIELD({d}, U8x{total} *, {o}) = M2C_FIELD({src}, U8x{total} *, {q});")
                i += 2
                continue
        out.append(lines[i])
        i += 1
    return "\n".join(out)


def typedefs(text):
    sizes = sorted({int(n) for n in re.findall(r"\bU8x(\d+)\b", text)})
    return "".join(f"typedef struct {{ u8 b[{n}]; }} U8x{n};\n" for n in sizes) + ("\n" if sizes else "")


def post(text, markers):
    for n, word in markers.items():
        text = re.sub(rf"^(\s*)__m2c_mark_{n}\(\);",
                      lambda m, w=word: f'{m.group(1)}__asm__ volatile(".word 0x{w:08X}" ::: "memory");',
                      text, flags=re.M)
    # Declarations of the placeholders m2c wrote for the calls.
    text = "\n".join(ln for ln in text.splitlines() if not MARK_RE.search(ln)) + "\n"
    return text


def fdiff(rel, name):
    r = subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), str(rel), name], cwd=ROOT,
                       capture_output=True, text=True)
    return r.stdout + r.stderr, bool(re.search(rf"^{re.escape(name)}: OK", r.stdout, re.M))


def attempt(name, s, c, opts, markers, asm_text, groups=None):
    r = subprocess.run([str(ROOT / ".venv/bin/python"), "-c", "import m2c.main as m; m.main()",
                        "--target", "mips-gcc-c", "--valid-syntax", *opts, "-f", name, str(s)],
                       capture_output=True, text=True, timeout=300)
    out = r.stdout
    if r.returncode or not out.strip():
        return "m2c failed", BIG
    macros = set(re.findall(r"\bM2C_\w+", out))
    if macros - ALLOWED:
        msg = re.search(r"M2C_ERROR\(/\* ([^*]*)", out)
        extra = f" ({msg.group(1).strip()})" if msg else ""
        return "m2c: " + ",".join(sorted(macros - ALLOWED)) + extra, BIG
    text = post(out, markers)
    if "__m2c_mark_" in text:
        return "marker left", BIG
    head = '#include "m2c_macros.h"\n\n'
    if groups:
        text = merge_copies(retype(text, groups))
        head += typedefs(text)
    c.write_text(head + text)
    rel = c.relative_to(ROOT)
    log, ok = fdiff(rel, name)
    if "could not compile" in log:
        fixed = m2c_fixsp.fix(c.read_text(), asm_text)
        if fixed:
            c.write_text(fixed)
            log, ok = fdiff(rel, name)
    if ok:
        return "OK", 0
    m = re.search(r"(\d+) of (\d+) instructions differ", log)
    if m:
        return f"differs {m.group(1)}/{m.group(2)}", int(m.group(1))
    return "compile", BIG - 1


def run_one(row):
    addr = int(row["addr"], 16)
    a6 = f"{addr:08X}"[-6:]
    s_path = SWEEP / f"{addr:08X}.s"
    name, lines = function_lines(s_path.read_text())
    if name is None:
        return row, "no glabel", None
    body = "\n".join(lines)
    if "jtbl" in body or re.search(r"\bjr\s+\$(?!ra)", body):
        return row, "jump table", None
    new_lines, markers = prefix(lines, name)
    new_lines, groups = group_rewrite(new_lines)
    PRE.mkdir(parents=True, exist_ok=True)
    s = PRE / f"{addr:08X}.s"
    s.write_text("\n".join(new_lines) + "\n")
    c = OUT / f"m2cx_{a6}.c"
    best = None
    for opts in VARIANTS:
        status, n = attempt(name, s, c, opts, markers, s.read_text(), groups=groups)
        if best is None or n < best[1]:
            best = (status, n, c.read_text() if c.exists() else "")
        if n == 0 or status.startswith(("m2c", "jump")):
            break
    status, n, text = best
    if text:
        c.write_text(text)
    return row, status, name


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--addr", action="append", default=[])
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--unal", action="store_true",
                    help="the functions blocked only by unaligned ops (ldl/ldr/sdl/sdr/lwl/lwr/swl/swr), smallest first")
    ap.add_argument("--first", type=int, default=0, help="with --unal: only the N smallest")
    args = ap.parse_args()
    with open(SWEEP / "status.csv") as f:
        rows = list(csv.DictReader(f))
    if args.all:
        sel = [r for r in rows if "M2C_ERROR" in r["status"]]
    elif args.unal:
        import json
        ids = json.loads((ROOT / "scratch/vu0/unal_sorted.json").read_text())
        byaddr = {r["addr"]: r for r in rows}
        sel = [byaddr["0x" + a] for a in ids]
        if args.first:
            sel = sel[: args.first]
    else:
        want = {int(a, 16) for a in args.addr}
        sel = [r for r in rows if int(r["addr"], 16) in want]
    if not sel:
        print("nothing to do", file=sys.stderr)
        return 1
    OUT.mkdir(parents=True, exist_ok=True)
    with ThreadPoolExecutor(max(1, min(args.jobs, 4))) as ex:
        results = list(ex.map(run_one, sel))

    # Status CSV: merged with earlier runs by address.
    status_path = OUT.parent / "c_status.csv"
    prev = {}
    if status_path.exists():
        for r in csv.DictReader(open(status_path)):
            prev[r["addr"]] = r
    ok_lines = {}
    if (OUT.parent / "ok_c.txt").exists():
        for ln in (OUT.parent / "ok_c.txt").read_text().splitlines():
            p = ln.split()
            if len(p) == 3:
                ok_lines[p[2]] = ln
    for row, status, name in results:
        name = name or row["name"]
        prev[row["addr"]] = {"addr": row["addr"], "name": name, "status": status}
        tag = "m2cx_" + f"{int(row['addr'], 16):08X}"[-6:]
        if status == "OK":
            start = int(row["addr"], 16)
            end = start + int(row["size"], 16)
            ok_lines[tag] = f"0x{start:08X} 0x{end:08X} {tag}"
        else:
            ok_lines.pop(tag, None)
        print(f"{row['addr']} {name}: {status}")
    with open(status_path, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=["addr", "name", "status"])
        w.writeheader()
        for k in sorted(prev):
            w.writerow(prev[k])
    (OUT.parent / "ok_c.txt").write_text("\n".join(sorted(ok_lines.values())) + ("\n" if ok_lines else ""))
    n_ok = sum(1 for r, s_, _ in results if s_ == "OK")
    print(f"OK this run: {n_ok}/{len(results)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
