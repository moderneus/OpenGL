#pragma once

#include "glad/glad.h"

class Logger
{
private:
    static bool initialized;    

public:
    Logger();
    bool isInit();
    void info(const char* msg, const char* value = "");
    void info(const char* msg, const GLubyte* value);
    void success(const char* msg);
    void error(const char* msg, const char* error = "", bool* errorsOccured = nullptr);
    void error(const char* msg, GLenum error, bool* errorsOccured = nullptr);
};
