#include "stdafx.h"

////////////////////////////////////////////////////////////////////
HRESULT IsLinkedToken(const HANDLE hToken, __inout HANDLE *pLinkedToken, bool *fIsLinked) {
    HRESULT hr = S_OK;
    DWORD cbData =0;
    TOKEN_LINKED_TOKEN LinkedToken = {0};

    *fIsLinked = FALSE;

    if (GetTokenInformation(hToken,
                             TokenLinkedToken,
                             &LinkedToken,
                             sizeof(LinkedToken),
                             &cbData)) {
        *fIsLinked = true;
        *pLinkedToken = LinkedToken.LinkedToken;
    } else {
        DWORD err = GetLastError();
        if (ERROR_NO_SUCH_LOGON_SESSION  != err)
            hr = HRESULT_FROM_WIN32(err);
    }

    return hr;
}

////////////////////////////////////////////////////////////////////
void DumpHighLevelStuff(const HANDLE hToken) {
    // Username and SID
    DWORD dwUser = 0;
    TOKEN_USER *ptu = NULL;
    GetTokenInformation(hToken, TokenUser, NULL, 0, &dwUser);
    if (dwUser > 0) {
        ptu = (TOKEN_USER*)malloc(dwUser);
        if (ptu) {
            if (GetTokenInformation(hToken, TokenUser, ptu, dwUser, &dwUser)) {
                ShowSid(ptu->User.Sid,ptu->User.Attributes);
            }
        }

        free(ptu);
    } else {
        ShowApiError(L"GetTokenInformation");
    }

    // Restricted

}

////////////////////////////////////////////////////////////////////
void DumpGroups(const HANDLE hToken, const bool fVerbose) {
    void *p = malloc(MAX_ALLOC);
    if (!p) {
        ShowApiError(L"malloc");
        return;
    }

    TOKEN_GROUPS *ptg = (TOKEN_GROUPS *)p;
    DWORD cbNeeded = MAX_ALLOC;
    if (!GetTokenInformation(hToken,TokenGroups,ptg,MAX_ALLOC,&cbNeeded)) {
        ShowApiError(L"GetTokenInformation(...,TokenGroups,...");
        return;
    }

    if (!fVerbose)  {
        wprintf(L"Number of groups: %d\n",ptg->GroupCount);
    } else { 
        if (ptg->GroupCount == 0 ) 
			wprintf(L"None");
        else {
            for (size_t i=0; i < ptg->GroupCount; i++) {
                ShowSid(ptg->Groups[i].Sid,ptg->Groups[i].Attributes);
            }
        }
    }
    
    if (p) free(p);
}

////////////////////////////////////////////////////////////////////
void DumpPrivs(const HANDLE hToken, const bool fVerbose) {
    void *p = malloc(MAX_ALLOC);
    if (!p) {
        ShowApiError(L"malloc");
        return;
    }

    TOKEN_PRIVILEGES *ptp = (TOKEN_PRIVILEGES *)p;
    DWORD cbNeeded = MAX_ALLOC;
    if (!GetTokenInformation(hToken,TokenPrivileges,ptp,MAX_ALLOC,&cbNeeded)) {
        ShowApiError(L"GetTokenInformation(...,TokenPrivileges,...");
        return;
    }

    if (!fVerbose)  {
        wprintf(L"Number of privs: %d\n",ptp->PrivilegeCount);
    } else { 
        if (ptp->PrivilegeCount == 0 ) 
			wprintf(L"None");
        else {
            for (size_t i=0; i < ptp->PrivilegeCount; i++)
               ShowPrivilege(ptp->Privileges[i]);
        }
    }
    
    if (p) free(p);
}

////////////////////////////////////////////////////////////////////
void DumpToken(const HANDLE hToken, const bool fVerbose) {
    DumpHighLevelStuff(hToken);
    DumpGroups(hToken,fVerbose);
    DumpPrivs(hToken,fVerbose);
}

////////////////////////////////////////////////////////////////////
HANDLE HandleLinkedToken(const HANDLE hToken) {
    HANDLE hLinkedToken = NULL;
    bool fLinked = false;
    if (IsLinkedToken(hToken,&hLinkedToken,&fLinked) == S_OK && fLinked) {
        wprintf(L"Linked:\tYes\n");
    } else {
        wprintf(L"Linked:\nNo\n");
    }

    return hLinkedToken;
}