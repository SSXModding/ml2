#ifndef ML_FUNCS_H
#define ML_FUNCS_H

#include <ml/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* These functions proxy libc from the injected game binary
    so we do not need to reimplement them (and also can work with
    games that choose to reimplement a memory allocator). Fancy! */

void* mlMalloc(u32 size);
void mlFree(void* pMemory);
void mlMemSet(void* pBuffer, int c, u32 len);
void mlMemCpy(void* pDestBuffer, const void* pSrcBuffer, u32 copyLen);

// Can be implemented by hand with SCE FIO if desired.
void* mlLoadFile(const char* pszFileName);

#ifdef __cplusplus
}
#endif

#endif
