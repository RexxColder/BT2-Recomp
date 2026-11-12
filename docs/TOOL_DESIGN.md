# One tool for all PS2 decomp projects on this PC: analysis and design

Status: analysis and design only. Nothing was built, configured or written except this file. Sources read:
`docs/PORT_LOG.md` §9-§16, `docs/agents/BRIEF.md`, `game.toml`, `scripts/*` of BT2-Recomp, and the kit
(`~/Proyectos/ps2-decomp-kit`: README, `docs/METHOD.md`, `docs/PORT_METHOD.md`, `kit/*`). Layouts and git logs
of BT3-Decompiled, Tenkaichi3Decomp, DownhillJam-Decompiled and Outbreak-Decompiled were checked; their numbers
are from their own status files, not re-measured. `/mnt/datos/Proyectos/ps2-tool` was listed only.

---

## 0. Summary

1. The kit is already the right shape (`game.toml` + `kit/gamecfg.py`). BT2 has moved past it: BT2's scripts
   are 2-4x larger per concern and carry fixes the kit lacks. Make the kit the single source, and port BT2's
   fixes back into it before anything else.
2. Three game-specific constants are still hardcoded in BT2 scripts (GP `0x38BDF0`, overlay base `0x3B3100`,
   the BT3 reference path `~/Proyectos/BT3-Decompiled`), plus `-G8`/`-G0` string rules in several files. Move
   them to `game.toml` before porting; they break on the first non-BT2 game.
3. The safety rules that cost real work (§14, §15 incidents) must become code, not habits: quarantine instead
   of delete, a snapshot before each round, a per-round cap on dropped files, a lock, and a symbol-file
   validator that runs before the gate.
4. Biggest payoffs in BT2, in order: BT3 cross-match and transplant (cheap, +2 points by itself), own-data
   placement (`data_split.py`) plus second copies (`xfer_dups.py`) plus the m2c-as-is sweep (+4.3 points in one
   step), linker swap (4 s instead of 10-56 min), permuter (+1 point). Agents were the least efficient source.
5. Proposed tool: `ps2dk` (one Python package, one CLI) living in `ps2-decomp-kit`. Reference projects (any decomp
   on the PC) are registered once and read through snapshots, never written.
6. Priority order: P0 safety and BT2 back-port; P1 config schema and removal of hardcodes; P2 package and
   `ps2dk` commands; P3 migration of DownhillJam, Outbreak, BT3 (as reference); P4 agent tooling and tests.

---

## 1. Inventory

### 1.1 Projects

| Project | Game / exe | Toolchain | Layout | Automation | Byte-identical | Progress (documented) |
|---|---|---|---|---|---|---|
| `~/Escritorio/BT2-Recomp` (master copy; `~/Proyectos/BT2-Recomp` is an archive, do not use) | DBZ BT2 USA, `SLUS_214.41` (Spike 2006, same engine as BT3) | Sony ee-gcc 2.96 `-O2 -fno-strict-aliasing`, `-G8` (`-G0` in cri/, menu/, sys/late_a); binutils 2.40 as assembler; **ld 2.47 from `/usr/bin/mips64-elf-ld`** (system path, not in `tools/`); m2c in `.venv`; `tools/decomp-permuter` | `src/<module>/xX_ADDR.c`, `include/`, `config/symbols/*.txt`, `config/c_files.txt` (+ `data_files.txt`), `config/SLUS_214.41.yaml` (splat), `build.ninja` from `configure.py`, `docs/agents/` | Most automated of all: 36 `.py` + 5 `.sh` in `scripts/`, one unattended round (`auto_round.sh`, §1.3) | Yes (gate: `cmp` of ROM) | 9.30% of game code bytes (0x3c458 / 0x287e80), 3357 C files, 8400 functions left in asm (§16); a PC port track (`port/`, PS2Recomp, PCSX2 oracles) runs in parallel |
| `~/Proyectos/ps2-decomp-kit` | none (shared kit) | `toolchain/` with ~20 ee-gcc builds, mwcps2 builds, binutils | `kit/` (21 .py), `templates/`, `docs/` (METHOD, PORT_METHOD, decomp_guide) | `new_project.py` creates a project from an ISO + exe | n/a | n/a |
| `~/Proyectos/BT3-Decompiled` | DBZ BT3 USA, `SLUS_216.78` + `BIN/DBZP.BIN` | ee-gcc 2.96, binutils 2.40 (2.47 rejected `sq $t7,..($k0)`) | `src/`, `include/`, `asm/`, `config/`, `docs/systems/` | 7 scripts only (`progress.py`, `fdiff.py`, `apply_names.py`, `permute.py`, `vuasm.py`, `set_eabi64.py`, `names_from_strings.py`) | Yes (main exe + DBZP) | 94.96% of main exe game code, 45 functions in asm; DBZP 99.24%. Also the **source of truth for BT2 transplants** (its build ELF is read by BT2's xmatch). ROM differs by 6 bytes in `ObjSeam_TransformVtx` (non-matching) |
| `~/Proyectos/Tenkaichi3Decomp` | DBZ BT3 PC port | none (consumes BT3-Decompiled) | `src/`, `config/`, `port/`, `scripts/` (apply_names, fdiff, names_from_strings, permute, progress, set_eabi64, vuasm), `install.py` | native-port build; not a decomp | n/a | Not a decomp project. Its status note mirrors BT3's (75.62% in an older note; stale) |
| `~/Proyectos/DownhillJam-Decompiled` | Tony Hawk's Downhill Jam EU, `SLES_547.15` (Neversoft, **C++**, SN ProDG 2.95.3-136 `-fopt-stack`, `-G0`, one PT_LOAD) | `ee-gcc2.95.3-136` (via kit), binutils | `src/{auto,math,nx,probe}`, `config/`, `game.toml`, `scripts/` (kit copies + `permute.py`, `native_bridge.py`, `recomp.py`, `vtables.py`) | `leaf_sweep.py` (1667 auto), `names_from_tables.py` (1145 names), `cc_probe.py` | Yes | 1670 functions in C, 0.76% of code bytes (smallest functions first). Has a native PC port track (`port/`, THDJ_* live FIFO) |
| `~/Proyectos/Outbreak-Decompiled` | Resident Evil Outbreak USA, `SLUS_207.65` (Capcom 2003, **flattened ELF**, no symbols) | ee-gcc 2.96, ee-gcc 2.95.3, 2.9-991111; the `sq` prologue compiler is an unidentified SN ProDG 2.95.x (not reproduced) | `config/SLUS_207.65.yaml`, `config/symbol_addrs.txt` (4824 names from Ghidra), `tools/` with own copies of `order_ld.py`, `gen_undefined.py`, `leaf_sweep.py`, `sweep2/3.py`, `modules.py` | Ghidra-derived map; `gen_yaml.py`; `leaf_sweep` | Bootstrap yes, `0` C functions in the main exe per status note | 255 functions in C (`sys/util`, `sys/addr`, ...); the note also says 0% game code in one place: the older table is stale, the 255 figure is newer |
| `/mnt/datos/Proyectos/ps2-tool` | none | Ghidra 11/12 headless scripts (`AnalyzeAndExport.java`, `ExportFunctions.java`, `ExportXRefs.java`), `functions.csv`, `sce_flat.txt` (SDK signatures), `strings.csv` | flat | Not a build project; source of function maps and SDK signatures for others | n/a | n/a |

Engine notes (from the status files and kit METHOD §2): BT2 and BT3 share Spike's engine (same compiler, same
`-G8`); DownhillJam is Neversoft's C++ engine with a different compiler; Outbreak is Capcom's flattened image.
Three compiler families are now known (Sony 2.96, SN ProDG 2.95.x/2.9x with `-fopt-stack`, and the unidentified
Outbreak one).

