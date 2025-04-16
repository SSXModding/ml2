// This file provides hooks that the ml core uses
// to perform certain functions

#include <ml/types.h>
#include <ml/sio.h>

#include "game_api.h"

extern "C" {

void* mlMalloc(u32 size) {
	return MEM_alloc("Riri~", size, 0);
}

void mlFree(void* pMemory) {
	if(pMemory)
		MEM_free(pMemory);
}

void mlMemSet(void* pBuffer, int c, u32 len) {
	memset(pBuffer, c, len);
}

void mlMemCpy(void* pDestBuffer, const void* pSrcBuffer, u32 copyLen) {
	memcpy(pDestBuffer, pSrcBuffer, copyLen);
}

i32 mlStrCmp(const char *pszLeft, const char *pszRight) {
	return strcmp(pszLeft, pszRight);
}

void* mlLoadFile(const char* pszFileName) {
	/* Not implemented for now */
	sioPuts("Warning: mlLoadFile() not implemented for this port\n");
	return (void*)0;
}
}