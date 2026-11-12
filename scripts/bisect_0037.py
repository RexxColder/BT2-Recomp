#!/usr/bin/env python3
"""Biseccion de las pasadas de cambios del 2026-10-23 (tarde) entre el estado de las 00:37 y el final.

Cadena de versiones de cada fichero (cada respaldo es el contenido ANTES de la pasada siguiente):
  src/auto/m2c_*  : 00:37 (arity_fix o el primero que haya) -> arity -> m2c_pre_fwd -> fwd -> m2c_pre_emp
                    -> emp -> src_pre_emp2 -> emp2 -> final (BT2-backups/pre_restore_0037)
  src/auto/auto_* : auto_pre_fwd -> fwd -> src_pre_emp2 -> emp2 -> final
  resto de src/   : src_pre_emp2 -> emp2 -> final
  port/eq/*       : 00:37 -> eq -> final
Pasadas, en orden: arity, fwd, emp, emp2, eq.

Uso: scripts/bisect_0037.py PASADA [--files N0:N1] [--apply]
  Deja cada fichero en la version posterior a PASADA (incluida) y anteriores; las siguientes no se aplican.
  --files N0:N1 aplica la pasada PASADA solo a los ficheros [N0,N1) de su lista ordenada (biseccion dentro de una
  pasada); los de fuera quedan en la version anterior a esa pasada.
  Sin --apply solo informa cuantos ficheros cambiarian. Cambia mtimes: build_full recompila lo tocado.
"""
import os
import shutil
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BK = ROOT.parent / "BT2-backups"
FULL = ROOT.parents[1] / "BT2-Port-FULL/home-Escritorio/BT2-Recomp"
PASSES = ["arity", "fwd", "emp", "emp2", "eq"]
KEEP_EQ = {"port/eq/26C7A8.c"}   # arreglo de reenvio de a2 (crash de menus con clang 22): fijo en su version final en todos los estados


def ex(p):
    return p if p and p.exists() else None


def chain(rel):
    """[(pasada que lleva a esta version o None para la base, ruta)] en orden."""
    name = Path(rel).name
    final = BK / "pre_restore_0037" / rel
    if rel.startswith("src/auto/m2c_"):
        v = [(None, ex(BK / "arity_fix" / name)), ("arity", ex(BK / "m2c_pre_fwd" / name)),
             ("fwd", ex(BK / "m2c_pre_emp" / name)), ("emp", ex(BK / "src_pre_emp2" / rel)), ("emp2", ex(final))]
    elif rel.startswith("src/auto/auto_"):
        v = [(None, ex(BK / "auto_pre_fwd" / name)), ("fwd", ex(BK / "src_pre_emp2" / rel)), ("emp2", ex(final))]
    elif rel.startswith("src/"):
        v = [(None, ex(BK / "src_pre_emp2" / rel)), ("emp2", ex(final))]
    elif rel.startswith("port/eq/"):
        v = [(None, ex(BK / "base_0037" / rel)), ("eq", ex(final))]
    else:
        return []
    out, last = [], None
    for p, path in v:   # una version que falta = igual a la anterior
        path = path or last
        out.append((p, path))
        last = path
    return out


def main():
    target = sys.argv[1]
    k = PASSES.index(target)
    rng = None
    if "--files" in sys.argv:
        a, b = sys.argv[sys.argv.index("--files") + 1].split(":")
        rng = (int(a), int(b))
    files = sorted(str(p.relative_to(BK / "pre_restore_0037")) for p in (BK / "pre_restore_0037").rglob("*.c"))
    # ficheros que la pasada target cambia de verdad (para --files)
    def ver(rel, upto):
        cur = None
        for p, path in chain(rel):
            if p is None or PASSES.index(p) <= upto:
                cur = path if path is not None else cur
        return cur
    touched_by_target = [r for r in files if r not in KEEP_EQ and chain(r) and
                         ver(r, k) and ver(r, k - 1) and ver(r, k).read_bytes() != ver(r, k - 1).read_bytes()]
    print(f"pasada {target}: cambia {len(touched_by_target)} ficheros")
    sel = set(touched_by_target[rng[0]:rng[1]]) if rng else set(touched_by_target)
    n = 0
    for rel in files:
        if rel in KEEP_EQ or not chain(rel):
            continue
        want = ver(rel, k if (rel in sel or rel not in touched_by_target) else k - 1)
        if want is None:   # port/eq en la base: la base es la copia restaurada (BT2-backups/base_0037)
            want = BK / "base_0037" / rel
        dst = ROOT / rel
        if not want.exists():
            continue
        if dst.read_bytes() != want.read_bytes():
            n += 1
            if "--apply" in sys.argv:
                shutil.copyfile(want, dst)
                os.utime(dst, None)
    print(f"ficheros a cambiar en el arbol: {n}" + (" (aplicado)" if "--apply" in sys.argv else ""))
    if rng:
        print("seleccion:", rng, "de", len(touched_by_target), "->", sorted(sel)[:3], "...")


if __name__ == "__main__":
    main()
