module;
#include "GL/gl3w.h"
// #include <cassert>
module Alloy:OpenGL.BasicShader;

const char *vs_source = R"(
    #version 460 core
    layout(location = 0) in vec3 inPos;
    layout(location = 1) in vec2 inTex;

    uniform mat4 MVP;
    out vec2 TexCoord;
    
    void main()
    {
        gl_Position = MVP * vec4(inPos, 1.0);
        TexCoord = inTex;
    })";

const char *fs_source = R"(
    #version 460 core
    in vec2 TexCoord;

    uniform sampler2D tex1;
    out vec4 FragColor;
    
    void main()
    {
        FragColor = texture(tex1, TexCoord);
    })";

namespace Alloy::OpenGL
{
void BasicShader::Compile()
{
    Shader::Compile(vs_source, fs_source);
}
} // namespace Alloy::OpenGL