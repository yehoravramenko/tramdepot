export module Alloy:EventHandler;

import std;

export namespace Alloy
{
enum class EventType
{
    None = 0,
    WindowClosed,
    KeyPressed,
};

struct Event
{
    EventType Type;
    // std::variant<std::monostate, wchar_t> Data;
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