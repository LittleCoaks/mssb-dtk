#define SQRT2_LINKAGE static
#include "game/animation/animation_dispatch.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/ball/foul_detection.h"
#include "game/math/game_math.h"
#include "game/sound/m_sound.h"
#include "game/match_setup/stat_lookups.h"
#define REP_HEADER_DATA_FN getRepHeaderData_animationDispatch
#include "header_rep_data.h"

// One animation-driven object (character model) in hugeAnimStruct's object pool.
struct AnimObject {
    /*0x00*/ u8 _00[0x30];
    /*0x30*/ s32 _30;
    /*0x34*/ f32 x;
    /*0x38*/ u8 _38[0x3C - 0x38];
    /*0x3C*/ f32 z;
    /*0x40*/ u8 _40[0x4C - 0x40];
    /*0x4C*/ f32 _4C;
    /*0x50*/ u8 _50[0x62 - 0x50];
    /*0x62*/ s16 animId;
    /*0x64*/ s16 _64;
    /*0x66*/ u8 _66[0x68 - 0x66];
    /*0x68*/ s16 framesLeft;
    /*0x6A*/ s16 _6A;
    /*0x6C*/ u8 _6C[0x70 - 0x6C];
    /*0x70*/ s16 _70;
    /*0x72*/ u8 _72[0x16A - 0x72];
    /*0x16A*/ u16 _16A;
    /*0x16C*/ u8 _16C[0x252 - 0x16C];
    /*0x252*/ s8 _252;
    /*0x253*/ u8 _253[0x25D - 0x253];
    /*0x25D*/ u8 _25D;
    /*0x25E*/ u8 _25E;
    /*0x25F*/ u8 _25F[0x26F - 0x25F];
    /*0x26F*/ u8 _26F;
    /*0x270*/ u8 _270[0x273 - 0x270];
    /*0x273*/ u8 _273;
    /*0x274*/ u8 _274;
    /*0x275*/ u8 _275[0x27C - 0x275];
};

// Reset block used by resetAnimTracks: four tracks, 0x90 bytes apart from +0x38.
typedef struct AnimTrack {
    /*0x00*/ s32 _00;
    /*0x04*/ u8 _04[0x0A - 0x04];
    /*0x0A*/ s16 _0A;
    /*0x0C*/ u8 _0C[0x54 - 0x0C];
    /*0x54*/ u8 _54;
    /*0x55*/ u8 _55;
    /*0x56*/ u8 _56;
    /*0x57*/ u8 _57;
    /*0x58*/ f32 _58;
    /*0x5C*/ f32 _5C;
    /*0x60*/ u8 _60[0x90 - 0x60];
} AnimTrack;

typedef struct AnimTrackBlock {
    /*0x00*/ u8 _00[0x38];
    /*0x38*/ AnimTrack tracks[4];
} AnimTrackBlock;

typedef struct AnimView {
    /*0x0000*/ u8 _0000[0x60];
    /*0x0060*/ AnimTrackBlock* trackBlock;
    /*0x0064*/ u8 _0064[0xC04 - 0x64];
    /*0x0C04*/ AnimObject pool[13];
    /*0x2C50*/ AnimObject* objects[13];
    /*0x2C84*/ u8 _2C84[0x307D - 0x2C84];
    /*0x307D*/ u8 _307D;
} AnimView;

typedef struct PlayTracking {
    /*0x00*/ s16 _00;
    /*0x02*/ s16 _02;
    /*0x04*/ s16 _04;
    /*0x06*/ s16 _06;
    /*0x08*/ u8 _08;
    /*0x09*/ u8 _09;
    /*0x0A*/ u8 _0A;
    /*0x0B*/ u8 _0B;
    /*0x0C*/ s8 _0C;
    /*0x0D*/ u8 _0D;
    /*0x0E*/ u8 _0E;
    /*0x0F*/ u8 _0F;
} PlayTracking;

// Per-fielder animation bookkeeping (g_UnkAnimation_31EAC).
typedef struct AnimSlot {
    /*0x00*/ f32 speed;
    /*0x04*/ u8 _04[0x10 - 0x04];
    /*0x10*/ VecXYZ pos;
    /*0x1C*/ VecXYZ prevPos;
    /*0x28*/ u8 _28[0x2C - 0x28];
    /*0x2C*/ VecXYZ target;
    /*0x38*/ s16 _38;
    /*0x3A*/ s16 _3A;
    /*0x3C*/ s16 _3C;
    /*0x3E*/ s16 _3E;
    /*0x40*/ u8 _40;
    /*0x41*/ u8 _41;
    /*0x42*/ u8 _42;
    /*0x43*/ u8 _43;
    /*0x44*/ u8 _44;
    /*0x45*/ u8 _45;
    /*0x46*/ u8 _46;
    /*0x47*/ u8 _47;
    /*0x48*/ u8 _48;
    /*0x49*/ u8 _49;
    /*0x4A*/ s16 countdown;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 _4D;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
    /*0x50*/ u8 _50;
    /*0x51*/ u8 state;
    /*0x52*/ u8 _52[2];
} AnimSlot; // size 0x54

// The pending throw's animation request.
typedef struct AnimThrowState {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ s16 fielder;
    /*0x0E*/ u8 type;
    /*0x0F*/ u8 anim;
    /*0x10*/ u8 _10;
} AnimThrowState;

// Per-runner animation state (lbl_3_common_bss_321A0), 0x20 bytes each.
typedef struct RunnerAnimSlot {
    /*0x00*/ f32 speed;
    /*0x04*/ u8 _04[0x10 - 0x04];
    /*0x10*/ s16 _10;
    /*0x12*/ u8 _12[0x16 - 0x12];
    /*0x16*/ s16 _16;
    /*0x18*/ u8 _18;
    /*0x19*/ u8 _19;
    /*0x1A*/ u8 _1A;
    /*0x1B*/ u8 state;
    /*0x1C*/ u8 prevState;
    /*0x1D*/ u8 direction;
    /*0x1E*/ u8 _1E[0x20 - 0x1E];
} RunnerAnimSlot;

extern AnimView hugeAnimStruct;
extern RunnerAnimSlot lbl_3_common_bss_321A0[4];
extern u8 characterStaticIndexes[54][6];
extern s16 lbl_3_data_7870[][3];
extern u8 runnerConstants[][5];
extern AnimSlot g_UnkAnimation_31EAC[9];
extern AnimThrowState g_UnkThrowing_31ACC[4];
extern u8 bodyCheckFrameRelatedConstants[][4];
extern u8 lbl_3_data_7D24[];
extern u8 lbl_3_data_7F0C[];
extern f32 lbl_3_data_476C[];
extern s16 barrelCollisionHitboxes[54];

extern void AnimateCharacter(int charId, int animId, int a2, int a3, int a4, int a5, int a6, int a7);
extern void QueueCharacterAnimation(int charId, int animId, int a2, int a3, int a4, int a5, int a6);
extern void fn_8001B4D8(int idx);
extern void fn_8001B5EC(int idx, int arg);
extern void fn_8004AE18(int index);
extern void fn_8001C528(int arg);
extern int* fn_800111D8(AnimObject* obj);
extern void fn_800B4A44(int a, int id);
extern s16 fn_8001B35C(int idx, int arg);
extern PlayTracking lbl_3_common_bss_32220;
typedef struct PitchAnimState {
    /*0x0*/ s16 timer;
    /*0x2*/ u8 state;
    /*0x3*/ u8 _3;
} PitchAnimState;

extern PitchAnimState us80893310;
extern s16 lbl_3_data_5EDC[];
extern u8 us80893314[6];
extern u8 highLevelSimulationFlag[2];
extern void versusScreen_seemsToDoNothing(void);

typedef struct ScreenState {
    /*0x000*/ u8 _000[0x25C];
    /*0x25C*/ u8 _25C;
} ScreenState;

extern ScreenState* lbl_3_common_bss_1323C;

#define MINIGAME_SELECTED_SLOT() (((s8*)&g_Minigame)[0x18CC + (s8)g_Minigame.minigamePlayerSelectedOrder])
#define MINIGAME_SLOT_OF(i) (((s8*)g_Minigame.minigameControlStruct[1].aIStrength)[(i)])

u8 lbl_3_data_65F0[0x70] = {
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x14, 0x05, 0x05, 0x05, 0x0F, 0x0F, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x14, 0x14, 0x14, 0x3C,
    0x3C, 0x3C, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x50, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00,
    0x05, 0x05, 0x05, 0x0F, 0x05, 0x05, 0x05, 0x00,
    0x0A, 0x1E, 0x00, 0x00, 0x00, 0x30, 0x00, 0x32,
    0x00, 0x32, 0x00, 0x50, 0x00, 0x50, 0x00, 0x19,
    0x00, 0x25, 0x00, 0x25, 0x00, 0x13, 0x00, 0x12,
    0x00, 0x11, 0x00, 0x19, 0x00, 0x18, 0x00, 0x17,
    0x00, 0x16, 0x00, 0x15, 0x00, 0x14, 0x00, 0x00,
    0x14, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x14,
};

u16 lbl_3_data_6660[0xAE] = {
    0x0016, 0x0010, 0x0017, 0x0011, 0x0018, 0x0012, 0x0019, 0x0013,
    0x001A, 0x0014, 0x001B, 0x0015, 0x0020, 0x001C, 0x0021, 0x001D,
    0x0022, 0x001E, 0x0023, 0x001F, 0x0026, 0x0025, 0x0028, 0x0027,
    0x003D, 0x003C, 0xFFFF, 0x0000, 0x004A, 0x004B, 0xFFFF, 0x0000,
    0x002F, 0x0034, 0x0030, 0x0035, 0x0031, 0x0036, 0x0032, 0x0037,
    0x0033, 0x0038, 0xFFFF, 0x0000, 0x0041, 0x0047, 0x0042, 0x0048,
    0x0043, 0x0049, 0x0044, 0x004A, 0x0045, 0x004B, 0x0046, 0x004C,
    0xFFFF, 0x0000, 0x002F, 0x0034, 0xFFFF, 0x0000, 0x0000, 0x0001,
    0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009,
    0x000E, 0x000F, 0x000D, 0x000C, 0x000B, 0x000A, 0x0016, 0x0017,
    0x0018, 0x0019, 0x001A, 0x001B, 0x0010, 0x0011, 0x0012, 0x0013,
    0x0014, 0x0015, 0x0020, 0x0021, 0x0022, 0x0023, 0x001C, 0x001D,
    0x001E, 0x001F, 0x0024, 0x0026, 0x0025, 0x0028, 0x0027, 0x0029,
    0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F, 0x0030, 0x0031,
    0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039,
    0x003A, 0x003B, 0x003D, 0x003C, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0203, 0x0405, 0x0607,
    0x0809, 0x0A0B, 0x0C0D, 0x000E, 0x0F10, 0x1112, 0x1314, 0x1516,
    0x1700, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0100, 0x0000, 0x0000, 0x0100, 0x0000, 0x0101, 0x0101,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0101,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0101, 0x0000,
};

// .text:0x0006714C size:0x394 mapped:0x806A61E0
void resetAndRunAnimations(int arg) {
    int i;
    int k;
    int slotIdx;
    AnimSlot* slot;
    AnimObject* obj;

    fn_8001C528(arg);
    us80893310.timer = 0;
    lbl_3_common_bss_32220._06 = 0;
    lbl_3_common_bss_32220._09 = 0;
    lbl_3_common_bss_32220._00 = 0;
    lbl_3_common_bss_32220._0A = 0;
    lbl_3_common_bss_32220._0D = 0;
    g_UnkThrowing_31ACC[0].type = 0;
    g_UnkThrowing_31ACC[1].type = 0;
    g_UnkThrowing_31ACC[2].type = 0;
    g_UnkThrowing_31ACC[3].type = 0;

    slot = g_UnkAnimation_31EAC;
    for (i = 0; i < 9; i++, slot++) {
        slotIdx = i;
        if (g_d_GameSettings.minigamesEnabled) {
            for (k = 0; k < 4; k++) {
                if ((s8)g_Minigame.minigameFielderIndex[k] == i) {
                    break;
                }
            }
            slotIdx = k;
            if (slotIdx >= 4) {
                continue;
            }
        }
        slot->_38 = 0;
        slot->_3A = 0;
        slot->_42 = 0;
        slot->_43 = 0;
        slot->_44 = 0;
        slot->_46 = 0;
        slot->_47 = 0;
        slot->_4C = 0;
        slot->_4F = 0;
        slot->_50 = 0;
        slot->state = 0;
        slot->speed = 0.0f;
        obj = hugeAnimStruct.objects[slotIdx];
        if (obj != NULL && obj->_30 == 0) {
            updateFielderState(i, 0);
        }
    }

    if (hugeAnimStruct._307D == 0) {
        for (k = 0; k < 4; k++) {
            if (!g_d_GameSettings.minigamesEnabled || (k == 0 && (s8)g_Minigame.rosterID >= 0) ||
                (s8)g_Minigame.runnerPlayerIndexU8[k] >= 0) {
                lbl_3_common_bss_321A0[k]._10 = -1;
                lbl_3_common_bss_321A0[k]._18 = 0;
                lbl_3_common_bss_321A0[k]._19 = 0;
                lbl_3_common_bss_321A0[k]._16 = 0;
            }
        }
    }

    setDefaultPlayTrackingVariables3();
    if (arg == 0) {
        us80893314[0] = 1;
        pitcherAnimation();
        batterAnimations();
    }

    if (g_d_GameSettings.minigamesEnabled) {
        fielderAnimations();
    } else {
        fielderAnimations();
        runnerAnimations();
    }
}

