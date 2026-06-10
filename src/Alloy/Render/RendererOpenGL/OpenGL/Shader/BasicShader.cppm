module;
#include "GL/gl3w.h"
export module Alloy:OpenGL.BasicShader;
import :OpenGL.Shader;

export namespace Alloy::OpenGL
{

class BasicShader : public Shader
{
  public:
    void Compile();
};

} // namespace Alloy::OpenGL