#!/usr/bin/env bash
set -euo pipefail
if ! command -v python3 >/dev/null 2>&1; then
  echo "Python3 required to run simple HTTP server for web demo"
  exit 1
fi
echo "Starting dev server in web/ at http://localhost:8000"
cd "$(dirname "$0")/../web"
python3 -m http.server 8000