### 1.2 Kit scripts versus BT2 scripts

Compared with `diff`/`cmp` (only the files that exist in both):

| Script | Status vs kit | What differs (BT2 side) |
|---|---|---|
| `gamecfg.py` | diverges (104 vs 100 lines) | `LINKER = TC.get("linker", ...)`; kit uses `BINUTILS + "ld"` |
| `configure.py` | diverges (BT2 root copy 200 vs kit `kit/configure.py`) | per-target `_provide.ld` generation, `PROVIDE()` for in-image symbol-file names, linker from `LINKER` |
| `gen_yaml.py` | diverges (102 vs 84 lines) | BT2 adds `.lit4`/data entries from `config/data_files.txt` |
| `fdiff.py` | diverges (227 vs 219 lines) | not diffed in detail; treat BT2 as newer |
| `permute.py`, `leaf_sweep.py` | identical | |
| `elf_survey.py`, `progress.py`, `apply_names.py`, `names_from_strings.py`, `sdk_names.py`, `cc_probe.py`, `vtables.py`, `order_ld.py`, `gen_undefined.py`, `set_eabi64.py`, `strip_func_pad.py`, `funcmap.py`, `recomp.py`, `vuasm.py` | exist in BT2 `scripts/` or only in the kit | not checked against each other in this pass (the kit copies are the ones `new_project.py` installs) |

BT2-only (not in the kit at all, 21 files: 16 `.py`, 5 `.sh`): `transplant.py`, `xmatch.py`, `integrate_xfer.py`,
`xfer_dups.py`, `gate_prune.py`, `fix_targets.py`, `data_split.py`, `m2c_sweep.py`, `m2c_fixsp.py`,
`m2c_context.py`, `perm_sweep.py`, `integrate_agents.py`, `integrate_scratch.py`, `jtbl_sweep.py`, `vu0_wrap.py`,
`overlay.py`, `drive.sh`, `measure.sh`, `measure_stall.sh`, `monitor_port.sh`, `auto_round.sh`. BT2 `scripts/`
holds 36 `.py` and 5 `.sh` files now (42 entries with `__pycache__`); the "26 scripts" figure used earlier is
outdated.

Added after the first draft (read 2026-10-10, 17:20-17:42):

| Script | What it is | Writes | Gate in its own code | Where it belongs in `ps2dk` |
|---|---|---|---|---|
| `m2c_fixsp.py DRAFT FUNC.s` | Declares m2c's undeclared `sp` stack buffer as `s32 sp[N]` (N up to the first declared `spXX` or the first register save) | the draft in place | no (exit 1 = nothing to do) | `ps2dk sweep m2c` helper (`sweep/m2c.py`), also used by `jtbl` |
| `perm_sweep.py` | Unattended decomp-permuter on m2c near misses (`differs n/m`, ratio and insn caps, `--seconds`, `--jobs`); score-0 outputs checked with `fdiff` and `data_split` | `build/permuter/sweep/<ADDR>/`, `src/auto/perm_*.c` and `config/c_files.txt` + `data_files.txt` with `--write` (rewrites both files whole) | only the caller (`auto_round.sh`) runs gate_prune | `ps2dk sweep permute` (`sweep/permute.py`) |
| `auto_round.sh` | One unattended round: tarball of src/include/config/scripts/docs/game.toml into `~/Escritorio/BT2-backups/`, then steps xfer, m2c, m2cfix, perm, agents, each followed by `gate_prune` and `progress.py`; stops on gate failure | `scratch/auto_round.log`, plus the step outputs | yes, after each step | `ps2dk round` (`rounds.py`) |
| `integrate_scratch.py OK_LIST SRC_DIR DEST_DIR TAG [DATA_LIST]` | Moves a tool's verified scratch results (`0xSTART 0xEND stem` list) into `src/DEST_DIR/`, adds `c_files.txt` lines with TAG (replacing earlier lines with the same TAG), skips any range overlapping a listed C file, adds data lines | `src/`, `config/c_files.txt`, `config/data_files.txt` | no; docstring says "the gate is still the judge", not run by `auto_round.sh` | `ps2dk integrate scratch` (`refs/integrate.py` shares the code path with `integrate_xfer`) |
| `jtbl_sweep.py [--only ...] [--limit] [--jobs]` | Decompiles the functions m2c_sweep skipped for a jump table: finds the `jtbl_*` tables the function reads, writes `scratch/jtbl/asm/<ADDR8>.s` with the tables in `.rodata`, runs m2c_sweep's attempt() (variants, `m2c_fixsp`, pointer steps), checks with fdiff, then `data_split` must place the table. Writes only under `scratch/jtbl/` (ok.txt, data.txt, status.csv) | `scratch/jtbl/*` | fdiff and data_split per function | `ps2dk sweep jtbl` (`sweep/jtbl.py`) |
| `vu0_wrap.py --classify / --addr / --all [--vu0-only] [--jobs 4]` | Turns `M2C_ERROR` functions into top-level `__asm__` C files (the BT3 way): one function per file, mnemonics kept, branch targets as labels, symbols by name; every name must be a known symbol; OK only when fdiff prints `NAME: OK` | `scratch/vu0/src/vu0_<ADDR6>.c`, `scratch/vu0/ok.txt` (nothing under `src/`) | fdiff only | `ps2dk sweep vu0` (`sweep/vu0.py`) |

Notes on these additions:
- `jtbl_sweep` and `vu0_wrap` are the two sweeps that hand-work used to cover. Neither is in `auto_round.sh`
  yet, so a round does not reach them: their output reaches `src/` only through `integrate_scratch.py` run by hand.
- `jtbl_sweep` writes nothing outside `scratch/` (good, matches the design principle); `vu0_wrap` likewise.
- `perm_sweep` is the one new script that writes to `src/` and rewrites `config/c_files.txt` and
  `config/data_files.txt` whole, before any gate runs. That is the cascade risk of §2.4 (P2) again; the tool must
  route it through the ledger API and the quarantine.
- `integrate_scratch` trusts its OK list (no fdiff re-check, no check that `src/DEST_DIR/<stem>.c` is absent,
  so it overwrites an existing file of the same stem). The tool version re-checks with fdiff and refuses overwrites.

Kit-only (not in BT2): `new_project.py`, `names_from_tables.py`, `native_bridge.py`, `configure.py` (in
`kit/`, the BT2 root copy is the newer one).

Consequence: any new project made with `new_project.py` today gets the older gate and the older linker
behaviour. The first task is a **back-port** of BT2's `gamecfg.py`, `configure.py`, `gen_yaml.py` into the kit.

