#define SQRT2_LINKAGE static
#define AIPOSSWAPINPUTS_LOCAL_VIEW
#include "Unknown/orderchange.h"
#include "Dolphin/os.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "musyx/musyx.h"
#include "text/text_channel.h"
#include "menus/yd_step.h"
#include "Unknown/File_0x800625a4.h"

extern s8 lineUpInfoStruct[TEAMS_PER_GAME][PLAYERS_PER_TEAM][4];
extern SuperstarStatBonus stonNiceContactIncrement;
extern u8 superstarUnlocked[0x130];
extern u8 lbl_802E4B00[2][9];
extern u32 lbl_803CB750;
extern u8 lbl_800EFBA4[0x10];
extern menuControlStruct* menuControlVariables;
extern s16 starMenuSizes[];

// The team-management state this unit touches; see AIPOSSWAPINPUTS_LOCAL_VIEW
// for why the full-size type is not used.
extern struct {
    /* 0x0000 */ controllerInputStruct playerInputs[4];
    /* 0x0018 */ u8 _0018[0xCF38 - 0x18];
    /* 0xCF38 */ E(u16, TEAM_MANAGEMENT_PROCESS) teamManagementProcessID;
    /* 0xCF3A */ u8 _CF3A[0xCF3C - 0xCF3A];
    /* 0xCF3C */ u8 charSelectedToBeSwapped[2];
    /* 0xCF3E */ u8 _CF3E[0xCF46 - 0xCF3E];
    /* 0xCF46 */ s8 teamManagement_cursorPos[2];
    /* 0xCF48 */ s8 teamManagement_prevCursorPos[2];
    /* 0xCF4A */ u8 onFieldingAlignmentScreen2[2];
    /* 0xCF4C */ u8 unkCF4C[2];
    /* 0xCF4E */ u8 _CF4E[0xCF52 - 0xCF4E];
    /* 0xCF52 */ E(u8, ROSTER_VIEW) rosterView[2];
    /* 0xCF54 */ u8 _CF54[0xCF74 - 0xCF54];
    /* 0xCF74 */ u8 unkCF74;
    /* 0xCF75 */ s8 starMenuCursorPos;
    /* 0xCF76 */ s8 starMenuPrevCursorPos;
    /* 0xCF77 */ u8 _CF77[0xCF92 - 0xCF77];
    /* 0xCF92 */ E(u8, CHECK_STARS_SCENE) challengeCheckStarsMenuSceneLoadingNumber;
    /* 0xCF93 */ u8 challengeCheckStarsMenuLoadingInd;
    /* 0xCF94 */ u8 _CF94;
    /* 0xCF95 */ s8 checkStarsMenuPrevCharIndex;
    /* 0xCF96 */ s8 checkStarsMenuCharIndex;
    /* 0xCF97 */ s8 checkStarsMenuPrevStarIndex;
    /* 0xCF98 */ s8 checkStarsMenuStarIndex;
    /* 0xCF99 */ E(u8, BOOL) checkStarsMenuCharViewOpen;
    /* 0xCF9A */ u8 numberOfChallengeStarsForPlayer;
    /* 0xCF9B */ u8 _CF9B;
    /* 0xCF9C */ s16 playerIndexNoVariants;
} aiPosSwapInputs;

#define SCENE_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)

s8 lineupOrderChangeRelated(u8 team, int position) {
    int i;

    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if (position == lineUpInfoStruct[team][i][2]) {
            return i + 1;
        }
    }
    OSPanic("orderchange.c", 0xD69, "//OZ 戻り値がありません\b");
    return 0;
}

