#include "Alloy.hpp"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void alloy_test()
{
    MessageBox(nullptr, L"Tram Depot is powered by AlloyEngine!", L"Tram Depot",
               MB_OK);
}