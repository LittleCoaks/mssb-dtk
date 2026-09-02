#include "menus/rep_1028.h"
#include "header_rep_data.h"
#include "Dolphin/GX/GXTypes.h"
#include "Unknown/File_0x800bd2b0.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x800b0a14.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "stl/math.h"
#include "static/UnknownHomes_Static.h"

extern u8 inputParams[0x268];

extern Unk1A8248 *lbl_2_bss_1A8248;
extern Unk340140 *lbl_2_bss_340140;
extern Unk3401BC *lbl_2_bss_3401BC;

extern DrawingSceneStruct *currentDrawingItem;
extern u8 lbl_2_data_38BC[];
extern u8 *lbl_2_bss_1A824C;

extern Vec lbl_2_data_308F4;
extern f32 lbl_2_bss_B640;

f32 fn_2_4A1E8(f32 z);

extern void fn_80062890(s32 arg0);
void fn_2_46D34(void *arg);
void fn_2_3FA14(void);

extern UnkRec14 lbl_2_data_369C[];
extern UnkRec14 lbl_2_data_3198[];
extern u32 lbl_2_data_30900[];

extern void (*lbl_2_data_308A4[])(UnkObjBC *);
extern void (*lbl_2_data_30898[])(UnkObjBC *);
extern void (*lbl_2_data_3088C[])(UnkObjBC *);
extern void (*lbl_2_data_30880[])(UnkObjBC *);
extern void (*lbl_2_data_30870[])(UnkObjBC *);
extern void (*lbl_2_data_30864[])(UnkObjBC *);
extern void (*lbl_2_data_30858[])(UnkObjBC *);
extern void (*lbl_2_data_3084C[])(UnkObjBC *);
extern void (*lbl_2_data_30840[])(UnkObjBC *);
extern void (*lbl_2_data_30834[])(UnkObjBC *);
extern void (*lbl_2_data_30828[])(UnkObjBC *);
extern void (*lbl_2_data_3081C[])(UnkObjBC *);
extern void (*lbl_2_data_30810[])(UnkObjBC *);

void fn_2_8AC84(int idx, int val);

extern const f32 lbl_2_rodata_1078;
extern const f32 lbl_2_rodata_1080;
extern const f32 lbl_2_rodata_10A8;
extern const f32 lbl_2_rodata_10AC;
extern const f32 lbl_2_rodata_10B0;
extern const f32 lbl_2_rodata_10B4;
extern const f32 lbl_2_rodata_10B8;
extern const f32 lbl_2_rodata_10BC;
extern const f32 lbl_2_rodata_107C;
extern const f32 lbl_2_rodata_1084;
extern const f64 lbl_2_rodata_1088;
extern const f32 lbl_2_rodata_1090;
extern const f32 lbl_2_rodata_1094;
extern const f32 lbl_2_rodata_1098;

// .text:0x0008F0F4 size:0x188 mapped:0x806CE188
void fn_2_8F0F4(int idx) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    GXColor color = *(GXColor *) &inputParams[0x28];
    int v;
    switch (o->unkA6) {
    case 0:
        o->unk84 = lbl_2_rodata_1078;
        o->unkA6 = 1;
        color.a = 0xFF;
        adjustLightingParams(1, color);
    case 1:
        o->unk84 = o->unk84 - o->unk8C;
        v = (int) (lbl_2_rodata_107C * o->unk84);
        if (v > 1) {
            color.a = v;
            adjustLightingParams(1, color);
        } else {
            color.a = 0;
            adjustLightingParams(1, color);
            o->unkA6 = 2;
        }
        break;
    case 2:
        color.a = 0;
        adjustLightingParams(1, color);
        o->unkA0 = 1;
        o->unk84 = lbl_2_rodata_1080;
        o->unkA6 = 3;
        break;
    case 3:
        if (o->unkA0 == 2) {
            color.a = 0xFF;
            adjustLightingParams(0, color);
            o->unkA6 = 4;
        }
        break;
    }
}

// .text:0x0008F27C size:0x158 mapped:0x806CE310
void fn_2_8F27C(int idx) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    GXColor color = *(GXColor *) &inputParams[0x28];
    int v;
    switch (o->unkA6) {
    case 0:
        fn_2_8AC84(o->index, 1);
        o->unk84 = lbl_2_rodata_1080;
        v = (int) (lbl_2_rodata_1084 * o->unk84);
        color.a = v;
        adjustLightingParams(1, color);
        o->unkA6 = 1;
        break;
    case 1:
        o->unk84 = o->unk84 + o->unk8C;
        v = (int) (lbl_2_rodata_1084 * o->unk84);
        if (v < 0xFF) {
            color.a = 1;
            color.a = v;
            adjustLightingParams(1, color);
        } else {
            color.a = 0xFF;
            adjustLightingParams(0, color);
            o->unkA6 = 2;
        }
        break;
    case 2:
        o->unk84 = lbl_2_rodata_1080;
        break;
    }
}

// .text:0x0008F3D4 size:0x154 mapped:0x806CE468
void fn_2_8F3D4(int idx) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    GXColor color = *(GXColor *) &inputParams[0x28];
    int v;
    switch (o->unkA6) {
    case 0:
        o->unk84 = lbl_2_rodata_1078;
        o->unkA6 = 1;
        color.a = 0xFF;
        adjustLightingParams(1, color);
    case 1:
        o->unkA6 = 2;
    case 2:
        o->unk84 = o->unk84 - o->unk8C;
        v = (int) (lbl_2_rodata_107C * o->unk84);
        if (v > 1) {
            color.a = v;
            adjustLightingParams(1, color);
        } else {
            color.a = 0;
            adjustLightingParams(1, color);
            o->unkA6 = 3;
        }
        break;
    case 3:
        color.a = 0;
        adjustLightingParams(1, color);
        o->unkA0 = 1;
        o->unk84 = lbl_2_rodata_1080;
        break;
    }
}

