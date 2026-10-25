#ifndef __MENUS_TEXT_71EC4_H_
#define __MENUS_TEXT_71EC4_H_

#include "mssbTypes.h"
#include "Unknown/File_0x800b0a14.h"

// One of the eight character-select slots, stored back to back at
// lbl_2_bss_1A8248 + 0x1610 (stride 0xD8).
typedef struct CssSlot {
    /* 0x00 */ u8 _00[0x80];
    /* 0x80 */ s32 index;
    /* 0x84 */ u8 _84[0x94 - 0x84];
    /* 0x94 */ s16 mode;        // dispatch index into lbl_2_data_2A1E8
    /* 0x96 */ u8 _96[0xB4 - 0x96];
    /* 0xB4 */ s16 _B4;
    /* 0xB6 */ u8 _B6[0xC0 - 0xB6];
    /* 0xC0 */ u8 _C0;
    /* 0xC1 */ u8 _C1[0xC3 - 0xC1];
    /* 0xC3 */ u8 state;        // dispatch index into lbl_2_data_2A2EC
    /* 0xC4 */ u8 _C4[0xD4 - 0xC4];
    /* 0xD4 */ void (*handler)(struct CssSlot *slot);
} CssSlot; // size 0xD8

void fn_2_71EC4(CssSlot *slot);
void fn_2_71EFC(CssSlot *slot);
void fn_2_71F20(CssSlot *slot);
void fn_2_71F60(void);
void fn_2_72038(int index, s16 value);
void fn_2_72054(int index, u8 state);
void fn_2_7207C(void);
void fn_2_72594(void);
void fn_2_72630(void);
void cssCheckSomethingAboutCharacters(void);
void fn_2_72814(void *scene);
void fn_2_728C0(void *scene);
void fn_2_7293C(void *scene);
void fn_2_729E0(void *scene);
void fn_2_72A58(void);
void fn_2_72A88(void *scene);
void fn_2_72CB4(void *scene);
void fn_2_72D60(void *scene);
void fn_2_72DDC(void *scene);
void fn_2_72E54(void *scene);
void fn_2_73028(void);
int fn_2_7302C(void);
void fn_2_7308C(void);
void fn_2_73758(void);
void fn_2_738C8(void);
void fn_2_73994(DrawingSceneStruct *node, int idx);
int fn_2_73B54(int x);
int fn_2_73B94(int x);
int fn_2_73BF0(int x);
void fn_2_73CBC(DrawingSceneStruct *node);
void fn_2_73EFC(void);

#endif // !__MENUS_TEXT_71EC4_H_
