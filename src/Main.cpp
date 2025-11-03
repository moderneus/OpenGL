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
    
    SDL_Window* pWindow = SDL_CreateWindow("OpenGL", 800, 600, SDL_WINDOW_OPENGL);

    if(pWindow == NULL)
    {
        fmt::print(fmt::fg(fmt::color::red), "Error: Window creation failed: ");
        fmt::print(fmt::fg(fmt::color::white_smoke), "{}\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    SDL_Event event;
    
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
                quit = true;
        }
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}