// .text:0x00067130 size:0x1C mapped:0x806A61C4
void setDefaultPlayTrackingVariables3(void) {
    lbl_3_common_bss_32220._08 = 0;
    lbl_3_common_bss_32220._0B = 0;
    lbl_3_common_bss_32220._04 = 0;
}

// .text:0x000668BC size:0x874 mapped:0x806A5950
void unsure_updateAnimations(void) {
    int i;
    int j;
    int idx;
    AnimSlot* slot;
    InMemFielder* fielder;
    AnimObject* obj;
    AnimObject* batterObj;
    AnimObject* pitcherObj;
    s16 animId;

    if (g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION || g_GameLogic.gameStatus == GAME_STATUS_GAME_START_MOVIE) {
        return;
    }

    for (i = 0; i < 13; i++) {
        hugeAnimStruct.pool[i]._274 = 0;
    }

    if (g_d_GameSettings.minigamesEnabled) {
        if ((g_GameLogic.gameStatus >= GAME_STATUS_0x1B && g_GameLogic.gameStatus <= GAME_STATUS_MINIGAME_READY) ||
            g_GameLogic.gameStatus == GAME_STATUS_GAME_START_MOVIE) {
            return;
        }
    }

    for (i = 0; i < 13; i++) {
        obj = hugeAnimStruct.objects[i];
        if (obj != NULL && obj->_25D != 0) {
            f32 one = 1.0f;
            u32 id = (obj != NULL) ? obj->_16A : 0xFFFF;

            if (id != 0xFFFF) {
                fn_800B4A44(*fn_800111D8(obj), (u16)id);
            }
            obj->framesLeft = (s16)(one / obj->_4C);
        }
    }

    if (g_Stats.replayInd != 0 && g_Stats.playFrameCounter == 1) {
        if (hugeAnimStruct.objects[9] != NULL && g_Stats._0034 != 0) {
            hugeAnimStruct.objects[9]->framesLeft = g_Stats._0034 - 1;
            hugeAnimStruct.objects[9]->_70 = g_Stats._0034 - 1;
        }
    }

    slot = g_UnkAnimation_31EAC;
    fielder = g_Fielders;
    for (i = 0; i < 9; i++, slot++, fielder++) {
        VEC_COPY(&slot->prevPos, &slot->pos);
        fielder->_020A = 0;
        idx = i;
        obj = hugeAnimStruct.objects[i];
        if (g_d_GameSettings.minigamesEnabled) {
            for (j = 0; j < 4; j++) {
                if ((s8)g_Minigame.minigameFielderIndex[j] == i) {
                    break;
                }
            }
            if (j >= 4) {
                continue;
            }
            idx = ((s8*)&g_Minigame)[0x18CC + j];
            obj = hugeAnimStruct.objects[j];
        }

        if (slot->_50 != 0) {
            fielder->animationRelatedInd = 1;
        } else {
            fielder->animationRelatedInd = 0;
        }
        if (slot->_4F != 0 && fielder->catchAnimationFramesCountDown <= 1) {
            fielder->animatingActionInd = 1;
        } else {
            fielder->animatingActionInd = 0;
        }

        if (obj != NULL) {
            if (slot->_42 != 0) {
                getAnimRelatedCoordinates(idx, 4, &slot->target);
                fielder->velocityX = slot->target.x - fielder->pos.x;
                fielder->velocityZ = slot->target.z - fielder->pos.z;
                fielder->currentVelocity = VEC_LENGTH_XZ((VecXZ*)&fielder->velocityX);
                fielder->pos.x = slot->target.x;
                fielder->pos.z = slot->target.z;
                fielder->_01FB = 1;
                foulAnimationRelatedMaybe(i, obj);
            } else {
                fielder->_01FB = 0;
                if (fielder->currentVelocity > fielder->joggingSpeed) {
                    fielder->currentVelocity = fielder->joggingSpeed;
                }
            }
        }

        fielder->_01F9 = slot->_43;
        fielder->jumpDiveStateRelated = 0;
        if (slot->_4F != 0 && slot->_4D != 0) {
            switch (slot->_4D) {
                case 1:
                case 2:
                    fielder->jumpDiveStateRelated = 1;
                    break;
                case 3:
                    fielder->jumpDiveStateRelated = 2;
                    break;
            }
        }

        if (slot->_44 != 0) {
            fielder->relatedToStandingStill = 1;
            if (fielder->someCounter < 0x7FFE) {
                fielder->someCounter++;
            } else {
                fielder->someCounter = 0x7FFF;
            }
        } else {
            fielder->relatedToStandingStill = 0;
            fielder->someCounter = 0;
        }

        if (obj != NULL && obj->animId == 0xF) {
            fielder->_01FE = 1;
        } else {
            fielder->_01FE = 0;
        }
        slot->_3C = fn_8001B35C(idx, 1);
        slot->_3E = fn_8001B35C(idx, 0);
    }

    if (g_FieldingLogic.pitcher_inPitchingState != 0) {
        pitcherObj = hugeAnimStruct.objects[0];
        idx = 0;
        if (g_d_GameSettings.minigamesEnabled) {
            idx = MINIGAME_SELECTED_SLOT();
            pitcherObj = hugeAnimStruct.objects[idx];
        }
        getAnimRelatedCoordinates(idx, 4, &g_UnkAnimation_31EAC[0].target);
        g_Pitcher.pitcherCoord.x = g_UnkAnimation_31EAC[0].target.x;
        g_Pitcher.pitcherCoord.z = g_UnkAnimation_31EAC[0].target.z;
        if (pitcherObj != NULL) {
            animId = pitcherObj->animId;
            if (animId == 0x40 || animId == 0x42 || (animId == 0x41 && pitcherObj->framesLeft < 0x1E) ||
                (animId == 0x43 && pitcherObj->framesLeft < 0x1E)) {
                g_Pitcher.pitchDeliveryAnimationPlaying = 1;
            } else {
                g_Pitcher.pitchDeliveryAnimationPlaying = 0;
            }
        } else {
            g_Pitcher.pitchDeliveryAnimationPlaying = 0;
        }
    }

    if (hugeAnimStruct._307D == 0) {
        batterObj = hugeAnimStruct.objects[9];
        if (g_d_GameSettings.minigamesEnabled) {
            batterObj = &hugeAnimStruct.pool[((s8*)&g_Minigame)[0x18CC + (s8)g_Minigame.rosterID]];
        }

        if (lbl_3_common_bss_32220._08 == 0) {
            if (batterObj != NULL && (batterObj->animId == 0x4B || batterObj->animId == 0x66)) {
                g_Batter.noSwingAnimationInd = 1;
            } else {
                g_Batter.noSwingAnimationInd = 0;
            }
        }

        if (batterObj != NULL) {
            if (batterObj->animId == 0x67) {
                g_Batter.beginningOfABAnimationOccuring = 1;
            } else {
                g_Batter.beginningOfABAnimationOccuring = 0;
            }

            if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
                if (batterObj->animId == 0x4D) {
                    lbl_3_common_bss_32220._0A = 1;
                    lbl_3_common_bss_32220._02++;
                } else if (batterObj->animId == 0x53) {
                    lbl_3_common_bss_32220._0A = 2;
                    lbl_3_common_bss_32220._02++;
                } else if (batterObj->animId == 0x50) {
                    lbl_3_common_bss_32220._0A = 3;
                    lbl_3_common_bss_32220._02++;
                } else if (batterObj->animId == 0x54) {
                    lbl_3_common_bss_32220._0A = 4;
                    lbl_3_common_bss_32220._02++;
                } else if (lbl_3_common_bss_32220._0A != 0) {
                    if (lbl_3_common_bss_32220._0A == 9) {
                        lbl_3_common_bss_32220._0A = 0;
                    } else {
                        lbl_3_common_bss_32220._0A = 9;
                        lbl_3_common_bss_32220._02 = 0;
                    }
                }
            }

            if (batterObj->animId == 0x5E || (u16)(batterObj->animId - 0x5F) <= 2 || batterObj->animId == 0x62) {
                lbl_3_common_bss_32220._06 = batterObj->framesLeft;
            }
        }
    }
}

// .text:0x000664FC size:0x3C0 mapped:0x806A5590
void matchAnimations(void) {
    int i;
    u8 status;

    for (i = 0; i < 9; i++) {
        g_UnkAnimation_31EAC[i]._48 = 0;
    }

    status = g_GameLogic.gameStatus;
    if (status == GAME_STATUS_PAUSED || (u8)(status - 3) <= 2 ||
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU ||
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_LOAD_PRACTICE_SCREEN ||
        (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.tutorialState == 0)) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE &&
            g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU && g_Practice.practiceType_1 == 6) {
            minigameIdleAnimations();
        } else {
            for (i = 0; i < 13; i++) {
                AnimateCharacter(i, 2, 1, 1, 0, 0, 0, 0);
            }
        }
        return;
    }

    if (status == GAME_STATUS_MVP_END_GAME) {
        if (g_GameLogic._125 > 2) {
            minigameEndOfGameAnimations();
        }
        return;
    }
    if (lbl_3_common_bss_1323C->_25C != 0) {
        versusScreen_seemsToDoNothing();
        return;
    }
    if (us80893314[1] != 0) {
        resetAndRunAnimations(0);
        us80893314[1] = 0;
        return;
    }
    if (g_GameLogic.minigameLastTurnSuccessInd != 0 && g_Ball.totalFramesAtPlay == 0) {
        resetAndRunAnimations(0);
        return;
    }
    us80893314[0] = 0;
    pitcherAnimation();
    batterAnimations();
    fielderAnimations();
    runnerAnimations();
}

// .text:0x00066140 size:0x3BC mapped:0x806A51D4
void minigameAnimations(void) {
    int i;
    u8 status;

    for (i = 0; i < 9; i++) {
        g_UnkAnimation_31EAC[i]._48 = 0;
    }

    if (g_Minigame.endSequencePhase != 0 || g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_POST_MENU ||
        g_GameLogic.gameStatus == GAME_STATUS_0x26 || g_GameLogic.gameStatus == GAME_STATUS_0x27) {
        minigameEndOfGameAnimations();
        return;
    }

    status = g_GameLogic.gameStatus;
    if (status >= GAME_STATUS_0x1B && status <= 0x29) {
        minigameIdleAnimations();
        return;
    }

    if (((u8)(status - 3) <= 4 || g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU ||
         g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_LOAD_PRACTICE_SCREEN ||
         g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING) &&
        !(g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL && status == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY)) {
        for (i = 0; i < 4; i++) {
            AnimateCharacter(i, 2, 1, 1, 0, 0, 0, 0);
        }
        return;
    }

    if (highLevelSimulationFlag[0] != 0) {
        return;
    }
    if (us80893314[1] != 0) {
        resetAndRunAnimations(0);
        us80893314[1] = 0;
        return;
    }
    if (g_GameLogic.minigameLastTurnSuccessInd != 0 && g_Ball.totalFramesAtPlay == 0) {
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL && g_Minigame.soloMinigameDifficulty == 3) {
            us80893314[0] = 0;
        } else {
            resetAndRunAnimations(0);
            return;
        }
    } else {
        us80893314[0] = 0;
    }
    pitcherAnimation();
    batterAnimations();
    fielderAnimations();
    runnerAnimations();
}

// .text:0x00065FE0 size:0x160 mapped:0x806A5074
void minigameIdleAnimations(void) {
    int i;
    int idx;
    u8 flag;
    AnimObject* obj;

    for (i = 0; i < 4; i++) {
        idx = i;
        flag = 0;
        obj = hugeAnimStruct.objects[i];
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            idx = 9;
            obj = hugeAnimStruct.objects[9];
        }
        if (obj != NULL) {
            s8 v = ((s8*)&g_Minigame)[0x19EC + i * 9];

            if (v == 0 || v == 2) {
                flag = 1;
            }
            if (((s8*)&g_Minigame)[0x19EA + i * 9] < 0) {
                AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
            } else if (((s8*)&g_Minigame)[0x19E9 + i * 9] != 0) {
                if (obj->animId == 0x69) {
                    AnimateCharacter(idx, 0x6A, 0, 1, 1, 0, flag, 0);
                    QueueCharacterAnimation(idx, 0x6B, 1, 1, 0, flag, -1);
                }
            } else {
                AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
                break;
            }
        }
    }
}

