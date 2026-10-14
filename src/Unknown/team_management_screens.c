#include "Unknown/team_management_screens.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "static/UnknownHomes_Static.h"
#include "text/text.h"
#include "Unknown/File_0x800363d8.h"
#include "game/challenge/challenge_state.h"
#include "game/UnknownHomes_Game.h"
#include "game/challenge/star_mission_data.h"
#include "Unknown/sub.h"
#include "musyx/musyx.h"

extern u8 gameSetUpStep[0x64];
extern void makeCursorUnmovable(s32 port);
extern void makeCursorMovable(s32 port);
extern void updateCharacterSelectProcessCode(s32 port, u8 process);
extern BOOL maybeCheckAndResetGrapicsElement(MenuScene* scene, s32 handle, s32 frame);
extern s8 lineUpInfoStruct[][9][4];
extern void fn_8005C830(MenuScene* scene, s32 port, s32 selection);
extern u8 superstarUnlocked[54];
extern s8 lineupOrderChangeRelated(u8 team, int position);
extern s32 determineIfMissionDescriptionIsShown(s32 tracker);
extern void transferStatsToInMemRoster(u8 team);
extern void sndFXRelated(u16 input);
extern u8 lbl_800EFBA4[0x10];
extern void fn_80058E0C(MenuScene* scene, u8 port);
extern void fn_80058B20(MenuScene* scene, u8 port);
extern void fn_80058644(MenuScene* scene);
extern void zMenuLoadGraphics(MenuScene* scene);
extern void fn_8000F8F4(MenuScene* scene);
extern BOOL fn_80042D68(MenuScene* scene, int handle, int frame);
extern void removeGraphicsElementFromScene(DrawingSceneStruct* node);

#define TEAM_MANAGEMENT_RECORD(scene, handle) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (handle)].object)

void fn_80059458(MenuScene* scene, s32 port, u32 inputMask) {
    s32 selected[2];
    s32 i;
    s32 count;
    s32 last = 12;

    memset(selected, -1, 2);
    for (i = 0, count = 0; i < 14; i++) {
        if ((inputMask & (1 << i)) != 0) {
            switch (i) {
            case 0:
                i++;
                break;
            case 1:
                selected[count++] = 1;
                break;
            case 2:
                selected[count++] = 2;
                break;
            case 3:
                selected[count++] = 3;
                break;
            case 4:
                selected[count++] = 4;
                break;
            case 5:
                selected[count++] = 5;
                break;
            case 6:
                selected[count++] = 6;
                break;
            case 7:
                selected[count++] = 7;
                break;
            case 8:
                selected[count++] = 8;
                break;
            case 9:
                selected[count++] = 9;
                break;
            case 10:
                selected[count++] = 10;
                break;
            case 11:
                selected[count++] = 11;
                break;
            case 12:
                selected[count++] = 12;
                break;
            default:
                selected[count++] = 13;
                break;
            }
        }
    }

    selected[0]--;
    selected[1]--;
    if (selected[0] < 0) {
        selected[0] = last;
    }
    if (selected[1] < 0) {
        selected[1] = last;
    }

    if (g_d_GameSettings._06 != 2) {
        TEAM_MANAGEMENT_RECORD(scene, (u8)port + 0x1B4)->frame = selected[0] << 16;
        TEAM_MANAGEMENT_RECORD(scene, (u8)port + 0x1B6)->frame = selected[1] << 16;
    } else {
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 0x125].object)->frame = selected[0] << 16;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 0x126].object)->frame = selected[1] << 16;
    }
}

void fn_800596D4(MenuScene* scene) {
    if (((u8*)&aiPosSwapInputs)[0xCF73] == 0) {
        if (challengeStarRelatedInd(aiPosSwapInputs.playerIndexNoVariants, aiPosSwapInputs.starMenuCursorPos)) {
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuCursorPos + 0x1E7)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuCursorPos + 0x1E7)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuCursorPos + 0x1E7)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuCursorPos + (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD))->frame = 0x00010000;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuCursorPos + 0x1E7)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuCursorPos + (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD))->frame = 0;
        }
        TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuCursorPos + 0x1FB)->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuCursorPos + 0x1FB)->playMode = UI_PLAY_FORWARD;
        if (challengeStarRelatedInd(aiPosSwapInputs.playerIndexNoVariants, aiPosSwapInputs.starMenuPrevCursorPos)) {
            TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuPrevCursorPos + 0x1E7)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuPrevCursorPos + (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD))->frame = 0;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuPrevCursorPos + (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD))->frame = 0;
        }
        TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuPrevCursorPos + 0x1FB)->flags &= ~UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD(scene, aiPosSwapInputs.starMenuPrevCursorPos + 0x1FB)->playMode = UI_PLAY_FORWARD;
        {
            s32 requirementRow = characterStaticIndexes[aiPosSwapInputs.playerIndexNoVariants].requirementRow;
            s32 textID;
            if ((s8)g_Challenge.characters[aiPosSwapInputs.playerIndexNoVariants].inGameMissionTracker[aiPosSwapInputs.starMenuCursorPos].shownOnPauseMenu != 0) {
                textID = starMissionDisplayRules[requirementRow][aiPosSwapInputs.starMenuCursorPos].textID;
            } else if (starMissionDisplayRules[requirementRow][aiPosSwapInputs.starMenuCursorPos].minScoutRow <= g_Challenge.difficulty) {
                textID = 0x1C5;
            } else {
                textID = 0x1C6;
            }
            text_setPtrToWhereCharsAreStored(((u8*)&aiPosSwapInputs)[0xCF7C], 0, textID);
        }
        ((u8*)&aiPosSwapInputs)[0xCF73] = 1;
    }
    if (((u8*)&aiPosSwapInputs)[0xCF73] != 0) {
        ((u8*)&aiPosSwapInputs)[0xCF74] = 0;
        ((u8*)&aiPosSwapInputs)[0xCF73] = 0;
    }
}

void starMissionRelated1(MenuScene* scene) {
    s32 character;
    s32 characterClass;
    s32 requirementRow;
    s32 rank;
    s32 missionCount;
    s32 mission;
    s32 textID;

    if (((u8*)&aiPosSwapInputs)[0xCF73] == 0) {
        character = *(s16*)((u8*)&aiPosSwapInputs + 0xCF78);
        aiPosSwapInputs.playerIndexNoVariants = characterStaticIndexes[character].trackerIdx;
        character = *(s16*)((u8*)&aiPosSwapInputs + 0xCF78);
        requirementRow = characterStaticIndexes[character].requirementRow;
        rank = (s8)g_Challenge.characters[aiPosSwapInputs.playerIndexNoVariants].variantClassification;
        characterClass = Static_Stats_Tables.characterStats[character / 9][character % 9].stats.CharacterClass;
        switch (rank) {
        case CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_CAPTAIN:
            rank = 3;
            missionCount = 10;
            break;
        case CHARACTER_VARIANT_CLASSIFICATION_SECONDARY_CAPTAIN:
            rank = 2;
            missionCount = 8;
            break;
        case CHARACTER_VARIANT_CLASSIFICATION_UNIQUE_NON_CAPTAIN:
            rank = 1;
            missionCount = 6;
            break;
        case CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_VARIANT:
            rank = 0;
            missionCount = 4;
            break;
        }
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x16e : 0x1D7)].object)->flags |= UI_FLAG_VISIBLE;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x16e : 0x1D7)].object)->playMode = UI_PLAY_FORWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x16a : 0x1D3)].object)->flags |= UI_FLAG_VISIBLE;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x16a : 0x1D3)].object)->playMode = UI_PLAY_FORWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x16b : 0x1D4)].object)->flags |= UI_FLAG_VISIBLE;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x16b : 0x1D4)].object)->frame = rank << 16;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x16c : 0x1D5)].object)->flags |= UI_FLAG_VISIBLE;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x16c : 0x1D5)].object)->playMode = UI_PLAY_FORWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x16d : 0x1D6)].object)->playMode = UI_PLAY_FORWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x171 : 0x1DA)].object)->frame =
            characterClass << 16;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (g_d_GameSettings._06 == 2 ? 0x172 : 0x1DB)].object)->frame = *(s16*)((u8*)&aiPosSwapInputs + 0xCF78) << 16;
        ((u8*)&aiPosSwapInputs)[0xCF7A] = text_initializeNewChannel((UnkText988Arg*)scene,
            g_d_GameSettings._06 == 2 ? 0x19B : 0x205, 0, 0, aiPosSwapInputs.playerIndexNoVariants + 8, 0);
        rank = determineIfMissionDescriptionIsShown(aiPosSwapInputs.playerIndexNoVariants);
        ((u8*)&aiPosSwapInputs)[0xCF7B] = text_initializeNewChannel((UnkText988Arg*)scene,
            g_d_GameSettings._06 == 2 ? 0x19C : 0x206, 1, 0,
            (s16)starRankTextIDs[requirementRow] + rank, 0);
        rank = determineIfMissionDescriptionIsShown(aiPosSwapInputs.playerIndexNoVariants);
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 0x1DC].object)->frame = (4 - rank) << 16;
        mission = aiPosSwapInputs.starMenuCursorPos;
        if ((s8)g_Challenge.characters[aiPosSwapInputs.playerIndexNoVariants].inGameMissionTracker[mission].shownOnPauseMenu != 0) {
            textID = starMissionDisplayRules[requirementRow][mission].textID;
        } else if (starMissionDisplayRules[requirementRow][mission].minScoutRow <= g_Challenge.difficulty) {
            textID = 0x1C5;
        } else {
            textID = 0x1C6;
        }
        ((u8*)&aiPosSwapInputs)[0xCF7C] = text_initializeNewChannel((UnkText988Arg*)scene,
            g_d_GameSettings._06 == 2 ? 0x19D : 0x207, 0, 0, textID, 0);
        screenTextArray.blocks[((u8*)&aiPosSwapInputs)[0xCF7C]].justify = 1;
        for (mission = 0; mission < missionCount; mission++) {
            if (challengeStarRelatedInd(aiPosSwapInputs.playerIndexNoVariants, mission)) {
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + mission + 0x1F1].object)->flags |= UI_FLAG_VISIBLE;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + mission + 0x1F1].object)->playMode = UI_PLAY_FORWARD;
            } else {
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + mission + 0x1F1].object)->flags &= ~UI_FLAG_VISIBLE;
            }
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + mission + 0x1FB].object)->flags &= ~UI_FLAG_VISIBLE;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + mission + 0x1E7].object)->flags &= ~UI_FLAG_VISIBLE;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + mission + (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD)].object)->frame = 0;
        }
        if (challengeStarRelatedInd(aiPosSwapInputs.playerIndexNoVariants, aiPosSwapInputs.starMenuCursorPos)) {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 0x1D9].object)->flags |= UI_FLAG_VISIBLE;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 0x1D9].object)->playMode = UI_PLAY_FORWARD;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + aiPosSwapInputs.starMenuCursorPos + 0x1E7].object)->flags |= UI_FLAG_VISIBLE;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + aiPosSwapInputs.starMenuCursorPos + 0x1E7].object)->playMode = UI_PLAY_FORWARD;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + aiPosSwapInputs.starMenuCursorPos + (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD)].object)->frame = 0x00010000;
        } else {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 0x1D9].object)->flags &= ~UI_FLAG_VISIBLE;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + aiPosSwapInputs.starMenuCursorPos + 0x1E7].object)->flags &= ~UI_FLAG_VISIBLE;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + aiPosSwapInputs.starMenuCursorPos + (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD)].object)->frame = 0;
        }
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + aiPosSwapInputs.starMenuCursorPos + 0x1FB].object)->flags |= UI_FLAG_VISIBLE;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + aiPosSwapInputs.starMenuCursorPos + 0x1FB].object)->playMode = UI_PLAY_FORWARD;
        ((u8*)&aiPosSwapInputs)[0xCF73] = 1;
    }
    if (((u8*)&aiPosSwapInputs)[0xCF73] != 0) {
        ((u8*)&aiPosSwapInputs)[0xCF74] = 0;
        ((u8*)&aiPosSwapInputs)[0xCF73] = 0;
    }
}

