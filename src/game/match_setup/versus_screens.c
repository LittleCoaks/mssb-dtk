#define SQRT2_LINKAGE static
#include "game/match_setup/versus_screens.h"
#include "header_rep_data.h"

#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800b0a14.h"
#include "game/ball/ball_physics.h"
#include "game/pitching/pitcher.h"
#include "game/batting/batter.h"
#include "game/baserunning/runner.h"
#include "game/fielding/fielder.h"
#include "game/match_setup/ai_defaults.h"
#include "game/math/game_math.h"
#include "Dolphin/mtx.h"
#include "stl/math.h"
#include "stl/string.h"
#include "stl/stdlib.h"

#define VS_SITUATION_COUNT 33
#define VS_SCREEN_ENTRY_COUNT 13
#define CHARACTER_COUNT 55

extern void SetGameStatus(GAME_STATUS status);
extern BOOL checkForButtonPressToSkip(int a, int b);
extern void fn_8001D074(int index, int enable);
extern void resetAndRunAnimations(int arg);
extern void fn_3_8C104(int arg);
extern int fn_3_6B4C8(void);
extern void fn_3_147DFC(void);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void fn_3_21AA8(void);
extern void setScissorMode(int mode);
extern void transitionToReplay(void);
extern void replaceGameStructs_postReplay(int arg);
extern u32 playCharacterSound(int charID, int soundCode);
extern BOOL decideScoutFlagMission(void);

extern s8 lbl_803C6CF8[0x708];
extern u8 lbl_8037169C[0x1C];
extern u8 animRelated[0x124];
extern u8 characterStaticIndexes[0x144];
extern s16 lbl_3_data_7F7C[][4];
typedef struct VsScoutMission {
    /*0x00*/ u8 _00[0xD];
    /*0x0D*/ s8 starMission;
    /*0x0E*/ u8 _0E;
} VsScoutMission; // size: 0xF

extern VsScoutMission scoutMissionTable[13];

extern s32 lbl_3_data_1F74[VS_SITUATION_COUNT];
extern s32 lbl_3_data_2368[6];
extern s32 lbl_3_data_2380[6];
extern s32 homerun_cameraSceneIDs[CHARACTER_COUNT];

// One evaluated vsSituations row: the game state it requires (-1 = don't care) and the flags it
// records once chosen.
typedef struct VsSituation {
    /*0x00*/ s32 inningPhase;
    /*0x04*/ s32 _04;
    /*0x08*/ s32 outs;
    /*0x0C*/ s32 runnerOnFirst;
    /*0x10*/ s32 runnerOnSecond;
    /*0x14*/ s32 runnerOnThird;
    /*0x18*/ s32 leadRequirement;
    /*0x1C*/ s32 scoreOrder;
    /*0x20*/ s32 captainMatchup;
    /*0x24*/ s32 _24;
    /*0x28*/ s32 _28;
    /*0x2C*/ s32 _2C;
    /*0x30*/ s32 _30;
    /*0x34*/ s32 _34;
    /*0x38*/ s32 _38;
    /*0x3C*/ s32 _3C;
} VsSituation; // size: 0x40

extern VsSituation vsSituations[VS_SITUATION_COUNT];

// The block of .data that starts at lbl_3_data_1D28, seen as one object.
typedef struct VsData {
    /*0x000*/ u8 _000[0x228];
    /*0x228*/ s8 situationLocked[0x24];
    /*0x24C*/ u8 _24C[0x2D0 - 0x24C];
    /*0x2D0*/ s32 homeRunCameraSceneIDs0[CHARACTER_COUNT];
    /*0x3AC*/ s32 homeRunCameraSceneIDs1[CHARACTER_COUNT];
    /*0x488*/ s32 homeRunCameraSceneIDs2[CHARACTER_COUNT];
    /*0x564*/ s32 homeRunCameraSceneIDs3[CHARACTER_COUNT];
    /*0x640*/ u8 _640[0x670 - 0x640];
    /*0x670*/ VsSituation situations[VS_SITUATION_COUNT];
    /*0xEB0*/ u8 matchupTable[CHARACTER_COUNT][CHARACTER_COUNT];
} VsData;

extern VsData lbl_3_data_1D28;

typedef struct VsScreenEntry {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ f32 angle;
    /*0x10*/ f32 targetAngle;
    /*0x14*/ f32 offset;
    /*0x18*/ f32 _18;
    /*0x1C*/ f32 radius;
    /*0x20*/ u8 _20[8];
    /*0x28*/ u8 done;
    /*0x29*/ u8 active;
    /*0x2A*/ u8 _2A[2];
} VsScreenEntry; // size: 0x2C

