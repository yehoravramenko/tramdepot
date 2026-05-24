module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
export module Alloy:IRenderer;
import :EventHandler;
import :Window;

export namespace Alloy
{
class IRenderer
{
  public:
    virtual void Update() = 0;
    virtual void Draw()   = 0;

    virtual ~IRenderer() {};

  protected:
    EventHandler *eventHandler{};
    Window *window{};
};
} // namespace Alloy