// .text:0x0008F528 size:0x118 mapped:0x806CE5BC
void fn_2_8F528(int idx) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    GXColor color = *(GXColor *) &inputParams[0x28];
    int v;
    switch (o->unkA6) {
    case 0:
        o->unk84 = lbl_2_rodata_1080;
        o->unkA6 = 1;
    case 1:
        o->unk84 = (f32) ((f64) o->unk84 + lbl_2_rodata_1088);
        v = (int) (lbl_2_rodata_1084 * o->unk84);
        if (v < 0xFF) {
            color.a = 1;
            color.a = v;
            adjustLightingParams(1, color);
        } else {
            color.a = 0xFF;
            adjustLightingParams(0, color);
            o->unkA6 = 2;
        }
        break;
    case 2:
        o->unk84 = lbl_2_rodata_1080;
        break;
    }
}

// .text:0x0008F640 size:0x48 mapped:0x806CE6D4
void fn_2_8F640(void) {
    GXColor c = *(GXColor *) &inputParams[0x28];
    c.a = 0xFF;
    adjustLightingParams(1, c);
}

// .text:0x0008F688 size:0x48 mapped:0x806CE71C
void fn_2_8F688(void) {
    GXColor c = *(GXColor *) &inputParams[0x28];
    c.a = 0xFF;
    adjustLightingParams(0, c);
}

// .text:0x0008F6D0 size:0x50 mapped:0x806CE764
void fn_2_8F6D0(int idx, int entryIdx) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    UnkRec28 *arr = lbl_2_bss_340140->unk2D94;
    if (arr == NULL) {
        return;
    }
    o->unkA6 = 0;
    arr[idx].unk0 = (void *) lbl_2_data_30900[entryIdx];
}

// .text:0x0008F720 size:0x1C mapped:0x806CE7B4
int fn_2_8F720(int idx) {
    return ((u8 *) lbl_2_bss_1A8248)[idx * 0xBC + 0x2294];
}

// .text:0x0008F73C size:0x1C mapped:0x806CE7D0
void fn_2_8F73C(int idx, u8 val) {
    ((u8 *)lbl_2_bss_1A8248)[idx * 0xBC + 0x2294] = val;
}

// .text:0x0008F758 size:0x1C mapped:0x806CE7EC
void fn_2_8F758(int idx, u8 val) {
    ((u8 *)lbl_2_bss_1A8248)[idx * 0xBC + 0x2288] = val;
}

// .text:0x0008F774 size:0x3C mapped:0x806CE808
void fn_2_8F774(int idx) {
    UnkElem90 *e = &lbl_2_bss_340140->unk68->elems[idx];
    scanBoneAttachmentData(e->unk0);
}

// .text:0x0008F7B0 size:0x88 mapped:0x806CE844
void fn_2_8F7B0(int idx, s16 arg1) {
    int v;
    UnkElem90 *e;
    if (lbl_2_bss_3401BC == NULL) {
        return;
    }
    v = lbl_2_bss_3401BC->unk4C;
    e = &lbl_2_bss_340140->unk68->elems[idx];
    e->unk4 = v;
    e->unkE = arg1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk58 = 1;
    e->unk59 = (v != 0);
    e->unk5A = (v != 0);
    e->unk60 = lbl_2_rodata_1080;
    e->unk54 = lbl_2_rodata_1078;
    e->unk5A = 1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk59 = 1;
    e->unk5B = 3;
}

// .text:0x0008F838 size:0x88 mapped:0x806CE8CC
void fn_2_8F838(int idx, s16 arg1) {
    int v;
    UnkElem90 *e;
    if (lbl_2_bss_3401BC == NULL) {
        return;
    }
    v = lbl_2_bss_3401BC->unk48;
    e = &lbl_2_bss_340140->unk68->elems[idx];
    e->unk4 = v;
    e->unkE = arg1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk58 = 1;
    e->unk59 = (v != 0);
    e->unk5A = (v != 0);
    e->unk60 = lbl_2_rodata_1080;
    e->unk54 = lbl_2_rodata_1078;
    e->unk5A = 1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk59 = 1;
    e->unk5B = 3;
}

// .text:0x0008F8C0 size:0x88 mapped:0x806CE954
void fn_2_8F8C0(int idx, s16 arg1) {
    int v;
    UnkElem90 *e;
    if (lbl_2_bss_3401BC == NULL) {
        return;
    }
    v = lbl_2_bss_3401BC->unk44;
    e = &lbl_2_bss_340140->unk68->elems[idx];
    e->unk4 = v;
    e->unkE = arg1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk58 = 1;
    e->unk59 = (v != 0);
    e->unk5A = (v != 0);
    e->unk60 = lbl_2_rodata_1080;
    e->unk54 = lbl_2_rodata_1078;
    e->unk5A = 1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk59 = 1;
    e->unk5B = 3;
}

// .text:0x0008F948 size:0x88 mapped:0x806CE9DC
void fn_2_8F948(int idx, s16 arg1) {
    int v;
    UnkElem90 *e;
    if (lbl_2_bss_3401BC == NULL) {
        return;
    }
    v = lbl_2_bss_3401BC->unk40;
    e = &lbl_2_bss_340140->unk68->elems[idx];
    e->unk4 = v;
    e->unkE = arg1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk58 = 1;
    e->unk59 = (v != 0);
    e->unk5A = (v != 0);
    e->unk60 = lbl_2_rodata_1080;
    e->unk54 = lbl_2_rodata_1078;
    e->unk5A = 1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk59 = 1;
    e->unk5B = 3;
}

