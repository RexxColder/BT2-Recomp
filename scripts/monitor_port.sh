#!/usr/bin/env bash
# Monitor del port: lee el log del watchdog (BT2_WATCH) y apunta cada 5 s la velocidad real del
# invitado, el ritmo de draws y si la cola del GS se ha quedado quieta (atasco).
# Uso: scripts/monitor_port.sh [log] [veces]
set -u
log=${1:-/tmp/opencode/port-live.log}
times=${2:-100000}
prev_cycle=""; prev_kick=""; prev_t=$(date +%s)
for i in $(seq 1 "$times"); do
    sleep 5
    line=$(grep -E "^\[watch" "$log" 2>/dev/null | tail -1)
    [ -z "$line" ] && { echo "esperando el primer watch..."; continue; }
    cycle=$(echo "$line" | sed -n 's/.*cycle \([0-9]*\).*/\1/p')
    kick=$(grep -E "draw kicks" "$log" 2>/dev/null | tail -1 | sed -n 's/.*draw kicks \([0-9]*\).*/\1/p')
    pc=$(echo "$line" | grep "thread  1" | sed -n 's/.*pc \([0-9A-Fa-f]*\).*/\1/p')
    st=$(echo "$line" | grep "thread  1" | awk '{print $2}')
    now=$(date +%s)
    if [ -n "$prev_cycle" ]; then
        dt=$((now - prev_t)); [ "$dt" -le 0 ] && dt=1
        mc=$(( (cycle - prev_cycle) / dt / 1000000 ))
        kps=$(( (kick - prev_kick) / dt ))
        printf "%s  guest %4s Mciclos/s (%2s%%)  draws %6s/s  hilo1 %s %s %s\n" \
            "$(date +%H:%M:%S)" "$mc" "$((mc * 100 / 295))" "$kps" "$pc" "$st" \
            "$([ "$kps" -eq 0 ] && echo '<- COLA PARADA' || echo '')"
    fi
    prev_cycle=$cycle; prev_kick=$kick; prev_t=$now
done
