module;
#include <d3d11.h>
export module TramDepot:RendererD3D11;

import :IRenderer;

namespace TramDepot
{
class RendererD3D11 : public IRenderer
{
  public:
    RendererD3D11(const HWND windowHandle);
    ~RendererD3D11();

    void Update() override;
    void Draw() override;

  private:
    IDXGISwapChain *swapChain{};
    ID3D11Device *d3dDevice{};
    ID3D11DeviceContext *d3dDeviceContext{};
    ID3D11RenderTargetView *renderTargetView{};
    ID3D11Texture2D *backBuffer{};
};
} // namespace TramDepot