// .text:0x0008F9D0 size:0x88 mapped:0x806CEA64
void fn_2_8F9D0(int idx, s16 arg1) {
    int v;
    UnkElem90 *e;
    if (lbl_2_bss_3401BC == NULL) {
        return;
    }
    v = lbl_2_bss_3401BC->unk3C;
    e = &lbl_2_bss_340140->unk68->elems[idx];
    e->unk4 = v;
    e->unkE = arg1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk58 = 1;
    e->unk59 = (v != 0);
    e->unk5A = (v != 0);
    e->unk60 = lbl_2_rodata_1080;
    e->unk54 = lbl_2_rodata_1078;
    e->unk5A = 1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk59 = 1;
    e->unk5B = 3;
}

// .text:0x0008FA58 size:0x88 mapped:0x806CEAEC
void fn_2_8FA58(int idx, s16 arg1) {
    int v;
    UnkElem90 *e;
    if (lbl_2_bss_3401BC == NULL) {
        return;
    }
    v = lbl_2_bss_3401BC->unk38;
    e = &lbl_2_bss_340140->unk68->elems[idx];
    e->unk4 = v;
    e->unkE = arg1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk58 = 1;
    e->unk59 = (v != 0);
    e->unk5A = (v != 0);
    e->unk60 = lbl_2_rodata_1080;
    e->unk54 = lbl_2_rodata_1078;
    e->unk5A = 1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk59 = 1;
    e->unk5B = 3;
}

// .text:0x0008FAE0 size:0x88 mapped:0x806CEB74
void fn_2_8FAE0(int idx, s16 arg1) {
    int v;
    UnkElem90 *e;
    if (lbl_2_bss_3401BC == NULL) {
        return;
    }
    v = lbl_2_bss_3401BC->unk34;
    e = &lbl_2_bss_340140->unk68->elems[idx];
    e->unk4 = v;
    e->unkE = arg1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk58 = 1;
    e->unk59 = (v != 0);
    e->unk5A = (v != 0);
    e->unk60 = lbl_2_rodata_1080;
    e->unk54 = lbl_2_rodata_1078;
    e->unk5A = 1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk59 = 1;
    e->unk5B = 3;
}

// .text:0x0008FB68 size:0x90 mapped:0x806CEBFC
void fn_2_8FB68(int idx, s16 arg1) {
    int v;
    UnkElem90 *e;
    if (lbl_2_bss_3401BC == NULL) {
        return;
    }
    e = &lbl_2_bss_340140->unk68->elems[idx];
    v = lbl_2_bss_3401BC->unkC[idx];
    e->unk4 = v;
    e->unkE = arg1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk58 = 1;
    e->unk59 = (v != 0);
    e->unk5A = (v != 0);
    e->unk60 = lbl_2_rodata_1080;
    e->unk54 = lbl_2_rodata_1078;
    e->unk5A = 1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk59 = 1;
    e->unk5B = 3;
}

// .text:0x0008FBF8 size:0x90 mapped:0x806CEC8C
void fn_2_8FBF8(int idx, s16 arg1) {
    int v;
    UnkElem90 *e;
    if (lbl_2_bss_3401BC == NULL) {
        return;
    }
    e = &lbl_2_bss_340140->unk68->elems[idx];
    v = lbl_2_bss_3401BC->unkC[idx];
    e->unk4 = v;
    e->unkE = arg1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk58 = 1;
    e->unk59 = (v != 0);
    e->unk5A = (v != 0);
    e->unk60 = lbl_2_rodata_1080;
    e->unk54 = lbl_2_rodata_1078;
    e->unk5A = 1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk59 = 1;
    e->unk5B = 3;
}

// .text:0x0008FC88 size:0x8C mapped:0x806CED1C
void fn_2_8FC88(int idx) {
    int v;
    UnkElem90 *e;

    if (lbl_2_bss_3401BC == NULL) {
        return;
    }
    v = lbl_2_bss_3401BC->unkC[0];
    e = &lbl_2_bss_340140->unk68->elems[idx];
    e->unk4 = v;
    e->unkE = 0;
    e->unk5C = lbl_2_rodata_1080;
    e->unk58 = 1;
    e->unk59 = (v != 0);
    e->unk5A = (v != 0);
    e->unk60 = lbl_2_rodata_1080;
    e->unk54 = lbl_2_rodata_1078;
    e->unk5A = 1;
    e->unk5C = lbl_2_rodata_1080;
    e->unk59 = 1;
    e->unk5B = 3;
}

// .text:0x0008FD14 size:0x9C mapped:0x806CEDA8
void fn_2_8FD14(void) {
    UnkRec28 *arr;
    UnkObjBC *o;
    int i;
    for (i = 0; i < lbl_2_bss_340140->unk3078; i++) {
        arr = lbl_2_bss_340140->unk2D94;
        if (arr != NULL) {
            o = &lbl_2_bss_1A8248->objs[i];
            memcpy(arr[i].unk4, o, 0xC);
            arr[i].unk14 = o->unk28;
            arr[i].unk26 = o->unkAA;
        }
    }
}

// .text:0x0008FDB0 size:0xEC mapped:0x806CEE44
void fn_2_8FDB0(int idx) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    if (!(o->unk30 <= lbl_2_rodata_1080)) {
        Mtx m;
        Vec v;
        PSMTXRotRad(m, 'Y', o->unk44);
        v.x = lbl_2_rodata_1080;
        v.y = lbl_2_rodata_1080;
        v.z = -o->unk30;
        PSMTXMultVec(m, &v, &v);
        o->unk18 = v.x;
        o->unk1C = v.z;
        o->unk0 += o->unk18;
        o->unk8 += o->unk1C;
    }
    o->unkC = o->unk0;
    o->unk14 = o->unk8;
    if (lbl_2_rodata_1080 == o->unk30) {
        o->unk20 = lbl_2_rodata_1080;
        o->unk24 = lbl_2_rodata_1080;
    }
}

