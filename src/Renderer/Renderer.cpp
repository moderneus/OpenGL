#include "Renderer/Renderer.hpp"
#include "Shaders/Shader.hpp"

#include <fmt/core.h>
#include <fmt/base.h>
#include <fmt/color.h>

#include <SDL3/SDL.h>

#include "glad/glad.h"

Renderer* Renderer::instance = nullptr;
Window* Renderer::window = nullptr;        
Logger* Renderer::log = Logger::getInstance();

void Renderer::createContext()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    log->info("Creating a Context...");

    context = SDL_GL_CreateContext(window->get());

    if(!context)
    {
        log->error("Failed to create context: ", SDL_GetError());
        std::exit(EXIT_FAILURE);
    }

    else
    {
        log->success("The Context was created!");
    }

    SDL_GL_MakeCurrent(window->get(), context);
}

void Renderer::init()
{
    log->info("Initialization...");
    log->info("Creating Renderer...");

    bool errorsOccured = false;
 
    log->info("Initializing SDL3...");

    if(!SDL_Init(SDL_INIT_VIDEO))
        log->error("SDL3 initialization failed: ", SDL_GetError(), &errorsOccured);

    else
        log->success("SDL3 was initialized!");

    
    window = Window::getInstance("OpenGL", 640, 480, SDL_WINDOW_OPENGL);
    
    errorsOccured = window->errors();
    
    createContext();
    
    log->info("Initializing GLAD...");

    if(!gladLoadGL())
        log->error("GLAD initialization failed: ", glGetError(), &errorsOccured);

    else
        log->success("GLAD was initialized!");
    

    if(errorsOccured)
    {
        log->error("Failed to create renderer.\n");
        std::exit(EXIT_FAILURE);
    }

    log->success("The Renderer was created!\n");
    
    log->info(GL_RENDERER, glGetString(GL_RENDERER));
    log->info(GL_VERSION, glGetString(GL_VERSION));

    log->success("Initializated!\n");
}

void Renderer::destroy()
{
    window->destroy();
    
    SDL_GL_DestroyContext(context);

    log->info("The Context was deleted.");
    
    SDL_Quit();

    log->info("The SDL3 memory free.");

    delete instance;
    instance = nullptr;

    log->info("The Renderer was deleted.");
    
    log->destroy();
}

Renderer* Renderer::getInstance()
{
    if(instance == nullptr)
        instance = new Renderer();

    return instance;
}

void Renderer::pollEvents()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_EVENT_QUIT:
                window->close();
            break;
        }
    }
}

void Renderer::draw()
{
    SDL_GL_SetSwapInterval(1);
    glClearColor(1, 1, 0, 1);

    GLfloat vertices[]
    {
        0.0f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
    };

    GLfloat colors[]
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };

    Shader vertexShader(GL_VERTEX_SHADER, "shaders/vertexShader.vert");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/fragmentShader.frag");
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vboVertices;
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    
    GLuint vboColors;
    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
    
    while(!window->closed())
    {
        pollEvents();

        Shader::use();

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(window->get());
    }
    
    log->info("Engine finished::", "User-quit.");
}
