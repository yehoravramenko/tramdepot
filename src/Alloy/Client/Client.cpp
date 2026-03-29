module;
#include <Windows.h>
module Alloy:Client;

constexpr WCHAR CLASS_NAME[] = TEXT("AlloyEngineWindowClass");

namespace Alloy
{

Client::Client(const HINSTANCE hInstance)
{
    MessageBox(nullptr, L"Alloy!", L"", MB_OK | MB_ICONINFORMATION);
    // WNDCLASSEX wc = {
    //     .cbSize        = sizeof(WNDCLASSEX),
    //     .hInstance     = hInstance,
    //     .lpszClassName = CLASS_NAME,
    // };

    // if (!RegisterClassEx(&wc))
}

} // namespace Alloy