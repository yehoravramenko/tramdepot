#include <Alloy.hpp>

class TramDepot : public Alloy::Client
{
  public:
    void OnInit() override {}
    void OnUpdate(float deltaTime) override {}
    void OnRender() override {}
    void OnShutdown() override {}
};

extern Alloy::Client *AllocClient()
{
    return new TramDepot;
}