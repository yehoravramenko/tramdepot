module;
#include "RGFW.h"
export module Alloy:IRenderer;
import :EventHandler;

export namespace Alloy
{
class IRenderer
{
  public:
    virtual void Draw()   = 0;
    virtual void Update() = 0;

    virtual ~IRenderer() {}

  protected:
    EventHandler *eventHandler;

    RGFW_window *window;
};
} // namespace Alloy