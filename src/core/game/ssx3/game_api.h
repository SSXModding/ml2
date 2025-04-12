#ifndef GAME_API_H
#define GAME_API_H 

#include <ml/types.h>

extern "C" {
        void cGame_load(void* pGame);
        void cGame_purge(void* pGame);
        void cGame_update(void* pGame);
        void cGame_render(void* pGame);

        void* memset(void* ptr, int c, unsigned int length);
        void* memcpy(void* pDest, const void* pSrc, unsigned int length);
        int strcmp(const char* pszLeft, const char* pszRight);

        void scePrintf(const char* pszFormat, ...);

        void* memAlloc(unsigned int length, const char* name, unsigned flags = 0, unsigned flags2 = 0);
        void memFree(void* ptr);

        class cFont {
        public:
                void text(float x, float y, const char* pszInput);
        };

        struct cGame {
                unsigned char pad[0x24];
                cFont* pDebugFont;
        };

        struct cSSXApplication {
                unsigned char pad[0x84];
                cGame* pGame;
        };

        
        extern cSSXApplication* SSXApp;

        unsigned int BXFILE_size(const char* pszFileName);
        unsigned int FILE_loadat(const char* pszFileName, void* pData, unsigned int maxsize); // returns amount of bytes actually loaded?

        /* REALFILE */
        struct FILESYSOPTS {
                int size;
                void*(*malloc)(u32 size);
                void(*free)(void* ptr);
                int DiscType;
                int MaxPathLength;
                bool IsDiscBootable;
                char* DemoCdRoot;
                char* REAL_filedevice;
                u32 whoever_the_hell_knows_what;
        };

        void FILESYS_getopts(FILESYSOPTS* outOpts);
        void FILESYS_setopts(FILESYSOPTS* inopts);

        /* REALFILE async (aka hell) */
        void ASYNCFILE_setcurrentpath(const char* pszPath);
}

#endif