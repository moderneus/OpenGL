#include "Renderer/Renderer.hpp"
#include "Renderer/Window.hpp"

int main()
{
    Renderer::Window window("OpenGL", 800, 600, SDL_WINDOW_OPENGL);

    Renderer::Renderer renderer(window, SDL_INIT_VIDEO);

    renderer.draw(window);
}
