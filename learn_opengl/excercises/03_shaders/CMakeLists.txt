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

configure_file(
        "shaders/moving.glsl"
        "${OUTPUT_DIR}/moving.glsl"
        COPYONLY
)

configure_file(
        "shaders/moving.frag"
        "${OUTPUT_DIR}/moving.frag"
        COPYONLY
)

add_executable(ex_0301_upside_down_triangle upside_down_triangle.cc)
target_link_libraries(ex_0301_upside_down_triangle PRIVATE glfw GL glad_lib dl tools)

add_executable(ex_0302_moving_triangle moving_triangle.cc)
target_link_libraries(ex_0302_moving_triangle PRIVATE glfw GL glad_lib dl tools)
# i did two and three in hte same executable :D
# to ansewr why hte bottom left is black:
# the interpolated position  is 0.0. which is black.