#include "Renderer/Window.hpp"

Window* Window::instance = nullptr;
Logger* Window::log = Logger::getInstance();

Window::Window(const char* title, int width, int height, const SDL_WindowFlags flags)
{
    log->info("Creating a Window...");
    
    pWindow = SDL_CreateWindow(title, width, height, flags);

    if(pWindow == nullptr)
    {
        log->error("Failed to create Window: ", SDL_GetError());
        errorsOccured = true;
    }

    else
    {
        log->success("The Window was created!");
    }
}

Window* Window::getInstance(const char* title, int width, int height, const SDL_WindowFlags flags)
{
    if(instance == nullptr)
        instance = new Window(title, width, height, flags);
    
    return instance;
}

void Window::destroy()
{
    SDL_DestroyWindow(pWindow);

    delete instance;
    instance = nullptr;

    log->info("The Window was deleted.");
}

bool Window::errors() const
{
    return errorsOccured;
}

bool Window::closed() const
{
    return isClosed;
}

void Window::close()
{
    isClosed = true;
}

SDL_Window* Window::get() const
{
    return pWindow;
}
