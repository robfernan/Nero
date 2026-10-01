#pragma once
#include <SDL.h>

namespace nero::renderer2d {

void init(SDL_Renderer* renderer);
void shutdown();

void begin();
void end();

void draw_quad(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

} // namespace nero::renderer2d
