#!/bin/sh
# Arma el AppImage portable:  dist/BT2-linux-x86_64-<versión>.tar.gz  ->  BT2/BT2.AppImage (+ LEEME, LICENSE)
#
# Antes: el C del juego compilado en el host (port/tools/build_full.py); no depende de la glibc.
# Acá, en un contenedor Ubuntu 22.04 (glibc 2.35, ver Containerfile): código del host, renderer, ImGui, relleno C++,
# el enlace (port/tools/link_full.py con salida en port/build/full_appimage) y BT2-setup. SDL3 y el ffmpeg mínimo
# del contenedor viajan en el AppImage.
#   podman build -t bt2-appimage package/appimage     (una vez)
#   BT2_VERSION=v1.0.1 package/appimage/build.sh
set -eu
cd "$(dirname "$0")/../.."
ROOT="$(pwd)"
IMG="${BT2_APPIMAGE_IMG:-bt2-appimage}"
VER="${BT2_VERSION:-$(git describe --tags --always --dirty)}"
OUT=port/build/full_appimage

# los shaders se generan en el host (el contenedor no tiene el compilador de SPIR-V)
[ -f port/build/full/gen/shaders.h ] || { echo "falta port/build/full/gen/shaders.h: enlazá una vez en el host" >&2; exit 1; }
mkdir -p "$OUT/gen"
cp -p port/build/full/gen/shaders.h "$OUT/gen/"

# el árbol se monta en la misma ruta (los enlaces simbólicos a disc/, build/, tools/ apuntan al checkout de al lado)
MNT="$(dirname "$ROOT")"
podman run --rm --userns=keep-id -v "$MNT:$MNT" -w "$ROOT" \
    -e BT2_FULL_OUT="$OUT" -e BT2_NO_CAP=1 -e APPIMAGE_EXTRACT_AND_RUN=1 -e VER="$VER" -e OUT="$OUT" \
    "$IMG" sh -eu -c '
python3 port/tools/link_full.py | tail -3
cmake -S setup -B setup/build-appimage -DCMAKE_BUILD_TYPE=Release >/dev/null
cmake --build setup/build-appimage -j"$(nproc)" | tail -1

A=dist/AppDir
rm -rf "$A" && mkdir -p "$A/usr/bin" "$A/usr/lib" "$A/usr/share/bt2/textos"
install -m 755 "$OUT/bt2full" "$A/usr/bin/BT2"
install -m 755 setup/build-appimage/bt2-setup "$A/usr/bin/BT2-setup"
strip --strip-debug "$A/usr/bin/BT2" "$A/usr/bin/BT2-setup"
cp -L /usr/local/lib/libSDL3.so.0 /usr/local/lib/libavformat.so.* /usr/local/lib/libavcodec.so.* \
      /usr/local/lib/libavutil.so.* /usr/local/lib/libswscale.so.* "$A/usr/lib/" 2>/dev/null
find "$A/usr/lib" -name "*.so.*.*" -delete   # sólo los nombres que pide el enlazador (SONAME)
cp package/textos/*.txt "$A/usr/share/bt2/textos/"
cp package/appimage/LEEME.txt "$A/usr/share/bt2/"
cp package/appimage/AppRun package/appimage/bt2.desktop package/appimage/bt2.png "$A/"
echo "--- dependencias del juego fuera del AppImage:"
LD_LIBRARY_PATH="$A/usr/lib" ldd "$A/usr/bin/BT2" | grep -vE "usr/lib/|linux-vdso" | awk "{print \$1}" | tr "\n" " "; echo
echo "--- glibc más nueva pedida: $(objdump -T "$A/usr/bin/BT2" "$A/usr/lib/"*.so* | grep -oE "GLIBC_2\.[0-9]+" | sort -V | tail -1)"
ARCH=x86_64 appimagetool --no-appstream "$A" dist/BT2.AppImage >/dev/null
'

# producto: la carpeta BT2/ con el AppImage; gamedata/, saves/, textos/ y logs/ los crea AppRun al lado
P=dist/appimage/BT2
rm -rf dist/appimage && mkdir -p "$P/gamedata"
mv dist/BT2.AppImage "$P/BT2.AppImage"
cp package/appimage/LEEME.txt LICENSE "$P/"
cp package/gamedata/LEEME.txt "$P/gamedata/"
printf '%s\n%s\n' "$VER" "$(date -u +%Y-%m-%dT%H:%MZ)" > "$P/VERSION"
TAR="BT2-linux-x86_64-$VER.tar.gz"
tar -C dist/appimage -czf "dist/$TAR" BT2
(cd dist && sha256sum "$TAR" > SHA256SUMS)
echo "listo: dist/$TAR ($(du -h "dist/$TAR" | cut -f1))"
