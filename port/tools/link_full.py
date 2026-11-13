#!/usr/bin/env python3
"""Enlaza el build 100 % nativo (docs/PLAN_NATIVO.md, etapa 3): port/build/full/bt2full.

Uso: port/tools/link_full.py [--no-link]      (después de port/tools/build_full.py)

Lee los objetos de port/build/gen/full/obj (los OK de report.csv), resuelve nombre->direccion PS2, y genera en
port/build/full/: obj2/ (copias de objetos con simbolos debilitados / renombrados), link.ld (alias y absolutos),
stubs.c, tables.c (direccion -> funcion nativa) y enlaza con port/full/*.c.  Todo se regenera de cero cada vez, asi
que tolera que los objetos cambien (otros agentes agregan C en port/eq/).
"""
import collections, csv, json, os, re, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "scripts"))
TRACE = bool(os.environ.get("BT2_TRACE_BUILD"))   # build instrumentado: ver build_full.py y port/full/plat_trace.c
GENDIR = ROOT / ("port/build/gen/full_trace" if TRACE else "port/build/gen/full")
OBJDIR = GENDIR / "obj"
OUT = ROOT / ("port/build/full_trace" if TRACE else "port/build/full")
if os.environ.get("BT2_FULL_OUT"):   # otro directorio de salida (AppImage: package/appimage/build.sh, enlace en contenedor)
    OUT = ROOT / os.environ["BT2_FULL_OUT"]
    OUT.mkdir(parents=True, exist_ok=True)
OVL_LO, OVL_HI = 0x3B3100, 0x421300
# stdio y afines: reciben FILE* del juego (struct de newlib), el libc del host no los entiende
STDIO = re.compile(r"^(f[a-z]+|_?[a-z]*printf|_?[a-z]*scanf|puts|putc|getc|putchar|getchar|setbuf|setvbuf|perror|exit|abort|_exit|atexit|signal|raise|malloc|free|calloc|realloc|memalign|brk|sbrk|sleep|usleep|time|clock|gettimeofday|open|read|write|close|lseek|stat|fstat|isatty|getenv|setenv|system|qsort_r)$")
FALLBACK = "--no-fallback" not in sys.argv   # relleno temporal (docs/agents/FALLBACK_SPEC.md): por defecto encendido
HEX = re.compile(r"^(func|D|jtbl)_([0-9A-Fa-f]{6,8})$")


def region(a):
    if a >= OVL_LO: return "overlay"
    if a < 0x2D0000: return "juego<2D0000"
    if a < 0x300000: return "2D0000-300000"
    if a < 0x33B5F8: return "SDK 300000-33B5F8"
    return "otra"


def name_addrs():
    """nombre -> direccion, de los mismos sitios que scripts/fdiff.py targets() mas bt3_names.csv."""
    import fdiff
    t = dict(fdiff.targets())
    fm = {}
    for row in (ROOT / "port/funcmap.csv").read_text().splitlines()[1:]:
        n, s, e, sz = row.split(",")
        fm[int(s, 16)] = (n, int(sz))
    names = {}
    p = ROOT / "build_port/bt3_names.csv"
    if p.exists():
        for r in csv.DictReader(p.open()):
            a = int(r["bt2_addr"], 16)
            names.setdefault(r["bt2_name"], a)
            bn = r["bt3_name"].split("|")
            if len(bn) == 1 and r["kind"] == "exact":
                names.setdefault(bn[0], a)
    for k, v in t.items():
        names[k] = v  # los archivos de simbolos mandan
    return names, fm


def nm_all(objs):
    defs, und = {}, collections.defaultdict(set)
    def one(chunk):
        r = subprocess.run(["nm", "-A", "-g", "--no-sort"] + [str(o) for o in chunk], capture_output=True, text=True).stdout
        return r
    chunks = [objs[i:i + 400] for i in range(0, len(objs), 400)]
    with ThreadPoolExecutor(2) as ex:
        outs = list(ex.map(one, chunks))
    for out in outs:
        for l in out.splitlines():
            f, rest = l.rsplit(".o:", 1)
            f = Path(f + ".o")
            p = rest.split()
            if len(p) == 2 and p[0] == "U":
                und[p[1]].add(f)
            elif len(p) == 3:
                defs.setdefault(p[2], []).append((f, p[1]))
    return defs, und


