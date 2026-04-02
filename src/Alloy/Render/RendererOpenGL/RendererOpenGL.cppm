export module Alloy:RendererOpenGL;

import :IRenderer;

export namespace Alloy
{
class RendererOpenGL : public IRenderer
{
  public:
    RendererOpenGL();

    virtual void Draw() override;
    virtual void Update() override;

    ~RendererOpenGL();
};
} // namespace Alloy