void battingOrderProcessInputs(MenuScene* scene, s32 port) {
    s32 inputPort = port;
    u16 buttons;
    s32 selection;
    s32 player;
    s32 completeCount;
    s32 firstComplete;

    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        if (port != 0) {
            return;
        }
        port = ((u8*)&aiPosSwapInputs)[0xCF43] != 0 ? 1 : 0;
    }
    if (g_d_GameSettings._06 != 2) {
        buttons = Static_Stats_Tables.controllerInputs[inputPort].newInput;
    } else {
        buttons = aiPosSwapInputs.playerInputs[port].newInput;
    }
    switch (buttons) {
    case INPUT_BUTTON_X:
        if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER &&
        g_d_GameSettings._06 != 2) {
            if (aiPosSwapInputs.teamManagement_cursorPos[port] != 0) {
                s32 stance;
                CharacterStats* stats;
                selection = aiPosSwapInputs.teamManagement_cursorPos[port] - 1;
                stats = &inMemRoster[port][selection];
                stance = stats->stats.BattingStance + stats->stats.FieldingArm * 2 + 1;
                if (stance == 4) {
                    stance = 0;
                }
                stats->stats.BattingStance = stance % 2;
                stats->stats.FieldingArm = stance / 2;
                TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0xAC)->frame = stance << 16;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            ((u8*)&aiPosSwapInputs)[0xCF58 + port] = 0;
        }
        break;
    }
    if (((u8*)&aiPosSwapInputs)[0xCF9E + port] != 0) {
        if (g_d_GameSettings._06 != 2) {
            if (aiPosSwapInputs.teamManagement_cursorPos[port] != 0) {
                transferStatsToInMemRoster((u8)port);
                sndFXRelated(INPUT_TRIGGER_L);
            } else {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            }
            if (aiPosSwapInputs.teamManagement_cursorPos[port] != 0 &&
                g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                s32 position;
                s32 teamOffset = port * 9;
                selection = aiPosSwapInputs.teamManagement_cursorPos[port] - 1;
                position = lineUpInfoStruct[port][selection][2];
                if (Static_Stats_Tables.charIsStarred[port][selection] != 0) {
                    TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x76)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x76)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x88)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x88)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x88)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x140)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x140)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x152)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x152)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x152)->playMode = UI_PLAY_FORWARD;
                } else {
                    TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x88)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x88)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x88)->playMode = UI_PLAY_STOP;
                    TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x152)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x152)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x152)->playMode = UI_PLAY_STOP;
                }
            }
        }
        ((u8*)&aiPosSwapInputs)[0xCF9E + port] = 0;
    }
    if (((u8*)&aiPosSwapInputs)[0xCF65 + port] != 0) {
        if (g_d_GameSettings._06 != 2) {
            if (((u8*)&aiPosSwapInputs)[0xCF61 + port] != 0) {
                switch (((u8*)&aiPosSwapInputs)[0xCF67 + port]) {
                case 0:
                    fn_80058E0C(scene, (u8)port);
                    break;
                case 1:
                    fn_80058B20(scene, (u8)port);
                    break;
                }
            } else {
                if (((u8*)&aiPosSwapInputs)[0xCF67 + port] == 0) {
                    if ((TEAM_MANAGEMENT_RECORD(scene, port + 0x19A)->frame >> 16) > 5) {
                        TEAM_MANAGEMENT_RECORD(scene, port + 0x19A)->frame = 0x00050000;
                    }
                    TEAM_MANAGEMENT_RECORD(scene, port + 0x19A)->playMode = UI_PLAY_BACKWARD;
                    TEAM_MANAGEMENT_RECORD(scene, port + 0x19C)->playMode = UI_PLAY_BACKWARD;
                    TEAM_MANAGEMENT_RECORD(scene, port + 0x1AC)->playMode = UI_PLAY_BACKWARD;
                    completeCount = maybeCheckAndResetGrapicsElement(scene, port + 0x19A, 0) != 0;
                    completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x19C, 0) != 0;
                    completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x1AC, 0) != 0;
                    if (completeCount == 3) {
                        ((u8*)&aiPosSwapInputs)[0xCF65 + port] = 0;
                    }
                } else {
                    if ((TEAM_MANAGEMENT_RECORD(scene, port + 0x19A)->frame >> 16) > 5) {
                        TEAM_MANAGEMENT_RECORD(scene, port + 0x19A)->frame = 0x00050000;
                    }
                    TEAM_MANAGEMENT_RECORD(scene, port + 0x19A)->playMode = UI_PLAY_BACKWARD;
                    TEAM_MANAGEMENT_RECORD(scene, port + 0x1C8)->playMode = UI_PLAY_BACKWARD;
                    if (maybeCheckAndResetGrapicsElement(scene, port + 0x1C8, 0) != 0) {
                        ((u8*)&aiPosSwapInputs)[0xCF65 + port] = 0;
                    }
                }
                ((u8*)&aiPosSwapInputs)[0xCF63 + port] = 0;
            }
        } else {
            if (((u8*)&aiPosSwapInputs)[0xCF61 + aiPosSwapInputs.playerWhoPaused] != 0) {
                switch (((u8*)&aiPosSwapInputs)[0xCF67 + port]) {
                case 0:
                    fn_80058644(scene);
                    break;
                case 1:
                    zMenuLoadGraphics(scene);
                    break;
                }
            } else {
                if (((u8*)&aiPosSwapInputs)[0xCF67 + port] == 0) {
                    if ((TEAM_MANAGEMENT_RECORD(scene, 0x118)->frame >> 16) > 5) {
                        TEAM_MANAGEMENT_RECORD(scene, 0x118)->frame = 0x00050000;
                    }
                    TEAM_MANAGEMENT_RECORD(scene, 0x118)->playMode = UI_PLAY_BACKWARD;
                    TEAM_MANAGEMENT_RECORD(scene, 0x119)->playMode = UI_PLAY_BACKWARD;
                    TEAM_MANAGEMENT_RECORD(scene, 0x121)->playMode = UI_PLAY_BACKWARD;
                    completeCount = maybeCheckAndResetGrapicsElement(scene, 0x118, 0) != 0;
                    completeCount += maybeCheckAndResetGrapicsElement(scene, 0x119, 0) != 0;
                    completeCount += maybeCheckAndResetGrapicsElement(scene, 0x121, 0) != 0;
                    if (completeCount == 3) {
                        ((u8*)&aiPosSwapInputs)[0xCF65 + port] = 0;
                    }
                } else {
                    if ((TEAM_MANAGEMENT_RECORD(scene, 0x118)->frame >> 16) > 5) {
                        TEAM_MANAGEMENT_RECORD(scene, 0x118)->frame = 0x00050000;
                    }
                    TEAM_MANAGEMENT_RECORD(scene, 0x118)->playMode = UI_PLAY_BACKWARD;
                    TEAM_MANAGEMENT_RECORD(scene, 0x12F)->playMode = UI_PLAY_BACKWARD;
                    if (maybeCheckAndResetGrapicsElement(scene, 0x12F, 0) != 0) {
                        ((u8*)&aiPosSwapInputs)[0xCF65 + aiPosSwapInputs.playerWhoPaused] = 0;
                    }
                }
                ((u8*)&aiPosSwapInputs)[0xCF63 + aiPosSwapInputs.playerWhoPaused] = 0;
            }
        }
    }
    if (((u8*)&aiPosSwapInputs)[0xCF71] == 0) {
        return;
    }
    if (((u8*)&aiPosSwapInputs)[0xCF72] != 0) {
        switch (((u8*)&aiPosSwapInputs)[0xCF74]) {
        case 1:
            starMissionRelated1(scene);
            break;
        case 2:
            fn_800596D4(scene);
            break;
        case 3:
            if (((u8*)&aiPosSwapInputs)[0xCF73] == 0) {
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16E : 0x1D7))->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16A : 0x1D3))->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16C : 0x1D5))->playMode = UI_PLAY_BACKWARD;
                ((u8*)&aiPosSwapInputs)[0xCF73] = 1;
            }
            if (((u8*)&aiPosSwapInputs)[0xCF73] != 0) {
                firstComplete = maybeCheckAndResetGrapicsElement(scene, (g_d_GameSettings._06 == 2 ? 0x16E : 0x1D7), 0) != 0;
                completeCount = firstComplete + (maybeCheckAndResetGrapicsElement(scene, (g_d_GameSettings._06 == 2 ? 0x16A : 0x1D3), 0) != 0);
                completeCount += maybeCheckAndResetGrapicsElement(scene, (g_d_GameSettings._06 == 2 ? 0x16C : 0x1D5), 0) != 0;
                if (completeCount == 3) {
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16A : 0x1D3))->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16B : 0x1D4))->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16C : 0x1D5))->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16E : 0x1D7))->flags &= ~UI_FLAG_VISIBLE;
                    for (player = 0; player < 3; player++) {
                        text_freeBlock(((u8*)&aiPosSwapInputs)[0xCF7A + player]);
                    }
                    fn_8000F8F4(scene);
                    ((u8*)&aiPosSwapInputs)[0xCF72] = 0;
                    ((u8*)&aiPosSwapInputs)[0xCF74] = 0;
                    ((u8*)&aiPosSwapInputs)[0xCF73] = 0;
                }
            }
            break;
        }
    } else {
        firstComplete = maybeCheckAndResetGrapicsElement(scene, (g_d_GameSettings._06 == 2 ? 0x16A : 0x1D3), 0) != 0;
        if (firstComplete + (maybeCheckAndResetGrapicsElement(scene, (g_d_GameSettings._06 == 2 ? 0x16C : 0x1D5), 0) != 0) == 2) {
            ((u8*)&aiPosSwapInputs)[0xCF73] = 0;
            ((u8*)&aiPosSwapInputs)[0xCF71] = 0;
        }
    }
}

