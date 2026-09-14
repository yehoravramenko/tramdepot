#pragma once
#include <SDL3/SDL.h>
#include <Windows.h>

namespace Alloy
{
class ALLOY_API Window
{
  public:
    Window(int width, int height);
    HWND GetWindowHandle() const;

    ~Window();

  private:
    SDL_Window *m_SDLWindow{};
};
} // namespace Alloy