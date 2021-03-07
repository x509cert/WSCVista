#include "stdafx.h"

#pragma comment(lib, "tbs")

// Data from TPM starts at byte 10
#define TPM_DATA_OFFSET 10

#ifdef _DEBUG
// Display TPM data hex dump
void TpmDisplayRawResult(
      __in_bcount(cbResult) BYTE *pbResult, 
      UINT32 cbResult) {

   if (!cbResult || !pbResult)
      return;

   if (cbResult >= TPM_DATA_OFFSET) {
      wprintf(L"Tag : %02X %02X\n",
         pbResult[0], pbResult[1]);

      wprintf(L"Len : %02X %02X %02X %02X\n",
         pbResult[2], pbResult[3], pbResult[4], pbResult[5]);

      wprintf(L"Err : %02X %02X %02X %02X\n",
         pbResult[6], pbResult[7], pbResult[8], pbResult[9]);

      if (cbResult > TPM_DATA_OFFSET) {      
         wprintf(L"Data: ");
         for (UINT32 i=TPM_DATA_OFFSET; i < cbResult-TPM_DATA_OFFSET; i++) 
            wprintf(L"%02X ",pbResult[i]);
         wprintf(L"\n");
      }
   }
}
#endif

#define MAX_RNG_BUFF 64
#define TPM_RNG_OFFSET 14
HRESULT TpmGetRandomData(
      TBS_HCONTEXT hContext,
      __inout_bcount(cData) BYTE *pData, 
      UINT32 cData) {

   if (!hContext || !pData || !cData || cData > MAX_RNG_BUFF)
      return HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

    BYTE   bCmd[] = {0x00, 0xc1,              // TPM_TAG_RQU_COMMAND
                     0x00, 0x00, 0x00, 0x0e,  // blob length in bytes
                     0x00, 0x00, 0x00, 0x46,  // TPM API code (TPM_ORD_GetRandom)
                     0x00, 0x00, 0x00, (BYTE)cData};// # bytes

    UINT32 cbCmd = sizeof bCmd;
    BYTE   bResult[128] = {0};
    UINT32 cbResult = sizeof bResult;
    HRESULT hr = Tbsip_Submit_Command(hContext, 
                  TBS_COMMAND_LOCALITY_ZERO,
                  TBS_COMMAND_PRIORITY_NORMAL, 
                  bCmd, 
                  cbCmd,
                  bResult, 
                  &cbResult);

#ifdef _DEBUG
    if (FAILED(hr)) 
       wprintf(L"Tbsip_Submit_Command failed %X",hr);
    else 
       TpmDisplayRawResult(bResult,cbResult);
#endif

    if (SUCCEEDED(hr))
       memcpy(pData,TPM_RNG_OFFSET+bResult,cData);

    return hr;
}

HRESULT TpmGetVersion(
      TBS_HCONTEXT hContext,
      __in_ecount(cVersion) wchar_t *wszVersion, 
      UINT32 cVersion) {

    if (!hContext || !wszVersion || !cVersion)
       return HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

    BYTE   bCmd[] = {0x00, 0xc1,             // TPM_TAG_RQU_COMMAND
                     0x00, 0x00, 0x00, 0x12, // blob length in bytes
                     0x00, 0x00, 0x00, 0x65, // TPM API code (TPM_ORD_GetCapability)
                     0x00, 0x00, 0x00, 0x06, // TCPA_CAP_VERSION
                     0x00, 0x00, 0x00, 0x00};// no sub capability
    UINT32 cbCmd = sizeof bCmd;
    BYTE   bResult[128] = {0};
    UINT32 cbResult = sizeof bResult;
    HRESULT hr = Tbsip_Submit_Command(hContext, 
                  TBS_COMMAND_LOCALITY_ZERO,
                  TBS_COMMAND_PRIORITY_NORMAL, 
                  bCmd, 
                  cbCmd,
                  bResult, 
                  &cbResult);

#ifdef _DEBUG
    if (FAILED(hr)) 
       wprintf(L"Tbsip_Submit_Command failed %X",hr);
    else 
       TpmDisplayRawResult(bResult,cbResult);
#endif

    if (SUCCEEDED(hr)) 
      swprintf_s(wszVersion,cVersion,L"TCG v%d.%d, Firmware v%d.%d",
         (UINT32)bResult[14],
         (UINT32)bResult[15],
         (UINT32)bResult[16],
         (UINT32)bResult[17]);

    return hr;
}

int main(int argc, char* argv[]) {
   argv;
   argc;

   // Create a TBS context
   TBS_HCONTEXT hContext = 0;
   TBS_CONTEXT_PARAMS contextParams = {0};
   contextParams.version = TBS_CONTEXT_VERSION_ONE;
   HRESULT hr = Tbsi_Context_Create(&contextParams, &hContext);
   if (FAILED(hr))
      return hr;

   wchar_t wszVersion[32];
   if (SUCCEEDED(TpmGetVersion(hContext,wszVersion,_countof(wszVersion))))
      wprintf(L"%s\n",wszVersion);

   BYTE buff[64];
   UINT32 cBuff = sizeof buff;
   if (SUCCEEDED(TpmGetRandomData(hContext,buff,cBuff)))
      for (UINT32 i=0; i < cBuff; i++)
         wprintf(L"%02X ",buff[i]);

   if (hContext)
      Tbsip_Context_Close(hContext);

	return 0;
}
