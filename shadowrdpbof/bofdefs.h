#pragma once
#define SECURITY_WIN32

#include <windows.h>
#include <process.h>
#include <stdio.h>

#ifdef __cplusplus

extern "C" {
#endif

#include "beacon.h"
#if defined(BOF) 
void go(char* buff, int len);
#elif defined(BRC4)
void coffee(char** argv, int argc, WCHAR** dispatch);
#endif

#define intAlloc(size) KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, size)
#define intRealloc(ptr, size) (ptr) ? KERNEL32$HeapReAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, ptr, size) : KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, size)
#define intFree(addr) KERNEL32$HeapFree(KERNEL32$GetProcessHeap(), 0, addr)
#define intZeroMemory(addr,size) MSVCRT$memset((addr),0,size)

/* Memory */
DECLSPEC_IMPORT LPVOID	WINAPI KERNEL32$HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
DECLSPEC_IMPORT BOOL	WINAPI KERNEL32$HeapFree(HANDLE, DWORD, PVOID);
DECLSPEC_IMPORT LPVOID	WINAPI KERNEL32$HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes);
DECLSPEC_IMPORT void* __cdecl  MSVCRT$memcpy(LPVOID, LPVOID, size_t);
DECLSPEC_IMPORT void __cdecl   MSVCRT$memset(void*, int, size_t);


