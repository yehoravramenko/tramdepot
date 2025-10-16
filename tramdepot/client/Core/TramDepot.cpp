module TramDepot;

import :Debug;
import :Time;

namespace TramDepot
{
TramDepot::TramDepot(const unsigned int windowWidth,
                     const unsigned int windowHeight)
    : render(windowWidth, windowHeight)
{
#ifdef DEBUG
    Debug::Init();
#endif

    this->render.postEvent = [this](const Event &e) {
        this->eventHandler.PostEvent(e);
    };
}

void TramDepot::MainLoop()
{
    for (;;)
    {
        Time::Tick();

        for (std::optional<Event> e;
             e = this->eventHandler.PollEvent(), e.has_value();)
        {
            if (e.value().type == EventType::Exit)
            {
                goto mainloop_exit;
            }
        }
        this->render.Update();
    }
mainloop_exit:;
}

TramDepot::~TramDepot()
{
#ifdef DEBUG
    Debug::Release();
#endif
}

} // namespace TramDepot