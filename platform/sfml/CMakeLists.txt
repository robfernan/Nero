find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_library(nero_platform_sfml
    platform_sfml.cpp
    platform_sfml.h
)

target_include_directories(nero_platform_sfml
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(nero_platform_sfml
    PUBLIC
        sfml-system
        sfml-window
        sfml-graphics
        nero_core
        nero_renderer2d
        nero_renderer3d
)