HOSTDEF = set()   # strong
TEMPDEF = set()   # weak (temp_stubs.c): se usan solo si ningun objeto define el simbolo   # simbolos definidos por port/full/plat_*.c (capa de plataforma): ganan a stubs


def host_syms():
    s = set()
    for lib in ("libc.so.6", "libm.so.6"):
        for d in ("/usr/lib", "/usr/lib64", "/lib/x86_64-linux-gnu"):
            if (Path(d) / lib).exists():
                s |= {l.split()[-1].split("@")[0] for l in subprocess.run(["nm", "-D", "--defined-only", str(Path(d) / lib)], capture_output=True, text=True).stdout.splitlines() if l.split()}
                break
    ga = subprocess.run(["gcc", "-print-libgcc-file-name"], capture_output=True, text=True).stdout.strip()
    s |= {l.split()[-1] for l in subprocess.run(["nm", "--defined-only", ga], capture_output=True, text=True).stdout.splitlines() if len(l.split()) == 3 and l.split()[1] in "TtDdRr"}
    # lo que define el propio port/full/*.c (compat.c: __divdi3...) cuenta como del host
    for c in sorted((ROOT / "port/full").glob("*.c")):
        o = OUT / "hostobj" / (c.stem + ".o")
        o.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(["gcc", "-c", "-w", "-O1", "-m64", "-fno-pie"] + (["-DBT2_FALLBACK"] if FALLBACK else []) + [str(c), "-o", str(o)], check=True)
        rows_ = [l.split() for l in subprocess.run(["nm", "-g", "--defined-only", str(o)], capture_output=True, text=True).stdout.splitlines() if len(l.split()) == 3]
        d = {r[-1] for r in rows_} - {"main"}
        s |= d
        if c.stem.startswith("plat_"): HOSTDEF.update(r[-1] for r in rows_ if r[1] != "W")
        TEMPDEF.update(r[-1] for r in rows_ if r[1] == "W")
    return s


FB_CXX = ["g++", "-std=c++20", os.environ.get("BT2_FB_OPT", "-O0"), "-msse4.2", "-w", "-fno-pie", "-fno-stack-protector", "-m64",
          "-I", str(ROOT / "port/full/recomp_shim"), "-I", str(ROOT / "port/build/recomp")]
DEF_RE = re.compile(r"^void (\w+)\(uint8_t\*\s*rdram", re.M)
CALL_RE = re.compile(r"\b(\w+_0x([0-9a-f]+))\(rdram, ctx, runtime\)")


def compile_one(args):
    src, o = args
    r = subprocess.run(["scripts/capped.sh", "3G"] + FB_CXX + ["-c", str(src), "-o", str(o)], cwd=ROOT, capture_output=True, text=True)
    return src, o, r