// .text:0x0008FE9C size:0x1E0 mapped:0x806CEF30
void fn_2_8FE9C(int idx) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    Vec pos;
    Vec diff;
    s8 port;
    u8 *rec;
    u16 flags;
    memcpy(&pos, o, 0xC);
    PSVECSubtract(&pos, &lbl_2_data_308F4, &diff);
    diff.x = lbl_2_rodata_1090 * diff.x;
    diff.z = lbl_2_rodata_1090 * diff.z;
    port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    rec = (u8 *) &AtBat_ButtonInput1 + port * 32;
    pos.x = pos.x + (f32) (s8) rec[0x10] / lbl_2_rodata_1094;
    pos.z = pos.z + (f32) (s8) rec[0x11] / lbl_2_rodata_1094;
    if (lbl_2_rodata_1080 != diff.x || lbl_2_rodata_1080 != diff.z) {
        lbl_2_bss_B640 = fn_2_4A1E8(diff.z);
    }
    port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    rec = (u8 *) &AtBat_ButtonInput1 + port * 32;
    flags = *(u16 *) (rec + 4);
    if (flags & 0x40) {
        pos.y = pos.y - lbl_2_rodata_1098;
    } else if (flags & 0x20) {
        pos.y = pos.y + lbl_2_rodata_1098;
    }
    memcpy(&lbl_2_data_308F4, o, 0xC);
    o->unk0 = pos.x;
    o->unk4 = pos.y;
    o->unk8 = pos.z;
    o->unk44 = lbl_2_bss_B640;
}

// .text:0x0009007C size:0x2C0 mapped:0x806CF110
void fn_2_9007C(void) {
    int idx = *(s16 *) &lbl_2_bss_1A824C[0x190000 + 0x72BE];
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    Vec pos;
    Vec diff;
    s8 port;
    u8 *rec;
    u16 flags;
    memcpy(&pos, o, 0xC);
    PSVECSubtract(&pos, &lbl_2_data_308F4, &diff);
    diff.x = lbl_2_rodata_1090 * diff.x;
    diff.z = lbl_2_rodata_1090 * diff.z;
    port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    rec = (u8 *) &AtBat_ButtonInput1 + port * 32;
    pos.x = pos.x + (f32) (s8) rec[0x10] / lbl_2_rodata_1094;
    pos.z = pos.z + (f32) (s8) rec[0x11] / lbl_2_rodata_1094;
    if (!(diff.x == lbl_2_rodata_1080 && diff.z == lbl_2_rodata_1080)) {
        lbl_2_bss_B640 = fn_2_4A1E8(diff.z);
    }
    port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    rec = (u8 *) &AtBat_ButtonInput1 + port * 32;
    flags = *(u16 *) (rec + 4);
    if (flags & 0x40) {
        pos.y = pos.y - lbl_2_rodata_1098;
    } else if (flags & 0x20) {
        pos.y = pos.y + lbl_2_rodata_1098;
    }
    memcpy(&lbl_2_data_308F4, o, 0xC);
    o->unk0 = pos.x;
    o->unk4 = pos.y;
    o->unk8 = pos.z;
    o->unk44 = lbl_2_bss_B640;

    if (!(o->unk30 <= lbl_2_rodata_1080)) {
        Mtx m;
        Vec v;
        PSMTXRotRad(m, 'Y', o->unk44);
        v.x = lbl_2_rodata_1080;
        v.y = lbl_2_rodata_1080;
        v.z = -o->unk30;
        PSMTXMultVec(m, &v, &v);
        o->unk18 = v.x;
        o->unk1C = v.z;
        o->unk0 += o->unk18;
        o->unk8 += o->unk1C;
    }
    o->unkC = o->unk0;
    o->unk14 = o->unk8;
    if (lbl_2_rodata_1080 == o->unk30) {
        o->unk20 = lbl_2_rodata_1080;
        o->unk24 = lbl_2_rodata_1080;
    }
}

// .text:0x0009033C size:0x6C mapped:0x806CF3D0
void fn_2_9033C(int idx, void *src, f32 f) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    memcpy(o, src, 0xC);
    o->unk28 = f;
    o->unk30 = lbl_2_rodata_1080;
    o->unk28 = f;
}

// .text:0x000903A8 size:0x80 mapped:0x806CF43C
void fn_2_903A8(int idx) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    memcpy(o, &lbl_2_data_369C[idx], 0xC);
    o->unk30 = lbl_2_rodata_1080;
    o->unk28 = lbl_2_data_369C[idx].unkC;
}

// .text:0x00090428 size:0x80 mapped:0x806CF4BC
void fn_2_90428(int idx) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[idx];
    memcpy(o, &lbl_2_data_3198[idx], 0xC);
    o->unk30 = lbl_2_rodata_1080;
    o->unk28 = lbl_2_data_3198[idx].unkC;
}

// .text:0x000904A8 size:0x90 mapped:0x806CF53C
void fn_2_904A8(void) {
    UnkObjBC *o;
    int i;
    for (i = 0; i < 29; i++) {
        o = &lbl_2_bss_1A8248->objs[i];
        o->index = i;
        o->unk7C = i;
        o->unk84 = lbl_2_rodata_1080;
        o->unk38 = lbl_2_rodata_1080;
        o->unk3C = lbl_2_rodata_1080;
        o->unkAA = 0;
        o->unk92 = i;
        o->unk94 = -1;
        o->unkA8 = 0;
        o->unkAB = 0;
        o->state = 0;
        o->unkAE = 0xFF;
        o->unkAC = 0;
        o->unkAD = 0;
        o->unk80 = lbl_2_rodata_1080;
        o->unkA6 = 0;
        o->unkB2 = 0xFF;
        o->unkB4 = 0;
    }
}