typedef struct VsScreenState {
    /*0x000*/ VsScreenEntry entries[VS_SCREEN_ENTRY_COUNT];
    /*0x23C*/ s16 frame;
    /*0x23E*/ s16 endFrame;
    /*0x240*/ s16 _240[VS_SCREEN_ENTRY_COUNT];
    /*0x25A*/ s16 _25A;
    /*0x25C*/ u8 _25C;
    /*0x25D*/ u8 _25D;
    /*0x25E*/ u8 _25E;
    /*0x25F*/ u8 _25F;
    /*0x260*/ s8 situation;
    /*0x261*/ u8 _261[VS_SCREEN_ENTRY_COUNT];
    /*0x26E*/ u8 _26E[VS_SCREEN_ENTRY_COUNT];
    /*0x27B*/ s8 _27B;
    /*0x27C*/ s8 _27C;
    /*0x27D*/ u8 _27D;
    /*0x27E*/ u8 _27E;
    /*0x27F*/ s8 _27F;
    /*0x280*/ s8 _280;
} VsScreenState;

extern VsScreenState *lbl_3_common_bss_1323C;

typedef struct VsAnimObject {
    /*0x00*/ u8 _00[0x62];
    /*0x62*/ s16 _62;
    /*0x64*/ s16 _64;
    /*0x66*/ s16 _66;
    /*0x68*/ s16 _68;
    /*0x6A*/ s16 _6A;
} VsAnimObject;

extern struct {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ VsAnimObject *objects[VS_SCREEN_ENTRY_COUNT];
} hugeAnimStruct;

typedef struct VsFadeItem {
    /*0x00*/ u8 _00[0x1E];
    /*0x1E*/ u16 frame;
    /*0x20*/ u16 alpha;
    /*0x22*/ s16 _22;
} VsFadeItem;

typedef struct VsFadeParams {
    /*0x00*/ f32 _00;
    /*0x04*/ u8 _04[0x10];
    /*0x14*/ s16 _14;
    /*0x16*/ u8 _16;
    /*0x17*/ u8 _17;
    /*0x18*/ u8 _18;
    /*0x19*/ u8 _19;
    /*0x1A*/ u8 _1A;
    /*0x1B*/ u8 _1B;
    /*0x1C*/ u8 _1C;
    /*0x1D*/ u8 _1D;
} VsFadeParams;

extern VsFadeParams lbl_803C5090;

typedef struct VsScoutState {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ s16 humanTeam;
    /*0x42*/ u8 _42[4];
    /*0x46*/ u8 scoutMissionID;
} VsScoutState;

extern VsScoutState lbl_3_common_bss_37400;

s32 lbl_3_data_3A40[55] = {
    0x78, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76,
    0x76, 0x76, 0x79, 0x76, 0x76, 0x76, 0x76, 0x76,
    0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76,
    0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76,
    0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76,
    0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76,
    0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76,
};

s32 lbl_3_data_3B1C[6] = {
    0x11C, 0x11D, 0x11E, 0x11A, 0x11F, 0x11B,
};

s32 lbl_3_data_3B34[6] = {
    0x11C, 0x11D, 0x11E, 0x11A, 0x11F, 0x11B,
};

s32 lbl_3_data_3B4C[54] = {
    0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9,
    0x9, 0x4E, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9,
    0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9,
    0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9,
    0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x34, 0x9,
    0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9,
    0x9, 0x9, 0x9, 0x9, 0x9, 0x9,
};

static struct {
    s32 state;
    u8 _04[0x24];
} lbl_3_bss_A0;
static s32 lbl_3_bss_9C;
static s32 pad_05_00000098_bss;

static inline void vsScreenAdvanceFrame(void) {
    VsScreenState *state = lbl_3_common_bss_1323C;

    if (state->frame < 0x7FFE) {
        state->frame++;
    } else {
        state->frame = 0x7FFF;
    }
}

static inline void vsScreenBegin(int mode) {
    s32 i;

    for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
        lbl_3_common_bss_1323C->_240[i] = -1;
        memset(&lbl_3_common_bss_1323C->entries[i], 0, sizeof(VsScreenEntry));
        lbl_3_common_bss_1323C->_261[i] = 0;
    }
    resetAndRunAnimations(0);
    lbl_3_common_bss_1323C->_25C = 1;
    lbl_3_common_bss_1323C->frame = 0;
    lbl_3_common_bss_1323C->_27C = 0;
    lbl_3_common_bss_1323C->_25D = mode;
    lbl_3_common_bss_1323C->_25F = 1;
    lbl_3_common_bss_1323C->_27D = 0;
    lbl_3_common_bss_1323C->_27E = 0;
    lbl_3_common_bss_1323C->_25A = 0;
    lbl_3_common_bss_1323C->_280 = 1;
}

