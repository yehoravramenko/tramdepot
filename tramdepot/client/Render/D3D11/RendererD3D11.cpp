module;
#include <d3d11.h>
module TramDepot:RendererD3D11;

import :Debug;
import std;

// We constantly check d3d functions for failure, so there is no reason to
// create separate HRESULT in every function.
// TODO: or it is?
static HRESULT hr = 0;

namespace TramDepot
{

RendererD3D11::RendererD3D11(const HWND windowHandle)
{
    constexpr IDXGIAdapter *DEFAULT_VIDEO_ADAPTER = nullptr;
    constexpr HMODULE NULL_SOFTWARE_MODULE        = nullptr;
    constexpr UINT runtimeLayersFlags             = D3D11_CREATE_DEVICE_DEBUG;

    constexpr D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0};
    constexpr UINT featureLevelsCount           = 1;

    // UINT msaaQualityLevels{};
    //  TODO: ID3D11Device::CheckMultisampleQualityLevels()

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
        .OutputWindow = windowHandle,
        .Windowed     = true,
        .SwapEffect   = DXGI_SWAP_EFFECT_DISCARD,
    };

    hr = D3D11CreateDeviceAndSwapChain(
        DEFAULT_VIDEO_ADAPTER, D3D_DRIVER_TYPE_HARDWARE, NULL_SOFTWARE_MODULE,
        runtimeLayersFlags, featureLevels, featureLevelsCount,
        D3D11_SDK_VERSION, &swapChainDesc, &this->swapChain, &this->d3dDevice,
        nullptr, &this->d3dDeviceContext);

    if (FAILED(hr))
    {
        Debug::Error(std::format(
            "D3D11: Failed to create device and swapchain ({:08x})", hr));
    }

    hr = this->swapChain->GetBuffer(
        0, __uuidof(ID3D11Texture2D),
        reinterpret_cast<void **>(&this->backBuffer));

    if (FAILED(hr))
    {
        Debug::Error("D3D11: Failed to obtain back buffer");
    }

    hr = this->d3dDevice->CreateRenderTargetView(this->backBuffer, nullptr,
                                                 &this->renderTargetView);

    if (FAILED(hr))
    {
        Debug::Error("D3D11: Failed to create render target view");
    }

    this->d3dDeviceContext->OMSetRenderTargets(1, &this->renderTargetView,
                                               nullptr);
}

RendererD3D11::~RendererD3D11()
{
}

void RendererD3D11::Update()
{
}

void RendererD3D11::Draw()
{
}

} // namespace TramDepot