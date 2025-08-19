#ifndef OPENGL_GEMINI_GUIDANCE_SHADER_H
#define OPENGL_GEMINI_GUIDANCE_SHADER_H

#include "glad/glad.h"
#include <string>
#include <glm/glm.hpp>

namespace tools {

class Shader {
public:
    unsigned int get_id;

    Shader(const std::string& vertex_path, const std::string& fragment_path);

    ~Shader();

    void use();

    void set_bool(const std::string& name, bool value);

    template<typename T>
    void set_uniform_data(const std::string& name, const T& data);

private:
    unsigned int ID;

    static std::string read_file(const std::string& path);

    static bool log_shader_error(unsigned int shader_index, const std::string& label);

    static bool log_program_error(unsigned int program_index);

};

extern template void Shader::set_uniform_data<int>(const std::string&, const int&);
extern template void Shader::set_uniform_data<float>(const std::string&, const float&);
extern template void Shader::set_uniform_data<glm::vec2>(const std::string&, const glm::vec2&);
extern template void Shader::set_uniform_data<glm::vec3>(const std::string&, const glm::vec3&);
extern template void Shader::set_uniform_data<glm::vec4>(const std::string&, const glm::vec4&);
extern template void Shader::set_uniform_data<glm::mat3>(const std::string&, const glm::mat3&);


}

#endif
