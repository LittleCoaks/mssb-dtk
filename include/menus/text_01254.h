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

#endif // !__MENUS_TEXT_01254_H_
