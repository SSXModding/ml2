// This file provides hooks that the ml core uses
// to perform certain functions

#include <ml/types.h>

#include "game_api.h"
#include "ml/libc_wrappers.h"

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

i32 mlStrCmp(const char *pszLeft, const char *pszRight) {
	return strcmp(pszLeft, pszRight);
}

void* mlLoadFile(const char* pszFileName) {
	// fun fact: this code techinically mirrors the same pattern
	// that cFileParser::cFileParser() uses. but it works so hey
	u32 uiFileSize = BXFILE_size(pszFileName);
	if(uiFileSize != 0) {
		u8* pData = (unsigned char*)mlMalloc(uiFileSize);
		FILE_loadat(pszFileName, &pData[0], uiFileSize);
		return (void*)pData;
	}
	return (void*)0;
}
}