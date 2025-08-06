#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib> // Required for getenv
#include <random>
#include <chrono>
#include <thread>

/**
 * Handles window resize.
 * @param window unused. needed due to library's requirements
 * @param width width of the window ot resize to
 * @param height height of the window to resize to
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

//language: glsl
const char* vertexShaderSource = "#version 330 core\n" // OpenGL Shading Language, version 3.3
                                 "layout (location = 0) in vec3 aPos;\n" //
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0"; // Vertices are already in Normalized Device Coordinates (-1.0 to 1.0)

const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // Orange color
                                   "}\0";


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


int main() {

    std::random_device rd;
    std::mt19937 gen(rd());

    // Initialize GLFW
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

    // ... rest of your code ... (glfwWindowHint, glfwCreateWindow, etc.)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required for macOS
#endif

    // Create a windowed mode window and its OpenGL context
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

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Register the resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD - IMPORTANT: Call this after glfwMakeContextCurrent
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set the initial viewport
    glViewport(0, 0, 800, 600); // Initial viewport size



    /*
     * Vertices:
     *          These are simply points in 3D space. To describe a 3D shape, you provide a list of vertices.
     *          For a simple 2D triangle, you'll need three vertices. Each vertex can have various attributes, like its position, color, texture coordinates, etc.
     *          For now, we'll just focus on position.
     */
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // Left bottom
            0.5f, -0.5f, 0.0f, // Right bottom
            0.0f, 0.5f, 0.0f  // Top center
    };

    unsigned int VAO, VBO; // Vertex array object. Vertices Buffer Objects

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    log_shader_error(vertexShader);

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    log_shader_error(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    log_program_error(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float red = 0.0f;
    int red_changed = 1;
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
//        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
//        float randomRed = dist(gen);

        // Render here
        glClearColor(red, 0.3f, 0.3f, 1.0f); // Set background color (dark cyan)
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
        std::chrono::milliseconds dura(50);
        std::this_thread::sleep_for(dura);


        if (red > 1.0f) {
            red_changed = -1;
        }

        if (red < 0.0f) {
            red_changed = 1;
        }
        red += 0.01f * red_changed;
    }


    // Terminate GLFW, clearing any allocated resources
    glfwTerminate();
    return 0;
}