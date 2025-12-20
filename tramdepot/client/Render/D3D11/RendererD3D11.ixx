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

    void Update() override;
    void Draw() override;

  private:
    IDXGISwapChain *swapChain{};
    ID3D11Device *d3dDevice{};
    ID3D11DeviceContext *d3dDeviceContext{};

    ID3D11RenderTargetView *renderTargetView{};
    ID3D11Texture2D *backBuffer{};

    ID3D11DepthStencilView *depthStencilView{};
    ID3D11Texture2D *depthStencilBuffer{};

    ID3D11Buffer *vertexBuffer{};
    ID3D11VertexShader *vs{};
    ID3D11PixelShader *ps{};
    ID3DBlob *vsBuffer{};
    ID3DBlob *psBuffer{};
    ID3D11InputLayout *vertexLayout{};
};
} // namespace TramDepot