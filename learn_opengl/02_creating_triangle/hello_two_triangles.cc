#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>


void framebuffer_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    // exit on escape or Q
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
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

int log_shader_error(unsigned int shader_index) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_index, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return success;
}

int log_program_error(unsigned int program_index) {
    int success;
    char infoLog[512];
    glGetProgramiv(program_index, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program_index, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    return success;
}

int main() {

#pragma region init_region
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int width = 800;
    const int height = 600;
    GLFWwindow* window = glfwCreateWindow(width, height, "Hello Window", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //this is where we load the glad functions to the memory
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // here we normalize the view and map 0, 0 to it's place
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#pragma endregion


    //define data

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    /*
     * for our purpose, we need only one buffer.
     * but we also could do:
     * unsigned int vbos[n];
     * glGenBuffers(n, vbos)
    */
    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    //now binding it. we use array buffer, but there are lots of other types.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //this copies the buffer data.and tell it to use the current VBO.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);



    auto vertex_shader_source = read_shader_file("vertex_shader.glsl"); //todo make const_expr?
    const char* shader_string = vertex_shader_source.c_str();

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &shader_string, NULL);
    glCompileShader(vertex_shader);

    if (!log_shader_error(vertex_shader)) {
        return 1;
    }

    auto fragment_source = read_shader_file("fragment.frag");
    const char* fragment_string = fragment_source.c_str();

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_string, NULL);
    glCompileShader(fragment_shader);

    if (!log_shader_error(fragment_shader)) {
        return 2;
    }

    unsigned int shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    if (!log_program_error(shader_program)) {
        return 3;
    }

    glUseProgram(shader_program);

    //and now we don't need the shaders anymore, so we can delete them.

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);





    while (!glfwWindowShouldClose(window)) {
        process_input(window);

#pragma region rendering_region

        glClearColor(0.5f, 0.3 , 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // clears the colour buffer

        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

#pragma endregion

        glfwSwapBuffers(window); //todo chek what are the buffers.
        glfwPollEvents(); // chekcs for input. and calls the callbacks if registered.
    }

    glfwTerminate();

    return 0;
}