#define REP_HEADER_DATA_FN getRepHeaderData_rep0610
#include "debug/rep_0610.h"
#include "debug/rep_0010.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800bd3a0.h"
#include "Unknown/File_0x800bd3cc.h"
#include "Unknown/File_0x800bd3ec.h"
#include "Unknown/File_0x800bd300.h"
#include "Unknown/File_0x800b2b74.h"
#include "Unknown/DisplayObject.h"
#include "Unknown/sub.h"
#include "Unknown/File_0x800bfe90.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/mtx.h"
#include "Dolphin/OS/OSUtil.h"
#include "C3/control.h"
#include "C3/anim.h"
#include "C3/actor.h"
#include "stl/mem.h"

#define BTN_HELD (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 0))
#define BTN_PRESSED (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 2))
#define BTN_REPEAT (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 4))

extern u8 lbl_80366158[0x30];

extern u32 lbl_80108B90;
extern u8 drawStadiumRelated;
extern void fn_800324EC(u16 id, s32 a, s32 b);
extern void fn_8002955C(Vec *pos, s32 arg);
extern void fn_80031CA4(Vec *pos, void *params);
extern void fn_80030D88(Vec *start, Vec *dir, void *slot, s32 arg);
extern void fn_80037AA0(void *buf, s32 a, void (*cb)(BOOL), u16 count, void *data);
extern void fn_800385F0(void *buf, f32 a, f32 b, f32 c, f32 d);
extern void fn_8004B208(s32 a, s32 b, s32 c);
extern void fn_800BD670(u32 a, void *b);
extern void fn_80026134(s32 a, Vec *v);
extern void fn_80026130(s32 a, void *p, f32 f);
extern void fn_800A7D4C(s32 arg0, void *arg1);
extern void fn_800B2C88(void *model, u16 idx, void *out);
extern void fn_800B806C(s32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h);
extern void fn_80052D70(void);
extern void minigamesSetSomePointers(void);
extern void fn_8002F258(Vec *pos, s32 id, void *params);
extern void fn_8002F1AC(Vec *pos, s32 id);
extern void fn_80039A4C(void);

static u32 lbl_1_bss_60E4;
static u8 lbl_1_bss_60A4[0x36];
static DbgBuf67E0 lbl_1_bss_67E0;
static DbgBuf68FC lbl_1_bss_68FC;
static DbgSel lbl_1_bss_6940[2];
static u32 lbl_1_bss_5F7C;
static s32 lbl_1_bss_5F58;
static u8 lbl_1_bss_5F72;
static u8 lbl_1_bss_5F78;
static f32 lbl_1_bss_5F74;
static u8 lbl_1_bss_5F73;
static u8 lbl_1_bss_5F71;
static u8 lbl_1_bss_5F70;
static u32 lbl_1_bss_5F6C;
static u8 lbl_1_bss_5F69;
static u8 lbl_1_bss_5F68;
static f32 lbl_1_bss_5F64;
static u8 lbl_1_bss_5F62;
static u16 lbl_1_bss_5F60;
static u32 lbl_1_bss_5F5C;
static DbgSlotEnt lbl_1_bss_3218[9];
static u8 lbl_1_bss_3216;
static u8 lbl_1_bss_3215;
static u8 lbl_1_bss_3214;
static DbgBuf30C0 lbl_1_bss_30C0;
static u32 lbl_1_bss_30BC;
static u8 lbl_1_bss_30B8;
static u32 lbl_1_bss_30A8;
static u32 lbl_1_bss_3098;
static s16 lbl_1_bss_30B4;
static u32 lbl_1_bss_30B0;
static u16 lbl_1_bss_30A4;
static u32 lbl_1_bss_30A0;
static u32 lbl_1_bss_309C;
static u32 lbl_1_bss_3094;
static u8 lbl_1_bss_3090;
static u32 lbl_1_bss_3084;
static u8 lbl_1_bss_3081;
static u8 lbl_1_bss_3078;
static u32 lbl_1_bss_307C;
static DbgGaugeLink *lbl_1_bss_67B8[10];

static DbgRowTbl lbl_1_data_F4D4;
static DbgDrawRow lbl_1_data_F4F8[2];
static f32 lbl_1_data_F568;
static u16 lbl_1_data_F56C;
static u16 lbl_1_data_F56E;
static u32 lbl_1_data_F4DC[3];
static u16 lbl_1_data_F17C[6];
static u32 lbl_1_data_F2A0[21];
static s32 lbl_1_data_F0BC[20];
static s32 lbl_1_data_F10C[26];
static s32 *lbl_1_data_F174[2];
static s32 lbl_1_data_F084;
static s32 lbl_1_data_F088;
static f32 lbl_1_data_F08C[4];
static f32 lbl_1_data_F0A0;
static u8 lbl_1_data_F0A8[0x14];
static s32 *lbl_1_data_F278[3];
static u8 lbl_1_data_F284[0x1C];
static f32 lbl_1_data_ADC0;
static u32 lbl_1_data_ADC4[7];
static s16 lbl_1_data_A978[0x6E];
static DbgDrawRow lbl_1_data_AA54[2];
static DbgDrawRow lbl_1_data_AAC4[2];
static DbgDrawRow lbl_1_data_AB34[2];
static u8 lbl_1_data_ABA8[0xE8];
static f32 lbl_1_data_AD0C[3];
static u32 teamStarModelFileDescriptorDebug[4];
static u32 lbl_1_data_A940[14];
static f32 lbl_1_data_F570[6];
static u8 lbl_1_data_2390[8];
static u16 lbl_1_data_1DC0[0x2C];
static u16 lbl_1_data_1E18[0x81];

// .text:0x00017D90 size:0x16C
void fn_1_17D90(void) {
    fn_800AD038(*(void **)(lbl_80366158 + 8));
    currentDrawingItem->state = 0;
    currentDrawingItem->func = fn_1_17B5C;
    fn_1_D7A4(0);
    while ((s8)lbl_1_data_F4D4.tbl[lbl_1_data_F4D4.cur].name[0] != 0) {
        lbl_1_data_F4D4.cur++;
    }
}

// .text:0x00017B5C size:0x234
void fn_1_17B5C(void) {
    s32 i;
    s32 first;
    lbl_1_bss_5F62 = -1;
    lbl_1_bss_5F60 = 4;
    for (i = 0; i < 0x36; i++) {
        lbl_1_bss_60A4[i] = lbl_1_data_A978[i] != -1;
    }
    for (first = 0; first < 7; first++) {
        if (lbl_1_data_2390[first] != 0) {
            break;
        }
    }
    lbl_1_bss_68FC.f40[0] = 0;
    lbl_1_bss_6940[0].f44 = first;
    lbl_1_bss_6940[0].f45 = 0;
    lbl_1_bss_6940[0].f46 = 0;
    lbl_1_bss_5F5C = 0;
    currentDrawingItem->func = fn_1_176EC;
    fn_80052D70();
}

