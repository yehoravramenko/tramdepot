#include "Debug.hpp"

#include <print>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace TramDepot::Debug
{
enum ASCIIColor
{
    Red    = 31,
    Green  = 32,
    Yellow = 33,
};

static inline void output(const ASCIIColor col, const char *prefix,
                          std::string_view msg)
{
#ifdef DEBUG
    std::println("\x1b[;{}m{}:\x1b[0m    {}", static_cast<int>(col), prefix,
                 msg);
#endif // DEBUG
}

void Init()
{
    static bool isInitialized = false;

    if (isInitialized)
        Error("Debug::Init was called twice");

    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    // https://superuser.com/a/1529908

    HANDLE hOut  = GetStdHandle(STD_OUTPUT_HANDLE);
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
    output(ASCIIColor::Yellow, "Warning", msg);
}

[[noreturn]] void Error(std::string_view msg)
{
    output(ASCIIColor::Red, "Error", msg);
#ifdef _WIN32
    ::MessageBoxA(nullptr, msg.data(), "Error", MB_OK | MB_ICONERROR);
#endif

    std::exit(1);
}

} // namespace TramDepot::Debug