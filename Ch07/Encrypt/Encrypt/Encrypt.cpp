#include "stdafx.h"

using namespace std;

#pragma comment(lib, "bcrypt")

wchar_t *GetEncryptionAlg() {
    return BCRYPT_AES_ALGORITHM;
}

LPBYTE GetPwd() {
    static const BYTE key[] = {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,0};
    return (LPBYTE)key;
}

LPBYTE GetIV() {
    static const BYTE iv[] = {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
    return (LPBYTE)iv;
}

int _tmain(int argc, _TCHAR* argv[]) {
    BCRYPT_ALG_HANDLE hAlg = NULL;
    if (BCryptOpenAlgorithmProvider(
                            &hAlg, 
                            GetEncryptionAlg(),
                            NULL,
                            0) == STATUS_SUCCESS) {

        BCRYPT_KEY_HANDLE hKey = NULL;
        DWORD cbKey = 0;
        DWORD cbData = 0;
        if (BCryptGetProperty(
                    hAlg,
                    BCRYPT_OBJECT_LENGTH, 
                    reinterpret_cast<PBYTE>(&cbKey),
                    sizeof cbKey,
                    &cbData,
                    0) == STATUS_SUCCESS) {
            LPBYTE pbKey = new (nothrow)BYTE[cbKey];
            if (pbKey) {
                BCRYPT_KEY_HANDLE hKey = NULL;
                LPCSTR szPwd = (LPCSTR)GetPwd(); 
                if (BCryptGenerateSymmetricKey(
                                    hAlg,
                                    &hKey,
                                    pbKey,
                                    cbKey,
                                    (PUCHAR)szPwd,
                                    (ULONG)strlen(szPwd),
                                    0) == STATUS_SUCCESS) {
                    printf("!!!");
                }


            }
        }
    }


	return 0;
}