static inline void dbgMoveCamera(void) {
    u8 *in = (u8 *)&AtBat_ButtonInput1;
    DbgActor *a = &hugeAnimStruct.slots[lbl_1_bss_5F73];
    f32 rt = in[0x15] / 768.0f;
    f32 sx = (s8)in[0x10] / 768.0f;
    f32 lt = in[0x14] / 768.0f;
    f32 sy = (s8)in[0x11] / 768.0f;
    a->pos.x += sx;
    a->pos.y = a->pos.y + rt - lt;
    a->pos.z += sy;
    lbl_1_data_AD0C[0] -= (s8)in[0x13] * 0.001953125f;
    lbl_1_data_AD0C[1] -= (s8)in[0x12] * 0.001953125f;
    a->rotX = lbl_1_data_AD0C[0];
    a->rotY = lbl_1_data_AD0C[1];
    a->rotZ = lbl_1_data_AD0C[2];
}

// .text:0x000179CC size:0x190
#pragma dont_inline on
void fn_1_179CC(void) {
    switch (lbl_1_bss_5F72) {
    case 0:
        fn_1_121D4(&lbl_1_bss_67E0);
        break;
    case 1:
        dbgMoveCamera();
        break;
    }
}
#pragma dont_inline reset

// .text:0x00017954 size:0x78
void fn_1_17954(void) {
    Mtx44 m;
    C_MTXFrustum(m, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(m, GX_PERSPECTIVE);
}

#pragma dont_inline on
// .text:0x0001770C size:0x248
void fn_1_1770C(void) {
    return;
}
#pragma dont_inline reset

// .text:0x000176EC size:0x20
void fn_1_176EC(void) {
    fn_1_1496C();
}

#pragma dont_inline on
// .text:0x00016978 size:0xD74
void fn_1_16978(void) {
    return;
}
#pragma dont_inline reset

// .text:0x000168C8 size:0xB0
void fn_1_168C8(void) {
    DbgScene *s = (DbgScene *)currentDrawingItem;
    if (lbl_1_bss_3084 == 0) {
        lbl_1_bss_3084 = 1;
        s->tick = OSGetTick();
        fn_1_135C0();
        s->tick = OSGetTick() - s->tick;
    } else {
        lbl_1_bss_3084 = 0;
        s->state = 0;
        if (hugeAnimStruct.slots[0].p8->f10 != 0) {
            currentDrawingItem->func = fn_1_1770C;
        } else {
            currentDrawingItem->func = fn_1_1770C;
        }
    }
}

// .text:0x000165E0 size:0x2E8
void fn_1_165E0(void) {
    DbgLight *light = hugeAnimStruct.lights[(s8)lbl_1_bss_5F70];
    s16 step = 0;
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_LEFT) {
        step = -1;
    } else if (b & INPUT_BUTTON_RIGHT) {
        step = 1;
    } else if (b & INPUT_BUTTON_UP) {
        if (--lbl_1_bss_307C < 0) {
            lbl_1_bss_307C = 9;
        }
    } else if (b & INPUT_BUTTON_DOWN) {
        if (++lbl_1_bss_307C >= 10) {
            lbl_1_bss_307C = 0;
        }
    } else if (BTN_PRESSED & INPUT_BUTTON_B) {
        lbl_1_bss_5F70 = 0;
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
    if (BTN_HELD & INPUT_BUTTON_X) {
        step *= 10;
    }
    switch (lbl_1_bss_307C) {
    case 0:
        lbl_1_bss_5F70 += step;
        if ((s8)lbl_1_bss_5F70 < 0) {
            lbl_1_bss_5F70 = 2;
        } else if ((s8)lbl_1_bss_5F70 >= 3) {
            lbl_1_bss_5F70 = 0;
        }
        break;
    case 1:
        light->r += step;
        if (light->r > 0xFF) {
            light->r = 0;
        }
        break;
    case 2:
        light->g += step;
        if (light->g > 0xFF) {
            light->g = 0;
        }
        break;
    case 3:
        light->b += step;
        if (light->b > 0xFF) {
            light->b = 0;
        }
        break;
    case 4:
        light->f40 += step;
        break;
    case 5:
        light->f44 += step;
        break;
    case 6:
        light->f48 += step;
        break;
    case 7:
        light->f58 += step;
        break;
    case 8:
        light->f5C += step;
        break;
    case 9:
        light->f60 += step;
        break;
    }
}

// .text:0x00016590 size:0x50
u32 fn_1_16590(void) {
    DbgSel *s = &lbl_1_bss_6940[lbl_1_bss_5F73];
    return hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[s->f44]->p4[s->f45][0];
}

// .text:0x00016558 size:0x38
u32 fn_1_16558(s32 a, s32 b) {
    return hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[a]->p4[b][0];
}

// .text:0x0001644C size:0x10C
void fn_1_1644C(void) {
    u8 idx = lbl_1_bss_5F73;
    DbgActor *act = hugeAnimStruct.actors[idx];
    s32 i;
    lbl_1_bss_5F69 ^= 1;
    if (act != NULL) {
        if (lbl_1_bss_5F69 == 0) {
            *(void **)((u8 *)&hugeAnimStruct.objs[idx] + 0x9C) = NULL;
        } else {
            *(void **)((u8 *)&hugeAnimStruct.objs[idx] + 0x9C) = (u8 *)act + 0x72;
        }
        fn_1_ECF8(lbl_1_bss_5F73, lbl_1_bss_6940[lbl_1_bss_5F73].f44, lbl_1_bss_5F69);
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_67B8[i] != NULL) {
                lbl_1_bss_67B8[i]->mode = 3;
            }
        }
    }
}

// .text:0x00016400 size:0x4C
void fn_1_16400(s8 delta) {
    u32 n = hugeAnimStruct.slots[lbl_1_bss_5F73].p8->count;
    lbl_1_bss_5F6C = (lbl_1_bss_5F6C + (n + delta)) % n;
}

// .text:0x000163FC size:0x4
void fn_1_163FC(void) {
}

#pragma dont_inline on
// .text:0x0001620C size:0x1F0
void fn_1_1620C(void) {
    return;
}
#pragma dont_inline reset

// .text:0x000161D0 size:0x3C
void fn_1_161D0(void) {
    lbl_1_bss_5F78 ^= 1;
    fn_800B9A9C((void *)lbl_1_bss_5F78, lbl_1_bss_5F74);
}

// .text:0x000160F8 size:0xD8
void fn_1_160F8(s32 dir) {
    f32 step = 0.01f;
    if (BTN_HELD & INPUT_BUTTON_X) {
        step *= 10.0f;
    }
    lbl_1_bss_5F74 += step * dir;
    if (lbl_1_bss_5F74 > 1.0f) {
        lbl_1_bss_5F74 = 0.0f;
    }
    if (lbl_1_bss_5F74 < 0.0f) {
        lbl_1_bss_5F74 = 1.0f;
    }
    fn_800B9A9C((void *)lbl_1_bss_5F78, lbl_1_bss_5F74);
}

