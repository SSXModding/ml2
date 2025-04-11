#include <ml/libc_wrappers.h>
#include <ml/sio.h>

#include <ml/mod.hpp>

// The head of the mod intrusive linked list.
static mlMod* modListHead = nil(mlMod*);

// Returns true if both strings are equal and the same length.
bool strEqual(const char* pszLeft, const char* pszRight) {
	return !mlStrCmp(pszLeft, pszRight);
}

void mlModRegister(mlMod* pMod) {
	if(modListHead == nil(mlMod*)) {
		modListHead = pMod;
		return;
	}

    // Find the mod which doesn't have a set next mod pointer 
    // and add this mod to it.
	mlMod* pIter = modListHead;
	while(pIter != nil(mlMod*)) {
		pIter = pIter->pNextMod;
	}

	pIter->pNextMod = pMod;
}

void mlModForEach(bool (*pcbCallback)(mlMod* pMod, void* context), void* context) {
	if(!modListHead)
		return;

	// Walk the list of registered mods to try to find
	// the mod by ID.
	mlMod* pIter = modListHead;
	while(pIter != nil(mlMod*)) {
		// The callback can return false to end iteration.
		if(!pcbCallback(pIter, context))
			break;
		pIter = pIter->pNextMod;
	}
}

// Callback/bootleg "lambda" for mlFindMod
struct findModContext {
	const char* pszModId;
	mlMod* mod;

	findModContext(const char* pszModId)
		: pszModId(pszModId) {
		mod = nil(mlMod*);
	}

	bool operator()(mlMod* pMod) {
		if(strEqual(pszModId, pMod->getId())) {
			mod = pMod;
			// Stop iteration
			return false;
		}
		return true;
	}

	static bool call(mlMod* pMod, void* ctx) {
		return ((findModContext*)ctx)->operator()(pMod);
	}
};

mlMod* mlModGetById(const char* pszModId) {
	// No mods are registered. We can't really find
	// something from nothing, so just return nil
	if(modListHead == nil(mlMod*))
		return nil(mlMod*);

	findModContext ctx(pszModId);
	mlModForEach(&findModContext::call, &ctx);
	return ctx.mod;
}