// .text:0x00090538 size:0xE4 mapped:0x806CF5CC
void fn_2_90538(void) {
    UnkObjBC *o;
    int i = 0;
    do {
        o = &lbl_2_bss_1A8248->objs[i];
        memset(o, 0, sizeof(UnkObjBC));
        o->index = i;
        o->unk7C = i;
        o->unk84 = lbl_2_rodata_1080;
        o->unk38 = lbl_2_rodata_1080;
        o->unk3C = lbl_2_rodata_1080;
        o->unkAA = 0;
        o->unk92 = i;
        i++;
        o->unk94 = -1;
        o->unkA8 = 0;
        o->unkAB = 0;
        o->state = 0;
        o->unkAE = 0xFF;
        o->unkAC = 0;
        o->unkAD = 0;
        o->unk80 = lbl_2_rodata_1080;
        o->unkA6 = 0;
        o->unkB2 = 0xFF;
        o->unkB4 = 0;
    } while (i < 29);
}

// .text:0x0009061C size:0xC mapped:0x806CF6B0
void fn_2_9061C(UnkObjBC *obj) {
    obj->state = 3;
}

// .text:0x00090628 size:0x70 mapped:0x806CF6BC
void fn_2_90628(UnkObjBC *obj) {
    if (obj->unkA0 == 1) {
        UnkObjBC *o;
        fn_2_8AC84(obj->index, 0);
        obj->unkA0 = 2;
        o = &lbl_2_bss_1A8248->objs[obj->index];
        o->unkAB = 0;
        o->state = 0;
    }
}

// .text:0x00090698 size:0x80 mapped:0x806CF72C
void fn_2_90698(UnkObjBC *obj) {
    int idx;
    UnkObjBC *o;
    UnkRec28 *arr;

    if (obj->unk9C-- != 0) {
        return;
    }
    obj->unk8C = lbl_2_rodata_10A8;
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[5];
    }
    obj->state = 2;
}

// .text:0x00090718 size:0xDC mapped:0x806CF7AC
void fn_2_90718(UnkObjBC *obj) {
    int idx;
    int v;
    UnkElem90 *e;

    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    if (lbl_2_bss_3401BC != NULL) {
        v = lbl_2_bss_3401BC->unk3C;
        e = &lbl_2_bss_340140->unk68->elems[idx];
        e->unk4 = v;
        e->unkE = 2;
        e->unk5C = lbl_2_rodata_1080;
        e->unk58 = 1;
        e->unk59 = (v != 0);
        e->unk5A = (v != 0);
        e->unk60 = lbl_2_rodata_1080;
        e->unk54 = lbl_2_rodata_1078;
        e->unk5A = 1;
        e->unk5C = lbl_2_rodata_1080;
        e->unk59 = 1;
        e->unk5B = 3;
    }
    obj->unk9C = 0x50;
    obj->unkA0 = 0;
    obj->state = 1;
}

// .text:0x000907F4 size:0x38 mapped:0x806CF888
void fn_2_907F4(UnkObjBC *obj) {
    lbl_2_data_308A4[obj->state](obj);
}

// .text:0x0009082C size:0xC mapped:0x806CF8C0
void fn_2_9082C(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x00090838 size:0x50 mapped:0x806CF8CC
void fn_2_90838(UnkObjBC *obj) {
    if (obj->unkA0 == 1) {
        fn_2_8AC84(obj->index, 0);
        obj->unkA0 = 2;
    }
    obj->state = 2;
}

// .text:0x00090888 size:0x74 mapped:0x806CF91C
void fn_2_90888(UnkObjBC *obj) {
    int idx;
    UnkObjBC *o;
    UnkRec28 *arr;

    obj->unk8C = lbl_2_rodata_10AC;
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[5];
    }
    obj->unkA0 = 0;
    obj->state = 1;
}

// .text:0x000908FC size:0x38 mapped:0x806CF990
void fn_2_908FC(UnkObjBC *obj) {
    lbl_2_data_30898[obj->state](obj);
}

