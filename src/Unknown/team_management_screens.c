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

    memset(selected, -1, 2);
    count = 0;
    for (i = 0; i < 14; i++) {
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
        selected[0] = 12;
    }
    if (selected[1] < 0) {
        selected[1] = 12;
    }

    if (g_d_GameSettings._06 == 2) {
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 0x125].object)->frame = selected[0] << 16;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 0x126].object)->frame = selected[1] << 16;
    } else {
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x1B4].object)->frame = selected[0] << 16;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x1B6].object)->frame = selected[1] << 16;
    }
}

void fn_800596D4(MenuScene* scene) {
    u8* input = (u8*)&aiPosSwapInputs;
    s32 tracker = aiPosSwapInputs.playerIndexNoVariants;
    s32 mission = aiPosSwapInputs.starMenuCursorPos;
    s32 previousMission = aiPosSwapInputs.starMenuPrevCursorPos;
    s32 frameBase = g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD;
    UIRecord* record;

    if (input[0xCF73] == 0) {
        if (challengeStarRelatedInd(tracker, mission)) {
            record = TEAM_MANAGEMENT_RECORD(scene, 0x1D9);
            record->flags |= UI_FLAG_VISIBLE;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, mission + 0x1E7);
            record->flags |= UI_FLAG_VISIBLE;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, mission + frameBase)->frame = 0x00010000;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, mission + 0x1E7)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, mission + frameBase)->frame = 0;
        }
        record = TEAM_MANAGEMENT_RECORD(scene, mission + 0x1FB);
        record->flags |= UI_FLAG_VISIBLE;
        record->playMode = UI_PLAY_FORWARD;
        if (challengeStarRelatedInd(tracker, previousMission)) {
            TEAM_MANAGEMENT_RECORD(scene, previousMission + 0x1E7)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, previousMission + frameBase)->frame = 0;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, previousMission + frameBase)->frame = 0;
        }
        record = TEAM_MANAGEMENT_RECORD(scene, previousMission + 0x1FB);
        record->flags &= ~UI_FLAG_VISIBLE;
        record->playMode = UI_PLAY_FORWARD;
        {
            StarMissionDisplayRule* rule = &starMissionDisplayRules[characterStaticIndexes[tracker].requirementRow][mission];
            s32 textID;
            if ((s8)g_Challenge.characters[tracker].inGameMissionTracker[mission].shownOnPauseMenu != 0) {
                textID = rule->textID;
            } else if (rule->minScoutRow <= g_Challenge.difficulty) {
                textID = 0x1C5;
            } else {
                textID = 0x1C6;
            }
            text_setPtrToWhereCharsAreStored(input[0xCF7C], 0, textID);
        }
        input[0xCF73] = 1;
    }
    if (input[0xCF73] != 0) {
        input[0xCF74] = 0;
        input[0xCF73] = 0;
    }
}

void starMissionRelated1(MenuScene* scene) {
    u8* input = (u8*)&aiPosSwapInputs;
    s32 character = *(s16*)(input + 0xCF78);
    s32 tracker;
    s32 requirementRow;
    s32 rank;
    s32 missionCount;
    s32 layoutOffset = g_d_GameSettings._06 == 2 ? -0x69 : 0;
    s32 mission;
    s32 textID;
    UIRecord* record;

    if (input[0xCF73] == 0) {
        tracker = characterStaticIndexes[character].trackerIdx;
        aiPosSwapInputs.playerIndexNoVariants = tracker;
        requirementRow = characterStaticIndexes[character].requirementRow;
        rank = g_Challenge.characters[tracker].variantClassification;
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
        record = TEAM_MANAGEMENT_RECORD(scene, 0x1D7 + layoutOffset);
        record->flags |= UI_FLAG_VISIBLE;
        record->playMode = UI_PLAY_FORWARD;
        record = TEAM_MANAGEMENT_RECORD(scene, 0x1D3 + layoutOffset);
        record->flags |= UI_FLAG_VISIBLE;
        record->playMode = UI_PLAY_FORWARD;
        record = TEAM_MANAGEMENT_RECORD(scene, 0x1D4 + layoutOffset);
        record->flags |= UI_FLAG_VISIBLE;
        record->frame = rank << 16;
        record = TEAM_MANAGEMENT_RECORD(scene, 0x1D5 + layoutOffset);
        record->flags |= UI_FLAG_VISIBLE;
        record->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, 0x1D6 + layoutOffset)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, 0x1DA + layoutOffset)->frame =
            Static_Stats_Tables.characterStats[character / 9][character % 9].stats.CharacterClass << 16;
        TEAM_MANAGEMENT_RECORD(scene, 0x1DB + layoutOffset)->frame = character << 16;
        input[0xCF7A] = text_initializeNewChannel((UnkText988Arg*)scene,
            g_d_GameSettings._06 == 2 ? 0x19B : 0x205, 0, 0, tracker + 8, 0);
        rank = determineIfMissionDescriptionIsShown(tracker);
        input[0xCF7B] = text_initializeNewChannel((UnkText988Arg*)scene,
            g_d_GameSettings._06 == 2 ? 0x19C : 0x206, 1, 0,
            (s16)starRankTextIDs[requirementRow] + rank, 0);
        rank = determineIfMissionDescriptionIsShown(tracker);
        TEAM_MANAGEMENT_RECORD(scene, 0x1DC)->frame = (4 - rank) << 16;
        mission = aiPosSwapInputs.starMenuCursorPos;
        if ((s8)g_Challenge.characters[tracker].inGameMissionTracker[mission].shownOnPauseMenu != 0) {
            textID = starMissionDisplayRules[requirementRow][mission].textID;
        } else if (starMissionDisplayRules[requirementRow][mission].minScoutRow <= g_Challenge.difficulty) {
            textID = 0x1C5;
        } else {
            textID = 0x1C6;
        }
        input[0xCF7C] = text_initializeNewChannel((UnkText988Arg*)scene,
            g_d_GameSettings._06 == 2 ? 0x19D : 0x207, 0, 0, textID, 0);
        screenTextArray.blocks[input[0xCF7C]].justify = 1;
        for (mission = 0; mission < missionCount; mission++) {
            record = TEAM_MANAGEMENT_RECORD(scene, mission + 0x1F1);
            if (challengeStarRelatedInd(tracker, mission)) {
                record->flags |= UI_FLAG_VISIBLE;
                record->playMode = UI_PLAY_FORWARD;
            } else {
                record->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD(scene, mission + 0x1FB)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, mission + 0x1E7)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, mission + (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD))->frame = 0;
        }
        mission = aiPosSwapInputs.starMenuCursorPos;
        if (challengeStarRelatedInd(tracker, mission)) {
            record = TEAM_MANAGEMENT_RECORD(scene, 0x1D9);
            record->flags |= UI_FLAG_VISIBLE;
            record->playMode = UI_PLAY_FORWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, mission + 0x1E7);
            record->flags |= UI_FLAG_VISIBLE;
            record->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, mission + (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD))->frame = 0x00010000;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, mission + 0x1E7)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, mission + (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD))->frame = 0;
        }
        record = TEAM_MANAGEMENT_RECORD(scene, mission + 0x1FB);
        record->flags |= UI_FLAG_VISIBLE;
        record->playMode = UI_PLAY_FORWARD;
        input[0xCF73] = 1;
    }
    if (input[0xCF73] != 0) {
        input[0xCF74] = 0;
        input[0xCF73] = 0;
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
    s32 team = ((s8*)&aiPosSwapInputs)[0xCF3B];
    s32 player;

    for (player = 0; player < 9; player++) {
        CharacterStats* stats = &inMemRoster[team][player];
        s32 position = lineUpInfoStruct[team][player][2];
        s32 handle = scene->firstHandle + player;
        UIRecord* record;
        BOOL isSuperstar;

        if (((u8*)&aiPosSwapInputs)[0xCFA2 + team] == 2) {
            continue;
        }

        load_Icon(scene, position + 0x23, 1, 0x83, stats->stats.CharID);
        record = (UIRecord*)graphicsRelatedArray[handle + 0x11].object;
        record->flags &= ~UI_FLAG_VISIBLE;

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
        } else {
            isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
        }

        if (isSuperstar && !(team == 1 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + position + 0x3E].object;
            record->playMode = UI_PLAY_FORWARD;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + position + 0x47].object;
            record->flags |= UI_FLAG_VISIBLE;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
        } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                   g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + position + 0x3E].object;
            record->playMode = UI_PLAY_FORWARD;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + position + 0x47].object;
            record->flags |= UI_FLAG_VISIBLE;
            record->frame = 0;
            record->playMode = UI_PLAY_STOP;
        } else {
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + position + 0x3E].object;
            record->flags &= ~UI_FLAG_VISIBLE;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + position + 0x47].object;
            record->flags &= ~UI_FLAG_VISIBLE;
        }

        record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0x35].object;
        record->flags &= ~UI_FLAG_VISIBLE;
        record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0x1A].object;
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && team != 0) {
            record->elementIndex = 0x1E + (Static_Stats_Tables.playerNumberByPort[0] == 0);
        } else {
            record->elementIndex = 0x1E + Static_Stats_Tables.playerNumberByPort[team];
        }
    }
}

