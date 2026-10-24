#include "menus/text_1B1BC.h"
#include "text/text.h"
#include "Dolphin/GX/GXFrameBuffer.h"
#include "Dolphin/pad.h"
#include "game/challenge/challenge_state.h"
#include "game/challenge/star_mission_data.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x800b0a14.h"
#include "menus/text_4D960.h"
#include "menus/text_4078C.h"
#include "menus/text_53408.h"
#include "menus/rep_0B08.h"
#include "menus/rep_0F60.h"

extern u8 lbl_2_bss_1034C[];
extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A823C;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_bss_1A8250[];
extern u8 *lbl_2_data_4BA0;
extern u8 lbl_803C6CF8[];
extern u8 teamStarModelFileDescriptorMenus[];
extern u8 Static_Stats_Tables[];
extern u8 g_d_GameSettings[];
extern u8 AtBat_ButtonInput1[];
extern u8 inningSetting[];
extern u8 superstarUnlocked[];
extern u8 hugeAnimStruct[];
extern u8 *lbl_2_bss_1A8230;
extern u8 *lbl_2_bss_1A8238;
extern u8 *lbl_2_bss_1A8244;
extern u8 *lbl_2_bss_340140;
extern u8 lbl_2_data_4BA8[];
extern u8 challengeCaptainCharIDs[];

void *memset(void *dst, s32 c, u32 n);
void *ARAMTransfer(void *file, s32 arg1, s32 arg2, s32 arg3);
void convertTextureHeader(void *tex);
void fn_8004B1B8(void *p);
void fn_80068720(u8 index);
void fn_800ACFB0(void *block);
void resetGameStadiumStateOnExit(void);
BOOL maybeLoadsGameSoundFiles(void);
void fn_2_47CFC(void);
void fn_2_46D94(s16 *a, s16 *b, s16 c, s32 d, s32 e);
int fn_8006CDC0(int charID);
void fn_8006C488(void);
void fn_2_4AB1C(void);
s32 fn_2_46D00(void);
void fn_2_20328(void);
void fn_2_46418(void);
void fn_2_468DC(void);
void fn_2_466AC(void);
void fn_2_467FC(void);
void fn_2_454E8(void);
void fn_2_207FC(void);
void fn_2_2460C(void);
s32 fn_2_20CB0(s32 x);
void fn_2_37460(void);
void fn_2_37D98(void);
void fn_2_40A9C(void);
void fn_2_379D0(void);
void fn_800627F8(void);
void fn_2_20D08(void);
void fn_800216F8(s32 id, void (*func)(void));
void playStream(s32 id);
void changeScene(s32 a, s32 b);
s32 fn_2_44E2C(s32 v);
void fn_2_8AEE0(void);
void fn_2_8ACB0(s32 idx, s32 val);

#define DRAW_STATE(node) (*(s8 *)&(node)->unk_28)
#define SCENE_STATE (*(s16 *)&lbl_2_bss_1A823C[0x32])
#define AT_BAT_BUTTON(off, idx) (*(u16 *)(AtBat_ButtonInput1 + (off) + ((idx) << 5)))

typedef struct ChallengeMapRecord {
    u8 kind;
    u8 state;
    u8 unknown2;
    s8 variant;
    u8 unknown4[6];
} ChallengeMapRecord;

static inline ChallengeMapRecord *challengeMapRecord(s32 index) {
    return &((ChallengeMapRecord *)(lbl_2_bss_1A8248 + 0x40F0))[index];
}