// .text:0x00090934 size:0xC mapped:0x806CF9C8
void fn_2_90934(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x00090940 size:0xC mapped:0x806CF9D4
void fn_2_90940(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x0009094C size:0xA8 mapped:0x806CF9E0
void fn_2_9094C(UnkObjBC *obj) {
    int idx;
    UnkObjBC *o;
    UnkRec28 *arr;

    fn_2_8AC84(obj->index, 0);
    obj->unk8C = lbl_2_rodata_10B0;
    obj->unkA0 = 0;
    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[4];
    }
    obj->state = 1;
}

// .text:0x000909F4 size:0x38 mapped:0x806CFA88
void fn_2_909F4(UnkObjBC *obj) {
    lbl_2_data_3088C[obj->state](obj);
}

// .text:0x00090A2C size:0x84 mapped:0x806CFAC0
void fn_2_90A2C(UnkObjBC *obj) {
    UnkElem90 *e = &lbl_2_bss_340140->unk68->elems[obj->index];
    if (scanBoneAttachmentData(e->unk0) == lbl_2_rodata_1080) {
        UnkObjBC *o = &lbl_2_bss_1A8248->objs[obj->index];
        o->unkAB = 2;
        o->state = 0;
    }
}

// .text:0x00090AB0 size:0xC mapped:0x806CFB44
void fn_2_90AB0(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x00090ABC size:0x114 mapped:0x806CFB50
void fn_2_90ABC(UnkObjBC *obj) {
    int idx;
    int v;
    UnkElem90 *e;
    UnkObjBC *o;
    UnkRec28 *arr;

    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    if (lbl_2_bss_3401BC != NULL) {
        v = lbl_2_bss_3401BC->unk34;
        e = &lbl_2_bss_340140->unk68->elems[idx];
        e->unk4 = v;
        e->unkE = 1;
        e->unk5C = lbl_2_rodata_1080;
        e->unk58 = 1;
        e->unk59 = (v != 0);
        e->unk5A = (v != 0);
        e->unk60 = lbl_2_rodata_1080;
        e->unk54 = lbl_2_rodata_1078;
        e->unk5A = 1;
        e->unk5C = lbl_2_rodata_1080;
        e->unk59 = 1;
        e->unk5B = 3;
    }
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[0];
    }
    obj->state = 1;
}

// .text:0x00090BD0 size:0x38 mapped:0x806CFC64
void fn_2_90BD0(UnkObjBC *obj) {
    lbl_2_data_30880[obj->state](obj);
}

// .text:0x00090C08 size:0xC mapped:0x806CFC9C
void fn_2_90C08(UnkObjBC *obj) {
    obj->state = 3;
}

// .text:0x00090C14 size:0x38 mapped:0x806CFCA8
void fn_2_90C14(UnkObjBC *obj) {
    if (obj->unkA0 == 1) {
        UnkObjBC *o = &lbl_2_bss_1A8248->objs[obj->index];
        o->unkAB = 0;
        o->state = 0;
    }
}

// .text:0x00090C4C size:0x84 mapped:0x806CFCE0
void fn_2_90C4C(UnkObjBC *obj) {
    int idx;
    UnkObjBC *o;
    UnkRec28 *arr;

    if (obj->unk9C-- != 0) {
        return;
    }
    obj->unk8C = lbl_2_rodata_10B4;
    obj->unkA0 = 0;
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[3];
    }
    obj->state = 2;
}

// .text:0x00090CD0 size:0xDC mapped:0x806CFD64
void fn_2_90CD0(UnkObjBC *obj) {
    UnkElem90 *e;
    int v;
    int idx;

    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    if (lbl_2_bss_3401BC != NULL) {
        e = &lbl_2_bss_340140->unk68->elems[idx];
        v = lbl_2_bss_3401BC->unkC[obj->index];
        e->unk4 = v;
        e->unkE = 0;
        e->unk5C = lbl_2_rodata_1080;
        e->unk58 = 1;
        e->unk59 = (v != 0);
        e->unk5A = (v != 0);
        e->unk60 = lbl_2_rodata_1080;
        e->unk54 = lbl_2_rodata_1078;
        e->unk5A = 1;
        e->unk5C = lbl_2_rodata_1080;
        e->unk59 = 1;
        e->unk5B = 3;
    }
    obj->unk9C = 0x1C;
    obj->state = 1;
}

// .text:0x00090DAC size:0x38 mapped:0x806CFE40
void fn_2_90DAC(UnkObjBC *obj) {
    lbl_2_data_30870[obj->state](obj);
}

// .text:0x00090DE4 size:0xB4 mapped:0x806CFE78
void fn_2_90DE4(UnkObjBC *obj, f32 limit) {
    f32 v;
    if (obj->unkB5 != 0) {
        f32 s = sin(obj->unk88);
        v = lbl_2_rodata_10B8 * -s;
        obj->unk88 += lbl_2_rodata_10BC;
        if (v >= limit) {
            obj->unk88 = lbl_2_rodata_1080;
            v = lbl_2_rodata_1080;
            obj->unkB5 = 0;
        }
        obj->unk4 = v;
    } else {
        obj->unk4 = lbl_2_rodata_1080;
    }
}

// .text:0x00090E98 size:0x2C mapped:0x806CFF2C
void fn_2_90E98(UnkObjBC *obj) {
    UnkObjBC *o = &lbl_2_bss_1A8248->objs[obj->index];
    o->unkAB = 0;
    o->state = 0;
}

// .text:0x00090EC4 size:0x194 mapped:0x806CFF58
void fn_2_90EC4(UnkObjBC *obj) {
    DrawingSceneStruct *item = currentDrawingItem;
    Mtx m;
    Vec v;
    f32 val;

    if (obj->unkB5 != 0) {
        f32 s = sin(obj->unk88);
        val = lbl_2_rodata_10B8 * -s;
        obj->unk88 += lbl_2_rodata_10BC;
        if (val >= lbl_2_rodata_1080) {
            obj->unk88 = lbl_2_rodata_1080;
            obj->unkB5 = 0;
            val = lbl_2_rodata_1080;
        }
        obj->unk4 = val;
    } else {
        obj->unk4 = lbl_2_rodata_1080;
    }
    PSMTXRotRad(m, 'Y', obj->unk2C);
    v.x = lbl_2_rodata_1080;
    v.y = lbl_2_rodata_1080;
    v.z = lbl_2_rodata_10A8;
    PSMTXMultVec(m, &v, &v);
    obj->unk0 -= v.x;
    obj->unk8 -= v.z;
    if (obj->unk4 >= lbl_2_rodata_1080) {
        fn_2_46D34(*(void **) lbl_2_data_38BC);
        if (lbl_2_bss_1A8248->unk43BE < 999) {
            DrawingSceneStruct *d = insertGraphicDrawingFunction(fn_2_3FA14, 2);
            *((u8 *) d + 0x28) = 0;
            item->state = 0;
        } else {
            *(s16 *) (lbl_2_bss_1A824C + 0x197740) = 1;
        }
        obj->state = 2;
    }
}

