#pragma once

#include <SDL.h>
#include <core/core.h>

namespace nero::platform {

struct SdlContext {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Uint32 start_ticks = 0;
};

SdlContext& get_context();
bool init(const EngineConfig& config);
void shutdown();
void process_events();
float get_delta_time();

} // namespace nero::platform
