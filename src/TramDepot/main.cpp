#include "Windows.h"

auto WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                    _In_ LPSTR lpCmdLine, _In_ int nShowCmd) -> int
{
    MessageBox(NULL, "Tram Depot", "", MB_OK | MB_ICONINFORMATION);

    return 0;
}
