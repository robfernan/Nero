#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace nero::platform {

struct SfmlContext {
    sf::RenderWindow window;
    sf::Clock        clock;
};

SfmlContext& get_context();

} // namespace nero::platform
