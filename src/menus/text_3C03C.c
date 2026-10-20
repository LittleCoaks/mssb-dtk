#include "menus/text_3C03C.h"
#include "Unknown/File_0x800b0a14.h"

/* Per-frame node whose phase byte lives at +0x28 and whose timer is an s16 at +0x14. */
typedef struct TextItem {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ void *prev;
    /* 0x08 */ void *next;
    /* 0x0C */ DrawingSceneStruct *parent;
    /* 0x10 */ s16 state;
    /* 0x12 */ u16 priority;
    /* 0x14 */ s16 timer;
    /* 0x16 */ s16 counter16;
    /* 0x18 */ u8 pad_18[0x28 - 0x18];
    /* 0x28 */ s8 phase;
} TextItem;

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A8234;
extern s16 lbl_2_data_3CE8[];
extern u8 lbl_800EFBA4[];
extern u8 AtBat_ButtonInput1[];
extern u8 g_d_GameSettings[];
extern u8 lbl_2_data_3CC8[];
extern u32 lbl_2_data_3C40[];
extern s16 lbl_2_data_1056C[];
extern u8 lbl_2_bss_1A8230[];

void fn_2_94604(s32 arg);
void fn_2_9461C(s16 arg);
void fn_2_94634(s32 arg);
void fn_2_94854(u8 value);
void fn_2_42490(void);
void fn_2_72054(s32 index, u8 state);
s32 fn_80062890(s32 arg);
void fn_2_44504(void);
void fn_2_1C41C(void);
void fn_2_1C490(void);
void fn_2_45354(void);
void fn_2_450E4(void);
int challenge_countRecruitedCharacters(void);
int challenge_isCharRecruited(int charID);
extern s16 lbl_2_data_373C[];
u8 fn_8006862C(u32 frames, u32 target);
u8 fn_80068514(u32 frames, u32 target);
void playStream(u8 streamId);
void sndFXStartEx(s32 fid, u8 vol, u8 pan, u8 studio);

#define WORK_ADDR(off) ((u8 *)lbl_2_bss_1A824C + 0x190000 + (off))

static u16 atBatButtonsOfCurrent(void) {
    s8 idx = (s8)*WORK_ADDR(0x7863);
    return *(u16 *)(AtBat_ButtonInput1 + idx * 0x20 + 2);
}

static void finishWorkFlagTail(TextItem *item) {
    if (*WORK_ADDR(0x783F) == 1) {
        ((TextItem *)currentDrawingItem)->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
    }
}

static void checkTableEntry(s16 value, s32 off) {
    if (value == lbl_2_bss_1A8248[0x40F0 + off] && lbl_2_bss_1A8248[0x40F1 + off] == 1) {
        *WORK_ADDR(0x7851) = value;
    }
}

void fn_2_3C03C(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        item->timer = 1;
        item->phase = 1;
        break;
    case 1:
        if (item->timer-- == 0) {
            fn_2_94854(0xB);
            fn_2_9461C(0);
            fn_2_94604(1);
            fn_2_94634(1);
            item->timer = 0x14;
            item->phase = 2;
        }
        break;
    case 2:
        if (item->timer-- == 0) {
            item->phase = 3;
        }
        break;
    case 3:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    finishWorkFlagTail(item);
}

void fn_2_3C168(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        item->timer = 1;
        item->phase = 1;
        break;
    case 1:
        if (item->timer-- == 0) {
            u8 *ctx = lbl_2_bss_1A8248;
            s16 *row = (s16 *)((u8 *)lbl_2_data_3CE8 + ctx[0x441C] * 12);
            u8 col = ctx[0x4422];
            s16 value = row[col + 1];
            s32 k;

            *WORK_ADDR(0x7851) = -1;
            if (row[col] != 5) {
                for (k = 0; k < 0x11; k++) {
                    checkTableEntry(value, k * 30);
                    checkTableEntry(value, k * 30 + 10);
                    checkTableEntry(value, k * 30 + 20);
                }
            }

            if ((s8)*WORK_ADDR(0x7851) == -1) {
                item->phase = 3;
            } else {
                fn_2_94854(0xB);
                fn_2_9461C((s8)*WORK_ADDR(0x7851) + 7);
                fn_2_94604(1);
                fn_2_94634(1);
                item->timer = 0x3C;
                item->phase = 2;
            }
        }
        break;
    case 2:
        if (item->timer-- == 0) {
            item->phase = 3;
        }
        break;
    case 3:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    finishWorkFlagTail(item);
}

