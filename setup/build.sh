#!/bin/sh
# Compila la app de setup de BT2.
#   ./build.sh          -> build/bt2-setup
#   ./build.sh --clean  -> borra build/ y compila de cero
# Usa SDL3 (pkg-config) y el Dear ImGui vendorizado en ../port/third_party/imgui.
set -eu
cd "$(dirname "$0")"

if [ "${1:-}" = "--clean" ]; then
    rm -rf build
fi

JOBS="${JOBS:-2}"
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j"$JOBS"

echo "listo: $(pwd)/build/bt2-setup"
