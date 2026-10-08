#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_minigameFielderAnim
#include "game/minigame/minigame_fielder_anim.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/fielding/fielder_orientation.h"
#include "game/batting/star_hit_sprites.h"
#include "game/ball/ball_visuals.h"
#include "game/math/game_math.h"
#include "game/minigame/pitching_machine.h"
#include "game/stadium/stadium_framework.h"
#include "Unknown/File_0x800bf038.h"
#include "Unknown/File_0x8003a538.h"
#include "Dolphin/gx.h"
#include "Dolphin/rand.h"
#include "game/match_setup/pause_menu.h"

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

// One 0x28-byte record of the model table at hugeAnimStruct+0x2D94.
typedef struct MinigameModelRec {
    void *_00;
    f32 _04;
    f32 _08;
    f32 _0C;
    u8 _10[0x14 - 0x10];
    f32 _14;
    u8 _18[0x26 - 0x18];
    E(u8, BOOL) _26; // shown
    u8 _27;
} MinigameModelRec;

typedef struct MinigameHugeAnimView {
    u8 _0000[0x2294];
    f32 _2294;
    f32 _2298;
    f32 _229C;
    u8 _22A0[4];
    f32 _22A4;
    u8 _22A8[0x24BD - 0x22A8];
    u8 _24BD;
    u8 _24BE[0x2C50 - 0x24BE];
    MinigameAnimObj *objects[13];
    u8 _2C84[0x2D68 - 0x2C84];
    s16 _2D68;
    u8 _2D6A[0x2D94 - 0x2D6A];
    MinigameModelRec *models;
    u8 _2D98[0x307A - 0x2D98];
    u8 _307A;
    u8 _307B[0x3087 - 0x307B];
    u8 _3087;
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

// This file's view of the tail of g_Minigame (+0x1E08 / +0x1E22), where the
// per-player result slots and scores live.
typedef struct MinigameResultView {
    u8 _0000[0x1E08];
    u8 slot[4][2];
    u8 _1E10[0x1E22 - 0x1E10];
    u8 score[4];
} MinigameResultView;

#define MG_RESULT ((MinigameResultView *)&g_Minigame)


extern u8 mapping_minigame_Stadium[8];
extern s16 lbl_3_data_18BB0[4];
extern f32 resultsFielderMinigameOffsets[7][4];
extern s16 minigameResultsFrames[2];
// Plant placement table owned by sta_c3.c; only the list terminator flag is read here.
typedef struct MinigamePlantView {
    u8 _00[0x10];
    u8 usedFlag;
    u8 _11[0x1C - 0x11];
} MinigamePlantView;

extern MinigamePlantView parkPlantData[];

extern void fn_800BDF70(StadiumModel *model);
extern void applyUniformScaleToObject(f32 scale, int model);
extern void fn_3_14A070(s32 *values, int count);
extern void fn_3_149BA8(void);
extern void fn_3_15FA58(int count, s32 *values);
extern void fn_3_15F9AC(void);
extern void animateShadows_nonBall(void);
extern void toyfield_drawHud(void);
extern void minigameGraphics(void);

// .data:0x18D98, size 0x38.
f32 lbl_3_data_18D98[14] = {
    1.0f, 1.2f, 18.8f, 0.15f, 19.5f, 0.7f, 0.0f, 0.15f, 38.8f, 0.0f, -18.8f, 0.15f, 19.5f, -0.7f,
};

// .data:0x18DD0, size 0x4.
f32 toyFieldCoinSpinStep = 0.2f;

// .data:0x18DD4, size 0x30 -- per-fielder {x, y, z} table (transition_init.c
// declares `extern f32 charSelectFielderPositions[3];` for its own 1-element use; this
// file strides it per-fielder, 4 * 3 floats = 0x30).
f32 charSelectFielderPositions[4][3] = {
    { -225.0f, -30.0f, 0.0f },
    { -75.0f, -30.0f, 0.0f },
    { 75.0f, -30.0f, 0.0f },
    { 225.0f, -30.0f, 0.0f },
};

// .data:0x18E04, size 0xC0 -- [participant count - 1][participant][x, y, z] offsets.
f32 resultsFielderOffsets[4][4][3] = {
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { -1.2f, 0.0f, 0.0f }, { 1.2f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { -2.4f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.4f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { -3.6f, 0.0f, 0.0f }, { -1.2f, 0.0f, 0.0f }, { 1.2f, 0.0f, 0.0f }, { 3.6f, 0.0f, 0.0f } },
};

// .data:0x18EC4, size 0xC.
f32 resultsFielderRowOffsets[3] = { -1.5f, 0.0f, 1.5f };

// .data:0x217D8, size 0x20 -- per-fielder {x, z} table.
extern f32 ccs_resultsRunnerOffsets[4][2];

extern void resetAnimationRelatedPointers(void);
extern void AnimBlr(void);
// Engine-wide .dol function, not declared anywhere else in the repo yet
// (same situation as barrel_batter.c's fn_8004C108). Returns the same/a
// different anim-object pointer depending on the BOOL argument.
extern MinigameAnimObj *fn_800111FC(MinigameAnimObj *obj, BOOL flag);
// Engine-wide .dol function, likewise undeclared elsewhere.
extern BOOL fn_8004ACC4(BOOL flag);

// .text:0x000E1D00 size:0xB8
void drawParkPlants(void) {
    StadiumObject *obj;
    int i;

    fn_800BF058(fn_3_B8184);
    updateFunctionPtr(parkPlantsTevSetup);
    for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
        if (parkPlantData[i].usedFlag == 2) {
            break;
        }
        obj = &stadiumObjectCollision.objects[i];
        fn_3_B828C((s32)obj);
        if (obj->model != NULL) {
            obj->model->root->drawFlags = obj->nodeDrawFlags | 6;
            fn_800BDF70(obj->model);
        }
    }
    updateFunctionPtr(NULL);
}

// .text:0x000E1C60 size:0xA0
void parkPlantsTevSetup(void) {
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_A2, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

// .text:0x000E19E8 size:0x278
void graphicsFunction_minigames(void) {
    int i;

    hugeAnimStruct._3087 = TRUE;
    if (g_GameLogic.gameStatus == GAME_STATUS_GAME_START_MOVIE && g_GameLogic._125 == 5) {
        mm_LoadModels();
    }

    if (g_GameLogic.gameStatus == GAME_STATUS_0x1B) {
        return;
    }

    if (hugeAnimStruct._307A == 0) {
        for (i = 0; i < 4; i++) {
            if (hugeAnimStruct.objects[i] != NULL) {
                hugeAnimStruct.objects[i]->_25D = 0;
            }
        }
        resetAnimationRelatedPointers();
        AnimBlr();
    } else if ((u8)(g_GameLogic.gameStatus - GAME_STATUS_MINIGAME_SELECT) <= 2 || g_GameLogic.gameStatus == GAME_STATUS_0x1F) {
        if (g_GameLogic.gameStatus == GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT) {
            charSelectPlaceFielders();
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME || g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_POST_MENU ||
               g_GameLogic.gameStatus == GAME_STATUS_0x24 || g_GameLogic.gameStatus == GAME_STATUS_0x26 ||
               g_GameLogic.gameStatus == GAME_STATUS_0x27) {
        hugeAnimStruct._3087 = g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD;
        minigameUpdateResultsScene();
        mm_ResetModels();
    } else if (g_GameLogic.gameStatus == GAME_STATUS_LOAD_GAME) {
        return;
    } else if (g_GameLogic.gameStatus != GAME_STATUS_GAME_START_MOVIE) {
        ballAnimations();
        displayBallTrail();
        updateMinigameFielderAnimations();
        animateShadows_nonBall();
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            toyFieldUpdateCoinModels();
        } else {
            mm_UpdateModels();
        }
        animateChargeSprites();
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        toyfield_drawHud();
    } else {
        minigameGraphics();
    }
}

// .text:0x000E1964 size:0x84
void toyFieldInitCoinModels(void) {
    toyFieldSetCoinScaleAndSpin();
}

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
                runnerObj->_34 += ccs_resultsRunnerOffsets[i][0];
                runnerObj->_3C += ccs_resultsRunnerOffsets[i][1];
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
                obj->_25A = g_Minigame.selectSlots[i].loadedHandedness / 2;
                obj->_25B = g_Minigame.selectSlots[i].loadedHandedness % 2;
            }
        }
    }
}

