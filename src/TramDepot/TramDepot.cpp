#include <Alloy.hpp>

class TramDepot : public Alloy::Client
{
  public:
    void OnInit() override { Alloy::Debug::Log("Hello Alloy!"); }

    void OnUpdate(float deltaTime) override {}
    void OnRender() override {}
    void OnShutdown() override {}
};

Alloy::Client *AllocClient()
{
    return new TramDepot;
}