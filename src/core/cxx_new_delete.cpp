#include <ml/types.h>
#include <ml/libc_wrappers.h>

#include <new>

void* operator new(usize len) {
    return mlMalloc(len);
}

void operator delete(void* ptr) {
    return mlFree(ptr);
}

void* operator new[](usize len) {
    return mlMalloc(len);
}

void operator delete[](void* ptr) {
    return mlFree(ptr);
}