// .text:0x0001CF94 size:0x4AC mapped:0x8065C028
void fn_2_1CF94(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    u8 *p;
    ChallengeState *q;
    ChallengeTrackingStruct *e;
    ScoutFlagTable *tbl;
    u16 btn;
    s32 idx;
    s32 k;
    s32 j;
    s32 cnt;
    s32 v;

    switch (DRAW_STATE(node)) {
    case 0:
        *(s16 *)&lbl_2_bss_1A824C[0x19771A] = 0;
        *(s16 *)&lbl_2_bss_1A824C[0x19771C] = 0;
        *(s16 *)&lbl_2_bss_1A824C[0x19771E] = NUM_CHOOSABLE_CHARACTERS;
        DRAW_STATE(node) = 1;
        break;
    case 1:
        p = lbl_2_bss_1A824C;
        idx = (s8)p[0x197863];
        btn = AT_BAT_BUTTON(4, idx);
        if (btn == PAD_BUTTON_UP || btn == PAD_BUTTON_DOWN) {
            fn_2_46D94((s16 *)&p[0x19771A], (s16 *)&p[0x19771C], *(s16 *)&p[0x19771E], 10, 9);
        }
        p = lbl_2_bss_1A824C;
        *(s16 *)&p[0x197716] = *(s16 *)&p[0x19771A] + *(s16 *)&p[0x19771C];

        q = (ChallengeState *)lbl_2_bss_1A8248;
        e = &q->characters[*(s16 *)&p[0x197716]];
        idx = (s8)lbl_2_bss_1A824C[0x197863];
        btn = AT_BAT_BUTTON(4, idx);
        tbl = e->scoutFlagPointer;
        if (btn & PAD_BUTTON_LEFT) {
            cnt = (s8)e->scoutFlagsAchieved;
            if (cnt > 0 && cnt != tbl->flagsRequired[q->difficulty][q->captain]) {
                e->scoutFlagsAchieved = cnt - 1;
            }
        } else if (btn & PAD_BUTTON_RIGHT) {
            cnt = (s8)e->scoutFlagsAchieved;
            if (cnt < tbl->flagsRequired[q->difficulty][q->captain]) {
                e->scoutFlagsAchieved = cnt + 1;
            }
        }

        idx = (s8)lbl_2_bss_1A824C[0x197863];
        btn = AT_BAT_BUTTON(2, idx);
        if (btn & (PAD_BUTTON_A | PAD_BUTTON_B)) {
            *(u16 *)((u8 *)node + 0x14) = 0x10;
            DRAW_STATE(node) = 2;
        }
        if (btn & PAD_TRIGGER_L) {
            for (k = 0; k < NUM_CHOOSABLE_CHARACTERS; k++) {
                e = &((ChallengeState *)lbl_2_bss_1A8248)->characters[k];
                for (j = 0; j < 10; j++) {
                    q = (ChallengeState *)lbl_2_bss_1A8248;
                    tbl = e->scoutFlagPointer;
                    if (tbl->flagsRequired[q->difficulty][q->captain] != 0) {
                        e->scoutFlagsAchieved = 0;
                    }
                }
                ((ChallengeState *)lbl_2_bss_1A8248)->recruitedChar[k] = FALSE;
                e->recruitmentStatus = CHALLENGE_RECRUITMENT_CD_NOT_RECRUITED;
            }
        } else if (btn & PAD_TRIGGER_R) {
            for (k = 0; k < NUM_CHOOSABLE_CHARACTERS; k++) {
                e = &((ChallengeState *)lbl_2_bss_1A8248)->characters[k];
                for (j = 0; j < 10; j++) {
                    q = (ChallengeState *)lbl_2_bss_1A8248;
                    tbl = e->scoutFlagPointer;
                    v = tbl->flagsRequired[q->difficulty][q->captain];
                    if (v != 0) {
                        e->scoutFlagsAchieved = v;
                    }
                }
            }
        }
        break;
    case 2:
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
        break;
    }
}

