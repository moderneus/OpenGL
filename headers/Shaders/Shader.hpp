#pragma once

#include "Utils/Logger.hpp"

#include "glad/glad.h"

#include <string>

class Shader
{
private:    
    GLuint ID;
    GLuint type;
    static GLuint shaderProgram;

    static Logger* log;

    std::string readFile(const std::string& path);
    void attach();
    void compile();
    void link();

public:
    Shader(const GLenum type, const GLchar* path, const GLsizei count = 1);
    ~Shader();

    static void use();
};
