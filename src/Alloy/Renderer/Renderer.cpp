#include "Renderer.hpp"
#include "Debug/Debug.hpp"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib") // For HLSL

namespace Alloy
{
Renderer::Renderer(HWND windowHandle, const std::array<int, 2> &windowSize)
    : m_WindowHandle(windowHandle), m_Size(windowSize)
{
    const DXGI_SWAP_CHAIN_DESC scDesc = {
        .BufferDesc{
            .Width  = static_cast<UINT>(m_Size[0]),
            .Height = static_cast<UINT>(m_Size[1]),
            .RefreshRate =
                {
                    .Numerator   = 60, // TODO: variable refresh rate
                    .Denominator = 1,
                },
            .Format = DXGI_FORMAT_R8G8B8A8_UNORM,
        },
        .SampleDesc{
            .Count   = 1,
            .Quality = 0,
        },
        .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        .BufferCount  = 2,
        .OutputWindow = m_WindowHandle,
        .Windowed     = TRUE,
        .SwapEffect   = DXGI_SWAP_EFFECT_FLIP_DISCARD,
    };

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel{};
    D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0};

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags,
        featureLevels, 1, D3D11_SDK_VERSION, &scDesc,
        m_SwapChain.GetAddressOf(), m_d3dDevice.GetAddressOf(), &featureLevel,
        m_ImmediateContext.GetAddressOf());

    Debug::IF_HR_FAILED(hr, "Failed to create D3D11 device.");

    ComPtr<ID3D11Texture2D> backBuffer;
    hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));

    Debug::IF_HR_FAILED(hr, "Failed to query back buffer");

    hr = m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr,
                                             m_RenderTargetView.GetAddressOf());

    Debug::IF_HR_FAILED(hr, "Failed to create render target view");

    const D3D11_VIEWPORT viewport = {
        .TopLeftX = 0.0f,
        .TopLeftY = 0.0f,
        .Width    = static_cast<FLOAT>(m_Size[0]),
        .Height   = static_cast<FLOAT>(m_Size[1]),
        .MinDepth = 0.0f,
        .MaxDepth = 1.0f,
    };

    m_ImmediateContext->RSSetViewports(1, &viewport);
}

void Renderer::BeginFrame()
{
    const static FLOAT clearColor[4] = {0.0f, 0.5f, 0.0f, 1.0f};

    m_ImmediateContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(),
                                           nullptr);

    m_ImmediateContext->ClearRenderTargetView(m_RenderTargetView.Get(),
                                              clearColor);

    m_SwapChain->Present(1, 0);
}

void Renderer::EndFrame()
{
}

} // namespace Alloy