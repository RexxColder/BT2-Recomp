#!/usr/bin/env python3
"""Manifiesto de SOLO LECTURA: lista las rutas del árbol de trabajo que entrarían en cada repo.

    python3 staging/repos/make_manifest.py decomp|port [--root .]

Escribe staging/repos/<repo>/MANIFEST.txt (ruta<TAB>bytes) y el total al final. No toca nada más."""
import argparse, fnmatch, os, pathlib

HERE = pathlib.Path(__file__).resolve().parent

# Lo que entra (prefijos relativos a la raíz) y lo que se excluye siempre.
INCLUDE = {
    "decomp": ["src/", "include/", "config/", "configure.py", "game.toml", "scripts/",
               "docs/decomp_guide.md", "docs/lessons_bt3_upstream.md", "docs/RESEARCH.md"],
    "port": ["src/", "include/", "config/", "configure.py", "game.toml", "play.sh",
             "port/full/", "port/eq/", "port/tools/", "port/src/", "port/include/", "port/third_party/",
             "port/funcmap.csv", "port/CMakeLists.txt",
             "scripts/gamecfg.py", "scripts/order_ld.py", "scripts/data_split.py", "scripts/overlay.py",
             "docs/PLAN_NATIVO.md", "docs/RENDERER_PLAN.md", "docs/RENDIMIENTO.md", "docs/REPRODUCIBILIDAD.md",
             "docs/bugs_open.md", "docs/AUDIO_PLAN.md"],
}
EXCLUDE = ["*.iso", "*.elf", "*.rom", "*.o", "*.a", "*.pre_*", "*.bak", "*.orig", "*.log", "*.mp4", "*.png",
           "*.jpg", "*/__pycache__/*", "*.v2.txt", "*.v3.txt*",
           "config/xmatch_bt3*", "scripts/dev/*"]
EXCLUDE_REPO = {
    # port: sin PS2Recomp ni su shim (fase 1 de docs/PLAN_PUBLICACION.md)
    "port": ["port/full/recomp_shim/*", "port/full/recomp_shim.cpp", "port/recomp*.toml", "port/sdk_stubs.toml"],
    "decomp": [],
}


def wanted(rel, repo):
    if any(fnmatch.fnmatch(rel, p) for p in EXCLUDE + EXCLUDE_REPO[repo]):
        return False
    return any(rel == i or (i.endswith("/") and rel.startswith(i)) for i in INCLUDE[repo])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("repo", choices=INCLUDE)
    ap.add_argument("--root", default=str(HERE.parents[1]))
    a = ap.parse_args()
    root = pathlib.Path(a.root).resolve()
    rows, total = [], 0
    for top in sorted({i.split("/")[0] if "/" in i else i for i in INCLUDE[a.repo]}):
        base = root / top
        paths = [base] if base.is_file() else (p for p in base.rglob("*") if p.is_file() and not p.is_symlink())
        for p in paths:
            rel = p.relative_to(root).as_posix()
            if wanted(rel, a.repo):
                s = p.stat().st_size
                rows.append((rel, s)); total += s
    rows.sort()
    out = HERE / a.repo / "MANIFEST.txt"
    with open(out, "w") as f:
        for rel, s in rows:
            f.write(f"{rel}\t{s}\n")
        f.write(f"# archivos={len(rows)} total={total} bytes ({total/2**20:.1f} MiB)\n")
    print(f"{a.repo}: {len(rows)} archivos, {total/2**20:.1f} MiB -> {out}")


if __name__ == "__main__":
    main()
