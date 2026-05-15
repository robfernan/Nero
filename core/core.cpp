#include "core.h"

namespace nero {

static bool g_running = false;
static EngineConfig g_config{};

bool init(const EngineConfig& config) {
    g_config = config;
    g_running = true;

    // TODO: init Lua, resources, renderer, etc.
    return true;
}

void shutdown() {
    g_running = false;

    // TODO: free resources, Lua, renderer, etc.
}

bool is_running() {
    return g_running;
}

void request_exit() {
    g_running = false;
}

} // namespace nero
