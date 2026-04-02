export module Alloy:RendererOpenGL;
import :IRenderer;
import :EventHandler;

export namespace Alloy
{
class RendererOpenGL : public IRenderer
{
  public:
    RendererOpenGL(EventHandler *const eventHandler);

    virtual void Draw() override;
    virtual void Update() override;

    ~RendererOpenGL();
};
} // namespace Alloy