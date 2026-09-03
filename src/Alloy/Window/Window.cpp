#include "Window.hpp"

namespace Alloy
{
Window::Window(int width, int height)
{
    m_SDLWindow = SDL_CreateWindow("Alloy Engine", width, height, 0);

    if (m_SDLWindow == nullptr)
    {
    }
}
} // namespace Alloy