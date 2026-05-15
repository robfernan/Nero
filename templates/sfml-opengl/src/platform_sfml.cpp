#ifndef BUILD_FOR_WEB
#include "platform.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "core.h"
#include <chrono>
#include <SFML/OpenGL.hpp>

struct SFMLPlatform : Platform {
    sf::RenderWindow window;
    std::chrono::steady_clock::time_point last;
    bool initedCore = false;
    bool init(int width, int height, const char* title) override {
        sf::ContextSettings settings;
        settings.depthBits = 24;
        window.create({(unsigned)width,(unsigned)height}, title, sf::Style::Default, settings);
        window.setVerticalSyncEnabled(true);
        last = std::chrono::steady_clock::now();
        return window.isOpen();
    }
    void poll_events() override {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
        }
    }
    bool should_close() override { return !window.isOpen(); }
    void swap_buffers() override { window.display(); }
    void run_core_frame() {
        using namespace std::chrono;
        auto now = steady_clock::now();
        float dt = duration_cast<duration<float>>(now - last).count();
        last = now;

        if (!initedCore) {
            // try to load default script from "game/main.lua"
            core::init("game/main.lua");
            initedCore = true;
        }

        core::update(dt);

        // clear and basic OpenGL clear color (host-side)
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        core::render();

        // fetch draw commands from core and render them using SFML shapes (mixing with OpenGL)
        auto rects = core::consume_draws();
        if (!rects.empty()) {
            window.pushGLStates();
            for (auto &r : rects) {
                sf::RectangleShape shape({r.w, r.h});
                shape.setPosition(r.x, r.y);
                sf::Color c(
                    static_cast<sf::Uint8>(r.r * 255.0f),
                    static_cast<sf::Uint8>(r.g * 255.0f),
                    static_cast<sf::Uint8>(r.b * 255.0f),
                    static_cast<sf::Uint8>(r.a * 255.0f)
                );
                shape.setFillColor(c);
                window.draw(shape);
            }
            window.popGLStates();
        }
    }
};

Platform* create_platform() { return new SFMLPlatform(); }
#endif
