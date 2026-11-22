#include "menus/text_50898.h"
#include "static/menu_control.h"
#include "Dolphin/pad.h"
#include "text/text.h"
#include "game/character_stats.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x80062a50.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/orderchange.h"

extern u8 *lbl_2_bss_1A824C;
extern u16 lbl_2_bss_9600[];
extern u16 lbl_2_bss_9604[];
extern u16 lbl_2_bss_9608[];
extern u16 lbl_2_bss_9A08[];
extern s16 lbl_2_bss_9E08;
extern u8 lbl_2_bss_55E8[];
extern u8 lbl_2_bss_5600[];
extern u8 lbl_2_bss_33FBCC[];
extern u8 lbl_2_bss_33FB4C[];
extern u8 *lbl_2_data_1E99C[];
extern u16 lbl_2_data_1F3A0[];
extern u16 lbl_2_data_1F3B0[];
extern u32 lbl_2_data_1F3E0[];
extern u32 lbl_2_data_1F3E8[];
extern u8 menuCursors[];
extern u8 *menuControlVariables;
extern u8 menuNumber[];
extern u8 superstarUnlocked[];
extern u8 Static_Stats_Tables[];
extern u8 g_Challenge[];
extern u8 inMemRoster[];
extern u8 cursorPositions[];
extern u8 lineUpInfoStruct[];
extern u8 cardCheck[];
extern u8 g_d_GameSettings[];
extern u8 g_MatchInfo[];
extern u8 lbl_800EFBA4[];
extern u8 lbl_80354768[];
extern u8 lbl_800FEF70[];
extern SceneChangeState lbl_8037169C;

extern s16 fn_2_4EB9C(void);
extern void fn_2_4906C(void);
extern void fn_2_51890(void);
extern void fn_2_51C58(void);
extern void fn_2_51A1C(void);
extern void fn_2_5163C(void);
extern void fn_2_89F70(void);
extern void fn_2_82DE8(void);
extern void fn_2_8ABFC(void);
extern void fn_80053FE8(void);
extern void fn_2_460EC(s32 team);
extern void fn_8003BF54(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void fn_8004A34C(void *, s32, s32, s32, s32);
extern void fn_80041150(s32, s32);
extern void fn_80035B50(int arg0);
extern void set803c5f77(void);
extern s32 exitMenu(u16 input);
extern void teamLogoDetermination(s32 team);
extern void *memcpy(void *dst, const void *src, u32 n);
extern void *memset(void *dst, s32 val, u32 n);

#define STATE_BLOCK (lbl_2_bss_1A824C + 0x190000)
#define B33(off) (lbl_2_bss_33FBCC[off])
#define B33_S8(off) (((s8 *)lbl_2_bss_33FBCC)[off])
#define B33_U16(off) (*(u16 *)(lbl_2_bss_33FBCC + (off)))

void fn_2_50898(u32 arg0) {
    s32 i;

    *(u32 *)(STATE_BLOCK + 0x6FB8) = arg0;
    *(s16 *)(STATE_BLOCK + 0x6FE0) = 1;
    *(s16 *)(STATE_BLOCK + 0x6FE4) = 1;
    for (i = 0; i < 0xA8; i += 8) {
        *(s16 *)(STATE_BLOCK + i * 2 + 0x6FE8) = 0;
        *(s16 *)(STATE_BLOCK + i * 2 + 0x6FEA) = 0;
        *(s16 *)(STATE_BLOCK + i * 2 + 0x6FEC) = 0;
        *(s16 *)(STATE_BLOCK + i * 2 + 0x6FEE) = 0;
        *(s16 *)(STATE_BLOCK + i * 2 + 0x6FF0) = 0;
        *(s16 *)(STATE_BLOCK + i * 2 + 0x6FF2) = 0;
        *(s16 *)(STATE_BLOCK + i * 2 + 0x6FF4) = 0;
        *(s16 *)(STATE_BLOCK + i * 2 + 0x6FF6) = 0;
    }
    *(s16 *)(STATE_BLOCK + 0x6FD2) = 1;
    *(u32 *)(STATE_BLOCK + 0x6F30) = 1;
    *(s16 *)(STATE_BLOCK + 0x7298) = 0;
}

void fn_2_509A4(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 *state = (s8 *)((u8 *)item + 0x28);
    s16 result;

    switch (*state) {
        case 0:
            *(s16 *)(STATE_BLOCK + 0x6FD4) = 0;
            *(s16 *)(STATE_BLOCK + 0x6FD2) = 0;
            memcpy(lbl_2_bss_5600, lbl_2_data_1E99C[*(s16 *)(STATE_BLOCK + 0x6FD6)], 0x4000);
            *(u32 *)(STATE_BLOCK + 0x6F1C) = (u32)lbl_2_bss_5600;
            (*state)++;
        case 1:
            result = fn_2_4EB9C();
            if (result != 0) {
                switch (result) {
                    case 1:
                        currentDrawingItem->currentDrawingItem->state = 1;
                        removeCurrentDrawingItem();
                        break;
                    default:
                        currentDrawingItem->currentDrawingItem->state = 1;
                        removeCurrentDrawingItem();
                        break;
                }
                *state = 0;
            }
            break;
        default:
            break;
    }
    if (*(u8 *)(STATE_BLOCK + 0x783F) == 1) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        *state = 0;
    }
}

