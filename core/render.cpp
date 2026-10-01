#include "core.h"
#include <renderer2d.h>
#include <platform_sdl.h>

namespace nero {

void render() {
    auto& ctx = platform::get_context();

    renderer2d::init(ctx.renderer);
    renderer2d::begin();

    // Clear screen to dark blue
    SDL_SetRenderDrawColor(ctx.renderer, 10, 15, 30, 255);
    SDL_RenderClear(ctx.renderer);

    // Draw a red quad
    renderer2d::draw_quad(100.0f, 100.0f, 200.0f, 150.0f, 255, 50, 50);

    // Draw another colored quad to show it works
    renderer2d::draw_quad(350.0f, 200.0f, 150.0f, 100.0f, 50, 150, 255);

    renderer2d::end();

    // Present the frame
    SDL_RenderPresent(ctx.renderer);
}

} // namespace nero
