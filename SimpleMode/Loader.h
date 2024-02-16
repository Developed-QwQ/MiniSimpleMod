#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include "../Utils/logger.h"
#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>

#include "../includes/kiero/minhook/include/MinHook.h"
#include "Module/ModManager.h"
#include "../Memory/Hooks.h"
#include "Menu/ImGuiMenu.h"
#include "../Utils/HMath.h"
#include "Menu/ModuleList.h"
#include "../Memory/GameData.h"
ModuleList* ListMod;
using namespace std;
class Loader
{
public:
	static bool isRunning;
};
