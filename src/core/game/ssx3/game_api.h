#ifndef GAME_API_H
#define GAME_API_H 

extern "C" {
        void cGame_load(void* pGame);
        void cGame_purge(void* pGame);
        void cGame_update(void* pGame);
        void cGame_render(void* pGame);

        void* memset(void* ptr, int c, unsigned int length);
        void* memcpy(void* pDest, const void* pSrc, unsigned int length);

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

#ifndef REL
        extern cSSXApplication* SSXApp;
#else
        #define SSXApp ((cSSXApplication*)0x004a28a8)
#endif

        unsigned int BXFILE_size(const char* pszFileName);
        unsigned int FILE_loadat(const char* pszFileName, void* pData, unsigned int maxsize); // returns amount of bytes actually loaded?
}

#endif