void teamManagementGraphics_fieldingAlignmentScreen(MenuScene* scene) {
    s32 position;
    s32 player;
    s32 team = ((s8*)&aiPosSwapInputs)[0xCF3B];

    for (player = 0; player < 9; player++) {
        CharacterStats* stats;
        BOOL isSuperstar;

        if (((u8*)&aiPosSwapInputs)[0xCFA2 + team] == 2) {
            continue;
        }

        position = lineUpInfoStruct[team][player][2];
        stats = &inMemRoster[team][player];
        load_Icon(scene, position + 0x23, 1, 0x83, stats->stats.CharID);
        TEAM_MANAGEMENT_RECORD(scene, player + 0x11)->flags &= ~UI_FLAG_VISIBLE;

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
        } else {
            isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
        }

        if ((u8)isSuperstar != 0 && !(team == 1 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
            TEAM_MANAGEMENT_RECORD(scene, position + 0x3E)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, position + 0x47)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, position + 0x47)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, position + 0x47)->playMode = UI_PLAY_FORWARD;
        } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                   g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            TEAM_MANAGEMENT_RECORD(scene, position + 0x3E)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, position + 0x47)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, position + 0x47)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, position + 0x47)->playMode = UI_PLAY_STOP;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, position + 0x3E)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, position + 0x47)->flags &= ~UI_FLAG_VISIBLE;
        }

        TEAM_MANAGEMENT_RECORD(scene, player + 0x35)->flags &= ~UI_FLAG_VISIBLE;
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && (s8)team != 0) {
            TEAM_MANAGEMENT_RECORD(scene, player + 0x1A)->elementIndex = 0x1E + (u8)((s8)Static_Stats_Tables.playerNumberByPort[0] == 0);
        } else {
            TEAM_MANAGEMENT_RECORD(scene, player + 0x1A)->elementIndex = 0x1E + (s8)Static_Stats_Tables.playerNumberByPort[team];
        }
    }
}

void teamManagementGraphics_battingOrderScreen(MenuScene* scene) {
    s32 team = ((s8*)&aiPosSwapInputs)[0xCF3B];
    s32 player;
    s32 orderFrame;

    for (player = 0, orderFrame = 0; player < 9; player++, orderFrame += 0x10000) {
        CharacterStats* stats = &inMemRoster[team][player];
        BOOL isSuperstar;

        TEAM_MANAGEMENT_RECORD(scene, player + 0x5A)->frame = orderFrame;
        TEAM_MANAGEMENT_RECORD(scene, player + 0x6C)->flags &= ~UI_FLAG_VISIBLE;

        if (((u8*)&aiPosSwapInputs)[0xCFA2 + team] == 0) {
            load_Icon(scene, player + 0x63, 1, 0x83, stats->stats.CharID);
            TEAM_MANAGEMENT_RECORD(scene, player + 0xAB)->frame = stats->stats.CharacterClass << 16;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x99)->frame = (stats->stats.BattingStance + stats->stats.FieldingArm * 2) << 16;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x134)->flags &= ~UI_FLAG_VISIBLE;
        } else {
            ChallengeTrackingStruct* tracking;
            s32 requiredFlags;
            s32 remainingFlags;
            s32 flag;
            load_Icon(scene, player + 0x63, 1, 0x83, inMemRoster[1][player].stats.CharID);
            tracking = &g_Challenge.characters[inMemRoster[1][player].stats.CharID];
            requiredFlags = (s8)tracking->scoutFlagPointer->flagsRequired[g_Challenge.difficulty][g_Challenge.captain];
            remainingFlags = requiredFlags - (s8)tracking->scoutFlagsAchieved;
            for (flag = 0; flag < 5; flag++) {
                if (flag < requiredFlags && flag < remainingFlags) {
                    TEAM_MANAGEMENT_RECORD(scene, flag + player * 5 + 0x13D)->frame = 0;
                } else if (flag < requiredFlags) {
                    TEAM_MANAGEMENT_RECORD(scene, flag + player * 5 + 0x13D)->playMode = UI_PLAY_FORWARD;
                    if (g_d_GameSettings._06 == 2) {
                        sndFXStartEx(0x1B1, 0x7F, 0x3F, 0);
                    } else {
                        sndFXStartEx(0x1E6, 0x7F, 0x3F, 0);
                    }
                } else if (flag >= requiredFlags) {
                    TEAM_MANAGEMENT_RECORD(scene, flag + player * 5 + 0x13D)->flags &= ~UI_FLAG_VISIBLE;
                }
            }
            TEAM_MANAGEMENT_RECORD(scene, player + 0xAB)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x99)->flags &= ~UI_FLAG_VISIBLE;
        }

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
        } else {
            isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
        }

        if ((u8)isSuperstar != 0 && !(team == 1 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
            TEAM_MANAGEMENT_RECORD(scene, player + 0x7E)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->playMode = UI_PLAY_FORWARD;
        } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                   g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            TEAM_MANAGEMENT_RECORD(scene, player + 0x7E)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->playMode = UI_PLAY_STOP;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, player + 0x7E)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->flags &= ~UI_FLAG_VISIBLE;
        }

        TEAM_MANAGEMENT_RECORD(scene, player + 0x75)->flags &= ~UI_FLAG_VISIBLE;
    }
}

void fn_8005B760(MenuScene* scene, s32 port) {
    if (gameSetUpStep[0x37 + port] == 0) {
        s8 selection = ((s8*)&aiPosSwapInputs)[0xCF46 + port];

        if (selection != 0) {
            s32 index = selection - 1;
            u8 lineupPosition = lineUpInfoStruct[port][index][2];
            s32 i;

            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD(scene, i + 0x75)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, i + 0x35)->flags &= ~UI_FLAG_VISIBLE;
            }

            if (((u8*)&aiPosSwapInputs)[0xCFA2 + port] == 0) {
                TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x23)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x1A)->playMode = UI_PLAY_FORWARD;
            } else {
                TEAM_MANAGEMENT_RECORD(scene, index + 0x63)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, index + 0x51)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, index + 0x51)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, index + 0x51)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, index + 0x6C)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, index + 0x6C)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, index + 0x6C)->playMode = UI_PLAY_FORWARD;
            }

            TEAM_MANAGEMENT_RECORD(scene, index + 0x6C)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, index + 0x6C)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, index + 0x6C)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, index + 0x75)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, index + 0x75)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, index + 0x75)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x35)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x35)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x35)->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, index);
            TEAM_MANAGEMENT_RECORD(scene, 0xE)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, 0xE)->playMode = UI_PLAY_STOP;
        }

        makeCursorUnmovable(port);
        gameSetUpStep[0x37 + port] = 1;
    }
}

