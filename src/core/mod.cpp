#include <ml/mod.hpp>
#include <ml/sio.h>

// Returns a typed null pointer.
#define nil(T) (T)0

// 
static mlMod* modListHead = nil(mlMod*);

// Returns true if both strings are equal and the same length.
bool strEqual(const char* pszLeft, const char* pszRight) {
    const char* pLeftIter = pszLeft;
    const char* pRightIter = pszRight;
    while(*pLeftIter && *pRightIter) {
        if(*pLeftIter != *pRightIter) {
            return false;
        }

        pLeftIter++;
        pRightIter++;
    }

    if(*pLeftIter == '\0' && *pRightIter != '\0')
        return false;
    
    if(*pRightIter == '\0' && *pLeftIter != '\0')
        return false;

    return true;
}

void mlRegisterMod(mlMod* pMod) {
    sioPuts("registering mod: ");
    sioPuts(pMod->getId());

    // TODO
    if(modListHead == nil(mlMod*)) {
        modListHead = pMod;
        return;
    }

    mlMod* pIter = modListHead;
    while(pIter->pNextMod != nil(mlMod*)) {
        pIter = pIter->pNextMod;
    }

    pIter->pNextMod = pMod;
}

void mlModForEach(bool(*pcbCallback)(mlMod* pMod, void* context), void* context) {
    if(!modListHead)
        return;

    // Walk the list of registered mods to try to find
    // the mod by ID.
    mlMod* pIter = modListHead;
    while(pIter->pNextMod != nil(mlMod*)) {
        // The callback can return false to end iteration.
        if(!pcbCallback(pIter, context))
            break;
        pIter = pIter->pNextMod;
    }
}

mlMod* mlFindMod(const char* pszModId) {
    // No mods are registered. We can't really find
    // something from nothing, so just return nil
    if(!modListHead)
        return nil(mlMod*);

    // Walk the list of registered mods to try to find
    // the mod by ID.
    mlMod* pIter = modListHead;
    while(pIter->pNextMod != nil(mlMod*)) {
        if(strEqual(pszModId, pIter->getId()))
            return pIter;

        pIter = pIter->pNextMod;
    }

    return nil(mlMod*);
}