void teamManagementGraphics_battingOrderScreen(MenuScene* scene) {
    s32 team = ((s8*)&aiPosSwapInputs)[0xCF3B];
    s32 player;

    for (player = 0; player < 9; player++) {
        CharacterStats* stats = &inMemRoster[team][player];
        s32 handle = scene->firstHandle + player;
        UIRecord* record;
        BOOL isSuperstar;

        record = (UIRecord*)graphicsRelatedArray[handle + 0x5A].object;
        record->frame = player << 16;
        record = (UIRecord*)graphicsRelatedArray[handle + 0x6C].object;
        record->flags &= ~UI_FLAG_VISIBLE;

        if (((u8*)&aiPosSwapInputs)[0xCFA2 + team] == 0) {
            load_Icon(scene, player + 0x63, 1, 0x83, stats->stats.CharID);
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0xAB].object;
            record->frame = stats->stats.CharacterClass << 16;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0x99].object;
            record->frame = (stats->stats.BattingStance + stats->stats.FieldingArm * 2) << 16;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0x134].object;
            record->flags &= ~UI_FLAG_VISIBLE;
        } else {
            ChallengeTrackingStruct* tracking = &g_Challenge.characters[inMemRoster[1][player].stats.CharID];
            s32 requiredFlags = tracking->scoutFlagPointer->flagsRequired[g_Challenge.difficulty][g_Challenge.captain];
            s32 remainingFlags = requiredFlags - (s8)tracking->scoutFlagsAchieved;
            s32 flag;
            load_Icon(scene, player + 0x63, 1, 0x83, inMemRoster[1][player].stats.CharID);
            for (flag = 0; flag < 5; flag++) {
                record = TEAM_MANAGEMENT_RECORD(scene, flag + player * 5 + 0x13D);
                if (flag < requiredFlags && flag < remainingFlags) {
                    record->frame = 0;
                } else if (flag < requiredFlags) {
                    record->playMode = UI_PLAY_FORWARD;
                    sndFXStartEx(g_d_GameSettings._06 == 2 ? 0x1B1 : 0x1E6, 0x7F, 0x3F, 0);
                } else if (flag >= requiredFlags) {
                    record->flags &= ~UI_FLAG_VISIBLE;
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

        if (isSuperstar && !(team == 1 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
            record = (UIRecord*)graphicsRelatedArray[handle + 0x7E].object;
            record->playMode = UI_PLAY_FORWARD;
            record = (UIRecord*)graphicsRelatedArray[handle + 0x87].object;
            record->flags |= UI_FLAG_VISIBLE;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
        } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                   g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            record = (UIRecord*)graphicsRelatedArray[handle + 0x7E].object;
            record->playMode = UI_PLAY_FORWARD;
            record = (UIRecord*)graphicsRelatedArray[handle + 0x87].object;
            record->flags |= UI_FLAG_VISIBLE;
            record->frame = 0;
            record->playMode = UI_PLAY_STOP;
        } else {
            record = (UIRecord*)graphicsRelatedArray[handle + 0x7E].object;
            record->flags &= ~UI_FLAG_VISIBLE;
            record = (UIRecord*)graphicsRelatedArray[handle + 0x87].object;
            record->flags &= ~UI_FLAG_VISIBLE;
        }

        record = (UIRecord*)graphicsRelatedArray[handle + 0x75].object;
        record->flags &= ~UI_FLAG_VISIBLE;
    }
}

void fn_8005B760(MenuScene* scene, s32 port) {
    if (gameSetUpStep[0x37 + port] == 0) {
        s32 selection = ((s8*)&aiPosSwapInputs)[0xCF46 + port];

        if (selection != 0) {
            s32 index = selection - 1;
            s32 lineupPosition = lineUpInfoStruct[port][index][2];
            s32 i;
            UIRecord* record;

            for (i = 0; i < 9; i += 3) {
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + 0x75].object;
                record->flags &= ~UI_FLAG_VISIBLE;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + 0x35].object;
                record->flags &= ~UI_FLAG_VISIBLE;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + 0x76].object;
                record->flags &= ~UI_FLAG_VISIBLE;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + 0x36].object;
                record->flags &= ~UI_FLAG_VISIBLE;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + 0x77].object;
                record->flags &= ~UI_FLAG_VISIBLE;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + 0x37].object;
                record->flags &= ~UI_FLAG_VISIBLE;
            }

            if (((u8*)&aiPosSwapInputs)[0xCFA2 + port] == 0) {
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + lineupPosition + 0x23].object;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + lineupPosition + 0x1A].object;
                record->playMode = UI_PLAY_FORWARD;
            } else {
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + index + 0x63].object;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + index + 0x51].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + index + 0x6C].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
            }

            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + index + 0x6C].object;
            record->flags |= UI_FLAG_VISIBLE;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + index + 0x75].object;
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            record->playMode = UI_PLAY_FORWARD;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + lineupPosition + 0x35].object;
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            record->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, index);
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + 0xE].object;
            record->frame = 0;
            record->playMode = UI_PLAY_STOP;
        }

        makeCursorUnmovable(port);
        gameSetUpStep[0x37 + port] = 1;
    }
}

