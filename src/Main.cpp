#include <SDL3/SDL.h>

#include <fmt/core.h>
#include <fmt/base.h>
#include <fmt/color.h>

#include "glad/glad.h"

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) != true)
    {
        fmt::print(fmt::fg(fmt::color::red), "Error: SDL3 initialization failed: ");
        fmt::print(fmt::fg(fmt::color::white_smoke), "{}\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_Window* pWindow = SDL_CreateWindow("OpenGL", 800, 600, SDL_WINDOW_OPENGL);

    if(!pWindow)
    {
        fmt::print(fmt::fg(fmt::color::red), "Error: Window creation failed: ");
        fmt::print(fmt::fg(fmt::color::white_smoke), "{}\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    SDL_GLContext context = SDL_GL_CreateContext(pWindow);
    if(!context)
    {
        fmt::print(fmt::fg(fmt::color::red), "Error: Context creation failed: ");
        fmt::print(fmt::fg(fmt::color::white_smoke), "{}\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_GL_MakeCurrent(pWindow, context);

    if(!gladLoadGL())
    {
        fmt::print(fmt::fg(fmt::color::red), "Error: OpenGL initialization failed: ");
        fmt::print(fmt::fg(fmt::color::white_smoke), "{}\n", glGetError());
        return EXIT_FAILURE;
    }
    
    glClearColor(0, 0, 0, 1);
    SDL_GL_SetSwapInterval(1);

    const bool* keys = SDL_GetKeyboardState(nullptr);

    SDL_Event event;

    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                    return EXIT_SUCCESS;
                break;

                case SDL_EVENT_KEY_DOWN:
                    if(keys[SDL_SCANCODE_R]) 
                        glClearColor(1, 0, 0, 1);

                    else if(keys[SDL_SCANCODE_G])
                        glClearColor(0, 1, 0, 1);

                    else if(keys[SDL_SCANCODE_B])
                        glClearColor(0, 0, 1, 1);
                break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(pWindow);
    }
    
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}