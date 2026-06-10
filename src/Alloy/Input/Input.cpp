module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
module Alloy:Input;
import :Debug;

namespace Alloy
{
int Input::mouseX{}, Input::mouseY{};

void Input::mouseMoved(int newMouseX, int newMouseY)
{
    Input::mouseX = newMouseX;
    Input::mouseY = newMouseY;

    Debug::Log(std::format("{}, {}", Input::mouseX, Input::mouseY));
}

void Input::SetMousePos(int newMouseX, int newMouseY)
{
    SetCursorPos(newMouseX, newMouseY);
}

bool Input::GetKey(char ch)
{
    return GetAsyncKeyState(ch) < 0;
}

} // namespace Alloy