// .text:0x0001C860 size:0x734 mapped:0x8065B8F4
void fn_2_1C860(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    u8 *p;
    ChallengeState *q;
    ChallengeTrackingStruct *e;
    CharStaticIndex *chars;
    StarMissionRequirement *row;
    u16 btn;
    s32 idx;
    s32 k;
    s32 n;
    s32 v;
    s32 w;
    s32 ret0;
    s32 ret1;

    switch (DRAW_STATE(node)) {
    case 0:
        *(s16 *)&lbl_2_bss_1A824C[0x19771A] = 0;
        *(s16 *)&lbl_2_bss_1A824C[0x19771C] = 0;
        *(s16 *)&lbl_2_bss_1A824C[0x197720] = 0;
        *(s16 *)&lbl_2_bss_1A824C[0x197722] = 0;
        *(s16 *)&lbl_2_bss_1A824C[0x19771E] = NUM_CHOOSABLE_CHARACTERS;
        *(s16 *)&lbl_2_bss_1A824C[0x197724] = STAR_MISSIONS_PER_CHARACTER;
        DRAW_STATE(node) = 1;
        break;
    case 1:
        p = lbl_2_bss_1A824C;
        idx = (s8)p[0x197863];
        btn = AT_BAT_BUTTON(4, idx);
        if (btn == PAD_BUTTON_UP || btn == PAD_BUTTON_DOWN) {
            fn_2_46D94((s16 *)&p[0x19771A], (s16 *)&p[0x19771C], *(s16 *)&p[0x19771E], 10, 9);
        }
        p = lbl_2_bss_1A824C;
        *(s16 *)&p[0x197716] = *(s16 *)&p[0x19771A] + *(s16 *)&p[0x19771C];

        idx = (s8)lbl_2_bss_1A824C[0x197863];
        btn = AT_BAT_BUTTON(2, idx);
        if (btn & PAD_BUTTON_A) {
            DRAW_STATE(node) = 2;
        } else if (btn & PAD_BUTTON_B) {
            DRAW_STATE(node) = 3;
        }

        idx = (s8)lbl_2_bss_1A824C[0x197863];
        btn = AT_BAT_BUTTON(2, idx);
        if (btn & PAD_TRIGGER_L) {
            for (k = 0; k < NUM_CHOOSABLE_CHARACTERS; k++) {
                chars = &characterStaticIndexes[k];
                q = (ChallengeState *)lbl_2_bss_1A8248;
                e = &q->characters[k];
                if (chars->hasOwnStarMissions == 1) {
                    for (n = 0; n < STAR_MISSIONS_PER_CHARACTER; n++) {
                        row = starMissionRequirementsTable[chars->requirementRow];
                        if (row[n].type != STAR_MISSION_TYPE_NONE) {
                            e->inGameMissionTracker[n].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                        }
                    }
                }
            }
        } else if (btn & PAD_TRIGGER_R) {
            for (k = 0; k < NUM_CHOOSABLE_CHARACTERS; k++) {
                chars = &characterStaticIndexes[k];
                q = (ChallengeState *)lbl_2_bss_1A8248;
                e = &q->characters[k];
                if (chars->hasOwnStarMissions == 1) {
                    for (n = 0; n < STAR_MISSIONS_PER_CHARACTER; n++) {
                        row = starMissionRequirementsTable[chars->requirementRow];
                        if (row[n].type != STAR_MISSION_TYPE_NONE) {
                            e->inGameMissionTracker[n].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                        }
                    }
                }
            }
        }
        break;
    case 2:
        p = lbl_2_bss_1A824C;
        idx = (s8)p[0x197863];
        btn = AT_BAT_BUTTON(4, idx);
        if (btn == PAD_BUTTON_UP || btn == PAD_BUTTON_DOWN) {
            fn_2_46D94((s16 *)&p[0x197720], (s16 *)&p[0x197722], *(s16 *)&p[0x197724], 10, 9);
        }
        p = lbl_2_bss_1A824C;
        *(s16 *)&p[0x197718] = *(s16 *)&p[0x197720] + *(s16 *)&p[0x197722];
        ret0 = fn_8006CDC0(*(s16 *)&p[0x197716]);
        p = lbl_2_bss_1A824C;
        ret1 = fn_2_44E2C(*(s16 *)&p[0x197716]);

        p = lbl_2_bss_1A824C;
        idx = (s8)lbl_2_bss_1A824C[0x197863];
        btn = AT_BAT_BUTTON(2, idx);
        q = (ChallengeState *)lbl_2_bss_1A8248;
        v = *(s16 *)&p[0x197716];
        e = &q->characters[v];
        chars = &characterStaticIndexes[v];
        if ((btn & (PAD_BUTTON_A | PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT)) && ret0 != ret1 && chars->hasOwnStarMissions == 1) {
            row = starMissionRequirementsTable[chars->requirementRow];
            w = *(s16 *)&p[0x197718];
            if (row[w].type != STAR_MISSION_TYPE_NONE) {
                e->inGameMissionTracker[w].starMissionStatus = (e->inGameMissionTracker[w].starMissionStatus >= 0) ? STAR_MISSION_TRACKING_COMPLETED_SAVED : STAR_MISSION_TRACKING_NOT_COMPLETED;
                fn_8006CDC0(*(s16 *)&p[0x197716]);
            }
        } else if (btn & PAD_BUTTON_B) {
            DRAW_STATE(node) = 1;
        }

        idx = (s8)lbl_2_bss_1A824C[0x197863];
        btn = AT_BAT_BUTTON(2, idx);
        if (btn & PAD_TRIGGER_L) {
            for (n = 0; n < STAR_MISSIONS_PER_CHARACTER; n++) {
                v = *(s16 *)&lbl_2_bss_1A824C[0x197716];
                chars = &characterStaticIndexes[v];
                if (chars->hasOwnStarMissions == 1) {
                    row = starMissionRequirementsTable[chars->requirementRow];
                    if (row[n].type != STAR_MISSION_TYPE_NONE) {
                        e->inGameMissionTracker[n].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                    }
                }
            }
        } else if (btn & PAD_TRIGGER_R) {
            for (n = 0; n < STAR_MISSIONS_PER_CHARACTER; n++) {
                v = *(s16 *)&lbl_2_bss_1A824C[0x197716];
                chars = &characterStaticIndexes[v];
                if (chars->hasOwnStarMissions == 1) {
                    row = starMissionRequirementsTable[chars->requirementRow];
                    if (row[n].type != STAR_MISSION_TYPE_NONE) {
                        e->inGameMissionTracker[n].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                    }
                }
            }
        }
        break;
    case 3:
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
        break;
    }
}

