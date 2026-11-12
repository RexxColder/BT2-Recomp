#!/usr/bin/env python3
"""Turns shape-only pairs into matching C by fixing the immediates the BT3 C gets wrong for BT2.

Shape-only pair = a config/xmatch_bt3.csv exact row whose BT2 address is not in config/xmatch_bt3_strict.csv (the
instruction shape is the same, but some 16-bit immediates differ: struct offsets, constants). Only BT2 functions
outside every range of config/c_files.txt are tried.

Usage: scripts/xfer_shape.py [--limit N] [--only 0xADDR,...] [--measure] [--rounds 20] [--no-resume]

Per pair:
 1. transplant.build_file takes only the BT3 function (renamed to its BT2 name) -> scratch/shape/src/<dir>/<name>_<ADDR6>.c
 2. Compiled with -g (the stabs give each instruction its source line; codegen is the same, checked) and compared
    word by word with the BT2 original, relocations masked as fdiff does. A differing word is IMM when the opcode and
    registers agree and only the low 16 bits differ, else OTHER (SIZE when the function sizes differ: not tried).
 3. Rewrite rounds, for each IMM word and the source line it came from:
      load/store  `ident->a.b` (the whole chain)  ->  `(*(T *)((u8 *)ident + BT2OFF))`, T from the opcode
      addiu/slti  integer literal equal to the BT3 value -> the BT2 value (negated literal for a negated one)
      andi/ori    literal with the BT3 low 16 bits -> the BT2 value
    A rewrite is kept when the number of differing words drops and OTHER does not grow (recompile each trial).
 4. OK: the callee names are pointed at the BT2 addresses (scripts/fix_targets.py, reverted when it breaks the file),
    fdiff.py must print OK, and data_split.py must place the object's data (if any).

Output (appended as it goes): scratch/shape/ok.txt (`0xSTART 0xEND stem`), scratch/shape/data.txt
(`.sec 0xA 0xB stem`), scratch/shape/status.csv (addr,name,status), scratch/shape/measure.csv (--measure).
"""

import argparse
import contextlib
import csv
import io
import re
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT, BINUTILS, CC_FLAGS  # noqa: E402
import fdiff  # noqa: E402
import transplant  # noqa: E402
import data_split  # noqa: E402

OUT = ROOT / "scratch/shape"
SRC = OUT / "src"
EXACT = ROOT / "config/xmatch_bt3.csv"
STRICT = ROOT / "config/xmatch_bt3_strict.csv"
FUNCMAP = ROOT / "port/funcmap.csv"
REF = Path.home() / "Proyectos/BT3-Decompiled"
AUTO = re.compile(r"func_[0-9A-Fa-f]{8}")

LOADS = {32: "s8", 36: "u8", 33: "s16", 37: "u16", 35: "s32", 39: "u32", 55: "s64", 49: "f32", 53: "double",
         40: "s8", 41: "s16", 43: "s32", 63: "s64", 57: "f32", 61: "double"}
ADDIU_LIKE = {9, 10, 11}      # addiu slti sltiu: signed immediate
MASK_LIKE = {12, 13, 14}      # andi ori xori: unsigned immediate
CHAIN = re.compile(r"(?<![\w&.>])((?:[A-Za-z_]\w*\(\)|[A-Za-z_]\w*))((?:->|\.)[A-Za-z_]\w*(?:(?:->|\.)[A-Za-z_]\w*)*)"
                   r"(\[\d+\])?(?![\w\[(.>])")   # group 3: a constant array index, part of the offset
AMP = re.compile(r"(?<![\w&.>])&((?:[A-Za-z_]\w*\(\)|[A-Za-z_]\w*))((?:(?:->|\.)[A-Za-z_]\w*)+)(?![\w\[(.>])")
LITERAL = re.compile(r"(?<![\w.])(0[xX][0-9A-Fa-f]+|\d+)(?![\w.])")
UNDEF = re.compile(r"^\s*\d+:\s+\S+\s+\S+\s+\S+\s+UND\s+(\S+)", re.M)


def covered():
    out = []
    for line in (ROOT / "config/c_files.txt").read_text().splitlines():
        p = line.split()
        if len(p) >= 2 and p[0].startswith("0x"):
            out.append((int(p[0], 16), int(p[1], 16)))
    return out


