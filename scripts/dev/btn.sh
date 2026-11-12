#!/bin/bash
# btn.sh "cross" [hold_s]  | luego mira con look.sh
echo "$1" > /tmp/pad.txt; sleep ${2:-0.3}; : > /tmp/pad.txt
