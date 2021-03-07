

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0499 */
/* at Mon Jan 08 20:37:29 2007
 */
/* Compiler settings for .\ExcusesAx.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_ExcusesAxLib,0x42C2C810,0x017D,0x4FF5,0xBF,0xFE,0xE6,0x2F,0xA0,0xD0,0xDB,0xFE);


MIDL_DEFINE_GUID(IID, DIID__DExcusesAx,0xA8B105B4,0x1272,0x484D,0xB9,0x74,0x41,0x08,0x06,0x1D,0x8E,0x41);


MIDL_DEFINE_GUID(IID, DIID__DExcusesAxEvents,0x51837D80,0x92C2,0x47DF,0x98,0x85,0x56,0xE2,0xD0,0xC6,0x62,0xC7);


MIDL_DEFINE_GUID(CLSID, CLSID_ExcusesAx,0x20B97D1A,0x2CC7,0x451E,0x9B,0x6C,0x2C,0x70,0x2F,0x2B,0x69,0x0F);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



