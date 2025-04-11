#include <ml/mod.hpp>
#include <ml/game.h>
#include "game_api.h"

cFont* getDebugFont() {
	cGame* game = SSXApp->pGame;
	return game->pDebugFont;
}

void cGame_renderHook(void* pGame) {
	getDebugFont()->text(30., 120., "Hello World!");
	cGame_render(pGame);
}

#if VERSION(us)
    #define CGAME_RENDER_VPTR_ADDRESS 0x0047d14c
#endif

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
	    *((void**)CGAME_RENDER_VPTR_ADDRESS) = (void*)cGame_renderHook;
    }

    virtual void disable() {
	    *((void**)CGAME_RENDER_VPTR_ADDRESS) = (void*)cGame_render;
    }
};

ML_REGISTER_MOD(testMod);