// .text:0x000160D8 size:0x20
s32 fn_1_160D8(s8 a, s8 b) {
    if (a == b) {
        return 0xFF0F;
    }
    return 0xFFFF;
}

#pragma dont_inline on
// .text:0x00015CE0 size:0x3F8
void fn_1_15CE0(void) {
    return;
}
#pragma dont_inline reset

#pragma dont_inline on
// .text:0x00015760 size:0x580
void fn_1_15760(void) {
    return;
}
#pragma dont_inline reset

#pragma dont_inline on
// .text:0x0001540C size:0x354
void fn_1_1540C(void) {
    return;
}
#pragma dont_inline reset

// .text:0x000151F8 size:0x214
void fn_1_151F8(void) {
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_UP) {
        if (--lbl_1_bss_307C < 0) {
            lbl_1_bss_307C = 1;
        }
    } else if (b & INPUT_BUTTON_DOWN) {
        if (++lbl_1_bss_307C >= 2) {
            lbl_1_bss_307C = 0;
        }
    } else if (b & INPUT_BUTTON_LEFT) {
        switch (lbl_1_bss_307C) {
        case 0:
            fn_1_161D0();
            break;
        case 1:
            fn_1_160F8(-1);
            break;
        }
    } else if (b & INPUT_BUTTON_RIGHT) {
        switch (lbl_1_bss_307C) {
        case 0:
            fn_1_161D0();
            break;
        case 1:
            fn_1_160F8(1);
            break;
        }
    } else if (b & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
}

// .text:0x00015170 size:0x88
void fn_1_15170(void) {
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_B) {
        fn_800AD038(*(void **)(lbl_80366158 + 8));
        currentDrawingItem->state = 0;
        currentDrawingItem->func = fn_1_176EC;
        lbl_1_bss_30B8 = 1;
    } else if (b & INPUT_BUTTON_A) {
        lbl_1_bss_5F71 = 1;
    }
}

// .text:0x00014FB8 size:0x1B8
void fn_1_14FB8(void) {
    DbgSceneB *s = (DbgSceneB *)currentDrawingItem;
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_UP) {
        if (s->b20 != 0) {
            s->b20--;
        } else {
            s->b20 = 8;
        }
    } else if (b & INPUT_BUTTON_DOWN) {
        s->b20++;
        if (s->b20 == 9) {
            s->b20 = 0;
        }
    } else if (BTN_HELD & INPUT_BUTTON_A) {
        switch (s->b20) {
        case 0:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 3;
            }
            break;
        case 1:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 4;
            }
            break;
        case 2:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 5;
            }
            break;
        case 3:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 6;
            }
            break;
        case 4:
            if (BTN_PRESSED & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 2;
            }
            break;
        case 5:
            if (BTN_PRESSED & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 8;
            }
            break;
        case 6:
            if (BTN_PRESSED & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 7;
            }
            break;
        case 7:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 9;
            }
            break;
        case 8:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 10;
            }
            break;
        }
    } else if (BTN_PRESSED & INPUT_BUTTON_B) {
        lbl_1_bss_5F71 = 0;
        minigamesSetSomePointers();
    }
}

#pragma dont_inline on
// .text:0x0001496C size:0x64C
void fn_1_1496C(void) {
    return;
}
#pragma dont_inline reset

// .text:0x00014928 size:0x44
void fn_1_14928(void) {
    fn_800AD038(*(void **)(lbl_80366158 + 8));
    currentDrawingItem->currentDrawingItem->state = 1;
}

// .text:0x000148CC size:0x5C
void fn_1_148CC(void) {
    fn_800AD038(*(void **)(lbl_80366158 + 8));
    currentDrawingItem->state = 0;
    currentDrawingItem->func = fn_1_176EC;
    lbl_1_bss_30B8 = 1;
}

// .text:0x00014888 size:0x44
void fn_1_14888(DbgLightHolder *h) {
    if (lbl_1_bss_67E0.f118 != 0) {
        setLITLightPtr(lbl_1_bss_67E0.light30);
    } else {
        setLITLightPtr(h->light70);
    }
}

// .text:0x00014710 size:0x178
void fn_1_14710(DbgPairObj *o) {
    s32 i;
    u16 *p;
    u16 *tbl;
    for (i = 0; i < 0x78; i++) {
        o->a[i] = i;
    }
    p = lbl_1_data_1DC0;
    do {
        u16 x = o->b[p[0]];
        u16 y = o->b[p[1]];
        if (x != 0xFFFF && y != 0xFFFF) {
            o->a[x] = y;
            o->a[y] = x;
        }
        p += 2;
    } while (p[0] != 0xFFFF);
    switch (lbl_1_bss_68FC.f40[lbl_1_bss_5F73]) {
    case 0x10:
    case 0x2C:
    case 0x2D:
    case 0x2E:
    case 0x2F:
        tbl = lbl_1_data_1E18;
        break;
    default:
        tbl = NULL;
        break;
    }
    if (tbl == NULL) {
        return;
    }
    for (p = tbl; p[0] != 0xFFFF; p += 2) {
        u16 x = o->b[p[0]];
        u16 y = o->b[p[1]];
        if (x != 0xFFFF && y != 0xFFFF) {
            o->a[x] = y;
            o->a[y] = x;
        }
    }
}

#pragma dont_inline on
// .text:0x000135C0 size:0x1150
void fn_1_135C0(void) {
    return;
}
#pragma dont_inline reset

// .text:0x0001347C size:0x144
void fn_1_1347C(void) {
    Mtx44 m;
    lbl_1_bss_67E0.f10C = -0.8f;
    lbl_1_bss_67E0.f108 = 0.0f;
    lbl_1_bss_67E0.f110 = 0.0f;
    lbl_1_bss_67E0.fFC = 0.0f;
    lbl_1_bss_67E0.f100 = 0.0f;
    lbl_1_bss_67E0.f104 = 10.0f;
    C_MTXFrustum(m, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(m, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -0.001f, 1280.0f);
    lbl_1_bss_67E0.f114 = 0;
    lbl_1_bss_67E0.fF8 = 0.0f;
    lbl_1_bss_67E0.fF0 = 0;
    lbl_1_bss_67E0.fF2 = 0;
}

#pragma dont_inline on
// .text:0x000131E4 size:0x298
void fn_1_131E4(void) {
    return;
}
#pragma dont_inline reset

#pragma dont_inline on
// .text:0x00012F8C size:0x258
void fn_1_12F8C(void) {
    return;
}
#pragma dont_inline reset

// .text:0x00012F18 size:0x74
void fn_1_12F18(DbgScene *s) {
    fn_1_12820(hugeAnimStruct.objs, (u8 *)s + 8);
    if (lbl_1_data_A978[(u8)lbl_1_bss_68FC.f40] >= 0) {
        fn_800BD670(lbl_1_bss_5F7C, (u8 *)s + 8);
    }
}

#pragma dont_inline on
// .text:0x000129D0 size:0x548
void fn_1_129D0(void) {
    return;
}
#pragma dont_inline reset

#pragma dont_inline on
// .text:0x00012820 size:0x1B0
void fn_1_12820(void *a, void *b) {
    return;
}
#pragma dont_inline reset

// .text:0x000126CC size:0x154
void fn_1_126CC(void) {
    dbgMoveCamera();
}

#pragma dont_inline on
// .text:0x000121D4 size:0x4F8
void fn_1_121D4(void *a) {
    return;
}
#pragma dont_inline reset

#pragma dont_inline on
// .text:0x00011F08 size:0x2CC
void fn_1_11F08(void) {
    return;
}
#pragma dont_inline reset

#pragma dont_inline on
// .text:0x00011D00 size:0x208
void fn_1_11D00(void) {
    return;
}
#pragma dont_inline reset

// .text:0x00011C98 size:0x68
void fn_1_11C98(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(hugeAnimStruct.lights[i], lbl_1_bss_68FC.mtx10);
    }
}

