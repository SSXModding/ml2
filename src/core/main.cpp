#include <ml/sio.h>
#include <ml/game.h>

extern "C" void __do_global_ctors();

// Initalizes the ml core.
// This shoulc be called once by hooking an appropiate game function.
extern "C" void mlStart() {
    __do_global_ctors();
    sioPuts("ML2 prototype - modeco80");
    mlGameInit();
}