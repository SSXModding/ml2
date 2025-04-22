#include <ml/types.h>

#include "ghidratypes.h"

class cGame;
class cFrontend3D;
class cLoadMan;
class cBezierManager;

typedef enum eLanguage {
	LANG_ENG = 0,
	LANG_JA = 1,
	LANG_DE = 2,
	LANG_FR = 3
} eLanguage;

typedef enum eVenueId { // enum for venue
	kVenue_Snow = 0,
	kVenue_Mesa = 1,
	kVenue_Rambl = 2,
	kVenue_Pipe = 3,
	kVenue_Megapl = 4,
	kVenue_Elys = 5,
	kVenue_AlohaIce = 6,
	kVenue_BigAd = 7,
	kVenue_Merq = 8,
	kVenue_Untr = 9,
	kVenue_Warm = 10,
	kVenue_FE3D = -1
} eVenueId;

struct cVenueManager_ListEntry {
	char mBigName[64];
	char mAltName[64];
	eVenueId mVenueID;
};

class cVenueManager {
   public:
	int venueCount;
	struct cVenueManager_ListEntry venues[12];
	int mUnk;
};

class cApplication {
   public:
	// data

	undefined4 mVBlankIntcHandler;
	void* locale2;
	int localeSize;
	char* mExe;
	enum eLanguage LocaleLanguage;
	struct cVenueManager mVenueManager;
	undefined field6_0x64c;
	undefined field7_0x64d;
	undefined field8_0x64e;
	undefined field9_0x64f;
	undefined field10_0x650;
	undefined field11_0x651;
	undefined field12_0x652;
	undefined field13_0x653;
	undefined field14_0x654;
	undefined field15_0x655;
	undefined field16_0x656;
	undefined field17_0x657;
	undefined field18_0x658;
	undefined field19_0x659;
	undefined field20_0x65a;
	undefined field21_0x65b;
	undefined field22_0x65c;
	undefined field23_0x65d;
	undefined field24_0x65e;
	undefined field25_0x65f;
	undefined field26_0x660;
	undefined field27_0x661;
	undefined field28_0x662;
	undefined field29_0x663;
	undefined field30_0x664;
	undefined field31_0x665;
	undefined field32_0x666;
	undefined field33_0x667;
	undefined field34_0x668;
	undefined field35_0x669;
	undefined field36_0x66a;
	undefined field37_0x66b;
	undefined field38_0x66c;
	undefined field39_0x66d;
	undefined field40_0x66e;
	undefined field41_0x66f;
	undefined field42_0x670;
	undefined field43_0x671;
	undefined field44_0x672;
	undefined field45_0x673;
	undefined field46_0x674;
	undefined field47_0x675;
	undefined field48_0x676;
	undefined field49_0x677;
	undefined field50_0x678;
	undefined field51_0x679;
	undefined field52_0x67a;
	undefined field53_0x67b;
	undefined field54_0x67c;
	undefined field55_0x67d;
	undefined field56_0x67e;
	undefined field57_0x67f;
	undefined field58_0x680;
	undefined field59_0x681;
	undefined field60_0x682;
	undefined field61_0x683;
	undefined field62_0x684;
	undefined field63_0x685;
	undefined field64_0x686;
	undefined field65_0x687;
	undefined field66_0x688;
	undefined field67_0x689;
	undefined field68_0x68a;
	undefined field69_0x68b;
	undefined field70_0x68c;
	undefined field71_0x68d;
	undefined field72_0x68e;
	undefined field73_0x68f;
	undefined field74_0x690;
	undefined field75_0x691;
	undefined field76_0x692;
	undefined field77_0x693;
	undefined field78_0x694;
	undefined field79_0x695;
	undefined field80_0x696;
	undefined field81_0x697;
	undefined field82_0x698;
	undefined field83_0x699;
	undefined field84_0x69a;
	undefined field85_0x69b;
	undefined field86_0x69c;
	undefined field87_0x69d;
	undefined field88_0x69e;
	undefined field89_0x69f;
	undefined field90_0x6a0;
	undefined field91_0x6a1;
	undefined field92_0x6a2;
	undefined field93_0x6a3;
	undefined field94_0x6a4;
	undefined field95_0x6a5;
	undefined field96_0x6a6;
	undefined field97_0x6a7;
	undefined field98_0x6a8;
	undefined field99_0x6a9;
	undefined field100_0x6aa;
	undefined field101_0x6ab;
	undefined field102_0x6ac;
	undefined field103_0x6ad;
	undefined field104_0x6ae;
	undefined field105_0x6af;
	undefined field106_0x6b0;
	undefined field107_0x6b1;
	undefined field108_0x6b2;
	undefined field109_0x6b3;
	undefined field110_0x6b4;
	undefined field111_0x6b5;
	undefined field112_0x6b6;
	undefined field113_0x6b7;
	undefined field114_0x6b8;
	undefined field115_0x6b9;
	undefined field116_0x6ba;
	undefined field117_0x6bb;
	undefined field118_0x6bc;
	undefined field119_0x6bd;
	undefined field120_0x6be;
	undefined field121_0x6bf;
	undefined field122_0x6c0;
	undefined field123_0x6c1;
	undefined field124_0x6c2;
	undefined field125_0x6c3;
	undefined field126_0x6c4;
	undefined field127_0x6c5;
	undefined field128_0x6c6;
	undefined field129_0x6c7;
	undefined field130_0x6c8;
	undefined field131_0x6c9;
	undefined field132_0x6ca;
	undefined field133_0x6cb;
	undefined field134_0x6cc;
	undefined field135_0x6cd;
	undefined field136_0x6ce;
	undefined field137_0x6cf;
	undefined field138_0x6d0;
	undefined field139_0x6d1;
	undefined field140_0x6d2;
	undefined field141_0x6d3;
	int mVenueBigHandle; // Created by retype action
	cBezierManager* mBezMan;
	u32 mFramesRendered; // could be amount of vblank'd frames
	float mGameRate;
	float mDeltaTime;
	undefined4 mShouldFlushCache;
	cGame* mGame;
	cFrontend3D* mFrontend;
	cLoadMan* mCurrLoadMan; // The current load manager. Set in cApplication::Run
	undefined4 field151_0x6f8;
	char mBuildNameString[64];
	u32 field153_0x73c;
	u32 field154_0x740;
	u32 field155_0x744;
	u32 field156_0x748;
	u32 field157_0x74c;
	u32 field158_0x750;
	u32 field159_0x754;
	u32 field160_0x758;
	u32 field161_0x75c;
	u32 field162_0x760;
	u32 field163_0x764;
	u32 field164_0x768;
	u32 field165_0x76c;
	u32 field166_0x770;
	u32 field167_0x774;
	u32 field168_0x778;
	u32 field169_0x77c;
	u32 field170_0x780;
	u32 mShowFPSDisplay;

};

class cExecutionMan {
public:
	// memfns we care about
	u32 getActiveJoypadInput(u32* pInputs);
};

extern cExecutionMan ExecMan;
extern cApplication TheApp;