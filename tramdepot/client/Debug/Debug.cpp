module;

#ifdef _WIN32
#include <Windows.h>
#endif

#include <cstdio>

module TramDepot:Debug;

import std;

namespace TramDepot::Debug
{
enum ASCIIColor
{
    Red    = 31,
    Green  = 32,
    Yellow = 33,
};

static inline void output(const ASCIIColor col, const char *prefix,
                          std::string_view msg, std::ostream &out = std::cout)
{
#ifdef DEBUG
    std::println(out, "\x1b[;{}m{}:\x1b[0m    {}", static_cast<int>(col),
                 prefix, msg);
#endif // DEBUG
}

void Init()
{
    static bool isInitialized = false;

    if (isInitialized)
        Debug::Error("Debug::Init was called twice");

    AllocConsole();
    std::freopen("CONIN$", "r", stdin);
    std::freopen("CONOUT$", "w", stdout);
    std::freopen("CONOUT$", "w", stderr);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // https://superuser.com/a/1529908

    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    isInitialized = true;
}

void Release()
{
    FreeConsole();
}

void Log(std::string_view msg)
{
    output(ASCIIColor::Green, "Log", msg);
}

void Warning(std::string_view msg)
{
    output(ASCIIColor::Yellow, "Warning", msg, std::cerr);
}

[[noreturn]] void Error(std::string_view msg)
{
    output(ASCIIColor::Red, "Error", msg, std::cerr);
#ifdef _WIN32
    ::MessageBoxA(nullptr, msg.data(), "Error", MB_OK | MB_ICONERROR);
#endif

    std::exit(1);
}

} // namespace TramDepot::Debug