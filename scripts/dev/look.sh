#!/bin/bash
sleep ${1:-1}
f=$(ls -t /mnt/Datos/Proyectos/BT2-Clean/BT2-test/port/build/shots/gpu_*.ppm 2>/dev/null | sed -n 2p); ffmpeg -loglevel error -y -i "$f" -vf scale=640:-1 /tmp/look.png; echo $f
