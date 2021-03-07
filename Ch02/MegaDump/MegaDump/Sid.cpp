#include "stdafx.h"

void ShowSid(__in PSID pSid, const DWORD attr) {
	wchar_t user[MAX_PATH], domain[MAX_PATH];
	DWORD cbUser, cbDomain;
	SID_NAME_USE snu;

	cbUser = _countof(user);
	cbDomain = _countof(domain);
	if (!LookupAccountSid( NULL, pSid, user, &cbUser, domain, &cbDomain, &snu )) {
		//DWORD rc = gle;

		//if ( IsLogonSid( pSid ) )
		//	wprintf( L"(interactive logon session SID)" );
		//else
		//	wprintf( L"[LAS(): gle = %lu]", rc );
		return;
	}

	const wchar_t *t;
	switch ( snu ) {
		case SidTypeUser:           t = L"user";            break;
		case SidTypeGroup:          t = L"group";           break;
		case SidTypeDomain:         t = L"domain";          break;
		case SidTypeAlias:          t = L"alias";           break;
		case SidTypeWellKnownGroup: t = L"well-known group";break;
		case SidTypeDeletedAccount: t = L"deleted";         break;
		case SidTypeInvalid:        t = L"invalid";         break;
		case SidTypeUnknown:        t = L"unknown";         break;
		case SidTypeComputer:       t = L"computer";        break;
        case SidTypeLabel:          t = L"integrity label"; break;
		default:                    t = L"unknown";         break;
	}
    
	const wchar_t *sep = L"\\"; 
	if ( domain[0] == L'\0' || user[0] == L'\0' )
		sep = L"";
    
    wchar_t wszAttr[128];
    wcscpy_s(wszAttr,_countof(wszAttr),L"");
    if (attr & SE_GROUP_MANDATORY)          wcscat_s(wszAttr,_countof(wszAttr),L"[Mandatory]");
    if (attr & SE_GROUP_ENABLED_BY_DEFAULT) wcscat_s(wszAttr,_countof(wszAttr),L"[Enabled by default]");
    if (attr & SE_GROUP_ENABLED)            wcscat_s(wszAttr,_countof(wszAttr),L"[Enabled]");
    if (attr & SE_GROUP_OWNER)              wcscat_s(wszAttr,_countof(wszAttr),L"[Owner]");
    if (attr & SE_GROUP_USE_FOR_DENY_ONLY)  wcscat_s(wszAttr,_countof(wszAttr),L"[Deny]");
    if (attr & SE_GROUP_INTEGRITY)          wcscat_s(wszAttr,_countof(wszAttr),L"[Integrity]");
    if (attr & SE_GROUP_INTEGRITY_ENABLED)  wcscat_s(wszAttr,_countof(wszAttr),L"[Integrity Enabled]");
    if (attr & SE_GROUP_LOGON_ID)           wcscat_s(wszAttr,_countof(wszAttr),L"[Logon ID]");
    if (attr & SE_GROUP_RESOURCE)           wcscat_s(wszAttr,_countof(wszAttr),L"[Resource]");

    wprintf( L"%ls%ls%ls (%ls) %ls%ls ", 
        domain, 
        sep, 
        user,
        t,
        wcslen(wszAttr)?L"":L", ",
        wszAttr);
    
    wchar_t *pwszSid=NULL;
    ConvertSidToStringSid ( pSid, &pwszSid);
	 wprintf(L"[%ls]\n", pwszSid);
    if (pwszSid) LocalFree(pwszSid);
}
