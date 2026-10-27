#ifndef __UNUSED_REL_REP_02A8_H_
#define __UNUSED_REL_REP_02A8_H_

#include "mssbTypes.h"

typedef enum ScrollDir {
    SCROLL_UP,
    SCROLL_DOWN,
    SCROLL_PAGE_UP,
    SCROLL_PAGE_DOWN
} ScrollDir;

typedef struct ScrollListEntry {
    /*0x00*/ const char *text;
    /*0x04*/ u8 pad04[0xC];
} ScrollListEntry; // size 0x10

typedef struct ScrollList {
    /*0x00*/ ScrollListEntry *items;
    /*0x04*/ s32 cursor;
    /*0x08*/ s32 top;
    /*0x0C*/ s32 visible;
    /*0x10*/ s32 total;
} ScrollList; // size 0x14

void fn_1_9EA0(s32 fileIndex, s32 (*pushCallback)());
void fn_1_9F04(void);
void fn_1_A024(ScrollList *list, ScrollDir dir);
void fn_1_A184(ScrollList *list);
void fn_1_A1F4(ScrollList *list, ScrollListEntry *items, s32 total, s32 visible);
char *fn_1_A210(char *path);
void fn_1_A250(void);
void fn_1_C2A4(void);
void fn_1_A2E4(void);
void sndTestTopScreen(void);
void sndTestTrainingSeScreen(void);
void fn_1_A634(void);
void fn_1_A714(void);
s32 fn_1_A718(void);
s32 fn_1_A77C(void);
s32 fn_1_A7B0(void);
s32 fn_1_A7E4(void);
s32 fn_1_A838(void);
s32 fn_1_A880(void);
s32 fn_1_A8B4(void);
s32 fn_1_A908(void);
void fn_1_A95C(void);
void fn_1_B4A4(void);
void sndTestSeScreen(void);
void fn_1_BA64(void);
void sndTestVoice2Screen(void);
void fn_1_BDD8(void);
void fn_1_BEF4(s16 voice);
s32 fn_1_BF34(s16 fxid);
void sndTestVoiceScreen(void);
void fn_1_C188(void);

#endif // !__UNUSED_REL_REP_02A8_H_
