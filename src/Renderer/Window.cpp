#include "Renderer/Window.hpp"

Renderer::Window::Window()
{
    pWindow = SDL_CreateWindow("NONE", 640, 480, NULL);
}

Renderer::Window::~Window()
{
    SDL_DestroyWindow(pWindow);
}

Renderer::Window::Window(const char* title, int width, int height, const SDL_WindowFlags flags)
{
    pWindow = SDL_CreateWindow(title, width, height, flags);
}

SDL_Window* Renderer::Window::get() const
{
    return pWindow;
}