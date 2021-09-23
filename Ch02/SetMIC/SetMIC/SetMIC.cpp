#include "stdafx.h"

void usage() {
    wprintf(L"\n\nUsage: SetMIC process [integritylevel]\n\n"
			L"Launches a process at the given integrity level, "
			L"where <integritylevel> can be:\n"
			L"\tL - low integrity (default)\n"
			L"\tM - medium integrity\n"
			L"\tH - high integrity\n"
			L"\tS - system integrity\n\n");
}

int __cdecl wmain(int argc, WCHAR** argv) {
    
    if ((argc != 3 && argc !=2) || argv == nullptr) {
		usage();
        return -1;
    }

    wchar_t *wszProcessName  = argv[1];
    wchar_t *wszIntegrityLevelName;
    wchar_t *wszIntegrityLevel = (argc == 3 ? argv[2] : L"L");
    wchar_t *wszIntegritySid = NULL;
    DWORD    colBackground = BACKGROUND_RED;

	 switch(*wszIntegrityLevel) {
		case 'l': 
		case 'L': wszIntegritySid=L"S-1-16-4096"; 
                  wszIntegrityLevelName=L"Low";
                  colBackground = BACKGROUND_GREEN;
				  break;
		case 'm':
		case 'M': wszIntegritySid=L"S-1-16-8192"; 
                  wszIntegrityLevelName=L"Medium";
                  colBackground = 0;
				  break;
		case 'h':
		case 'H': wszIntegritySid=L"S-1-16-12288";
                  wszIntegrityLevelName=L"High";
				  break;
		case 's':
		case 'S': wszIntegritySid=L"S-1-16-16384"; 
                  wszIntegrityLevelName=L"System";
				  break;

		default: usage(); 
				 return -1;
	}

    DWORD err = 0;
    HANDLE hToken = NULL;
    HANDLE hNewToken = NULL;
    PROCESS_INFORMATION  ProcInfo = {0};
    PSID pIntegritySid = NULL;

    try {
        if (!OpenProcessToken(
                GetCurrentProcess(), 
                TOKEN_ALL_ACCESS, 
                &hToken)) {

            wprintf(L"OpenProcessToken failed (%u)\n", 
                GetLastError());

            throw GetLastError();
        }

        TOKEN_ELEVATION_TYPE ElevationType = TokenElevationTypeDefault;
        DWORD cbSize = sizeof TOKEN_ELEVATION_TYPE;
        if (GetTokenInformation(hToken,
           TokenElevationType,
           &ElevationType,
           sizeof(ElevationType),
           &cbSize)) 
        {
            if (ElevationType == TokenElevationTypeFull) 
            {
                throw ERROR_ACCESS_DENIED;
            }
        } 
        else 
        {
            wprintf(L"GetTokenInformation failed (%u)\n", GetLastError());
            throw GetLastError();
        }

	    if (!DuplicateTokenEx(
                hToken,
                TOKEN_ALL_ACCESS,
                NULL,
                SecurityImpersonation,
                TokenPrimary,
			    &hNewToken)) {

            wprintf(
                L"DuplicateTokenEx failed (%u)\n", 
                GetLastError());

            CloseHandle(hToken);
            hToken = NULL;

            throw GetLastError();
        }

        if (!ConvertStringSidToSid(
                wszIntegritySid,
			    &pIntegritySid)) {

            wprintf(L"ConvertStringSidToSid failed (%u)\n", 
                GetLastError());

            throw GetLastError();
        }

        TOKEN_MANDATORY_LABEL til = {0};
        til.Label.Attributes = SE_GROUP_INTEGRITY;
        til.Label.Sid        = pIntegritySid;
        if (!SetTokenInformation(
                hNewToken,
                TokenIntegrityLevel,
                &til,
			    sizeof(TOKEN_MANDATORY_LABEL) + GetLengthSid(pIntegritySid))) {

            wprintf(L"SetTokenInformation failed (%u)\n", 
                GetLastError());
            
            throw GetLastError();
        }

        wchar_t wszTitle[200];
        swprintf_s(wszTitle,_countof(wszTitle)-1,L"%ls (%ls integrity)",
            wszProcessName,
            wszIntegrityLevelName);

	    STARTUPINFO           StartupInfo = {0};
        StartupInfo.cb        = sizeof(STARTUPINFO);
        StartupInfo.dwFlags   = STARTF_USEFILLATTRIBUTE;
        StartupInfo.lpTitle   = wszTitle;
        StartupInfo.dwFillAttribute = colBackground | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;

        if (!CreateProcessAsUser(
                hNewToken,NULL,
                wszProcessName,
                NULL,NULL,
                FALSE,
                CREATE_NEW_CONSOLE,
                NULL,NULL,
                &StartupInfo,&ProcInfo)) 
        {

            wprintf(L"CreateProcessAsUser failed (%u)\n", GetLastError());
            throw GetLastError();
        }
    } catch (const DWORD dwErr) 
    {
        err = dwErr;
    } 

    if (hToken)             CloseHandle(hToken);
    if (hNewToken)          CloseHandle(hNewToken);
    if (ProcInfo.hProcess)  CloseHandle(ProcInfo.hProcess);
    if (ProcInfo.hThread)   CloseHandle(ProcInfo.hThread);
    if (pIntegritySid)      LocalFree(pIntegritySid);

    return err;
}