void fn_2_3C3EC(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        item->timer = 1;
        item->phase = 1;
        break;
    case 1:
        if (item->timer-- == 0) {
            u8 *ctx = lbl_2_bss_1A8248;
            u8 *slot = ctx + ctx[0x4420];

            if (slot[0x4431] == 0) {
                slot[0x4431] = 1;
                item->timer = 0x3C;
                fn_2_72054(lbl_2_bss_1A8248[0x441E], 0xF);
                item->phase = 2;
            } else {
                item->phase = 3;
            }
        }
        break;
    case 2:
        if (item->timer-- == 0) {
            item->phase = 3;
        }
        break;
    case 3:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    finishWorkFlagTail(item);
}

void fn_2_3C53C(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    if (phase == 0) {
        *WORK_ADDR(0x78F0) = 0;
        fn_2_42490();
        if ((s8)*WORK_ADDR(0x78EF) > 0) {
            item->timer = 1;
            item->phase = 1;
        } else {
            item->phase = 7;
        }
    } else if (phase == 1) {
        if (item->timer-- == 0) {
            item->phase = 2;
        }
    } else if (phase == 2) {
        lbl_2_bss_1A8234[0x160000 + 0x2686] = 1;
        fn_80062890(0x38);
        item->timer = 0xA;
        item->phase = 3;
    } else if (phase == 3) {
        if (item->timer-- == 0) {
            item->phase = 4;
        }
    } else if (phase == 4) {
        s8 idx = *WORK_ADDR(0x7863);
        u16 buttons = *(u16 *)(AtBat_ButtonInput1 + idx * 0x20 + 2);

        if (buttons & 0x100) {
            lbl_2_bss_1A8234[0x160000 + 0x2870] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            item->timer = 0xA;
            item->phase = 5;
        } else if (buttons & 0x200) {
            lbl_2_bss_1A8234[0x160000 + 0x2870] = 1;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            item->timer = 0xA;
            item->phase = 5;
        }
    } else if (phase == 5) {
        if (item->timer-- == 0) {
            u8 *cnt = WORK_ADDR(0x78F0);
            u8 *lim = WORK_ADDR(0x78EF);
            *cnt += 1;
            if ((s8)*cnt == (s8)*lim) {
                item->phase = 7;
            } else {
                item->phase = 2;
            }
        }
    } else if (phase == 7) {
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
    }

    finishWorkFlagTail(item);
}

void fn_2_3DF28(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        item->timer = 0x14;
        item->phase = 1;
        break;
    case 1:
        if (item->timer-- == 0) {
            item->phase = 2;
        }
        break;
    case 2: {
        s8 idx = (s8)*WORK_ADDR(0x7863);
        u16 buttons = *(u16 *)(AtBat_ButtonInput1 + idx * 0x20 + 2);

        if (buttons & 0x300) {
            item->timer = 0x32;
            item->phase = 3;
        }
        break;
    }
    case 3:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    finishWorkFlagTail(item);
}

void fn_2_3DC60(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        lbl_2_bss_1A8234[0x160000 + 0x264B] = 1;
        item->timer = 0x10;
        fn_80062890(0x38);
        item->phase = 1;
        break;
    case 1:
        if (item->timer-- == 0) {
            item->phase = 2;
        }
        break;
    case 2:
        if (atBatButtonsOfCurrent() & 0x300) {
            lbl_2_bss_1A8234[0x160000 + 0x2835] = 1;
            item->timer = 0x10;
            item->phase = 3;
        }
        break;
    case 3:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    finishWorkFlagTail(item);
}

void fn_2_3DDC4(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        lbl_2_bss_1A8234[0x160000 + 0x264C] = 1;
        item->timer = 0x10;
        fn_80062890(0x38);
        item->phase = 1;
        break;
    case 1:
        if (item->timer-- == 0) {
            item->phase = 2;
        }
        break;
    case 2:
        if (atBatButtonsOfCurrent() & 0x300) {
            lbl_2_bss_1A8234[0x160000 + 0x2836] = 1;
            item->timer = 0x10;
            item->phase = 3;
        }
        break;
    case 3:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    finishWorkFlagTail(item);
}

