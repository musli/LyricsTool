// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <stdio.h>
//#include "stdafx.h"
#pragma warning(disable: 4996)
#define MemoryHookLength 5

unsigned _stdcall ExitDetectionThread(VOID* pArg)
{
	while (TRUE)
	{
		if (-32768 == GetAsyncKeyState(VK_MENU) && -32767 == GetAsyncKeyState(VK_OEM_3))
		{
			printf("即将关闭程序...\n");
			//关闭控制台
			PostMessage((HWND)pArg, WM_CLOSE, 0, 0);
			DWORD PID = 0;
			GetWindowThreadProcessId((HWND)pArg, &PID);
			HANDLE ProcessHandle = OpenProcess(THREAD_ALL_ACCESS, FALSE, PID);
			TerminateProcess(ProcessHandle, 0);
			CloseHandle(ProcessHandle);
		}
		Sleep(150);
	}
}

VOID ProntColor(CHAR colorIndex)
{

	//0:=:黑色1=蓝色2:=绿色 3:=湖蓝色4:二红色5=紫色6=黄色:7:=白色8:=灰色”
	//9 =淡蓝色10=淡绿色11:= 淡浅绿色12:=淡红色13-=淡紫色14-=淡黄色15 =亮白色
	//因为如果超过15后面的改变的是文本背景色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorIndex);
}

VOID PrintUI(CONST CHAR* UIName, CONST CHAR* colorCommand, SHORT x, SHORT y, WORD UIWidth, WORD UIhight, BOOL inMode)
{
	AllocConsole();
	//使用cin,scanf
	freopen("conin$", "r+t", stdin);
	//使用cout,printf
	freopen("conout$", "w+t", stdout);
	//设置UIName
	SetConsoleTitleA(UIName);
	//设置控制台颜色

	system(colorCommand);
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, ExitDetectionThread, GetConsoleWindow(), 0, 0));
	HWND PrintUI = GetConsoleWindow();
	if (inMode)
	{
		char winWidth[5], winHeight[5];
		itoa(UIWidth, winWidth, 10);
		itoa(UIhight, winHeight, 10);

		char commandLine[50] = "mode con dols=";
		strcat(commandLine, winWidth);
		strcat(commandLine, " lines=");
		strcat(commandLine, winHeight);
		system(commandLine);
	}
	else
	{
		SetWindowPos(PrintUI, 0, 0, 0, UIWidth, UIhight, SWP_NOMOVE);
	}
	//MoveWindows一次性设置框架会错乱原因不明
	//支持wcout输出中文
	std::wcout.imbue(std::locale("CHS"));
}

//恢复的数据
BYTE RecoveryMemory[MemoryHookLength];
//恢复的数据
BYTE RecoveryMyTextOutW[MemoryHookLength];

/// <summary>
/// 内存钩子
/// </summary>
/// <param name="APIAdress"></param>
/// <param name="jmpAddress"></param>
/// <returns></returns>
BYTE* MemonryHook(LPVOID APIAdress, /*我们要勾住的API地址*/ LPVOID jmpAddress/*我们要跳转的位置*/)
{
	DWORD 之前保护属性;
	if (VirtualProtectEx(GetCurrentProcess(), APIAdress, MemoryHookLength, PAGE_EXECUTE_READWRITE, &之前保护属性))
	{
		if (!ReadProcessMemory(GetCurrentProcess(), APIAdress, RecoveryMemory, MemoryHookLength, NULL))
		{
			printf("读取内存失败\n", GetLastError());
		}
		CHAR Shellcode[MemoryHookLength];
		ZeroMemory(Shellcode, MemoryHookLength);
		//jmp
		Shellcode[0] = 0xE9;
		*(DWORD*)(Shellcode + 1) = (DWORD)jmpAddress - (DWORD)APIAdress - 5;/*这个公式你们下了个再去理解*/
		if (!WriteProcessMemory(GetCurrentProcess(), APIAdress, Shellcode, MemoryHookLength, NULL))
		{
			printf("写入内存失败\n", GetLastError());
		}

	}
	VirtualProtectEx(GetCurrentProcess(), APIAdress, MemoryHookLength, 之前保护属性, &之前保护属性);
	return RecoveryMemory;
}

/// <summary>
/// 还原数据
/// </summary>
/// <param name="recoveryAddress">我们要勾住的API地址</param>
/// <param name="recoveryData">我们要跳转的位置</param>
/// <returns></returns>
CHAR RecoveryCode(LPVOID recoveryAddress, BYTE* recoveryData)
{
	printf("RecoveryCode\n");
	if (!WriteProcessMemory(GetCurrentProcess(), recoveryAddress, recoveryData, MemoryHookLength, NULL))
	{
		printf("写入内存失败\n", GetLastError());
		return -1;
	}
	return 0;
}

CHAR* 内存 = 0;
DWORD MemoryLength = 0;
CHAR* WCHARTOChar(const wchar_t* Buffer)
{
	if (内存)
	{
		free(内存);
		内存 = 0;
	}
	//unicode编码转换成GBK编码
	//得到单字节字符串的内存大小
	MemoryLength = WideCharToMultiByte(CP_ACP, 0, Buffer, -1, NULL, 0, 0, 0);
	内存 = (CHAR*)malloc(MemoryLength);
	memset(内存, 0, MemoryLength);
	WideCharToMultiByte(CP_ACP, 0, Buffer, -1, 内存, MemoryLength, 0, 0);
	return 内存;
}

BOOL WINAPI MyTextOutW(_In_ HDC hdc, _In_ int x, _In_ int y, _In_reads_(c) LPCWSTR lpString, _In_ int c)
{
	//我们跳转这里做事情
	bool Bool;
	if (c)
	{
		printf(": \t%s\n",WCHARTOChar(lpString));
		//wprintf(lpString);
		//我们要保存数据
	}
	RecoveryCode(TextOutW, RecoveryMyTextOutW);
	Bool = TextOutW(hdc, x, y, lpString, c);
	MemonryHook(TextOutW, MyTextOutW);
	return Bool;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		//进程加载的时候
	case DLL_PROCESS_ATTACH:
	{
		//开始执行注入
		PrintUI("这是第三程序", "color 0A", (2560 - 500) / 2 - 50, (1440 - 500) / 2, 1063, 816, 0);
		printf("第三步\n");
		memcpy(RecoveryMyTextOutW, MemonryHook(TextOutW, MyTextOutW), MemoryHookLength);
		break;
	}
	//进程卸载的时候
	case DLL_THREAD_DETACH:
	{
		break;
	}
	}
	return TRUE;
}

