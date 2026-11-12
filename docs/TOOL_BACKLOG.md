# ps2dk: ordered backlog

Companion to `docs/TOOL_DESIGN.md` (design, command table, schema). Each item: ID, title, files touched, acceptance
test, size (S < half a day, M one or two days, L several days, rough), and what it depends on. Order is the
build order; P0 first. Every acceptance test runs on a **scratch copy** (`scratch/ps2dk_test/`) or on the fixtures
in `tests/fixtures/`, never on a project that is in use. BT2's running rounds and agents are not to be stopped
for these tests.

Rules for every item: no write to `~/Proyectos/*` or to BT2 `src/`/`config/` except by the migration items
(P3); each item ends with its test passing; no game data in the repo.

## P0: safety and the back-port (blocks everything)

| ID | Title | Files touched | Acceptance test | Size | Depends on |
|---|---|---|---|---|---|
| B01 | Back-port BT2's `gamecfg.py` (linker key), `configure.py` (provide.ld, inside-name PROVIDE), `gen_yaml.py` (data lines) into the kit | `~/Proyectos/ps2-decomp-kit/kit/gamecfg.py`, `kit/configure.py`, `kit/gen_yaml.py` (from BT2 `scripts/`, `configure.py`) | Copy `kit/new_project.py` output for DownhillJam's exe into `scratch/ps2dk_test/dj`; `.venv/bin/python configure.py && ninja` gives the same rom sha1 as `disc/SLES_547.15.rom` in DJ's status | S | none |
| B02 | Diff and reconcile `fdiff.py` (BT2 227 lines vs kit 219) | `kit/fdiff.py`, BT2 `scripts/fdiff.py` | `fdiff.py` on the four probe functions of DJ (`src/probe/`) prints the same result under both copies; written diff of the two is kept in `scratch/` | S | B01 |
| B03 | Gate: quarantine with `.why` sidecar, cap from config, never clear `build/fdiff`, `build/scratch_*` | new `ps2dk/gate.py` (port of `scripts/gate_prune.py`) | Fixture: two C objects, one changes bytes. Gate moves exactly that file to `src_dropped/` with `.why`; deletes nothing; a fixture with 11 machine files stops at the cap (10) and writes the list | M | none |
| B04 | Ledger module: parse symbol lines, validate (one name one address project-wide, no `:` after `//`, no dup), append-only writes, TAG replace, backup before every write | new `ps2dk/names/ledger.py` | `tests/test_ledger.py`: a `:` in a comment is rejected; a duplicate name is rejected; TAG replace keeps other lines; a rename prints a diff and writes nothing without `--write` | M | none |
| B05 | Lock and tarball snapshot helpers | new `ps2dk/rounds.py` (snapshot, lock) | Two `lock()` calls: second raises; tarball of a fixture tree lists src/include/config/scripts/docs/game.toml and nothing else | S | none |
| B06 | Read-only reference snapshot | new `ps2dk/refs/snapshot.py` | Fixture reference: snapshot copies ELF, ROM, src, symbols into `scratch/refs/<id>/`; a checksum of the reference tree is unchanged after the call | S | none |
| B07 | Fdiff module in the package (from B02's result) | new `ps2dk/fdiff.py` | `tests/test_fdiff.py`: a known C function on a fixture object prints OK; a wrong one prints DIFF n/m; `jal` masking on and off | M | B02 |
| B08 | Agent `collect` validator (checks each listed file: fdiff, data_split, names present, no `:`, no unexpected data section) | new `ps2dk/agents.py` (collect only) | On BT2's `docs/agents/` file lists (read-only): the validator reports the same 10 rejected files that `integrate_agents` dropped in §12 (names missing) | M | B04, B07 |

## P1: config, hardcodes, round

| ID | Title | Files touched | Acceptance test | Size | Depends on |
|---|---|---|---|---|---|
| B09 | `game.toml` loader and validator (schema of TOOL_DESIGN §3.3: unknown keys error, overlay vs game_ranges overlap, absolute path outside project refused, `gp` checked against ELF sections) | new `ps2dk/config.py`, `ps2dk/elf.py` (section read only) | `tests/test_config.py` with bad fixtures (each error message); BT2's real `game.toml` loads with no error | M | none |
| B10 | Remove hardcodes (GP `0x38BDF0`, overlay `0x3B3100`, `TEXT_END`, BT3 path, `-G8`/`-G0` literals, `>= 0x3B3100` cuts) by reading config | BT2 `scripts/`: `data_split.py`, `integrate_xfer.py`, `transplant.py`, `overlay.py`, `xfer_dups.py`, `xmatch.py`, `m2c_sweep.py`, `cc_probe.py`, `elf_survey.py`; BT2 `game.toml` gets the new keys (in a copy first) | In a copy of BT2 (`scratch/ps2dk_test/bt2`): `grep -rn '3B3100\|38BDF0\|BT3-Decompiled' scripts/` returns only comments; ROM sha1 unchanged after `ninja` | M | B09 |
| B11 | Reference registry: `ps2dk ref add/list`, `~/.config/ps2dk/refs.toml`, sha1 check of the reference ROM | new `ps2dk/refs/registry.py`, `ps2dk/cli.py` (ref subcommand) | `ref add` on BT3 (read-only) records its ROM sha1; a wrong path errors; `list` prints `verified` | S | B06, B09 |
| B12 | Linker into the toolchain: binutils 2.47 `ld` copied into `tools/` (or a named package), `game.toml` key, check that the path exists under `tools/` | `game.toml` (BT2, in a copy first), `gamecfg.py` / `config.py` | In the copy: link time under 30 s; ROM sha1 identical to before | S | B09, B10 |
| B13 | `ps2dk round`: ordered steps (xfer, m2c, m2cfix, perm, jtbl, vu0, scratch, agents), snapshot first, lock, gate after each step, logs to `scratch/round.log`, `--dry` | new `ps2dk/rounds.py` (replaces `auto_round.sh`) | `ps2dk round --dry` on a copy prints the plan and writes nothing (tree checksum before/after equal); a fixture gate failure stops the round after its step | M | B03, B05, B22, B24, B25, B26 |
| B14 | Test suite skeleton and fixtures (tiny ELF from hand-written MIPS words, tiny C, tiny symbol files) | new `tests/fixtures/`, `tests/conftest.py`, `tests/test_elf.py` | `pytest -q` passes; no ROM or ISO is needed | M | none |

## P2: the package and its commands

| ID | Title | Files touched | Acceptance test | Size | Depends on |
|---|---|---|---|---|---|
| B15 | Package skeleton: `pyproject.toml`, `ps2dk/cli.py` (argparse, every command of TOOL_DESIGN §3.4 listed, most stubs), console script `ps2dk`, shims in `kit/` that call the new modules | `ps2-decomp-kit/pyproject.toml`, `ps2dk/__init__.py`, `ps2dk/cli.py`, `kit/*.py` shims | `ps2dk --help` lists all commands; `tests/test_cli.py`: dry-run writes nothing | S | B14 |
| B16 | `elf.py` complete: sections, `$gp` from `.reginfo`, prologue styles (`survey`), image size, yaml by section | `ps2dk/elf.py` (from `kit/elf_survey.py`) | `ps2dk survey` on the DJ ELF prints the same sections and style counts as `kit/elf_survey.py` (kept as oracle in the test) | M | B09, B14 |
| B17a | Split and build: `split` (yaml, configure, build.ninja) and `build` (ninja, cmp, progress) | `ps2dk/split.py`, `ps2dk/build.py` (from `configure.py`, `gen_yaml.py`) | On DJ copy: `ps2dk split && ps2dk build` gives the sha1 of DJ's status | L | B01, B16 |
| B17b | Progress: one number from `game_ranges` and the ledgers; writes nothing | `ps2dk/progress.py` (from `scripts/progress.py`) | On BT2 copy: same bytes-in-C figure as `progress.py` (9.30% at §16 if the ledgers are the same) | S | B09 |
| B18 | Names: apply, sdk, strings, tables | `ps2dk/names/apply.py`, `sdk.py`, `strings.py`, `tables.py` (from BT2/kit copies) | On DJ copy: `ps2dk names tables` finds the 1145 entries of `0x3D5EF0` the status file gives | M | B04 |
| B19 | `data.py`: data_split placement, returns lines for the data ledger | `ps2dk/data.py` (from `scripts/data_split.py`) | `tests/test_data.py`: a fixture object whose `.rodata` matches the image is placed; a reordered one fails with exit != 0 | M | B07, B09 |
| B20 | Refs: xmatch and transplant from a snapshot | `ps2dk/refs/xmatch.py`, `ps2dk/refs/transplant.py` (from `scripts/xmatch.py`, `transplant.py`) | `tests/test_xmatch.py` (strict vs fuzzy, `jal` masked, struct offset not equal). On BT2 copy: strict match count equals §9 (3548 identical) | L | B06, B10, B11, B19 |
| B21 | Integrate: `integrate xfer` (from integrate_xfer), `integrate scratch` (hardened: fdiff re-check, refuses overwrite, ledger API), `dups` (xfer_dups + fix_targets) | `ps2dk/refs/integrate.py`, `ps2dk/refs/dups.py`, `ps2dk/fixtargets.py` | P18 test: a scratch OK list with an existing `src/auto/<stem>.c` is refused; a file that fails fdiff is not added; on BT2 copy the xfer count matches §9 (282 files) | L | B04, B07, B20 |
| B22 | Sweep m2c: m2c_sweep + variants + `m2c_fixsp` + `m2c_context` | `ps2dk/sweep/m2c.py`, `ps2dk/sweep/fixsp.py` | `tests/test_fixsp.py`: a draft with `Mtx_StoreIdentity(sp)` gets `s32 sp[N]` with N from the fixture asm; a draft with no `sp` returns None. On BT2 copy: status counts for 5 functions equal `scratch/m2c_sweep/status.csv` | L | B07, B16, B19 |
| B23 | Sweep leaf | `ps2dk/sweep/leaf.py` (from `leaf_sweep.py`, identical to kit) | On DJ copy: `ps2dk sweep leaf` reproduces the 1667 `src/auto` files with `gate` OK | M | B17a |
| B24 | Sweep jtbl (new script, unmeasured): m2c with the table, variants, data_split for the table; writes only scratch/jtbl | `ps2dk/sweep/jtbl.py` (from `scripts/jtbl_sweep.py`) | On BT2 copy with `--limit 5`: outputs only under `scratch/jtbl/`; the OK ones pass fdiff | M | B22, B19 |
| B25 | Sweep vu0 (new, unmeasured): M2C_ERROR to `__asm__` files, names checked | `ps2dk/sweep/vu0.py` (from `scripts/vu0_wrap.py`) | On BT2 copy: `--classify` output equals the script's; `--addr` for one known VU0 function gives NAME: OK | M | B07, B16 |
| B26 | Sweep permute with ledger routing (P17): permuter output goes through B04 with backup; no whole-file rewrite | `ps2dk/sweep/permute.py` (from `scripts/perm_sweep.py`, `permute.py`) | Fixture: running the sweep twice leaves the first run's lines in both ledgers; a corrupt line is refused | M | B04, B19, B07 |
| B27 | Gate wired into every writing command (`--write` requires a gate pass or `--no-gate` with a loud warning) | `ps2dk/cli.py`, each module's entry | `tests/test_cli.py`: a write command without a gate run prints a warning and exits 2 | S | B03, B15 |

## P3: migration of each project

| ID | Title | Files touched | Acceptance test | Size | Depends on |
|---|---|---|---|---|---|
| B28 | BT2 shim conversion, one script at a time, after the running round or agents finish | BT2 `scripts/*.py` become shims calling `ps2dk`; each commit-equivalent backed up first (tarball) | After each shim: `ps2dk build` gives the same rom sha1 as the master; `scripts/` files left are only shims | L | B13, B17a..B26 |
| B29 | BT2 `game.toml` complete (gp, overlay, rom_sha1, iso_sha1, linker under tools) | BT2 `game.toml` | `ps2dk config check` passes on BT2 | S | B09, B12 |
| B30 | DownhillJam: C++ and `-G0` profile (`language = "cxx"`, `small_data = false`, `cc_flags` `-O2 -fopt-stack`, cc `ee-gcc2.95.3-136`) | DJ `game.toml` (one-line-level edits in a copy first; DJ itself after the copy passes) | `ps2dk build` sha1 equals DJ status; `ps2dk sweep leaf --dry` lists 0 new files | M | B17a, B23, B19 |
| B31 | Outbreak: flat profile (`flatten = true`, `order_ld`, `gen_undefined`, function map from `ps2-tool` export) | Outbreak `game.toml` (create; it has none), new `ps2dk/split.py --flat` | Bootstrap rom sha1 `64c4946c...` (from its status) reproduced in a copy | L | B17a |
| B32 | BT3 as reference: add a `game.toml` (new file only, nothing else in BT3 changes) and register it | BT3 `game.toml` (new file) | `ps2dk ref add ~/Proyectos/BT3-Decompiled --id bt3` verifies the main ROM sha1; the 6-byte exception is listed in `exclude` | S | B11 |
| B33 | Tenkaichi3Decomp: documented as not a decomp, no matching migration | none (note in its docs only if asked) | none | S | none |
| B34 | Kit docs: README and METHOD point to `ps2dk`; `new_project.py` writes the new game.toml | `ps2-decomp-kit/README.md`, `docs/METHOD.md`, `kit/new_project.py` | `ps2dk init` in a scratch dir from a fixture ISO-less skeleton writes a game.toml that `ps2dk config check` accepts | M | B15, B09 |
| B35 | Status generation: `docs/status.md` numbers from `ps2dk progress` (Outbreak's stale 0% note, Tenkaichi3Decomp's stale note) | project status files (generated section only) | `ps2dk progress --md` output matches the number in each project's status after the next run | S | B17b |

## P4: agents, measurement, port track

| ID | Title | Files touched | Acceptance test | Size | Depends on |
|---|---|---|---|---|---|
| B36 | Agent `plan` and `brief`: picks disjoint asm ranges by bytes still in asm, writes the brief from `templates/brief/` with range, snapshot path, candidate CSV, names available | `ps2dk/agents.py`, `templates/brief/brief.md.tmpl` | On BT2 copy: three disjoint ranges, none overlapping a ledger line; brief text contains the names available for the range | M | B08, B20 |
| B37 | Agent `integrate`: collect (B08) then integrate OK files, gate after | `ps2dk/agents.py` | Fixture: one OK and one bad file; only the OK one is added; the bad one is quarantined by the gate | S | B08, B03, B21 |
| B38 | Measurement run (not code): run jtbl and vu0 on BT2 copy, record numbers in PORT_LOG and in this backlog | PORT_LOG (BT2, by the user's decision) | A table of counts (functions OK, files, bytes) exists for both | S | B24, B25 |
| B39 | Port track as `ps2dk port` (PS2Recomp, funcmap, native_bridge, recomp) | `ps2dk/port/`, `port/` | Out of scope for the first release; decide with the user (see open questions) | L | B15 |

## Summary of the critical path

B01 -> B02 -> B07 -> B08 (agent safety), B03 + B04 (gate and ledger, parallel with B01), B09 -> B10 -> B17a ->
B20 -> B21 -> B28. Items B24, B25 (new sweeps) and B26 (permuter routing) can start as soon as B07, B19 and B04 are
in. The migrations B30-B32 are independent once B17a is in.

## Open questions for the user

1. Stop the running BT2 round and agents for B28 (shim conversion), or wait for them to finish?
2. Are the kit (`~/Proyectos/ps2-decomp-kit`) and its layout allowed to change (`kit/` becomes the `ps2dk/`
   package with shims), or should the package be a sibling folder?
3. The linker `/usr/bin/mips64-elf-ld` (2.47): may it be copied into `tools/` (B12), or should `ps2dk` only check
   and report it?
4. Should `jtbl_sweep` and `vu0_wrap` be added to `auto_round.sh` now (before `ps2dk round` exists), or only after
   B24/B25 measurement (B38)?
5. Port track (B39): in scope for this tool, or a separate project?