static inline void copyCharacterStats(CharacterStats* dst, CharacterStats* src) {
    memcpy(dst, src, 0x1E);
    dst->stats.CharID = src->stats.CharID;
    dst->stats.FieldingArm = src->stats.FieldingArm;
    dst->stats.BattingStance = src->stats.BattingStance;
    memcpy(&dst->stats.SlapContactSize, &src->stats.SlapContactSize, 2);
    memcpy(&dst->stats.SlapHitPower, &src->stats.SlapHitPower, 2);
    dst->stats.BuntingContactSize = src->stats.BuntingContactSize;
    dst->stats.HitTrajectoryPushPull = src->stats.HitTrajectoryPushPull;
    dst->stats.HitTrajectoryHighLow = src->stats.HitTrajectoryHighLow;
    dst->stats.Speed = src->stats.Speed;
    dst->stats.ThrowingArm = src->stats.ThrowingArm;
    dst->stats.CharacterClass = src->stats.CharacterClass;
    dst->stats.Weight = src->stats.Weight;
    dst->stats.Captain = src->stats.Captain;
    dst->stats.CaptainStarHitPitch = src->stats.CaptainStarHitPitch;
    memcpy(&dst->stats.NonCaptainStarSwing, &src->stats.NonCaptainStarSwing, 2);
    dst->stats.FieldingStats = src->stats.FieldingStats;
    memcpy(&dst->stats.BattingStatBar, &src->stats.BattingStatBar, 4);
    memcpy(&dst->chemistry, &src->chemistry, sizeof(ChemistryTable));
    dst->BytesAfterChemistry[0] = src->BytesAfterChemistry[0];
    dst->UnusedShorts[0] = src->UnusedShorts[0];
    dst->UnusedShorts[1] = src->UnusedShorts[1];
    dst->UnusedShorts[2] = src->UnusedShorts[2];
    dst->UnusedShorts[3] = src->UnusedShorts[3];
    dst->UnusedShorts[4] = src->UnusedShorts[4];
    dst->UnusedShorts[5] = src->UnusedShorts[5];
    dst->UnusedShorts[6] = src->UnusedShorts[6];
    dst->UnusedShorts[7] = src->UnusedShorts[7];
    dst->UnusedShorts[8] = src->UnusedShorts[8];
    dst->UnusedShorts[9] = src->UnusedShorts[9];
    dst->UnusedShorts[10] = src->UnusedShorts[10];
    dst->UnusedShorts[11] = src->UnusedShorts[11];
    dst->UnusedShorts[12] = src->UnusedShorts[12];
    dst->UnusedShorts[13] = src->UnusedShorts[13];
    dst->UnusedShorts[14] = src->UnusedShorts[14];
    dst->UnusedShorts[15] = src->UnusedShorts[15];
    dst->UnusedShorts[16] = src->UnusedShorts[16];
    dst->UnusedShorts[17] = src->UnusedShorts[17];
    dst->UnusedShorts[18] = src->UnusedShorts[18];
    dst->UnusedShorts[19] = src->UnusedShorts[19];
    dst->UnusedShorts[20] = src->UnusedShorts[20];
}

void transferStatsToInMemRoster(u8 team) {
    int slot;
    s16 charID;
    u8 row;
    u8 col;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        return;
    }

    slot = aiPosSwapInputs.teamManagement_cursorPos[team] - 1;
    if (superstarUnlocked[inMemRoster[team][slot].stats.CharID] == 0) {
        return;
    }

    Static_Stats_Tables.unk4720[team]++;
    if (Static_Stats_Tables.unk4720[team] == 2) {
        Static_Stats_Tables.unk4720[team] = 0;
    }

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        Static_Stats_Tables.charIsStarred[team][slot] ^= 1;
        memcpy(lbl_802E4B00[team], Static_Stats_Tables.charIsStarred[team], sizeof(Static_Stats_Tables.charIsStarred[team]));
    } else {
        Static_Stats_Tables.charIsStarred[0][slot] = TRUE;
    }

    if (Static_Stats_Tables.charIsStarred[team][slot]) {
        inMemRoster[team][slot].stats.SlapContactSize += stonNiceContactIncrement.SlapContactSize;
        inMemRoster[team][slot].stats.ChargeContactSize += stonNiceContactIncrement.ChargeContactSize;
        inMemRoster[team][slot].stats.SlapHitPower += stonNiceContactIncrement.SlapHitPower;
        inMemRoster[team][slot].stats.ChargeHitPower += stonNiceContactIncrement.ChargeHitPower;
        inMemRoster[team][slot].stats.Speed += stonNiceContactIncrement.Speed;
        inMemRoster[team][slot].stats.ThrowingArm += stonNiceContactIncrement.ThrowingArm;
        inMemRoster[team][slot].stats.BuntingContactSize += stonNiceContactIncrement.BuntingContactSize;
        inMemRoster[team][slot].stats.CurveBallSpeed += stonNiceContactIncrement.CurveBallSpeed;
        inMemRoster[team][slot].stats.FastBallSpeed += stonNiceContactIncrement.FastBallSpeed;
        inMemRoster[team][slot].stats.cursedBall += stonNiceContactIncrement.cursedBall;
        inMemRoster[team][slot].stats.Curve += stonNiceContactIncrement.Curve;
        inMemRoster[team][slot].stats.curveControl += stonNiceContactIncrement.curveControl;

        inMemRoster[team][slot].stats.BattingStatBar += 2;
        if (inMemRoster[team][slot].stats.BattingStatBar > 10) {
            inMemRoster[team][slot].stats.BattingStatBar = 10;
        }
        inMemRoster[team][slot].stats.PitchingStatBar += 2;
        if (inMemRoster[team][slot].stats.PitchingStatBar > 10) {
            inMemRoster[team][slot].stats.PitchingStatBar = 10;
        }
        inMemRoster[team][slot].stats.RunningStatBar += 2;
        if (inMemRoster[team][slot].stats.RunningStatBar > 10) {
            inMemRoster[team][slot].stats.RunningStatBar = 10;
        }
        inMemRoster[team][slot].stats.FieldingStatBar += 2;
        if (inMemRoster[team][slot].stats.FieldingStatBar > 10) {
            inMemRoster[team][slot].stats.FieldingStatBar = 10;
        }
    } else {
        charID = inMemRoster[team][slot].stats.CharID;
        row = charID / 9;
        col = charID % 9;
        copyCharacterStats(&inMemRoster[team][slot], &Static_Stats_Tables.characterStats[row][col]);
    }
}

