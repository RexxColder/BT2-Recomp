# Memoria de Claude Code sobre este proyecto (copia de ~/.claude/projects/-home-rexx/memory/, 2026-10-21)

Si el nuevo Claude no tiene esa carpeta, estas son las reglas y el contexto acumulado. Respaldo original en BT2-Port-FULL/claude/.

---------------- bt2-handoff-2026-10-21.md ----------------
---
name: bt2-handoff-2026-10-21
description: BT2 port copied to /mnt/datos/Proyectos/BT2-Port for a new OS; read docs/HANDOFF.md there first
metadata:
  type: project
---

On 2026-10-21 the decompilation (all 442 missing port/eq files) was finished and the relevant trees were copied to /mnt/datos/Proyectos/BT2-Port (BT2-Recomp, BT2-test, BT2-overlay-work, ref, legacy-Proyectos-BT2-Recomp, extras). Originals in ~/Escritorio and ~/Proyectos were NOT deleted.

**Why:** the user continues from another OS. **How to apply:** open BT2-Recomp/docs/HANDOFF.md and SETUP_NUEVO_SISTEMA.md; first tasks are fixing port/eq 100008, 2D40B0, 2DF0A0 (build fails), link, tests; the demo crash comes after. See [[bt2-recomp-project]].

---------------- bt2-recomp-project.md ----------------
---
name: bt2-recomp-project
description: "DBZ Budokai Tenkaichi 2 USA (SLUS_214.41) port; master ~/Escritorio/BT2-Recomp; goal native like Tenkaichi3Decomp; state, docs, quirks"
metadata:
  node_type: memory
  type: project
  originSessionId: 76314755-7c8b-48cf-94a8-707a7c328925
  modified: 2026-10-10T20:13:58.005Z
---

