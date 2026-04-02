module Alloy:Client;

import std;
import :RendererOpenGL;
import :Debug;

namespace Alloy
{

Client::Client()
{
    Debug::Init();
    this->renderer = std::make_unique<RendererOpenGL>();
}

void Client::MainLoop()
{
    for (;;)
    {
        this->renderer->Update();
        this->renderer->Draw();
    }
}

} // namespace Alloy