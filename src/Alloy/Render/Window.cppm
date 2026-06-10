module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
export module Alloy:Window;
import :EventHandler;

namespace Alloy
{
class Window
{
  public:
    Window(EventHandler *eventHandler);

    void Update();

    HWND GetHandle() const { return this->handle; }
    int GetWidth() const { return this->width; }
    int GetHeight() const { return this->height; }

  private:
    int width  = 1280;
    int height = 720;

    HWND handle{};
    EventHandler *eventHandler{};
};
} // namespace Alloy