void fn_2_3DAB8(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0: {
        u8 *ctx = lbl_2_bss_1A8248;
        u8 *flag = g_d_GameSettings + lbl_2_data_3CC8[ctx[0x441C]] + 0x1A;

        if (*flag == 0) {
            *flag = 1;
            lbl_2_bss_1A8234[0x160000 + 0x264D] = 1;
            item->timer = 0x10;
            fn_80062890(0x38);
            item->phase = 1;
        } else {
            item->phase = 3;
        }
        break;
    }
    case 1:
        if (item->timer-- == 0) {
            item->phase = 2;
        }
        break;
    case 2:
        if (atBatButtonsOfCurrent() & 0x300) {
            lbl_2_bss_1A8234[0x160000 + 0x2837] = 1;
            item->timer = 0x10;
            item->phase = 3;
        }
        break;
    case 3:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    finishWorkFlagTail(item);
}

void fn_2_3D878(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    if (phase == 0) {
        fn_2_44504();
        lbl_2_bss_1A8234[0x160000 + 0x2650] = 1;
        item->timer = 0x12C;
        item->phase = 1;
    } else if (phase == 1) {
        if (item->timer == 0x118) {
            fn_80062890(0x44);
        }
        if (item->timer-- == 0) {
            item->timer = 0x64;
            item->phase = 2;
        }
    } else if (phase == 2) {
        if (item->timer-- == 0) {
            u8 *ctx = lbl_2_bss_1A8248;
            s16 *row;

            lbl_2_bss_1A8234[0x160000 + 0x27AE] = 1;
            lbl_2_bss_1A8230[0x30000 + 0x2A0F] = 1;
            row = (s16 *)((u8 *)lbl_2_data_1056C + ctx[0x4415] * 12);
            item->timer = row[ctx[0x441C]];
            item->phase = 3;
        }
    } else if (phase == 3) {
        if (item->timer == 0x32) {
            fn_80062890(lbl_2_data_3C40[lbl_2_bss_1A8248[0x441C]]);
            playStream(0xC);
        }
        if (item->timer-- == 0) {
            item->timer = 0xB4;
            item->phase = 4;
        }
    } else if (phase == 4) {
        if (item->timer-- == 0) {
            item->timer = 0x32;
            item->phase = 5;
        }
    } else if (phase == 5) {
        if (item->timer-- == 0) {
            item->phase = 6;
        }
    } else if (phase == 6) {
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
    }

    finishWorkFlagTail(item);
}

void fn_2_3E058(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        fn_2_1C490();
        item->timer = 0x1E;
        if (lbl_2_bss_1A8248[0x4422] >= 5 && lbl_2_bss_1A8248[0x4447] == 0 &&
            lbl_2_bss_1A8248[0x441C] == 5) {
            lbl_2_bss_1A8248[0x4447] = 1;
            item->phase = 1;
        } else {
            item->phase = 0xE;
        }
        break;
    case 1:
        if (!fn_8006862C(0x78, 0)) {
            lbl_2_bss_1A8248[0x44F2] = 4;
            fn_2_94854(0xB);
            fn_2_9461C(0xC);
            fn_2_94604(1);
            fn_2_94634(1);
            item->timer = 0x3C;
            item->phase = 2;
        }
        break;
    case 2:
        if (item->timer-- == 0) {
            item->phase = 3;
        }
        break;
    case 3:
        lbl_2_bss_1A8234[0x160000 + 0x2679] = 1;
        item->timer = 0xC8;
        item->phase = 4;
        break;
    case 4:
        if (item->timer-- == 0) {
            item->phase = 5;
        }
        break;
    case 5:
        item->timer = 0xBC;
        item->phase = 6;
        break;
    case 6:
        if (item->timer-- == 0) {
            item->phase = 7;
        }
        break;
    case 7:
        if (!fn_80068514(0x78, 0x7F)) {
            item->phase = 0xC;
        }
        break;
    case 12:
        fn_2_94854(0xB);
        fn_2_9461C(0);
        fn_2_94604(1);
        fn_2_94634(1);
        item->timer = 0x3C;
        item->phase = 0xD;
        break;
    case 13:
        if (item->timer-- == 0) {
            lbl_2_bss_1A8248[0x44F2] = 0;
            item->phase = 0xE;
        }
        break;
    case 14:
        fn_2_1C41C();
        ((TextItem *)currentDrawingItem)->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    item->counter16 += 1;
    if (item->counter16 == 0xA6) {
        *(s32 *)WORK_ADDR(0x76A8) = fn_80062890(0x3A);
    } else if (item->counter16 == 0xF6) {
        *(s32 *)WORK_ADDR(0x76A8) = fn_80062890(0x3B);
    } else if (item->counter16 == 0x13C) {
        *(s32 *)WORK_ADDR(0x76A8) = fn_80062890(0x3C);
    }

    finishWorkFlagTail(item);
}

