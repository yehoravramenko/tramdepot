module;
#include <d3d11.h>
export module TramDepot:Render;

import :Event;
import :IRenderer;

import std;

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

    std::unique_ptr<IRenderer> renderer;
    std::function<void(const Event &e)> postEvent = nullptr;

    void createWindow();
};
} // namespace TramDepot