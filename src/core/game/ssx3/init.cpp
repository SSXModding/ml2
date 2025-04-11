// TEST CODE
#include <ml/sio.h>

#include "game_api.h"
#include "ml/mod.hpp"


void mlGameInit() {
	sioPuts("mlGameInit() called");

	// do some testing
	if(mlFindMod("test") != 0) {
		sioPuts("found test mod");
	} else {
		sioPuts(":( couldn't find test mod");
	}
}

