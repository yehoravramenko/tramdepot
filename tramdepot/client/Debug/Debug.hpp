#pragma once
#include <string_view>

namespace TramDepot::Debug
{
void Init();
void Log(std::string_view msg);
void Warning(std::string_view msg);
[[noreturn]] void Error(std::string_view msg);
} // namespace TramDepot::Debug