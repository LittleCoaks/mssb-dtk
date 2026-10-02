#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_minigameFielderAnim
#include "game/minigame/minigame_fielder_anim.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/fielding/fielder_orientation.h"
#include "game/batting/star_hit_sprites.h"

// This file's own local view of hugeAnimStruct (extern, defined elsewhere):
// only the object-pointer array at +0x2C50 is touched here. Per-TU local
// views of this same global already exist elsewhere (AnimView in
// animation_dispatch.c, the anonymous struct in actor_transform.c); this is
// another one, not a shared type.
typedef struct MinigameAnimObj {
    u8 _00[0x34];
    f32 _34;
    f32 _38;
    f32 _3C;
    f32 _40;
    f32 _44;
    f32 _48;
    u8 _4C[0x252 - 0x4C];
    s8 _252;
    u8 _253[0x25A - 0x253];
    u8 _25A;
    u8 _25B;
    u8 _25C;
    u8 _25D;
    u8 _25E[0x275 - 0x25E];
    u8 _275;
    u8 _276[0x278 - 0x276];
    u8 _278;
} MinigameAnimObj;

typedef struct MinigameHugeAnimView {
    u8 _0000[0x2C50];
    MinigameAnimObj *objects[13];
    u8 _2C84[0x2D68 - 0x2C84];
    s16 _2D68;
} MinigameHugeAnimView;

extern MinigameHugeAnimView hugeAnimStruct;

// This file's own local view of g_UnkAnimation_31EAC (AnimSlot[9] in
// animation_dispatch.c); only fields _28 and _42 are touched here.
typedef struct MinigameAnimSlot {
    u8 _00[0x28];
    f32 _28;
    u8 _2C[0x42 - 0x2C];
    u8 _42;
    u8 _43[0x54 - 0x43];
} MinigameAnimSlot;

extern MinigameAnimSlot g_UnkAnimation_31EAC[9];

// .data:0x18DD4, size 0x30 -- per-fielder {x, y, z} table (transition_init.c
// already declares `extern f32 lbl_3_data_18DD4[3];` for its own 1-element
// use; this file strides it per-fielder, 4 * 3 floats = 0x30, matching
// symbols.txt's recorded size).
extern f32 lbl_3_data_18DD4[4][3];

// .data:0x217D8, size 0x20 -- per-fielder {x, z} table.
extern f32 lbl_3_data_217D8[4][2];

extern void resetAnimationRelatedPointers(void);
extern void AnimBlr(void);
// Engine-wide .dol function, not declared anywhere else in the repo yet
// (same situation as barrel_batter.c's fn_8004C108). Returns the same/a
// different anim-object pointer depending on the BOOL argument.
extern MinigameAnimObj *fn_800111FC(MinigameAnimObj *obj, BOOL flag);
// Engine-wide .dol function, likewise undeclared elsewhere.
extern BOOL fn_8004ACC4(BOOL flag);

