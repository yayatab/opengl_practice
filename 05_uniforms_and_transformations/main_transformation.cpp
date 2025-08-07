#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

    glViewport(0, 0, 800, 600);

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

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glm::mat4 model = glm::mat4(1.0f); // init identity matrix 4x4.
    glm::vec3 camera_pos(0.0f, 0.0f, 3.0f);
    glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
    glm::vec3 up_direction(0.0f, 1.0f, 0.0f); //meaning y+ is our world's "up".


    glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    float radius = 2.0f;

    while (!glfwWindowShouldClose(window)) {

        auto curr_time = static_cast<float>(glfwGetTime());
        float radians = glm::radians(curr_time * 2.0f);

        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        int model_matrix_location = glGetUniformLocation(shader_program, "model");
        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 rotation = glm::rotate(model, radians, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(model_matrix_location, 1, GL_TRUE, glm::value_ptr(rotation));


        float cam_x = radius * std::cos(radians);
        float cam_z = radius * std::cos(radians);
        camera_pos = glm::vec3(cam_x, 0.0f, cam_z);
        glm::mat4 view_matrix = glm::lookAt(camera_pos, camera_target, up_direction);
        int view_matrix_location = glGetUniformLocation(shader_program, "view");
        glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view_matrix));

        int projection_matrix_location = glGetUniformLocation(shader_program, "projection");
        glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(projection_matrix));



        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}