#define SQRT2_LINKAGE static
#include "menus/rep_08E8.h"
#include "text/text.h"
#include "Dolphin/pad.h"
#include "Dolphin/OS/OSUtil.h"
#include "game/math/game_math.h"
#include "header_rep_data.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/GX/GXEnum.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"
#include "C3/light/light.h"

extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_bss_1A81D4[];
extern u8 hugeAnimStruct[0x3154];
extern u8 drawStadiumRelated;
extern u8 lbl_2_data_12EC0[];
extern u8 lbl_2_data_13228[];
extern u16 lbl_2_data_13238[];

extern u32 lbl_803CBD0C;
extern u32 *lbl_2_data_13374;
extern u8 g_d_GameSettings[];
extern s32 lbl_2_data_38B8;
extern u8 *lbl_2_bss_340140;
extern u8 StatsScreenScores[];
extern u8 AtBat_ButtonInput1[];
extern u8 lbl_800EFBA4[];
extern u8 lbl_2_data_3804[];
extern u8 lbl_2_data_3840[];
extern u8 lbl_2_data_387C[];
extern u8 lbl_2_data_13304[];
extern u8 lbl_2_data_13310[];
extern u8 lbl_2_data_132EC[];
extern u8 lbl_2_data_132F8[];
extern f32 lbl_2_bss_55B8;
extern f32 lbl_2_bss_55BC;
extern f32 lbl_2_rodata_948;
extern f32 lbl_2_rodata_94C;
extern f32 lbl_2_rodata_9A0;
extern f32 lbl_2_rodata_9A4;
extern f32 lbl_2_rodata_98C;
extern f32 lbl_2_rodata_990;
extern u32 lbl_2_rodata_938;
extern u32 lbl_2_rodata_93C;
extern u32 lbl_2_rodata_940;
extern f32 lbl_2_rodata_960;
extern f32 lbl_2_rodata_974;
extern f32 lbl_2_rodata_978;
extern f32 lbl_2_rodata_97C;
extern f32 lbl_2_rodata_980;
extern f32 lbl_2_rodata_984;
extern f32 lbl_2_rodata_988;
extern f32 lbl_2_rodata_950;
extern f32 lbl_2_rodata_954;
extern f32 lbl_2_rodata_958;
extern f32 lbl_2_rodata_95C;
extern f32 lbl_2_rodata_964;
extern f32 lbl_2_rodata_968;
extern f32 lbl_2_rodata_96C;
extern f32 lbl_2_rodata_970;
extern u8 lbl_2_data_12EA8[];
extern u8 lbl_2_data_12EB4[];
extern u8 lbl_803532A8[];
extern u8 *lbl_2_bss_1A823C;
s32 fn_80062890(s32 arg);
extern u8 lbl_2_bss_55C0;
extern u8 *currentDrawingItem;
extern u32 memoryUsedOrStorage[];
s32 fn_80016710(s32 character, s32 item);
void fn_2_93C64(void);
void removeCurrentDrawingItem(void);
extern u8 BatterStats_P1_P2[];
extern u8 PitcherStats_P1_P2[];
void CTRLSetTranslation(void *ctrl, f32 x, f32 y, f32 z);
void CTRLSetRotation(void *ctrl, f32 x, f32 y, f32 z);
void CTRLSetScale(void *ctrl, f32 x, f32 y, f32 z);
void fn_80024DB0(void *state);
void fn_80024FA4(void *model, void *handle, void *state, s32 arg);
void fn_2_8D024(void);
void fn_2_4B2D0(void);
void challenge_leftoverTeammatesJoinBowserJr(void);
void initActorArray(s32 count);
void sndFXStartEx(s32 fid, u8 vol, u8 pan, u8 studio);
void fn_80014204(s32 arg);
s32 fn_80023AA4(void);
void *getAnimObjectActor(void *anim);
void ACTSetAnimation(void *actor, void *animBank, char *sequenceName, u16 seqNum, f32 startFrame, f32 time);
void setActorAnimFrame(void *actor, f32 frame);
void ACTSetSpeed(void *actor, f32 speed);
void updateBoneParam(void *actor, s32 flag);
void Set_FUN_800b2b6c(void *actor, s32 value);
void fn_800BDA24(void *obj);
void *returnFloatFromModeIndex(s32 mode);
s32 returnScissorMode(void);
s32 fn_800B3C04(s32 arg, void *root, Mtx m);

static inline u32 allocationEntrySize(s32 offset) {
    u8 *entry = lbl_2_data_12EC0;
    entry += offset;
    return *(u32 *)(entry + 4) & 0x0FFFFFFF;
}

static inline void addStatCounter(s32 delta) {
    *(s16 *)(lbl_2_bss_1A8248 + 0x43BE) = *(s16 *)(lbl_2_bss_1A8248 + 0x43BC);
    *(s16 *)(lbl_2_bss_1A8248 + 0x43BC) += delta;
    if (*(s16 *)(lbl_2_bss_1A8248 + 0x43BC) > 999) {
        *(s16 *)(lbl_2_bss_1A8248 + 0x43BC) = 999;
    }
    if (*(s16 *)(lbl_2_bss_1A8248 + 0x43BC) < 0) {
        *(s16 *)(lbl_2_bss_1A8248 + 0x43BC) = 0;
    }
}

void fn_800ACFB0(void *obj);
void fn_2_68690(s32 flag);
void fn_2_68DAC(void *self, Vec *out);
void fn_80031CA4(Vec *v, u32 *dst);
void fn_2_513E0(void *a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h);
void *fn_80052768_getCamera(s32 mode);
void fn_800BD670(void *model, void *arg);
void fn_800A7D4C(s32 phase, void *node);
void LITXForm(void *arg0, void *arg1);
void *_OSAllocFromHeap(s32 alignment, s32 size);
void *memcpy(void *dest, const void *src, u32 n);
void PSMTXCopy(const Mtx src, Mtx dest);
void graphics_relatedToVsScreen(void);
void fn_2_6A87C(void);
void fn_2_93BF8(void *arg);
void fn_2_9007C(void);
f64 atan2(f64 y, f64 x);

// .text:0x0004AEE4 size:0x2C8 mapped:0x80689F78
void fn_2_4AEE4(void) {
    u8 *st;
    u8 *b;
    u8 idx;
    s32 delta;
    s32 bit;

    fn_2_4B2D0();
    b = lbl_2_bss_1A824C + 0x190000;
    st = lbl_2_bss_1A8248;
    if (b[0x7843] == 0) {
        idx = st[0x4420];
        *(s16 *)(b + 0x777C) = (s16)*(u32 *)(lbl_2_data_3840 + idx * 12 + g_d_GameSettings[0x3A] * 4);
        *(s16 *)(b + 0x777E) = (s16)((f32)*(s16 *)(g_d_GameSettings + 0x20 + g_d_GameSettings[0x35] * 4) *
                                     *(f32 *)(lbl_2_data_3804 + idx * 12 + g_d_GameSettings[0x3A] * 4));
        delta = *(s16 *)(b + 0x777C) + *(s16 *)(b + 0x777E);
        addStatCounter(delta);
        *(s16 *)(b + 0x7780) = (s16)delta;
        *(s16 *)(b + 0x7798) = (s16)delta;
    } else if (b[0x7843] == 1) {
        idx = st[0x4420];
        delta = *(s32 *)(lbl_2_data_387C + idx * 12 + g_d_GameSettings[0x3A] * 4);
        addStatCounter(delta);
        *(s16 *)(b + 0x7782) = (s16)delta;
        *(s16 *)(b + 0x7798) = (s16)delta;
    } else if (b[0x7843] == 2) {
        *(s16 *)(b + 0x7796) = 0;
        *(s16 *)(b + 0x7798) = 0;
    }

    idx = st[0x4420];
    if ((s8)st[0x44F8 + idx] > 0) {
        st[0x44F8 + idx]--;
    }
    if (b[0x7843] == 0) {
        bit = 1 << st[0x4420];
        if ((st[0x4428] & bit) == 0) {
            st[0x4423]++;
            st[0x4428] |= bit;
        }
    }
}

// .text:0x0004ACF8 size:0x1EC mapped:0x80689D8C
void fn_2_4ACF8(void) {
    fn_2_4B2D0();
    if ((s8)(lbl_2_bss_1A824C + 0x190000)[0x7843] == 0) {
        addStatCounter(*(s16 *)(g_d_GameSettings + 0x30));
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7792) = *(s16 *)(g_d_GameSettings + 0x30);
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7798) = *(s16 *)(g_d_GameSettings + 0x30);
    } else if ((s8)(lbl_2_bss_1A824C + 0x190000)[0x7843] == 1) {
        addStatCounter(lbl_2_data_38B8);
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7794) = (s16)lbl_2_data_38B8;
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7798) = (s16)lbl_2_data_38B8;
    } else if ((s8)(lbl_2_bss_1A824C + 0x190000)[0x7843] == 2) {
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7796) = 0;
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7798) = 0;
        if ((s8)lbl_2_bss_1A8248[0x44FD] > 0) {
            lbl_2_bss_1A8248[0x44FD]--;
        }
        if ((s8)(lbl_2_bss_1A824C + 0x190000)[0x7843] == 0) {
            if (lbl_2_bss_1A8248[0x4429] == 0) {
                lbl_2_bss_1A8248[0x4429] = 1;
            }
        }
    }
}