### 1.3 BT2's automation: what each step does

`scripts/auto_round.sh` runs, in order, with a tarball backup first and `gate_prune.py` after each step:

| Step | Script | Input | Output | Gate |
|---|---|---|---|---|
| xfer | `integrate_xfer.py`, then `xfer_dups.py` | `config/xmatch_bt3_strict.csv`, BT3 `src/` and `build/` | `src/**/*.c` tagged `# bt3`/`# bt3 copy`, `config/data_files.txt`, `config/symbols/bt3_*.txt` | gate |
| m2c | `m2c_sweep.py --write --jobs 6` | `asm/cod/*.s` | `src/auto/m2c_*.c` (tag `# m2c`), `scratch/m2c_sweep/status.csv` | gate |
| m2cfix | `m2c_sweep.py --only compile`, then `--only differs` | status.csv | same | gate |
| perm | `perm_sweep.py` (60 s, then 120 s with `--max-ratio 0.2 --max-insns 250`) | near misses | `src/auto/perm_*.c` | gate after the first pass |
| agents | `integrate_agents.py --dry`, then the real run | `docs/agents/<X>_files.txt`, `<X>_data.txt` | yaml and c_files.txt lines | gate inside |

`gate_prune.py` compiles, links, byte-compares, and removes machine files (`from BT3-Decompiled`, `auto/`,
`# agent`) whose bytes differ, looping to a fixed point (`--max-rounds`).

Not in the round yet (run by hand): `jtbl_sweep.py` (jump tables), `vu0_wrap.py` (M2C_ERROR functions as
`__asm__`), and the hand-off of their OK lists through `integrate_scratch.py`. `m2c_fixsp.py` runs inside the m2c
step (through `m2c_sweep`). The round's `perm` step runs `perm_sweep.py --write` and gates after the first pass
only; the second pass is gated at the end of the step. `gate_prune.py` already quarantines to `src_dropped/`
(line 26-29) and stops when more than 10 agent/auto files would go in one pass (line 99); the design makes both
configurable (`max_machine_drop`) and adds the tarball, lock and ledger checks that are still missing.

---

## 2. Patterns: game-specific versus generic

### 2.1 Hardcoded in BT2 scripts (must move to `game.toml`)

| Constant | Where | Meaning | Proposed key |
|---|---|---|---|
| `GP = 0x0038BDF0` | `data_split.py:32`, `integrate_xfer.py:34` | `$gp` value (`.sbss` + 0x7FF0) | `[target.small_data] gp = ...`, or derive from `.reginfo` / `ld_gp_expression`; `elf_survey.py` already finds it |
| `BASE = 0x3B3100` (overlay) | `overlay.py:23`, `transplant.py:76`, `xfer_dups.py:65`, `xmatch.py:142,147`, and the `>= 0x3B3100` cut in `data_split`/`xfer` paths | overlay (DBZP) load base; addresses at or above it are not in the main exe | `[[target.overlay]] base`, `end`, `file`, `table` |
| `TEXT_END = 0x421300`, `disc/DBZP.BIN`, `port/build/combined.elf` | `overlay.py` | overlay image and port combined ELF | `[overlay] bin = ...`, `[port] elf = ...` (port track is optional) |
| `Path.home() / "Proyectos/BT3-Decompiled"` | `xmatch.py:118`, `integrate_xfer.py:88` | the reference decomp | `ps2dk ref` registry (§3.5) |
| `-G8` string | `m2c_sweep.py:81`; `-G0` in `cc_probe.py:30`, `elf_survey.py:161` | default and CRI/menu rule | read `gflag()` from config, never a literal |
| `game_ranges = [[0x100000, 0x387e80]]` | `game.toml` (BT2), denominator of progress | where game code is | already in `game.toml`; keep |
| `image = [0x100000, 0x3b3038]` | `game.toml` | image for ROM compare | already in `game.toml` |
| `linker = "/usr/bin/mips64-elf-ld"` | `game.toml` | system path outside `tools/` | `[toolchain] linker` should accept `tools/...` first, else a named package; reproducibility note in §4.3 |
| `G_FLAGS` keys `scratch/xfer/src/cri/` ... | `game.toml` | duplicated per scratch dir | match on a path *suffix* (`src/cri/`) so scratch copies inherit it |

`game.toml` already holds the important game facts (name, iso, image, `game_ranges`, cc, cc_flags, the `-G0`
prefixes). Things that should be there and are not: the `$gp` value, overlay base and file, the ROM SHA-1 and
the ISO SHA-1 (so a wrong disc is refused), the compiler family found by `cc_probe`, the entry point, the
`e_flags`, and the asm snapshot policy.

### 2.2 Generic (already in the kit, or should be)

- `gamecfg.py` (TOML loading, `tools/ee-gcc*` alt-compiler discovery, `gflag()` prefix rule, `target_for()`).
- `elf_survey.py` (sections, `$gp`, prologue styles, yaml by section); `fdiff.py` (per-function compare with
  relocation masking); `cc_probe.py` (compiler × flags matrix); `gen_yaml.py`; `progress.py`; `leaf_sweep.py`.
- `gate` as `cmp` of the rebuilt image (BT2, BT3, DJ and Outbreak all use it).
- Symbol-file format `Name = 0xADDR; // type:func` (one name, one address, project-wide).

### 2.3 Techniques that paid off (BT2, measured in PORT_LOG)

Ranked by bytes of game code gained per unit of work. Byte figures are from the log.

