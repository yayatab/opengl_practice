get_filename_component(CMAKELISTS_NAME "${CMAKE_CURRENT_LIST_FILE}" NAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${CMAKE_CURRENT_LIST_DIR}")
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/out/${CMAKE_CURRENT_LIST_DIR}/resources/")

configure_file(
        "shaders/upside_down.glsl"
        "${OUTPUT_DIR}/upside_down.glsl"
        COPYONLY
)

configure_file(
        "shaders/upside_down.frag"
        "${OUTPUT_DIR}/upside_down.frag"
        COPYONLY
)
#
#configure_file(
#        "vertex_shader_prog_colour.glsl"
#        "${OUTPUT_DIR}/vertex_shader_prog_colour.glsl"
#        COPYONLY
#)
#
#configure_file(
#        "fragment_prog_colour.frag"
#        "${OUTPUT_DIR}/fragment_prog_colour.frag"
#        COPYONLY
#)

add_executable(ex_03_upside_down_triangle upside_down_triangle.cc)
target_link_libraries(ex_03_upside_down_triangle PRIVATE glfw GL glad_lib dl tools)

#add_executable(a03_excersize_1 hello_uniforms.cc)
#target_link_libraries(a03_excersize_1 PRIVATE glfw GL glad_lib dl tools)

#add_executable(a03_hello_attributes more_attributes.cc)
#target_link_libraries(a03_hello_attributes PRIVATE glfw GL glad_lib dl)
