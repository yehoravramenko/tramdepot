module;
#include "GL/gl3w.h"
export module Alloy:RendererOpenGL;
import :IRenderer;
import :EventHandler;
import :Window;
import :OpenGL;

import std;

export namespace Alloy
{
class RendererOpenGL : public IRenderer
{
  public:
    RendererOpenGL() = delete;
    RendererOpenGL(EventHandler *const eventHandler, Window *const window);

    virtual void Update() override;
    virtual void Draw() override;

    virtual ~RendererOpenGL() override;

  private:
    GLuint vertexBuffer{};
    GLuint vertexArray{};

    OpenGL::Shader shader;

    HDC deviceContext{};
    HGLRC glContext{};
};
} // namespace Alloy