def build_fallback(fb, fm):
    """Compila (con cache por fecha) los .cpp de PS2Recomp de las funciones sin C y genera fallback_tbl.cpp (tabla de
    relleno + reenviadores para llamadas C++ directas a funciones que SI tienen C). Devuelve (objetos, fb final)."""
    FBD = OUT / "fallback"
    FBD.mkdir(parents=True, exist_ok=True)
    newest_shim = max(p.stat().st_mtime for p in (ROOT / "port/full/recomp_shim").glob("*.h"))   # cabeceras: recompila todo
    fbsym, fwd = {}, {}   # addr -> simbolo C++ ; simbolo -> addr (reenviadores)
    for a, (n, p) in fb.items():
        m = DEF_RE.search(p.read_text(errors="replace")[:4000])
        if m: fbsym[a] = m.group(1)
    todo = []
    for a in sorted(fbsym):
        p = fb[a][1]
        o = FBD / (p.stem + ".o")
        if not o.exists() or o.stat().st_mtime < max(p.stat().st_mtime, newest_shim):
            todo.append((p, o))
    print(f"relleno: {len(fbsym)} funciones sin C con C++ recompilado; {len(todo)} por compilar ({FB_CXX[3]})", flush=True)
    failed = set()
    if todo:
        with ThreadPoolExecutor(2) as ex:
            for i, (src, o, r) in enumerate(ex.map(compile_one, todo)):
                if r.returncode:
                    a = int(src.stem.rsplit("_0x", 1)[1], 16)
                    failed.add(a)
                    o.unlink(missing_ok=True)
                    print(f"  FALLO {src.name}: {(r.stderr.strip().splitlines() or ['?'])[0][:160]}", flush=True)
                if (i + 1) % 200 == 0: print(f"  compiladas {i + 1}/{len(todo)}", flush=True)
    for a in failed: fbsym.pop(a, None)
    # llamadas C++ directas (saltos de cola) a funciones que no estan en el relleno
    for a in sorted(fbsym):
        for m in CALL_RE.finditer(fb[a][1].read_text(errors="replace")):
            t = int(m.group(2), 16)
            if t != a and t not in fbsym: fwd[m.group(1)] = t
    L = ['// generado por port/tools/link_full.py (relleno temporal): tabla de funciones recompiladas sin C',
         '#include <cstdint>', 'struct R5900Context; class PS2Runtime;',
         'typedef void (*FbFn)(uint8_t *, R5900Context *, PS2Runtime *);',
         'extern "C" void bt2_forward(R5900Context *, uint32_t);',
         'struct FbFunc { uint32_t addr, end; FbFn fn; const char *name; };']
    L += [f'void {s}(uint8_t *, R5900Context *, PS2Runtime *);' for s in sorted(fbsym.values())]
    L += [f'void {s}(uint8_t *, R5900Context *ctx, PS2Runtime *) {{ bt2_forward(ctx, 0x{t:08X}u); }}' for s, t in sorted(fwd.items())]
    L += ['extern const FbFunc bt2_fb_funcs[] = {']
    L += [f'  {{0x{a:08X}u, 0x{a + fm[a][1]:08X}u, {fbsym[a]}, "{fb[a][0]}"}},' for a in sorted(fbsym)]
    L += ['  {0, 0, 0, 0}', '};', f'extern const uint32_t bt2_fb_n = {len(fbsym)};']
    tbl = FBD / "fallback_tbl.cpp"
    tbl.write_text("\n".join(L) + "\n")
    objs = [FBD / (fb[a][1].stem + ".o") for a in sorted(fbsym)]
    for src in (tbl, ROOT / "port/full/recomp_shim.cpp"):
        o = FBD / (src.stem + ".o")
        if not o.exists() or o.stat().st_mtime < max(src.stat().st_mtime, newest_shim):
            r = subprocess.run(FB_CXX[:2] + ["-O1"] + FB_CXX[3:] + ["-c", str(src), "-o", str(o)], capture_output=True, text=True)
            if r.returncode:
                print("FALLO " + src.name + ":\n" + r.stderr[:3000]); sys.exit(1)
        objs.append(o)
    return objs, {a: v for a, v in fb.items() if a in fbsym}, len(fwd), len(failed)


