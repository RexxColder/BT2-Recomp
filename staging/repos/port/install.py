#!/usr/bin/env python3
"""BORRADOR. Build de un comando del port de BT2: desde una copia limpia del repo y TU imagen de disco a un ejecutable.

    python3 install.py --iso <disco.iso>      todo el proceso
    python3 install.py --check                solo revisa requisitos
    python3 install.py --from build           retoma desde un paso (requisitos|disco|split|generar|build|link)

Pasos (cada uno se salta si su resultado ya está; --force los rehace):
  1. requisitos   $CC (clang), llc, python3, 7z, binutils MIPS, splat en un .venv
  2. disco        la ISO aportada por el usuario; se extrae SLUS_214.41 y se verifica por SHA1
  3. split        configure.py: imagen plana + splat (asm/ y assets/ quedan locales, nunca se suben)
  4. generar      shaders (port/tools/gen_shaders.py)
  5. build        port/tools/build_full.py (todo el C del juego a objetos x86-64)
  6. link         port/tools/link_full.py -> port/build/native/bt2  (+ play.sh)
El repo no trae datos del juego. Sin rutas absolutas ni contenedores. Solo biblioteca estándar. Linux."""
import argparse, hashlib, os, pathlib, shutil, subprocess, sys

ROOT = pathlib.Path(__file__).resolve().parent
LOG = ROOT / "install.log"
VENV = ROOT / ".venv"
ELF_NAME = "SLUS_214.41"
ELF_SHA1 = "cf01d5b2023843eecf7cf8ccda8bcd102dd61db7"   # SLUS_214.41 tal cual en el disco USA
ROM_SHA1 = "64ca01af0124c6dc9be50e30e7ca861b9814fddd"   # imagen plana (config/SLUS_214.41.yaml)
SPLAT = "splat64[mips]==0.50.0"                          # TODO: fijar la versión que usa configure.py
CC = os.environ.get("CC", "clang")
STEPS = ["requisitos", "disco", "split", "generar", "build", "link"]


class Failed(Exception):
    pass


def log(t):
    with open(LOG, "a") as f:
        f.write(t if t.endswith("\n") else t + "\n")


def run(cmd, env=None):
    log("\n$ " + " ".join(map(str, cmd)))
    r = subprocess.run([str(c) for c in cmd], cwd=ROOT, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                       text=True, errors="replace")
    log(r.stdout)
    if r.returncode:
        raise Failed(f"falló: {' '.join(map(str, cmd[:3]))} ... (ver install.log)")
    return r.stdout


def sha1(p):
    h = hashlib.sha1()
    with open(p, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def env():
    e = dict(os.environ, CC=CC, PATH=os.pathsep.join([str(VENV / "bin"), str(ROOT / "tools/bin"), os.environ["PATH"]]))
    return e


def step_requisitos(a):
    need = {CC: "clang (>= 17) — p.ej. pacman -S clang / apt install clang",
            "llc": "llvm", "7z": "p7zip", "g++": "gcc (solo mientras exista el relleno PS2Recomp)"}
    # binutils MIPS: configure.py usa game.toml [toolchain]; TODO: que no dependa de tools/ descargado a mano
    missing = [f"{k}: {v}" for k, v in need.items() if not shutil.which(k)]
    if missing:
        raise Failed("faltan:\n  " + "\n  ".join(missing))
    if not (VENV / "bin/python").exists():
        run([sys.executable, "-m", "venv", VENV])
    run([VENV / "bin/python", "-m", "pip", "install", "-q", SPLAT])
    return "ok"


def step_disco(a):
    disc = ROOT / "disc"
    elf = disc / ELF_NAME
    if elf.exists() and sha1(elf) == ELF_SHA1 and not a.force:
        return "ya extraído"
    iso = pathlib.Path(a.iso or "")
    if not iso.is_file():
        raise Failed("pasá tu imagen del disco USA (SLUS-21441) con --iso <archivo.iso>")
    disc.mkdir(exist_ok=True)
    run(["7z", "x", "-y", f"-o{disc}", iso, "SYSTEM.CNF", ELF_NAME])
    got = sha1(elf)
    if got != ELF_SHA1:
        raise Failed(f"{ELF_NAME} no coincide (sha1 {got}); se necesita la edición USA original")
    # Enlace local a la ISO para el runtime (play.sh la lee); queda fuera del repo por .gitignore
    link = ROOT / "gamedata.iso"
    if not link.exists():
        link.symlink_to(iso.resolve())
    # TODO: extraer gamedata/ (BIN, DATA, IOPModules) si el runtime deja de leer la ISO directamente
    return "verificado"


def step_split(a):
    if (ROOT / "build.ninja").exists() and not a.force:
        return "ya hecho"
    run([VENV / "bin/python", "configure.py"], env=env())
    rom = ROOT / "disc" / f"{ELF_NAME}.rom"
    if rom.exists() and sha1(rom) != ROM_SHA1:
        raise Failed("la imagen plana no coincide con config/SLUS_214.41.yaml")
    return "ok"


def step_generar(a):
    run([sys.executable, "port/tools/gen_shaders.py"], env=env())
    return "ok"


def step_build(a):
    run([sys.executable, "port/tools/build_full.py", "--jobs", str(a.jobs)], env=env())
    return "ok"


def step_link(a):
    run([sys.executable, "port/tools/link_full.py"], env=env())
    exe = ROOT / "port/build/native/bt2"   # TODO: confirmar la salida real de link_full.py
    return f"listo: {exe} — jugá con ./play.sh"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--from", dest="start", choices=STEPS, default=STEPS[0])
    ap.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 2) // 2))
    a = ap.parse_args()
    todo = STEPS[:1] if a.check else STEPS[STEPS.index(a.start):]
    for i, name in enumerate(todo, 1):
        print(f"[{i}/{len(todo)}] {name} ...", end=" ", flush=True)
        try:
            print(globals()[f"step_{name}"](a))
        except Failed as e:
            print(f"ERROR\n{e}")
            return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
