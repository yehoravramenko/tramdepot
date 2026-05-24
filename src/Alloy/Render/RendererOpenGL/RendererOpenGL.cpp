module;
#include "GL/gl3w.h"
module Alloy:RendererOpenGL;

import :Debug;
import :OpenGL;

import std;

#pragma comment(lib, "opengl32.lib")

constexpr float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                              0.0f,  0.0f,  0.5f, 0.0f};

namespace Alloy
{

RendererOpenGL::RendererOpenGL(EventHandler *const eventHandler,
                               Window *const window)

{
    this->eventHandler = eventHandler;
    this->window       = window;

    this->deviceContext = GetDC(this->window->GetHandle());
    this->glContext     = wglCreateContext(this->deviceContext);
    wglMakeCurrent(this->deviceContext, this->glContext);

    if (gl3wInit() != GL3W_OK)
        Debug::Error("Failed to initialize OpenGL.");

    if (!gl3wIsSupported(4, 6))
        Debug::Error(
            "Failed to initialize OpenGL (OpenGL version is not supported).");

    Debug::Log(
        std::format("OpenGL {}, GLSL {}",
                    reinterpret_cast<const char *>(glGetString(GL_VERSION)),
                    reinterpret_cast<const char *>(
                        glGetString(GL_SHADING_LANGUAGE_VERSION))));

    const char *vs_source = R"(
    #version 460 core
    layout(location = 0) in vec3 inPos;
    
    void main()
    {
        gl_Position = vec4(inPos, 1.0);
    })";

    const char *fs_source = R"(
    #version 460 core
    out vec4 FragColor;
    
    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    })";

    this->shader.Create(vs_source, fs_source);

    glGenVertexArrays(1, &this->vertexArray);
    glBindVertexArray(this->vertexArray);
    {
        glGenBuffers(1, &this->vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
    }
    glBindVertexArray(0);

    this->shader.Use();
}

void RendererOpenGL::Draw()
{
    glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(this->vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SwapBuffers(this->deviceContext);
}

void RendererOpenGL::Update()
{
}

RendererOpenGL::~RendererOpenGL()
{
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(this->glContext);
    ReleaseDC(this->window->GetHandle(), this->deviceContext);
}
} // namespace Alloy