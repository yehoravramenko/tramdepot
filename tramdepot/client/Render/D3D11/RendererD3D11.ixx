module;
#include <d3d11.h>
export module TramDepot:RendererD3D11;

import :IRenderer;
import std;
import wext;

namespace TramDepot
{
class RendererD3D11 : public IRenderer
{
  public:
    RendererD3D11(const HWND windowHandle, const WindowSize &windowSize);
    ~RendererD3D11();

    void Update() override;
    void Draw() override;

    [[noreturn]] static inline void Error(std::string_view message);

  private:
    HWND windowHandle;
    WindowSize size;

    wext::com_ptr<IDXGISwapChain> swapChain;
    wext::com_ptr<ID3D11Device> d3dDevice;
    wext::com_ptr<ID3D11DeviceContext> d3dDeviceContext;

    wext::com_ptr<ID3D11RenderTargetView> renderTargetView;
    wext::com_ptr<ID3D11Texture2D> backBuffer;

    wext::com_ptr<ID3D11DepthStencilView> depthStencilView;
    wext::com_ptr<ID3D11Texture2D> depthStencilBuffer;

    wext::com_ptr<ID3D11Buffer> vertexBuffer;
    wext::com_ptr<ID3D11VertexShader> vs;
    wext::com_ptr<ID3D11PixelShader> ps;
    wext::com_ptr<ID3DBlob> vsBuffer;
    wext::com_ptr<ID3DBlob> psBuffer;
    wext::com_ptr<ID3D11InputLayout> vertexLayout;

    void createSwapchain();
    void createRenderTargetView();
    void createDepthStencilView();
    void compileShaders();
};
} // namespace TramDepot