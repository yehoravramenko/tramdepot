#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <d3d11.h>
#include <dxgi.h>

namespace TramDepot
{
class Game
{
  public:
    Game();
    ~Game();

    void createWindow();
    void MainLoop();

    HWND getWindowHandle();

    ID3D11Device *d3dDevice  = nullptr;
    ID3D11DeviceContext *ctx = nullptr;

  private:
    HWND windowHandle = nullptr;
    MSG msg           = {};

    IDXGISwapChain *swapChain = nullptr;
    UINT msaaQuality          = 0;

    void gameUpdate();
    void gameStart();
};
} // namespace TramDepot