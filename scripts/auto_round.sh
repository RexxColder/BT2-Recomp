#!/bin/bash
# One unattended decomp round: every automatic source of matching C, each followed by the build gate.
#
# Usage: scripts/auto_round.sh [STEP...]     (default: all steps, in this order)
#   xfer     BT3 transplants with their own data (integrate_xfer.py) + second copies (xfer_dups.py)
#   m2c      m2c output as is and its variants, for every function still in asm (m2c_sweep.py)
#   m2cfix   only the drafts that did not compile / differed, retried with the newer fixes
#   perm     decomp-permuter on the near misses (perm_sweep.py), small ones first, then wider
#   agents   the agents' listed files (integrate_agents.py)
# Before the round: a tarball of src/include/config/scripts/docs in ~/Escritorio/BT2-backups/. After each
# step: gate_prune.py (byte-identical image or the offending machine files are dropped), then progress.py.
# Log: scratch/auto_round.log.
set -u
cd "$(dirname "$0")/.."
PY=.venv/bin/python
LOG=scratch/auto_round.log
STEPS=("$@")
[ ${#STEPS[@]} -eq 0 ] && STEPS=(xfer m2c m2cfix perm agents)

say() { echo "[$(date +%H:%M)] $*" | tee -a "$LOG"; }
gate() {
    $PY -u scripts/gate_prune.py --max-rounds 20 >> "$LOG" 2>&1
    local rc=$?
    say "gate after $1: rc=$rc; $(python3 scripts/progress.py 2>&1 | grep 'bytes of game code')"
    return $rc
}

mkdir -p ~/Escritorio/BT2-backups
tar czf ~/Escritorio/BT2-backups/src_cfg_$(date +%Y%m%d_%H%M)_auto.tgz src include config scripts docs \
    src_dropped game.toml configure.py 2>/dev/null
say "round start: ${STEPS[*]}"
for step in "${STEPS[@]}"; do
    say "step $step"
    case $step in
        xfer)   $PY -u scripts/integrate_xfer.py >> "$LOG" 2>&1 && $PY -u scripts/xfer_dups.py >> "$LOG" 2>&1 ;;
        m2c)    $PY -u scripts/m2c_sweep.py --write --jobs 6 >> "$LOG" 2>&1 ;;
        m2cfix) $PY -u scripts/m2c_sweep.py --only compile --write --jobs 6 >> "$LOG" 2>&1
                $PY -u scripts/m2c_sweep.py --only differs --write --jobs 6 >> "$LOG" 2>&1 ;;
        perm)   $PY -u scripts/perm_sweep.py --seconds 60 --jobs 6 --write >> "$LOG" 2>&1
                gate perm-small || exit 1
                $PY -u scripts/perm_sweep.py --max-ratio 0.2 --max-insns 250 --seconds 120 --jobs 6 --write \
                    >> "$LOG" 2>&1 ;;
        agents) $PY -u scripts/integrate_agents.py --dry >> "$LOG" 2>&1
                $PY -u scripts/integrate_agents.py >> "$LOG" 2>&1; say "agents: integrated (gate inside)"
                continue ;;
        *)      say "unknown step $step"; exit 2 ;;
    esac
    gate "$step" || { say "gate failed after $step: see ninja.log"; exit 1; }
done
say "round done"