// .text:0x00024708 size:0x2E0 mapped:0x8066379C
void fn_3_24708(void) {
    VsAnimObject *obj;
    InMemRunnerType *runner;
    s32 i;

    for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
        f32 dist;

        obj = hugeAnimStruct.objects[i];

        if (obj == NULL) {
            continue;
        }
        if (lbl_3_common_bss_1323C->entries[i].active != 1) {
            continue;
        }
        if (lbl_3_common_bss_1323C->_27F == 3 && lbl_3_common_bss_1323C->entries[i].radius > (f32)obj->_68) {
        } else if (i <= 8) {
            dist = PSVECDistance((Vec *)&g_Fielders[i], (Vec *)&lbl_3_common_bss_1323C->entries[i]);
        } else if (i <= 12) {
            Mtx m;
            Vec v;
            f32 diff;

            runner = &g_Runners[i - 9];
            lbl_3_common_bss_1323C->entries[i].targetAngle =
                ATAN2F(-(lbl_3_common_bss_1323C->entries[i].pos.x - runner->position.x),
                       -(lbl_3_common_bss_1323C->entries[i].pos.z - runner->position.z));
            PSMTXRotRad(m, 'Y', lbl_3_common_bss_1323C->entries[i].angle);
            v.x = 0.0f;
            v.y = 0.0f;
            v.z = lbl_3_common_bss_1323C->entries[i].offset;
            PSMTXMultVec(m, &v, &v);
            runner->position.x = runner->position.x - v.x;
            runner->position.z = runner->position.z - v.z;
            diff = radianAngleReduction(lbl_3_common_bss_1323C->entries[i].angle - lbl_3_common_bss_1323C->entries[i].targetAngle);
            if ((diff < 0.02 && diff > 0.0f) || (diff > -0.02 && diff < 0.0f)) {
            } else if (diff < 0.0f) {
                lbl_3_common_bss_1323C->entries[i].angle += 0.017453292f;
            } else {
                lbl_3_common_bss_1323C->entries[i].angle -= 0.017453292f;
            }
            runner->runningAngle = lbl_3_common_bss_1323C->entries[i].angle;
            dist = PSVECDistance((Vec *)runner, (Vec *)&lbl_3_common_bss_1323C->entries[i]);
        }

        if (lbl_3_common_bss_1323C->_27F == 3) {
            if (obj->_68 == 0) {
                lbl_3_common_bss_1323C->entries[i].done = 1;
                lbl_3_common_bss_1323C->entries[i].active = 0;
            }
        } else if (dist < 3.0f) {
            lbl_3_common_bss_1323C->entries[i].done = 1;
            lbl_3_common_bss_1323C->entries[i].active = 0;
        }
    }
}

// .text:0x00024630 size:0xD8 mapped:0x806636C4
void fn_3_24630(void) {
    s32 i;

    setScissorMode(1);
    for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
        lbl_3_common_bss_1323C->_261[i] = 0;
    }
    lbl_3_common_bss_1323C->_25C = 0;
}

// .text:0x00024598 size:0x98 mapped:0x8066362C
void fn_3_24598(void) {
    vsScreenAdvanceFrame();
    if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame - 7) {
        changeScene(3, 6);
    }
    if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame) {
        g_GameLogic._125 = g_GameLogic._125 + 1;
    }
}

// .text:0x000240F8 size:0x4A0 mapped:0x8066318C
void postReplayBatterCelebration(void) {
    VsData *data = &lbl_3_data_1D28;
    GameInitVariables *settings = &g_d_GameSettings;
    s32 i;

    switch (g_GameLogic._125) {
    case 0:
        if (lbl_803C6CF8[0x715] == 1) {
            *(s16 *)((u8 *)g_pCamera + 0xAAA) = 1;
            *(s16 *)((u8 *)g_pCamera + 0xAAE) = 2;
            insertGraphicDrawingFunction(fn_3_21DE4, 6);
            g_GameLogic._125 = 1;
        }
        break;
    case 1:
        changeScene(1, 6);
        vsScreenBegin(5);
        if (g_Runners[0].baseStandingOn == 1) {
            camera_switchScene(data->homeRunCameraSceneIDs1[g_Runners[0].charID]);
        } else if (g_Runners[0].baseStandingOn == 2) {
            camera_switchScene(data->homeRunCameraSceneIDs2[g_Runners[0].charID]);
        } else if (g_Runners[0].baseStandingOn == 3) {
            camera_switchScene(data->homeRunCameraSceneIDs3[g_Runners[0].charID]);
        } else {
            camera_switchScene(data->homeRunCameraSceneIDs1[g_Runners[0].charID]);
        }
        g_GameLogic._125 = 2;
        break;
    case 2:
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 3;
    case 3:
        fn_3_24708();
        vsScreenAdvanceFrame();
        if (checkForButtonPressToSkip(1, 0x1100) && lbl_3_common_bss_1323C->frame < lbl_3_common_bss_1323C->endFrame - 8 &&
            settings->GameModeSelected != GAME_TYPE_DEMO) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x3C) {
                lbl_3_common_bss_1323C->_27C = 1;
                lbl_3_common_bss_1323C->frame = lbl_3_common_bss_1323C->endFrame - 8;
                changeScene(3, 6);
            }
        } else if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame - 7) {
            changeScene(3, 6);
        }
        if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame) {
            g_GameLogic._125 = 5;
        }
        for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
            if (i == 0 || i == 1 || i == 9) {
                fn_8001D074(i, 1);
            } else {
                fn_8001D074(i, 0);
            }
        }
        break;
    case 5:
        fn_3_24630();
        fn_3_FBD70();
        fn_3_FBD58();
        replaceGameStructs_postReplay(1);
        for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
            fn_8001D074(i, 1);
        }
        break;
    }

    if (hugeAnimStruct.objects[9]->_62 == 0x3A) {
        if (hugeAnimStruct.objects[9]->_6A == lbl_3_data_7F7C[characterStaticIndexes[g_Batter.charID * 6 + 2]][2]) {
            playCharacterSound(g_Batter.charID, 0);
        }
    }
}

