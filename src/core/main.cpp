#include <ml/sio.h>
#include <ml/game.h>

// Initalizes the ml core.
// This shoulc be called once by hooking an appropiate game function.
extern "C" void mlStart() {
    sioPuts("ML2 prototype - modeco80");
    mlGameInit();
}