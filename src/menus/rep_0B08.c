#include "menus/rep_0B08.h"
#include "menus/text_71EC4.h"
#include "header_rep_data.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "stl/math.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "C3/light/light.h"

// One of the character slots stored back to back at lbl_2_bss_1A8248 + 0x1610
// (stride 0xD8); the same layout as CssSlot, with every accessed field spelled out.
typedef struct Rep0B08Slot {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 _58[0x6C - 0x58];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ s32 index;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ s16 mode;
    /* 0x96 */ s16 unk96;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ s16 unk9A;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 unkA2;
    /* 0xA4 */ s16 unkA4;
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ s16 unkA8;
    /* 0xAA */ s16 unkAA;
    /* 0xAC */ s16 unkAC;
    /* 0xAE */ s16 unkAE;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ u8 unkB6;
    /* 0xB7 */ u8 unkB7;
    /* 0xB8 */ u8 unkB8;
    /* 0xB9 */ u8 unkB9;
    /* 0xBA */ u8 unkBA;
    /* 0xBB */ u8 unkBB;
    /* 0xBC */ u8 unkBC;
    /* 0xBD */ u8 unkBD;
    /* 0xBE */ u8 unkBE;
    /* 0xBF */ u8 unkBF;
    /* 0xC0 */ u8 unkC0;
    /* 0xC1 */ u8 unkC1;
    /* 0xC2 */ u8 unkC2;
    /* 0xC3 */ u8 state;
    /* 0xC4 */ u8 unkC4;
    /* 0xC5 */ u8 unkC5;
    /* 0xC6 */ u8 unkC6;
    /* 0xC7 */ u8 unkC7;
    /* 0xC8 */ u8 unkC8;
    /* 0xC9 */ u8 unkC9;
    /* 0xCA */ u8 unkCA;
    /* 0xCB */ s8 unkCB;
    /* 0xCC */ s8 unkCC;
    /* 0xCD */ s8 unkCD;
    /* 0xCE */ u8 unkCE;
    /* 0xCF */ s8 unkCF;
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 _D1[3];
    /* 0xD4 */ void (*handler)(struct Rep0B08Slot *slot);
} Rep0B08Slot; // size 0xD8

typedef void (*Rep0B08StateFn)(Rep0B08Slot *obj);

typedef struct {
    /* 0x0000 */ u8 _0000[0x1610];
    /* 0x1610 */ Rep0B08Slot slots[8];
} Rep0B08Menu;

#define MENU ((Rep0B08Menu *)lbl_2_bss_1A8248)

typedef struct {
    /* 0x000000 */ u8 _000000[0x197746];
    /* 0x197746 */ s16 unk197746;
    /* 0x197748 */ u8 _197748[0x197756 - 0x197748];
    /* 0x197756 */ s16 curAnim[8];
    /* 0x197766 */ u8 _197766[0x19783D - 0x197766];
    /* 0x19783D */ u8 unk19783D;
    /* 0x19783E */ u8 _19783E[0x197843 - 0x19783E];
    /* 0x197843 */ s8 unk197843;
    /* 0x197844 */ u8 _197844[0x197863 - 0x197844];
    /* 0x197863 */ u8 unk197863;
    /* 0x197864 */ u8 _197864[0x1978F1 - 0x197864];
    /* 0x1978F1 */ u8 unk1978F1;
} Rep0B08Anim;

typedef struct {
    /* 0x0 */ s16 anim;
    /* 0x2 */ s16 arg4;
    /* 0x4 */ u8 arg2;
    /* 0x5 */ u8 _5;
} Rep0B08AnimEntry;

#define ANIM lbl_2_bss_1A824C
#define REP_SLOT(idx) (&MENU->slots[idx])
#define SLOTS ((Rep0B08Slot *)(lbl_2_bss_1A8248 + 0x1610))


extern u8 *lbl_2_bss_1A8248;
extern Rep0B08Anim *lbl_2_bss_1A824C;
extern u8 inputParams[0x268];
extern u8 hugeAnimStruct[];
extern u8 lbl_2_data_2EA4[];
extern u8 lbl_2_data_3150[];
extern u8 lbl_2_data_3C84[];
extern s16 lbl_2_data_2E80[][3];
extern u8 lbl_2_data_3198[];
extern s16 lbl_2_data_3C20[];
extern s16 lbl_2_data_3ED4[];
extern f32 lbl_2_data_3F44[];
extern s16 *lbl_2_data_3C2C[];
extern f32 lbl_2_data_3EF4[];
extern f32 lbl_2_data_3F0C[];
extern f32 lbl_2_data_3F2C[];
extern f32 lbl_2_data_3F5C;
extern s16 lbl_2_data_3D30[][4];
extern s32 lbl_2_data_3C40[];
extern s32 lbl_2_data_3C5C[];

extern Rep0B08StateFn lbl_2_data_2A1F4[];
extern Rep0B08StateFn lbl_2_data_2A200[];
extern Rep0B08StateFn lbl_2_data_2A208[];
extern Rep0B08StateFn lbl_2_data_2A210[];
extern Rep0B08StateFn lbl_2_data_2A220[];
extern Rep0B08StateFn lbl_2_data_2A234[];
extern Rep0B08StateFn lbl_2_data_2A248[];
extern Rep0B08StateFn lbl_2_data_2A250[];
extern Rep0B08StateFn lbl_2_data_2A25C[];
extern Rep0B08StateFn lbl_2_data_2A268[];
extern Rep0B08StateFn lbl_2_data_2A274[];
extern Rep0B08StateFn lbl_2_data_2A280[];
extern Rep0B08StateFn lbl_2_data_2A28C[];
extern Rep0B08StateFn lbl_2_data_2A29C[];
extern Rep0B08StateFn lbl_2_data_2A2AC[];
extern Rep0B08StateFn lbl_2_data_2A2B8[];
extern Rep0B08StateFn lbl_2_data_2A2C4[];
extern Rep0B08StateFn lbl_2_data_2A2D4[];
extern Rep0B08StateFn lbl_2_data_2A2E0[];

f32 fn_2_4A18C(f32 angle);
void fn_2_8CD58(s32 idx, s16 a, u8 b, s32 c, s16 d, s32 e, s32 f);
s32 fn_2_4A2C4(f32 angle);
s16 fn_2_4A150(s16 angle);
f32 fn_2_4A1E8(f32 x);
s16 fn_2_4A234(f32 x, f32 y);
s16 fn_2_4A310(s16 a, s16 b);

extern u8 lbl_2_data_2A340[];
extern u8 AtBat_ButtonInput1[];
extern f32 lbl_2_bss_A170;
s32 fn_2_8CC88(s32 p);
void fn_2_46C88(s32 a, s32 b);
void fn_80062890(s32 flag);

void fn_2_9033C(s32 idx, void *src, f32 f);
int rand(void);
void fn_2_92654(s32 slot, u8 value);
void fn_2_8F73C(s32 idx, u8 val);

static void rep0B08TransitionSlot(s32 idx, u8 state) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    slot->state = state;
    slot->mode = 0;
}

static void rep0B08EnableSlot(s32 idx) {
    ((Rep0B08Slot *)(lbl_2_bss_1A8248 + idx * sizeof(Rep0B08Slot) + 0x1610))->unkC0 = 1;
}

static inline void rep0B08EnableObj(Rep0B08Slot *obj) {
    rep0B08EnableSlot(obj->index);
}

static inline void rep0B08CheckAnimCue(Rep0B08Slot *obj) {
    u8 kind = lbl_2_bss_1A8248[0x441C];
    s32 base = lbl_2_data_2E80[kind][0] * 2;
    s32 a = base - lbl_2_data_2E80[kind][2] * 2;
    s32 b = base - lbl_2_data_2E80[kind][1] * 2;
    if (obj->index == 0) {
        u8 *hp = hugeAnimStruct + 0xC04;
        if (hp != NULL && (*(s16 *)(hp + 0x68) == a || *(s16 *)(hp + 0x68) == b)) {
            if (kind == 5) {
                fn_80062890(1);
            } else {
                fn_80062890(0);
            }
        }
    }
}

static inline void rep0B08LookAtPartner(Rep0B08Slot *obj, s32 idx) {
    Rep0B08Slot *other = REP_SLOT((s8)obj->unkCE);
    Rep0B08Slot *self = REP_SLOT(idx);
    f32 heading = atan2(-(self->pos.x - other->pos.x), -(self->pos.z - other->pos.z));
    f32 diff = fn_2_4A18C(other->unk4C) - heading;
    if (other->state == 7 && (obj->mode == 0 || obj->mode == 1)) {
        if ((f32)fabs(diff) < 1.5707964f) {
            ANIM->unk1978F1 = 0;
        } else {
            ANIM->unk1978F1 = 2;
        }
    } else {
        ANIM->unk1978F1 = 1;
    }
}

static inline f32 rep0B08TurnToSlot(s32 idx, s32 other) {
    Rep0B08Slot *self = REP_SLOT(idx);
    Rep0B08Slot *o = REP_SLOT(other);
    f32 h = atan2(-(o->pos.x - self->pos.x), -(o->pos.z - self->pos.z));
    return fn_2_4A18C(self->unk4C) - h;
}

