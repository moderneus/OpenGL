#include <fmt/core.h>
#include <fmt/base.h>
#include <fmt/color.h>

#include "glad/glad.h"

int main()
{
    fmt::print(fmt::fg(fmt::color::sea_green), "Hello, OpenGL!\n");
    
    return EXIT_SUCCESS;
}