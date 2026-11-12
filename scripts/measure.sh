#!/usr/bin/env bash
# Mide la velocidad del port: ciclos de guest por segundo de pared, en una escena fija
# (título con BT2_SKIP_MOVIES=1, sin entrada). Uso: measure.sh [etiqueta] [segundos]
set -u
cd "$(dirname "$0")/.."
tag=${1:-run}
secs=${2:-60}
out=/tmp/opencode/measure-$tag
rm -rf "$out"; mkdir -p "$out"
BT2_SKIP_MOVIES=1 BT2_WATCH=10 timeout $((secs + 30)) xvfb-run -a -s "-screen 0 640x480x24" \
    port/build/native/bt2 run/SLUS_214.41 gamedata.iso > "$out/run.log" 2>&1
python3 - "$out/run.log" "$secs" "$tag" <<'EOF'
import re, sys
log, secs, tag = sys.argv[1], float(sys.argv[2]), sys.argv[3]
cur = None; prev = None; kicks = None; first = None
rate = []
for line in open(log):
    m = re.match(r"\[watch (\d+)s\] cycle (\d+)", line)
    if m:
        t, c = float(m.group(1)), int(m.group(2))
        if first is None:
            first = (t, c)
        else:
            rate.append((c - first[1]) / (t - first[0]))
    m2 = re.search(r"draw kicks (\d+)", line)
    if m2:
        kicks = int(m2.group(1))
r = sum(rate) / len(rate) if rate else 0
print(f"{tag}: guest {r/1e6:.1f} Mciclos/s ({r/294912000*100:.1f}% de tiempo real), "
      f"draw kicks {kicks}, muestras {len(rate)}")
EOF
