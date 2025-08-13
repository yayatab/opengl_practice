
add_executable(a01_hello_window hello_window.cc)

target_link_libraries(a01_hello_window PRIVATE glfw GL glad_lib dl)