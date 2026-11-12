#!/usr/bin/env python3
"""Las funciones definidas con retorno s8/u8/s16/u16 no garantizan los bits altos de eax en x86-64 (clang devuelve p.ej.
movzx eax,word [..] para un s16 -1 = 0xFFFF). Los llamadores que declaran el prototipo como s32 leen basura (bug: ADXF_OpenAfs(1,132962)).
Arreglo en la definicion: el tipo de retorno pasa a s32 y cada `return E;` pasa a `return (T)(E);` (T = el tipo estrecho original),
con lo que el valor llega extendido a 32 bits segun su signo. Uso: widen_narrow_returns.py [--apply] <ficheros...>"""
import re, sys, shutil, os
NARROW = {'s8','u8','s16','u16','signed char','unsigned char','short','unsigned short','char'}
CAST = {'char':'s8','signed char':'s8','unsigned char':'u8','short':'s16','unsigned short':'u16'}
head = re.compile(r'^(s8|u8|s16|u16|signed char|unsigned char|short|unsigned short)\s+((?:func_[0-9A-Fa-f]{8})|[A-Za-z_]\w*)\s*\(', re.M)

def match_close(t, i, o, c):
    d = 0
    while i < len(t):
        if t[i] == o: d += 1
        elif t[i] == c:
            d -= 1
            if d == 0: return i
        i += 1
    return -1

def process(path):
    t = open(path, errors='surrogateescape').read()
    out = []; pos = 0; n = 0
    for m in head.finditer(t):
        if m.start() < pos: continue
        pe = match_close(t, m.end() - 1, '(', ')')
        if pe < 0: continue
        j = pe + 1
        while j < len(t) and t[j] in ' \t\r\n': j += 1
        if j >= len(t) or t[j] != '{': continue          # prototipo
        be = match_close(t, j, '{', '}')
        if be < 0: continue
        T = CAST.get(m.group(1), m.group(1))
        body = t[j:be + 1]
        def fix(mm):
            e = mm.group(1).strip()
            return 'return (%s)(%s);' % (T, e)
        body2, k = re.subn(r'\breturn\s+([^;]+);', fix, body)
        out.append(t[pos:m.start()]); out.append('s32 ' + t[m.start() + len(m.group(1)):j] + body2)
        pos = be + 1; n += 1
    out.append(t[pos:])
    return ''.join(out), n

if __name__ == '__main__':
    apply = '--apply' in sys.argv
    tot = 0
    import glob
    files = [a for a in sys.argv[1:] if not a.startswith('--')]
    if not files:
        files = sorted(glob.glob('src/**/*.c', recursive=True) + glob.glob('port/eq/*.c') + glob.glob('port/full/*.c'))
    for p in files:
        if not os.path.isfile(p):
            continue
        new, n = process(p)
        if n:
            tot += n
            print(p, n)
            if apply:
                shutil.copy(p, os.path.expanduser('~/Escritorio/BT2-backups/narrow_ret/') + p.replace('/', '__'))
                open(p, 'w', errors='surrogateescape').write(new)
    print('definiciones:', tot)
