#pragma once
#include "Core/ComPtr.hpp"

#include <d3d11.h>

namespace Alloy
{
template <typename T> class ConstantBuffer
{
  private:
    ComPtr<ID3D11Buffer> m_buffer;

  public:
    ConstantBuffer(const ID3D11Device *d3dDevice)
    {
        const D3D11_BUFFER_DESC cbDesc = {
            .ByteWidth      = sizeof(T),
            .Usage          = D3D11_USAGE_DYNAMIC,
            .BindFlags      = D3D11_BIND_CONSTANT_BUFFER,
            .CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
        };

        auto hr =
            d3dDevice->CreateBuffer(&cbDesc, nullptr, m_buffer.GetAddressOf());
    }
};
} // namespace Alloy