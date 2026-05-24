#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

import Alloy;

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // TODO: check _DEBUG and add linker flags for console
    Alloy::Client tramDepot;
    tramDepot.MainLoop();
}