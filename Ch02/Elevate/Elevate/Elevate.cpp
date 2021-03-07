#include "stdafx.h"

BOOL IsElevated() {
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken)) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof TOKEN_ELEVATION;
	    if (GetTokenInformation(hToken,
                   TokenElevation,
                   &Elevation,
                   sizeof(Elevation),
                   &cbSize)) 
            fRet = Elevation.TokenIsElevated;
    }

    if (hToken) CloseHandle(hToken);

    return fRet;
}

TOKEN_ELEVATION_TYPE GetElevationType() {
    HANDLE hToken = NULL; 
    TOKEN_ELEVATION_TYPE type = (TOKEN_ELEVATION_TYPE)0;
    if (OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken)) {
        TOKEN_ELEVATION_TYPE ElevationType;
        DWORD cbSize = sizeof TOKEN_ELEVATION_TYPE;
        if (GetTokenInformation(hToken,
                   TokenElevationType,
                   &ElevationType,
                   sizeof(ElevationType),
	               &cbSize))
        type = ElevationType;
    }

    if (hToken) CloseHandle(hToken);

    return type;
 }

int _tmain(int argc, _TCHAR* argv[]) {
	argc;
	argv;

    wchar_t result[64];
    StringCchPrintf(result,
			    _countof(result),
			    L"Token %s elevated\n",
			    IsElevated() ? L"is" : L"is not");
    MessageBox(NULL,result,argv[0],MB_OK|MB_ICONINFORMATION);


   switch(GetElevationType()) {
       case TokenElevationTypeDefault : 
           MessageBox(NULL,L"TokenElevationTypeDefault",argv[0],MB_OK|MB_ICONINFORMATION);
           break;

       case TokenElevationTypeFull : 
           MessageBox(NULL,L"TokenElevationTypeFull",argv[0],MB_OK|MB_ICONINFORMATION);
           break;

       case TokenElevationTypeLimited : 
           MessageBox(NULL,L"TokenElevationTypeLimited",argv[0],MB_OK|MB_ICONINFORMATION);
           break;

       default: 
           MessageBox(NULL,L"Unknown type",argv[0],MB_OK|MB_ICONEXCLAMATION);
   }

	return 0;
}
