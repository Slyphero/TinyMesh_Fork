#!/usr/bin/env bash
# build.sh — configure & build AppTinyMesh outside Qt Creator
set -euo pipefail

# --- Config ---------------------------------------------------------------
QT_PREFIX="${HOME}/Qt/6.11.2/gcc_64"   # override: QT_PREFIX=/path/to/qt ./build.sh
BUILD_DIR="build"
BUILD_TYPE="${BUILD_TYPE:-Release}"     # override: BUILD_TYPE=Debug ./build.sh

# --- Resolve project root (dir containing this script) --------------------
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# --- Sanity checks --------------------------------------------------------
if [[ ! -d "$QT_PREFIX" ]]; then
    echo "ERROR: Qt prefix not found at '$QT_PREFIX'" >&2
    echo "       Set QT_PREFIX to your Qt installation, e.g.:" >&2
    echo "       QT_PREFIX=\$HOME/Qt/6.11.2/gcc_64 ./build.sh" >&2
    exit 1
fi

# --- Create build dir if missing -----------------------------------------
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# --- Configure ------------------------------------------------------------
echo "==> Configuring (${BUILD_TYPE}) with Qt at ${QT_PREFIX}"
cmake .. \
    -DCMAKE_PREFIX_PATH="$QT_PREFIX" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

# --- Build -----------------------------------------------------------------
JOBS="$(nproc)"
echo "==> Building with ${JOBS} jobs"
cmake --build . -j"$JOBS"

# --- Done ------------------------------------------------------------------
EXE="$PWD/AppTinyMesh"
if [[ -f "$EXE" ]]; then
    echo "==> Build OK: $EXE"
    echo "    Run it with: cd $(dirname "$EXE") && ./AppTinyMesh"
else
    echo "WARNING: build finished but executable not found at $EXE" >&2
fi
