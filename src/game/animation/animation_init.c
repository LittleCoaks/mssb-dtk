#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_animationInit
#include "header_rep_data.h"
#include "game/animation/animation_init.h"
#include "game/animation/animation_dispatch.h"
#include "game/math/game_math.h"
#include "Dolphin/stl.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x8001b918.h"

/* Trailing fields of one vsSituations row (0x40 bytes each). */
typedef struct AnimVsRow {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ s32 _34;
    /*0x38*/ s32 _38;
    /*0x3C*/ s32 _3C;
} AnimVsRow;

#define VS_ROW_COUNT 33

extern AnimScreenState *lbl_3_common_bss_1323C;
extern AnimActorView hugeAnimStruct;
extern AnimVsRow vsSituations[VS_ROW_COUNT];
extern AnimSetupEntry lbl_3_data_1E434[];
extern AnimSetupEntry lbl_3_data_1F090[];
extern AnimSetupEntry lbl_3_data_1D28[];
extern u8 *lbl_3_data_1F40[];

// .text:0x000250FC size:0xE8
void initializeAnimations(void) {
    int i;

    lbl_3_common_bss_1323C->_25C = 0;
    for (i = 0; i < VS_ROW_COUNT; i++) {
        vsSituations[i]._34 = 0;
        vsSituations[i]._38 = 0;
        vsSituations[i]._3C = 0;
    }
    lbl_3_common_bss_1323C->_27B = 0;
}

// .text:0x00024F24 size:0x1D8
void fn_3_24F24(int scriptIndex) {
    u8 *cursor = lbl_3_data_1F40[scriptIndex];
    int extraRoll = 0;
    int i;

    for (i = 0; i < ANIM_SLOT_COUNT; i++) {
        lbl_3_common_bss_1323C->_240[i] = -1;
    }
    lbl_3_common_bss_1323C->_25C = 1;
    lbl_3_common_bss_1323C->_23C = 0;
    lbl_3_common_bss_1323C->_27C = 0;
    lbl_3_common_bss_1323C->_25D = scriptIndex;
    lbl_3_common_bss_1323C->_25F = 1;
    lbl_3_common_bss_1323C->_27D = 0;
    lbl_3_common_bss_1323C->_27E = 0;
    lbl_3_common_bss_1323C->_25A = 0;
    lbl_3_common_bss_1323C->_280 = 1;

    lbl_3_common_bss_1323C->_23E = cursor[0] * 10;
    cursor++;
    if (*cursor == 0xFD) {
        extraRoll = 2;
        cursor++;
    }
    lbl_3_common_bss_1323C->_25E = *cursor++;
    if (extraRoll != 0) {
        lbl_3_common_bss_1323C->_25E += random_fn_3_9EE24(extraRoll);
    }
    for (;;) {
        u8 index = *cursor;
        if (index == 0xFE) {
            break;
        }
        cursor++;
        lbl_3_common_bss_1323C->_240[lbl_3_data_1D28[index].slot] = index;
    }
}

// .text:0x00024F20 size:0x4
void fn_3_24F20(void) {
}

// .text:0x00024EA0 size:0x80
void fn_3_24EA0(void) {
    int i;

    for (i = 0; i < ANIM_SLOT_COUNT; i++) {
        lbl_3_common_bss_1323C->_240[i] = -1;
        memset(&lbl_3_common_bss_1323C->slots[i], 0, sizeof(AnimStateSlot));
        lbl_3_common_bss_1323C->_261[i] = 0;
    }
}

// .text:0x00024DBC size:0xE4
void fn_3_24DBC(int value) {
    int i;

    for (i = 0; i < ANIM_SLOT_COUNT; i++) {
        lbl_3_common_bss_1323C->_240[i] = -1;
        memset(&lbl_3_common_bss_1323C->slots[i], 0, sizeof(AnimStateSlot));
        lbl_3_common_bss_1323C->_261[i] = 0;
    }
    resetAndRunAnimations(0);
    lbl_3_common_bss_1323C->_25C = 1;
    lbl_3_common_bss_1323C->_23C = 0;
    lbl_3_common_bss_1323C->_27C = 0;
    lbl_3_common_bss_1323C->_25D = value;
    lbl_3_common_bss_1323C->_25F = 1;
    lbl_3_common_bss_1323C->_27D = 0;
    lbl_3_common_bss_1323C->_27E = 0;
    lbl_3_common_bss_1323C->_25A = 0;
    lbl_3_common_bss_1323C->_280 = 1;
}

