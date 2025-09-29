#define _CRT_SECURE_NO_WARNINGS
#include "Game.hpp"

#include "Debug.hpp"

namespace TramDepot
{
constexpr int MSAA_COUNT = 4;

Game::Game()
{
#ifdef DEBUG
    Debug::Init();
#endif

    D3D_FEATURE_LEVEL featureLevel;

    constexpr IDXGIAdapter *DEFAULT_ADAPTER = nullptr;
    constexpr HMODULE NO_SOFTWARE_DEVICE    = nullptr;
    constexpr UINT deviceFlags =
        D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_SINGLETHREADED;
    constexpr D3D_FEATURE_LEVEL *GREATEST_FEATURE_LEVEL = nullptr;

    auto hr = D3D11CreateDevice(DEFAULT_ADAPTER, D3D_DRIVER_TYPE_HARDWARE,
                                NO_SOFTWARE_DEVICE, deviceFlags,
                                GREATEST_FEATURE_LEVEL, 0, D3D11_SDK_VERSION,
                                &this->d3dDevice, &featureLevel, &this->ctx);

    if (FAILED(hr))
    {
        Debug::Error("Failed to create D3D11 device context");
    }

    if (featureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        Debug::Error("D3D11 is not supported");
    }
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

void Game::createWindow()
{
    WNDCLASS wc = {};

    HINSTANCE instanceHandle = GetModuleHandle(nullptr);

    wc.lpfnWndProc   = wndProc;
    wc.hInstance     = instanceHandle;
    wc.lpszClassName = L"Tram Depot";

    RegisterClass(&wc);

    this->windowHandle = CreateWindowEx(
        NULL, L"Tram Depot", L"Tram Depot", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, nullptr, nullptr,
        instanceHandle, nullptr);

    if (this->windowHandle == nullptr)
    {
        Debug::Error("Failed to create window");
    }

    UpdateWindow(this->windowHandle);
}

void Game::MainLoop()
{
    this->gameStart();
    while (this->msg.message != WM_QUIT)
    {
        if (PeekMessage(&this->msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&this->msg);
            DispatchMessage(&this->msg);
        }
        else
        {
            this->gameUpdate();
        }
    }
}

void Game::gameStart()
{
    auto hr = this->d3dDevice->CheckMultisampleQualityLevels(
        DXGI_FORMAT_R8G8B8A8_UNORM, MSAA_COUNT, &msaaQuality);

    if (FAILED(hr))
    {
        Debug::Error("4x MSAA is not avaliable");
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    swapChainDesc.BufferDesc.Width                   = 1280;
    swapChainDesc.BufferDesc.Height                  = 720;
    swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.ScanlineOrdering =
        DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    swapChainDesc.SampleDesc.Count   = MSAA_COUNT;
    swapChainDesc.SampleDesc.Quality = msaaQuality - 1;

    swapChainDesc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount  = 1;
    swapChainDesc.OutputWindow = this->windowHandle;
    swapChainDesc.Windowed     = true;
    swapChainDesc.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags        = 0;

    IDXGIDevice *dxgiDevice = nullptr;

    hr = d3dDevice->QueryInterface(__uuidof(IDXGIDevice),
                                   reinterpret_cast<void **>(&dxgiDevice));
    if (FAILED(hr))
    {
        Debug::Error("Failed to query interface");
    }

    IDXGIAdapter *dxgiAdapter = nullptr;

    hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter),
                               reinterpret_cast<void **>(&dxgiAdapter));
    if (FAILED(hr))
    {
        Debug::Error("Failed to get adapter");
    }

    IDXGIFactory *dxgiFactory = nullptr;

    hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
                                reinterpret_cast<void **>(&dxgiFactory));
    if (FAILED(hr))
    {
        Debug::Error("Failed to get factory");
    }

    hr = dxgiFactory->CreateSwapChain(this->d3dDevice, &swapChainDesc,
                                      &this->swapChain);
    if (FAILED(hr))
    {
        Debug::Error("Failed to create a swapchain");
    }

    dxgiDevice->Release();
    dxgiAdapter->Release();
    dxgiFactory->Release();
}

void Game::gameUpdate()
{
}

HWND Game::getWindowHandle()
{
    return this->windowHandle;
}

Game::~Game()
{
#ifdef DEBUG
    FreeConsole();
#endif
}

} // namespace TramDepot