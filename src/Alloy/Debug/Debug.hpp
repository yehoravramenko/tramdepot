#pragma once
#include <string_view>
#include <format>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Alloy::Debug
{
enum class LogLevel
{
    Message = 32,
    Warning = 33,
    Error   = 31,
};

ALLOY_API void Log(std::string_view msg, LogLevel logLevel = LogLevel::Message);
[[noreturn]] ALLOY_API void Error(std::string_view msg);
[[noreturn]] void IF_HR_FAILED(HRESULT hr, std::string_view msg);
} // namespace Alloy::Debug