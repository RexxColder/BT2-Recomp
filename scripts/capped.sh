#!/bin/bash
# Runs a heavy job under a memory ceiling, so that it (not the desktop) is what gets killed when it runs out.
#
# Usage: scripts/capped.sh MAX COMMAND...      e.g. scripts/capped.sh 12G ninja -j3 -C port/build/native
#
# The PC has 31 GB; the 2026-10-10 night run nearly froze it: the native build's ninja started 14 compilers on
# 64-file unity batches at -O2 (2-4 GB each) while an m2c sweep (6 jobs) and PCSX2 ran too. Rules since then:
# one heavy job at a time, each through this script (systemd-run user scope: MemoryMax, no swap).
set -u
MAX=$1
shift
# Sin systemd de usuario (contenedor del AppImage, package/appimage): sin tope, el comando tal cual.
if ! command -v systemd-run >/dev/null 2>&1 || [ -n "${BT2_NO_CAP:-}" ]; then
    exec "$@"
fi
exec systemd-run --user --scope --quiet -p MemoryMax="$MAX" -p MemorySwapMax=0 -- "$@"
