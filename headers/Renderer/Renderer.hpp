#pragma once

#include <SDL3/SDL.h>

#include "glad/glad.h"

#include "Renderer/Window.hpp"
#include "Utils/Logger.hpp"

class Renderer
{
private:
    static Renderer* instance;
    static Logger* log;
    
    SDL_GLContext context;
    
    void createContext(const Window& window);
    Renderer() = default;

public:
    Renderer(const Renderer& renderer) = delete;
    ~Renderer();
    
    void init(const Window& window, const SDL_WindowFlags flags);
    static Renderer* get();
    
    void draw(const Window& window);
};

