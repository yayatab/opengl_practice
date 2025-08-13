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

add_executable(06_square main_square.cpp)

target_link_libraries(06_square PRIVATE glfw GL glad_lib Xrandr Xi Xxf86vm Xcursor Xinerama dl)