#pragma once

#include "Utils/Logger.hpp"

#include <SDL3/SDL.h>

class Window
{
private:
    static Window* instance; 
    static Logger* log;
    
    int width, height;
    const char* title;
    SDL_Window* pWindow;
    bool isClosed = false;
    bool errorsOccured = false;

    Window() = default;
    
public:
    Window(const Window& other) = delete;
    Window operator=(const Window& other) = delete;
    
    Window(const char* title, int width, int height, const SDL_WindowFlags flags);

    static Window* getInstance(const char* title, int width, int height, const SDL_WindowFlags flags);
    void destroy();
    SDL_Window* get() const;
    bool errors() const;
    bool closed() const;
    void close();
};
