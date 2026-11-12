#!/bin/bash
# Recrea las rutas absolutas que esperan scripts y docs (~/Escritorio/BT2-Recomp, BT2-test, BT2-overlay-work, ~/Proyectos/*).
# Uso: setup_symlinks.sh [RAIZ_DE_LA_COPIA = carpeta que contiene BT2-Recomp/BT2-test/BT2-overlay-work]
set -eu
R="${1:-$(cd "$(dirname "$(readlink -f "$0")")/../.." && pwd)}"
mkdir -p ~/Escritorio ~/Proyectos
for n in BT2-Recomp BT2-test BT2-overlay-work; do ln -sfn "$R/$n" ~/Escritorio/$n; done
F=/mnt/datos/Proyectos/BT2-Port-FULL/home-Proyectos
if [ -d "$F" ]; then for n in BT2-Recomp BT3-Decompiled Tenkaichi3Decomp ps2-decomp-kit; do [ -e "$F/$n" ] && ln -sfn "$F/$n" ~/Proyectos/$n; done; fi
ls -la ~/Escritorio/BT2-* ~/Proyectos 2>/dev/null | head -20
