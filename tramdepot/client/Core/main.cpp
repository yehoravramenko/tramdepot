#include "Game.hpp"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    TramDepot::Game game;

    game.createWindow();
    game.MainLoop();

    return 0;
}
