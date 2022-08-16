// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#pragma warning(disable: 4996)

HINSTANCE 实例句柄 = 0;
HHOOK HHook = 0;
LRESULT CALLBACK CALLBACK_WH_GETMESSAGE(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

extern "C" _declspec(dllexport)HHOOK StartHook(char 钩子类型, DWORD 线程ID)
{

	switch (钩子类型)
	{

	case 1:
		HHook = SetWindowsHookEx(WH_GETMESSAGE, CALLBACK_WH_GETMESSAGE, 实例句柄, 线程ID);
		break;
	default:
		break;
	}
	return HHook;
}
extern "C" _declspec(dllexport) bool UnHook(HHOOK HHook) 
{
return UnhookWindowsHookEx(HHook);
}

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		//被进程加载的时候
	case DLL_PROCESS_ATTACH:
	{

		printf("第二步\n");
		//现在到了微信的程序凌空
		实例句柄 = hModule;
		//当微信响应GETMESSAGE的时候，我们就执行这里了
		//加载狗子功能的dll

		LoadLibrary("C:\\Users\\musli\\OneDrive - 4p2c2j\\Works\\LyricsTool\\src\\MyDll\\Debug\\MyDll.dll");
		break;
	}
		//进程有新线程的时候
	case DLL_THREAD_ATTACH:
		//进程有一个线程被关闭的时候
	case DLL_THREAD_DETACH:
		//被进程卸载的时候
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

