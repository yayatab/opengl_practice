set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

configure_file(
        "vertex_shader.glsl"
        "${OUTPUT_DIR}/vertex_shader.glsl"
        COPYONLY
)

configure_file(
        "fragment.frag"
        "${OUTPUT_DIR}/fragment.frag"
        COPYONLY
)

add_executable(a02_hello_triangle hello_triangle.cc)

target_link_libraries(a02_hello_triangle PRIVATE glfw GL glad_lib dl)