// .text:0x0004AB1C size:0x1DC mapped:0x80689BB0
void fn_2_4AB1C(void) {
    volatile s32 score0;
    volatile s32 score1;
    u8 *st;
    u8 *b;
    s32 bit;

    fn_2_4B2D0();
    score0 = *(u16 *)(StatsScreenScores + 0x8);
    score1 = *(u16 *)(StatsScreenScores + 0x2E);
    if (score0 < 0) {
        score0 = 0;
    }
    if (score0 > 99) {
        score0 = 99;
    }
    if (score1 > 99) {
        score1 = 99;
    }

    b = lbl_2_bss_1A824C + 0x190000;
    if (b[0x7843] == 0) {
        *(s16 *)(b + 0x776E) = 0;
        *(s16 *)(b + 0x7772) = 0;
        *(s16 *)(b + 0x7776) = 0;
        *(s16 *)(b + 0x7798) = *(s16 *)(b + 0x776E) + *(s16 *)(b + 0x7772) + *(s16 *)(b + 0x7776);
    } else if (b[0x7843] == 1) {
        *(s16 *)(b + 0x7770) = 0;
        *(s16 *)(b + 0x7774) = 0;
        *(s16 *)(b + 0x7798) = *(s16 *)(b + 0x7770) + *(s16 *)(b + 0x7774);
    } else if (b[0x7843] == 2) {
        *(s16 *)(b + 0x7796) = 0;
        *(s16 *)(b + 0x7798) = 0;
    }

    st = lbl_2_bss_1A8248;
    if (!(st[0x441C] == 5 && st[0x44EF] == 1)) {
        bit = 1 << st[0x441E];
        if ((st[0x4427] & bit) == 0) {
            st[0x4427] |= bit;
        }
    }

    if (b[0x7843] == 0) {
        if (st[0x441C] == 5 && st[0x44EF] == 1) {
            st[0x4422]++;
        } else {
            bit = 1 << st[0x441E];
            if ((st[0x4426] & bit) == 0) {
                st[0x4422]++;
                st[0x4426] |= bit;
            }
        }
    }
    challenge_leftoverTeammatesJoinBowserJr();
}

#define TIMING_FIELD(offset) (*(s16 *)(lbl_2_bss_1A824C + 0x190000 + (offset)))

// .text:0x0004A6E8 size:0x434 mapped:0x8068977C
void fn_2_4A6E8(void) {
    s32 kind = *(s16 *)(lbl_2_bss_1A823C + 0x30);

    if (kind == 3) {
        if (*(s8 *)(lbl_2_bss_1A824C + 0x197843) == 0) {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x776E);
            TIMING_FIELD(0x7768) = TIMING_FIELD(0x7772);
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
        } else if (*(s8 *)(lbl_2_bss_1A824C + 0x197843) == 1) {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x7770);
            TIMING_FIELD(0x7768) = TIMING_FIELD(0x7774);
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
        } else {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x7796);
            TIMING_FIELD(0x7768) = 10000;
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
        }
    } else if (kind == 5) {
        if (*(s8 *)(lbl_2_bss_1A824C + 0x197843) == 0) {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x777C);
            TIMING_FIELD(0x7768) = TIMING_FIELD(0x777E);
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
            *(s32 *)(lbl_2_bss_1A824C + 0x1976A8) = fn_80062890(14);
        } else if (*(s8 *)(lbl_2_bss_1A824C + 0x197843) == 1) {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x7782);
            TIMING_FIELD(0x7768) = 10000;
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
            *(s32 *)(lbl_2_bss_1A824C + 0x1976A8) = fn_80062890(15);
        } else {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x7796);
            TIMING_FIELD(0x7768) = 10000;
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
            *(s32 *)(lbl_2_bss_1A824C + 0x1976A8) = fn_80062890(15);
        }
    } else if (kind == 4) {
        if (*(s8 *)(lbl_2_bss_1A824C + 0x197843) == 0) {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x7778);
            TIMING_FIELD(0x7768) = 10000;
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
        } else if (*(s8 *)(lbl_2_bss_1A824C + 0x197843) == 1) {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x777A);
            TIMING_FIELD(0x7768) = 10000;
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
        } else {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x7796);
            TIMING_FIELD(0x7768) = 10000;
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
        }
    } else {
        if (*(s8 *)(lbl_2_bss_1A824C + 0x197843) == 0) {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x7792);
            TIMING_FIELD(0x7768) = 10000;
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
            *(s32 *)(lbl_2_bss_1A824C + 0x1976A8) = fn_80062890(14);
        } else if (*(s8 *)(lbl_2_bss_1A824C + 0x197843) == 1) {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x7794);
            TIMING_FIELD(0x7768) = 10000;
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
            *(s32 *)(lbl_2_bss_1A824C + 0x1976A8) = fn_80062890(15);
        } else {
            TIMING_FIELD(0x7766) = TIMING_FIELD(0x7796);
            TIMING_FIELD(0x7768) = 10000;
            TIMING_FIELD(0x776A) = 10000;
            TIMING_FIELD(0x776C) = TIMING_FIELD(0x7798);
            *(s32 *)(lbl_2_bss_1A824C + 0x1976A8) = fn_80062890(15);
        }
    }
}

#undef TIMING_FIELD

// .text:0x0004A340 size:0x3A8 mapped:0x806893D4
void fn_2_4A340(void) {
    u8 *ss = StatsScreenScores;
    u8 *gs = g_d_GameSettings;
    u8 *st = lbl_2_bss_1A8248;
    u8 *table;
    u8 *bat;
    u8 *pit;
    u16 a;
    u16 b;
    u8 cur;
    s32 s;
    s32 j;
    s32 opp;
    s32 base12;
    s32 counter;
    s32 idx25;
    s32 idx24;
    s32 idx;

    gs[0xC] = st[0x441C];
    idx25 = gs[0xE];
    idx24 = idx25 ^ 1;
    *(u8 *)(gs + 0xD) = st[(s16)*(s16 *)(st + 0x16C2) * 10 + 0x40F3];

    *(s16 *)(ss + 0x8) = 0;
    *(s16 *)(ss + 0xA) = 4;
    *(s16 *)(ss + 0xC) = 0;
    *(s16 *)(ss + 0xE) = 2;
    *(s16 *)(ss + 0x10) = 0;
    *(s16 *)(ss + 0x12) = 10;
    *(s16 *)(ss + 0x14) = 0;
    *(s16 *)(ss + 0x16) = 0;
    *(s16 *)(ss + 0x18) = 0;
    *(s16 *)(ss + 0x1A) = 0;
    *(s16 *)(ss + idx25 * 0x26 + 0x1C) = 0;
    for (idx = 0x2E; idx <= 0x44; idx += 2) {
        *(s16 *)(ss + idx) = 0;
    }
    *(s16 *)(ss + 0x54 + idx25 * 0x26) = 0;
    *(s16 *)(ss + 0x54 + idx24 * 0x26) = 0;
    *(s16 *)(ss + 0x54) = 0;
    *(s16 *)(ss + 0x56) = 0;
    *(s16 *)(ss + 0x58) = 1;
    *(s16 *)(ss + 0x5A) = 2;
    *(s16 *)(ss + 0x5C) = 0;
    *(s16 *)(ss + 0x5E) = 0;
    *(s16 *)(ss + 0x60) = 0;
    *(s16 *)(ss + 0x62) = 3;
    *(s16 *)(ss + 0x64) = 0;
    *(s16 *)(ss + 0x66) = 0;
    *(s16 *)(ss + 0x68) = 0;
    *(s16 *)(ss + 0x6A) = 0;
    *(s16 *)(ss + 0x7A) = 1;
    *(s16 *)(ss + 0x7C) = 0;
    *(s16 *)(ss + 0x7E) = 0;
    *(s16 *)(ss + 0x80) = 3;
    *(s16 *)(ss + 0x82) = 0;
    *(s16 *)(ss + 0x84) = 0;
    *(s16 *)(ss + 0x86) = 0;
    *(s16 *)(ss + 0x88) = 0;
    *(s16 *)(ss + 0x8A) = 0;
    *(s16 *)(ss + 0x8C) = 0xC;
    *(s16 *)(ss + 0x8E) = 0;
    *(s16 *)(ss + 0x90) = 0;
    ss[0xF0 + idx25] = 1;
    ss[0xF0 + idx24] = 1;
    ss[0xF6] = 9;

    a = *(u16 *)(ss + 0x8);
    b = *(u16 *)(ss + 0x2E);
    if (a > b) {
        ss[0xF2] = 0;
    } else if (a < b) {
        ss[0xF2] = 1;
    } else {
        ss[0xF2] = 2;
    }

    for (idx = 0; idx < 30; idx++) {
        ss[0xA0 + idx] = 0xFF;
    }

    table = lbl_803532A8;
    table[1] = (table[1] & ~7) | 1;
    table[2] = 0;
    table[3] = 10;
    table[5] = (table[5] & ~7) | 1;
    table[6] = 0;
    table[7] = 10;
    table[9] = (table[9] & ~7) | 1;
    table[0xA] = 0;
    table[0xB] = 10;
    ss[0xA0] = 0;
    ss[0xA1] = 1;
    ss[0xA2] = 2;

    bat = BatterStats_P1_P2;
    pit = PitcherStats_P1_P2;
    for (s = 0; s < 2; s++) {
        opp = 1 - s;
        base12 = opp * 12;
        cur = (u8)(u32)(g_d_GameSettings + s * 10);
        counter = 0;
        for (j = 0; j < 9; j++) {
            bat[0x26 * j + 0x4] = (u8)(base12 + counter);
            bat[0x26 * j + 0x5] = (u8)(s + j);
            *(s16 *)(pit + 0x1E * j + 0xA) = (s16)(s + j + 2);
            pit[0x1E * j + 0x1A] = cur;
            cur += 3;
            *(s16 *)(pit + 0x1E * j + 0x2) = 3;
            pit[0x1E * j + 0x1C] = 2;
            counter += s;
            bat[0x26 * j + 0x10] = (u8)(2 * j);
            bat[0x26 * j + 0x12] = (u8)(s + 1);
            bat[0x26 * j + 0x18] = (u8)j;
        }
        pit += 0x10E;
        bat += 0x156;
    }
}

