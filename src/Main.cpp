#include "Renderer/Renderer.hpp"

int main()
{
    Renderer* renderer = Renderer::getInstance();

    renderer->init();
    renderer->draw();

    renderer->destroy();
}
