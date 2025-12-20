module;
#include <d3d11.h>
export module DX11;

namespace DX11
{

export struct Vertex
{
    float x, y, z;

    static constexpr D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
         D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
};

} // namespace DX11