// .text:0x00023CEC size:0x40C mapped:0x80662D80
void homeRunEnd(void) {
    GameInitVariables *settings = &g_d_GameSettings;
    s32 i;

    switch (g_GameLogic._125) {
    case 0:
        if (lbl_803C6CF8[0x715] == 1) {
            changeScene(1, 6);
            g_GameLogic._125 = 1;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        }
        break;
    case 1:
        vsScreenBegin(3);
        camera_switchScene(homerun_cameraSceneIDs[g_Runners[0].charID]);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 2;
        break;
    case 2:
        fn_3_24708();
        vsScreenAdvanceFrame();
        if (checkForButtonPressToSkip(1, 0x1100) && lbl_3_common_bss_1323C->frame < lbl_3_common_bss_1323C->endFrame - 7 &&
            settings->GameModeSelected != GAME_TYPE_DEMO) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x3C) {
                lbl_3_common_bss_1323C->_27C = 1;
                lbl_3_common_bss_1323C->frame = lbl_3_common_bss_1323C->endFrame - 8;
                changeScene(3, 6);
            }
        } else if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame - 7) {
            changeScene(3, 6);
        }
        if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame) {
            g_GameLogic._125 = 4;
        }
        for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
            if (i == 0 || i == 1 || i == 9) {
                fn_8001D074(i, 1);
            } else {
                fn_8001D074(i, 0);
            }
        }
        break;
    case 4:
        fn_3_24630();
        fn_3_FBD70();
        fn_3_FBD58();
        replaceGameStructs_postReplay(1);
        for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
            fn_8001D074(i, 1);
        }
        break;
    }

    if (hugeAnimStruct.objects[9]->_62 == 0x3C) {
        if (hugeAnimStruct.objects[9]->_6A == lbl_3_data_7F7C[characterStaticIndexes[g_Batter.charID * 6 + 2]][0]) {
            playCharacterSound(g_Batter.charID, 0);
        }
    }
}

// .text:0x00023890 size:0x45C mapped:0x80662924
void homeRunTrot(void) {
    DrawingSceneStruct *cur = currentDrawingItem;
    GameInitVariables *settings = &g_d_GameSettings;
    s32 i;

    switch (g_GameLogic._125) {
    case 0:
        if (lbl_803C6CF8[0x715] == 1) {
            *(s16 *)((u8 *)g_pCamera + 0xAAA) = 1;
            *(s16 *)((u8 *)g_pCamera + 0xAAE) = 2;
            insertGraphicDrawingFunction(fn_3_21DE4, 6);
            g_GameLogic._125 = 1;
        }
        break;
    case 1:
        vsScreenBegin(4);
        camera_switchScene(0x4C);
        g_GameLogic._125 = 2;
        break;
    case 2: {
        VsFadeItem *item;

        changeScene(1, 6);
        lbl_3_common_bss_1323C->_27E = 1;
        item = (VsFadeItem *)insertGraphicDrawingFunction(fn_3_21AA8, 4);
        cur->state = 0;
        item->_22 = 0;
        item->frame = 0;
        g_GameLogic._125 = 3;
        break;
    }
    case 3:
        fn_3_24708();
        vsScreenAdvanceFrame();
        if (checkForButtonPressToSkip(1, 0x1100)) {
            if (lbl_3_common_bss_1323C->frame < lbl_3_common_bss_1323C->endFrame - 0x1F && settings->GameModeSelected != GAME_TYPE_DEMO &&
                g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x3C && animRelated[0xB1] == 0) {
                lbl_3_common_bss_1323C->_27C = 1;
                lbl_3_common_bss_1323C->frame = lbl_3_common_bss_1323C->endFrame - 0x1F;
            }
        }
        if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame - 0x1F) {
            animRelated[0xB1] = 1;
        }
        if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame) {
            g_GameLogic._125 = 5;
        }
        for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
            if (i == 0 || i == 1 || i == 9) {
                fn_8001D074(i, 1);
            } else {
                fn_8001D074(i, 0);
            }
        }
        break;
    case 4:
        break;
    case 5:
        lbl_3_common_bss_1323C->_27E = 0;
        fn_3_24630();
        fn_3_FBD70();
        fn_3_FBD58();
        g_GameLogic._125 = 6;
        break;
    case 6:
        for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
            fn_8001D074(i, 1);
        }
        transitionToReplay();
        if (lbl_3_common_bss_1323C->_27C != 0) {
            SetGameStatus(g_GameLogic.gameStatus_prev);
            *((u8 *)&g_Stats + 0x39) = 2;
        } else {
            SetGameStatus(g_GameLogic.gameStatus_prev);
            *((u8 *)&g_Stats + 0x39) = 2;
        }
        break;
    }
}

