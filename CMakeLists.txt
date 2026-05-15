cmake_minimum_required(VERSION 3.20)
project(NeroEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add engine modules
add_subdirectory(core)
add_subdirectory(renderer2d)
add_subdirectory(renderer3d)
add_subdirectory(platform/sfml)

# Nero Engine meta-target
add_library(nero_engine INTERFACE)

# Make all module headers visible to each other
target_include_directories(nero_engine INTERFACE
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/renderer2d
    ${CMAKE_SOURCE_DIR}/renderer3d
    ${CMAKE_SOURCE_DIR}/platform/sfml
)

target_link_libraries(nero_engine
    INTERFACE
        nero_core
        nero_renderer2d
        nero_renderer3d
)

# Desktop host executable (SFML)
add_executable(nero_desktop
    platform/sfml/main.cpp
)

target_link_libraries(nero_desktop
    PRIVATE
        nero_core
        nero_renderer2d
        nero_renderer3d
        nero_platform_sfml
)


install(TARGETS nero_desktop)
