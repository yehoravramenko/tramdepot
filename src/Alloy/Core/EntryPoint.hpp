#pragma once
#include "Client/Client.hpp"

extern Alloy::Client *AllocClient();

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static Alloy::Client *g_CL = nullptr;

int main(int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        return -1;
    }

    g_CL = AllocClient();

    g_CL->MainLoop();

    delete g_CL;
    SDL_Quit();

    return 0;
}