// .text:0x0004A310 size:0x30 mapped:0x806893A4
s16 fn_2_4A310(s16 a, s16 b) {
    s32 d = a - b;
    s32 sign = d >> 31;
    s16 diff = (sign ^ d) - sign;
    if (diff > SANG_ANG_180) {
        diff = SANG_ANG_360 - diff;
    }
    return diff;
}

// .text:0x0004A2C4 size:0x4C mapped:0x80689358
s32 fn_2_4A2C4(f32 angle) {
    f32 v = 0.0f;
    if (angle < 0.0f) {
        v = 2048.0f * (6.2831855f + angle) / 3.1415927f;
    }
    return (s32)v;
}

// .text:0x0004A234 size:0x90 mapped:0x806892C8
s16 fn_2_4A234(f32 x, f32 y) {
    s16 angle;
    if (x == 0.0f) {
        if (y >= 0.0f) {
            return SANG_ANG_90;
        }
        return SANG_ANG_270;
    }
    angle = (s32)(2048.0f * (f32)atan2(y, x) / 3.1415927f);
    if (angle < 0) {
        angle += SANG_ANG_360;
    }
    return angle;
}

// .text:0x0004A1E8 size:0x4C mapped:0x8068927C
f32 fn_2_4A1E8(f32 x, f32 y) {
    if (x != 0.0f || y != 0.0f) {
        return (f32)atan2(y, x);
    }
    return 0.0f;
}

// .text:0x0004A18C size:0x5C mapped:0x80689220
f32 fn_2_4A18C(f32 angle) {
    if (angle >= 3.1415927f) {
        while (angle >= 3.1415927f) {
            angle -= 6.2831855f;
        }
    }
    if (angle < -3.1415927f) {
        while (angle < -3.1415927f) {
            angle = 6.2831855f + angle;
        }
    }
    return angle;
}

// .text:0x0004A150 size:0x3C mapped:0x806891E4
s16 fn_2_4A150(s16 angle) {
    if (angle < 0) {
        while (angle < 0) {
            angle += SANG_ANG_360;
        }
    }
    if (angle >= SANG_ANG_360) {
        while (angle >= SANG_ANG_360) {
            angle -= SANG_ANG_360;
        }
    }
    return angle;
}

// .text:0x0004A0C4 size:0x8C mapped:0x80689158
s32 fn_2_4A0C4(u16 *a, u16 *b) {
    for (;;) {
        u16 ca = *a;
        u16 cb;
        s32 diff;
        if ((ca & 0xC000) == 0xC000) {
            return -1;
        }
        cb = *b;
        if ((cb & 0xC000) == 0xC000) {
            return 1;
        }
        if (ca != 0x4000 || cb != 0x4000) {
            if (ca == 0x4000) {
                return -1;
            }
            if (cb == 0x4000) {
                return 1;
            }
            diff = ca - cb;
            if (diff != 0) {
                return diff;
            }
            a++;
            b++;
            continue;
        }
        return 0;
    }
}

// .text:0x0004A094 size:0x30 mapped:0x80689128
u16 *fn_2_4A094(u16 *dst, u16 *src) {
    u16 *start = dst;
    while (*src != 0x4000) {
        *dst++ = *src++;
    }
    *dst = *src;
    return start;
}

// .text:0x0004A068 size:0x2C mapped:0x806890FC
s32 fn_2_4A068(u16 *str) {
    u16 *p = str;
    while (*p != 0x4000) {
        p++;
    }
    return p - str;
}

// .text:0x0004A064 size:0x4 mapped:0x806890F8
void fn_2_4A064(void) {
    return;
}

// .text:0x00049F7C size:0xE8 mapped:0x80689010
u16 *fn_2_49F7C(u16 *str, s32 capacity, u16 ch, s32 pos) {
    u16 *p = str;
    s32 len;
    s32 i;
    while (*p != 0x4000) {
        p++;
    }
    len = p - str;
    if (len < pos) {
        return NULL;
    }
    if (ch == 0x4000) {
        return NULL;
    }
    if (len + 2 > capacity) {
        return NULL;
    }
    for (i = len; i >= pos; i--) {
        str[i + 1] = str[i];
    }
    str[pos] = ch;
    return str;
}

// .text:0x00049EFC size:0x80 mapped:0x80688F90
s32 fn_2_49EFC(u16 *str, u16 idx) {
    s32 total = 0;
    u16 c;
    while ((c = *str) != 0x4000) {
        if (c == 0x4003) {
            total += lbl_2_data_13238[idx];
        } else if (c == 0x4002) {
            total += lbl_2_data_13238[idx] >> 1;
        } else if (!(c & 0x4000)) {
            if (c & 0x8000) {
                total += lbl_2_data_13238[idx];
            } else {
                total += lbl_2_data_13238[idx] >> 1;
            }
        }
        str++;
    }
    return total;
}

// .text:0x00049E5C size:0xA0 mapped:0x80688EF0
void fn_2_49E5C(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7, s32 p8, s32 p9) {
    void *tmp = _OSAllocFromHeap(0x10, 0x40);
    fn_2_4917C(tmp, p3, p4, p5, p6);
    fn_2_513E0(tmp, p1, p2, 0, p6, p7, p8, p9);
    if (tmp != NULL) {
        fn_800ACFB0(tmp);
    }
}

// .text:0x00049DB8 size:0xA4 mapped:0x80688E4C
void fn_2_49DB8(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7, s32 p8, s32 p9, s32 p10) {
    void *tmp = _OSAllocFromHeap(0x10, 0x40);
    fn_2_4917C(tmp, p3, p4, p6, p7);
    fn_2_513E0(tmp, p1, p2, p5, p7, p8, p9, p10);
    if (tmp != NULL) {
        fn_800ACFB0(tmp);
    }
}

typedef struct NumberGlyphBuffer {
    u8 _00[0xA];
    u16 space;
    u16 minus;
    u16 separator;
    u16 glyphs[16];
} NumberGlyphBuffer;

u32 strlen(const char *str);

static inline u16 *insertNumberGlyph(u16 *str, int capacity, u16 glyph, int position) {
    u16 *end = str;
    int length;
    int i;

    while (*end != 0x4000) end++;
    length = end - str;
    if (length < position || glyph == 0x4000 || length + 2 > capacity) return NULL;
    for (i = length; i >= position; i--) str[i + 1] = str[i];
    str[position] = glyph;
    return str;
}

