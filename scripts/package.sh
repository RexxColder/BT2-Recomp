#!/bin/sh
# Arma el producto para Linux:  dist/BT2/  y  dist/BT2-linux-x86_64-<versión>.tar.gz
#
#   BT2/
#     BT2            el juego (port/build/full/bt2full)
#     BT2-setup      el instalador (setup/build/bt2-setup)
#     gamedata/      vacía (sólo un LEEME): la llena BT2-setup con la ISO del jugador
#     saves/         vacía
#     textos/        textos del port (package/textos)
#     logs/          vacía; el juego deja ahí BT2.log (se pisa en cada corrida)
#     LEEME.txt  LICENSE  VERSION
#
# Antes hay que compilar: port/tools/build_full.py + link_full.py y setup/build.sh.
# Nunca empaqueta datos del juego: si encuentra algo que lo parezca, corta.
set -eu
cd "$(dirname "$0")/.."

GAME=port/build/full/bt2full
SETUP=setup/build/bt2-setup
for f in "$GAME" "$SETUP"; do
    [ -x "$f" ] || { echo "falta $f: compilalo primero" >&2; exit 1; }
done

VER="${BT2_VERSION:-$(git describe --tags --always --dirty)}"
OUT=dist/BT2
rm -rf "$OUT"
mkdir -p "$OUT/gamedata" "$OUT/saves" "$OUT/textos" "$OUT/logs"

install -m 755 "$GAME" "$OUT/BT2"
install -m 755 "$SETUP" "$OUT/BT2-setup"
strip --strip-debug "$OUT/BT2" "$OUT/BT2-setup" 2>/dev/null || true
cp package/LEEME.txt LICENSE "$OUT/"
cp package/gamedata/LEEME.txt "$OUT/gamedata/"
cp package/textos/*.txt "$OUT/textos/"
printf '%s\n%s\n' "$VER" "$(date -u +%Y-%m-%dT%H:%MZ)" > "$OUT/VERSION"

# Guardia: nada del disco del juego ni de partidas.
bad=$(find "$OUT" \( -iname 'SLUS*' -o -iname '*.afs' -o -iname '*.iso' -o -iname '*.bin' -o -iname '*.elf' \
        -o -iname 'DBZP*' -o -path '*/saves/*' -o -path '*/gamedata/*' ! -name LEEME.txt \) -print)
if [ -n "$bad" ]; then
    echo "ABORTO: el paquete contiene algo que parece dato del juego o partida:" >&2
    echo "$bad" >&2
    exit 1
fi

TAR="dist/BT2-linux-x86_64-$VER.tar.gz"
tar -C dist -czf "$TAR" BT2
echo "listo: $OUT  y  $TAR ($(du -h "$TAR" | cut -f1))"
