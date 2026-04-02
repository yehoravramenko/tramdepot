module Alloy:Client;
import :Debug;
import :RendererOpenGL;

import std;

namespace Alloy
{

Client::Client()
{
    Debug::Init();
    this->renderer = std::make_unique<RendererOpenGL>(&this->eventHandler);
}

void Client::MainLoop()
{
    for (;;)
    {
        Event currentEvent = Event::None;
        while ((currentEvent = this->eventHandler.PopEvent()),
               currentEvent != Event::None)
        {
            if (currentEvent == Event::WindowClosed)
                return;
        }

        this->renderer->Update();
        this->renderer->Draw();
    }
}

} // namespace Alloy