void fn_2_3D5C4(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        fn_2_45354();
        *WORK_ADDR(0x7867) = 0;
        item->timer = 1;
        if (*(s8 *)WORK_ADDR(0x7866) != 0) {
            item->phase = 1;
        } else {
            item->phase = 6;
        }
        break;
    case 1:
        if (item->timer-- == 0) {
            item->phase = 2;
        }
        break;
    case 2:
        if (lbl_2_bss_1A8248[0x44F4] != 0) {
            lbl_2_bss_1A8234[0x160000 + 0x264E] = 1;
        } else {
            lbl_2_bss_1A8234[0x160000 + 0x2674] = 1;
        }
        item->timer = 0xC;
        fn_80062890(0x38);
        item->phase = 3;
        break;
    case 3:
        if (item->timer-- == 0) {
            item->phase = 4;
        }
        break;
    case 4: {
        s8 idx = (s8)*WORK_ADDR(0x7863);
        u16 buttons = *(u16 *)(AtBat_ButtonInput1 + idx * 0x20 + 2);

        if (buttons & 0x300) {
            if (lbl_2_bss_1A8248[0x44F4] != 0) {
                lbl_2_bss_1A8234[0x160000 + 0x2838] = 1;
            } else {
                lbl_2_bss_1A8234[0x160000 + 0x285E] = 1;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            item->timer = 0xC;
            item->phase = 5;
        }
        break;
    }
    case 5: {
        s8 a;
        s8 b;

        *WORK_ADDR(0x7867) += 1;
        a = *(s8 *)WORK_ADDR(0x7866);
        b = *(s8 *)WORK_ADDR(0x7867);
        if (a > b) {
            item->phase = 2;
        } else {
            item->phase = 6;
        }
        break;
    }
    case 6:
        fn_2_450E4();
        ((TextItem *)currentDrawingItem)->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    finishWorkFlagTail(item);
}

static int challengeFlagsAllSet(void) {
    s32 k;

    for (k = 0; k < 19; k++) {
        if (lbl_2_bss_1A8248[0x43C2 + k] == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

static s32 challengeCharForIndex(s32 i) {
    if (i == 6) return 0;
    if (i == 7) return 1;
    if (i == 8) return 4;
    if (i == 9) return 5;
    if (i == 10) return 10;
    if (i == 11) return 11;
    if (i == 12) return 6;
    if (i == 13) return 17;
    if (i == 14) return 2;
    if (i == 15) return 3;
    if (i == 16) return 9;
    return 19;
}

void fn_2_3C7DC(void) {
    s32 i;

    for (i = 0; i < 0x14; i++) {
        *WORK_ADDR(0x789F + i) = 0;
    }

    challenge_countRecruitedCharacters();

    for (i = 0; i < 0x14; i++) {
        if (lbl_2_data_373C[i] == 1) {
            if (i == 5 && lbl_2_bss_1A8248[0x442C] == 0) {
                *WORK_ADDR(0x789F + i) = 2;
            } else if (i == 0x13 && !challengeFlagsAllSet()) {
                *WORK_ADDR(0x789F + i) = 2;
            }
        } else if (lbl_2_data_373C[i] == 0) {
            if (lbl_2_bss_1A8248[0x43C2 + i] == 1) {
                *WORK_ADDR(0x789F + i) = 1;
            } else if (lbl_2_bss_1A8248[0x43C2 + i] == 0) {
                if (i == 18) {
                    if (lbl_2_bss_1A8248[0x4428] != 0x1F) {
                        *WORK_ADDR(0x789F + i) = 2;
                    }
                } else if (i >= 6 && i < 18) {
                    if (!challenge_isCharRecruited(challengeCharForIndex(i))) {
                        *WORK_ADDR(0x789F + i) = 2;
                    }
                }
            }
        }
    }
}