// .text:0x000234BC size:0x3D4 mapped:0x80662550
void starChanceVsScreenProcess(void) {
    GameInitVariables *settings = &g_d_GameSettings;
    s32 i;

    switch (g_GameLogic._125) {
    case 0:
        if (lbl_803C6CF8[0x715] == 1) {
            if (g_GameLogic.playOverInd == 0 && maybeSetVsIndOrScoutFlagChance() == 0) {
                lbl_3_common_bss_1323C->_25C = 0;
                changeScene(1, 6);
                fn_3_FBD58();
                SetGameStatus(GAME_STATUS_DEFAULT);
            } else {
                setDefaultInMemBall();
                setDefaultInMemPitcher();
                setDefaultInMemBatter();
                setDefaultInMemRunner();
                setDefaultInMemFielder();
                setDefaultAIValues();
                g_Pitcher.playStartOfGameAnimation = 0;
                g_GameLogic.scoutFlag_VsScreenInd = 1;
                g_GameLogic._125 = 1;
            }
        }
        break;
    case 1:
        vsScreenBegin(0);
        if (g_GameLogic.playOverInd == 1) {
            camera_switchScene(0x6A);
        } else {
            camera_switchScene(lbl_3_data_1F74[lbl_3_common_bss_1323C->situation]);
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 2;
        break;
    case 2:
        fn_3_24708();
        if (lbl_3_common_bss_1323C->frame == 9) {
            changeScene(1, 6);
        }
        vsScreenAdvanceFrame();
        for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
            fn_8001D074(i, 1);
        }
        if (checkForButtonPressToSkip(1, 0x1100)) {
            if (lbl_3_common_bss_1323C->frame < lbl_3_common_bss_1323C->endFrame - 7 && settings->GameModeSelected != GAME_TYPE_DEMO &&
                g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x3C) {
                lbl_3_common_bss_1323C->frame = lbl_3_common_bss_1323C->endFrame - 8;
                changeScene(3, 6);
            }
        }
        if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame) {
            g_GameLogic._125 = 3;
        }
        break;
    case 3:
        fn_3_24630();
        fn_3_FBD70();
        fn_3_FBD58();
        SetGameStatus(GAME_STATUS_DEFAULT);
        break;
    }
}

// .text:0x000230D4 size:0x3E8 mapped:0x80662168
void fn_3_230D4(void) {
    GameInitVariables *settings = &g_d_GameSettings;
    s32 i;

    switch (g_GameLogic._125) {
    case 0:
        if (lbl_803C6CF8[0x715] == 1) {
            changeScene(1, 6);
            fn_3_24630();
            fn_3_FBD70();
            fn_3_FBD58();
            SetGameStatus(GAME_STATUS_DEFAULT);
        }
        break;
    case 1:
        changeScene(1, 6);
        vsScreenBegin(1);
        camera_switchScene(0x6B);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 2;
        break;
    case 2:
        if (lbl_3_common_bss_1323C->frame == 9) {
            changeScene(1, 6);
        }
        vsScreenAdvanceFrame();
        for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
            fn_8001D074(i, 1);
        }
        if (checkForButtonPressToSkip(1, 0x1100)) {
            if (lbl_3_common_bss_1323C->frame < lbl_3_common_bss_1323C->endFrame - 7 && settings->GameModeSelected != GAME_TYPE_DEMO &&
                g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x3C) {
                lbl_3_common_bss_1323C->frame = lbl_3_common_bss_1323C->endFrame - 8;
                changeScene(3, 6);
            }
        }
        if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame) {
            fn_3_24630();
            fn_3_FBD70();
            fn_3_FBD58();
            SetGameStatus(GAME_STATUS_DEFAULT);
        }
        break;
    }
}