void fn_2_50B0C(s16 arg0, s16 arg1) {
    *(s16 *)(STATE_BLOCK + 0x6FD4) = 0;
    *(s16 *)(STATE_BLOCK + 0x6FD2) = 0;
    *(s16 *)(STATE_BLOCK + 0x6FD6) = arg0;
    *(s32 *)(STATE_BLOCK + 0x6F34) = arg1;
    *(s32 *)(STATE_BLOCK + 0x6F30) = arg1;
    *(s16 *)(STATE_BLOCK + 0x6FCC) = 0;
    *(s16 *)(STATE_BLOCK + 0x6FCA) = 0;
    *(s16 *)(STATE_BLOCK + 0x729E) = 0;
    *(s16 *)(STATE_BLOCK + 0x729C) = 0;
    memcpy(lbl_2_bss_5600, lbl_2_data_1E99C[*(s16 *)(STATE_BLOCK + 0x6FD6)], 0x4000);
    *(u32 *)(STATE_BLOCK + 0x6F1C) = (u32)lbl_2_bss_5600;
    fn_2_4EB9C();
}

void fn_2_50BF4(s16 arg0) {
    *(s16 *)(STATE_BLOCK + 0x6FD4) = 0;
    *(s16 *)(STATE_BLOCK + 0x6FD2) = 0;
    *(s16 *)(STATE_BLOCK + 0x6FD6) = arg0;
    *(s16 *)(STATE_BLOCK + 0x6FCC) = 0;
    *(s16 *)(STATE_BLOCK + 0x6FCA) = 0;
    *(s16 *)(STATE_BLOCK + 0x729E) = 0;
    *(s16 *)(STATE_BLOCK + 0x729C) = 0;
    memcpy(lbl_2_bss_5600, lbl_2_data_1E99C[*(s16 *)(STATE_BLOCK + 0x6FD6)], 0x4000);
    *(u32 *)(STATE_BLOCK + 0x6F1C) = (u32)lbl_2_bss_5600;
    fn_2_4EB9C();
}

void fn_2_50CC0(s16 arg0) {
    DrawingSceneStruct *node;

    *(s16 *)(STATE_BLOCK + 0x6FD6) = arg0;
    *(s16 *)(STATE_BLOCK + 0x6FCC) = 0;
    *(s16 *)(STATE_BLOCK + 0x6FCA) = 0;
    *(s16 *)(STATE_BLOCK + 0x729E) = 0;
    *(s16 *)(STATE_BLOCK + 0x729C) = 0;
    node = insertGraphicDrawingFunction(fn_2_509A4, 4);
    *(u8 *)((u8 *)node + 0x28) = 0;
}

void fn_2_50D40(s32 idx) {
    u8 *base = lbl_2_bss_55E8;
    u16 *count = (u16 *)(base + 0x401C);
    u16 *row;
    u16 *dst;
    u16 v;
    s32 w;

    if (count[idx] != 0) {
        count[idx]--;
    }
    row = (u16 *)(base + 0x4020 + (idx << 9));
    dst = (u16 *)(base + 0x4420 + (idx << 9));
    for (;;) {
        v = *row;
        row++;
        w = count[idx];
        count[idx] = w + 1;
        dst[w] = v;
        if (count[idx] == 0x100) {
            return;
        }
        if ((v & 0x4000) && (v & 0x3FFF) == 0) {
            return;
        }
    }
}

static inline u16 *pickString(u16 **strings, s32 id, u16 *fallback) {
    if (id == -1) {
        return fallback;
    }
    return strings[id];
}

void fn_2_50DB4(s32 idx, s32 arg1, u16 *src) {
    u16 *dst;
    u16 v;
    s32 w;
    u16 **strings;

    strings = screenTextArray.textBanks[*(u8 *)(STATE_BLOCK + 0x72B8)]->strings;
    if (lbl_2_bss_9600[idx] != 0) {
        lbl_2_bss_9600[idx]--;
    }
    src = pickString(strings, arg1, src);
    dst = (u16 *)((u8 *)lbl_2_bss_9608 + (idx << 9));
    for (;;) {
        w = lbl_2_bss_9600[idx];
        v = *src;
        src++;
        lbl_2_bss_9600[idx] = w + 1;
        dst[w] = v;
        if (lbl_2_bss_9600[idx] == 0x100) {
            return;
        }
        if ((v & 0x4000) && (v & 0x3FFF) == 0) {
            return;
        }
    }
}

void fn_2_50E5C(s32 idx) {
    s32 i;

    lbl_2_bss_9600[idx] = 0;
    for (i = 0; i < 0x100; i++) {
        ((u16 (*)[0x100])lbl_2_bss_9608)[idx][i] = 0;
    }
}

void fn_2_50F20(s32 idx, s32 arg1, u16 *src) {
    u16 *dst;
    u16 v;
    s32 w;
    u16 **strings;

    strings = screenTextArray.textBanks[*(u8 *)(STATE_BLOCK + 0x72B8)]->strings;
    if (lbl_2_bss_9604[idx] != 0) {
        lbl_2_bss_9604[idx]--;
    }
    src = pickString(strings, arg1, src);
    dst = (u16 *)((u8 *)lbl_2_bss_9A08 + (idx << 9));
    for (;;) {
        w = lbl_2_bss_9604[idx];
        v = *src;
        src++;
        lbl_2_bss_9604[idx] = w + 1;
        dst[w] = v;
        if (lbl_2_bss_9604[idx] == 0x100) {
            return;
        }
        if ((v & 0x4000) && (v & 0x3FFF) == 0) {
            return;
        }
    }
}

