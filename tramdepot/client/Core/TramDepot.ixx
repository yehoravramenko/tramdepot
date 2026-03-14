export module TramDepot;

export import :Debug;

import :Render;
import :EventHandler;
import :Time;

namespace TramDepot
{
export class TramDepot
{
  public:
    TramDepot(const unsigned int windowWidth, const unsigned int windowHeight);

    void MainLoop();

  private:
    EventHandler eventHandler;
    Render render;
};
} // namespace TramDepot