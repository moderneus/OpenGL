#include "Shaders/Shader.hpp"

#include <fmt/color.h>
#include <fstream>
#include <sstream>

Logger* Shader::log = Logger::getInstance();
GLuint Shader::shaderProgram = 0;

Shader::Shader(const GLenum type, const GLchar* path, const GLsizei count)
{
    log->info("Creating Shader...", type);
    
    this->type = type;
    ID = glCreateShader(type);

    std::string fileContent = readFile(path);
    const GLchar* src = fileContent.c_str();

    glShaderSource(ID, count, &src, nullptr);
    
    compile();
    attach();
    link();
    
    log->success("Shader was created!\n", type);
}

Shader::~Shader()
{
    glDeleteShader(ID);
}

std::string Shader::readFile(const std::string& path)
{
    std::ifstream shaderFile(path);

    if(!shaderFile.is_open())
        log->error("Failed to open file by path: ", path, type);
    
    std::stringstream ss;
    ss << shaderFile.rdbuf();

    return ss.str();
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}

void Shader::attach()
{
    if(shaderProgram == 0)
            shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, ID);
}

void Shader::compile()
{
    log->info("Compiling shader...", type);
    
    glCompileShader(ID);

    int success; 
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

    char infoLog[1024];
    if(!success)
    {
        glGetShaderInfoLog(ID, 1024, nullptr, infoLog);
        
        std::string error;
        for(auto& x : infoLog)
            error += x;
        
        log->error("Shader compilation failed: ", error, type);
    }

    else
    {
        log->success("Shader was compiled!", type);
    }
}

void Shader::link()
{
    log->info("Linking shader...", type);
    
    glLinkProgram(shaderProgram);

    int success;
    glGetShaderiv(ID, GL_LINK_STATUS, &success);

    char infoLog[1024];
    if(!success)
    {
        glGetProgramInfoLog(ID, 1024, nullptr, infoLog);
        
        std::string error;
        for(auto& x : infoLog)
            error += x;

        log->error("Shader link failed: ", error, type);
    }

    else
    {
        log->success("Shader was linked!", type);
    }
}
