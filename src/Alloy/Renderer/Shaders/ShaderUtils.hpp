#pragma once
#include <vector>
#include <string_view>

namespace Alloy::ShaderUtils
{
std::vector<char> ReadCSOFile(std::string_view filepath);
}