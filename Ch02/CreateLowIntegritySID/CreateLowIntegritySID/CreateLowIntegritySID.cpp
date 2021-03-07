#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[]) {

   // method 1
   wchar_t* wszLowIntegritySid = L"S-1-16-4096";
   PSID pLowIntegritySid = NULL;
   if (!ConvertStringSidToSid(wszLowIntegritySid,&pLowIntegritySid)) {
      wprintf(L"ConvertStringSidToSid failed (%d)\n", GetLastError());
      return GetLastError();
   }

   // method 2
   SID LowIntegritySid = { 
         SID_REVISION, 1,
         {SECURITY_MANDATORY_LABEL_AUTHORITY}, 
         SECURITY_MANDATORY_LOW_RID};

   int i = memcmp(&LowIntegritySid,wszLowIntegritySid,sizeof(SID));

   return 0;
}

