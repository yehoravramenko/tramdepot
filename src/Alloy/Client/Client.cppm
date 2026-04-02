export module Alloy:Client;
import :IRenderer;

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
};
} // namespace Alloy