static inline u32 nextRandSeed(void) {
    return lbl_803CB750 = lbl_803CB750 * 0x5D588B65 + 1;
}

/* Random integer in the inclusive range between a and b, in either order. */
int randRange_FUN_80042bf0(int a, int b) {
    int min;

    if (a == b) {
        return a;
    }
    if (a <= b) {
        min = a;
    } else {
        min = b;
        b = a;
    }
    a = nextRandSeed() >> 16;
    a %= b - min + 1;
    a += min;
    return a;
}

void sndFXRelated(u16 input) {
    switch (input) {
    case INPUT_BUTTON_A:
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, SND_STUDIO_DEFAULT);
        break;
    case INPUT_BUTTON_B:
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
        break;
    case INPUT_BUTTON_LEFT:
    case INPUT_BUTTON_RIGHT:
    case INPUT_BUTTON_DOWN:
    case INPUT_BUTTON_UP:
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        break;
    case INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT:
    case INPUT_TRIGGER_R:
    case INPUT_TRIGGER_L:
    case INPUT_BUTTON_X:
    case INPUT_BUTTON_Y:
        break;
    }
}

void fn_80042D38(u16 screen) {
    menuControlVariables->previousScreen = menuControlVariables->currentScreen;
    menuControlVariables->previousState = menuControlVariables->currentState;
    menuControlVariables->currentScreen = screen;
    menuControlVariables->currentState = 0;
}

BOOL fn_80042D68(MenuScene* scene, int handle, int frame) {
    UIRecord* record = SCENE_RECORD(scene, handle);

    if ((s32)(record->frame >> 16) >= frame) {
        record->playMode = UI_PLAY_STOP;
        return TRUE;
    }
    return FALSE;
}

BOOL maybeCheckAndResetGrapicsElement(MenuScene* scene, int handle, int frame) {
    UIRecord* record = SCENE_RECORD(scene, handle);

    if ((s32)(record->frame >> 16) == frame) {
        record->playMode = UI_PLAY_STOP;
        return TRUE;
    }
    return FALSE;
}

