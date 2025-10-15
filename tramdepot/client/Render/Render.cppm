module;
#include <d3d11.h>
#include <memory>
#include <functional>
export module TramDepot:Render;

import :Event;
import :IRenderer;

namespace TramDepot
{
class Render
{
    friend class TramDepot;

  public:
    Render(const unsigned int windowWidth, const unsigned int windowHeight);

    void Update();

  private:
    HINSTANCE instanceHandle = nullptr;

    HWND windowHandle     = nullptr;
    WindowSize windowSize = {0, 0};
    __int64 prevTicksCount;
    double secondsPerCount;
    double deltaTime;

    std::unique_ptr<IRenderer> renderer;
    std::function<void(const Event &e)> postEvent = nullptr;

    void createWindow();
    inline __int64 getTicks();
};
} // namespace TramDepot