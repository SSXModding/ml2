// Some notes:
// - We are not bootstrapping. We have a valid $sp, so we can
//   safely write full-fat C code without issues.
// - The code here basically calls rel_main() and returns back
//   so that the core can continue exeuction and bringup.

/// [param] is actually a pointer to a struct which provides the rel
/// useful functions (and an ABI version), but we don't need to know that.
int RelMain(void* param);

/* TODO: these definitions should be in a core and rel shared place. */

/* These are passed by the core's rel loader to tell us
   what it is doing. */
#define REL_COMMAND_LOAD 0 
#define REL_COMMAND_UNLOAD 1

// This struct is shared by the core and the REL crt0
// to tell it things.
typedef struct {
    int command; // see REL_
    int exitCode;
    void* param;
} RelLoaderBlock;

// This function is the entrypoint of all ML2 RELs and papers over the startup
// in an easier fashion. When your REL is loaded, RelMain() will be called.
// If it returns a nonzero value, it will be unloaded.
void RelStartup(RelLoaderBlock* lb) {
    switch(lb->command) {
        case REL_COMMAND_LOAD:
            // TODO __do_global_ctors();
            lb->exitCode = RelMain(lb->param);
            // if lb->exitCode is != 0 then the core loader will respond
            // by immediately unloading.
            break;
        case REL_COMMAND_UNLOAD:
            // TODO: run global dtors and atexit()
            // (if I ever gain the spoons to implement a full libc)
            break;
    }

    return;
}