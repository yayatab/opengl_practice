cmake_minimum_required(VERSION 3.16)
project(opengl_gemini_guidance LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(ENV{DISPLAY} "192.168.1.217:0.0") # <--- ADD THIS LINE
set(ENV{LIBGL_ALWAYS_INDIRECT} "1")             # <--- ADD THIS LINE

# Define GLAD directory globally, so subdirectories can use it
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/libs/glad" CACHE PATH "Path to GLAD library")
include_directories(${GLAD_DIR}/include) # Include GLAD headers globally if common

#set_source_files_properties(${GLAD_DIR}/src/glad.c PROPERTIES LANGUAGE C)
#add_library(glad_lib STATIC ${GLAD_DIR}/src/glad.c)
#target_include_directories(glad_lib PUBLIC ${GLAD_DIR}/include)

# dummy executable
 add_executable(GeneralApp main.cpp)
 target_link_libraries(GeneralApp PRIVATE glfw GL) # making sure the linking is good

add_library(glad_lib STATIC ${GLAD_DIR}/src/glad.c)
set_source_files_properties(${GLAD_DIR}/src/glad.c PROPERTIES LANGUAGE C)

# Add your subdirectories as separate build modules
add_subdirectory(01_blank_window)
add_subdirectory(02_triangle)
add_subdirectory(03_coloured_triangle)
add_subdirectory(04_moving_triangle)

# You would add more subdirectories as you create more demos:
# add_subdirectory(02_triangle_drawing)
# add_subdirectory(03_first_shader)