void challengeTeamManagementRelated(MenuScene* scene) {
    s32 team;
    s32 player;

    for (team = 0; team < 2; team++) {
        for (player = 0; player < 9; player++) {
            CharacterStats* stats = &inMemRoster[team][player];
            s32 handle = scene->firstHandle + player + team * 9;
            UIRecord* record;

            load_Icon(scene, player + team * 9 + 0x40, 1, 0x83, stats->stats.CharID);
            ((UIRecord*)graphicsRelatedArray[handle + 0x2E].object)->frame = player << 16;
            if (team == 0) {
                BOOL isSuperstar;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0xD0].object)->frame = inMemRoster[0][player].stats.CharacterClass << 16;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0xAC].object)->frame =
                    (inMemRoster[0][player].stats.FieldingArm * 2 + inMemRoster[0][player].stats.BattingStance) << 16;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0x64].object)->flags &= ~UI_FLAG_VISIBLE;
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                    isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
                } else {
                    isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
                }
                if ((u8)isSuperstar != 0 && team == 0) {
                    ((UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0x76].object)->playMode = UI_PLAY_FORWARD;
                    record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0x88].object;
                    record->flags |= UI_FLAG_VISIBLE;
                    record->frame = 0;
                    record->playMode = UI_PLAY_FORWARD;
                } else {
                    ((UIRecord*)graphicsRelatedArray[scene->firstHandle + player + 0x88].object)->flags &= ~UI_FLAG_VISIBLE;
                }
            } else {
                s32 requiredFlags;
                s32 flag;
                ((UIRecord*)graphicsRelatedArray[handle + 0xD0].object)->flags &= ~UI_FLAG_VISIBLE;
                ((UIRecord*)graphicsRelatedArray[handle + 0xAC].object)->flags &= ~UI_FLAG_VISIBLE;
                ((UIRecord*)graphicsRelatedArray[handle + 0x88].object)->flags &= ~UI_FLAG_VISIBLE;
                ((UIRecord*)graphicsRelatedArray[handle + 0x64].object)->flags &= ~UI_FLAG_VISIBLE;
                requiredFlags = g_Challenge.characters[inMemRoster[1][player].stats.CharID].scoutFlagPointer->flagsRequired[g_Challenge.difficulty][g_Challenge.captain];
                for (flag = 0; flag < 5; flag++) {
                    record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + flag + player * 5 + 0x16D].object;
                    if (flag < requiredFlags) {
                        record->frame = 0;
                        record->playMode = UI_PLAY_STOP;
                    } else if (flag >= requiredFlags) {
                        record->flags &= ~UI_FLAG_VISIBLE;
                    }
                }
            }
        }
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + team + 8].object)->frame = Static_Stats_Tables.teamName[team] << 16;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + team + 0xC].object)->frame = Static_Stats_Tables.teamName[team] << 16;
    }
}

void teamManagementGraphics_fieldingAlignmentInfo(MenuScene* scene) {
    s32 team;
    s32 player;

    for (team = 0; team < 2; team++) {
        for (player = 0; player < 9; player++) {
            CharacterStats* stats = &inMemRoster[team][player];
            s32 position = lineUpInfoStruct[team][player][2];
            s32 handle = scene->firstHandle + team * 9 + position;
            UIRecord* record;
            BOOL isSuperstar;

            load_Icon(scene, position + team * 9 + 0x10A, 1, 0x83, stats->stats.CharID);
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + team * 9 + player + 0xE6].object;
            record->flags &= ~UI_FLAG_VISIBLE;

            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
            } else {
                isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
            }

            if (isSuperstar || superstarUnlocked[stats->stats.CharID] != 0) {
                record = (UIRecord*)graphicsRelatedArray[handle + 0x140].object;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[handle + 0x152].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->frame = 0;
                record->playMode = isSuperstar ? UI_PLAY_FORWARD : UI_PLAY_STOP;
            } else {
                record = (UIRecord*)graphicsRelatedArray[handle + 0x152].object;
                record->flags &= ~UI_FLAG_VISIBLE;
            }

            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + team * 9 + player + 0x12E].object;
            record->flags &= ~UI_FLAG_VISIBLE;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + team * 9 + player + 0xF8].object;
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && team != 0) {
                record->elementIndex = 0x1E + (Static_Stats_Tables.playerNumberByPort[0] == 0);
            } else {
                record->elementIndex = 0x1E + Static_Stats_Tables.playerNumberByPort[team];
            }
        }
    }
}

void teamManagementGraphics_battingOrderInfo(MenuScene* scene) {
    s32 team;
    s32 player;
    s32 teamHandle;

    for (team = 0; team < 2; team++) {
        for (player = 0; player < 9; player++) {
            CharacterStats* stats = &inMemRoster[team][player];
            UIRecord* record;
            BOOL isSuperstar;

            load_Icon(scene, player + team * 9 + 0x40, 1, 0x83, stats->stats.CharID);
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + team * 9 + 0x2E].object;
            record->frame = player << 16;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + team * 9 + 0xD0].object;
            record->frame = stats->stats.CharacterClass << 16;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + team * 9 + 0xAC].object;
            record->frame = (stats->stats.BattingStance + stats->stats.FieldingArm * 2) << 16;

            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
            } else {
                isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
            }

            if (isSuperstar) {
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + team * 9 + 0x76].object;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + team * 9 + 0x88].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
            } else if (superstarUnlocked[stats->stats.CharID] != 0) {
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + team * 9 + 0x76].object;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + team * 9 + 0x88].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->frame = 0;
                record->playMode = UI_PLAY_STOP;
            } else {
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + team * 9 + 0x88].object;
                record->flags &= ~UI_FLAG_VISIBLE;
            }

            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + player + team * 9 + 0x64].object;
            record->flags &= ~UI_FLAG_VISIBLE;
        }

        teamHandle = scene->firstHandle + team;
        ((UIRecord*)graphicsRelatedArray[teamHandle + 8].object)->frame =
            Static_Stats_Tables.teamName[team] << 16;
        ((UIRecord*)graphicsRelatedArray[teamHandle + 0xC].object)->frame =
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
        if ((((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->frame >> 16) == 0x1E) {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->frame = 0x001E0000;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->playMode = UI_PLAY_FORWARD;
        } else {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->frame = 0x00140000;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->playMode = UI_PLAY_BACKWARD;
        }
    }

    ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x16].object)->frame = 0x000A0000;
    ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x16].object)->playMode = UI_PLAY_BACKWARD;
    ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x18].object)->frame = 0x00140000;
    ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x18].object)->playMode = UI_PLAY_BACKWARD;
    ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x12].object)->frame = 0x00140000;
    ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x12].object)->playMode = UI_PLAY_FORWARD;
    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = 1;
}

