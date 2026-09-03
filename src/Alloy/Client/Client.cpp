#include "Client.hpp"
#include <SDL3/SDL.h>

namespace Alloy
{
Client::Client() : m_Window(1024, 768)
{
}

void Client::MainLoop()
{
    bool isRunning = true;
    SDL_Event event{};

    OnInit();

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                isRunning = false;

            OnEvent(&event);
        }

        OnUpdate(0.016f);
        OnRender();
    }

    OnShutdown();
}
} // namespace Alloy