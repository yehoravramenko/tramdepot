export module Alloy:Input;

namespace Alloy
{
class Input
{
    friend class Window;

  public:
    static bool GetKey(char ch);

    static int GetMouseX() { return Input::mouseX; }
    static int GetMouseY() { return Input::mouseY; }
    static void SetMousePos(int newMouseX, int newMouseY);

  private:
    static int mouseX, mouseY;

    static void mouseMoved(int newMouseX, int newMouseY);
};
} // namespace Alloy