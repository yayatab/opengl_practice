#ifndef OPENGL_GEMINI_GUIDANCE_SHADER_H
#define OPENGL_GEMINI_GUIDANCE_SHADER_H

#include "glad/glad.h"
#include <string>


namespace tools {

class Shader {
public:
    unsigned int get_id;

    Shader(const std::string& vertex_path, const std::string& fragment_path);
    ~Shader();

    void use();

    void set_bool(const std::string& name, bool value);

    template<typename T>
    void set_uniform_data(const std::string& name, T data);

private:
    unsigned int ID;

    static std::string read_file(const std::string& path);

    static bool log_shader_error(unsigned int shader_index, const std::string& label);
    static bool log_program_error(unsigned int program_index);

};

}

#endif
