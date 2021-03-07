#include "stdafx.h"
#include "Bcrypt.h"

#pragma comment(lib, "Bcrypt")

int _tmain(int argc, _TCHAR* argv[]) {
    argc;
    argv;

    BCRYPT_ALG_HANDLE hRngAlg = NULL;
    if (BCryptOpenAlgorithmProvider(&hRngAlg,BCRYPT_RNG_ALGORITHM,NULL,0) == STATUS_SUCCESS) {

        BYTE buf[32];
        DWORD cbBuf = sizeof buf;
        
        if (BCryptGenRandom(hRngAlg,buf,cbBuf,BCRYPT_RNG_USE_ENTROPY_IN_BUFFER) == STATUS_SUCCESS) {
            // We have the random data
        }

        BCryptCloseAlgorithmProvider(hRngAlg,0);
        hRngAlg = NULL;
    }
	return 0;
}

