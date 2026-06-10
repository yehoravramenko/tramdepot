module;
#include "GL/gl3w.h"
#include "glm/gtc/matrix_transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
module Alloy:RendererOpenGL;

import :Debug;
import :Input;
import :Time;
import :OpenGL;

import std;

#pragma comment(lib, "opengl32.lib")

constexpr float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                              0.0f,  0.0f,  0.5f, 0.0f};

constexpr float texCoords[] = {
    0.0f, 0.0f, // lower-left corner
    1.0f, 0.0f, // lower-right corner
    0.5f, 1.0f  // top-center corner
};

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

    this->shader.Compile();

    glGenVertexArrays(1, &this->vertexArray);
    glBindVertexArray(this->vertexArray);
    {
        glGenBuffers(1, &this->vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &this->texCoordBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->texCoordBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), &texCoords,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glEnableVertexAttribArray(1);
    }
    glBindVertexArray(0);

    this->shader.Use();

    unsigned tex1{};
    glGenTextures(1, &tex1);
    glBindTexture(GL_TEXTURE_2D, tex1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w{}, h{}, channels{};
    unsigned char *data =
        stbi_load("D:\\aura\\tramdepot\\wall.jpg", &w, &h, &channels, 0);
    assert(data);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    auto samplerID = this->shader.GetUniformLocation("tex1");
    assert(samplerID);
    this->shader.SetUniformTexture(*samplerID, 0);

    this->projection = glm::perspective(glm::radians(45.0f),
                                        (float)this->window->GetWidth() /
                                            this->window->GetHeight(),
                                        0.1f, 100.0f);

    this->model = glm::mat4(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void RendererOpenGL::Draw()
{
    glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(this->vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SwapBuffers(this->deviceContext);
}

void RendererOpenGL::Update()
{
    const float cam_speed = 5.0f * Time::DeltaTime();
    if (Input::GetKey('W'))
        this->cam_position += cam_speed * this->cam_front;

    if (Input::GetKey('S'))
        this->cam_position -= cam_speed * this->cam_front;

    if (Input::GetKey('A'))
        this->cam_position -=
            cam_speed *
            glm::normalize(glm::cross(this->cam_front, this->cam_up));

    if (Input::GetKey('D'))
        this->cam_position +=
            cam_speed *
            glm::normalize(glm::cross(this->cam_front, this->cam_up));

    this->view = glm::lookAt(
        this->cam_position, this->cam_position + this->cam_front, this->cam_up);
    this->mvp  = this->projection * this->view * this->model;
    auto mvpID = this->shader.GetUniformLocation("MVP");
    assert(mvpID);
    this->shader.SetUniformMatrix4(*mvpID, &this->mvp[0][0]);

    // Debug::Log(std::format("{}, {}, {}", this->cam_position.x,
    //                        this->cam_position.y, this->cam_position.z));
}

RendererOpenGL::~RendererOpenGL()
{
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(this->glContext);
    ReleaseDC(this->window->GetHandle(), this->deviceContext);
}
} // namespace Alloy