#pragma dont_inline on
// .text:0x00011714 size:0x584
void fn_1_11714(void) {
    return;
}
#pragma dont_inline reset

// .text:0x000116EC size:0x28
void fn_1_116EC(void *tex) {
    SetDisplayStateTexture(tex, 0, 0);
}

#pragma dont_inline on
// .text:0x0001125C size:0x490
void fn_1_1125C(void) {
    return;
}
#pragma dont_inline reset

#pragma dont_inline on
// .text:0x00010E2C size:0x430
void fn_1_10E2C(void *a, void *b, u32 c, u32 d, u32 e) {
    return;
}
#pragma dont_inline reset

// .text:0x00010CEC size:0x140
void fn_1_10CEC(DbgBlob *blob) {
    if (lbl_1_data_ABA8[0] == 0) {
        Mtx m;
        Mtx buf;
        s32 i;
        DbgActor *a = &hugeAnimStruct.slots[lbl_1_bss_5F73];
        PSMTXTrans(m, a->pos.x, a->pos.y, a->pos.z);
        PSMTXConcat(blob->mtx8, m, m);
        for (i = 0; i < hugeAnimStruct.objs[lbl_1_bss_5F73].model->count; i++) {
            u32 c0, c1, c2;
            if (i != lbl_1_bss_5F6C) {
                c0 = 0x80008080;
                c1 = 0x80800080;
                c2 = 0x00808080;
            } else {
                u8 t = lbl_1_bss_3090++;
                if (t & 0x20) {
                    c0 = 0xFF8080FF;
                    c1 = 0x80FF80FF;
                    c2 = 0x8080FFFF;
                } else {
                    c0 = 0xFFFFFFFF;
                    c1 = 0xFFFFFFFF;
                    c2 = 0xFFFFFFFF;
                }
            }
            fn_800B2C88(hugeAnimStruct.objs[lbl_1_bss_5F73].model, i, buf);
            fn_1_10E2C(buf, m, c0, c1, c2);
        }
    }
}

#pragma dont_inline on
// .text:0x00010ACC size:0x220
void fn_1_10ACC(void) {
    return;
}
#pragma dont_inline reset

// .text:0x00010AA4 size:0x28
void fn_1_10AA4(DbgGauge *g, f32 v) {
    g->value = v;
    g->dirty = TRUE;
    if (lbl_1_bss_67B8[0] != NULL) {
        lbl_1_bss_67B8[0]->value = v;
    }
}

#pragma dont_inline on
// .text:0x000107B8 size:0x2EC
void fn_1_107B8(void) {
    return;
}
#pragma dont_inline reset

// .text:0x0001073C size:0x7C
void fn_1_1073C(DbgActor *a) {
    Vec v;
    v.x = lbl_1_bss_67E0.f108 - a->pos.x;
    v.y = lbl_1_bss_67E0.f10C - a->pos.y;
    v.z = lbl_1_bss_67E0.f110 - a->pos.z;
    fn_80026134(0, &v);
    fn_80026130(0, lbl_1_data_ADC4, lbl_1_data_ADC0);
}

// .text:0x000106C4 size:0x78
void fn_1_106C4(void) {
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_UP) {
        return;
    }
    if (b & INPUT_BUTTON_DOWN) {
        return;
    }
    if (b & INPUT_BUTTON_LEFT) {
        lbl_1_bss_3081 ^= 1;
        return;
    }
    if (b & INPUT_BUTTON_RIGHT) {
        lbl_1_bss_3081 ^= 1;
        return;
    }
    if (b & INPUT_BUTTON_A) {
        return;
    }
    if (!(b & INPUT_BUTTON_B)) {
        return;
    }
    lbl_1_bss_307C = 0;
    lbl_1_bss_5F71 = 1;
}

// .text:0x000106B4 size:0x10
void fn_1_106B4(void) {
    lbl_1_bss_3098 = 0;
}

// .text:0x000106A4 size:0x10
u32 fn_1_106A4(void) {
    return lbl_1_bss_3098;
}

// .text:0x00010670 size:0x34
void fn_1_10670(void) {
    DbgScene *d = (DbgScene *)insertGraphicDrawingFunction(fn_1_10560, 11);
    d->state = 0;
}

// .text:0x00010560 size:0x110
void fn_1_10560(void) {
    switch (currentDrawingItem->state) {
    case 0:
        lbl_1_bss_3094 = (u32)ARAMTransfer(teamStarModelFileDescriptorDebug, 0, 0, 0);
        currentDrawingItem->state = 1;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            lbl_1_bss_3098 = lbl_1_bss_3094 + *(u32 *)lbl_1_bss_3094;
            convertTextureHeader((void *)lbl_1_bss_3098);
            lbl_1_bss_60E4 = (u32)ARAMTransfer(lbl_1_data_A940, 0, 1, 0);
            currentDrawingItem->state = 2;
        }
        break;
    case 2:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            convertTextureHeader((void *)lbl_1_bss_60E4);
            removeCurrentDrawingItem();
        }
        break;
    }
}

// .text:0x00010458 size:0x108
void fn_1_10458(void) {
    if (lbl_1_bss_3098 == 0) {
        if (lbl_1_bss_3094 == 0) {
            DbgScene *d = (DbgScene *)insertGraphicDrawingFunction(fn_1_10560, 11);
            d->state = 0;
        }
    } else {
        u16 b = BTN_REPEAT;
        if (b & INPUT_BUTTON_UP) {
            if (lbl_1_bss_307C != 0) {
                lbl_1_bss_307C--;
            } else {
                lbl_1_bss_307C = 6;
            }
        } else if (b & INPUT_BUTTON_DOWN) {
            lbl_1_bss_307C++;
            if (lbl_1_bss_307C == 7) {
                lbl_1_bss_307C = 0;
            }
        } else if (!(b & INPUT_BUTTON_LEFT) && !(b & INPUT_BUTTON_RIGHT)) {
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = lbl_1_bss_307C + lbl_1_bss_5F71 + 1;
                lbl_1_bss_307C = 0;
            } else if (b & INPUT_BUTTON_B) {
                lbl_1_bss_307C = 0;
                lbl_1_bss_5F71 = 1;
            }
        }
    }
}

