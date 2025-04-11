#include <ml/mod.hpp>
#include "game_api.h"

cFont* getDebugFont() {
	cGame* game = SSXApp->pGame;
	return game->pDebugFont;
}

void cGame_renderHook(void* pGame) {
	getDebugFont()->text(30., 120., "Hello World!");
	cGame_render(pGame);
}

struct testMod : public mlMod {
    virtual const mlModMeta& getMeta() const {
        static mlModMeta meta =  {
            "modeco80",
            "Test Mod"
        };
        return meta;
    }
    
    virtual const char* getId() const { return "test"; }

    virtual void enable() {
	    *((void**)0x0047d14c) = (void*)cGame_renderHook;
    }

    virtual void disable() {
	    *((void**)0x0047d14c) = (void*)cGame_render;
    }
};

ML_REGISTER_MOD(testMod);