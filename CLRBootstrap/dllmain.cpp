// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <MSCorEE.h>

HANDLE hThread;
ICLRRuntimeHost*	pClrHost;

DWORD __stdcall StartCLR(LPVOID lpParam)
{
	CorBindToRuntimeEx(NULL, L"wks", 0, CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (PVOID*)&pClrHost);

	pClrHost->Start();

	return 0;

}

DWORD __stdcall StopCLR()
{
	pClrHost->Stop();
	pClrHost->Release();
	pClrHost = 0;

	TerminateThread(hThread, 0);

	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			hThread = CreateThread(NULL, NULL, StartCLR, NULL, NULL, NULL);
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			StopCLR();
			break;
	}
	return TRUE;
}

