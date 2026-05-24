module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
module Alloy:Render;
import :EventHandler;
import :RendererOpenGL;
import :Debug;
import :Window;

import std;

namespace Alloy
{

Render::Render(EventHandler *const eventHandler)
    : eventHandler(eventHandler), window(eventHandler)
{
    this->renderer =
        std::make_unique<RendererOpenGL>(this->eventHandler, &this->window);
}

void Render::Update()
{
    this->window.Update();
    this->renderer->Update();
    this->renderer->Draw();
}

} // namespace Alloy