#include "glad/glad.h"
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

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        std::chrono::milliseconds dura(50);
        std::this_thread::sleep_for(dura);

    }

    // Terminate GLFW, clearing any allocated resources
    glfwTerminate();
    return 0;
}