static inline u8 rep0B08FacingTarget(s32 idx, s32 other) {
    s16 point = MENU->slots[0].unkB0;
    Rep0B08Slot *self = REP_SLOT(idx);
    Rep0B08Slot *o = REP_SLOT(other);
    Vec target;
    f32 h;
    h = atan2(-(o->pos.x - self->pos.x), -(o->pos.z - self->pos.z));
    memcpy(&target, lbl_2_data_2EA4 + point * 12, 12);
    h -= (f32)atan2(-(target.x - self->pos.x), -(target.z - self->pos.z));
    if (h < 1.2217305898666382f && h > -1.2217305898666382f) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x00071C6C size:0x258 mapped:0x806B0D00
void fn_2_71C6C(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    Rep0B08Slot *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    rep0B08EnableSlot(idx);
    memcpy(&obj->unk74, lbl_2_data_2EA4 + MENU->slots[0].unkB0 * 0xC, 12);
    fn_2_6A450(idx, obj->unk74, obj->unk7C);
    obj->unkBA = 0xD;
    fn_2_68FBC(idx, 0);
    obj->mode = 1;
}

// .text:0x00071B80 size:0xEC mapped:0x806B0C14
void fn_2_71B80(Rep0B08Slot *obj) {
    u8 kind;
    s32 start;
    s32 endA;
    s32 endB;
    s32 frameA;
    s32 frameB;
    fn_2_69E1C(obj->index);
    kind = lbl_2_bss_1A8248[0x441C];
    start = lbl_2_data_2E80[kind][0] * 2;
    endA = lbl_2_data_2E80[kind][2] * 2;
    endB = lbl_2_data_2E80[kind][1] * 2;
    frameA = start - endA;
    frameB = start - endB;
    if (obj->index == 0) {
        u8 *anim = hugeAnimStruct + 0xC04;
        if (anim != NULL) {
            s16 frame = *(s16 *)(anim + 0x68);
            if (frame == frameA || frame == frameB) {
                if (kind == 5) {
                    fn_80062890(1);
                } else {
                    fn_80062890(0);
                }
            }
        }
    }
    if (obj->unk50 <= 0.0f) {
        obj->unkBA = 4;
        obj->unkC4 = 1;
        obj->mode = 2;
    }
}

// .text:0x00071A70 size:0x110 mapped:0x806B0B04
void fn_2_71A70(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    u8 kind;
    s32 start;
    s32 endA;
    s32 endB;
    s32 frameA;
    s32 frameB;
    fn_2_69E1C(idx);
    kind = lbl_2_bss_1A8248[0x441C];
    start = lbl_2_data_2E80[kind][0] * 2;
    endA = lbl_2_data_2E80[kind][2] * 2;
    endB = lbl_2_data_2E80[kind][1] * 2;
    frameA = start - endA;
    frameB = start - endB;
    if (obj->index == 0) {
        u8 *anim = hugeAnimStruct + 0xC04;
        if (anim != NULL) {
            s16 frame = *(s16 *)(anim + 0x68);
            if (frame == frameA || frame == frameB) {
                if (kind == 5) {
                    fn_80062890(1);
                } else {
                    fn_80062890(0);
                }
            }
        }
    }
    if (obj->unk38 <= 0.0f) {
        Rep0B08Slot *slot = REP_SLOT(idx);
        obj->unk34 = obj->unk4C;
        rep0B08TransitionSlot(idx, 3);
    }
}

// .text:0x00071A38 size:0x38 mapped:0x806B0ACC
void fn_2_71A38(Rep0B08Slot *obj) {
    lbl_2_data_2A1F4[obj->mode](obj);
}

// .text:0x00071098 size:0x9A0 mapped:0x806B012C
void fn_2_71098(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    BOOL flag = FALSE;
    s32 i;
    rep0B08EnableObj(obj);
    memcpy(&obj->unk74, lbl_2_data_2EA4 + MENU->slots[0].unkB0 * 12, 12);
    fn_2_6A450(idx, obj->unk74, obj->unk7C);
    obj->unkBA = 0xC;
    for (i = 1; i < 7; i++) {
        if (fn_2_68C80(idx, i)) {
            obj->unkCB = i;
            break;
        }
        obj->unkCB = -1;
    }
    if (obj->unkCB >= 2 && obj->unkCB <= 6) {
        rep0B08TurnToSlot(idx, obj->unkCB);
        flag = rep0B08FacingTarget(idx, obj->unkCB);
    }
    if (flag == 0) {
        fn_2_69E1C(idx);
    } else {
        fn_2_699D4(idx);
    }
    fn_2_68FBC(idx, 0);
    for (i = 1; i < 7; i++) {
        s32 nearby = fn_2_68C80(idx, i);
        if (nearby && i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
                obj->unkC4 = 2;
                obj->unkCB = (u8)i;
                rep0B08TransitionSlot(idx, 3);
                return;
            }
        if (nearby && i >= 2 && i <= 6) {
                obj->unkBA = 4;
                obj->unkC4 = 1;
                obj->unkB2 = fn_2_689CC(0);
                rep0B08TransitionSlot(idx, 4);
                return;
            }
        obj->unkCB = -1;
        obj->mode = 1;
    }
    if (obj->unkCD == 1) {
        rep0B08LookAtPartner(obj, idx);
        obj->unkBA = 4;
        obj->unkC4 = 1;
        obj->unkB2 = fn_2_689CC(0);
        rep0B08TransitionSlot(idx, 4);
    }
    if (!(obj->unk50 <= 0.0f)) {
        return;
    }
    obj->unkBA = 9;
    obj->unkC4 = 1;
    if (ANIM->unk19783D == 0) {
        MENU->slots[0].unkB2 = MENU->slots[0].unkB0;
    } else {
        MENU->slots[0].unkB2 = MENU->slots[0].unkAE;
    }
    fn_2_68FBC(idx, 1);
    obj->unkC4 = 1;
    obj->unkB2 = fn_2_689CC(0);
    rep0B08TransitionSlot(idx, 4);
}

// .text:0x000709A0 size:0x6F8 mapped:0x806AFA34
void fn_2_709A0(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    BOOL flag = FALSE;
    s32 i;
    for (i = 1; i < 7; i++) {
        if (fn_2_68C80(idx, i)) {
            obj->unkCB = i;
            break;
        }
        obj->unkCB = -1;
    }
    if (obj->unkCB >= 2 && obj->unkCB <= 6) {
        rep0B08TurnToSlot(idx, obj->unkCB);
        flag = rep0B08FacingTarget(idx, obj->unkCB);
    }
    for (i = 1; i < 7; i++) {
        BOOL hit = fn_2_68C80(idx, i);
        if (hit && i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
            obj->unkC4 = 2;
            obj->unkCB = i;
            rep0B08TransitionSlot(idx, 3);
            return;
        }
        if (hit && i >= 2 && i <= 6) {
            obj->unkBA = 4;
            obj->unkC4 = 1;
            obj->unkB2 = fn_2_689CC(0);
            rep0B08TransitionSlot(idx, 4);
            return;
        }
        obj->unkCB = -1;
    }
    if (flag == FALSE) {
        fn_2_69E1C(idx);
    } else {
        fn_2_699D4(idx);
    }
    rep0B08CheckAnimCue(obj);
    if (obj->unk50 <= 0.0f) {
        obj->unkBA = 4;
        obj->unkC4 = 1;
        if (ANIM->unk19783D == 0) {
            MENU->slots[0].unkB2 = MENU->slots[0].unkB0;
        } else {
            MENU->slots[0].unkB2 = MENU->slots[0].unkAE;
        }
        obj->mode = 2;
        return;
    }
    if (obj->unkCD == 1) {
        rep0B08LookAtPartner(obj, idx);
        obj->unkBA = 4;
        obj->unkC4 = 1;
        obj->unkB2 = fn_2_689CC(0);
        rep0B08TransitionSlot(idx, 4);
    }
}

// .text:0x000705C0 size:0x3E0 mapped:0x806AF654
void fn_2_705C0(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 i;
    fn_2_69E1C(idx);
    rep0B08CheckAnimCue(obj);
    if (obj->unk38 <= 0.0f) {
        obj->unk34 = obj->unk4C;
        rep0B08TransitionSlot(idx, 4);
    }
    for (i = 1; i < 7; i++) {
        if (fn_2_68C80(idx, i) && i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
            obj->unkC4 = 2;
            obj->unkCB = i;
            rep0B08TransitionSlot(idx, 3);
            return;
        }
        obj->unkCB = -1;
    }
    if (obj->unkCD == 1) {
        rep0B08LookAtPartner(obj, idx);
        obj->unkBA = 4;
        obj->unkC4 = 1;
        obj->unkB2 = fn_2_689CC(0);
        rep0B08TransitionSlot(idx, 4);
    }
}

// .text:0x00070588 size:0x38 mapped:0x806AF61C
void fn_2_70588(Rep0B08Slot *obj) {
    lbl_2_data_2A200[obj->mode](obj);
}

// .text:0x000704AC size:0xDC mapped:0x806AF540
void fn_2_704AC(Rep0B08Slot *obj) {
    MENU->slots[obj->index].unkC0 = 1;
    fn_2_68FBC(obj->index, 1);
    obj->mode = 1;
}

// .text:0x000704A0 size:0xC mapped:0x806AF534
void fn_2_704A0(Rep0B08Slot *obj) {
    obj->mode = 2;
}

// .text:0x00070494 size:0xC mapped:0x806AF528
void fn_2_70494(Rep0B08Slot *obj) {
    obj->mode = 2;
}

// .text:0x0007045C size:0x38 mapped:0x806AF4F0
void fn_2_7045C(Rep0B08Slot *obj) {
    lbl_2_data_2A208[obj->mode](obj);
}

// .text:0x00070110 size:0x34C mapped:0x806AF1A4
void fn_2_70110(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 i;
    rep0B08EnableSlot(idx);
    fn_2_68FBC(obj->index, 1);
    if (obj->unkCD == 1) {
        rep0B08LookAtPartner(obj, idx);
    }
    for (i = 1; i < 7; i++) {
        BOOL hit = fn_2_68C80(idx, i);
        if (hit && i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
            obj->unkC4 = 2;
            obj->unkCB = i;
            rep0B08TransitionSlot(idx, 3);
            return;
        }
        if (hit && i >= 2 && i <= 6) {
            obj->unkCB = i;
            rep0B08TransitionSlot(idx, 4);
            return;
        }
        obj->unkCB = -1;
    }
    obj->mode = 1;
}

// .text:0x0006FE6C size:0x2A4 mapped:0x806AEF00
void fn_2_6FE6C(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 i;
    if (obj->unkCD == 1) {
        rep0B08LookAtPartner(obj, idx);
    }
    for (i = 1; i < 7; i++) {
        BOOL hit = fn_2_68C80(idx, i);
        if (hit && i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
            obj->unkC4 = 2;
            obj->unkCB = i;
            rep0B08TransitionSlot(idx, 3);
            return;
        }
        if (hit && i >= 2 && i <= 6) {
            obj->unkCB = i;
            rep0B08TransitionSlot(idx, 4);
            return;
        }
        obj->unkCB = -1;
    }
}

// .text:0x0006FE34 size:0x38 mapped:0x806AEEC8
void fn_2_6FE34(Rep0B08Slot *obj) {
    lbl_2_data_2A210[obj->mode](obj);
}

// .text:0x0006FB0C size:0x328 mapped:0x806AEBA0
void fn_2_6FB0C(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 other = MENU->slots[0].index;
    rep0B08EnableSlot(idx);
    fn_2_68FBC(obj->index, 1);
    obj->unk34 = obj->unk4C;
    if (idx >= 2 && idx <= 6) {
        s32 b = fn_2_68690(0);
        if (fn_2_68670(0) == 1 && b == idx) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 2;
            return;
        }
    }
    if (fn_2_68C80(idx, other)) {
        if (idx == 1) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 2;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            obj->unkCB = 0;
        }
    } else {
        obj->unkCB = -1;
    }
    obj->mode = 1;
}

// .text:0x0006F88C size:0x280 mapped:0x806AE920
void fn_2_6F88C(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 other = MENU->slots[0].index;
    if (idx >= 2 && idx <= 6) {
        s32 a = fn_2_68670(0);
        s32 b = fn_2_68690(0);
        if (a == 1 && b == idx) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 2;
            return;
        }
    }
    if (fn_2_68C80(idx, other)) {
        if (idx == 1) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 2;
        } else if (idx >= 2 && idx <= 6) {
            obj->unkCB = 0;
        }
    } else {
        obj->unkCB = -1;
    }
}

// .text:0x0006F78C size:0x100 mapped:0x806AE820
void fn_2_6F78C(Rep0B08Slot *obj) {
    Rep0B08Slot *b = REP_SLOT(0);
    f32 r;
    obj->unk4C = (f32)atan2(-(b->pos.x - obj->pos.x),
                                      -(b->pos.z - obj->pos.z));
    r = fn_2_4A18C(obj->unk34 - obj->unk4C);
    if ((r < 0.02 && r > 0.0f) || (r > -0.02 && r < 0.0f)) {
        obj->mode = 3;
    } else if (r < 0.0f) {
        obj->unk34 += 0.05235987901687622f;
    } else {
        obj->unk34 = obj->unk34 - 0.05235987901687622f;
    }
    obj->unk4C = obj->unk34;
}

