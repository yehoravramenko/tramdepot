#include "Client.hpp"
#include <Windows.h>

namespace Alloy
{
Client::Client() : m_Window(1024, 768)
{
}

void Client::MainLoop()
{
    MessageBox(nullptr, L"test", L"", MB_OK);
}
} // namespace Alloy