// .text:0x000E1478 size:0x4EC mapped:0x8072050C
void updateMinigameFielderAnimations(void) {
    E(u8, GAME_STATUS) status = g_GameLogic.gameStatus;
    int i;

    if (status != GAME_STATUS_DEFAULT && status != GAME_STATUS_AT_BAT && status != GAME_STATUS_LIVE_BALL &&
        status != GAME_STATUS_TRANSITION && status != GAME_STATUS_INNING_TRANSITION &&
        status != GAME_STATUS_PAUSED && status != GAME_STATUS_HOW_TO_PLAY_SCREEN &&
        status != GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING &&
        !(g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL && status == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY)) {
        for (i = 0; i < 4; i++) {
            if (hugeAnimStruct.objects[i] != NULL) {
                hugeAnimStruct.objects[i]->_25D = 0;
            }
        }
        resetAnimationRelatedPointers();
        AnimBlr();
        return;
    }

    for (i = 0; i < 4; i++) {
        if (hugeAnimStruct.objects[i] != NULL) {
            hugeAnimStruct.objects[i]->_25D = 0;
        }
    }

    for (i = 0; i < 4; i++) {
        s8 ctrlByte = g_Minigame.minigameControlStruct[0].characterIndex[i];
        MinigameAnimSlot *animSlot;
        MinigameAnimObj *obj;
        InMemFielder *fielder;
        MinigameAnimObj *runnerObj;
        InMemRunnerType *runner;
        int runnerIdx;
        int fielderIdx;
        s8 fielderSlot;
        E(u8, GAME_STATUS) curStatus;

        if (ctrlByte < 0) {
            continue;
        }

        if ((curStatus = g_GameLogic.gameStatus) == GAME_STATUS_INNING_TRANSITION) {
            MinigameAnimObj *idleObj = hugeAnimStruct.objects[ctrlByte];

            if (idleObj != NULL) {
                idleObj->_25D = 0;
            }
            continue;
        }

        if (g_Minigame.minigameControlStruct[1].battingHandedness[2 + i] == 0) {
            /* "assigned fielder" path */
            fielderIdx = g_Minigame.minigameFielderIndex[i];
            if ((s8)fielderIdx < 0) {
                return;
            }
            fielderSlot = (s8)fielderIdx;

            obj = hugeAnimStruct.objects[ctrlByte];
            if (obj == NULL) {
                continue;
            }

            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                switch (curStatus) {
                case GAME_STATUS_DEFAULT:
                case GAME_STATUS_AT_BAT:
                case GAME_STATUS_LIVE_BALL:
                case GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY:
                    obj = fn_800111FC(obj, TRUE);
                    break;
                case GAME_STATUS_PAUSED:
                case GAME_STATUS_0xC:
                case GAME_STATUS_HOW_TO_PLAY_SCREEN:
                    break;
                default:
                    obj = fn_800111FC(obj, FALSE);
                    break;
                }
            }

            obj->_25D = 1;
            obj->_278 = 0;
            animSlot = &g_UnkAnimation_31EAC[fielderSlot];
            fielder = &g_Fielders[fielderSlot];
            if (animSlot->_42 == 0) {
                obj->_34 = fielder->pos.x;
                obj->_38 = -fielder->pos.y - fielder->actionYOffset;
                obj->_3C = fielder->pos.z;
            }
            {
                f32 orientation = computeAdjustedFielderOrientation(fielderSlot);
                obj->_44 = orientation;
                obj->_40 = 0.0f;
                obj->_48 = 0.0f;
                animSlot->_28 = orientation;
            }
            obj->_275 = fielder->terrainOrCollisionRelated;

            if (g_Fielders[i]._0263 != 0) {
                obj->_25D = 2;
            }
            if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
                if (fielder->onFire == 0 && g_Minigame.starDashStunType[i] == 3 &&
                    (g_d_GameSettings.FrameCountWhileNotAtMainMenu & 1) != 0) {
                    obj->_25D = 2;
                }
            }
        } else {
            /* "runner" path */

            if ((s8)g_Minigame.rosterID == i) {
                runnerIdx = 0;
            } else {
                runnerIdx = i;
                if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY ||
                    g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
                    continue;
                }
            }

            runnerObj = hugeAnimStruct.objects[ctrlByte];
            if (runnerObj == NULL) {
                continue;
            }
            runnerObj = fn_800111FC(runnerObj, FALSE);

            if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY) {
                u8 field33 = g_d_GameSettings._33;
                if (field33 == 0) {
                    continue;
                }
                if ((u8)(field33 - 1) <= 1) {
                    continue;
                }
            }

            if ((s8)g_Minigame.rosterID == i) {
                runnerObj->_278 = 1;
            }

            runnerObj->_25D = 1;
            runner = &g_Runners[runnerIdx];
            runnerObj->_34 = runner->position.x;
            runnerObj->_38 = runner->position.y;
            runnerObj->_3C = runner->position.z;
            runnerObj->_40 = 0.0f;
            runnerObj->_44 = runner->runningAngle;
            runnerObj->_48 = 0.0f;

            if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                runnerObj->_34 += lbl_3_data_217D8[i][0];
                runnerObj->_3C += lbl_3_data_217D8[i][1];
                if (g_Minigame.ccs.runnerChompHitState[i] == 3 && (g_d_GameSettings.FrameCountWhileNotAtMainMenu & 1) != 0) {
                    runnerObj->_25D = 2;
                }
            }

            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && runnerIdx == 0 &&
                g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) {
                s8 catchAnim = runnerObj->_252;
                if (catchAnim == 0x30 || (u8)(catchAnim - 0x31) <= 1 || catchAnim == 0x33) {
                    runnerObj->_25D = 2;
                    if (fn_8004ACC4(TRUE)) {
                        fn_3_6A2A4(runnerObj->_252);
                    }
                }
            }

            runnerObj->_275 = runner->someCollisionCheck;
        }
    }
}

// .text:0x000E1370 size:0x108 mapped:0x80720404
void fn_3_E1370(int mode) {
    MinigameAnimObj *obj;
    int i;

    for (i = 0; i < 4; i++) {
        if (mode == 3) {
            obj = hugeAnimStruct.objects[i];

            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
                obj = hugeAnimStruct.objects[9];
                if (i >= 1) {
                    return;
                }
            }
            if (obj != NULL) {
                obj->_25A = ((s8 *)&g_Minigame)[0x19EC + i * 9] / 2;
                obj->_25B = ((s8 *)&g_Minigame)[0x19EC + i * 9] % 2;
            }
        }
    }
}

// .text:0x000E12F8 size:0x78 mapped:0x8072038C
void fn_3_E12F8(void) {
    int i;

    for (i = 0; i < 4; i++) {
        if (hugeAnimStruct.objects[i] != NULL) {
            hugeAnimStruct.objects[i]->_25D = 0;
        }
    }
    resetAnimationRelatedPointers();
    AnimBlr();
}

// .text:0x000E11E0 size:0x118 mapped:0x80720274
void fn_3_E11E0(void) {
    int i;

    hugeAnimStruct._2D68 = -1;

    for (i = 0; i < 4; i++) {
        MinigameAnimObj *obj = hugeAnimStruct.objects[i];
        s8 throwDestField;
        s8 ballSpinField;
        s8 charField;

        if (obj == NULL) {
            continue;
        }
        obj->_25D = 0;

        if (((u8 *)&g_Minigame)[0x1A13 + i] != 0) {
            continue;
        }
        throwDestField = ((s8 *)&g_Minigame)[0x19EA + i * 9];
        if (throwDestField < 0) {
            continue;
        }
        ballSpinField = ((s8 *)&g_Minigame)[0x19EF + i * 9];
        if (ballSpinField == 0) {
            continue;
        }
        charField = ((s8 *)&g_Minigame)[0x19DA + i];
        if (charField < 0) {
            continue;
        }

        if (!g_d_GameSettings.exhibitionMatchInd) {
            if (charField >= 1) {
                continue;
            }
        } else if (g_Minigame._19E6 == 1 && g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD &&
                   g_Minigame._1A3C == 0) {
            if (charField >= 1) {
                continue;
            }
        }

        obj->_25D = 1;
        obj->_34 = lbl_3_data_18DD4[i][0];
        obj->_38 = -lbl_3_data_18DD4[i][1];
        obj->_3C = lbl_3_data_18DD4[i][2];
        obj->_40 = 0.0f;
        obj->_44 = 0.0f;
        obj->_48 = 0.0f;
    }
}
