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

target_include_directories(glad_lib PUBLIC ${GLAD_DIR}/include} "${GLM_DIR}")

# Now, define your executable
add_executable(04_moving_triangle main_moving_triangle.cpp)

# Link your executable against GLFW, GL, AND the new glad_lib
# Add common X11 dependencies for GLFW
target_link_libraries(04_moving_triangle PRIVATE glfw GL glad_lib Xrandr Xi Xxf86vm Xcursor Xinerama dl)