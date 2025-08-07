cmake_minimum_required(VERSION 3.16)
project(opengl_gemini_guidance LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(ENV{DISPLAY} "192.168.1.217:0.0")
set(ENV{LIBGL_ALWAYS_INDIRECT} "1")

include(FetchContent)

# Define GLAD directory globally, so subdirectories can use it
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/libs/glad" CACHE PATH "Path to GLAD library")
include_directories(${GLAD_DIR}/include) # Include GLAD headers globally if common

add_library(glad_lib STATIC ${GLAD_DIR}/src/glad.c)
set_source_files_properties(${GLAD_DIR}/src/glad.c PROPERTIES LANGUAGE C)

set(GLM_DIR "${CMAKE_SOURCE_DIR}/libs/glm" CACHE PATH "Path to glm library") #todo remove this and use FetchContent
include_directories(${GLM_DIR}/glm) # Include GLAD headers globally if common

#find_package(glm CONFIG REQUIRED)

#FetchContent_Declare(
#        glm
#        GIT_REPOSITORY	https://github.com/g-truc/glm.git
#        GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
#)
#
#FetchContent_MakeAvailable(glm)

# dummy executable
add_executable(GeneralApp main.cpp)
target_link_libraries(GeneralApp PRIVATE glfw GL) # making sure the linking is good

# Add your subdirectories as separate build modules
add_subdirectory(01_blank_window)
add_subdirectory(02_triangle)
add_subdirectory(03_coloured_triangle)
add_subdirectory(04_moving_triangle)
add_subdirectory(04_rotating_triangle)
add_subdirectory(05_uniforms_and_transformations)
add_subdirectory(06_square)