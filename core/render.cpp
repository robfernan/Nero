#include "core.h"
#include <renderer2d.h>
#include <renderer3d.h>
#include <platform_sfml.h>
#include <SFML/Graphics.hpp>


namespace nero {

void render() {
    auto& ctx = platform::get_context();
    auto& window = ctx.window;

    renderer2d::init(&window);
    renderer2d::begin();

    renderer2d::draw_quad(100.0f, 100.0f, 200.0f, 150.0f, sf::Color::Red);

    renderer2d::end();
    renderer2d::shutdown();
}

} // namespace nero
