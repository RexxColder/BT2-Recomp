#!/usr/bin/env python3
"""Barrido estatico asm vs C de la PILA de cada port/eq/*.c (heuristico). Clases:
  STACK_SHORT       el C pasa a un callee un puntero a un array local mas pequeno que lo que el callee lee/escribe y que el asm reserva
                    (caso 14F8E0: u8 blk[48] y el callee copia 0x40 bytes); o bien el total de aggregados locales del C cubre < 85 % de
                    la region de pila con direccion tomada que usa el asm (confianza MED).
  STRUCT_BY_VALUE   el bloque (copia por valor, p.ej. ld/sd sp->sp o callee que lee 0x20/0x30/0x40/0x80 bytes) tiene campos que el asm
                    rellena (stores directos o sub-bloques pasados a callees) y el C no (offsets relativos al inicio del bloque).
  STACK_ARGS        antes de un jal el asm guarda en 0($sp),8($sp).. (args de pila, nunca leidos) y el C llama con menos de 8+n
                    parametros enteros.
  UNINIT_STACK      el bloque pasado al callee no recibe NINGUNA escritura en el C y el asm si lo rellenaba.
  UNFILLED          como STRUCT_BY_VALUE pero sin indicio de copia por valor.
Uso: check_stack.py [--dir DIR] [--out FICHERO] [ficheros .c ...]    (sin args: port/eq/*.c)
Confianza HIGH: el asm escribe mas alla de la capacidad del array del C / el callee lee tamano conocido; MED: el resto."""
import re, sys, os, glob, collections
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM_DIRS = [os.path.join(ROOT, 'scratch/m2c_sweep'), os.path.expanduser('~/Escritorio/BT2-overlay-work/scratch/m2c_sweep')]
CALLEE_SAVED = {'s0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 'fp', 'ra', 'gp', 's8'} | {'f%d' % i for i in range(20, 32)}
SIZES = {'lb': 1, 'lbu': 1, 'sb': 1, 'lh': 2, 'lhu': 2, 'sh': 2, 'lw': 4, 'lwu': 4, 'sw': 4, 'lwc1': 4, 'swc1': 4, 'lwl': 4, 'lwr': 4,
         'swl': 4, 'swr': 4, 'ld': 8, 'sd': 8, 'ldc1': 8, 'sdc1': 8, 'ldl': 8, 'ldr': 8, 'sdl': 8, 'sdr': 8, 'lq': 16, 'sq': 16,
         'lqc2': 16, 'sqc2': 16}
STORES = {'sb', 'sh', 'sw', 'swc1', 'swl', 'swr', 'sd', 'sdc1', 'sdl', 'sdr', 'sq', 'sqc2'}
NODEST = STORES | {'nop', 'jr', 'j', 'jal', 'jalr', 'mtc1', 'ctc1', 'ctc2', 'qmtc2', 'mthi', 'mtlo', 'sync', 'break', 'syscall',
                   'mtsab', 'mtsah', 'mtc0', 'ei', 'di', 'cache', 'pref'}
ARGREGS = ['a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3']
CALLER_SAVED = {'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7', 't8', 't9', 'at'}
LIBC = {'memcpy': ('w', 'r'), 'memmove': ('w', 'r'), 'memset': ('w',), 'bzero': ('w',)}
INS = re.compile(r'/\*\s*\w+\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/\s+(\S+)\s*(.*)$')
LAB = re.compile(r'^\s*\.?(\.L\w+):')


def num(s):
    s = s.strip()
    try:
        return int(s, 0)
    except Exception:
        return None


LEFT = {'lwl': 4, 'ldl': 8, 'swl': 4, 'sdl': 8}


def span(op, off):
    if op in LEFT:
        return off - LEFT[op] + 1, off + 1
    return off, off + SIZES[op]


def asm_path(addr):
    for d in ASM_DIRS:
        p = os.path.join(d, '%08X.s' % addr)
        if os.path.exists(p):
            return p
    return None


_asm_cache = {}


def parse_asm(addr):
    if addr in _asm_cache:
        return _asm_cache[addr]
    p = asm_path(addr)
    res = None
    if p:
        ins = []
        for ln in open(p, errors='replace'):
            m = INS.search(ln)
            if m:
                ops = [o.strip() for o in re.split(r',(?![^(]*\))', m.group(4).split('#')[0].strip())] if m.group(4).strip() else []
                w = int.from_bytes(bytes.fromhex(m.group(2)), 'little')
                ins.append([m.group(3), ops, w, int(m.group(1), 16), False])
            elif LAB.match(ln):
                ins.append(['<label>', [], 0, 0, False])
        # delay slot: process the delay slot first (it runs before the callee / branch target)
        out = []
        i = 0
        while i < len(ins):
            o = ins[i][0]
            if (o in ('jal', 'jalr', 'jr', 'j') or (o.startswith('b') and o not in ('break',))) and not o.endswith('l') or o in ('jal', 'jalr'):
                if i + 1 < len(ins) and ins[i + 1][0] != '<label>':
                    out.append(ins[i + 1]); out.append(ins[i]); i += 2; continue
            out.append(ins[i]); i += 1
        res = out
    _asm_cache[addr] = res
    return res


def reg(o):
    return o.strip().lstrip('$')


def mem(o):
    m = re.match(r'^(-?(?:0x)?[0-9A-Fa-f]*)\(\$(\w+)\)$', o.strip())
    if not m:
        return None
    off = num(m.group(1)) if m.group(1) not in ('', '-') else 0
    return (off, m.group(2)) if off is not None else None


def dest_of(op, ops):
    if op in NODEST or op.startswith('b') and op != 'break' or op.startswith('c.') or not ops:
        return None
    if op in ('mult', 'multu', 'div', 'divu', 'mult1', 'multu1', 'div1', 'divu1') and len(ops) == 2:
        return None
    if ops[0].startswith('$') and not ops[0].startswith('$f'):
        return reg(ops[0])
    return None


# ---------------------------------------------------------------- callee extents (bytes touched through its argument registers)
_ext_cache = {}
passed = {}


def callee_extents(addr):
    """-> {argindex: (read_end, write_end)} from linear scan of the callee asm; None when no asm."""
    if addr in _ext_cache:
        return _ext_cache[addr]
    ins = parse_asm(addr)
    if not ins:
        _ext_cache[addr] = None
        return None
    al = {ARGREGS[i]: (i, 0) for i in range(8)}
    ext = {}
    for op, ops, w, a, _ in ins:
        if op == '<label>':
            continue
        if op in SIZES and len(ops) == 2:
            mm = mem(ops[1])
            if mm and mm[1] in al and mm[0] is not None:
                k, base = al[mm[1]]
                st0, en0 = span(op, mm[0])
                end = base + en0
                if base + st0 >= 0 and end <= 0x400:
                    r, wr = ext.get(k, (0, 0))
                    if op in STORES:
                        wr = max(wr, end)
                    else:
                        r = max(r, end)
                    ext[k] = (r, wr)
        if op in ('jal', 'jalr'):
            for r in list(al):
                if r in ARGREGS:
                    passed.setdefault(addr, set()).add(al[r][0])
            for r in list(al):
                if r in CALLER_SAVED:
                    del al[r]
            continue
        d = dest_of(op, ops)
        if d is None:
            continue
        new = None
        if op in ('daddu', 'addu', 'or') and len(ops) == 3 and reg(ops[2]) == 'zero' and reg(ops[1]) in al:
            new = al[reg(ops[1])]
        elif op in ('addiu', 'daddiu') and len(ops) == 3 and reg(ops[1]) in al and num(ops[2]) is not None:
            k, b = al[reg(ops[1])]
            new = (k, b + num(ops[2]))
        if new:
            al[d] = new
        elif d in al:
            del al[d]
    _ext_cache[addr] = ext
    return ext


_sa_cache = {}


def callee_stackargs(addr):
    """slots (8 bytes) of the caller's outgoing area that the callee reads/addresses; None when no asm."""
    if addr in _sa_cache:
        return _sa_cache[addr]
    ins = parse_asm(addr)
    res = None
    if ins:
        frame = 0
        for op, ops, w, a, _ in ins:
            if op in ('addiu', 'daddiu') and len(ops) == 3 and reg(ops[0]) == 'sp' and reg(ops[1]) == 'sp':
                v = num(ops[2])
                if v is not None and v < 0:
                    frame = -v
                break
        res = set()
        for op, ops, w, a, _ in ins:
            if op in SIZES and op not in STORES and len(ops) == 2:
                mm = mem(ops[1])
                if mm and mm[1] == 'sp' and mm[0] is not None and mm[0] >= frame:
                    res.add((mm[0] - frame) // 8)
            elif op in ('addiu', 'daddiu') and len(ops) == 3 and reg(ops[1]) == 'sp' and reg(ops[0]) != 'sp':
                v = num(ops[2])
                if v is not None and v >= frame:
                    res.add((v - frame) // 8)
    _sa_cache[addr] = res
    return res


# ---------------------------------------------------------------- asm analysis of one function
class Call:
    pass


def analyse_asm(addr):
    ins = parse_asm(addr)
    if not ins:
        return None
    frame = 0
    for op, ops, w, a, _ in ins:
        if op in ('addiu', 'daddiu') and len(ops) == 3 and reg(ops[0]) == 'sp' and reg(ops[1]) == 'sp':
            v = num(ops[2])
            if v is not None and v < 0:
                frame = -v
            break
    if not frame:
        return None
    acc = []     # (idx, op, reg, off, size, store)
    taken = collections.defaultdict(list)   # off -> [idx]
    st = {}      # reg -> ('sp', off) | ('imm', v)
    calls = []
    pend_stores = []     # (off, idx) direct sp stores since last call
    firstacc = {}
    for i, (op, ops, w, a, _) in enumerate(ins):
        if op == '<label>':
            continue
        if op in SIZES and len(ops) == 2:
            mm = mem(ops[1])
            if mm and mm[1] == 'sp' and mm[0] is not None:
                r = reg(ops[0])
                st0, en0 = span(op, mm[0])
                acc.append((i, op, r, st0, en0 - st0, op in STORES))
                if op in STORES and 0 <= mm[0] < 0x80 and mm[0] % 4 == 0:
                    pend_stores.append((mm[0], op, SIZES[op], i))
        if op == 'jal' or op == 'jalr':
            c = Call()
            c.idx = i
            c.target = ((w & 0x3FFFFFF) << 2) if op == 'jal' else None
            c.name = ops[0] if op == 'jal' and ops else None
            c.args = {}
            c.imm = {}
            for k, r in enumerate(ARGREGS):
                v = st.get(r)
                if v and v[0] == 'sp':
                    c.args[k] = v[1]
                elif v and v[0] == 'imm':
                    c.imm[k] = v[1]
            c.stores = list(pend_stores)
            calls.append(c)
            pend_stores = []
            for r in list(st):
                if r in CALLER_SAVED:
                    del st[r]
            continue
        d = dest_of(op, ops)
        if d is None:
            continue
        new = None
        if op in ('addiu', 'daddiu') and len(ops) == 3:
            v = num(ops[2])
            if reg(ops[1]) == 'sp' and d != 'sp' and v is not None:
                new = ('sp', v)
                taken[v].append(i)
            elif reg(ops[1]) == 'zero' and v is not None:
                new = ('imm', v)
            elif st.get(reg(ops[1])) and st[reg(ops[1])][0] == 'sp' and v is not None:
                new = ('sp', st[reg(ops[1])][1] + v)
        elif op in ('daddu', 'addu', 'or') and len(ops) == 3 and reg(ops[2]) == 'zero':
            if reg(ops[1]) == 'sp' and d != 'sp':
                new = ('sp', 0)
                taken[0].append(i)
            elif reg(ops[1]) in st:
                new = st[reg(ops[1])]
        elif op == 'ori' and len(ops) == 3 and reg(ops[1]) == 'zero' and num(ops[2]) is not None:
            new = ('imm', num(ops[2]))
        if new:
            st[d] = new
        elif d in st:
            del st[d]
    # saved-register slots
    saved = set()
    seen = {}
    loads_rk = {(r, off) for (i, op, r, off, sz, store) in acc if not store}
    for (i, op, r, off, sz, store) in acc:
        if r in CALLER_SAVED or r in ('zero',):
            continue
        key = (r, off)
        if key not in seen:
            seen[key] = store
            if store and r in CALLEE_SAVED and key in loads_rk:
                saved.add(off)
    save_min = min(saved) if saved else frame
    loaded = set()
    for (i, op, r, off, sz, store) in acc:
        if not store:
            loaded.add(off)
    outidx = set()
    for c in calls:
        cov = []
        for k0, o0 in c.args.items():
            cov.append((o0, o0 + 0x40))
        for (o, op, sz, si) in c.stores:
            if o not in loaded and o < 0x40 and not any(a0 <= o < b0 for a0, b0 in cov):
                outidx.add(si)
    A = collections.namedtuple('A', 'frame acc taken calls saved save_min loaded outidx')
    return A(frame, acc, taken, calls, saved, save_min, loaded, outidx)


# ---------------------------------------------------------------- C parsing
TS = {'u8': 1, 's8': 1, 'char': 1, 'u16': 2, 's16': 2, 'u32': 4, 's32': 4, 'f32': 4, 'int': 4, 'float': 4, 'u64': 8, 's64': 8, 'f64': 8,
      'u128': 16, 's128': 16}


def strip_comments(t):
    t = re.sub(r'/\*.*?\*/', lambda m: ' ' * len(m.group(0)) if False else re.sub(r'[^\n]', ' ', m.group(0)), t, flags=re.S)
    return re.sub(r'//[^\n]*', lambda m: ' ' * len(m.group(0)), t)


def ev(e):
    e = e.strip()
    if not e:
        return None
    e2 = re.sub(r'\b(0[xX][0-9a-fA-F]+|\d+)[uUlL]+\b', r'\1', e)
    if not re.match(r'^[0-9a-fA-FxX+\-*()<> \t/]+$', e2):
        return None
    try:
        v = eval(e2.replace('/', '//'), {'__builtins__': {}})
        return int(v)
    except Exception:
        return None


def match_close(t, i, o='(', c=')'):
    d = 0
    for j in range(i, len(t)):
        if t[j] == o:
            d += 1
        elif t[j] == c:
            d -= 1
            if d == 0:
                return j
    return -1


def split_top(s):
    out = []; d = 0; cur = 0
    for j, ch in enumerate(s):
        if ch in '([{':
            d += 1
        elif ch in ')]}':
            d -= 1
        elif ch == ',' and d == 0:
            out.append((cur, j)); cur = j + 1
    out.append((cur, len(s)))
    return out


def find_func(t, name):
    m = None
    for mm in re.finditer(r'^[A-Za-z_][\w \*]*?\b(\w+)\s*\(([^;{}]*)\)\s*\{', t, flags=re.M):
        if mm.group(1) == name:
            m = mm; break
        if m is None:
            m = mm
    if not m:
        return None
    ob = t.index('{', m.end() - 1)
    cb = match_close(t, ob, '{', '}')
    return m, ob, cb


class CFunc:
    pass


def parse_c(path, addr):
    raw = open(path, errors='replace').read()
    t = strip_comments(raw)
    f = find_func(t, 'func_%08X' % addr)
    if not f:
        return None
    m, ob, cb = f
    body = t[ob:cb + 1]
    cf = CFunc()
    cf.text = t; cf.body = body; cf.bodyoff = ob
    cf.params = m.group(2)
    # locals
    loc = {}
    for mm in re.finditer(r'(?:^|[;{}])\s*(?:const\s+|volatile\s+)*(u8|s8|u16|s16|u32|s32|f32|f64|u64|s64|u128|s128|int|float|char)\s+(\w+)((?:\s*\[[^\]]+\])*)\s*(?:__attribute__\s*\(\([^;=]*\)\)\s*)?(?=[=;,])', body):
        ty, nm, dims = mm.group(1), mm.group(2), mm.group(3)
        sz = TS[ty]
        n = 1; isarr = False
        for d in re.findall(r'\[([^\]]+)\]', dims):
            v = ev(d)
            n *= (v if v else 1); isarr = True
        loc[nm] = dict(ty=ty, esz=sz, size=sz * n, arr=isarr)
    # struct locals of unknown size
    cf.unknown_struct = bool(re.search(r'(?:^|[;{}])\s*(?:struct\s+)?[A-Z]\w*\s+\w+\s*(?:\[[^\]]*\])?\s*;', body))
    cf.loc = loc
    cf.addrtaken = {n for n in loc if re.search(r'&\s*\(?\s*' + re.escape(n) + r'\b', body)}
    # pointer aliases p = X + N / &X
    cf.alias = {}
    cf.ptrvars = set(re.findall(r'\b(?:u8|s8|u16|s16|u32|s32|f32|void|u64|s64)\s*\*\s*(\w+)\s*(?:=|;)', body))
    # calls
    cf.calls = []
    for mm in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', body):
        nm = mm.group(1)
        if nm in ('if', 'while', 'for', 'switch', 'return', 'sizeof'):
            continue
        # skip casts/prototype: previous char word-ish after a type means declaration; keep simple
        op = mm.end() - 1
        cl = match_close(body, op)
        if cl < 0:
            continue
        inner = body[op + 1:cl]
        args = [(op + 1 + a, op + 1 + b) for a, b in split_top(inner)] if inner.strip() else []
        cf.calls.append((nm, mm.start(), args))
    # prototypes in file
    cf.decl = {}
    for mm in re.finditer(r'^[A-Za-z_][\w \*]*?\b(\w+)\s*\(([^;{}]*)\)\s*;', t, flags=re.M):
        cf.decl[mm.group(1)] = mm.group(2)
    cf.full = t
    return cf


CAST = re.compile(r'\(\s*(?:const\s+)?(?:struct\s+)?[A-Za-z_]\w*(?:\s+\w+)*\s*\*+\s*\)')


def resolve(expr, cf):
    """expr -> (array name, byte offset) if it points into a local array/addr-taken scalar."""
    e = expr.strip()
    e = re.sub(r'^\s*[A-Z]{1,3}\((.*)\)\s*$', r'\1', e)
    bytes_ = bool(re.search(r'\(\s*(?:const\s+)?(?:u8|s8|void|char)\s*\*\s*\)\s*\w+\s*\+', e))
    e = CAST.sub('', e)
    e = re.sub(r'\(\s*(?:u8|s8|u16|s16|u32|s32|f32|u64|s64|void)\s*\*?\s*\)', '', e).strip()
    while e.startswith('(') and match_close(e, 0) == len(e) - 1:
        e = e[1:-1].strip()
    m = re.match(r'^&?\s*(\w+)\s*(?:\[\s*([^\]]+)\s*\])?\s*(?:\+\s*(.+))?$', e)
    if not m:
        return None
    nm = m.group(1)
    if nm in cf.alias:
        base, off0 = cf.alias[nm]
    elif nm in cf.loc:
        base, off0 = nm, 0
    else:
        return None
    info = cf.loc[base]
    off = off0
    if m.group(2) is not None:
        v = ev(m.group(2))
        if v is None:
            return None
        off += v * info['esz']
    if m.group(3) is not None:
        v = ev(m.group(3).strip().strip('()'))
        if v is None:
            return None
        if e.startswith('&') or info['arr'] is False:
            off += v
        else:
            off += v if (info['esz'] == 1 or bytes_) else v * info['esz']
    # array pointer arithmetic: for u8 arrays bytes; others scaled by element size (C semantics)
    if not (info['arr'] or nm in cf.addrtaken or e.startswith('&')) and nm not in cf.alias:
        return None
    return base, off


def build_alias(cf):
    for mm in re.finditer(r'\b(\w+)\s*=\s*([^;=]+);', cf.body):
        nm = mm.group(1)
        if nm in cf.loc and not cf.loc[nm]['arr'] and nm in cf.ptrvars:
            r = resolve(mm.group(2), cf)
            if r:
                cf.alias[nm] = r


def c_written(cf, base, ext, skip=()):
    """-> (set of written granule offsets (4-byte), whole_flag)  for array/local `base` over the function body."""
    body = cf.body
    wr = set(); whole = False
    names = [base] + [a for a, (b, o) in cf.alias.items() if b == base]
    consumed = []
    # calls: arguments resolving into base
    for nm, pos, args in cf.calls:
        for k, (a, b) in enumerate(args):
            r = resolve(body[a:b], cf)
            if r and r[0] == base:
                consumed.append((a, b))
                if (a, b) in skip:
                    continue
                n2 = nm.replace('__builtin_', '')
                if n2 in ('memset', 'memcpy', 'memmove'):
                    if k == 0 and len(args) >= 3:
                        sz = ev(body[args[2][0]:args[2][1]])
                        if sz is None:
                            whole = True
                        else:
                            for g in range(r[1] // 4, (r[1] + sz + 3) // 4):
                                wr.add(g)
                elif n2 in ('sqrtf', 'fabsf'):
                    pass
                else:
                    sz = ext(nm, k)
                    for g in range(r[1] // 4, (r[1] + (sz if sz else 16) + 3) // 4):
                        wr.add(g)
    # other occurrences
    for n in names:
        for mm in re.finditer(r'\b' + re.escape(n) + r'\b', body):
            p = mm.start()
            if any(a <= p < b for a, b in consumed):
                continue
            pre = body[max(0, p - 40):p]
            suf = body[mm.end():mm.end() + 60]
            info = cf.loc[base]
            if re.search(r'\b(?:u8|s8|u16|s16|u32|s32|f32|f64|u64|s64|u128|s128|int|float|char)\s*$', pre):
                continue
            m1 = re.search(r'\*\s*\(\s*(\w+)\s*(\*?)\s*\*\s*\)\s*\(?\s*$', pre)
            m1b = re.search(r'\*\s*\(\s*(\w+)\s*\*\s*\)\s*\(\s*\(\s*(?:u8|void)\s*\*\s*\)\s*$', pre)
            if not m1:
                m1 = re.search(r'\*\s*\(\s*(\w+)\s*(\*?)\s*\*\s*\)\s*\(\s*\(\s*(?:u8|s8|void)\s*\*\s*\)\s*$', pre)
            if m1:
                sz = 4 if m1.group(2) else TS.get(m1.group(1), 4)
                ms = re.match(r'\s*(?:\+\s*([^)=]+?))?\s*\)?\s*(=(?!=)|[-+|&^*]=)', suf)
                if ms:
                    off = ev(ms.group(1)) if ms.group(1) else 0
                    if off is None:
                        whole = True
                    else:
                        if n in cf.alias:
                            off += cf.alias[n][1]
                        for g in range(off // 4, (off + sz + 3) // 4):
                            wr.add(g)
                continue
            ms = re.match(r'\s*\[\s*([^\]]+)\]\s*(=(?!=)|[-+|&^*]=)', suf)
            if ms:
                v = ev(ms.group(1))
                if v is None:
                    whole = True
                else:
                    off = v * info['esz'] + (cf.alias[n][1] if n in cf.alias else 0)
                    for g in range(off // 4, (off + info['esz'] + 3) // 4):
                        wr.add(g)
                continue
            if re.match(r'\s*\[', suf) or re.match(r'\s*=(?!=)', suf) and not info['arr']:
                if re.match(r'\s*=(?!=)', suf):
                    wr.update(range(0, (info['size'] + 3) // 4))
                    continue
                whole = True
                continue
            # a read-like or unknown use
            if re.match(r'\s*(?:\+|\)|,|;)', suf) or pre.rstrip().endswith('&') or pre.rstrip().endswith('('):
                if re.search(r'=\s*$', pre) or re.match(r'\s*[,;)]', suf) and not re.search(r'[,(]\s*$', pre):
                    pass
                else:
                    pass
            whole = whole or False
    return wr, whole


# ---------------------------------------------------------------- main check per file
def check_file(path, addr, rep):
    an = analyse_asm(addr)
    if an is None:
        return
    cf = parse_c(path, addr)
    if cf is None:
        return
    build_alias(cf)
    nm = os.path.basename(path)
    carr = sum(v['size'] for k, v in cf.loc.items() if v['arr'] or k in cf.addrtaken)

    # asm written granules (direct stores)
    direct = collections.defaultdict(set)
    for (i, op, r, off, sz, store) in an.acc:
        if store and off not in an.saved and i not in an.outidx:
            for g in range(off // 4, (off + sz + 3) // 4):
                direct[g].add(i)
    copy_dest = set()   # offsets that are the destination of ld->sd pair copy
    lastld = {}
    for (i, op, r, off, sz, store) in an.acc:
        if not store and op in ('ld', 'lq', 'lw'):
            lastld[r] = off
        elif store and op in ('sd', 'sq') and r in lastld and lastld[r] != off:
            copy_dest.add(off)

    def ext_of(nmc, k):
        # extent of callee nm (by C name) arg k, if we can map it to an asm call
        for c in an.calls:
            if c.name == nmc or ('func_%08X' % (c.target or 0)) == nmc:
                e = callee_extents(c.target) if c.target else None
                if e is not None and k in passed.get(c.target, ()):
                    return 0x400
                if e and k in e:
                    return max(e[k])
        return None

    # per call checks
    tot_cover = []
    for c in an.calls:
        if c.target is None:
            continue
        cname = c.name
        lc = cname.replace('__builtin_', '')
        # sizes
        e = callee_extents(c.target) or {}
        libc = LIBC.get(cname)
        # --- C calls matching this callee
        ccalls = [(n2, p, a) for (n2, p, a) in cf.calls
                  if n2 == cname or n2 == 'func_%08X' % c.target or n2.replace('__builtin_', '') == cname]
        # --- STACK_ARGS
        cov = []
        for k0, o0 in c.args.items():
            ee0 = e.get(k0)
            cov.append((o0, o0 + (max(ee0) if ee0 and max(ee0) else 16)))
        outgoing = [(o, op, sz) for (o, op, sz, si) in c.stores
                    if o not in an.loaded and o < 0x40 and not any(a0 <= o < b0 for a0, b0 in cov)]
        if outgoing and not libc:
            n = max(o // 8 for o, _, _ in outgoing) + 1
            # contiguous from slot 0
            slots = {o // 8 for o, _, _ in outgoing}
            n = 0
            while n in slots:
                n += 1
            used = callee_stackargs(c.target)
            if used is None or not used:
                n = 0
            else:
                n = min(n, max(used) + 1)
            if n:
                best = None
                for (n2, p, a) in ccalls:
                    dec = cf.decl.get(n2)
                    cnt = len(a)
                    if dec is not None and dec.strip() not in ('', 'void'):
                        ps = [x for x in re.split(r',(?![^(]*\))', dec) if x.strip()]
                        cnt_int = len(ps)
                        # call args beyond decl count also count (unprototyped)
                        cnt_int = max(cnt_int, 0)
                    else:
                        cnt_int = cnt
                    best = max(best or 0, cnt_int if dec else cnt, cnt)
                if ccalls and best < 8 + n:
                    rep.append(('HIGH', nm, 'STACK_ARGS', '%s @%X: asm guarda %d arg(s) de pila (%s) antes del jal; el C llama con %d parametros enteros (<%d)' % (
                        cname, c.idx, n, ','.join('0x%X' % o for o, _, _ in sorted(outgoing)), best, 8 + n)))
        # --- stack blocks passed
        for k, off in c.args.items():
            if off in an.saved or libc:
                continue
            need = 0
            if libc:
                if k in (0, 1) and 2 in c.imm:
                    need = c.imm[2]
            elif k in e:
                need = max(e[k])
            if need <= 0:
                continue
            cap_asm = an.save_min - off
            need_eff = min(need, cap_asm)
            if need_eff <= 4 and not libc:
                continue
            # C side
            res = []
            for (n2, p, a) in ccalls:
                if k < len(a):
                    r = resolve(cf.body[a[k][0]:a[k][1]], cf)
                    if r:
                        res.append(r)
            if not res:
                continue
            for (base, boff) in res:
                info = cf.loc[base]
                cap = info['size'] - boff
                # asm writes beyond cap?
                beyond = any(g * 4 >= off + cap for g in direct if off <= g * 4 < off + need_eff)
                wr, whole = c_written(cf, base, ext_of, {tuple(a[k]) for (n2, p, a) in ccalls if k < len(a)})
                # asm granules within block
                asm_g = {g - off // 4 for g in direct if off <= g * 4 < off + need_eff and min(direct[g]) < c.idx}
                rd_need = min(max(e[k][0] if k in e else 0, 0), need_eff) if not libc else 0
                # sub-block pointers passed to callees (asm) also write
                for c2 in an.calls:
                    if c2 is c:
                        continue
                    if c2.idx > c.idx:
                        continue
                    for k2, o2 in c2.args.items():
                        if off <= o2 < off + need_eff:
                            ee = callee_extents(c2.target) if c2.target else None
                            sz2 = 16
                            if LIBC.get(c2.name):
                                if k2 != 0 or 2 not in c2.imm:
                                    continue
                                sz2 = c2.imm[2]
                            elif ee is not None:
                                sz2 = ee[k2][1] if k2 in ee else 0
                                if k2 in passed.get(c2.target, ()):
                                    sz2 = 0x400
                            for g in range(o2 // 4, (o2 + sz2 + 3) // 4):
                                if off <= g * 4 < off + need_eff:
                                    asm_g.add(g - off // 4)
                if c.name in LIBC:
                    pass
                c_g = {g - boff // 4 for g in wr}
                if os.environ.get("CSDBG"): print("DBG", sorted(asm_g), sorted(c_g), whole)
                missing = sorted(g for g in asm_g if (g not in c_g) and 0 <= g < rd_need // 4)
                isblock = (any((off + 8 * j) in copy_dest for j in range(max(1, need_eff // 8))) or need_eff in (0x20, 0x30, 0x40, 0x80))
                det = '%s arg%d: asm bloque sp+0x%X (callee usa 0x%X, reserva asm 0x%X); C %s[%d]+0x%X cap=0x%X' % (
                    cname, k, off, need, cap_asm, base, info['size'], boff, cap)
                if cap < need_eff:
                    sev = 'HIGH' if (beyond or need in (0x10, 0x20, 0x30, 0x40, 0x80) and not libc) else 'MED'
                    rep.append((sev, nm, 'STACK_SHORT', det + '; asm escribe mas alla de la capacidad: %s' % beyond))
                if not whole and missing and not libc:
                    if not c_g and asm_g:
                        rep.append(('HIGH', nm, 'UNINIT_STACK', det + '; C no escribe nada en el bloque, asm rellena %d campos (rel ' % len(asm_g) + ','.join('0x%X' % (g * 4) for g in sorted(asm_g)[:12]) + ')'))
                    else:
                        cls = 'STRUCT_BY_VALUE' if isblock else 'UNFILLED'
                        rep.append(('HIGH' if isblock else 'MED', nm, cls, det + '; campos que el asm escribe y el C no (rel): ' + ','.join('0x%X' % (g * 4) for g in missing[:16])))

    # --- global: total aggregated locals vs asm address-taken region
    if an.taken:
        iv = []
        for t in sorted(an.taken):
            if t in an.saved:
                continue
            end = t + 4
            # contiguous direct accesses
            changed = True
            accs = [(off, sz) for (_, op, r, off, sz, store) in an.acc if off not in an.saved and off >= t]
            while changed:
                changed = False
                for off, sz in accs:
                    if off <= end and off + sz > end:
                        end = off + sz; changed = True
            for c in an.calls:
                for k, o in c.args.items():
                    if o == t:
                        e = callee_extents(c.target) if c.target else None
                        if LIBC.get(c.name) and 2 in c.imm:
                            end = max(end, t + c.imm[2])
                        elif e and k in e:
                            end = max(end, t + min(max(e[k]), an.save_min - t))
            iv.append((t, min(end, an.save_min)))
        iv.sort()
        tot = 0; cur = None
        for a, b in iv:
            if cur and a <= cur[1]:
                cur = (cur[0], max(cur[1], b))
            else:
                if cur:
                    tot += cur[1] - cur[0]
                cur = (a, b)
        if cur:
            tot += cur[1] - cur[0]
        if tot >= 24 and carr < 0.85 * tot and not cf.unknown_struct:
            rep.append(('LOW' if carr == 0 else 'MED', nm, 'STACK_SHORT', 'total: asm direccion-tomada abarca 0x%X bytes (%s), aggregados locales del C = 0x%X (%d%%)' % (
                tot, ','.join('0x%X' % t for t in sorted(an.taken)[:8]), carr, 100 * carr // tot)))


def main():
    args = sys.argv[1:]
    out = None
    d = os.path.join(ROOT, 'port/eq')
    files = []
    while args:
        a = args.pop(0)
        if a == '--out':
            out = args.pop(0)
        elif a == '--dir':
            d = args.pop(0)
        else:
            files.append(a)
    if not files:
        files = sorted(glob.glob(os.path.join(d, '*.c')))
    rep = []
    for f in files:
        m = re.match(r'^([0-9A-Fa-f]{6})\.c$', os.path.basename(f))
        if not m:
            continue
        try:
            check_file(f, int(m.group(1), 16), rep)
        except Exception as ex:
            print('ERR', f, ex, file=sys.stderr)
    order = {'HIGH': 0, 'MED': 1, 'LOW': 2}
    cl = {'STACK_SHORT': 0, 'UNINIT_STACK': 1, 'STRUCT_BY_VALUE': 2, 'STACK_ARGS': 3, 'UNFILLED': 4}
    seen = set(); rr = []
    for r in rep:
        if r in seen:
            continue
        seen.add(r); rr.append(r)
    rr.sort(key=lambda r: (order[r[0]], cl.get(r[2], 9), r[1]))
    lines = ['%s\t%s\t%s\t%s' % r for r in rr]
    cnt = collections.Counter((r[0], r[2]) for r in rr)
    hdr = '# check_stack: %d entradas; %s' % (len(rr), ', '.join('%s/%s=%d' % (a, b, n) for (a, b), n in sorted(cnt.items())))
    text = hdr + '\n# severidad\tfichero\tclase\tdetalle asm vs C\n' + '\n'.join(lines) + '\n'
    if out:
        open(out, 'w').write(text)
    else:
        sys.stdout.write(text)


if __name__ == '__main__':
    main()
