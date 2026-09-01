#pragma once
#include "Window/Window.hpp"

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
    virtual void OnRender() {}
    virtual void OnShutdown() {}

    // void Shutdown();

  private:
    Window m_Window;
};
} // namespace Alloy