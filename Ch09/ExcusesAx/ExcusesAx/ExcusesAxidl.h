

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __ExcusesAxidl_h__
#define __ExcusesAxidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DExcusesAx_FWD_DEFINED__
#define ___DExcusesAx_FWD_DEFINED__
typedef interface _DExcusesAx _DExcusesAx;
#endif 	/* ___DExcusesAx_FWD_DEFINED__ */


#ifndef ___DExcusesAxEvents_FWD_DEFINED__
#define ___DExcusesAxEvents_FWD_DEFINED__
typedef interface _DExcusesAxEvents _DExcusesAxEvents;
#endif 	/* ___DExcusesAxEvents_FWD_DEFINED__ */


#ifndef __ExcusesAx_FWD_DEFINED__
#define __ExcusesAx_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExcusesAx ExcusesAx;
#else
typedef struct ExcusesAx ExcusesAx;
#endif /* __cplusplus */

#endif 	/* __ExcusesAx_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ExcusesAxLib_LIBRARY_DEFINED__
#define __ExcusesAxLib_LIBRARY_DEFINED__

/* library ExcusesAxLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_ExcusesAxLib;

#ifndef ___DExcusesAx_DISPINTERFACE_DEFINED__
#define ___DExcusesAx_DISPINTERFACE_DEFINED__

/* dispinterface _DExcusesAx */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DExcusesAx;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A8B105B4-1272-484D-B974-4108061D8E41")
    _DExcusesAx : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DExcusesAxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DExcusesAx * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DExcusesAx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DExcusesAx * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DExcusesAx * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DExcusesAx * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DExcusesAx * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DExcusesAx * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DExcusesAxVtbl;

    interface _DExcusesAx
    {
        CONST_VTBL struct _DExcusesAxVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DExcusesAx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DExcusesAx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DExcusesAx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DExcusesAx_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DExcusesAx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DExcusesAx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DExcusesAx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DExcusesAx_DISPINTERFACE_DEFINED__ */


#ifndef ___DExcusesAxEvents_DISPINTERFACE_DEFINED__
#define ___DExcusesAxEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DExcusesAxEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DExcusesAxEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("51837D80-92C2-47DF-9885-56E2D0C662C7")
    _DExcusesAxEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DExcusesAxEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DExcusesAxEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DExcusesAxEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DExcusesAxEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DExcusesAxEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DExcusesAxEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DExcusesAxEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DExcusesAxEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DExcusesAxEventsVtbl;

    interface _DExcusesAxEvents
    {
        CONST_VTBL struct _DExcusesAxEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DExcusesAxEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DExcusesAxEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DExcusesAxEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DExcusesAxEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DExcusesAxEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DExcusesAxEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DExcusesAxEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DExcusesAxEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ExcusesAx;

#ifdef __cplusplus

class DECLSPEC_UUID("20B97D1A-2CC7-451E-9B6C-2C702F2B690F")
ExcusesAx;
#endif
#endif /* __ExcusesAxLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


