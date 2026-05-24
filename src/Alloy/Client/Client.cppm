export module Alloy:Client;
import :EventHandler;
import :Render;

import std;

export namespace Alloy
{
class Client
{
  public:
    ALLOY_EXPORT Client();
    ALLOY_EXPORT ~Client();

    ALLOY_EXPORT void MainLoop();

  private:
    EventHandler eventHandler;
    Render render;
};
} // namespace Alloy