#include "Utils/Logger.hpp"

#include <fmt/core.h>
#include <fmt/color.h>

Logger* Logger::instance = nullptr;

Logger::~Logger()
{
    delete instance;
    instance = nullptr;
}

Logger* Logger::get()
{
    if(instance == nullptr)
        instance = new Logger();

    return instance;
}

void Logger::info(const char* msg, const char* value)
{
    fmt::print(fmt::fg(fmt::color::white_smoke), "INFO::{}{}\n", msg, value);
}

void Logger::info(const char* msg, const GLubyte* value)
{
    fmt::print(fmt::fg(fmt::color::white_smoke), "INFO::{}{}\n", msg, (const char*)value);
}

void Logger::success(const char* msg)
{
    fmt::print(fmt::fg(fmt::color::lime_green), "SUCCESS::{}\n", msg);
}

void Logger::error(const char* msg, const char* error, bool* errorsOccured)
{
    fmt::print(fmt::fg(fmt::color::red), "ERROR::{}", msg);
    fmt::print(fmt::fg(fmt::color::white_smoke), "{}\n", error);

    *errorsOccured = true;
}

void Logger::error(const char* msg, GLenum error, bool* errorsOccured)
{
    fmt::print(fmt::fg(fmt::color::red), "ERROR::{}", msg);
    fmt::print(fmt::fg(fmt::color::white_smoke), "{}\n", error);
}