void challengeStarMenu(void) {
    controllerInputStruct input;
    u8 isVariant = FALSE;

    memset(&input, 0, sizeof(input));
    if (aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber != CHECK_STARS_SCENE_NONE) {
        return;
    }

    input.currentHeldInput = aiPosSwapInputs.playerInputs[Static_Stats_Tables.playerNumberByPort[0]].currentHeldInput;
    input.newInput = aiPosSwapInputs.playerInputs[Static_Stats_Tables.playerNumberByPort[0]].newInput;
    input.processedInput = aiPosSwapInputs.playerInputs[Static_Stats_Tables.playerNumberByPort[0]].processedInput;
    if (starMissionCompletionTracker[aiPosSwapInputs.playerIndexNoVariants].variantClassification ==
        CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_VARIANT) {
        isVariant = TRUE;
    }

    if (input.processedInput & INPUT_BUTTON_UP) {
        if (aiPosSwapInputs.checkStarsMenuCharViewOpen) {
            if (!isVariant) {
                aiPosSwapInputs.checkStarsMenuPrevStarIndex = aiPosSwapInputs.checkStarsMenuStarIndex;
                aiPosSwapInputs.checkStarsMenuStarIndex -= (s32)(aiPosSwapInputs.numberOfChallengeStarsForPlayer / 2U);
                if (aiPosSwapInputs.checkStarsMenuStarIndex < 0) {
                    aiPosSwapInputs.checkStarsMenuStarIndex += aiPosSwapInputs.numberOfChallengeStarsForPlayer;
                }
                if (aiPosSwapInputs.checkStarsMenuPrevStarIndex != aiPosSwapInputs.checkStarsMenuStarIndex) {
                    aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_MOVE_IN_STAR_LIST;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
                }
            }
        } else {
            aiPosSwapInputs.checkStarsMenuPrevCharIndex = aiPosSwapInputs.checkStarsMenuCharIndex;
            aiPosSwapInputs.checkStarsMenuCharIndex--;
            if (aiPosSwapInputs.checkStarsMenuCharIndex < 0) {
                aiPosSwapInputs.checkStarsMenuCharIndex = PLAYERS_PER_TEAM - 1;
            }
            if (aiPosSwapInputs.checkStarsMenuPrevCharIndex != aiPosSwapInputs.checkStarsMenuCharIndex) {
                aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_MOVE_IN_CHAR_LIST;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            }
        }
    } else if (input.processedInput & INPUT_BUTTON_DOWN) {
        if (aiPosSwapInputs.checkStarsMenuCharViewOpen) {
            if (!isVariant) {
                aiPosSwapInputs.checkStarsMenuPrevStarIndex = aiPosSwapInputs.checkStarsMenuStarIndex;
                aiPosSwapInputs.checkStarsMenuStarIndex += (s32)(aiPosSwapInputs.numberOfChallengeStarsForPlayer / 2U);
                if (aiPosSwapInputs.checkStarsMenuStarIndex >= aiPosSwapInputs.numberOfChallengeStarsForPlayer) {
                    aiPosSwapInputs.checkStarsMenuStarIndex =
                        aiPosSwapInputs.checkStarsMenuStarIndex - aiPosSwapInputs.numberOfChallengeStarsForPlayer;
                }
                if (aiPosSwapInputs.checkStarsMenuPrevStarIndex != aiPosSwapInputs.checkStarsMenuStarIndex) {
                    aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_MOVE_IN_STAR_LIST;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
                }
            }
        } else {
            aiPosSwapInputs.checkStarsMenuPrevCharIndex = aiPosSwapInputs.checkStarsMenuCharIndex;
            aiPosSwapInputs.checkStarsMenuCharIndex++;
            if (aiPosSwapInputs.checkStarsMenuCharIndex == PLAYERS_PER_TEAM) {
                aiPosSwapInputs.checkStarsMenuCharIndex = 0;
            }
            if (aiPosSwapInputs.checkStarsMenuPrevCharIndex != aiPosSwapInputs.checkStarsMenuCharIndex) {
                aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_MOVE_IN_CHAR_LIST;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            }
        }
    } else if (input.processedInput & INPUT_BUTTON_LEFT) {
        if (aiPosSwapInputs.checkStarsMenuCharViewOpen) {
            if (!isVariant) {
                aiPosSwapInputs.checkStarsMenuPrevStarIndex = aiPosSwapInputs.checkStarsMenuStarIndex;
                aiPosSwapInputs.checkStarsMenuStarIndex--;
                if (aiPosSwapInputs.checkStarsMenuStarIndex < 0 &&
                    aiPosSwapInputs.checkStarsMenuStarIndex < (s32)(aiPosSwapInputs.numberOfChallengeStarsForPlayer / 2U)) {
                    aiPosSwapInputs.checkStarsMenuStarIndex = (s32)(aiPosSwapInputs.numberOfChallengeStarsForPlayer / 2U) - 1;
                } else if (aiPosSwapInputs.checkStarsMenuStarIndex < aiPosSwapInputs.numberOfChallengeStarsForPlayer / 2 &&
                           aiPosSwapInputs.checkStarsMenuStarIndex >= aiPosSwapInputs.numberOfChallengeStarsForPlayer / 2 - 1) {
                    aiPosSwapInputs.checkStarsMenuStarIndex = aiPosSwapInputs.numberOfChallengeStarsForPlayer - 1;
                }
            } else {
                aiPosSwapInputs.checkStarsMenuPrevStarIndex = aiPosSwapInputs.checkStarsMenuStarIndex;
                aiPosSwapInputs.checkStarsMenuStarIndex--;
                if (aiPosSwapInputs.checkStarsMenuStarIndex < 0) {
                    aiPosSwapInputs.checkStarsMenuStarIndex = aiPosSwapInputs.numberOfChallengeStarsForPlayer - 1;
                }
            }
            if (aiPosSwapInputs.checkStarsMenuPrevStarIndex != aiPosSwapInputs.checkStarsMenuStarIndex) {
                aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_MOVE_IN_STAR_LIST;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            }
        }
    } else if (input.processedInput & INPUT_BUTTON_RIGHT) {
        if (aiPosSwapInputs.checkStarsMenuCharViewOpen) {
            if (!isVariant) {
                aiPosSwapInputs.checkStarsMenuPrevStarIndex = aiPosSwapInputs.checkStarsMenuStarIndex;
                aiPosSwapInputs.checkStarsMenuStarIndex++;
                if (aiPosSwapInputs.checkStarsMenuStarIndex > aiPosSwapInputs.numberOfChallengeStarsForPlayer / 2 - 1 &&
                    aiPosSwapInputs.checkStarsMenuStarIndex <= aiPosSwapInputs.numberOfChallengeStarsForPlayer / 2) {
                    aiPosSwapInputs.checkStarsMenuStarIndex = 0;
                } else if (aiPosSwapInputs.checkStarsMenuStarIndex > aiPosSwapInputs.numberOfChallengeStarsForPlayer - 1 &&
                           aiPosSwapInputs.checkStarsMenuStarIndex >= aiPosSwapInputs.numberOfChallengeStarsForPlayer / 2) {
                    aiPosSwapInputs.checkStarsMenuStarIndex = aiPosSwapInputs.numberOfChallengeStarsForPlayer / 2;
                }
            } else {
                aiPosSwapInputs.checkStarsMenuPrevStarIndex = aiPosSwapInputs.checkStarsMenuStarIndex;
                aiPosSwapInputs.checkStarsMenuStarIndex++;
                if (aiPosSwapInputs.checkStarsMenuStarIndex == aiPosSwapInputs.numberOfChallengeStarsForPlayer) {
                    aiPosSwapInputs.checkStarsMenuStarIndex = 0;
                }
            }
            if (aiPosSwapInputs.checkStarsMenuPrevStarIndex != aiPosSwapInputs.checkStarsMenuStarIndex) {
                aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_MOVE_IN_STAR_LIST;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            }
        }
    } else if (input.newInput & INPUT_BUTTON_A) {
        if (!aiPosSwapInputs.checkStarsMenuCharViewOpen) {
            aiPosSwapInputs.checkStarsMenuCharViewOpen ^= 1;
            aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_LOAD_CHAR_VIEW;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, SND_STUDIO_DEFAULT);
        }
    } else if (input.newInput & INPUT_BUTTON_B) {
        if (!aiPosSwapInputs.checkStarsMenuCharViewOpen) {
            aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_EXIT;
            aiPosSwapInputs.checkStarsMenuPrevStarIndex = 0;
            aiPosSwapInputs.checkStarsMenuStarIndex = 0;
            aiPosSwapInputs.checkStarsMenuPrevCharIndex = 0;
            aiPosSwapInputs.checkStarsMenuCharIndex = 0;
            aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_2;
        } else {
            aiPosSwapInputs.checkStarsMenuCharViewOpen ^= 1;
            aiPosSwapInputs.checkStarsMenuPrevStarIndex = 0;
            aiPosSwapInputs.checkStarsMenuStarIndex = 0;
            aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_EXIT_CHAR_VIEW;
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
    }
}

