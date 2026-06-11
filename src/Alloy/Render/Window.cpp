module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>
module Alloy:Window;
import :Debug;
import :Input;

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam,
                                LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        return TRUE;
    case WM_DESTROY:
        PostQuitMessage(0);
        return TRUE;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

namespace Alloy
{
Window::Window(EventHandler *eventHandler) : eventHandler(eventHandler)
{
    HINSTANCE instanceHandle = GetModuleHandle(nullptr);

    WNDCLASSEX wndClass = {
        .cbSize        = sizeof(WNDCLASSEX),
        .style         = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc   = &WndProc,
        .hInstance     = instanceHandle,
        .hIcon         = LoadIcon(nullptr, IDI_WINLOGO),
        .lpszClassName = L"AlloyWindow",
    };

    RegisterClassEx(&wndClass);

    constexpr DWORD style = (WS_OVERLAPPEDWINDOW | WS_VISIBLE);
    this->handle =
        CreateWindowEx(0, wndClass.lpszClassName, L"Alloy Engine", style,
                       CW_USEDEFAULT, CW_USEDEFAULT, this->width, this->height,
                       nullptr, nullptr, instanceHandle, nullptr);

    SetWindowLongPtr(this->handle, GWLP_USERDATA,
                     reinterpret_cast<LONG_PTR>(this));

    const HDC hdc = GetDC(this->handle);

    constexpr PIXELFORMATDESCRIPTOR pixelFormatDesc = {
        .nSize      = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion   = 1,
        .dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = 32,
    };

    int pixelFormat = ChoosePixelFormat(hdc, &pixelFormatDesc);
    if (pixelFormat == 0)
        Debug::Error("Failed to find suitable pixel format for HDC");

    if (SetPixelFormat(hdc, pixelFormat, &pixelFormatDesc) == FALSE)
        Debug::Error("Failed to set pixel format", GetLastError());

    // DescribePixelFormat(hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR),
    //                     &pixelFormatDesc);

    ReleaseDC(this->handle, hdc);
}

void Window::Update()
{
    MSG msg{};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
    {
        switch (msg.message)
        {
        case WM_QUIT:
            this->eventHandler->PushEvent({EventType::WindowClosed});
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Input::updateMouse();
}
} // namespace Alloy