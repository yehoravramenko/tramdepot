#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

import Alloy;

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Alloy::Client tramDepot{};
    tramDepot.MainLoop();
}