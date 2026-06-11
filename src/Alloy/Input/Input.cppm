module;
#include "glm/vec2.hpp"
export module Alloy:Input;

export namespace Alloy
{
enum class MouseButton
{
    Left   = 0x01,
    Middle = 0x04,
    Right  = 0x02,
};

class Input
{
    friend class Window;

  public:
    static bool GetKey(char ch);

    static int GetMouseX() { return Input::mouseX; }
    static int GetMouseY() { return Input::mouseY; }
    static void SetMousePos(int newMouseX, int newMouseY);
    static void SetMousePos(const glm::ivec2 &newMousePos);
    static bool GetMouseButton(const MouseButton mouseButton);
    static void HideCursor();
    static void ShowCursor();

  private:
    static int mouseX, mouseY;

    static void updateMouse();
};
} // namespace Alloy