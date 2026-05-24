module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
export module Alloy:Render;
import :EventHandler;
import :Window;
import :IRenderer;

import std;

export namespace Alloy
{
class Render
{
  public:
    Render() = delete;
    Render(EventHandler *const eventHandler);

    void Update();

  private:
    Window window;

    EventHandler *eventHandler{};
    std::unique_ptr<IRenderer> renderer;
};
} // namespace Alloy