// .text:0x000657E4 size:0x7FC mapped:0x806A4878
void minigameEndOfGameAnimations(void) {
    int k;
    int trigger = 0;
    u8 status = g_GameLogic.gameStatus;
    int idx;
    u8 flag;
    int sound;

    if (status == GAME_STATUS_MVP_END_GAME) {
        BOOL mg = g_d_GameSettings.minigamesEnabled;

        if (mg && g_GameLogic._125 == 1) {
            trigger = 1;
        }
        if (!mg && g_GameLogic._125 == 3) {
            trigger = 1;
        }
    }
    if (status == GAME_STATUS_0x27 && g_GameLogic._125 == 0) {
        trigger = 1;
    }

    if (trigger != 0) {
        if (!g_d_GameSettings.minigamesEnabled) {
            u8 rank = StatsScreenScores.mvpKind;

            if (rank == 2) {
                us80893314[2] = 1;
            } else if (rank == 3) {
                us80893314[2] = 2;
            } else {
                us80893314[2] = 0;
            }
        } else if (status == GAME_STATUS_0x27 && g_Minigame.grandPrixFinalHumanCount == 1) {
            s8 player = g_Minigame.soloPlayerSlot;
            BOOL found = FALSE;

            for (k = 0; k < 4; k++) {
                if (((u8*)&g_Minigame)[0x1E08 + k * 2] == player && ((u8*)&g_Minigame)[0x1E09 + k * 2] == 0) {
                    found = TRUE;
                    break;
                }
            }
            if (g_Minigame.grandPrixRanks[0][1] == 0 && g_Minigame.grandPrixRanks[1][1] == 0 && g_Minigame.grandPrixRanks[2][1] == 0 &&
                g_Minigame.grandPrixRanks[3][1] == 0) {
                us80893314[2 + player] = 2;
            } else if (found) {
                us80893314[2 + player] = 0;
            } else {
                us80893314[2 + player] = 1;
            }
        } else if (g_Minigame.miniGameNumberOfParticipants == 1) {
            u8 difficulty = g_Minigame.soloMinigameDifficulty;
            u8 a = g_Minigame.newRecordInd;
            u8 b = g_Minigame.winLossResult;

            for (k = 0; k < 4; k++) {
                if (((s8*)&g_Minigame)[0x18CC + k] >= 0) {
                    if (difficulty == 3) {
                        if (a != 0) {
                            us80893314[2 + k] = 0;
                        } else {
                            us80893314[2 + k] = 1;
                        }
                    } else if (b == 1) {
                        us80893314[2 + k] = 0;
                    } else {
                        us80893314[2 + k] = 1;
                    }
                }
            }
        } else {
            u8 x = g_Minigame.challenge_minigame_haven_tWonYetIndicator;

            for (k = 0; k < 4; k++) {
                if (((s8*)&g_Minigame)[0x18CC + k] >= 0) {
                    if (x != 0) {
                        us80893314[2 + k] = 2;
                    } else if (((u8*)&g_Minigame)[0x18E8 + k] == 1) {
                        us80893314[2 + k] = 0;
                    } else {
                        us80893314[2 + k] = 1;
                    }
                }
            }
        }
    }

    if ((!g_d_GameSettings.minigamesEnabled && g_GameLogic._125 < 4) ||
        (g_d_GameSettings.minigamesEnabled && g_Minigame.endSequencePhase <= 1)) {
        for (k = 0; k < 4; k++) {
            if (!g_d_GameSettings.minigamesEnabled) {
                idx = 9;
            } else {
                idx = ((s8*)&g_Minigame)[0x18CC + k];
                if (idx < 0) {
                    continue;
                }
            }
            if (!g_d_GameSettings.minigamesEnabled) {
                flag = 1;
            } else {
                s8 v = ((s8*)&g_Minigame)[0x19EC + k * 9];

                if (v == 0 || v == 2) {
                    flag = 1;
                } else {
                    flag = 0;
                }
            }
            if (us80893314[2 + k] == 0) {
                AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
            } else if (us80893314[2 + k] == 1) {
                AnimateCharacter(idx, 0x6F, 1, 1, 1, 0, flag, 0);
            } else {
                AnimateCharacter(idx, 0x72, 1, 1, 1, 0, flag, 0);
            }
            if (!g_d_GameSettings.minigamesEnabled) {
                break;
            }
        }
    } else if ((!g_d_GameSettings.minigamesEnabled && g_GameLogic._125 == 4 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) ||
               (g_d_GameSettings.minigamesEnabled && g_Minigame.endSequencePhase == 2) ||
               (g_GameLogic.gameStatus == GAME_STATUS_0x27 && g_GameLogic._125 == 0)) {
        g_Minigame.endSequencePhase = 3;
        for (k = 0; k < 4; k++) {
            if (!g_d_GameSettings.minigamesEnabled) {
                idx = 9;
            } else {
                idx = ((s8*)&g_Minigame)[0x18CC + k];
                if (idx < 0) {
                    continue;
                }
            }
            if (g_GameLogic.gameStatus == GAME_STATUS_0x27 && g_Minigame.soloPlayerSlot >= 0 && g_Minigame.soloPlayerSlot != k) {
                continue;
            }
            if (!g_d_GameSettings.minigamesEnabled) {
                sound = StatsScreenScores.mvpCharID;
                flag = 1;
            } else {
                s8 v = ((s8*)&g_Minigame)[0x19EC + k * 9];

                if (v == 0 || v == 2) {
                    sound = ((u8*)&g_Minigame)[0x18D0 + k];
                    flag = 1;
                } else {
                    flag = 0;
                    sound = ((u8*)&g_Minigame)[0x18D0 + k];
                }
            }
            if (us80893314[2 + k] == 0) {
                AnimateCharacter(idx, 0x6D, 0, 1, 1, 0, flag, -1);
                QueueCharacterAnimation(idx, 0x6B, 1, 1, 0, flag, -1);
                playCharacterSound(sound, 7);
            } else if (us80893314[2 + k] == 1) {
                AnimateCharacter(idx, 0x70, 0, 1, 1, 0, flag, -1);
                QueueCharacterAnimation(idx, 0x71, 1, 1, 0, flag, -1);
                if (g_Minigame.miniGameNumberOfParticipants > 1) {
                    fn_3_90150(sound, 9);
                } else {
                    playCharacterSound(sound, 9);
                }
            } else {
                AnimateCharacter(idx, 0x73, 0, 1, 1, 0, flag, -1);
                QueueCharacterAnimation(idx, 0x74, 1, 1, 0, flag, -1);
            }
            if (!g_d_GameSettings.minigamesEnabled) {
                break;
            }
        }
    }
}

// .text:0x00064BDC size:0xC08 mapped:0x806A3C70
void pitcherAnimation(void) {
    int idx = 0;
    int flag = 0;
    int stage;
    AnimObject* obj;
    VecSrcDst probe;
    CollisionStruct hit;
    u8 status;

    if (g_Pitcher.handedness != 0) {
        flag = 1;
    }

    if (g_d_GameSettings.minigamesEnabled) {
        if ((s8)g_Minigame.minigamePlayerSelectedOrder < 0) {
            return;
        }
        idx = MINIGAME_SELECTED_SLOT();
    }

    obj = hugeAnimStruct.objects[idx];
    if (obj != NULL) {
        if (obj->animId == 0x44 && obj->_6A == 1) {
            playCharacterSound(obj->_252, 4);
        } else if (obj->animId == 0x45 && obj->_6A == 1) {
            playCharacterSound(obj->_252, 3);
        }
    }

    status = g_GameLogic.gameStatus;
    if (!(status == GAME_STATUS_DEFAULT || (u8)(status - 1) <= 1 || status == GAME_STATUS_STAR_CHANCE_VS ||
          (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL && status == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY) ||
          (status == GAME_STATUS_PAUSED && us80893314[0] != 0))) {
        if (g_d_GameSettings.minigamesEnabled && status == GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING) {
            AnimateCharacter(idx, 0x3F, 1, 2, 1, 0, flag, -1);
            us80893310.state = 1;
        } else {
            us80893310.state = 0;
        }
        return;
    }

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_PITCHING && g_Practice.instructionNumber < 0 &&
        g_Practice.completionMenuActive != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.practiceLevel == 4) {
        return;
    }
    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
        us80893310.state = 0;
        return;
    }
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
        if (g_Minigame.wallBallRotatePitchersInd != 0) {
            return;
        }
        idx = (s8)g_Minigame.minigamePlayerSelectedOrder;
    }

    if (us80893314[0] != 0) {
        stage = 0;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE && !g_d_GameSettings.minigamesEnabled) {
            if (g_Pitcher.playStartOfGameAnimation != 0) {
                g_Pitcher.playStartOfGameAnimation = 0;
                stage = 1;
                if (getAdjustedPitcherStamina(g_GameLogic.teamFielding, g_Pitcher.rosterID, 0) < lbl_3_data_5EDC[3]) {
                    stage = 2;
                }
            } else if (g_Pitcher.nPitchesThisAB == 0 && g_Pitcher.nPickoffAttempts == 0) {
                if (getAdjustedPitcherStamina(g_GameLogic.teamFielding, g_Pitcher.rosterID, 0) < lbl_3_data_5EDC[3]) {
                    stage = 2;
                }
            }
        }
        if (stage == 2) {
            AnimateCharacter(idx, 0x46, 0, 1, 1, 0, flag, 0);
            QueueCharacterAnimation(idx, 0x3F, 1, 1, 0, flag, -1);
        } else if (stage == 1) {
            AnimateCharacter(idx, 0x48, 0, 1, 1, 0, flag, 0);
            QueueCharacterAnimation(idx, 0x3F, 1, 1, 0, flag, -1);
        } else {
            AnimateCharacter(idx, 0x3F, 1, 1, 1, 0, flag, 0);
            us80893310.state = 1;
        }
        return;
    }

    if (g_Pitcher.pitchTotalTimeCounter == 0) {
        if (us80893310.state != 1) {
            if (!(g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_PITCHING &&
                  g_Practice.instructionNumber < 0 && g_Practice.guidedPracticeCompletionRelated != 0)) {
                if (obj->_64 != 0x41 && obj->_64 != 0x43) {
                    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
                        if (g_Minigame.soloMinigameDifficulty != 3) {
                            AnimateCharacter(idx, 0x3F, 1, 1, 1, 0, flag, 0xC);
                        } else if (g_Minigame.miniGameTurnCounter == 0) {
                            AnimateCharacter(idx, 0x3F, 1, 1, 1, 0, flag, 0xC);
                        } else {
                            AnimateCharacter(idx, 0x3F, 1, 2, 1, 0, flag, 0xC);
                        }
                    } else {
                        AnimateCharacter(idx, 0x3F, 1, 2, 1, 0, flag, 0xC);
                    }
                }
            }
        }
        us80893310.state = 1;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            return;
        }
        if ((u8)(g_d_GameSettings.GameModeSelected - 6) <= 1) {
            return;
        }
        us80893310.timer = (us80893310.timer < 0x7FFE) ? us80893310.timer + 1 : 0x7FFF;
        if (us80893310.timer > 0x244 && g_Ball.StaticRandomInt1 % 0x78 == 0) {
            us80893310.timer = 0;
            AnimateCharacter(idx, 0x47, 0, 2, 1, 0, flag, -1);
            QueueCharacterAnimation(idx, 0x3F, 1, 1, 0, flag, 0xC);
        }
        return;
    }

    us80893310.timer = 0;
    if (g_Pitcher.pitchTotalTimeCounter == 1) {
        stage = 1;
        if (g_Pitcher.ChargePitchType >= 1 || g_Pitcher.TypeOfPitch != 0) {
            AnimateCharacter(idx, 0x40, 0, 1, 1, 0, flag, -1);
            stage = 0;
            g_Pitcher.windupCountdownUntilBallReleased = g_Pitcher.pitchWindUpCountDown;
        } else {
            AnimateCharacter(idx, 0x42, 0, 1, 1, 0, flag, -1);
            g_Pitcher.windupCountdownUntilBallReleased = g_Pitcher.curvePitchWindupFrames;
        }
        if (obj->_252 == 0xB || obj->_252 == 0x1B) {
            stage = 0;
        }
        if (obj->_252 == 3 || obj->_252 == 0xE || (u8)(obj->_252 - 0x25) <= 1 ||
            characterStaticIndexes[obj->_252][2] == 0x17) {
            QueueCharacterAnimation(idx, 0x3F, 1, 1, 0, flag, 0xC);
        } else {
            QueueCharacterAnimation(idx, stage + 0x49, 1, 1, 0, flag, -1);
        }
        us80893310.state = 2;
        return;
    }

    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL && g_Minigame.soloMinigameDifficulty == 3) {
        if (g_Minigame._1A8C[0] == 0) {
            return;
        }
        if (obj->animId == 0x40) {
            AnimateCharacter(idx, 0x41, 0, 1, 1, 0, flag, -1);
        } else {
            AnimateCharacter(idx, 0x43, 0, 1, 1, 0, flag, -1);
        }
        QueueCharacterAnimation(idx, 0x3F, 1, 1, 0, flag, 0xC);
        us80893310.state = 3;
        g_Minigame._1A8C[0] = 0;
        return;
    }

    if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_NO_CONTACT && g_Ball.postPitchResultCounter > 1 &&
        us80893310.state != 3) {
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL && g_Minigame.soloMinigameDifficulty != 3) {
            return;
        }
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_PITCHING && g_Practice.instructionNumber < 0 &&
            g_Practice.guidedPracticeCompletionRelated != 0) {
            if (us80893310.state != 4) {
                AnimateCharacter(idx, 0x44, 0, 2, 1, 0, flag, -1);
            }
            us80893310.state = 4;
            return;
        }
        if (g_Pitcher.miniGameRelated != 0) {
            u8 variant;

            if (obj->_252 == 3 || obj->_252 == 0xE || (u8)(obj->_252 - 0x25) <= 1 ||
                characterStaticIndexes[obj->_252][2] == 0x17) {
                AnimateCharacter(idx, 0x3F, 1, 2, 1, 0, flag, 0xC);
                us80893310.state = 3;
                return;
            }
            if (obj->animId == 0x40 || obj->animId == 0x42) {
                variant = 2;
            } else {
                variant = 1;
            }
            if (obj->animId == 0x40 || obj->animId == 0x49) {
                AnimateCharacter(idx, 0x41, 0, variant, 1, 0, flag, 0xC);
            } else {
                AnimateCharacter(idx, 0x43, 0, variant, 1, 0, flag, 0xC);
            }
            QueueCharacterAnimation(idx, 0x3F, 1, 1, 0, flag, 0xC);
            us80893310.state = 3;
        }
    } else if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_HIT) {
        u8 outcome = g_Pitcher.strikeOutOrWalk;

        if ((outcome == 1 && us80893310.state != 4) || ((outcome == 2 || outcome == 3) && us80893310.state != 5)) {
            if (obj->framesLeft == 0 || obj->animId == 0x49 || obj->animId == 0x4A) {
                if (outcome == 1) {
                    if (characterStaticIndexes[obj->_252][2] == 0xB) {
                        AnimateCharacter(idx, 0x44, 0, 1, 1, 0, flag, 0);
                    } else {
                        AnimateCharacter(idx, 0x44, 0, 1, 1, 0, flag, -1);
                    }
                    us80893310.state = 4;
                } else {
                    AnimateCharacter(idx, 0x45, 0, 1, 1, 0, flag, -1);
                    us80893310.state = 5;
                }
                g_Pitcher.pitcher.x = g_UnkAnimation_31EAC[0].target.x;
                g_Pitcher.pitcher.z = g_UnkAnimation_31EAC[0].target.z;
                if (g_d_GameSettings.minigamesEnabled) {
                    InMemFielder* f = &g_Fielders[(s8)g_Minigame.minigameFielderIndex[(s8)g_Minigame.minigamePlayerSelectedOrder]];

                    f->pos.x = g_UnkAnimation_31EAC[0].target.x;
                    f->pos.z = g_UnkAnimation_31EAC[0].target.z;
                } else {
                    g_Fielders[0].pos.x = g_UnkAnimation_31EAC[0].target.x;
                    g_Fielders[0].pos.z = g_UnkAnimation_31EAC[0].target.z;
                }
                probe.src.x = g_Fielders[0].pos.x;
                probe.src.y = -1.0f;
                probe.src.z = g_Fielders[0].pos.z;
                probe.dst.x = g_Fielders[0].pos.x;
                probe.dst.y = 1.0f;
                probe.dst.z = g_Fielders[0].pos.z;
                checkCollision(&probe, &hit, 0, FALSE);
                g_Fielders[0].actionYOffset = -hit.position.y;
                g_Fielders[0].storedPosY = -hit.position.y;
            }
        }
    }
}

