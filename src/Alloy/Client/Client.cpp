module Alloy:Client;

import :RendererOpenGL;

namespace Alloy
{

Client::Client() : renderer(new RendererOpenGL)
{
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