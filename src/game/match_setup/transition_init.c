#define SQRT2_LINKAGE static
#include "game/match_setup/transition_init.h"
#define REP_HEADER_DATA_FN getRepHeaderData_transitionInit
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

#define TRANSITION_OBJECT_COUNT 13

typedef struct TransitionObject {
    /*0x000*/ u8 _000[0x34];
    /*0x034*/ f32 x;
    /*0x038*/ f32 y;
    /*0x03C*/ f32 z;
    /*0x040*/ f32 _40;
    /*0x044*/ f32 _44;
    /*0x048*/ f32 _48;
    /*0x04C*/ u8 _04C[0x25D - 0x4C];
    /*0x25D*/ u8 _25D;
} TransitionObject;

typedef struct TransitionAnimView {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ TransitionObject* objects[TRANSITION_OBJECT_COUNT];
    /*0x2C84*/ u8 _2C84[0x2D68 - 0x2C84];
    /*0x2D68*/ s16 _2D68;
    /*0x2D6A*/ u8 _2D6A[0x307A - 0x2D6A];
    /*0x307A*/ u8 _307A;
    /*0x307B*/ u8 _307B[3];
    /*0x307E*/ u8 _307E;
} TransitionAnimView;

typedef struct TransitionScreenState {
    /*0x000*/ u8 _000[0x240];
    /*0x240*/ s16 _240[TRANSITION_OBJECT_COUNT];
    /*0x25A*/ u8 _25A[2];
    /*0x25C*/ u8 _25C;
    /*0x25D*/ u8 _25D[4];
    /*0x261*/ u8 _261[TRANSITION_OBJECT_COUNT];
    /*0x26E*/ u8 _26E[TRANSITION_OBJECT_COUNT];
} TransitionScreenState;

extern TransitionAnimView hugeAnimStruct;
extern TransitionScreenState* lbl_3_common_bss_1323C;
extern u8 animRelated[0x124];
extern f32 charSelectFielderPositions[3];

extern void clearAnimationRelatedPointers(void);
extern void resetAnimationFlags(void);
extern void resetAnimationFlags2(void);
extern void resetAnimRelatedPointer(void);
extern void ballAnimations(void);
extern void displayBallTrail(void);
extern void animateDefence(void);
extern void animateOffence(void);
extern void emptyFunction(void);
extern void animateShadows_nonBall(void);
extern void animateChargeSprites(void);
extern void animatePracticeScene(void);
extern void animateMatchScene(void);
extern void fn_3_6916C(void);
extern void fn_3_674E0(void);
extern void initAnimStruct(void);
extern void fn_3_B93C8(int arg);

// .text:0x0006C1D8 size:0x238 mapped:0x806AB26C
void graphicsFunction_nonMiniGame(void) {
    GameInitVariables* settings;
    u8 status;
    u8 mode;

    status = g_GameLogic.gameStatus;
    if (status == GAME_STATUS_LOAD_GAME) {
        return;
    }
    settings = &g_d_GameSettings;
    mode = settings->GameModeSelected;
    if (mode == GAME_TYPE_PRACTICE && g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU &&
        g_Practice.practiceType_1 == 6) {
        fn_3_6C000();
    } else if (status != GAME_STATUS_GAME_START_MOVIE && hugeAnimStruct._307A != 0) {
        if (lbl_3_common_bss_1323C->_25C != 0) {
            syncAnimObjectsToFieldersAndRunners();
        } else if (((u8)(status - GAME_STATUS_PAUSED) <= 1 ||
                    g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU ||
                    g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_LOAD_PRACTICE_SCREEN ||
                    (mode == GAME_TYPE_PRACTICE && g_Practice.tutorialState == 0)) &&
                   !(mode == GAME_TYPE_TOY_FIELD && status == GAME_STATUS_PAUSED)) {
            clearAnimationRelatedPointers();
            resetAnimationFlags();
            resetAnimationFlags2();
            resetAnimRelatedPointer();
            g_UnkSound_32718._07 = 0;
        } else {
            ballAnimations();
            displayBallTrail();
            animateDefence();
            animateOffence();
            emptyFunction();
            animateShadows_nonBall();
            animateChargeSprites();
        }
    }
    if (settings->GameModeSelected == GAME_TYPE_PRACTICE) {
        animatePracticeScene();
    } else {
        animateMatchScene();
    }
}