// .text:0x000E12F8 size:0x78 mapped:0x8072038C
void hideMinigameFielders(void) {
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
void charSelectPlaceFielders(void) {
    int i;

    hugeAnimStruct._2D68 = -1;

    for (i = 0; i < 4; i++) {
        MinigameAnimObj *obj = hugeAnimStruct.objects[i];
        s8 loadedChar;
        s8 charReady;
        s8 slotState;

        if (obj == NULL) {
            continue;
        }
        obj->_25D = 0;

        if (g_Minigame.charLoadPending[i] != 0) {
            continue;
        }
        loadedChar = g_Minigame.selectSlots[i].loadedCharID;
        if (loadedChar < 0) {
            continue;
        }
        charReady = g_Minigame.selectSlots[i].charReadyInd;
        if (charReady == 0) {
            continue;
        }
        slotState = g_Minigame.selectSlotState[i];
        if (slotState < 0) {
            continue;
        }

        if (!g_d_GameSettings.exhibitionMatchInd) {
            if (slotState >= 1) {
                continue;
            }
        } else if (g_Minigame.targetParticipantCount == 1 && g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD &&
                   g_Minigame.grandPrixInd == 0) {
            if (slotState >= 1) {
                continue;
            }
        }

        obj->_25D = 1;
        obj->_34 = charSelectFielderPositions[i][0];
        obj->_38 = -charSelectFielderPositions[i][1];
        obj->_3C = charSelectFielderPositions[i][2];
        obj->_40 = 0.0f;
        obj->_44 = 0.0f;
        obj->_48 = 0.0f;
    }
}

// .text:0x000E07DC size:0xA04
void minigameUpdateResultsScene(void) {
    Vec v;
    s32 values[4];
    int i;
    int k;
    int participants;
    BOOL canShow = TRUE;
    int count;
    BOOL showWinners = FALSE;
    BOOL tWon = g_Minigame.challenge_minigame_haven_tWonYetIndicator;

    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME && g_GameLogic._125 == 0) {
            showWinners = TRUE;
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME) {
        if (g_GameLogic._125 < 4 || (g_GameLogic._125 == 4 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0)) {
            showWinners = TRUE;
        }
    }

    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_MINIGAME_POSTGAME || showWinners) {
        for (i = 0; i < 4; i++) {
            if (hugeAnimStruct.objects[i] != NULL) {
                hugeAnimStruct.objects[i]->_25D = 0;
            }
        }
        return;
    }

    if (g_GameLogic.gameStatus == GAME_STATUS_0x27) {
        tWon = TRUE;
        if (g_Minigame.grandPrixFinalHumanCount == 1) {
            tWon = FALSE;
            if (MG_RESULT->score[0] == MG_RESULT->score[1] && MG_RESULT->score[0] == MG_RESULT->score[2] &&
                MG_RESULT->score[0] == MG_RESULT->score[3]) {
                tWon = TRUE;
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.playerSlots.rank[i] != 1) {
                    tWon = FALSE;
                    break;
                }
            }
        }
    }

    showWinners = FALSE;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if ((g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME && g_GameLogic.FrameCountOfCurrentPitch == 1) ||
            (g_GameLogic.gameStatus == GAME_STATUS_0x27 && g_GameLogic.FrameCountOfCurrentPitch == 1)) {
            showWinners = TRUE;
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME && g_GameLogic._125 == 4 &&
               g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
        showWinners = TRUE;
    }

    if (showWinners) {
        count = 0;
        if (g_GameLogic.gameStatus == GAME_STATUS_0x27 || g_Minigame.grandPrixFinalInd != 0) {
            int best = -1;

            for (i = 0; i < 4; i++) {
                if (MG_RESULT->score[i] > best) {
                    best = MG_RESULT->score[i];
                }
            }
            if (g_Minigame.grandPrixFinalHumanCount == 1) {
                s8 me = g_Minigame.soloPlayerSlot;

                for (i = 0; i < 4; i++) {
                    if (MG_RESULT->slot[i][0] == me && MG_RESULT->slot[i][1] == 0) {
                        values[0] = me;
                        count = 1;
                        break;
                    }
                }
            } else {
                s32 *out = values;

                for (i = 0; i < 4; i++) {
                    if (MG_RESULT->score[i] == best) {
                        *out++ = i;
                        count++;
                    }
                }
            }
        } else if (g_d_GameSettings.minigamesEnabled == 0) {
            values[0] = 9;
            count = 1;
            if (StatsScreenScores.mvpKind >= 2) {
                canShow = FALSE;
            }
        } else if (g_Minigame.miniGameNumberOfParticipants > 1) {
            s32 *out = values;

            for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
                if (g_Minigame.playerSlots.rank[i] == 1) {
                    *out++ = g_Minigame.playerSlots.characterIndex[i];
                    count++;
                }
            }
            StatsScreenScores.mvpKind = 0;
        } else if (g_Minigame.soloMinigameDifficulty == 3) {
            if (g_Minigame.newRecordRank == 1 || g_Minigame.newRecordInd != 0) {
                count = 1;
                values[0] = g_Minigame.playerSlots.characterIndex[0];
            }
        } else {
            values[0] = g_Minigame.playerSlots.characterIndex[0];
            if (g_Minigame.winLossResult == 1) {
                StatsScreenScores.mvpKind = 0;
                count = 1;
            }
        }

        if (tWon == FALSE || count == 1) {
            fn_3_14A070(values, count);
            if (canShow && g_d_GameSettings.minigamesEnabled != 0) {
                if (count == 1) {
                    values[1] = values[0];
                    count = 2;
                } else if (count == 2) {
                    values[2] = values[0];
                    values[3] = values[1];
                    count = 4;
                }
                fn_3_15FA58(count, values);
            }
        }
    }

    if (tWon == FALSE) {
        if ((g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME && g_GameLogic.FrameCountOfCurrentPitch == minigameResultsFrames[0] &&
             StatsScreenScores.mvpKind <= 1) ||
            (g_GameLogic.gameStatus == GAME_STATUS_0x27 && g_GameLogic.FrameCountOfCurrentPitch == minigameResultsFrames[0])) {
            BOOL ok = TRUE;

            if (g_GameLogic.gameStatus == GAME_STATUS_0x27 && g_Minigame.grandPrixFinalHumanCount == 1) {
                s8 me = g_Minigame.soloPlayerSlot;

                ok = FALSE;
                for (i = 0; i < 4; i++) {
                    if (MG_RESULT->slot[i][0] == me && MG_RESULT->slot[i][1] == 0) {
                        ok = TRUE;
                        break;
                    }
                }
            }
            if (ok) {
                if (g_d_GameSettings.minigamesEnabled != 0) {
                    fn_3_15F9AC();
                }
                fn_3_149BA8();
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled == 0) {
        int idx;
        MinigameHugeAnimView *h = &hugeAnimStruct;

        for (idx = 0; idx < 6; idx++) {
            if (g_d_GameSettings.StadiumID == mapping_minigame_Stadium[idx]) {
                break;
            }
        }
        h->_24BD = 1;
        fieldersRunningToDugoutCalculateOffsets(resultsFielderMinigameOffsets[idx][3], resultsFielderMinigameOffsets[idx][0], resultsFielderMinigameOffsets[idx][2], &v.x, &v.z);
        v.y = resultsFielderMinigameOffsets[idx][1];
        h->_2294 = v.x + resultsFielderOffsets[0][0][0];
        h->_2298 = v.y + resultsFielderOffsets[0][0][1];
        h->_229C = v.z + resultsFielderOffsets[0][0][2];
        h->_2298 = -h->_2298;
        h->_22A4 = resultsFielderMinigameOffsets[idx][3];
        return;
    }

    k = 0;
    participants = g_Minigame.miniGameNumberOfParticipants;
    for (i = 0; i < 4; i++) {
        MinigameAnimObj *obj = hugeAnimStruct.objects[i];

        if (obj == NULL) {
            continue;
        }
        obj->_25D = 0;
        if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_POST_MENU) {
            if (pauseControl.state == 7) {
                continue;
            }
            if (g_GameLogic.framesOfExitingToMenu != 0) {
                continue;
            }
        }
        if (g_Minigame.playerSlots.characterIndex[k] != i) {
            continue;
        }
        if (g_Minigame.grandPrixFinalHumanCount == 1) {
            if (g_Minigame.playerSlots.characterIndex[i] != g_Minigame.soloPlayerSlot) {
                continue;
            }
            participants = 1;
        }
        obj->_25D = 1;
        fieldersRunningToDugoutCalculateOffsets(resultsFielderMinigameOffsets[g_Minigame.GameMode_MiniGame][3], resultsFielderMinigameOffsets[g_Minigame.GameMode_MiniGame][0],
                                                resultsFielderMinigameOffsets[g_Minigame.GameMode_MiniGame][2], &v.x, &v.z);
        v.y = resultsFielderMinigameOffsets[g_Minigame.GameMode_MiniGame][1];
        obj->_34 = v.x + resultsFielderOffsets[participants - 1][k][0];
        obj->_38 = v.y + resultsFielderOffsets[participants - 1][k][1];
        obj->_3C = v.z + resultsFielderOffsets[participants - 1][k][2];
        obj->_38 = -obj->_38;
        obj->_44 = resultsFielderMinigameOffsets[g_Minigame.GameMode_MiniGame][3];
        if (g_GameLogic.gameStatus == GAME_STATUS_0x27 || g_Minigame.grandPrixFinalInd != 0) {
            if (g_Minigame.grandPrixFinalHumanCount <= 1) {
            } else if (g_Minigame.playerSlots.rank[i] == 1) {
                obj->_3C += resultsFielderRowOffsets[0];
            } else {
                obj->_3C += resultsFielderRowOffsets[2];
            }
        } else if (tWon != FALSE) {
            if (g_Minigame.playerSlots.charID[i] == 0x26) {
                obj->_3C += resultsFielderRowOffsets[1];
            } else {
                obj->_3C += resultsFielderRowOffsets[0];
            }
        } else if (g_Minigame.playerSlots.rankCopy[i] == 1) {
            obj->_3C += resultsFielderRowOffsets[0];
        } else {
            obj->_3C += resultsFielderRowOffsets[2];
        }
        k++;
    }
}

