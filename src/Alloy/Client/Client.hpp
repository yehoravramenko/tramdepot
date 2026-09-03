#pragma once
#include "Window/Window.hpp"
#include <SDL3/SDL.h>

namespace Alloy
{
class Client
{
  public:
    ALLOY_API Client();
    virtual ~Client() {}

    ALLOY_API void MainLoop();

    virtual void OnInit() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnEvent(const SDL_Event *event) {}
    virtual void OnRender() {}
    virtual void OnShutdown() {}

  private:
    Window m_Window;
};
} // namespace Alloy