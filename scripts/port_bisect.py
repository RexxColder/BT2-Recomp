#!/usr/bin/env python3
"""Finds the C functions that keep the in-place port executable from reaching the demo fight, unattended.

Usage: scripts/port_bisect.py [--candidates FILE] [--timeout 150] [--state build_port/bisect.json]

Group testing on PCSX2 (scripts/port_inplace.py builds, scripts/ps2_boot_test.py judges): the functions known good
stay switched on, a group of candidates is added; the group passes or is split in halves and each half tried, so
every culprit costs about log2(n) boots. Each result is saved in --state as it comes (good / bad lists), so a cut
run resumes where it stopped. Candidates default to every function port_inplace.py can patch, game code only
(the SDK at 0x300000 and up is the platform layer's on PC).
"""

import argparse
import json
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402

OUT = ROOT / "build_port"


SIZES = {}  # patched function address -> size, from the port_inplace list


def boot(addrs, timeout, tag):
    only = OUT / f"only_{tag}.txt"
    only.write_text("\n".join(f"0x{a:08X}" for a in sorted(addrs)) + "\n")
    elf = OUT / f"test_{tag}.elf"
    subprocess.run([sys.executable, str(ROOT / "scripts/port_inplace.py"), "--only", str(only), "--out", str(elf)],
                   cwd=ROOT, capture_output=True)
    r = subprocess.run([sys.executable, str(ROOT / "scripts/ps2_boot_test.py"), str(elf), "--timeout", str(timeout),
                        "--alive", "20"], cwd=ROOT, capture_output=True, text=True)
    pcs = [int(x, 16) for l in r.stdout.splitlines() if l.startswith("SUSPECT_PCS") for x in l.split()[1:]]
    # Patched functions the stuck game was inside (or called from): the first ones to try.
    sus = sorted({f for f in addrs for pc in pcs if f <= pc < f + SIZES.get(f, 4)})
    return r.returncode == 0, sus


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--candidates", type=Path)
    ap.add_argument("--timeout", type=int, default=150)
    ap.add_argument("--state", type=Path, default=OUT / "bisect.json")
    a = ap.parse_args()
    if a.candidates:
        cands = [int(x, 16) for x in a.candidates.read_text().split()]
    else:
        listed = (OUT / "SLUS_214.41.list").read_text().split("\n")
        cands = [int(l.split()[0], 16) for l in listed if l.strip() and int(l.split()[0], 16) < 0x300000]
    for l in (OUT / "SLUS_214.41.list").read_text().splitlines():
        if l.strip():
            SIZES[int(l.split()[0], 16)] = int(l.split()[2], 16)
    st = json.loads(a.state.read_text()) if a.state.exists() else {"good": [], "bad": [], "tests": 0}
    good, bad = set(st["good"]), set(st["bad"])
    todo = [c for c in sorted(cands) if c not in good and c not in bad]
    print(f"{len(cands)} candidates, {len(good)} good and {len(bad)} bad known, {len(todo)} to test", flush=True)

    def save():
        st.update(good=sorted(good), bad=sorted(bad))
        a.state.write_text(json.dumps(st))

    def test(group):
        st["tests"] += 1
        ok, sus = boot(good | set(group), a.timeout, "b")
        sus = [x for x in sus if x in group]
        print(f"  test {st['tests']}: {len(group)} functions from 0x{min(group):08X}: {'pass' if ok else 'FAIL'}"
              + (f" suspects {' '.join(f'0x{x:08X}' for x in sus)}" if sus else ""), flush=True)
        return ok, sus

    def solve(group):
        if not group:
            return
        ok, sus = test(group)
        if ok:
            good.update(group)
            save()
            return
        # The backtrace named patched functions: check each alone first (one boot each instead of log2(n)).
        for x in sus:
            if len(group) > 1:
                alone, _ = test([x])
                if not alone:
                    bad.add(x)
                    save()
                    print(f"  BAD 0x{x:08X} (from the backtrace)", flush=True)
                    group = [g for g in group if g != x]
        if sus and group:
            ok, _ = test(group)
            if ok:
                good.update(group)
                save()
                return
        if not group:
            return
        if len(group) == 1:
            bad.add(group[0])
            save()
            print(f"  BAD 0x{group[0]:08X}", flush=True)
            return
        mid = len(group) // 2
        solve(group[:mid])
        solve(group[mid:])

    # Chunks of 256 keep each failing group's bisection short and let progress show.
    for i in range(0, len(todo), 256):
        solve(todo[i:i + 256])
    print(f"done: {len(good)} good, {len(bad)} bad, {st['tests']} boots", flush=True)


if __name__ == "__main__":
    main()
