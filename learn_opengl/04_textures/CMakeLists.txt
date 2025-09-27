get_filename_component(CMAKELISTS_NAME "${CMAKE_CURRENT_LIST_FILE}" NAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${CMAKE_CURRENT_LIST_DIR}")
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/out/${CMAKE_CURRENT_LIST_DIR}/resources/")


configure_file(
        "shaders/vertex.vert"
        "${OUTPUT_DIR}/vertex.vert"
        COPYONLY
)

configure_file(
        "shaders/fragment.frag"
        "${OUTPUT_DIR}/fragment.frag"
        COPYONLY
)

configure_file(
        "resources/wooden_container.jpg"
        "${OUTPUT_DIR}/wooden_container.jpg"
        COPYONLY
)


add_executable(04_textures_01_box ./01_texture.cc)
target_link_libraries(04_textures_01_box PRIVATE glfw GL glad_lib dl tools stb_lib)