// .text:0x00024ADC size:0x2E0
void fn_3_24ADC(int setupIndex, int queueAnim) {
    AnimSetupEntry *entry = &lbl_3_data_1E434[setupIndex];
    int slot = entry->slot;
    AnimObject *obj;
    InMemRunnerType *runner;
    u8 animFlag = 0;

    lbl_3_common_bss_1323C->_240[slot] = setupIndex;
    if (slot <= 8) {
        obj = hugeAnimStruct.objects[slot];
        if (entry->_19 == 0) {
            memcpy(&g_Fielders[slot], entry, 0xC);
            if (obj != NULL) {
                memcpy(&obj->pos, entry, 0xC);
            }
        }
        lbl_3_common_bss_1323C->slots[slot]._0C = entry->_0C;
        g_Fielders[slot].desiredMovementDirection = entry->_0C;
        if (obj != NULL) {
            obj->_44 = entry->_0C;
            obj->_25D = 1;
        }
        if (entry->animId >= 0x69 && entry->animId < 0x75) {
            animFlag = 0;
        } else {
            animFlag = g_Fielders[slot].throwingHandedness;
        }
        lbl_3_common_bss_1323C->_261[slot] = 1;
        lbl_3_common_bss_1323C->_26E[slot] = 1;
    } else if (slot <= 12) {
        obj = hugeAnimStruct.objects[slot];
        if (slot == 10) {
            if (obj == NULL) {
                return;
            }
        } else if (slot == 11) {
            if (obj == NULL) {
                return;
            }
        } else if (slot == 12) {
            if (obj == NULL) {
                return;
            }
        }
        runner = &g_Runners[slot - 9];
        if (entry->_19 == 0) {
            memcpy(runner, entry, 0xC);
            if (obj != NULL) {
                memcpy(&obj->pos, entry, 0xC);
            }
        }
        lbl_3_common_bss_1323C->slots[slot]._0C = entry->_0C;
        runner->runningAngle = entry->_0C;
        if (obj != NULL) {
            obj->_44 = entry->_0C;
            obj->_25D = 1;
        }
        lbl_3_common_bss_1323C->_261[slot] = 1;
        lbl_3_common_bss_1323C->_26E[slot] = 1;
        if (slot == 9) {
            u8 state = lbl_3_common_bss_1323C->_25D;
            if (state == 0 || state == 1) {
                if (g_Batter.batterHand == BATTING_HAND_LEFT) {
                    animFlag = 0;
                } else {
                    animFlag = 1;
                }
            }
        }
    }

    if (queueAnim == 0) {
        AnimateCharacter(slot, entry->animId, entry->_16, entry->_17, entry->_18, entry->_12, animFlag, 0);
    } else {
        QueueCharacterAnimation(slot, entry->animId, entry->_16, entry->_18, entry->_12, animFlag, 0);
    }
}

// .text:0x000249E8 size:0xF4
void fn_3_249E8(int setupIndex) {
    AnimSetupEntry *entry = &lbl_3_data_1F090[setupIndex];
    int i;
    u8 slot = entry->slot;

    for (i = 0; i < 9; i++) {
        if (slot == g_Fielders[i].rosterLocSkippingCap) {
            lbl_3_common_bss_1323C->_240[i] = setupIndex;
            if (entry->_19 == 0) {
                memcpy(&g_Fielders[i], entry, 0xC);
            }
            lbl_3_common_bss_1323C->slots[i]._0C = entry->_0C;
            g_Fielders[i].desiredMovementDirection = entry->_0C;
            lbl_3_common_bss_1323C->_261[i] = 1;
            AnimateCharacter(i, entry->animId, entry->_16, entry->_17, entry->_18, entry->_12, 0, 0);
        }
    }
}