// .text:0x000E0758 size:0x84
void toyFieldSetCoinScaleAndSpin(void) {
    MinigameModelRec *rec;
    int i;

    for (i = 0; i < 30; i++) {
        rec = &hugeAnimStruct.models[i];

        applyUniformScaleToObject(lbl_3_data_18D98[0], i);
        rec->_14 = shortAngleToRad_Capped((s16)(rand() % SANG_MAX_ANGLE));
    }
}

// .text:0x000E0668 size:0xF0
void toyFieldUpdateCoinModels(void) {
    MinigameModelRec *rec;
    int i;

    for (i = 0; i < 30; i++) {
        rec = &hugeAnimStruct.models[i];

        if (g_Minigame.coinState[i] == 0) {
            rec->_26 = FALSE;
        } else if (g_Minigame.coinFrameCounter[0] > lbl_3_data_18BB0[g_Minigame._199E * 2 + 1] &&
                   (g_Minigame.coinFrameCounter[0] & 1) != 0) {
            rec->_26 = FALSE;
        } else {
            rec->_26 = TRUE;
            rec->_04 = g_Minigame.coinPos[i].x;
            rec->_08 = -g_Minigame.coinPos[i].y;
            rec->_0C = g_Minigame.coinPos[i].z;
            rec->_14 = radianAngleReduction(rec->_14 + toyFieldCoinSpinStep);
        }
    }
}
