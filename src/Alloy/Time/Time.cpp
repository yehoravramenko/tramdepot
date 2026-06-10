module Alloy:Time;
import :Debug;
import std;

using namespace std::chrono_literals;

namespace Alloy
{
float Time::delta{};
std::chrono::steady_clock::time_point Time::lastTime{};

void Time::Tick()
{
    auto now       = std::chrono::steady_clock::now();
    Time::delta    = std::chrono::duration<float>(now - Time::lastTime).count();
    Time::lastTime = now;
}

float Time::DeltaTime()
{
    return Time::delta;
}

} // namespace Alloy