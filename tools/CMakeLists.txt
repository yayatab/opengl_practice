add_library(tools STATIC
        src/shader.cc
        src/window.cc
)

target_include_directories(tools PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(tools glad_lib glfw GL dl)