#pragma once
#include "Window/Window.hpp"

namespace Alloy
{
class Client
{
  public:
    ALLOY_API Client();
    ALLOY_API void MainLoop();

  private:
    Window m_Window;
};
} // namespace Alloy