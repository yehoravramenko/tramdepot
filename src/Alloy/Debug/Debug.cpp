#define _CRT_SECURE_NO_WARNINGS
module;
#include <Windows.h>
#include <cassert>
#include <cstdio>
module Alloy:Debug;

import std;

namespace Alloy
{
bool Debug::isInitialized = false;

void Debug::output(const ASCIIColor col, const char *prefix,
                   const std::string_view msg, const unsigned hr,
                   std::ostream &out)
{
    if (!Debug::isInitialized)
        Debug::Init();

    std::print(out, "\x1b[;{}m{}:\x1b[0m    {}", static_cast<int>(col), prefix,
               msg);

    if (hr != 0)
        std::println(" ({:#0x})", hr);
    else
        std::println();
}

void Debug::Init()
{
    assert(!Debug::isInitialized);
    assert(_DEBUG);

    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // https://superuser.com/a/1529908

    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    Debug::isInitialized = true;
}

void Debug::Release()
{
    if (!Debug::isInitialized)
        return;
    FreeConsole();
}

void Debug::Log(const std::string_view msg, const unsigned hr)
{
    Debug::output(ASCIIColor::Green, "Log", msg, hr);
}

void Debug::Warning(const std::string_view msg, const unsigned hr)
{
    Debug::output(ASCIIColor::Yellow, "Warning", msg, hr, std::cerr);
}

[[noreturn]] void Debug::Error(const std::string_view msg, const unsigned hr)
{
    Debug::output(ASCIIColor::Red, "Error", msg, hr, std::cerr);
#ifdef _WIN32
    if (hr != 0)
    {
        ::MessageBoxA(nullptr, std::format("{} ({:#0x})", msg, hr).c_str(),
                      "Error", MB_OK | MB_ICONERROR);
    }
    else
    {
        ::MessageBoxA(nullptr, msg.data(), "Error", MB_OK | MB_ICONERROR);
    }
#endif

    std::exit(1);
}
} // namespace Alloy