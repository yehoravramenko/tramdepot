#pragma once
#include <filesystem>

namespace Alloy
{
std::filesystem::path GetExecutableDirectory();
void SetWorkingDirectory(const std::filesystem::path &dir);
} // namespace Alloy