void fn_8005C830(MenuScene* scene, s32 port, s32 selection) {
    s32 chemistryIndex;
    s32 teamHandle = port * 9;
    s32 mode = ((u8*)&aiPosSwapInputs)[0xCF52 + port];

    for (chemistryIndex = 0; chemistryIndex < 9; chemistryIndex++) {
        s32 characterID = Static_Stats_Tables.highChemTeammates[port][selection][chemistryIndex];
        s32 rosterIndex;

        for (rosterIndex = 0; rosterIndex < 9; rosterIndex++) {
            CharacterStats* stats = &inMemRoster[port][rosterIndex];
            s32 position;
            s32 handle;
            UIRecord* record;

            if (stats->stats.CharID != characterID) {
                continue;
            }

            position = lineUpInfoStruct[port][rosterIndex][2];
            if (mode == 0 && g_d_GameSettings._06 != 2) {
                handle = scene->firstHandle + teamHandle + rosterIndex;
                record = (UIRecord*)graphicsRelatedArray[handle + 0x52].object;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[handle + 0x64].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->elementIndex = 0x2B;
                record->playMode = UI_PLAY_FORWARD;
            } else if (mode == 0) {
                handle = scene->firstHandle + position;
                record = (UIRecord*)graphicsRelatedArray[handle + 0x35].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->elementIndex = 0x2B;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + rosterIndex + 0x6C].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + rosterIndex + 0x75].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->elementIndex = 0x2B;
                record->playMode = UI_PLAY_FORWARD;
            } else if (g_d_GameSettings._06 != 2) {
                handle = scene->firstHandle + teamHandle + position;
                record = (UIRecord*)graphicsRelatedArray[handle + 0x12E].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->elementIndex = 0x2B;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
            } else {
                handle = scene->firstHandle + position;
                record = (UIRecord*)graphicsRelatedArray[handle + 0x35].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->elementIndex = 0x2B;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + rosterIndex + 0x6C].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + rosterIndex + 0x75].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->elementIndex = 0x2B;
                record->playMode = UI_PLAY_FORWARD;
            }
        }
    }
}

