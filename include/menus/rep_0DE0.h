#ifndef __MENUS_REP_0DE0_H_
#define __MENUS_REP_0DE0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct {
    /* 0x00 */ void (*unk0)(s32);
    /* 0x04 */ Vec pos;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 _pad0[0x26 - 0x1C];
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 _pad1;
} Rep0DERec28; // size 0x28

typedef struct {
    /* 0x0000 */ u8 _pad0[0x68];
    /* 0x0068 */ void *unk68;
    /* 0x006C */ u8 _pad1[0xAC - 0x6C];
    /* 0x00AC */ void *unkAC[4];
    /* 0x00BC */ u8 _pad2[0x2D94 - 0xBC];
    /* 0x2D94 */ Rep0DERec28 *unk2D94;
    /* 0x2D98 */ u8 _pad3[0x3078 - 0x2D98];
    /* 0x3078 */ u16 unk3078;
    /* 0x307A */ u8 unk307A;
} Rep0DEState;

typedef struct {
    /* 0x00 */ Mtx mtx;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ Vec unk3C;
    /* 0x48 */ Vec unk48;
    /* 0x54 */ s32 unk54;
} Rep0DEMtxBlock; // size 0x5C

extern Rep0DEState *lbl_2_bss_340140;
extern Rep0DEMtxBlock lbl_2_bss_1A81D4;
extern Rep0DEState hugeAnimStruct;
extern u8 drawStadiumRelated;
extern u8 lbl_2_data_2E9B4[];
extern Vec lbl_2_data_2E9D0;
extern f32 lbl_2_bss_B29C;
extern f32 lbl_2_data_2E9C4[];
extern f32 lbl_2_data_2E944[];
extern u8 lbl_2_data_2E608[];
extern Vec lbl_2_data_2E9E8;
extern f32 lbl_2_data_2E9DC[];
extern f32 lbl_2_bss_B2A0;
extern u8 lbl_2_bss_33FBF0[];
extern s8 lbl_2_bss_33FBF5;
extern u8 lbl_2_bss_B2A4;
extern u8 lbl_2_bss_B2A5;

void fn_2_48D54(void);
f32 fn_2_4A1E8(f32 z);
void fn_2_190DC(void *table, void *view);

void fn_2_8563C(Rep0DEMtxBlock *self);
void fn_2_858A4(Rep0DEMtxBlock *self);
void fn_2_85AC0(Rep0DEMtxBlock *self);
void fn_2_85D6C(Rep0DEMtxBlock *self);
void fn_2_86470(void);
void fn_2_868C8(void);
void fn_2_869B4(void);
void fn_2_86A0C(void);
void fn_2_86A80(void);
void fn_2_86DCC(void);
void fn_2_86F40(void);
void fn_2_86FEC(void);
void fn_2_870D4(f32 arg);
void fn_2_87114(void);
void fn_2_87118(void);
void fn_2_87350(void);
void fn_2_87654(s32 unused, s32 start, s32 count, s32 a, s32 b);

#endif // !__MENUS_REP_0DE0_H_
