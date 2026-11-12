#!/usr/bin/env bash
# Plays the native port in a window on the desktop (keyboard and any gamepad). Log: play.log
cd "$(dirname "$0")"
BT2_WATCH=0 exec port/build/native/bt2 gamedata/SLUS_214.41 gamedata.iso "$@" > play.log 2>&1
