#pragma once
#include "Core/ComPtr.hpp"

#include <d3d11.h>

#include <string_view>

namespace Alloy
{
class Shader
{
  public:
    Shader(ID3D11Device *d3dDevice, std::string_view VSBytecodeFilename,
           std::string_view PSBytecodeFilename);

    void Bind(ID3D11DeviceContext *immediateContext) const;

  private:
    ComPtr<ID3D11VertexShader> m_vertexShader;
    ComPtr<ID3D11PixelShader> m_pixelShader;
    ComPtr<ID3D11InputLayout> m_inputLayout;
};
} // namespace Alloy