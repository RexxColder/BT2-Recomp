#!/usr/bin/env bash
# Runs the port headless and drives it through BT2_CONTROL: each argument is "<wall seconds>:<command>", where the
# command is a button name (start, cross, up, ...) or "shot" (saves <outdir>/<seconds>.ppm).
# Usage: scripts/drive.sh <outdir> <total seconds> 60:start 65:shot ...
set -u
out=$1; total=$2; shift 2
mkdir -p "$out"
fifo="$out/control.fifo"
[ -p "$fifo" ] || mkfifo "$fifo"
cd "$(dirname "$0")/.."
# BT2_ELF=<dir>/SLUS_214.41 para usar otro directorio de datos (el juego lee el disco y escribe la
# memory card junto al ELF; "run/" es la copia local con enlaces a gamedata/).
elf=${BT2_ELF:-gamedata/SLUS_214.41}
BT2_CONTROL="$fifo" BT2_WATCH=10 timeout "$total" xvfb-run -a port/build/native/bt2 "$elf" gamedata.iso \
    > "$out/run.log" 2>&1 &
exec 3>"$fifo"
t0=$(date +%s)
for step in "$@"; do
    at=${step%%:*}; cmd=${step#*:}
    while [ $(( $(date +%s) - t0 )) -lt "$at" ]; do sleep 0.5; done
    if [ "$cmd" = shot ]; then echo "shot $out/$at.ppm" >&3; else echo "$cmd" >&3; fi
done
wait