// .text:0x00063AF8 size:0x10E4 mapped:0x806A2B8C
void batterAnimations(void) {
    int idx = 9;
    u8 hand = g_Batter.batterHand ^ 1;
    AnimObject* obj;
    BOOL runnerForced;
    BOOL trigger;
    u8 status;
    int i;

    if (hugeAnimStruct._307D != 0) {
        return;
    }
    if (g_d_GameSettings.minigamesEnabled) {
        if ((s8)g_Minigame.rosterID < 0) {
            return;
        }
        idx = ((s8*)&g_Minigame)[0x18CC + (s8)g_Minigame.rosterID];
    }

    obj = hugeAnimStruct.objects[idx];
    if (obj == NULL) {
        return;
    }

    if (obj->animId == 0x5D || (u16)(obj->animId - 0x5E) <= 1 || obj->animId == 0x60) {
        if (obj->_6A == 1) {
            playCharacterSound(obj->_252, 10);
        }
    }
    if (obj->animId == 0x52 || obj->animId == 0x65) {
        lbl_3_common_bss_32220._08 = 4;
    }

    if (lbl_3_common_bss_32220._08 == 0) {
        status = g_FieldingLogic.liveBallBcOfPickoffOrStealCd;
        if (status == 1 || status == 2 || status == 3) {
            if (g_Strikes.outs < 3) {
                AnimateCharacter(idx, 0x65, 1, 1, 1, 0, hand, 0xA);
            }
            goto done;
        }

        if (us80893314[0] == 0) {
            u8 reason = g_Runners[0].batterStayInBattersBoxReason;

            if (reason == 0) {
                goto done;
            }
            if (reason >= 2) {
                if (lbl_3_common_bss_32220._09 != 0) {
                    goto done;
                }
                if (g_Batter.hitTrajectory == HIT_TRAJECTORY_2) {
                    lbl_3_common_bss_32220._09 = 1;
                } else if (g_Batter.hitTrajectory == HIT_TRAJECTORY_5) {
                    if (g_Ball.framesSinceHit >= 5) {
                        lbl_3_common_bss_32220._09 = 1;
                    }
                } else if (g_Batter.hitTrajectory == HIT_TRAJECTORY_6) {
                    AnimateCharacter(idx, 0x64, 0, 2, 1, 0, hand, -1);
                    lbl_3_common_bss_32220._09 = 1;
                } else if (g_Batter.hitTrajectory == HIT_TRAJECTORY_3) {
                    AnimateCharacter(idx, 0x63, 0, 2, 1, 0, hand, -1);
                    lbl_3_common_bss_32220._09 = 1;
                } else if (g_Batter.hitTrajectory == HIT_TRAJECTORY_4) {
                    AnimateCharacter(idx, 0x51, 0, 2, 1, 8, hand, 0);
                    QueueCharacterAnimation(idx, 0x52, 1, 1, 0, hand, -1);
                    lbl_3_common_bss_32220._09 = 1;
                }
                goto done;
            }
        }

        if (us80893314[0] != 0) {
            trigger = FALSE;
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
                if (g_d_GameSettings.GameModeSelected == 6) {
                    if (g_Minigame._19A5 != 0) {
                        g_Minigame._19A5 = 0;
                        trigger = TRUE;
                    }
                } else if (g_Pitcher.nPitchesThisAB == 0 && g_Pitcher.nPickoffAttempts == 0 &&
                           ((u8*)&g_GameLogic)[0x12A] == 1) {
                    trigger = TRUE;
                }
            }
            if (g_GameLogic.scoutFlag_VsScreenInd != 0) {
                trigger = FALSE;
            }
            if (trigger) {
                AnimateCharacter(idx, 0x67, 0, 1, 1, 0, hand, 0);
                QueueCharacterAnimation(idx, 0x4B, 1, 1, 0, hand, 0);
            } else {
                AnimateCharacter(idx, 0x4B, 1, 2, 1, 0, hand, 0);
                lbl_3_common_bss_32220._09 = 0;
                lbl_3_common_bss_32220._00 = 0;
            }
            goto done;
        }

        if (g_Ball.totalFramesAtPlay == 3 || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
            if (g_Batter.swingInd == 0 && g_Batter.buntStatus == BUNT_STATUS_NONE) {
                AnimateCharacter(idx, 0x4B, 1, 2, 1, 0, hand, 0xA);
                lbl_3_common_bss_32220._09 = 0;
                lbl_3_common_bss_32220._00 = 0;
            }
        }
        if (g_Pitcher.pitchTotalTimeCounter == 0) {
            if (g_Batter.swingInd != 0 || g_Batter.buntStatus != BUNT_STATUS_NONE) {
                lbl_3_common_bss_32220._00 = 0;
            }
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE && g_d_GameSettings.GameModeSelected != 7) {
                lbl_3_common_bss_32220._00 = (lbl_3_common_bss_32220._00 < 0x7FFE) ? lbl_3_common_bss_32220._00 + 1 : 0x7FFF;
                if (lbl_3_common_bss_32220._00 > 0x258 && g_Batter.chargeStatus == CHARGE_SWING_STAGE_NONE &&
                    g_Ball.StaticRandomInt1 % 0x78 == 0) {
                    lbl_3_common_bss_32220._00 = 0;
                    AnimateCharacter(idx, 0x66, 0, 2, 1, 0, hand, -1);
                    QueueCharacterAnimation(idx, 0x4B, 1, 1, 0, hand, 0xF);
                }
            }
        }

        if (g_Batter.chargeStatus != CHARGE_SWING_STAGE_NONE && g_Batter.swingInd == 0) {
            if (g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_HIT) {
                if (g_Batter.chargeStatus == CHARGE_SWING_STAGE_RELEASE) {
                    if (obj->animId != 0x58 && obj->animId != 0x68 && obj->animId != 0x4B) {
                        if (obj->animId == 0x55) {
                            AnimateCharacter(idx, 0x58, 1, 1, 1, 0, hand, 0x14);
                            QueueCharacterAnimation(idx, 0x4B, 1, 1, 0, hand, 0xC);
                        } else {
                            AnimateCharacter(idx, 0x68, 0, 1, 1, 0, hand, 0x14);
                            QueueCharacterAnimation(idx, 0x4B, 1, 1, 0, hand, 0xC);
                        }
                    }
                } else if (g_Batter.chargeStatus == CHARGE_SWING_STAGE_CHARGEUP && g_Batter.chargeFrames == 1) {
                    if (obj->animId == 0x4B) {
                        AnimateCharacter(idx, 0x4C, 0, 3, 1, g_Batter.chargeFrames, hand, 0x14);
                    } else {
                        AnimateCharacter(idx, 0x4C, 0, 3, 1, g_Batter.chargeFrames, hand, 0);
                    }
                    QueueCharacterAnimation(idx, 0x55, 1, 1, 0, hand, 0xC);
                }
            }
        } else if (lbl_3_common_bss_32220._0B != 0) {
            if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_NO_CONTACT && g_Ball.postPitchResultCounter >= 3) {
                lbl_3_common_bss_32220._0B = 0;
                if (obj->animId == 0x55) {
                    AnimateCharacter(idx, 0x58, 0, 1, 1, 0, hand, 0x14);
                    QueueCharacterAnimation(idx, 0x4B, 1, 1, 0, hand, -1);
                } else {
                    AnimateCharacter(idx, 0x68, 0, 1, 1, 0, hand, 0x14);
                    QueueCharacterAnimation(idx, 0x4B, 1, 1, 0, hand, 0xC);
                }
            } else {
                lbl_3_common_bss_32220._04++;
            }
        } else if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_WINDUP && g_Batter.buntStatus == BUNT_STATUS_NONE &&
                   g_Batter.swingInd == 0 && g_Pitcher.windupCountdownUntilBallReleased <= 8) {
            AnimateCharacter(idx, 0x57, 0, 3, 1, 0, hand, 0x14);
            QueueCharacterAnimation(idx, 0x56, 1, 1, 0, hand, 0);
            lbl_3_common_bss_32220._0B = 1;
            lbl_3_common_bss_32220._04 = 0;
        }

        if (g_Batter.buntStatus != BUNT_STATUS_NONE) {
            lbl_3_common_bss_32220._0B = 0;
            if (g_Pitcher.strikeOutOrWalk != 2) {
                if (g_Batter.missedBuntStatus == 1) {
                    AnimateCharacter(idx, 0x5C, 0, 1, 1, 0, hand, -1);
                    QueueCharacterAnimation(idx, 0x4B, 1, 1, 0, hand, 0xA);
                } else if (g_Batter.buntStatus == BUNT_STATUS_STARTING) {
                    if (g_Pitcher.framesUntilUnhittable > 5 && g_Pitcher.framesUntilUnhittable < 0xF) {
                        AnimateCharacter(idx, 0x59, 0, 1, 1, 5, hand, -1);
                        goto tail;
                    }
                    AnimateCharacter(idx, 0x59, 0, 1, 1, 0, hand, -1);
                } else if (g_Batter.buntStatus == BUNT_STATUS_SHOWING) {
                    AnimateCharacter(idx, 0x5A, 0, 2, 1, 0, hand, -1);
                } else if (g_Batter.buntStatus == BUNT_STATUS_LATE && g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_NO_CONTACT &&
                           g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_HIT) {
                    AnimateCharacter(idx, 0x5B, 0, 1, 1, 0, hand, -1);
                } else if (g_Batter.buntStatus == BUNT_STATUS_LATE && g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_NO_CONTACT) {
                    AnimateCharacter(idx, 0x4B, 1, 2, 1, 0, hand, 0xF);
                } else if (g_Batter.buntStatus == BUNT_STATUS_RETREATING || g_Batter.buntStatus == BUNT_STATUS_7) {
                    if (obj->animId != 0x4B) {
                        AnimateCharacter(idx, 0x5B, 0, 1, 1, 0, hand, -1);
                    }
                }
            }
            if (obj->animId == 0x5B && obj->_64 != 0x4B && obj->_6A > 0 && g_Batter.buntStatus != BUNT_STATUS_STARTING &&
                lbl_3_common_bss_32220._0B == 0) {
                AnimateCharacter(idx, 0x4B, 1, 2, 1, 0, hand, 0xF);
            }
        } else if (g_Batter.swingInd != 0) {
            lbl_3_common_bss_32220._0B = 0;
            if (g_Batter.framesSinceStartOfSwing == 1) {
                if (g_Batter.swingMissThatWasHittable != 0) {
                    lbl_3_common_bss_32220._0C = g_Pitcher.framesUntilBallReachesBatterZ - 6;
                } else {
                    lbl_3_common_bss_32220._0C = 0;
                }
                lbl_3_common_bss_32220._0D = 0;
            }
            if (lbl_3_common_bss_32220._0C <= 0 && lbl_3_common_bss_32220._0D == 0) {
                if (g_Batter.hitGeneralType == 0) {
                    AnimateCharacter(idx, 0x4D, 0, 1, 1, -lbl_3_common_bss_32220._0C, hand, 2);
                    QueueCharacterAnimation(idx, 0x50, 0, 1, 0, hand, 0);
                } else {
                    AnimateCharacter(idx, 0x53, 0, 1, 1, -lbl_3_common_bss_32220._0C, hand, 2);
                    QueueCharacterAnimation(idx, 0x54, 0, 1, 0, hand, 0);
                }
                lbl_3_common_bss_32220._0D = 1;
            } else {
                lbl_3_common_bss_32220._0C--;
            }
            if (obj->animId == 0x50 || obj->animId == 0x54) {
                if (obj->_64 != 0x4E && obj->_64 != 0x4F && obj->_6A > 0) {
                    if (obj->animId == 0x54) {
                        AnimateCharacter(idx, 0x4F, 0, 2, 1, 0, hand, -1);
                    } else {
                        AnimateCharacter(idx, 0x4E, 0, 2, 1, 0, hand, -1);
                    }
                }
            }
            if (obj->animId == 0x4E || obj->animId == 0x4F) {
                if (obj->_64 != 0x4B && obj->_6A > 0 && lbl_3_common_bss_32220._0B == 0) {
                    AnimateCharacter(idx, 0x4B, 1, 2, 1, 0, hand, 0xA);
                }
            }
        }

