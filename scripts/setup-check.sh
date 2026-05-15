#!/usr/bin/env bash
set -euo pipefail
OUT=./scripts/setup-report.txt
echo "Setup check report" > "$OUT"

check_cmd() {
  if command -v "$1" >/dev/null 2>&1; then
    echo "$1: ok" | tee -a "$OUT"
  else
    echo "$1: MISSING" | tee -a "$OUT"
  fi
}

echo "Checking required commands..." | tee -a "$OUT"
check_cmd cmake
check_cmd gcc
check_cmd g++
check_cmd pkg-config
check_cmd python3
check_cmd node

echo "Checking libraries (Debian/Ubuntu hints)" | tee -a "$OUT"
PKGS=(libsfml-dev liblua5.3-dev libglew-dev)
for p in "${PKGS[@]}"; do
  dpkg -s "$p" >/dev/null 2>&1 && echo "$p: installed" | tee -a "$OUT" || echo "$p: not installed (apt: sudo apt install $p)" | tee -a "$OUT"
done

echo "If you're targeting Android, ensure ANDROID_NDK_HOME is set and the NDK is installed." | tee -a "$OUT"
echo "Console SDKs must be installed manually (PSn00bSDK, AthenaEnv, PSPSDK). See docs/ for links." | tee -a "$OUT"

echo "Done. See $OUT" | tee -a "$OUT"