void starMenuCursor(void) {
    controllerInputStruct input;
    u8 isVariant = FALSE;
    u8 size;
    s8 variant;

    memset(&input, 0, sizeof(input));
    input.currentHeldInput = g_d_GameSettings._06 == 2
                                 ? aiPosSwapInputs.playerInputs[Static_Stats_Tables.playerNumberByPort[0]].currentHeldInput
                                 : Static_Stats_Tables.controllerInputs[0].currentHeldInput;
    input.newInput = g_d_GameSettings._06 == 2
                         ? aiPosSwapInputs.playerInputs[Static_Stats_Tables.playerNumberByPort[0]].newInput
                         : Static_Stats_Tables.controllerInputs[0].newInput;
    input.processedInput = g_d_GameSettings._06 == 2
                               ? aiPosSwapInputs.playerInputs[Static_Stats_Tables.playerNumberByPort[0]].processedInput
                               : Static_Stats_Tables.controllerInputs[0].processedInput;

    variant = starMissionCompletionTracker[aiPosSwapInputs.playerIndexNoVariants].variantClassification;
    size = starMenuSizes[variant];
    if (variant == CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_VARIANT) {
        isVariant = TRUE;
    }

    if (input.processedInput & INPUT_BUTTON_UP) {
        if (!isVariant) {
            aiPosSwapInputs.starMenuPrevCursorPos = aiPosSwapInputs.starMenuCursorPos;
            aiPosSwapInputs.starMenuCursorPos -= size / 2;
            if (aiPosSwapInputs.starMenuCursorPos < 0) {
                aiPosSwapInputs.starMenuCursorPos += size;
            }
            if (aiPosSwapInputs.starMenuPrevCursorPos != aiPosSwapInputs.starMenuCursorPos) {
                aiPosSwapInputs.unkCF74 = 2;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            }
        }
    } else if (input.processedInput & INPUT_BUTTON_DOWN) {
        if (!isVariant) {
            aiPosSwapInputs.starMenuPrevCursorPos = aiPosSwapInputs.starMenuCursorPos;
            aiPosSwapInputs.starMenuCursorPos += size / 2;
            if (aiPosSwapInputs.starMenuCursorPos >= size) {
                aiPosSwapInputs.starMenuCursorPos = aiPosSwapInputs.starMenuCursorPos - size;
            }
            if (aiPosSwapInputs.starMenuPrevCursorPos != aiPosSwapInputs.starMenuCursorPos) {
                aiPosSwapInputs.unkCF74 = 2;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            }
        }
    } else if (input.processedInput & INPUT_BUTTON_LEFT) {
        if (!isVariant) {
            aiPosSwapInputs.starMenuPrevCursorPos = aiPosSwapInputs.starMenuCursorPos;
            aiPosSwapInputs.starMenuCursorPos--;
            if (aiPosSwapInputs.starMenuCursorPos < 0 && aiPosSwapInputs.starMenuCursorPos < size / 2) {
                aiPosSwapInputs.starMenuCursorPos = size / 2 - 1;
            } else if (aiPosSwapInputs.starMenuCursorPos < size / 2 &&
                       aiPosSwapInputs.starMenuCursorPos >= size / 2 - 1) {
                aiPosSwapInputs.starMenuCursorPos = size - 1;
            }
        } else {
            aiPosSwapInputs.starMenuPrevCursorPos = aiPosSwapInputs.starMenuCursorPos;
            aiPosSwapInputs.starMenuCursorPos--;
            if (aiPosSwapInputs.starMenuCursorPos < 0) {
                aiPosSwapInputs.starMenuCursorPos = size - 1;
            }
        }
        if (aiPosSwapInputs.starMenuPrevCursorPos != aiPosSwapInputs.starMenuCursorPos) {
            aiPosSwapInputs.unkCF74 = 2;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        }
    } else if (input.processedInput & INPUT_BUTTON_RIGHT) {
        if (!isVariant) {
            aiPosSwapInputs.starMenuPrevCursorPos = aiPosSwapInputs.starMenuCursorPos;
            aiPosSwapInputs.starMenuCursorPos++;
            if (aiPosSwapInputs.starMenuCursorPos > size / 2 - 1 && aiPosSwapInputs.starMenuCursorPos <= size / 2) {
                aiPosSwapInputs.starMenuCursorPos = 0;
            } else if (aiPosSwapInputs.starMenuCursorPos > size - 1 &&
                       aiPosSwapInputs.starMenuCursorPos >= size / 2) {
                aiPosSwapInputs.starMenuCursorPos = size / 2;
            }
        } else {
            aiPosSwapInputs.starMenuPrevCursorPos = aiPosSwapInputs.starMenuCursorPos;
            aiPosSwapInputs.starMenuCursorPos++;
            if (aiPosSwapInputs.starMenuCursorPos == size) {
                aiPosSwapInputs.starMenuCursorPos = 0;
            }
        }
        if (aiPosSwapInputs.starMenuPrevCursorPos != aiPosSwapInputs.starMenuCursorPos) {
            aiPosSwapInputs.unkCF74 = 2;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        }
    } else if ((input.newInput & INPUT_BUTTON_A) || (input.newInput & INPUT_BUTTON_B)) {
        aiPosSwapInputs.unkCF74 = 3;
        if (input.newInput & INPUT_BUTTON_A) {
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, SND_STUDIO_DEFAULT);
        } else {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
        }
        aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_ON_SCREEN;
    }
}

