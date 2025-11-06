#pragma once

#include "glad/glad.h"

class Logger
{
private:
    static Logger* instance;
    Logger() = default;
    
public:
    Logger(const Logger& log) = delete;
    ~Logger();

    static Logger* get();
    
    void info(const char* msg, const char* value = "");
    void info(const char* msg, const GLubyte* value);
    
    void success(const char* msg);

    void error(const char* msg, const char* error = "", bool* errorsOccured = nullptr);
    void error(const char* msg, GLenum error, bool* errorsOccured = nullptr);
};