// .text:0x00022C20 size:0x4B4 mapped:0x80661CB4
void championshipScreen(void) {
    GameInitVariables *settings = &g_d_GameSettings;
    StoredInningInfo *inning = &storedInningInfo;
    s32 i;

    switch (g_GameLogic._125) {
    case 0:
        if (lbl_803C6CF8[0x715] == 1) {
            fn_3_147DFC();
            animRelated[0x9A] = 0;
            g_GameLogic._125 = 1;
        }
        break;
    case 1:
        if (fn_3_6B4C8()) {
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        fn_3_8C104(-1);
        vsScreenBegin(2);
        {
            u8 *tracker = (u8 *)starMissionCompletionTracker;

            if (inning->goAheadRunOccurrences != 0) {
                camera_switchScene(lbl_3_data_2368[tracker[0x441C]]);
            } else {
                camera_switchScene(lbl_3_data_2380[tracker[0x441C]]);
            }
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 3;
        break;
    case 3:
        if (lbl_3_common_bss_1323C->frame == 9) {
            changeScene(1, 0x5A);
        }
        vsScreenAdvanceFrame();
        for (i = 0; i < VS_SCREEN_ENTRY_COUNT; i++) {
            fn_8001D074(i, 1);
        }
        if (checkForButtonPressToSkip(1, 0x1100) && lbl_3_common_bss_1323C->frame < lbl_3_common_bss_1323C->endFrame - 0x5B &&
            settings->GameModeSelected != GAME_TYPE_DEMO) {
            if (lbl_3_common_bss_1323C->_280 == 1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x3C) {
                lbl_3_common_bss_1323C->frame = lbl_3_common_bss_1323C->endFrame - 0x5C;
                changeScene(3, 0x5A);
                sound_crowd_EffectsStruct._2A = 1;
                sound_crowd_EffectsStruct._24 = 0x5A;
            }
        } else if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame - 0x5B) {
            changeScene(3, 0x5A);
            sound_crowd_EffectsStruct._2A = 1;
            sound_crowd_EffectsStruct._24 = 0x5A;
        }
        if (lbl_3_common_bss_1323C->frame == lbl_3_common_bss_1323C->endFrame) {
            g_GameLogic._125 = 4;
        }
        break;
    case 4:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_24630();
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 5;
        }
        break;
    case 5:
        g_GameLogic.exitingToMenu = 1;
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }

    {
        int team = lbl_3_common_bss_37400.humanTeam;
        int charID = inMemRoster[team][g_GameLogic.Team_CaptainRosterLoc[team]].stats.CharID;

        if (lbl_3_common_bss_1323C->frame == lbl_3_data_7F7C[characterStaticIndexes[charID * 6 + 2]][3]) {
            playCharacterSound(charID, 7);
        }
    }
}

// .text:0x00022C10 size:0x10 mapped:0x80661CA4
void versusScreen_seemsToDoNothing(void) {
    s32 i;

    for (i = 13; i != 0; i--) {
    }
}

// .text:0x00022ABC size:0x154 mapped:0x80661B50
int fn_3_22ABC(void) {
    GameScoresControlsStruct *scores = &g_Scores;
    BOOL trailing = FALSE;
    int runners;
    int lead;

    runners = 0;
    if (g_Runners[1].rosterID != -1) {
        runners = 1;
    }
    if (g_Runners[2].rosterID != -1) {
        runners++;
    }
    if (g_Runners[3].rosterID != -1) {
        runners++;
    }
    lead = scores->_A6;
    if (ABS(lead) <= 4 && runners == 3) {
        if (scores->scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total <=
            scores->scores[g_GameLogic.awayTeamBattingInd_battingTeam].total) {
            trailing = TRUE;
        }
    }

    runners = 0;
    if (g_Runners[2].rosterID != -1) {
        runners = 1;
    }
    if (g_Runners[3].rosterID != -1) {
        runners++;
    }
    lead = scores->_A6;
    if (ABS(lead) <= runners && runners > 0) {
        if (scores->scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total <=
            scores->scores[g_GameLogic.awayTeamBattingInd_battingTeam].total) {
            trailing = TRUE;
        }
    }

    if (trailing) {
        return g_Batter.aiControlledInd != 0 ? 1 : 2;
    }
    return -1;
}

// .text:0x00022A20 size:0x9C mapped:0x80661AB4
BOOL fn_3_22A20(void) {
    if (g_Batter.aiControlledInd != 0) {
        return g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total >=
               g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
    } else {
        return g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total <
               g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
    }
}

// .text:0x00022948 size:0xD8 mapped:0x806619DC
void fn_3_22948(void) {
    s32 i;

    for (i = 0; i < VS_SITUATION_COUNT; i++) {
        vsSituations[i]._34 = 0;
        vsSituations[i]._38 = 0;
        vsSituations[i]._3C = 0;
    }
    lbl_3_common_bss_1323C->_27B = 0;
}

// .text:0x00022944 size:0x4 mapped:0x806619D8
void fn_3_22944(void) {
    return;
}

// .text:0x00022850 size:0xF4 mapped:0x806618E4
void resetSomethingRelatedToVersus(void) {
    s32 i;

    for (i = 0; i < VS_SITUATION_COUNT; i++) {
        vsSituations[i]._38 = 0;
        vsSituations[i]._3C = 0;
    }
    lbl_3_common_bss_1323C->_27B = 0;
}

// .text:0x0002281C size:0x34 mapped:0x806618B0
BOOL fn_3_2281C(int index) {
    if (hugeAnimStruct.objects[index] == NULL) {
        return TRUE;
    }
    return hugeAnimStruct.objects[index]->_68 == 0;
}

