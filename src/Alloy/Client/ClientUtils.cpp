#include "ClientUtils.hpp"
#include "Debug/Debug.hpp"

#include <windows.h>

namespace Alloy
{
std::filesystem::path GetExecutableDirectory()
{
    wchar_t buffer[MAX_PATH]{};
    auto length = GetModuleFileNameW(nullptr, buffer, MAX_PATH);

    if (length == 0)
        Debug::Error("Failed to get path to exe");

    return std::filesystem::path(buffer).parent_path();
}

void SetWorkingDirectory(const std::filesystem::path &dir)
{
    std::filesystem::current_path(dir);
}
} // namespace Alloy