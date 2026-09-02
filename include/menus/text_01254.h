#ifndef __MENUS_TEXT_01254_H_
#define __MENUS_TEXT_01254_H_

#include "mssbTypes.h"

typedef struct Unk8Rec {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ s32 unk4;
} Unk8Rec;

void fn_2_1254(void);
u32 fn_2_1258(u8 *p, int off, int type);
void fn_2_12A0(s16 *p, int v);
void fn_2_12CC(u8 *p, int v);
void fn_2_12F8(u16 *p, int v);
void fn_2_1328(u32 *p, u16 v);
void fn_2_1354(Unk8Rec *arr, int n, int desc);
int fn_2_145C(u16 *a, u16 *b);
int fn_2_148C(u16 *s);
int stadiumRandomizer(int a, int b);
u32 fn_2_1554(void);
void fn_2_1578(void);
void fn_2_1800(void);
void fn_2_1A88(void);
void fn_2_1BAC(void);
void cursorSndFx(u16 button);
void fn_2_1D28(void);
void fn_2_1D54(int *cursor, u8 port, int count);
void fn_2_1DC4(void);
void fn_2_1DC8(void);
void mainMenuRelated(void);
void mainMenuScreen(void);
void fn_2_2BB8(void);
void fn_2_2D1C(void);
void loadDemoMatch(u8 arg0, int arg1, int arg2);
void fn_2_3204(void);

#endif // !__MENUS_TEXT_01254_H_
