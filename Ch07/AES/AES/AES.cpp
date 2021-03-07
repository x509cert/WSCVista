#include "stdafx.h"

#pragma comment(lib,"Bcrypt")

char *pKey = "1234567890123456";
char *pPlaintext = "'twas midnight in the schoolroom...";

int _tmain(int argc, _TCHAR* argv[]) {

    //open an algorithm handle
    BCRYPT_ALG_HANDLE  hAesAlg = NULL;
    NTSTATUS status = BCryptOpenAlgorithmProvider(&hAesAlg,
                                        BCRYPT_AES_ALGORITHM,
                                        NULL,   // implementation
                                        0);     // flags (DISPATCH)

    DWORD  cbKeyObject = 0;
    DWORD  cbData = 0;
    status = BCryptGetProperty(hAesAlg,
        BCRYPT_OBJECT_LENGTH,
        (PBYTE)&cbKeyObject,
        sizeof DWORD,
        &cbData,0);

    BYTE   *pbKeyObject = new BYTE[cbKeyObject];
    memset(pbKeyObject,0,cbKeyObject);
 
    // generate the key from supplied input key bytes
    BCRYPT_KEY_HANDLE hKey = NULL;
    status = BCryptGenerateSymmetricKey(hAesAlg, 
                                       &hKey, 
                                       pbKeyObject, 
                                       cbKeyObject, 
                                       (PBYTE)pKey, 
                                       strlen(pKey), 
                                       0); 

    //BCryptDeriveKey(

    ULONG cbCipherText = 0;
    status = BCryptEncrypt(hKey,
                (PUCHAR)pPlaintext,
                strlen(pPlaintext),
                NULL,
                NULL,
                0,
                NULL,
                0,
                &cbCipherText,
                BCRYPT_BLOCK_PADDING);

    PUCHAR pCipherText = new UCHAR[cbCipherText];
    status = BCryptEncrypt(hKey,
                (PUCHAR)pPlaintext,
                strlen(pPlaintext),
                NULL,
                NULL,
                0,
                pCipherText,
                cbCipherText,
                &cbCipherText,
                BCRYPT_BLOCK_PADDING);

    BCryptDestroyKey(hKey);
    hKey = NULL;

    SecureZeroMemory(pbKeyObject,cbKeyObject);
    delete [] pbKeyObject;
    pbKeyObject = NULL;

    // Close the algorithm provider
    BCryptCloseAlgorithmProvider(hAesAlg,0);

    return 0;
}

