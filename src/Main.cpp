#include "Renderer/Renderer.hpp"
#include "Renderer/Window.hpp"

int main()
{
    Window window("OpenGL", 800, 600, SDL_WINDOW_OPENGL);

    Renderer* renderer = Renderer::get();

    renderer->init(window, SDL_INIT_VIDEO);
    renderer->draw(window);
}
