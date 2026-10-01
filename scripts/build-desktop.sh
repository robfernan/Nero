#!/usr/bin/env bash
set -euo pipefail
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j$(nproc || 4)
echo "Built desktop binary in build/"