void challengeTeamManagementRelated(MenuScene* scene) {
    s32 team;
    s32 player;
    s32 orderFrame;

    for (team = 0; team < 2; team++) {
        for (player = 0, orderFrame = 0; player < 9; player++, orderFrame += 0x10000) {
            CharacterStats* stats = &inMemRoster[team][player];

            load_Icon(scene, player + team * 9 + 0x40, 1, 0x83, stats->stats.CharID);
            TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x2E)->frame = orderFrame;
            if (team == 0) {
                BOOL isSuperstar;
                TEAM_MANAGEMENT_RECORD(scene, player + 0xD0)->frame = inMemRoster[0][player].stats.CharacterClass << 16;
                TEAM_MANAGEMENT_RECORD(scene, player + 0xAC)->frame =
                    (inMemRoster[0][player].stats.FieldingArm * 2 + inMemRoster[0][player].stats.BattingStance) << 16;
                TEAM_MANAGEMENT_RECORD(scene, player + 0x64)->flags &= ~UI_FLAG_VISIBLE;
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                    isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
                } else {
                    isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
                }
                if ((u8)isSuperstar != 0 && team == 0) {
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x76)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x88)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x88)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x88)->playMode = UI_PLAY_FORWARD;
                } else {
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x88)->flags &= ~UI_FLAG_VISIBLE;
                }
            } else {
                s32 requiredFlags;
                s32 flag;
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0xD0)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0xAC)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x88)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x64)->flags &= ~UI_FLAG_VISIBLE;
                requiredFlags = (s8)g_Challenge.characters[inMemRoster[1][player].stats.CharID].scoutFlagPointer->flagsRequired[g_Challenge.difficulty][g_Challenge.captain];
                for (flag = 0; flag < 5; flag++) {
                    if (flag < requiredFlags) {
                        TEAM_MANAGEMENT_RECORD(scene, flag + player * 5 + 0x16D)->frame = 0;
                        TEAM_MANAGEMENT_RECORD(scene, flag + player * 5 + 0x16D)->playMode = UI_PLAY_STOP;
                    } else if (flag >= requiredFlags) {
                        TEAM_MANAGEMENT_RECORD(scene, flag + player * 5 + 0x16D)->flags &= ~UI_FLAG_VISIBLE;
                    }
                }
            }
        }
        TEAM_MANAGEMENT_RECORD(scene, team + 8)->frame = Static_Stats_Tables.teamName[team] << 16;
        TEAM_MANAGEMENT_RECORD(scene, team + 0xC)->frame = Static_Stats_Tables.teamName[team] << 16;
    }
}

void teamManagementGraphics_fieldingAlignmentInfo(MenuScene* scene) {
    s32 team;
    s32 player;

    for (team = 0; team < 2; team++) {
        for (player = 0; player < 9; player++) {
            CharacterStats* stats = &inMemRoster[team][player];
            BOOL isSuperstar;

            load_Icon(scene, lineUpInfoStruct[team][player][2] + team * 9 + 0x10A, 1, 0x83, stats->stats.CharID);
            TEAM_MANAGEMENT_RECORD(scene, team * 9 + player + 0xE6)->flags &= ~UI_FLAG_VISIBLE;

            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
            } else {
                isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
            }

            if ((u8)isSuperstar != 0) {
                TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[team][player][2] + team * 9 + 0x140)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[team][player][2] + team * 9 + 0x152)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[team][player][2] + team * 9 + 0x152)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[team][player][2] + team * 9 + 0x152)->playMode = UI_PLAY_FORWARD;
            } else if (superstarUnlocked[stats->stats.CharID] != 0) {
                TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[team][player][2] + team * 9 + 0x140)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[team][player][2] + team * 9 + 0x152)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[team][player][2] + team * 9 + 0x152)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[team][player][2] + team * 9 + 0x152)->playMode = UI_PLAY_STOP;
            } else {
                TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[team][player][2] + team * 9 + 0x152)->flags &= ~UI_FLAG_VISIBLE;
            }

            TEAM_MANAGEMENT_RECORD(scene, team * 9 + player + 0x12E)->flags &= ~UI_FLAG_VISIBLE;
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && team != 0) {
                TEAM_MANAGEMENT_RECORD(scene, team * 9 + player + 0xF8)->elementIndex = 0x1E + (Static_Stats_Tables.playerNumberByPort[0] == 0);
            } else {
                TEAM_MANAGEMENT_RECORD(scene, team * 9 + player + 0xF8)->elementIndex = 0x1E + (s8)Static_Stats_Tables.playerNumberByPort[team];
            }
        }
    }
}

void teamManagementGraphics_battingOrderInfo(MenuScene* scene) {
    s32 team;
    s32 player;
    s32 orderFrame;

    for (team = 0; team < 2; team++) {
        for (player = 0, orderFrame = 0; player < 9; player++, orderFrame += 0x10000) {
            CharacterStats* stats = &inMemRoster[team][player];
            BOOL isSuperstar;

            load_Icon(scene, player + team * 9 + 0x40, 1, 0x83, stats->stats.CharID);
            TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x2E)->frame = orderFrame;
            TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0xD0)->frame = stats->stats.CharacterClass << 16;
            TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0xAC)->frame = (stats->stats.BattingStance + stats->stats.FieldingArm * 2) << 16;

            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
            } else {
                isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
            }

            if ((u8)isSuperstar != 0) {
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x76)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x88)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x88)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x88)->playMode = UI_PLAY_FORWARD;
            } else if (superstarUnlocked[stats->stats.CharID] != 0) {
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x76)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x88)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x88)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x88)->playMode = UI_PLAY_STOP;
            } else {
                TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x88)->flags &= ~UI_FLAG_VISIBLE;
            }

            TEAM_MANAGEMENT_RECORD(scene, player + team * 9 + 0x64)->flags &= ~UI_FLAG_VISIBLE;
        }

        TEAM_MANAGEMENT_RECORD(scene, team + 8)->frame =
            Static_Stats_Tables.teamName[team] << 16;
        TEAM_MANAGEMENT_RECORD(scene, team + 0xC)->frame =
            Static_Stats_Tables.teamName[team] << 16;
    }
}

void fn_8005C5C4(MenuScene* scene, s32 port) {
    if (gameSetUpStep[0x37 + port] != 0) {
        return;
    }

    if (g_d_GameSettings._06 == 2) {
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle].object)->frame = 0x00140000;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle].object)->playMode = UI_PLAY_BACKWARD;
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle].object)->frame = 0x00140000;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 1].object)->frame = 0x00140000;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle].object)->playMode = UI_PLAY_BACKWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 1].object)->playMode = UI_PLAY_BACKWARD;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        if (port != 0) {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->frame = 0x00140000;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->playMode = UI_PLAY_BACKWARD;
        } else {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->frame = 0x001E0000;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->playMode = UI_PLAY_FORWARD;
        }
    } else {
        if (((u32)((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->frame >> 16) == 0x1E) {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->frame = 0x001E0000;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->playMode = UI_PLAY_FORWARD;
        } else {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->frame = 0x00140000;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->playMode = UI_PLAY_BACKWARD;
        }
    }

    TEAM_MANAGEMENT_RECORD(scene, port + 0x16)->frame = 0x000A0000;
    TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->playMode = UI_PLAY_BACKWARD;
    TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->frame = 0x00140000;
    TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->playMode = UI_PLAY_FORWARD;
    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = 1;
}

void fn_8005C830(MenuScene* scene, s32 port, s32 selection) {
    s32 chemistryIndex;

    for (chemistryIndex = 0; chemistryIndex < 9; chemistryIndex++) {
        s32 rosterIndex;
        CHAR_ID characterID = Static_Stats_Tables.highChemTeammates[port][selection][chemistryIndex];

        for (rosterIndex = 0; rosterIndex < 9; rosterIndex++) {
            CharacterStats* stats = &inMemRoster[port][rosterIndex];

            if (stats->stats.CharID != characterID) {
                continue;
            }

            if (((u8*)&aiPosSwapInputs)[0xCF52 + port] == ROSTER_VIEW_BATTING_ORDER) {
                if (g_d_GameSettings._06 != 2) {
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + (port * 9) + 0x52)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + (port * 9) + 0x52)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + (port * 9) + 0x64)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + (port * 9) + 0x64)->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + (port * 9) + 0x64)->playMode = UI_PLAY_FORWARD;
                } else {
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + 0x35)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + 0x35)->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + 0x35)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + 0x35)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x6C)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x6C)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x6C)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x75)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x75)->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x75)->playMode = UI_PLAY_FORWARD;
                }
            } else {
                if (g_d_GameSettings._06 != 2) {
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + (port * 9) + 0x12E)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + (port * 9) + 0x12E)->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + (port * 9) + 0x12E)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + (port * 9) + 0x12E)->playMode = UI_PLAY_FORWARD;
                } else {
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + 0x35)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + 0x35)->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + 0x35)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, lineUpInfoStruct[port][rosterIndex][2] + 0x35)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x6C)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x6C)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x6C)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x75)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x75)->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD(scene, rosterIndex + 0x75)->playMode = UI_PLAY_FORWARD;
                }
            }
        }
    }
}

