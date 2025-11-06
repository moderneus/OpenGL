#pragma once

#include <SDL3/SDL.h>

class Window
{
private:
    int width, height;
    const char* title;
    SDL_Window* pWindow;
    
public:
    Window();
    ~Window();
    Window(const char* title, int width, int height, const SDL_WindowFlags flags);
    SDL_Window* get() const;
};
