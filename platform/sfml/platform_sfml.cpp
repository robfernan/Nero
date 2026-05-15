#include "platform_sfml.h"
#include "core.h"

namespace nero::platform {

static SfmlContext g_ctx;

SfmlContext& get_context() {
    return g_ctx;
}

} // namespace nero::platform
