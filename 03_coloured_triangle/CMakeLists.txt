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

target_include_directories(glad_lib PUBLIC ${GLAD_DIR}/include)

add_executable(03_coloured_triangle main_triangle.cpp)

target_link_libraries(03_coloured_triangle PRIVATE glfw GL glad_lib Xrandr Xi Xxf86vm Xcursor Xinerama dl)