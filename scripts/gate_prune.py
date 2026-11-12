#!/usr/bin/env python3
"""Builds and, while the image is not byte-identical, drops the C files whose range holds a differing byte.

Usage: scripts/gate_prune.py [--max-rounds 10]

For machine-made C (scripts/integrate_xfer.py): a transplanted function can compile to the right shape but call
or load a different symbol than the original (two wrappers with the same code and different targets); the link
gate is the judge. Only lines tagged "from BT3-Decompiled" in config/c_files.txt are ever dropped; a difference
outside them (asm, hand-written C) stops the loop and is reported. Dropped files are listed in
config/xfer_dropped.txt.
"""

import argparse
import re
import bisect
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT, TARGETS  # noqa: E402
import fdiff  # noqa: E402


def attic(stem):
    """A dropped file is moved to src_dropped/ (same path), never deleted: it goes back to its author."""
    src = ROOT / "src" / (stem + ".c")
    if src.exists():
        dest = ROOT / "src_dropped" / (stem + ".c")
        dest.parent.mkdir(parents=True, exist_ok=True)
        src.replace(dest)


def drop_data(stems):
    """The data lines (config/data_files.txt) of dropped files go with them."""
    df = ROOT / "config/data_files.txt"
    if df.exists():
        keep = [l for l in df.read_text().splitlines() if l.strip() and l.split()[3] not in stems]
        df.write_text("\n".join(keep) + "\n")


def build():
    subprocess.run([sys.executable, "scripts/gen_yaml.py"], cwd=ROOT, check=True, capture_output=True)
    # Only what splat/ninja regenerate: agents keep scratch under build/ (fdiff/, scratch_*).
    subprocess.run("rm -rf asm build/asm build/src build/*.elf build/*.rom build/*.ok build/*.ld", shell=True,
                   cwd=ROOT, check=True)
    subprocess.run([str(ROOT / ".venv/bin/python"), "configure.py"], cwd=ROOT, check=True, capture_output=True)
    r = subprocess.run(["ninja", "-j6"], cwd=ROOT, capture_output=True, text=True)
    (ROOT / "ninja.log").write_text(r.stdout + r.stderr)
    return r.returncode == 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-rounds", type=int, default=10)
    a = ap.parse_args()
    t = TARGETS[0]
    cf = ROOT / "config/c_files.txt"
    dropped_log = ROOT / "config/xfer_dropped.txt"
    for round_ in range(a.max_rounds):
        if build():
            n = sum(1 for l in cf.read_text().splitlines() if l.strip())
            print(f"round {round_}: byte-identical with {n} C files")
            return 0
        built = ROOT / f"build/{t['name']}.rom"
        if not built.exists():
            # Link failure: drop the machine/agent files whose objects have an undefined reference.
            log = (ROOT / "ninja.log").read_text()
            objs = set(re.findall(r"build/src/(\S+?)\.o:\(", log)) | set(re.findall(r"build/src/(\S+?)\.o: in function", log))
            # A file that does not compile stops ninja before the link: drop it the same way.
            objs |= set(re.findall(r"^FAILED: \[code=\d+\] build/src/(\S+?)\.o\b", log, re.M))
            lines = [l for l in cf.read_text().splitlines() if l.strip()]
            # Jump tables stay in the asm data: a `.L00XXXXXX` they point at must stay in asm too, so the C file
            # whose range holds that address goes.
            labels = {int(m, 16) for m in re.findall(r"undefined reference to `\.L([0-9A-F]{8})'", log)}
            # Asm that uses a label (D_/func_XXXXXXXX, or a symbol-file name) inside a C file's code or data range:
            # the original object is wider than the C file (a literal pool shared with functions still in asm, a
            # stub the range swallowed). That C file goes.
            known = fdiff.targets()
            for name in set(re.findall(r"undefined reference to `([\w.]+)'", log)):
                m = re.fullmatch(r"(?:D|func|jtbl)_([0-9A-F]{8})", name)
                if m:
                    labels.add(int(m.group(1), 16))
                elif name in known:
                    labels.add(known[name])
            spans = {l: [(int(l.split()[0], 16), int(l.split()[1], 16))] for l in lines}
            df = ROOT / "config/data_files.txt"
            by_stem = {l.split()[2]: l for l in lines}
            for d in (df.read_text().splitlines() if df.exists() else []):
                p = d.split()
                if len(p) >= 4 and p[3] in by_stem:
                    spans[by_stem[p[3]]].append((int(p[1], 16), int(p[2], 16)))
            bad = {l for l in lines if ("from BT3-Decompiled" in l or " auto/" in l or "# agent " in l or "# bt3 copy" in l) and
                   (l.split()[2] in objs or
                    any(x <= a < y for a in labels for x, y in spans[l]))}
            # Hand-written and leaf files only fail to link when a name they use vanished (a symbol file was
            # rewritten): that is the tools' fault, not theirs. Many of them at once: stop instead of dropping them.
            theirs = [l for l in bad if ("# agent " in l or " auto/" in l) and "# m2c" not in l]
            if len(theirs) > 10:
                print(f"round {round_}: link failed and {len(theirs)} agent/auto files would go "
                      f"(e.g. {theirs[0].split()[2]}): a name they use vanished, see ninja.log")
                return 1
            print(f"round {round_}: link failed, {len(bad)} files with undefined references dropped")
            if not bad:
                print("link failed: see ninja.log")
                return 1
            with open(dropped_log, "a") as f:
                for l in sorted(bad):
                    f.write(l + "  (link)\n")
            cf.write_text("\n".join(l for l in lines if l not in bad) + "\n")
            drop_data({l.split()[2] for l in bad})
            continue
        orig = (ROOT / t["original"]).read_bytes()
        mine = built.read_bytes()
        base = t["image"][0]
        diffs = [base + i for i, (x, y) in enumerate(zip(mine, orig)) if x != y]
        lines = [l for l in cf.read_text().splitlines() if l.strip()]
        rows = [(int(l.split()[0], 16), int(l.split()[1], 16), l) for l in lines]
        # A file's own data ranges (config/data_files.txt) count as that file's.
        by_stem = {l.split()[2]: l for l in lines}
        df = ROOT / "config/data_files.txt"
        for d in (df.read_text().splitlines() if df.exists() else []):
            p = d.split()
            if len(p) >= 4 and p[3] in by_stem:
                rows.append((int(p[1], 16), int(p[2], 16), by_stem[p[3]]))
        rows.sort()
        starts = [r[0] for r in rows]
        # A wrong size moves everything after it: then only the file holding the first differing byte is judged.
        if len(mine) != len(orig) or len(diffs) > 4096:
            diffs = diffs[:1]
        bad, outside = set(), 0
        for addr in diffs:
            i = bisect.bisect_right(starts, addr) - 1
            if i >= 0 and addr < rows[i][1] and ("from BT3-Decompiled" in rows[i][2] or " auto/" in rows[i][2] or "# agent " in rows[i][2] or "# bt3 copy" in rows[i][2]):
                bad.add(rows[i][2])
            else:
                outside += 1
        print(f"round {round_}: {len(diffs)} bytes differ, {len(bad)} C files to drop, {outside} bytes outside them")
        if not bad:
            print("differences outside the transplanted files: look at them by hand")
            return 1
        with open(dropped_log, "a") as f:
            for l in sorted(bad):
                f.write(l + "\n")
                attic(l.split()[2])
        cf.write_text("\n".join(l for l in lines if l not in bad) + "\n")
        drop_data({l.split()[2] for l in bad})
    return 1


if __name__ == "__main__":
    sys.exit(main())
