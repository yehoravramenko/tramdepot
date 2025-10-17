module;
#include <Windows.h>
module TramDepot:Render;

import :Debug;
import :RendererD3D11;

import std;

namespace TramDepot
{

constexpr HWND NO_PARENT_HWND = nullptr;
constexpr HMENU NO_MENU       = nullptr;
constexpr LPVOID NO_LPPARAM   = 0;

Render::Render(const unsigned int windowWidth, const unsigned int windowHeight)
{
    LARGE_INTEGER performanceFrequency{};

    this->windowSize     = {.width = windowWidth, .height = windowHeight};
    this->instanceHandle = ::GetModuleHandle(nullptr);

    this->createWindow();

    this->renderer =
        std::make_unique<RendererD3D11>(this->windowHandle, this->windowSize);
}

static LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return TRUE;
    }
    return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Render::createWindow()
{
    WNDCLASS wc = {
        .style         = CS_VREDRAW | CS_HREDRAW,
        .lpfnWndProc   = WndProc,
        .lpszClassName = L"TramDepotWindow",
    };

    RegisterClass(&wc);

    this->windowHandle = ::CreateWindow(
        wc.lpszClassName, L"Tram Depot", WS_POPUP | WS_VISIBLE, CW_USEDEFAULT,
        CW_USEDEFAULT, this->windowSize.width, this->windowSize.height,
        NO_PARENT_HWND, NO_MENU, this->instanceHandle, NO_LPPARAM);

    if (this->windowHandle == nullptr)
    {
        Debug::Error("Failed to create a window");
    }

    ::UpdateWindow(this->windowHandle);
}

void Render::Update()
{
    MSG msg     = {};
    BOOL result = 0;

    result = ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
    if (result < 0)
    {
        Debug::Error("Render::Update() -> PeekMessage() An error occured");
    }
    switch (msg.message)
    {
    case WM_QUIT:
        this->postEvent(Event{.type = EventType::Exit});
        break;
    }
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);

    this->renderer->Update();
    this->renderer->Draw();
}

} // namespace TramDepot