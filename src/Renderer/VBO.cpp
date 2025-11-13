#include "Renderer/VBO.hpp"
#include <SDL3/SDL_video.h>
#include <fmt/color.h>

VBO::VBO(GLenum type)
{
    glGenBuffers(type, &ID);
    this->type = type;
}

VBO::~VBO()
{
    glDeleteBuffers(type, &ID);
}

void VBO::data(const GLsizei size, const GLvoid* data, const GLenum usage) const
{
    glBufferData(type, size, data, usage);
}

void VBO::bind() const
{
    glBindBuffer(type, ID);
}

void VBO::unbind() const 
{
    glBindBuffer(type, ID);
}
