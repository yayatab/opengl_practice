#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>


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

int main() {

    std::cout << "C++ Standard: " << __cplusplus << std::endl;
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

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

#pragma region rendering_region
        auto curr_time = static_cast<float>(glfwGetTime());
        float radians = M_PI * curr_time / 180;

        glClearColor(0.2f, std::sin(radians * 20), std::cos(radians * 50), -1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // clears the colour buffer

#pragma endregion

        glfwSwapBuffers(window); //todo chek what are the buffers.
        glfwPollEvents(); // chekcs for input. and calls the callbacks if registered.
    }

    glfwTerminate();

    return 0;
}