#include "tools/window.h"
#include "tools/shader.h"
#include <glad/glad.h>
#include <iostream>


int main() {
    tools::Window window(600, 800, "Upside Down Triangle ( i lied. it's a star of david.)");
    std::cout << "C++ Standard: " << __cplusplus << std::endl;

    float vertices[] = {
            // first triangle
            -0.5f, 0.35f, 0.0f,  // left
            0.5f, 0.35f, 0.0f,  // right
            -0.0f, -0.65f, 0.0f,  // top
            // second triangle
            -0.5f,-0.35, 0.0f,  // left
            0.5f, -0.35, 0.0f,  // right
            -0.0f,0.65, 0.0f   // top
    };


    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    auto shader = tools::Shader("resources/upside_down.glsl", "resources/upside_down.frag");


    while (!window.should_close()) {

#pragma region rendering_region
        glClearColor(1.0f,1.0f,1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 6);

#pragma endregion

        window.swap_buffers();
        window.poll_events();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    return 0;

}