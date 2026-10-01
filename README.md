# Nero Engine

A cross-platform game engine using SDL2 as the universal backend across all platforms. Write once in C++ with Lua scripting, deploy to desktop, web, PSP, PS2, and PS1.

## Platform Support & Frameworks

| Platform | Backend | Toolchain | Status |
|----------|---------|-----------|--------|
| Desktop (Win/Mac/Linux) | SDL2 | GCC/Clang/MSVC | ✅ Working |
| Web | SDL2 + Emscripten → WebGL | Emscripten SDK | 🚧 In Progress |
| Android | SDL2 | Android NDK | 🚧 Planned |
| PSP | SDL2 | PSPSDK (psp-gcc) | 🚧 Planned |
| PS2 | SDL2 | ps2dev (CMake) | 🚧 Planned |
| PS1 | SDL2 Compat Layer + PSn00bSDK | PSn00bSDK toolchain | 🔮 Future |

### Architecture

```
Your Game Code (C++ + Lua scripts)
    ↓
Nero Engine API
    ↓
├── Real SDL2 → Desktop, Web, Android, PSP, PS2
└── SDL2 Compatibility Layer → PS1 (PSn00bSDK underneath)
```

The PS1 compatibility layer implements the SDL2 API using PSn00bSDK's hardware primitives:
- `SDL_BlitSurface()` → PS1 hardware sprites (`SPRT`)
- `SDL_FillRect()` → PS1 `TILE` primitive
- `SDL_RenderPresent()` → Ordering tables + `VSync()`
- Input via PS1 PAD library mapped to SDL events

---

## 🚀 Current Status

The engine successfully initializes the SFML desktop host and renders its first quad using the 2D renderer.

### Screenshot (May 15, 2026 as of 2:32PM)

![Nero Engine Screenshot](/assets/screenshots/Screenshot_2_32PM_5_15_26.png)

---

## 🧩 Modules

- **Core** — engine lifecycle, update loop, render dispatch
- **Renderer2D** — immediate-mode quad rendering via SDL2
- **Renderer3D** — mesh + shader system (scaffolding)
- **Platform Backends**
  - Desktop: Real SDL2
  - Web: SDL2 compiled to WebGL via Emscripten
  - Android: SDL2 with Android NDK
  - PSP: SDL2 with PSPSDK toolchain
  - PS2: SDL2 with ps2dev toolchain
  - PS1: Custom SDL2 compatibility layer over PSn00bSDK  

---

## 🛠 Build Instructions

### Desktop (SDL2)

```bash
cmake -S . -B build
cmake --build build
./build/nero_desktop
```

Requires: SDL2 development libraries installed on your system.

### Web (Emscripten)

```bash
emcmake cmake -S . -B build-web
emmake make -C build-web
```

Requires: [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)


---

## 📌 Next Milestones

### Immediate (Get Desktop Working)
- [ ] Fix render loop to not reinit/shutdown every frame
- [ ] Add proper game loop with fixed timestep
- [ ] Implement basic input handling via SDL2 events
- [ ] Get Lua scripting integrated for gameplay code

### Short-term (Cross-Platform Foundation)
- [ ] Add texture loading and sprite rendering
- [ ] Implement camera/transform system
- [ ] Build web version using Emscripten
- [ ] Android build with SDL2 + NDK
- [ ] Test PSP build with PSPSDK toolchain

### Medium-term (Console Ports)
- [ ] PS2 port using SDL2 + ps2dev
- [ ] PS1 SDL2 compatibility layer over PSn00bSDK
- [ ] Asset pipeline for all platforms
