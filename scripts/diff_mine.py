#!/usr/bin/env python3
"""Classifies the instruction differences of m2c near misses, and tries mechanical source rewrites on them.

Usage:
  .venv/bin/python scripts/diff_mine.py classify [--n 300] [--seed 1] [--jobs 3] [--max-n 6]
      samples scratch/diffmine_pool.csv (status "differs k/m", k <= --max-n) from scratch/m2c_sweep, runs
      scripts/fdiff.py on each draft, classifies the differing instructions and writes
      scratch/diffmine/classified.jsonl and scratch/diffmine/tally.txt.
  .venv/bin/python scripts/diff_mine.py rewrite [--jobs 3] --rule NAME [...]
      applies each rewrite rule to the drafts of the sample, re-checks with fdiff and counts the ones that become OK
      (scratch/diffmine/rewrite_<rule>.csv). Only a draft that becomes OK is kept (written to *_rw.c).

fdiff prints the ORIGINAL on the left and MINE on the right, index-aligned; "!" marks a positional mismatch.
Categories (per function, from an opcode alignment of the two listings):
  reg        same mnemonic and immediates, other registers
  imm:gp / imm:sp / imm:other   same mnemonic and registers, another offset/immediate
  width      load/store of another width at the same operands
  branch     another branch kind (beq/bne/beqz/bnel...)
  mnem       other mnemonic pair
  extra:X / missing:X   instruction mine has more / less (X = its mnemonic)
  order      same multiset of instructions, different sequence
"""

import argparse
import csv
import difflib
import json
import random
import re
import subprocess
import sys
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SWEEP = ROOT / "scratch/m2c_sweep"
WORK = ROOT / "scratch/diffmine"
LINE = re.compile(r"^  ([! ]) +([0-9a-f]+)  (.*)$")
LOADS = {"lb", "lbu", "lh", "lhu", "lw", "lwu", "ld", "lwc1", "lq"}
STORES = {"sb", "sh", "sw", "sd", "swc1", "sq"}
BRANCH = re.compile(r"^(b|j)")


def parse(out):
    """(orig, mine, marked) of one function's fdiff listing; marked = indices fdiff flags with '!'."""
    orig, mine, marked = [], [], set()
    for line in out.splitlines():
        m = LINE.match(line)
        if not m:
            continue
        rest = m.group(3)
        if " | " not in rest:
            continue
        left, right = rest.split(" | ", 1)
        if m.group(1) == "!":
            marked.add(len(orig))
        orig.append(left.strip())
        mine.append(right.strip())
    return orig, mine, marked


def split_ins(text):
    if not text:
        return "", []
    p = text.split(None, 1)
    ops = [] if len(p) == 1 else [t for t in re.split(r",\s*", p[1]) if t]
    return p[0], ops


def is_branch(mn):
    return mn.startswith("b") or mn in ("j", "jal", "beqz", "bnez")


def key(text, regs=True):
    mn, ops = split_ins(text)
    if is_branch(mn) and ops:
        ops = ops[:-1]  # the target
    if mn == "jal":
        ops = []
    if not regs:
        ops = [re.sub(r"\$?\b[a-z]\w*\b|\(\w+\)", lambda m: "R" if m.group(0) and re.search(r"[a-z]", m.group(0)) and not m.group(0).lstrip("-").isdigit() else m.group(0), o) for o in ops]
    return mn, tuple(ops)


def imm_of(o):
    m = re.match(r"^(-?(?:0x)?[0-9a-fA-F]+)\(([\w$]+)\)$", o)
    if m:
        return m.group(1), m.group(2)
    return None


def masked(o, m):
    """fdiff masks relocated fields: mine shows 0 where the original has the %gp_rel / %hi / %lo value."""
    mo, oo = split_ins(o)
    mm, om = split_ins(m)
    if mo != mm or not oo or not om:
        return False
    if mo in ("lui", "addiu", "ori") and om[-1] in ("0", "0x0") and oo[-1] not in ("0", "0x0"):
        return True  # %hi / %lo field, masked by fdiff
    if imm_of(oo[-1]) and imm_of(om[-1]) and imm_of(om[-1])[1] == "gp" and om[-1].split("(")[0] in ("0", "0x0"):
        return True
    return False


