#pragma once

#include "glad/glad.h"

class VAO
{
private:
    GLuint ID;

public:
    VAO();
    ~VAO();

    void link(const GLuint index, const GLint size, const GLenum type, const GLsizei stride, const GLvoid* ptr) const;
    void bind() const;
    void unbind() const;
};
