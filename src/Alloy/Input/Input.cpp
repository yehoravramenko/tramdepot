module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "glm/vec2.hpp"
module Alloy:Input;
import :Debug;

namespace Alloy
{
int Input::mouseX{}, Input::mouseY{};

bool Input::GetKey(char ch)
{
    return GetAsyncKeyState(ch) < 0;
}

void Input::updateMouse()
{
    POINT pt{};
    HWND handle = GetActiveWindow();

    GetCursorPos(&pt);
    ScreenToClient(handle, &pt);
    Input::mouseX = pt.x;
    Input::mouseY = pt.y;
}

void Input::SetMousePos(int newMouseX, int newMouseY)
{
    const HWND handle = GetActiveWindow();
    POINT pt{.x = newMouseX, .y = newMouseY};

    ClientToScreen(handle, &pt);
    SetCursorPos(pt.x, pt.y);
}

void Input::SetMousePos(const glm::ivec2 &newMousePos)
{
    Input::SetMousePos(newMousePos.x, newMousePos.y);
}

bool Input::GetMouseButton(const MouseButton mouseButton)
{
    return GetAsyncKeyState(static_cast<int>(mouseButton)) < 0;
}

void Input::HideCursor()
{
    for (int i = ::ShowCursor(FALSE); i >= 0; i = ::ShowCursor(FALSE))
    {
    }
}

void Input::ShowCursor()
{
    ::ShowCursor(TRUE);
}

} // namespace Alloy