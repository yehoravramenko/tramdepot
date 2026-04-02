export module Alloy:Client;
import :IRenderer;
import :EventHandler;

import std;

export namespace Alloy
{
class Client
{
  public:
    ALLOY_EXPORT Client();

    ALLOY_EXPORT void MainLoop();

  private:
    std::unique_ptr<IRenderer> renderer;
    EventHandler eventHandler;
};
} // namespace Alloy