module;
#include "GL/gl3w.h"
export module Alloy:OpenGL.Shader;

import std;

export namespace Alloy::OpenGL
{

class Shader
{
  public:
    Shader() = default;
    void Create(const GLchar *vertexShaderSource,
                const GLchar *fragmentShaderSource);
    ~Shader();

    void Use() const;

  private:
    GLuint program = 0;
};

} // namespace Alloy::OpenGL