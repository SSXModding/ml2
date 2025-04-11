// TEST CODE
#include <ml/sio.h>

#include "game_api.h"
#include "ml/mod.hpp"


void mlGameInit() {
	sioPuts("mlGameInit() called");

	mlMod* pMod = mlModGetById("test");
	if(pMod) {
		scePrintf("Enabling test mod\n");
		pMod->enable();
	}
}

