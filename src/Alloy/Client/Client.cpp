module Alloy:Client;
import :Debug;
import :RendererOpenGL;
import :Time;

import std;

namespace Alloy
{

Client::Client() : render(&eventHandler)
{
}

Client::~Client()
{
    Debug::Release();
}

void Client::MainLoop()
{
    for (;;)
    {
        Time::Tick();
        for (std::optional<Event> currentEvent;
             currentEvent = this->eventHandler.PopEvent(),
             currentEvent.has_value();)
        {
            if (currentEvent->Type == EventType::WindowClosed)
                return;
        }

        this->render.Update();
    }
}

} // namespace Alloy