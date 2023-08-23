#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <rpc.h>
#include "bofdefs.h"

void __RPC_FAR* __RPC_API midl_user_allocate(size_t cBytes);
void __RPC_API midl_user_free(void __RPC_FAR* p);

void __RPC_FAR* __RPC_API midl_user_allocate(size_t cBytes)
{
	return ((void __RPC_FAR*) malloc(cBytes));
}

void __RPC_API midl_user_free(void __RPC_FAR* p)
{
	free(p);
}
