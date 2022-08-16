// Project.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include <iostream>
#include "pch.h"
#pragma warning(disable: 4996)

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

VOID PrintUI(CONST CHAR* ExeName, CONST CHAR* UIName, CONST CHAR* colorCommand, SHORT x, SHORT y, WORD UIWidth, WORD UIhight, BOOL inMode)
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

	CHAR OldPathName[1024], NewPathName[1024];
	GetModuleFileName(NULL, OldPathName, 1024);
	strcpy(NewPathName, OldPathName);
	for (int i = strlen(NewPathName); i > 0; i--)
	{
		if (NewPathName[i - 1] == '\\')
		{
			NewPathName[i] = '\0';/*删除最后斜杠后的字符*/
			strcat(NewPathName, ExeName);/*合井路径*/
			break;
		}
	}
	/*删除名称相同的exe*/
	CHAR 命令符[MAXBYTE * 2] = { '\O' };
	strcat(命令符, "del/f/q \"");
	strcat(命令符, NewPathName);
	strcat(命令符, "\">nul 2>nul");
	system(命令符);
	/*修改新生成的exe名称*/
	rename(OldPathName, NewPathName);

	//设置宽高 * /
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
int main()
{
	//开始执行注入
	PrintUI("新程序.exe", "自定义标题", "color 0A", (2560 - 500) / 2 - 50, (1440 - 500) / 2, 500, 500, 0);
	printf("第一步\n");

	HINSTANCE 加载的DLL = LoadLibrary("SetWindowHook.dll");
	if (!加载的DLL)return 0;
	HHOOK(*StartHook)(char 钩子类型, DWORD 线程ID) = (HHOOK(*)(char 钩子类型, DWORD 线程ID))GetProcAddress(加载的DLL, "StartHook");
	bool(*UnHook)(HHOOK 钩子句柄) = (bool(*)(HHOOK 钩子句柄))GetProcAddress(加载的DLL, "UnHook");
	if (!StartHook || !UnHook)return 0;


	DWORD 进程PID = NULL;
	HWND dd = FindWindow("WeChatMainWndForPC", 0);
	HHOOK 钩子句柄 = StartHook(1, GetWindowThreadProcessId(dd, &进程PID));
	short szInput = 0;
	while (szInput != 1)
	{
		cin >> szInput;
	}
	UnHook(钩子句柄);
	system("pause");
	return 0;


	std::cout << "Hello World!\n";
	Sleep(200000);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
