#ifndef ML_ALLOCATOR_HPP
#define ML_ALLOCATOR_HPP

#include <ml/libc_wrappers.h>

/// A standard allocator
template<class T>
struct mlStdAllocator {
    template<class U>
    struct Rebind { typedef mlStdAllocator<U> Type; };

    static T* allocateArray(usize count) {
        return new T[count];
    }

    static void deallocateArray(T* pArray, usize count) {
        static_cast<void>(count); // Not used, but can be used in implementations
                                  // that (for some reason) choose to not use new[]
        delete[] pArray;
    }

    static T* allocateOne() {
        return new T;
    }

    static void deallocateOne(T* pObj) {
        delete pObj;
    }

};

#endif