def pair_class(o, m):
    mo, oo = split_ins(o)
    mm, om = split_ins(m)
    if not mo or not mm:
        return "other"
    if masked(o, m):
        return "reloc"
    if mo == mm and is_branch(mo):
        if oo[:-1] == om[:-1] or [x.split()[0] for x in oo] == [x.split()[0] for x in om]:
            return "branch-target"
        return "branch-regs"
    if mo == mm:
        if oo == om:
            return "same"
        if len(oo) == len(om) and oo[-1:] != om[-1:] and not any(imm_of(x) for x in oo + om):
            pass
        imm_o = [imm_of(x) for x in oo]
        imm_m = [imm_of(x) for x in om]
        if any(imm_o) and any(imm_m) and [x and x[1] for x in imm_o] == [x and x[1] for x in imm_m]:
            base = imm_o[[i for i, x in enumerate(imm_o) if x][0]][1]
            return f"imm:{'gp' if base == 'gp' else 'sp' if base == 'sp' else 'other'}"
        strip = lambda ops: [re.sub(r"\$?[a-z]\w*|\(\w+\)", "R", x) for x in ops]
        if strip(oo) == strip(om):
            return "reg"
        if any(re.search(r"\b0x|-?\d", x) for x in oo + om):
            return "imm:other"
        return "reg"
    if mo in LOADS | STORES and mm in LOADS | STORES:
        return "width"
    if is_branch(mo) and is_branch(mm):
        return "branch"
    return f"mnem:{mo}->{mm}"


def classify_fn(orig, mine, marked=None):
    if marked is not None and len(orig) == len(mine):
        # same length: fdiff's own '!' flags are the real differences (relocated fields are masked there)
        cats = [pair_class(orig[i], mine[i]) for i in sorted(marked)]
        cats = [c for c in cats if c not in ("same", "branch-target", "reloc")]
        return cats or ["none"]
    ko = [key(t) for t in orig]
    km = [key(t) for t in mine]
    if not orig and not mine:
        return []
    if sorted(map(str, ko)) == sorted(map(str, km)) and ko != km:
        return ["order"]
    if all(masked(o, m) for o, m in zip(orig, mine)) and len(orig) == len(mine):
        return ["none"]
    cats = []
    sm = difflib.SequenceMatcher(a=ko, b=km, autojunk=False)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            continue
        if tag == "replace" and (i2 - i1) == (j2 - j1):
            for o, m in zip(orig[i1:i2], mine[j1:j2]):
                c = pair_class(o, m)
                if c not in ("same", "branch-target", "reloc"):
                    cats.append(c)
        elif tag == "replace":
            cats.append("block")
        elif tag == "insert":
            for m in mine[j1:j2]:
                cats.append("extra:" + split_ins(m)[0])
        elif tag == "delete":
            for o in orig[i1:i2]:
                cats.append("missing:" + split_ins(o)[0])
    return cats or ["none"]


def fdiff_out(rel, name):
    r = subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), str(rel), name], cwd=ROOT,
                       capture_output=True, text=True)
    return r.stdout + r.stderr


def sample(n, seed, max_n):
    rows = list(csv.DictReader((SWEEP / "status.csv").read_text().splitlines()))
    pool = []
    for r in rows:
        m = re.match(r"differs (\d+)/(\d+)", r["status"])
        if m and 1 <= int(m.group(1)) <= max_n:
            pool.append(r)
    return random.Random(seed).sample(pool, min(n, len(pool)))


def draft_of(row):
    a6 = f"{int(row['addr'], 16):08X}"[-6:]
    return SWEEP / f"m2c_{a6}.c"


def classify_one(row):
    c = draft_of(row)
    out = fdiff_out(c.relative_to(ROOT), row["name"])
    orig, mine, marked = parse(out)
    cats = classify_fn(orig, mine, marked) if orig else ["no-listing"]
    return {"addr": row["addr"], "name": row["name"], "status": row["status"], "cats": cats}


