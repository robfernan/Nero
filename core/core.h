#pragma once
#include <cstdint>

namespace nero {

struct EngineConfig {
    int width  = 1280;
    int height = 720;
    const char* title = "Nero";
};

bool init(const EngineConfig& config);
void shutdown();

void update(float dt);
void render();

bool is_running();
void request_exit();

} // namespace nero