// .text:0x00091058 size:0x188 mapped:0x806D00EC
void fn_2_91058(UnkObjBC *obj) {
    int idx;
    int v;
    UnkElem90 *e;
    UnkObjBC *o;
    UnkRec28 *arr;
    f32 a;
    f32 b;
    Unk1A8248 *base = lbl_2_bss_1A8248;

    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    if (lbl_2_bss_3401BC != NULL) {
        v = lbl_2_bss_3401BC->unk4C;
        e = &lbl_2_bss_340140->unk68->elems[idx];
        e->unk4 = v;
        e->unkE = 1;
        e->unk5C = lbl_2_rodata_1080;
        e->unk58 = 1;
        e->unk59 = (v != 0);
        e->unk5A = (v != 0);
        e->unk60 = lbl_2_rodata_1080;
        e->unk54 = lbl_2_rodata_1078;
        e->unk5A = 1;
        e->unk5C = lbl_2_rodata_1080;
        e->unk59 = 1;
        e->unk5B = 3;
    }
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[0];
    }
    obj->unkB5 = 1;
    obj->unk88 = lbl_2_rodata_10BC;
    obj->unk4 = lbl_2_rodata_1080;
    obj->unk28 = lbl_2_rodata_1080;
    obj->unk28 = lbl_2_rodata_1080;
    fn_80062890(0x40);
    a = base->unk1610.x - base->unk16E8.x;
    b = base->unk1610.z - base->unk16E8.z;
    obj->unk2C = atan2(-a, -b);
    obj->state = 1;
}

// .text:0x000911E0 size:0x38 mapped:0x806D0274
void fn_2_911E0(UnkObjBC *obj) {
    lbl_2_data_30864[obj->state](obj);
}

// .text:0x00091218 size:0x84 mapped:0x806D02AC
void fn_2_91218(UnkObjBC *obj) {
    UnkElem90 *e = &lbl_2_bss_340140->unk68->elems[obj->index];
    if (scanBoneAttachmentData(e->unk0) == lbl_2_rodata_1080) {
        UnkObjBC *o = &lbl_2_bss_1A8248->objs[obj->index];
        o->unkAB = 2;
        o->state = 0;
    }
}

// .text:0x0009129C size:0xC mapped:0x806D0330
void fn_2_9129C(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x000912A8 size:0x1A8 mapped:0x806D033C
void fn_2_912A8(UnkObjBC *obj) {
    int idx;
    int v;
    UnkElem90 *e;
    UnkObjBC *o;
    UnkRec28 *arr;

    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    if (idx == 0x19) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk44;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 3;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    } else {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk48;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 3;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    }
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[0];
    }
    obj->state = 1;
}

// .text:0x00091450 size:0x38 mapped:0x806D04E4
void fn_2_91450(UnkObjBC *obj) {
    lbl_2_data_30858[obj->state](obj);
}

// .text:0x00091488 size:0x84 mapped:0x806D051C
void fn_2_91488(UnkObjBC *obj) {
    UnkElem90 *e = &lbl_2_bss_340140->unk68->elems[obj->index];
    if (scanBoneAttachmentData(e->unk0) == lbl_2_rodata_1080) {
        UnkObjBC *o = &lbl_2_bss_1A8248->objs[obj->index];
        o->unkAB = 2;
        o->state = 0;
    }
}

// .text:0x0009150C size:0xC mapped:0x806D05A0
void fn_2_9150C(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x00091518 size:0x1A8 mapped:0x806D05AC
void fn_2_91518(UnkObjBC *obj) {
    int idx;
    int v;
    UnkElem90 *e;
    UnkObjBC *o;
    UnkRec28 *arr;

    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    if (idx == 0x19) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk44;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    } else {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk48;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    }
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[0];
    }
    obj->state = 1;
}

// .text:0x000916C0 size:0x38 mapped:0x806D0754
void fn_2_916C0(UnkObjBC *obj) {
    lbl_2_data_3084C[obj->state](obj);
}

// .text:0x000916F8 size:0x84 mapped:0x806D078C
void fn_2_916F8(UnkObjBC *obj) {
    UnkElem90 *e = &lbl_2_bss_340140->unk68->elems[obj->index];
    if (scanBoneAttachmentData(e->unk0) == lbl_2_rodata_1080) {
        UnkObjBC *o = &lbl_2_bss_1A8248->objs[obj->index];
        o->unkAB = 2;
        o->state = 0;
    }
}

// .text:0x0009177C size:0xC mapped:0x806D0810
void fn_2_9177C(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x00091788 size:0x11C mapped:0x806D081C
void fn_2_91788(UnkObjBC *obj) {
    UnkElem90 *e;
    int v;
    int idx;
    UnkObjBC *o;
    UnkRec28 *arr;

    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    if (lbl_2_bss_3401BC != NULL) {
        e = &lbl_2_bss_340140->unk68->elems[idx];
        v = lbl_2_bss_3401BC->unkC[obj->index];
        e->unk4 = v;
        e->unkE = 1;
        e->unk5C = lbl_2_rodata_1080;
        e->unk58 = 1;
        e->unk59 = (v != 0);
        e->unk5A = (v != 0);
        e->unk60 = lbl_2_rodata_1080;
        e->unk54 = lbl_2_rodata_1078;
        e->unk5A = 1;
        e->unk5C = lbl_2_rodata_1080;
        e->unk59 = 1;
        e->unk5B = 3;
    }
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[0];
    }
    obj->state = 1;
}

// .text:0x000918A4 size:0x38 mapped:0x806D0938
void fn_2_918A4(UnkObjBC *obj) {
    lbl_2_data_30840[obj->state](obj);
}

