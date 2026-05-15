#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "core.h"
#include "platform_sfml.h"

using namespace nero;

int main() {
    platform::SfmlContext& ctx = platform::get_context();

    EngineConfig cfg;
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.title  = "Nero (SFML Desktop)";

    sf::VideoMode mode(cfg.width, cfg.height);
    ctx.window.create(mode, cfg.title, sf::Style::Default);
    ctx.window.setVerticalSyncEnabled(true);

    if (!init(cfg)) {
        return -1;
    }

    while (is_running() && ctx.window.isOpen()) {
        sf::Event event;
        while (ctx.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                request_exit();
                ctx.window.close();
            }
        }

        float dt = ctx.clock.restart().asSeconds();
        update(dt);

        ctx.window.clear(sf::Color::Black);
        render();
        ctx.window.display();
    }

    shutdown();
    return 0;
}
