

/* this ALWAYS GENERATED file contains the RPC client stubs */


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

#if defined(_M_AMD64)


#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/

#include <string.h>

#include "SessEnvRpc.h"

#ifdef _MSC_VER
#define decor extern
#else
#define decor static
#endif

#define TYPE_FORMAT_STRING_SIZE   39                                
#define PROC_FORMAT_STRING_SIZE   73                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _SessEnvRpc_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } SessEnvRpc_MIDL_TYPE_FORMAT_STRING;

typedef struct _SessEnvRpc_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } SessEnvRpc_MIDL_PROC_FORMAT_STRING;

typedef struct _SessEnvRpc_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } SessEnvRpc_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};

static const RPC_SYNTAX_IDENTIFIER  _NDR64_RpcTransferSyntax = 
{{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}};

#if defined(_CONTROL_FLOW_GUARD_XFG)
#define XFG_TRAMPOLINES(ObjectType)\
static unsigned long ObjectType ## _UserSize_XFG(unsigned long * pFlags, unsigned long Offset, void * pObject)\
{\
return  ObjectType ## _UserSize(pFlags, Offset, pObject);\
}\
static unsigned char * ObjectType ## _UserMarshal_XFG(unsigned long * pFlags, unsigned char * pBuffer, void * pObject)\
{\
return ObjectType ## _UserMarshal(pFlags, pBuffer, pObject);\
}\
static unsigned char * ObjectType ## _UserUnmarshal_XFG(unsigned long * pFlags, unsigned char * pBuffer, void * pObject)\
{\
return ObjectType ## _UserUnmarshal(pFlags, pBuffer, pObject);\
}\
static void ObjectType ## _UserFree_XFG(unsigned long * pFlags, void * pObject)\
{\
ObjectType ## _UserFree(pFlags, pObject);\
}
#define XFG_TRAMPOLINES64(ObjectType)\
static unsigned long ObjectType ## _UserSize64_XFG(unsigned long * pFlags, unsigned long Offset, void * pObject)\
{\
return  ObjectType ## _UserSize64(pFlags, Offset, pObject);\
}\
static unsigned char * ObjectType ## _UserMarshal64_XFG(unsigned long * pFlags, unsigned char * pBuffer, void * pObject)\
{\
return ObjectType ## _UserMarshal64(pFlags, pBuffer, pObject);\
}\
static unsigned char * ObjectType ## _UserUnmarshal64_XFG(unsigned long * pFlags, unsigned char * pBuffer, void * pObject)\
{\
return ObjectType ## _UserUnmarshal64(pFlags, pBuffer, pObject);\
}\
static void ObjectType ## _UserFree64_XFG(unsigned long * pFlags, void * pObject)\
{\
ObjectType ## _UserFree64(pFlags, pObject);\
}
#define XFG_BIND_TRAMPOLINES(HandleType, ObjectType)\
static void* ObjectType ## _bind_XFG(HandleType pObject)\
{\
return ObjectType ## _bind((ObjectType) pObject);\
}\
static void ObjectType ## _unbind_XFG(HandleType pObject, handle_t ServerHandle)\
{\
ObjectType ## _unbind((ObjectType) pObject, ServerHandle);\
}
#define XFG_TRAMPOLINE_FPTR(Function) Function ## _XFG
#else
#define XFG_TRAMPOLINES(ObjectType)
#define XFG_TRAMPOLINES64(ObjectType)
#define XFG_BIND_TRAMPOLINES(HandleType, ObjectType)
#define XFG_TRAMPOLINE_FPTR(Function) Function
#endif



decor const SessEnvRpc_MIDL_TYPE_FORMAT_STRING SessEnvRpc__MIDL_TypeFormatString;
decor const SessEnvRpc_MIDL_PROC_FORMAT_STRING SessEnvRpc__MIDL_ProcFormatString;
decor const SessEnvRpc_MIDL_EXPR_FORMAT_STRING SessEnvRpc__MIDL_ExprFormatString;

#define GENERIC_BINDING_TABLE_SIZE   0            


/* Standard interface: __MIDL_itf_SessEnvRpc_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Standard interface: SessEnvPublicRpc, ver. 1.0,
   GUID={0x1257B580,0xCE2F,0x4109,{0x82,0xD6,0xA9,0x45,0x9D,0x0B,0xF6,0xBC}} */

 decor const MIDL_STUBLESS_PROXY_INFO SessEnvPublicRpc_ProxyInfo;


