add_library(nero_platform_sdl STATIC
    platform_sdl.cpp
)

target_include_directories(nero_platform_sdl
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}
)
target_link_libraries(nero_platform_sdl PRIVATE ${SDL2_LIB_DIR}/SDL2.lib)
