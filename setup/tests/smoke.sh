#!/bin/sh
# Pruebas rápidas de bt2-setup con una ISO sintética (no usa la ISO real ni datos del juego del repo).
#
#   ./setup/tests/smoke.sh
#   BT2_TEST_ELF=.../SLUS_214.41 BT2_TEST_DBZP=.../BIN/DBZP.BIN ./setup/tests/smoke.sh
#   BT2_TEST_PAL_ISO="/ruta/pal.iso" ./setup/tests/smoke.sh   # además prueba el rechazo de región
#
# Los datos reales se leen de la copia local del usuario sólo para armar la ISO de prueba; no se copian al repo.
set -u

ROOT=$(cd "$(dirname "$0")/../.." && pwd)
BIN="$ROOT/setup/build/bt2-setup"
ELF="${BT2_TEST_ELF:-$ROOT/../BT2-test/gamedata/SLUS_214.41}"
DBZP="${BT2_TEST_DBZP:-$ROOT/../BT2-test/gamedata/BIN/DBZP.BIN}"

if [ ! -x "$BIN" ]; then
    echo "FAIL: falta $BIN (corré ./setup/build.sh)" >&2
    exit 2
fi
if [ ! -f "$ELF" ] || [ ! -f "$DBZP" ]; then
    echo "FAIL: faltan ELF/DBZP para la ISO sintética; definí BT2_TEST_ELF y BT2_TEST_DBZP" >&2
    exit 2
fi

TMP=$(mktemp -d /tmp/opencode/bt2-setup-test.XXXXXX) || exit 2
trap 'rm -rf "$TMP"' EXIT HUP INT TERM
PASS=0
FAIL=0

ok() { PASS=$((PASS + 1)); printf 'ok   %s\n' "$1"; }
bad() { FAIL=$((FAIL + 1)); printf 'FAIL %s\n' "$1"; }

run_expect() { # descripción, código esperado, comando...
    desc=$1
    want=$2
    shift 2
    "$@" >"$TMP/out.log" 2>&1
    got=$?
    if [ "$got" -eq "$want" ]; then
        ok "$desc (exit $got)"
    else
        bad "$desc: exit $got, esperaba $want"
        tail -5 "$TMP/out.log" | sed 's/^/     /'
    fi
}

echo "== bt2-setup smoke =="
python3 "$ROOT/setup/tests/make_test_iso.py" "$TMP/good.iso" "$ELF" "$DBZP" >/dev/null || exit 2
python3 "$ROOT/setup/tests/make_test_iso.py" "$TMP/bad.iso" "$ELF" "$DBZP" --bad-elf >/dev/null || exit 2

"$BIN" --list "$TMP/good.iso" >"$TMP/list.log" 2>&1
if grep -q 'SLUS_214.41' "$TMP/list.log" && grep -q '12 archivos' "$TMP/list.log"; then
    ok "--list lee la ISO sintética"
else
    bad "--list"
fi

run_expect "instalación sintética" 0 "$BIN" --install "$TMP/good.iso" --dest "$TMP/dest"
if [ "$(find "$TMP/dest" -type f ! -name .installed | wc -l)" -eq 12 ] &&
   [ -f "$TMP/dest/.installed" ]; then
    ok "12 archivos y marcador"
else
    bad "faltan archivos o marcador"
fi

run_expect "--check del destino" 0 "$BIN" --check --dest "$TMP/dest"
grep -q 'ELF: SHA-1 correcto' "$TMP/out.log" && ok "SHA-1 del ELF verificado" || bad "SHA-1 del ELF"

run_expect "ISO con ELF alterado" 3 "$BIN" --install "$TMP/bad.iso" --dest "$TMP/bad_dest"
if [ -e "$TMP/bad_dest/.installed" ]; then bad "quedó marcador de una instalación fallida"; else ok "sin marcador tras hash malo"; fi

printf 'no soy una iso\n' >"$TMP/not.iso"
run_expect "archivo que no es ISO" 1 "$BIN" --install "$TMP/not.iso" --dest "$TMP/not_dest"

run_expect "retomar (todo ya está)" 0 "$BIN" --install "$TMP/good.iso" --dest "$TMP/dest"
grep -q '0 copiados, 12 ya estaban' "$TMP/out.log" && ok "salteó los 12" || bad "no salteó los archivos"

run_expect "--force" 0 "$BIN" --install "$TMP/good.iso" --dest "$TMP/dest" --force
grep -q '12 copiados, 0 ya estaban' "$TMP/out.log" && ok "--force recopió los 12" || bad "--force"

if [ -n "${BT2_TEST_PAL_ISO:-}" ] && [ -f "$BT2_TEST_PAL_ISO" ]; then
    run_expect "rechazo de región PAL" 1 "$BIN" --install "$BT2_TEST_PAL_ISO" --dest "$TMP/pal_dest"
    grep -q 'edición PAL' "$TMP/out.log" && ok "mensaje de región PAL" || bad "mensaje de región PAL"
fi

if command -v python3 >/dev/null 2>&1 && [ -f "$ROOT/setup/install.py" ]; then
    run_expect "install.py con la misma ISO" 0 python3 "$ROOT/setup/install.py" --iso "$TMP/good.iso" --dest "$TMP/py_dest"
    (cd "$TMP/dest" && find . -type f ! -name .installed -printf '%s %p\n' | sort -k2) >"$TMP/native.list"
    (cd "$TMP/py_dest" && find . -type f ! -name .installed -printf '%s %p\n' | sort -k2) >"$TMP/py.list"
    if diff -u "$TMP/native.list" "$TMP/py.list" >/dev/null; then
        ok "listado idéntico a install.py"
    else
        bad "listado distinto a install.py"
    fi
fi

rm -f "$TMP/dest/DATA/ZS2USOP.SFD"
run_expect "check con archivo faltante" 1 "$BIN" --check --dest "$TMP/dest"

echo "== $PASS ok, $FAIL fallos =="
[ "$FAIL" -eq 0 ]
