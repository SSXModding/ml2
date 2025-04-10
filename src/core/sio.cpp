#include <ml/types.h>

extern "C" {

    void sioPutc(char c) {
        *((i8*)0x1000f180) = c;
    }

    void sioPuts(const char* pszIn) {
        // code golf is fun for the whole family
        while(*pszIn)
            sioPutc(*pszIn++);
        // act like real libc puts() and add a newline
        sioPutc('\n');
    }

}