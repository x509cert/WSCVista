#pragma once

//#pragma strict_gs_check (  on )

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0600	// Change this to the appropriate value to target other versions of Windows.
#endif						

#define MAX_ALLOC 20000

#include <stdio.h>
#include <tchar.h>
#include "sal.h"
#include "windows.h"
#include "sddl.h"

void    ShowApiError(__in_z const wchar_t *wszError);
HRESULT IsLinkedToken(const HANDLE hToken, __inout HANDLE *pLinkedToken, bool *fIsLinked);
void    DumpHighLevelStuff(const HANDLE hToken);
void    DumpGroups(const HANDLE hToken, const bool fVerbose);
void    DumpPrivs(const HANDLE hToken, const bool fVerbose);
void    DumpToken(const HANDLE hToken, const bool fVerbose);
HANDLE  HandleLinkedToken(const HANDLE hToken);
void    ShowSid(__in PSID psid,const DWORD attr);
void    ShowPrivilege(LUID_AND_ATTRIBUTES &pPriv);