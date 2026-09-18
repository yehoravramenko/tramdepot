#pragma once
#include <SDL3/SDL.h>
#include <Windows.h>
#include <array>

namespace Alloy
{
class ALLOY_API Window
{
  public:
    Window(int width, int height);
    HWND GetWindowHandle() const;

    std::array<int, 2> GetWindowSize() const;

    ~Window();

  private:
    SDL_Window *m_SDLWindow{};
    std::array<int, 2> m_Size;
};
} // namespace Alloy