#include "Client.hpp"
#include "Debug/Debug.hpp"
#include "ClientUtils.hpp"

#include <SDL3/SDL.h>

namespace Alloy
{
Client::Client() : m_Window(1024, 768)
{
    SetWorkingDirectory(GetExecutableDirectory());

    m_Renderer = std::make_unique<Renderer>(m_Window.GetWindowHandle(),
                                            m_Window.GetWindowSize());
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

        // TODO: set up fixed fps delta time
        OnUpdate(0.016f);

        m_Renderer->BeginFrame();
        OnRender();
        m_Renderer->EndFrame();
    }

    OnShutdown();
}
} // namespace Alloy