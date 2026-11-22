#include "menus/text_3C03C.h"
#include "Unknown/File_0x800b0a14.h"
#include "menus/menu_work.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"

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
extern u8 *lbl_2_bss_1A8230;
extern s16 lbl_2_data_3CE8[][6];
extern s16 lbl_2_data_373C[];
extern u8 lbl_2_data_3764[];
extern s16 lbl_2_data_1056C[][6];
extern u32 lbl_2_data_3C40[];
extern u8 lbl_2_data_3CC8[];
extern u8 lbl_800EFBA4[];

typedef struct PadInput {
    /* 0x00 */ E(u16, INPUT_BUTTON) hold;
    /* 0x02 */ E(u16, INPUT_BUTTON) trg;
    /* 0x04 */ E(u16, INPUT_BUTTON) rep;
    /* 0x06 */ u8 _06[0x20 - 0x06];
} PadInput;

extern PadInput AtBat_ButtonInput1[4];
extern u8 g_d_GameSettings[];

void menuCamera_setEyeFollowsSlot(s32 arg);
void menuCamera_setFollowSlot(s32 arg);
void menuCamera_setSpringPreset(s32 arg);
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
u8 fn_8006862C(u32 frames, u32 target);
u8 fn_80068514(u32 frames, u32 target);
void playStream(u8 streamId);
void fn_2_42638(void);
void fn_2_45E48(void);
void fn_2_432EC(void);
void fn_2_43E8C(void);
void fn_2_44014(void);
void fn_2_50CC0(s32 arg);
void fn_2_50B0C(s16 arg0, s16 arg1);
void fn_2_46D34(s32 delta);
void fn_2_46D94(s16 *a, s16 *b, s16 c, s32 d, s32 e);
void fn_2_3F66C(void);
void fn_2_38538(void);
void sndFXStartEx(s32 fid, u8 vol, u8 pan, u8 studio);

#define WB(off) (lbl_2_bss_1A824C[(off)])
#define WORK ((u8 *)lbl_2_bss_1A824C + 0x190000)
#define WORK_S8(off) (*(s8 *)(WORK + (off)))
#define WORK_S16(off) (*(s16 *)(WORK + (off)))
#define FLAGS ((u8 *)lbl_2_bss_1A8234 + 0x160000)

static inline u16 atBatButtonsOfCurrent(void) {
    return AtBat_ButtonInput1[(s8)WORK[MENU_WORK_ACTIVE_PORT]].trg;
}

static inline void finishWorkFlagTail(TextItem *item) {
    if (WORK[0x783F] == 1) {
        ((TextItem *)currentDrawingItem)->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
    }
}

static inline void checkTableEntry(s16 value, s32 off) {
    if (value == (lbl_2_bss_1A8248 + off)[0x40F0] && (lbl_2_bss_1A8248 + off)[0x40F1] == 1) {
        WORK[0x7851] = value;
    }
}

#define CHALLENGE_FLAG(k) (((s8 *)lbl_2_bss_1A8248)[0x43C2 + (k)])

#define CHALLENGE_FLAGS_ALL_SET() \
    (CHALLENGE_FLAG(0) && CHALLENGE_FLAG(1) && CHALLENGE_FLAG(2) && CHALLENGE_FLAG(3) && \
           CHALLENGE_FLAG(4) && CHALLENGE_FLAG(5) && CHALLENGE_FLAG(6) && CHALLENGE_FLAG(7) && \
           CHALLENGE_FLAG(8) && CHALLENGE_FLAG(9) && CHALLENGE_FLAG(10) && CHALLENGE_FLAG(11) && \
           CHALLENGE_FLAG(12) && CHALLENGE_FLAG(13) && CHALLENGE_FLAG(14) && CHALLENGE_FLAG(15) && \
           CHALLENGE_FLAG(16) && CHALLENGE_FLAG(17) && CHALLENGE_FLAG(18))

static inline void setIfNotRecruited(s32 index, s32 charID) {
    if (challenge_isCharRecruited(charID) == 0) {
        WB(0x19789F + index) = 2;
    }
}

