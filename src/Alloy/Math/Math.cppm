export module Alloy:Math;

export namespace Alloy::Math
{

template <class T> inline void Clamp(T &value, T min, T max)
{
    if (value < min)
        value = min;
    else if (value > max)
        value = max;
}

} // namespace Alloy::Math