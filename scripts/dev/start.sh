#!/bin/bash
cd /mnt/Datos/Proyectos/BT2-Clean/BT2-test
pkill bt2full_test; pkill -f "Xvfb :87"; sleep 1
rm -f port/build/shots/*.ppm /tmp/pad.txt; : > /tmp/pad.txt
Xvfb :87 -screen 0 1280x960x24 >/dev/null 2>&1 &
sleep 2
BT2_SKIP_MOVIES=1 DISPLAY=:87 SDL_VIDEODRIVER=x11 BT3_SCALE=1 BT3_GS=gpu BT3_GPU_API=gl BT2_UNCAPPED=1 BT2_MAXFRAMES=2000000 BT3_SHOT=12 BT3_PADFILE=/tmp/pad.txt BT2_SAVES=/tmp/saves_test nohup /tmp/bt2full_test > /tmp/run.log 2>&1 &
( while pgrep -x bt2full_test >/dev/null; do cd port/build/shots; ls -t gpu_*.ppm 2>/dev/null | tail -n +6 | xargs -r rm -f; cd ../../..; sleep 1; done ) &
