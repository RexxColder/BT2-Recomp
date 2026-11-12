#!/bin/bash
cd /mnt/Datos/Proyectos/BT2-Clean/BT2-test
pkill -x bt2full_test; sleep 1
rm -f port/build/shots/*.ppm /tmp/pad.txt; : > /tmp/pad.txt
BT2_ULTRALOG=1 BT2_TRACE_OUT=/tmp/trace/t.txt BT2_TRACE_RING=16777216 BT2_SKIP_MOVIES=1 DISPLAY=:87 SDL_VIDEODRIVER=x11 BT3_SCALE=1 BT3_GS=gpu BT3_GPU_API=gl BT2_MAXFRAMES=2000000 BT3_SHOT=12 BT3_PADFILE=/tmp/pad.txt BT2_SAVES=/tmp/saves_copy BT2_DUMP=/tmp/dump/port_A.bin nohup /tmp/bt2full_test > /tmp/run.log 2>&1 &
