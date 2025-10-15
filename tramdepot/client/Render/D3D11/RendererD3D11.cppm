module;
#include <d3d11.h>
export module TramDepot:RendererD3D11;

import :IRenderer;

namespace TramDepot
{
class RendererD3D11 : public IRenderer
{
  public:
    RendererD3D11(const HWND windowHandle, const WindowSize &windowSize);
    ~RendererD3D11();

    virtual void Update() override;

  private:
    ID3D11Device *d3dDevice               = nullptr;
    ID3D11DeviceContext *d3dDeviceContext = nullptr;

    IDXGISwapChain *swapChain                = nullptr;
    ID3D11RenderTargetView *renderTargetView = nullptr;
    ID3D11Texture2D *depthStencilBuffer      = nullptr;
    ID3D11DepthStencilView *depthStencilView = nullptr;
    D3D11_VIEWPORT viewport;
    UINT qualityLevelsCount;

    void createDevice();
    void createSwapChain();
};
} // namespace TramDepot