void fn_8005CCE4(MenuScene* scene, s32 port) {
    s32 selection;
    s32 swapSelection;
    s32 position;
    s32 swapPosition;
    s32 teamOffset = port * 9;
    s32 player;
    UIRecord* record;

    if (gameSetUpStep[0x37 + port] != 0) {
        return;
    }
    selection = aiPosSwapInputs.teamManagement_cursorPos[port] - 1;
    swapSelection = aiPosSwapInputs.charSelectedToBeSwappedCharID[port];
    position = lineUpInfoStruct[port][selection][2];
    swapPosition = lineUpInfoStruct[port][swapSelection][2];

    if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
        if (selection != swapSelection) {
            record = TEAM_MANAGEMENT_RECORD(scene, swapSelection + teamOffset + 0x1C);
            record->frame = 0x000A0000;
            record->playMode = UI_PLAY_BACKWARD;
        }
        TEAM_MANAGEMENT_RECORD(scene, swapSelection + teamOffset + 0x40)->playMode = UI_PLAY_BACKWARD;
        load_Icon(scene, selection + teamOffset + 0x40, 1, 0x83, inMemRoster[port][selection].stats.CharID);
        load_Icon(scene, swapSelection + teamOffset + 0x40, 1, 0x83, inMemRoster[port][swapSelection].stats.CharID);
        TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0xD0)->frame = inMemRoster[port][selection].stats.CharacterClass << 16;
        TEAM_MANAGEMENT_RECORD(scene, swapSelection + teamOffset + 0xD0)->frame = inMemRoster[port][swapSelection].stats.CharacterClass << 16;
        TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0xAC)->frame =
            (inMemRoster[port][selection].stats.FieldingArm * 2 + inMemRoster[port][selection].stats.BattingStance) << 16;
        TEAM_MANAGEMENT_RECORD(scene, swapSelection + teamOffset + 0xAC)->frame =
            (inMemRoster[port][swapSelection].stats.FieldingArm * 2 + inMemRoster[port][swapSelection].stats.BattingStance) << 16;
    } else if (g_d_GameSettings._06 != 2) {
        load_Icon(scene, swapPosition + teamOffset + 0x10A, 1, 0x83, inMemRoster[port][swapSelection].stats.CharID);
        load_Icon(scene, position + teamOffset + 0x10A, 1, 0x83, inMemRoster[port][selection].stats.CharID);
        TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x10A)->playMode = UI_PLAY_BACKWARD;
        TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0xF8)->playMode = UI_PLAY_BACKWARD;
        TEAM_MANAGEMENT_RECORD(scene, swapPosition + teamOffset + 0x10A)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, swapPosition + teamOffset + 0xF8)->playMode = UI_PLAY_FORWARD;
    } else {
        load_Icon(scene, swapPosition + 0x23, 1, 0x83, inMemRoster[port][swapSelection].stats.CharID);
        load_Icon(scene, position + 0x23, 1, 0x83, inMemRoster[port][selection].stats.CharID);
        TEAM_MANAGEMENT_RECORD(scene, position + 0x23)->playMode = UI_PLAY_BACKWARD;
        TEAM_MANAGEMENT_RECORD(scene, position + 0x1A)->playMode = UI_PLAY_BACKWARD;
        TEAM_MANAGEMENT_RECORD(scene, swapPosition + 0x23)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, swapPosition + 0x1A)->playMode = UI_PLAY_FORWARD;
    }

    for (player = 0; player < 9; player++) {
        CharacterStats* stats = &inMemRoster[port][player];
        BOOL isSuperstar;
        BOOL showSuperstar;
        s32 iconHandle;
        s32 starHandle;
        s32 lineupPosition = lineUpInfoStruct[port][player][2];

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
        } else {
            isSuperstar = ((u8*)&Static_Stats_Tables)[0x489B + teamOffset + player];
        }
        showSuperstar = (u8)isSuperstar != 0;
        if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
            iconHandle = player + (g_d_GameSettings._06 == 2 ? 0x7E : teamOffset + 0x76);
            starHandle = player + (g_d_GameSettings._06 == 2 ? 0x87 : teamOffset + 0x88);
        } else {
            iconHandle = lineupPosition + (g_d_GameSettings._06 == 2 ? 0x3E : teamOffset + 0x140);
            starHandle = lineupPosition + (g_d_GameSettings._06 == 2 ? 0x47 : teamOffset + 0x152);
            if (g_d_GameSettings._06 == 2 && port == 1 &&
                g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                showSuperstar = FALSE;
            }
        }
        if (showSuperstar || (superstarUnlocked[stats->stats.CharID] != 0 &&
                             g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE)) {
            record = TEAM_MANAGEMENT_RECORD(scene, iconHandle);
            record->flags |= UI_FLAG_VISIBLE;
            record->playMode = UI_PLAY_FORWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, starHandle);
            record->flags |= UI_FLAG_VISIBLE;
            record->frame = showSuperstar ? 0x000F0000 : 0;
            record->playMode = showSuperstar ? UI_PLAY_FORWARD : UI_PLAY_STOP;
            if (aiPosSwapInputs.rosterView[port] != ROSTER_VIEW_BATTING_ORDER && g_d_GameSettings._06 == 2) {
                record = TEAM_MANAGEMENT_RECORD(scene, player + 0x7E);
                record->flags |= UI_FLAG_VISIBLE;
                record->playMode = UI_PLAY_FORWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, player + 0x87);
                record->flags |= UI_FLAG_VISIBLE;
                record->frame = showSuperstar ? 0x000F0000 : 0;
                record->playMode = showSuperstar ? UI_PLAY_FORWARD : UI_PLAY_STOP;
            }
        } else {
            TEAM_MANAGEMENT_RECORD(scene, iconHandle)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, starHandle)->flags &= ~UI_FLAG_VISIBLE;
            if (aiPosSwapInputs.rosterView[port] != ROSTER_VIEW_BATTING_ORDER && g_d_GameSettings._06 == 2) {
                TEAM_MANAGEMENT_RECORD(scene, player + 0x7E)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, player + 0x87)->flags &= ~UI_FLAG_VISIBLE;
            }
        }
        if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
            TEAM_MANAGEMENT_RECORD(scene, player + (g_d_GameSettings._06 == 2 ? 0x75 : teamOffset + 0x64))->flags &= ~UI_FLAG_VISIBLE;
        } else if (g_d_GameSettings._06 != 2) {
            TEAM_MANAGEMENT_RECORD(scene, player + teamOffset + 0x12E)->flags &= ~UI_FLAG_VISIBLE;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, player + 0x35)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, player + 0x75)->flags &= ~UI_FLAG_VISIBLE;
        }
    }

    if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
        record = TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x64);
        record->flags |= UI_FLAG_VISIBLE;
        record->elementIndex = 0x2A;
        record->playMode = UI_PLAY_FORWARD;
        fn_8005C830(scene, port, selection);
    } else {
        if (g_d_GameSettings._06 != 2) {
            record = TEAM_MANAGEMENT_RECORD(scene, swapPosition + teamOffset + 0x12E);
        } else {
            record = TEAM_MANAGEMENT_RECORD(scene, swapSelection + 0x75);
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            record->playMode = UI_PLAY_FORWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, swapPosition + 0x35);
        }
        record->flags |= UI_FLAG_VISIBLE;
        record->elementIndex = 0x2A;
        record->playMode = UI_PLAY_FORWARD;
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
    s32 position;
    s32 previousPosition;
    s32 swapPosition;
    s32 teamOffset = port * 9;
    s32 i;
    UIRecord* record;

    if (gameSetUpStep[0x37 + port] != 0) {
        return;
    }
    selection = (s8)(aiPosSwapInputs.teamManagement_cursorPos[port] - 1);
    previousSelection = (s8)(aiPosSwapInputs.teamManagement_prevCursorPos[port] - 1);
    swapSelection = (s8)aiPosSwapInputs.charSelectedToBeSwappedCharID[port];

    if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
        if (g_d_GameSettings._06 != 2) {
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD(scene, i + teamOffset + 0x64)->flags &= ~UI_FLAG_VISIBLE;
            }
            record = TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x40);
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x1C);
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x52);
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, selection + teamOffset + 0x64);
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            record->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            record = TEAM_MANAGEMENT_RECORD(scene, previousSelection + teamOffset + 0x40);
            record->frame = 0;
            record->playMode = UI_PLAY_BACKWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, previousSelection + teamOffset + 0x1C);
            record->frame = 0x000A0000;
            record->playMode = UI_PLAY_BACKWARD;
            if (swapSelection != CHAR_ID_NONE) {
                record = TEAM_MANAGEMENT_RECORD(scene, swapSelection + teamOffset + 0x1C);
                record->frame = 0x000A0000;
                record->playMode = UI_PLAY_STOP;
                TEAM_MANAGEMENT_RECORD(scene, swapSelection + teamOffset + 0x40)->playMode = UI_PLAY_FORWARD;
            }
        } else {
            position = lineUpInfoStruct[port][selection][2];
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD(scene, i + 0x75)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, i + 0x35)->flags &= ~UI_FLAG_VISIBLE;
            }
            record = TEAM_MANAGEMENT_RECORD(scene, selection + 0x63);
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, selection + 0x51);
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x6C)->frame = 0;
            record = TEAM_MANAGEMENT_RECORD(scene, selection + 0x75);
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD(scene, selection + 0x6C)->playMode = UI_PLAY_FORWARD;
            record->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            record = TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x63);
            record->frame = 0;
            record->playMode = UI_PLAY_BACKWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x51);
            record->frame = 0x000A0000;
            record->playMode = UI_PLAY_BACKWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, position + 0x35);
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            record->playMode = UI_PLAY_FORWARD;
            if (swapSelection != CHAR_ID_NONE) {
                record = TEAM_MANAGEMENT_RECORD(scene, swapSelection + 0x51);
                record->frame = 0x000A0000;
                record->playMode = UI_PLAY_STOP;
                TEAM_MANAGEMENT_RECORD(scene, swapSelection + 0x63)->playMode = UI_PLAY_FORWARD;
            }
        }
    } else {
        position = lineUpInfoStruct[port][selection][2];
        previousPosition = lineUpInfoStruct[port][previousSelection][2];
        swapPosition = lineUpInfoStruct[port][swapSelection][2];
        if (g_d_GameSettings._06 != 2) {
            TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x10A)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0xF8)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0xE6)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, previousPosition + teamOffset + 0x10A)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, previousPosition + teamOffset + 0xF8)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, previousPosition + teamOffset + 0xE6)->flags &= ~UI_FLAG_VISIBLE;
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD(scene, i + teamOffset + 0x12E)->flags &= ~UI_FLAG_VISIBLE;
            }
            record = TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x12E);
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            record->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            if (swapSelection != CHAR_ID_NONE) {
                TEAM_MANAGEMENT_RECORD(scene, swapPosition + teamOffset + 0x10A)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, swapPosition + teamOffset + 0xF8)->playMode = UI_PLAY_FORWARD;
            }
        } else {
            TEAM_MANAGEMENT_RECORD(scene, position + 0x23)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, position + 0x1A)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD(scene, position + 0x11)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, previousPosition + 0x23)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, previousPosition + 0x1A)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD(scene, previousPosition + 0x11)->flags &= ~UI_FLAG_VISIBLE;
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD(scene, i + 0x35)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD(scene, i + 0x75)->flags &= ~UI_FLAG_VISIBLE;
            }
            record = TEAM_MANAGEMENT_RECORD(scene, selection + 0x6C);
            record->flags |= UI_FLAG_VISIBLE;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, selection + 0x75);
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            record->playMode = UI_PLAY_FORWARD;
            record = TEAM_MANAGEMENT_RECORD(scene, position + 0x35);
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            record->playMode = UI_PLAY_FORWARD;
            if (swapSelection != CHAR_ID_NONE) {
                TEAM_MANAGEMENT_RECORD(scene, swapPosition + 0x23)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD(scene, swapPosition + 0x1A)->playMode = UI_PLAY_FORWARD;
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
        return;
    }

    if (((u8*)&aiPosSwapInputs)[0xCF3C + port] == 0) {
        fn_8005CCE4(scene, port);
        return;
    }
    if (gameSetUpStep[0x37 + port] != 0) {
        return;
    }

    {
        u8 selection = ((u8*)&aiPosSwapInputs)[0xCF3E + port];
        s32 mode = ((u8*)&aiPosSwapInputs)[0xCF52 + port];
        u8 position = ((u8*)lineUpInfoStruct)[port * 0x24 + selection * 4 + 2];
        s32 teamOffset = port * 9;
        s32 first = scene->firstHandle;
        UIRecord* record;

        if (mode == 0) {
            record = (UIRecord*)graphicsRelatedArray[first + selection + teamOffset + 0x1C].object;
            record->frame = 0x000A0000;
            record->playMode = UI_PLAY_STOP;
            record = (UIRecord*)graphicsRelatedArray[first + selection + teamOffset + 0x40].object;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
        } else if (g_d_GameSettings._06 != 2) {
            record = (UIRecord*)graphicsRelatedArray[first + position + teamOffset + 0x10A].object;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = (UIRecord*)graphicsRelatedArray[first + position + teamOffset + 0xF8].object;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
        } else {
            record = (UIRecord*)graphicsRelatedArray[first + position + 0x23].object;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = (UIRecord*)graphicsRelatedArray[first + position + 0x1A].object;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
        }
        gameSetUpStep[0x5D + port] = 0;
        gameSetUpStep[0x37 + port] = 2;
    }
}