tail:
        runnerForced = FALSE;
        for (i = 1; i < 4; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 1 && g_Runners[i].furthestBaseForcedToGoToOnWalk != 0) {
                runnerForced = TRUE;
            }
        }

        if (g_Batter.hitByPitch != 0) {
            if (lbl_3_common_bss_32220._08 == 0 || lbl_3_common_bss_32220._08 == 5) {
                AnimateCharacter(idx, 0x62, 0, 1, 1, 0, hand, -1);
                lbl_3_common_bss_32220._08 = 3;
                playCharacterSound(g_Batter.charID, 10);
            }
        } else {
            trigger = FALSE;
            if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_HIT) {
                trigger = TRUE;
            } else if (g_Strikes.GameControls_StrikeBallBitVector >= 0x20 && g_Batter.missSwingOrBunt == DID_SWING_TYPE_SWING &&
                       (obj->animId == 0x4D || obj->animId == 0x53) && obj->framesLeft == 1 && g_Batter.contactMadeInd == 0) {
                trigger = TRUE;
            }

            if (g_Pitcher.strikeOutOrWalk == 2) {
                if (runnerForced) {
                    if (g_Ball.framesSinceHit > 0) {
                        AnimateCharacter(idx, 0x66, 0, 1, 1, 0, hand, -1);
                    }
                } else if (g_Batter.buntStatus == BUNT_STATUS_LATE) {
                    AnimateCharacter(idx, 0x61, 0, 1, 1, 0, hand, 0);
                } else {
                    AnimateCharacter(idx, 0x61, 0, 1, 1, 0, hand, 0);
                }
            } else if (trigger && lbl_3_common_bss_32220._08 == 0) {
                if (g_Batter.buntStatus == BUNT_STATUS_LATE) {
                    AnimateCharacter(idx, 0x5F, 0, 1, 1, 0, hand, -1);
                    lbl_3_common_bss_32220._08 = 1;
                } else if (obj->animId == 0x4D || obj->animId == 0x53) {
                    if (runnerForced && g_Strikes.storedOuts < 2) {
                        AnimateCharacter(idx, 0x5E, 0, 2, 1, 0, hand, -1);
                        QueueCharacterAnimation(idx, 0x66, 1, 1, 0, hand, -1);
                    } else if (obj->animId == 0x53) {
                        AnimateCharacter(idx, 0x60, 0, 2, 1, 0, hand, -1);
                    } else {
                        AnimateCharacter(idx, 0x5E, 0, 2, 1, 0, hand, -1);
                    }
                    lbl_3_common_bss_32220._08 = 1;
                } else if ((u16)(obj->animId - 0x4B) <= 1 || (u16)(obj->animId - 0x55) <= 3 || obj->animId == 0x68) {
                    AnimateCharacter(idx, 0x5F, 0, 1, 1, 0, hand, -1);
                    lbl_3_common_bss_32220._08 = 1;
                } else if (obj->animId == 0x4E || obj->animId == 0x4F) {
                    AnimateCharacter(idx, 0x5F, 0, 2, 1, 0, hand, -1);
                    lbl_3_common_bss_32220._08 = 1;
                }
            }
        }
    }

done:
    obj->_273 = 1;
}

// .text:0x00063A38 size:0xC0 mapped:0x806A2ACC
void runnerAnimations(void) {
    int i;

    for (i = 0; i < 4; i++) {
        RunnerAnimSlot* slot = &lbl_3_common_bss_321A0[i];
        InMemRunnerType* runner = &g_Runners[i];

        slot->prevState = slot->state;
        if (g_d_GameSettings.minigamesEnabled && (s8)g_Minigame.runnerPlayerIndexU8[i] < 0) {
            continue;
        }
        if (runner->runnerOnFieldOrOutOrScored == 0) {
            slot->state = 0;
        } else {
            slot->state = 3;
            slot->speed = runner->groundVelocity[0];
            slot->direction = runner->runningDirectionCode;
            runnerAnimation_detailed(i);
            runnerAnimation_general(i);
        }
    }
}

// .text:0x00063874 size:0x1C4 mapped:0x806A2908
void runnerAnimation_detailed(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    RunnerAnimSlot* slot = &lbl_3_common_bss_321A0[runnerIdx];

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT && g_Minigame.ccs.runnerChompHitState[runnerIdx] == 1) {
        slot->state = 0x11;
        return;
    }
    if (runner->batterStayInBattersBoxReason != 0) {
        slot->state = 1;
    } else if (runner->actionCode != 0) {
        slot->state = 8;
    } else if (runner->overRun1BStage >= 2) {
        if (runner->overRun1BStage == 2) {
            slot->state = 9;
        } else {
            slot->state = 0xA;
        }
    } else if (runner->overrunBaseStage >= 2) {
        if (runner->overrunBaseStage == 2) {
            slot->state = 0xB;
        } else {
            slot->state = 0xC;
        }
    } else if (runner->runningToDugoutInd == 1) {
        slot->state = 0xD;
    } else if (runner->runningToDugoutInd != 0) {
        slot->state = 0xE;
    } else if (runner->leadOffStatus == 1) {
        slot->state = 0xF;
    } else if (runner->leadOffStatus == 2) {
        slot->state = 0x10;
    } else if (runner->turnaroundCode != 0) {
        slot->state = 5;
    } else if (runner->runningDirectionCode == 1 || runner->runningDirectionCode == 3) {
        if (runner->turningAroundInd != 0 && runner->framesSinceLastDirectionChange < lbl_3_data_7870[runner->charID][0]) {
            slot->state = 7;
        } else {
            slot->state = 2;
        }
    } else if (runner->baseStandingOn >= 0) {
        slot->state = 3;
    } else {
        slot->state = 4;
    }
}

// .text:0x000631AC size:0x6C8 mapped:0x806A2240
void runnerAnimation_general(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    RunnerAnimSlot* slot = &lbl_3_common_bss_321A0[runnerIdx];
    int idx = runnerIdx + 9;
    AnimObject* obj = hugeAnimStruct.objects[idx];
    s16 animId;
    BOOL flag;
    u8 cls;

    if (g_d_GameSettings.minigamesEnabled) {
        idx = g_Minigame.playerSlots.runnerPlayerIndex[runnerIdx];
        obj = hugeAnimStruct.objects[idx];
    }
    if (obj != NULL) {
        animId = obj->animId;
    }

    switch (slot->state) {
        case 0:
            return;
        case 2:
            flag = FALSE;
            cls = characterStaticIndexes[runner->charID][2];
            if (cls == 0xE || cls == 0x14 || cls == 0x1A || cls == 0x1E) {
                flag = TRUE;
            }
            if (runner->runningDirectionCode == 1 && runner->framesToNextBase < 10 &&
                g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT && flag) {
                AnimateCharacter(idx, 0x2E, 0, 1, 0, (s16)(lbl_3_data_7870[runner->charID][2] - 10), 0, -1);
            } else if (animId == 0x31) {
                AnimateCharacter(idx, 0x2D, 1, 2, 0, 0, 0, -1);
            } else {
                AnimateCharacter(idx, 0x2D, 1, 1, 0, 0, 0, -1);
            }
            break;
        case 3:
            if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_NONE) {
                AnimateCharacter(idx, 0x39, 1, 1, 1, 0, 0, -1);
            } else if (characterStaticIndexes[runner->charID][2] == 0xC) {
                AnimateCharacter(idx, 0x39, 1, 1, 1, 0, 0, -1);
            } else {
                AnimateCharacter(idx, 0x38, 1, 1, 1, 0, 0, -1);
            }
            break;
        case 4:
            AnimateCharacter(idx, 0x39, 1, 1, 1, 0, 0, -1);
            break;
        case 5:
            if (runner->runningDirectionCode == 3) {
                AnimateCharacter(idx, 0x30, 0, 1, 0, 0x14, 1, -1);
            } else {
                AnimateCharacter(idx, 0x30, 0, 1, 0, 0x14, 0, -1);
            }
            break;
        case 7:
            if (runner->runnerDirectionCode_stored == 3) {
                AnimateCharacter(idx, 0x31, 0, 1, 0, 0, 1, 0);
            } else {
                AnimateCharacter(idx, 0x31, 0, 1, 0, 0, 0, 0);
            }
            break;
        case 8:
            if (runner->actionStage == 1) {
                if (runner->actionFrames_countUp == 1) {
                    if (runner->actionCode == 2) {
                        AnimateCharacter(idx, 0x33, 0, 1, 1, (s16)(runnerConstants[runner->charID][2] - runner->actionFrames_countDown), 1, -1);
                    } else if (runner->actionCode == 3) {
                        AnimateCharacter(idx, 0x33, 0, 1, 1, (s16)(runnerConstants[runner->charID][2] - runner->actionFrames_countDown), 1, -1);
                    } else if (runner->actionInForwardDirectionInd != 0 && runner->nextBase != 0) {
                        AnimateCharacter(idx, 0x32, 0, 1, 1, (s16)(runnerConstants[runner->charID][2] - runner->actionFrames_countDown), 1, -1);
                    } else {
                        AnimateCharacter(idx, 0x34, 0, 1, 1, (s16)(runnerConstants[runner->charID][4] - runner->actionFrames_countDown), 0, -1);
                    }
                    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
                        playSoundEffect(0x171);
                    }
                }
            } else if (runner->actionStage == 2) {
                if (runner->actionFrames_countDown == 1) {
                    AnimateCharacter(idx, 0x38, 1, 1, 1, 0, 0, 0);
                }
            }
            break;
        case 9:
            AnimateCharacter(idx, 0x2D, 1, 1, 0, 0, 0, -1);
            break;
        case 10:
            AnimateCharacter(idx, 0x2F, 1, 1, 0, 0, 0, -1);
            break;
        case 11:
            AnimateCharacter(idx, 0x30, 1, 1, 0, 0, 0, -1);
            break;
        case 12:
            AnimateCharacter(idx, 0x2F, 1, 1, 0, 0, 0, -1);
            break;
        case 13:
            AnimateCharacter(idx, 0x2D, 1, 1, 0, 0, 0, -1);
            break;
        case 14:
            if (runner->slideHomeFrames_CountDown == 0 && runner->velocity.x != 0.0f) {
                AnimateCharacter(idx, 0x2D, 1, 1, 0, 0, 0, -1);
            }
            break;
        case 15:
            AnimateCharacter(idx, 0x35, 0, 1, 0, (s16)(lbl_3_data_7870[runner->charID][1] - runner->leadOffTotalFrameCountDown), 0, -1);
            break;
        case 16:
            AnimateCharacter(idx, 0x39, 1, 1, 1, 0, 0, 0);
            break;
        case 17:
            if (animId != 0x24) {
                playCharacterSound(runner->charID, 10);
            }
            AnimateCharacter(idx, 0x24, 0, 1, 1, 0, 0, 0x14);
            break;
    }
}

