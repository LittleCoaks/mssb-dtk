#include "game/fielding/fielder_orientation.h"
#define REP_HEADER_DATA_FN getRepHeaderData_fielderOrientation
#include "header_rep_data.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

#define SANG_MAX_ANGLE 0x1000
#define SANG_ANG_180 0x800

extern f32 radianAngleReduction(f32 angle);
extern int radToShortAngle(f32 angle);
extern int angleDifferenceNormalized(s16 a, s16 b);
extern f32 shortAngleToRad(int angle);

typedef struct {
    u8 _00[0x28];
    f32 orientation;
    u8 _2C[0x16];
    u8 _42;
    u8 _43[0x11];
} FielderAnimSlot;

typedef struct {
    u8 _00[0x34];
    VecXYZ position;
    f32 zeroA;
    f32 orientation;
    f32 zeroB;
    u8 _4C[0x25D - 0x4C];
    u8 displayState;
    u8 _25E[0x275 - 0x25E];
    u8 terrain;
} FielderAnimObject;

extern FielderAnimSlot g_UnkAnimation_31EAC[9];
extern struct {
    u8 _00[0x2C50];
    FielderAnimObject* objects[13];
} hugeAnimStruct;
extern u8 lbl_3_data_69C0[];
extern u8* lbl_3_common_bss_1323C;
extern const f32 lbl_3_rodata_1030;
extern const f32 lbl_3_rodata_1034;


// .text:0x0006AF9C size:0x1A8 mapped:0x806AA030
f32 computeAdjustedFielderOrientation(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    FielderAnimSlot* anim = &g_UnkAnimation_31EAC[fielderIndex];
    f32 angle = radianAngleReduction(-fielder->desiredMovementDirection - lbl_3_rodata_1030);
    s16 targetAngle;
    s16 currentAngle;
    s16 difference;

    if (fielder->wallActionFacingAngleInd != FALSE) {
        return angle;
    }

    targetAngle = radToShortAngle(angle);
    currentAngle = radToShortAngle(anim->orientation);
    difference = (s16)angleDifferenceNormalized(currentAngle, targetAngle);
    if (difference > SANG_ANG_180) {
        difference -= SANG_MAX_ANGLE;
    } else if (difference <= -SANG_ANG_180) {
        difference += SANG_MAX_ANGLE;
    }

    if (difference > 0x600) {
        if (fielder->throwingHandedness == FALSE) {
            currentAngle -= 0x280;
        } else {
            currentAngle += 0x280;
        }
    } else if (difference < -0x600) {
        if (fielder->throwingHandedness == FALSE) {
            currentAngle -= 0x280;
        } else {
            currentAngle += 0x280;
        }
    } else if (difference > 0x200) {
        currentAngle -= 0x180;
    } else if (difference < -0x200) {
        currentAngle += 0x180;
    } else if (difference > 0x180) {
        currentAngle -= 0x100;
    } else if (difference < -0x180) {
        currentAngle += 0x100;
    } else if (difference > 0xC0) {
        currentAngle -= 0x80;
    } else if (difference < -0xC0) {
        currentAngle += 0x80;
    } else if (difference > 0x60) {
        currentAngle -= 0x40;
    } else if (difference < -0x60) {
        currentAngle += 0x40;
    } else {
        return angle;
    }
    return shortAngleToRad((s16)currentAngle);
}

// .text:0x0006B144 size:0x384 mapped:0x806AA1D8
void animateDefence(void) {
    E(u8, GAME_STATUS) status = g_GameLogic.gameStatus;
    int i;
    FielderAnimObject* model;
    InMemFielder* fielder;
    FielderAnimSlot* anim;
    f32 orientation;

    if (status == GAME_STATUS_DEFAULT) goto animate;
    if (status == GAME_STATUS_AT_BAT) goto animate;
    if (status == GAME_STATUS_LIVE_BALL) goto animate;
    if (status == GAME_STATUS_TRANSITION) goto animate;
    if (status == GAME_STATUS_INNING_TRANSITION) goto animate;
    if (status == GAME_STATUS_STAR_CHANCE_VS) goto animate;
    if (status == GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING) goto animate;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && status == GAME_STATUS_PAUSED) goto animate;
    for (i = 0; i < 9; i++) {
        model = hugeAnimStruct.objects[i];
        if (model != 0) {
            model->displayState = FALSE;
        }
    }
    return;

animate:
    for (i = 0; i < 9; i++) {
        model = hugeAnimStruct.objects[i];
        fielder = &g_Fielders[i];
        anim = &g_UnkAnimation_31EAC[i];
        if (model == 0) {
            continue;
        }
        model->displayState = FALSE;
        model->terrain = fielder->terrainOrCollisionRelated;
        if (g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION) {
            continue;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            E(u8, SECONDARY_GAME_MODE) mode = g_GameLogic.secondaryGameMode;
            if (mode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING || g_Practice.practiceLevel == 4) {
                continue;
            }
            if ((mode == SECONDARY_GAME_MODE_PRACTICE_PITCHING ||
                 mode == SECONDARY_GAME_MODE_PRACTICE_BATTING) && i > 0) {
                continue;
            }
        }
        model->displayState = TRUE;
        if (anim->_42 == FALSE) {
            model->position.x = fielder->pos.x;
            model->position.y = -fielder->pos.y - fielder->actionYOffset;
            model->position.z = fielder->pos.z;
        }
        orientation = computeAdjustedFielderOrientation(i);
        if (fielder->_020A != FALSE) {
            orientation = anim->orientation;
        }
        model->orientation = orientation;
        model->zeroA = lbl_3_rodata_1034;
        model->zeroB = lbl_3_rodata_1034;
        anim->orientation = orientation;
        if (fielder->_0263 != FALSE) {
            model->displayState = 2;
        }
        if (g_Stats.replayInd != FALSE) {
            model->displayState = lbl_3_common_bss_1323C[i + 0x261];
        } else if (i == 1) {
            if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT ||
                g_GameLogic.gameStatus == GAME_STATUS_DEFAULT ||
                g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY ||
                g_GameLogic.gameStatus == GAME_STATUS_STAR_CHANCE_VS ||
                g_GameLogic.sceneID == SCENE_ID_AT_BAT) {
                model->displayState = 2;
            }
            if (g_GameLogic.sceneID == SCENE_ID_REPLAY_AT_BAT) {
                model->displayState = 1;
            }
        } else if (lbl_3_data_69C0[i] != 0) {
            if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT ||
                g_GameLogic.gameStatus == GAME_STATUS_DEFAULT ||
                g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY ||
                g_GameLogic.gameStatus == GAME_STATUS_STAR_CHANCE_VS ||
                g_GameLogic.sceneID == SCENE_ID_AT_BAT) {
                model->displayState = 2;
            }
            if (g_GameLogic.sceneID == SCENE_ID_REPLAY_AT_BAT) {
                model->displayState = 1;
            }
        }
        if (fielder->clamberStatus == 1 ||
            (u8)(fielder->clamberStatus - 2) <= 3 || fielder->clamberStatus == 6) {
            model->displayState = 3;
        }
    }
}

const f32 lbl_3_rodata_1030 = 1.5707964f;
const f32 lbl_3_rodata_1034 = 0.0f;
