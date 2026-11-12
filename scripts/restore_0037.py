#!/usr/bin/env python3
"""Reconstruye las fuentes al estado del binario del 2026-10-23 00:37 (BT2-backups/bt2full_20261023_0037).

Cada fichero fuente modificado despues de las 00:37 se reemplaza por su copia de respaldo MAS TEMPRANA posterior a
esa hora (= su contenido antes del primer cambio de la tarde). Las pasadas de cambios del 23-oct, en orden:
  arity_fix (03:31) < mem.c.pre_trace (04:34) < 26C7A8.c.pre_a2 (04:50) < *.pre_a1 (12:11) < 26D6A0.c.pre_dbg (12:31)
  < auto_pre_fwd (12:39) < m2c_pre_fwd (12:45) < m2c_pre_emp (13:03) < src_pre_emp2 (13:10)
Lo que se reemplaza se guarda antes en BT2-backups/pre_restore_0037/ (misma ruta relativa).

Uso: scripts/restore_0037.py [--apply]     (sin --apply solo informa)
"""
import os
import shutil
import sys
from datetime import datetime
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BK = ROOT.parent / "BT2-backups"
T0037 = datetime(2026, 10, 23, 0, 37, 21).timestamp()
KEEP = {  # capa de plataforma con el logging nuevo y el control por archivo: se mantienen
    "port/full/plat_fightlog.c", "port/full/plat_trace.c", "port/full/plat_gs.c", "port/full/gs/gs_input.c",
}


def candidates(rel):
    """Copias 'antes del cambio' de rel, en orden cronologico."""
    name = Path(rel).name
    stem = Path(rel).stem
    c = []
    if rel.startswith("src/auto/m2c_"):
        c.append(BK / "arity_fix" / name)
    if rel == "port/full/mem.c":
        c.append(BK / "mem.c.pre_trace")
    if rel.startswith("port/eq/"):
        c += [BK / f"{stem}.c.pre_a2", BK / f"{stem}.c.pre_a1", BK / f"{stem}.c.pre_dbg"]
    if rel.startswith("src/auto/auto_"):
        c.append(BK / "auto_pre_fwd" / name)
    if rel.startswith("src/auto/m2c_"):
        c += [BK / "m2c_pre_fwd" / name, BK / "m2c_pre_emp" / name]
    if rel.startswith("src/"):
        c.append(BK / "src_pre_emp2" / rel)
    if rel == "port/eq/11ADA0.c":   # stack_fix, 00:56
        c.append(ROOT / "BT2-backups/stack_fix/11ADA0.c.orig")
    if rel in ("port/eq/2113C0.c", "port/eq/268F60.c", "port/eq/273B80.c", "port/eq/2746C0.c", "port/eq/29E6D0.c",
               "port/eq/2A13E8.c"):
        # sin respaldo propio: la copia completa del 21-oct (su diferencia con la actual es solo el cambio de la tarde)
        c.append(ROOT.parents[1] / "BT2-Port-FULL/home-Escritorio/BT2-Recomp" / rel)
    return [p for p in c if p.exists()]


def main():
    apply = "--apply" in sys.argv
    changed = []
    for d in ("port/eq", "src", "port/full", "port/tools"):
        for p in (ROOT / d).rglob("*"):
            if p.is_file() and p.suffix in (".c", ".h", ".py", ".cpp") and p.stat().st_mtime > T0037:
                changed.append(str(p.relative_to(ROOT)))
    restored, kept, missing = [], [], []
    for rel in sorted(changed):
        if rel in KEEP:
            kept.append(rel)
            continue
        c = candidates(rel)
        if not c:
            missing.append(rel)
            continue
        src = c[0]
        if apply:
            dst = ROOT / rel
            save = BK / "pre_restore_0037" / rel
            save.parent.mkdir(parents=True, exist_ok=True)
            if not save.exists():   # re-ejecucion: no pisar el estado previo guardado la primera vez
                shutil.copy2(dst, save)
            shutil.copyfile(src, dst)
            os.utime(dst, None)   # mas nuevo que su objeto: build_full lo recompila
        restored.append((rel, src.relative_to(BK) if src.is_relative_to(BK) else Path(src.parent.name) / src.name))
    print(f"cambiados despues de 00:37: {len(changed)}; restaurados: {len(restored)}; mantenidos (logging): {len(kept)}; "
          f"sin respaldo: {len(missing)}")
    from collections import Counter
    print("por respaldo:", dict(Counter(str(s).split("/")[0] for _, s in restored)))
    for m in missing:
        print("  SIN RESPALDO:", m)
    for k in kept:
        print("  MANTENIDO:", k)


if __name__ == "__main__":
    main()
