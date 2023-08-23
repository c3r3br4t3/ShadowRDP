

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0626 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for SessEnvRpc.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0626 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __SessEnvRpc_h_h__
#define __SessEnvRpc_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if _CONTROL_FLOW_GUARD_XFG
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

/* header files for imported files */
//#include "ms-dtyp.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_SessEnvRpc_0000_0000 */
/* [local] */ 

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_SessEnvRpc_0000_0000_0001
    {
        SHADOW_CONTROL_REQUEST_VIEW	= 0,
        SHADOW_CONTROL_REQUEST_TAKECONTROL	= ( SHADOW_CONTROL_REQUEST_VIEW + 1 ) ,
        SHADOW_CONTROL_REQUEST_Count	= ( SHADOW_CONTROL_REQUEST_TAKECONTROL + 1 ) 
    } 	SHADOW_CONTROL_REQUEST;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_SessEnvRpc_0000_0000_0002
    {
        SHADOW_PERMISSION_REQUEST_SILENT	= 0,
        SHADOW_PERMISSION_REQUEST_REQUESTPERMISSION	= ( SHADOW_PERMISSION_REQUEST_SILENT + 1 ) ,
        SHADOW_PERMISSION_REQUEST_Count	= ( SHADOW_PERMISSION_REQUEST_REQUESTPERMISSION + 1 ) 
    } 	SHADOW_PERMISSION_REQUEST;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_SessEnvRpc_0000_0000_0003
    {
        SHADOW_REQUEST_RESPONSE_ALLOW	= 0,
        SHADOW_REQUEST_RESPONSE_DECLINE	= ( SHADOW_REQUEST_RESPONSE_ALLOW + 1 ) ,
        SHADOW_REQUEST_RESPONSE_POLICY_PERMISSION_REQUIRED	= ( SHADOW_REQUEST_RESPONSE_DECLINE + 1 ) ,
        SHADOW_REQUEST_RESPONSE_POLICY_DISABLED	= ( SHADOW_REQUEST_RESPONSE_POLICY_PERMISSION_REQUIRED + 1 ) ,
        SHADOW_REQUEST_RESPONSE_POLICY_VIEW_ONLY	= ( SHADOW_REQUEST_RESPONSE_POLICY_DISABLED + 1 ) ,
        SHADOW_REQUEST_RESPONSE_POLICY_VIEW_ONLY_PERMISSION_REQUIRED	= ( SHADOW_REQUEST_RESPONSE_POLICY_VIEW_ONLY + 1 ) ,
        SHADOW_REQUEST_RESPONSE_SESSION_ALREADY_CONTROLLED	= ( SHADOW_REQUEST_RESPONSE_POLICY_VIEW_ONLY_PERMISSION_REQUIRED + 1 ) 
    } 	SHADOW_REQUEST_RESPONSE;



extern RPC_IF_HANDLE __MIDL_itf_SessEnvRpc_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SessEnvRpc_0000_0000_v0_0_s_ifspec;

#ifndef __SessEnvPublicRpc_INTERFACE_DEFINED__
#define __SessEnvPublicRpc_INTERFACE_DEFINED__

/* interface SessEnvPublicRpc */
/* [unique][version][uuid] */ 

#ifndef _SESSENVPUBLICRPC_ENDPOINT_DEF
#define _SESSENVPUBLICRPC_ENDPOINT_DEF
static LPCWSTR SESSENVPUBLICRPC_ENDPOINT = L"\\pipe\\SessEnvPublicRpc"; 
static LPCWSTR SESSENVPUBLICRPC_PROTOCOL_SEQUENCE = L"ncacn_np"; 
#endif // !_SESSENVPUBLICRPC_ENDPOINT_DEF
HRESULT RpcShadow2( 
    /* [in] */ handle_t hBinding,
    /* [in] */ ULONG TargetSessionId,
    /* [in] */ SHADOW_CONTROL_REQUEST eRequestControl,
    /* [in] */ SHADOW_PERMISSION_REQUEST eRequestPermission,
    /* [out] */ SHADOW_REQUEST_RESPONSE *pePermission,
    /* [size_is][string][out] */ LPWSTR pszInvitation,
    /* [range][in] */ ULONG cchInvitation);



extern RPC_IF_HANDLE SessEnvPublicRpc_v1_0_c_ifspec;
extern RPC_IF_HANDLE SessEnvPublicRpc_v1_0_s_ifspec;
#endif /* __SessEnvPublicRpc_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


