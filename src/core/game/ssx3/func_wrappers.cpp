// This file provides hooks that the ml core uses
// to perform certain functions

#include <ml/types.h>

#include "game_api.h"

extern "C" {

void* mlMalloc(u32 size) {
	return memAlloc(size, "riri!", 0, 0);
}

void mlFree(void* pMemory) {
	if(pMemory)
		memFree(pMemory);
}

void mlMemSet(void* pBuffer, int c, u32 len) {
	memset(pBuffer, c, len);
}

void mlMemCpy(void* pDestBuffer, const void* pSrcBuffer, u32 copyLen) {
	memcpy(pDestBuffer, pSrcBuffer, copyLen);
}

void* mlLoadFile(const char* pszFileName) {
	u32 uiRel0Size = BXFILE_size(pszFileName);
	if(uiRel0Size != 0) {
		u8* pData = (unsigned char*)mlMalloc(uiRel0Size);
		FILE_loadat(pszFileName, &pData[0], uiRel0Size);
		return (void*)pData;
	}
	return (void*)0;
}
}