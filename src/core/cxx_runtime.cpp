#include <ml/sio.h>
#include <ml/types.h>

// This provides implementation of some GCC C/C++
// runtime stuff that's needed, *without* dragging in
// libgcc, since that requires a lot of libc to also be
// dragged in (and we don't want that!).

extern "C" {
    void __pure_virtual() {
        sioPuts("ML Error: Pure virtual function called in ml2");
        sioPuts("Aborting here");
        while(true);
    }

    typedef void(*vfunc)();

    // Global constructors
    extern vfunc __CTOR_LIST__[];

    void __do_global_ctors() {
        u32 nrPtrs = (u32)__CTOR_LIST__[0];

        // A -1 value means that we need to size the list ourselves.
        // Do so.
        if(nrPtrs == (u32)0xffffffff) {
            for(nrPtrs = 0; __CTOR_LIST__[nrPtrs + 1] != 0; nrPtrs++);
        }

        // Call constructors in reverse order.
        for(u32 i = nrPtrs; i >= 1; i--) {
            __CTOR_LIST__[i]();
        }
    }
}