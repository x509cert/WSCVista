#include "stdafx.h"

#pragma comment(lib, "authz")

int _tmain(int argc, _TCHAR* argv[]) {

    // Install event source
    AUTHZ_SOURCE_SCHEMA_REGISTRATION assr = {0};
    assr.dwFlags = 0;
    assr.szEventSourceName = L"MyAppEvents";
    assr.
    BOOL fRet = AuthzInstallSecurityEventSource)
          0,

    
    // Register the event source
    AUTHZ_SECURITY_EVENT_PROVIDER_HANDLE hEventProvider = NULL;
    fRet = AuthzRegisterSecurityEventSource(
          0,
          L"MyApp",
          &hEventProvider);

    if (!fRet) {
        wprintf(L"Failed to register event source, error is %d",GetLastError());
        return -1;
    }

    // Write an entry
    fRet = AuthzReportSecurityEvent(
          APF_AuditSuccess,
          hEventProvider,


	return 0;
}

