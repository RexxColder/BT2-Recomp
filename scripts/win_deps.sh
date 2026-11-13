#!/bin/sh
# Dependencias del build de Windows (mingw-w64 cruzado): SDL3 y ffmpeg para win64, en port/build/win/{SDL3,ffmpeg}.
# Versiones fijas y verificadas por sha256. ffmpeg es la build LGPL compartida de BtbN (las DLLs viajan con el .exe).
#   scripts/win_deps.sh            (una vez; vuelve a bajar sólo lo que falta)
# BtbN borra sus autobuilds viejos cada tanto: si la descarga da 404, elegí otro tag (n9.0.x lgpl shared) de
# https://github.com/BtbN/FFmpeg-Builds/releases y actualizá FFMPEG_URL y FFMPEG_SHA256.
set -eu
cd "$(dirname "$0")/.."
DEST=port/build/win
SDL3_URL=https://github.com/libsdl-org/SDL/releases/download/release-3.4.20/SDL3-devel-3.4.20-mingw.tar.gz
SDL3_SHA256=d2d3bf3fb97a90b22e908a306d7362631ef1bab229d988fe6669595dc29cd9ed
FFMPEG_URL=https://github.com/BtbN/FFmpeg-Builds/releases/download/autobuild-2026-11-12-15-40/ffmpeg-n9.0.2-57-gd838f9f9ae-win64-lgpl-shared-9.0.zip
FFMPEG_SHA256=85997c85effa2ebea19eac63c76adedb9d381b0c3d22a09cd69b32f9f66c4d30

mkdir -p "$DEST/dl"
get() {   # get <url> <archivo> <sha256>
    if [ ! -f "$2" ] || ! echo "$3  $2" | sha256sum -c --quiet - 2>/dev/null; then
        echo "bajando $(basename "$1")"
        curl -fSL -o "$2.part" "$1" || { echo "no se pudo bajar $1" >&2; exit 1; }
        mv "$2.part" "$2"
    fi
    echo "$3  $2" | sha256sum -c --quiet - || { echo "sha256 distinto: $2" >&2; exit 1; }
}

if [ ! -f "$DEST/SDL3/lib/libSDL3.dll.a" ]; then
    get "$SDL3_URL" "$DEST/dl/sdl3.tar.gz" "$SDL3_SHA256"
    rm -rf "$DEST/SDL3" "$DEST/dl/sdl3" && mkdir -p "$DEST/dl/sdl3"
    tar -C "$DEST/dl/sdl3" -xzf "$DEST/dl/sdl3.tar.gz"
    mv "$DEST/dl/sdl3"/SDL3-*/x86_64-w64-mingw32 "$DEST/SDL3"
    rm -rf "$DEST/dl/sdl3"
fi
if [ ! -f "$DEST/ffmpeg/lib/libavformat.dll.a" ]; then
    get "$FFMPEG_URL" "$DEST/dl/ffmpeg.zip" "$FFMPEG_SHA256"
    rm -rf "$DEST/ffmpeg" "$DEST/dl/ffmpeg" && mkdir -p "$DEST/dl/ffmpeg"
    (cd "$DEST/dl/ffmpeg" && unzip -q ../ffmpeg.zip)
    mv "$DEST/dl/ffmpeg"/ffmpeg-* "$DEST/ffmpeg"
    rm -rf "$DEST/dl/ffmpeg"
fi
echo "listo: $DEST/SDL3 y $DEST/ffmpeg"