// .text:0x0002273C size:0xE0 mapped:0x806617D0
BOOL fn_3_2273C(void) {
    s32 i;

    for (i = 0; i < 9; i++) {
        if (g_Fielders[i].rosterLocSkippingCap == 0) {
            if (hugeAnimStruct.objects[i] == NULL) {
                return TRUE;
            }
            if (hugeAnimStruct.objects[i]->_68 == 0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

// .text:0x00021F14 size:0x828 mapped:0x80660FA8
BOOL maybeSetVsIndOrScoutFlagChance(void) {
    GameInitVariables *settings = &g_d_GameSettings;
    VsData *data = &lbl_3_data_1D28;
    u8 *tracker = (u8 *)starMissionCompletionTracker;
    VsScoutState *scout = &lbl_3_common_bss_37400;
    VsScoutMission *scoutMissions = scoutMissionTable;
    BOOL scoutMission = FALSE;
    s32 i;

    if (settings->exhibitionMatchInd == 0) {
        if (tracker[0x441E] == 5 ||
            *(s16 *)(tracker + 0x16C2) == 0x2A) {
            scoutMission = FALSE;
        } else {
            scoutMission = decideScoutFlagMission();
        }
    }

    if (settings->exhibitionMatchInd == 0) {
        if (scoutMission) {
            if (scoutMissions[scout->scoutMissionID].starMission != 0) {
                lbl_3_common_bss_1323C->situation = 0x1C;
                tracker[0x44F1] = 0;
                return TRUE;
            }
        }
        return FALSE;
    }

    lbl_3_common_bss_1323C->situation = -1;
    for (i = 0; i < VS_SITUATION_COUNT; i++) {
        VsSituation *s;
        BOOL ok;
        int result;

        if (i == 45) {
            i = 45;
        }
        s = &data->situations[i];
        ok = TRUE;

        if (g_Scores._pad_AC != s->inningPhase) {
            if (s->inningPhase == 1 && g_Scores._pad_AC != 1 && g_Scores._pad_AC != 0) {
                ok = FALSE;
            } else if (s->inningPhase != 1 && (g_Scores._pad_AC == 1 || g_Scores._pad_AC == 0)) {
                ok = FALSE;
            } else if (s->inningPhase == 2 && g_Scores._pad_AC != 2) {
                ok = FALSE;
            } else if (s->inningPhase != 2 && g_Scores._pad_AC == 2) {
                ok = FALSE;
            } else if (s->inningPhase == 3 && g_Scores._pad_AC != 3) {
                ok = FALSE;
            } else if (s->inningPhase != 3 && g_Scores._pad_AC == 3) {
                ok = FALSE;
            } else if (s->inningPhase == 4 && g_Scores._pad_AC < 4) {
                ok = FALSE;
            } else if (s->inningPhase != 4 && g_Scores._pad_AC >= 4) {
                ok = FALSE;
            }
        }

        if (s->outs != -1 && g_Strikes.outs != s->outs) {
            ok = FALSE;
        }

        if (s->runnerOnFirst != -1) {
            if (s->runnerOnFirst == 1 && g_Runners[1].rosterID == -1) {
                ok = FALSE;
            } else if (s->runnerOnFirst == 0 && g_Runners[1].rosterID != -1) {
                ok = FALSE;
            }
        }
        if (s->runnerOnSecond != -1) {
            if (s->runnerOnSecond == 1 && g_Runners[2].rosterID == -1) {
                ok = FALSE;
            } else if (s->runnerOnSecond == 0 && g_Runners[2].rosterID != -1) {
                ok = FALSE;
            }
        }
        if (s->runnerOnThird != -1) {
            if (s->runnerOnThird == 1 && g_Runners[3].rosterID == -1) {
                ok = FALSE;
            } else if (s->runnerOnThird == 0 && g_Runners[3].rosterID != -1) {
                ok = FALSE;
            }
        }

        if (s->leadRequirement != -1) {
            result = fn_3_22ABC();
            if (s->leadRequirement == 0 && result != 0) {
                ok = FALSE;
            }
            if (s->leadRequirement == 1 && result != 1) {
                ok = FALSE;
            }
            if (s->leadRequirement == 2 && result != 2) {
                ok = FALSE;
            }
        }

        if (s->scoreOrder != -1) {
            result = fn_3_22A20();
            if (s->scoreOrder == 0 && result != 0) {
                ok = FALSE;
            } else if (s->scoreOrder == 1 && result != 1) {
                ok = FALSE;
            }
        }

        if (s->captainMatchup != -1) {
            int batter = g_Batter.charID;
            int pitcher = g_Pitcher.charID;

            if (s->captainMatchup == 1) {
                if (data->matchupTable[batter][pitcher] == 0) {
                    if (g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamBatting] != batter ||
                        g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamFielding] != pitcher) {
                        ok = FALSE;
                    }
                }
            } else if (s->captainMatchup == 0) {
                if (data->matchupTable[batter][pitcher] == 1) {
                    ok = FALSE;
                }
            }
        }

        if (s->_24 != -1 && s->_24 != 0 && s->_34 != 0) {
            ok = FALSE;
        }

        if (s->_28 != -1 && s->_28 != 0) {
            if (s->_38 == 0) {
                if (lbl_3_common_bss_1323C->_27B >= s->_30) {
                    ok = FALSE;
                }
            } else if (s->captainMatchup == 1) {
                int batter = g_Batter.charID;
                int pitcher = g_Pitcher.charID;

                if (data->matchupTable[batter][pitcher] == 1) {
                    if (g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamBatting] == batter &&
                        g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamFielding] == pitcher) {
                        if (s->_3C != 0) {
                            ok = FALSE;
                        }
                    } else {
                        ok = FALSE;
                    }
                } else {
                    ok = FALSE;
                }
            } else {
                ok = FALSE;
            }
        }

        if (ok) {
            lbl_3_common_bss_1323C->situation = i;
        }
    }

    if (lbl_3_common_bss_1323C->situation == -1) {
        return FALSE;
    }

    if (settings->exhibitionMatchInd == 0 &&
        data->situationLocked[lbl_3_common_bss_1323C->situation] == 1) {
        lbl_3_common_bss_1323C->situation = -1;
        return FALSE;
    }

    if (data->situations[lbl_3_common_bss_1323C->situation]._24 == 1) {
        data->situations[lbl_3_common_bss_1323C->situation]._34 = 1;
    }
    if (data->situations[lbl_3_common_bss_1323C->situation]._28 == 1) {
        VsSituation *s = &data->situations[lbl_3_common_bss_1323C->situation];

        s->_38 = 1;
        s = &data->situations[lbl_3_common_bss_1323C->situation];
        if (s->captainMatchup == 1) {
            int batter = g_Batter.charID;
            int pitcher = g_Pitcher.charID;

            if (data->matchupTable[batter][pitcher] == 1) {
                if (g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamBatting] == batter &&
                    g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamFielding] == pitcher) {
                    s->_3C = 1;
                }
                animRelated[0xAE] = 1;
                animRelated[0xAF] = g_Pitcher.rosterID;
            }
        }
    }
    lbl_3_common_bss_1323C->_27B = data->situations[lbl_3_common_bss_1323C->situation]._30;
    return TRUE;
}

