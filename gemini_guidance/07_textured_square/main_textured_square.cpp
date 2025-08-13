#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

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

    glViewport(0, 0, 800, 600);

    // (X, Y, Z, R, G, B, U, V). U/V are texture coordinates
    std::array<float, 32> vertices = {
            -0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.1f, // Left bottom
            0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.1f, // Right bottom
            0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.1f,  // Left Top
            -0.25f, 0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.1f,  // Right Top
    };

    std::array<unsigned int, 6> indices = {0, 1, 2, 0, 2, 3};


    unsigned int VAO, VBO, EBO ; // ElementBufferObjects


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);



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

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);


    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}