#!/usr/bin/env python3
"""Static checker of call sites: compares each `jal`/`jalr`/tail `j` of the original MIPS asm with the
call in port/eq/<ADDR6>.c.  Catches the decompilation errors that crashed the game:
  ARITY_LESS     C passes fewer args than the asm fixes (delay-slot args included)
  ARGS_SWAPPED   same expressions (reg+offset / constants) at other positions
  CONST_MISMATCH asm sets a constant arg, the C passes another literal
  ARITY_LESS_CALLEE  C passes fewer args than the callee reads (callee asm), regs not set by caller asm
  ARITY_MORE     C passes more args than the asm fixes and the callee reads (low)
  RET_USED_BUT_VOID / RET_DISCARDED / RET64 / RET_PTR_AS_S32 / RET_F0  return value handling
  PROTO_ARITY / PROTO_RET  caller prototype disagrees with the callee's own port/eq definition
Usage: scripts/check_calls.py [--out FILE] [--jobs 4] [files...]   (default: all port/eq/*.c)
No heavy tools: pure python + multiprocessing (<=4).  Asm: scratch/m2c_sweep (main) and
~/Escritorio/BT2-overlay-work/scratch/m2c_sweep (overlay >= 0x3B3100).
"""
import os
import re
import sys
from collections import defaultdict, namedtuple
from multiprocessing import Pool
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
EQ = ROOT / "port" / "eq"
ASM_DIRS = [ROOT / "scratch" / "m2c_sweep",
            Path.home() / "Escritorio" / "BT2-overlay-work" / "scratch" / "m2c_sweep"]

INT_ARGS = {"a0": 0, "a1": 1, "a2": 2, "a3": 3, "t0": 4, "t1": 5, "t2": 6, "t3": 7}
FP_ARGS = {"f%d" % (12 + i): i for i in range(8)}
INT_ARG_NAMES = list(INT_ARGS)
FP_ARG_NAMES = list(FP_ARGS)
ALL_ARG = set(INT_ARGS) | set(FP_ARGS)
CALLER_SAVED = (set(INT_ARGS) | {"v0", "v1", "at", "t4", "t5", "t6", "t7", "t8", "t9"} |
                {"f%d" % i for i in range(0, 20)})

STORES = {"sw", "sb", "sh", "sd", "sq", "swc1", "swl", "swr", "sdl", "sdr", "sdc1", "sqc2", "swc2", "sc"}
LOADS = {"lw", "lb", "lbu", "lh", "lhu", "lwu", "ld", "lq", "lwl", "lwr", "ldl", "ldr", "lwc1", "ldc1",
         "lqc2", "lwc2"}
LOAD_RMW = {"lwl", "lwr", "ldl", "ldr"}
BRANCH_LIKELY = {"beql", "bnel", "blezl", "bgtzl", "bltzl", "bgezl", "bc1tl", "bc1fl", "bltzall", "bgezall"}
BRANCHES = {"beq", "bne", "blez", "bgtz", "bltz", "bgez", "beqz", "bnez", "b", "bc1t", "bc1f", "bal",
            "bgezal", "bltzal"} | BRANCH_LIKELY
NODEST2 = {"mult", "multu", "div", "divu", "mult1", "multu1", "div1", "divu1", "madd", "maddu", "madd1",
           "maddu1"}
NODEST = {"mthi", "mtlo", "mthi1", "mtlo1", "nop", "sync", "sync.p", "break", "syscall", "ei", "di", "cache",
          "pref", ".word", "ctc1", "c1", "tlbwi", "eret"}
READ0_ONLY = {"mtc2", "ctc2", "qmtc2", "mtc2.ni", "ctc2.ni", "qmtc2.ni", "mtsah", "mtsab"}
S64_OPS = {"sd", "dsll", "dsll32", "dsrl", "dsrl32", "dsra", "dsra32", "dsllv", "dsrlv", "dsrav", "dmult",
           "dmultu", "ddiv", "ddivu", "sq"}
NODEST_RE = re.compile(r"^(c\.\w+\.s|adda\.s|suba\.s|mula\.s|madda\.s|msuba\.s|v\w+)")

Ins = namedtuple("Ins", "pc word op ops")
INS_RE = re.compile(r"^\s*/\*\s*\S+\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/\s*(\S+)\s*(.*?)\s*$")
LABEL_RE = re.compile(r"^\s*(\.?L?[A-Za-z_0-9]+):\s*$")


# ---------------------------------------------------------------- symbols
def load_symbols():
    n2a = {}
    sd = ROOT / "config" / "symbols"
    rx = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)")
    for f in sorted(sd.glob("*.txt")):
        for line in open(f, errors="replace"):
            m = rx.match(line)
            if m:
                n2a[m.group(1)] = int(m.group(2), 16)
    return n2a


SYM = load_symbols()
A2N = {}
for _n, _a in SYM.items():
    A2N.setdefault(_a, _n)
BUILTIN_ALIAS = {"__builtin_memset": "memset", "__builtin_memcpy": "memcpy", "__builtin_memmove": "memmove",
                 "__builtin_strlen": "strlen"}


def name_to_addr(name):
    name = BUILTIN_ALIAS.get(name, name)
    m = re.fullmatch(r"func_([0-9A-Fa-f]{6,8})", name)
    if m:
        return int(m.group(1), 16)
    return SYM.get(name)


def addr_name(a):
    return A2N.get(a, "func_%08X" % a)


VARIADIC = re.compile(r"printf|scanf|sprintf|dprintf|DebugPrint|Printf", re.I)


# ---------------------------------------------------------------- asm
_asm_index = None


def asm_path(addr):
    global _asm_index
    if _asm_index is None:
        _asm_index = {}
        for d in ASM_DIRS:
            if d.is_dir():
                for fn in os.listdir(d):
                    if len(fn) == 10 and fn.endswith(".s"):
                        try:
                            _asm_index.setdefault(int(fn[:8], 16), d / fn)
                        except ValueError:
                            pass
    return _asm_index.get(addr)


