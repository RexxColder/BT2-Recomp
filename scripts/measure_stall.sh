#!/usr/bin/env bash
# Mide la escena de atasco: mismo guion de entrada (título -> menú -> New Game -> selector de modos)
# y mira cuándo vuelve a avanzar el contador de "draw kicks". Cuando la cola del GS se vacía, el
# invitado se desbloquea y el contador crece otra vez.
# Uso: scripts/measure_stall.sh [etiqueta] [segundos]
set -u
cd "$(dirname "$0")/.."
tag=${1:-stall}
secs=${2:-300}
out=/tmp/opencode/stall-$tag
rm -rf "$out"; mkdir -p "$out"
fifo="$out/control.fifo"; mkfifo "$fifo"
BT2_SKIP_MOVIES=1 BT2_CONTROL="$fifo" BT2_WATCH=15 timeout $((secs + 120)) \
    xvfb-run -a -s "-screen 0 640x480x24" port/build/native/bt2 run/SLUS_214.41 gamedata.iso \
    > "$out/run.log" 2>&1 &
exec 3>"$fifo"
sleep 30; echo "start" >&3
sleep 15; echo "cross" >&3
sleep 22; echo "left" >&3
sleep 3;  echo "cross" >&3
sleep "$secs"
exec 3>&-
wait
python3 - "$out/run.log" "$tag" <<'EOF'
import re, sys
log, tag = sys.argv[1], sys.argv[2]
prev = None
last_change = None
lines = [l for l in open(log) if l.startswith('[')]
for line in lines:
    m = re.search(r"cycle (\d+)", line)
    k = re.search(r"draw kicks (\d+)", line)
    if m: t = int(m.group(1))
    if k:
        v = int(k.group(1))
        if prev is None or v != prev:
            prev = v
            # el timestamp del watch
            mt = re.match(r"\[watch (\d+)s\]", line)
            if mt: last_change = int(mt.group(1))
print(f"{tag}: kicks finales {prev}, último avance a los {last_change}s de reloj"
      + ("  -> SE RECUPERA" if last_change and last_change < 250 else "  -> sigue atascado"))
EOF
