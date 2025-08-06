# No cmake_minimum_required or project() here

# First, create a static library for GLAD
#add_library(glad_lib STATIC ${GLAD_DIR}/src/glad.c)
#set_source_files_properties(${GLAD_DIR}/src/glad.c PROPERTIES LANGUAGE C)
target_include_directories(glad_lib PUBLIC ${GLAD_DIR}/include)

# Now, define your executable
add_executable(01_blank_space main_blank_window.cpp)

# Link your executable against GLFW, GL, AND the new glad_lib
# Add common X11 dependencies for GLFW
target_link_libraries(01_blank_space PRIVATE glfw GL glad_lib Xrandr Xi Xxf86vm Xcursor Xinerama dl) # <--- ADDED LIBRARIES