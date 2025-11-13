#include "Renderer/VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &ID);
}

void VAO::link(const GLuint index, const GLint size, const GLenum type, const GLsizei stride, const GLvoid* ptr) const
{
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, ptr);
    glEnableVertexAttribArray(index);
}

void VAO::bind() const
{
    glBindVertexArray(ID);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
}