// .text:0x0001C714 size:0x14C mapped:0x8065B7A8
void fn_2_1C714(s32 idx) {
    u8 *q;
    ChallengeMapRecord *record;
    s32 i;
    u32 mask;

    for (i = 0; i < 51; i++) {
        record = challengeMapRecord(i);
        if (idx == record->kind && (record->state == 1 || record->state == 0)) {
            if (record->unknown2 == 0 && ((ChallengeState *)lbl_2_bss_1A8248)->captain != idx) {
                if (((ChallengeState *)lbl_2_bss_1A8248)->captain == CHALLENGE_CAPTAIN_BOWSER) {
                    record->state = 3;
                } else {
                    record->state = 0;
                }
            } else {
                record->state = 0;
            }
            record = challengeMapRecord(i);
            if (record->unknown2 == 2) {
                record->state = 0;
            }
        }
        record = challengeMapRecord(i);
        if (record->kind == 6 || record->kind == 7 || record->kind == 8) {
            record->state = 0;
            lbl_2_bss_1A8248[0x4412] = TRUE;
            lbl_2_bss_1A8248[0x4413] = TRUE;
            lbl_2_bss_1A8248[0x4414] = TRUE;
        }
    }
    lbl_2_bss_1A8248[0x440C + idx] = TRUE;
    q = lbl_2_bss_1A8248;
    if (((ChallengeState *)lbl_2_bss_1A8248)->captain == idx) {
        return;
    }
    mask = 1U << idx;
    if (q[0x4426] & mask) {
        return;
    }
    ((ChallengeState *)q)->stage++;
    q = lbl_2_bss_1A8248;
    q[0x4426] |= mask;
}

// .text:0x0001C5C8 size:0x14C mapped:0x8065B65C
void fn_2_1C5C8(s32 idx) {
    u8 *q;
    ChallengeMapRecord *record;
    s32 i;
    u32 mask;

    for (i = 0; i < 51; i++) {
        record = challengeMapRecord(i);
        if (idx == record->kind && (record->state == 1 || record->state == 0)) {
            if (record->unknown2 == 0 && ((ChallengeState *)lbl_2_bss_1A8248)->captain != idx) {
                if (((ChallengeState *)lbl_2_bss_1A8248)->captain == CHALLENGE_CAPTAIN_BOWSER) {
                    record->state = 3;
                } else {
                    record->state = 2;
                }
            } else {
                record->state = 0;
            }
            record = challengeMapRecord(i);
            if (record->unknown2 == 2) {
                record->state = 0;
            }
        }
        record = challengeMapRecord(i);
        if (record->kind == 6 || record->kind == 7 || record->kind == 8) {
            record->state = 0;
            lbl_2_bss_1A8248[0x4412] = TRUE;
            lbl_2_bss_1A8248[0x4413] = TRUE;
            lbl_2_bss_1A8248[0x4414] = TRUE;
        }
    }
    lbl_2_bss_1A8248[0x440C + idx] = TRUE;
    q = lbl_2_bss_1A8248;
    if (((ChallengeState *)lbl_2_bss_1A8248)->captain == idx) {
        return;
    }
    mask = 1U << idx;
    if (q[0x4426] & mask) {
        return;
    }
    ((ChallengeState *)q)->stage++;
    q = lbl_2_bss_1A8248;
    q[0x4426] |= mask;
}

// .text:0x0001C504 size:0xC4 mapped:0x8065B598
void fn_2_1C504(s32 idx) {
    u8 *q;
    ChallengeMapRecord *record;
    s32 i;
    u32 mask;

    for (i = 0; i < 51; i++) {
        record = challengeMapRecord(i);
        if (idx == record->kind && (record->state == 1 || record->state == 0)) {
            if (((ChallengeState *)lbl_2_bss_1A8248)->captain == CHALLENGE_CAPTAIN_BOWSER) {
                if (record->unknown2 == 1) {
                    record->state = 3;
                } else {
                    record->state = 0;
                }
            } else {
                record->state = 0;
            }
        }
    }
    q = lbl_2_bss_1A8248;
    q[0x440C + idx] = TRUE;
    mask = 1U << idx;
    q = lbl_2_bss_1A8248;
    if (q[0x4428] & mask) {
        return;
    }
    q[0x4423]++;
    q = lbl_2_bss_1A8248;
    q[0x4428] |= mask;
}

