#pragma once
#include "Render/Render.hpp"
#include "Core/EventHandler.hpp"

namespace TramDepot
{
class Game
{
  public:
    Game(const unsigned int windowWidth, const unsigned int windowHeight);
    ~Game();

    void MainLoop();

  private:
    EventHandler eventHandler;
    Render render;
};
} // namespace TramDepot