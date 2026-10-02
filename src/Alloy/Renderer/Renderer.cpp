#include "Renderer.hpp"
#include "Debug/Debug.hpp"
#include "ShaderUtils.hpp"

#include <D3DCompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib") // For HLSL

namespace Alloy
{
struct Vertex
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT4 color;
};

static Vertex verts[] = {
    {{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
};

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

    const D3D11_BUFFER_DESC vertexBufferDesc = {
        .ByteWidth = sizeof(verts),
        .BindFlags = D3D11_BIND_VERTEX_BUFFER,
    };

    const D3D11_SUBRESOURCE_DATA resourceData = {.pSysMem = verts};

    m_d3dDevice->CreateBuffer(&vertexBufferDesc, &resourceData,
                              m_VertexBuffer.GetAddressOf());

    auto const vsBytecode = ReadCSOFile("Shaders_VS.cso");

    hr =
        m_d3dDevice->CreateVertexShader(vsBytecode.data(), vsBytecode.size(),
                                        nullptr, m_VertexShader.GetAddressOf());
    Debug::IF_HR_FAILED(hr, "Failed to create vertex shader");

    constexpr D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
         D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
         D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    hr = m_d3dDevice->CreateInputLayout(layout, ARRAYSIZE(layout),
                                        vsBytecode.data(), vsBytecode.size(),
                                        m_InputLayout.GetAddressOf());

    Debug::IF_HR_FAILED(hr, "Failed to create input layout");

    auto const psBytecode = ReadCSOFile("Shaders_PS.cso");
    m_d3dDevice->CreatePixelShader(psBytecode.data(), psBytecode.size(),
                                   nullptr, m_PixelShader.GetAddressOf());
    Debug::IF_HR_FAILED(hr, "Failed to create pixel shader");
}

void Renderer::BeginFrame()
{
    const static FLOAT clearColor[4] = {0.0f, 0.5f, 0.0f, 1.0f};

    m_ImmediateContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(),
                                           nullptr);

    m_ImmediateContext->ClearRenderTargetView(m_RenderTargetView.Get(),
                                              clearColor);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_ImmediateContext->IASetInputLayout(m_InputLayout.Get());
    m_ImmediateContext->VSSetShader(m_VertexShader.Get(), nullptr, 0);
    m_ImmediateContext->PSSetShader(m_PixelShader.Get(), nullptr, 0);
    m_ImmediateContext->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(),
                                           &stride, &offset);
    m_ImmediateContext->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_ImmediateContext->Draw(3, 0);
}

void Renderer::EndFrame()
{
    m_SwapChain->Present(1, 0);
}

} // namespace Alloy