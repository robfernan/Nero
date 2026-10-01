#include "core/core.h"
#include "platform_sdl.h"

using namespace nero;

int main(int argc, char* argv[]) {
    EngineConfig cfg;
    cfg.width = 1280;
    cfg.height = 720;
    cfg.title = "Nero Engine (SDL2)";

    if (!platform::init(cfg)) {
        return -1;
    }

    if (!init(cfg)) {
        platform::shutdown();
        return -1;
    }

    while (is_running()) {
        platform::process_events();

        float dt = platform::get_delta_time();
        update(dt);

        render();
    }

    shutdown();
    platform::shutdown();
    return 0;
}
