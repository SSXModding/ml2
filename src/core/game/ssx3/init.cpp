// TEST CODE
#include <ml/sio.h>

#include "game_api.h"

cFont* getDebugFont() {
	cGame* game = SSXApp->pGame;
	return game->pDebugFont;
}

void cGame_renderHook(void* pGame) {
	getDebugFont()->text(30., 30., "Hello World!");
	cGame_render(pGame);
}

void mlGameInit() {
	// As a test, vtable hook cGame::render() :3
	*((void**)0x0047d14c) = (void*)cGame_renderHook;
}