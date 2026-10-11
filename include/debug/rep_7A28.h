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

/* Particle emitter settings; fields from num on are edited through the
   debug menu, whose item labels give the names. */
typedef struct DbgTexEntry {
    /* 0x00 */ void *tex;
    /* 0x04 */ s32 fmt;
    /* 0x08 */ s32 num;
    /* 0x0C */ s32 size;
    /* 0x10 */ s32 speed;
    /* 0x14 */ s32 slowdown;
    /* 0x18 */ s32 life;
    /* 0x1C */ s32 lifeTurn;
    /* 0x20 */ s32 scaleUp;
    /* 0x24 */ s32 scaleDown;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 maxAlpha;
    /* 0x30 */ s32 spAngle;
    /* 0x34 */ s32 hAngMax;
    /* 0x38 */ s32 vAngMin;
    /* 0x3C */ s32 vAngMax;
    /* 0x40 */ u32 color;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 bias;
    /* 0x4C */ s32 unk4C;
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
