#include "Renderer/Window.hpp"

Window::Window()
{
    pWindow = SDL_CreateWindow("NONE", 640, 480, NULL);
}

Window::~Window()
{
    SDL_DestroyWindow(pWindow);
}

Window::Window(const char* title, int width, int height, const SDL_WindowFlags flags)
{
    pWindow = SDL_CreateWindow(title, width, height, flags);
}

SDL_Window* Window::get() const
{
    return pWindow;
}
