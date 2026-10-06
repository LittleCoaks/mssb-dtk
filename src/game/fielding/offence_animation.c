#include "game/fielding/offence_animation.h"
#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_offenceAnimation
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

typedef struct OffenceAnimObject {
    u8 _000[0x34];
    VecXYZ position;
    f32 zeroA;
    f32 orientation;
    f32 zeroB;
    u8 _04C[0x252 - 0x04C];
    s8 animation;
    u8 _253[0x25D - 0x253];
    u8 displayState;
    u8 _25E[0x275 - 0x25E];
    u8 terrain;
    u8 _276[0x278 - 0x276];
    u8 firstRunner;
} OffenceAnimObject;

typedef struct OffenceAnimView {
    u8 _0000[0x2C50];
    OffenceAnimObject* objects[13];
    u8 _2C84[0x2D77 - 0x2C84];
    u8 hideRunners;
} OffenceAnimView;

extern OffenceAnimView hugeAnimStruct;
extern u8 lbl_3_data_6EF0[8];
extern u8* lbl_3_common_bss_1323C;
static const f32 lbl_3_rodata_10E0[2] = { 0.0f, 0.0f };
extern void resetAnimationRelatedPointers(void);
extern void AnimBlr(void);
extern void fn_3_E07DC(void);
extern BOOL fn_8004ACDC(BOOL flag);
extern BOOL fn_8004ACC4(BOOL flag);
extern void fn_3_6A254(void);
extern void fn_3_6A2A4(s8 animation);

// .text:0x0006C4D0 size:0x384 mapped:0x806AB564
void animateOffence(void) {
    OffenceAnimObject* obj;
    int i;
    InMemRunnerType* runner;
    E(u8, GAME_STATUS) status;

    if (hugeAnimStruct.hideRunners != FALSE) {
        for (i = 0; i < 4; i++) {
            obj = hugeAnimStruct.objects[i + 9];
            if (obj != NULL) {
                obj->displayState = FALSE;
            }
        }
        resetAnimationRelatedPointers();
        AnimBlr();
        return;
    }

    status = g_GameLogic.gameStatus;
    if (status != GAME_STATUS_DEFAULT && status != GAME_STATUS_AT_BAT &&
        status != GAME_STATUS_LIVE_BALL && status != GAME_STATUS_TRANSITION &&
        status != GAME_STATUS_STAR_CHANCE_VS) {
        for (i = 0; i < 4; i++) {
            obj = hugeAnimStruct.objects[i + 9];
            if (obj != NULL) {
                obj->displayState = FALSE;
            }
        }
        resetAnimationRelatedPointers();
        AnimBlr();
        if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME) {
            fn_3_E07DC();
        }
        return;
    }

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_PITCHING) {
        for (i = 0; i < 4; i++) {
            obj = hugeAnimStruct.objects[i + 9];
            if (obj != NULL) {
                obj->displayState = FALSE;
            }
        }
        resetAnimationRelatedPointers();
        AnimBlr();
        return;
    }

    for (i = 0; i < 4; i++) {
        OffenceAnimObject* runnerObj = hugeAnimStruct.objects[i + 9];
        runner = &g_Runners[i];
        if (runnerObj == NULL) {
            continue;
        }
        runnerObj->terrain = runner->someCollisionCheck;
        if (i == 0) {
            runnerObj->firstRunner = TRUE;
        }
        if (runner->runningToDugoutStage == 3) {
            runnerObj->displayState = FALSE;
            continue;
        }
        if (i == 0 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) {
            s8 animation = runnerObj->animation;
            if (animation == 0x26) {
                if (fn_8004ACDC(TRUE)) {
                    fn_3_6A254();
                }
            } else if ((u8)(animation - 0x30) <= 2 || animation == 0x33) {
                runnerObj->displayState = 2;
                if (fn_8004ACC4(TRUE)) {
                    fn_3_6A2A4(runnerObj->animation);
                }
                continue;
            }
        }
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_NONE || runner->rosterID < 0) {
            runnerObj->displayState = FALSE;
        } else if (runner->runningToDugoutStage == 3) {
            runnerObj->displayState = FALSE;
        } else {
            runnerObj->displayState = TRUE;
            runnerObj->position.x = runner->position.x;
            runnerObj->position.y = runner->position.y;
            runnerObj->position.z = runner->position.z;
            runnerObj->zeroA = lbl_3_rodata_10E0[0];
            runnerObj->orientation = runner->runningAngle;
            runnerObj->zeroB = lbl_3_rodata_10E0[0];
        }
        if (g_Stats.replayInd != FALSE) {
            runnerObj->displayState = lbl_3_common_bss_1323C[i + 0x261];
        } else if (lbl_3_data_6EF0[i] != FALSE && g_GameLogic.sceneID != SCENE_ID_REPLAY_AT_BAT &&
                   g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_PRACTICE_BASERUNNING &&
                   (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT ||
                    g_GameLogic.gameStatus == GAME_STATUS_DEFAULT ||
                    g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY ||
                    g_GameLogic.sceneID == SCENE_ID_AT_BAT)) {
            runnerObj->displayState = FALSE;
        }
    }
}
