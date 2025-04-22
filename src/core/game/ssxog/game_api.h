#ifndef GAME_API_H
#define GAME_API_H 

#include <ml/types.h>

extern "C" {
        void* memset(void* ptr, int c, unsigned int length);
        void* memcpy(void* pDest, const void* pSrc, unsigned int length);
        int strcmp(const char* pszLeft, const char* pszRight);

        void scePrintf(const char* pszFormat, ...);

        // FIXME: Everything below here should actually have C++ linkage
        // and their actual names

        void* MEM_alloc(const char* pszIdentifier, u32 size, u32 flags = 0);
        void MEM_free(void* ptr);
        
}

// Include piecemeal headers
// (they are not yet intended to be included individually)
#include "gameapi/execman.h"
#include "gameapi/menu.h"
#include "gameapi/game.h"

#endif