// .text:0x0001C490 size:0x74 mapped:0x8065B524
void fn_2_1C490(void) {
    lbl_2_bss_1A8234[0x162841] = 1;
    lbl_2_bss_1A8234[0x162860] = 1;
    lbl_2_bss_1A8234[0x162861] = 1;
    lbl_2_bss_1A8234[0x162862] = 1;
    lbl_2_bss_1A8234[0x162657] = 0;
    lbl_2_bss_1A8234[0x162676] = 0;
    lbl_2_bss_1A8234[0x162677] = 0;
    lbl_2_bss_1A8234[0x162678] = 0;
}

// .text:0x0001C41C size:0x74 mapped:0x8065B4B0
void fn_2_1C41C(void) {
    lbl_2_bss_1A8234[0x162657] = 1;
    lbl_2_bss_1A8234[0x162676] = 1;
    lbl_2_bss_1A8234[0x162677] = 1;
    lbl_2_bss_1A8234[0x162678] = 1;
    lbl_2_bss_1A8234[0x162841] = 0;
    lbl_2_bss_1A8234[0x162860] = 0;
    lbl_2_bss_1A8234[0x162861] = 0;
    lbl_2_bss_1A8234[0x162862] = 0;
}

// .text:0x0001C3A8 size:0x74 mapped:0x8065B43C
void fn_2_1C3A8(void) {
    if (lbl_2_bss_1A824C[0x1978FB] == 1) {
        lbl_2_bss_1A8234[0x16268A] = 1;
        lbl_2_bss_1A8234[0x162874] = 0;
    } else {
        lbl_2_bss_1A8234[0x162874] = 1;
        lbl_2_bss_1A8234[0x16268A] = 0;
    }
}

// .text:0x0001C3A4 size:0x4 mapped:0x8065B438
void fn_2_1C3A4(void) {
    return;
}

// .text:0x0001C33C size:0x68 mapped:0x8065B3D0
void fn_2_1C33C(void) {
    ChallengeState *p = (ChallengeState *)lbl_2_bss_1A8248;
    s16 v;

    if (p->captain >= CHALLENGE_CAPTAIN_BOWSER + 1) {
        while (TRUE) {}
    }
    if (p->difficulty >= 4) {
        while (TRUE) {}
    }
    v = *(s16 *)((u8 *)p + 0x43BC);
    if (v < 0 || v > 999) {
        while (TRUE) {}
    }
    if (*(s16 *)&lbl_2_bss_1A823C[0x30] != 5) {
        return;
    }
    if (p->_4420[0] >= 5) {
        while (TRUE) {}
    }
}

// .text:0x0001C244 size:0xF8 mapped:0x8065B2D8
void fn_2_1C244(void) {
    u8 *rowBase;
    u8 *p;
    s32 row;
    s32 entry;
    s32 field;
    s32 n;

    rowBase = lbl_2_bss_1A8234;
    for (row = 0; row < 0x46; row++) {
        p = rowBase;
        n = 0;
        for (entry = 0; entry < 0x90; entry++) {
            for (field = 0; field < 6; field++) {
                if (row >= 0x23 && n >= 0x64 && *(u32 *)(p + field * 0x18) != 0) {
                    return;
                }
                n++;
            }
            p += 0x90;
        }
        rowBase += 0x5100;
    }
}

// .text:0x0001C21C size:0x28 mapped:0x8065B2B0
void fn_2_1C21C(void) {
    u8 buf[0x18];
    fn_2_68DAC(0, buf);
}

// .text:0x0001C0D4 size:0x148 mapped:0x8065B168
void fn_2_1C0D4(void) {
    s32 i;

    lbl_2_bss_1A823C[0x34] = 1;
    memset(lbl_2_bss_1A8250, 0, 0x1978FC);
    for (i = 0; i < 8; i++) {
        ((s16 *)(lbl_2_bss_1A824C + 0x197756))[i] = -1;
    }
    fn_2_54474();
    lbl_2_bss_1A8248[0x44F2] = 0;
    *(s16 *)&lbl_2_bss_1A824C[0x1976D6] = 0;
    lbl_2_bss_1A824C[0x197833] = 0;
    lbl_2_bss_1A8234[0x162992] = 0;
    lbl_2_bss_1A824C[0x197838] = 0;
    lbl_2_bss_1A824C[0x197835] = 0;
    g_d_GameSettings[9] = 0;
    lbl_2_bss_1A824C[0x197863] = Static_Stats_Tables[0x46F8];
    lbl_2_bss_1A824C[0x197848] = 0;
}