void fn_2_50FC8(s32 idx) {
    s32 i;

    lbl_2_bss_9604[idx] = 0;
    ((s16 *)(STATE_BLOCK + 0x6FCA))[idx] = 1;
    for (i = 0; i < 0x100; i++) {
        ((u16 (*)[0x100])lbl_2_bss_9A08)[idx][i] = 0;
    }
}

void fn_2_510A8(void) {
    s32 i;

    lbl_2_bss_9604[1] = 0;
    lbl_2_bss_9604[0] = 0;
    *(s16 *)(STATE_BLOCK + 0x6FCC) = 1;
    *(s16 *)(STATE_BLOCK + 0x6FCA) = 1;
    for (i = 0; i < 0x100; i++) {
        ((u16 (*)[0x100])lbl_2_bss_9A08)[0][i] = 0;
        ((u16 (*)[0x100])lbl_2_bss_9A08)[1][i] = 0;
    }
}

void fn_2_5118C(void) {
    return;
}

void fn_2_51190(u32 arg0, u32 arg1) {
    s32 i;

    *(s16 *)(STATE_BLOCK + 0x6FE0) = 1;
    *(s16 *)(STATE_BLOCK + 0x6FE4) = 1;
    for (i = 0; i < 0xA8; i++) {
        *(s16 *)(STATE_BLOCK + 0x6FE8 + i * 2) = 0;
    }
    *(u32 *)(STATE_BLOCK + 0x6FB8) = arg0;
    *(u32 *)(STATE_BLOCK + 0x6F30) = arg1;
    *(s16 *)(STATE_BLOCK + 0x6FCA) = 0;
    *(s16 *)(STATE_BLOCK + 0x7298) = 0;
    *(s16 *)(STATE_BLOCK + 0x729C) = 0;
}

void fn_2_512B4(void) {
    return;
}

u32 fn_2_512B8(void) {
    return 0;
}

void fn_2_512C0(s32 idx) {
    u16 *p;
    u16 v;

    p = ((u16 **)(STATE_BLOCK + 0x54AC))[idx];
    for (;;) {
        v = *p++;
        if (v & 0x4000) {
            switch (v & 0x3FFF) {
                case 0:
                    return;
                case 4:
                default:
                    break;
            }
            *(s16 *)(STATE_BLOCK + 0x7294 + idx * 2) += 1;
        } else {
            *(s16 *)(STATE_BLOCK + 0x7294 + idx * 2) += 1;
        }
    }
}

void fn_2_51358(void) {
    return;
}

void fn_2_5135C(u8 *arg0, s32 idx) {
    s32 n;

    n = *(u16 *)(arg0 + 0x10);
    if (n % lbl_2_data_1F3B0[idx] != 1) {
        return;
    }
    ((u32 *)(lbl_2_bss_55E8 + 8))[idx] = lbl_2_data_1F3E0[idx];
    ((u32 *)lbl_2_bss_55E8)[idx] = lbl_2_data_1F3E8[idx];
    ((u32 *)(lbl_2_bss_55E8 + 0x10))[idx] = ((u32 *)(STATE_BLOCK + 0x54AC))[idx];
}

void fn_2_513DC(void) {
    return;
}

void fn_2_513E0(void) {
    return;
}

void fn_2_513E4(void) {
    return;
}

u16 fn_2_513E8(u16 *p, u16 idx) {
    u32 sum;
    u16 v;

    sum = 0;
    for (;;) {
        v = *p;
        p++;
        if (v & 0x4000) {
            switch (v & 0x3FFF) {
                case 2:
                    sum = (u16)(sum + ((u32)lbl_2_data_1F3A0[idx] >> 1));
                    break;
                case 3:
                    sum += lbl_2_data_1F3A0[idx];
                    break;
                default:
                    return sum;
            }
        } else {
            u16 advance;

            if (v & 0x8000) {
                advance = lbl_2_data_1F3A0[idx];
            } else {
                advance = (u32)lbl_2_data_1F3A0[idx] >> 1;
            }
            sum += advance;
        }
    }
}

void fn_2_5146C(void) {
    return;
}

u16 fn_2_51470(s32 idx, u16 mode) {
    u32 *list;
    u16 *p;

    if (mode == 0) {
        list = (u32 *)(*(u32 *)((u8 *)&screenTextArray + *(u8 *)(STATE_BLOCK + 0x72B8) * 4 + 0x798));
        p = (u16 *)list[idx + 1];
    } else {
        list = (u32 *)(*(u32 *)((u8 *)&screenTextArray + *(u8 *)(STATE_BLOCK + 0x72B8) * 4 + 0x798));
        p = (u16 *)list[idx + 1];
    }
    return fn_2_513E8(p, mode);
}

void fn_2_51568(void) {
    return;
}

u32 fn_2_5156C(s32 idx, u16 mode) {
    TextBank *bank;

    if (mode == 0) {
        bank = screenTextArray.textBanks[*(u8 *)(STATE_BLOCK + 0x72B8)];
        return (u32)bank->strings[idx];
    } else {
        bank = screenTextArray.textBanks[*(u8 *)(STATE_BLOCK + 0x72B8)];
        return (u32)bank->strings[idx];
    }
}

