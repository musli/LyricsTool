#pragma once/*��֤ͷ�ļ������ظ�����*/
#include <sdkddkver.h>/*������ǰ��ϵͳ*/
#include<stdio.h>
#include<tchar.h>
//#include "resource.h" //��Դ�ļ�
#include <bitset>/*������*/
//#include <afxwin.h>
//#include<Afxwin.h>
#include <conio.h>/*��Ҫ��atlstr.h֮ǰ��ȡ*/
#include "atlstr.h"
#include <atlimage.h>/*ʹ��CImage,���ƺ�ʹ��CString��,TRACE�T����, debug�������п�Ϊ"���߳�(MT)"��Ϊ"���߳�DLL(/MD)���޷�ʹ��*/
#include <iostream>
#include <WinSock2.h>/*windows�����̣���Ҫ��windiws.h֮ǰ*/
#include "Winhttp.h"
#define INITGUID/*������<Guiddef.h֮ǰ,���ز�����*/
#include <guiddef.h>/*������*/
//#include <GPEdit.h>/*������CLSID_GroupPolicyObject����*/
#include <Shlwapi.h>
#include <direct.h>/*�½��ļ��У�getcwd����*/
#pragma warning(disable:4996)//getcwd
#include <ctime>/*ϵͳʱ��*/
#include <TlHelp32.h> //���̺���PROCESSENTRY32��
#include<Psapi.h>
#include<io.h>/*�ж��ļ���*/
#include <iphlpapi.h>/*������������Ϣ*/
#include<fstream>/*��д�ļ�*/
#include<string>
#include<process.h>
#define WIN32_LEAN_AND_MEAN/*��Windowsͷ���ų�����ʹ�õ�����*/
#include <Windows.h>/*GetPixel���������ڣ�Sleep�����а�*/
#include<sys/timeb.h>/*ͨ������time.h*/
//#include "time.h"
#include <Shlwapi.h>
#include <ShlObj.h>
#pragma comment(lib,"Iphlpapi.lib")
#pragma comment(lib,"winhttp.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"psapi.lib")
#pragma comment(lib,"shlwapi.lib")
#define myhtons(A)(((WORD)(A)&0XFF00)>>8|((WORD)(A)&0XFF00)<<8)/*������*/
#define SIO_RCVALL _WASIOW(IOC_VENDOR,1)/*������*/
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
