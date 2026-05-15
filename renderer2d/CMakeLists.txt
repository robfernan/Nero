add_library(nero_renderer2d
    renderer2d.cpp
    renderer2d.h
    quad_batch.cpp
    quad_batch.h
)

target_include_directories(nero_renderer2d
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(nero_renderer2d
    PUBLIC
        nero_core
)