Started 2026-10-08. ~/Proyectos/BT2-Recomp, created with ps2-decomp-kit `new_project.py` (see [[ps2-decomp-kit-project]]).
- ISO: ~/Descargas/Roms/PS2/BT2/ (user-supplied .7z), symlinked; `gamedata/` = extracted disc.
- third_party/PS2Recomp: fresh upstream clone (HEAD was 2c5fbb9), branch `bt2` = kit patches 0001-0009 via `git am`.
- Bootstrap byte-identical after yaml fix: .text_nop/.ctors/.dtors/.reginfo sit between .vutext and .data -> one `textbin` subsegment at 0x23F350.
- Overlay BIN/DBZP.BIN (0x3B3100) translated via scripts/overlay.py (combined ELF). Movies: port/src/movie.cpp FFmpeg HLE of func_0024BA78.
- 2026-10-08 state: logos, intro movie, title, main menu work (~0.45x speed); play.sh = windowed play, scripts/drive.sh = headless FIFO driver. Uncommitted patch-0010 work in third_party/PS2Recomp (bt2 branch): _sceSifLoadModuleBuffer, D1, D4, IOP heap first-fit + HeapBase 0xA0000. Goal: playable fight.
- 2026-10-09: user switched goal to FULL matching decomp (like z3xox BT3). Cross-ref with BT3-Decompiled: scripts/xmatch.py --strict (3548 identical funcs, 1530 with BT3 C), transplant.py (790 OK after name dedupe), integrate_xfer.py -> src/ + config/c_files.txt; PORT_LOG §9 has numbers. BT3-Decompiled built locally with kit toolchain (tools/binutils -> kit 2.40). User tools: /mnt/datos/Proyectos/ps2-tool (ghidra scripts, sce_flat.txt), /mnt/datos/Herramientas/Ghidra.
- 2026-10-09 decomp state: ROM byte-identical with 1175 C files (195 from BT3 + 980 leaf_sweep), 2.11% bytes. Gate tool: scripts/gate_prune.py (drops machine C files that break the image). Pending: 261 BT3 funcs needing own data split, 891 non-strict BT3 pairs, m2c installed in .venv. PORT_LOG §10.
- 2026-10-10: MASTER copy is ~/Escritorio/BT2-Recomp (~/Proyectos/BT2-Recomp = archive, never touch). Decomp at 9.30% (3357 C files, byte-identical). Automated pipeline (PORT_LOG §15-16): integrate_xfer.py (BT3 + own data via data_split.py), xfer_dups.py (second copies), m2c_sweep.py (m2c as-is + variants), perm_sweep.py (decomp-permuter unattended), gate_prune.py (judge). Linker = system ld 2.47 (/usr/bin/mips64-elf-ld) because kit ld 2.40 is quadratic in object count. Backups: ~/Escritorio/BT2-backups/*.tgz before big runs (no git commits yet: user never approved).
- User preference 2026-10-10: automate to raise %, agents only once the pipeline is solid, always cheapest model (haiku); reply in Spanish.
- Docs: docs/RESEARCH.md (deadlock catalogue D1-D20 vs our tree), docs/PORT_LOG.md (step log).
- Fixed in kit (uncommitted): new_project.py quotes yaml name; sdk_names.py mkdirs config/symbols.

**Why:** user wants a reproducible BT2 recomp, validated against other PS2 recomps.
**How to apply:** log every step in docs/PORT_LOG.md; next runtime fixes go to patch 0010 (D1 D_ENABLEW mirror, D4 delay-slot resume, MFC0 Count, _sceSifSendCmd from THDJ).
- 2026-10-11 hybrid port: port/tools/gen_native.py puts fn_diff-EQUAL drafts as native C into the recomp build
  (function table replace, call bridge bt2CallGuest, PS2X_IDENTITY_RDRAM=1 BT2_NATIVE=1); 91 native, no crash.
  Incremental rebuild after gen_native = ~1 min (recomp output no longer depends on the native set). The
  recompiled build (any mode) stalls on a flat gray screen after the title (attract demo never loads): pre-existing.
  asm_ovl/ is gone from the master: scripts/overlay.py now keeps port/funcmap.csv's overlay rows (11700 total).
- 2026-10-11 night: batch 9 done, equivalent C for all non-SDK asm functions in port/eq/ (3892 files, haiku
  agents, docs/agents/b9/PROMPT.md + PROMPT_EXTRA.md). Verification in PCSX2 is the bottleneck (fn_diff --csv
  build_port/eq/fn_diff.csv; --far for C larger than its slot). Hand-work list: docs/agents/b9/manual_todo.txt.
- 2026-10-13: goal now = BT2 like Tenkaichi3Decomp (native, no runtime; docs/PLAN_NATIVO.md). bt2full (port/tools/build_full.py + link_full.py + port/full/plat_*) runs main headless to the overlay. User approved TEMPORARY fallback of PS2Recomp-generated code inside bt2full (docs/agents/FALLBACK_SPEC.md) as long as the final goal (readable C, no PS2Recomp) is kept. Batch 10 (exe) / 11 (overlay, worked from ~/Escritorio/BT2-overlay-work) write remaining C with docs/agents/EQ_PROMPT.md. Reproducibility notes: docs/REPRODUCIBILIDAD.md — master's gamedata/ and tools/bin still symlink into ~/Proyectos/BT2-Recomp. EE cvt.w.s TRUNCATES (old rule was wrong).

2026-10-14: bt2full (sin PS2Recomp) dibuja los logos con el renderer de BT3 (BT2_GS=1 software, BT2_GS=gpu GL/Vulkan); SDK en port/full/plat_sdk.c, plat_mc.c (saves/card1). Después de los logos: pantalla azul con texturas mal. Películas Sofdec (mwPly*) son no-op temporal.

---------------- feedback-crash-workflow.md ----------------
---
name: feedback-crash-workflow
description: BT2 testing workflow since 2026-10-21: user plays with strace, reports crash; no automated scripted menu runs
metadata:
  type: feedback
---

The user plays the game themselves (BT2-test/jugar.sh, GL, strace on). Do NOT run long scripted/automated runs or menu tours; wait for the user to report a crash or bug, then investigate (logs/vivo/<fecha>.log/.strace, backtrace) and fix.

**Why:** scripted BT3_PAD menu tours wasted ~2 h and the input timing was wrong; the user stopped all agents. **How to apply:** after a fix, rebuild (build_full --only + link_full), copy bt2full to BT2-test/bin and tell the user; don't launch background test runs unprompted. See [[bt2-handoff-2026-10-21]].

---------------- feedback-delegate-cheap-model.md ----------------
---
name: feedback-delegate-cheap-model
description: "Model tiers: sonnet for reasoning/planning subagents, haiku (cheapest available) for trivial precise execution; max 4 agents"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 76314755-7c8b-48cf-94a8-707a7c328925
  modified: 2026-10-13T13:36:21.120Z
---

Tiering the user asked for (2026-10-13): **sonnet** for subagents that reason/plan (diagnosis, design, deciding what to do); **haiku** — the cheapest/oldest model available (enum: haiku/sonnet/opus/fable; nothing cheaper exists) — for trivial, precise execution (runs, builds, mechanical edits, checks, quick reviews). Main model reads, plans and reviews results. Batches of at most 4 agents (raised 3→6 on 2026-10-13, lowered to 4 on 2026-10-14 to save tokens).

**Why:** user hits session/weekly usage limits (2026-10-09/10 batches cut by 429s) and wants tokens saved; explicitly restated the sonnet/haiku split on 2026-10-13.
**How to apply:** for [[bt2-recomp-project]] launch Agent with `model: "haiku"` for execution, `model: "sonnet"` only when the subtask needs reasoning; briefs that save work incrementally; verify output with cheap shell checks.

Measured 2026-10-13 (BT2 eq C with Hex-Rays draft, ~180-instr functions): haiku ~53k tokens/function, sonnet ~13k (4× fewer, fewer errors) → eq-C translation of functions ≥ ~150 instr goes to sonnet; haiku for small/mechanical work.

---------------- feedback-ram-heavy-jobs.md ----------------
---
name: feedback-ram-heavy-jobs
description: "Never run heavy jobs in parallel on the user's PC (31 GB): one at a time, each memory-capped"
metadata:
  type: feedback
---

Run at most ONE heavy job at a time on the user's PC, each under `scripts/capped.sh MAX cmd` (systemd-run user scope with MemoryMax, no swap); native PS2Recomp builds with `ninja -j3`.

**Why:** 2026-10-10 night the PC nearly died of RAM ("casi se muere el pc por falta de ram"): native rebuild (ninja default 14 jobs on 64-file unity batches at -O2, 2-4 GB each) + m2c sweep (6 jobs) + PCSX2 differential tests all at once.
**How to apply:** for [[bt2-recomp-project]] and any other big build/sweep: queue jobs sequentially, cap each (e.g. 12G for builds, 8G for sweeps, 6G for PCSX2 runs), check `free -h` before launching.

---------------- feedback-report-format.md ----------------
---
name: feedback-report-format
description: "Every progress report must include estimated remaining time, % remaining, and next steps"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 76314755-7c8b-48cf-94a8-707a7c328925
  modified: 2026-10-13T18:38:52.205Z
---

Each progress report to the user ends with: estimated time remaining, estimated % remaining (toward the current goal), and the next steps.

**Why:** user asked explicitly on 2026-10-13 ("empezá a adjuntar en los reportes: tiempo y % estimado restantes y siguientes pasos").
**How to apply:** for [[bt2-recomp-project]] status updates (agent hand-backs, milestones), add a short block with those three items; base estimates on measured throughput (functions/hour per agent) and say they are estimates.

---------------- feedback-resume-after-reset.md ----------------
---
name: feedback-resume-after-reset
description: "After a usage-limit reset, compress context before resuming/reading; restart agents with a short brief instead of resuming full transcripts"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 76314755-7c8b-48cf-94a8-707a7c328925
  modified: 2026-10-14T04:48:53.329Z
---

User (2026-10-14): "cuando se reanude todo por reset de tokens que haga una compresión antes de empezar lectura".

**Why:** resuming after a 429 reset re-sends every cut agent's whole transcript plus my long context; tokens run out again fast.
**How to apply:** after a reset: (1) ask the user to run `/compact` first if my context is long (I can't run it myself); (2) don't SendMessage-resume cut agents — check their done files / port/eq, build `_b` lists with what's left, and launch fresh agents with a short brief; (3) compress big tool outputs (headroom) and read only head/tail. Max 4 agents ([[feedback-delegate-cheap-model]]).

---------------- MEMORY.md ----------------
- [PS2 decomp kit project](ps2-decomp-kit-project.md) — kit + Downhill Jam decomp/port state, docs locations, reproducibility rule
- [BT2 recomp project](bt2-recomp-project.md) — DBZ BT2 USA PS2Recomp port: setup, overlay addr, deadlock catalogue
- [Delegate to cheap model](feedback-delegate-cheap-model.md) — sonnet plans/reasons, haiku executes (cheapest), max 4
- [Heavy jobs one at a time, capped](feedback-ram-heavy-jobs.md) — PC nearly died of RAM; scripts/capped.sh, ninja -j3
- [Report format](feedback-report-format.md) — every report: time left, % left, next steps
- [Resume after reset](feedback-resume-after-reset.md) — compress first; fresh agents with _b lists, not resumes
- [BT2 handoff 2026-10-21](bt2-handoff-2026-10-21.md) — copia en /mnt/datos/Proyectos/BT2-Port, leer docs/HANDOFF.md
- [Crash workflow](feedback-crash-workflow.md) — user plays with strace, reports crash; no scripted tours

---------------- ps2-decomp-kit-project.md ----------------
---
name: ps2-decomp-kit-project
description: "PS2 matching-decomp + native-port pipeline (ps2-decomp-kit, DownhillJam-Decompiled); state and where the docs are"
metadata:
  node_type: memory
  type: project
  originSessionId: 6306a33c-b516-4606-8e36-f93d3e317653
  modified: 2026-10-08T08:49:12.037Z
---

User is generalising BT3-Decompiled (z3xox) into a reusable kit and applying it to other PS2 games.
- ~/Proyectos/ps2-decomp-kit: kit scripts; docs/METHOD.md (decomp stage), docs/PORT_METHOD.md (native port stage, step log, steps 0-19+); third_party/PS2Recomp (commit 2c5fbb9 + `git am` of third_party/patches/ps2recomp-000N-*.patch, numbered series).
- ~/Proyectos/DownhillJam-Decompiled (SLES_547.15): decomp byte-identical, SN ProDG 2.95.3-136. Native port boots from the ISO (`gamedata.iso` symlink to ~/Descargas/Roms/PS2/...), renders menus, scripted input via THDJ_INPUT / THDJ_CONTROL fifo (user's real gamepad still not detected, deprioritized). PS2Recomp patches 0001-0008 (0008 = threaded/banded GS raster, 0.23x realtime on 2026-10-08). Run under `xvfb-run`. Speed work 2026-10-08: game thread ~65% in VU1 interpreter (~100 ns/VU cycle); built PS2X_VU1_RECORD + `ps2x_vu1_replay` (hash of regs/mem/XGKICK/cycles) as exact regression check for interpreter changes; working on VIF1/VU1 on its own thread (PS2X_VIF1_THREAD, PS2X_VIF1_STATS) -> patch 0009, PORT_METHOD step 28. Header edits to ps2_vu1.h/ps2_memory.h force a ~10 min rebuild of all translated code.
- 2026-10-08 Bink intro debug vs PCSX2: patched PCSX2 at ~/pcsx2-src/build/bin/pcsx2-qt has a JSON DebugServer on TCP 21512 (client script pattern: newline JSON {"cmd":"read_memory",...}); MCP `pcsx2` registered user-scope. Diffing RAD state at the 3rd EE handler hit (func_003BBD90) showed the port loses the reply that the dispatcher func_003BB6E0 sends via isceSifSendCmd -> _sceSifSendCmd (internal ABI: cid,mode,packet,psize,src,dest,size in a0..t2); the runtime aliased _sceSifSendCmd to sceSifSendCmd (wrong ABI). Fix: own `_sceSifSendCmd` handler in RPC.cpp (uncommitted, for patch 0010). Also fixed MFC0 Count (was frozen 0; Bink clock). Movie now decodes but sceGsExecLoadImage HLE returns -1 always -> no picture; next step. Full status: DownhillJam-Decompiled/docs/PORT_STATUS.md; diff scripts in tools/pcsx2_diff/. Movies still need PS2X_IOP_RAM_MODULES=1. PC froze once during a -j12 build: use -j6.
- Outbreak-Decompiled is an unfinished earlier attempt (user said so); BT3-Decompiled is the reference.

**Why:** user wants reproducibility across titles and asked to document every step for a later tool. User granted permission to install packages (sudo pacman) and use ~/Descargas.
**How to apply:** log each new step (command + decision + result) in PORT_METHOD.md as you go; PS2Recomp changes go into a new numbered patch (rebuild series in a temp worktree with `git am` + format-patch); game-specific stubs/unstubs in port/recomp_extra.toml; never commit other agents' uncommitted files (vtables.py/native_bridge.py/port/native/ and src/ renames from a parallel agent).