#pragma dont_inline on
// .text:0x00010044 size:0x414
void fn_1_10044(void) {
    return;
}
#pragma dont_inline reset

// .text:0x0000FB98 size:0x4AC
void fn_1_FB98(void) {
    u16 rep = BTN_REPEAT;
    s32 step;
    if (rep & INPUT_BUTTON_UP) {
        if (lbl_1_bss_307C != 0) {
            lbl_1_bss_307C--;
        } else {
            lbl_1_bss_307C = 7;
        }
    } else if (rep & INPUT_BUTTON_DOWN) {
        lbl_1_bss_307C++;
        if (lbl_1_bss_307C == 8) {
            lbl_1_bss_307C = 0;
        }
    } else if (rep & INPUT_BUTTON_LEFT) {
        u16 held = BTN_HELD;
        if (held & INPUT_BUTTON_X) {
            step = 10;
        } else if (held & INPUT_BUTTON_Y) {
            step = 100;
        } else {
            step = 1;
        }
        switch (lbl_1_bss_307C) {
        case 0:
            if (--lbl_1_bss_309C < 0) {
                lbl_1_bss_309C = 13;
            }
            break;
        case 1:
            lbl_1_data_F0A0 -= 0.1 * step;
            break;
        case 2:
            lbl_1_data_F08C[0] -= 0.0001 * step;
            break;
        case 3:
            lbl_1_data_F08C[1] -= 0.0001 * step;
            break;
        case 4:
            lbl_1_data_F08C[2] -= 0.0001 * step;
            break;
        case 5:
            lbl_1_data_F08C[3] -= 0.0001 * step;
            break;
        case 6:
            lbl_1_data_F084 -= step;
            if (lbl_1_data_F084 < 1) {
                lbl_1_data_F084 = 1;
            }
            break;
        case 7:
            lbl_1_data_F088 -= step;
            if (lbl_1_data_F088 < 0) {
                lbl_1_data_F088 = 0;
            }
            break;
        }
    } else if (rep & INPUT_BUTTON_RIGHT) {
        u16 held = BTN_HELD;
        if (held & INPUT_BUTTON_X) {
            step = 10;
        } else if (held & INPUT_BUTTON_Y) {
            step = 100;
        } else {
            step = 1;
        }
        switch (lbl_1_bss_307C) {
        case 0:
            if (++lbl_1_bss_309C >= 14) {
                lbl_1_bss_309C = 0;
            }
            break;
        case 1:
            lbl_1_data_F0A0 += 0.1 * step;
            break;
        case 2:
            lbl_1_data_F08C[0] += 0.0001 * step;
            break;
        case 3:
            lbl_1_data_F08C[1] += 0.0001 * step;
            break;
        case 4:
            lbl_1_data_F08C[2] += 0.0001 * step;
            break;
        case 5:
            lbl_1_data_F08C[3] += 0.0001 * step;
            break;
        case 6:
            lbl_1_data_F084 += step;
            break;
        case 7:
            lbl_1_data_F088 += step;
            if (lbl_1_data_F088 > 0xFF) {
                lbl_1_data_F088 = 0xFF;
            }
            break;
        }
    } else if (BTN_HELD & INPUT_BUTTON_A) {
        if (BTN_PRESSED & INPUT_BUTTON_A) {
            lbl_1_bss_30A0 = (lbl_1_bss_30A0 + 1) % 16;
        }
    } else if (BTN_REPEAT & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000F798 size:0x400
void fn_1_F798(s32 *vals, u8 *map, s32 n) {
    s32 s, m, l;
    u16 held = BTN_HELD;
    u16 rep;
    u8 v;
    if (held & INPUT_BUTTON_X) {
        s = 10;
        m = 100;
        l = 10000;
    } else if (held & INPUT_BUTTON_Y) {
        s = 20;
        m = 10000;
        l = 1000000;
    } else {
        s = 1;
        m = 1000;
        l = 100000;
    }
    rep = BTN_REPEAT;
    if (rep & INPUT_BUTTON_UP) {
        if (lbl_1_bss_307C != 0) {
            lbl_1_bss_307C--;
        } else {
            lbl_1_bss_307C = n - 1;
        }
        return;
    }
    if (rep & INPUT_BUTTON_DOWN) {
        lbl_1_bss_307C++;
        if (lbl_1_bss_307C == n) {
            lbl_1_bss_307C = 0;
        }
        return;
    }
    if (rep & INPUT_BUTTON_LEFT) {
        v = map[lbl_1_bss_307C];
        switch (v) {
        case 1:
            vals[v] = (vals[v] + 0x29) % 0x2A;
            break;
        case 2:
            vals[2] -= s;
            if (vals[2] < 1) {
                vals[2] = 1;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
        case 20:
            if (vals[v] - m > 0) {
                vals[v] -= m;
            }
            break;
        case 6:
            vals[6] -= s;
            if (vals[6] < 1) {
                vals[6] = 1;
            }
            if (vals[7] > vals[6]) {
                vals[7] = vals[6];
            }
            break;
        case 7:
        case 11:
        case 21:
        case 22:
            vals[v] -= s;
            if (vals[map[lbl_1_bss_307C]] < 0) {
                vals[map[lbl_1_bss_307C]] = 0;
            }
            break;
        case 10:
            vals[v] ^= 1;
            break;
        case 12:
        case 13:
            vals[v] -= l;
            if (vals[map[lbl_1_bss_307C]] < 0) {
                vals[map[lbl_1_bss_307C]] = 0;
            }
            break;
        case 23:
        case 24:
            vals[v] -= m;
            break;
        case 14:
        case 15:
            vals[v] -= l;
            /* fallthrough */
        case 16: {
            s32 c = (vals[16] >> 8) & 0xFF;
            c -= s;
            if (c < 0) {
                c = 0;
            }
            vals[16] = c * 0x1010100;
            break;
        }
        }
    } else if (rep & INPUT_BUTTON_RIGHT) {
        v = map[lbl_1_bss_307C];
        switch (v) {
        case 1:
            vals[v] = (vals[v] + 1) % 0x2A;
            break;
        case 2:
            vals[2] += s;
            break;
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
        case 20:
            vals[v] += m;
            break;
        case 6:
            vals[6] += s;
            break;
        case 7:
            vals[7] += s;
            if (vals[7] > vals[6]) {
                vals[7] = vals[6];
            }
            break;
        case 11:
        case 21:
            vals[v] += s;
            if (vals[map[lbl_1_bss_307C]] > 0xFF) {
                vals[map[lbl_1_bss_307C]] = 0xFF;
            }
            break;
        case 22:
            vals[v] += s;
            break;
        case 10:
            vals[v] ^= 1;
            break;
        case 12:
        case 13:
            vals[v] += l;
            break;
        case 23:
        case 24:
            vals[v] += m;
            break;
        case 14:
        case 15:
            vals[v] += l;
            break;
        case 16: {
            s32 c = (vals[16] >> 8) & 0xFF;
            c += s;
            if (c > 0xFF) {
                c = 0xFF;
            }
            vals[16] = c * 0x1010100;
            break;
        }
        }
    }
}

// .text:0x0000F6E4 size:0xB4
void fn_1_F6E4(void) {
    Vec v = {0.0f, 0.0f, 10.0f};
    fn_1_F798(lbl_1_data_F0BC, lbl_1_data_F0A8, 12);
    if (BTN_REPEAT & INPUT_BUTTON_A) {
        lbl_1_data_F0BC[0] = lbl_1_bss_3098;
        fn_80031CA4(&v, lbl_1_data_F0BC);
    } else if (BTN_REPEAT & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000F50C size:0x1D8
void fn_1_F50C(void) {
    DbgSceneP *s = (DbgSceneP *)currentDrawingItem;
    DbgActor *a = &hugeAnimStruct.slots[lbl_1_bss_5F73];
    if (a != NULL) {
        a->pos.x = s->pos.x;
        a->pos.y = s->pos.y;
        a->pos.z = s->pos.z;
    }
    fn_80030D88(&s->pos, &s->vel, lbl_1_data_F10C, 5);
    if (s->b3E != 0) {
        s->b3E = 0;
        if (s->b3F != 0) {
            Vec p;
            getAnimRelatedCoordinates(0, 0x1E, (VecXYZ *)&p);
            p.y = 0.0f;
            fn_8002F258(&p, s->w38, lbl_1_data_F174[0]);
            getAnimRelatedCoordinates(0, 0x22, (VecXYZ *)&p);
            p.y = 0.0f;
            fn_8002F258(&p, s->w38 + 1, lbl_1_data_F174[0]);
        } else {
            fn_8002F258(&s->pos, s->w38, lbl_1_data_F174[0]);
        }
    } else {
        if (s->b3F != 0) {
            Vec p;
            getAnimRelatedCoordinates(0, 0x1E, (VecXYZ *)&p);
            p.y = 0.0f;
            fn_8002F1AC(&p, s->w38);
            getAnimRelatedCoordinates(0, 0x22, (VecXYZ *)&p);
            p.y = 0.0f;
            fn_8002F1AC(&p, s->w38 + 1);
        } else {
            fn_8002F1AC(&s->pos, s->w38);
        }
    }
    PSVECAdd(&s->vel, &s->acc, &s->vel);
    PSVECAdd(&s->pos, &s->vel, &s->pos);
    if (--s->h3C == 0) {
        removeCurrentDrawingItem();
    }
}

// .text:0x0000F37C size:0x190
void fn_1_F37C(void) {
    fn_1_F798(lbl_1_data_F10C, lbl_1_data_F0A8, 18);
    if (BTN_REPEAT & (INPUT_BUTTON_A | INPUT_BUTTON_START)) {
        DbgSceneP *d;
        u32 v = lbl_1_bss_3098;
        lbl_1_data_F10C[0] = v;
        lbl_1_data_F174[0][0] = v;
        lbl_1_data_F174[0][1] = 5;
        d = (DbgSceneP *)insertGraphicDrawingFunction(fn_1_F50C, currentDrawingItem->priority + 1);
        d->pos.x = 0.0f;
        d->pos.y = 0.0f;
        d->pos.z = 10.0f;
        d->vel.x = 0.0f;
        d->vel.y = 0.0f;
        d->vel.z = (s32)lbl_1_data_F10C[0x5C / 4] / 100000.0f;
        d->acc.x = 0.0f;
        d->acc.y = 0.0f;
        d->acc.z = (s32)lbl_1_data_F10C[0x60 / 4] / 100000.0f;
        d->h3C = 0x20;
        d->b3E = 1;
        d->w38 = lbl_1_bss_30A4;
        lbl_1_bss_30A4 += 2;
        d->b3F = (BTN_REPEAT >> 12) & 1;
    } else if (BTN_REPEAT & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000F2F8 size:0x84
void fn_1_F2F8(void) {
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_A) {
        lbl_80108B90 = lbl_1_bss_3098;
        fn_800324EC(lbl_1_data_F17C[0], 0, -1);
    } else if (b & INPUT_BUTTON_B) {
        lbl_80108B90 = 0;
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000F1D8 size:0x120
void fn_1_F1D8(void) {
    DbgSceneT *s = (DbgSceneT *)currentDrawingItem;
    DbgActor *a = hugeAnimStruct.actors[lbl_1_bss_5F73];
    Vec p;
    Control ctl;
    Mtx m;
    Vec v;
    getAnimRelatedCoordinates(0, s->w24, (VecXYZ *)&p);
    ctl.type = 0;
    CTRLSetRotation(&ctl, a->rotX, a->rotY, a->rotZ);
    CTRLBuildMatrix(&ctl, m);
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 1.0f;
    PSMTXMultVec(m, &v, &v);
    fn_80030D88(&p, &v, lbl_1_data_F278[0], 5);
    fn_80030D88(&p, &v, lbl_1_data_F278[1], 5);
    fn_80030D88(&p, &v, lbl_1_data_F278[2], 5);
    if (--s->w20 == 0) {
        removeCurrentDrawingItem();
    }
}

// .text:0x0000F0D0 size:0x108
void fn_1_F0D0(void) {
    fn_1_F798(lbl_1_data_F278[lbl_1_bss_30A8], lbl_1_data_F284, 16);
    if (BTN_REPEAT & INPUT_BUTTON_START) {
        lbl_1_bss_30A8 = (lbl_1_bss_30A8 + 1) % 3;
    } else if (BTN_HELD & INPUT_BUTTON_A) {
        if (BTN_PRESSED & INPUT_BUTTON_A) {
            u32 v = lbl_1_bss_3098;
            DbgSceneT *d;
            lbl_1_data_F278[2][0] = v;
            lbl_1_data_F278[1][0] = v;
            lbl_1_data_F278[0][0] = v;
            d = (DbgSceneT *)insertGraphicDrawingFunction(fn_1_F1D8, 0);
            d->w20 = 0xF0;
            d->w24 = 4;
        }
    } else if (BTN_REPEAT & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000F040 size:0x90
void fn_1_F040(void) {
    Vec v = {0.0f, -5.0f, 0.0f};
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_A) {
        lbl_1_data_F2A0[0] = lbl_1_bss_3098;
        fn_8002955C(&v, 0);
    } else if (b & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

#pragma dont_inline on
// .text:0x0000ECF8 size:0x348
void fn_1_ECF8(s32 a, s32 b, s32 c) {
    return;
}
#pragma dont_inline reset

// .text:0x0000EA20 size:0x2D8
void fn_1_EA20(void) {
    switch (lbl_1_bss_30B0) {
    case 0: {
        DbgActor *a;
        u32 (*arr)[3];
        s32 i;
        u8 *obj = (u8 *)&hugeAnimStruct.objs[lbl_1_bss_5F73];
        lbl_1_bss_5F68 = 1;
        lbl_1_bss_5F64 = 0.0f;
        *(f32 *)(obj + 0x34 + 0x5C) = 0.0f;
        *(u8 *)(obj + 0x34 + 0x59) = 1;
        lbl_1_bss_30B0 = 1;
        lbl_1_bss_5F58 = 0;
        a = &hugeAnimStruct.slots[lbl_1_bss_5F73];
        arr = a->tbl[lbl_1_bss_6940[lbl_1_bss_5F73].f44]->p4;
        for (i = 0; i < *(u16 *)((u8 *)arr + lbl_1_bss_6940[lbl_1_bss_5F73].f45 * 12 + 8); i++) {
            f32 f = ((f32 *)arr[lbl_1_bss_6940[lbl_1_bss_5F73].f45][1])[i * 4];
            if ((f32)lbl_1_bss_5F58 < f) {
                lbl_1_bss_5F58 = (s32)f;
            }
        }
        break;
    }
    case 1:
        if (BTN_PRESSED & INPUT_BUTTON_B) {
            lbl_1_bss_30B0 = 0;
            lbl_1_bss_5F71 = 1;
        } else if (BTN_REPEAT & INPUT_BUTTON_LEFT) {
            lbl_1_bss_30B4--;
            if (lbl_1_bss_30B4 < 0) {
                lbl_1_bss_30B4 = lbl_1_bss_5F58 - 2;
            }
        } else if (BTN_REPEAT & INPUT_BUTTON_RIGHT) {
            lbl_1_bss_30B4++;
            if (lbl_1_bss_30B4 > lbl_1_bss_5F58 - 2) {
                lbl_1_bss_30B4 = 0;
            }
        } else if (BTN_REPEAT & INPUT_BUTTON_A) {
            lbl_1_bss_5F68 = 0;
            fn_80039A4C();
            hugeAnimStruct.f3084 = lbl_1_bss_5F73;
            lbl_1_bss_30B0 = 2;
            hugeAnimStruct.actors[lbl_1_bss_5F73] = &hugeAnimStruct.slots[lbl_1_bss_5F73];
        }
        break;
    default:
        if (lbl_1_bss_30B0 - 2 == lbl_1_bss_30B4 * 2) {
            hugeAnimStruct.f3083 = 1;
        }
        lbl_1_bss_30B0++;
        if (BTN_PRESSED & INPUT_BUTTON_B) {
            lbl_1_bss_30B0 = 0;
            hugeAnimStruct.f3083 = 0;
        } else if (BTN_PRESSED & INPUT_BUTTON_A) {
            u8 *obj = (u8 *)&hugeAnimStruct.objs[lbl_1_bss_5F73];
            *(f32 *)(obj + 0x34 + 0x5C) = 0.0f;
            *(u8 *)(obj + 0x34 + 0x59) = 1;
            fn_80039A4C();
            hugeAnimStruct.f3084 = lbl_1_bss_5F73;
            lbl_1_bss_30B0 = 2;
            hugeAnimStruct.actors[lbl_1_bss_5F73] = &hugeAnimStruct.slots[lbl_1_bss_5F73];
        }
        break;
    }
}

// .text:0x0000E9F8 size:0x28
void fn_1_E9F8(DbgModel *m, s32 start, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        start++;
        if (start == m->count) {
            start = 0;
        }
    }
}

// .text:0x0000E8D4 size:0x124
void fn_1_E8D4(void) {
    fn_1_D7A4(0);
    while ((s8)lbl_1_data_F4D4.tbl[lbl_1_data_F4D4.cur].name[0] != 0) {
        lbl_1_data_F4D4.cur++;
    }
}

#pragma dont_inline on
// .text:0x0000E098 size:0x83C
void fn_1_E098(void) {
    return;
}
#pragma dont_inline reset

#pragma dont_inline on
// .text:0x0000DF14 size:0x184
void fn_1_DF14(void) {
    return;
}
#pragma dont_inline reset

// .text:0x0000DE1C size:0xF8
void fn_1_DE1C(void) {
    DbgSceneB *s = (DbgSceneB *)currentDrawingItem;
    switch (s->b14) {
    case 0:
        if ((s8)s->b15 == 0) {
            s->func = fn_1_D9B8;
        } else {
            while ((s8)s->b15-- != 0) {
                if (lbl_1_bss_3218[(s8)s->b15].f0 >= 0) {
                    DbgSceneB *d = (DbgSceneB *)insertGraphicDrawingFunction(fn_1_DF14, currentDrawingItem->priority + 1);
                    d->state = 0;
                    d->b14 = s->b15;
                    s->state = 0;
                    s->b14++;
                    break;
                }
            }
        }
        break;
    case 1:
        if (s->state != 0) {
            s->b14 = 0;
        }
        break;
    }
    fn_1_D8A0();
}

#pragma dont_inline on
// .text:0x0000D9B8 size:0x464
void fn_1_D9B8(void) {
    return;
}
#pragma dont_inline reset

// .text:0x0000D8A0 size:0x118
#pragma dont_inline on
void fn_1_D8A0(void) {
    fn_1_17954();
    fn_1_179CC();
    PSMTXCopy(lbl_1_bss_67E0.mtx0, lbl_1_bss_68FC.mtx10);
    fn_800A7D4C(7, &lbl_1_data_AA54[drawStadiumRelated]);
    if (lbl_1_bss_3078 != 0) {
        fn_800A7D4C(7, &lbl_1_data_AB34[drawStadiumRelated]);
    }
    fn_800A7D4C(7, &lbl_1_data_AAC4[drawStadiumRelated]);
    fn_1_129D0();
}
#pragma dont_inline reset

// .text:0x0000D7A4 size:0xFC
void fn_1_D7A4(s32 row) {
    DbgRow *r = (DbgRow *)((u8 *)lbl_1_data_F4D4.tbl + row * 0x50);
    DbgActor *act = &hugeAnimStruct.slots[lbl_1_bss_5F73];
    s32 i;
    for (i = 8; i >= 0; i--) {
        DbgRowEnt *s = &r->ent[i];
        DbgSlotEnt *e = &lbl_1_bss_3218[i];
        if ((s8)s->kind != 0) {
            DbgAnimEntry *tb;
            e->f0 = s->a;
            tb = act->tbl[e->f0];
            e->f2 = s->b;
            e->f6 = (s8)s->c;
            if (s->d == -2) {
                if (tb != NULL) {
                    e->f4 = *(f32 *)tb->p4[s->b][1];
                } else {
                    e->f4 = 0;
                }
            } else {
                e->f4 = s->d;
            }
        } else {
            e->f0 = -1;
            e->f6 = 0;
            e->f4 = 0;
        }
    }
}

// .text:0x0000D71C size:0x88
f32 fn_1_D71C(s32 idx) {
    DbgModel *m = hugeAnimStruct.objs[idx].model;
    u16 n = m->count;
    s32 i;
    for (i = 0; i < n; i++) {
        DbgPartData *d = m->parts[i]->data;
        if (d != NULL && d->flag != 0) {
            break;
        }
    }
    if (i < n) {
        return m->parts[i]->data->value;
    }
    return 0.0f;
}

u32 fn_1_D6E4(void) {
    s32 i = lbl_1_bss_3216;
    switch (i) {
    case 0:
    case 1:
    case 2:
        return lbl_1_data_F4DC[(u8)i];
    default:
        return 0;
    }
}

// .text:0x0000D6B4 size:0x30
void fn_1_D6B4(void) {
    if (lbl_1_bss_3216 == 0) {
        lbl_1_bss_3216 = 3;
    }
    lbl_1_bss_3216--;
}

// .text:0x0000D688 size:0x2C
void fn_1_D688(void) {
    lbl_1_bss_3216++;
    if (lbl_1_bss_3216 == 3) {
        lbl_1_bss_3216 = 0;
    }
}

// .text:0x0000D67C size:0xC
void fn_1_D67C(u8 value) {
    lbl_1_bss_3215 = value;
}

// .text:0x0000D660 size:0x1C
BOOL fn_1_D660(void) {
    return lbl_1_bss_3215 != 0;
}

// .text:0x0000D650 size:0x10
void fn_1_D650(void) {
    lbl_1_bss_3214 = TRUE;
}

// .text:0x0000D638 size:0x18
u8 fn_1_D638(void) {
    u8 v = lbl_1_bss_3214;
    lbl_1_bss_3214 = FALSE;
    return v;
}

// .text:0x0000D590 size:0xA8
void fn_1_D590(s32 a, s32 b, f32 v) {
    if (lbl_1_bss_3215 != 0) {
        if (lbl_1_bss_3216 == 0) {
            return;
        }
        if (lbl_1_bss_3216 == 2) {
            if ((s32)v == 0) {
                lbl_1_bss_3214 += (lbl_1_bss_3214 != 0);
            }
            if (lbl_1_bss_3214 == 3) {
                lbl_1_bss_3214 = 0;
            }
            if (lbl_1_bss_3214 != 2) {
                return;
            }
        }
        {
            s32 lvl = (s8)lbl_1_bss_5F62;
            if (lvl < 0) {
                lvl = 0;
            }
            fn_8004B208(a, b, lvl);
        }
    }
}

// .text:0x0000D4BC size:0xD4
void fn_1_D4BC(void) {
    DbgActor *a = hugeAnimStruct.slots;
    if (a != NULL) {
        VecXYZ p;
        a->flags = (s32)a->flags >> 1;
        a->flags = (a->flags & 0x1F) << 3;
        getAnimRelatedCoordinates(0, 0x1E, &p);
        if (a->pos.y - p.y < 0.3f) {
            a->flags |= 2;
        }
        getAnimRelatedCoordinates(0, 0x22, &p);
        if (a->pos.y - p.y < 0.3f) {
            a->flags |= 4;
        }
    }
    hugeAnimStruct.actors[0]->flags |= 1;
}

#pragma dont_inline on
// .text:0x0000D300 size:0x1BC
void fn_1_D300(void) {
    return;
}
#pragma dont_inline reset

// .text:0x0000D2F0 size:0x10
void fn_1_D2F0(void) {
    lbl_1_bss_30B8 = TRUE;
}

#pragma dont_inline on
// .text:0x0000D13C size:0x1B4
void fn_1_D13C(void) {
    return;
}
#pragma dont_inline reset

#pragma dont_inline on
// .text:0x0000CDC8 size:0x374
void fn_1_CDC8(void) {
    return;
}
#pragma dont_inline reset

// .text:0x0000CCC8 size:0x100
void fn_1_CCC8(void) {
    DbgScene *s = (DbgScene *)currentDrawingItem;
    f32 *fp = s->data;
    if (fp != NULL && fp[0] < fp[1]) {
        if (lbl_1_bss_5F69 != 0) {
            fn_800385F0(&lbl_1_bss_30C0, 1.0f, 0.5f, 0.1f, 1.0f);
        } else {
            fn_800385F0(&lbl_1_bss_30C0, -1.0f, 0.5f, 0.1f, 1.0f);
        }
        lbl_1_bss_30C0.f50 = lbl_1_data_F568;
        fn_80037AA0(&lbl_1_bss_30C0, 0, fn_1_CB9C, s->count, s->data);
        removeCurrentDrawingItem();
    }
}

// .text:0x0000CC24 size:0xA4
void fn_1_CC24(void) {
    if (lbl_1_bss_30BC == 0) {
        DbgScene *d;
        lbl_1_bss_30BC = 1;
        d = (DbgScene *)insertGraphicDrawingFunction(fn_1_CCC8, currentDrawingItem->priority + 1);
        if (lbl_1_bss_5F69 != 0) {
            d->data = lbl_1_bss_67B8[1];
            d->count = lbl_1_data_F56C;
        } else {
            d->data = lbl_1_bss_67B8[2];
            d->count = lbl_1_data_F56E;
        }
    }
}

// .text:0x0000CB9C size:0x88
void fn_1_CB9C(BOOL flag) {
    if (flag) {
        lbl_1_bss_30BC = 0;
    } else {
        PSMTXCopy(lbl_1_bss_30C0.mtx58, lbl_1_data_F4F8[drawStadiumRelated].mtx);
        fn_800A7D4C(8, &lbl_1_data_F4F8[drawStadiumRelated]);
    }
}

// .text:0x0000C9E0 size:0x1BC
void fn_1_C9E0(DbgBlob *blob) {
    Mtx m;
    Vec v;
    fn_1_F2C(4, 0, 0);
    PSMTXConcat(lbl_1_bss_68FC.mtx10, blob->mtx8, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZMode(1, GX_ALWAYS, 1);
    GXBegin(GX_LINES, GX_VTXFMT0, 6);
    GXPosition3f32(lbl_1_bss_30C0.f0[3], lbl_1_bss_30C0.f0[4], lbl_1_bss_30C0.f0[5]);
    GXColor1u32(0xFF0000FF);
    GXPosition3f32(lbl_1_bss_30C0.f0[0], lbl_1_bss_30C0.f0[1], lbl_1_bss_30C0.f0[2]);
    GXColor1u32(0x00FF00FF);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0xFF);
    PSVECScale(&lbl_1_bss_30C0.v128, lbl_1_data_F570[0], &v);
    GXPosition3f32(v.x, v.y, v.z);
    GXColor1u32(0xFF);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0xFFFFFFFF);
    PSVECScale(&lbl_1_bss_30C0.v140, lbl_1_data_F570[0], &v);
    GXPosition3f32(v.x, v.y, v.z);
    GXColor1u32(0xFFFFFFFF);
}

#pragma dont_inline on
// .text:0x0000C5AC size:0x434
void fn_1_C5AC(void) {
    return;
}
#pragma dont_inline reset
