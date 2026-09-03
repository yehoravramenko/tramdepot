#include "Debug.hpp"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
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
        prefix = "WARNING";
        break;
    case LogLevel::Error:
        prefix = "ERROR";
        break;
    }
    _print(prefix, msg, static_cast<int>(logLevel));
}

} // namespace Alloy::Debug