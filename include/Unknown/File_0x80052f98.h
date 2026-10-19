#ifndef __UNKNOWN_FILE_0X80052F98_H_
#define __UNKNOWN_FILE_0X80052F98_H_

#include "mssbTypes.h"

typedef struct lbl_803c60bc_s {
    /* 0x00 */ f32 _00;
    /* 0x04 */ f32 _04;
    /* 0x08 */ f32 _08;
    /* 0x0C */ f32 _0C;
    /* 0x10 */ f32 _10;
    /* 0x14 */ f32 _14;
    artificial_padding(0x14, 0x24, f32);
    /* 0x24 */ f32 _24;
    /* 0x28 */ f32 _28;
    /* 0x2C */ f32 _2C;
    artificial_padding(0x2C, 0x3C, f32);
    /* 0x3C */ u8 _3C;
    /* 0x3D */ u8 _3D;
} lbl_803c60bc_s;

extern lbl_803c60bc_s lbl_803C60BC;
extern s32 lbl_803CBD10;

extern f32 lbl_803CC870;
extern f32 lbl_803CC874;
extern f32 lbl_803CC878;
extern f32 lbl_803CC87C;
extern f32 lbl_803CC880;
extern f32 lbl_803CC888;
extern f32 lbl_803CC88C;
extern f32 lbl_803CC890;
extern f32 lbl_803CC894;
extern f32 lbl_803CC898;
extern f32 lbl_803CC89C;
extern f32 lbl_803CC8A0;
extern f32 lbl_803CC8A4;
extern f32 lbl_803CC8A8;
extern f32 lbl_803CC8C4;
extern f32 lbl_803CC8C8;
extern f32 lbl_803CC8CC;

void possiblyTransitionBlackScreen(void);

#endif // !__UNKNOWN_FILE_0X80052F98_H_
