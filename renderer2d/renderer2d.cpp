#include "renderer2d.h"

namespace nero::renderer2d {

static SDL_Renderer* g_renderer = nullptr;

void init(SDL_Renderer* renderer) {
    g_renderer = renderer;
}

void shutdown() {
    g_renderer = nullptr;
}

void begin() {
    if (g_renderer) {
        SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
    }
}

void end() {
    // Nothing to do - SDL presents on next frame automatically
}

void draw_quad(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    if (!g_renderer) return;

    SDL_SetRenderDrawColor(g_renderer, r, g, b, a);
    SDL_Rect rect = { (int)x, (int)y, (int)w, (int)h };
    SDL_RenderFillRect(g_renderer, &rect);
}

} // namespace nero::renderer2d
