#pragma once
#include <SDL3/SDL.h>

namespace Alloy
{
class Window
{
  public:
    Window(int width, int height);

  private:
    SDL_Window *m_SDLWindow;
};
} // namespace Alloy