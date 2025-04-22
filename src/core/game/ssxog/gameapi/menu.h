#include <ml/types.h>

// opaque 4 now
class cMenu {
    u8 pad[0x114];
};

class cMenuSys {
public:
    u32 MenuDepth;
    cMenu* MenuStack[9];

    void activate(u32 activateFlag);
    void pushMenu(cMenu* menu);
    void popMenu();
};

extern cMenuSys TheMenuSys;

// debug menu
class cDebugMenu : cMenu {};