// .text:0x0006F72C size:0x60 mapped:0x806AE7C0
void fn_2_6F72C(Rep0B08Slot *obj) {
    f32 dist = (f32)fabs(PSVECDistance((Vec *)REP_SLOT(0), (Vec *)obj));
    if (dist > 1.6f) {
        obj->mode = 1;
    }
}

// .text:0x0006F6F4 size:0x38 mapped:0x806AE788
void fn_2_6F6F4(Rep0B08Slot *obj) {
    lbl_2_data_2A220[obj->mode](obj);
}

// .text:0x0006F104 size:0x5F0 mapped:0x806AE198
void fn_2_6F104(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 other = MENU->slots[0].index;
    Rep0B08Slot *slot = REP_SLOT(idx);
    s16 cand[4];
    s16 *row;
    s32 count = 0;
    s32 j;
    s16 c;
    u8 *rec;
    Rep0B08Slot *sIdx;
    Rep0B08Slot *sOther;
    u8 kind;
    f32 dx;
    f32 dz;
    f32 limit;
    f32 dist;
    rep0B08EnableSlot(idx);
    row = lbl_2_data_3D30[slot->unkB2];
    for (j = 0; j < 4; j++) {
        c = row[j];
        if (c != -1) {
            rec = lbl_2_bss_1A8248 + c * 10;
            if (rec[0x40F4] == 0 && rec[0x40F2] != 7 && rec[0x40F2] != 8) {
                cand[count] = c;
                count++;
            }
        }
    }
    slot->unkB0 = cand[rand() % count];
    memcpy(&obj->unk74, lbl_2_data_2EA4 + slot->unkB0 * 12, 12);
    fn_2_6A450(idx, obj->unk74, obj->unk7C);
    obj->unkBA = 0xD;
    fn_2_69E1C(idx);
    fn_2_68FBC(idx, 0);
    if (idx >= 2 && idx <= 6) {
        s32 b = fn_2_68690(0);
        if (fn_2_68670(0) == 1 && b == idx) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 3;
            return;
        }
    }
    sIdx = REP_SLOT(idx);
    sOther = REP_SLOT(other);
    dist = PSVECDistance((Vec *)sIdx, (Vec *)sOther);
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        limit = lbl_2_data_3F0C[other] + lbl_2_data_3EF4[kind];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && sIdx->unkC0 != 0 && sOther->unkC0 != 0) {
        if (idx == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 3;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            obj->unkCB = 0;
            return;
        }
    }
    obj->unkCB = -1;
    obj->mode = 1;
}

// .text:0x0006ED30 size:0x3D4 mapped:0x806ADDC4
void fn_2_6ED30(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 other = MENU->slots[0].index;
    Rep0B08Slot *sIdx;
    Rep0B08Slot *sOther;
    u8 kind;
    f32 limit;
    f32 dist;
    fn_2_69E1C(idx);
    if (idx >= 2 && idx <= 6) {
        s32 b = fn_2_68690(0);
        if (fn_2_68670(0) == 1 && b == idx) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 3;
            return;
        }
    }
    sIdx = REP_SLOT(idx);
    sOther = REP_SLOT(other);
    dist = PSVECDistance((Vec *)sIdx, (Vec *)sOther);
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        limit = lbl_2_data_3F0C[other] + lbl_2_data_3EF4[kind];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && sIdx->unkC0 != 0 && sOther->unkC0 != 0) {
        if (idx == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 3;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            obj->unkCB = 0;
        } else {
            obj->unkCB = -1;
        }
    } else {
        obj->unkCB = -1;
    }
    if (obj->unk50 <= 0.0f) {
        obj->unkAE = obj->unkB2;
        obj->unkB2 = obj->unkB0;
        if (rand() % 100 < 10) {
            fn_2_68FBC(idx, 1);
            obj->unkA2 = rand() % 180 + 60;
            obj->mode = 2;
        } else {
            obj->mode = 0;
        }
    }
}

// .text:0x0006EA74 size:0x2BC mapped:0x806ADB08
void fn_2_6EA74(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 other = MENU->slots[0].index;
    Rep0B08Slot *sIdx;
    Rep0B08Slot *sOther;
    u8 kind;
    f32 limit;
    f32 dist;
    s16 cd;
    if (idx >= 2 && idx <= 6) {
        s32 a = fn_2_68670(0);
        s32 b = fn_2_68690(0);
        if (a == 1 && b == idx) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 3;
            return;
        }
    }
    sIdx = REP_SLOT(idx);
    sOther = REP_SLOT(other);
    dist = PSVECDistance((Vec *)sIdx, (Vec *)sOther);
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        limit = lbl_2_data_3F0C[other] + lbl_2_data_3EF4[kind];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && sIdx->unkC0 != 0 && sOther->unkC0 != 0) {
        if (idx == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 3;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            obj->unkCB = 0;
        } else {
            obj->unkCB = -1;
        }
    } else {
        obj->unkCB = -1;
    }
    cd = obj->unkA2;
    obj->unkA2 = cd - 1;
    if (cd == 0) {
        obj->mode = 0;
    }
}

// .text:0x0006E88C size:0x1E8 mapped:0x806AD920
void fn_2_6E88C(Rep0B08Slot *obj) {
    Rep0B08Slot *b = REP_SLOT(0);
    f32 r;
    f32 t;
    f32 f31;
    obj->unk4C = (f32)atan2(-(b->pos.x - obj->pos.x),
                                      -(b->pos.z - obj->pos.z));
    r = fn_2_4A18C(obj->unk34 - obj->unk4C);
    t = (f32)fabs(r);
    if (t > 2.268928050994873f) {
        f31 = 1.5707963705062866f;
    } else if (t > 1.5707963705062866f) {
        f31 = 0.6981317400932312f;
    } else if (t > 0.6981317400932312f) {
        f31 = 0.3490658700466156f;
    } else if (t > 0.3490658700466156f) {
        f31 = 0.1745329350233078f;
    } else if (t > 0.1745329350233078f) {
        f31 = 0.0872664675116539f;
    } else if (t > 0.0872664675116539f) {
        f31 = 0.03490658476948738f;
    } else if (t > 0.03490658476948738f) {
        f31 = 0.01745329238474369f;
    } else if (t > 0.01745329238474369f) {
        f31 = 0.008726646192371845f;
    } else {
        f31 = 0.0034906587097793818f;
    }
    if (!((r < 0.02 && r > 0.0f) || (r > -0.02 && r < 0.0f))) {
        if (r < 0.0f) {
            obj->unk34 += f31;
        } else {
            obj->unk34 -= f31;
        }
    }
    obj->unk4C = obj->unk34;
}

// .text:0x0006E880 size:0xC mapped:0x806AD914
void fn_2_6E880(Rep0B08Slot *obj) {
    obj->mode = 4;
}

// .text:0x0006E848 size:0x38 mapped:0x806AD8DC
void fn_2_6E848(Rep0B08Slot *obj) {
    lbl_2_data_2A234[obj->mode](obj);
}

// .text:0x0006E1D0 size:0x678 mapped:0x806AD264
void fn_2_6E1D0(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 other = MENU->slots[0].index;
    s16 *row;
    s16 n;
    s16 pick;
    s16 chosen;
    rep0B08EnableObj(obj);
    n = lbl_2_data_3C20[idx - 2];
    row = lbl_2_data_3C2C[idx - 2];
    pick = rand() % n;
    if (obj->unkCF == -1) {
        pick = 0;
        obj->unkCF = 0;
    } else if (row[pick] == obj->unkB2) {
        pick ^= 1;
    }
    chosen = row[pick];
    SLOTS[idx].unkB0 = chosen;
    memcpy(&obj->unk74, lbl_2_data_2EA4 + SLOTS[idx].unkB0 * 12, 12);
    fn_2_6A450(idx, obj->unk74, obj->unk7C);
    obj->unkBA = 0xD;
    fn_2_69E1C(idx);
    fn_2_68FBC(idx, 0);
    if (idx >= 2 && idx <= 6) {
        s32 b = fn_2_68690(0);
        if (fn_2_68670(0) == 1 && b == idx) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 4;
            return;
        }
    }
    if (fn_2_68C80(idx, other)) {
        if (idx == 1) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 3;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            s16 target = SLOTS[idx].unkB2;
            if ((target == chosen && SLOTS[idx].unkB0 == chosen) ||
                (target == lbl_2_data_3ED4[idx - 2] && SLOTS[idx].unkB0 == lbl_2_data_3ED4[idx - 2])) {
                if (obj->unk50 <= 0.01f) {
                    obj->unkA2 = 120;
                    fn_2_68FBC(idx, 1);
                    obj->unkBA = 9;
                    obj->unk50 = 0.0f;
                    obj->unk38 = 0.0f;
                    obj->unkCF = 0;
                    obj->mode = 2;
                    return;
                }
            }
            obj->unkCB = 0;
            obj->unkCF = -1;
            obj->mode = 0;
        }
    } else {
        obj->unkCB = -1;
        obj->mode = 1;
    }
}

// .text:0x0006DE54 size:0x37C mapped:0x806ACEE8
void fn_2_6DE54(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 other = MENU->slots[0].index;
    fn_2_69E1C(idx);
    if (idx >= 2 && idx <= 6) {
        s32 b = fn_2_68690(0);
        if (fn_2_68670(0) == 1 && b == idx) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 4;
            return;
        }
    }
    if (fn_2_68C80(idx, other)) {
        if (idx == 1) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 3;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            obj->unkCB = 0;
            obj->unkCF = -1;
            obj->mode = 0;
        }
    } else {
        obj->unkCB = -1;
    }
    if (obj->unk50 <= 0.0f) {
        obj->unkAE = obj->unkB2;
        obj->unkB2 = obj->unkB0;
        obj->unkA2 = 0x78;
        fn_2_68FBC(idx, 1);
        obj->unkBA = 9;
        obj->unk50 = 0.0f;
        obj->unk38 = 0.0f;
        obj->mode = 2;
    }
}

// .text:0x0006DB30 size:0x324 mapped:0x806ACBC4
void fn_2_6DB30(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    s32 other = MENU->slots[0].index;
    s16 timer;
    fn_2_69E1C(idx);
    if (idx >= 2 && idx <= 6) {
        s32 b;
        if (idx == 2) {
            idx = 2;
        }
        b = fn_2_68690(0);
        if (fn_2_68670(0) == 1 && b == idx) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 4;
            return;
        }
    }
    if (fn_2_68C80(idx, other)) {
        if (idx == 1) {
            fn_2_68FBC(idx, 1);
            obj->unkC4 = 2;
            obj->unkCB = 0;
            obj->mode = 4;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            if (SLOTS[idx].unkB2 == *lbl_2_data_3C2C[idx - 2]) {
                obj->unkCB = 0;
                obj->unkA2 = 120;
                obj->unkCF = 0;
            } else {
                obj->unkCB = 0;
                obj->unkCF = -1;
                obj->mode = 0;
            }
        }
    } else {
        obj->unkCB = -1;
    }
    timer = obj->unkA2;
    obj->unkA2 = timer - 1;
    if (timer == 0) {
        obj->mode = 0;
    }
}

