#ifndef __UNUSED_REL_REP_00B0_H_
#define __UNUSED_REL_REP_00B0_H_

#include "mssbTypes.h"
#include "Dolphin/gd.h"
#include "Dolphin/mtx.h"

typedef struct DlVertex {
    Vec pos;
    u16 key;
    u16 pad;
} DlVertex;

typedef struct DlPrim {
    u8 pad0;
    u8 type;
    u16 count;
    DlVertex verts[1];
} DlPrim;

typedef struct DbgPickList {
    f32 (*boxes)[6];
    DlPrim *prims[1];
} DbgPickList;

typedef struct DbgGfxState {
    /*0x000*/ Mtx mtx;
    /*0x030*/ u8 pad030[0x20C - 0x30];
    /*0x20C*/ GDCurrentDL gdl;
    /*0x21C*/ u8 *dlBuf;
    /*0x220*/ s32 dlSize;
    /*0x224*/ DbgPickList *list;
    /*0x228*/ s16 count;
    /*0x22A*/ u8 pad22A[4];
    /*0x22E*/ s16 selected;
    /*0x230*/ u8 pad230[9];
    /*0x239*/ s8 showBoxes;
    /*0x23A*/ u8 pad23A[0x3C0 - 0x23A];
} DbgGfxState;

typedef struct PickState {
    /*0x00*/ Mtx mtx;
    /*0x30*/ u8 pad30[0x30];
    /*0x60*/ Vec normal;
    /*0x6C*/ f32 unk6C;
    /*0x70*/ f32 dist;
    /*0x74*/ u16 hit;
} PickState;

void fn_1_196C(void);
void fn_1_19AC(void);
void fn_1_1BF8(f32 *boxes, s32 idx);
void fn_1_1DBC(s32 a, s32 b, s32 c, s32 d, s32 e);
void fn_1_25BC(DlPrim *p);
void fn_1_3E38(Vec *p, u32 key);
void fn_1_4074(Vec *p);
void fn_1_4290(f32 *box);
u32 fn_1_4728(Vec *ray, Vec *out);
void fn_1_4A24(PickState *st, DlPrim *p);

#endif // !__UNUSED_REL_REP_00B0_H_