/* Process */
DECLSPEC_IMPORT HANDLE	WINAPI KERNEL32$OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);
DECLSPEC_IMPORT BOOL	WINAPI ADVAPI32$CreateProcessWithLogonW(LPCWSTR lpUsername, LPCWSTR lpDomain, LPCWSTR lpPassword, DWORD dwLogonFlags, LPCWSTR lpApplicationName, LPWSTR lpCommandLine, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
DECLSPEC_IMPORT HANDLE	WINAPI KERNEL32$GetProcessHeap();
DECLSPEC_IMPORT SIZE_T WINAPI  KERNEL32$VirtualQueryEx(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
DECLSPEC_IMPORT DWORD WINAPI   KERNEL32$GetProcessId(HANDLE Process);
DECLSPEC_IMPORT BOOL WINAPI    KERNEL32$ReadProcessMemory(HANDLE  hProcess, LPCVOID lpBaseAddress, LPVOID  lpBuffer, SIZE_T  nSize, SIZE_T* lpNumberOfBytesRead);
DECLSPEC_IMPORT VOID WINAPI    KERNEL32$Sleep(DWORD dwMilliseconds);
DECLSPEC_IMPORT HANDLE WINAPI  KERNEL32$GetCurrentProcess(VOID);
DECLSPEC_IMPORT BOOL WINAPI	   ADVAPI32$LookupPrivilegeValueW(LPCWSTR lpSystemName, LPCWSTR lpName, PLUID lpLuid);
DECLSPEC_IMPORT DWORD WINAPI   PSAPI$GetModuleFileNameExW(HANDLE hProcess, HMODULE hModule, LPWSTR lpFilename, DWORD nSize);
DECLSPEC_IMPORT HMODULE WINAPI KERNEL32$GetModuleHandleA(LPCSTR lpModuleName);

/* GetLast Error */
DECLSPEC_IMPORT DWORD	WINAPI KERNEL32$GetLastError(VOID);

/* strings */
DECLSPEC_IMPORT PSTR WINAPI SHLWAPI$StrChrA(PCSTR pszStart, WORD wMatch);
DECLSPEC_IMPORT LPSTR	__cdecl	MSVCRT$strchr(LPSTR, int);
DECLSPEC_IMPORT size_t	__cdecl	MSVCRT$strlen(const char*);
DECLSPEC_IMPORT errno_t __cdecl MSVCRT$strcat_s(LPSTR, size_t, LPCSTR);
DECLSPEC_IMPORT char* __cdecl 	MSVCRT$strcpy( char *strDestination, const char *strSource);
DECLSPEC_IMPORT errno_t __cdecl MSVCRT$strcpy_s(LPSTR, size_t, LPCSTR);
DECLSPEC_IMPORT errno_t __cdecl MSVCRT$strncpy_s(LPSTR, size_t, LPCSTR, size_t);
DECLSPEC_IMPORT int		__cdecl	MSVCRT$_snprintf(LPSTR, size_t, LPCSTR, ...);
DECLSPEC_IMPORT void WINAPI		MSVCRT$sprintf(char*, char[], ...);
DECLSPEC_IMPORT int		__cdecl MSVCRT$_vsnprintf(LPSTR, size_t, LPCSTR, va_list);
DECLSPEC_IMPORT int __cdecl		MSVCRT$strcmp(const char* _Str1, const char* _Str2);
DECLSPEC_IMPORT LPSTR WINAPI	Kernel32$lstrcpyA(LPSTR lpString1, LPCSTR lpString2);
DECLSPEC_IMPORT LPSTR WINAPI	Kernel32$lstrcatA(LPSTR lpString1, LPCSTR lpString2);
DECLSPEC_IMPORT LPSTR WINAPI	Kernel32$lstrcpynA(LPSTR lpString1, LPCSTR lpString2, int iMaxLength);
DECLSPEC_IMPORT int WINAPI		KERNEL32$lstrlenW(LPCWSTR lpString);
DECLSPEC_IMPORT LPWSTR WINAPI	KERNEL32$lstrcpyW(LPWSTR lpString1, LPCWSTR lpString2);
DECLSPEC_IMPORT int	__cdecl	    MSVCRT$atoi(const char*);
DECLSPEC_IMPORT int __cdecl     MSVCRT$_vsnwprintf_s(wchar_t *buffer, size_t sizeOfBuffer, size_t count, const wchar_t *format, va_list argptr);


/* RPC */
DECLSPEC_IMPORT RPC_STATUS RPC_ENTRY Rpcrt4$RpcStringFreeA(RPC_CSTR* String);
DECLSPEC_IMPORT RPC_STATUS RPC_ENTRY Rpcrt4$UuidCreate(UUID* Uuid);
DECLSPEC_IMPORT RPC_STATUS RPC_ENTRY Rpcrt4$UuidToStringA(const UUID* Uuid, RPC_CSTR* StringUuid);
DECLSPEC_IMPORT int RPC_ENTRY RPCRT4$RpcExceptionFilter(unsigned int ExceptionCode);
RPCRTAPI RPC_STATUS WINAPI RPCRT4$RpcStringBindingComposeW(RPC_WSTR ObjUuid, RPC_WSTR ProtSeq, RPC_WSTR NetworkAddr, RPC_WSTR Endpoint, RPC_WSTR Options, RPC_WSTR* StringBinding);
RPCRTAPI RPC_STATUS WINAPI RPCRT4$RpcBindingFromStringBindingW(RPC_WSTR StringBinding, RPC_BINDING_HANDLE* Binding);
RPCRTAPI RPC_STATUS WINAPI RPCRT4$RpcBindingSetAuthInfoExW(RPC_BINDING_HANDLE Binding, RPC_WSTR ServerPrincName, unsigned long AuthnLevel, unsigned long AuthnSvc, RPC_AUTH_IDENTITY_HANDLE AuthIdentity, unsigned long AuthzSvc, RPC_SECURITY_QOS* SecurityQOS);
RPCRTAPI RPC_STATUS WINAPI RPCRT4$RpcBindingFree(RPC_BINDING_HANDLE* Binding);
RPCRTAPI RPC_STATUS WINAPI RPCRT4$RpcStringFreeW(RPC_WSTR* String);
RPCRTAPI CLIENT_CALL_RETURN RPC_VAR_ENTRY RPCRT4$NdrClientCall3(PMIDL_STUBLESS_PROXY_INFO pProxyInfo, unsigned long nProcNum, void* pReturnValue, ...);
WINBASEAPI PVOID WINAPI KERNEL32$AddVectoredExceptionHandler(ULONG First, PVECTORED_EXCEPTION_HANDLER Handler);
WINBASEAPI ULONG WINAPI KERNEL32$RemoveVectoredExceptionHandler(PVOID Handle);
DECLSPEC_IMPORT uintptr_t __cdecl MSVCRT$_beginthreadex(void* _Security, unsigned _StackSize, _beginthreadex_proc_type _StartAddress, void* _ArgList, unsigned _InitFlag, unsigned* _ThrdAddr);
DECLSPEC_IMPORT void __cdecl MSVCRT$_endthreadex(unsigned _Retval);
WINBASEAPI DWORD WINAPI KERNEL32$WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
WINBASEAPI BOOL WINAPI KERNEL32$GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode);


DECLSPEC_IMPORT	int		__cdecl MSVCRT$wcscmp(LPCWSTR, LPCWSTR);
DECLSPEC_IMPORT	LPCWSTR	__cdecl	MSVCRT$wcscat(LPWSTR, LPCWSTR);
DECLSPEC_IMPORT	wchar_t *	__cdecl	MSVCRT$wcscpy(wchar_t *strDestination, const wchar_t *strSource);
DECLSPEC_IMPORT int WINAPI KERNEL32$MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
DECLSPEC_IMPORT int WINAPI KERNEL32$WideCharToMultiByte(UINT CodePage, DWORD dwFlags, LPCWSTR lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar);
DECLSPEC_IMPORT BOOL WINAPI KERNEL32$CloseHandle(HANDLE hObject);
DECLSPEC_IMPORT DWORD WINAPI KERNEL32$FormatMessageA(DWORD, LPCVOID, DWORD, DWORD, LPTSTR, DWORD, va_list*);
DECLSPEC_IMPORT HANDLE WINAPI KERNEL32$CreateThread( LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, __drv_aliasesMem LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
DECLSPEC_IMPORT DWORD WINAPI KERNEL32$WaitForSingleObject( HANDLE hHandle, DWORD  dwMilliseconds);
DECLSPEC_IMPORT DWORD WINAPI KERNEL32$WaitForMultipleObjects( DWORD nCount, const HANDLE *lpHandles, BOOL bWaitAll, DWORD dwMilliseconds);
DECLSPEC_IMPORT HANDLE WINAPI KERNEL32$CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName);
DECLSPEC_IMPORT BOOL WINAPI KERNEL32$ReleaseMutex(HANDLE hMutex);
DECLSPEC_IMPORT HLOCAL WINAPI KERNEL32$LocalAlloc(UINT uFlags, SIZE_T uBytes);
DECLSPEC_IMPORT	char *		__cdecl MSVCRT$strcat(char *, const char *);
DECLSPEC_IMPORT	size_t	__cdecl MSVCRT$wcslen(LPCWSTR);
WINBASEAPI size_t __cdecl MSVCRT$mbstowcs(wchar_t *__restrict__ _Dest, const char *__restrict__ _Source, size_t _MaxCount);

WINBASEAPI void *__cdecl MSVCRT$calloc(size_t num, size_t size);
DECLSPEC_IMPORT HGLOBAL KERNEL32$GlobalAlloc(UINT uFlags, SIZE_T dwBytes);
DECLSPEC_IMPORT HGLOBAL KERNEL32$GlobalFree(HGLOBAL hMem);

WINBASEAPI long __cdecl MSVCRT$strtoul(const char *string, char **end_ptr, int base);
WINBASEAPI long __cdecl MSVCRT$strtol(const char *string, char **end_ptr, int base);

DECLSPEC_IMPORT FARPROC WINAPI kernel32$GetProcAddress(HANDLE, CHAR*);
DECLSPEC_IMPORT HANDLE WINAPI kernel32$LoadLibraryA(CHAR*);

WINADVAPI WINBOOL WINAPI ADVAPI32$SetThreadToken(PHANDLE Thread, HANDLE Token);
WINADVAPI WINBOOL WINAPI ADVAPI32$OpenThreadToken(HANDLE ThreadHandle, DWORD DesiredAccess, BOOL OpenAsSelf, PHANDLE TokenHandle);
DECLSPEC_IMPORT HANDLE WINAPI KERNEL32$GetCurrentThread();

#define SetThreadToken ADVAPI32$SetThreadToken
#define OpenThreadToken ADVAPI32$OpenThreadToken
#define GetCurrentThread KERNEL32$GetCurrentThread

#define RtlUnicodeStringToAnsiString NTDLL$RtlUnicodeStringToAnsiString
#define RtlFreeAnsiString NTDLL$RtlFreeAnsiString

#define strtol MSVCRT$strtol
#define strtoul MSVCRT$strtoul
#define calloc MSVCRT$calloc
#define MSVCRT$mbstowcs mbstowcs
#define _vsnprintf MSVCRT$_vsnprintf
#define _snprintf MSVCRT$_snprintf


#ifdef __cplusplus
}
#endif