// .text:0x0006D968 size:0x1C8 mapped:0x806AC9FC
void fn_2_6D968(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    Rep0B08Slot *b = REP_SLOT(0);
    f32 r;
    obj->unk4C = (f32)atan2(-(b->pos.x - obj->pos.x),
                                      -(b->pos.z - obj->pos.z));
    r = fn_2_4A18C(obj->unk34 - obj->unk4C);
    if ((r < 0.02 && r > 0.0f) || (r > -0.02 && r < 0.0f)) {
        obj->mode = 4;
    } else if (r < 0.0f) {
        obj->unk34 += 0.05235987901687622f;
    } else {
        obj->unk34 = obj->unk34 - 0.05235987901687622f;
    }
    obj->unk4C = obj->unk34;
    if ((s8)MENU->slots[0].unkCD == 0) {
        obj->unkA2 = 0x78;
        fn_2_68FBC(idx, 1);
        obj->unkBA = 9;
        obj->unk50 = 0.0f;
        obj->unk38 = 0.0f;
        obj->mode = 2;
    }
}

// .text:0x0006D878 size:0xF0 mapped:0x806AC90C
void fn_2_6D878(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    if (MENU->slots[0].unkCD == 0) {
        obj->unkA2 = 0x78;
        fn_2_68FBC(idx, 1);
        obj->unkBA = 9;
        obj->unk50 = 0.0f;
        obj->unk38 = 0.0f;
        obj->mode = 2;
    }
}

// .text:0x0006D840 size:0x38 mapped:0x806AC8D4
void fn_2_6D840(Rep0B08Slot *obj) {
    lbl_2_data_2A248[obj->mode](obj);
}

// .text:0x0006D754 size:0xEC mapped:0x806AC7E8
void fn_2_6D754(Rep0B08Slot *obj) {
    MENU->slots[obj->index].unkC0 = 1;
    fn_2_68FBC(obj->index, 1);
    obj->unk4C = 0.0f;
    obj->unk34 = 0.0f;
    obj->mode = 1;
}

// .text:0x0006D748 size:0xC mapped:0x806AC7DC
void fn_2_6D748(Rep0B08Slot *obj) {
    obj->mode = 1;
}

// .text:0x0006D710 size:0x38 mapped:0x806AC7A4
void fn_2_6D710(Rep0B08Slot *obj) {
    lbl_2_data_2A250[obj->mode](obj);
}

// .text:0x0006D5D4 size:0x13C mapped:0x806AC668
void fn_2_6D5D4(Rep0B08Slot *obj) {
    s32 n = obj->index;
    MENU->slots[n].unkC0 = 1;
    if (obj->unk84 == 0) {
        fn_80062890(lbl_2_data_3C40[lbl_2_bss_1A8248[0x441C]]);
    } else if (obj->unk84 == 1) {
        fn_80062890(lbl_2_data_3C40[6]);
    }
    obj->unk34 = 0.0f;
    obj->unk4C = 0.0f;
    fn_2_68FBC(obj->index, 2);
    obj->mode = 1;
}

// .text:0x0006D4F8 size:0xDC mapped:0x806AC58C
void fn_2_6D4F8(Rep0B08Slot *obj) {
    if (fn_2_8CC88(obj->unk84)) {
        fn_2_68FBC(obj->index, 5);
        obj->unkA2 = 0x1E;
        obj->mode = 2;
    }
}

// .text:0x0006D4E8 size:0x10 mapped:0x806AC57C
void fn_2_6D4E8(Rep0B08Slot *obj) {
    obj->unkA2 -= 1;
}

// .text:0x0006D4B0 size:0x38 mapped:0x806AC544
void fn_2_6D4B0(Rep0B08Slot *obj) {
    lbl_2_data_2A25C[obj->mode](obj);
}

// .text:0x0006D374 size:0x13C mapped:0x806AC408
void fn_2_6D374(Rep0B08Slot *obj) {
    s32 n = obj->index;
    MENU->slots[n].unkC0 = 1;
    if (obj->unk84 == 0) {
        fn_80062890(lbl_2_data_3C5C[lbl_2_bss_1A8248[0x441C]]);
    } else if (obj->unk84 == 1) {
        fn_80062890(lbl_2_data_3C5C[6]);
    }
    obj->unk34 = 0.0f;
    obj->unk4C = 0.0f;
    fn_2_68FBC(obj->index, 3);
    obj->mode = 1;
}

// .text:0x0006D298 size:0xDC mapped:0x806AC32C
void fn_2_6D298(Rep0B08Slot *obj) {
    if (fn_2_8CC88(obj->unk84)) {
        fn_2_68FBC(obj->index, 6);
        obj->unkA2 = 0x1E;
        obj->mode = 2;
    }
}

// .text:0x0006D288 size:0x10 mapped:0x806AC31C
void fn_2_6D288(Rep0B08Slot *obj) {
    obj->unkA2 -= 1;
}

// .text:0x0006D250 size:0x38 mapped:0x806AC2E4
void fn_2_6D250(Rep0B08Slot *obj) {
    lbl_2_data_2A268[obj->mode](obj);
}

// .text:0x0006D164 size:0xEC mapped:0x806AC1F8
void fn_2_6D164(Rep0B08Slot *obj) {
    MENU->slots[obj->index].unkC0 = 1;
    obj->unk34 = 0.0f;
    obj->unk4C = 0.0f;
    fn_2_68FBC(obj->index, 4);
    obj->mode = 1;
}

// .text:0x0006D088 size:0xDC mapped:0x806AC11C
void fn_2_6D088(Rep0B08Slot *obj) {
    if (fn_2_8CC88(obj->unk84)) {
        fn_2_68FBC(obj->index, 7);
        obj->unkA2 = 0x1E;
        obj->mode = 2;
    }
}

// .text:0x0006D078 size:0x10 mapped:0x806AC10C
void fn_2_6D078(Rep0B08Slot *obj) {
    obj->unkA2 -= 1;
}

// .text:0x0006D040 size:0x38 mapped:0x806AC0D4
void fn_2_6D040(Rep0B08Slot *obj) {
    lbl_2_data_2A274[obj->mode](obj);
}

// .text:0x0006CDD4 size:0x26C mapped:0x806ABE68
void fn_2_6CDD4(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    Rep0B08Slot *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    rep0B08EnableSlot(idx);
    memcpy(&obj->unk74, lbl_2_data_2EA4 + MENU->slots[0].unkB0 * 0xC, 12);
    fn_2_6A450(idx, obj->unk74, obj->unk7C);
    obj->unkBA = 0xC;
    fn_2_69E1C(idx);
    fn_2_68FBC(idx, 0);
    obj->mode = 1;
}

// .text:0x0006CCB8 size:0x11C mapped:0x806ABD4C
void fn_2_6CCB8(Rep0B08Slot *obj) {
    s32 i;
    fn_2_69E1C(obj->index);
    if (obj->unk50 <= 0.0f) {
        obj->unkBA = 4;
        obj->unkC4 = 1;
        for (i = 0; i < 4; i++) {
            if (MENU->slots[0].unkB0 == lbl_2_data_3D30[MENU->slots[0].unkB2][i]) {
                lbl_2_bss_1A8248[0x4448] = i;
            }
        }
        MENU->slots[0].unkB2 = MENU->slots[0].unkB0;
        obj->mode = 2;
    }
}

// .text:0x0006CBB0 size:0x108 mapped:0x806ABC44
void fn_2_6CBB0(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    u8 kind;
    s32 start;
    s32 endA;
    s32 endB;
    s32 frameA;
    s32 frameB;
    fn_2_69E1C(idx);
    kind = lbl_2_bss_1A8248[0x441C];
    start = lbl_2_data_2E80[kind][0] * 2;
    endA = lbl_2_data_2E80[kind][2] * 2;
    endB = lbl_2_data_2E80[kind][1] * 2;
    frameA = start - endA;
    frameB = start - endB;
    if (obj->index == 0) {
        u8 *anim = hugeAnimStruct + 0xC04;
        if (anim != NULL) {
            s16 frame = *(s16 *)(anim + 0x68);
            if (frame == frameA || frame == frameB) {
                if (kind == 5) {
                    fn_80062890(1);
                } else {
                    fn_80062890(0);
                }
            }
        }
    }
    if (obj->unk38 <= 0.0f) {
        Rep0B08Slot *slot = REP_SLOT(idx);
        slot->state = 3;
        slot->mode = 0;
    }
}

// .text:0x0006CB78 size:0x38 mapped:0x806ABC0C
void fn_2_6CB78(Rep0B08Slot *obj) {
    lbl_2_data_2A280[obj->mode](obj);
}

// .text:0x0006C988 size:0x1F0 mapped:0x806ABA1C
void fn_2_6C988(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    f32 tmp[3];
    f32 v[3];
    Mtx mtx;
    f32 r;
    rep0B08EnableSlot(idx);
    PSVECSubtract((Vec *)(lbl_2_data_2EA4 + MENU->slots[0].unkB0 * 0xC),
                  (Vec *)(lbl_2_data_2EA4 + MENU->slots[0].unkAE * 0xC),
                  (Vec *)tmp);
    PSVECScale((Vec *)tmp, 0.5f, (Vec *)tmp);
    PSMTXRotRad(mtx, 'Y', MENU->slots[0].unk4C);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = -1.2000000476837158f;
    PSMTXMultVec(mtx, (Vec *)v, (Vec *)v);
    PSVECAdd((Vec *)tmp, (Vec *)v, (Vec *)tmp);
    memcpy(obj, lbl_2_data_2EA4 + MENU->slots[0].unkAE * 0xC, 12);
    PSVECAdd((Vec *)obj, (Vec *)tmp, (Vec *)obj);
    fn_2_68FBC(obj->index, 1);
    r = (f32)atan2(-(MENU->slots[0].pos.x - obj->pos.x),
                   -(MENU->slots[0].pos.z - obj->pos.z));
    obj->unk4C = r;
    fn_2_46C88(obj->index, 0);
    obj->mode = 1;
}

// .text:0x0006C97C size:0xC mapped:0x806ABA10
void fn_2_6C97C(Rep0B08Slot *obj) {
    obj->mode = 2;
}

// .text:0x0006C970 size:0xC mapped:0x806ABA04
void fn_2_6C970(Rep0B08Slot *obj) {
    obj->mode = 2;
}

// .text:0x0006C938 size:0x38 mapped:0x806AB9CC
void checkForButtonPressToSkip_maybe(Rep0B08Slot *obj) {
    lbl_2_data_2A28C[obj->mode](obj);
}

// .text:0x0006C5E0 size:0x358 mapped:0x806AB674
void fn_2_6C5E0(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    Rep0B08Slot *slot = REP_SLOT(idx);
    Vec tmp;
    s32 flag;
    rep0B08EnableSlot(idx);
    obj->unkBA = 0xB;
    if (lbl_2_bss_1A8248[0x4439] == 1) {
        memcpy(&obj->unk74, lbl_2_data_2EA4 + 0x1E0, 12);
        flag = 1;
    } else if (obj->pos.x > *(f32 *)(lbl_2_data_2EA4 + 0x1E0) &&
               obj->pos.z > *(f32 *)(lbl_2_data_2EA4 + 0x1E8)) {
        memcpy(&obj->unk74, lbl_2_data_2EA4 + 0x1F8, 12);
        flag = 0;
    } else {
        memcpy(&obj->unk74, lbl_2_data_2EA4 + 0x1E0, 12);
        flag = 1;
    }
    slot = REP_SLOT(idx);
    fn_2_6A450(idx, obj->unk74, obj->unk7C);
    fn_2_68FBC(idx, 0);
    if (ANIM->unk197843 == 0) {
        tmp.x = 2.0f * obj->pos.x;
        tmp.y = 2.0f * (0.3f + obj->pos.y);
        tmp.z = 2.0f * obj->pos.z;
        fn_2_9033C(0x1C, &tmp, 0.0f);
        fn_2_92654(0x1C, 0xA);
        fn_2_8F73C(0x1C, 1);
    }
    if (flag == 1) {
        obj->mode = 1;
    } else {
        obj->mode = 2;
    }
}

