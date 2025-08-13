#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <valarray>
#include "gtc/type_ptr.hpp"

/**
 * Handles window resize.
 * @param window unused. needed due to library's requirements
 * @param width width of the window ot resize to
 * @param height height of the window to resize to
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void log_shader_error(unsigned int shader_index) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_index, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void log_program_error(unsigned int program_index) {
    int success;
    char infoLog[512];
    glGetProgramiv(program_index, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program_index, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

std::string read_shader_file(const std::string& filename) {
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shader_file.open(filename);
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        return shader_stream.str();
    } catch (std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filename << std::endl;
        return "";
    }
}



int main() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        // Print more detailed error from GLFW if available
        const char* description;
        int code = glfwGetError(&description);
        if (description) {
            std::cerr << "GLFW Error " << code << ": " << description << std::endl;
        }
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required for macOS
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        const char* description;
        int code = glfwGetError(&description);
        if (description) {
            std::cerr << "GLFW Error " << code << ": " << description << std::endl;
        }
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600); // Initial viewport size

    // now adding colour. red/ blue /green.
    // so now it's x,y,z,r,g,b

    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Left bottom
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Right bottom
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // Top center
    };

    unsigned int VAO, VBO; // Vertex array object. Vertices Buffer Objects

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    //colour attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    auto string_content = read_shader_file("shader_source.glsl"); //todo make const_expr?
    const char* shader_string = string_content.c_str();

    if (string_content.empty()) {
        std::cerr << "Failed to read shader file" << std::endl;
        glfwTerminate();
        return -1;
    }

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &shader_string, NULL);
    glCompileShader(vertex_shader);
    log_shader_error(vertex_shader);


    auto fragment_shader_source = read_shader_file("fragment_shader_source.glsl"); //todo make const_expr?
    const char* fragment_shader_string = fragment_shader_source.c_str();

    if (fragment_shader_source.empty()) {
        std::cerr << "Failed to read shader file" << std::endl;
        glfwTerminate();
        return -1;
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_string, NULL);
    glCompileShader(fragment_shader);
    log_shader_error(fragment_shader);

    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    log_program_error(shader_program);

    int x_offset = glGetUniformLocation(shader_program, "xOffset");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glm::mat4 trans = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window)) {

        auto curr_time = static_cast<float>(glfwGetTime());
        auto radians = glm::radians(curr_time);

        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform1f(x_offset, std::sin(curr_time));
        auto  rotation_location = glGetUniformLocation(shader_program, "transform");
        trans = glm::rotate(trans, glm::radians(curr_time), glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(rotation_location, 1, true, glm::value_ptr(trans));

        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}