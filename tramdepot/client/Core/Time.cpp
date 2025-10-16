module;
#include <Windows.h>
module TramDepot:Time;

import :Debug;

import std;

namespace TramDepot::Time
{
static __int64 prevCounter    = 0;
static double secondsPerCount = 0.0;
static double deltaTime       = 0.0;

void Time::Tick()
{
    if (Time::secondsPerCount == 0)
    {
        ::LARGE_INTEGER performanceFrequency;
        ::QueryPerformanceFrequency(&performanceFrequency);
        Time::secondsPerCount = 1.0 / performanceFrequency.QuadPart;
    }

    ::LARGE_INTEGER counter;

    ::QueryPerformanceCounter(&counter);
    deltaTime = (counter.QuadPart - Time::prevCounter) * Time::secondsPerCount;
    Debug::Log(std::format("deltaTime: {}s", Time::deltaTime));

    if (deltaTime < 0.0)
        deltaTime = 0.0;

    Time::prevCounter = counter.QuadPart;
}

double Time::DeltaTime()
{
    return Time::deltaTime;
}
} // namespace TramDepot::Time