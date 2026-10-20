#ifndef __MENUS_TEXT_92394_H_
#define __MENUS_TEXT_92394_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct Text92394Entry Text92394Entry;

typedef void (*Text92394Fn)(Text92394Entry *entry);

// Entry in the array at lbl_2_bss_1A8248 + 0x21E0, stride 0xBC.
struct Text92394Entry {
    /* 0x00 */ u8 _pad0[0x78];
    /* 0x78 */ s32 slot;
    /* 0x7C */ u8 _pad1[0x90 - 0x7C];
    /* 0x90 */ s16 state;
    /* 0x92 */ u8 _pad2[0xA6 - 0x92];
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ u8 _pad3[0xAB - 0xA8];
    /* 0xAB */ u8 unkAB;
    /* 0xAC */ u8 _pad4[0xB8 - 0xAC];
    /* 0xB8 */ Text92394Fn unkB8;
}; // size 0xBC

void fn_2_92394(Text92394Entry *entry);
void fn_2_923CC(Text92394Entry *entry);
void fn_2_923D8(Text92394Entry *entry);
void fn_2_923E4(Text92394Entry *entry);
void fn_2_9246C(Text92394Entry *entry);
void fn_2_924A4(Text92394Entry *entry);
void fn_2_924B0(Text92394Entry *entry);
void fn_2_92504(Text92394Entry *entry);
void fn_2_9253C(Text92394Entry *entry);
void fn_2_9257C(void);
void fn_2_92654(s32 slot, u8 value);
void fn_2_9267C(Vec *out, Vec *a, Vec *b, Vec *c, f32 t, f32 kA, f32 kB, f32 kC);

#endif // !__MENUS_TEXT_92394_H_