void fn_8005CCE4(MenuScene* scene, s32 port) {
    s32 selection;
    s32 swapSelection;
    u8 position;
    u8 swapPosition;
    s32 player;

    if (gameSetUpStep[0x37 + port] != 0) {
        return;
    }
    selection = aiPosSwapInputs.teamManagement_cursorPos[port] - 1;
    swapSelection = aiPosSwapInputs.charSelectedToBeSwappedCharID[port];
    position = lineUpInfoStruct[port][selection][2];
    swapPosition = lineUpInfoStruct[port][swapSelection][2];

    if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {

        if (selection != swapSelection) {
            TEAM_MANAGEMENT_RECORD(scene, swapSelection + (port * 9) + 0x1C)->frame = 0x000A0000;
            TEAM_MANAGEMENT_RECORD(scene, swapSelection + (port * 9) + 0x1C)->playMode = UI_PLAY_BACKWARD;
        }
        TEAM_MANAGEMENT_RECORD(scene, swapSelection + (port * 9) + 0x40)->playMode = UI_PLAY_BACKWARD;
        load_Icon(scene, selection + (port * 9) + 0x40, 1, 0x83, inMemRoster[port][selection].stats.CharID);
        load_Icon(scene, swapSelection + (port * 9) + 0x40, 1, 0x83, inMemRoster[port][swapSelection].stats.CharID);
        TEAM_MANAGEMENT_RECORD(scene, selection + (port * 9) + 0xD0)->frame = inMemRoster[port][selection].stats.CharacterClass << 16;
        TEAM_MANAGEMENT_RECORD(scene, swapSelection + (port * 9) + 0xD0)->frame = inMemRoster[port][swapSelection].stats.CharacterClass << 16;
        TEAM_MANAGEMENT_RECORD(scene, selection + (port * 9) + 0xAC)->frame =
        (inMemRoster[port][selection].stats.FieldingArm * 2 + inMemRoster[port][selection].stats.BattingStance) << 16;
        TEAM_MANAGEMENT_RECORD(scene, swapSelection + (port * 9) + 0xAC)->frame =
        (inMemRoster[port][swapSelection].stats.FieldingArm * 2 + inMemRoster[port][swapSelection].stats.BattingStance) << 16;
        for (player = 0; player < 9; player++) {
            CharacterStats* stats = &inMemRoster[port][player];
            BOOL isSuperstar;
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
            } else {
                isSuperstar = ((u8*)&Static_Stats_Tables)[0x489B + (port * 9) + player];
            }
            if ((u8)isSuperstar != 0) {
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76) + player)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76) + player)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88) + player)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88) + player)->frame = 0x000F0000;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88) + player)->playMode = UI_PLAY_FORWARD;
            } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76) + player)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76) + player)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88) + player)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88) + player)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88) + player)->playMode = UI_PLAY_STOP;
            } else {
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76) + player)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88) + player)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD(scene, player + (g_d_GameSettings._06 == 2 ? 0x75 : (port * 9) + 0x64))->flags &= ~UI_FLAG_VISIBLE;
        }
        TEAM_MANAGEMENT_RECORD(scene, selection + (port * 9) + 0x64)->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD(scene, selection + (port * 9) + 0x64)->elementIndex = 0x2A;
        TEAM_MANAGEMENT_RECORD(scene, selection + (port * 9) + 0x64)->playMode = UI_PLAY_FORWARD;
        fn_8005C830(scene, port, selection);
    } else {
        if (g_d_GameSettings._06 != 2) {

            load_Icon(scene, (s8)swapPosition + (port * 9) + 0x10A, 1, 0x83, inMemRoster[port][swapSelection].stats.CharID);
            load_Icon(scene, (s8)position + (port * 9) + 0x10A, 1, 0x83, inMemRoster[port][selection].stats.CharID);
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + (port * 9) + 0x10A)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + (port * 9) + 0xF8)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + (port * 9) + 0x10A)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + (port * 9) + 0xF8)->playMode = UI_PLAY_FORWARD;
            for (player = 0; player < 9; player++) {
                CharacterStats* stats = &inMemRoster[port][player];
                BOOL isSuperstar;
                u8 lineupPosition = (u8)lineUpInfoStruct[port][player][2];
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                    isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
                } else {
                    isSuperstar = ((u8*)&Static_Stats_Tables)[0x489B + (port * 9) + player];
                }
                if ((u8)isSuperstar != 0) {
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x3E : (port * 9) + 0x140) + (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x3E : (port * 9) + 0x140) + (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152) + (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152) + (s8)lineupPosition)->frame = 0x000F0000;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152) + (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
                } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                    g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x3E : (port * 9) + 0x140) + (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x3E : (port * 9) + 0x140) + (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152) + (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152) + (s8)lineupPosition)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152) + (s8)lineupPosition)->playMode = UI_PLAY_STOP;
                } else {
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x3E : (port * 9) + 0x140) + (s8)lineupPosition)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152) + (s8)lineupPosition)->flags &= ~UI_FLAG_VISIBLE;
                }
                TEAM_MANAGEMENT_RECORD(scene, player + (port * 9) + 0x12E)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + (port * 9) + 0x12E)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + (port * 9) + 0x12E)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + (port * 9) + 0x12E)->playMode = UI_PLAY_FORWARD;
        } else {

            load_Icon(scene, (s8)swapPosition + 0x23, 1, 0x83, inMemRoster[port][swapSelection].stats.CharID);
            load_Icon(scene, (s8)position + 0x23, 1, 0x83, inMemRoster[port][selection].stats.CharID);
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x23)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x1A)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + 0x23)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + 0x1A)->playMode = UI_PLAY_FORWARD;
            for (player = 0; player < 9; player++) {
                CharacterStats* stats = &inMemRoster[port][player];
                BOOL isSuperstar;
                u8 lineupPosition = (u8)lineUpInfoStruct[port][player][2];
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                    isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
                } else {
                    isSuperstar = ((u8*)&Static_Stats_Tables)[0x489B + (port * 9) + player];
                }
                if ((u8)isSuperstar != 0 && !(port == 1 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x3E)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x3E)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x47)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x47)->frame = 0x000F0000;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x47)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x7E)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x7E)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->frame = 0x000F0000;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->playMode = UI_PLAY_FORWARD;
                } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                    g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x3E)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x3E)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x47)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x47)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x47)->playMode = UI_PLAY_STOP;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x7E)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x7E)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->playMode = UI_PLAY_STOP;
                } else {
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x3E)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + 0x47)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, player + (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76))->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, player + (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88))->flags &= ~UI_FLAG_VISIBLE;
                }
                TEAM_MANAGEMENT_RECORD(scene, player + 0x35)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, player + 0x75)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD(scene, swapSelection + 0x75)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, swapSelection + 0x75)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, swapSelection + 0x75)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + 0x35)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + 0x35)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + 0x35)->playMode = UI_PLAY_FORWARD;
        }
        fn_8005C830(scene, port, swapSelection);
        aiPosSwapInputs.teamManagement_cursorPos[port] = lineupOrderChangeRelated((u8)port, lineUpInfoStruct[port][swapSelection][2]);
    }
    aiPosSwapInputs.charSelectedToBeSwappedCharID[port] = (u8)CHAR_ID_NONE;
    gameSetUpStep[0x5D + port] = 0;
    gameSetUpStep[0x37 + port] = 2;
}


void fn_8005DE14(MenuScene* scene, s32 port) {
    s32 selection;
    s32 previousSelection;
    s32 swapSelection;
    u8 position;
    u8 previousPosition;
    u8 swapPosition;
    s32 i;

    if (gameSetUpStep[0x37 + port] != 0) {
        return;
    }
    selection = (s8)(aiPosSwapInputs.teamManagement_cursorPos[port] - 1);
    previousSelection = (s8)(aiPosSwapInputs.teamManagement_prevCursorPos[port] - 1);
    swapSelection = (s8)aiPosSwapInputs.charSelectedToBeSwappedCharID[port];

    if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
        if (g_d_GameSettings._06 != 2) {
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x64)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x40)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x40)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x1C)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x1C)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x52)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x52)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x64)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x64)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x64)->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x40)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x40)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x1C)->frame = 0x000A0000;
            TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x1C)->playMode = UI_PLAY_BACKWARD;
            if (swapSelection != CHAR_ID_NONE) {
                TEAM_MANAGEMENT_RECORD(scene, swapSelection + port * 9 + 0x1C)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD(scene, swapSelection + port * 9 + 0x1C)->playMode = UI_PLAY_STOP;
                TEAM_MANAGEMENT_RECORD(scene, swapSelection + port * 9 + 0x40)->playMode = UI_PLAY_FORWARD;
            }
        } else {
            position = lineUpInfoStruct[port][selection][2];
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD(scene, i + 0x75)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, i + 0x35)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x63)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x63)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x51)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x51)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x6C)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x75)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x75)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x6C)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x75)->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x63)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x63)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x51)->frame = 0x000A0000;
            TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x51)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x35)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x35)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x35)->playMode = UI_PLAY_FORWARD;
            if (swapSelection != CHAR_ID_NONE) {
                TEAM_MANAGEMENT_RECORD(scene, swapSelection + 0x51)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD(scene, swapSelection + 0x51)->playMode = UI_PLAY_STOP;
                TEAM_MANAGEMENT_RECORD(scene, swapSelection + 0x63)->playMode = UI_PLAY_FORWARD;
            }
        }
    } else {
        position = lineUpInfoStruct[port][selection][2];
        previousPosition = lineUpInfoStruct[port][previousSelection][2];
        swapPosition = lineUpInfoStruct[port][swapSelection][2];
        if (g_d_GameSettings._06 != 2) {
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + port * 9 + 0x10A)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + port * 9 + 0xF8)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + port * 9 + 0xE6)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, (s8)previousPosition + port * 9 + 0x10A)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)previousPosition + port * 9 + 0xF8)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)previousPosition + port * 9 + 0xE6)->flags &= ~UI_FLAG_VISIBLE;
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x12E)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + port * 9 + 0x12E)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + port * 9 + 0x12E)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + port * 9 + 0x12E)->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            if (swapSelection != CHAR_ID_NONE) {
                TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + port * 9 + 0x10A)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + port * 9 + 0xF8)->playMode = UI_PLAY_FORWARD;
            }
        } else {
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x23)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x1A)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x11)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, (s8)previousPosition + 0x23)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)previousPosition + 0x1A)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)previousPosition + 0x11)->flags &= ~UI_FLAG_VISIBLE;
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD(scene, i + 0x35)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, i + 0x75)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x6C)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x6C)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x6C)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x75)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x75)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x75)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x35)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x35)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x35)->playMode = UI_PLAY_FORWARD;
            if (swapSelection != CHAR_ID_NONE) {
                TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + 0x23)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + 0x1A)->playMode = UI_PLAY_FORWARD;
            }
            fn_8005C830(scene, port, selection);
        }
    }
    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = 1;
}

