add_library(nero_core
    core.cpp
    core.h
    update.cpp
    render.cpp
    lua_bindings.cpp
)

target_include_directories(nero_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/renderer2d
        ${CMAKE_SOURCE_DIR}/platform/sdl
)

target_link_libraries(nero_core PRIVATE ${SDL2_LIB_DIR}/SDL2.lib)
