import TramDepot;
#include <Windows.h>

#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
#ifdef DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    TramDepot::Debug::Init();
#endif
    TramDepot::TramDepot game(1280, 720);

    game.MainLoop();

#ifdef DEBUG
    TramDepot::Debug::Release();
#endif // DEBUG

    return 0;
}
