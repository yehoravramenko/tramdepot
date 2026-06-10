export module Alloy:Time;
import std;

namespace Alloy
{
class Time
{
    friend class Client;

  public:
    static float DeltaTime();

  private:
    static std::chrono::steady_clock::time_point lastTime;

    static void Tick();

    static float delta;
};
} // namespace Alloy