module;
#include <d3d11.h>
#include <d3dcompiler.h>
module TramDepot:RendererD3D11;

import :Debug;
import std;
import DX11;

// Since we constantly check d3d functions for failure, there is no reason to
// create separate HRESULT in every function.
// TODO: or it is?
static HRESULT hr = 0;

namespace TramDepot
{

void RendererD3D11::Error(std::string_view message)
{
    Debug::Error(std::format("D3D11: {}", message));
}

RendererD3D11::RendererD3D11(const HWND windowHandle,
                             const WindowSize &windowSize)
{
    this->windowHandle = windowHandle;
    this->windowSize   = windowSize;

    this->createSwapchain();
    this->createRenderTargetView();
    this->createDepthStencilView();
    this->compileShaders();

    DX11::Vertex v[] = {
        {0.0f, 0.5f, 0.5f},
        {0.5f, -0.5f, 0.5f},
        {-0.5f, -0.5f, 0.5f},
    };

    D3D11_BUFFER_DESC vertexBufferDesc = {
        .ByteWidth      = sizeof(DX11::Vertex) * 3,
        .Usage          = D3D11_USAGE_DEFAULT,
        .BindFlags      = D3D11_BIND_VERTEX_BUFFER,
        .CPUAccessFlags = 0,
        .MiscFlags      = 0,
    };

    D3D11_SUBRESOURCE_DATA vertexBufferData = {
        .pSysMem = v,
    };

    hr = this->d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData,
                                       this->vertexBuffer.put());
    // TODO: check buffer for errors

    UINT stride = sizeof(DX11::Vertex);
    UINT offset = 0;
    this->d3dDeviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer.put(),
                                               &stride, &offset);

    hr = this->d3dDevice->CreateInputLayout(
        DX11::Vertex::layout, 1, this->vsBuffer->GetBufferPointer(),
        this->vsBuffer->GetBufferSize(), this->vertexLayout.put());

    this->d3dDeviceContext->IASetInputLayout(this->vertexLayout.get());
    this->d3dDeviceContext->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    D3D11_VIEWPORT viewport = {
        .TopLeftX = 0,
        .TopLeftY = 0,
        .Width    = static_cast<float>(this->windowSize.width),
        .Height   = static_cast<float>(this->windowSize.height),
        .MinDepth = 0.0f,
        .MaxDepth = 1.0f,
    };

    this->d3dDeviceContext->RSSetViewports(1, &viewport);
}

RendererD3D11::~RendererD3D11()
{
}

void RendererD3D11::createSwapchain()
{
    constexpr IDXGIAdapter *DEFAULT_VIDEO_ADAPTER = nullptr;
    constexpr HMODULE NULL_SOFTWARE_MODULE        = nullptr;
    constexpr UINT runtimeLayersFlags             = D3D11_CREATE_DEVICE_DEBUG;

    constexpr D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0};
    constexpr UINT featureLevelsCount           = 1;

    // UINT msaaQualityLevels{};
    // TODO: ID3D11Device::CheckMultisampleQualityLevels()

    const DXGI_SWAP_CHAIN_DESC swapChainDesc = {
        .BufferDesc{
            .RefreshRate{.Numerator = 60, .Denominator = 1},
            .Format           = DXGI_FORMAT_R8G8B8A8_UNORM,
            .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
            .Scaling          = DXGI_MODE_SCALING_UNSPECIFIED,
        },
        .SampleDesc{.Count = 1, .Quality = 0},
        .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        .BufferCount  = 1,
        .OutputWindow = this->windowHandle,
        .Windowed     = true,
        .SwapEffect   = DXGI_SWAP_EFFECT_DISCARD,
    };

    hr = D3D11CreateDeviceAndSwapChain(
        DEFAULT_VIDEO_ADAPTER, D3D_DRIVER_TYPE_HARDWARE, NULL_SOFTWARE_MODULE,
        runtimeLayersFlags, featureLevels, featureLevelsCount,
        D3D11_SDK_VERSION, &swapChainDesc, this->swapChain.put(),
        this->d3dDevice.put(), nullptr, this->d3dDeviceContext.put());

    if (FAILED(hr))
        RendererD3D11::Error(
            std::format("Failed to create device and swapchain ({:08x})", hr));
}