// .text:0x00062E70 size:0x33C mapped:0x806A1F04
void fielderAnimations(void) {
    int i;
    int j;
    InMemFielder* fielder;
    AnimSlot* slot;

    g_UnkThrowing_31ACC[0].fielder = g_Ball.fielderWBallIndex;
    if (g_Ball.fielderWBallIndex >= 0 && g_Fielders[g_Ball.fielderWBallIndex].isJump != 0) {
        g_UnkThrowing_31ACC[0].fielder = -1;
    }

    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_NONE) {
        setThrowAnimationType();
        handleRunnerActionsAndTagging();
    }

    for (i = 0; i < 9; i++) {
        fielder = &g_Fielders[i];
        slot = &g_UnkAnimation_31EAC[i];
        slot->_40 = fielder->throwingHandedness;

        if (g_d_GameSettings.minigamesEnabled) {
            for (j = 0; j < 4; j++) {
                if ((s8)g_Minigame.minigameFielderIndex[j] == i) {
                    break;
                }
            }
            if (j >= 4) {
                continue;
            }
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL &&
            (s8)fielder->_020D == (s8)g_Minigame.minigamePlayerSelectedOrder && g_Minigame.wallBallRotatePitchersInd == 0) {
            continue;
        }

        if (i == 0) {
            if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
                continue;
            }
            if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_FieldingLogic.pitcher_inPitchingState != 0) {
                continue;
            }
            if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED || g_GameLogic.gameStatus == GAME_STATUS_STAR_CHANCE_VS) {
                continue;
            }
        }
        if (i == 1) {
            if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT ||
                g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
                catcherIdleAnimation();
                continue;
            }
        }

        slot->speed = fielder->currentVelocity;
        slot->_45 = 0;
        latchCatchAnimation(i);
        shiftFielderAnimCounter(i);
        updateFielderAnimHints(i);
        fielderAnimations_setAnimation(i);
    }
}

// .text:0x00062E28 size:0x48 mapped:0x806A1EBC
void catcherIdleAnimation(void) {
    AnimateCharacter(1, 0x3D, 1, 1, 1, 0, g_Fielders[1].throwingHandedness, 0);
}

// .text:0x00062E04 size:0x24 mapped:0x806A1E98
void shiftFielderAnimCounter(int fielderIdx) {
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];

    slot->_3A = slot->_38;
    slot->_38 = 0;
}

// .text:0x00062D44 size:0xC0 mapped:0x806A1DD8
void updateFielderAnimHints(int fielderIdx) {
    InMemFielder* fielder = &g_Fielders[fielderIdx];
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];
    u8 kind = fielder->animationRelated;

    slot->_41 = 0;
    if (kind == 2) {
        slot->_41 = 1;
    } else if (kind == 3) {
        slot->_41 = 2;
    }

    if (fielder->closingInOnCatchingFlyBall != 0 && g_Ball.AtBat_ContactResult == 0 &&
        fielder->distToWhereFlyBallWillBeAtHalfFielderHeight < fielder->hitbox[0] &&
        g_Ball.framesUntilBallHitsGround < 0x78 && g_Ball.maxYOfHit > 5.0f && g_FieldingLogic._0144 != 0) {
        slot->_45 = 1;
    }
}

// .text:0x00062CA8 size:0x9C mapped:0x806A1D3C
void latchCatchAnimation(int fielderIdx) {
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];
    InMemFielder* fielder = &g_Fielders[fielderIdx];
    AnimObject* obj = hugeAnimStruct.objects[fielderIdx];

    if (slot->_4C == 0) {
        u8 kind = fielder->catchAnimation;

        slot->_4C = kind;
        slot->countdown = fielder->catchAnimationFramesCountDown;
        if (kind == 1 || kind == 2) {
            slot->_4E = fielder->catchVerticalZone;
        }
        if (slot->_4C != 0) {
            slot->_4D = slot->_4C;
        }
    }
    if (obj != NULL && obj->animId == 0x24) {
        slot->_4C = 0;
        slot->_4F = 0;
    }
}

// .text:0x00062B50 size:0x158 mapped:0x806A1BE4
void setThrowAnimationType(void) {
    s16 holder = g_Ball.fielderWBallIndex;
    int target;

    if (holder < 0) {
        g_UnkThrowing_31ACC[0].type = 0;
        return;
    }
    target = g_FieldingLogic.locationThrownTo;
    if (target < 0) {
        g_UnkThrowing_31ACC[0].type = 0;
        return;
    }
    if (g_UnkThrowing_31ACC[0].type != 0) {
        return;
    }

    g_FieldingLogic.throwWindupAnimationDoneInd = 0;
    VEC_COPY(&g_UnkThrowing_31ACC[0].pos, &g_Ball.throwDestination);

    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 1 && holder == 0 && (target == 1 || target == 2 || target == 3) &&
        g_Pitcher.pickOffLoc != 4 && g_Pitcher.pickOffLoc != -1) {
        g_UnkThrowing_31ACC[0].type = 7;
        return;
    }

    if (g_FieldingLogic.throwSpeedType == 8) {
        g_UnkThrowing_31ACC[0].type = 3;
    } else if (g_FieldingLogic.throwSpeedType == 9) {
        g_UnkThrowing_31ACC[0].type = 4;
    } else if (g_FieldingLogic.throwSpeedType == 10) {
        if (holder == 3) {
            g_UnkThrowing_31ACC[0].type = 5;
        } else {
            g_UnkThrowing_31ACC[0].type = 6;
        }
    } else if (g_FieldingLogic.birdoFarThrowInd_forAnimation != 0) {
        g_UnkThrowing_31ACC[0].type = 2;
    } else {
        g_UnkThrowing_31ACC[0].type = 1;
    }
}

// .text:0x00062904 size:0x24C mapped:0x806A1998
void handleRunnerActionsAndTagging(void) {
    int i;
    s16 fielderIdx;
    int state;
    AnimSlot* slot;
    InMemFielder* fielder;
    s16 diff;
    s16 angle;

    if (g_d_GameSettings.minigamesEnabled) {
        return;
    }

    for (i = 0; i < 9; i++) {
        if (g_Fielders[i].bodyCheckResult != 0) {
            if (g_Fielders[i].bodyCheckResult != 0) {
                if (g_UnkAnimation_31EAC[i].state != 8 && g_UnkAnimation_31EAC[i].state != 9) {
                    g_UnkAnimation_31EAC[i].state = 8;
                }
            }
            break;
        }
    }

    fielderIdx = g_Ball.fielderWBallIndex;
    if (fielderIdx < 0 || g_FieldingLogic.tagAnimationType == 0) {
        return;
    }

    fielder = &g_Fielders[fielderIdx];
    slot = &g_UnkAnimation_31EAC[fielderIdx];
    if (g_FieldingLogic.tagOutFirstFrameInd != 0) {
        fielder->someCounter = 0;
    }
    g_UnkThrowing_31ACC[0]._10 = g_FieldingLogic.tagOutFirstFrameInd;

    if (g_FieldingLogic.tagAnimationType == 1) {
        state = 1;
        if (g_FieldingLogic.runnerBeingTargettedForOut >= 0) {
            angle = (s16)calculateAngleFromCoordinates(g_FieldingLogic.tagDirection.x - fielder->pos.x,
                                                  g_FieldingLogic.tagDirection.z - fielder->pos.z);
            diff = angleDifferenceNormalized(angle, (s16)radToShortAngle(fielder->desiredMovementDirection));
            if (diff < -0x280) {
                state = 2;
            } else if (diff > 0x280) {
                state = 3;
            }
        }
        slot->state = state;
    } else if (g_FieldingLogic.tagAnimationType == 2) {
        slot->state = 4;
    } else if (g_FieldingLogic.tagAnimationType == 5) {
        state = 5;
        if (g_FieldingLogic.runnerBeingTargettedForOut >= 0) {
            InMemRunnerType* runner = &g_Runners[g_FieldingLogic.runnerBeingTargettedForOut];
            angle = (s16)calculateAngleFromCoordinates(runner->position.x - fielder->pos.x, runner->position.z - fielder->pos.z);
            diff = angleDifferenceNormalized(angle, (s16)radToShortAngle(fielder->desiredMovementDirection));
            if (diff < -0x1C0) {
                state = 7;
            } else if (diff > 0x1C0) {
                state = 6;
            }
        }
        slot->state = state;
    }
}

