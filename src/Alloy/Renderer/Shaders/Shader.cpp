#include "Shader.hpp"
#include "ShaderUtils.hpp"
#include "Debug/Debug.hpp"

namespace Alloy
{
Shader::Shader(ID3D11Device *d3dDevice, std::string_view VSBytecodeFilename,
               std::string_view PSBytecodeFilename)
{
    constexpr D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
         D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
         D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    auto const vsBytecode = ShaderUtils::ReadCSOFile(VSBytecodeFilename);
    auto const psBytecode = ShaderUtils::ReadCSOFile(PSBytecodeFilename);

    /* Vertex Shader */
    auto hr =
        d3dDevice->CreateVertexShader(vsBytecode.data(), vsBytecode.size(),
                                      nullptr, m_vertexShader.GetAddressOf());
    Debug::hr_assert(hr, "Failed to compile vertex shader");

    /* Pixel Shader */
    hr = d3dDevice->CreatePixelShader(psBytecode.data(), psBytecode.size(),
                                      nullptr, m_pixelShader.GetAddressOf());
    Debug::hr_assert(hr, "Failed to compile pixel shader");

    /* Input Layout */
    hr = d3dDevice->CreateInputLayout(layoutDesc, ARRAYSIZE(layoutDesc),
                                      vsBytecode.data(), vsBytecode.size(),
                                      m_inputLayout.GetAddressOf());
    Debug::hr_assert(hr, "Failed to create input layout");
}

void Shader::Bind(ID3D11DeviceContext *immediateContext) const
{
    immediateContext->IASetInputLayout(m_inputLayout.Get());
    immediateContext->VSSetShader(m_vertexShader.Get(), nullptr, 0);
    immediateContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}
} // namespace Alloy