#ifndef CPP_MINECRAFT_SHADER_H
#define CPP_MINECRAFT_SHADER_H

#include "../includes.hpp"

class Shader {
public:
    unsigned int ID;

public:
    Shader() = default;
    Shader(const char* vertexPath, const char* fragmentPath);

public:
    void use();

    void set(const std::string &name, bool value) const {glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);}
    void set(const std::string &name, int value) const {glUniform1i(glGetUniformLocation(ID, name.c_str()), value);}
    void set(const std::string &name, float value) const {glUniform1f(glGetUniformLocation(ID, name.c_str()), value);}
    void set(const std::string &name, glm::mat4 value) const {glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));}
};

#endif //CPP_MINECRAFT_SHADER_H
