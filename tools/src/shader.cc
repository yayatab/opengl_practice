#include "tools/shader.h"
#include "shader.hh"
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <type_traits>
#include <limits>

namespace tools {

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {

    std::string vertex_code;
    std::string fragment_code;

    try {
        vertex_code = read_file(vertex_path);
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << vertex_path << std::endl;
    }

    try {
        fragment_code = read_file(fragment_path);
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << fragment_path << std::endl;
    }

    const char* vertex_source = vertex_code.c_str();
    const char* fragment_source = fragment_code.c_str();

    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_source, NULL);
    glCompileShader(vertex);
    log_shader_error(vertex, "vertex");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_source, NULL);
    glCompileShader(fragment);
    log_shader_error(fragment, "fragment");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);

    glLinkProgram(ID);
    log_program_error(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

std::string Shader::read_file(const std::string& path) {
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    shader_file.open(path);
    std::stringstream shader_stream;
    shader_stream << shader_file.rdbuf();
    return shader_stream.str();
}

bool Shader::log_shader_error(unsigned int shader_index, const std::string& label) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_index, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << label << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    return true;
}

bool Shader::log_program_error(unsigned int program_index) {
    int success;
    char infoLog[512];
    glGetProgramiv(program_index, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program_index, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

void Shader::use() {
    glUseProgram(ID);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

template void Shader::set_uniform_data<int>(const std::string&, const int&);
template void Shader::set_uniform_data<float>(const std::string&, const float&);
template void Shader::set_uniform_data<glm::vec2>(const std::string&, const glm::vec2&);
template void Shader::set_uniform_data<glm::vec3>(const std::string&, const glm::vec3&);
template void Shader::set_uniform_data<glm::vec4>(const std::string&, const glm::vec4&);
template void Shader::set_uniform_data<glm::mat3>(const std::string&, const glm::mat3&);


}