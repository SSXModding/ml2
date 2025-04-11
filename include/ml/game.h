#ifndef ML_GAME_H
#define ML_GAME_H

#ifndef __cplusplus
	#error C++ only
#endif

// These allow, for instance #if GAME(ssx3)
#define GAME(game) GAME_##game == 1
#define VERSION(version) VERSION_##version == 1

// Initalizes game-specific code/hooks.
void mlGameInit();

#endif