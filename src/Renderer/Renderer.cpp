#include "Renderer/Renderer.hpp"

#include <fmt/core.h>
#include <fmt/base.h>
#include <fmt/color.h>

#include <SDL3/SDL.h>

#include "glad/glad.h"

Renderer* Renderer::instance = nullptr;
Logger* Renderer::log = Logger::get();

void Renderer::createContext(const Window& window)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    context = SDL_GL_CreateContext(window.get());

    if(!context)
    {
        log->error("Failed to create context: ", SDL_GetError());
        std::exit(EXIT_FAILURE);
    }

    SDL_GL_MakeCurrent(window.get(), context);
}

Renderer::~Renderer()
{
    delete instance;
    instance = nullptr;
    SDL_GL_DestroyContext(context);
    SDL_Quit();
}

void Renderer::init(const Window& window, const SDL_WindowFlags flags)
{
    createContext(window);

    bool errorsOccured = false;
 
    log->info("Initializing SDL3...");

    if(!SDL_Init(flags))
        log->error("SDL3 initialization failed: ", SDL_GetError(), &errorsOccured);

    else
        log->success("SDL3 was initialized!");
    
    log->info("Initializing GLAD...");

    if(!gladLoadGL())
        log->error("GLAD initialization failed: ", glGetError(), &errorsOccured);

    else
        log->success("GLAD was initialized!");
    
    log->info("Creating Renderer...");

    if(errorsOccured)
    {
        log->error("Errors occured: Failed to create renderer.\n");
        std::exit(EXIT_FAILURE);
    }

    log->success("The Renderer was created!\n");

    log->info("GPU Device::", glGetString(GL_RENDERER));
    log->info("OpenGL Version::", glGetString(GL_VERSION));
}

Renderer* Renderer::get()
{
    if(instance == nullptr)
        instance = new Renderer();

    return instance;
}

void Renderer::draw(const Window& window)
{
    SDL_GL_SetSwapInterval(1);
    glClearColor(0, 0, 1, 1);

    SDL_Event event;

    bool quit = false;
    while(!quit)
    {
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                    quit = true;
                break;
            }
        }

        SDL_GL_SwapWindow(window.get());
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    log->info("Engine finished::", "User-quit.");
}
