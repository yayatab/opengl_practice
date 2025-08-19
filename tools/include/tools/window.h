#ifndef OPENGL_GEMINI_GUIDANCE_WINDOW_H
#define OPENGL_GEMINI_GUIDANCE_WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>

namespace tools {


class Window {
public:
    Window(int height, int width, const std::string& window_name);
    ~Window();

    void make_current();

   GLFWwindow* operator~(); //not entirely sure about this one. and then, why would i need the not on window of this object in excersize context?
   //todo maybe add adding callbacks and input processes. so we won't need the operator overload

    bool should_close() const;

    void poll_events();

    void swap_buffers();

private:
    GLFWwindow* _window;
};

} // tools

#endif //OPENGL_GEMINI_GUIDANCE_WINDOW_H