def build_renderer():
    """Renderer de Tenkaichi3Decomp (port/full/gs, etapa 5): shaders.h + gs/*.c + ui.cpp (ImGui) -> objetos en
    port/build/full/gs_obj (cache por fecha). Devuelve la lista de objetos. BT2_NO_GS=1 lo omite."""
    if os.environ.get("BT2_NO_GS"): return [], []
    GS = ROOT / "port/full/gs"
    GEN = OUT / "gen"
    OBJ = OUT / "gs_obj"
    OBJ.mkdir(parents=True, exist_ok=True)
    shaders = sorted((GS / "shaders").glob("*.*"))
    sh = GEN / "shaders.h"
    if not sh.exists() or sh.stat().st_mtime < max(s.stat().st_mtime for s in shaders):
        subprocess.run([sys.executable, str(ROOT / "port/tools/gen_shaders.py")], check=True)
    inc = ["-I", str(GS), "-I", str(GEN), "-I", str(ROOT / "port/third_party/imgui")]
    todo, objs = [], []
    TP = ROOT / "port/third_party/imgui"
    # gs/snd_adx.c / snd_se.c (sonido de BT3) quedan fuera: el sonido de BT2 es port/full/plat_snd_adx.c y plat_snd_se.c
    srcs = [(c, "gcc", ["-std=gnu11", "-O2"]) for c in sorted(GS.glob("*.c")) if c.name not in ("plat_settings_bt3.c", "snd_adx.c", "snd_se.c")]
    srcs += [(c, "g++", ["-std=c++17", "-O2"]) for c in [GS / "ui.cpp", *sorted(TP.glob("imgui*.cpp"))] if not c.name.startswith("imgui_impl_sdlgpu3_shaders")]
    for c, cc, fl in srcs:
        o = OBJ / (("im_" if c.parent == TP else "") + c.stem + ".o")
        objs.append(o)
        deps = [c] + list(GS.glob("*.h")) + [sh]
        if not o.exists() or o.stat().st_mtime < max(d.stat().st_mtime for d in deps):
            todo.append((cc, fl, c, o))
    def one(a):
        cc, fl, c, o = a
        r = subprocess.run(["scripts/capped.sh", "3G", cc, "-c", "-w", "-m64", "-fno-pie", "-g", *fl, *inc, "-DBT2_GS", str(c), "-o", str(o)], cwd=ROOT, capture_output=True, text=True)
        if r.returncode: print("FALLO " + c.name + ":\n" + r.stderr[-1500:]); sys.exit(1)
    with ThreadPoolExecutor(2) as ex: list(ex.map(one, todo))
    print(f"renderer: {len(srcs)} fuentes, {len(todo)} compiladas")
    return objs, (subprocess.run(["pkg-config", "--libs", "sdl3"], capture_output=True, text=True).stdout.split() or ["-lSDL3"])


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    (OUT / "obj2").mkdir(exist_ok=True)
    rows = list(csv.reader((GENDIR / "report.csv").open()))[1:]
    objs = []
    for r in rows:
        if r[1] == "OK":
            o = OBJDIR / (r[0].replace("/", "__")[:-2] + ".o")
            if o.exists(): objs.append(o)
    names, fm = name_addrs()
    SYMD = {}
    for f_ in sorted((ROOT / "config").glob("symbol_addrs*.txt")) + sorted((ROOT / "config/symbols").glob("*.txt")):
        for l_ in f_.read_text().splitlines():
            m_ = re.match(r"(D_([0-9A-Fa-f]{6,8})) = 0x([0-9A-Fa-f]+);", l_)
            if m_ and int(m_.group(2), 16) != int(m_.group(3), 16): SYMD[m_.group(1)] = int(m_.group(3), 16)
    defs, und = nm_all(objs)
    print(f"{len(objs)} objetos, {len(defs)} simbolos globales definidos, {len(und)} indefinidos distintos")

    def addr_of(n):
        if n.startswith("D_") and n in SYMD: return SYMD[n]   # D_<hex> de un archivo de simbolos cuya direccion NO es la del nombre (D_002C3550 = 0x340070)
        m = HEX.match(n)
        if m: return int(m.group(2), 16)
        return names.get(n)

    # --- 1. direccion canonica de cada funcion definida
    per_obj = collections.defaultdict(list)
    for n, lst in defs.items():
        for f, t in lst:
            if t in "TtWw": per_obj[f].append(n)
    cand = collections.defaultdict(list)   # addr -> [(prio, obj, sym)]
    noaddr = []
    for f, syms in per_obj.items():
        prio = 0 if f.name.startswith("src__") else 1
        stem = None
        if f.name.startswith("port__eq__"):
            try: stem = int(f.stem.split("__")[-1], 16)
            except ValueError: pass
        rs = {s: addr_of(s) for s in syms}
        if stem is not None and stem not in rs.values():
            un = [s for s, a in rs.items() if a is None]
            if len(un) == 1: rs[un[0]] = stem
            elif len(syms) == 1: rs[syms[0]] = stem
        for s, a in rs.items():
            if a is None: noaddr.append((f.name, s)); continue
            cand[a].append((prio, f.name, s, f))
    canon = {}          # addr -> (sym, obj)
    for a, lst in cand.items():
        lst.sort(key=lambda x: (x[0], x[1]))
        canon[a] = (lst[0][2], lst[0][3])
    sym2addr = {s: a for a, (s, _) in canon.items()}

    # --- duplicados por nombre: gana src/ sobre eq/
    weaken = collections.defaultdict(set)
    ndup = 0
    for n, lst in defs.items():
        if len(lst) > 1:
            ndup += 1
            lst2 = sorted(lst, key=lambda x: (0 if x[0].name.startswith("src__") else 1, x[0].name))
            for f, t in lst2[1:]: weaken[f].add(n)
    global GS_OBJS, GS_LIBS
    GS_OBJS, GS_LIBS = build_renderer()
    for o in GS_OBJS:   # gs_sony.c define sceGs* del SDK: cuentan como capa de plataforma (ganan a los stubs)
        if o.name == "gs_sony.o":
            HOSTDEF.update(l.split()[-1] for l in subprocess.run(["nm", "-g", "--defined-only", str(o)], capture_output=True, text=True).stdout.splitlines() if len(l.split()) == 3)
    host0 = host_syms()   # (llena HOSTDEF)
    for n in HOSTDEF:     # la capa plat_* manda sobre cualquier C que defina el mismo simbolo
        for f, t in defs.get(n, []): weaken[f].add(n)
    # --- datos definidos con direccion -> absolutos
    redef = collections.defaultdict(dict)
    absolutes = {}
    for n, lst in defs.items():
        for f, t in lst:
            if t not in "TtWw":
                a = addr_of(n)
                if a is not None:
                    redef[f][n] = "__dup_" + n
                    absolutes[n] = a
    # simbolos del juego que chocan con los del host (main, malloc, free...: los pisarian dentro de libc): se
    # renombran a game_X en definicion y en cada referencia
    ren = {n: "game_" + n for n in defs if (n in host0 and n not in HOSTDEF) or n == "main"}
    for n, m in ren.items():
        for f in {x for x, _ in defs[n]} | und.get(n, set()):
            redef[f][n] = m
    R = lambda n: ren.get(n, n)
    # --- indefinidos
    host = host_syms()
    alias, stubs, hostres, unknown = {}, {}, [], []
    hostaddr = {}
    hostbyaddr = {}   # direccion -> simbolo del host (otro nombre del mismo punto de entrada: alias)
    for h in HOSTDEF | TEMPDEF:
        ha = addr_of(h)
        if ha is not None and ha not in canon: hostbyaddr.setdefault(ha, h)
    defined = set(defs)
    for n in sorted(und):
        if n in defined or n in absolutes: continue
        a = addr_of(n)
        if n not in HOSTDEF and n not in TEMPDEF and not STDIO.match(n) and a is not None and a in hostbyaddr and hostbyaddr[a] != n:   # stdio nativo = host (ABI x86); la version EE va solo por direccion
            alias[n] = (hostbyaddr[a], a)
            hostaddr[a] = hostbyaddr[a]
            continue
        if n in HOSTDEF or n in TEMPDEF:          # definido por la capa plat_*: no es stub ni alias
            hostres.append(n)
            if a is not None and a not in canon: hostaddr[a] = n
            continue
        isfunc = n.startswith("func_") or (a in fm if a is not None else False)
        if a is not None and a in canon and isfunc is not False or (a in canon):
            alias[n] = (R(canon[a][0]), a)
        elif n in host and (a is None or not n.startswith(("func_", "D_"))) and not (a is not None and not isfunc):
            hostres.append(n)
        elif a is None:
            if n in host: hostres.append(n)
            else: unknown.append(n); stubs[n] = 0
        elif isfunc:
            stubs[n] = a
        else:
            absolutes[n] = a
    # --- funciones de libc/libm del SDK que PS2Recomp conoce por nombre (memset_0x3251dc.cpp...): el codigo recompilado las
    # llama por su direccion PS2; se mapean a la del host (mismo nombre) y los stubs por nombre pasan a alias.
    libc_addr = {}
    for p_ in (ROOT / "port/build/recomp").glob("*_0x*.cpp"):
        nm, _, ad = p_.stem.rpartition("_0x")
        if nm and nm in host and not HEX.match(nm) and not STDIO.match(nm) and nm not in HOSTDEF and nm not in TEMPDEF and nm != "main":
            try: libc_addr[int(ad, 16)] = nm
            except ValueError: pass
    nlibc = 0
    for n, a in list(stubs.items()):
        if a in libc_addr and a not in canon:
            alias[n] = (libc_addr[a], a); del stubs[n]; nlibc += 1
    libc_used = {a: nm for a, nm in libc_addr.items() if a not in canon and a not in hostaddr}
    for a, nm in libc_used.items(): hostaddr[a] = "bt2l_" + nm   # envoltorio local (el jmp rel32 de full_patch_range no llega a libc)
    # --- copias de objetos modificadas
    mod = {}
    todo = set(weaken) | set(redef)
    for f in todo:
        o2 = OUT / "obj2" / f.name
        cmd = ["objcopy"]
        for n in sorted(weaken.get(f, ())): cmd += ["--weaken-symbol", n]
        for n, m in redef.get(f, {}).items(): cmd += ["--redefine-sym", f"{n}={m}"]
        subprocess.run(cmd + [str(f), str(o2)], check=True)
        mod[f] = o2
    final = [str(mod.get(o, o)) for o in objs]
    # --- link.ld
    ld = ["/* generado por port/tools/link_full.py */"]
    ld += [f"{n} = 0x{a:08X};" for n, a in sorted(absolutes.items())]
    ld += [f"{n} = {s};" for n, (s, a) in sorted(alias.items())]
    (OUT / "link.ld").write_text("\n".join(ld) + "\n")
    # --- stubs.c (referenciados) + extra por funcmap sin codigo nativo
    tbl = {}   # addr -> simbolo
    for a, (s, f) in canon.items(): tbl[a] = R(s)
    for a, n in hostaddr.items(): tbl[a] = n
    for n in HOSTDEF | TEMPDEF:   # plat_* que el juego no referencia por nombre pero tienen direccion: tambien al jmp
        a = addr_of(n)
        if a is not None and a not in tbl and a in fm: tbl[a] = n
    stubsym = {}
    for n, a in stubs.items():
        if a and a in tbl: continue
        if a: stubsym.setdefault(a, n)
    extra = []
    for a, (n, sz) in fm.items():
        if a in tbl or a in stubsym: continue
        stubsym[a] = f"func_{a:08X}" if f"func_{a:08X}" not in defined and f"func_{a:08X}" not in stubs else f"stubx_{a:08X}"
        extra.append(a)
    for a, s in stubsym.items(): tbl[a] = s
    GAME_END = 0x30C7B8   # por encima empieza el SDK / libc / libm (lo de abajo es C del juego + CRI que aun no existe)
    thunks = 0
    fb, fb_objs, nfwd, nfail = {}, [], 0, 0   # addr -> (simbolo, archivo .cpp): funciones sin C que corre el relleno (PS2Recomp)
    if FALLBACK:
        rc = {}
        for p in (ROOT / "port/build/recomp").glob("*_0x*.cpp"):
            try: rc[int(p.stem.rsplit("_0x", 1)[1], 16)] = p
            except ValueError: pass
        # SDK/libc/libm (>= GAME_END): solo las "puras" (sin syscall ni acceso a registros de hardware): el resto sigue
        # siendo un stub que corta (hay que escribir su plat_*).
        hw = re.compile(r"handleSyscall|\(uint32_t\)(4[01]\d\d|42\d\d|43\d\d|44\d\d|45\d\d|46[01]\d|8128|28672) << 16")
        for a, n in stubsym.items():
            if n in HOSTDEF or n in TEMPDEF or a not in rc: continue
            txt = rc[a].read_text(errors="replace")
            if "ps2_stubs::" in txt: thunks += 1; continue   # PS2Recomp no recompilo esta (sceSif*, sceVu0*...): llama a su runtime
            if a < GAME_END or a >= OVL_LO or not hw.search(txt):
                fb[a] = (n, rc[a])
        fb_objs, fb, nfwd, nfail = build_fallback(fb, fm)
    sl = ['/* generado por port/tools/link_full.py: una funcion por simbolo que el juego usa y no tiene C */',
          'extern long full_stub(const char *name, unsigned addr);',
          'extern long full_stub_game(const char *name, unsigned addr);']
    def stubline(n, a):
        if a in fb:   # adaptador nativo -> funcion recompilada (recomp_shim.cpp: bt2_fb_entry)
            return f'__asm__(".text\\n.globl {n}\\n.type {n},@function\\n{n}:\\nmovl $0x{a:08X},%r11d\\njmp bt2_fb_entry\\n");\nextern void {n}(void);'
        return f'long {n}(void) {{ return full_stub{"_game" if a < GAME_END or a >= OVL_LO else ""}("{n}", 0x{a:08X}u); }}'
    stub_names = {}
    for n, a in sorted(stubs.items()):
        sl.append(stubline(n, a))
    for a in extra:
        n = stubsym[a]
        if n not in stubs:
            sl.append(stubline(n, a))
    for a, nm in sorted(libc_used.items()):
        sl.append(f'__asm__(".text\\n.globl bt2l_{nm}\\n.type bt2l_{nm},@function\\nbt2l_{nm}:\\njmp {nm}@PLT\\n");')
    (OUT / "stubs.c").write_text("\n".join(sl) + "\n")
    # lista de funciones DEL JUEGO con stub temporal (devuelven 0): se regenera en cada enlace
    gl = sorted((a, n) for a, n in stubsym.items() if (a < GAME_END or a >= OVL_LO) and n not in HOSTDEF and n not in TEMPDEF)
    (ROOT / "port/full/TEMP_STUBS_AUTO.txt").write_text(
        "# generado por port/tools/link_full.py: funciones del JUEGO (no SDK) sin C que el enlace cubre con un stub que\n"
        "# devuelve 0 (full_stub_game en port/full/mem.c; BT2_STUB_STRICT=1 las convierte en error). Motivo comun: aun sin C\n"
        "# (batch 10 / overlay DBZP.BIN). Desaparecen solas cuando exista el C. %d funciones; %d de ellas se referencian.\n" % (len(gl), sum(1 for a, n in gl if n in stubs))
        + "".join(f"{a:08X} {n}{'' if n in stubs else '  (solo en la tabla de punteros)'}\n" for a, n in gl))
    # --- tables.c
    tl = ['/* generado por port/tools/link_full.py */', 'typedef unsigned u32;', 'typedef struct { u32 addr; void (*fn)(void); } FullFunc;']
    allsyms = sorted(set(tbl.values()))
    tl += [f'extern void {s}(void);' for s in allsyms]
    tl += ['const FullFunc full_funcs[] = {'] + [f'  {{0x{a:08X}u, {s}}},' for a, s in sorted(tbl.items())] + ['  {0, 0}', '};']
    tl.append(f'const u32 full_nfuncs = {len(tbl)};')
    (OUT / "tables.c").write_text("\n".join(tl) + "\n")
    # --- informe
    reg = collections.Counter
    rep = {
        "objetos": len(objs), "duplicados_debilitados": ndup,
        "canonicas": len(canon), "sin_direccion": len(noaddr),
        "alias": len(alias), "absolutos": len(absolutes), "stubs_ref": len(stubs), "stubs_extra_tabla": len(extra),
        "host": len(hostres), "desconocidos": len(unknown),
        "stubs_ref_por_region": dict(reg(region(a) for a in stubs.values() if a)),
        "absolutos_por_region": dict(reg(region(a) for a in absolutes.values())),
        "alias_por_region": dict(reg(region(a) for _, a in alias.values())),
        "relleno": len(fb), "relleno_por_region": dict(reg(region(a) for a in fb)), "relleno_reenviadores": nfwd,
        "relleno_fallo_compilar": nfail, "sin_relleno_thunk_de_runtime_PS2Recomp": thunks,
        "sin_C_ni_relleno": len([1 for a, n in stubsym.items() if (a < GAME_END or a >= OVL_LO) and n not in HOSTDEF and n not in TEMPDEF and a not in fb]),
        "sdk_con_stub_que_corta": len([1 for a, n in stubsym.items() if GAME_END <= a < OVL_LO and n not in HOSTDEF and n not in TEMPDEF and a not in fb]),
    }
    if FALLBACK:
        (ROOT / "port/full/FALLBACK_AUTO.txt").write_text(
            "# generado por port/tools/link_full.py: funciones del JUEGO sin C que corren por el RELLENO TEMPORAL (C++ de PS2Recomp en\n"
            "# bt2full, port/full/recomp_shim.cpp). %d funciones; esa cifra tiene que bajar a 0. Se apaga con link_full.py --no-fallback.\n" % len(fb)
            + "".join(f"{a:08X} {v[0]:<32} {region(a)}\n" for a, v in sorted(fb.items())))
    (OUT / "report.json").write_text(json.dumps({**rep, "hostres": hostres, "unknown": unknown, "stubs": {k: f"0x{v:08X}" for k, v in stubs.items()}, "noaddr": noaddr[:500]}, indent=1))
    print(json.dumps(rep, indent=1))
    if "--no-link" in sys.argv: return
    cflags = ["-O1", "-g", "-w", "-m64", "-fno-pie", "-fno-omit-frame-pointer", "-fno-stack-protector"]
    hostc = sorted(str(p) for p in (ROOT / "port/full").glob("*.c"))
    gs_objs, gs_libs = GS_OBJS, GS_LIBS
    hostc += [str(ROOT / "port/full/gs/plat_settings_bt3.c")] if gs_objs else []
    exe = OUT / "bt2full"
    cmd = ["gcc", "-no-pie", "-m64", "-w", "-g", "-O1", "-o", str(exe), *hostc, str(OUT / "stubs.c"), str(OUT / "tables.c"),
           *final, str(OUT / "link.ld"), "-Wl,-Ttext-segment=0x40000000", "-Wl,--allow-multiple-definition" if False else "-Wl,-z,noexecstack",
           *map(str, fb_objs), *(["-DBT2_FALLBACK"] if FALLBACK else []),
           *map(str, gs_objs), *gs_libs, "-rdynamic", "-lavformat", "-lavcodec", "-lswscale", "-lavutil", "-lm", "-lpthread", "-lstdc++", f"-Wl,-Map={exe}.map"]
    cmd = ["scripts/capped.sh", "6G"] + cmd
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    errs = [l for l in r.stderr.splitlines() if "multiple definition" in l or "undefined reference" in l or "rror" in l]
    (OUT / "link.log").write_text(r.stderr)
    print(f"enlace {'OK -> ' + str(exe.relative_to(ROOT)) if r.returncode == 0 else 'FALLO'}; {len(errs)} lineas de error")
    for l in errs[:15]: print("  " + l[-200:])
    sys.exit(r.returncode)


main()