// .text:0x0006C348 size:0x298 mapped:0x806AB3DC
void fn_2_6C348(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    fn_2_69E1C(idx);
    if (obj->unk50 <= 0.0f) {
        if (lbl_2_bss_1A8248[0x4439] == 1) {
            obj->unkBA = 4;
            obj->unkC4 = 1;
            obj->mode = 3;
        } else {
            memcpy(&obj->unk74, lbl_2_data_2EA4 + 0x1F8, 12);
            fn_2_6A450(idx, 0.2f + obj->unk74, 0.5f + obj->unk7C);
            fn_2_68FBC(idx, 0);
            obj->mode = 2;
        }
    }
}

// .text:0x0006C2E8 size:0x60 mapped:0x806AB37C
void fn_2_6C2E8(Rep0B08Slot *obj) {
    fn_2_69E1C(obj->index);
    if (obj->unk50 <= 0.0f) {
        obj->unkBA = 4;
        obj->unkC4 = 1;
        obj->mode = 3;
    }
}

// .text:0x0006C2C4 size:0x24 mapped:0x806AB358
void fn_2_6C2C4(void) {
    lbl_2_bss_1A8248[0x442F] = 0;
    rep0B08TransitionSlot(1, 0);
}

// .text:0x0006C28C size:0x38 mapped:0x806AB320
void fn_2_6C28C(Rep0B08Slot *obj) {
    lbl_2_data_2A29C[obj->mode](obj);
}

// .text:0x0006C190 size:0xFC mapped:0x806AB224
void fn_2_6C190(Rep0B08Slot *obj) {
    MENU->slots[obj->index].unkC0 = 1;
    fn_2_68FBC(obj->index, 1);
    obj->unk34 = obj->unk4C;
    fn_2_46C88(lbl_2_bss_1A8248[0x441E], 0);
    obj->mode = 1;
}

// .text:0x0006C120 size:0x70 mapped:0x806AB1B4
void fn_2_6C120(Rep0B08Slot *obj) {
    f32 dist = (f32)fabs(PSVECDistance((Vec *)REP_SLOT(0), (Vec *)obj));
    if (dist < 1.6f && dist != 0.0f) {
        obj->mode = 2;
    }
}

// .text:0x0006C020 size:0x100 mapped:0x806AB0B4
void fn_2_6C020(Rep0B08Slot *obj) {
    Rep0B08Slot *b = REP_SLOT(0);
    f32 r;
    obj->unk4C = (f32)atan2(-(b->pos.x - obj->pos.x),
                                      -(b->pos.z - obj->pos.z));
    r = fn_2_4A18C(obj->unk34 - obj->unk4C);
    if ((r < 0.02 && r > 0.0f) || (r > -0.02 && r < 0.0f)) {
        obj->mode = 3;
    } else if (r < 0.0f) {
        obj->unk34 += 0.05235987901687622f;
    } else {
        obj->unk34 = obj->unk34 - 0.05235987901687622f;
    }
    obj->unk4C = obj->unk34;
}

// .text:0x0006BFC0 size:0x60 mapped:0x806AB054
void fn_2_6BFC0(Rep0B08Slot *obj) {
    f32 dist = (f32)fabs(PSVECDistance((Vec *)REP_SLOT(0), (Vec *)obj));
    if (dist > 1.6f) {
        obj->mode = 1;
    }
}

// .text:0x0006BF88 size:0x38 mapped:0x806AB01C
void fn_2_6BF88(Rep0B08Slot *obj) {
    lbl_2_data_2A2AC[obj->mode](obj);
}

// .text:0x0006BE80 size:0x108 mapped:0x806AAF14
void fn_2_6BE80(Rep0B08Slot *obj) {
    MENU->slots[obj->index].unkC0 = 0;
    fn_2_68FBC(obj->index, 1);
    MENU->slots[obj->index].unkCA = 0xFF;
    obj->unk8C = 0.0f;
    obj->mode = 1;
}

// .text:0x0006BDE0 size:0xA0 mapped:0x806AAE74
void fn_2_6BDE0(Rep0B08Slot *obj) {
    s32 v;
    MENU->slots[obj->index].unkC0 = 1;
    obj->unk8C = (f32)(obj->unk8C + 0.1);
    v = (s32)(256.0f * obj->unk8C);
    if (v < 0xFF) {
        MENU->slots[obj->index].unkCA = v;
    } else {
        MENU->slots[obj->index].unkCA = 0xFF;
        obj->mode = 2;
    }
}

// .text:0x0006BDD4 size:0xC mapped:0x806AAE68
void fn_2_6BDD4(Rep0B08Slot *obj) {
    obj->mode = 2;
}

// .text:0x0006BD9C size:0x38 mapped:0x806AAE30
void fn_2_6BD9C(Rep0B08Slot *obj) {
    lbl_2_data_2A2B8[obj->mode](obj);
}

// .text:0x0006BCAC size:0xF0 mapped:0x806AAD40
void fn_2_6BCAC(Rep0B08Slot *obj) {
    fn_2_68F08(obj->index, 0);
    fn_2_68F24(obj->index, 9);
    obj->unk4C = 0.0f;
    obj->unk34 = 0.0f;
    fn_2_68D90(obj->index, 0xFF);
    obj->unk8C = 0.0f;
    obj->mode = 1;
}

// .text:0x0006BC0C size:0xA0 mapped:0x806AACA0
void fn_2_6BC0C(Rep0B08Slot *obj) {
    s32 v;
    MENU->slots[obj->index].unkC0 = 1;
    obj->unk8C = (f32)(obj->unk8C + 0.1);
    v = (s32)(256.0f * obj->unk8C);
    if (v < 0xFF) {
        MENU->slots[obj->index].unkCA = v;
    } else {
        MENU->slots[obj->index].unkCA = 0xFF;
        obj->mode = 2;
    }
}

// .text:0x0006BC00 size:0xC mapped:0x806AAC94
void fn_2_6BC00(Rep0B08Slot *obj) {
    obj->mode = 2;
}

// .text:0x0006BBC8 size:0x38 mapped:0x806AAC5C
void fn_2_6BBC8(Rep0B08Slot *obj) {
    lbl_2_data_2A2C4[obj->mode](obj);
}

// .text:0x0006BB7C size:0x4C mapped:0x806AAC10
void fn_2_6BB7C(Rep0B08Slot *obj) {
    MENU->slots[obj->index].unkC0 = 1;
    MENU->slots[obj->index].unkCA = 0xFF;
    obj->unk8C = 1.0f;
    obj->mode = 1;
}

// .text:0x0006BAD8 size:0xA4 mapped:0x806AAB6C
void fn_2_6BAD8(Rep0B08Slot *obj) {
    s32 v;
    obj->unk8C = (f32)(obj->unk8C - 0.1);
    v = (s32)(255.0f * obj->unk8C);
    if (v > 1) {
        MENU->slots[obj->index].unkCA = v;
    } else {
        MENU->slots[obj->index].unkCA = 0;
        MENU->slots[obj->index].unkC0 = 0;
        obj->mode = 2;
    }
}

// .text:0x0006BAAC size:0x2C mapped:0x806AAB40
void fn_2_6BAAC(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    MENU->slots[idx].unkCA = 0xFF;
    obj->mode = 3;
}

// .text:0x0006BA50 size:0x5C mapped:0x806AAAE4
void fn_2_6BA50(Rep0B08Slot *obj) {
    GXColor color = *(GXColor *)&inputParams[0x28];
    color.a = 0xFF;
    adjustLightingParams(0, color);
    obj->mode = 2;
}

// .text:0x0006BA18 size:0x38 mapped:0x806AAAAC
void fn_2_6BA18(Rep0B08Slot *obj) {
    lbl_2_data_2A2D4[obj->mode](obj);
}

// .text:0x0006B744 size:0x2D4 mapped:0x806AA7D8
void fn_2_6B744(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    Rep0B08Slot *slot = REP_SLOT(idx);
    Vec tmp;
    f32 dx;
    f32 dz;
    rep0B08EnableSlot(idx);
    obj->unkBA = 0xC;
    obj->unkD0 = 1;
    obj->unk90 = 0.0f;
    obj->pos.y = 0.0f;
    if (slot->unkB0 == 0x30) {
        memcpy(&tmp, lbl_2_data_3198 + 0x1F4, 12);
    } else {
        memcpy(&tmp, lbl_2_data_3198 + 0x208, 12);
    }
    PSVECScale(&tmp, 0.5f, &tmp);
    memcpy(&obj->unk74, &tmp, 12);
    fn_2_6A450(idx, obj->unk74, obj->unk7C);
    fn_2_68FBC(idx, 8);
    obj->mode = 1;
}

// .text:0x0006B620 size:0x124 mapped:0x806AA6B4
void fn_2_6B620(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    fn_2_69E1C(idx);
    fn_2_698EC(idx, 1.5f);
    if (obj->unk50 <= 0.0f) {
        obj->unkBA = 4;
        obj->unkC4 = 1;
        obj->mode = 2;
    }
}

// .text:0x0006B4FC size:0x124 mapped:0x806AA590
void fn_2_6B4FC(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    fn_2_698EC(idx, 1.5f);
    if (obj->unkD0 == 0) {
        rep0B08TransitionSlot(idx, 0);
    }
}

// .text:0x0006B4C4 size:0x38 mapped:0x806AA558
void fn_2_6B4C4(Rep0B08Slot *obj) {
    lbl_2_data_2A2E0[obj->mode](obj);
}

// .text:0x0006B238 size:0x28C mapped:0x806AA2CC
void fn_2_6B238(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    Rep0B08Slot *slot = REP_SLOT(idx);
    rep0B08EnableSlot(idx);
    obj->unkBA = 0xE;
    obj->unkD0 = 1;
    obj->unk90 = 0.0f;
    obj->pos.y = 0.0f;
    if (slot->unkB0 == 0x30) {
        memcpy(&obj->unk74, lbl_2_data_2EA4 + 0x258, 12);
    } else {
        memcpy(&obj->unk74, lbl_2_data_2EA4 + 0xD8, 12);
    }
    fn_2_6A450(idx, obj->unk74, obj->unk7C);
    fn_2_68FBC(idx, 8);
    obj->mode = 1;
}

// .text:0x0006B120 size:0x118 mapped:0x806AA1B4
void fn_2_6B120(Rep0B08Slot *obj) {
    s32 idx = obj->index;
    fn_2_69E1C(idx);
    fn_2_698EC(idx, 0.0f);
    if (obj->unk50 <= 0.0f) {
        obj->unkBA = 4;
        obj->mode = 2;
    }
}