void swapPosMenu_left_rightPress(u8 right, u8 team) {
    if (aiPosSwapInputs.teamManagement_cursorPos[team] == 0) {
        return;
    }
    if (g_d_GameSettings._06 == 2 && aiPosSwapInputs.rosterView[team] != ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
        return;
    }
    if (aiPosSwapInputs.rosterView[team] != ROSTER_VIEW_DEFENSIVE_ALIGNMENT && g_d_GameSettings._06 != 2) {
        return;
    }

    aiPosSwapInputs.unkCF4C[team] = aiPosSwapInputs.onFieldingAlignmentScreen2[team];
    if (!right) {
        if (aiPosSwapInputs.teamManagement_cursorPos[team] != 0 &&
            aiPosSwapInputs.rosterView[team] == ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
            aiPosSwapInputs.teamManagement_prevCursorPos[team] = aiPosSwapInputs.teamManagement_cursorPos[team];
            switch (lineUpInfoStruct[team][aiPosSwapInputs.teamManagement_cursorPos[team] - 1][2]) {
            case FIELDING_POSITION_PITCHER:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_THIRD_BASE);
                break;
            case FIELDING_POSITION_CATCHER:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_THIRD_BASE);
                break;
            case FIELDING_POSITION_FIRST_BASE:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_SECOND_BASE);
                break;
            case FIELDING_POSITION_SECOND_BASE:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_SHORTSTOP);
                break;
            case FIELDING_POSITION_CENTER_FIELD:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_LEFT_FIELD);
                break;
            case FIELDING_POSITION_RIGHT_FIELD:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CENTER_FIELD);
                break;
            case FIELDING_POSITION_THIRD_BASE:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_FIRST_BASE);
                break;
            case FIELDING_POSITION_SHORTSTOP:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_THIRD_BASE);
                break;
            case FIELDING_POSITION_LEFT_FIELD:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_RIGHT_FIELD);
                break;
            }
            if (aiPosSwapInputs.teamManagement_prevCursorPos[team] != aiPosSwapInputs.teamManagement_cursorPos[team]) {
                updateCharacterSelectProcessCode(team, 0x3B);
            }
        }
    } else if (aiPosSwapInputs.teamManagement_cursorPos[team] == 0) {
        if (g_d_GameSettings._06 != 2) {
            aiPosSwapInputs.onFieldingAlignmentScreen2[team]++;
            if (aiPosSwapInputs.rosterView[team] > ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
                aiPosSwapInputs.rosterView[team] = ROSTER_VIEW_DEFENSIVE_ALIGNMENT;
            }
            switch (aiPosSwapInputs.rosterView[team]) {
            case ROSTER_VIEW_BATTING_ORDER:
                aiPosSwapInputs.rosterView[team] = ROSTER_VIEW_BATTING_ORDER;
                break;
            case ROSTER_VIEW_DEFENSIVE_ALIGNMENT:
                aiPosSwapInputs.rosterView[team] = ROSTER_VIEW_DEFENSIVE_ALIGNMENT;
                break;
            }
            updateCharacterSelectProcessCode(team, 0x3C);
        } else {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, SND_STUDIO_DEFAULT);
            return;
        }
    } else if (aiPosSwapInputs.teamManagement_cursorPos[team] != 0 &&
               aiPosSwapInputs.rosterView[team] == ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
        aiPosSwapInputs.teamManagement_prevCursorPos[team] = aiPosSwapInputs.teamManagement_cursorPos[team];
        switch (lineUpInfoStruct[team][aiPosSwapInputs.teamManagement_cursorPos[team] - 1][2]) {
        case FIELDING_POSITION_PITCHER:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_FIRST_BASE);
            break;
        case FIELDING_POSITION_CATCHER:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_FIRST_BASE);
            break;
        case FIELDING_POSITION_THIRD_BASE:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_SHORTSTOP);
            break;
        case FIELDING_POSITION_SHORTSTOP:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_SECOND_BASE);
            break;
        case FIELDING_POSITION_LEFT_FIELD:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CENTER_FIELD);
            break;
        case FIELDING_POSITION_CENTER_FIELD:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_RIGHT_FIELD);
            break;
        case FIELDING_POSITION_RIGHT_FIELD:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_LEFT_FIELD);
            break;
        case FIELDING_POSITION_FIRST_BASE:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_THIRD_BASE);
            break;
        case FIELDING_POSITION_SECOND_BASE:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_FIRST_BASE);
            break;
        }
        if (aiPosSwapInputs.teamManagement_prevCursorPos[team] != aiPosSwapInputs.teamManagement_cursorPos[team]) {
            updateCharacterSelectProcessCode(team, 0x3B);
        }
    }

    if (!right) {
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
    } else {
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
    }
}

