module;
#include <string_view>
export module TramDepot:Debug;

export namespace TramDepot::Debug
{
void Init();
void Release();
void Log(std::string_view msg);
void Warning(std::string_view msg);
[[noreturn]] void Error(std::string_view msg);
} // namespace TramDepot::Debug