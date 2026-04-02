module;
#include "RGFW.h"
export module Alloy:IRenderer;

export namespace Alloy
{
class IRenderer
{
  public:
    virtual void Draw()   = 0;
    virtual void Update() = 0;

    virtual ~IRenderer() {}

  protected:
    RGFW_window *window{};
};
} // namespace Alloy