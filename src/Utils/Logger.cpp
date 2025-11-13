#include "Utils/Logger.hpp"

#include "glad/glad.h"

#include <fmt/core.h>
#include <fmt/color.h>

Logger* Logger::instance = nullptr;

Logger::Logger()
{
    info("Creating a Logger...");
    success("The Logger was created!\n");
}

Logger* Logger::getInstance()
{
    if(instance == nullptr)
        instance = new Logger();

    return instance;
}

void Logger::destroy()
{
    info("The Logger was deleted.");
    
    delete instance;
    instance = nullptr;
}

std::string Logger::enumName(const GLenum value)
{
    switch(value)
    {
        case GL_VERTEX_SHADER:
            return "GL_VERTEX_SHADER";
        break;

        case GL_FRAGMENT_SHADER:
            return "GL_FRAGMENT_SHADER";
        break;

        case GL_RENDERER:
            return "GL_RENDERER";
        break;

        case GL_VERSION:
            return "GL_VERSION";
        break;
    }

    return "UNKNOWN";
}

void Logger::info(const std::string& msg, const std::string& value)
{
    fmt::print(fmt::fg(fmt::color::white_smoke), "INFO::{}{}\n", msg, value);
}

void Logger::info(const std::string& msg, const GLubyte* value)
{
    fmt::print(fmt::fg(fmt::color::white_smoke), "INFO::{}{}\n", msg, (const char*)value);
}

void Logger::info(const std::string& msg, const GLenum value)
{
    fmt::print(fmt::fg(fmt::color::white_smoke), "INFO::{}::{}\n", enumName(value), msg);
}

void Logger::info(const GLenum value, const GLubyte* str)
{
    fmt::print(fmt::fg(fmt::color::white_smoke), "INFO::{}::{}\n", enumName(value), (const char*)str);
}
    
void Logger::success(const std::string& msg)
{
    fmt::print(fmt::fg(fmt::color::lime_green), "SUCCESS::{}\n", msg);
}

void Logger::success(const std::string& msg, const GLenum value)
{
    fmt::print(fmt::fg(fmt::color::lime_green), "SUCCESS::{}::{}\n", enumName(value), msg);
}

void Logger::error(const std::string& msg, const std::string& error, bool* errorsOccured)
{
    fmt::print(fmt::fg(fmt::color::red), "ERROR::{}", msg);
    fmt::print(fmt::fg(fmt::color::white_smoke), "{}\n", error);

    *errorsOccured = true;
}

void Logger::error(const std::string& msg, GLenum error, bool* errorsOccured)
{
    fmt::print(fmt::fg(fmt::color::red), "ERROR::{}", msg);
    fmt::print(fmt::fg(fmt::color::white_smoke), "{}\n", enumName(error));
}

void Logger::error(const std::string& msg, const std::string& error, GLenum value)
{
    fmt::print(fmt::fg(fmt::color::lime_green), "ERROR::{}::{}::", enumName(value), msg);
    fmt::print(fmt::fg(fmt::color::white_smoke), "{}\n", error);
}
