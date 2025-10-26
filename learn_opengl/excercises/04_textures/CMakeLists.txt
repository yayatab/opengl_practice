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
        "shaders/fragment_two_textures.frag"
        "${OUTPUT_DIR}/fragment_two_textures.frag"
        COPYONLY
)

configure_file(
        "resources/wooden_container.jpg"
        "${OUTPUT_DIR}/wooden_container.jpg"
        COPYONLY
)

configure_file(
        "resources/awesomeface.png"
        "${OUTPUT_DIR}/awesomeface.png"
        COPYONLY
)


add_executable(ex_0401_only_smily_straight ./01_smiley.cc)
target_link_libraries(ex_0401_only_smily_straight PRIVATE glfw GL glad_lib dl tools stb_lib)


add_executable(ex_0402_wrapping ./02_texture_wrapping.cc)
target_link_libraries(ex_0402_wrapping PRIVATE glfw GL glad_lib dl tools stb_lib)

add_executable(ex_0403_blending ./03_texture_blending.cc)
target_link_libraries(ex_0403_blending PRIVATE glfw GL glad_lib dl tools stb_lib)

