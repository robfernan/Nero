#pragma once

namespace core {
    struct DrawRect { float x,y,w,h; float r,g,b,a; };
    // Initialize core and load Lua gameplay scripts from `script_path` (optional)
    bool init(const char* script_path = nullptr);
    void update(float dt);
    void render();
    void shutdown();

    // Push a rectangle draw command from native or Lua
    void push_draw_rect(float x, float y, float w, float h, float r, float g, float b, float a);
    // Consume pending draws (returns vector copy and clears internal queue)
    std::vector<DrawRect> consume_draws();
}
