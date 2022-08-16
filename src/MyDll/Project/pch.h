#pragma once/*保证头文件不被重复包含*/
#include <sdkddkver.h>/*兼容以前的系统*/
#include<stdio.h>
#include<tchar.h>
//#include "resource.h" //资源文件
#include <bitset>/*二进制*/
//#include <afxwin.h>
//#include<Afxwin.h>
#include <conio.h>/*需要再atlstr.h之前获取*/
#include "atlstr.h"
#include <atlimage.h>/*使用CImage,控制合使用CString类,TRACE凾数等, debug工程运行库为"多线程(MT)"或为"多线程DLL(/MD)“无法使用*/
#include <iostream>
#include <WinSock2.h>/*windows网络编程，需要在windiws.h之前*/
#include "Winhttp.h"
#define INITGUID/*必须在<Guiddef.h之前,加载策略组*/
#include <guiddef.h>/*策略组*/
//#include <GPEdit.h>/*策略组CLSID_GroupPolicyObject函数*/
#include <Shlwapi.h>
#include <direct.h>/*新建文件夹，getcwd函数*/
#pragma warning(disable:4996)//getcwd
#include <ctime>/*系统时间*/
#include <TlHelp32.h> //进程函数PROCESSENTRY32等
#include<Psapi.h>
#include<io.h>/*判断文件夹*/
#include <iphlpapi.h>/*网络适配器信息*/
#include<fstream>/*读写文件*/
#include<string>
#include<process.h>
#define WIN32_LEAN_AND_MEAN/*从Windows头中排除极少使用的资料*/
#include <Windows.h>/*GetPixel函数，窗口，Sleep，剪切板*/
#include<sys/timeb.h>/*通常包含time.h*/
//#include "time.h"
#include <Shlwapi.h>
#include <ShlObj.h>
#pragma comment(lib,"Iphlpapi.lib")
#pragma comment(lib,"winhttp.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"psapi.lib")
#pragma comment(lib,"shlwapi.lib")
#define myhtons(A)(((WORD)(A)&0XFF00)>>8|((WORD)(A)&0XFF00)<<8)/*网络编程*/
#define SIO_RCVALL _WASIOW(IOC_VENDOR,1)/*网络编程*/
using namespace std;
//void RandomSeed()
//{
//	srand(time(0));
//}
//float randomFloat(float radix, WORD increments, WORD divisor)
//{
//	float f = rand() % (increments + 1) + radix;
//	f = f / divisor;
//	return f;
//}
