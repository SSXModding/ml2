#include <ml/mod.hpp>
#include <ml/game.h>
#include <ml/sio.h>
#include "game_api.h"

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
        TheApp.mShowFPSDisplay = 1;
	    sioPuts("Test mod enabled!!! yay >w<\n");
    }

    virtual void disable() {
        TheApp.mShowFPSDisplay = 0;
    }
};

ML_REGISTER_MOD(testMod);