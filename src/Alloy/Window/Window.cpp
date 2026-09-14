#include "Window.hpp"
#include "Debug/Debug.hpp"

#include <Windows.h>

namespace Alloy
{
Window::Window(int width, int height)
{
    m_SDLWindow = SDL_CreateWindow("Alloy Engine", width, height, 0);

    if (m_SDLWindow == nullptr)
    {
        Debug::Log("Failed to create a window", Debug::LogLevel::Error);
    }
}

HWND Window::GetWindowHandle() const
{
    SDL_PropertiesID props = SDL_GetWindowProperties(m_SDLWindow);
    HWND handle            = reinterpret_cast<HWND>(SDL_GetPointerProperty(
        props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr));

    if (handle == nullptr)
    {
        Debug::Log("Failed to get HWND", Debug::LogLevel::Error);
        // return nullptr;
    }

    return handle;
}

Window::~Window()
{
    SDL_DestroyWindow(m_SDLWindow);
    SDL_Quit();
}
} // namespace Alloy