| Rank | Technique | Script | Result (PORT_LOG) | Notes |
|---|---|---|---|---|
| 1 | Leaf sweep of simple functions, one compile per batch | `leaf_sweep.py --write` | +980 files, 1451 functions verified (§10); DJ: 1667 auto functions | Cheapest per function. Only for leaves with a fdiff OK |
| 2 | BT3 cross-match with **strict** form (struct offsets kept) | `xmatch.py --strict` then `transplant.py` | 3548 identical, 1530 with BT3 C (§9); 790 OK after dedupe | Strict is what avoids layout drift (`Heap_Alloc` offset 36 vs 20) |
| 3 | Transplant + group by contiguous same-file ranges | `integrate_xfer.py` | 282 files, 529 functions (§9) | |
| 4 | Gate prune: drop machine files whose bytes differ, loop to fixed point | `gate_prune.py` | Round 0: 203 bytes, 11 files; round 1 identical (§10) | Makes wrong guesses cheap. Now quarantines (see §4) |
| 5 | **Own data placement** (`data_split.py`) | `data_split.py FILE START` | 261 functions unlocked from "has .rodata" (§15) | Biggest single enabler |
| 6 | **Second copies** of duplicated helpers (VU0, `Vec4_*`, `Mtx_*`) + `fix_targets.py` retarget (`#define`) | `xfer_dups.py`, `fix_targets.py` | 195 files (§15); 12 recovered (§14) | The cause of most drops: one name per address |
| 7 | **m2c as is**, per function, fdiff-checked, with variants (`--reg-vars saved`, `--descending-regs`, `--no-andor`, relaxed prototypes, `.data` section for externs, pointer steps in elements) | `m2c_sweep.py` | 1431 functions (§15) + 327 with variants (§16) | Biggest sweep by count. Variants are cheap retries |
| 8 | Linker swap to binutils 2.47 ld | `gamecfg.LINKER` | 10-56 min link → 4 s, output identical (§16) | See §4.2 |
| 9 | Unattended **decomp-permuter** on near misses | `perm_sweep.py` | 41 of 192 near misses (≤10% differing, ≤120 insns, 60 s) (§16) | Needs `toml` in `.venv` |
| 10 | Agents (Haiku) on hand work | `docs/agents/BRIEF.md`, `integrate_agents.py` | ~50 functions for ~450k tokens (§16); batches 1-3 gave +1.5 points | Least efficient per token; keep for near misses that scripts cannot fix |
| 11 | Jump-table sweep: m2c given the `jtbl_*` table in its input, plus the variants, then `data_split` places the table | `jtbl_sweep.py` | Not yet measured in PORT_LOG (script added after §16); skipped by m2c_sweep before | The table is the reason m2c skipped the function; the table has to be in the input, not patched after |
| 12 | VU0 macro functions as top-level `__asm__` (BT3's way) checked by fdiff | `vu0_wrap.py` | Not yet measured (added after §16); its M2C_ERROR input is the m2c sweep's output | Keeps VU0 as text that assembles back to the same bytes; no C semantics needed |
| 13 | `sp` stack buffer declared for m2c drafts | `m2c_fixsp.py` | Used by m2c_sweep and jtbl_sweep; no separate number | Small fix with large effect on drafts that otherwise fail to compile |

Per-stage progress of BT2 (from the log): 2.11% (BT3 transplant + leaf, §10) → 3.38% (agents, §12) → 3.93%
(§14) → 8.26% (own data + second copies + m2c, §15) → 9.30% (linker, m2c variants, permuter, §16).

### 2.4 Pitfalls documented in PORT_LOG (and the fix each one needs)

| # | Pitfall | Where | Required fix in the tool |
|---|---|---|---|
| P1 | `gate_prune.py` deleted files it removed and emptied `build/` (scratch lost) | §14 | Quarantine to `src_dropped/` (done in BT2), never delete; never clear `build/fdiff`, `build/scratch_*` |
| P2 | `integrate_xfer` cleared `bt3_data.txt`; a failed round's ELF made `fix_targets` rename names to `D_` labels; the next link **cascade-dropped ~100 files** | §15 | Symbol files are an append-only ledger per run; `fix_targets` refuses to rename from a failed link; a per-round cap (BT2 now stops at >10 machine-file drops) |
| P3 | Symbol files rewritten → every file using a renamed name fails at link | §15 | Same as P2: names never change silently; rename is a separate command with a diff |
| P4 | binutils 2.40 `ld` quadratic in object count (10 min at 4500 objects, ~56 min at 5226) | §16 | Linker from config (2.47); assembler stays 2.40 |
| P5 | A `:` in a symbol-file comment on the same line breaks splat | §16, BRIEF | Validator rejects it (§3.6) |
| P6 | Duplicate name (`BattleResult_GetFlags` at two addresses) breaks splat | §9 | Validator: one name, one address, project-wide |
| P7 | Name only in an agent's head (not in `config/symbols/`) = #1 reason files were dropped | BRIEF Batch 3 | `ps2dk agents collect` checks every referenced name before the file is listed |
| P8 | Jump tables (`jtbl_*` in `.rodata`) in a C file | BRIEF Batch 3 | Now allowed via `data_split`; still validated by it |
| P9 | `fdiff` masks `jal` targets, so a wrong-copy function looks OK and fails only at link | §14 | Gate is the link + `cmp`; fdiff OK is necessary, not sufficient |
| P10 | `.p2align` after each function from ee-gcc 2.9 | kit trap 9 | `strip_func_pad` per compiler (already in config) |
| P11 | Splat turns a split-off function into an `alabel` of the previous one | kit trap 10 | Write `type:func` on its symbol line |
| P12 | Two compilers in one project need per-file routing | Outbreak, BT2 `config/cc_<key>.txt` | Keep; generic |
| P13 | Agent runs cut by session limits: unsaved work lost | §11 | Save each finished file to the ledger at once; run ≤3 agents |
| P14 | Shared tool writes into a *reference* project (BT3) | general | References are read-only: snapshot copy of their ELF/src before use |
| P15 | Stale `status.md` notes (Tenkaichi3Decomp, Outbreak) disagree with later numbers | §1.1 | `ps2dk progress` generates the number; notes link to it |
| P16 | PCSX2 oracle instance shut down by itself at ~14 min (§12) | port track | Out of scope for the decomp tool; note in port tooling |
| P17 | `perm_sweep.py --write` writes `src/`, `config/c_files.txt` and `config/data_files.txt` whole, before any gate; a second run can overwrite lines of the first | perm_sweep (new) | All writes go through the ledger API (append, TAG replace, sorted, backup) and a gate call; no whole-file rewrite |
| P18 | `integrate_scratch.py` trusts its OK list: no fdiff re-check, overwrites an existing `src/DEST/<stem>.c` of the same name | integrate_scratch (new) | `ps2dk integrate scratch` re-runs fdiff and refuses to overwrite |
| P19 | `jtbl_sweep` and `vu0_wrap` are outside `auto_round.sh`: their output reaches the build only by hand | jtbl, vu0 (new) | `ps2dk round` gets them as steps; the hand-off is the same code path |

---

## 3. Design: the tool

### 3.1 Principles

1. One package, one CLI, one config file per game. The game-specific part is `game.toml` and nothing else.
2. Every destructive step is **dry-run first**, quarantines instead of deleting, and is followed by the gate.
3. Byte-identical is the only success criterion. A stage that cannot prove it (`cmp` OK) cannot write to `src/`.
4. References (other decomps on the PC) are inputs, read through snapshots.
5. Agents are clients of the tool: they get a brief and a file list from it, and their output is checked by it.

### 3.2 Package layout

Lives in `~/Proyectos/ps2-decomp-kit` (replaces `kit/`; `templates/` and `docs/` stay). BT2 and the others
run it from a venv, or through a wrapper `scripts/ps2dk` that the project carries (one line).

```
ps2-decomp-kit/
  pyproject.toml                  # console script: ps2dk
  ps2dk/
    __init__.py
    cli.py                        # argparse subcommands (table in §3.4)
    config.py                     # load + validate game.toml (schema §3.3); find project root
    toolchain.py                  # discover tools/ee-gcc*, binutils prefix, linker, wine; cc_probe
    elf.py                        # elf_survey: read ELF, sections, $gp, prologue styles, image size
    split.py                      # gen_yaml, splat yaml, configure (writes build.ninja), overlay table
    build.py                      # ninja driver, lock file, gate (cmp), image compare
    fdiff.py                      # compile a .c and compare each function (reloc masking)
    data.py                       # data_split (own .rodata/.lit4/.sdata placement)
    names/
      ledger.py                   # symbol-file ledger: parse, validate, append-only writes
      sdk.py                      # sdk_names (signatures from ps2-tool sce_flat.txt)
      strings.py                  # names_from_strings
      tables.py                   # names_from_tables (script command tables)
      apply.py                    # apply_names
    refs/
      registry.py                 # ~/.config/ps2dk/refs.toml: reference projects
      snapshot.py                 # copy a reference's ELF/ROM/src to scratch (read-only)
      xmatch.py                   # normalized shape compare (strict and fuzzy)
      transplant.py               # reference C -> target addresses, fdiff check
      integrate.py                # integrate_xfer + integrate_scratch: group OK functions into files, data via data.py
      dups.py                     # second copies + retarget (fix_targets logic)
    sweep/
      leaf.py                     # leaf_sweep
      m2c.py                      # m2c_sweep + variants; m2c_context
      fixsp.py                    # m2c_fixsp: declares the `sp` stack buffer (used by m2c and jtbl)
      jtbl.py                     # jtbl_sweep: m2c with the jump table in its input; scratch/jtbl only
      vu0.py                      # vu0_wrap: M2C_ERROR functions as top-level __asm__; scratch/vu0 only
      permute.py                  # perm_sweep on top of permute (decomp-permuter wrapper)
    gate.py                       # gate_prune: quarantine, cap, fixed point, backups
    progress.py                   # numbers from the game_ranges + C file list (one source)
    agents.py                     # brief, ranges, candidates, collect, integrate
    rounds.py                     # auto_round replacement: ordered steps, snapshot, logs
    port/                         # PS2Recomp, funcmap, native_bridge, recomp: optional extra
  templates/
    include/                      # prelude, INCLUDE_ASM, m2c macros
    brief/                        # agent brief template with {placeholders}
    game.toml.example
  tests/
    fixtures/                     # tiny ELF + tiny C file; no game data (repo ships no ROM)
    test_*.py
```

Note: `kit/` disappears and its scripts become modules. Keep thin compatibility shims (`kit/leaf_sweep.py`
calling `ps2dk.sweep.leaf`) for one release, so existing projects keep running.

### 3.3 Per-game config schema (`game.toml`)

One file per project, read by every `ps2dk` command. "R" = required. Keys not in the table are errors (typos
fail loudly). Defaults are shown where they exist.

| Table.key | Type | R | Meaning | Default / example |
|---|---|---|---|---|
| `game.name` | string | R | display name | `"Dragon Ball Z: Budokai Tenkaichi 2 (USA)"` |
| `game.id` | string | R | short id for file names and the registry | `"bt2"` |
| `game.iso` | path | R | disc image, a link in the project root, never copied | `"DragonBall Z - ... .iso"` |
| `game.iso_sha1` | string | R for new projects | refuses a wrong disc | sha1 of the image |
| `game.engine` | string | no | engine tag used to pick references | `"spike-2006"` |
| `game.family` | string | no | compiler family, written by `ps2dk probe --write` | `"ee-gcc2.96"` |
| `layout.src` / `include` / `symbols` | path | no | source, headers, symbol files | `src`, `include`, `config/symbols` |
| `layout.ledger` | path | R for matching | the C file list; append-only at run time | `config/c_files.txt` |
| `layout.data_ledger` | path | no | own-data lines from data_split | `config/data_files.txt` |
| `layout.agent_dir` | path | no | briefs, agent file lists | `docs/agents` |
| `layout.scratch` / `snapshot` | path | no | scratch area; frozen asm for agents and sweeps | `scratch`, `scratch/asm_snap` |
| `toolchain.root` | path | no | where `ee-gcc*` and binutils live | `tools` |
| `toolchain.cc` | path | R | main compiler | `tools/ee-gcc2.96/bin/ee-gcc` |
| `toolchain.cc_flags` / `cxx_flags` | string | R | flags for C and C++ | `-O2 -fno-strict-aliasing -Iinclude` |
| `toolchain.binutils` | path prefix | R | MIPS binutils prefix (assembler, readelf, objdump) | `tools/binutils/mips-ps2-decompals-` |
| `toolchain.linker` | path | no | linker; must be under `tools/` or a named package | `tools/binutils/...-ld` (binutils 2.47) |
| `toolchain.g_default` | string | R | default small-data flag | `-G8` (`-G0` for DownhillJam) |
| `toolchain.g_rule` | array of {match, flag} | no | flag by path suffix; scratch copies inherit it | `{match="src/cri/", flag="-G0"}` |
| `toolchain.alt_cc` | table | no | per-file compiler routing, from `config/cc_<key>.txt` | `ee-gcc2.9-990721` |
| `toolchain.strip_func_pad` | array | no | compilers whose output gets the `.p2align` stripped | `["ee-gcc2.9-990721", ...]` |
| `target.name` | string | R | target name (also the yaml name) | `"SLUS_214.41"` |
| `target.elf` | path | R | the executable as on the disc | `disc/SLUS_214.41` |
| `target.image` | [lo, hi] | R | address range of the flat image | `[0x100000, 0x3b3038]` |
| `target.game_ranges` | [[lo, hi]] | R | where game code is (progress denominator) | `[[0x100000, 0x387e80]]` |
| `target.rom_sha1` | string | R for new projects | expected rebuilt image (the gate's target) | sha1 of `disc/...rom` |
| `target.gp` | address | no | `$gp`; `elf.py` checks it against `.sbss`/`.sdata` | `0x0038BDF0` (derive from `.reginfo` if absent) |
| `target.small_data` | bool | no | false for `-G0` games | `true` |
| `target.language` | `c` or `cxx` | no | picks flags and tests | `"c"` |
| `target.flatten` | bool | no | flat image, address-ordered link (Outbreak) | `false` |
| `target.entry` / `e_flags` | int | no | entry point and ELF flags, for the yaml | `0x100008`, `0x20924001` |
| `target.overlay.base` / `end` | address | no | overlay load base and end (BT2's DBZP.BIN) | `0x3b3100`, `0x421300` |
| `target.overlay.file` | path | no | overlay image | `disc/BIN/DBZP.BIN` |
| `automation.max_machine_drop` | int | no | gate stops when more machine files would go in one pass | `10` |
| `automation.quarantine` | path | no | where dropped files go | `src_dropped` |
| `automation.backup_dir` | path | no | round tarballs | `~/Escritorio/<id>-backups` |
| `automation.machine_tags` | array | no | tags the gate treats as machine output (explicit, not by accident) | `["# bt3", "# m2c", "# perm", "# agent", "# jtbl", "# vu0"]` |
| `automation.m2c_jobs` | int | no | parallel jobs for m2c and jtbl | `6` |
| `automation.perm_seconds` | [int, int] | no | permuter time, first and wide pass | `[60, 120]` |
| `automation.perm_max_ratio` | [float, float] | no | near-miss ratio, first and wide pass | `[0.1, 0.2]` |
| `automation.perm_max_insns` | [int, int] | no | near-miss size cap, first and wide pass | `[120, 250]` |
| `references.use` | array of ids | no | which registered references xmatch/transplant may read | `["bt3"]` |
| `agents.max_concurrent` | int | no | agents at once | `3` |
| `agents.model` | string | no | cheap model for agent work (plan and review stay with the main model) | `"haiku"` |

Short example (the BT2 values above, as they would appear in the file):

```toml
[game]
id = "bt2"
name = "Dragon Ball Z: Budokai Tenkaichi 2 (USA)"
iso = "DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).iso"

[toolchain]
cc = "tools/ee-gcc2.96/bin/ee-gcc"
cc_flags = "-O2 -fno-strict-aliasing -Iinclude"
g_default = "-G8"
linker = "tools/binutils/mips-ps2-decompals-ld"   # 2.47, copied into tools/ (see 4.2)

[[toolchain.g_rule]]
match = "src/cri/"
flag = "-G0"

[[target]]
name = "SLUS_214.41"
elf = "disc/SLUS_214.41"
image = [0x100000, 0x3b3038]
game_ranges = [[0x100000, 0x387e80]]
gp = 0x0038BDF0

[target.overlay]
base = 0x3b3100
end = 0x421300
file = "disc/BIN/DBZP.BIN"
```

Rules the loader enforces: a `[target.overlay]` range must not overlap `game_ranges`; `gp` must lie inside
the `.sbss`/`.sdata` range of the ELF (checked by `elf.py`); any absolute path outside the project must come
from `~/.config/ps2dk/` (no `/usr/bin/...` in the project config; BT2's linker line is the example to fix).

### 3.4 Commands

| Command | Stage | Replaces (BT2) | Writes | Gate |
|---|---|---|---|---|
| `ps2dk init DEST ISO EXE [--id bt2] [--flat]` | skeleton, survey, game.toml draft | `new_project.py` | DEST only | no |
| `ps2dk survey` | prologue styles, compiler family guess, `$gp` | `elf_survey.py` | nothing (prints) | no |
| `ps2dk probe [--funcs FILE]` | compiler × flags matrix on probe functions; writes the answer into game.toml only with `--write` | `cc_probe.py` | game.toml with `--write` | no |
| `ps2dk split` | yaml + `configure` (build.ninja) | `configure.py`, `gen_yaml.py` | config/*.yaml, build.ninja | no |
| `ps2dk build` | ninja + `cmp` + progress | `ninja`, `cmp`, `progress.py` | build/ | yes (prints) |
| `ps2dk xmatch REF [--strict\|--fuzzy 0.85]` | shape compare with a registered reference | `xmatch.py` | `config/xmatch_<ref>.csv` | no |
| `ps2dk transplant REF` | reference C at target addresses + fdiff | `transplant.py` | scratch/xfer | no |
| `ps2dk integrate REF` | group OK functions into files, data via data_split | `integrate_xfer.py` | src, ledgers | yes |
| `ps2dk dups REF` | second copies + retarget | `xfer_dups.py` + `fix_targets.py` | src (tag `# <ref> copy`) | yes |
| `ps2dk sweep leaf [--write]` | leaf functions | `leaf_sweep.py` | src/auto | yes |
| `ps2dk sweep m2c [--only compile\|differs] [--variants] [--write]` | m2c as is + variants | `m2c_sweep.py`, `m2c_fixsp.py` | src/auto, scratch/m2c_sweep | yes |
| `ps2dk sweep permute [--seconds N] [--max-ratio R] [--write]` | permuter on near misses | `perm_sweep.py` | src/auto | yes |
| `ps2dk sweep jtbl [--only ADDR,...] [--limit N]` | m2c with the jump table in its input, data_split for the table | `jtbl_sweep.py` | scratch/jtbl/ only | fdiff per function |
| `ps2dk sweep vu0 --classify \| --addr ADDR... \| --all [--vu0-only]` | M2C_ERROR functions as top-level `__asm__` C, fdiff-checked | `vu0_wrap.py` | scratch/vu0/ only | fdiff per function |
| `ps2dk integrate scratch OK_LIST SRC_DIR DEST TAG [DATA]` | hand-off of a tool's OK list into `src/`; re-runs fdiff, refuses overwrites | `integrate_scratch.py` | src, ledgers | yes |
| `ps2dk data FILE START` | own data placement for one object | `data_split.py` | data ledger (on success) | no |
| `ps2dk names apply \| sdk \| strings \| tables` | names | `apply_names.py`, `sdk_names.py`, `names_from_*` | symbol ledger | no |
| `ps2dk gate [--max-rounds N]` | fixed point: drop machine files that change bytes, quarantine | `gate_prune.py` | src (quarantine only) | yes |
| `ps2dk progress` | the one number (bytes in C, functions in C, files) | `progress.py` | nothing | no |
| `ps2dk round [STEPS...] [--dry]` | ordered rounds with snapshot, lock, logs | `auto_round.sh` | everything above | yes per step |
| `ps2dk agents plan [--n 3]` | split the asm ranges by bytes still in asm; write brief per range | new | scratch/agents/plan.json, docs/agents/*.md | no |
| `ps2dk agents brief X` | brief for one range: template + candidates + names available + snapshot path | `BRIEF.md` (by hand) | docs/agents/X_brief.md | no |
| `ps2dk agents collect X` | validate X_files.txt and X_data.txt before integration | `integrate_agents.py --dry` (partly) | nothing | no |
| `ps2dk agents integrate X` | the integration after collect | `integrate_agents.py` | ledgers | yes |
| `ps2dk ref add PATH [--id bt3]` / `ps2dk ref list` | reference registry | hardcoded paths | ~/.config/ps2dk/refs.toml | no |
| `ps2dk port ...` | PS2Recomp track (optional extra) | `recomp.py`, `funcmap.py`, `native_bridge.py` | port/ | n/a |

`ps2dk round` is the replacement for `auto_round.sh`: same steps and order, plus a lock file
(`scratch/.ps2dk.lock`) so two rounds or a round and an agent integration cannot run at once.

### 3.5 Cross-reference generalized to any decomp on the PC

Today BT2 knows BT3 by path and needs BT3's build ELF (its `build/SLUS_216.78.elf`) and its `src/`. The general
form:

1. **Registry** `~/.config/ps2dk/refs.toml`, written only by `ps2dk ref add`. One table per reference:

   | Key | Meaning | Example (BT3) |
   |---|---|---|
   | `id` | short id used in `references.use` | `"bt3"` |
   | `path` | the reference project | `/home/rexx/Proyectos/BT3-Decompiled` |
   | `engine` | engine/game tag (same tag as the target to allow transplant) | `"spike-2006"` |
   | `elf` | ELF with symbols from its own build | `build/SLUS_216.78.elf` |
   | `rom` | rebuilt image, byte-identical to the disc (checked by sha1) | `build/SLUS_216.78.rom` |
   | `src` / `symbols` | its C and its names (for renames in transplant) | `src`, `config/symbols` |
   | `verified` | true only when its `cmp` passed | `true` |
   | `exclude` | address ranges known not to match (BT3: 6 bytes in `ObjSeam_TransformVtx`) | `[]` plus that range |

   Any project with a matching build qualifies. Tenkaichi3Decomp, DownhillJam and Outbreak can be references
   for anything of the same engine or compiler. DownhillJam's compiler differs (SN 2.95.3), so it is a reference
   for code shape only after `cc_probe` on the BT2 side says the family is compatible.
2. **Snapshot first** (`refs/snapshot.py`): copy the reference's `elf`, `rom`, `src` and `symbols` into
   `<project>/scratch/refs/<id>/` (hardlinks or copy). Nothing reads the reference's tree directly after that,
   and nothing writes to it (P14).
3. **Compatibility check** before use: the reference's ROM is byte-identical to its disc (sha1 in the
   registry), and `ps2dk xmatch` reports the same compiler family on a probe (`cc_probe` on both sides). A
   reference with a different family is allowed with `--shape-only` (shape, no transplant).
4. **Scope of use**: `xmatch`/`transplant` apply to a target address range only, so a reference that covers the
   same engine but a different version is still usable where bytes match (the 6-byte difference in BT3's
   `ObjSeam_TransformVtx` is reported and excluded, not silently used).

### 3.6 Byte-identical safety

- **Gate after every write**: `ps2dk build` compares the rebuilt image with `rom_sha1`/disc. Every stage that
  changes `src/` ends with `ps2dk gate`.
- **Quarantine, never delete** (P1): dropped machine files go to `src_dropped/<stage>/` with the reason in a
  sidecar `.why` file. `build/fdiff` and `scratch/` are never cleared by a gate.
- **Snapshot before a round**: `ps2dk round` writes `<backup_dir>/<id>_<stamp>.tgz` of `src include config docs
  scripts game.toml` (what BT2 does by hand now); a round refuses to start if the tarball fails.
- **Caps**: `max_machine_drop` per gate call (P2). A gate that wants to drop more stops and writes the list.
- **Ledger rules** (P2, P3, P6): `config/symbols` and `config/c_files.txt` are append-only at run time. A
  rename is `ps2dk names rename OLD NEW` with a printed diff and a gate. A name may be in one file only. Lines
  with `:` after the `//` marker are rejected. A failed link never feeds `fix_targets` (P2).
- **Lock**: `scratch/.ps2dk.lock` (pid, command) held by every command that writes; `ps2dk` refuses a second.
- **Dry-run default** for `integrate`, `gate`, `round`: prints the plan, writes with `--write`/`--yes`.
- **Reproducibility**: the tool records the versions it used (`toolchain` file in `scratch/`: compiler build,
  binutils, linker, splat version, m2c commit, permuter commit) next to each round's log. A changed linker or
  compiler invalidates the gate's last-known-good marker and forces a full gate.

### 3.7 Agents (cheap LLM subagents) plugged into the tool

Lesson from §16: scripts give far more per token than agents. Agents are for the residue: near misses the
permuter and m2c variants cannot fix, and files that need a human-like rewrite. Their loop, as the tool sees
it:

1. `ps2dk agents plan --n 3` picks disjoint address ranges by bytes still in asm (today's A-F rule), excluding
   everything in the ledgers, and writes `docs/agents/<X>_brief.md` from `templates/brief/` with:
   the range, the snapshot path (`scratch/asm_snap/`), the candidates CSV (BT3 and m2c near misses inside the
   range), and the list of names already in `config/symbols` (so the agent uses them and does not invent).
2. The agent writes `src/<dir>/x<X>_<START>.c`, `docs/agents/<X>_files.txt`, `<X>_data.txt`, and its symbol
   file `config/symbols/agent_<X>.txt`. It never runs gate, integrate, configure or ninja (BRIEF rules).
3. `ps2dk agents collect X` is the check that prevents P7: for each listed file it runs `fdiff`, `data`, the
   reference-name check (every called name must exist in the ledger or be `func_`/`D_` in the snapshot), the
   no-`:` rule, and that the object has no unexpected data section. It prints OK/rejected per file. Only OK
   files go on.
4. `ps2dk agents integrate X` appends OK files to the ledger and runs the gate (quarantining bad ones).
5. The main model reviews the collect report and decides the next batch. At most 3 agents at once (memory
   rule and BT2 batches).

### 3.8 Tests

No game data in the repo. Tests use fixtures:

| Test | What it proves |
|---|---|
| `test_elf.py` | section, `$gp` and prologue parsing on a tiny checked-in ELF (fixture built from a few hand-written MIPS words) |
| `test_fdiff.py` | a known C function compiles and compares OK against its own object; a wrong one reports DIFF n/m; `jal` masking on/off |
| `test_ledger.py` | one name one address; `:` rejected; rename produces a diff; append-only |
| `test_gate.py` | a fake build (two objects, one changes bytes) quarantines exactly that file; cap stops at `max_machine_drop`; nothing is deleted |
| `test_config.py` | schema errors: missing `cc`, overlap of overlay and game range, absolute path outside the project |
| `test_xmatch.py` | strict vs fuzzy: a struct offset change is not strict-equal; a `jal` target difference is masked; `lui` immediates masked |
| `test_data.py` | a section placed by relocation-resolved bytes; failure when the order differs |
| `test_cli.py` | `ps2dk --help` lists every command in §3.4; dry-run writes nothing (checksum of the tree before and after) |
| `test_regression_dj.py` (slow, opt-in) | DownhillJam: `split` + `build` gives the same ROM sha1 as its status file |

Regression for real projects is `ps2dk build` plus `progress` on each project's own config, run by hand (it
takes minutes; BT2's full build is about 5 min).

### 3.9 Decisions that are open for the user

- Whether BT2's `scripts/` become shims to `ps2dk` at once, or after the current agent batch finishes (the
  master copy is in use).
- Whether the PS2Recomp port track is in scope (`ps2dk port`). It is independent of matching; propose it as
  a later extra.
- Whether `ps2-tool` (Ghidra) is a dependency: a function map export (`ExportFunctions.java`) would replace
  `funcmap.csv` for flattened images like Outbreak; keep it as an external command, not a package dependency.

---

## 4. Specific risks found while reading

### 4.1 Ledger cascades

BT2's `config/c_files.txt` is both the list of C files and the input of the yaml. Any run that rewrote it from
partial state lost files (§14, §15). The tool makes it append-only at run time and keeps a dated copy
`config/c_files.v<N>.txt` per round (BT2 does this by hand: `v2`, `v3`).

### 4.2 Linker choice

BT2's `game.toml` points to `/usr/bin/mips64-elf-ld` (2.47, from the `mips64-elf-binutils` package). That path
is outside the project and outside `tools/`, so the project will not build on another PC without that package.
Proposed: the kit's `toolchain/` gets a `binutils-2.47-ld` entry, and `game.toml` uses it. Output is
byte-identical (§16), so the gate proves the switch.

### 4.3 Compiler and binutils versions

`mips-ps2-decompals` binutils 2.40 is the assembler (2.47 rejects `sq $t7,..($k0)`, §9). BT2 uses 2.40 for the
assembler and 2.47 for the linker. The tool must record both, as §3.6 says.

### 4.4 Hidden coupling between BT2 scripts

- `transplant.py`, `xfer_dups.py` and `xmatch.py` all know the overlay boundary 0x3B3100; `integrate_xfer.py`
  and `data_split.py` know GP 0x38BDF0. A new game with no overlay would fail silently (the constant is
  used as a cut, not checked). The config-driven version checks presence first.
- `gate_prune.py`'s "machine file" test is by path prefix (`from BT3-Decompiled`, `auto/`) and by tag
  (`# agent`). The tag set must be explicit in config (`[automation] machine_tags`), so new sources (permuter,
  dups) are listed rather than matched by accident.

---

## 5. Migration plan per project

Order: kit back-port first (no project is touched), then BT2 (master, in use), then the others.

### 5.1 Kit back-port (P0, blocks everything)

- Copy BT2's `gamecfg.py` (linker key), `configure.py` (provide.ld, PROVIDE for inside names), `gen_yaml.py`
  (data file lines), and diff `fdiff.py` (227 vs 219 lines) into the kit, after reading the diff.
- Add the kit's `names_from_tables.py` and `new_project.py` to BT2's knowledge (no code change needed; they
  are generic).
- Add tests (§3.8) before the port of code, against the kit copies.

### 5.2 BT2-Recomp (master, in use; do not interrupt a running round)

| Need | Change |
|---|---|
| Hardcodes (§2.1) | `game.toml`: `[target] gp`, `[target.overlay]`, `[references] use = ["bt3"]`; delete the literals from `data_split.py`, `integrate_xfer.py`, `transplant.py`, `overlay.py`, `xfer_dups.py`, `xmatch.py` |
| BT3 path | `ps2dk ref add ~/Proyectos/BT3-Decompiled --id bt3` (read-only; snapshot before use) |
| Linker | `[toolchain] linker` under `tools/`, not `/usr/bin` (§4.2) |
| Scripts | `scripts/*.py` become shims calling `ps2dk`, one at a time, each proved by `ps2dk build` = same sha1 |
| Safety | `ps2dk gate` replaces `gate_prune.py` (quarantine, cap, lock) |
| Agents | `ps2dk agents collect/integrate` replaces `integrate_agents.py`; BRIEF becomes a template |
| Reproduce | write `scratch/toolchain.json` with the versions in use; record the sha1 of the ROM |
| Stale | `docs/status.md` and PORT_LOG get the numbers from `ps2dk progress` |

Do not run any of this while `auto_round` or agents are writing. Take a tarball first (BT2's own rule).

### 5.3 BT3-Decompiled (reference; no changes to its code)

- Add a `game.toml` (it has none; `configure.py` is its own) so `ps2dk` can read it as a reference with
  `ps2dk ref add ... --id bt3`. This is the only change, and it is a new file, not an edit to existing ones.
  Its scripts can stay as they are; they are not needed by the tool.
- Its ROM differs in 6 bytes (`ObjSeam_TransformVtx`); record that in the registry so the tool excludes it.
- Its build `build/SLUS_216.78.elf` must exist (it is not in git: a `ps2dk ref add` checks it and says how to
  rebuild, which is `configure.py && ninja`).

### 5.4 Tenkaichi3Decomp (PC port, not a decomp)

- Not a decomp project: no migration needed for matching. Its `install.py` and `scripts/` stay.
- As a reference it is useful only for its port code (not for matching). Do not register it as a matching
  reference; it has no C-to-bytes match story of its own beyond BT3's.

### 5.5 DownhillJam-Decompiled (C++, -G0, flagged compiler)

- Has `game.toml` already (kit style). Migration: `ps2dk` config keys: `language = "cxx"`, `small_data = false`,
  `g_default = "-G0"`, the `cc` = `ee-gcc2.95.3-136` with `cc_flags` `-O2 -fopt-stack`. Its `gp` is absent
  (`-G0`), so `data.py` must not require it.
- Its tools (`leaf_sweep`, `names_from_tables`, `native_bridge`, `vtables`, `recomp`) become `ps2dk sweep leaf`,
  `ps2dk names tables`, `ps2dk port`, `vtables`.
- Gate: its build already matches (`cmp` OK), so `ps2dk build` must reproduce the same sha1 before any change.
- Biggest open item: the `sd16`/`sq` libraries outside the game range are out of scope (as in BT3); the
  tool's `game_ranges` covers them.

### 5.6 Outbreak-Decompiled (flattened ELF, no symbols)

- Needs the **flat profile**: `[target] flatten = true`, `order_ld.py` (address order, drop `SUBALIGN`),
  `gen_undefined.py` (define splat-missing symbols), function map from Ghidra (`ps2-tool` export) instead of
  ELF symbols. These go into `ps2dk split --flat`.
- Its compiler is not identified (the `sq` prologue, §5 of METHOD): do not automate sweeps there until the
  family is found; `ps2dk probe` must report "no match" and stop, not guess.
- Its `tools/` has its own `leaf_sweep.py`, `sweep2/3.py`, `modules.py`: fold into `ps2dk sweep leaf` after
  checking the ones that differ.
- Status note is stale (0% vs 255 functions): fix with `ps2dk progress`.

### 5.7 ps2-tool (Ghidra)

- Not a build project. Keep it outside the package; `ps2dk funcmap --ghidra-csv PATH` reads its exports.
- `sce_flat.txt` (SDK signatures) and `functions.csv` become inputs of `ps2dk names sdk`.

---

## 6. Priorities

| Pri | Item | Why first | Effort (rough) |
|---|---|---|---|
| P0 | Back-port BT2's `gamecfg`/`configure`/`gen_yaml` into the kit; add quarantine, cap, lock to the gate (BT2 first, then kit) | Current kit produces the old, unsafe gate; §14 and §15 losses | small |
| P0 | Ledger validator (one name, one address, no `:`) and `agents collect` | P7 and P6 are the most frequent drops | small |
| P1 | Config schema (§3.3) and removal of the hardcodes (§2.1); `ps2dk ref add` for BT3 | Blocks any second game from using BT2's scripts | medium |
| P1 | Snapshot + tarball in `ps2dk round` | Protects work in progress | small |
| P2 | `ps2dk` package + CLI for build, split, progress, gate, sweep leaf/m2c/permute | Consolidates the 41 scripts of BT2 `scripts/` (36 `.py`, 5 `.sh`) | medium-large |
| P2 | Linker in `tools/` (2.47), recorded toolchain versions | Reproducibility on this PC and others | small |
| P3 | Migration of DownhillJam (C++ path), Outbreak (flat path) | Other projects benefit; tests real generality | medium each |
| P3 | Test suite (§3.8) | Needed before the big refactor is trusted | medium |
| P4 | Agent tooling (`plan`, `brief`, `collect`, `integrate`) | Agents are the least efficient source; do after the scripts | small-medium |
| P4 | Port track (`ps2dk port`) | Separate workstream | later |

---

## 7. Open questions for the user

1. Is `~/Proyectos/ps2-decomp-kit` allowed to change its layout (kit/ into ps2dk/ package), or should the new
   package be a sibling (`ps2dk/`) with the kit left alone?
2. The BT2 round in progress (agents, `auto_round`): OK to wait for it to finish before the shim conversion?
3. Should new references (Tenkaichi3Decomp, DownhillJam) be registered at all, given their engine/compiler
   differences? Proposed: only BT3 for BT2; DJ only for shape checks.
4. The linker `/usr/bin/mips64-elf-ld` (2.47): may it be copied into `tools/` (license: GPL binutils, fine to
   redistribute as a binary the user already has), or should `ps2dk` only check and report it?
