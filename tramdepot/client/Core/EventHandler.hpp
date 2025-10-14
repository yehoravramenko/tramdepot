#pragma once

#include "Event.hpp"

#include <queue>
#include <optional>

namespace TramDepot
{
class EventHandler
{
  public:
    void PostEvent(const Event &event);
    std::optional<Event> PollEvent();

  private:
    std::queue<Event> events;
};
} // namespace TramDepot