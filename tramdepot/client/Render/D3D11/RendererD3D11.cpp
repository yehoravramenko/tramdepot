module;
#include <d3d11.h>
module TramDepot:RendererD3D11;

import :Debug;

// We constantly check d3d functions for failure, so there is no reason to
// create separate HRESULT in every function.
static HRESULT hr = 0;

namespace TramDepot
{
RendererD3D11::RendererD3D11(const HWND windowHandle,
                             const WindowSize &windowSize)
{
    this->windowHandle = windowHandle;
    this->windowSize   = windowSize;

    this->initializeD3D();
}

void RendererD3D11::initializeD3D()
{
    D3D_FEATURE_LEVEL supportedFeatureLevel;
    UINT deviceFlags                   = D3D11_CREATE_DEVICE_SINGLETHREADED;
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    constexpr IDXGIAdapter *PRIMARY_DISPLAY_ADAPTER     = nullptr;
    constexpr HMODULE NO_SOFTWARE_ADAPTER               = nullptr;
    constexpr D3D_FEATURE_LEVEL *GREATEST_FEATURE_LEVEL = nullptr;
    constexpr UINT SWAP_CHAIN_FLAGS                     = 0;

#ifdef DEBUG
    deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    swapChainDesc = {
        .BufferDesc{
            .Width  = this->windowSize.width,
            .Height = this->windowSize.height,
            // TODO: get refresh rate data from Render class
            .RefreshRate{.Numerator = 60, .Denominator = 1},
            .Format           = DXGI_FORMAT_R8G8B8A8_UNORM,
            .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
            .Scaling          = DXGI_MODE_SCALING_UNSPECIFIED,
        },

        // TODO: implement MSAA
        .SampleDesc{.Count   = this->msaaSamples.count,
                    .Quality = this->msaaSamples.quality},

        .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        .BufferCount  = 1,
        .OutputWindow = windowHandle,
        .Windowed     = true, // TODO: make this parameter tweakable
        .SwapEffect =
            DXGI_SWAP_EFFECT_DISCARD, // TODO: Flip Model instead of BitBlt mode
        .Flags = SWAP_CHAIN_FLAGS,
    };

    hr = ::D3D11CreateDeviceAndSwapChain(
        PRIMARY_DISPLAY_ADAPTER, D3D_DRIVER_TYPE_HARDWARE, NO_SOFTWARE_ADAPTER,
        deviceFlags, GREATEST_FEATURE_LEVEL, 0, D3D11_SDK_VERSION,
        &swapChainDesc, &this->swapChain, &this->d3dDevice,
        &supportedFeatureLevel, &this->d3dDeviceContext);

    if (FAILED(hr))
    {
        Debug::Error("Failed to create D3D11 Device");
    }
    if (supportedFeatureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        Debug::Error("DirectX 11 is not supported");
    }

    // TODO: implement MSAA
    // this->d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,
    //                                                MSAA_SAMPLE_COUNT,
    //                                                &this->qualityLevelsCount);

    //// All D3D11 compatible devices must support 4xMSAA
    // if (this->qualityLevelsCount <= 0)
    //{
    //     Debug::Error("DirectX 11 is not supported");
    // }

    hr = this->swapChain->GetBuffer(
        0, __uuidof(ID3D11Texture2D),
        reinterpret_cast<void **>(&this->swapChainBuffer));

    if (FAILED(hr))
    {
        Debug::Error("Failed to get a back buffer from swap chain");
    }

#ifdef DEBUG
    hr = this->d3dDevice->QueryInterface(
        __uuidof(ID3D11Debug), reinterpret_cast<void **>(&this->debugLayer));

    if (FAILED(hr))
    {
        Debug::Error("Failed to get a debug layer from D3D device");
    }
#endif // DEBUG

    static constexpr D3D11_RENDER_TARGET_VIEW_DESC *NO_DESC = nullptr;
    hr = this->d3dDevice->CreateRenderTargetView(this->swapChainBuffer, NO_DESC,
                                                 &this->renderTargetView);

    if (FAILED(hr))
    {
        Debug::Error("Failed to get a debug layer from D3D device");
    }

    this->createDepthStencil();
}

void RendererD3D11::createDepthStencil()
{
    const D3D11_TEXTURE2D_DESC desc = {
        .Width     = this->windowSize.width,
        .Height    = this->windowSize.height,
        .MipLevels = 1,
        .ArraySize = 1,
        .Format    = DXGI_FORMAT_D32_FLOAT,
        .SampleDesc{
            .Count   = this->msaaSamples.count,
            .Quality = this->msaaSamples.quality,
        },
        .Usage     = D3D11_USAGE_DEFAULT,
        .BindFlags = D3D11_BIND_DEPTH_STENCIL,
    };

    static constexpr D3D11_SUBRESOURCE_DATA *NO_INITIAL_DATA = nullptr;
    hr = this->d3dDevice->CreateTexture2D(&desc, NO_INITIAL_DATA,
                                          &this->depthStencilBuffer);
    if (FAILED(hr))
    {
        Debug::Error("Failed to create a depth stencil buffer");
    }

    static constexpr D3D11_DEPTH_STENCIL_VIEW_DESC *NO_DESC = nullptr;
    hr = this->d3dDevice->CreateDepthStencilView(
        this->depthStencilBuffer, NO_DESC, &this->depthStencilView);

    if (FAILED(hr))
    {
        Debug::Error("Failed to create a depth stencil view");
    }

    this->d3dDeviceContext->OMSetRenderTargets(1, &this->renderTargetView,
                                               this->depthStencilView);
}

void RendererD3D11::Update()
{
}

void RendererD3D11::Draw()
{
    static constexpr float juliaGreenColor[] = {0.0, 0.5, 0.0, 1.0};

    this->d3dDeviceContext->ClearRenderTargetView(this->renderTargetView,
                                                  juliaGreenColor);
    this->d3dDeviceContext->ClearDepthStencilView(
        this->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f,
        0);

    // TODO: remove magic numbers
    this->swapChain->Present(0, 0);
}

RendererD3D11::~RendererD3D11()
{
    this->d3dDeviceContext->ClearState();

    this->renderTargetView->Release();
    this->depthStencilView->Release();
    this->depthStencilBuffer->Release();

    this->swapChainBuffer->Release();
    this->swapChain->Release();
    this->d3dDeviceContext->Release();

#ifdef DEBUG
    this->debugLayer->Release();
#endif // DEBUG

    this->d3dDevice->Release();
}

} // namespace TramDepot