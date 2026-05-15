cmake_minimum_required(VERSION 3.16)
project(sfml_opengl_template LANGUAGES CXX)

option(USE_IMGUI "Enable ImGui integration" OFF)
option(BUILD_FOR_WEB "Build for Web (Emscripten)" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT BUILD_FOR_WEB)
  find_package(SFML 2.5 COMPONENTS window system graphics REQUIRED)
endif()

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

if(NOT BUILD_FOR_WEB)
  target_include_directories(${PROJECT_NAME} PRIVATE include)
  target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics)
  # Try to find Lua
  find_package(Lua)
  if(Lua_FOUND)
    message(STATUS "Found Lua: ${LUA_VERSION}")
    target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LUA_LIBRARIES})
  else()
    message(WARNING "Lua not found - Lua gameplay scripts will not be available. Install Lua dev packages or adjust CMake.")
  endif()
else()
  target_include_directories(${PROJECT_NAME} PRIVATE include)
  # When building with emscripten, user should configure via emcmake/emmake
endif()