void fn_8005EC88(MenuScene* scene, s32 port) {
    s32 teamOffset = port * 9;
    s32 lineupPosition;
    s32 i;
    UIRecord* record;

    if (gameSetUpStep[0x37 + port] == 0) {
        if (((s8*)&aiPosSwapInputs)[0xCF46 + port] != 0) {
            s32 index = aiPosSwapInputs.teamManagement_cursorPos[port] - 1;
            lineupPosition = lineUpInfoStruct[port][index][2];
            for (i = 0; i < 9; i += 3) {
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x64].object;
                record->flags &= ~UI_FLAG_VISIBLE;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x12E].object;
                record->flags &= ~UI_FLAG_VISIBLE;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x65].object;
                record->flags &= ~UI_FLAG_VISIBLE;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x12F].object;
                record->flags &= ~UI_FLAG_VISIBLE;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x66].object;
                record->flags &= ~UI_FLAG_VISIBLE;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x130].object;
                record->flags &= ~UI_FLAG_VISIBLE;
            }

            if (((u8*)&aiPosSwapInputs)[0xCF52 + port] == 0) {
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + index + teamOffset + 0x40].object;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + index + teamOffset + 0x1C].object;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + index + teamOffset + 0x52].object;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + index + teamOffset + 0x64].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->elementIndex = 0x2A;
                record->playMode = UI_PLAY_FORWARD;
                fn_8005C830(scene, port, index);
            } else if (((u8*)&aiPosSwapInputs)[0xCF52 + port] == 1) {
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + lineupPosition + teamOffset + 0x10A].object;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + lineupPosition + teamOffset + 0xF8].object;
                record->playMode = UI_PLAY_FORWARD;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + lineupPosition + teamOffset + 0x12E].object;
                record->flags |= UI_FLAG_VISIBLE;
                record->elementIndex = 0x2A;
                record->playMode = UI_PLAY_FORWARD;
                fn_8005C830(scene, port, index);
            }
        }

        record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x18].object;
        record->frame = 0x000A0000;
        record->playMode = 4;
        makeCursorUnmovable(port);
        gameSetUpStep[0x37 + port] = 1;
    }
}

void fn_8005F068(MenuScene* scene, s32 port) {
    s32 selection;
    s32 selectedPosition;
    s32 swapSelection = CHAR_ID_NONE;
    s32 swapPosition = CHAR_ID_NONE;
    s32 teamOffset = port * 9;
    s32 i;
    UIRecord* record;

    if (gameSetUpStep[0x37 + port] != 0) {
        return;
    }

    selection = (s8)(aiPosSwapInputs.teamManagement_cursorPos[port] - 1);
    selectedPosition = lineUpInfoStruct[port][selection][2];
    if (aiPosSwapInputs.charSelectedToBeSwappedCharID[port] != (u8)CHAR_ID_NONE) {
        swapSelection = (s8)aiPosSwapInputs.charSelectedToBeSwappedCharID[port];
        swapPosition = lineUpInfoStruct[port][swapSelection][2];
    }

    if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER &&
        ((u8*)&aiPosSwapInputs)[0xCF54 + port] == 1) {
        record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x14].object;
        record->frame = 0x00140000;
        record->playMode = UI_PLAY_BACKWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x1A].object)->playMode = UI_PLAY_FORWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0xE2].object)->playMode = UI_PLAY_BACKWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0xE4].object)->playMode = UI_PLAY_BACKWARD;
        for (i = 0; i < 9; i++) {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x64].object)->flags &= ~UI_FLAG_VISIBLE;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x1C].object;
            record->frame = 0;
            record->playMode = UI_PLAY_STOP;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x40].object;
            record->frame = 0;
            record->playMode = UI_PLAY_STOP;
        }
        if (selection >= 0 && selection < 9) {
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + selection + teamOffset + 0x1C].object;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + selection + teamOffset + 0x52].object;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + selection + teamOffset + 0x64].object;
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            record->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + selection + teamOffset + 0x40].object;
            record->frame = 0;
            record->playMode = UI_PLAY_FORWARD;
            if (aiPosSwapInputs.charSelectedToBeSwappedCharID[port] != (u8)CHAR_ID_NONE) {
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + swapSelection + teamOffset + 0x1C].object;
                record->frame = 0x000A0000;
                record->playMode = UI_PLAY_STOP;
                record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + swapSelection + teamOffset + 0x40].object;
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
            }
        }
    } else if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_DEFENSIVE_ALIGNMENT &&
               ((u8*)&aiPosSwapInputs)[0xCF54 + port] != 1) {
        for (i = 0; i < 9; i++) {
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x10A].object;
            record->frame = 0;
            record->playMode = UI_PLAY_STOP;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0xF8].object;
            record->frame = 0;
            record->playMode = UI_PLAY_STOP;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0xE6].object)->flags &= ~UI_FLAG_VISIBLE;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + i + teamOffset + 0x12E].object)->flags &= ~UI_FLAG_VISIBLE;
        }
        record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x14].object;
        record->frame = 0x000A0000;
        record->playMode = UI_PLAY_FORWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x1A].object)->playMode = UI_PLAY_BACKWARD;
        record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0xE2].object;
        record->playMode = UI_PLAY_FORWARD;
        record->flags |= UI_FLAG_VISIBLE;
        record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0xE4].object;
        record->playMode = UI_PLAY_FORWARD;
        record->flags |= UI_FLAG_VISIBLE;
        if (selection >= 0 && selection < 9) {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + selectedPosition + teamOffset + 0x10A].object)->playMode = UI_PLAY_FORWARD;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + selectedPosition + teamOffset + 0xF8].object)->playMode = UI_PLAY_FORWARD;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + selectedPosition + teamOffset + 0xE6].object)->flags |= UI_FLAG_VISIBLE;
            record = (UIRecord*)graphicsRelatedArray[scene->firstHandle + selectedPosition + teamOffset + 0x12E].object;
            record->flags |= UI_FLAG_VISIBLE;
            record->elementIndex = 0x2A;
            record->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            if (aiPosSwapInputs.charSelectedToBeSwappedCharID[port] != (u8)CHAR_ID_NONE) {
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + swapPosition + teamOffset + 0x10A].object)->playMode = UI_PLAY_FORWARD;
                ((UIRecord*)graphicsRelatedArray[scene->firstHandle + swapPosition + teamOffset + 0xF8].object)->playMode = UI_PLAY_FORWARD;
            }
        }
    }

    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = 1;
}

