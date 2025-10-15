import TramDepot;
#include <Windows.h>

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    TramDepot::TramDepot game(1280, 720);

    game.MainLoop();

    return 0;
}