static const RPC_CLIENT_INTERFACE SessEnvPublicRpc___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0x1257B580,0xCE2F,0x4109,{0x82,0xD6,0xA9,0x45,0x9D,0x0B,0xF6,0xBC}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    &SessEnvPublicRpc_ProxyInfo,
    0x02000000
    };
RPC_IF_HANDLE SessEnvPublicRpc_v1_0_c_ifspec = (RPC_IF_HANDLE)& SessEnvPublicRpc___RpcClientInterface;

decor const MIDL_STUB_DESC SessEnvPublicRpc_StubDesc;

static RPC_BINDING_HANDLE SessEnvPublicRpc__MIDL_AutoBindHandle;


HRESULT RpcShadow2( 
    /* [in] */ handle_t hBinding,
    /* [in] */ ULONG TargetSessionId,
    /* [in] */ SHADOW_CONTROL_REQUEST eRequestControl,
    /* [in] */ SHADOW_PERMISSION_REQUEST eRequestPermission,
    /* [out] */ SHADOW_REQUEST_RESPONSE *pePermission,
    /* [size_is][string][out] */ LPWSTR pszInvitation,
    /* [range][in] */ ULONG cchInvitation)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall3(
                  ( PMIDL_STUBLESS_PROXY_INFO  )&SessEnvPublicRpc_ProxyInfo,
                  0,
                  0,
                  hBinding,
                  TargetSessionId,
                  eRequestControl,
                  eRequestPermission,
                  pePermission,
                  pszInvitation,
                  cchInvitation);
    return ( HRESULT  )_RetVal.Simple;
    
}


#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const SessEnvRpc_MIDL_PROC_FORMAT_STRING SessEnvRpc__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure RpcShadow2 */

			0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x40 ),	/* X64 Stack size/offset = 64 */
/* 10 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 12 */	NdrFcShort( 0x0 ),	/* X64 Stack size/offset = 0 */
/* 14 */	NdrFcShort( 0x1c ),	/* 28 */
/* 16 */	NdrFcShort( 0x22 ),	/* 34 */
/* 18 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x7,		/* 7 */
/* 20 */	0xa,		/* 10 */
			0x43,		/* Ext Flags:  new corr desc, clt corr check, has range on conformance */
/* 22 */	NdrFcShort( 0x1 ),	/* 1 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */
/* 28 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter TargetSessionId */

/* 30 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter eRequestControl */

/* 36 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 38 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 40 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter eRequestPermission */

/* 42 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 44 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 46 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pePermission */

/* 48 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 50 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 52 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Parameter pszInvitation */

/* 54 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 56 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 58 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Parameter cchInvitation */

/* 60 */	NdrFcShort( 0x88 ),	/* Flags:  in, by val, */
/* 62 */	NdrFcShort( 0x30 ),	/* X64 Stack size/offset = 48 */
/* 64 */	NdrFcShort( 0x1c ),	/* 28 */

	/* Return value */

/* 66 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 68 */	NdrFcShort( 0x38 ),	/* X64 Stack size/offset = 56 */
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const SessEnvRpc_MIDL_TYPE_FORMAT_STRING SessEnvRpc__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x0,	/* FC_RP */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x25,		/* FC_C_WSTRING */
			0x44,		/* FC_STRING_SIZED */
/* 12 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 14 */	NdrFcShort( 0x30 ),	/* X64 Stack size/offset = 48 */
/* 16 */	NdrFcShort( 0x10 ),	/* Corr flags:  */
/* 18 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 20 */	NdrFcLong( 0x1 ),	/* 1 */
/* 24 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 28 */	0xb7,		/* FC_RANGE */
			0x8,		/* 8 */
/* 30 */	NdrFcLong( 0x1 ),	/* 1 */
/* 34 */	NdrFcLong( 0x2000 ),	/* 8192 */

			0x0
        }
    };

static const unsigned short SessEnvPublicRpc_FormatStringOffsetTable[] =
    {
    0
    };



#endif /* defined(_M_AMD64)*/



/* this ALWAYS GENERATED file contains the RPC client stubs */


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

#if defined(_M_AMD64)




#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif


#include "ndr64types.h"
#include "pshpack8.h"


typedef 
NDR64_FORMAT_CHAR
__midl_frag12_t;
decor const __midl_frag12_t __midl_frag12;

typedef 
struct _NDR64_RANGE_FORMAT
__midl_frag11_t;
decor const __midl_frag11_t __midl_frag11;

