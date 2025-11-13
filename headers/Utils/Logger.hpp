#pragma once

#include "glad/glad.h"

#include <string>

class Logger
{
private:
    static Logger* instance;
    Logger();

    std::string enumName(const GLenum value);
    
public:
    Logger(const Logger& log) = delete;

    static Logger* getInstance();
    void destroy();
    
    void info(const std::string& msg, const std::string& value = "");
    void info(const std::string& msg, const GLubyte* value);
    void info(const std::string& msg, const GLenum value);
    void info(const GLenum value, const GLubyte* str);
    
    void success(const std::string& msg);
    void success(const std::string& msg, const GLenum value);

    void error(const std::string& msg, const std::string& error = "", bool* errorsOccured = nullptr);
    void error(const std::string& msg, GLenum error, bool* errorsOccured = nullptr);
    void error(const std::string& msg, const std::string& error, GLenum value);
};