// .text:0x0006B024 size:0xFC mapped:0x806AA0B8
void fn_2_6B024(Rep0B08Slot *obj) {
    fn_2_698EC(obj->index, 0.0f);
    if (obj->unkD0 == 0) {
        obj->unkC4 = 1;
    }
}

// .text:0x0006AFD4 size:0x50 mapped:0x806AA068
s32 fn_2_6AFD4(s32 idx) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    if (slot->unkC4 == 1) {
        slot->unkC4 = 0;
        return 1;
    }
    if (slot->unkC4 == 2) {
        slot->unkC4 = 0;
        return 2;
    }
    return 0;
}

// .text:0x0006AF9C size:0x38 mapped:0x806AA030
BOOL fn_2_6AF9C(s32 idx) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    if (slot->unkD0 == 0) {
        slot->unkD0 = 0;
        return TRUE;
    }
    return FALSE;
}

// .text:0x0006AF80 size:0x1C mapped:0x806AA014
void fn_2_6AF80(s32 idx, u8 val) {
    MENU->slots[idx].unkC4 = val;
}

// .text:0x0006AE08 size:0x178 mapped:0x806A9E9C
void fn_2_6AE08(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        Rep0B08Slot *slot = REP_SLOT(i);
        memset(slot, 0, 0xD8);
        slot->index = i;
        slot->unk84 = i;
        slot->unk8C = 0.0f;
        slot->unkB6 = 10;
        slot->unk40 = 0.0003f * (f32)slot->unkB6 + 0.1f;
        slot->unkB8 = 10;
        slot->unkB7 = 15;
        slot->unk44 = slot->unk40 / (f32)slot->unkB7;
        slot->unkBB = 0;
        slot->unkC0 = 0;
        slot->unk96 = i;
        slot->unk98 = -1;
        slot->unkBC = 1;
        slot->unkBA = 12;
        slot->state = 0;
        slot->mode = 0;
        slot->unkC6 = 0xFF;
        slot->unkC4 = 0;
        slot->unkC5 = 0;
        slot->unk88 = 0.0f;
        slot->unkC1 = 0;
        slot->unkAC = 0;
        slot->unkCA = 0xFF;
        slot->unkCB = 0xFF;
        slot->unkCC = 0xFF;
    }
}

// .text:0x0006ACF4 size:0x114 mapped:0x806A9D88
void fn_2_6ACF4(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        Rep0B08Slot *slot = REP_SLOT(i);
        slot->index = i;
        slot->unk84 = i;
        slot->unk8C = 0.0f;
        slot->unkB6 = 10;
        slot->unk40 = 0.0003f * (f32)slot->unkB6 + 0.1f;
        slot->unkB8 = 10;
        slot->unkB7 = 15;
        slot->unk44 = slot->unk40 / (f32)slot->unkB7;
        slot->unkBB = 0;
        slot->unkC0 = 0;
        slot->unk96 = i;
        slot->unk98 = -1;
        slot->unkBC = 1;
        slot->state = 0;
        slot->mode = 0;
        slot->unkC6 = 0xFF;
        slot->unkC4 = 0;
        slot->unkC5 = 0;
        slot->unk88 = 0.0f;
        slot->unkC1 = 0;
        slot->unkAC = 0;
        slot->unkCA = 0xFF;
        slot->unkCB = 0xFF;
        slot->unkCC = 0xFF;
    }
}

// .text:0x0006ACF0 size:0x4 mapped:0x806A9D84
void fn_2_6ACF0(void) {
    return;
}

// .text:0x0006ABFC size:0xF4 mapped:0x806A9C90
void fn_2_6ABFC(s32 idx, s32 which) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    if (idx < 2) {
        memcpy(slot, lbl_2_data_2EA4 + which * 0xC, 12);
    } else if (idx >= 2 && idx <= 6) {
        memcpy(slot, lbl_2_data_2EA4 + which * 0xC, 12);
    } else {
        memcpy(slot, lbl_2_data_3150 + (idx - 7) * 0xC, 12);
    }
    slot->unk0C = 0.0f;
    slot->unk10 = 0.0f;
    slot->unk14 = 0.0f;
    slot->unk18 = 0.0f;
    slot->unk1C = 0.0f;
    slot->unk20 = 0.0f;
    slot->unk6C = slot->pos.x;
    slot->unk70 = slot->pos.z;
    slot->unk38 = 0.0f;
    slot->unkBB = 0;
    {
        f32 v = slot->unk4C;
        slot->unk34 = v;
        slot->unk30 = v;
    }
}

// .text:0x0006AB3C size:0xC0 mapped:0x806A9BD0
void fn_2_6AB3C(s32 idx, const void *src, f32 angle) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    memcpy(slot, src, 12);
    slot->unk0C = 0.0f;
    slot->unk10 = 0.0f;
    slot->unk14 = 0.0f;
    slot->unk18 = 0.0f;
    slot->unk1C = 0.0f;
    slot->unk20 = 0.0f;
    slot->unk30 = angle;
    slot->unk6C = slot->pos.x;
    slot->unk70 = slot->pos.z;
    slot->unk38 = 0.0f;
    slot->unkBB = 0;
    angle = (f32)atan2(slot->pos.x, slot->pos.z);
    slot->unk34 = angle;
    slot->unk30 = angle;
}

// .text:0x0006AABC size:0x80 mapped:0x806A9B50
void fn_2_6AABC(s32 idx, const void *src) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    memcpy(slot, src, 12);
    slot->unk0C = 0.0f;
    slot->unk10 = 0.0f;
    slot->unk14 = 0.0f;
    slot->unk18 = 0.0f;
    slot->unk1C = 0.0f;
    slot->unk20 = 0.0f;
    slot->unk6C = slot->pos.x;
    slot->unk70 = slot->pos.z;
    slot->unk38 = 0.0f;
    slot->unkBB = 0;
}

// .text:0x0006AAB8 size:0x4 mapped:0x806A9B4C
void fn_2_6AAB8(void) {
    return;
}

// .text:0x0006A87C size:0x23C mapped:0x806A9910
void fn_2_6A87C(void) {
    MENU->slots[0].unkBB = 0;
    fn_2_6A708();
    fn_2_6A628();
}

// .text:0x0006A708 size:0x174 mapped:0x806A979C
void fn_2_6A708(void) {
    Rep0B08Slot *slot = REP_SLOT(0);
    Vec tmp;
    Vec v;
    memcpy(&tmp, slot, sizeof(Vec));
    PSVECSubtract(&tmp, (Vec *)lbl_2_data_2A340, &v);
    v.z *= -1.0f;
    v.x *= -1.0f;
    tmp.x += (s8)AtBat_ButtonInput1[(s8)ANIM->unk197863 * 0x20 + 0x10] / 768.0f;
    tmp.z += (s8)AtBat_ButtonInput1[(s8)ANIM->unk197863 * 0x20 + 0x11] / 768.0f;
    if (v.x != 0.0f || v.z != 0.0f) {
        lbl_2_bss_A170 = fn_2_4A1E8(v.z);
    }
    memcpy(lbl_2_data_2A340, slot, sizeof(Vec));
    slot->pos.x = tmp.x;
    slot->pos.y = tmp.y;
    slot->pos.z = tmp.z;
    slot->unk4C = lbl_2_bss_A170;
}

// .text:0x0006A628 size:0xE0 mapped:0x806A96BC
void fn_2_6A628(void) {
    Rep0B08Menu *menu = MENU;
    Mtx mtx;
    f32 vec[3];
    if (!(menu->slots[0].unk38 <= 0.0f)) {
        PSMTXRotRad(mtx, 'Y', menu->slots[0].unk4C);
        vec[0] = 0.0f;
        vec[1] = 0.0f;
        vec[2] = -menu->slots[0].unk38;
        PSMTXMultVec(mtx, (Vec *)vec, (Vec *)vec);
        menu->slots[0].unk18 = vec[0];
        menu->slots[0].unk20 = vec[2];
        menu->slots[0].pos.x += menu->slots[0].unk18;
        menu->slots[0].pos.z += menu->slots[0].unk20;
    }
    menu->slots[0].unk0C = menu->slots[0].pos.x;
    menu->slots[0].unk14 = menu->slots[0].pos.z;
    if (menu->slots[0].unk38 == 0.0f) {
        menu->slots[0].unk24 = 0.0f;
        menu->slots[0].unk2C = 0.0f;
    }
}

// .text:0x0006A5A8 size:0x80 mapped:0x806A963C
void fn_2_6A5A8(s32 idx) {
    SLOTS[idx].unk0C = SLOTS[idx].pos.x;
    SLOTS[idx].unk10 = SLOTS[idx].pos.y;
    SLOTS[idx].unk14 = SLOTS[idx].pos.z;
    SLOTS[idx].unk18 = 0.0f;
    SLOTS[idx].unk1C = 0.0f;
    SLOTS[idx].unk20 = 0.0f;
    SLOTS[idx].unk38 = 0.0f;
    SLOTS[idx].unk50 = 0.0f;
}

// .text:0x0006A450 size:0x158 mapped:0x806A94E4
void fn_2_6A450(s32 idx, f32 x, f32 z) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    slot->unk0C = x;
    slot->unk14 = z;
    dx = x - slot->pos.x;
    dz = z - slot->pos.z;
    if (dx == 0.0f && dz == 0.0f) {
        slot->unk38 = 0.0f;
        slot->unk50 = 0.0f;
    } else {
        slot->unk50 = dolsqrtf2(dx * dx + dz * dz);
    }
    slot->unkBB = 1;
}