typedef 
struct NDR64_SIZED_CONFORMANT_STRING_FORMAT
__midl_frag10_t;
decor const __midl_frag10_t __midl_frag10;

typedef 
struct 
{
    NDR64_FORMAT_UINT32 frag1;
    struct _NDR64_RANGE_FORMAT frag2;
    struct _NDR64_EXPR_VAR frag3;
}
__midl_frag9_t;
decor const __midl_frag9_t __midl_frag9;

typedef 
struct _NDR64_POINTER_FORMAT
__midl_frag8_t;
decor const __midl_frag8_t __midl_frag8;

typedef 
NDR64_FORMAT_CHAR
__midl_frag7_t;
decor const __midl_frag7_t __midl_frag7;

typedef 
struct _NDR64_POINTER_FORMAT
__midl_frag6_t;
decor const __midl_frag6_t __midl_frag6;

typedef 
struct 
{
    struct _NDR64_PROC_FORMAT frag1;
    struct _NDR64_BIND_AND_NOTIFY_EXTENSION frag2;
    struct _NDR64_PARAM_FORMAT frag3;
    struct _NDR64_PARAM_FORMAT frag4;
    struct _NDR64_PARAM_FORMAT frag5;
    struct _NDR64_PARAM_FORMAT frag6;
    struct _NDR64_PARAM_FORMAT frag7;
    struct _NDR64_PARAM_FORMAT frag8;
    struct _NDR64_PARAM_FORMAT frag9;
}
__midl_frag2_t;
decor const __midl_frag2_t __midl_frag2;

typedef 
NDR64_FORMAT_UINT32
__midl_frag1_t;
decor const __midl_frag1_t __midl_frag1;

static const __midl_frag12_t __midl_frag12 =
0x5    /* FC64_INT32 */;

static const __midl_frag11_t __midl_frag11 =
{ 
/* ULONG */
    0xa4,    /* FC64_RANGE */
    0x5,    /* FC64_INT32 */
    (NDR64_UINT16) 0 /* 0x0 */,
    (NDR64_INT64) 1 /* 0x1 */,
    (NDR64_INT64) 8192 /* 0x2000 */
};

static const __midl_frag10_t __midl_frag10 =
{ 
/* *wchar_t */
    { 
    /* *wchar_t */
        0x64,    /* FC64_CONF_WCHAR_STRING */
        { 
        /* *wchar_t */
            1,
            0,
            0,
            0,
            0,
            0,
            0,
            0
        },
        (NDR64_UINT16) 2 /* 0x2 */
    },
    &__midl_frag9
};

static const __midl_frag9_t __midl_frag9 =
{ 
/*  */
    (NDR64_UINT32) 4 /* 0x4 */,
    { 
    /* struct _NDR64_RANGE_FORMAT */
        0xa4,    /* FC64_RANGE */
        0x5,    /* FC64_INT32 */
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_INT64) 1 /* 0x1 */,
        (NDR64_INT64) 8192 /* 0x2000 */
    },
    { 
    /* struct _NDR64_EXPR_VAR */
        0x3,    /* FC_EXPR_VAR */
        0x6,    /* FC64_UINT32 */
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT32) 48 /* 0x30 */  /* Offset */
    }
};

static const __midl_frag8_t __midl_frag8 =
{ 
/* *wchar_t */
    0x20,    /* FC64_RP */
    (NDR64_UINT8) 0 /* 0x0 */,
    (NDR64_UINT16) 0 /* 0x0 */,
    &__midl_frag10
};

static const __midl_frag7_t __midl_frag7 =
0x5    /* FC64_INT32 */;

static const __midl_frag6_t __midl_frag6 =
{ 
/* *SHADOW_REQUEST_RESPONSE */
    0x20,    /* FC64_RP */
    (NDR64_UINT8) 12 /* 0xc */,
    (NDR64_UINT16) 0 /* 0x0 */,
    &__midl_frag7
};

