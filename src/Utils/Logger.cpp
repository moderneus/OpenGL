#include "Utils/Logger.hpp"

#include <fmt/core.h>
#include <fmt/color.h>

bool Logger::initialized = false;

Logger::Logger()
{
    bool errorsOccured = false;

    if(initialized)
        error("Failed to initialize the Logger: ", "Already initialized.", &errorsOccured);

    if(errorsOccured)
    {
        error("Failed to create the Logger.\n");
        std::exit(EXIT_FAILURE);
    }

    initialized = true;
}

bool Logger::isInit()
{
    return initialized ? true : false;
}

void Logger::info(const char* msg)
{
    fmt::print(fmt::fg(fmt::color::white_smoke), "INFO::{}\n", msg);
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