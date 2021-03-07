#include "stdafx.h"

#pragma comment(lib, "bcrypt")

#ifndef NT_SUCCESS
#   define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

int  __cdecl main(int argc, __in_ecount(argc) LPWSTR *wargv) {
    argc;
    wargv;

    BOOLEAN bFipsEnabled = FALSE;
    if (NT_SUCCESS(BCryptGetFipsAlgorithmMode(&bFipsEnabled))) 
        printf("FIPS is %Senabled.\n",bFipsEnabled ? L"" : L"not ");

    PCRYPT_PROVIDER_REFS pProviders = NULL;
    DWORD dwBufSize = 0;
    const DWORD dwFlags = CRYPT_ALL_FUNCTIONS | CRYPT_ALL_PROVIDERS;

    for (DWORD i = BCRYPT_CIPHER_INTERFACE; i <= BCRYPT_RNG_INTERFACE; i++) {
        NTSTATUS ret = BCryptResolveProviders(
                            NULL, 
                            i, 
                            NULL, 
                            NULL, 
                            CRYPT_UM, 
                            dwFlags, 
                            &dwBufSize, 
                            &pProviders);
        if (NT_SUCCESS(ret) && pProviders) {
	        printf("dwInterface = %d\n", i);

            for (DWORD k=0; k < pProviders->cProviders; k++) {
                PCRYPT_PROVIDER_REF pProv = pProviders->rgpProviders[k];
    	        
                printf("\tFunction = %S\n", pProv->pszFunction);
	            printf("\tProvider = %S\n", pProv->pszProvider);

	            // dump property names
	            for ( DWORD j = 0; j < pProv->cProperties; j++)
		            printf("\tProperty %d = %S\n", j, pProv->rgpProperties[j]->pszProperty);    

                printf("\n");
            }

     	    BCryptFreeBuffer(pProviders);
            pProviders = NULL;		
	        dwBufSize = 0;
        }
    }

    return 0;
}

