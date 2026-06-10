module;
#include "GL/gl3w.h"
export module Alloy:OpenGL.Shader;

import std;

export namespace Alloy::OpenGL
{

class Shader
{
  public:
    virtual ~Shader();

    void Use() const;
    std::optional<GLuint> GetUniformLocation(std::string_view name) const;
    void SetUniformMatrix4(GLuint id, const GLfloat *value);
    void SetUniformTexture(GLuint id, GLuint texID);

  protected:
    void Compile(const GLchar *vertexShaderSource,
                 const GLchar *fragmentShaderSource);

    GLuint program = 0;
};

} // namespace Alloy::OpenGL