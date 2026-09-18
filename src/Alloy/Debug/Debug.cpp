#include "Debug.hpp"
#include <assert.h>

#include <print>

static bool cmdAllocated = false;

static void _print(std::string_view prefix, std::string_view msg, int colorCode)
{
    std::println("\x1B[1;{}m{}:\x1B[0m {}", colorCode, prefix, msg);
}

namespace Alloy::Debug
{

void Log(std::string_view msg, LogLevel logLevel)
{
    std::string prefix = "LOG";
    switch (logLevel)
    {
    case LogLevel::Message:
        prefix = "LOG";
        break;
    case LogLevel::Warning:
        prefix = "WARNING";
        break;
    case LogLevel::Error:
        prefix = "ERROR";
        break;
    }
    _print(prefix, msg, static_cast<int>(logLevel));
}

void Error(std::string_view msg)
{
    Log(msg, LogLevel::Error);
    MessageBoxA(nullptr, msg.data(), "Error", MB_OK | MB_ICONERROR);

    ExitProcess(1);
}

void Debug::IF_HR_FAILED(HRESULT hr, std::string_view msg)
{
    if (FAILED(hr))
        Error(std::format("{} (HRESULT: {:#0x})", msg,
                          static_cast<uint32_t>(hr)));
}

} // namespace Alloy::Debug