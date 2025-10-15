export module TramDepot:Event;

export namespace TramDepot
{
enum EventType
{
    Null = 0,
    Exit = 1,
};

struct Event
{
    EventType type;
};
} // namespace TramDepot