void fn_2_515DC(u8 arg0) {
    memset(STATE_BLOCK + 0x542C, 0, 0x1E90);
    *(u8 *)(STATE_BLOCK + 0x72B8) = arg0;
    fn_2_4906C();
}

static inline void copyCharacterStats(CharacterStats* dst, CharacterStats* src) {
    memcpy(dst, src, 0x1E);
    dst->stats.CharID = src->stats.CharID;
    dst->stats.FieldingArm = src->stats.FieldingArm;
    dst->stats.BattingStance = src->stats.BattingStance;
    memcpy(&dst->stats.SlapContactSize, &src->stats.SlapContactSize, 2);
    memcpy(&dst->stats.SlapHitPower, &src->stats.SlapHitPower, 2);
    dst->stats.BuntingContactSize = src->stats.BuntingContactSize;
    dst->stats.HitTrajectoryPushPull = src->stats.HitTrajectoryPushPull;
    dst->stats.HitTrajectoryHighLow = src->stats.HitTrajectoryHighLow;
    dst->stats.Speed = src->stats.Speed;
    dst->stats.ThrowingArm = src->stats.ThrowingArm;
    dst->stats.CharacterClass = src->stats.CharacterClass;
    dst->stats.Weight = src->stats.Weight;
    dst->stats.Captain = src->stats.Captain;
    dst->stats.CaptainStarHitPitch = src->stats.CaptainStarHitPitch;
    memcpy(&dst->stats.NonCaptainStarSwing, &src->stats.NonCaptainStarSwing, 2);
    dst->stats.FieldingStats = src->stats.FieldingStats;
    memcpy(&dst->stats.BattingStatBar, &src->stats.BattingStatBar, 4);
    memcpy(&dst->chemistry, &src->chemistry, sizeof(ChemistryTable));
    dst->BytesAfterChemistry[0] = src->BytesAfterChemistry[0];
    dst->UnusedShorts[0] = src->UnusedShorts[0];
    dst->UnusedShorts[1] = src->UnusedShorts[1];
    dst->UnusedShorts[2] = src->UnusedShorts[2];
    dst->UnusedShorts[3] = src->UnusedShorts[3];
    dst->UnusedShorts[4] = src->UnusedShorts[4];
    dst->UnusedShorts[5] = src->UnusedShorts[5];
    dst->UnusedShorts[6] = src->UnusedShorts[6];
    dst->UnusedShorts[7] = src->UnusedShorts[7];
    dst->UnusedShorts[8] = src->UnusedShorts[8];
    dst->UnusedShorts[9] = src->UnusedShorts[9];
    dst->UnusedShorts[10] = src->UnusedShorts[10];
    dst->UnusedShorts[11] = src->UnusedShorts[11];
    dst->UnusedShorts[12] = src->UnusedShorts[12];
    dst->UnusedShorts[13] = src->UnusedShorts[13];
    dst->UnusedShorts[14] = src->UnusedShorts[14];
    dst->UnusedShorts[15] = src->UnusedShorts[15];
    dst->UnusedShorts[16] = src->UnusedShorts[16];
    dst->UnusedShorts[17] = src->UnusedShorts[17];
    dst->UnusedShorts[18] = src->UnusedShorts[18];
    dst->UnusedShorts[19] = src->UnusedShorts[19];
    dst->UnusedShorts[20] = src->UnusedShorts[20];
}

void fn_2_5163C(void) {
    s32 i;
    s32 x;
    u8 val;

    *(u32 *)(Static_Stats_Tables + 0x46E0) = g_Challenge[0x441D];
    for (i = 0; i < 9; i++) {
        cursorPositions[i + 2] = *(s16 *)(g_Challenge + i * 6 + 0x40B8);
        x = (s8)cursorPositions[i + 2];
        copyCharacterStats((CharacterStats *)inMemRoster + i, (CharacterStats *)(Static_Stats_Tables + (x / 9) * 0x5A0) + x % 9);
        val = g_Challenge[i * 6 + 0x40BB];
        lineUpInfoStruct[i * 4 + 1] = i;
        lineUpInfoStruct[i * 4 + 0] = i;
        cursorPositions[i + 0x14] = val;
        lineUpInfoStruct[i * 4 + 2] = val;
    }
    teamLogoDetermination(0);
}

void fn_2_51890(void) {
    if ((s8)lbl_80354768[superstarUnlocked[0xF6] * 0x4508 + 0x1606] != 0) {
        if (lbl_80354768[Static_Stats_Tables[0x4754] * 0x4508 + 0x441B] != 0) {
            *(s32 *)(menuCursors + 0x54) = 1;
            B33(5) = 3;
            B33(7) = 0;
            B33(8) = 1;
            B33(9) = 1;
            B33(0xA) = 1;
            B33(0xB) = 1;
            B33(0xC) = 1;
        } else {
            *(s32 *)(menuCursors + 0x54) = 2;
            B33(5) = 2;
            B33(7) = 0;
            B33(8) = 0;
            B33(9) = 1;
            B33(0xA) = 1;
            B33(0xB) = 1;
            B33(0xC) = 1;
        }
    } else {
        if (lbl_80354768[Static_Stats_Tables[0x4754] * 0x4508 + 0x441B] != 0) {
            *(s32 *)(menuCursors + 0x54) = 1;
            B33(5) = 1;
            B33(7) = 0;
            B33(8) = 1;
            B33(9) = 0;
            B33(0xA) = 1;
            B33(0xB) = 1;
            B33(0xC) = 1;
        } else {
            *(s32 *)(menuCursors + 0x54) = 0;
            B33(5) = 0;
            B33(7) = 1;
            B33(8) = 0;
            B33(9) = 0;
            B33(0xA) = 0;
            B33(0xB) = 0;
            B33(0xC) = 1;
        }
    }
}

