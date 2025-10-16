export module TramDepot;

import :Render;
import :EventHandler;
import :Time;

namespace TramDepot
{
export class TramDepot
{
  public:
    TramDepot(const unsigned int windowWidth, const unsigned int windowHeight);
    ~TramDepot();

    void MainLoop();

  private:
    EventHandler eventHandler;
    Render render;
};
} // namespace TramDepot