static const __midl_frag2_t __midl_frag2 =
{ 
/* RpcShadow2 */
    { 
    /* RpcShadow2 */      /* procedure RpcShadow2 */
        (NDR64_UINT32) 21626944 /* 0x14a0040 */,    /* explicit handle */ /* IsIntrepreted, ServerMustSize, HasReturn, ClientCorrelation, HasExtensions */
        (NDR64_UINT32) 64 /* 0x40 */ ,  /* Stack size */
        (NDR64_UINT32) 32 /* 0x20 */,
        (NDR64_UINT32) 40 /* 0x28 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 7 /* 0x7 */,
        (NDR64_UINT16) 8 /* 0x8 */
    },
    { 
    /* struct _NDR64_BIND_AND_NOTIFY_EXTENSION */
        { 
        /* struct _NDR64_BIND_AND_NOTIFY_EXTENSION */
            0x72,    /* FC64_BIND_PRIMITIVE */
            (NDR64_UINT8) 0 /* 0x0 */,
            0 /* 0x0 */,   /* Stack offset */
            (NDR64_UINT8) 0 /* 0x0 */,
            (NDR64_UINT8) 0 /* 0x0 */
        },
        (NDR64_UINT16) 0 /* 0x0 */      /* Notify index */
    },
    { 
    /* TargetSessionId */      /* parameter TargetSessionId */
        &__midl_frag7,
        { 
        /* TargetSessionId */
            0,
            0,
            0,
            1,
            0,
            0,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [in], Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        8 /* 0x8 */,   /* Stack offset */
    },
    { 
    /* eRequestControl */      /* parameter eRequestControl */
        &__midl_frag7,
        { 
        /* eRequestControl */
            0,
            0,
            0,
            1,
            0,
            0,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [in], Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        16 /* 0x10 */,   /* Stack offset */
    },
    { 
    /* eRequestPermission */      /* parameter eRequestPermission */
        &__midl_frag7,
        { 
        /* eRequestPermission */
            0,
            0,
            0,
            1,
            0,
            0,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [in], Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        24 /* 0x18 */,   /* Stack offset */
    },
    { 
    /* pePermission */      /* parameter pePermission */
        &__midl_frag7,
        { 
        /* pePermission */
            0,
            0,
            0,
            0,
            1,
            0,
            1,
            0,
            1,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            1
        },    /* [out], Basetype, SimpleRef, UseCache */
        (NDR64_UINT16) 0 /* 0x0 */,
        32 /* 0x20 */,   /* Stack offset */
    },
    { 
    /* pszInvitation */      /* parameter pszInvitation */
        &__midl_frag10,
        { 
        /* pszInvitation */
            1,
            1,
            0,
            0,
            1,
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* MustSize, MustFree, [out], SimpleRef */
        (NDR64_UINT16) 0 /* 0x0 */,
        40 /* 0x28 */,   /* Stack offset */
    },
    { 
    /* cchInvitation */      /* parameter cchInvitation */
        &__midl_frag11,
        { 
        /* cchInvitation */
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [in], ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        48 /* 0x30 */,   /* Stack offset */
    },
    { 
    /* HRESULT */      /* parameter HRESULT */
        &__midl_frag12,
        { 
        /* HRESULT */
            0,
            0,
            0,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [out], IsReturn, Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        56 /* 0x38 */,   /* Stack offset */
    }
};

static const __midl_frag1_t __midl_frag1 =
(NDR64_UINT32) 0 /* 0x0 */;


#include "poppack.h"


static const FormatInfoRef SessEnvPublicRpc_Ndr64ProcTable[] =
    {
    &__midl_frag2
    };


static const MIDL_STUB_DESC SessEnvPublicRpc_StubDesc = 
    {
    (void *)& SessEnvPublicRpc___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &SessEnvPublicRpc__MIDL_AutoBindHandle,
    0,
    0,
    0,
    0,
    SessEnvRpc__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x8010272, /* MIDL Version 8.1.626 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x2000001, /* MIDL flag */
    0, /* cs routines */
    (void *)& SessEnvPublicRpc_ProxyInfo,   /* proxy/server info */
    0
    };

static const MIDL_SYNTAX_INFO SessEnvPublicRpc_SyntaxInfo [  2 ] = 
    {
    {
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    SessEnvRpc__MIDL_ProcFormatString.Format,
    SessEnvPublicRpc_FormatStringOffsetTable,
    SessEnvRpc__MIDL_TypeFormatString.Format,
    0,
    0,
    0
    }
    ,{
    {{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}},
    0,
    0 ,
    (unsigned short *) SessEnvPublicRpc_Ndr64ProcTable,
    0,
    0,
    0,
    0
    }
    };

static const MIDL_STUBLESS_PROXY_INFO SessEnvPublicRpc_ProxyInfo =
    {
    &SessEnvPublicRpc_StubDesc,
    SessEnvRpc__MIDL_ProcFormatString.Format,
    SessEnvPublicRpc_FormatStringOffsetTable,
    (RPC_SYNTAX_IDENTIFIER*)&_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)SessEnvPublicRpc_SyntaxInfo
    
    };

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