// .text:0x00021DE4 size:0x130 mapped:0x80660E78
void fn_3_21DE4(void) {
    VsFadeItem *item = (VsFadeItem *)currentDrawingItem;

    switch (lbl_3_bss_9C) {
    case 0:
        item->frame = 0;
        item->alpha = 0xFF;
        lbl_803C5090._1D = 9;
        lbl_803C5090._00 = 1.0f;
        lbl_803C5090._14 = 0x1C0;
        lbl_803C5090._19 = 1;
        lbl_803C5090._18 = 0;
        lbl_803C5090._1A = 0xFF;
        lbl_803C5090._1B = 0xFF;
        lbl_803C5090._1C = 0xFF;
        lbl_803C5090._17 = 0xFF;
        lbl_3_bss_9C = lbl_3_bss_9C + 1;
        break;
    case 1:
        lbl_803C5090._1D = 8;
        lbl_803C5090._00 = 1.0f;
        lbl_803C5090._14 = 0x1C0;
        lbl_803C5090._19 = 1;
        lbl_803C5090._18 = 0;
        lbl_803C5090._1A = 0xFF;
        lbl_803C5090._1B = 0xFF;
        lbl_803C5090._1C = 0xFF;
        lbl_803C5090._17 = 0xFF;
        item->frame = item->frame + 1;
        if (*(u16 *)((u8 *)g_pCamera + 0xAAE) <= item->frame) {
            *(s16 *)((u8 *)g_pCamera + 0xAAA) = 0;
            removeCurrentDrawingItem();
            lbl_3_bss_9C = 0;
        }
        break;
    }
}

// .text:0x00021C90 size:0x154 mapped:0x80660D24
void fn_3_21C90(void) {
    VsFadeItem *item = (VsFadeItem *)currentDrawingItem;

    switch (lbl_3_bss_A0.state) {
    case 0:
        item->frame = 0;
        item->alpha = 0xFF;
        lbl_803C5090._1D = 9;
        lbl_803C5090._00 = 1.0f;
        lbl_803C5090._14 = 0x1C0;
        lbl_803C5090._19 = 1;
        lbl_803C5090._18 = 0;
        lbl_803C5090._1A = 0xFF;
        lbl_803C5090._1B = 0xFF;
        lbl_803C5090._1C = 0xFF;
        lbl_803C5090._17 = item->alpha;
        lbl_3_bss_A0.state = lbl_3_bss_A0.state + 1;
        break;
    case 1:
        lbl_803C5090._1D = 8;
        lbl_803C5090._00 = 1.0f;
        lbl_803C5090._14 = 0x1C0;
        lbl_803C5090._19 = 1;
        lbl_803C5090._18 = 0;
        lbl_803C5090._1A = 0xFF;
        lbl_803C5090._1B = 0xFF;
        lbl_803C5090._1C = 0xFF;
        lbl_803C5090._17 = item->alpha;
        item->frame = item->frame + 1;
        if (*(u16 *)((u8 *)g_pCamera + 0xAAC) <= item->frame) {
            *(s16 *)((u8 *)g_pCamera + 0xAA8) = 0;
            removeCurrentDrawingItem();
            lbl_3_bss_A0.state = 0;
        } else {
            item->alpha = 0xFF - (item->frame * 0xFF) / *(u16 *)((u8 *)g_pCamera + 0xAAC);
        }
        break;
    }
}
