#pragma once

#include <SDL3/SDL.h>

#include "glad/glad.h"

#include "Renderer/Window.hpp"
#include "Utils/Logger.hpp"

namespace Renderer
{
    class Renderer
    {
    private:
        static bool initialized;
        SDL_GLContext context;
        static Logger* log;

        void createContext(const Window& window);

    public:
        Renderer(const Window& window, const SDL_WindowFlags flags = NULL);
        ~Renderer();
        void draw(const Window& window);
    };
}