module;
#define RGFW_OPENGL
#define RGFW_PRINT_ERRORS
#ifdef DEBUG
#define RGFW_DEBUG
#endif // DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"
module Alloy:RendererOpenGL;

import :Debug;

namespace Alloy
{

RendererOpenGL::RendererOpenGL()
{
    RGFW_glHints *hints = RGFW_getGlobalHints_OpenGL();
    hints->major        = 4;
    hints->minor        = 6;
    RGFW_setGlobalHints_OpenGL(hints);

    this->window = RGFW_createWindow(
        "Alloy Engine", 0, 0, 800, 600,
        RGFW_windowCenter | RGFW_windowScaleToMonitor | RGFW_windowOpenGL);

    if (window == nullptr)
        Debug::Error("Failed to create window.");
}

void RendererOpenGL::Draw()
{
}

void RendererOpenGL::Update()
{
}

RendererOpenGL::~RendererOpenGL()
{
}

} // namespace Alloy