void RendererD3D11::createRenderTargetView()
{
    hr = this->swapChain->GetBuffer(
        0, __uuidof(ID3D11Texture2D),
        reinterpret_cast<void **>(&this->backBuffer));

    if (FAILED(hr))
        RendererD3D11::Error("Failed to obtain back buffer");

    hr = this->d3dDevice->CreateRenderTargetView(
        this->backBuffer.get(), nullptr, this->renderTargetView.put());

    if (FAILED(hr))
        RendererD3D11::Error("Failed to create render target view");
}

void RendererD3D11::createDepthStencilView()
{
    D3D11_TEXTURE2D_DESC depthStencilDesc = {
        .Width     = this->windowSize.width,
        .Height    = this->windowSize.height,
        .MipLevels = 1,
        .ArraySize = 1,
        .Format    = DXGI_FORMAT_D24_UNORM_S8_UINT,
        .SampleDesc{.Count = 1, .Quality = 0},
        .Usage          = D3D11_USAGE_DEFAULT,
        .BindFlags      = D3D11_BIND_DEPTH_STENCIL,
        .CPUAccessFlags = 0,
        .MiscFlags      = 0,
    };

    hr = this->d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr,
                                          this->depthStencilBuffer.put());

    if (FAILED(hr))
        RendererD3D11::Error(
            "(createDepthStencilView): Failed to create 2D Texture");

    hr = this->d3dDevice->CreateDepthStencilView(
        this->depthStencilBuffer.get(), nullptr, this->depthStencilView.put());

    if (FAILED(hr))
        RendererD3D11::Error(
            "(createDepthStencilView): Failed to create depth/stencil view");

    this->d3dDeviceContext->OMSetRenderTargets(1, this->renderTargetView.put(),
                                               this->depthStencilView.get());
}

void RendererD3D11::compileShaders()
{
    constexpr char shader_data[] = R"(
        float4 VS(float4 inPos : POSITION) : SV_Position
        { 
            return inPos; 
        }
        float4 PS() : SV_Target
        { 
            return float4(0.0f, 0.3f, 0.0f, 1.0f); 
        }
       )";

    hr = ::D3DCompile(shader_data, sizeof shader_data / sizeof shader_data[0],
                      nullptr, nullptr, nullptr, "VS", "vs_5_0", 0, 0,
                      this->vsBuffer.put(), nullptr);
    hr = ::D3DCompile(shader_data, sizeof shader_data / sizeof shader_data[0],
                      nullptr, nullptr, nullptr, "PS", "ps_5_0", 0, 0,
                      this->psBuffer.put(), nullptr);

    // TODO: Shader class?
    if (FAILED(hr))
        RendererD3D11::Error("Shader compilation error");

    hr = this->d3dDevice->CreateVertexShader(this->vsBuffer->GetBufferPointer(),
                                             this->vsBuffer->GetBufferSize(),
                                             nullptr, this->vs.put());

    if (FAILED(hr))
        RendererD3D11::Error("Failed to create vertex shader");

    hr = this->d3dDevice->CreatePixelShader(this->psBuffer->GetBufferPointer(),
                                            this->psBuffer->GetBufferSize(),
                                            nullptr, this->ps.put());

    if (FAILED(hr))
        RendererD3D11::Error("Failed to create pixel shader");

    // TODO: check shader objects creation result

    this->d3dDeviceContext->VSSetShader(this->vs.get(), nullptr, 0);
    this->d3dDeviceContext->PSSetShader(this->ps.get(), nullptr, 0);
}

void RendererD3D11::Update()
{
}

void RendererD3D11::Draw()
{
    const float juliaGreenColor[] = {0.0f, 0.5f, 0.0f, 1.0f};
    this->d3dDeviceContext->ClearRenderTargetView(this->renderTargetView.get(),
                                                  juliaGreenColor);
    this->d3dDeviceContext->ClearDepthStencilView(
        this->depthStencilView.get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
        1.0f, 0);

    this->d3dDeviceContext->Draw(3, 0);

    this->swapChain->Present(0, 0);
}

} // namespace TramDepot