#pragma once

#include "glad/glad.h"

class VBO
{
private:    
    GLuint ID;
    GLenum type;

public:
    VBO(GLenum type = GL_ARRAY_BUFFER);
    ~VBO();

    void data(const GLsizei size, const GLvoid* data, GLenum usage) const;
    void bind() const;
    void unbind() const;
};
