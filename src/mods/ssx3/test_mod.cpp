#include <ml/mod.hpp>
#include <ml/game.h>
#include "game_api.h"


#include <ml/vthook.h>

cFont* getDebugFont() {
	cGame* game = SSXApp->pGame;
	return game->pDebugFont;
}

mlVTHookMan0<void, void> cGame_Render_vthook;

void cGame_renderHook(void* pGame) {
    mlVTHookMan0<void*, void>::ResultType res = cGame_Render_vthook.Call(pGame);
    if(res.code == kVtHook_RunOriginal) {
	    cGame_render(pGame);
    }
}



#if VERSION(us)
    #define CGAME_RENDER_VPTR_ADDRESS 0x0047d14c
#endif

mlVtHookResult<void> myTestHook(void* pGame) {
	getDebugFont()->text(30., 120., "Hello World!");
    return mlVtHookResult<void>(kVtHook_RunOriginal);
}

mlVtHookResult<void> myTestHook2(void* pGame) {
	getDebugFont()->text(30., 140., "Hello World! (from another hook function)");
    return mlVtHookResult<void>(kVtHook_RunOriginal);
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
	    *((void**)CGAME_RENDER_VPTR_ADDRESS) = (void*)cGame_renderHook;

        cGame_Render_vthook.RegisterHook(&myTestHook);
        cGame_Render_vthook.RegisterHook(&myTestHook2);
    }

    virtual void disable() {
	    //*((void**)CGAME_RENDER_VPTR_ADDRESS) = (void*)cGame_render;
    }
};

ML_REGISTER_MOD(testMod);