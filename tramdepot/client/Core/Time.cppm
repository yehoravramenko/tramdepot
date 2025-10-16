module;
#include <Windows.h>
export module TramDepot:Time;

namespace TramDepot::Time
{

static __int64 prevCounter    = 0;
static double secondsPerCount = 0.0;
static double deltaTime       = 0.0;

export double DeltaTime();
export __int64 tick();

// class Time
//{
//     friend class Render;
//
//   public:
//     static double GetDeltaTime() { return Time::deltaTime; }
//
//   private:
//     static __int64 prevCounter;
//     static double secondsPerCount;
//     static double deltaTime;
//
//     static inline __int64 tick()
//     {
//         ::LARGE_INTEGER counter;
//
//         if (secondsPerCount == 0)
//         {
//             ::LARGE_INTEGER frequency;
//             ::QueryPerformanceFrequency(&frequency);
//             Time::secondsPerCount = 1. / frequency.QuadPart;
//         }
//
//         QueryPerformanceCounter(&counter);
//         Time::deltaTime =
//             (counter.QuadPart - Time::prevCounter) * Time::secondsPerCount;
//         if (Time::deltaTime < )
//     }
// };
} // namespace TramDepot::Time