void fn_8005E9D8(MenuScene* scene, s32 port) {
    s8 currentSelection = ((s8*)&aiPosSwapInputs)[0xCF46 + port];
    s8 previousSelection = ((s8*)&aiPosSwapInputs)[0xCF48 + port];

    if (currentSelection != previousSelection) {
        fn_8005DE14(scene, port);
        if (gameSetUpStep[0x37 + port] == 1) {
            makeCursorMovable(port);
            gameSetUpStep[0x37 + port] = 2;
        }
    } else if (((u8*)&aiPosSwapInputs)[0xCF3C + port] != 0) {
        if (gameSetUpStep[0x37 + port] == 0) {
            s32 selection = ((u8*)&aiPosSwapInputs)[0xCF3E + port];
            u8 mode = ((u8*)&aiPosSwapInputs)[0xCF52 + port];
            u8 position = ((u8*)lineUpInfoStruct)[port * 0x24 + (u8)selection * 4 + 2];

            if (mode == 0) {
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + selection + port * 9 + 0x1C].object)->frame = 0x000A0000;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + selection + port * 9 + 0x1C].object)->playMode = UI_PLAY_STOP;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + selection + port * 9 + 0x40].object)->frame = 0;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + selection + port * 9 + 0x40].object)->playMode = UI_PLAY_FORWARD;
            } else if (g_d_GameSettings._06 != 2) {
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (s8)position + port * 9 + 0x10A].object)->frame = 0;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (s8)position + port * 9 + 0x10A].object)->playMode = UI_PLAY_FORWARD;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (s8)position + port * 9 + 0xF8].object)->frame = 0;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (s8)position + port * 9 + 0xF8].object)->playMode = UI_PLAY_FORWARD;
            } else {
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (s8)position + 0x23].object)->frame = 0;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (s8)position + 0x23].object)->playMode = UI_PLAY_FORWARD;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (s8)position + 0x1A].object)->frame = 0;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + (s8)position + 0x1A].object)->playMode = UI_PLAY_FORWARD;
            }
            gameSetUpStep[0x5D + port] = 0;
            gameSetUpStep[0x37 + port] = 2;
        }
    } else if (((u8*)&aiPosSwapInputs)[0xCF3C + port] == 0) {
        fn_8005CCE4(scene, port);
    }
}

void fn_8005EC88(MenuScene* scene, s32 port) {
    u8 lineupPosition;
    s32 i;

    if (gameSetUpStep[0x37 + port] == 0) {
        if (((s8*)&aiPosSwapInputs)[0xCF46 + port] != 0) {
            s32 index = (s8)aiPosSwapInputs.teamManagement_cursorPos[port] - 1;
            lineupPosition = lineUpInfoStruct[port][index][2];
            for (i = 0; i < 9; i += 3) {
                TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x64)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x12E)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x65)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x12F)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x66)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x130)->flags &= ~UI_FLAG_VISIBLE;
            }

            if (((u8*)&aiPosSwapInputs)[0xCF52 + port] == 0) {
                TEAM_MANAGEMENT_RECORD(scene, index + port * 9 + 0x40)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, index + port * 9 + 0x1C)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, index + port * 9 + 0x1C)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, index + port * 9 + 0x52)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, index + port * 9 + 0x52)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, index + port * 9 + 0x64)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, index + port * 9 + 0x64)->elementIndex = 0x2A;
                TEAM_MANAGEMENT_RECORD(scene, index + port * 9 + 0x64)->playMode = UI_PLAY_FORWARD;
                fn_8005C830(scene, port, index);
            } else if (((u8*)&aiPosSwapInputs)[0xCF52 + port] == 1) {
                TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + port * 9 + 0x10A)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + port * 9 + 0xF8)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + port * 9 + 0x12E)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + port * 9 + 0x12E)->elementIndex = 0x2A;
                TEAM_MANAGEMENT_RECORD(scene, (s8)lineupPosition + port * 9 + 0x12E)->playMode = UI_PLAY_FORWARD;
                fn_8005C830(scene, port, index);
            }
        }

        TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->frame = 0x000A0000;
        TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->playMode = UI_PLAY_BACKWARD;
        makeCursorUnmovable(port);
        gameSetUpStep[0x37 + port] = 1;
    }
}

void fn_8005F068(MenuScene* scene, s32 port) {
    s8 selection;
    u8 selectedPosition;
    s32 swapSelection;
    u8 swapPosition;
    s32 i;

    if (gameSetUpStep[0x37 + port] != 0) {
        return;
    }

    selection = (s8)(aiPosSwapInputs.teamManagement_cursorPos[port] - 1);
    selectedPosition = lineUpInfoStruct[port][selection][2];
    if (aiPosSwapInputs.charSelectedToBeSwappedCharID[port] != (u8)CHAR_ID_NONE) {
        swapSelection = (s8)aiPosSwapInputs.charSelectedToBeSwappedCharID[port];
        swapPosition = lineUpInfoStruct[port][swapSelection][2];
    }

    switch (aiPosSwapInputs.rosterView[port]) {
    case ROSTER_VIEW_BATTING_ORDER: {
            if (((u8*)&aiPosSwapInputs)[0xCF54 + port] == 1) {
                TEAM_MANAGEMENT_RECORD(scene, port + 0x14)->frame = 0x00140000;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x14)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x1A)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0xE2)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0xE4)->playMode = UI_PLAY_BACKWARD;
                for (i = 0; i < 9; i++) {
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x64)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x1C)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x1C)->playMode = UI_PLAY_STOP;
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x40)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x40)->playMode = UI_PLAY_STOP;
                }
                if (selection >= 0 && selection < 9) {
                    TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x1C)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x1C)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x52)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x52)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x64)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x64)->elementIndex = 0x2A;
                    TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x64)->playMode = UI_PLAY_FORWARD;
                    fn_8005C830(scene, port, selection);
                    TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x40)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, selection + port * 9 + 0x40)->playMode = UI_PLAY_FORWARD;
                    if (aiPosSwapInputs.charSelectedToBeSwappedCharID[port] != (u8)CHAR_ID_NONE) {
                        TEAM_MANAGEMENT_RECORD(scene, swapSelection + port * 9 + 0x1C)->frame = 0x000A0000;
                        TEAM_MANAGEMENT_RECORD(scene, swapSelection + port * 9 + 0x1C)->playMode = UI_PLAY_STOP;
                        TEAM_MANAGEMENT_RECORD(scene, swapSelection + port * 9 + 0x40)->frame = 0;
                        TEAM_MANAGEMENT_RECORD(scene, swapSelection + port * 9 + 0x40)->playMode = UI_PLAY_FORWARD;
                    }
                }
            }
            break;
        }
    case ROSTER_VIEW_DEFENSIVE_ALIGNMENT: {
            if (((u8*)&aiPosSwapInputs)[0xCF54 + port] != 1) {
                for (i = 0; i < 9; i++) {
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x10A)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x10A)->playMode = UI_PLAY_STOP;
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0xF8)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0xF8)->playMode = UI_PLAY_STOP;
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0xE6)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, i + port * 9 + 0x12E)->flags &= ~UI_FLAG_VISIBLE;
                }
                TEAM_MANAGEMENT_RECORD(scene, port + 0x14)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x14)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x1A)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0xE2)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0xE2)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, port + 0xE4)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0xE4)->flags |= UI_FLAG_VISIBLE;
                if (selection >= 0 && selection < 9) {
                    TEAM_MANAGEMENT_RECORD(scene, (s8)selectedPosition + port * 9 + 0x10A)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)selectedPosition + port * 9 + 0xF8)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)selectedPosition + port * 9 + 0xE6)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)selectedPosition + port * 9 + 0x12E)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)selectedPosition + port * 9 + 0x12E)->elementIndex = 0x2A;
                    TEAM_MANAGEMENT_RECORD(scene, (s8)selectedPosition + port * 9 + 0x12E)->playMode = UI_PLAY_FORWARD;
                    fn_8005C830(scene, port, selection);
                    if (aiPosSwapInputs.charSelectedToBeSwappedCharID[port] != (u8)CHAR_ID_NONE) {
                        TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + port * 9 + 0x10A)->playMode = UI_PLAY_FORWARD;
                        TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + port * 9 + 0xF8)->playMode = UI_PLAY_FORWARD;
                    }
                }
            }
            break;
        }
    }

    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = 1;
}

void fn_8005F734(MenuScene* scene, s32 port) {
    if (gameSetUpStep[0x37 + port] == 0) {
        TEAM_MANAGEMENT_RECORD(scene, port)->elementIndex = 0x49;
        TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x00320000;
        TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_BACKWARD;

        TEAM_MANAGEMENT_RECORD(scene, port + 2)->elementIndex = 0x52;
        TEAM_MANAGEMENT_RECORD(scene, port + 2)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, port + 2)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, port + 4)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, port + 4)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, port + 6)->frame = 0x000E0000;
        TEAM_MANAGEMENT_RECORD(scene, port + 6)->playMode = UI_PLAY_FORWARD;

        TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->playMode = UI_PLAY_FORWARD;

        TEAM_MANAGEMENT_RECORD(scene, port + 0x14)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, port + 0x14)->playMode = UI_PLAY_FORWARD;

        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port == 0) {
            TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->frame = 0x001E0000;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->playMode = UI_PLAY_STOP;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->playMode = UI_PLAY_FORWARD;
        }

        makeCursorUnmovable(port);
        gameSetUpStep[0x37 + port] = 1;
    }
}

