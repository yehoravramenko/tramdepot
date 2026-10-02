#include "ShaderUtils.hpp"
#include <fstream>
#include <Debug/Debug.hpp>

namespace Alloy
{
std::vector<char> ReadCSOFile(const std::string &filepath)
{
    std::ifstream shaderFile(filepath, std::ios::binary | std::ios::ate);
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
} // namespace Alloy