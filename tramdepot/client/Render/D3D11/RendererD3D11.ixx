module;
#include <d3d11.h>
#include <winrt/base.h>
export module TramDepot:RendererD3D11;

import :IRenderer;

namespace TramDepot
{
class RendererD3D11 : public IRenderer
{
  public:
    RendererD3D11(const HWND windowHandle, const WindowSize &windowSize);

    void Update() override;
    void Draw() override;

  private:
    DXGI_RATIONAL refreshRate{};

    winrt::com_ptr<IDXGISwapChain> swapChain{};
    winrt::com_ptr<ID3D11Device> d3dDevice{};
    winrt::com_ptr<ID3D11DeviceContext> d3dDeviceContext{};
};
} // namespace TramDepot