void fn_8005F734(MenuScene* scene, s32 port) {
    if (gameSetUpStep[0x37 + port] == 0) {
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->elementIndex = 0x49;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->frame = 0x00320000;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port].object)->playMode = UI_PLAY_BACKWARD;

        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 2].object)->elementIndex = 0x52;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 2].object)->frame = 0;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 2].object)->playMode = UI_PLAY_FORWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 4].object)->frame = 0;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 4].object)->playMode = UI_PLAY_FORWARD;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 6].object)->frame = 0x000E0000;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 6].object)->playMode = UI_PLAY_FORWARD;

        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0xA].object)->flags |= UI_FLAG_VISIBLE;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0xA].object)->frame = 0;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0xA].object)->playMode = UI_PLAY_FORWARD;

        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x14].object)->frame = 0;
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x14].object)->playMode = UI_PLAY_FORWARD;

        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port == 0) {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x12].object)->frame = 0x001E0000;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x12].object)->playMode = UI_PLAY_BACKWARD;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x18].object)->frame = 0;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x18].object)->playMode = 0;
        } else {
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x12].object)->frame = 0;
            ((UIRecord*)graphicsRelatedArray[scene->firstHandle + port + 0x12].object)->playMode = UI_PLAY_FORWARD;
        }

        makeCursorUnmovable(port);
        gameSetUpStep[0x37 + port] = 1;
    }
}

void fn_8005F9D0(MenuScene* scene, s32 port) {
    s32 completeCount = 0;

    if (gameSetUpStep[0x37 + port] != 1) {
        return;
    }

    completeCount += maybeCheckAndResetGrapicsElement(scene, port + 4, 0x14) != 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        completeCount += maybeCheckAndResetGrapicsElement(scene, port, 0x14) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0xA, 0xA) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, 0x12, 0xA) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, 0x14, 0xA) != 0;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port != 0) {
        completeCount += maybeCheckAndResetGrapicsElement(scene, port, 0x1E) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0xA, 0xA) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x12, 0x14) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0xA) != 0;
    } else {
        completeCount += maybeCheckAndResetGrapicsElement(scene, port, 0x14) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0xA, 0xA) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x12, 0xA) != 0;
        completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0xA) != 0;
    }

    if (completeCount != 5) {
        return;
    }

    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        ((u8*)&aiPosSwapInputs)[0xCF5B + port] = 1;
        if (((u8*)&aiPosSwapInputs)[0xCF5B] == 0 || ((u8*)&aiPosSwapInputs)[0xCF5C] == 0) {
            return;
        }
        ((u8*)&aiPosSwapInputs)[0xCF5B] = 0;
        ((u8*)&aiPosSwapInputs)[0xCF5C] = 0;
        makeCursorMovable(0);
        makeCursorMovable(1);
        gameSetUpStep[0x37] = 2;
        gameSetUpStep[0x38] = 2;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            updateCharacterSelectProcessCode(0, 0x45);
        }
    } else {
        makeCursorMovable(port);
        gameSetUpStep[0x37 + port] = 2;
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
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
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
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port != 0) {
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

    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = 1;
}