// .text:0x0006C150 size:0x88 mapped:0x806AB1E4
void fn_3_6C150(void) {
    *(s16*)&animRelated[0x9E] = -1;
    *(s16*)&animRelated[0xA0] = -1;
    *(s16*)&animRelated[0xA2] = -1;
    fn_3_6916C();
    fn_3_674E0();
    initAnimStruct();
    if (g_d_GameSettings.minigamesEnabled) {
        hugeAnimStruct._307E = 0;
    } else if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        hugeAnimStruct._307A = 1;
        hugeAnimStruct._307E = 1;
    }
}

// .text:0x0006C13C size:0x14 mapped:0x806AB1D0
void setInningEndingKIndTo0(void) {
    g_Scores._C3 = 0;
}

// .text:0x0006C108 size:0x34 mapped:0x806AB19C
void initializeSomethingDuringTransition2(void) {
    fn_3_B93C8(1);
    animRelated[0xAE] = 0;
}

// .text:0x0006C0E0 size:0x28 mapped:0x806AB174
void setDefaultPlayTrackingVariables2(void) {
    *(s16*)&animRelated[0x90] = -1;
    *(s16*)&animRelated[0x92] = 0;
    animRelated[0xA9] = 0;
    animRelated[0xD3] = 0;
    animRelated[0xB5] = 0;
}

// .text:0x0006C000 size:0xE0 mapped:0x806AB094
void fn_3_6C000(void) {
    int i;
    TransitionObject* obj;

    hugeAnimStruct._2D68 = -1;
    for (i = 0; i < TRANSITION_OBJECT_COUNT; i++) {
        if (hugeAnimStruct.objects[i] != NULL) {
            hugeAnimStruct.objects[i]->_25D = 0;
        }
    }
    if (g_Practice.practiceState != PRACTICE_STATE_6 && g_Practice.practiceState > PRACTICE_STATE_1) {
        obj = hugeAnimStruct.objects[9];
        if (obj != NULL && g_Minigame.charLoadPending[0] == 0 && (s8)g_Minigame.selectSlots[0].loadedCharID >= 0 && (s8)g_Minigame.selectSlots[0].charReadyInd != 0 &&
            (s8)g_Minigame.selectSlotState[0] >= 0) {
            obj->_25D = 1;
            obj->x = charSelectFielderPositions[0];
            obj->y = -charSelectFielderPositions[1];
            obj->z = charSelectFielderPositions[2];
            obj->_40 = 0.0f;
            obj->_44 = 0.0f;
            obj->_48 = 0.0f;
        }
    }
}

// .text:0x0006BEA4 size:0x15C mapped:0x806AAF38
void syncAnimObjectsToFieldersAndRunners(void) {
    int i;
    TransitionObject* obj;
    InMemRunnerType* runner;

    clearAnimationRelatedPointers();
    resetAnimationFlags();
    resetAnimationFlags2();
    g_UnkSound_32718._07 = 0;
    for (i = 0; i < TRANSITION_OBJECT_COUNT; i++) {
        if (lbl_3_common_bss_1323C->_240[i] < 0) {
            continue;
        }
        obj = hugeAnimStruct.objects[i];
        if (obj == NULL) {
            continue;
        }
        obj->_25D = lbl_3_common_bss_1323C->_261[i];
        if (i <= 8) {
            lbl_3_common_bss_1323C->_26E[i] = 0;
            if (g_Fielders[i].rosterLocation != -1) {
                obj->x = g_Fielders[i].pos.x;
                obj->y = g_Fielders[i].pos.y;
                obj->z = g_Fielders[i].pos.z;
                obj->_44 = g_Fielders[i].desiredMovementDirection;
            }
        } else if (i <= 12) {
            runner = &g_Runners[i - 9];
            lbl_3_common_bss_1323C->_26E[i] = 0;
            if (runner->rosterID != -1) {
                obj->x = runner->position.x;
                obj->y = runner->position.y;
                obj->z = runner->position.z;
                obj->_44 = runner->runningAngle;
            }
        }
        obj->_40 = 0.0f;
        obj->_48 = 0.0f;
    }
}