static inline void showSlotMessage(void) {
    u8 *w = WORK;
    s16 slot = *(s16 *)(w + 0x7726);

    if ((s32)(w + slot)[0x789F] == 2) {
        fn_2_50B0C(0x26C, 0);
    } else {
        fn_2_50B0C(slot + 0x26D, 0);
    }
}

static inline u16 repeatButtonsOfCurrent(void) {
    return AtBat_ButtonInput1[(s8)WORK[MENU_WORK_ACTIVE_PORT]].rep;
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
            menuCamera_setFollowSlot(0xC);
            menuCamera_setEyeFollowsSlot(1);
            menuCamera_setSpringPreset(1);
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
        FLAGS[0x2679] = 1;
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
    case 8:
    case 9:
    case 10:
    case 11:
        break;
    case 12:
        fn_2_94854(0xB);
        menuCamera_setFollowSlot(0);
        menuCamera_setEyeFollowsSlot(1);
        menuCamera_setSpringPreset(1);
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
        *(s32 *)(WORK + 0x76A8) = fn_80062890(0x3A);
    } else if (item->counter16 == 0xF6) {
        *(s32 *)(WORK + 0x76A8) = fn_80062890(0x3B);
    } else if (item->counter16 == 0x146) {
        /* Empty in the original game; these frames were left without a cue. */
    } else if (item->counter16 == 0x10A) {
    } else if (item->counter16 == 0x16E) {
    } else if (item->counter16 == 0x13C) {
        *(s32 *)(WORK + 0x76A8) = fn_80062890(0x3C);
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
    case 2:
        if (atBatButtonsOfCurrent() & (INPUT_BUTTON_A | INPUT_BUTTON_B)) {
            item->timer = 0x32;
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
        FLAGS[0x264C] = 1;
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
        if (atBatButtonsOfCurrent() & (INPUT_BUTTON_A | INPUT_BUTTON_B)) {
            FLAGS[0x2836] = 1;
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

void fn_2_3DC60(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        FLAGS[0x264B] = 1;
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
        if (atBatButtonsOfCurrent() & (INPUT_BUTTON_A | INPUT_BUTTON_B)) {
            FLAGS[0x2835] = 1;
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
    u8 *settings = g_d_GameSettings;
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0: {
        u8 *flag = settings + lbl_2_data_3CC8[lbl_2_bss_1A8248[0x441C]];

        flag += 0x1A;

        if (*flag == 0) {
            *flag = 1;
            FLAGS[0x264D] = 1;
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
        if (atBatButtonsOfCurrent() & (INPUT_BUTTON_A | INPUT_BUTTON_B)) {
            FLAGS[0x2837] = 1;
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

    switch (phase) {
    case 0:
        fn_2_44504();
        FLAGS[0x2650] = 1;
        item->timer = 0x12C;
        item->phase = 1;
        break;
    case 1:
        if (item->timer == 0x118) {
            fn_80062890(0x44);
        }
        if (item->timer-- == 0) {
            item->timer = 0x64;
            item->phase = 2;
        }
        break;
    case 2:
        if (item->timer-- == 0) {
            FLAGS[0x27AE] = 1;
            lbl_2_bss_1A8230[0x32A0F] = 1;
            item->timer = lbl_2_data_1056C[lbl_2_bss_1A8248[0x4415]][lbl_2_bss_1A8248[0x441C]];
            item->phase = 3;
        }
        break;
    case 3:
        if (item->timer == 0x32) {
            fn_80062890(lbl_2_data_3C40[lbl_2_bss_1A8248[0x441C]]);
        }
        if (item->timer == 0x32) {
            playStream(0xC);
        }
        if (item->timer-- == 0) {
            item->timer = 0xB4;
            item->phase = 4;
        }
        break;
    case 4:
        if (item->timer-- == 0) {
            item->timer = 0x32;
            item->phase = 5;
        }
        break;
    case 5:
        if (item->timer-- == 0) {
            item->phase = 6;
        }
        break;
    case 6:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    finishWorkFlagTail(item);
}

void fn_2_3D5C4(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        fn_2_45354();
        WORK[0x7867] = 0;
        item->timer = 1;
        if (WORK_S8(0x7866) == 0) {
            item->phase = 6;
        } else {
            item->phase = 1;
        }
        break;
    case 1:
        if (item->timer-- == 0) {
            item->phase = 2;
        }
        break;
    case 2:
        if (((s8 *)lbl_2_bss_1A8248)[0x44F4] != 0) {
            FLAGS[0x264E] = 1;
        } else {
            FLAGS[0x2674] = 1;
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
    case 4:
        if (atBatButtonsOfCurrent() & (INPUT_BUTTON_A | INPUT_BUTTON_B)) {
            if (((s8 *)lbl_2_bss_1A8248)[0x44F4] != 0) {
                FLAGS[0x2838] = 1;
            } else {
                FLAGS[0x285E] = 1;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            item->timer = 0xC;
            item->phase = 5;
        }
        break;
    case 5:
        WORK[0x7867]++;
        if (WORK_S8(0x7866) <= WORK_S8(0x7867)) {
            item->phase = 6;
        } else {
            item->phase = 2;
        }
        break;
    case 6:
        fn_2_450E4();
        ((TextItem *)currentDrawingItem)->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }

    finishWorkFlagTail(item);
}

void fn_2_3CD34(void) {
    TextItem *item = (TextItem *)currentDrawingItem;

    switch (item->phase) {
    case 0:
        fn_2_42638();
        fn_2_45E48();
        fn_2_3C7DC();
        WORK_S16(0x7726) = 0;
        WORK_S16(0x772A) = 0;
        WORK_S16(0x7728) = 0;
        WORK_S16(0x772C) = 0x14;
        item->timer = 0x12;
        FLAGS[0x2675] = 1;
        item->phase = 1;
        break;
    case 1:
        if (item->timer-- == 0) {
            showSlotMessage();
            item->phase = 2;
        }
        break;
    case 2:
        if (repeatButtonsOfCurrent() == INPUT_BUTTON_UP || repeatButtonsOfCurrent() == INPUT_BUTTON_DOWN) {
            FLAGS[0x27D3] = 1;
            fn_2_46D94(&WORK_S16(0x7728), &WORK_S16(0x772A), WORK_S16(0x772C), 6, 9);
            WORK_S16(0x7726) = WORK_S16(0x7728) + WORK_S16(0x772A);
            showSlotMessage();
            item->phase = 3;
        } else {
            u16 buttons;

            WORK_S16(0x7726) = WORK_S16(0x7728) + WORK_S16(0x772A);
            buttons = atBatButtonsOfCurrent();
            if (buttons & INPUT_BUTTON_A) {
                u8 *w = WORK;
                s16 slot = *(s16 *)(w + 0x7726);
                s8 v = (w + slot)[0x789F];

                if (v == 2) {
                    fn_2_50B0C(0x267, 0);
                    sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                } else if (v == 1) {
                    fn_2_50B0C(0x269, 0);
                    sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                } else if (v == 0 &&
                           *(s16 *)(lbl_2_data_3764 + slot * 8 + lbl_2_bss_1A8248[0x4415] * 2) >
                               *(s16 *)(lbl_2_bss_1A8248 + 0x43BC)) {
                    fn_2_50B0C(0x268, 0);
                    sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                } else if ((s8)lbl_2_bss_1A8248[0x444B] == slot && lbl_2_data_373C[slot] == 1) {
                    fn_2_50B0C(0x269, 0);
                    sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                } else {
                    item->phase = 7;
                }
            } else if (buttons & INPUT_BUTTON_B) {
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                FLAGS[0x285F] = 1;
                item->phase = 9;
            }
        }
        break;
    case 7:
        if ((s8)lbl_2_bss_1A8248[0x444B] == -1 || lbl_2_data_373C[WORK_S16(0x7726)] == 0) {
            fn_2_50CC0(0x264);
        } else {
            fn_2_50CC0(0x265);
        }
        item->state = 0;
        item->phase = 8;
        break;
    case 8:
        if (item->state == 1 && WORK_S16(0x72B0) == 0) {
            FLAGS[0x2701] = 1;
            fn_2_50B0C(0x26A, 0);
            if (lbl_2_data_373C[WORK_S16(0x7726)] == 1) {
                FLAGS[0x2704] = 1;
                lbl_2_bss_1A8248[0x444A] = 1;
                lbl_2_bss_1A8248[0x444B] = WORK_S16(0x7726);
            }
            (lbl_2_bss_1A8248 + WORK_S16(0x7726))[0x43C2] = 1;
            fn_2_3C7DC();
            if (WORK_S16(0x7726) == 0x12) {
                WORK[0x789E] = 1;
            }
            WORK[0x78F4] = 1;
            WORK[0x78F5] = WORK_S16(0x7726);
            *(s32 *)(WORK + 0x76A8) = fn_80062890(0xC);
            item->timer = 0x10;
            item->phase = 4;
        } else if (item->state == 1 && WORK_S16(0x72B0) == 1) {
            showSlotMessage();
            item->phase = 2;
        }
        break;
    case 3:
        item->phase = 2;
        break;
    case 4:
        if (item->timer-- == 0) {
            item->phase = 5;
        }
        break;
    case 5:
        fn_2_46D34(-*(s16 *)(lbl_2_data_3764 + WORK_S16(0x7726) * 8 + lbl_2_bss_1A8248[0x4415] * 2));
        if (*(s16 *)(lbl_2_bss_1A8248 + 0x43BE) > 0) {
            TextItem *node = (TextItem *)insertGraphicDrawingFunction(fn_2_3F66C, 2);

            node->phase = 0;
            item->state = 0;
        } else {
            item->state = 1;
        }
        item->phase = 6;
        break;
    case 6:
        if (item->state == 1) {
            if (lbl_2_data_373C[WORK_S16(0x7726)] == 1) {
                lbl_2_bss_1A8248[0x444C] = lbl_2_bss_1A8248[0x444B];
            }
            item->phase = 2;
        }
        break;
    case 9:
        fn_2_44014();
        fn_2_43E8C();
        fn_2_432EC();
        fn_2_50CC0(0x26B);
        item->state = 0;
        item->phase = 0xA;
        break;
    case 10:
        if (item->state == 1) {
            TextItem *node;

            FLAGS[0x2836] = 1;
            FLAGS[0x2837] = 1;
            FLAGS[0x2838] = 1;
            WORK_S16(0x72AC) = 0;
            WORK[0x72B9] = 0;
            FLAGS[0x2842] = 1;
            FLAGS[0x2871] = 1;
            FLAGS[0x2872] = 1;
            node = (TextItem *)insertGraphicDrawingFunction(fn_2_38538, 2);
            node->phase = 0;
            item->state = 0;
            item->phase = 0xB;
        }
        break;
    case 11:
        if (item->state == 1) {
            TextItem *node = (TextItem *)insertGraphicDrawingFunction(fn_2_3C53C, 2);

            node->phase = 0;
            item->state = 0;
            item->phase = 0xC;
        }
        break;
    case 12:
        if (item->state == 1) {
            item->parent->state = 1;
            removeCurrentDrawingItem();
            item->phase = 0;
        }
        break;
    }

    finishWorkFlagTail(item);
}

void fn_2_3C7DC(void) {
    s32 i;

    for (i = 0; i < 0x14; i++) {
        WB(0x19789F + i) = 0;
    }

    challenge_countRecruitedCharacters();

    for (i = 0; i < 0x14; i++) {
        if (lbl_2_data_373C[i] == 1) {
            if (i == 5 && lbl_2_bss_1A8248[0x442C] == 0) {
                WB(0x19789F + i) = 2;
            } else if (i == 0x13 && !CHALLENGE_FLAGS_ALL_SET()) {
                WB(0x19789F + i) = 2;
            }
        } else if (lbl_2_data_373C[i] == 0 && (s8)lbl_2_bss_1A8248[0x43C2 + i] == 1) {
            WB(0x19789F + i) = 1;
        } else if (lbl_2_data_373C[i] == 0 && (s8)lbl_2_bss_1A8248[0x43C2 + i] == 0) {
            switch (i) {
            case 6:
                setIfNotRecruited(i, CHAR_ID_MARIO);
                break;
            case 8:
                setIfNotRecruited(i, CHAR_ID_PEACH);
                break;
            case 10:
                setIfNotRecruited(i, CHAR_ID_WARIO);
                break;
            case 12:
                setIfNotRecruited(i, CHAR_ID_YOSHI);
                break;
            case 14:
                setIfNotRecruited(i, CHAR_ID_DK);
                break;
            case 16:
                setIfNotRecruited(i, CHAR_ID_BOWSER);
                break;
            case 7:
                setIfNotRecruited(i, CHAR_ID_LUIGI);
                break;
            case 9:
                setIfNotRecruited(i, CHAR_ID_DAISY);
                break;
            case 11:
                setIfNotRecruited(i, CHAR_ID_WALUIGI);
                break;
            case 13:
                setIfNotRecruited(i, CHAR_ID_BIRDO);
                break;
            case 15:
                setIfNotRecruited(i, CHAR_ID_DIDDY);
                break;
            case 17:
                setIfNotRecruited(i, CHAR_ID_BOWSERJR);
                break;
            case 18:
                if (lbl_2_bss_1A8248[0x4428] != 0x1F) {
                    WB(0x19789F + i) = 2;
                }
                break;
            }
        }
    }
}

void fn_2_3C53C(void) {
    TextItem *item = (TextItem *)currentDrawingItem;
    s8 phase = item->phase;

    switch (phase) {
    case 0:
        WORK[0x78F0] = 0;
        fn_2_42490();
        if (WORK_S8(0x78EF) > 0) {
            item->timer = 1;
            item->phase = 1;
        } else {
            item->phase = 7;
        }
        break;
    case 1:
        if (item->timer-- == 0) {
            item->phase = 2;
        }
        break;
    case 2:
        FLAGS[0x2686] = 1;
        fn_80062890(0x38);
        item->timer = 0xA;
        item->phase = 3;
        break;
    case 3:
        if (item->timer-- == 0) {
            item->phase = 4;
        }
        break;
    case 4: {
        u16 buttons = atBatButtonsOfCurrent();

        if (buttons & INPUT_BUTTON_A) {
            FLAGS[0x2870] = 1;
            item->timer = 0xA;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            item->phase = 5;
        } else if (buttons & INPUT_BUTTON_B) {
            FLAGS[0x2870] = 1;
            item->timer = 0xA;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            item->phase = 5;
        }
        break;
    }
    case 5:
        if (item->timer-- == 0) {
            WORK[0x78F0]++;
            if (WORK_S8(0x78F0) == WORK_S8(0x78EF)) {
                item->phase = 7;
            } else {
                item->phase = 2;
            }
        }
        break;
    case 6:
        break;
    case 7:
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
            s16 value = lbl_2_data_3CE8[lbl_2_bss_1A8248[0x441C]][lbl_2_bss_1A8248[0x4422] + 1];
            s32 k;

            WORK_S8(0x7851) = -1;
            if (lbl_2_data_3CE8[lbl_2_bss_1A8248[0x441C]][lbl_2_bss_1A8248[0x4422]] != 5) {
                for (k = 0; k < 0x33; k++) {
                    checkTableEntry(value, k * 10);
                }
            }

            if ((s8)WORK[0x7851] != -1) {
                fn_2_94854(0xB);
                menuCamera_setFollowSlot((s8)WORK[0x7851] + 7);
                menuCamera_setEyeFollowsSlot(1);
                menuCamera_setSpringPreset(1);
                item->timer = 0x3C;
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
            menuCamera_setFollowSlot(0);
            menuCamera_setEyeFollowsSlot(1);
            menuCamera_setSpringPreset(1);
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
