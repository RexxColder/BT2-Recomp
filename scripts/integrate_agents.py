#!/usr/bin/env python3
"""Links the agents' C files (docs/agents/<X>_files.txt) into the build and checks the image.

Usage: scripts/integrate_agents.py [--dry]

1. Each `0xSTART 0xEND stem` line becomes a config/c_files.txt line tagged `# agent X` (lines of a previous run
   of this script are replaced). A range that overlaps an existing C file, or whose file is missing, is reported
   and skipped.
   Their data lines (docs/agents/<X>_data.txt, from scripts/data_split.py) go to config/data_files.txt.
2. Every config/symbols/agent_*.txt goes into the yaml's symbol_addrs_path; a name defined at two addresses
   across all symbol files is reported (splat would refuse it) and the agent file that adds it second is skipped.
3. scripts/gate_prune.py then builds; agent files that make the image differ are dropped and listed in
   config/xfer_dropped.txt (they go back to their agent).
"""

import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402

YAML = ROOT / "config/SLUS_214.41.yaml"


def main():
    dry = "--dry" in sys.argv
    cf = ROOT / "config/c_files.txt"
    base = [l for l in cf.read_text().splitlines() if l.strip() and "# agent " not in l]
    taken = sorted((int(l.split()[0], 16), int(l.split()[1], 16)) for l in base)
    new, problems = [], []
    for lst in sorted((ROOT / "docs/agents").glob("*_files.txt")):
        agent = lst.name.split("_")[0]
        for line in lst.read_text().splitlines():
            p = line.split("#")[0].split()
            if len(p) != 3:
                continue
            s, e, stem = int(p[0], 16), int(p[1], 16), p[2].removesuffix(".c").removeprefix("src/")
            if not (ROOT / "src" / f"{stem}.c").exists():
                problems.append(f"{agent}: missing src/{stem}.c")
                continue
            if any(a < e and s < b for a, b in taken):
                problems.append(f"{agent}: {stem} [{s:#x},{e:#x}) overlaps another C file")
                continue
            # Calls/data pointing at another copy of a helper (several in BT2): retarget before the gate.
            subprocess.run([sys.executable, str(ROOT / "scripts/fix_targets.py"), f"src/{stem}.c", f"{s:#x}", "--write"],
                           cwd=ROOT, capture_output=True)
            taken.append((s, e))
            new.append(f"0x{s:08X} 0x{e:08X} {stem}  # agent {agent}")

    # Symbol files: one name, one address across everything splat reads.
    seen = {}
    for path in sorted((ROOT / "config/symbols").glob("*.txt")) + [ROOT / "config/symbol_addrs.txt"]:
        if path.name.startswith("agent_"):
            continue
        for m in re.finditer(r"^(\w+) = 0x([0-9A-Fa-f]+);", path.read_text(), re.M):
            seen.setdefault(m.group(1), int(m.group(2), 16))
    agent_files = []
    for path in sorted((ROOT / "config/symbols").glob("agent_*.txt")):
        clash = [m.group(1) for m in re.finditer(r"^(\w+) = 0x([0-9A-Fa-f]+);", path.read_text(), re.M)
                 if seen.get(m.group(1), int(m.group(2), 16)) != int(m.group(2), 16)]
        if clash:
            problems.append(f"{path.name}: names already at another address: {', '.join(clash[:8])}")
            continue
        for m in re.finditer(r"^(\w+) = 0x([0-9A-Fa-f]+);", path.read_text(), re.M):
            seen.setdefault(m.group(1), int(m.group(2), 16))
        agent_files.append(f"config/symbols/{path.name}")

    # Their own data (docs/agents/<X>_data.txt, `.rodata 0xSTART 0xEND stem` lines from scripts/data_split.py).
    df = ROOT / "config/data_files.txt"
    dbase = [l for l in df.read_text().splitlines() if l.strip() and "# agent " not in l] if df.exists() else []
    linked = {l.split()[2] for l in new}
    dnew = []
    for lst in sorted((ROOT / "docs/agents").glob("*_data.txt")):
        agent = lst.name.split("_")[0]
        for line in lst.read_text().splitlines():
            p = line.split("#")[0].split()
            if len(p) == 4 and p[3].removeprefix("src/").removesuffix(".c") in linked:
                dnew.append(f"{p[0]} 0x{int(p[1], 16):08X} 0x{int(p[2], 16):08X} "
                            f"{p[3].removeprefix('src/').removesuffix('.c')}  # agent {agent}")
    print(f"{len(new)} agent files, {len(agent_files)} agent symbol files, {len(dnew)} data lines")
    for p in problems:
        print("  !", p)
    if dry:
        return 0
    cf.write_text("\n".join(sorted(base + new, key=lambda l: int(l.split()[0], 16))) + "\n")
    df.write_text("\n".join(sorted(dbase + dnew, key=lambda l: int(l.split()[1], 16))) + "\n")
    y = YAML.read_text()
    y = re.sub(r"\n    - config/symbols/agent_\w+\.txt", "", y)
    extra = "".join(f"\n    - {f}" for f in agent_files)
    y = y.replace("\n    - config/symbols/bt3_data.txt", "\n    - config/symbols/bt3_data.txt" + extra, 1)
    YAML.write_text(y)
    return subprocess.run([sys.executable, str(ROOT / "scripts/gate_prune.py")], cwd=ROOT).returncode


if __name__ == "__main__":
    sys.exit(main())