// .text:0x0001BFD0 size:0x104 mapped:0x8065B064
void fn_2_1BFD0(void) {
    fn_80068720(0xA);
    lbl_2_bss_1A824C[0x1972BC] = 1;
    lbl_2_bss_1A824C[0x1972C0] = 1;
    *(s16 *)&lbl_2_bss_1A824C[0x1976D6] = 0;
    lbl_2_bss_1A8248[0x44F2] = 0;
    if (lbl_2_bss_1A824C[0x197864] == 0) {
        fn_2_4E7EC();
    }
    resetGameStadiumStateOnExit();
    maybeLoadsGameSoundFiles();
    fn_800ACFB0(audioFileDescriptors.files[0x27]);
    if ((s8)lbl_2_bss_1A8248[0x44F4] != 0) {
        fn_2_4E8BC();
        fn_2_4E904();
        fn_2_4E928();
    } else {
        fn_2_4E928();
    }
    fn_2_4E94C();
    if (screenTextArray.textBanks[4] != NULL) {
        fn_800ACFB0(screenTextArray.textBanks[4]);
        screenTextArray.textBanks[4] = NULL;
    }
    lbl_2_bss_1A823C[0x34] = 0;
}

// .text:0x0001BF50 size:0x80 mapped:0x8065AFE4
void fn_2_1BF50(void) {
    fn_80068720(0xD);
    lbl_2_bss_1A824C[0x1972BC] = 1;
    lbl_2_bss_1A824C[0x1972C0] = 1;
    *(s16 *)&lbl_2_bss_1A824C[0x1976D6] = 0;
    lbl_2_bss_1A8248[0x44F2] = 0;
    fn_2_4E898();
    lbl_2_bss_1A823C[0x34] = 0;
}

