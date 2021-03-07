#include "stdafx.h"

HRESULT CoCreateInstanceElevated(
    __in_opt        HWND      hwndParent,
    __in            REFCLSID  rclsid,
    __in            LPCWSTR   lpwszElevationType,
    __in            REFIID    riid,
    __deref_out_opt PVOID    *ppv) {

    wchar_t      wszCLSID[64];
    wchar_t      wszMonikerName[128];

    *ppv = NULL;
    if (0 == StringFromGUID2(rclsid, wszCLSID, _countof(wszCLSID)))
        return E_OUTOFMEMORY;

    int err = swprintf_s(wszMonikerName,
                     _countof(wszMonikerName),
                     L"Elevation:%s!new:%s",
                     lpwszElevationType, 
                     wszCLSID);
    if (-1 == err)
        return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);

    BIND_OPTS3 bo;
    ZeroMemory(&bo, sizeof bo);
    bo.cbStruct       = sizeof bo;
    bo.hwnd           = hwndParent;
    bo.dwClassContext = CLSCTX_LOCAL_SERVER;

    return CoGetObject(wszMonikerName, &bo, riid, ppv);
}


int _tmain(int argc, _TCHAR* argv[]) {

    // this will instantiate the clock's set date/time applet
    // but you won't see it because it needs the base clock applet
    GUID CLSID_Clock;
    wchar_t *wszClsid = L"{9df523b0-a6c0-4ea9-b5f1-f4565c3ac8b8}";
    IIDFromString(wszClsid, &CLSID_Clock);

    GUID IID_Clock;
    wchar_t *wszIid = L"{44557A26-6DAD-4AEC-89B9-7A052719EF01}";
    IIDFromString(wszIid, &IID_Clock);

    CoInitialize(NULL);

    void *pObj = NULL;
    HRESULT hr = CoCreateInstanceElevated(NULL,CLSID_Clock,L"Highest",IID_Clock,(void**)&pObj);
    if (hr!=0) 
        wprintf(L"%X",hr);

    CoUninitialize();

    return 0;
}


