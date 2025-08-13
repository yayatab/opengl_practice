set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

configure_file(
        "fragment_shader_source.glsl"
        "${OUTPUT_DIR}/fragment_shader_source.glsl"
        COPYONLY
)
configure_file(
        "shader_source.glsl"
        "${OUTPUT_DIR}/shader_source.glsl"
        COPYONLY
)

add_executable(07_textured_square main_textured_square.cpp)

target_link_libraries(07_textured_square PRIVATE glfw GL glad_lib Xrandr Xi Xxf86vm Xcursor Xinerama dl)