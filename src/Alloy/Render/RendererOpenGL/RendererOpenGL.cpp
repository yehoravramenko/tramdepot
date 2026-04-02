module;

#include "GL/gl3w.h"

#define RGFW_OPENGL
#define RGFW_PRINT_ERRORS
#ifdef DEBUG
#define RGFW_DEBUG
#endif // DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

module Alloy:RendererOpenGL;
import :Debug;

import std;

namespace Alloy
{

RendererOpenGL::RendererOpenGL(EventHandler *const eventHandler)
{
    this->eventHandler = eventHandler;

    RGFW_glHints *hints = RGFW_getGlobalHints_OpenGL();
    hints->major        = 4;
    hints->minor        = 6;
    RGFW_setGlobalHints_OpenGL(hints);

    this->window = RGFW_createWindow(
        "Alloy Engine", 0, 0, 800, 600,
        RGFW_windowCenter | RGFW_windowScaleToMonitor | RGFW_windowOpenGL);

    if (this->window == nullptr)
        Debug::Error("Failed to create window.");

    RGFW_window_makeCurrentContext_OpenGL(this->window);

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
}

void RendererOpenGL::Draw()
{
}

void RendererOpenGL::Update()
{
    RGFW_event event{};

    while (RGFW_window_checkEvent(this->window, &event))
    {
        switch (event.type)
        {
        case RGFW_windowClose:
            this->eventHandler->PushEvent(Event::WindowClosed);
            break;
        default:
            break;
        }
    }

    RGFW_window_swapBuffers_OpenGL(this->window);
}

RendererOpenGL::~RendererOpenGL()
{
    RGFW_window_close(this->window);
}

} // namespace Alloy