/* helper macros */

#define malloc(size) KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, size)	/* trustedsec */
#define free(addr) KERNEL32$HeapFree(KERNEL32$GetProcessHeap(), 0, (LPVOID)addr)	/* trustedsec */
#define ZeroMemory(address, size) memset(address, 0, size);


/* ----------------------------------- DEFINITIONS ------------------------------------------*/

/* memory */
#define HeapFree				KERNEL32$HeapFree
#define HeapAlloc				KERNEL32$HeapAlloc
#define HeapReAlloc				KERNEL32$HeapReAlloc
#define memcpy					MSVCRT$memcpy
#define memset					MSVCRT$memset


/* process */
#define GetProcessHeap			KERNEL32$GetProcessHeap
#define CreateProcessWithLogonW ADVAPI32$CreateProcessWithLogonW
#define OpenProcess				KERNEL32$OpenProcess
#define VirtualQueryEx			KERNEL32$VirtualQueryEx
#define GetProcessId			KERNEL32$GetProcessId
#define	ReadProcessMemory		KERNEL32$ReadProcessMemory
#define GetCurrentProcess		KERNEL32$GetCurrentProcess
#define Sleep					KERNEL32$Sleep
#define LookupPrivilegeValueW	ADVAPI32$LookupPrivilegeValueW
#define	GetModuleFileNameExW	PSAPI$GetModuleFileNameExW


