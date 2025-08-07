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
add_executable(05_uniforms_and_transformations main_transformation.cpp)

# Link your executable against GLFW, GL, AND the new glad_lib
# Add common X11 dependencies for GLFW
target_link_libraries(05_uniforms_and_transformations PRIVATE glfw GL glad_lib Xrandr Xi Xxf86vm Xcursor Xinerama dl)