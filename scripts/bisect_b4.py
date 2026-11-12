#!/usr/bin/env python3
"""Biseccion automatica del bug B4 (menu sin construir al volver de la pelea) sobre los cambios de la tarde del
23-oct (BT2-backups/pre_restore_0037), aplicados encima del arbol actual.

Cada vuelta: copia la version de la tarde de un subconjunto de archivos, compila con clang 23 (bt2-old), corre la prueba
COM vs COM -> pausa -> Return to Main Menu (scratchpad mm.sh) y mide los objetos dibujados en el menu (gpu: frame N: D draws).
BUENO = el menu se dibuja (>= 5 draws), MALO = negro (<= 2), NADA = crash o sin datos. Al terminar cada vuelta restaura el
arbol. Se excluyen los archivos arreglados despues de la reconstruccion (lista EXCL).

Uso: scripts/bisect_b4.py            (estado y resultados en BT2-backups/bisect_b4/)
"""
import filecmp
import json
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BK = os.path.join(ROOT, "..", "BT2-backups")
TARDE = os.path.join(BK, "pre_restore_0037")
WORK = os.path.join(BK, "bisect_b4")
SCR = "/tmp/claude-1000/-run-media-system-Datos-Proyectos-BT2-Clean/dfccedd3-bf2f-4ddc-bf29-e60f581d6523/scratchpad"
LOGS = os.path.join(ROOT, "..", "BT2-test", "logs", "vivo")
EXCL = {"201F90", "212820", "273B80", "2746C0", "18A9C0", "41CD90", "3E92E8", "2B0F78", "23BDA8", "201B90", "201568",
        "202AA8", "11A3B0", "26C7A8", "main_11A5F8"}
EXCL |= {f[:-2] for f in os.listdir(os.path.join(BK, "pre_stackgrow"))}
EXCL |= {f[:-2] for f in os.listdir(os.path.join(BK, "pre_ptr32fix"))} if os.path.isdir(os.path.join(BK, "pre_ptr32fix")) else set()


def log(*a):
    msg = " ".join(str(x) for x in a)
    print(msg, flush=True)
    with open(os.path.join(WORK, "bisect.log"), "a") as f:
        f.write(msg + "\n")


def candidates():
    out = []
    for root, _, fs in os.walk(TARDE):
        for f in fs:
            if not f.endswith(".c"):
                continue
            rel = os.path.relpath(os.path.join(root, f), TARDE)
            if any(e in f for e in EXCL):
                continue
            cur = os.path.join(ROOT, rel)
            if os.path.exists(cur) and not filecmp.cmp(cur, os.path.join(TARDE, rel), shallow=False):
                out.append(rel)
    return sorted(out)


def apply(files):
    for rel in files:
        dst = os.path.join(ROOT, rel)
        save = os.path.join(WORK, "actual", rel)
        os.makedirs(os.path.dirname(save), exist_ok=True)
        if not os.path.exists(save):
            shutil.copy2(dst, save)
        shutil.copyfile(os.path.join(TARDE, rel), dst)
        os.utime(dst, None)


def restore(files):
    for rel in files:
        dst = os.path.join(ROOT, rel)
        shutil.copyfile(os.path.join(WORK, "actual", rel), dst)
        os.utime(dst, None)


def run(cmd, timeout):
    return subprocess.run(cmd, shell=True, cwd=ROOT, capture_output=True, text=True, timeout=timeout)


def build():
    r = run("distrobox-host-exec distrobox enter bt2-old -- bash -c 'cd %s && export CPATH=/usr/include/ffmpeg BT2_IRFIX=1 && "
            "scripts/capped.sh 12G python3 port/tools/build_full.py --jobs 4 2>&1 | tail -1 && python3 port/tools/link_full.py 2>&1 | tail -1'"
            % ROOT, 3600)
    ok = "enlace OK" in r.stdout
    if ok:
        shutil.copy2(os.path.join(ROOT, "port/build/full/bt2full"), os.path.join(ROOT, "..", "BT2-test/bin/bt2full_c23"))
    return ok, r.stdout[-300:]


def test():
    run("distrobox-host-exec distrobox enter bt2-old -- env FIGHT=5 %s/mm.sh > %s/mm.out 2>&1" % (SCR, SCR), 900)
    t = open(os.path.join(SCR, "sess_cvc.txt")).read().strip()
    lg = open(os.path.join(LOGS, t + ".log"), errors="ignore").read()
    if "señal" in lg:
        return "NADA", t + " (crash)"
    d = [int(m) for m in re.findall(r"^gpu: frame \d+: (\d+) draws", lg, re.M)][-6:]
    if not d:
        return "NADA", t + " (sin datos)"
    med = sorted(d)[len(d) // 2]
    return ("BUENO" if med >= 5 else "MALO" if med <= 2 else "NADA"), "%s draws %s" % (t, d)


def trial(files, tag):
    apply(files)
    try:
        ok, out = build()
        if not ok:
            log(tag, len(files), "NO COMPILA", out)
            return "NADA"
        res, info = test()
        log(tag, len(files), res, info)
        return res
    finally:
        restore(files)


def main():
    os.makedirs(WORK, exist_ok=True)
    c = candidates()
    log("candidatos:", len(c))
    json.dump(c, open(os.path.join(WORK, "candidatos.json"), "w"), indent=0)
    if trial(c, "TODOS") != "BUENO":
        log("con todos los cambios de la tarde el menu tampoco anda (o no se pudo medir): fin")
        return
    while len(c) > 1:
        a, b = c[:len(c) // 2], c[len(c) // 2:]
        ra = trial(a, "mitad A")
        if ra == "BUENO":
            c = a
        else:
            rb = trial(b, "mitad B")
            if rb == "BUENO":
                c = b
            else:
                log("ninguna mitad sola alcanza (A=%s B=%s): el arreglo esta repartido; quedan %d" % (ra, rb, len(c)))
                break
        json.dump(c, open(os.path.join(WORK, "candidatos.json"), "w"), indent=0)
        log("quedan", len(c), c[:8])
    log("RESULTADO:", c[:50])
    ok, _ = build()   # arbol restaurado: deja instalado el binario actual
    log("binario actual reinstalado" if ok else "OJO: no compilo el arbol restaurado")


if __name__ == "__main__":
    main()
