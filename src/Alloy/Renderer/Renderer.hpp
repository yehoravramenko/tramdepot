#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <DirectXMath.h>

#include <array>

using Microsoft::WRL::ComPtr;

namespace Alloy
{
struct alignas(16) TransformCB
{
    DirectX::XMMATRIX worldViewProjection;
};

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

    ComPtr<ID3D11Buffer> m_VertexBuffer;
    ComPtr<ID3D11Buffer> m_ConstantBuffer;

    ComPtr<ID3D11InputLayout> m_InputLayout;
    ComPtr<ID3D11VertexShader> m_VertexShader;
    ComPtr<ID3D11PixelShader> m_PixelShader;

    void _ClearFramebuffer();
};
} // namespace Alloy