def split_ops(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


_asm_cache = {}


def parse_asm(addr):
    if addr in _asm_cache:
        return _asm_cache[addr]
    p = asm_path(addr)
    res = None
    if p:
        ins, labels = [], {}
        for line in open(p, errors="replace"):
            m = INS_RE.match(line)
            if m:
                ops = split_ops(m.group(4).split("#")[0])
                ins.append(Ins(int(m.group(1), 16), int(m.group(2), 16), m.group(3), ops))
                continue
            m = LABEL_RE.match(line)
            if m and not line.strip().startswith("glabel"):
                labels[m.group(1)] = len(ins)
        res = (ins, labels)
    _asm_cache[addr] = res
    return res


def jtarget(x):
    w = int.from_bytes(x.word.to_bytes(4, "big"), "little")  # word text is little-endian bytes
    return ((w & 0x03FFFFFF) << 2) | ((x.pc + 4) & 0xF0000000)


def rname(tok):
    tok = tok.strip()
    return tok[1:] if tok.startswith("$") else None


MEM_RE = re.compile(r"^(.*)\(\s*\$(\w+)\s*\)$")


def decode(x):
    """returns (reads, writes, immval) for a non-control instruction"""
    op, ops = x.op, x.ops
    reads, writes = [], []

    def R(t):
        m = MEM_RE.match(t)
        if m:
            reads.append(m.group(2))
            return
        n = rname(t)
        if n and n != "zero":
            reads.append(n)

    def W(t):
        n = rname(t)
        if n and n != "zero":
            writes.append(n)

    if op in NODEST or not ops:
        for t in ops:
            R(t)
    elif op in STORES:
        R(ops[0])
        for t in ops[1:]:
            R(t)
    elif op in LOADS:
        W(ops[0])
        for t in ops[1:]:
            R(t)
    elif op in ("mtc1", "dmtc1"):
        R(ops[0])
        if len(ops) > 1:
            W(ops[1])
    elif op in READ0_ONLY or op.split(".")[0] in READ0_ONLY:
        R(ops[0])
    elif op in NODEST2 and len(ops) == 2:
        for t in ops:
            R(t)
    elif NODEST_RE.match(op) and not op.startswith(("vm", "vs", "va")) and op[0] == "c":
        for t in ops:
            R(t)
    elif op[0] == "v" and op not in ("vnop",):
        pass  # VU0 macro ops: no integer/fpr effects (vi regs not tracked)
    else:
        W(ops[0])
        if op in ("movz", "movn"):
            R(ops[0])
        for t in ops[1:]:
            R(t)
    return reads, writes


def parse_imm(t):
    t = t.strip()
    try:
        return int(t, 0)
    except ValueError:
        return None


def val_of(x, st, depth_cap=3):
    """symbolic value of the destination written by x (only simple forms), else None"""
    op, ops = x.op, x.ops
    def v(t):
        n = rname(t)
        if n == "zero":
            return ("c", 0)
        return st.vals.get(n, ("init", n))
    def dep(a):
        d = 0
        while isinstance(a, tuple) and a and a[0] in ("add", "ld"):
            d += 1
            a = a[1]
        return d
    if op in ("addiu", "daddiu") and len(ops) == 3:
        k = parse_imm(ops[2])
        if k is None:
            return None
        b = v(ops[1])
        if b == ("c", 0):
            return ("c", k & 0xFFFFFFFF)
        if b[0] == "c":
            return ("c", (b[1] + k) & 0xFFFFFFFF)
        r = ("add", b, k)
        return r if dep(r) <= depth_cap else None
    if op == "ori" and len(ops) == 3:
        k = parse_imm(ops[2])
        if k is None:
            return None
        b = v(ops[1])
        if b[0] == "c":
            return ("c", (b[1] | k) & 0xFFFFFFFF)
        return None
    if op == "lui" and len(ops) == 2:
        k = parse_imm(ops[1])
        return ("c", (k << 16) & 0xFFFFFFFF) if k is not None else None
    if op in ("addu", "daddu", "or") and len(ops) == 3:
        a, b = v(ops[1]), v(ops[2])
        if ops[2].strip() == "$zero":
            return a
        if ops[1].strip() == "$zero":
            return b
        return None
    if op in LOADS and op in ("lw", "ld", "lwu") and len(ops) == 2:
        m = MEM_RE.match(ops[1])
        if m:
            k = parse_imm(m.group(1) or "0")
            if k is not None:
                r = ("ld", v("$" + m.group(2)), k)
                return r if dep(r) <= depth_cap else None
    return None


class State:
    __slots__ = ("W", "M", "vals", "U", "Wm")

    def __init__(self, W, M, vals, U=None, Wm=None):
        self.W, self.M, self.vals = W, M, vals
        self.U = U if U is not None else set()
        self.Wm = Wm if Wm is not None else set()

    def copy(self):
        return State(set(self.W), set(self.M), dict(self.vals), set(self.U), set(self.Wm))


def merge(a, b):
    """returns merged state (new object) or a if unchanged"""
    if a is None:
        return b.copy(), True
    W = a.W | b.W
    M = a.M & b.M
    vals = {}
    for k in set(a.vals) | set(b.vals):
        va, vb = a.vals.get(k), b.vals.get(k)
        vals[k] = va if va == vb else ("u", 0)
    U = a.U | b.U
    Wm = a.Wm & b.Wm
    changed = (W != a.W) or (M != a.M) or (vals != a.vals) or (U != a.U) or (Wm != a.Wm)
    return State(W, M, vals, U, Wm), changed


Call = namedtuple("Call", "pc kind target W vals M idx U")


class FuncInfo:
    def __init__(self):
        self.calls = []
        self.exposed = set()
        self.ins = []
        self.labels = {}


def analyze(addr, depth=2):
    """dataflow over the asm of one function; returns FuncInfo or None"""
    key = (addr, depth)
    if key in _an_cache:
        return _an_cache[key]
    _an_cache[key] = None  # cycle guard
    pa = parse_asm(addr)
    if not pa:
        return None
    ins, labels = pa
    n = len(ins)
    fi = FuncInfo()
    fi.ins, fi.labels = ins, labels
    # leaders
    leaders = {0}
    for i, x in enumerate(ins):
        if x.op in BRANCHES or x.op in ("j", "jr"):
            if i + 2 < n:
                leaders.add(i + 2)
            if x.ops and x.ops[-1] in labels:
                leaders.add(labels[x.ops[-1]])
    for l in labels.values():
        if l < n:
            leaders.add(l)

    def callee_arity(t):
        if depth <= 0 or t is None:
            return (0, 0)
        sub = analyze(t, depth - 1)
        if not sub:
            return (0, 0)
        return arity_of(sub)

    def apply(x, st, rec):
        reads, writes = decode(x)
        if rec is not None:
            for r in reads:
                if r in ALL_ARG and r not in st.M:
                    rec.exposed.add(r)
        for r in reads:
            if r in st.W:
                st.U.add(r)
        v = None
        if writes:
            v = val_of(x, st)
        for w in writes:
            st.U.discard(w)
            if w in ALL_ARG:
                st.W.add(w)
                st.Wm.add(w)
                st.M.add(w)
            if v is not None and len(writes) == 1:
                st.vals[w] = v
            else:
                st.vals[w] = ("u", x.pc)

    def do_call(i, st, rec, kind, target):
        x = ins[i]
        if kind == "jalr" and x.ops:
            r = rname(x.ops[-1])
            if r in ALL_ARG and r not in st.M and rec is not None:
                rec.exposed.add(r)
        if i + 1 < n:
            apply(ins[i + 1], st, rec)
        if rec is not None:
            ci, cf = callee_arity(target) if kind == "tail" else (0, 0)
            for nm in INT_ARG_NAMES[:ci]:
                if nm not in st.M:
                    rec.exposed.add(nm)
            for nm in FP_ARG_NAMES[:cf]:
                if nm not in st.M:
                    rec.exposed.add(nm)
            rec.calls.append(Call(x.pc, kind, target, set(st.W), dict(st.vals), set(st.M), i, set(st.U) | (set(st.W) - st.Wm)))
        st.W = set()
        st.Wm = set()
        st.U = set()
        st.M |= ALL_ARG
        for r in CALLER_SAVED:
            st.vals.pop(r, None)
        st.vals["v0"] = ("ret", x.pc)

    def run(start, st, rec):
        i = start
        out = []
        while i < n:
            if i != start and i in leaders:
                out.append((i, st))
                return out
            x = ins[i]
            op = x.op
            if op == "jal":
                do_call(i, st, rec, "jal", jtarget(x))
                i += 2
                continue
            if op == "jalr":
                do_call(i, st, rec, "jalr", None)
                i += 2
                continue
            if op == "j":
                tgt = x.ops[0] if x.ops else ""
                if tgt in labels:
                    apply(ins[i + 1], st, rec) if i + 1 < n else None
                    out.append((labels[tgt], st))
                else:
                    do_call(i, st, rec, "tail", jtarget(x))
                return out
            if op == "jr":
                r = rname(x.ops[0]) if x.ops else None
                if rec is not None and r in ALL_ARG and r not in st.M:
                    rec.exposed.add(r)
                if i + 1 < n:
                    apply(ins[i + 1], st, rec)
                return out
            if op in BRANCHES:
                if rec is not None:
                    for t in x.ops[:-1]:
                        r = rname(t)
                        if r in ALL_ARG and r not in st.M:
                            rec.exposed.add(r)
                tgt = x.ops[-1] if x.ops else ""
                if op in BRANCH_LIKELY:
                    pre = st.copy()
                    if i + 1 < n:
                        apply(ins[i + 1], st, rec)
                    if tgt in labels:
                        out.append((labels[tgt], st))
                    if i + 2 < n:
                        out.append((i + 2, pre))
                else:
                    if i + 1 < n:
                        apply(ins[i + 1], st, rec)
                    if tgt in labels:
                        out.append((labels[tgt], st.copy()))
                    if op not in ("b",) and i + 2 < n:
                        out.append((i + 2, st))
                return out
            apply(x, st, rec)
            i += 1
        return out

    in_state = {}
    in_state[0] = State(set(), set(), {})
    work = [0]
    # orphan seeds (jump-table targets): leaders that are labels never targeted by a branch/j/fallthrough
    targeted = set()
    for i, x in enumerate(ins):
        if (x.op in BRANCHES or x.op == "j") and x.ops and x.ops[-1] in labels:
            targeted.add(labels[x.ops[-1]])
    iters = 0
    seeded = set()
    while True:
        while work and iters < 20000:
            iters += 1
            b = work.pop()
            st = in_state[b].copy()
            for (t, s) in run(b, st, None):
                m, ch = merge(in_state.get(t), s)
                if ch:
                    in_state[t] = m
                    work.append(t)
        # seed unreached labelled leaders (switch cases) with TOP
        new = []
        sl = sorted(leaders)
        for k, l in enumerate(sl):
            if l >= n or l in in_state or l in seeded:
                continue
            e = sl[k + 1] if k + 1 < len(sl) else n
            if all(ins[q].op == "nop" for q in range(l, e)):
                continue
            new.append(l)
        if not new:
            break
        for l in new:
            seeded.add(l)
            in_state[l] = State(set(), set(), {})
            work.append(l)
    for b in sorted(in_state):
        run(b, in_state[b].copy(), fi)
    fi.calls.sort(key=lambda c: c.pc)
    _an_cache[key] = fi
    return fi


_an_cache = {}


def arity_of(fi):
    ci = max([INT_ARGS[r] + 1 for r in fi.exposed if r in INT_ARGS], default=0)
    cf = max([FP_ARGS[r] + 1 for r in fi.exposed if r in FP_ARGS], default=0)
    return ci, cf


# ---------------------------------------------------------------- return value use
def ret_use(fi, call):
    """scan after the call: kinds of first access to v0 / f0 along paths"""
    ins, labels = fi.ins, fi.labels
    n = len(ins)
    if call.kind == "tail":
        return {"ret"}, {"fret"}
    kinds = set()
    fkinds = set()
    stack = [(call.idx + 2, True, True)]
    seen = set()
    steps = 0
    while stack and steps < 400:
        i, live_v, live_f = stack.pop()
        while i < n and steps < 400:
            steps += 1
            if (i, ) in seen and False:
                break
            x = ins[i]
            op = x.op
            if op in ("jal", "jalr"):
                # delay slot first
                if i + 1 < n:
                    rd, wr = decode(ins[i + 1])
                    if "v0" in rd and live_v:
                        kinds.add("val")
                    if "f0" in rd and live_f:
                        fkinds.add("f")
                if op == "jalr" and x.ops and rname(x.ops[-1]) == "v0" and live_v:
                    kinds.add("val")
                break
            if op == "jr":
                if i + 1 < n:
                    rd, wr = decode(ins[i + 1])
                    if "v0" in rd and live_v:
                        kinds.add("val")
                    if "v0" in wr:
                        live_v = False
                if x.ops and rname(x.ops[0]) == "ra":
                    if live_v:
                        kinds.add("ret")
                    if live_f:
                        fkinds.add("fret")
                break
            if op == "j":
                tgt = x.ops[0] if x.ops else ""
                if i + 1 < n:
                    rd, wr = decode(ins[i + 1])
                    if "v0" in rd and live_v:
                        kinds.add("val")
                if tgt in labels:
                    if (labels[tgt], live_v, live_f) not in seen:
                        seen.add((labels[tgt], live_v, live_f))
                        stack.append((labels[tgt], live_v, live_f))
                else:
                    if live_v:
                        kinds.add("ret")
                break
            if op in BRANCHES:
                rds = [rname(t) for t in x.ops[:-1]]
                if "v0" in rds and live_v:
                    kinds.add("val")
                if i + 1 < n:
                    rd, wr = decode(ins[i + 1])
                    if "v0" in rd and live_v:
                        kinds.add("val")
                    if "f0" in rd and live_f:
                        fkinds.add("f")
                    if "v0" in wr:
                        live_v = False
                    if "f0" in wr:
                        live_f = False
                tgt = x.ops[-1] if x.ops else ""
                if (live_v or live_f) and tgt in labels and (labels[tgt], live_v, live_f) not in seen:
                    seen.add((labels[tgt], live_v, live_f))
                    stack.append((labels[tgt], live_v, live_f))
                if not (live_v or live_f):
                    break
                if op == "b":
                    break
                i += 2
                continue
            rd, wr = decode(x)
            if live_v and "v0" in rd:
                if op in S64_OPS:
                    kinds.add("s64")
                else:
                    mem = [MEM_RE.match(t) for t in x.ops]
                    if any(m and m.group(2) == "v0" for m in mem) and (op in LOADS or op in STORES):
                        kinds.add("ptr")
                    else:
                        kinds.add("val")
            if live_f and "f0" in rd:
                fkinds.add("f")
            if "v0" in wr:
                live_v = False
            if "f0" in wr:
                live_f = False
            if not live_v and not live_f:
                break
            i += 1
    return kinds, fkinds


# ---------------------------------------------------------------- C parsing
def strip_c(src):
    out, i, n = [], 0, len(src)
    while i < n:
        c = src[i]
        if src.startswith("/*", i):
            j = src.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append(" " * 0 + " ")
            i = j
        elif src.startswith("//", i):
            j = src.find("\n", i)
            j = n if j < 0 else j
            i = j
        elif c == '"':
            j = i + 1
            while j < n and src[j] != '"':
                j += 2 if src[j] == "\\" else 1
            out.append('""')
            i = j + 1
        elif c == "'":
            j = i + 1
            while j < n and src[j] != "'":
                j += 2 if src[j] == "\\" else 1
            out.append(src[i:j + 1])
            i = j + 1
        else:
            out.append(c)
            i += 1
    s = "".join(out)
    # preprocessor lines (with continuations)
    s = re.sub(r"(?m)^[ \t]*#(?:[^\n\\]|\\.|\\\n)*$", "", s)
    s = re.sub(r"__attribute__\s*\(\(.*?\)\)", " ", s)
    return s


def classify_ret(t):
    t = re.sub(r"\b(extern|static|inline|noinline|const|volatile|register)\b", " ", t)
    t = t.strip()
    if "*" in t:
        return "ptr"
    if re.search(r"\bvoid\b", t):
        return "void"
    if re.search(r"\b(s64|u64|long|int64\w*|u_long|ull|sll)\b", t):
        return "64"
    if re.search(r"\b(f32|float|double|f64)\b", t):
        return "f"
    return "32"


def count_params(p):
    p = p.strip()
    if p == "":
        return None  # unprototyped
    if p == "void":
        return 0
    if "..." in p:
        return -1
    return len(split_ops(p))


HDR_RE = re.compile(r"^(.*?)\b([A-Za-z_]\w*)\s*\(([^()]*)\)\s*$", re.S)


def parse_c(path):
    src = strip_c(open(path, errors="replace").read())
    decls, defs = {}, {}
    seg = ""
    depth = 0
    body_chars = []  # list of (pos, char) at depth>=1 kept as string with positions
    i, n = 0, len(src)
    bodies = []  # (start,end) of depth>=1 regions of function bodies
    start = None
    while i < n:
        c = src[i]
        if depth == 0:
            if c == ";":
                m = HDR_RE.match(seg.strip())
                if m and "=" not in m.group(1):
                    decls[m.group(2)] = (classify_ret(m.group(1)), count_params(m.group(3)), m.group(3))
                seg = ""
            elif c == "{":
                m = HDR_RE.match(seg.strip())
                if m and "=" not in m.group(1):
                    defs[m.group(2)] = (classify_ret(m.group(1)), count_params(m.group(3)), m.group(3))
                    start = i
                    depth = 1
                else:
                    start = None
                    depth = 1
                seg = ""
            else:
                seg += c
        else:
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0 and start is not None:
                    bodies.append((start, i))
                    start = None
        i += 1
    return src, decls, defs, bodies


IDENT_RE = re.compile(r"[A-Za-z_]\w*")


def matching(s, i, o="(", c=")"):
    d = 0
    n = len(s)
    while i < n:
        if s[i] == o:
            d += 1
        elif s[i] == c:
            d -= 1
            if d == 0:
                return i
        i += 1
    return -1


CCall = namedtuple("CCall", "name addr args text stmt pos indirect")


def find_ccalls(src, bodies):
    calls = []
    for (a, b) in bodies:
        for m in IDENT_RE.finditer(src, a, b):
            name = m.group(0)
            e = m.end()
            j = e
            while j < b and src[j].isspace():
                j += 1
            if j >= b or src[j] != "(":
                continue
            addr = name_to_addr(name)
            if addr is None:
                continue
            k = matching(src, j)
            if k < 0:
                continue
            argtxt = src[j + 1:k]
            args = split_ops(argtxt) if argtxt.strip() else []
            p = m.start() - 1
            while p >= a and src[p].isspace():
                p -= 1
            prev = src[p] if p >= a else ""
            pw = src[max(a, p - 3):p + 1]
            q = k + 1
            while q < b and src[q].isspace():
                q += 1
            nxt = src[q] if q < b else ""
            stmt = (prev in ";{}" or pw.endswith("else") or prev == ")" and False) and nxt == ";"
            calls.append(CCall(name, addr, args, name + "(" + argtxt.strip() + ")", stmt, m.start(), False))
        # indirect calls: ((T (*)(...))expr)(args)
        for m in re.finditer(r"\(\s*\*\s*\)\s*\(", src[a:b]):
            pos = a + m.start()
            ps = a + m.end() - 1
            pe = matching(src, ps)
            if pe < 0:
                continue
            q = pe + 1
            # after the cast's closing ')' we are inside outer '(' ; find the outer close
            # position of the cast paren open: scan back for '(' that encloses "(*)"
            d = 1
            r = q
            while r < b and d > 0:
                if src[r] == "(":
                    d += 1
                elif src[r] == ")":
                    d -= 1
                r += 1
            # r is after outer ')'; now an arg list must follow
            while r < b and src[r].isspace():
                r += 1
            if r < b and src[r] == "(":
                k = matching(src, r)
                if k > 0:
                    argtxt = src[r + 1:k]
                    args = split_ops(argtxt) if argtxt.strip() else []
                    calls.append(CCall("<indirect>", None, args, "(*)(" + argtxt.strip() + ")", False, pos, True))
    calls.sort(key=lambda c: c.pos)
    return calls


NUM_RE = re.compile(r"^\(?\s*(?:\([A-Za-z_][\w\s\*]*\)\s*)*\(?\s*(-?(?:0[xX][0-9A-Fa-f]+|\d+))[uUlL]*\s*\)?\)?$")
ADD_RE = re.compile(r"^(?:\([A-Za-z_][\w\s\*]*\)\s*)*\(?\s*[A-Za-z_]\w*(?:\s*\[[^\]]*\])?\s*\+\s*(0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\s*\)?$")
AMP_RE = re.compile(r"^&\s*[A-Za-z_]\w*\s*\[\s*(0[xX][0-9A-Fa-f]+|\d+)\s*\]$")


def c_key(a):
    a = a.strip()
    m = NUM_RE.match(a)
    if m:
        return ("c", int(m.group(1), 0) & 0xFFFFFFFF)
    m = ADD_RE.match(a)
    if m:
        return ("add", int(m.group(1), 0))
    m = AMP_RE.match(a)
    if m:
        return ("add", int(m.group(1), 0))
    return None


def asm_key(v):
    if v is None:
        return None
    if v[0] == "c":
        return ("c", v[1])
    if v[0] == "add":
        return ("add", v[2] & 0xFFFFFFFF if v[2] < 0 else v[2])
    return None


def fmt_val(v):
    if v is None:
        return "?"
    if v[0] == "c":
        return "0x%X" % v[1]
    if v[0] == "add":
        return "(%s)+0x%X" % (fmt_val(v[1]), v[2] & 0xFFFFFFFF if v[2] < 0 else v[2])
    if v[0] == "ld":
        return "[%s+0x%X]" % (fmt_val(v[1]), v[2] & 0xFFFFFFFF if v[2] < 0 else v[2])
    if v[0] == "init":
        return v[1]
    if v[0] == "ret":
        return "ret@%X" % v[1]
    return "?"


# ---------------------------------------------------------------- the checks
Finding = namedtuple("Finding", "sev cls conf file callee asmtxt ctxt note")
SEV = {"ARGS_SWAPPED": 0, "ARITY_LESS": 0, "CONST_MISMATCH": 1, "RET_USED_BUT_VOID": 2, "RET64": 3,
       "ARITY_LESS_CALLEE": 4, "RET_DISCARDED": 5, "PROTO_ARITY": 6, "PROTO_RET": 7, "RET_PTR_AS_S32": 8,
       "ARITY_MORE": 9, "RET_F0": 10, "OFFSET_MISMATCH": 8}
CONF = {"HIGH": 0, "MED": 1, "LOW": 2}


def asm_call_desc(fi, c):
    parts = []
    for r in INT_ARG_NAMES:
        if r in c.W:
            parts.append("%s=%s" % (r, fmt_val(c.vals.get(r))))
    for r in FP_ARG_NAMES:
        if r in c.W:
            parts.append("%s=set" % r)
    return "%s@%X %s(%s)" % (c.kind, c.pc, addr_name(c.target) if c.target else "<ptr>", ", ".join(parts))


_defs_cache = {}


SRC_DEFS = {}


def _src_scan(f):
    try:
        _, _, defs, _ = parse_c(f)
    except Exception:
        return []
    return [(name_to_addr(nm), d) for nm, d in defs.items() if name_to_addr(nm) is not None]


def build_src_index():
    files = [str(p) for p in (ROOT / "src").rglob("*.c")]
    with Pool(4) as pool:
        for lst in pool.imap_unordered(_src_scan, files, chunksize=64):
            for a, d in lst:
                SRC_DEFS.setdefault(a, d)


def param_arity(d):
    """(ints, floats) from a definition tuple (ret, n, paramtext) or None"""
    if not d or d[1] in (None, -1) or len(d) < 3:
        return None
    ps = split_ops(d[2]) if d[2].strip() not in ("", "void") else []
    nf = sum(1 for p in ps if re.search(r"\b(f32|float|double)\b", p) and "*" not in p)
    return (len(ps) - nf, nf)


_hx_cache = {}


def hexrays_arity(addr):
    if addr in _hx_cache:
        return _hx_cache[addr]
    r = None
    f = ROOT / "scratch" / "hexrays" / "f" / ("%06X.c" % addr)
    if f.exists():
        txt = open(f, errors="replace").read(4000)
        m = re.search(r"^[^\n/;{}]*?\b[A-Za-z_]\w*(?:@<[^>]*>)?\s*\(([^()]*)\)\s*\n?\s*\{", txt, re.M)
        if m:
            p = m.group(1).strip()
            ps = [] if p in ("", "void") else split_ops(p)
            nf = sum(1 for q in ps if re.search(r"\b(float|double)\b", q))
            r = (len(ps) - nf, nf)
    _hx_cache[addr] = r
    return r


def callee_def(addr):
    if addr in _defs_cache:
        return _defs_cache[addr]
    r = None
    f = EQ / ("%06X.c" % addr)
    if f.exists():
        _, _, defs, _ = parse_c(f)
        for nm, d in defs.items():
            if name_to_addr(nm) == addr:
                r = d
                break
    if r is None:
        r = SRC_DEFS.get(addr)
    _defs_cache[addr] = r
    return r


def check_file(path):
    path = Path(path)
    stem = path.stem
    try:
        addr = int(stem, 16)
    except ValueError:
        return []
    fi = analyze(addr)
    if fi is None or not fi.ins:
        return []
    src, decls, defs, bodies = parse_c(path)
    ccalls = find_ccalls(src, bodies)
    fname = path.name
    out = []
    own_ar = arity_of(fi)
    own_ret = None
    for nm, d in defs.items():
        if name_to_addr(nm) == addr:
            own_ret = d[0]
    by_callee_asm = defaultdict(list)
    for c in fi.calls:
        if c.kind == "jalr":
            by_callee_asm["<ptr>"].append(c)
        else:
            by_callee_asm[c.target].append(c)
    by_callee_c = defaultdict(list)
    for cc in ccalls:
        by_callee_c["<ptr>" if cc.indirect else cc.addr].append(cc)

    for tgt, alist in by_callee_asm.items():
        clist = by_callee_c.get(tgt, [])
        if not clist:
            continue
        cname = addr_name(tgt) if tgt != "<ptr>" else "<ptr>"
        if tgt != "<ptr>" and VARIADIC.search(cname):
            continue
        sub = analyze(tgt) if tgt != "<ptr>" else None
        car_i, car_f = arity_of(sub) if sub else (None, None)
        if sub and tgt != "<ptr>":
            _hx = hexrays_arity(tgt)  # Hex-Rays prototype is more reliable than the asm scan when it reads fewer
            if _hx is not None and _hx[0] < car_i and _hx[1] >= car_f:
                car_i = _hx[0]
        if car_f is not None and car_f >= 7 and car_i >= 5:
            continue  # variadic (printf-like: dumps every arg reg)
        _d = callee_def(tgt) if tgt != "<ptr>" else None
        if _d and _d[1] == -1:
            continue
        ext = None
        if sub is None and tgt != "<ptr>":
            ext = param_arity(callee_def(tgt)) or hexrays_arity(tgt)
        paired = len(alist) == len(clist)
        needs = []
        needs_weak = []
        for c in alist:
            for lst, WW in ((needs, set(c.W) - c.U), (needs_weak, set(c.W))):
                if car_i is not None:
                    ni = max([INT_ARGS[r] + 1 for r in WW if r in INT_ARGS and INT_ARGS[r] < car_i], default=0)
                    nf = max([FP_ARGS[r] + 1 for r in WW if r in FP_ARGS and FP_ARGS[r] < car_f], default=0)
                else:
                    ni = max([INT_ARGS[r] + 1 for r in WW if r in INT_ARGS], default=0)
                    nf = max([FP_ARGS[r] + 1 for r in WW if r in FP_ARGS], default=0)
                lst.append(ni + nf)
        multi_diff = len(set(needs)) > 1
        decl = decls.get(cname) or defs.get(cname)
        used = set()
        for idx, cc in enumerate(clist):
            def score(j):
                ac = alist[j]
                m = 0
                for r in INT_ARG_NAMES:
                    k = INT_ARGS[r]
                    if r in ac.W and k < len(cc.args):
                        ak, ck = asm_key(ac.vals.get(r)), c_key(cc.args[k])
                        if ak and ck and ak != ck:
                            m += 1
                return (m, abs(len(cc.args) - needs[j]), 0 if (j == idx) else 1, j)
            if len(alist) == 1:
                j = 0
            else:
                cand = [j for j in range(len(alist)) if j not in used] or list(range(len(alist)))
                j = min(cand, key=score)
            used.add(j)
            c, need = alist[j], needs[j]
            nc = len(cc.args)
            conf_base = "HIGH" if (paired or len(alist) == 1) else "MED"
            if tgt == "<ptr>" and (not paired):
                continue
            asmtxt = asm_call_desc(fi, c)
            ci = max([INT_ARGS[r] + 1 for r in c.W if r in INT_ARGS], default=0)
            # ---- arity
            if nc < need and not paired and len(alist) > 1 and min(needs) <= nc:
                pass  # another asm call of the same callee explains this C call (unpaired): no finding
            elif nc < need:
                conf = conf_base
                note = "C passes %d, asm fixes %d" % (nc, need)
                if car_i is None and tgt != "<ptr>":
                    if ext is None:
                        conf = "MED" if conf == "HIGH" else conf
                        note += " (callee arity unknown)"
                    elif ext[0] + ext[1] >= need:
                        note += " (callee proto/hexrays has %d args)" % (ext[0] + ext[1])
                    else:
                        conf = "LOW"
                        note += " (callee proto/hexrays has only %d args: maybe temp)" % (ext[0] + ext[1])
                elif tgt == "<ptr>":
                    conf = "LOW"  # indirect call: callee unknown, extra regs may be temps
                if tgt != "<ptr>" and car_i is None and ext is None and conf == "MED":
                    # callee unknown: keep MED only if integer args are involved (fp-only gaps are usually temps)
                    if not any(r in INT_ARGS for r in c.W):
                        conf = "LOW"
                out.append(Finding(SEV["ARITY_LESS"], "ARITY_LESS", conf, fname, cname, asmtxt, cc.text, note))
            elif nc < needs_weak[j]:
                out.append(Finding(SEV["ARITY_LESS"], "ARITY_LESS", "LOW" if conf_base == "HIGH" else "LOW", fname, cname, asmtxt, cc.text,
                                   "C passes %d, asm sets %d regs (some read before the call: maybe temps)" % (nc, needs_weak[j])))
            elif car_i is not None and nc < car_i + car_f and nc >= need:
                # callee reads regs the caller asm does not set: must be pass-through own params
                miss = [r for r in INT_ARG_NAMES[:car_i] if r not in c.W and r in c.M and False]
                miss = [r for r in INT_ARG_NAMES[:car_i] if r not in c.W]
                if miss and car_i > nc:
                    pt = [r for r in miss[nc - 0:] if r not in c.M] if nc < len(miss) else []
                    if pt or True:
                        # only when the register was NOT written since entry (pass-through of own params)
                        pt = [r for r in INT_ARG_NAMES[nc:car_i] if r not in c.M and INT_ARGS[r] < (own_ar[0] or 0)]
                        if pt:
                            out.append(Finding(SEV["ARITY_LESS_CALLEE"], "ARITY_LESS_CALLEE", "MED", fname, cname, asmtxt,
                                               cc.text, "callee reads %d args, C passes %d; asm passes through %s"
                                               % (car_i, nc, ",".join(pt))))
            elif car_i is not None and nc > max(car_i + (car_f or 0), need) and decl and decl[1] not in (None, -1) \
                    and tgt != "<ptr>":
                out.append(Finding(SEV["ARITY_MORE"], "ARITY_MORE", "LOW", fname, cname, asmtxt, cc.text,
                                   "C passes %d, callee reads %d, asm fixes %d" % (nc, car_i, need)))
            # ---- per-arg (only when no fp args involved)
            nfloat = any(r in FP_ARGS for r in c.W)
            cidx = list(range(nc))
            dd = decl or callee_def(tgt) if tgt != "<ptr>" else None
            if dd and len(dd) >= 3 and dd[1] not in (None, -1):
                pl = split_ops(dd[2]) if dd[2].strip() not in ("", "void") else []
                if len(pl) == nc:
                    cidx = [i for i, q in enumerate(pl) if not (re.search(r"\b(f32|float|double)\b", q) and "*" not in q)]
                elif any(re.search(r"\b(f32|float|double)\b", q) for q in pl):
                    cidx = []
            if re.search(r"\d\.\d*f?\b|\bfarg|\bf\d", " ".join(cc.args)) and not (dd and len(dd) >= 3):
                cidx = []
            if not nfloat and nc >= 1 and cidx:
                mism = []
                for r in INT_ARG_NAMES:
                    k = INT_ARGS[r]
                    if r in c.W and k < len(cidx) and (car_i is None or k < car_i):
                        ak = asm_key(c.vals.get(r))
                        ck = c_key(cc.args[cidx[k]])
                        if ak and ck:
                            if ak != ck:
                                mism.append((k, ak, ck))
                if mism and len(alist) > 1:
                    def _nm(a2):
                        n = 0
                        for r in INT_ARG_NAMES:
                            k = INT_ARGS[r]
                            if r in a2.W and k < len(cidx) and (car_i is None or k < car_i):
                                x, y = asm_key(a2.vals.get(r)), c_key(cc.args[cidx[k]])
                                if x and y and x != y:
                                    n += 1
                        return n
                    if any(_nm(a2) == 0 for a2 in alist):
                        mism = []  # another asm call matches this C call exactly: unpaired, no finding
                if mism:
                    ak_ms = sorted(m[1] for m in mism)
                    ck_ms = sorted(m[2] for m in mism)
                    conf = conf_base
                    if len(mism) >= 2 and ak_ms == ck_ms:
                        out.append(Finding(SEV["ARGS_SWAPPED"], "ARGS_SWAPPED", conf, fname, cname, asmtxt, cc.text,
                                           "positions %s" % [m[0] for m in mism]))
                    else:
                        for (k, ak, ck) in mism:
                            if ak[0] == "c" and ck[0] == "c" and cname in ("memset", "memcpy") and k == 2 and ck[1] > ak[1]:
                                continue  # adjacent memset/memcpy calls fused into one bigger C call
                            if ak[0] == "c" and ck[0] == "c" and not paired and any(
                                    (r in a2.W and asm_key(a2.vals.get(r)) == ck) for a2 in alist):
                                continue
                            if ak[0] == "c" and ck[0] == "c":
                                out.append(Finding(SEV["CONST_MISMATCH"], "CONST_MISMATCH", conf, fname, cname, asmtxt,
                                                   cc.text, "arg%d asm=0x%X C=0x%X" % (k, ak[1], ck[1])))
                            elif ak[0] == "add" and ck[0] == "add":
                                out.append(Finding(SEV["OFFSET_MISMATCH"], "OFFSET_MISMATCH", "LOW", fname, cname,
                                                   asmtxt, cc.text, "arg%d asm +0x%X C +0x%X" % (k, ak[1], ck[1])))
                            else:
                                out.append(Finding(SEV["CONST_MISMATCH"], "CONST_MISMATCH", "LOW", fname, cname, asmtxt,
                                                   cc.text, "arg%d asm=%s C=%s" % (k, ak, ck)))
            # ---- return value
            if paired and tgt != "<ptr>":
                kinds, fkinds = ret_use(fi, c)
                dret = decl[0] if decl else None
                cdef = callee_def(tgt)
                real = {"val", "s64", "ptr"} & kinds
                if "ret" in kinds and own_ret not in (None, "void"):
                    real = real | {"ret"}
                if real and dret == "void":
                    out.append(Finding(SEV["RET_USED_BUT_VOID"], "RET_USED_BUT_VOID", "HIGH" if "ret" not in kinds or len(kinds) > 1 else "MED",
                                       fname, cname, asmtxt + " uses v0:" + ",".join(sorted(kinds)), cc.text,
                                       "prototype returns void"))
                elif real and cc.stmt and dret not in ("void", None):
                    out.append(Finding(SEV["RET_DISCARDED"], "RET_DISCARDED", "MED" if "ret" not in kinds else "LOW", fname, cname,
                                       asmtxt + " uses v0:" + ",".join(sorted(kinds)), cc.text,
                                       "value discarded in C (statement call)"))
                if "s64" in kinds and dret in ("32", "ptr", "void") and not (cdef and cdef[0] == "64"):
                    out.append(Finding(SEV["RET64"], "RET64", "MED", fname, cname, asmtxt + " 64-bit use of v0",
                                       cc.text, "prototype ret=%s" % dret))
                if "ptr" in kinds and dret == "32":
                    out.append(Finding(SEV["RET_PTR_AS_S32"], "RET_PTR_AS_S32", "LOW", fname, cname,
                                       asmtxt + " v0 used as base", cc.text, "prototype returns integer"))
                if fkinds and "f" in fkinds and dret in ("32", "void", "ptr", "64"):
                    out.append(Finding(SEV["RET_F0"], "RET_F0", "LOW", fname, cname, asmtxt + " reads f0", cc.text,
                                       "prototype ret=%s" % dret))
        # ---- prototype vs callee own definition
        if tgt != "<ptr>":
            cdef = callee_def(tgt)
            if decl and cdef and cname not in defs:
                if decl[1] not in (None, -1) and cdef[1] not in (None, -1) and decl[1] != cdef[1]:
                    out.append(Finding(SEV["PROTO_ARITY"], "PROTO_ARITY", "MED" if decl[1] < cdef[1] else "LOW", fname, cname, "decl args=%d" % decl[1],
                                       "def args=%d" % cdef[1], "caller prototype disagrees with port/eq/%06X.c" % tgt))
                if (decl[0] == "void") != (cdef[0] == "void") or ("64" in (decl[0], cdef[0]) and decl[0] != cdef[0]):
                    out.append(Finding(SEV["PROTO_RET"], "PROTO_RET", "MED" if "64" in (decl[0], cdef[0]) else "LOW", fname, cname, "decl ret=%s" % decl[0],
                                       "def ret=%s" % cdef[0], "caller prototype disagrees with port/eq/%06X.c" % tgt))
    return out


def worker(p):
    try:
        return check_file(p)
    except Exception as e:  # keep going
        return [Finding(99, "ERROR", "LOW", Path(p).name, "", "", "", repr(e))]


def write_report(findings, out, full=False):
    findings.sort(key=lambda f: (f.sev + (0 if f.conf == "HIGH" else (20 if f.conf == "MED" else 40)), f.file))
    cnt = defaultdict(int)
    for f in findings:
        cnt[(f.cls, f.conf)] += 1
    TIER1 = {"ARITY_LESS", "ARGS_SWAPPED", "CONST_MISMATCH"}
    with open(out, "w") as o:
        o.write("# check_calls report (filtered): %d findings total, LOW omitted unless --full\n" % len(findings))
        for (c, cf), v in sorted(cnt.items(), key=lambda kv: (SEV.get(kv[0][0], 99), kv[0][1])):
            o.write("#   %-18s %-4s %d\n" % (c, cf, v))
        o.write("# Section 1: full entries (ARITY_LESS/ARGS_SWAPPED/CONST_MISMATCH HIGH+MED, RET_USED_BUT_VOID HIGH).\n"
                "# Section 2: one-line entries (other MED). format: CLASS file callee | asm | C | note\n\n")
        sec2 = []
        for f in findings:
            if f.conf == "LOW" and not full:
                continue
            if (f.cls in TIER1) or (f.cls == "RET_USED_BUT_VOID" and f.conf == "HIGH") or full:
                o.write("[%s/%s] %s -> %s\n    asm: %s\n    C  : %s\n    %s\n" % (f.cls, f.conf, f.file, f.callee,
                                                                               f.asmtxt, f.ctxt, f.note))
            else:
                sec2.append(f)
        if sec2:
            o.write("\n# ---- Section 2 ----\n")
            for f in sec2:
                o.write("%s/%s %s %s | %s | %s | %s\n" % (f.cls, f.conf, f.file, f.callee, f.asmtxt[:110], f.ctxt[:90], f.note[:80]))
    return cnt


def main():
    args = sys.argv[1:]
    out = ROOT / "docs" / "agents" / "b12" / "check_calls_report.txt"
    jobs = 4
    FULL = False
    files = []
    while args:
        a = args.pop(0)
        if a == "--out":
            out = args.pop(0)
        elif a == "--full":
            FULL = True
        elif a == "--jobs":
            jobs = min(4, int(args.pop(0)))
        else:
            files.append(a)
    if not files:
        files = sorted(str(p) for p in EQ.glob("*.c") if re.fullmatch(r"[0-9A-Fa-f]{6}", p.stem))
    build_src_index()
    with Pool(jobs) as pool:
        res = pool.map(worker, files, chunksize=32)
    findings = [f for r in res for f in r]
    cnt = write_report(findings, out, FULL)
    for (c, cf), v in sorted(cnt.items(), key=lambda kv: (SEV.get(kv[0][0], 99), kv[0][1])):
        print("%-18s %-4s %d" % (c, cf, v))
    print("total", len(findings), "->", out)


if __name__ == "__main__":
    main()
