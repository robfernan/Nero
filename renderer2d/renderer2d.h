#pragma once
#include <SFML/Graphics.hpp>

namespace nero::renderer2d {

void init(sf::RenderTarget* target);
void shutdown();

void begin();
void end();

void draw_quad(float x, float y, float w, float h, const sf::Color& color);

} // namespace nero::renderer2d
