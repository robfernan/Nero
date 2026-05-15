#include "renderer2d.h"

namespace nero::renderer2d {

static sf::RenderTarget* g_target = nullptr;

void init(sf::RenderTarget* target) {
    g_target = target;
}

void shutdown() {
    g_target = nullptr;
}

void begin() {
    // nothing yet
}

void end() {
    // nothing yet
}

void draw_quad(float x, float y, float w, float h, const sf::Color& color) {
    if (!g_target) return;

    sf::RectangleShape rect;
    rect.setPosition({x, y});
    rect.setSize({w, h});
    rect.setFillColor(color);
    g_target->draw(rect);
}

} // namespace nero::renderer2d
