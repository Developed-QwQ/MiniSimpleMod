#include "Loader.h"
bool Loader::isRunning = true;
HWND hWnd;
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
DWORD WINAPI ejectThread(LPVOID lpParam) {
	return false;
}
DWORD WINAPI start(LPVOID lpParam) {
	{
		DWORD targetProcessId = GetCurrentProcessId();
		system("taskkill /f /t /im MicroMiniNew.exe");
		EnumWindows(EnumWindowsProc, (LPARAM)&targetProcessId);
	}
	OPEN_COONSOLE();
	LOG_INFO("Starting up...");
	GameData::initGameData();
	MH_Initialize();
//	Hooks::Init();

	DWORD ejectThreadId;
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)ejectThread, lpParam, NULL, &ejectThreadId); 

	moduleMgr->initMods();
	LOG_INFO("Initialized module manager (1/1)");
	ImGuiMenu::Init();
//	Hooks::Enable();
	return TRUE;
}
BOOL __stdcall DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH: {
		MessageBox(0, 0, 0, 0);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start, hModule, NULL, NULL);
		DisableThreadLibraryCalls(hModule);
	} break;
	case DLL_PROCESS_DETACH: {
		Hooks::Restore();
		MH_Uninitialize();
		LOG_INFO("MinHook-> Removing");
		kiero::shutdown();
		LOG_INFO("kiero-> Removing");
		moduleMgr->deInitMods();
		break;
	}
	}
	return TRUE;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	DWORD targetProcessId = *((DWORD*)lParam);
	DWORD windowProcessId;
	GetWindowThreadProcessId(hwnd, &windowProcessId);
	if (windowProcessId == targetProcessId) {
		ShowWindow(hwnd, SW_MAXIMIZE);
		return FALSE;
	}
	return TRUE;
}