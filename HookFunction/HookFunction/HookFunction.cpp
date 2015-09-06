// HookFunction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdint.h>
#include "easyhook.h"


int main(int argc,char** argv)
{
	DWORD pid = atoi(argv[1]);/*the process's id which dll is injected into*/

	wchar_t* dllname = L"HookDll.dll";/*the dll's name to be injected*/
	DWORD namesize = wcslen(dllname);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	LPVOID pRemoteBuf = VirtualAllocEx(hProcess, NULL, namesize * 2 + 2, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(hProcess, pRemoteBuf, dllname, namesize * 2 + 2, NULL);
	HANDLE hThread=CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, pRemoteBuf, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
    return 0;
}

