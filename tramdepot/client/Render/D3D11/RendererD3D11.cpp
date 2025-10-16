module;
#include <d3d11.h>
module TramDepot:RendererD3D11;

import :Debug;

namespace TramDepot
{
constexpr IDXGIAdapter *PRIMARY_DISPLAY_ADAPTER     = nullptr;
constexpr HMODULE NO_SOFTWARE_ADAPTER               = nullptr;
constexpr D3D_FEATURE_LEVEL *GREATEST_FEATURE_LEVEL = nullptr;

constexpr UINT MSAA_SAMPLE_COUNT = 4;

constexpr UINT SWAP_CHAIN_FLAGS = 0;

constexpr D3D11_RENDER_TARGET_VIEW_DESC *NO_DESC = nullptr;

RendererD3D11::RendererD3D11(const HWND windowHandle,
                             const WindowSize &windowSize)
{
    this->windowHandle = windowHandle;
    this->windowSize   = windowSize;

    this->createDevice();
    this->createSwapChain();
}

void RendererD3D11::createDevice()
{
    HRESULT hr;
    D3D_FEATURE_LEVEL supportedFeatureLevel;

    UINT deviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#ifdef DEBUG
    deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    hr = ::D3D11CreateDevice(
        PRIMARY_DISPLAY_ADAPTER, D3D_DRIVER_TYPE_HARDWARE, NO_SOFTWARE_ADAPTER,
        deviceFlags, GREATEST_FEATURE_LEVEL, 0, D3D11_SDK_VERSION,
        &this->d3dDevice, &supportedFeatureLevel, &this->d3dDeviceContext);

    if (FAILED(hr))
    {
        Debug::Error("Failed to create D3D11 Device");
    }
    if (supportedFeatureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        Debug::Error("DirectX 11 is not supported");
    }

    this->d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,
                                                   MSAA_SAMPLE_COUNT,
                                                   &this->qualityLevelsCount);

    // All D3D11 compatible devices must support 4xMSAA
    if (this->qualityLevelsCount <= 0)
    {
        Debug::Error("D3D11 is unsupported");
    }
}

void RendererD3D11::createSwapChain()
{
    HRESULT hr;
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    IDXGIDevice *dxgiDevice   = nullptr;
    IDXGIAdapter *dxgiAdapter = nullptr;
    IDXGIFactory *dxgiFactory = nullptr;

    ID3D11Texture2D *backBuffer = nullptr;

    swapChainDesc = {
        .BufferDesc{
            .Width  = this->windowSize.width,
            .Height = this->windowSize.height,
            .RefreshRate{.Numerator = 60, .Denominator = 1},
            .Format           = DXGI_FORMAT_R8G8B8A8_UNORM,
            .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
            .Scaling          = DXGI_MODE_SCALING_UNSPECIFIED,
        },

        .SampleDesc{.Count   = MSAA_SAMPLE_COUNT,
                    .Quality = this->qualityLevelsCount - 1},

        .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        .BufferCount  = 1,
        .OutputWindow = windowHandle,
        .Windowed     = true, // TODO: make this parameter tweakable
        .SwapEffect =
            DXGI_SWAP_EFFECT_DISCARD, // TODO: Flip Model instead of BitBlt mode
        .Flags = SWAP_CHAIN_FLAGS,
    };

    hr = this->d3dDevice->QueryInterface(
        __uuidof(IDXGIDevice), reinterpret_cast<void **>(&dxgiDevice));
    if (FAILED(hr))
    {
        Debug::Error("Failed to query IDXGIDevice interface");
    }

    hr = dxgiDevice->GetAdapter(&dxgiAdapter);
    if (FAILED(hr))
    {
        Debug::Error("Failed to get IDXGIAdapter");
    }

    hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
                                reinterpret_cast<void **>(&dxgiFactory));
    if (FAILED(hr))
    {
        Debug::Error("Failed to get IDXGIFactory");
    }

    hr = dxgiFactory->CreateSwapChain(this->d3dDevice, &swapChainDesc,
                                      &this->swapChain);
    if (FAILED(hr))
    {
        Debug::Error("Failed to create a swap chain");
    }

    dxgiDevice->Release();
    dxgiAdapter->Release();
    dxgiFactory->Release();

    hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                                    reinterpret_cast<void **>(&backBuffer));
    if (FAILED(hr))
    {
        Debug::Error("Failed to get back buffer");
    }

    hr = this->d3dDevice->CreateRenderTargetView(backBuffer, NO_DESC,
                                                 &this->renderTargetView);
    if (FAILED(hr))
    {
        Debug::Error("Failed to create render target view");
    }

    backBuffer->Release();

    D3D11_TEXTURE2D_DESC depthBufferDesc{
        .Width     = this->windowSize.width,
        .Height    = this->windowSize.height,
        .MipLevels = 1,
        .ArraySize = 1,
        .Format    = DXGI_FORMAT_D24_UNORM_S8_UINT,
        .SampleDesc{
            .Count   = 4,
            .Quality = this->qualityLevelsCount - 1,
        },
        .Usage          = D3D11_USAGE_DEFAULT,
        .BindFlags      = D3D11_BIND_DEPTH_STENCIL,
        .CPUAccessFlags = 0,
        .MiscFlags      = 0,
    };

    this->d3dDevice->CreateTexture2D(&depthBufferDesc, 0,
                                     &this->depthStencilBuffer);
    this->d3dDevice->CreateDepthStencilView(this->depthStencilBuffer, 0,
                                            &this->depthStencilView);

    this->d3dDeviceContext->OMSetRenderTargets(1, &this->renderTargetView,
                                               this->depthStencilView);

    this->viewport = {
        .TopLeftX = 0,
        .TopLeftY = 0,
        .Width    = static_cast<float>(this->windowSize.width),
        .Height   = static_cast<float>(this->windowSize.height),
        .MinDepth = 0.0,
        .MaxDepth = 1.0,
    };

    this->d3dDeviceContext->RSSetViewports(1, &this->viewport);
}

void RendererD3D11::Update()
{
}

RendererD3D11::~RendererD3D11()
{
}

} // namespace TramDepot