// .text:0x00061B64 size:0xDA0 mapped:0x806A0BF8
void fielderAnimations_setAnimation(int fielderIdx) {
    int idx = fielderIdx;
    AnimObject** objects;
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];
    InMemFielder* fielder = &g_Fielders[fielderIdx];
    AnimObject* obj;
    s16 animId;
    int anim;

    if (g_d_GameSettings.minigamesEnabled) {
        if (idx == 0) {
            idx = MINIGAME_SELECTED_SLOT();
        } else {
            idx = ((s8*)&g_Minigame)[0x18CC + fielder->_020D];
        }
    }

    objects = hugeAnimStruct.objects;
    obj = objects[idx];
    if (obj == NULL) {
        return;
    }

    animId = obj->animId;
    if (g_UnkThrowing_31ACC[0].fielder == fielderIdx && g_Ball.fielderWBallIndex == fielderIdx) {
        obj->_274 = 1;
    }

    if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_WALLBALL) {
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC) {
            u8 state = g_Minigame.pP_hitState[fielder->_020D];
            if (state == 1) {
                if (animId != 0x24) {
                    playCharacterSound(fielder->CharID, 10);
                }
                AnimateCharacter(idx, 0x24, 1, 1, 0, 0, 0, -1);
                slot->_43 = 0;
                goto done;
            }
            if (state == 2) {
                AnimateCharacter(idx, 0, 1, 1, 0, 0, 0, -1);
                goto done;
            }
            if (minigameFielderAnimCheck(fielderIdx)) {
                goto done;
            }
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH && g_Minigame.starDashStunType[fielder->_020D] == 2) {
            if (animId == 0x24 || animId == 0x25) {
                goto done;
            }
            playCharacterSound(fielder->CharID, 10);
            AnimateCharacter(idx, 0x24, 0, 1, 0, 0, 0, -1);
            QueueCharacterAnimation(idx, 0x25, 0, 0, 0, 0, 0);
            goto done;
        }
        if (fielder->knockoutStatus != 0) {
            if (fielder->knockoutStatus == 1) {
                if (fielder->knockOutCountUp == 1) {
                    updateFielderState(fielderIdx, 0);
                    if (animId != 0x24) {
                        playCharacterSound(fielder->CharID, 10);
                    }
                    AnimateCharacter(idx, 0x24, 0, 1, 0, 0, slot->_40, -1);
                }
            } else {
                if (fielder->knockOutCountUp == 1) {
                    AnimateCharacter(idx, 0x25, 0, 1, 1, 0, slot->_40, 0);
                    updateFielderState(fielderIdx, 1);
                }
                if (fielder->knockOutCountDown == 1) {
                    AnimateCharacter(idx, 0, 1, 1, 0, 0, slot->_40, -1);
                    updateFielderState(fielderIdx, 0);
                }
            }
            slot->_43 = 0;
            goto done;
        }
        if (animationsForFielding(fielderIdx)) {
            if (!fielderThrowingAnimations(fielderIdx)) {
                fielderBodyCheckAnimation(fielderIdx);
            }
            goto done;
        }
        if (fielder->onFire != 0) {
            if (fielder->onFireCountUp == 0) {
                updateFielderState(fielderIdx, 0);
            }
            AnimateCharacter(idx, 0x10, 1, 1, 0, 0, slot->_40, 0);
            if (animId != 0x10) {
                playCharacterSound(fielder->CharID, 11);
            }
            slot->_43 = 0;
            goto done;
        }
        if (g_UnkThrowing_31ACC[0].fielder == fielderIdx) {
            if (fielderThrowingAnimations(fielderIdx)) {
                goto done;
            }
            if (fielderBodyCheckAnimation(fielderIdx)) {
                goto done;
            }
            if (fielder->clamberStatus >= 3) {
                AnimateCharacter(idx, 0x27, 0, 1, 0, 0, slot->_40, -1);
                goto done;
            }
            if (slot->speed > 0.02f) {
                if (g_Strikes.outs >= 3 && fielder->fielderVeloAdjustmentCode == 0xD) {
                    AnimateCharacter(idx, 7, 1, 1, 0, 0, slot->_40, -1);
                    goto done;
                }
                if (g_Ball.fielderWBallIndex == fielderIdx && fielder->distanceToMound < 30.0f) {
                    if (animId == 5) {
                        AnimateCharacter(idx, 0x22, 1, 2, 0, 0, slot->_40, -1);
                    } else {
                        AnimateCharacter(idx, 0x22, 1, 1, 0, 0, slot->_40, -1);
                    }
                    goto done;
                }
                if (slot->speed > 0.1f) {
                    if (animId == 0x22) {
                        AnimateCharacter(idx, 5, 1, 2, 0, 0, slot->_40, -1);
                    } else {
                        AnimateCharacter(idx, 5, 1, 1, 0, 0, slot->_40, -1);
                    }
                } else {
                    AnimateCharacter(idx, 7, 1, 1, 0, 0, slot->_40, -1);
                }
                goto done;
            }
            AnimateCharacter(idx, 1, 1, 1, 1, 0, slot->_40, -1);
            goto done;
        }
        slot->_44 = 0;
        if (fielderThrowWindupDone(fielderIdx)) {
            goto done;
        }
    }

    if (fielder->bodyCheckResult != 0 && fielder->bodyCheckStatus == 3) {
        if (g_FieldingLogic.bodyCheckStageCountdown > 1) {
            goto done;
        }
        updateFielderState(idx, 0);
        slot->_44 = 0;
        slot->state = 0;
        goto done;
    }
    if (fielder->isJump != 0) {
        AnimateCharacter(idx, 0x26, 0, 1, 0, 0, slot->_40, -1);
        goto done;
    }
    if (fielder->wallSplatStatus != 0) {
        if (fielder->wallSplatStatus == 1) {
            AnimateCharacter(idx, 0x26, 0, 1, 0, 0, slot->_40, -1);
        } else if (fielder->wallSplatStatus == 2) {
            AnimateCharacter(idx, 0x28, 0, 1, 1, 0, slot->_40, -1);
            obj->_26F = 1;
        } else if (fielder->wallSplatStatus == 3) {
            if (fielder->wallSplatStageCountDown == 1) {
                updateFielderState(idx, 1);
            }
        } else if (fielder->wallSplatStatus == 4) {
            obj->_26F = 0;
            if (fielder->wallSplatStageCountDown == 1) {
                AnimateCharacter(idx, 0, 1, 1, 0, 0, slot->_40, -1);
                updateFielderState(idx, 0);
            }
        }
        goto done;
    }
    if (fielder->clamberStatus != 0) {
        if (fielder->clamberStatus == 1) {
            AnimateCharacter(idx, 0x26, 0, 1, 0, 0, slot->_40, -1);
        } else if (fielder->clamberStatus == 2) {
            if (fielder->wjRelated != 0) {
                anim = 0x2A;
                if (fielder->wjRelated == 3) {
                    anim = 0x2B;
                } else if (fielder->wjRelated == 4) {
                    anim = 0x2C;
                }
                if ((u16)(animId - 0x2A) <= 1 || animId == 0x2C) {
                    AnimateCharacter(idx, anim, 1, 2, 1, 0, slot->_40, -1);
                } else {
                    AnimateCharacter(idx, anim, 1, 1, 1, 0, slot->_40, -1);
                }
            } else if (animId == 0x2A) {
                AnimateCharacter(idx, 0x28, 1, 2, 1, 0, slot->_40, -1);
            } else {
                AnimateCharacter(idx, 0x28, 1, 1, 1, 0, slot->_40, 0);
            }
        } else if (fielder->clamberStatus >= 3) {
            AnimateCharacter(idx, 0x27, 0, 1, 0, 0, slot->_40, -1);
        }
        goto done;
    }

    if (slot->speed > 0.01f) {
        if (fielder->closingInOnCatchingFlyBall != 0) {
            s16 cur = radToShortAngle(fielder->desiredMovementDirection);
            s16 diff = angleDifferenceNormalized(cur, calculateAngleFromCoordinates(fielder->velocityX, fielder->velocityZ));
            if (fielder->closingInOnCatchingFlyBall == 1) {
                anim = 8;
                if (diff < -0x600 || diff > 0x600) {
                    anim = 9;
                } else if (diff > 0x200) {
                    if (slot->_40 == 0) {
                        anim = 0xA;
                    } else {
                        anim = 0xB;
                    }
                } else if (diff < -0x200) {
                    if (slot->_40 == 0) {
                        anim = 0xB;
                    } else {
                        anim = 0xA;
                    }
                }
            }
            AnimateCharacter(idx, anim, 1, 1, 0, 0, slot->_40, -1);
        } else if (fielder->wallActionAbility == 1 && animId == 0x28) {
            AnimateCharacter(idx, 2, 1, 2, 1, 0, slot->_40, -1);
            fielder->_020A = 1;
        } else if (slot->speed > 0.1f) {
            AnimateCharacter(idx, 5, 1, 1, 0, 0, slot->_40, -1);
        } else {
            AnimateCharacter(idx, 7, 1, 1, 0, 0, slot->_40, -1);
        }
    } else {
        int a7;

        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL && animId >= 0x3F && animId < 0x4B) {
            return;
        }
        anim = 2;
        if (slot->_41 == 1) {
            anim = 0;
        }
        if (animId == 0x24 || animId == 0x25) {
            if (animId == 0x25) {
                AnimateCharacter(idx, 0, 1, 2, 1, 0, slot->_40, -1);
            }
        } else if (slot->_45 != 0) {
            AnimateCharacter(idx, 3, 1, 1, 0, 0, slot->_40, -1);
        } else if (fielder->wallActionAbility == 1 && animId == 0x28) {
            AnimateCharacter(idx, anim, 1, 2, 1, 0, slot->_40, -1);
            fielder->_020A = 1;
        } else if (animId == 0xF) {
            AnimateCharacter(idx, anim, 1, 2, 1, 0, slot->_40, -1);
        } else if (fielderIdx == 1 && g_Ball.framesSinceHit < 0x78) {
            if (g_Ball.framesSinceHit == 0x1E) {
                AnimateCharacter(idx, 0x3E, 0, 1, 1, 0, slot->_40, -1);
            }
        } else if (animId == 0x3E) {
            AnimateCharacter(idx, anim, 1, 2, 1, 0, slot->_40, -1);
        } else {
            a7 = -1;
            if (animId == 0x40 || animId == 0x42 || animId == 0x49 || animId == 0x4A) {
                a7 = 0;
            }
            AnimateCharacter(idx, anim, 1, 1, 1, 0, slot->_40, a7);
        }
    }

done:
    if (slot->_42 != 0) {
        obj->x = slot->pos.x;
        obj->z = slot->pos.z;
        slot->_42 = 1;
    } else {
        slot->_42 = 0;
    }
    if (fielder->wallActionAbility == 1 && animId == 0x28) {
        if (obj->framesLeft <= 1 || obj->_25E == 1) {
            updateFielderState(idx, 0);
        }
    }
}

// .text:0x00061544 size:0x620 mapped:0x806A05D8
BOOL animationsForFielding(int fielderIdx) {
    GameInitVariables* settings = &g_d_GameSettings;
    int idx = fielderIdx;
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];
    InMemFielder* fielder = &g_Fielders[fielderIdx];
    u8* tbl = lbl_3_data_65F0;
    AnimObject* obj;
    int frames = 0;
    int anim = -1;
    u8 state;
    int cd;
    int lim;

    if (settings->minigamesEnabled) {
        if (idx == 0) {
            idx = MINIGAME_SELECTED_SLOT();
        } else {
            idx = MINIGAME_SLOT_OF(idx);
        }
    }

    obj = hugeAnimStruct.objects[idx];
    if (slot->_43 != 0) {
        return FALSE;
    }

    if (slot->_4F == 0) {
        if (fielder->onFire != 0) {
            return FALSE;
        }
        if (fielder->knockoutStatus != 0) {
            return FALSE;
        }
        if (fielder->wallSplatStatus != 0) {
            return FALSE;
        }
        if (slot->_4C != 0) {
            slot->countdown--;
            state = slot->_4C;
            if (state == 1 || state == 2) {
                cd = slot->countdown;
                lim = *(s16*)(tbl + 0x6C);
                if (cd <= lim) {
                    u8 side = fielder->catchCentreRightLeftOfBody;
                    if (side == 0) {
                        anim = ((s16*)(tbl + 0x54))[slot->_4E];
                    } else if ((side == 1 && fielder->throwingHandedness == 0) ||
                               (side == 2 && fielder->throwingHandedness != 0)) {
                        anim = ((s16*)(tbl + 0x54 + 6))[slot->_4E];
                    } else {
                        anim = ((s16*)(tbl + 0x54 + 0xC))[slot->_4E];
                    }
                    frames = lim - cd;
                }
            } else if (state == 7 || state == 8) {
                int variant;
                if (fielder->actionAngleType == 1) {
                    if (slot->_40 != 0) {
                        variant = 0xE;
                    } else {
                        variant = 0xD;
                    }
                } else if (fielder->actionAngleType == 2) {
                    if (slot->_40 != 0) {
                        variant = 0xD;
                    } else {
                        variant = 0xE;
                    }
                } else {
                    variant = 0xC;
                }
                AnimateCharacter(idx, variant, 1, 1, 0, 0, slot->_40, -1);
                slot->_46 = variant;
                slot->_4F = 1;
                return TRUE;
            } else if (state == 3) {
                cd = slot->countdown;
                lim = ((s16*)(tbl + 0x6C))[1];
                if (cd <= lim) {
                    frames = lim - cd;
                    anim = 0x1B;
                }
            } else if (state == 4) {
                AnimateCharacter(idx, 0x26, 0, 1, 0, (s16)(lbl_3_data_7F0C[0] - fielder->wallJumpFramesTillTopOfWallContact),
                                 slot->_40, -1);
                slot->_46 = 0x26;
                slot->_4F = 1;
                return TRUE;
            } else if (state == 5) {
                cd = slot->countdown;
                anim = 0x29;
                frames = tbl[0x10] - cd;
            }

            if (anim < 0 || frames < 0) {
                return FALSE;
            }
            AnimateCharacter(idx, anim, 0, 1, 0, (s16)frames, slot->_40, -1);
            slot->_46 = anim;
            slot->_4F = 1;
            slot->_50 = tbl[0x68];
            return TRUE;
        }

    if (fielder->onFire == 0) {
        if (fielder->_0200 != 0) {
            obj->_26F = 1;
            if (settings->minigamesEnabled) {
                fn_8004AE18(fielder->_020D);
            } else {
                fn_8004AE18(fielderIdx);
            }
        }
        if (slot->_50 != 0) {
            slot->_50--;
        }
        slot->countdown--;
        if (slot->_46 == 0x26) {
            if (fielder->wallJumpFramesTillTopOfWallContact == 1) {
                AnimateCharacter(idx, 0x28, 0, 1, 0, 0, slot->_40, 0);
            }
            if (fielder->wallJumpStatus != 4) {
                return TRUE;
            }
        } else {
            if (slot->countdown == 1) {
                u8 bobble = fielder->bobble;
                if ((bobble != 1 || fielder->catchAnimation != 1) && slot->_4C != 7 && slot->_4C != 8 &&
                    obj->animId != 0x29) {
                    if (bobble == 3 && slot->_4C != 3) {
                        AnimateCharacter(idx, 0x1C, 0, 1, 1, 0, slot->_40, 10);
                        updateFielderState(fielderIdx, 1);
                    } else {
                        updateFielderState(fielderIdx, 1);
                    }
                }
            }
            if (obj->animId == 0x1B) {
                s16 t = g_Ball.timeSinceBallPickedUp;
                if (t >= tbl[0x40] && t <= tbl[0x41] && !checkFieldingStat(g_GameLogic.teamFielding, fielder->rosterLocation, 7) &&
                    !checkFieldingStat(g_GameLogic.teamFielding, fielder->rosterLocation, 8) &&
                    !checkFieldingStat(g_GameLogic.teamFielding, fielder->rosterLocation, 9) &&
                    (g_FieldingLogic.locationThrownTo >= 0 || g_FieldingLogic.humanSelectedPlaceToThrow >= 0) &&
                    slot->_42 != 0) {
                    AnimateCharacter(idx, 0x1A, 0, 1, 1, 0, slot->_40, -1);
                    updateFielderState(fielderIdx, 1);
                }
            }
            if (slot->_4C == 7 || slot->_4C == 8) {
                if (fielder->runningCatchCountDown == 0 && fielder->catchAnimation == 0 && fielder->hitKnockbackCountdown == 0) {
                    AnimateCharacter(idx, 0, 0, 1, 1, 0, slot->_40, -1);
                } else {
                    return TRUE;
                }
            } else if (obj->framesLeft > 1) {
                return TRUE;
            }
        }
    }
    slot->_4C = 0;
    slot->_4F = 0;
    slot->_47 = 0;
    slot->_46 = 0;
    slot->_50 = 0;
    updateFielderState(fielderIdx, 0);
    return FALSE;
    }
    return FALSE;
}