// .text:0x00069E1C size:0x634 mapped:0x806A8EB0
void fn_2_69E1C(s32 idx) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    Mtx mtx;
    Vec v;
    f32 r;
    f32 a;
    f32 step;
    f32 dx;
    f32 dz;
    f32 len;
    s16 ang1;
    s16 ang2;
    u8 kind;
    if (slot->unk50 > 0.0f) {
        ang1 = fn_2_4A2C4(slot->unk4C);
        ang2 = fn_2_4A2C4(slot->unk54);
        fn_2_4A310(ang1, ang2);
        slot->unkBC = 0;
        slot->unkBD = 0;
        if (slot->unk9E < 0x7FFE) {
            slot->unk9E = slot->unk9E + 1;
        } else {
            slot->unk9E = 0x7FFF;
        }
    } else {
        slot->unkBC = 1;
        if (slot->unk9E > 0x2D) {
            slot->unk9E = 0x2D;
        }
        if (slot->unk9E != 0) {
            slot->unk9E = slot->unk9E - 1;
        }
    }
    switch (slot->unkBA) {
    case 0:
        fn_2_69710(idx);
        break;
    case 1:
    case 5:
        slot->unk38 = slot->unk38 - 0.0005f;
        break;
    case 2:
    case 6:
        slot->unk38 = slot->unk38 - 0.001f;
        break;
    case 3:
    case 7:
        slot->unk38 = slot->unk38 - 0.002f;
        break;
    case 4:
    case 8:
        slot->unkBA = slot->unkBA + 0x14;
        break;
    case 24:
    case 28:
        slot->unk38 = slot->unk38 - 0.005f;
        break;
    case 9:
        slot->unk38 = 0.0f;
        break;
    case 10:
        slot->unk38 = 0.08f;
        break;
    case 11:
        slot->unk38 = 0.12f;
        break;
    case 12:
        if (idx == 0) {
            kind = lbl_2_bss_1A8248[0x441C];
            slot->unk38 = lbl_2_data_3F44[kind];
        } else {
            slot->unk38 = 0.04f;
        }
        break;
    case 13:
        slot->unk38 = 0.012f;
        break;
    case 14:
        slot->unk38 = 0.025f;
        break;
    default:
        break;
    }
    if (slot->unk38 <= 0.0f) {
        slot->unk38 = 0.0f;
    }
    slot->unk50 = slot->unk50 - slot->unk38;
    dx = slot->pos.x - slot->unk0C;
    dz = slot->pos.z - slot->unk14;
    {
        f32 squaredX = dx * dx;
        f32 squaredZ = dz * dz;
        len = dolsqrtf2(squaredX + squaredZ);
    }
    if (len < slot->unk38) {
        slot->unk50 = -1.0f;
    }
    if (!(slot->unk38 <= 0.0f)) {
        if (slot->unkBA != 4 && slot->unkBA != 0x18 && slot->unk50 > 0.0f) {
            slot->unk4C = atan2(-(slot->unk0C - slot->pos.x),
                                         -(slot->unk14 - slot->pos.z));
        }
        PSMTXRotRad(mtx, 'Y', slot->unk34);
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = -slot->unk38;
        PSMTXMultVec(mtx, &v, &v);
        slot->unk18 = v.x;
        slot->unk20 = v.z;
        slot->pos.x = slot->pos.x + slot->unk18;
        slot->pos.z = slot->pos.z + slot->unk20;
        if (slot->unkBA != 4 && slot->unkBA != 0x18 && slot->unk50 > 0.0f) {
            slot->unk4C = atan2(-(slot->unk0C - slot->pos.x),
                                         -(slot->unk14 - slot->pos.z));
            r = fn_2_4A18C(slot->unk34 - slot->unk4C);
            a = fabs(r);
            if (a > 2.268928050994873f) {
                step = 1.5707964f;
            } else if (a > 1.5707964f) {
                step = 0.6981317400932312f;
            } else if (a > 0.6981317400932312f) {
                step = 0.3490658700466156f;
            } else if (a > 0.3490658700466156f) {
                step = 0.1745329350233078f;
            } else if (a > 0.1745329350233078f) {
                step = 0.0872664675116539f;
            } else if (a > 0.0872664675116539f) {
                step = 0.03490658476948738f;
            } else if (a > 0.03490658476948738f) {
                step = 0.01745329238474369f;
            } else if (a > 0.01745329238474369f) {
                step = 0.008726646192371845f;
            } else if (a < 0.01745329238474369f) {
                step = 0.0034906587097793818f;
            }
            if (!((r < 0.02 && r > 0.0f) || (r > -0.02 && r < 0.0f))) {
                if (r < 0.0f) {
                    slot->unk34 = slot->unk34 + step;
                } else {
                    slot->unk34 = slot->unk34 - step;
                }
            }
            slot->unk4C = slot->unk34;
        }
    }
    if (slot->unk38 == 0.0f && slot->unkBD == 0) {
        slot->unkBC = 1;
    }
}

// .text:0x000699D4 size:0x448 mapped:0x806A8A68
void fn_2_699D4(s32 idx) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    Mtx mtx;
    Vec v;
    f32 r;
    f32 a;
    f32 step;
    f32 dx;
    f32 dz;
    f32 len;
    if (slot->unk38 <= 0.0f) {
        slot->unk38 = 0.0f;
    }
    slot->unk50 = slot->unk50 - slot->unk38;
    dx = slot->pos.x - slot->unk0C;
    dz = slot->pos.z - slot->unk14;
    {
        f32 squaredX = dx * dx;
        f32 squaredZ = dz * dz;
        len = dolsqrtf2(squaredX + squaredZ);
    }
    if (len < slot->unk38) {
        slot->unk50 = -1.0f;
    }
    if (slot->unkBA != 4 && slot->unkBA != 0x18 && slot->unk50 > 0.0f) {
        slot->unk4C = atan2(-(slot->unk0C - slot->pos.x),
                                     -(slot->unk14 - slot->pos.z));
    }
    PSMTXRotRad(mtx, 'Y', slot->unk34);
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    PSMTXMultVec(mtx, &v, &v);
    slot->unk18 = v.x;
    slot->unk20 = v.z;
    slot->pos.x = slot->pos.x + slot->unk18;
    slot->pos.z = slot->pos.z + slot->unk20;
    if (slot->unkBA != 4 && slot->unkBA != 0x18 && slot->unk50 > 0.0f) {
        slot->unk4C = atan2(-(slot->unk0C - slot->pos.x),
                                     -(slot->unk14 - slot->pos.z));
        r = fn_2_4A18C(slot->unk34 - slot->unk4C);
        a = fabs(r);
        if (a > 2.268928050994873f) {
            step = 1.5707964f;
        } else if (a > 1.5707964f) {
            step = 0.6981317400932312f;
        } else if (a > 0.6981317400932312f) {
            step = 0.3490658700466156f;
        } else if (a > 0.3490658700466156f) {
            step = 0.1745329350233078f;
        } else if (a > 0.1745329350233078f) {
            step = 0.0872664675116539f;
        } else if (a > 0.0872664675116539f) {
            step = 0.03490658476948738f;
        } else if (a > 0.03490658476948738f) {
            step = 0.01745329238474369f;
        } else if (a > 0.01745329238474369f) {
            step = 0.008726646192371845f;
        } else if (a < 0.01745329238474369f) {
            step = 0.0034906587097793818f;
        }
        if (!((r < 0.02 && r > 0.0f) || (r > -0.02 && r < 0.0f))) {
            if (r < 0.0f) {
                slot->unk34 = slot->unk34 + step;
            } else {
                slot->unk34 = slot->unk34 - step;
            }
        }
        slot->unk4C = slot->unk34;
    }
    if (slot->unk38 == 0.0f && slot->unkBD == 0) {
        slot->unkBC = 1;
    }
}

// .text:0x000698EC size:0xE8 mapped:0x806A8980
void fn_2_698EC(s32 idx, f32 angle) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    if (slot->unkD0 != 0) {
        f32 out = 1.6f * -(f32)sin(slot->unk90);
        slot->unk90 += 0.07f;
        if (slot->pos.y > angle) {
            slot->unk90 = 0.0f;
            out = 0.0f;
            slot->unkD0 = 0;
            if (slot->state == 0x13) {
                fn_2_68F08(slot->index, 0);
            }
        }
        slot->pos.y = out;
    } else {
        slot->pos.y = 0.0f;
    }
}

// .text:0x00069710 size:0x1DC mapped:0x806A87A4
void fn_2_69710(s32 idx) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    if (slot->unk9C == 0) {
        s16 a1 = fn_2_4A2C4(slot->unk4C);
        s16 a2 = fn_2_4A2C4(slot->unk30);
        s16 d = fn_2_4A150((s16)(a1 - a2));
        if (d < 0x200) {
            slot->unkBE = 0;
        } else if (d < 0x600) {
            slot->unkBE = 3;
        } else if (d < 0xA00) {
            slot->unkBE = 1;
        } else if (d < 0xE00) {
            slot->unkBE = 2;
        } else {
            slot->unkBE = 0;
        }
        if (slot->unkBC != 1) {
            if (slot->unkBE == 1) {
                slot->unkBE = 5;
            } else {
                slot->unkBE = 4;
            }
        }
    }
    if (slot->unkBE == 4 || slot->unkBE == 5) {
        slot->unk38 = 0.5f * slot->unk44 + slot->unk38;
    } else {
        slot->unk38 = slot->unk38 + slot->unk44;
    }
    if (slot->unkC1 == 0 && slot->unkC2 != 0 && slot->unkA0 == 0) {
        slot->unkA0 = 30;
    }
    if (slot->unkC1 != 0) {
        if (slot->unk38 > slot->unk40) {
            slot->unk38 = slot->unk40;
        }
        slot->unkA0 = 0;
    } else if (slot->unkA0 != 0) {
        if (slot->unk38 >= slot->unk40) {
            slot->unk38 = slot->unk40;
        } else {
            slot->unkA0 = 0;
        }
    } else {
        if (slot->unk38 > 0.12f) {
            slot->unk38 = 0.12f;
        }
    }
}

// .text:0x000696D4 size:0x3C mapped:0x806A8768
void fn_2_696D4(s32 idx) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    if (slot->unkA0 != 0) {
        slot->unk38 = slot->unk3C;
    } else {
        slot->unk38 = 0.0f;
    }
}

// .text:0x00069554 size:0x180 mapped:0x806A85E8
s32 fn_2_69554(s32 idx, f32 x, f32 z) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    f32 div;
    f32 t;
    if (x == slot->pos.x && z == slot->pos.z) {
        return 1;
    }
    dx = x - slot->pos.x;
    dz = z - slot->pos.z;
    t = dolsqrtf2(dx * dx + dz * dz);
    div = slot->unk40;
    if (div == 0.0f) {
        div = 1.0f;
    }
    return (slot->unkB7 >> 1) + (s32)(t / div);
}

// .text:0x000692D0 size:0x284 mapped:0x806A8364
void fn_2_692D0(s32 idx, s32 n, f32 x, f32 z, f32 *outX, f32 *outZ, f32 *outT) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    f32 t = 0.0f;
    f32 acc = slot->unk38;
    f32 len;
    f32 nx;
    f32 nz;
    s16 ang;
    s32 cnt;
    s32 i;
    if (x == 0.0f && z == 0.0f) {
        *outX = slot->pos.x;
        *outZ = slot->pos.z;
        *outT = 0.0f;
        return;
    }
    len = dolsqrtf2(x * x + z * z);
    nx = x / len;
    nz = z / len;
    ang = fn_2_4A234(nx, nz);
    if (!(slot->unk38 < 0.05f) && slot->unk9A >= 0 &&
        fn_2_4A310(ang, slot->unk9A) > 0x2A8) {
        acc = 0.0f;
    }
    cnt = slot->unkB7;
    for (i = 0; i <= cnt; i++) {
        acc += slot->unk44;
        if (acc > slot->unk40) {
            t += slot->unk40;
            break;
        }
        t += acc;
    }
    n -= i + 1;
    t += slot->unk40 * (f32)n;
    *outT = t;
    *outX = nx * t + slot->pos.x;
    *outZ = nz * t + slot->pos.z;
}

// .text:0x00069070 size:0x260 mapped:0x806A8104
f32 fn_2_69070(s32 idx, f32 x, f32 z) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    f32 proj;
    f32 disc;
    if (slot->unk38 < 0.01f) {
        dx = slot->pos.x - x;
        dz = slot->pos.z - z;
        {
            f32 squaredX = dx * dx;
            f32 squaredZ = dz * dz;
            return dolsqrtf2(squaredX + squaredZ);
        }
    }
    dz = z - slot->pos.z;
    dx = x - slot->pos.x;
    proj = slot->unk24 * dx + slot->unk2C * dz;
    disc = dx * dx + dz * dz - proj * proj;
    if (disc < 0.0f) {
        return 0.0f;
    }
    return dolsqrtf2(disc);
}

