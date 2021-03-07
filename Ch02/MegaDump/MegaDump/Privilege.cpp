#include "stdafx.h"

void  ShowPrivilege(LUID_AND_ATTRIBUTES &priv) {
   wchar_t wszPriv[128];
   LookupPrivilegeValue(NULL,wszPriv,&priv.Luid);
   DWORD dw = GetLastError();
}