void fn_2_519F0(void) {
    insertGraphicDrawingFunction(fn_2_89F70, 0x3000);
}

void fn_2_51A1C(void) {
    switch (B33_U16(0x12)) {
    case 0:
        if (B33(0x14) == 0) {
            fn_8004A34C(lbl_2_bss_33FB4C, 0, 0x2E, 0, 0);
        } else {
            fn_8004A34C(lbl_2_bss_33FB4C, 0, 0x2F, 0, 0);
        }
        B33_U16(0x12) = 1;
        break;
    case 1:
        B33_U16(0x12) = 2;
        break;
    case 2:
        switch (exitMenu(*(u16 *)(Static_Stats_Tables + 0x472E))) {
        case 0:
            break;
        case 1:
            set803c5f77();
            break;
        case 3:
            if (++B33(0x14) == 2) {
                fn_2_460EC(Static_Stats_Tables[0x4754]);
                fn_8003BF54(0, 0, 0, 0, 1, 5, 3, Static_Stats_Tables[0x4754], 3);
                cardCheck[0x52] = 4;
                currentDrawingItem->state = 0;
                B33(0x14) = 0;
                B33_U16(0x12) = 3;
            } else {
                B33_U16(0x12) = 0;
            }
            break;
        case 2:
            set803c5f77();
            break;
        case 4:
            B33(0x22) = 0x52;
            B33(0xE) = 1;
            B33_S8(0xF) = -1;
            B33_U16(0x12) = 0;
            B33(0x14) = 0;
            lbl_2_bss_9E08 = 5;
            break;
        }
        break;
    case 3:
        if (currentDrawingItem->state != 0) {
            B33(0x17) = 0x50;
            B33(0x22) = 0x52;
            B33(0xE) = 1;
            B33_S8(0xF) = -1;
            B33_U16(0x12) = 0;
            B33(0x14) = 0;
            lbl_2_bss_9E08 = 5;
        }
        break;
    }
}