def cmd_classify(a):
    WORK.mkdir(parents=True, exist_ok=True)
    rows = sample(a.n, a.seed, a.max_n)
    with ThreadPoolExecutor(max_workers=a.jobs) as ex:
        res = list(ex.map(classify_one, rows))
    with (WORK / "classified.jsonl").open("w") as f:
        for r in res:
            f.write(json.dumps(r) + "\n")
    tally = Counter()
    for r in res:
        for c in set(r["cats"]):
            tally[c] += 1
    lines = [f"sample {len(res)} drafts (differs <= {a.max_n}), seed {a.seed}; count = drafts with the category",
             *[f"{n:4d}  {c}" for c, n in tally.most_common()]]
    (WORK / "tally.txt").write_text("\n".join(lines) + "\n")
    print("\n".join(lines[:40]))


# ---- rewrites: each takes a draft's text and yields candidate texts, one edit each ----
TYPES = ["M2C_UNK", "s8", "u8", "s16", "u16", "s32", "u32", "f32", "s64", "u64"]
DECL = re.compile(r"^(    )((?:%s)) (\*?)(\w+)(;|\s*=.*;)$" % "|".join(TYPES))


def rw_retype(lines):
    """A local's type (and a pointer's element type, which sets its step) replaced by another width."""
    for i, ln in enumerate(lines):
        m = DECL.match(ln)
        if not m:
            continue
        for t in TYPES:
            if t != m.group(2):
                new = list(lines)
                new[i] = f"{m.group(1)}{t} {m.group(3)}{m.group(4)}{m.group(5)}"
                yield f"retype {m.group(4)} {m.group(2)}->{t}", new


def decl_block(lines):
    """(start, end) of the function's leading local declarations."""
    start = next((i for i, ln in enumerate(lines) if ln.endswith(") {") and not ln.startswith(" ")), None)
    if start is None:
        return None
    j = start + 1
    while j < len(lines) and DECL.match(lines[j]):
        j += 1
    return start + 1, j


def rw_decl_order(lines):
    """Register allocation follows declaration order in ee-gcc: reverse the locals, or swap neighbours."""
    blk = decl_block(lines)
    if not blk or blk[1] - blk[0] < 2:
        return
    a, b = blk
    yield "decl reverse", lines[:a] + lines[a:b][::-1] + lines[b:]
    for k in range(a, b - 1):
        new = list(lines)
        new[k], new[k + 1] = new[k + 1], new[k]
        yield f"decl swap {k - a}", new


STMT = re.compile(r"^    (?!\s*(?:if|else|do|while|return|goto|case|default|break|continue)\b)[^\s}][^{}]*;$")
DECLLIKE = re.compile(r"^    (?:%s) " % "|".join(TYPES))


def lhs_names(stmt):
    """Identifiers assigned by a statement (`x = ...`, `x += ...`), plus the names it reads."""
    m = re.match(r"^\s*(\S+?)\s*(?:[-+*/|&^]|<<|>>)?=\s", stmt)
    return set(re.findall(r"\w+", m.group(1))) if m else set(), set(re.findall(r"\w+", stmt))


def independent(a, b):
    """No name written by one statement is read or written by the other (a swap keeps the C meaning)."""
    wa, _ = lhs_names(a)
    wb, _ = lhs_names(b)
    ra = set(re.findall(r"\w+", a))
    rb = set(re.findall(r"\w+", b))
    return not (wa & rb) and not (wb & ra) and not (wa & wb)


def rw_stmt_swap(lines):
    """Two neighbouring independent statements in opposite order (m2c's order is one of several)."""
    n = 0
    for i in range(len(lines) - 1):
        a, b = lines[i], lines[i + 1]
        if STMT.match(a) and STMT.match(b) and not DECLLIKE.match(a) and not DECLLIKE.match(b) and independent(a, b):
            new = list(lines)
            new[i], new[i + 1] = b, a
            yield f"stmt swap {i}", new
            n += 1
            if n >= 40:
                return


