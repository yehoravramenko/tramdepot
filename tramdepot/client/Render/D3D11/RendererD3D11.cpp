module;
#include <d3d11.h>
#include <winrt/base.h>
module TramDepot:RendererD3D11;

import :Debug;

static HRESULT hr = 0;

namespace TramDepot
{

RendererD3D11::RendererD3D11(const HWND windowHandle,
                             const WindowSize &windowSize)
{
    this->windowSize   = windowSize;
    this->windowHandle = windowHandle;

    winrt::com_ptr<IDXGIFactory> dxgiFactory;
    winrt::com_ptr<IDXGIAdapter> dxgiAdapter;
    winrt::com_ptr<IDXGIOutput> dxgiAdapterOutput;
    unsigned modesCount = 0;

    hr = CreateDXGIFactory(IID_PPV_ARGS(dxgiFactory.put()));
    if (FAILED(hr))
        Debug::Error("Failed to create DXGI Factory");

    hr = dxgiFactory->EnumAdapters(0, dxgiAdapter.put());
    if (FAILED(hr))
        Debug::Error("Failed to create DXGI Adapter");

    hr = dxgiAdapter->EnumOutputs(0, dxgiAdapterOutput.put());
    if (FAILED(hr))
        Debug::Error("Failed to create enumerate DXGI adapter outputs");

    hr = dxgiAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
                                               DXGI_ENUM_MODES_INTERLACED,
                                               &modesCount, nullptr);
    if (FAILED(hr))
        Debug::Error("Failed to get display mode list");

    std::vector<DXGI_MODE_DESC> dxgiOutputModes(modesCount);
    hr = dxgiAdapterOutput->GetDisplayModeList(
        DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &modesCount,
        dxgiOutputModes.data());

    const std::pair<UINT, UINT> screenSize = {GetSystemMetrics(SM_CXSCREEN),
                                              GetSystemMetrics(SM_CYSCREEN)};

    for (const DXGI_MODE_DESC &desc : dxgiOutputModes)
    {
        if (desc.Width == screenSize.first && desc.Height == screenSize.second)
        {
            this->refreshRate = desc.RefreshRate;
        }
    }

    if (this->refreshRate.Numerator == 0)
        Debug::Error("Failed to get suitable display mode");

    DXGI_ADAPTER_DESC adapterDesc{};

    hr = dxgiAdapter->GetDesc(&adapterDesc);
    if (FAILED(hr))
        Debug::Error("Failed to get adapter desc");

    Debug::Log(std::format("Video adapter: {}",
                           winrt::to_string(adapterDesc.Description)));
    Debug::Log(std::format("Dedicated video memory: {} MB",
                           adapterDesc.DedicatedVideoMemory / (1024 * 1024)));

    DXGI_SWAP_CHAIN_DESC swapChainDesc{
        .BufferDesc{
            .Width            = this->windowSize.width,
            .Height           = this->windowSize.height,
            .RefreshRate      = this->refreshRate,
            .Format           = DXGI_FORMAT_R8G8B8A8_UNORM,
            .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
            .Scaling          = DXGI_MODE_SCALING_UNSPECIFIED,
        },
        .SampleDesc =
            {
                .Count   = 1,
                .Quality = 0,
            },
        .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        .BufferCount  = 1,
        .OutputWindow = this->windowHandle,
        .Windowed     = true,
        .SwapEffect   = DXGI_SWAP_EFFECT_DISCARD,
    };

    UINT createDeviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;

#ifdef DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    // D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_DEBUGGABLE;
    // TODO: DEBUGGABLE (requires D3D11 1.1)
#endif // DEBUG

    hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr,
        0, D3D11_SDK_VERSION, &swapChainDesc, this->swapChain.put(),
        this->d3dDevice.put(), nullptr, this->d3dDeviceContext.put());

    if (FAILED(hr))
        Debug::Error("Failed to create D3D11 device");
}

void RendererD3D11::Update()
{
}

void RendererD3D11::Draw()
{
}

} // namespace TramDepot