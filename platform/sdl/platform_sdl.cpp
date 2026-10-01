#include <stdio.h>
#include "platform_sdl.h"

namespace nero::platform {

static SdlContext g_ctx;

SdlContext& get_context() {
    return g_ctx;
}

bool init(const EngineConfig& config) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }

    Uint32 window_flags = SDL_WINDOW_SHOWN;
#ifdef __EMSCRIPTEN__
    window_flags |= SDL_WINDOW_RESIZABLE;
#endif

    g_ctx.window = SDL_CreateWindow(
        config.title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config.width,
        config.height,
        window_flags
    );

    if (!g_ctx.window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return false;
    }

    g_ctx.renderer = SDL_CreateRenderer(g_ctx.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g_ctx.renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return false;
    }

    g_ctx.start_ticks = SDL_GetTicks();
    return true;
}

void shutdown() {
    if (g_ctx.renderer) {
        SDL_DestroyRenderer(g_ctx.renderer);
        g_ctx.renderer = nullptr;
    }
    if (g_ctx.window) {
        SDL_DestroyWindow(g_ctx.window);
        g_ctx.window = nullptr;
    }
    SDL_Quit();
}

void process_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            nero::request_exit();
        }
    }
}

float get_delta_time() {
    Uint32 current = SDL_GetTicks();
    float dt = (current - g_ctx.start_ticks) / 1000.0f;
    g_ctx.start_ticks = current;
    return dt;
}

} // namespace nero::platform
