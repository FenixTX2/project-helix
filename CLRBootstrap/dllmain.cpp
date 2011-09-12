// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <MSCorEE.h>

ICLRRuntimeHost *pClrHost = NULL;
HANDLE hThread;

DWORD __stdcall StartTheDotNetRuntime(LPVOID lpParam)
{

    HRESULT hr = CorBindToRuntimeEx(NULL, L"wks", 0, CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost, (PVOID*)&pClrHost);
    hr = pClrHost->Start();
	MessageBox(0, "Dll Injection Successful! ", "Dll Injector", MB_ICONEXCLAMATION | MB_OK); 
	     

    //DWORD dwRet = 0;
    //hr = pClrHost->ExecuteInDefaultAppDomain(L"ClassLibrary2.dll",L"ClassLibrary2.Class1", L"Test", L"MyParameter", &dwRet);   
    //hr = pClrHost->Stop();    
    //pClrHost->Release();

	return 0;
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved)
{

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&StartTheDotNetRuntime, 0, 0, NULL);
        break;

    case DLL_THREAD_ATTACH:  break;
    case DLL_THREAD_DETACH:  break;
    case DLL_PROCESS_DETACH:

		pClrHost->Stop(); 
		pClrHost->Release(); 
		TerminateThread(hThread, 0);

		//MessageBox(0, "Dll Detatch Successful! ", "Dll Injector", MB_ICONEXCLAMATION | MB_OK); 

        break;
    }

    return TRUE;
}