void teamManagementGraphics_steadyState(void) {
    MenuScene* scene = (MenuScene*)currentDrawingItem;
    u8* input = (u8*)&aiPosSwapInputs;
    s32 index;

    for (index = 0; index < 2; index++) {
        s32 port = gameSetUpStep[0x59 + index];
        s32 completeCount = 0;
        s32 requiredCount = 0;
        s32 selection;
        s32 previousSelection;
        s32 position;
        s32 swapPosition;
        s32 teamOffset = port * 9;
        s32 player;
        UIRecord* record;

        switch (gameSetUpStep[0x5D + index]) {
        case 0x38:
            if (g_d_GameSettings._06 != 2) {
                fn_8005FCA0(scene, port);
                fn_8005F9D0(scene, port);
            } else {
                if (gameSetUpStep[0x37 + port] == 0) {
                    record = TEAM_MANAGEMENT_RECORD(scene, 0);
                    record->frame = 0;
                    record->playMode = UI_PLAY_FORWARD;
                    if (input[0xCFA2 + port] != 1) {
                        record = TEAM_MANAGEMENT_RECORD(scene, 1);
                        record->frame = 0;
                        record->playMode = UI_PLAY_FORWARD;
                    }
                    TEAM_MANAGEMENT_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
                    record = TEAM_MANAGEMENT_RECORD(scene, 0xE);
                    record->frame = 0;
                    record->playMode = UI_PLAY_FORWARD;
                    makeCursorUnmovable(port);
                    gameSetUpStep[0x37 + port] = 1;
                }
                if (gameSetUpStep[0x37 + port] == 1) {
                    requiredCount = 1;
                    completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0x14) != 0;
                    if (input[0xCFA2 + port] != 1) {
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
                completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0xA, 0xA) != 0;
                if (completeCount == 5) {
                    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                        input[0xCF5B + port] = 1;
                        if (input[0xCF5B] != 0 && input[0xCF5C] != 0) {
                            input[0xCF5C] = 0;
                            input[0xCF5B] = 0;
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
                record = TEAM_MANAGEMENT_RECORD(scene, port);
                if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE &&
                    g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port != 0) {
                    record->frame = 0x001E0000;
                    record->playMode = UI_PLAY_FORWARD;
                } else {
                    record->frame = 0x00140000;
                    record->playMode = UI_PLAY_BACKWARD;
                }
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                s32 endFrame = 0;
                if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE &&
                    g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port != 0) {
                    endFrame = 0x32;
                }
                if (maybeCheckAndResetGrapicsElement(scene, port, endFrame) != 0) {
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
                if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER && input[0xCF54 + port] == 1) {
                    requiredCount = 1;
                    completeCount = maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0xA) != 0;
                } else if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_DEFENSIVE_ALIGNMENT && input[0xCF54 + port] != 1) {
                    requiredCount = 1;
                    completeCount = maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0x14) != 0;
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
            } else {
                fn_8005B760(scene, port);
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                makeCursorMovable(port);
                gameSetUpStep[0x37 + port] = 2;
            }
            break;
        case 0x3E:
            if (gameSetUpStep[0x37 + port] == 0) {
                if (g_d_GameSettings._06 == 2 || aiPosSwapInputs.teamManagement_cursorPos[port] == 0) {
                    previousSelection = (s8)(aiPosSwapInputs.teamManagement_prevCursorPos[port] - 1);
                    if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
                        if (g_d_GameSettings._06 != 2) {
                            TEAM_MANAGEMENT_RECORD(scene, previousSelection + teamOffset + 0x40)->playMode = UI_PLAY_BACKWARD;
                            record = TEAM_MANAGEMENT_RECORD(scene, previousSelection + teamOffset + 0x1C);
                        } else {
                            TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x63)->playMode = UI_PLAY_BACKWARD;
                            record = TEAM_MANAGEMENT_RECORD(scene, previousSelection + 0x51);
                        }
                        record->frame = 0x000A0000;
                        record->playMode = UI_PLAY_BACKWARD;
                        for (player = 0; player < 9; player++) {
                            if (g_d_GameSettings._06 != 2) {
                                TEAM_MANAGEMENT_RECORD(scene, player + teamOffset + 0x64)->flags &= ~UI_FLAG_VISIBLE;
                            } else {
                                TEAM_MANAGEMENT_RECORD(scene, player + 0x75)->flags &= ~UI_FLAG_VISIBLE;
                                TEAM_MANAGEMENT_RECORD(scene, player + 0x35)->flags &= ~UI_FLAG_VISIBLE;
                            }
                        }
                    } else if (aiPosSwapInputs.rosterView[port] == ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
                        position = lineUpInfoStruct[port][previousSelection][2];
                        if (g_d_GameSettings._06 != 2) {
                            TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0x10A)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0xF8)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, position + teamOffset + 0xE6)->flags &= ~UI_FLAG_VISIBLE;
                        } else {
                            TEAM_MANAGEMENT_RECORD(scene, position + 0x23)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, position + 0x1A)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, position + 0x11)->flags &= ~UI_FLAG_VISIBLE;
                        }
                        for (player = 0; player < 9; player++) {
                            if (g_d_GameSettings._06 != 2) {
                                TEAM_MANAGEMENT_RECORD(scene, player + teamOffset + 0x12E)->flags &= ~UI_FLAG_VISIBLE;
                            } else {
                                TEAM_MANAGEMENT_RECORD(scene, player + 0x35)->flags &= ~UI_FLAG_VISIBLE;
                                TEAM_MANAGEMENT_RECORD(scene, player + 0x75)->flags &= ~UI_FLAG_VISIBLE;
                            }
                        }
                    }
                }
                record = TEAM_MANAGEMENT_RECORD(scene, g_d_GameSettings._06 == 2 ? 0xE : port + 0x18);
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                makeCursorMovable(port);
                gameSetUpStep[0x37 + port] = 2;
            }
            break;
        case 0x3F:
            if (g_d_GameSettings._06 == 2) {
                break;
            }
            if (gameSetUpStep[0x37 + port] == 0) {
                record = TEAM_MANAGEMENT_RECORD(scene, 0);
                record->frame = 0x00140000;
                record->playMode = UI_PLAY_FORWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, 1);
                record->frame = 0x001E0000;
                record->playMode = UI_PLAY_BACKWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, 0x18);
                record->frame = 0x000A0000;
                record->playMode = UI_PLAY_BACKWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, 0x19);
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, 0x12);
                record->frame = 0x000A0000;
                record->playMode = UI_PLAY_FORWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, 0x13);
                record->frame = 0x00140000;
                record->playMode = UI_PLAY_BACKWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0x1E) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 1, 0x14) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x12, 0x14) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x13, 0xA) != 0;
                if (completeCount == 4) {
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
                record = TEAM_MANAGEMENT_RECORD(scene, 0);
                record->frame = 0x001E0000;
                record->playMode = UI_PLAY_BACKWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, 1);
                record->frame = 0x00140000;
                record->playMode = UI_PLAY_FORWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, 0x18);
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, 0x19);
                record->frame = 0x000A0000;
                record->playMode = UI_PLAY_BACKWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, 0x12);
                record->frame = 0x00140000;
                record->playMode = UI_PLAY_BACKWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, 0x13);
                record->frame = 0x000A0000;
                record->playMode = UI_PLAY_FORWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0x14) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 1, 0x1E) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x12, 0xA) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x13, 0x14) != 0;
                if (completeCount == 4) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x41:
            if (gameSetUpStep[0x37 + port] == 0) {
                record = TEAM_MANAGEMENT_RECORD(scene, port);
                record->frame = 0x00140000;
                record->playMode = UI_PLAY_FORWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, port + 0x18);
                record->frame = 0x000A0000;
                record->playMode = UI_PLAY_BACKWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, port + 0x12);
                record->frame = 0x000A0000;
                record->playMode = UI_PLAY_FORWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = fn_80042D68(scene, port, 0x1E) != 0;
                completeCount += fn_80042D68(scene, port + 0x12, 0x14) != 0;
                if (completeCount == 2) {
                    input[0xCF50 + port] = 0;
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x42:
            if (gameSetUpStep[0x37 + port] == 0) {
                record = TEAM_MANAGEMENT_RECORD(scene, port);
                record->frame = 0x001E0000;
                record->playMode = UI_PLAY_BACKWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, port + 0x18);
                record->frame = 0;
                record->playMode = UI_PLAY_FORWARD;
                record = TEAM_MANAGEMENT_RECORD(scene, port + 0x12);
                record->frame = 0x00140000;
                record->playMode = UI_PLAY_BACKWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = 1;
            }
            if (gameSetUpStep[0x37 + port] == 1) {
                completeCount = maybeCheckAndResetGrapicsElement(scene, port, 0x14) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x12, 0xA) != 0;
                if (completeCount == 2) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = 2;
                }
            }
            break;
        case 0x43:
            fn_8005C5C4(scene, port);
            if (gameSetUpStep[0x37 + port] == 1) {
                if (g_d_GameSettings._06 != 2) {
                    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                        requiredCount = 2;
                        completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0) != 0;
                        completeCount += maybeCheckAndResetGrapicsElement(scene, 1, 0) != 0;
                    } else {
                        s32 endFrame;
                        requiredCount = 1;
                        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                            endFrame = port != 0 ? 0 : 0x32;
                        } else {
                            endFrame = (TEAM_MANAGEMENT_RECORD(scene, port)->frame >> 16) >= 0x1E ? 0x32 : 0;
                        }
                        completeCount = maybeCheckAndResetGrapicsElement(scene, port, endFrame) != 0;
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
                        record = TEAM_MANAGEMENT_RECORD(scene, previousSelection + teamOffset + 0x1C);
                        record->frame = 0x000A0000;
                        record->playMode = UI_PLAY_BACKWARD;
                        record = TEAM_MANAGEMENT_RECORD(scene, previousSelection + teamOffset + 0x40);
                        record->frame = 0x000A0000;
                        record->playMode = UI_PLAY_BACKWARD;
                    }
                } else {
                    position = lineUpInfoStruct[port][selection][2];
                    swapPosition = lineUpInfoStruct[port][previousSelection][2];
                    if (previousSelection != CHAR_ID_NONE && swapPosition != position) {
                        if (g_d_GameSettings._06 != 2) {
                            TEAM_MANAGEMENT_RECORD(scene, swapPosition + teamOffset + 0x10A)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, swapPosition + teamOffset + 0xF8)->playMode = UI_PLAY_BACKWARD;
                        } else {
                            TEAM_MANAGEMENT_RECORD(scene, swapPosition + 0x23)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD(scene, swapPosition + 0x1A)->playMode = UI_PLAY_BACKWARD;
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
                if (playedFlag) {
                    sndFXStartEx(g_d_GameSettings._06 == 2 ? 0x1B1 : 0x1E6, 0x7F, 0x3F, 0);
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
            record = TEAM_MANAGEMENT_RECORD(scene, 0x1D2);
            record->flags |= UI_FLAG_VISIBLE;
            record->playMode = UI_PLAY_FORWARD;
            gameSetUpStep[0x5D] = 0;
            break;
        }
        battingOrderProcessInputs(scene, port);
    }
    if (input[0xCF45] != 0) {
        input[0xCF45] = 0;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}
