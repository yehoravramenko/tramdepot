#include "EventHandler.hpp"

namespace TramDepot
{
void EventHandler::PostEvent(const Event &event)
{
    this->events.push(event);
}

std::optional<Event> EventHandler::PollEvent()
{
    if (this->events.size() == 0)
        return std::nullopt;

    Event event = std::move(this->events.front());
    this->events.pop();

    return event;
}
} // namespace TramDepot