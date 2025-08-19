#include <iostream>
#include "tools/window.h"

namespace tools {

void framebuffer_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(int height, int width, const std::string& window_name) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    if (_window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

}

Window::~Window() {
    glfwTerminate();
}

void Window::make_current() {
    glfwMakeContextCurrent(_window);
}

GLFWwindow* Window::operator~() {
    return _window;
}

bool Window::should_close() const {
    return glfwWindowShouldClose(_window);
}

void Window::poll_events() {
    glfwPollEvents();
}

void Window::swap_buffers() {
    glfwSwapBuffers(_window);
}


} // tools