#!/usr/bin/env python3
"""Barrido de coherencia de declaraciones: cada `func_X`/nombre simbolico se compara entre su DEFINICION (src/**, port/eq, port/full) y
todas las DECLARACIONES de los demas ficheros. Clases de problema (todas rompen el ABI x86-64 al compilar cada fichero por separado):
  RET_CLASS   retorno de otra clase (int32 / int64 / f32 / f64 / void / puntero) o retorno estrecho (s8/u8/s16/u16) declarado ancho
  PARAM_CLASS un parametro de otra clase (int vs f32 vs f64 vs 64 bits): f32 viaja en xmm y los enteros en registros generales
  PARAM_COUNT la declaracion tiene menos parametros que la definicion (los que faltan llegan con basura)
Uso: check_decls.py > informe"""
import re, glob, collections, sys
def cls(t):
    t = re.sub(r'\b(const|volatile|register|extern|static|__ptr32|__uptr)\b', '', t).strip()
    t = re.sub(r'\s+', ' ', t)
    if '*' in t or '[' in t: return 'ptr'
    if t in ('f32','float'): return 'f32'
    if t in ('f64','double'): return 'f64'
    if t in ('s64','u64','long long','unsigned long long','long','unsigned long','s64 ','u128','s128'): return 'i64'
    if t in ('void',): return 'void'
    if t in ('s8','u8','char','signed char','unsigned char'): return 'n8'
    if t in ('s16','u16','short','unsigned short'): return 'n16'
    if t in ('s32','u32','int','unsigned int','unsigned','bool','_Bool','enum'): return 'i32'
    return 'other:' + t
def params(s):
    s = s.strip()
    if s in ('', 'void'): return []
    out = []
    for p in split_args(s):
        p = p.strip()
        if p == '...': out.append('var'); continue
        # quitar el nombre del parametro
        m = re.match(r'^(.*?)(\w+)(\s*\[[^\]]*\])?\s*$', p)
        typ = p
        if m and m.group(1).strip() and not re.match(r'^(const|struct|unsigned|signed)$', m.group(2)):
            typ = m.group(1) + (m.group(3) or '')
        if re.search(r'\(\s*\*', p): typ = '*'
        out.append(cls(typ))
    return out
def split_args(s):
    d = 0; cur = ''; res = []
    for ch in s:
        if ch == '(': d += 1
        if ch == ')': d -= 1
        if ch == ',' and d == 0: res.append(cur); cur = ''
        else: cur += ch
    res.append(cur); return res
sig = re.compile(r'^(?:extern\s+|static\s+)*((?:const\s+)?[A-Za-z_][\w\s\*]*?)\s+\**\s*([A-Za-z_]\w*)\s*\(([^;{}()]*(?:\([^()]*\)[^;{}()]*)*)\)\s*(;|\{)', re.M)
defs = {}; decls = collections.defaultdict(list)
files = glob.glob('src/**/*.c', recursive=True) + glob.glob('port/eq/*.c') + glob.glob('port/full/*.c')
for f in files:
    t = open(f, errors='ignore').read()
    t = re.sub(r'/\*.*?\*/', '', t, flags=re.S); t = re.sub(r'//[^\n]*', '', t)
    for m in sig.finditer(t):
        ret, name, ps, end = m.group(1).strip(), m.group(2), m.group(3), m.group(4)
        if ret.split()[-1] in ('return', 'else', 'if', 'while', 'switch', 'sizeof'): continue
        full = m.group(0)
        stars = '*' if re.search(r'\*\s*' + re.escape(name) + r'\s*\(', full) else ''
        rc = cls(ret + stars)
        rec = (f, rc, params(ps), ret)
        if end == '{':
            if name not in defs or f.startswith('port/eq'): defs[name] = rec
        else:
            decls[name].append(rec)
rows = []
INT = {'i32', 'ptr', 'n8', 'n16'}
def seqs(ps):
    ints = [('i64' if c == 'i64' else 'i32') for c in ps if c in INT or c == 'i64']
    fl = [c for c in ps if c in ('f32', 'f64')]
    return ints, fl
for name, d in defs.items():
    df, drc, dps, dret = d
    for (f, rc, ps, ret) in decls.get(name, []):
        if f == df: continue
        probs = []
        # retorno
        if drc == 'void' and rc != 'void':
            probs.append('RET_VOID_DEF decl=%s (la definicion no devuelve nada: el llamador lee basura)' % rc)
        elif drc in ('f32', 'f64') and rc != drc:
            probs.append('RET_FLOAT def=%s decl=%s' % (drc, rc))
        elif drc in INT | {'i64'} and rc in ('f32', 'f64'):
            probs.append('RET_FLOAT def=%s decl=%s' % (drc, rc))
        elif drc in INT and rc == 'i64':
            probs.append('RET_WIDE def=%s decl=i64 (bits altos indefinidos)' % drc)
        # parametros
        if 'var' not in dps and 'var' not in ps:
            di, df_ = seqs(dps); ci, cf = seqs(ps)
            if len(cf) < len(df_):
                probs.append('PARAM_FLOAT_COUNT def=%d decl=%d' % (len(df_), len(cf)))
            for k in range(min(len(cf), len(df_))):
                if cf[k] != df_[k]: probs.append('PARAM_FLOAT_TYPE #%d def=%s decl=%s' % (k, df_[k], cf[k])); break
            if len(ci) < len(di):
                probs.append('PARAM_INT_COUNT def=%d decl=%d' % (len(di), len(ci)))
            for k in range(min(len(ci), len(di))):
                if ci[k] != di[k]: probs.append('PARAM_INT_WIDTH #%d def=%s decl=%s' % (k, di[k], ci[k])); break
        for pr in probs:
            rows.append((pr.split()[0], name, df, f, pr))
order = {'RET_FLOAT': 0, 'PARAM_FLOAT_TYPE': 1, 'PARAM_FLOAT_COUNT': 2, 'RET_VOID_DEF': 3, 'PARAM_INT_WIDTH': 4, 'RET_WIDE': 5, 'PARAM_INT_COUNT': 6}
rows.sort(key=lambda r: (order.get(r[0], 9), r[1], r[3]))
cnt = collections.Counter(r[0] for r in rows)
print('# check_decls: %d definiciones, %d hallazgos %s' % (len(defs), len(rows), dict(cnt)))
for r in rows: print('%s\t%s\tdef:%s\tdecl:%s\t%s' % (r[0], r[1], r[2], r[3], r[4]))