// .text:0x0004917C size:0xC3C mapped:0x80688210
u16 *fn_2_4917C(void *output, s32 value, s32 flags, s32 width, s32 unused) {
    char digits[12];
    NumberGlyphBuffer *buffer = (NumberGlyphBuffer *)&lbl_2_bss_55B8;
    u16 *dst;
    u16 *glyphs = buffer->glyphs;
    u8 *bank;
    char *start;
    s32 working;
    int i;
    int digit;
    s32 count = 0;
    s32 specialFont;
    s32 fullWidth;

    if (flags & 0x20) {
        flags |= 4;
        width = 3;
    } else if (flags & 0x40) {
        flags |= 4;
        width = 4;
    } else if (flags & 0x80) {
        flags |= 4;
        width = 2;
    }
    if (flags & 8) {
        if (value == 0) {
            for (i = 0; i < 7; i++) digits[i] = ' ';
            digits[7] = '0';
            digits[8] = 0;
        } else {
            digits[8] = 0;
            i = 7;
            working = value;
            while (working != 0) {
                digit = working % 16;
                if (digit < 10) digits[i] = digit + '0';
                else digits[i] = digit + 0x57;
                working /= 16;
                i--;
            }
            for (; i >= 0; i--) digits[i] = ' ';
        }
    } else {
        if (value == 0) {
            for (i = 0; i < 9; i++) digits[i] = ' ';
            digits[9] = '0';
            digits[10] = 0;
        } else {
            i = value < -999999999 ? 11 : 10;
            digits[i] = 0;
            i--;
            working = value;
            if (value < 0) working = -value;
            while (working != 0) {
                digits[i] = working % 10 + '0';
                working /= 10;
                i--;
            }
            if (value < 0) {
                if (flags & 0xE0) digits[i] = ' ';
                else digits[i] = '-';
                i--;
            }
            for (; i >= 0; i--) digits[i] = ' ';
        }
    }
    if (!(flags & 6)) width = 0;
    start = digits + strlen(digits) - width;
    while (start != digits && start[-1] != ' ') start--;

    if ((flags & 4) && (flags & 1)) {
        buffer->separator = **(u16 **)(lbl_2_bss_1A824C + 0x19544C);
    } else if ((flags & 4) && (flags & 0x10)) {
        buffer->separator = **(u16 **)(lbl_2_bss_1A824C + 0x195464);
    } else if (flags & 4) {
        buffer->separator = **(u16 **)(lbl_2_bss_1A824C + 0x195460);
    } else if (flags & 1) {
        buffer->separator = 0x4003;
    } else {
        buffer->separator = 0x4002;
    }
    buffer->space = (flags & 1) + 0x4002;
    specialFont = flags & 0x10;
    fullWidth = flags & 1;
    bank = lbl_2_bss_1A824C + 0x190000;
    dst = glyphs;
    while (*start != 0) {
        if (*start == ' ') {
            *dst = buffer->separator;
        } else if (*start == '-') {
            if (specialFont) *dst = **(u16 **)(bank + 0x545C);
            else if (fullWidth) *dst = **(u16 **)(bank + 0x5458);
            else *dst = **(u16 **)(bank + 0x545C);
        } else if (*start >= '0' && *start <= '9') {
            if (specialFont) *dst = (*(u16 **)(bank + 0x5464))[*start - '0'];
            else if (fullWidth) *dst = (*(u16 **)(bank + 0x544C))[*start - '0'];
            else *dst = (*(u16 **)(bank + 0x5460))[*start - '0'];
        } else {
            if (specialFont) *dst = (*(u16 **)(bank + 0x5464))[*start - 0x55];
            else if (fullWidth) *dst = (*(u16 **)(bank + 0x5444))[*start - 'a'];
            else *dst = (*(u16 **)(bank + 0x5450))[*start - 'a'];
        }
        dst++;
        count++;
        start++;
    }
    glyphs[count] = 0x4000;
    if (specialFont) buffer->separator = (*(u16 **)(lbl_2_bss_1A824C + 0x195464))[10];
    else if (fullWidth) buffer->separator = (*(u16 **)(lbl_2_bss_1A824C + 0x195460))[10];
    else buffer->separator = (*(u16 **)(lbl_2_bss_1A824C + 0x195460))[10];
    if (specialFont) buffer->minus = **(u16 **)(lbl_2_bss_1A824C + 0x19545C);
    else if (fullWidth) buffer->minus = **(u16 **)(lbl_2_bss_1A824C + 0x195458);
    else buffer->minus = **(u16 **)(lbl_2_bss_1A824C + 0x19545C);

    if (flags & 0x20) {
        insertNumberGlyph(glyphs, 16, buffer->separator, count - 2);
        if (value < 0) insertNumberGlyph(glyphs, 16, buffer->minus, count - 4);
    } else if (flags & 0x40) {
        insertNumberGlyph(glyphs, 16, buffer->separator, count - 3);
        if (value < 0) insertNumberGlyph(glyphs, 16, buffer->minus, count - 5);
    } else if (flags & 0x80) {
        insertNumberGlyph(glyphs, 16, buffer->separator, count - 1);
        if (value < 0) insertNumberGlyph(glyphs, 16, buffer->minus, count - 3);
    }
    if (output != NULL) {
        dst = output;
        while (*glyphs != 0x4000) *dst++ = *glyphs++;
        *dst = *glyphs;
    }
    return buffer->glyphs;
}

// .text:0x0004906C size:0x110 mapped:0x80688100
void fn_2_4906C(void) {
    s32 i;
    for (i = 0; i < 15; i++) {
        TextBank *bank = screenTextArray.textBanks[lbl_2_bss_1A824C[0x1972B8]];
        ((u16 **)(lbl_2_bss_1A824C + 0x19542C))[i] = bank->strings[i];
    }
}

