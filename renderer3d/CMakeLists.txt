add_library(nero_renderer3d
    renderer3d.cpp
    renderer3d.h
    mesh.cpp
    mesh.h
    shader.cpp
    shader.h
)

target_include_directories(nero_renderer3d
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(nero_renderer3d
    PUBLIC
        nero_core
)
