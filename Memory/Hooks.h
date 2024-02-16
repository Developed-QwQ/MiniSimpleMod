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
	static char _fastcall localPlayer(LocalPlayer* _this);
	static void _fastcall ActorList_tick(ActorList* actorList);

	std::unique_ptr<FuncHook> entity_tick;
	std::unique_ptr<FuncHook> _localPlayer;
};

extern Hooks g_Hooks;

class FuncHook {
public:
	void* funcPtr;
	void* funcReal;

	FuncHook(void* func, void* hooked) {
		funcPtr = func;

		// Check if the function pointer is valid
		if (IsBadReadPtr(funcPtr, sizeof(funcPtr))) {
			//		cout<<"Invalid function pointer!"<<endl;
			return;
		}

		MH_STATUS ret = MH_CreateHook(func, hooked, &funcReal);
		if (ret == MH_OK && (__int32)func > 10) {
			// Hook created successfully
		}
		else {
			//		cout<<"MH_CreateHook "<<ret<<endl;
		}
	};

	FuncHook(uintptr_t func, void* hooked) {
		funcPtr = reinterpret_cast<void*>(func);

		// Check if the function pointer is valid
		if (IsBadReadPtr(funcPtr, sizeof(funcPtr))) {
			//		cout<<"Invalid function pointer!"<<endl;
			return;
		}

		MH_STATUS ret = MH_CreateHook(funcPtr, hooked, &funcReal);
		if (ret == MH_OK && (__int32)funcPtr > 10) {
		}
		else {
			//			cout << "MH_CreateHook " << ret << endl;
		}
	};

	void enableHook(bool enable = true) {
		if (funcPtr != nullptr) {
			int ret = enable ? MH_EnableHook(funcPtr) : MH_DisableHook(funcPtr);
			if (ret != MH_OK) {
				//	cout<<"MH_EnableHook"<< ret<<endl;
			}
		}
		else {
			//			cout<<"enableHook() called with nullptr func!"<<endl;
		}
	}
	~FuncHook() { Restore(); }
	// Restore the hook
	void Restore() {
		if (funcPtr != nullptr) {
			MH_STATUS ret = MH_DisableHook(funcPtr);
			if (ret != MH_OK) {
				//				cout<<"MH_DisableHook"<<ret<<endl;
			}
		}
	}
	// Get the original function pointer with fastcall calling convention
	template <typename TRet, typename... TArgs>

	inline auto* GetFastcall() {
		using Fn = TRet(__fastcall*)(TArgs...);
		return reinterpret_cast<Fn>(funcReal);
	};
};
