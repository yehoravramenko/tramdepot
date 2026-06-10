module;
#include "GL/gl3w.h"
#include "glm/gtc/matrix_transform.hpp"
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
    GLuint texCoordBuffer{};
    GLuint vertexArray{};

    OpenGL::BasicShader shader;

    HDC deviceContext{};
    HGLRC glContext{};

    glm::vec3 cam_position{0, 0, 3};
    glm::vec3 cam_front{0, 0, -1};
    glm::vec3 cam_target{0, 0, 0};
    glm::vec3 cam_up{0, 1, 0};

    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 mvp;
};
} // namespace Alloy