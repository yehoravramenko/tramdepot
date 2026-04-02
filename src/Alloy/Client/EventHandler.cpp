module Alloy:EventHandler;

namespace Alloy
{

void EventHandler::PushEvent(const Event &event)
{
    this->events.push(event);
}

const Event EventHandler::PopEvent()
{
    if (this->events.size() == 0)
        return Event::None;

    Event &&currentEvent = std::move(this->events.front());
    this->events.pop();

    return currentEvent;
}

} // namespace Alloy