#pragma once

#ifndef PERFORMANCE_TEST
//#define PERFORMANCE_TEST
#endif
#include "../includes/kiero/minhook/include/MinHook.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <intrin.h>

#include <thread>
#include <unordered_map>

#include <iostream>
#include "../SimpleMode/Module/ModManager.h"
#include "../SDK/ActorList.h"
#include "../Memory/GameData.h"
using namespace std;
class VMTHook;
class FuncHook;

struct CoolSkinData {
};

class Hooks {
private:
	bool shouldRender = true;
public:

	char currentScreenName[100];
	std::vector<std::shared_ptr<FuncHook>> lambdaHooks;
	struct NPCListPointerHolder {
		//	ActorBotNpc* ent;
		ActorBase* ent;
		int addedTick;
	};
	std::vector<NPCListPointerHolder> actorList;
	__int32 RMBManager = 0;
	bool shouldLocalPlayerBeImmobile = false;

	static void Init();
	static void Restore();
	static void Enable();

private:
	static char* _fastcall TextMessage(__int32);
	static void _fastcall localPlayers(LocalPlayer* _this);
	static Player __fastcall Actor_PlayerTick(Player* _this);
	static void _fastcall ActorList_tick(ActorList* actorList);
	static int _fastcall setBlockAll(void* _this,int a2,int a3,Vec3i pos);

	std::unique_ptr<FuncHook> text;
	std::unique_ptr<FuncHook> setblock;
	std::unique_ptr<FuncHook> entity_tick;
	std::unique_ptr<FuncHook> localPlayeres;
	std::unique_ptr<FuncHook> Actor_playerTick;
public:
	std::unique_ptr<FuncHook> oPresent;
	std::unique_ptr<FuncHook> oDrawIndexed;

	std::unique_ptr<FuncHook> oWGLSwapBuffers;
	std::unique_ptr<FuncHook> oGLBegin;
	std::unique_ptr<FuncHook> oGLColor4f;
	std::unique_ptr<FuncHook> oGLClear;
};

extern Hooks g_Hooks;

class FuncHook {
public:
	void* funcPtr;
	void* funcReal;
	FuncHook(void* func) {}
	FuncHook(void* func, void* hooked) {
		funcPtr = func;
		if (IsBadReadPtr(funcPtr, sizeof(funcPtr))) {
			return;
		}

		MH_STATUS ret = MH_CreateHook(func, hooked, &funcReal);
		if (ret == MH_OK && (__int32)func > 10) {
		}
	};
	FuncHook(uintptr_t func, void* hooked) {
		funcPtr = reinterpret_cast<void*>(func);
		if (IsBadReadPtr(funcPtr, sizeof(funcPtr))) {
			return;}
		MH_STATUS ret = MH_CreateHook(funcPtr, hooked, &funcReal);
		if (ret == MH_OK && (__int32)funcPtr > 10) {}
	};

	void enableHook(bool enable = true) {
		if (funcPtr != nullptr) {
			int ret = enable ? MH_EnableHook(funcPtr) : MH_DisableHook(funcPtr);
			if (ret != MH_OK) {}}
	}
	~FuncHook() { Restore(); }
	void Restore() {
		if (funcPtr != nullptr) {
			MH_STATUS ret = MH_DisableHook(funcPtr);
			if (ret != MH_OK) {}
		}
	}
	template <typename TRet, typename... TArgs>

	inline auto* GetFastcall() {
		using Fn = TRet(__fastcall*)(TArgs...);
		return reinterpret_cast<Fn>(funcReal);
	};

	template <typename TRet, typename... TArgs>

	inline auto* Getstdcall() {
		using Fn = TRet(__stdcall*)(TArgs...);
		return reinterpret_cast<Fn>(funcReal);
	};
};