void fn_8005F9D0(MenuScene* scene, s32 port) {
    s32 requiredCount;
    s32 completeCount;
    u8* steps = &gameSetUpStep[0x37];

    if (steps[port] != 1) {
        return;
    }

    completeCount = maybeCheckAndResetGrapicsElement(scene, port + 4, 0x14) != 0;
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port != 0) {
            completeCount += maybeCheckAndResetGrapicsElement(scene, port, 0x1E) != 0;
            completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0xA, 0xA) != 0;
            completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x12, 0x14) != 0;
            requiredCount = 5;
            completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0xA) != 0;
        } else {
            completeCount += maybeCheckAndResetGrapicsElement(scene, port, 0x14) != 0;
            completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0xA, 0xA) != 0;
            completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x12, 0xA) != 0;
            requiredCount = 5;
            completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0xA) != 0;
        }
    } else {
        completeCount += maybeCheckAndResetGrapicsElement(scene, port, 0x14) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0xA, 0xA) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, 0x12, 0xA) != 0;
        requiredCount = 5;
        completeCount += maybeCheckAndResetGrapicsElement(scene, 0x14, 0xA) != 0;
    }

    if (completeCount != requiredCount) {
        return;
    }

    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        u8* ready = (u8*)&aiPosSwapInputs + 0xCF5B;
        ready[port] = 1;
        if (ready[0] == 0 || ready[1] == 0) {
            return;
        }
        ready[0] = 0;
        ready[1] = 0;
        makeCursorMovable(0);
        makeCursorMovable(1);
        steps[0] = 2;
        steps[1] = 2;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            updateCharacterSelectProcessCode(0, 0x45);
        }
    } else {
        makeCursorMovable(port);
        steps[port] = 2;
    }
}

void fn_8005FCA0(MenuScene* scene, s32 port) {
    if (gameSetUpStep[0x37 + port] != 0) {
        return;
    }

    TEAM_MANAGEMENT_RECORD(scene, port + 4)->frame = 0;
    TEAM_MANAGEMENT_RECORD(scene, port + 4)->playMode = UI_PLAY_FORWARD;
    TEAM_MANAGEMENT_RECORD(scene, port + 6)->frame = 0x000E0000;
    TEAM_MANAGEMENT_RECORD(scene, port + 6)->playMode = UI_PLAY_FORWARD;
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port != 0) {
            TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, port + 2)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 2)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->frame = 0x001E0000;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x14)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x14)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->playMode = UI_PLAY_STOP;
            TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->playMode = UI_PLAY_FORWARD;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, port + 2)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 2)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, port + 2)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 2)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x14)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port + 0x14)->playMode = UI_PLAY_FORWARD;
        }
    } else {
        TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, port + 0xA)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, 0x12)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, 0x12)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, 0x14)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, 0x14)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, 2)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, 3)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
        if (((u8*)&aiPosSwapInputs)[0xCF70] == 0) {
            TEAM_MANAGEMENT_RECORD(scene, 0x1D2)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, 0x1D2)->frame = 0x000A0000;
            TEAM_MANAGEMENT_RECORD(scene, 0x1D2)->playMode = UI_PLAY_FORWARD;
        }
    }

    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = 1;
}

