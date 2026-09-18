#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wrl/client.h>
#include <d3d11.h>

#include <array>

using Microsoft::WRL::ComPtr;

namespace Alloy
{
class Renderer
{
  public:
    Renderer(HWND windowHandle, const std::array<int, 2> &windowSize);

    void BeginFrame();
    void EndFrame();

  private:
    HWND m_WindowHandle{};
    std::array<int, 2> m_Size;

    ComPtr<ID3D11Device> m_d3dDevice;
    ComPtr<ID3D11DeviceContext> m_ImmediateContext;
    ComPtr<IDXGISwapChain> m_SwapChain;
    ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
};
} // namespace Alloy