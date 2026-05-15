SFML + OpenGL Template (Web-friendly)

Overview
- Minimal starter showing a platform abstraction so the same core can be wired to SFML (desktop) or a Web backend (WebGL) using Emscripten.

Build (Desktop)

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

Build (Web - Emscripten)

```bash
source /path/to/emsdk/emsdk_env.sh
mkdir build && cd build
emcmake cmake .. -DBUILD_FOR_WEB=ON
emmake make -j4
```

Notes
- This template intentionally keeps the web backend as a thin stub that you can implement using raw WebGL via Emscripten glue or by exposing a C API the JS wrapper will call.
- For reliable web builds, design your renderer around GLES2/GLES3 compatible API and write GLSL ES shaders.
- WebGPU support is feasible but requires a separate adapter layer (Dawn/Native or JS bindings) and a different shader language path (WGSL).
