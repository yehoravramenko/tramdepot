export module Alloy:EventHandler;

import std;

export namespace Alloy
{
enum class Event
{
    None = 0,
    WindowClosed,
};

class EventHandler
{
  public:
    void PushEvent(const Event &event);
    const std::optional<Event> PopEvent();

  private:
    std::queue<Event> events;
};

} // namespace Alloy