void teamManagementGraphics_steadyState(void) {
    MenuScene* scene = (MenuScene*)currentDrawingItem;
    s32 index;

    for (index = 0; index < 2; index++) {
        s32 port = gameSetUpStep[0x59 + index];
        s32 completeCount;
        s32 requiredCount;
        s32 selection;
        s32 previousSelection;
        u8 position;
        u8 swapPosition;
        s32 player;

        switch (gameSetUpStep[0x5D + index]) {
        case 0x38:
            if (g_d_GameSettings._06 != 2) {
                fn_8005FCA0(scene, port);
                fn_8005F9D0(scene, port);
            } else {
                if (gameSetUpStep[0x37 + port] == 0) {
                    TEAM_MANAGEMENT_RECORD(scene, 0)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                    if (((u8*)&aiPosSwapInputs)[0xCFA2 + port] != 1) {
                        TEAM_MANAGEMENT_RECORD(scene, 1)->frame = 0;
                        TEAM_MANAGEMENT_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
                    }
                    TEAM_MANAGEMENT_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, 0xE)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, 0xE)->playMode = UI_PLAY_FORWARD;
                    makeCursorUnmovable(port);
                    gameSetUpStep[0x37 + port] = 1;
                }
                if (gameSetUpStep[0x37 + port] == 1) {
                    requiredCount = 1;
                    completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0x14) != 0;
                    if (((u8*)&aiPosSwapInputs)[0xCFA2 + port] != 1) {
                        requiredCount = 2;
                        completeCount += maybeCheckAndResetGrapicsElement(scene, 1, 0x14) != 0;
                    }
                    if (completeCount == requiredCount) {
                        makeCursorMovable(port);
                        gameSetUpStep[0x37 + port] = 2;
                    }
                }
            }
            break;
        case 0x39:
            if (g_d_GameSettings._06 == 2) {
                break;
            }
            fn_8005F734(scene, port);
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0xA) != 0;
                if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port == 0) {
                    completeCount += maybeCheckAndResetGrapicsElement(scene, port, 0x1E) != 0;
                    completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x12, 0x14) != 0;
                } else {
                    completeCount += maybeCheckAndResetGrapicsElement(scene, port, 0x14) != 0;
                    completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x12, 0xA) != 0;
                }
                completeCount += maybeCheckAndResetGrapicsElement(scene, port + 4, 0x14) != 0;
                requiredCount = 5;
                completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0xA, 0xA) != 0;
                if (completeCount == requiredCount) {
                    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                        ((u8*)&aiPosSwapInputs)[0xCF5B + port] = 1;
                        if (((u8*)&aiPosSwapInputs)[0xCF5B] != 0 && ((u8*)&aiPosSwapInputs)[0xCF5C] != 0) {
                            ((u8*)&aiPosSwapInputs)[0xCF5C] = 0;
                            ((u8*)&aiPosSwapInputs)[0xCF5B] = 0;
                            makeCursorMovable(0);
                            makeCursorMovable(1);
                            gameSetUpStep[0x37] = 2;
                            gameSetUpStep[0x38] = 2;
                        }
                    } else {
                        makeCursorMovable(port);
                        gameSetUpStep[0x37 + port] = 2;
                    }
                }
            }
            break;
        case 0x3A:
            if (gameSetUpStep[0x37 + port] == 0) {
                if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port != 0) {
                        TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x001E0000;
                        TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
                    } else {
                        TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x00140000;
                        TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_BACKWARD;
                    }
                } else {
                    TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x00140000;
                    TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_BACKWARD;
                }
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port != 0) {
                        requiredCount = 1;
                        completeCount = maybeCheckAndResetGrapicsElement(scene, port, 0x32) != 0;
                    } else {
                        requiredCount = 1;
                        completeCount = maybeCheckAndResetGrapicsElement(scene, port, 0) != 0;
                    }
                } else {
                    requiredCount = 1;
                    completeCount = maybeCheckAndResetGrapicsElement(scene, port, 0) != 0;
                }
                if (completeCount == requiredCount) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x3B:
            fn_8005E9D8(scene, port);
            break;
        case 0x3C:
            if (g_d_GameSettings._06 == 2) {
                break;
            }
            fn_8005F068(scene, port);
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = 0;
                requiredCount = 0;
                switch (aiPosSwapInputs.rosterView[port]) {
                case ROSTER_VIEW_BATTING_ORDER:
                    if (((u8*)&aiPosSwapInputs)[0xCF54 + port] == 1) {
                        requiredCount = 1;
                        completeCount = maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0xA) != 0;
                    }
                    break;
                case ROSTER_VIEW_DEFENSIVE_ALIGNMENT:
                    if (((u8*)&aiPosSwapInputs)[0xCF54 + port] != 1) {
                        requiredCount = 1;
                        completeCount = maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0x14) != 0;
                    }
                    break;
                }
                if (completeCount == requiredCount) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x3D:
            if (g_d_GameSettings._06 != 2) {
                fn_8005EC88(scene, port);
                if (gameSetUpStep[0x37 + port] == 1) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            } else {
                fn_8005B760(scene, port);
                if (gameSetUpStep[0x37 + port] == 1) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x3E:
            if (g_d_GameSettings._06 != 2) {
                if (gameSetUpStep[0x37 + port] == 0) {
                    if ((s8)aiPosSwapInputs.teamManagement_cursorPos[port] == 0) {
                        previousSelection = (s8)(aiPosSwapInputs.teamManagement_prevCursorPos[port] - 1);
                        position = lineUpInfoStruct[port][previousSelection][2];
                        switch (aiPosSwapInputs.rosterView[port]) {
                        case ROSTER_VIEW_BATTING_ORDER:
                            TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x40)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x1C)->frame = 0x000A0000;
                            TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x1C)->playMode = UI_PLAY_BACKWARD;
                            for (player = 0; player < 9; player++) {
                                TEAM_MANAGEMENT_RECORD(scene, player + port * 9 + 0x64)->flags &= ~UI_FLAG_VISIBLE;
                            }
                            break;
                        case ROSTER_VIEW_DEFENSIVE_ALIGNMENT:
                            TEAM_MANAGEMENT_RECORD(scene, (s8)position + port * 9 + 0x10A)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, (s8)position + port * 9 + 0xF8)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, (s8)position + port * 9 + 0xE6)->flags &= ~UI_FLAG_VISIBLE;
                            for (player = 0; player < 9; player++) {
                                TEAM_MANAGEMENT_RECORD(scene, player + port * 9 + 0x12E)->flags &= ~UI_FLAG_VISIBLE;
                            }
                            break;
                        }
                    }
                    TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->playMode = UI_PLAY_FORWARD;
                    makeCursorUnmovable(port);
                    gameSetUpStep[0x37 + port] = 1;
                }
                if (gameSetUpStep[0x37 + port] == 1) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            } else {
                if (gameSetUpStep[0x37 + port] == 0) {
                    switch (aiPosSwapInputs.rosterView[port]) {
                    case ROSTER_VIEW_BATTING_ORDER:
                        previousSelection = (s8)(aiPosSwapInputs.teamManagement_prevCursorPos[port] - 1);
                        TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x63)->playMode = UI_PLAY_BACKWARD;
                        TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x51)->frame = 0x000A0000;
                        TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x51)->playMode = UI_PLAY_BACKWARD;
                        for (player = 0; player < 9; player++) {
                            TEAM_MANAGEMENT_RECORD(scene, player + 0x75)->flags &= ~UI_FLAG_VISIBLE;
                            TEAM_MANAGEMENT_RECORD(scene, player + 0x35)->flags &= ~UI_FLAG_VISIBLE;
                        }
                        break;
                    case ROSTER_VIEW_DEFENSIVE_ALIGNMENT:
                        previousSelection = (s8)(aiPosSwapInputs.teamManagement_prevCursorPos[port] - 1);
                        position = lineUpInfoStruct[port][previousSelection][2];
                        TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x23)->playMode = UI_PLAY_BACKWARD;
                        TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x1A)->playMode = UI_PLAY_BACKWARD;
                        TEAM_MANAGEMENT_RECORD(scene, (s8)position + 0x11)->flags &= ~UI_FLAG_VISIBLE;
                        for (player = 0; player < 9; player++) {
                            TEAM_MANAGEMENT_RECORD(scene, player + 0x35)->flags &= ~UI_FLAG_VISIBLE;
                            TEAM_MANAGEMENT_RECORD(scene, player + 0x75)->flags &= ~UI_FLAG_VISIBLE;
                        }
                        break;
                    }
                    TEAM_MANAGEMENT_RECORD(scene, 0xE)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, 0xE)->playMode = UI_PLAY_FORWARD;
                    makeCursorUnmovable(port);
                    gameSetUpStep[0x37 + port] = 1;
                }
                if (gameSetUpStep[0x37 + port] == 1) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x3F:
            if (g_d_GameSettings._06 == 2) {
                break;
            }
            if (gameSetUpStep[0x37 + port] == 0) {
                TEAM_MANAGEMENT_RECORD(scene, 0)->frame = 0x00140000;
                TEAM_MANAGEMENT_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, 1)->frame = 0x001E0000;
                TEAM_MANAGEMENT_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, 0x18)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD(scene, 0x18)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, 0x19)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, 0x19)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, 0x12)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD(scene, 0x12)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, 0x13)->frame = 0x00140000;
                TEAM_MANAGEMENT_RECORD(scene, 0x13)->playMode = UI_PLAY_BACKWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0x1E) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 1, 0x14) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x12, 0x14) != 0;
                requiredCount = 4;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x13, 0xA) != 0;
                if (completeCount == requiredCount) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x40:
            if (g_d_GameSettings._06 == 2) {
                break;
            }
            if (gameSetUpStep[0x37 + port] == 0) {
                TEAM_MANAGEMENT_RECORD(scene, 0)->frame = 0x001E0000;
                TEAM_MANAGEMENT_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, 1)->frame = 0x00140000;
                TEAM_MANAGEMENT_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, 0x18)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, 0x18)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, 0x19)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD(scene, 0x19)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, 0x12)->frame = 0x00140000;
                TEAM_MANAGEMENT_RECORD(scene, 0x12)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, 0x13)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD(scene, 0x13)->playMode = UI_PLAY_FORWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0x14) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 1, 0x1E) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x12, 0xA) != 0;
                requiredCount = 4;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x13, 0x14) != 0;
                if (completeCount == requiredCount) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x41:
            if (gameSetUpStep[0x37 + port] == 0) {
                TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x00140000;
                TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->playMode = UI_PLAY_FORWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = fn_80042D68(scene, port, 0x1E) != 0;
                requiredCount = 2;
                completeCount += fn_80042D68(scene, port + 0x12, 0x14) != 0;
                if (completeCount == requiredCount) {
                    ((u8*)&aiPosSwapInputs)[0xCF50 + port] = 0;
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x42:
            if (gameSetUpStep[0x37 + port] == 0) {
                TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x001E0000;
                TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->frame = 0;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x18)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->frame = 0x00140000;
                TEAM_MANAGEMENT_RECORD(scene, port + 0x12)->playMode = UI_PLAY_BACKWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = maybeCheckAndResetGrapicsElement(scene, port, 0x14) != 0;
                requiredCount = 2;
                completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x12, 0xA) != 0;
                if (completeCount == requiredCount) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x43:
            fn_8005C5C4(scene, port);
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = 0;
                requiredCount = 0;
                if (g_d_GameSettings._06 != 2) {
                    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                        requiredCount = 2;
                        completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0) != 0;
                        completeCount += maybeCheckAndResetGrapicsElement(scene, 1, 0) != 0;
                    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                        if (port != 0) {
                            requiredCount = 1;
                            completeCount = maybeCheckAndResetGrapicsElement(scene, port, 0) != 0;
                        } else {
                            requiredCount = 1;
                            completeCount = maybeCheckAndResetGrapicsElement(scene, port, 0x32) != 0;
                        }
                    } else if (((u32)TEAM_MANAGEMENT_RECORD(scene, port)->frame >> 16) >= 0x1E) {
                        requiredCount = 1;
                        completeCount = maybeCheckAndResetGrapicsElement(scene, port, 0x32) != 0;
                    } else {
                        requiredCount = 1;
                        completeCount = maybeCheckAndResetGrapicsElement(scene, port, 0) != 0;
                    }
                }
                if (completeCount == requiredCount) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x44:
            if (gameSetUpStep[0x37 + port] == 0) {
                selection = (s8)(aiPosSwapInputs.teamManagement_cursorPos[port] - 1);
                previousSelection = (s8)aiPosSwapInputs.charSelectedToBeSwappedCharID[port];
                if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
                    if (previousSelection != CHAR_ID_NONE && previousSelection != selection) {
                        TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x1C)->frame = 0x000A0000;
                        TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x1C)->playMode = UI_PLAY_BACKWARD;
                        TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x40)->frame = 0x000A0000;
                        TEAM_MANAGEMENT_RECORD(scene, previousSelection + port * 9 + 0x40)->playMode = UI_PLAY_BACKWARD;
                    }
                } else {
                    position = lineUpInfoStruct[port][selection][2];
                    swapPosition = lineUpInfoStruct[port][previousSelection][2];
                    if (g_d_GameSettings._06 != 2) {
                        if (previousSelection != CHAR_ID_NONE && (s8)swapPosition != (s8)position) {
                            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + port * 9 + 0x10A)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + port * 9 + 0xF8)->playMode = UI_PLAY_BACKWARD;
                        }
                    } else {
                        if (previousSelection != CHAR_ID_NONE && (s8)swapPosition != (s8)position) {
                            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + 0x23)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, (s8)swapPosition + 0x1A)->playMode = UI_PLAY_BACKWARD;
                        }
                    }
                }
                aiPosSwapInputs.charSelectedToBeSwappedCharID[port] = (u8)CHAR_ID_NONE;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                makeCursorMovable(port);
                gameSetUpStep[0x37 + port] = 2;
            }
            break;
        case 0x45:
            if (gameSetUpStep[0x37] == 0) {
                BOOL playedFlag = FALSE;
                for (player = 0; player < 9; player++) {
                    s32 flags = (s8)g_Challenge.characters[inMemRoster[1][player].stats.CharID].scoutFlagsAchieved;
                    s32 flag;
                    for (flag = 0; flag < flags; flag++) {
                        TEAM_MANAGEMENT_RECORD(scene, flag + player * 5 + 0x16D)->playMode = UI_PLAY_FORWARD;
                        playedFlag = TRUE;
                    }
                }
                if ((u8)playedFlag != 0) {
                    if (g_d_GameSettings._06 == 2) {
                        sndFXStartEx(0x1B1, 0x7F, 0x3F, 0);
                    } else {
                        sndFXStartEx(0x1E6, 0x7F, 0x3F, 0);
                    }
                }
                makeCursorUnmovable(0);
                gameSetUpStep[0x37] = 1;
            }
            if (gameSetUpStep[0x37] == 1) {
                makeCursorMovable(0);
                gameSetUpStep[0x37] = 2;
            }
            break;
        case 0x46:
            TEAM_MANAGEMENT_RECORD(scene, 0x1D2)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, 0x1D2)->playMode = UI_PLAY_FORWARD;
            gameSetUpStep[0x5D] = 0;
            break;
        }
        battingOrderProcessInputs(scene, port);
    }
    if (((u8*)&aiPosSwapInputs)[0xCF45] != 0) {
        ((u8*)&aiPosSwapInputs)[0xCF45] = 0;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}
