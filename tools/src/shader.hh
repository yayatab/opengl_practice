#pragma once
#include "tools/shader.h"
#include <type_traits>
#include <limits>
#include <iostream>
#include "gtc/type_ptr.hpp"

namespace tools {

template<typename T>
inline void Shader::set_uniform_data(const std::string& name, const T& data) {
    const GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1) {
        std::cerr << "ERROR::SHADER::INVALID_UNIFORM" << std::endl;
        return;
    }

    if constexpr (std::numeric_limits<T>::is_integer) {
        glUniform1i(loc, static_cast<GLint>(data));
    } else if constexpr (std::is_floating_point_v<T>) {
        glUniform1f(loc, static_cast<GLfloat>(data));
    } else if constexpr (std::is_same_v<T, glm::vec2>) {
        glUniform2f(loc, data.x, data.y);
    } else if constexpr (std::is_same_v<T, glm::vec3>) {
        glUniform3f(loc, data.x, data.y, data.z);
    } else if constexpr (std::is_same_v<T, glm::vec4>) {
        glUniform4f(loc, data.x, data.y, data.z, data.w);
    } else if constexpr (std::is_same_v<T, glm::mat3>) {
        glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(data));
    } else {
        static_assert(!sizeof(T), "Unsupported uniform type for set_uniform_data");
    }
}

}