// .text:0x00061228 size:0x31C mapped:0x806A02BC
BOOL fielderThrowingAnimations(int fielderIdx) {
    int idx = fielderIdx;
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];
    InMemFielder* fielder = &g_Fielders[fielderIdx];
    AnimThrowState* throwState = g_UnkThrowing_31ACC;
    g_FieldingLogic_s* fielding = &g_FieldingLogic;
    int anim = 0x1D;
    BOOL isWild = FALSE;
    AnimObject* obj;
    s16 cur;
    s16 timer;

    if (g_d_GameSettings.minigamesEnabled) {
        if (idx == 0) {
            idx = MINIGAME_SELECTED_SLOT();
        } else {
            idx = MINIGAME_SLOT_OF(idx);
        }
    }

    obj = hugeAnimStruct.objects[idx];
    if (obj == NULL) {
        return FALSE;
    }
    if (throwState->fielder != fielderIdx) {
        return FALSE;
    }

    if (slot->_43 != 0) {
        if (fielder->autoMovementFunctionIndex == 0x11) {
            slot->_43 = 0;
            updateFielderState(fielderIdx, 0);
            return FALSE;
        }
        timer = obj->_6A;
        if (timer > 0 && obj->framesLeft <= 0) {
            slot->_43 = 0;
            updateFielderState(fielderIdx, 0);
            return FALSE;
        }
        if (timer >= (lbl_3_data_7D24 + obj->_252 * 5)[obj->animId - 0x1D]) {
            fielding->throwWindupAnimationDoneInd = 1;
        }
        return TRUE;
    }

    if (fielder->throwWindUpFrames != 0) {
        return FALSE;
    }
    if (throwState->type == 0) {
        return FALSE;
    }

    switch (throwState->type) {
        case 2:
            anim = 0x1E;
            break;
        case 3:
            anim = 0x1F;
            break;
        case 4:
            anim = 0x1D;
            break;
        case 5:
            anim = 0x1D;
            break;
        case 6:
            anim = 0x1D;
            break;
        case 7:
            anim = 0x1D;
            isWild = TRUE;
            break;
    }

    if (isWild) {
        int adj;
        int diff;

        cur = (s16)radToShortAngle(fielder->desiredMovementDirection);
        diff = angleDifferenceNormalized(
            cur, (s16)calculateAngleFromCoordinates(throwState->pos.x - fielder->pos.x, throwState->pos.z - fielder->pos.z));
        adj = -diff;
        if (diff < -0x600 || diff > 0x600) {
            if (diff < -0x600) {
                adj = -0x800 - diff;
            } else {
                adj = 0x800 - diff;
            }
        } else if (diff > 0x200) {
            adj = 0x400 - diff;
        } else if (diff < -0x200) {
            adj = -0x400 - diff;
        }
        fielder->desiredMovementDirection = shortAngleToRad_Capped(cur + adj);
    }

    AnimateCharacter(idx, anim, 0, 1, 1, 0, slot->_40, -1);
    throwState->anim = anim;
    slot->_43 = 1;
    if (isWild) {
        slot->_43 = 2;
    }
    slot->_4C = 0;
    slot->_4F = 0;
    slot->_47 = 0;
    slot->_46 = 0;
    slot->_50 = 0;
    updateFielderState(fielderIdx, 1);
    return TRUE;
}

// .text:0x00061148 size:0xE0 mapped:0x806A01DC
BOOL fielderThrowWindupDone(int fielderIdx) {
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];
    int idx = fielderIdx;
    AnimObject* obj;

    if (g_d_GameSettings.minigamesEnabled) {
        if (idx == 0) {
            idx = MINIGAME_SELECTED_SLOT();
        } else {
            idx = MINIGAME_SLOT_OF(idx);
        }
    }

    obj = hugeAnimStruct.objects[idx];
    if (obj == NULL) {
        return FALSE;
    }
    if (slot->_43 != 0) {
        if (obj->framesLeft <= 0) {
            slot->_43 = 0;
            updateFielderState(fielderIdx, 0);
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

// .text:0x00060E90 size:0x2B8 mapped:0x8069FF24
BOOL fielderBodyCheckAnimation(int fielderIdx) {
    int idx = fielderIdx;
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];
    InMemFielder* fielder = &g_Fielders[fielderIdx];
    AnimObject* obj;
    u8 state;
    s16 animId;

    if (g_d_GameSettings.minigamesEnabled) {
        if (idx == 0) {
            idx = MINIGAME_SELECTED_SLOT();
        } else {
            idx = MINIGAME_SLOT_OF(idx);
        }
    }

    obj = hugeAnimStruct.objects[idx];
    state = slot->state;
    animId = obj->animId;
    if (state != 9 && g_Ball.fielderWBallIndex != fielderIdx) {
        slot->_44 = 0;
        return FALSE;
    }
    if (state == 9) {
        return TRUE;
    }
    if (slot->_44 != 0 && g_UnkThrowing_31ACC[0]._10 == 0) {
        if (state == 8 && fielder->bodyCheckStatus == 3) {
            if (animId != 0x24) {
                playCharacterSound(fielder->CharID, 10);
            }
            slot->state = 9;
            AnimateCharacter(idx, 0x24, 0, 1, 0, 0, slot->_40, 0);
            QueueCharacterAnimation(idx, 0x25, 0, 1, 0, slot->_40, 0);
            updateFielderState(fielderIdx, 0);
            return TRUE;
        }
        if (obj->framesLeft <= 0) {
            slot->_44 = 0;
            slot->state = 0;
            updateFielderState(fielderIdx, 0);
            return FALSE;
        }
        return TRUE;
    }
    if (state != 0 && state != 4) {
        if (state == 8) {
            s8 k = obj->_252;
            if (bodyCheckFrameRelatedConstants[k][1] - g_FieldingLogic.bodyCheckStageCountdown >= 0) {
                AnimateCharacter(idx, 0x23, 0, 1, 1, bodyCheckFrameRelatedConstants[k][0], slot->_40, -1);
                slot->_44 = 1;
                updateFielderState(fielderIdx, 0);
                return TRUE;
            }
        } else {
            AnimateCharacter(idx, 0x21, 0, 1, 0, bodyCheckFrameRelatedConstants[(s8)obj->_252][0], slot->_40, -1);
            slot->_44 = 1;
            updateFielderState(fielderIdx, 0);
            return TRUE;
        }
    }
    slot->_44 = 0;
    return FALSE;
}

// .text:0x00060D80 size:0x110 mapped:0x8069FE14
BOOL minigameFielderAnimCheck(int fielderIdx) {
    int idx = MINIGAME_SLOT_OF(fielderIdx);
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];
    s16 flag = g_Minigame.pP_swingFrames[idx];
    AnimObject* obj = hugeAnimStruct.objects[idx];
    s16 animId = obj->animId;

    if (flag < 0) {
        if (animId == 0x1D || animId == 0x1F) {
            AnimateCharacter(idx, 0, 1, 3, 0, 0, slot->_40, -1);
        }
        return FALSE;
    }
    if (flag == 0) {
        if ((int)g_Minigame.pP_throwDirection[idx] == 3) {
            AnimateCharacter(idx, 0x1F, 0, 3, 0, 0, slot->_40, -1);
        } else {
            AnimateCharacter(idx, 0x1D, 0, 3, 0, 0, slot->_40, -1);
        }
    }
    return TRUE;
}

// .text:0x00060A98 size:0x2E8 mapped:0x8069FB2C
void foulAnimationRelatedMaybe(int fielderIdx, AnimObject* obj) {
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];
    InMemFielder* fielder = &g_Fielders[fielderIdx];
    s16 animId = obj->animId;
    f32 scale, nz, nx, dist, dz, dx;

    if (obj != NULL) {
        if (fielder->distanceToBases[0] < 60.0f && !foul_checkIfFoul(fielder->pos.x, fielder->pos.z)) {
            return;
        }
        dz = fielder->pos.z - slot->pos.z;
        dx = fielder->pos.x - slot->pos.x;
        dist = dolsqrtf2(SQ(dx) + SQ(dz));
        if (dist <= 0.0f) {
            return;
        }
        nx = dx / dist;
        nz = dz / dist;
        if (animId == 0x1A || animId == 0x1B) {
            scale = 0.01f * (barrelCollisionHitboxes[fielder->CharID] + 30) * charSizeMultipliers[fielder->CharID][0];
            nx *= scale;
            nz *= scale;
        } else {
            scale = lbl_3_data_476C[fielder->Weight];
            nx *= scale;
            nz *= scale;
        }
        if (isCoordinateUncatchableTerrain(nx + fielder->pos.x, nz + fielder->pos.z)) {
            updateFielderState(fielderIdx, 0);
            if (g_d_GameSettings.minigamesEnabled) {
                if (fielderIdx == 0) {
                    fielderIdx = MINIGAME_SELECTED_SLOT();
                } else {
                    fielderIdx = MINIGAME_SLOT_OF(fielderIdx);
                }
            }
            fn_8001B5EC(fielderIdx, 0);
            fielder->pos.x = fielder->posXLastFrame;
            fielder->pos.z = fielder->posZLastFrame;
            fielder->_01FB = 0;
        }
    }
}

// .text:0x00060804 size:0x294 mapped:0x8069F898
void updateFielderState(int fielderIdx, int reset) {
    AnimSlot* slot = &g_UnkAnimation_31EAC[fielderIdx];
    InMemFielder* fielder = &g_Fielders[fielderIdx];
    AnimObject* obj;
    VecXYZ coords;
    int idx = fielderIdx;

    if (g_d_GameSettings.minigamesEnabled) {
        if (idx == 0) {
            idx = MINIGAME_SELECTED_SLOT();
        } else {
            idx = MINIGAME_SLOT_OF(idx);
        }
    }

    obj = hugeAnimStruct.objects[idx];
    if (obj == NULL) {
        return;
    }

    if (reset == 0) {
        if (slot->_42 == 1) {
            slot->_42 = 0;
            getAnimRelatedCoordinates(idx, 4, &slot->target);
            fielder->velocityX = slot->target.x - fielder->pos.x;
            fielder->velocityZ = slot->target.z - fielder->pos.z;
            fielder->currentVelocity = VEC_LENGTH_XZ((VecXZ*)&fielder->velocityX);
            fielder->pos.x = slot->target.x;
            fielder->pos.z = slot->target.z;
            slot->_48 = 1;
        }
    } else if (slot->_42 == 0) {
        fn_8001B4D8(idx);
        if (slot->_48 == 1) {
            slot->pos.x = slot->target.x;
            slot->pos.z = slot->target.z;
        } else {
            slot->pos.x = obj->x;
            slot->pos.z = obj->z;
        }
        slot->_42 = 1;
    } else {
        getAnimRelatedCoordinates(idx, 4, &coords);
        slot->pos.x = obj->x = coords.x;
        slot->pos.z = obj->z = coords.z;
    }
}

// .text:0x00060768 size:0x9C mapped:0x8069F7FC
void resetAnimTracks(void) {
    AnimTrackBlock* block;

#define RESET_TRACK(n)                 \
    block = hugeAnimStruct.trackBlock; \
    block->tracks[n]._00 = 0;          \
    block->tracks[n]._0A = 0;          \
    block->tracks[n]._58 = 0.0f;       \
    block->tracks[n]._54 = 1;          \
    block->tracks[n]._55 = 0;          \
    block->tracks[n]._56 = 0;          \
    block->tracks[n]._5C = 0.0f
    RESET_TRACK(0);
    RESET_TRACK(1);
    RESET_TRACK(2);
    RESET_TRACK(3);
#undef RESET_TRACK
}
