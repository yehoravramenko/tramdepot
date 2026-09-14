#pragma once
#include <Windows.h>

namespace Alloy
{
class Renderer
{
  public:
    Renderer(HWND windowHandle);

  private:
    HWND m_windowHandle{};
};
} // namespace Alloy