CMP = re.compile(r"^(\s*(?:\}\s*else\s*)?if \()(\S+) (==|!=) (\S+)\) \{$")
FLIP = {"==": "==", "!=": "!="}


def rw_cmp_swap(lines):
    """`if (x == 0)` becomes `if (0 == x)`: the same test, with the operands in the other order for the compiler."""
    for i, ln in enumerate(lines):
        m = CMP.match(ln)
        if m and not m.group(4).startswith(("M2C_", "(")) and m.group(2).isidentifier() or (m and m.group(4)[:1].isdigit()):
            new = list(lines)
            new[i] = f"{m.group(1)}{m.group(4)} {m.group(3)} {m.group(2)}) {{"
            yield f"cmp swap {i}", new


RULES = {"retype": rw_retype, "decl-order": rw_decl_order, "stmt-swap": rw_stmt_swap, "cmp-swap": rw_cmp_swap}


def try_rule(row, rule):
    """First single-edit rewrite of this rule that makes the draft OK. Returns (desc, path) or None."""
    src = draft_of(row)
    lines = src.read_text().splitlines()
    a6 = src.stem
    out = WORK / "rw" / f"{a6}_{rule}.c"
    out.parent.mkdir(parents=True, exist_ok=True)
    tried = 0
    for desc, new in RULES[rule](lines):
        tried += 1
        out.write_text("\n".join(new) + "\n")
        text = fdiff_out(out.relative_to(ROOT), row["name"])
        if re.search(rf"^{re.escape(row['name'])}: OK", text, re.M):
            return desc, out, tried
    out.unlink(missing_ok=True)
    return None, None, tried


def cmd_rewrite(a):
    rows = sample(a.n, a.seed, a.max_n)
    rules = a.rule or list(RULES)
    lines_out = []
    for rule in rules:
        with ThreadPoolExecutor(max_workers=a.jobs) as ex:
            res = list(ex.map(lambda r: (r, *try_rule(r, rule)), rows))
        ok = [(r, d) for r, d, _, _ in res if d]
        tries = sum(t for _, _, _, t in res)
        lines_out.append(f"{rule}: OK {len(ok)} of {len(rows)} drafts (single edit; {tries} candidate checks)")
        with (WORK / f"rewrite_{rule}.csv").open("w") as f:
            f.write("addr,name,status,edit\n")
            for r, d, _, _ in res:
                f.write(f"{r['addr']},{r['name']},{r['status']},{d or ''}\n")
    print("\n".join(lines_out))


def c_files_ranges():
    """[start, end) of every range of config/c_files.txt: those functions are already in C."""
    rng = []
    for line in (ROOT / "config/c_files.txt").read_text().splitlines():
        p = line.split("#")[0].split()
        if len(p) >= 2:
            try:
                rng.append((int(p[0], 16), int(p[1], 16)))
            except ValueError:
                pass
    return rng


def sweep_targets(max_n):
    """status.csv rows `differs k/m`, 1 <= k <= max_n, outside every c_files range, with a draft and a size."""
    rng = c_files_ranges()
    out = []
    for r in csv.DictReader((SWEEP / "status.csv").read_text().splitlines()):
        m = re.match(r"differs (\d+)/(\d+)", r["status"])
        if not m or not (1 <= int(m.group(1)) <= max_n):
            continue
        a = int(r["addr"], 16)
        if any(s <= a < e for s, e in rng) or not draft_of(r).exists():
            continue
        out.append(r)
    return out


def check_text(lines, row, tmp):
    tmp.write_text("\n".join(lines) + "\n")
    text = fdiff_out(tmp.relative_to(ROOT), row["name"])
    return bool(re.search(rf"^{re.escape(row['name'])}: OK", text, re.M))