def load_pairs(only=None):
    strict = {r["bt2_addr"] for r in csv.DictReader(open(STRICT))}
    cov = covered()
    ends = {int(r.split(",")[1], 16): int(r.split(",")[2], 16) for r in FUNCMAP.read_text().splitlines()[1:]}
    pairs = []
    for r in csv.DictReader(open(EXACT)):
        if r["kind"] != "exact" or not r["ref_src"] or r["bt2_addr"] in strict:
            continue
        a = int(r["bt2_addr"], 16)
        if only and a not in only:
            continue
        if any(s <= a < e for s, e in cov) or a not in ends:
            continue
        pairs.append({**r, "addr": a, "end": ends[a]})
    return pairs


def build_c(names, r):
    names[r["ref_name"]] = r["bt2_name"]
    text = transplant.build_file(REF, r["ref_src"], {r["ref_name"]}, names)
    path = SRC / Path(r["ref_src"]).parent.relative_to("src") / f"{Path(r['ref_src']).stem}_{r['addr']:06X}.c"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text)
    return path


def compile_obj(path, flags=None):
    """(obj, asm, stderr) compiled with fdiff's compiler; flags None = the project's flags."""
    err = io.StringIO()
    fdiff.FLAGS_OVERRIDE = flags
    try:
        with contextlib.redirect_stderr(err):
            obj = fdiff.compile_src(path.relative_to(ROOT), "default")
    finally:
        fdiff.FLAGS_OVERRIDE = None
    return obj, (obj.with_suffix(".s") if obj else None), err.getvalue()


def compile_g(path):
    return compile_obj(path, CC_FLAGS + " -g")


