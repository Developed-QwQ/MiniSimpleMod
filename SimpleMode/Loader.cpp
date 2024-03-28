#include "Loader.h"
#include "Config/UserManager.h"
SlimUtils::SlimMem mem;
const SlimUtils::SlimModule* gameModule;
bool Loader::isRunning = true;
HWND hWnd;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
DWORD WINAPI ejectThread(LPVOID lpParam) {
	while (Loader::isRunning) {
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x4C)) {
			Loader::isRunning = false;
			break;
		}
		Sleep(20);
	}
	LOG_INFO("Stopping Threads...");
	GameData::terminate();
	Sleep(50);

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);
}
DWORD WINAPI start(LPVOID lpParam) {
	{
		DWORD targetProcessId = GetCurrentProcessId();
	//	auto winhwid = FindWindow(NULL,"MiniGameApp.exe");
	//	ShowWindow(winhwid, SW_MAXIMIZE);
		//system("taskkill /f /t /im MicroMiniNew.exe");
		EnumWindows(EnumWindowsProc, (LPARAM)&targetProcessId);
	}
	OPEN_COONSOLE();
	LOG_INFO("Starting up...");
	LOG_EVENT("Sock up...");
//	user->getSimpleUser();
	DWORD procId = GetCurrentProcessId();
	if (!mem.Open(procId, SlimUtils::ProcessAccess::Full)) {
		LOG_INFO("Failed to open process, error-code: %i", GetLastError());
		return 1;}
	gameModule = mem.GetModule(L"libSandboxEngine.dll");
	MH_Initialize();
	DWORD ejectThreadId;
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)ejectThread, lpParam, NULL, &ejectThreadId);
	GameData::initGameData(gameModule, &mem, lpParam);
	Hooks::Init();

	moduleMgr->initMods();
	LOG_INFO("Initialized module manager (1/1)");

	Hooks::Enable();
	return TRUE;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start, hModule, NULL, NULL);
		DisableThreadLibraryCalls(hModule);
		break;
	case DLL_PROCESS_DETACH: {
		Hooks::Restore();
		MH_Uninitialize();
		LOG_INFO("MinHook -> MH_Uninitialize");
		moduleMgr->deInitMods();
		LOG_INFO("moduleMgr -> deInitMods");
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