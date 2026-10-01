cmake_minimum_required(VERSION 3.20)
project(NeroEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# SDL2 paths - use local installation
set(SDL2_ROOT "${CMAKE_SOURCE_DIR}/SDL2-2.30.11")
set(SDL2_INCLUDE_DIR "${SDL2_ROOT}/include")
if(WIN32)
    set(SDL2_LIB_DIR "${SDL2_ROOT}/lib/x64")
else()
    set(SDL2_LIB_DIR "${SDL2_ROOT}/lib")
endif()

# Make SDL2 include path available to all targets
include_directories(${SDL2_INCLUDE_DIR})

# Add engine modules
add_subdirectory(core)
add_subdirectory(renderer2d)
add_subdirectory(renderer3d)
add_subdirectory(platform/sdl)

# Nero Engine meta-target
add_library(nero_engine INTERFACE)

# Make all module headers visible to each other
target_include_directories(nero_engine INTERFACE
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/renderer2d
    ${CMAKE_SOURCE_DIR}/renderer3d
    ${CMAKE_SOURCE_DIR}/platform/sdl
)

target_link_libraries(nero_engine
    INTERFACE
        nero_core
        nero_renderer2d
        nero_renderer3d
)

# Desktop host executable (SDL2)
add_executable(nero_desktop
    platform/sdl/main.cpp
)

target_link_libraries(nero_desktop
    PRIVATE
        nero_core
        nero_renderer2d
        nero_renderer3d
        nero_platform_sdl
        ${SDL2_LIB_DIR}/SDL2.lib
        ${SDL2_LIB_DIR}/SDL2main.lib
)

install(TARGETS nero_desktop)
