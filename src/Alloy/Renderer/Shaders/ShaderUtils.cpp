#include "ShaderUtils.hpp"
#include "Debug/Debug.hpp"

#include <fstream>

namespace Alloy::ShaderUtils
{
std::vector<char> ReadCSOFile(std::string_view filepath)
{
    std::ifstream shaderFile(filepath.data(), std::ios::binary | std::ios::ate);
    if (!shaderFile.is_open())
    {
        Debug::Error("Failed to open shader binary");
    }

    size_t fileSize = shaderFile.tellg();
    std::vector<char> buffer(fileSize);

    shaderFile.seekg(0);
    shaderFile.read(buffer.data(), fileSize);

    if (buffer.empty())
        Debug::Log(std::format("{} is empty", filepath));

    shaderFile.close();

    return buffer;
}
} // namespace Alloy::ShaderUtils