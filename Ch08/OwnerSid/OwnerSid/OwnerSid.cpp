#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[]) {
   PSID TheSID;

   DWORD SidSize = SECURITY_MAX_SID_SIZE;
   // Allocate enough memory for the largest possible SID.
   if(!(TheSID = LocalAlloc(LMEM_FIXED, SidSize))) {    
      fprintf(stderr, "Could not allocate memory.\n");
      exit(1);
   }

   // Create a SID for the Owner on the local computer.
   if(!CreateWellKnownSid(WinCreatorOwnerRightsSid, NULL, TheSID, &SidSize)) {
    fprintf(stderr,
            "CreateWellKnownSid Error %u",
            GetLastError());
   } else {
    // Get the string version of the SID (S-1-1-0).
    LPTSTR p = NULL;
    if(!(ConvertSidToStringSid(TheSID, &p))) {
        fprintf(stderr, 
                "Error during ConvertSidToStringSid.\n");
        exit(1);
    }

    // Use the string SID as needed.
    // ...

    // When done, free the memory used.
    LocalFree(p);
    LocalFree(TheSID);
   }

   return 0;
}

