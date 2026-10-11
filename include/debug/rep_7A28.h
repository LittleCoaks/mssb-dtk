#ifndef __UNUSED_REL_REP_7A28_H_
#define __UNUSED_REL_REP_7A28_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct DbgMenuItem {
    u32 unk0;
    u32 label;
    u8 pad8[0x2C - 0x8];
} DbgMenuItem;

typedef struct DbgMenu {
    const char *title;
    s32 cursor;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    DbgMenuItem *items;
} DbgMenu;

typedef struct DbgTexEntry {
    void *tex;
    s32 fmt;
    u8 pad8[0x50 - 0x8];
} DbgTexEntry;

/* View of the drawing-script node used by this debug scene. */
typedef struct DbgScene {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ struct DbgScene *prev;
    /* 0x08 */ struct DbgScene *next;
    /* 0x0C */ struct DbgScene *parent;
    /* 0x10 */ s16 state;
    /* 0x12 */ u16 priority;
    /* 0x14 */ f32 (*mtx)[4];
    /* 0x18 */ void *tex;
    /* 0x1C */ DbgMenu *menu;
    /* 0x20 */ Vec pos;
    /* 0x2C */ f32 radius;
    /* 0x30 */ f32 scale;
    /* 0x34 */ u16 flags;
    /* 0x36 */ s8 mode;
    /* 0x37 */ s8 field;
} DbgScene;

void fn_1_27560(void *tex);
void fn_1_27594(void);
void fn_1_276CC(void);
void fn_1_27AD0(void);
void fn_1_27AD4(void);
void fn_1_27BB8(void);
void fn_1_27D6C(void);
void fn_1_27E50(void);
void fn_1_27E98(void);
void fn_1_28118(void);
void fn_1_28200(void);

#endif // !__UNUSED_REL_REP_7A28_H_
