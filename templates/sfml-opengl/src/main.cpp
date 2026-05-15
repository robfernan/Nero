#include <cstdio>
#include "platform.h"

int main() {
    Platform* plat = create_platform();
    if (!plat) {
        std::fprintf(stderr, "No platform available\n");
        return 1;
    }

    if (!plat->init(1280, 720, "SFML OpenGL Template"))
        return 1;

    while (!plat->should_close()) {
        plat->poll_events();

        // simple clear (app core should call renderer)
        // clear is done in renderer implementation

        plat->swap_buffers();
    }

    delete plat;
    return 0;
}
