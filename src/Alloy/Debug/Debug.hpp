#pragma once

#include <string_view>

namespace Alloy::Debug
{
enum class LogLevel
{
    Message = 32,
    Warning = 33,
    Error   = 31,
};

ALLOY_API void Log(std::string_view msg, LogLevel logLevel = LogLevel::Message);
} // namespace Alloy::Debug