void swapPosMenu_up_downPress(u8 down, u8 team) {
    aiPosSwapInputs.teamManagement_prevCursorPos[team] = aiPosSwapInputs.teamManagement_cursorPos[team];
    if (!down) {
        if (aiPosSwapInputs.rosterView[team] == ROSTER_VIEW_BATTING_ORDER) {
            aiPosSwapInputs.teamManagement_cursorPos[team]--;
            if (aiPosSwapInputs.charSelectedToBeSwapped[team] != 0 && aiPosSwapInputs.teamManagement_cursorPos[team] < 1) {
                aiPosSwapInputs.teamManagement_cursorPos[team] = PLAYERS_PER_TEAM;
                updateCharacterSelectProcessCode(team, 0x3B);
                return;
            }
            if (aiPosSwapInputs.teamManagement_prevCursorPos[team] == 0) {
                aiPosSwapInputs.teamManagement_cursorPos[team] = PLAYERS_PER_TEAM;
                updateCharacterSelectProcessCode(team, 0x3D);
            } else if (aiPosSwapInputs.teamManagement_cursorPos[team] == 0) {
                updateCharacterSelectProcessCode(team, 0x3E);
            } else {
                updateCharacterSelectProcessCode(team, 0x3B);
            }
        } else if (aiPosSwapInputs.teamManagement_prevCursorPos[team] == 0) {
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CATCHER);
            updateCharacterSelectProcessCode(team, 0x3D);
        } else {
            switch (lineUpInfoStruct[team][aiPosSwapInputs.teamManagement_cursorPos[team] - 1][2]) {
            case FIELDING_POSITION_PITCHER:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_SHORTSTOP);
                break;
            case FIELDING_POSITION_CATCHER:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_PITCHER);
                break;
            case FIELDING_POSITION_FIRST_BASE:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_RIGHT_FIELD);
                break;
            case FIELDING_POSITION_SECOND_BASE:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CENTER_FIELD);
                break;
            case FIELDING_POSITION_THIRD_BASE:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_LEFT_FIELD);
                break;
            case FIELDING_POSITION_SHORTSTOP:
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CENTER_FIELD);
                break;
            case FIELDING_POSITION_LEFT_FIELD:
                if (aiPosSwapInputs.charSelectedToBeSwapped[team] != 0) {
                    aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_THIRD_BASE);
                    updateCharacterSelectProcessCode(team, 0x3B);
                } else {
                    aiPosSwapInputs.teamManagement_cursorPos[team] = 0;
                    updateCharacterSelectProcessCode(team, 0x3E);
                }
                break;
            case FIELDING_POSITION_RIGHT_FIELD:
                if (aiPosSwapInputs.charSelectedToBeSwapped[team] != 0) {
                    aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_FIRST_BASE);
                    updateCharacterSelectProcessCode(team, 0x3B);
                } else {
                    aiPosSwapInputs.teamManagement_cursorPos[team] = 0;
                    updateCharacterSelectProcessCode(team, 0x3E);
                }
                break;
            case FIELDING_POSITION_CENTER_FIELD:
                if (aiPosSwapInputs.charSelectedToBeSwapped[team] != 0) {
                    aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CATCHER);
                    updateCharacterSelectProcessCode(team, 0x3B);
                } else {
                    aiPosSwapInputs.teamManagement_cursorPos[team] = 0;
                    updateCharacterSelectProcessCode(team, 0x3E);
                }
                break;
            }
            if (aiPosSwapInputs.teamManagement_cursorPos[team] != 0 &&
                aiPosSwapInputs.teamManagement_prevCursorPos[team] != aiPosSwapInputs.teamManagement_cursorPos[team]) {
                updateCharacterSelectProcessCode(team, 0x3B);
            }
        }
    } else if (aiPosSwapInputs.rosterView[team] == ROSTER_VIEW_BATTING_ORDER) {
        aiPosSwapInputs.teamManagement_cursorPos[team]++;
        if (aiPosSwapInputs.charSelectedToBeSwapped[team] != 0 &&
            aiPosSwapInputs.teamManagement_cursorPos[team] == PLAYERS_PER_TEAM + 1) {
            aiPosSwapInputs.teamManagement_cursorPos[team] = 1;
            updateCharacterSelectProcessCode(team, 0x3B);
            return;
        }
        if (aiPosSwapInputs.teamManagement_cursorPos[team] == PLAYERS_PER_TEAM + 1) {
            aiPosSwapInputs.teamManagement_cursorPos[team] = 0;
            updateCharacterSelectProcessCode(team, 0x3E);
        } else if (aiPosSwapInputs.teamManagement_prevCursorPos[team] == 0) {
            updateCharacterSelectProcessCode(team, 0x3D);
        } else {
            updateCharacterSelectProcessCode(team, 0x3B);
        }
    } else if (aiPosSwapInputs.teamManagement_prevCursorPos[team] == 0) {
        aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CENTER_FIELD);
        updateCharacterSelectProcessCode(team, 0x3D);
    } else {
        switch (lineUpInfoStruct[team][aiPosSwapInputs.teamManagement_cursorPos[team] - 1][2]) {
        case FIELDING_POSITION_PITCHER:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CATCHER);
            break;
        case FIELDING_POSITION_FIRST_BASE:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CATCHER);
            break;
        case FIELDING_POSITION_THIRD_BASE:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CATCHER);
            break;
        case FIELDING_POSITION_SECOND_BASE:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_PITCHER);
            break;
        case FIELDING_POSITION_SHORTSTOP:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_PITCHER);
            break;
        case FIELDING_POSITION_CENTER_FIELD:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_SHORTSTOP);
            break;
        case FIELDING_POSITION_LEFT_FIELD:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_THIRD_BASE);
            break;
        case FIELDING_POSITION_RIGHT_FIELD:
            aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_FIRST_BASE);
            break;
        case FIELDING_POSITION_CATCHER:
            if (aiPosSwapInputs.charSelectedToBeSwapped[team] != 0) {
                aiPosSwapInputs.teamManagement_cursorPos[team] = lineupOrderChangeRelated(team, FIELDING_POSITION_CENTER_FIELD);
                updateCharacterSelectProcessCode(team, 0x3B);
            } else {
                aiPosSwapInputs.teamManagement_cursorPos[team] = 0;
                updateCharacterSelectProcessCode(team, 0x3E);
            }
            break;
        }
        if (aiPosSwapInputs.teamManagement_cursorPos[team] != 0 &&
            aiPosSwapInputs.teamManagement_prevCursorPos[team] != aiPosSwapInputs.teamManagement_cursorPos[team]) {
            updateCharacterSelectProcessCode(team, 0x3B);
        }
    }
}
