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
    IRenderer(EventHandler *const eh, Window *const w)
        : eventHandler(eh), window(w) {};
    virtual void Update() = 0;
    virtual void Draw()   = 0;

    virtual ~IRenderer() {};

  protected:
    EventHandler *eventHandler{};
    Window *window{};
};
} // namespace Alloy