// This file provides hooks that the ml core uses
// to provide certain C library functions to the mlcore.

extern "C" {


void* mlMalloc(u32 size) {
	return 0;
}

void mlFree(void* pMemory) {
	return;
}

void mlMemSet(void* pBuffer, int c, u32 len) {
	return;
}

void mlMemCpy(void* pDestBuffer, const void* pSrcBuffer, u32 copyLen) {
	return;
}

void* mlLoadFile(const char* pszFileName) {
    return 0;
}

}