// .text:0x0001B7B4 size:0x79C mapped:0x8065A848
void fn_2_1B7B4(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    DrawingSceneStruct *fresh;
    u8 *q;
    BOOL changeSceneRequested;
    s32 i;
    s32 captain;

    lbl_2_bss_1A8248 = (u8 *)&g_Challenge;
    lbl_2_bss_1A824C = lbl_2_bss_1A8250;
    lbl_2_bss_1A8238 = (u8 *)&g_Challenge + 0x1610;
    lbl_2_bss_1A8244 = superstarUnlocked;
    lbl_2_bss_1A823C = inningSetting + 0x28;
    lbl_2_bss_1A8234 = lbl_2_bss_1A8250;
    lbl_2_bss_1A8230 = lbl_2_bss_1A8250 + 0x162998;
    lbl_2_bss_340140 = hugeAnimStruct;

    switch (SCENE_STATE) {
    case 0:
        fn_8006C488();
        resetGameStadiumStateOnExit();
        lbl_2_bss_1A823C[0x34] = 1;
        memset(lbl_2_bss_1A8250, 0, 0x1978FC);
        for (i = 0; i < 8; i++) {
            ((s16 *)(lbl_2_bss_1A824C + 0x197756))[i] = -1;
        }
        fn_2_54474();
        lbl_2_bss_1A8248[0x44F2] = 0;
        *(s16 *)&lbl_2_bss_1A824C[0x1976D6] = 0;
        lbl_2_bss_1A824C[0x197833] = 0;
        lbl_2_bss_1A8234[0x162992] = 0;
        lbl_2_bss_1A824C[0x197838] = 0;
        lbl_2_bss_1A824C[0x197835] = 0;
        g_d_GameSettings[9] = 0;
        lbl_2_bss_1A824C[0x197863] = Static_Stats_Tables[0x46F8];
        lbl_2_bss_1A824C[0x197848] = 0;
        fn_8000F4B8(0, -1, -1, -1);
        SCENE_STATE = 2;
        break;
    case 1:
        if (node->state == 1) {
            SCENE_STATE = 2;
        }
        break;
    case 2:
        SCENE_STATE = 3;
        break;
    case 3:
        SCENE_STATE = 4;
        break;
    case 4:
        changeSceneRequested = FALSE;
        if (*(s16 *)&lbl_2_bss_1A823C[0x30] == 3) {
            fn_2_4AB1C();
            if (lbl_2_bss_1A824C[0x197843] == 0) {
                q = lbl_2_bss_1A8248;
                if (((ChallengeState *)q)->captain == CHALLENGE_CAPTAIN_BOWSER) {
                    if (fn_2_46D00() != 0) {
                        changeSceneRequested = TRUE;
                    }
                } else if (q[0x4426] & 0x20) {
                    changeSceneRequested = TRUE;
                }
            }
        }
        q = lbl_2_bss_1A8248;
        q[0x44F4] = (changeSceneRequested != FALSE);
        q = lbl_2_bss_1A8248;
        if (q[0x44F4] == 0) {
            SCENE_STATE = 0xC;
        } else {
            GXSetCopyClear(*(GXColor *)lbl_2_data_4BA8, 0xFFFFFF);
            changeScene(1, 6);
            q = lbl_2_bss_1A8248;
            if (((ChallengeState *)q)->difficulty < 3) {
                SCENE_STATE = 0xC;
            } else if (fn_2_4E970() == TRUE) {
                SCENE_STATE = 5;
            }
        }
        break;
    case 5:
        fresh = insertGraphicDrawingFunction(fn_2_37460, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 6;
        break;
    case 6:
        if (node->state == 1) {
            SCENE_STATE = 7;
        }
        break;
    case 7:
        lbl_2_bss_1A8250[0x162992] = 0;
        lbl_2_bss_1A8230[0x32A86] = 0;
        fn_2_54474();
        fn_2_2460C();
        SCENE_STATE = 8;
        break;
    case 8:
        playStream(0xD);
        fresh = insertGraphicDrawingFunction(fn_2_37D98, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 9;
        break;
    case 9:
        if (node->state == 1) {
            SCENE_STATE = 0xA;
        }
        break;
    case 10:
        fresh = insertGraphicDrawingFunction(fn_2_40A9C, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 0xB;
        break;
    case 11:
        if (node->state == 1) {
            SCENE_STATE = 0xC;
        }
        break;
    case 12:
        if (lbl_2_bss_1A8248[0x44F4] == 0) {
            fresh = insertGraphicDrawingFunction(fn_2_1B6CC, 2);
        } else {
            fresh = insertGraphicDrawingFunction(fn_2_1B5C0, 2);
        }
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 0xD;
        break;
    case 13:
        if (node->state == 1) {
            SCENE_STATE = 0xE;
        }
        break;
    case 14:
        fn_800216F8(0x26, fn_800627F8);
        node->state = 0;
        SCENE_STATE = 0xF;
        break;
    case 15:
        if (node->state == 1) {
            SCENE_STATE = 0x12;
        }
        break;
    case 18:
        switch (*(s16 *)&lbl_2_bss_1A823C[0x30]) {
        case 1:
            fn_2_468DC();
            SCENE_STATE = 0x17;
            break;
        case 0:
            captain = fn_2_20CB0(*(u32 *)&Static_Stats_Tables[0x46E0]);
            q = lbl_2_bss_1A8248;
            ((ChallengeState *)q)->captain = captain;
            q = lbl_2_bss_1A8248;
            ((ChallengeState *)q)->captainCharID = challengeCaptainCharIDs[((ChallengeState *)q)->captain];
            q = lbl_2_bss_1A8248;
            if (q[0x1606] != 0) {
                fn_2_20328();
                fn_2_46418();
                fn_2_468DC();
                fn_2_466AC();
                fn_2_467FC();
                fn_2_454E8();
            } else {
                q[0x1605] = 0;
                fn_2_207FC();
                fn_2_466AC();
            }
            fresh = insertGraphicDrawingFunction(fn_2_379D0, 2);
            DRAW_STATE(fresh) = 0;
            node->state = 0;
            SCENE_STATE = 0x13;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            lbl_2_bss_1A8248[0x44F2] = 0;
            SCENE_STATE = 0x17;
            break;
        }
        break;
    case 19:
        if (node->state == 1) {
            SCENE_STATE = 0x17;
        }
        break;
    case 20:
        *(s16 *)&lbl_2_bss_1A824C[0x197746] = 7;
        fresh = insertGraphicDrawingFunction(fn_2_1B314, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 0x15;
        break;
    case 21:
        if (node->state == 1) {
            SCENE_STATE = 0x16;
        }
        break;
    case 22:
        fresh = insertGraphicDrawingFunction(fn_2_1B1BC, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 0x17;
        break;
    case 23:
        if (node->state == 1) {
            node->state = 0;
            node->func = fn_2_20D08;
            SCENE_STATE = 0;
        }
        break;
    }

    *(u16 *)&g_d_GameSettings[4] += 1;
    *(u32 *)&lbl_2_bss_1A824C[0x1976C0] += 1;
}

// .text:0x0001B6CC size:0xE8 mapped:0x8065A760
void fn_2_1B6CC(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    DrawingSceneStruct *fresh;

    switch (DRAW_STATE(node)) {
    case 0:
        fresh = insertGraphicDrawingFunction(fn_2_409CC, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        DRAW_STATE(node) = 1;
        break;
    case 1:
        if (node->state == 1) {
            DRAW_STATE(node) = 2;
        }
        break;
    case 2:
        if (fn_2_4EB64() == TRUE) {
            DRAW_STATE(node) = 3;
        }
        break;
    case 3:
        if (fn_2_4EB2C() == TRUE) {
            DRAW_STATE(node) = 4;
        }
        break;
    case 4:
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
        break;
    }
}

// .text:0x0001B5C0 size:0x10C mapped:0x8065A654
void fn_2_1B5C0(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    DrawingSceneStruct *fresh;

    switch (DRAW_STATE(node)) {
    case 0:
        fresh = insertGraphicDrawingFunction(fn_2_409CC, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        DRAW_STATE(node) = 1;
        break;
    case 1:
        if (node->state == 1) {
            DRAW_STATE(node) = 2;
        }
        break;
    case 2:
        if (fn_2_4EB64() == 1) {
            DRAW_STATE(node) = 3;
        }
        break;
    case 3:
        if (fn_2_4EB2C() == 1) {
            DRAW_STATE(node) = 4;
        }
        break;
    case 4:
        if (fn_2_4EAF4() == 1) {
            DRAW_STATE(node) = 5;
        }
        break;
    case 5:
        if (fn_2_4E9A8() == 1) {
            DRAW_STATE(node) = 6;
        }
        break;
    case 6:
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
        break;
    }
}

// .text:0x0001B52C size:0x94 mapped:0x8065A5C0
void fn_2_1B52C(void) {
    DrawingSceneStruct *node = currentDrawingItem;

    switch (DRAW_STATE(node)) {
    case 0:
        if (fn_2_4E970() == TRUE) {
            DRAW_STATE(node) = 1;
        }
        break;
    case 1:
        DRAW_STATE(node) = 6;
        break;
    case 6:
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
        break;
    }
}

// .text:0x0001B314 size:0x218 mapped:0x8065A3A8
void fn_2_1B314(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    DrawingSceneStruct *fresh;
    s32 i;

    switch (DRAW_STATE(node)) {
    case 0:
        *(s16 *)&lbl_2_bss_1A824C[0x197746] = 7;
        fresh = insertGraphicDrawingFunction(fn_2_8EA80, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        DRAW_STATE(node) = 1;
        break;
    case 1:
        if (node->state == 1) {
            DRAW_STATE(node) = 2;
        }
        break;
    case 2:
        fresh = insertGraphicDrawingFunction(fn_2_8E478, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        DRAW_STATE(node) = 3;
        break;
    case 3:
        if (node->state == 1) {
            DRAW_STATE(node) = 12;
        }
        break;
    case 4:
        for (i = 0; i < *(s16 *)&lbl_2_bss_1A824C[0x197746]; i++) {
            fn_2_8CCAC(i, 1);
            fn_2_68FBC(i, 1);
        }
        DRAW_STATE(node) = 5;
        break;
    case 5:
        fn_2_47CFC();
        DRAW_STATE(node) = 6;
        break;
    case 6:
        for (i = 0; i < *(s16 *)&lbl_2_bss_1A824C[0x197746]; i++) {
            fn_2_8CCAC(i, 0);
        }
        fn_2_47CFC();
        DRAW_STATE(node) = 7;
        break;
    case 7:
        fn_2_47CFC();
        DRAW_STATE(node) = 8;
        break;
    case 8:
        DRAW_STATE(node) = 9;
        break;
    case 9:
        fn_2_8AEE0();
        DRAW_STATE(node) = 10;
        break;
    case 10:
        for (i = 0; i < 0x1D; i++) {
            fn_2_8ACB0(i, 0);
        }
        fn_2_8AEE0();
        DRAW_STATE(node) = 11;
        break;
    case 11:
        fn_2_8AEE0();
        DRAW_STATE(node) = 12;
        break;
    case 12:
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
        break;
    }
}

// .text:0x0001B1BC size:0x158 mapped:0x8065A250
void fn_2_1B1BC(void) {
    DrawingSceneStruct *node = currentDrawingItem;

    switch (DRAW_STATE(node)) {
    case 0:
        lbl_2_data_4BA0 = lbl_2_bss_1034C;
        *(void **)(lbl_2_data_4BA0 + 8) = ARAMTransfer(teamStarModelFileDescriptorMenus, 0, 0, 0);
        DRAW_STATE(node) = 1;
        break;
    case 1:
        if (lbl_803C6CF8[0x715] == 1) {
            DRAW_STATE(node) = 2;
        }
        break;
    case 2: {
        u32 *tbl = *(u32 **)(lbl_2_data_4BA0 + 8);
        void *texture = (void *)(tbl[0] + (u32)tbl);
        s32 i = 1;
        while (i--) {
            tbl[i] += (u32)tbl;
        }
        convertTextureHeader(texture);
        tbl = *(u32 **)(lbl_2_data_4BA0 + 8);
        *(u32 *)(lbl_2_data_4BA0 + 4) = tbl[0];
        fn_8004B1B8(*(void **)(lbl_2_data_4BA0 + 4));
        DRAW_STATE(node) = 3;
        break;
    }
    case 3:
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
    }
}
