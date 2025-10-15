module;
#include <Windows.h>
export module TramDepot:IRenderer;

namespace TramDepot
{
struct WindowSize
{
    unsigned int width, height;
};

class IRenderer
{
  public:
    virtual ~IRenderer() {};

    virtual void Update() = 0;

  protected:
    HWND windowHandle;
    WindowSize windowSize;
};
} // namespace TramDepot