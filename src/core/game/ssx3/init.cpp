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

	FILESYSOPTS opts;
	FILESYS_getopts(&opts);

	// dump the structure bro
	scePrintf("Opts:\n");
	scePrintf("Size: %d\n", opts.size);
	scePrintf("DiscType: %d\n", opts.DiscType);
	scePrintf("MaxPathLength: %d\n", opts.MaxPathLength);
	scePrintf("IsDiscBootable: %s\n", opts.IsDiscBootable ? "yes" : "HELL no sir. hell no");
	scePrintf("DemoCdRoot: %s\n", opts.DemoCdRoot);
	scePrintf("REAL_filedevice: %s\n", opts.REAL_filedevice);
	scePrintf("????????: %d (0x%08x)\n", opts.whoever_the_hell_knows_what, opts.whoever_the_hell_knows_what);
}