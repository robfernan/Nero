#ifdef BUILD_FOR_WEB
#include "platform.h"
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <cstdio>

struct WebPlatform : Platform {
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = 0;
    bool init(int width, int height, const char* title) override {
        EmscriptenWebGLContextAttributes attrs;
        emscripten_webgl_init_context_attributes(&attrs);
        attrs.alpha = false;
        attrs.depth = true;
        attrs.stencil = false;
        attrs.majorVersion = 2; // try WebGL2
        ctx = emscripten_webgl_create_context("canvas", &attrs);
        if (!ctx) {
            std::fprintf(stderr, "Failed to create WebGL context\n");
            return false;
        }
        emscripten_webgl_make_context_current(ctx);
        return true;
    }
    void poll_events() override {
        // browser handles events; you can bind JS callbacks to call into WASM if needed
    }
    bool should_close() override { return false; }
    void swap_buffers() override { /* browser presents automatically */ }
};

Platform* create_platform() { return new WebPlatform(); }
#endif
