module;
#include "GL/gl3w.h"
#include <cassert>
module Alloy:OpenGL.Shader;

import :Debug;

namespace Alloy::OpenGL
{

void Shader::Create(const GLchar *vertexShaderSource,
                    const GLchar *fragmentShaderSource)
{
    assert(this->program == 0 && "Shader::Create called twice.");

    GLuint vertexShader = 0, fragmentShader = 0;
    int result = 0;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
        Debug::Error("Failed to compile vertex shader");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
        Debug::Error("Failed to compile fragment shader");

    this->program = glCreateProgram();
    glAttachShader(this->program, vertexShader);
    glAttachShader(this->program, fragmentShader);
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
        Debug::Error("Failed to link shader program");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(this->program);
}

void Shader::Use() const
{
    assert(this->program != 0 &&
           "Using program with object id 0 (Uninitialized)");
    glUseProgram(this->program);
}

} // namespace Alloy::OpenGL