// .text:0x000918DC size:0xC mapped:0x806D0970
void fn_2_918DC(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x000918E8 size:0xC mapped:0x806D097C
void fn_2_918E8(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x000918F4 size:0x88 mapped:0x806D0988
void fn_2_918F4(UnkObjBC *obj) {
    int idx;
    UnkRec28 *arr;
    UnkObjBC *o;
    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[2];
    }
    obj->state = 1;
}

// .text:0x0009197C size:0x38 mapped:0x806D0A10
void fn_2_9197C(UnkObjBC *obj) {
    lbl_2_data_30834[obj->state](obj);
}

// .text:0x000919B4 size:0xC mapped:0x806D0A48
void fn_2_919B4(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x000919C0 size:0xC mapped:0x806D0A54
void fn_2_919C0(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x000919CC size:0x118 mapped:0x806D0A60
void fn_2_919CC(UnkObjBC *obj) {
    int idx;
    int v;
    UnkElem90 *e;
    UnkObjBC *o;
    UnkRec28 *arr;

    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    if (lbl_2_bss_3401BC != NULL) {
        v = lbl_2_bss_3401BC->unkC[0];
        e = &lbl_2_bss_340140->unk68->elems[idx];
        e->unk4 = v;
        e->unkE = 0;
        e->unk5C = lbl_2_rodata_1080;
        e->unk58 = 1;
        e->unk59 = (v != 0);
        e->unk5A = (v != 0);
        e->unk60 = lbl_2_rodata_1080;
        e->unk54 = lbl_2_rodata_1078;
        e->unk5A = 1;
        e->unk5C = lbl_2_rodata_1080;
        e->unk59 = 1;
        e->unk5B = 3;
    }
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[0];
    }
    obj->state = 1;
}

// .text:0x00091AE4 size:0x38 mapped:0x806D0B78
void fn_2_91AE4(UnkObjBC *obj) {
    lbl_2_data_30828[obj->state](obj);
}

// .text:0x00091B1C size:0xC mapped:0x806D0BB0
void fn_2_91B1C(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x00091B28 size:0x4 mapped:0x806D0BBC
void fn_2_91B28(void) {
    return;
}

// .text:0x00091B2C size:0xC mapped:0x806D0BC0
void fn_2_91B2C(UnkObjBC *obj) {
    obj->state = 1;
}

// .text:0x00091B38 size:0x38 mapped:0x806D0BCC
void fn_2_91B38(UnkObjBC *obj) {
    lbl_2_data_3081C[obj->state](obj);
}

// .text:0x00091B70 size:0xC mapped:0x806D0C04
void fn_2_91B70(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x00091B7C size:0x4 mapped:0x806D0C10
void fn_2_91B7C(void) {
    return;
}

// .text:0x00091B80 size:0x88 mapped:0x806D0C14
void fn_2_91B80(UnkObjBC *obj) {
    int idx;
    UnkRec28 *arr;
    UnkObjBC *o;
    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[0];
    }
    obj->state = 1;
}

// .text:0x00091C08 size:0x38 mapped:0x806D0C9C
void fn_2_91C08(UnkObjBC *obj) {
    lbl_2_data_30810[obj->state](obj);
}

// .text:0x00091C40 size:0xC mapped:0x806D0CD4
void fn_2_91C40(UnkObjBC *obj) {
    obj->state = 2;
}

// .text:0x00091C4C size:0x128 mapped:0x806D0CE0
void fn_2_91C4C(UnkObjBC *obj) {
    int idx = obj->index;
    UnkElem90 *e;

    if (obj->unkA8 == 1) {
        if (lbl_2_bss_3401BC != NULL) {
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk54 = lbl_2_rodata_1080;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 2;
            e->unk58 = 0;
            obj->state = 2;
        }
    } else if (obj->unkA8 == 2) {
        e = &lbl_2_bss_340140->unk68->elems[idx];
        if (scanBoneAttachmentData(e->unk0) == lbl_2_rodata_1080) {
            if (lbl_2_bss_3401BC != NULL) {
                e = &lbl_2_bss_340140->unk68->elems[idx];
                e->unk54 = lbl_2_rodata_1080;
                e->unk5A = 1;
                e->unk5C = lbl_2_rodata_1080;
                e->unk59 = 1;
                e->unk5B = 2;
                e->unk58 = 0;
                obj->state = 2;
            }
        }
    }
}

// .text:0x00091D74 size:0x620 mapped:0x806D0E08
void fn_2_91D74(UnkObjBC *obj) {
    int idx;
    int v;
    UnkElem90 *e;
    UnkObjBC *o;
    UnkRec28 *arr;

    fn_2_8AC84(obj->index, 1);
    idx = obj->index;
    if (idx >= 1 && idx <= 7) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unkC[idx];
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 0;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    } else if (idx == 8) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unkC[idx];
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 0;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    } else if (idx >= 0xA && idx <= 0xF) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk34;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 0;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    } else if (idx == 0x16) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk38;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 0;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    } else if (idx == 0x18) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk3C;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 0;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    } else if (idx == 0x1B) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk40;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 0;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    } else if (idx == 0x19) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk44;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 0;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    } else if (idx == 0x1A) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk48;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 0;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    } else if (idx == 0x1C) {
        if (lbl_2_bss_3401BC != NULL) {
            v = lbl_2_bss_3401BC->unk4C;
            e = &lbl_2_bss_340140->unk68->elems[idx];
            e->unk4 = v;
            e->unkE = 0;
            e->unk5C = lbl_2_rodata_1080;
            e->unk58 = 1;
            e->unk59 = (v != 0);
            e->unk5A = (v != 0);
            e->unk60 = lbl_2_rodata_1080;
            e->unk54 = lbl_2_rodata_1078;
            e->unk5A = 1;
            e->unk5C = lbl_2_rodata_1080;
            e->unk59 = 1;
            e->unk5B = 3;
        }
    }
    idx = obj->index;
    o = &lbl_2_bss_1A8248->objs[idx];
    arr = lbl_2_bss_340140->unk2D94;
    if (arr != NULL) {
        o->unkA6 = 0;
        arr[idx].unk0 = (void *) lbl_2_data_30900[0];
    }
    obj->state = 1;
}
