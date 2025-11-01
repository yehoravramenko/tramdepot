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
    ID3D11Device *d3dDevice                  = {};
    ID3D11DeviceContext *d3dDeviceContext    = {};
    IDXGISwapChain *swapChain                = {};
    ID3D11Texture2D *swapChainBuffer         = {};
    ID3D11Debug *debugLayer                  = {};
    ID3D11RenderTargetView *renderTargetView = {};
    ID3D11Texture2D *depthStencilBuffer      = {};
    ID3D11DepthStencilView *depthStencilView = {};

    /*UINT qualityLevelsCount = 0;*/

    // TODO: implement MSAA
    struct
    {
        unsigned int count   = 1;
        unsigned int quality = 0;
    } msaaSamples;

    void initializeD3D();
    void createDepthStencil();
};
} // namespace TramDepot