/* error */
#define GetLastError			KERNEL32$GetLastError 


/* registry */
#define RegOpenKeyExA			ADVAPI32$RegOpenKeyExA
#define RegOpenKeyExW			ADVAPI32$RegOpenKeyExW
#define RegDeleteTreeA			ADVAPI32$RegDeleteTreeA
#define RegCreateKeyExA			ADVAPI32$RegCreateKeyExA
#define RegCreateKeyExW			ADVAPI32$RegCreateKeyExW
#define RegSetValueExA			ADVAPI32$RegSetValueExA
#define RegSetValueExW			ADVAPI32$RegSetValueExW
#define RegCloseKey				ADVAPI32$RegCloseKey
#define RegConnectRegistryW		ADVAPI32$RegConnectRegistryW


/* strings */
#define strchr					MSVCRT$strchr
#define strcat_s				MSVCRT$strcat_s
#define strcpy					MSVCRT$strcpy
#define strcpy_s				MSVCRT$strcpy_s
#define strncpy_s				MSVCRT$strncpy_s
#define snprintf				MSVCRT$_snprintf	/*beacon can't find snprintf without the preceeding '_' */
#define wcslen					MSVCRT$wcslen
#define vsnprintf				MSVCRT$vsnprintf
#define lstrlenW				KERNEL32$lstrlenW
#define lstrcpyW				KERNEL32$lstrcpyW
#define strcmp					MSVCRT$strcmp
#define lstrcpyA				Kernel32$lstrcpyA
#define	lstrcatA				Kernel32$lstrcatA
#define	lstrcpynA				Kernel32$lstrcpynA
#define lstrcpyW				KERNEL32$lstrcpyW
#define sprintf					MSVCRT$sprintf
#define strlen                  MSVCRT$strlen
#define atoi                    MSVCRT$atoi

#define RpcStringFreeA			Rpcrt4$RpcStringFreeA 
#define UuidCreate				Rpcrt4$UuidCreate
#define UuidToStringA			Rpcrt4$UuidToStringA
#define wcscmp	MSVCRT$wcscmp
#define wcscat	MSVCRT$wcscat
#define wcscpy MSVCRT$wcscpy
#define	MultiByteToWideChar			KERNEL32$MultiByteToWideChar
#define	WideCharToMultiByte			KERNEL32$WideCharToMultiByte
#define CloseHandle KERNEL32$CloseHandle
#define ADsOpenObject ACTIVEDS$ADsOpenObject
#define FormatMessageA KERNEL32$FormatMessageA
#define CreateThread KERNEL32$CreateThread
#define WaitForSingleObject KERNEL32$WaitForSingleObject
#define GetExitCodeThread KERNEL32$GetExitCodeThread
#define WaitForMultipleObjects KERNEL32$WaitForMultipleObjects
#define CreateMutex KERNEL32$CreateMutexA
#define ReleaseMutex KERNEL32$ReleaseMutex
#define LocalAlloc KERNEL32$LocalAlloc

#define RpcExceptionFilter RPCRT4$RpcExceptionFilter
#define RpcStringBindingComposeW RPCRT4$RpcStringBindingComposeW
#define RpcBindingFromStringBindingW RPCRT4$RpcBindingFromStringBindingW
#define RpcBindingSetAuthInfoExW RPCRT4$RpcBindingSetAuthInfoExW
#define RpcBindingFree RPCRT4$RpcBindingFree
#define RpcStringFreeW RPCRT4$RpcStringFreeW
#define NdrClientCall3 RPCRT4$NdrClientCall3
#define AddVectoredExceptionHandler KERNEL32$AddVectoredExceptionHandler
#define RemoveVectoredExceptionHandler KERNEL32$RemoveVectoredExceptionHandler

#define GlobalAlloc KERNEL32$GlobalAlloc 
#define GlobalFree KERNEL32$GlobalFree 
