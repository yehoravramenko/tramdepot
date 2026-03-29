// #pragma once
module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
export module Alloy:Client;

export namespace Alloy
{
class ALLOY_EXPORT Client
{
  public:
    Client(const HINSTANCE hInstance);
};
} // namespace Alloy