void fn_2_51C58(void) {
    u16 buf[3];
    s32 state = *(s32 *)(menuCursors + 0x54);
    s32 idx = *(s32 *)(menuCursors + 0x50);

    memset(buf, 0, 6);
    buf[0] = *(u16 *)(Static_Stats_Tables + 0x472C);
    buf[1] = *(u16 *)(Static_Stats_Tables + 0x472E);
    buf[2] = *(u16 *)(Static_Stats_Tables + 0x4730);
    if (B33(0x21) != 0) {
        buf[2] = 0;
        buf[1] = 0;
        buf[0] = 0;
    }

    if (buf[1] & PAD_BUTTON_A) {
        switch (state) {
        case 0:
            B33(0x17) = 0x4A;
            memset(lbl_80354768 + Static_Stats_Tables[0x4754] * 0x4508 + 0xAF8, 0, 0xB10);
            memcpy(g_Challenge, lbl_80354768 + Static_Stats_Tables[0x4754] * 0x4508, 0x4508);
            superstarUnlocked[0xF6] = idx;
            B33(6) = 0;
            B33_U16(2) = 2;
            break;
        case 1:
            fn_80041150(2, Static_Stats_Tables[0x4754]);
            B33(0x17) = 0x4A;
            B33(0x22) = 0x52;
            menuNumber[0x26] = 1;
            fn_2_5163C();
            superstarUnlocked[0xF6] = idx;
            B33(6) = 1;
            B33(0xE) = 1;
            lbl_2_bss_9E08 = 0xA;
            break;
        case 2:
            if (lbl_80354768[Static_Stats_Tables[0x4754] * 0x4508 + 0x441B] != 0) {
                fn_8004A34C(cardCheck, 0, 0x38, 0, 0);
            } else {
                fn_8004A34C(cardCheck, 0, 0x37, 0, 0);
            }
            superstarUnlocked[0xF6] = idx;
            B33(6) = 0;
            lbl_2_bss_9E08 = 0x10;
            break;
        case 3: {
            B33(0xF) = Static_Stats_Tables[0x4754];
            B33(0x15) = 3;
            memcpy(g_Challenge, lbl_80354768 + B33_S8(0xF) * 0x4508, 0x4508);
            cardCheck[0x52] = 5;
            if (++*(s32 *)(menuCursors + 0x50) == 3) {
                *(s32 *)(menuCursors + 0x50) = 0;
            }
            B33(0xD) = *(s32 *)(menuCursors + 0x50);
            B33(0x17) = 0x4D;
            B33_U16(2) = 3;
            break;
        }
        case 4:
            B33(0xF) = Static_Stats_Tables[0x4754];
            B33(0x15) = 4;
            B33_U16(2) = 4;
            break;
        case 5:
            B33_U16(2) = 3;
            break;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (buf[1] & PAD_BUTTON_B) {
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        B33_U16(2) = 3;
    } else if (buf[2] & PAD_BUTTON_UP) {
        *(s32 *)(lbl_2_bss_33FBCC + 0x1C) = state;
        do {
            if (--state < 0) {
                state = 5;
            }
        } while (B33(state + 7) == 0);
        B33(0x22) = 0x53;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (buf[2] & PAD_BUTTON_DOWN) {
        *(s32 *)(lbl_2_bss_33FBCC + 0x1C) = state;
        do {
            if (++state == 6) {
                state = 0;
            }
        } while (B33(state + 7) == 0);
        B33(0x22) = 0x53;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
    *(s32 *)(menuCursors + 0x54) = state;
}

void fn_2_520A4(void) {
    switch (B33_U16(2)) {
    case 0:
        fn_2_51890();
        insertGraphicDrawingFunction(fn_2_89F70, 0x3000);
        B33(0x22) = 0x51;
        B33_U16(2) = 1;
        break;
    case 1:
        if (B33(0x22) != 0x51) {
            fn_2_51C58();
        }
        break;
    case 2:
        B33(0x22) = 0x52;
        B33(0xE) = 1;
        B33_U16(2) = 0;
        lbl_2_bss_9E08 = 0xA;
        break;
    case 3:
        B33(0x22) = 0x52;
        lbl_2_bss_9E08 = 5;
        B33(0xE) = 1;
        B33_U16(2) = 0;
        break;
    case 4:
        fn_2_51A1C();
        break;
    }
}

void fn_2_52198(void) {
    s32 screen;

    if (*(u16 *)(menuControlVariables + 6) == 5 || *(u16 *)(menuControlVariables + 6) == 0x10) {
        insertGraphicDrawingFunction(fn_80053FE8, 0);
        insertGraphicDrawingFunction(fn_2_82DE8, 0x3000);
    }
    if (Static_Stats_Tables[0x4756] == 0) {
        screen = 0xB;
    } else {
        menuNumber[3] = Static_Stats_Tables[0x4711];
        screen = 0x10;
    }
    menuNumber[0] = screen;
    menuNumber[9] = menuNumber[8];
    menuNumber[8] = *(u16 *)(lbl_800FEF70 + screen * 16 + 8);
    insertGraphicDrawingFunction(fn_2_8ABFC, 0x3000);
}

void fn_2_52260(void) {
    u16 buf[3];
    s32 idx = *(s32 *)(menuCursors + 0x50);

    memset(buf, 0, 6);
    buf[0] = *(u16 *)(Static_Stats_Tables + 0x472C);
    buf[1] = *(u16 *)(Static_Stats_Tables + 0x472E);
    buf[2] = *(u16 *)(Static_Stats_Tables + 0x4730);

    if (buf[1] & PAD_BUTTON_UP) {
        if (--idx < 0) {
            idx = 2;
        }
        if (B33_S8(0xF) != -1 && idx == Static_Stats_Tables[0x4754]) {
            if (--idx < 0) {
                idx = 2;
            }
        }
        B33(0x17) = 0x4C;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (buf[1] & PAD_BUTTON_DOWN) {
        if (++idx == 3) {
            idx = 0;
        }
        if (B33_S8(0xF) != -1 && idx == Static_Stats_Tables[0x4754]) {
            if (++idx == 3) {
                idx = 0;
            }
        }
        B33(0x17) = 0x4C;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (buf[1] & PAD_BUTTON_A) {
        u8 mode = Static_Stats_Tables[0x4756];

        Static_Stats_Tables[0x4754] = idx;
        superstarUnlocked[0xF6] = idx;
        if (mode == 0 && B33_S8(0xF) == -1) {
            B33_U16(2) = 0;
            *(s32 *)(menuCursors + 0x54) = 0;
            lbl_2_bss_9E08 = 6;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (mode == 1 || B33_S8(0xF) != -1) {
            if (B33_S8(0xF) != -1) {
                if (lbl_80354768[idx + 0xCF5E] != 0) {
                    fn_8004A34C(lbl_2_bss_33FB4C, 0, 0x29, 0, 0);
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    lbl_2_bss_9E08 = 7;
                } else {
                    fn_8003BF54(0, 0, 0, 0, 1, 1, 2, (u8)idx, 2);
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    currentDrawingItem->state = 0;
                    lbl_2_bss_9E08 = 9;
                }
            } else {
                fn_8004A34C(lbl_2_bss_33FB4C, 0, 0x1B, 0, 0);
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                lbl_2_bss_9E08 = 7;
            }
        }
    } else if (buf[1] & PAD_BUTTON_B) {
        if (B33_S8(0xF) != -1) {
            B33(0x10) = B33(0xF);
            B33_S8(0xF) = -1;
            lbl_2_bss_9E08 = 6;
            B33(0x17) = 0x4E;
            cardCheck[0x52] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else {
            B33(0x17) = 0x4A;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            B33_S8(0xF) = -1;
            lbl_2_bss_9E08 = 0xE;
        }
    }
    *(s32 *)(menuCursors + 0x50) = idx;
}

void fn_2_52648(u32 priority) {
    insertGraphicDrawingFunction(fn_2_52690, priority);
    Static_Stats_Tables[0x472B] = g_d_GameSettings[6];
}

void fn_2_5268C(void) {
    return;
}

static inline void fn_2_52690_startSave(s32 slot, s32 mode) {
    fn_8003BF54(0, 0, 0, 0, 1, 1, 2, slot, mode);
    currentDrawingItem->state = 0;
    lbl_2_bss_9E08 = 9;
}

static inline void fn_2_52690_setScene(s32 mode) {
    g_MenuControl.sceneMode = mode;
    g_MenuControl.sceneState = 0;
}

static inline void fn_2_52690_finish(void) {
    B33_U16(0) = 0;
    *(s32 *)(menuCursors + 0x50) = 0;
    lbl_2_bss_9E08 = 0;
    cardCheck[0x52] = 0;
    removeCurrentDrawingItem();
}

void fn_2_52690(void) {
    s32 v;
    s32 c;

    switch (*(u16 *)&lbl_2_bss_9E08) {
    case 0:
        changeScene(1, 6);
        B33_S8(0xF) = -1;
        B33(0x1A) = 0;
        *(s32 *)(menuCursors + 0x54) = 0;
        *(s32 *)(menuCursors + 0x50) = 0;
        lbl_2_bss_9E08 = 1;
        break;
    case 1:
        fn_2_52198();
        g_MatchInfo[0x36] = 1;
        g_MatchInfo[0x37] = g_MatchInfo[0x38];
        g_MatchInfo[0x38] = 0;
        B33(0x17) = 0x49;
        if (Static_Stats_Tables[0x4756] == 1) {
            if (cardCheck[0x47] != 0) {
                lbl_2_bss_9E08 = 0xF;
                break;
            }
            lbl_2_bss_9E08 = 2;
        } else {
            lbl_2_bss_9E08 = 5;
        }
        *(s32 *)(menuCursors + 0x54) = superstarUnlocked[0xF6];
        break;
    case 2:
        v = g_MenuControl.sceneMode;
        if (v == 8 || v == 9) {
            if (v == 9) {
                cardCheck[0x52] = 3;
            } else {
                cardCheck[0x52] = 1;
            }
            fn_2_52690_startSave(superstarUnlocked[0xF6], 0);
        } else {
            fn_8004A34C(cardCheck, 0, 0x34, 0, 0);
            cardCheck[0x52] = 2;
            lbl_2_bss_9E08 = 3;
        }
        break;
    case 3:
        switch (cardCheck[0x45]) {
        case 2:
            v = g_MenuControl.sceneMode;
            if (v == 9) {
                g_MatchInfo[0x39] = 1;
            } else if (v == 10) {
                *(s16 *)(g_Challenge + 0x43BC) = 0;
            }
            fn_2_52690_startSave(superstarUnlocked[0xF6], 0);
            break;
        case 3:
        case 4:
            if (g_MenuControl.sceneMode == 10) {
                fn_8004A34C(cardCheck, 0, 0x35, 0, 0);
                lbl_2_bss_9E08 = 4;
            } else {
                B33(0x17) = 0x4A;
                B33_S8(0xF) = -1;
                lbl_2_bss_9E08 = 0xE;
            }
            break;
        }
        break;
    case 4:
        switch (cardCheck[0x45]) {
        case 2:
            B33(0x17) = 0x4A;
            B33_S8(0xF) = -1;
            lbl_2_bss_9E08 = 0xA;
            break;
        case 3:
        case 4:
            lbl_2_bss_9E08 = 2;
            break;
        }
        break;
    case 5:
        if (B33(0x17) != 0x49 && B33(0x21) == 0 && B33(0x19) == 0) {
            fn_2_52260();
        }
        break;
    case 6:
        fn_2_520A4();
        break;
    case 7:
        lbl_2_bss_9E08 = 8;
        break;
    case 8:
        switch (exitMenu(*(u16 *)(Static_Stats_Tables + 0x472E))) {
        case 0:
            break;
        case 1:
            set803c5f77();
            break;
        case 3:
            if (B33_S8(0xF) != -1) {
                fn_8003BF54(0, 0, 0, 0, 1, 1, 2, Static_Stats_Tables[0x4754], 2);
            } else {
                fn_8003BF54(0, 0, 0, 0, 1, 1, 2, Static_Stats_Tables[0x4754], 0);
            }
            currentDrawingItem->state = 0;
            lbl_2_bss_9E08 = 9;
            break;
        case 2:
            set803c5f77();
            break;
        case 4:
            B33(0x17) = 0x4E;
            B33(0x10) = B33(0xF);
            B33_S8(0xF) = -1;
            lbl_2_bss_9E08 = 5;
            break;
        }
        break;
    case 9: {
        s16 choice = currentDrawingItem->state;
        if (choice == 0) {
            break;
        }
        if (Static_Stats_Tables[0x4756] == 1) {
            switch (choice) {
            case 1:
                if (B33_S8(0xF) != -1) {
                    B33(0x17) = 0x4E;
                    B33(0x22) = 0x52;
                    B33(0x10) = B33(0xF);
                    B33_S8(0xF) = -1;
                    lbl_2_bss_9E08 = 5;
                } else {
                    B33(0x17) = 0x4B;
                    B33(0x22) = 0x52;
                    B33(0x16) = 100;
                    lbl_2_bss_9E08 = 0xF;
                }
                break;
            case 0xB:
                if (B33_S8(0xF) != -1) {
                    B33(0x22) = 0x52;
                    lbl_2_bss_9E08 = 5;
                } else {
                    v = g_MenuControl.sceneMode;
                    if (v == 9) {
                        fn_8004A34C(cardCheck, 0, 0x24, 0, 0);
                    } else if (v == 10) {
                        B33(0x17) = 0x4A;
                        lbl_2_bss_9E08 = 0xF;
                        break;
                    } else {
                        fn_8004A34C(cardCheck, 0, 0x1C, 0, 0);
                    }
                    lbl_2_bss_9E08 = 0x11;
                }
                break;
            default:
                if (cardCheck[0x52] == 2) {
                    lbl_2_bss_9E08 = 2;
                } else if (cardCheck[0x52] == 4) {
                    B33(0xE) = 1;
                    lbl_2_bss_9E08 = 5;
                } else if (cardCheck[0x52] == 1 || cardCheck[0x52] == 3) {
                    B33(0x17) = 0x4B;
                    B33(0x16) = 100;
                    lbl_2_bss_9E08 = 0xF;
                } else {
                    lbl_2_bss_9E08 = 5;
                }
                B33(0x22) = 0x52;
                break;
            }
        } else {
            switch (choice) {
            case 1:
                if (B33_S8(0xF) != -1) {
                    if (B33(0x15) == 4) {
                        B33(0x22) = 0x52;
                        B33(0xE) = 1;
                    } else {
                        B33(0x17) = 0x4F;
                        B33(0x22) = 0x52;
                    }
                    B33(0x10) = B33(0xF);
                    B33_S8(0xF) = -1;
                    lbl_2_bss_9E08 = 5;
                } else if (B33(6) == 1) {
                    B33(0x17) = 0x4A;
                    B33(0x22) = 0x52;
                    menuNumber[0x26] = 1;
                    B33(0xE) = 1;
                    lbl_2_bss_9E08 = 0xA;
                } else {
                    B33(0x17) = 0x4A;
                    B33(0x22) = 0x52;
                    B33(0xE) = 1;
                    lbl_2_bss_9E08 = 0xA;
                    B33_U16(2) = 0;
                }
                break;
            default:
                B33(0x22) = 0x52;
                if (B33_S8(0xF) != -1) {
                    B33(0x17) = 0x4E;
                    B33(0x10) = B33(0xF);
                    B33_S8(0xF) = -1;
                }
                B33(0xE) = 1;
                lbl_2_bss_9E08 = 5;
                break;
            }
        }
        break;
    }
    case 10:
        if (B33(0x19) != 1 && lbl_8037169C._12[1] != 0) {
            lbl_2_bss_9E08 = 0xB;
        }
        break;
    case 11:
        if (Static_Stats_Tables[0x4756] == 0) {
            fn_80035B50(8);
            switch ((s32)B33(6)) {
            case 0:
                fn_80042D38(0xC);
                break;
            case 1:
                fn_80062A74();
                fn_80035B50(0xF);
                fn_80035B50(0x12);
                fn_80035B50(9);
                fn_80035B50(6);
                fn_800AD054(*(u32 *)(Static_Stats_Tables + 0x46F0), *(u32 *)(Static_Stats_Tables + 0x46F4));
                maybeLoadsGameSoundFiles();
                fn_800ACFB0(audioFileDescriptors.files[0x98 / sizeof(void *)]);
                fn_80042D38(0x10);
                break;
            default:
                break;
            }
            B33(6) = 0;
            fn_2_52690_setScene(1);
        } else {
            fn_80035B50(6);
            fn_80035B50(8);
            if (g_MenuControl.sceneMode == 8) {
                fn_80042D38(0x10);
            } else {
                fn_80042D38(5);
            }
            menuNumber[0x26] = 1;
        }
        fn_2_52690_finish();
        break;
    case 14:
        if (B33(0x19) != 1 && lbl_8037169C._12[1] != 0) {
            lbl_2_bss_9E08 = 0xD;
        }
        break;
    case 13:
        menuNumber[0x26] = 1;
        Static_Stats_Tables[0x48AF] = 1;
        if (Static_Stats_Tables[0x4756] == 0) {
            fn_80035B50(8);
            fn_80042D38(5);
            fn_2_52690_setScene(1);
        } else {
            fn_80035B50(6);
            fn_80035B50(8);
            if (g_MenuControl.sceneMode != 10) {
                fn_2_52690_setScene(8);
                fn_80042D38(0x10);
            } else {
                fn_2_52690_setScene(9);
                fn_80042D38(5);
            }
        }
        fn_2_52690_finish();
        break;
    case 12:
        if (cardCheck[0x45] != 0) {
            switch (cardCheck[0x45]) {
            case 2:
            case 3:
                lbl_2_bss_9E08 = 5;
                break;
            }
        }
        break;
    case 15:
        if (B33(0x19) != 1) {
            if (B33_S8(0x16) > 0) {
                B33(0x16) = B33(0x16) - 1;
            } else {
                B33(0x16) = 0;
                B33(0x17) = 0x4A;
                lbl_2_bss_9E08 = 0xA;
            }
        }
        break;
    case 16:
        switch (cardCheck[0x45]) {
        case 1:
        case 2:
            fn_80041150(2, Static_Stats_Tables[0x4754]);
            B33(0x17) = 0x4A;
            B33(0x22) = 0x52;
            B33(0xE) = 1;
            lbl_2_bss_9E08 = 0xA;
            break;
        }
        break;
    case 17:
        switch (cardCheck[0x45]) {
        case 2:
            B33(0x17) = 0x4A;
            lbl_2_bss_9E08 = 0xF;
            break;
        case 3:
        case 4:
            fn_2_52690_startSave(superstarUnlocked[0xF6], 0);
            break;
        }
        break;
    }
}