def diff_words(obj, name, addr, size):
    """(status, bad) with bad = [(index, mine, original)] and the function's .text offset."""
    funcs = fdiff.functions(obj)
    if name not in funcs:
        return "NOFUNC", []
    off, msize = funcs[name]
    orig = fdiff.original_words(addr, size)
    if msize != size:
        # The BT2 extent (port/funcmap.csv) runs to the next 8-byte aligned start: trailing nops are padding.
        if not (0 < size - msize <= 8 and msize < size and not any(orig[msize // 4:])):
            return "SIZE", []
        size = msize
        orig = orig[:size // 4]
    masks = fdiff.reloc_masks(obj)
    text = fdiff.text_bytes(obj)
    mine = struct.unpack_from(f"<{size // 4}I", text, off)
    bad = [(i, m, o) for i, (m, o) in enumerate(zip(mine, orig)) if (m ^ o) & ~masks.get(off + i * 4, 0) & 0xFFFFFFFF]
    return ("OK" if not bad else "DIFF"), bad


def is_imm(m, o):
    return m >> 26 == o >> 26 and ((m ^ o) & 0xFFFF0000) == 0


def classify(bad):
    imm = sum(1 for _, m, o in bad if is_imm(m, o))
    return imm, len(bad) - imm


def instr_lines(asm, name, obj):
    """Source line of each word of function `name`: the -g assembly's instructions matched against the object's
    disassembly (a symbol load or a big li is one assembler line but two words, lui + op, when the object shows
    the lui; .p2align padding is nops). None when they do not line up."""
    funcs = fdiff.functions(obj)
    off, size = funcs[name]
    words = fdiff.disasm(obj, off, size)
    lines, cur, on = [], None, False
    j, prev_branch = 0, False
    for raw in asm.read_text(errors="replace").splitlines():
        s = raw.strip()
        if not on:
            on = s == f"{name}:"
            continue
        if s.startswith(".end"):
            while j < len(words) and words[j] == "nop":   # the delay slot of the last jump
                lines.append(cur)
                j += 1
            break
        m = re.match(r"\.stabn 68,0,(\d+),", s)
        if m:
            cur = int(m.group(1))
            continue
        m = re.match(r"\.p2align (\d+)(?:,,(\d+))?", s)
        if m:
            a = 1 << int(m.group(1))
            pad = (-(off + 4 * len(lines))) % a
            if pad and (m.group(2) is None or pad <= int(m.group(2))):
                for _ in range(pad // 4):
                    if j >= len(words):
                        return None
                    lines.append(cur)
                    j += 1
            continue
        if not s or s.startswith(".") or s.startswith("$") or s.endswith(":") or s.startswith("#"):
            continue
        # Reorder mode: the assembler puts a nop in the delay slot of a branch or jump it could not fill.
        while j < len(words) and words[j] == "nop" and prev_branch and not s.startswith("nop"):
            lines.append(cur)
            j += 1
        n = 1
        if j < len(words) and words[j].startswith("lui") and (words_of(s) == 2):
            n = 2
        if j + n > len(words):
            return None
        lines.extend([cur] * n)
        j += n
        prev_branch = s[0] in "bj" or s.startswith("jal")
    return lines if j == len(words) == size // 4 else None


def words_of(s):
    """2 when the assembler line is a macro that may expand to lui + op (a load or store of a symbol, a li of a value
    that does not fit 16 bits), else 1."""
    op = s.split()[0]
    args = s[len(op):]
    if op in ("lw", "lh", "lhu", "lb", "lbu", "sw", "sh", "sb", "ld", "sd", "lwc1", "swc1", "ldc1", "sdc1",
              "l.s", "s.s", "l.d", "s.d", "li.s", "li.d", "la") and "(" not in args:
        return 2
    if op == "li":
        m = re.search(r",\s*(-?(?:0x[0-9a-fA-F]+|\d+))", args)
        if m and not -0x8000 <= int(m.group(1), 0) <= 0xFFFF:
            return 2
    return 1


def rewrite_candidates(line, m, o, op):
    """(new line text) candidates for one IMM word on a source line."""
    out = []
    if op in LOADS:
        t = LOADS[op]
        off = o & 0xFFFF
        off = off - 0x10000 if off & 0x8000 else off
        for c in CHAIN.finditer(line):
            if "->" not in c.group(2):
                continue
            rep = f"(*({t} *)((u8 *)({c.group(1)}) + ({off})))"
            out.append(line[:c.start()] + rep + line[c.end():])
    if op == 9:
        # `&ident->member`, or a member array decaying to its address: an addiu of the struct pointer.
        ov = o & 0xFFFF
        so = ov - 0x10000 if ov & 0x8000 else ov
        for c in list(AMP.finditer(line)) + [m for m in CHAIN.finditer(line) if not m.group(3)]:
            if "->" not in c.group(2):
                continue
            rep = f"((void *)((u8 *)({c.group(1)}) + ({so})))"
            out.append(line[:c.start()] + rep + line[c.end():])
    if op in LOADS:
        pass
    elif op in ADDIU_LIKE or op in MASK_LIKE:
        mv = m & 0xFFFF
        sm = mv - 0x10000 if mv & 0x8000 else mv
        ov = o & 0xFFFF
        so = ov - 0x10000 if ov & 0x8000 else ov
        for lit in LITERAL.finditer(line):
            txt = lit.group(1)
            v = int(txt, 0)
            if op in ADDIU_LIKE:
                if v == sm:
                    new = so
                elif v == -sm:
                    new = -so
                else:
                    continue
            else:
                if v & 0xFFFF != mv:
                    continue
                new = ov
            s = f"0x{new & 0xFFFFFFFF:X}" if txt[:2].lower() == "0x" else str(new)
            out.append(line[:lit.start()] + s + line[lit.end():])
    return out


def score(bad):
    imm, other = classify(bad)
    return len(bad), other


def fix_pair(path, name, addr, size, rounds=5, log=None):
    """Rewrites the file in place until fdiff says OK, no progress or `rounds`. Returns the final status."""
    text = path.read_text()
    best = None
    for rnd in range(rounds):
        obj, asm, err = compile_g(path)
        if obj is None:
            path.write_text(text)
            return "NOCOMPILE"
        st, bad = diff_words(obj, name, addr, size)
        if st != "OK" and best is None:
            pass
        if st in ("NOFUNC", "SIZE"):
            return st
        if st == "OK":
            return "OK"
        cur = score(bad)
        if best is None:
            best = cur
        lines = instr_lines(asm, name, obj)
        src = path.read_text().split("\n")
        progress = False
        for i, m, o in bad:
            if not is_imm(m, o) or lines is None:
                continue
            op = m >> 26
            ln = lines[i]
            if not ln or ln > len(src):
                continue
            cands = rewrite_candidates(src[ln - 1], m, o, op)
            for new_line in cands[:12]:
                trial = src[:]
                trial[ln - 1] = new_line
                path.write_text("\n".join(trial))
                o2, asm2, _ = compile_g(path)
                if o2 is None:
                    continue
                st2, bad2 = diff_words(o2, name, addr, size)
                if st2 == "OK":
                    return "OK"
                if score(bad2)[0] < cur[0] and score(bad2)[1] <= cur[1]:
                    src = trial
                    cur = score(bad2)
                    progress = True
                    if log:
                        log(f"  round {rnd}: line {ln} -> {new_line.strip()[:110]}  (diff {cur[0]})")
                    break
            else:
                continue
            # keep going on the other words of this round with the accepted text
            text_now = "\n".join(src)
            path.write_text(text_now)
            # the line map of this round is stale after an edit: recompile before the next word
            break
        if not progress:
            path.write_text("\n".join(src))
            break
        text = path.read_text()
    obj, _, _ = compile_obj(path)
    if obj is None:
        return "NOCOMPILE"
    st, bad = diff_words(obj, name, addr, size)
    return st if st != "DIFF" else "DIFF"


def callee_fix(path, addr):
    subprocess.run([sys.executable, str(ROOT / "scripts/fix_targets.py"), str(path.relative_to(ROOT)),
                    f"{addr:x}", "--write"], cwd=ROOT, capture_output=True)


def undefined_missing(obj):
    out = subprocess.run([str(ROOT / (BINUTILS + "readelf")), "-sW", str(obj)], capture_output=True, text=True).stdout
    known = fdiff.targets()
    miss = []
    for line in out.splitlines():
        p = line.split()
        if len(p) == 8 and p[6] == "UND" and p[7] and not p[7].startswith(".") and p[7] not in known \
                and not re.fullmatch(r"D_[0-9A-F]{8}", p[7]):   # splat's address labels name themselves
            miss.append(p[7])
    return miss


def final_check(path, name):
    r = subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), str(path.relative_to(ROOT)), name],
                       cwd=ROOT, capture_output=True, text=True)
    return r.returncode == 0 and any(l.startswith(f"{name}: OK") for l in r.stdout.splitlines())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--only")
    ap.add_argument("--measure", action="store_true")
    ap.add_argument("--rounds", type=int, default=20)
    ap.add_argument("--no-resume", action="store_true")
    a = ap.parse_args()
    OUT.mkdir(parents=True, exist_ok=True)
    only = {int(x, 16) for x in a.only.split(",")} if a.only else None
    pairs = load_pairs(only)
    if a.limit:
        pairs = pairs[:a.limit]
    names = transplant.load_names(EXACT)
    status_path = OUT / "status.csv"
    done = set()
    if status_path.exists() and not a.no_resume and not a.measure:
        done = {r["addr"] for r in csv.DictReader(open(status_path))}
    else:
        if not a.measure:
            status_path.write_text("addr,name,status\n")
    print(f"{len(pairs)} shape-only pairs outside c_files.txt", flush=True)

    if a.measure:
        mf = open(OUT / "measure.csv", "w")
        mf.write("addr,name,status,imm,other,kinds\n")
    for r in pairs:
        addr_s = f"0x{r['addr']:08X}"
        name = r["bt2_name"]
        if addr_s in done:
            continue
        path = build_c(names, r)
        obj, asm, err = compile_obj(path)
        if obj is None:
            st, imm, other, kinds = "NOCOMPILE", 0, 0, ""
            if err.strip():
                kinds = err.strip().splitlines()[-1][:120].replace(",", ";")
        else:
            st, bad = diff_words(obj, name, r["addr"], r["end"] - r["addr"])
            imm, other = classify(bad)
            kinds = ";".join(f"{m >> 26}:{m & 0xFFFF}->{o & 0xFFFF}" for _, m, o in bad[:4] if is_imm(m, o))
        if a.measure:
            mf.write(f"{addr_s},{name},{st},{imm},{other},{kinds}\n")
            mf.flush()
            print(f"{addr_s} {name}: {st} imm={imm} other={other} {kinds}", flush=True)
            continue
        if st in ("OK", "DIFF"):
            st = fix_pair(path, name, r["addr"], r["end"] - r["addr"], a.rounds, log=None)
        if st == "OK":
            callee_fix(path, r["addr"])
            obj, _, _ = compile_obj(path)
            if obj is None or not final_check(path, name):
                st = "FINAL_FAIL"
        if st == "OK":
            miss = undefined_missing(obj)
            if miss:
                st = "NONAME"
        if st == "OK":
            secs = data_split.place(obj, r["addr"])
            lines, why = secs
            if why:
                st = "DATA"
            elif lines:
                stem = str(path.with_suffix("").relative_to(SRC))
                with open(OUT / "data.txt", "a") as f:
                    for sec, x, y in lines:
                        f.write(f"{sec} 0x{x:08X} 0x{y:08X} {stem}\n")
        if st == "OK":
            stem = str(path.with_suffix("").relative_to(SRC))
            with open(OUT / "ok.txt", "a") as f:
                f.write(f"0x{r['addr']:08X} 0x{r['end']:08X} {stem}\n")
        with open(status_path, "a") as f:
            f.write(f"{addr_s},{name},{st}\n")
        print(f"{addr_s} {name}: {st}", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
