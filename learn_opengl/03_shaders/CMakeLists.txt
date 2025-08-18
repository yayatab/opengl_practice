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

configure_file(
        "vertex_shader_prog_colour.glsl"
        "${OUTPUT_DIR}/vertex_shader_prog_colour.glsl"
        COPYONLY
)

configure_file(
        "fragment_prog_colour.frag"
        "${OUTPUT_DIR}/fragment_prog_colour.frag"
        COPYONLY
)

add_executable(a03_hello_shaders hello_uniforms.cc)
target_link_libraries(a03_hello_shaders PRIVATE glfw GL glad_lib dl)

add_executable(a03_hello_attributes more_attributes.cc)
target_link_libraries(a03_hello_attributes PRIVATE glfw GL glad_lib dl)
