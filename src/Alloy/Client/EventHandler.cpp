module Alloy:EventHandler;

namespace Alloy
{

void EventHandler::PushEvent(const Event &event)
{
    this->events.push(event);
}

const std::optional<Event> EventHandler::PopEvent()
{
    if (this->events.size() == 0)
        return std::nullopt;

    Event &&currentEvent = std::move(this->events.front());
    this->events.pop();

    return currentEvent;
}

} // namespace Alloy