// .text:0x00048DB4 size:0x2B8 mapped:0x80687E48
void fn_2_48DB4(void) {
    u32 color0 = lbl_2_rodata_940;
    u32 color1 = lbl_2_rodata_93C;
    u32 color2 = lbl_2_rodata_938;
    u32 color3 = lbl_2_rodata_938;

    LITAlloc((void **)(hugeAnimStruct + 0xAC));
    LITAlloc((void **)(hugeAnimStruct + 0xB0));
    LITAlloc((void **)(hugeAnimStruct + 0xB4));
    LITAlloc((void **)(hugeAnimStruct + 0xB8));

    LITInitAttn(*(void **)(hugeAnimStruct + 0xAC), lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(*(void **)(hugeAnimStruct + 0xAC), lbl_2_rodata_974, lbl_2_rodata_978, lbl_2_rodata_97C);
    LITInitDir(*(void **)(hugeAnimStruct + 0xAC), lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitColor(*(void **)(hugeAnimStruct + 0xAC), (GXColor *)&color0);
    LITInitDir(*(void **)(hugeAnimStruct + 0xAC), lbl_2_rodata_980, lbl_2_rodata_978, lbl_2_rodata_97C);

    LITInitAttn(*(void **)(hugeAnimStruct + 0xB0), lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(*(void **)(hugeAnimStruct + 0xB0), lbl_2_rodata_980, lbl_2_rodata_984, lbl_2_rodata_988);
    LITInitDir(*(void **)(hugeAnimStruct + 0xB0), lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitColor(*(void **)(hugeAnimStruct + 0xB0), (GXColor *)&color1);

    LITInitAttn(*(void **)(hugeAnimStruct + 0xB4), lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(*(void **)(hugeAnimStruct + 0xB4), lbl_2_rodata_94C, lbl_2_rodata_978, lbl_2_rodata_97C);
    LITInitDir(*(void **)(hugeAnimStruct + 0xB4), lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitColor(*(void **)(hugeAnimStruct + 0xB4), (GXColor *)&color2);

    LITInitAttn(*(void **)(hugeAnimStruct + 0xB8), lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(*(void **)(hugeAnimStruct + 0xB8), lbl_2_rodata_94C, lbl_2_rodata_978, lbl_2_rodata_97C);
    LITInitDir(*(void **)(hugeAnimStruct + 0xB8), lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitColor(*(void **)(hugeAnimStruct + 0xB8), (GXColor *)&color3);
}

// .text:0x00048D54 size:0x60 mapped:0x80687DE8
void fn_2_48D54(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        LITXForm(*(void **)(hugeAnimStruct + 0xAC + i * 4), (u8 *)fn_80052768_getCamera(0) + 0x40);
    }
}

// .text:0x00048D08 size:0x4C mapped:0x80687D9C
void fn_2_48D08(void) {
    u32 idx = *(u32 *)(lbl_2_bss_1A824C + 0x19769C);
    f32 *p = (f32 *)(hugeAnimStruct + idx * 0x27C + 0xC04);
    p[13] = lbl_2_rodata_94C;
    p[14] = lbl_2_rodata_94C;
    p[15] = lbl_2_rodata_94C;
    p[16] = lbl_2_rodata_94C;
    p[17] = lbl_2_rodata_94C;
    p[18] = lbl_2_rodata_94C;
}

// .text:0x00048BE0 size:0x128 mapped:0x80687C74
void fn_2_48BE0(void) {
    Vec pos;
    Vec delta;
    u8 *entry;
    u32 idx;
    f32 angle;

    idx = *(u32 *)(lbl_2_bss_1A824C + 0x19769C);
    entry = hugeAnimStruct + idx * 0x27C + 0xC04;
    memcpy(&pos, entry + 0x34, 12);
    PSVECSubtract(&pos, (Vec *)lbl_2_data_132F8, &delta);
    delta.x *= lbl_2_rodata_9A0;
    delta.z *= lbl_2_rodata_9A0;
    if (delta.x != lbl_2_rodata_94C || delta.z != lbl_2_rodata_94C) {
        lbl_2_bss_55B8 = (f32)atan2(delta.x, delta.z);
    }
    memcpy(lbl_2_data_132F8, entry + 0x34, 12);
    *(f32 *)(entry + 0x34) = pos.x;
    *(f32 *)(entry + 0x38) = pos.y;
    *(f32 *)(entry + 0x3C) = pos.z;
    *(f32 *)(entry + 0x40) = *(f32 *)(lbl_2_data_132EC + 0x0);
    *(f32 *)(entry + 0x44) = lbl_2_bss_55B8;
    *(f32 *)(entry + 0x48) = *(f32 *)(lbl_2_data_132EC + 0x8);
}

// .text:0x00048A1C size:0x1C4 mapped:0x80687AB0
void fn_2_48A1C(void) {
    Vec pos;
    Vec delta;
    u8 *entry;
    u8 *stick;
    u32 idx;

    idx = *(u32 *)(lbl_2_bss_1A824C + 0x19769C);
    entry = hugeAnimStruct + idx * 0x27C + 0xC04;
    memcpy(&pos, entry + 0x34, 12);
    PSVECSubtract(&pos, (Vec *)lbl_2_data_13310, &delta);
    delta.x *= lbl_2_rodata_9A0;
    delta.z *= lbl_2_rodata_9A0;
    stick = AtBat_ButtonInput1 + (s8)lbl_2_bss_1A824C[0x197863] * 0x20;
    pos.x = pos.x + (f32)(s8)stick[0x10] / lbl_2_rodata_9A4;
    pos.z = pos.z + (f32)(s8)stick[0x11] / lbl_2_rodata_9A4;
    if (delta.x != lbl_2_rodata_94C || delta.z != lbl_2_rodata_94C) {
        lbl_2_bss_55BC = (f32)atan2(delta.x, delta.z);
    }
    memcpy(lbl_2_data_13310, entry + 0x34, 12);
    *(f32 *)(entry + 0x34) = pos.x;
    *(f32 *)(entry + 0x38) = pos.y;
    *(f32 *)(entry + 0x3C) = pos.z;
    *(f32 *)(entry + 0x40) = *(f32 *)(lbl_2_data_13304 + 0x0);
    *(f32 *)(entry + 0x44) = lbl_2_bss_55BC;
    *(f32 *)(entry + 0x48) = *(f32 *)(lbl_2_data_13304 + 0x8);
}

// .text:0x000489DC size:0x40 mapped:0x80687A70
void fn_2_489DC(void) {
    fn_800A7D4C(12, lbl_2_data_13228 + drawStadiumRelated * 8);
}

// .text:0x000487A0 size:0x23C mapped:0x80687834
void fn_2_487A0(void) {
    s32 i;
    f32 fi;

    GXLoadPosMtxImm((f32 (*)[4])((u8 *)fn_80052768_getCamera(0) + 0x40), 0);
    GXSetCurrentMtx(0);
    GXSetColorUpdate(TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, 0xFF, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, FALSE, 1, 1, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, FALSE, 1, 1, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);

    for (i = -24; i < 25; i++) {
        fi = (f32)i;
        GXBegin(GX_LINES, GX_VTXFMT0, 4);
        GXWGFifo.f32 = lbl_2_rodata_98C;
        GXWGFifo.f32 = lbl_2_rodata_94C;
        GXWGFifo.f32 = fi;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xC8;
        GXWGFifo.f32 = lbl_2_rodata_990;
        GXWGFifo.f32 = lbl_2_rodata_94C;
        GXWGFifo.f32 = fi;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xC8;
        GXWGFifo.f32 = fi;
        GXWGFifo.f32 = lbl_2_rodata_94C;
        GXWGFifo.f32 = lbl_2_rodata_98C;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xC8;
        GXWGFifo.f32 = fi;
        GXWGFifo.f32 = lbl_2_rodata_94C;
        GXWGFifo.f32 = lbl_2_rodata_990;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xC8;
    }
}

// .text:0x000481F4 size:0x5AC mapped:0x80687288
void fn_2_481F4(void) {
    u32 maxSize = 0;
    u32 aligned;
    u8 *pool;
    u8 *next;
    s32 off = 0;
    s32 i;
    s32 j;
    u32 color0;
    u32 color1;
    u32 color2;
    u32 color3;
    u8 *entry;
    u32 idx;
    u8 *cdi = currentDrawingItem;
    s32 character = lbl_2_bss_1A8248[0x441D];

    switch (lbl_2_bss_55C0) {
    case 0:
        *(u32 *)(lbl_2_bss_1A824C + 0x195424) = memoryUsedOrStorage[1];
        *(u32 *)(lbl_2_bss_1A824C + 0x195428) = memoryUsedOrStorage[2];

        color0 = lbl_2_rodata_940;
        color1 = lbl_2_rodata_93C;
        color2 = lbl_2_rodata_938;
        color3 = lbl_2_rodata_938;
        LITAlloc((void **)(hugeAnimStruct + 0xAC));
        LITAlloc((void **)(hugeAnimStruct + 0xB0));
        LITAlloc((void **)(hugeAnimStruct + 0xB4));
        LITAlloc((void **)(hugeAnimStruct + 0xB8));

        LITInitAttn(*(void **)(hugeAnimStruct + 0xAC), lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
        LITInitPos(*(void **)(hugeAnimStruct + 0xAC), lbl_2_rodata_974, lbl_2_rodata_978, lbl_2_rodata_97C);
        LITInitDir(*(void **)(hugeAnimStruct + 0xAC), lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
        LITInitColor(*(void **)(hugeAnimStruct + 0xAC), (GXColor *)&color0);
        LITInitDir(*(void **)(hugeAnimStruct + 0xAC), lbl_2_rodata_980, lbl_2_rodata_978, lbl_2_rodata_97C);

        LITInitAttn(*(void **)(hugeAnimStruct + 0xB0), lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
        LITInitPos(*(void **)(hugeAnimStruct + 0xB0), lbl_2_rodata_980, lbl_2_rodata_984, lbl_2_rodata_988);
        LITInitDir(*(void **)(hugeAnimStruct + 0xB0), lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
        LITInitColor(*(void **)(hugeAnimStruct + 0xB0), (GXColor *)&color1);

        LITInitAttn(*(void **)(hugeAnimStruct + 0xB4), lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
        LITInitPos(*(void **)(hugeAnimStruct + 0xB4), lbl_2_rodata_94C, lbl_2_rodata_978, lbl_2_rodata_97C);
        LITInitDir(*(void **)(hugeAnimStruct + 0xB4), lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
        LITInitColor(*(void **)(hugeAnimStruct + 0xB4), (GXColor *)&color2);

        LITInitAttn(*(void **)(hugeAnimStruct + 0xB8), lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
        LITInitPos(*(void **)(hugeAnimStruct + 0xB8), lbl_2_rodata_94C, lbl_2_rodata_978, lbl_2_rodata_97C);
        LITInitDir(*(void **)(hugeAnimStruct + 0xB8), lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
        LITInitColor(*(void **)(hugeAnimStruct + 0xB8), (GXColor *)&color3);

        fn_2_93C64();
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 6; j++) {
                u32 size = allocationEntrySize(off);
                if (maxSize < size) {
                    maxSize = size;
                }
                off += 0x130;
            }
        }
        aligned = OSRoundUp32B(maxSize);
        pool = _OSAllocFromHeap(0x20, aligned * 4);
        next = pool + aligned;
        *(u8 **)(hugeAnimStruct + 0xE88) = next;
        next += aligned;
        *(u8 **)(hugeAnimStruct + 0x1104) = next;
        next += aligned;
        *(u8 **)(hugeAnimStruct + 0x2C8C) = pool;
        *(u8 **)(hugeAnimStruct + 0xC0C) = pool;
        *(u8 **)(hugeAnimStruct + 0x1380) = next;

        fn_2_47540();
        initActorArray(0xD);
        fn_80014204(4);
        *(s32 *)(hugeAnimStruct + 0x13C) = fn_80023AA4();

        hugeAnimStruct[0xE59] = 0;
        *(u32 *)(hugeAnimStruct + 0x2C50) = 0;
        hugeAnimStruct[0x2D6A] = 0xFF;
        hugeAnimStruct[0xE5B] = 0xFF;
        hugeAnimStruct[0x10D5] = 1;
        *(u32 *)(hugeAnimStruct + 0x2C54) = 0;
        hugeAnimStruct[0x2D6B] = 0xFF;
        hugeAnimStruct[0x10D7] = 0xFF;
        hugeAnimStruct[0x1351] = 2;
        *(u32 *)(hugeAnimStruct + 0x2C58) = 0;
        hugeAnimStruct[0x2D6C] = 0xFF;
        hugeAnimStruct[0x1353] = 0xFF;
        hugeAnimStruct[0x15CD] = 3;
        *(u32 *)(hugeAnimStruct + 0x2C5C) = 0;
        hugeAnimStruct[0x2D6D] = 0xFF;
        hugeAnimStruct[0x15CF] = 0xFF;
        hugeAnimStruct[0x2D7F] = 0xFF;
        hugeAnimStruct[0x2D80] = 0xFF;
        hugeAnimStruct[0x2D81] = 0xFF;
        hugeAnimStruct[0x2D82] = 0xFF;
        hugeAnimStruct[0x2D83] = 0xFF;
        hugeAnimStruct[0x2D84] = 0xFF;
        hugeAnimStruct[0x2D85] = 0xFF;
        hugeAnimStruct[0x2D86] = 0xFF;
        hugeAnimStruct[0x2D87] = 0xFF;
        hugeAnimStruct[0x2D77] = 0;
        hugeAnimStruct[0x2D89] = 0xFF;
        hugeAnimStruct[0x2D8A] = 0xFF;
        hugeAnimStruct[0x2D8B] = 0xFF;
        hugeAnimStruct[0x2D8C] = 0xFF;
        hugeAnimStruct[0x2D77] = 0;
        hugeAnimStruct[0x2D7B] = 0;
        hugeAnimStruct[0x2D7C] = 0;
        lbl_2_bss_55C0 = 1;
        break;
    case 1:
        if (fn_80016710(character, *(s16 *)(cdi + 0x16)) == 0) {
            return;
        }
        *(s32 *)(lbl_2_bss_1A824C + 0x19769C) = *(s16 *)(cdi + 0x16);
        lbl_2_bss_55C0 = 0;
        idx = *(u32 *)(lbl_2_bss_1A824C + 0x19769C);
        entry = hugeAnimStruct + idx * 0x27C + 0xC04;
        *(f32 *)(entry + 0x34) = lbl_2_rodata_94C;
        *(f32 *)(entry + 0x38) = lbl_2_rodata_94C;
        *(f32 *)(entry + 0x3C) = lbl_2_rodata_94C;
        *(f32 *)(entry + 0x40) = lbl_2_rodata_94C;
        *(f32 *)(entry + 0x44) = lbl_2_rodata_94C;
        *(f32 *)(entry + 0x48) = lbl_2_rodata_94C;
        hugeAnimStruct[0x2D77] = 0;
        *(s16 *)(*(u8 **)(currentDrawingItem + 0xC) + 0x10) = 1;
        removeCurrentDrawingItem();
        return;
    }
}

// .text:0x000481B8 size:0x3C mapped:0x8068724C
void fn_2_481B8(void) {
    fn_800BD670(*(void **)(hugeAnimStruct + 0x60), (u8 *)fn_80052768_getCamera(0) + 0x40);
}

// .text:0x00047FF8 size:0x1C0 mapped:0x8068708C
void fn_2_47FF8(void) {
    Mtx44 proj;
    s32 i;
    u8 *base = lbl_2_bss_1A824C + 0x190000;
    C_MTXFrustum(proj, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    for (i = 0; i < 4; i++) {
        LITXForm(*(void **)(hugeAnimStruct + 0xAC + i * 4), (u8 *)fn_80052768_getCamera(0) + 0x40);
    }
    if (base[0x784A] != 0) {
        if (base[0x7846] == 1) {
            fn_2_6A87C();
            if (base[0x7847] != 0) {
                fn_2_93BF8(lbl_2_bss_1A81D4);
            }
        } else if (base[0x7846] == 2) {
            fn_2_9007C();
        } else {
            fn_2_93BF8(lbl_2_bss_1A81D4);
        }
    } else {
        fn_2_93BF8(lbl_2_bss_1A81D4);
    }
    memcpy((u8 *)fn_80052768_getCamera(0) + 0x70, lbl_2_bss_1A81D4 + 0x4C, 12);
    memcpy((u8 *)fn_80052768_getCamera(0) + 0x7C, lbl_2_bss_1A81D4 + 0x40, 12);
    *(f32 *)((u8 *)fn_80052768_getCamera(0) + 0xA4) = *(f32 *)(lbl_2_bss_1A81D4 + 0x3C);
    PSMTXCopy((f32 (*)[4])((u8 *)fn_80052768_getCamera(0) + 0x40), (f32 (*)[4])lbl_2_bss_1A81D4);
    graphics_relatedToVsScreen();
}

// .text:0x00047CFC size:0x2FC mapped:0x80686D90
void fn_2_47CFC(void) {
    Mtx44 proj;
    Vec tmp;
    s32 i;
    u8 *entry;
    u8 *rec;
    u8 *obj;
    u8 *pose;
    f32 rotScale;

    C_MTXFrustum(proj, lbl_2_rodata_950, lbl_2_rodata_954, lbl_2_rodata_958, lbl_2_rodata_95C, lbl_2_rodata_960, lbl_2_rodata_964);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_2_8D024();

    rotScale = lbl_2_rodata_968;
    for (i = 0; i < *(s16 *)(lbl_2_bss_1A824C + 0x197746); i++) {
        entry = hugeAnimStruct + i * 0x27C;
        rec = *(u8 **)(hugeAnimStruct + 0x60) + 0x34 + i * 0x90;
        rec[0x6C] = entry[0xE61] & 1;
        CTRLSetTranslation(rec + 0x10, *(f32 *)(entry + 0xC38), *(f32 *)(entry + 0xC3C), *(f32 *)(entry + 0xC40));
        CTRLSetRotation(rec + 0x10, rotScale * *(f32 *)(entry + 0xC44), rotScale * *(f32 *)(entry + 0xC48),
                        rotScale * *(f32 *)(entry + 0xC4C));

        if (lbl_2_bss_1A824C[0x197848] == 0) {
            memcpy(&tmp, lbl_2_data_12EA8, 12);
            if (lbl_2_bss_1A8248[0x441C] == 5 && i == 0) {
                PSVECScale(&tmp, lbl_2_rodata_96C, &tmp);
            }
            CTRLSetScale(rec + 0x10, tmp.x, tmp.y, tmp.z);
        } else {
            memcpy(&tmp, lbl_2_data_12EB4, 12);
            CTRLSetScale(rec + 0x10, tmp.x, tmp.y, tmp.z);
        }
        *(f32 *)(rec + 0x54) = lbl_2_rodata_970;
        rec[0x5A] = 1;

        obj = *(u8 **)(entry + 0xC34);
        if (obj != NULL && *(u32 *)(obj + 4) != 0 && *(u32 *)(obj + 0x68) != 0 && obj[0xCC] != 0) {
            pose = *(u8 **)(hugeAnimStruct + 0x13C) + obj[0x60] * 0x90 + 0x34;
            *(f32 *)(obj + 0x14) = lbl_2_rodata_970;
            obj[0x21] |= 0x80;
            fn_80024DB0(obj + 0x10);
            fn_80024FA4(pose, *(void **)(obj + 0x30), obj + 0x10, -1);

            pose = *(u8 **)(hugeAnimStruct + 0x13C) + obj[0xC4] * 0x90 + 0x34;
            *(f32 *)(obj + 0x78) = lbl_2_rodata_970;
            obj[0x85] |= 0x80;
            fn_80024DB0(obj + 0x74);
            fn_80024FA4(pose, *(void **)(obj + 0x94), obj + 0x74, -1);
        }
    }
    fn_2_47B24(*(u16 **)(hugeAnimStruct + 0x60));
}

// .text:0x00047B24 size:0x1D8 mapped:0x80686BB8
void fn_2_47B24(u16 *list) {
    u16 i;
    u16 k;
    Mtx mtx;
    u8 *obj;
    u8 *actor;
    u8 *anim;

    if (lbl_2_bss_340140[0x307A] == 3) {
        return;
    }
    for (i = 0; i < list[0]; i++) {
        anim = *(u8 **)(hugeAnimStruct + 0x2C50 + i * 4);
        if (anim != NULL && anim[0x25D] != 0) {
            obj = getAnimObjectActor(anim);
            actor = *(u8 **)obj;
            if (actor != NULL) {
                if (obj[0x58] != 0) {
                    ACTSetAnimation(actor, *(void **)(obj + 0x4), NULL, *(u16 *)(obj + 0xE), 0.0f, *(f32 *)(obj + 0x60));
                }
                if (obj[0x59] != 0) {
                    setActorAnimFrame(actor, *(f32 *)(obj + 0x5C));
                }
                if (obj[0x5A] != 0) {
                    ACTSetSpeed(actor, *(f32 *)(obj + 0x54));
                }
                if (obj[0x5B] & 2) {
                    updateBoneParam(actor, obj[0x5B] & 1);
                }
                Set_FUN_800b2b6c(actor, *(s32 *)(obj + 0x68));
                if (obj[0x6C] != 0) {
                    fn_800BDA24(obj);
                }
                for (k = 0; k < returnScissorMode(); k++) {
                    u8 *cam = (u8 *)returnFloatFromModeIndex(k) + 0x40;
                    PSMTXTrans(mtx, *(f32 *)(anim + 0x34), *(f32 *)(anim + 0x38), *(f32 *)(anim + 0x3C));
                    PSMTXConcat((f32 (*)[4])cam, mtx, mtx);
                    actor[0x98] = (actor[0x98] & ~(3 << (3 * k))) | (fn_800B3C04(k, actor, mtx) << (3 * k));
                }
                obj[0x58] = 0;
                obj[0x59] = 0;
                obj[0x5A] = 0;
                obj[0x5B] &= 1;
            }
        }
    }
}

// .text:0x00047AFC size:0x28 mapped:0x80686B90
void fn_2_47AFC(void) {
    s32 i;
    for (i = 0; i < 13; i++) {
    }
}

// .text:0x000478F4 size:0x208 mapped:0x80686988
void fn_2_478F4(void) {
    u32 maxSize = 0;
    u32 aligned;
    u8 *pool;
    u8 *next;
    s32 i;
    for (i = 0; i < 54; i++) {
        u32 size = allocationEntrySize(i * 0x130);
        if (maxSize < size) {
            maxSize = size;
        }
    }
    aligned = OSRoundUp32B(maxSize);
    pool = _OSAllocFromHeap(0x20, aligned * 4);
    next = pool + aligned;
    *(u8 **)(hugeAnimStruct + 0xE88) = next;
    next += aligned;
    *(u8 **)(hugeAnimStruct + 0x1104) = next;
    next += aligned;
    *(u8 **)(hugeAnimStruct + 0x2C8C) = pool;
    *(u8 **)(hugeAnimStruct + 0xC0C) = pool;
    *(u8 **)(hugeAnimStruct + 0x1380) = next;

    fn_2_47540();
    initActorArray(0xD);
    fn_80014204(4);
    *(s32 *)(hugeAnimStruct + 0x13C) = fn_80023AA4();

    hugeAnimStruct[0xE59] = 0;
    *(u32 *)(hugeAnimStruct + 0x2C50) = 0;
    hugeAnimStruct[0x2D6A] = 0xFF;
    hugeAnimStruct[0xE5B] = 0xFF;
    hugeAnimStruct[0x10D5] = 1;
    *(u32 *)(hugeAnimStruct + 0x2C54) = 0;
    hugeAnimStruct[0x2D6B] = 0xFF;
    hugeAnimStruct[0x10D7] = 0xFF;
    hugeAnimStruct[0x1351] = 2;
    *(u32 *)(hugeAnimStruct + 0x2C58) = 0;
    hugeAnimStruct[0x2D6C] = 0xFF;
    hugeAnimStruct[0x1353] = 0xFF;
    hugeAnimStruct[0x15CD] = 3;
    *(u32 *)(hugeAnimStruct + 0x2C5C) = 0;
    hugeAnimStruct[0x2D6D] = 0xFF;
    hugeAnimStruct[0x15CF] = 0xFF;
    hugeAnimStruct[0x2D7F] = 0xFF;
    hugeAnimStruct[0x2D80] = 0xFF;
    hugeAnimStruct[0x2D81] = 0xFF;
    hugeAnimStruct[0x2D82] = 0xFF;
    hugeAnimStruct[0x2D83] = 0xFF;
    hugeAnimStruct[0x2D84] = 0xFF;
    hugeAnimStruct[0x2D85] = 0xFF;
    hugeAnimStruct[0x2D86] = 0xFF;
    hugeAnimStruct[0x2D87] = 0xFF;
    hugeAnimStruct[0x2D89] = 0xFF;
    hugeAnimStruct[0x2D8A] = 0xFF;
    hugeAnimStruct[0x2D8B] = 0xFF;
    hugeAnimStruct[0x2D8C] = 0xFF;
    hugeAnimStruct[0x2D77] = 0;
    hugeAnimStruct[0x2D7B] = 0;
    hugeAnimStruct[0x2D7C] = 0;
}

// .text:0x000477C0 size:0x134 mapped:0x80686854
void fn_2_477C0(void) {
    u32 maxSize = 0;
    u32 aligned;
    u8 *pool;
    u8 *next;
    s32 i;
    for (i = 0; i < 54; i++) {
        u32 size = allocationEntrySize(i * 0x130);
        if (maxSize < size) {
            maxSize = size;
        }
    }
    aligned = OSRoundUp32B(maxSize);
    pool = _OSAllocFromHeap(0x20, aligned * 4);
    next = pool + aligned;
    *(u8 **)(hugeAnimStruct + 0xE88) = next;
    next += aligned;
    *(u8 **)(hugeAnimStruct + 0x1104) = next;
    next += aligned;
    *(u8 **)(hugeAnimStruct + 0x2C8C) = pool;
    *(u8 **)(hugeAnimStruct + 0xC0C) = pool;
    *(u8 **)(hugeAnimStruct + 0x1380) = next;
}

// .text:0x0004777C size:0x44 mapped:0x80686810
void fn_2_4777C(void) {
    void *obj = *(void **)(hugeAnimStruct + 0x2C8C);
    if (obj != NULL) {
        fn_800ACFB0(obj);
        *(void **)(hugeAnimStruct + 0x2C8C) = NULL;
    }
}

// .text:0x00047540 size:0x23C mapped:0x806865D4
void fn_2_47540(void) {
    u32 maxD = 0;
    u32 maxA = 0;
    u32 maxB = 0;
    u32 maxC = 0;
    u32 sizeA;
    u32 sizeB;
    u32 sizeC;
    u32 sizeD;
    u8 *pool;
    u8 *q;
    s32 e;
    u8 *entry;

    for (e = 0; e < 4; e++) {
        entry = lbl_2_data_12EC0 + e * 0x130;
        if (maxD < (*(u32 *)(entry + 0x44) & 0x0FFFFFFF)) {
            maxD = *(u32 *)(entry + 0x44) & 0x0FFFFFFF;
        }
        if (maxA < (*(u32 *)(entry + 0x34) & 0x0FFFFFFF)) {
            maxA = *(u32 *)(entry + 0x34) & 0x0FFFFFFF;
        }
        if (maxB < (*(u32 *)(entry + 0x54) & 0x0FFFFFFF)) {
            maxB = *(u32 *)(entry + 0x54) & 0x0FFFFFFF;
        }
        if (maxC < (*(u32 *)(entry + 0x24) & 0x0FFFFFFF)) {
            maxC = *(u32 *)(entry + 0x24) & 0x0FFFFFFF;
        }
    }

    sizeA = (maxA + 0x1F) & ~0x1F;
    sizeB = (maxB + 0x1F) & ~0x1F;
    sizeC = (maxC + 0x1F) & ~0x1F;
    sizeD = (maxD + 0x1F) & ~0x1F;
    *(u32 *)(hugeAnimStruct + 0x2C98) = sizeD;
    *(u32 *)(hugeAnimStruct + 0x2C94) = sizeA;
    *(u32 *)(hugeAnimStruct + 0x2C9C) = sizeB;
    *(u32 *)(hugeAnimStruct + 0x2C90) = sizeC;

    pool = _OSAllocFromHeap(0x20, (sizeA + sizeB + sizeC + sizeD) * 4);
    *(u8 **)(hugeAnimStruct + 0x2C88) = pool;
    *(u8 **)(hugeAnimStruct + 0x2CEC) = pool;

    q = pool + sizeD;
    *(u8 **)(hugeAnimStruct + 0x2CF0) = q;
    q += sizeA;
    *(u8 **)(hugeAnimStruct + 0x2CF4) = q;
    q += sizeB;
    *(u8 **)(hugeAnimStruct + 0x2CF8) = q;
    q += sizeC;
    *(u32 *)(hugeAnimStruct + 0xC14) = 0;
    *(u32 *)(hugeAnimStruct + 0xC20) = 0;
    *(u32 *)(hugeAnimStruct + 0xC24) = 0;
    *(u32 *)(hugeAnimStruct + 0xC18) = 0;
    *(u32 *)(hugeAnimStruct + 0xC1C) = 0;
    *(u8 **)(hugeAnimStruct + 0x2D00) = q;
    q += sizeD;
    *(u8 **)(hugeAnimStruct + 0x2D04) = q;
    q += sizeA;
    *(u8 **)(hugeAnimStruct + 0x2D08) = q;
    q += sizeB;
    *(u8 **)(hugeAnimStruct + 0x2D0C) = q;
    q += sizeC;
    *(u32 *)(hugeAnimStruct + 0xE90) = 0;
    *(u32 *)(hugeAnimStruct + 0xE9C) = 0;
    *(u32 *)(hugeAnimStruct + 0xEA0) = 0;
    *(u32 *)(hugeAnimStruct + 0xE94) = 0;
    *(u32 *)(hugeAnimStruct + 0xE98) = 0;
    *(u8 **)(hugeAnimStruct + 0x2D14) = q;
    q += sizeD;
    *(u8 **)(hugeAnimStruct + 0x2D18) = q;
    q += sizeA;
    *(u8 **)(hugeAnimStruct + 0x2D1C) = q;
    q += sizeB;
    *(u8 **)(hugeAnimStruct + 0x2D20) = q;
    q += sizeC;
    *(u32 *)(hugeAnimStruct + 0x110C) = 0;
    *(u32 *)(hugeAnimStruct + 0x1118) = 0;
    *(u32 *)(hugeAnimStruct + 0x111C) = 0;
    *(u32 *)(hugeAnimStruct + 0x1110) = 0;
    *(u32 *)(hugeAnimStruct + 0x1114) = 0;
    *(u8 **)(hugeAnimStruct + 0x2D28) = q;
    q += sizeD;
    *(u8 **)(hugeAnimStruct + 0x2D2C) = q;
    q += sizeA;
    *(u8 **)(hugeAnimStruct + 0x2D30) = q;
    q += sizeB;
    *(u8 **)(hugeAnimStruct + 0x2D34) = q;
    *(u32 *)(hugeAnimStruct + 0x1388) = 0;
    *(u32 *)(hugeAnimStruct + 0x1394) = 0;
    *(u32 *)(hugeAnimStruct + 0x1398) = 0;
    *(u32 *)(hugeAnimStruct + 0x138C) = 0;
    *(u32 *)(hugeAnimStruct + 0x1390) = 0;
}

// .text:0x000474FC size:0x44 mapped:0x80686590
void fn_2_474FC(void) {
    void *obj = *(void **)(hugeAnimStruct + 0x2C88);
    if (obj != NULL) {
        fn_800ACFB0(obj);
        *(void **)(hugeAnimStruct + 0x2C88) = NULL;
    }
}

// .text:0x000474F8 size:0x4 mapped:0x8068658C
void fn_2_474F8(void) {
    return;
}

// .text:0x000472C4 size:0x234 mapped:0x80686358
static inline BOOL invalidTimerPeriod(s16 period, s16 step) {
    s32 differenceBits = period ^ step;
    return (period == 0) | (((differenceBits >> 1) - (differenceBits & period)) < 0);
}

void fn_2_472C4(s16 *timer, s16 *value, s16 step, s16 period, s16 flags) {
    s32 remainder;
    s16 lastPeriod;
    s16 limit;
    s16 current;
    s16 amount;
    u16 input;

    if (step == 0) return;
    if (invalidTimerPeriod(period, step)) period = step;
    remainder = step % period;
    lastPeriod = period;
    if (remainder != 0) lastPeriod = remainder;
    limit = step - period;
    if (flags & 4) limit = step - lastPeriod;
    input = *(u16 *)(AtBat_ButtonInput1 + (s8)lbl_2_bss_1A824C[0x197863] * 0x20 + 4);
    switch (input) {
    case PAD_TRIGGER_R:
    case PAD_BUTTON_DOWN:
        if ((flags & 8) || value == NULL || step <= period) break;
        current = *value;
        amount = period - current % period;
        if (current == limit) {
            if (flags & 2) {
                *value = 0;
            } else {
                *value = limit;
                break;
            }
        } else {
            current += amount;
            *value = current;
            if (current > limit) *value = limit;
        }
        *timer = 0;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        break;
    case PAD_TRIGGER_L:
    case PAD_BUTTON_UP:
        if ((flags & 8) || value == NULL || step <= period) break;
        current = *value;
        amount = current % period;
        if (amount == 0) amount = period;
        if (current <= 0) {
            if (flags & 2) {
                *value = limit;
                *timer = 0;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else {
            *value = *value - amount;
            *timer = 0;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        }
        break;
    }
}

static inline void playCountdownSfx(s32 fid, s32 volIdx) {
    sndFXStartEx(fid, lbl_800EFBA4[volIdx], 0x3F, 0);
}

// .text:0x00046D94 size:0x530 mapped:0x80685E28
void fn_2_46D94(s16 *timer, s16 *value, s16 step, s16 period, u16 flags) {
    s32 remainder;
    s16 lastPeriod;
    s16 limit;
    s16 current;
    s16 amount;
    s16 t;
    s16 v;
    u16 input;

    if (step == 0) return;
    if (invalidTimerPeriod(period, step)) period = step;
    remainder = step % period;
    lastPeriod = period;
    if (remainder != 0) lastPeriod = remainder;
    limit = step - period;
    if (flags & 4) limit = step - lastPeriod;
    input = *(u16 *)(AtBat_ButtonInput1 + (s8)lbl_2_bss_1A824C[0x197863] * 0x20 + 4);
    switch (input) {
    case PAD_BUTTON_UP:
        if (value != NULL) {
            *timer = *timer - 1;
            if (*timer < 0) {
                if (*value != 0) {
                    *value = *value - 1;
                    if (!(flags & 0x10)) playCountdownSfx(0x1B7, 0);
                } else if (flags & 1) {
                    if (flags & 4) *timer = lastPeriod - 1;
                    else *timer = period - 1;
                    *value = limit;
                    if (!(flags & 0x10)) playCountdownSfx(0x1B7, 0);
                    break;
                }
                *timer = *timer + 1;
            } else {
                if (!(flags & 0x10)) playCountdownSfx(0x1B7, 0);
            }
        } else {
            *timer = *timer - 1;
            if (*timer < 0) {
                if (flags & 1) {
                    *timer = step - 1;
                    if (!(flags & 0x10)) playCountdownSfx(0x1B7, 0);
                } else {
                    *timer = *timer + 1;
                }
            } else {
                if (!(flags & 0x10)) playCountdownSfx(0x1B7, 0);
            }
        }
        break;
    case PAD_BUTTON_DOWN:
        if (value != NULL) {
            t = *timer;
            v = *value;
            if (t + v >= step - 1) {
                if (v < limit) {
                    *value = v + 1;
                    *timer = *timer - 1;
                } else if (flags & 1) {
                    *timer = 0;
                    *value = 0;
                } else {
                    break;
                }
                if (!(flags & 0x10)) playCountdownSfx(0x1B7, 0);
            } else if (t >= period - 1) {
                if (v < limit) {
                    *value = v + 1;
                } else if (flags & 1) {
                    *timer = 0;
                    *value = 0;
                } else {
                    break;
                }
                if (!(flags & 0x10)) playCountdownSfx(0x1B7, 0);
            } else {
                *timer = t + 1;
                if (!(flags & 0x10)) playCountdownSfx(0x1B7, 0);
            }
        } else {
            *timer = *timer + 1;
            if (*timer >= step) {
                if (flags & 1) *timer = 0;
                else {
                    *timer = *timer - 1;
                    break;
                }
            }
            if (!(flags & 0x10)) playCountdownSfx(0x1B7, 0);
        }
        break;
    case PAD_TRIGGER_R:
        if ((flags & 8) || value == NULL || step <= period) break;
        current = *value;
        amount = period - current % period;
        if (current == limit) {
            if (flags & 2) *value = 0;
            else {
                *value = limit;
                break;
            }
        } else {
            current += amount;
            *value = current;
            if (current > limit) *value = limit;
        }
        *timer = 0;
        if (!(flags & 0x10)) playCountdownSfx(0x1B8, 1);
        break;
    case PAD_TRIGGER_L:
        if ((flags & 8) || value == NULL || step <= period) break;
        current = *value;
        amount = current % period;
        if (amount == 0) amount = period;
        if (current <= 0) {
            if (flags & 2) {
                *value = limit;
                *timer = 0;
                if (!(flags & 0x10)) playCountdownSfx(0x1B8, 1);
            }
        } else {
            *value = *value - amount;
            *timer = 0;
            if (!(flags & 0x10)) playCountdownSfx(0x1B8, 1);
        }
        break;
    }
}

// .text:0x00046D34 size:0x60 mapped:0x80685DC8
void fn_2_46D34(s32 delta) {
    addStatCounter(delta);
}

// .text:0x00046D00 size:0x34 mapped:0x80685D94
BOOL fn_2_46D00(void) {
    u8 *state = lbl_2_bss_1A8248;
    if (state[0x441C] == 5 && state[0x4422] >= 6) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x00046C88 size:0x78 mapped:0x80685D1C
void fn_2_46C88(void *self) {
    Vec v;
    fn_2_68690(0);
    fn_2_68DAC(self, &v);
    PSVECScale(&v, lbl_2_rodata_948, &v);
    *lbl_2_data_13374 = lbl_803CBD0C;
    fn_80031CA4(&v, lbl_2_data_13374);
}