// .text:0x00068FBC size:0xB4 mapped:0x806A8050
void fn_2_68FBC(s32 idx, s32 val) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    Rep0B08AnimEntry *ent = &((Rep0B08AnimEntry *)lbl_2_data_3C84)[val];
    if (ANIM->curAnim[slot->index] != val) {
        fn_2_8CD58(slot->index, ent->anim, ent->arg2, 1, ent->arg4, 0, 0);
        ANIM->curAnim[slot->index] = val;
    }
}

// .text:0x00068F24 size:0x98 mapped:0x806A7FB8
void fn_2_68F24(s32 idx, s32 val) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    Rep0B08AnimEntry *ent = &((Rep0B08AnimEntry *)lbl_2_data_3C84)[val];
    fn_2_8CD58(slot->index, ent->anim, ent->arg2, 1, ent->arg4, 0, 0);
    ANIM->curAnim[slot->index] = val;
}

// .text:0x00068F08 size:0x1C mapped:0x806A7F9C
void fn_2_68F08(s32 idx, u8 val) {
    MENU->slots[idx].unkC0 = val;
}

// .text:0x00068E68 size:0xA0 mapped:0x806A7EFC
void fn_2_68E68(void) {
    s32 i;
    for (i = 0; i < ANIM->unk197746; i++) {
        Rep0B08Slot *slot = REP_SLOT(i);
        u8 *dst = hugeAnimStruct + i * 0x27C + 0xC04;
        memcpy(dst + 0x34, slot, 12);
        *(f32 *)(dst + 0x44) = slot->unk4C;
        dst[0x25D] = slot->unkC0;
        dst[0x277] = slot->unkCA;
    }
}

// .text:0x00068DE8 size:0x80 mapped:0x806A7E7C
void fn_2_68DE8(s32 idx, void *dst) {
    if (idx != -1) {
        memcpy(dst, REP_SLOT(idx), 12);
        PSVECScale(dst, 2.0f, dst);
    } else {
        *(f32 *)((u8 *)dst + 0x8) = 0.0f;
        *(f32 *)((u8 *)dst + 0x4) = 0.0f;
        *(f32 *)((u8 *)dst + 0x0) = 0.0f;
    }
}

// .text:0x00068DAC size:0x3C mapped:0x806A7E40
void fn_2_68DAC(s32 idx, void *dst) {
    memcpy(dst, REP_SLOT(idx), 12);
}

// .text:0x00068D90 size:0x1C mapped:0x806A7E24
void fn_2_68D90(s32 idx, u8 val) {
    MENU->slots[idx].unkCA = val;
}

// .text:0x00068C80 size:0x110 mapped:0x806A7D14
u8 fn_2_68C80(s32 idx, s32 otherIdx) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    Rep0B08Slot *other = REP_SLOT(otherIdx);
    f32 distance = PSVECDistance((Vec *)slot, (Vec *)other);
    f32 lhs;
    f32 rhs;
    if (idx == 0) {
        lhs = lbl_2_data_3EF4[lbl_2_bss_1A8248[0x441C]];
        rhs = lbl_2_data_3F0C[otherIdx];
    } else {
        lhs = lbl_2_data_3F0C[idx];
        rhs = lbl_2_data_3EF4[lbl_2_bss_1A8248[0x441C]];
    }
    if (distance < lhs + rhs && slot->unkC0 != 0 && other->unkC0 != 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x00068B54 size:0x12C mapped:0x806A7BE8
u8 fn_2_68B54(s32 idx, s32 otherIdx) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    Rep0B08Slot *other = REP_SLOT(otherIdx);
    f32 distance = PSVECDistance((Vec *)slot, (Vec *)other);
    f32 lhs;
    f32 rhs;
    if (idx == 0) {
        lhs = lbl_2_data_3EF4[lbl_2_bss_1A8248[0x441C]] + lbl_2_data_3F2C[lbl_2_bss_1A8248[0x441C]];
        rhs = lbl_2_data_3F0C[otherIdx];
    } else {
        lhs = lbl_2_data_3F0C[idx];
        rhs = lbl_2_data_3EF4[lbl_2_bss_1A8248[0x441C]] + lbl_2_data_3F2C[lbl_2_bss_1A8248[0x441C]];
    }
    if (distance < lhs + rhs && slot->unkC0 != 0 && other->unkC0 != 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x00068A88 size:0xCC mapped:0x806A7B1C
BOOL fn_2_68A88(s32 idx, s32 which) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    f32 *rec = (f32 *)(lbl_2_bss_1A8248 + 0x21E0 + which * 0xBC);
    f32 tmp[3];
    f32 dist;
    f32 limit;
    tmp[0] = rec[0] * 0.5f;
    tmp[1] = rec[1] * 0.5f;
    tmp[2] = rec[2] * 0.5f;
    dist = PSVECDistance((Vec *)slot, (Vec *)tmp);
    limit = lbl_2_data_3EF4[lbl_2_bss_1A8248[0x441C]] + lbl_2_data_3F5C;
    if (dist < limit && slot->unkC0 != 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000689CC size:0xBC mapped:0x806A7A60
s16 fn_2_689CC(s32 idx) {
    Vec a;
    Vec b;
    f32 best = 10000.0f;
    s32 i;
    s32 bestIdx = 0;
    memcpy(&a, REP_SLOT(idx), 12);
    for (i = 0; i < 0x33; i++) {
        f32 dist;
        memcpy(&b, lbl_2_data_2EA4 + i * 0xC, 12);
        dist = PSVECDistance(&a, &b);
        if (dist < best) {
            best = dist;
            bestIdx = i;
        }
    }
    return (s16)bestIdx;
}

// .text:0x00068940 size:0x8C mapped:0x806A79D4
f32 fn_2_68940(s32 idxA, s32 idxB) {
    Rep0B08Slot *a = REP_SLOT(idxA);
    Rep0B08Slot *b = REP_SLOT(idxB);
    return fn_2_4A18C(a->unk4C) -
           (f32)atan2(-(b->pos.x - a->pos.x),
                      -(b->pos.z - a->pos.z));
}

// .text:0x000688A4 size:0x9C mapped:0x806A7938
f32 fn_2_688A4(s32 idx, s32 which) {
    f32 tmp[3];
    Rep0B08Slot *a = REP_SLOT(idx);
    memcpy(tmp, lbl_2_data_2EA4 + which * 0xC, 12);
    return fn_2_4A18C(a->unk4C) -
           (f32)atan2(-(tmp[0] - a->pos.x),
                      -(tmp[2] - a->pos.z));
}

// .text:0x000687A4 size:0x100 mapped:0x806A7838
BOOL fn_2_687A4(s32 idxA, s32 idxB, s32 which) {
    Rep0B08Slot *a = REP_SLOT(idxA);
    Rep0B08Slot *b = REP_SLOT(idxB);
    f32 tmp[3];
    f32 angleB;
    f32 angleTmp;
    f32 diff;
    angleB = (f32)atan2(-(b->pos.x - a->pos.x),
                        -(b->pos.z - a->pos.z));
    memcpy(tmp, lbl_2_data_2EA4 + which * 0xC, 12);
    angleTmp = (f32)atan2(-(tmp[0] - a->pos.x),
                          -(tmp[2] - a->pos.z));
    diff = angleB - angleTmp;
    if (diff < 1.2217305898666382f && diff > -1.2217305898666382f) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000686EC size:0xB8 mapped:0x806A7780
BOOL fn_2_686EC(s32 idxA, s32 idxB) {
    Rep0B08Slot *a = REP_SLOT(idxA);
    Rep0B08Slot *b = REP_SLOT(idxB);
    f32 diff;
    diff = fn_2_4A18C(a->unk4C) -
           (f32)atan2(-(b->pos.x - a->pos.x),
                      -(b->pos.z - a->pos.z));
    if (diff < 1.2217305898666382f && diff > -1.2217305898666382f) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000686D0 size:0x1C mapped:0x806A7764
void fn_2_686D0(s32 idx, u8 val) {
    MENU->slots[idx].unkCF = val;
}

// .text:0x000686B0 size:0x20 mapped:0x806A7744
s32 fn_2_686B0(s32 idx) {
    return MENU->slots[idx].unkCB;
}

// .text:0x00068690 size:0x20 mapped:0x806A7724
s32 fn_2_68690(s32 idx) {
    return MENU->slots[idx].unkCC;
}

// .text:0x00068670 size:0x20 mapped:0x806A7704
s32 fn_2_68670(s32 idx) {
    return MENU->slots[idx].unkCD;
}

// .text:0x00068654 size:0x1C mapped:0x806A76E8
void fn_2_68654(s32 idx, u8 val) {
    MENU->slots[idx].unkCD = val;
}

// .text:0x00068638 size:0x1C mapped:0x806A76CC
void fn_2_68638(s32 idx, u8 val) {
    MENU->slots[idx].unkCE = val;
}

// .text:0x000684D0 size:0x168 mapped:0x806A7564
s32 fn_2_684D0(s32 idx) {
    Rep0B08Slot *slot = REP_SLOT(idx);
    s32 i;
    slot->unkCC = -1;
    for (i = 1; i < 7; i++) {
        if (fn_2_68B54(idx, i) && i >= 2 && i <= 6) {
            slot->unkCC = i;
            break;
        }
        slot->unkCC = -1;
    }
    return slot->unkCC;
}

// .text:0x000683EC size:0xE4 mapped:0x806A7480
void fn_2_683EC(void) {
    Rep0B08Slot *s1;
    Rep0B08Menu *menu = MENU;
    menu->slots[1].pos.x = menu->slots[0].pos.x;
    menu->slots[1].pos.y = menu->slots[0].pos.y;
    menu->slots[1].pos.z = menu->slots[0].pos.z;
    s1 = REP_SLOT(1);
    memcpy(s1, lbl_2_data_2EA4 + MENU->slots[0].unkB2 * 0xC, 12);
    s1->unk0C = 0.0f;
    s1->unk10 = 0.0f;
    s1->unk14 = 0.0f;
    s1->unk18 = 0.0f;
    s1->unk1C = 0.0f;
    s1->unk20 = 0.0f;
    s1->unk6C = s1->pos.x;
    s1->unk70 = s1->pos.z;
    s1->unk38 = 0.0f;
    s1->unkBB = 0;
    {
        f32 v = s1->unk4C;
        s1->unk34 = v;
        s1->unk30 = v;
    }
    MENU->slots[1].unkB2 = MENU->slots[0].unkB2;
    rep0B08TransitionSlot(1, 6);
    lbl_2_bss_1A8248[0x442F] = 1;
}

// .text:0x0006832C size:0xC0 mapped:0x806A73C0
void fn_2_6832C(void) {
    Rep0B08Slot *slot = REP_SLOT(1);
    memcpy(slot, lbl_2_data_2EA4 + 0x3C, 12);
    slot->unk0C = 0.0f;
    slot->unk10 = 0.0f;
    slot->unk14 = 0.0f;
    slot->unk18 = 0.0f;
    slot->unk1C = 0.0f;
    slot->unk20 = 0.0f;
    slot->unk6C = slot->pos.x;
    slot->unk70 = slot->pos.z;
    slot->unk38 = 0.0f;
    slot->unkBB = 0;
    {
        f32 v = slot->unk4C;
        slot->unk34 = v;
        slot->unk30 = v;
    }
    MENU->slots[1].unkB2 = 5;
    rep0B08TransitionSlot(1, 6);
    lbl_2_bss_1A8248[0x442F] = 1;
}
