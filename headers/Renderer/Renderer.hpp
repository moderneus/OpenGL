#pragma once

#include <SDL3/SDL.h>

#include "glad/glad.h"

#include "Renderer/Window.hpp"
#include "Utils/Logger.hpp"

class Renderer
{
private:
    static Window* window;
    static Renderer* instance;
    static Logger* log;

    SDL_GLContext context; 

    void pollEvents();
    void createContext();

    Renderer() = default;

public:
    Renderer(const Renderer& renderer) = delete;
    
    void init();
    void destroy();
    static Renderer* getInstance();
    
    void draw();
};