def sweep_one(row, cap=150):
    """Single edits (retype, then stmt-swap), then pairs (retype+stmt-swap in either order). First OK wins."""
    src = draft_of(row)
    base = src.read_text().splitlines()
    a6 = src.stem[-6:]
    tmp = WORK / "tmp" / f"{a6}.c"
    tmp.parent.mkdir(parents=True, exist_ok=True)
    checks, found = 0, None
    for rule in ("retype", "stmt-swap"):
        for desc, new in RULES[rule](base):
            checks += 1
            if check_text(new, row, tmp):
                found = [desc]; new_ok = new; break
        if found:
            break
    if not found:
        for first, second in (("retype", "stmt-swap"), ("stmt-swap", "retype")):
            for d1, l1 in RULES[first](base):
                if checks >= cap:
                    break
                for d2, l2 in RULES[second](l1):
                    checks += 1
                    if checks > cap:
                        break
                    if check_text(l2, row, tmp):
                        found = [d1, d2]; new_ok = l2; break
                if found:
                    break
            if found:
                break
    tmp.unlink(missing_ok=True)
    return {"addr": row["addr"], "name": row["name"], "status": row["status"], "edits": found,
            "checks": checks, "ok": found is not None, "text": "\n".join(new_ok) + "\n" if found else None}


def finish_ok(row, text):
    """Writes out/dm_<ADDR6>.c and runs scripts/data_split.py on it. Returns (passed, data lines, why)."""
    a6 = f"{int(row['addr'], 16):08X}"[-6:]
    out = WORK / "out" / f"dm_{a6}.c"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(text)
    start = int(row["addr"], 16)
    r = subprocess.run([sys.executable, str(ROOT / "scripts/data_split.py"), str(out.relative_to(ROOT)),
                        f"0x{start:08X}"], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        out.unlink(missing_ok=True)
        return False, [], (r.stdout + r.stderr).strip().splitlines()[-1:] or ["data_split failed"]
    return True, [ln for ln in r.stdout.splitlines() if ln.strip()], []


def cmd_sweep(a):
    rows = sweep_targets(a.max_n)
    WORK.mkdir(parents=True, exist_ok=True)
    jl = (WORK / "sweep.jsonl").open("w")
    ok_lines, data_lines, dropped = [], [], []
    with ThreadPoolExecutor(max_workers=a.jobs) as ex:
        for res in ex.map(sweep_one, rows):
            jl.write(json.dumps({k: v for k, v in res.items() if k != "text"}) + "\n")
            jl.flush()
            if not res["ok"]:
                continue
            passed, data, why = finish_ok(res, res["text"])
            if not passed:
                dropped.append((res["name"], why))
                continue
            start = int(res["addr"], 16)
            size = int(next(r["size"] for r in rows if r["addr"] == res["addr"]), 16)
            a6 = f"{start:08X}"[-6:]
            ok_lines.append(f"0x{start:08X} 0x{start + size:08X} dm_{a6}")
            data_lines += data
            (WORK / "ok.txt").write_text("\n".join(ok_lines) + "\n")
            (WORK / "data.txt").write_text("\n".join(data_lines) + ("\n" if data_lines else ""))
    jl.close()
    total = sum(int(ln.split()[1], 16) - int(ln.split()[0], 16) for ln in ok_lines)
    print(f"targets {len(rows)}; OK {sum(1 for _ in open(WORK / 'sweep.jsonl') if json.loads(_)['ok'])}; "
          f"passed data_split {len(ok_lines)}; dropped {len(dropped)}; bytes {total}")


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    c = sub.add_parser("classify")
    c.add_argument("--n", type=int, default=300)
    c.add_argument("--seed", type=int, default=1)
    c.add_argument("--jobs", type=int, default=3)
    c.add_argument("--max-n", type=int, default=6)
    r = sub.add_parser("rewrite")
    r.add_argument("--n", type=int, default=300)
    r.add_argument("--seed", type=int, default=1)
    r.add_argument("--jobs", type=int, default=3)
    r.add_argument("--max-n", type=int, default=6)
    r.add_argument("--rule", action="append", choices=list(RULES))
    w = sub.add_parser("sweep")
    w.add_argument("--max-n", type=int, default=8)
    w.add_argument("--jobs", type=int, default=2)
    a = ap.parse_args()
    if a.cmd == "classify":
        cmd_classify(a)
    elif a.cmd == "rewrite":
        cmd_rewrite(a)
    else:
        cmd_sweep(a)


if __name__ == "__main__":
    main()
