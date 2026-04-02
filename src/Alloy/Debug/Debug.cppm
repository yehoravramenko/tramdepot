export module Alloy:Debug;

import std;

namespace Alloy
{
enum ASCIIColor
{
    Red    = 31,
    Green  = 32,
    Yellow = 33,
};

export class Debug
{
  public:
    Debug() = delete;

    static void Init();
    static void Release();

    static void Log(const std::string_view msg, const unsigned hr = 0);
    static void Warning(const std::string_view msg, const unsigned hr = 0);
    [[noreturn]] static void Error(const std::string_view msg,
                                   const unsigned hr = 0);

  private:
    static std::string header;
    static bool isInitialized;

    static void output(const ASCIIColor col, const char *prefix,
                       const std::string_view msg, const unsigned hr,
                       std::ostream &out = std::cout);
};

} // namespace Alloy