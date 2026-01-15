#!/bin/bash
set -e

# Go to repo root (script location)
cd "$(dirname "$0")"

mkdir -p build
cd build

BUILD_TYPE="Release"

for arg in "$@"; do
    case "$arg" in
        -debug)
            BUILD_TYPE="Debug"
            ;;
    esac
done

GENERATOR_ARGS=()
if command -v ninja &> /dev/null; then
    GENERATOR_ARGS=(-G Ninja)
fi

cmake .. \
    "${GENERATOR_ARGS[@]}" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DOPENGEDCOM_BUILD_TESTS=ON

cmake --build .

./tests/OpenGedcomTests

