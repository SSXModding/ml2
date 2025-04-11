// TEST CODE
#include <ml/sio.h>

#include "game_api.h"
#include "ml/mod.hpp"


void mlGameInit() {
	sioPuts("mlGameInit() called");

	// do some testing
	mlFindMod("test")->enable();
}

