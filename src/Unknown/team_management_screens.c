#define SQRT2_LINKAGE static
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
extern BOOL fn_80042D68(MenuScene* scene, int handle, int frame);
extern void removeGraphicsElementFromScene(DrawingSceneStruct* node);

static inline UIRecord* TEAM_MANAGEMENT_RECORD(MenuScene* scene, s32 handle) {
    return (UIRecord*)graphicsRelatedArray[scene->firstHandle + handle].object;
}

#define TEAM_MANAGEMENT_RECORD_C(scene, base, ...) ((UIRecord*)graphicsRelatedArray[(base) + (scene)->firstHandle + __VA_ARGS__].object)

static inline BOOL isGraphicsElementDone(MenuScene* scene, s32 handle, s32 frame) {
    return maybeCheckAndResetGrapicsElement(scene, handle, frame) != 0 ? TRUE : FALSE;
}

static inline BOOL isAnimStepStart(u8 step) {
    return step == TEAM_MANAGEMENT_ANIM_STEP_START ? TRUE : FALSE;
}

static inline BOOL isAnimStepPlaying(u8 step) {
    return step == TEAM_MANAGEMENT_ANIM_STEP_PLAYING ? TRUE : FALSE;
}

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
        TEAM_MANAGEMENT_RECORD_C(scene, 0x1B4, (u8)port)->frame = selected[0] << 16;
        TEAM_MANAGEMENT_RECORD_C(scene, 0x1B6, (u8)port)->frame = selected[1] << 16;
    } else {
        TEAM_MANAGEMENT_RECORD(scene, 0x125)->frame = selected[0] << 16;
        TEAM_MANAGEMENT_RECORD(scene, 0x126)->frame = selected[1] << 16;
    }
}

void fn_800596D4(MenuScene* scene) {
    if (g_TeamManagement.starMenuStepStarted == 0) {
        if (challengeStarRelatedInd(g_TeamManagement.playerIndexNoVariants, g_TeamManagement.starMenuCursorPos)) {
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1E7, g_TeamManagement.starMenuCursorPos)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1E7, g_TeamManagement.starMenuCursorPos)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1E7, g_TeamManagement.starMenuCursorPos)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD), g_TeamManagement.starMenuCursorPos)->frame = 0x00010000;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1E7, g_TeamManagement.starMenuCursorPos)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD), g_TeamManagement.starMenuCursorPos)->frame = 0;
        }
        TEAM_MANAGEMENT_RECORD_C(scene, 0x1FB, g_TeamManagement.starMenuCursorPos)->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD_C(scene, 0x1FB, g_TeamManagement.starMenuCursorPos)->playMode = UI_PLAY_FORWARD;
        if (challengeStarRelatedInd(g_TeamManagement.playerIndexNoVariants, g_TeamManagement.starMenuPrevCursorPos)) {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1E7, g_TeamManagement.starMenuPrevCursorPos)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD), g_TeamManagement.starMenuPrevCursorPos)->frame = 0;
        } else {
            TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD), g_TeamManagement.starMenuPrevCursorPos)->frame = 0;
        }
        TEAM_MANAGEMENT_RECORD_C(scene, 0x1FB, g_TeamManagement.starMenuPrevCursorPos)->flags &= ~UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD_C(scene, 0x1FB, g_TeamManagement.starMenuPrevCursorPos)->playMode = UI_PLAY_FORWARD;
        {
            s32 requirementRow = characterStaticIndexes[g_TeamManagement.playerIndexNoVariants].requirementRow;
            s32 textID;
            if ((s8)g_Challenge.characters[g_TeamManagement.playerIndexNoVariants].inGameMissionTracker[g_TeamManagement.starMenuCursorPos].shownOnPauseMenu != 0) {
                textID = starMissionDisplayRules[requirementRow][g_TeamManagement.starMenuCursorPos].textID;
            } else if (starMissionDisplayRules[requirementRow][g_TeamManagement.starMenuCursorPos].minScoutRow <= g_Challenge.difficulty) {
                textID = 0x1C5;
            } else {
                textID = 0x1C6;
            }
            text_setPtrToWhereCharsAreStored(g_TeamManagement.textBlocks[2], 0, textID);
        }
        g_TeamManagement.starMenuStepStarted = TRUE;
    }
    if (g_TeamManagement.starMenuStepStarted != 0) {
        g_TeamManagement.starMenuDrawStep = STAR_MENU_DRAW_STEP_NONE;
        g_TeamManagement.starMenuStepStarted = FALSE;
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

    if (g_TeamManagement.starMenuStepStarted == 0) {
        character = g_TeamManagement.starMenuCharID;
        g_TeamManagement.playerIndexNoVariants = characterStaticIndexes[character].trackerIdx;
        character = g_TeamManagement.starMenuCharID;
        requirementRow = characterStaticIndexes[character].requirementRow;
        rank = (s8)g_Challenge.characters[g_TeamManagement.playerIndexNoVariants].variantClassification;
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
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16e : 0x1D7))->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16e : 0x1D7))->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16a : 0x1D3))->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16a : 0x1D3))->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16b : 0x1D4))->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16b : 0x1D4))->frame = rank << 16;
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16c : 0x1D5))->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16c : 0x1D5))->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16d : 0x1D6))->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x171 : 0x1DA))->frame =
            characterClass << 16;
        TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x172 : 0x1DB))->frame = g_TeamManagement.starMenuCharID << 16;
        g_TeamManagement.textBlocks[0] = text_initializeNewChannel((UnkText988Arg*)scene,
            g_d_GameSettings._06 == 2 ? 0x19B : 0x205, 0, 0, g_TeamManagement.playerIndexNoVariants + 8, 0);
        rank = determineIfMissionDescriptionIsShown(g_TeamManagement.playerIndexNoVariants);
        g_TeamManagement.textBlocks[1] = text_initializeNewChannel((UnkText988Arg*)scene,
            g_d_GameSettings._06 == 2 ? 0x19C : 0x206, 1, 0,
            (s16)starRankTextIDs[requirementRow] + rank, 0);
        rank = determineIfMissionDescriptionIsShown(g_TeamManagement.playerIndexNoVariants);
        TEAM_MANAGEMENT_RECORD(scene, 0x1DC)->frame = (4 - rank) << 16;
        mission = g_TeamManagement.starMenuCursorPos;
        if ((s8)g_Challenge.characters[g_TeamManagement.playerIndexNoVariants].inGameMissionTracker[mission].shownOnPauseMenu != 0) {
            textID = starMissionDisplayRules[requirementRow][mission].textID;
        } else if (starMissionDisplayRules[requirementRow][mission].minScoutRow <= g_Challenge.difficulty) {
            textID = 0x1C5;
        } else {
            textID = 0x1C6;
        }
        g_TeamManagement.textBlocks[2] = text_initializeNewChannel((UnkText988Arg*)scene,
            g_d_GameSettings._06 == 2 ? 0x19D : 0x207, 0, 0, textID, 0);
        screenTextArray.blocks[g_TeamManagement.textBlocks[2]].justify = 1;
        for (mission = 0; mission < missionCount; mission++) {
            if (challengeStarRelatedInd(g_TeamManagement.playerIndexNoVariants, mission)) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1F1, mission)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1F1, mission)->playMode = UI_PLAY_FORWARD;
            } else {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1F1, mission)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1FB, mission)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1E7, mission)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD), mission)->frame = 0;
        }
        if (challengeStarRelatedInd(g_TeamManagement.playerIndexNoVariants, g_TeamManagement.starMenuCursorPos)) {
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1E7, g_TeamManagement.starMenuCursorPos)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1E7, g_TeamManagement.starMenuCursorPos)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD), g_TeamManagement.starMenuCursorPos)->frame = 0x00010000;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, 0x1D9)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1E7, g_TeamManagement.starMenuCursorPos)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x173 : 0x1DD), g_TeamManagement.starMenuCursorPos)->frame = 0;
        }
        TEAM_MANAGEMENT_RECORD_C(scene, 0x1FB, g_TeamManagement.starMenuCursorPos)->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD_C(scene, 0x1FB, g_TeamManagement.starMenuCursorPos)->playMode = UI_PLAY_FORWARD;
        g_TeamManagement.starMenuStepStarted = TRUE;
    }
    if (g_TeamManagement.starMenuStepStarted != 0) {
        g_TeamManagement.starMenuDrawStep = STAR_MENU_DRAW_STEP_NONE;
        g_TeamManagement.starMenuStepStarted = FALSE;
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
        if (g_TeamManagement.onePlayerEditingTeam != 0) {
            port = 1;
        } else {
            port = 0;
        }
    }
    if (g_d_GameSettings._06 != 2) {
        buttons = Static_Stats_Tables.controllerInputs[inputPort].newInput;
    } else {
        buttons = g_TeamManagement.playerInputs[port].newInput;
    }
    switch (buttons) {
    case INPUT_BUTTON_X:
        if (g_TeamManagement.rosterView[port] == ROSTER_VIEW_BATTING_ORDER &&
        g_d_GameSettings._06 != 2) {
            if (g_TeamManagement.teamManagement_cursorPos[port] != 0) {
                s32 stance;
                CharacterStats* stats;
                selection = g_TeamManagement.teamManagement_cursorPos[port] - 1;
                stats = &inMemRoster[port][selection];
                stance = stats->stats.BattingStance + stats->stats.FieldingArm * 2 + 1;
                if (stance == 4) {
                    stance = 0;
                }
                stats->stats.BattingStance = stance % 2;
                stats->stats.FieldingArm = stance / 2;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xAC, selection + port * 9)->frame = stance << 16;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            g_TeamManagement.stanceChangeRequested[port] = FALSE;
        }
        break;
    }
    if (g_TeamManagement.inProgress_superStarAPlayer[port] != 0) {
        if (g_d_GameSettings._06 != 2) {
            if (g_TeamManagement.teamManagement_cursorPos[port] != 0) {
                transferStatsToInMemRoster((u8)port);
                sndFXRelated(INPUT_TRIGGER_L);
            } else {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            }
            if (g_TeamManagement.teamManagement_cursorPos[port] != 0 &&
                g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                s32 position;
                s32 teamOffset = port * 9;
                selection = g_TeamManagement.teamManagement_cursorPos[port] - 1;
                position = lineUpInfoStruct[port][selection][2];
                if (Static_Stats_Tables.charIsStarred[port][selection] != 0) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x76, selection + teamOffset)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x76, selection + teamOffset)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x88, selection + teamOffset)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x88, selection + teamOffset)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x88, selection + teamOffset)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x140, position + teamOffset)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x140, position + teamOffset)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x152, position + teamOffset)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x152, position + teamOffset)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x152, position + teamOffset)->playMode = UI_PLAY_FORWARD;
                } else {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x88, selection + teamOffset)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x88, selection + teamOffset)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x88, selection + teamOffset)->playMode = UI_PLAY_STOP;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x152, position + teamOffset)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x152, position + teamOffset)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x152, position + teamOffset)->playMode = UI_PLAY_STOP;
                }
            }
        }
        g_TeamManagement.inProgress_superStarAPlayer[port] = FALSE;
    }
    if (g_TeamManagement.zMenuActive[port] != 0) {
        if (g_d_GameSettings._06 != 2) {
            if (g_TeamManagement.zMenuOpen[port] != 0) {
                switch (g_TeamManagement.zMenuPage[port]) {
                case Z_MENU_PAGE_MAIN:
                    fn_80058E0C(scene, (u8)port);
                    break;
                case Z_MENU_PAGE_STAR_MOVES:
                    fn_80058B20(scene, (u8)port);
                    break;
                }
            } else {
                if (g_TeamManagement.zMenuPage[port] == Z_MENU_PAGE_MAIN) {
                    if ((TEAM_MANAGEMENT_RECORD_C(scene, 0x19A, port)->frame >> 16) > 5) {
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x19A, port)->frame = 0x00050000;
                    }
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x19A, port)->playMode = UI_PLAY_BACKWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x19C, port)->playMode = UI_PLAY_BACKWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x1AC, port)->playMode = UI_PLAY_BACKWARD;
                    completeCount = maybeCheckAndResetGrapicsElement(scene, port + 0x19A, 0) != 0;
                    completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x19C, 0) != 0;
                    completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x1AC, 0) != 0;
                    if (completeCount == 3) {
                        g_TeamManagement.zMenuActive[port] = FALSE;
                    }
                } else {
                    if ((TEAM_MANAGEMENT_RECORD_C(scene, 0x19A, port)->frame >> 16) > 5) {
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x19A, port)->frame = 0x00050000;
                    }
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x19A, port)->playMode = UI_PLAY_BACKWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x1C8, port)->playMode = UI_PLAY_BACKWARD;
                    if (isGraphicsElementDone(scene, port + 0x1C8, 0) == TRUE) {
                        g_TeamManagement.zMenuActive[port] = FALSE;
                    }
                }
                g_TeamManagement.zMenuPageLoaded[port] = FALSE;
            }
        } else {
            if (g_TeamManagement.zMenuOpen[g_TeamManagement.playerWhoPaused] != 0) {
                switch (g_TeamManagement.zMenuPage[port]) {
                case Z_MENU_PAGE_MAIN:
                    fn_80058644(scene);
                    break;
                case Z_MENU_PAGE_STAR_MOVES:
                    zMenuLoadGraphics(scene);
                    break;
                }
            } else {
                if (g_TeamManagement.zMenuPage[port] == Z_MENU_PAGE_MAIN) {
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
                        g_TeamManagement.zMenuActive[port] = FALSE;
                    }
                } else {
                    if ((TEAM_MANAGEMENT_RECORD(scene, 0x118)->frame >> 16) > 5) {
                        TEAM_MANAGEMENT_RECORD(scene, 0x118)->frame = 0x00050000;
                    }
                    TEAM_MANAGEMENT_RECORD(scene, 0x118)->playMode = UI_PLAY_BACKWARD;
                    TEAM_MANAGEMENT_RECORD(scene, 0x12F)->playMode = UI_PLAY_BACKWARD;
                    if (isGraphicsElementDone(scene, 0x12F, 0) == TRUE) {
                        g_TeamManagement.zMenuActive[g_TeamManagement.playerWhoPaused] = FALSE;
                    }
                }
                g_TeamManagement.zMenuPageLoaded[g_TeamManagement.playerWhoPaused] = FALSE;
            }
        }
    }
    if (g_TeamManagement.starMenuOpen == 0) {
        return;
    }
    if (g_TeamManagement.starMenuActive != 0) {
        switch (g_TeamManagement.starMenuDrawStep) {
        case STAR_MENU_DRAW_STEP_OPEN:
            starMissionRelated1(scene);
            break;
        case STAR_MENU_DRAW_STEP_CURSOR_MOVED:
            fn_800596D4(scene);
            break;
        case STAR_MENU_DRAW_STEP_CLOSE:
            if (g_TeamManagement.starMenuStepStarted == 0) {
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16E : 0x1D7))->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16A : 0x1D3))->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16C : 0x1D5))->playMode = UI_PLAY_BACKWARD;
                g_TeamManagement.starMenuStepStarted = TRUE;
            }
            if (g_TeamManagement.starMenuStepStarted != 0) {
                firstComplete = maybeCheckAndResetGrapicsElement(scene, (g_d_GameSettings._06 == 2 ? 0x16E : 0x1D7), 0) != 0;
                completeCount = firstComplete + (maybeCheckAndResetGrapicsElement(scene, (g_d_GameSettings._06 == 2 ? 0x16A : 0x1D3), 0) != 0);
                completeCount += maybeCheckAndResetGrapicsElement(scene, (g_d_GameSettings._06 == 2 ? 0x16C : 0x1D5), 0) != 0;
                if (completeCount == 3) {
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16A : 0x1D3))->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16B : 0x1D4))->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16C : 0x1D5))->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD(scene, (g_d_GameSettings._06 == 2 ? 0x16E : 0x1D7))->flags &= ~UI_FLAG_VISIBLE;
                    for (player = 0; player < 3; player++) {
                        text_freeBlock(g_TeamManagement.textBlocks[player]);
                    }
                    fn_8000F8F4(scene);
                    g_TeamManagement.starMenuActive = FALSE;
                    g_TeamManagement.starMenuDrawStep = STAR_MENU_DRAW_STEP_NONE;
                    g_TeamManagement.starMenuStepStarted = FALSE;
                }
            }
            break;
        }
    } else {
        firstComplete = maybeCheckAndResetGrapicsElement(scene, (g_d_GameSettings._06 == 2 ? 0x16A : 0x1D3), 0) != 0;
        if (firstComplete + (maybeCheckAndResetGrapicsElement(scene, (g_d_GameSettings._06 == 2 ? 0x16C : 0x1D5), 0) != 0) == 2) {
            g_TeamManagement.starMenuStepStarted = FALSE;
            g_TeamManagement.starMenuOpen = FALSE;
        }
    }
}

void teamManagementGraphics_fieldingAlignmentScreen(MenuScene* scene) {
    s32 position;
    s32 player;
    s32 team = *(s8*)&g_TeamManagement.playerWhoPaused;  // signed read; a (s8) cast shifts the register allocation

    for (player = 0; player < 9; player++) {
        CharacterStats* stats;
        BOOL isSuperstar;

        if (g_TeamManagement.teamMenuType[team] == TEAM_MENU_TYPE_SCOUT_FLAGS) {
            continue;
        }

        position = lineUpInfoStruct[team][player][2];
        stats = &inMemRoster[team][player];
        load_Icon(scene, 0x23 + position, 1, 0x83, stats->stats.CharID);
        TEAM_MANAGEMENT_RECORD_C(scene, 0x11, player)->flags &= ~UI_FLAG_VISIBLE;

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
        } else {
            isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
        }

        if ((u8)isSuperstar != 0 && !(team == 1 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x3E, position)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x47, position)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x47, position)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x47, position)->playMode = UI_PLAY_FORWARD;
        } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                   g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x3E, position)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x47, position)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x47, position)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x47, position)->playMode = UI_PLAY_STOP;
        } else {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x3E, position)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x47, position)->flags &= ~UI_FLAG_VISIBLE;
        }

        TEAM_MANAGEMENT_RECORD_C(scene, 0x35, player)->flags &= ~UI_FLAG_VISIBLE;
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && (s8)team != 0) {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, player)->elementIndex = 0x1E + (u8)((s8)Static_Stats_Tables.playerNumberByPort[0] == 0);
        } else {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, player)->elementIndex = 0x1E + (s8)Static_Stats_Tables.playerNumberByPort[team];
        }
    }
}

void teamManagementGraphics_battingOrderScreen(MenuScene* scene) {
    s32 team = (s8)g_TeamManagement.playerWhoPaused;
    s32 player;
    s32 orderFrame;

    for (player = 0, orderFrame = 0; player < 9; player++, orderFrame += 0x10000) {
        CharacterStats* stats = &inMemRoster[team][player];
        BOOL isSuperstar;

        TEAM_MANAGEMENT_RECORD_C(scene, 0x5A, player)->frame = orderFrame;
        TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, player)->flags &= ~UI_FLAG_VISIBLE;

        if (g_TeamManagement.teamMenuType[team] == TEAM_MENU_TYPE_FIELDER_SWAP) {
            load_Icon(scene, 0x63 + player, 1, 0x83, stats->stats.CharID);
            TEAM_MANAGEMENT_RECORD_C(scene, 0xAB, player)->frame = stats->stats.CharacterClass << 16;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x99, player)->frame = (stats->stats.BattingStance + stats->stats.FieldingArm * 2) << 16;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x134, player)->flags &= ~UI_FLAG_VISIBLE;
        } else {
            ChallengeTrackingStruct* tracking;
            s32 requiredFlags;
            s32 remainingFlags;
            s32 flag;
            load_Icon(scene, 0x63 + player, 1, 0x83, inMemRoster[1][player].stats.CharID);
            tracking = &g_Challenge.characters[inMemRoster[1][player].stats.CharID];
            requiredFlags = (s8)tracking->scoutFlagPointer->flagsRequired[g_Challenge.difficulty][g_Challenge.captain];
            remainingFlags = requiredFlags - (s8)tracking->scoutFlagsAchieved;
            for (flag = 0; flag < 5; flag++) {
                if (flag < requiredFlags && flag < remainingFlags) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x13D, flag + player * 5)->frame = 0;
                } else if (flag < requiredFlags) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x13D, flag + player * 5)->playMode = UI_PLAY_FORWARD;
                    if (g_d_GameSettings._06 == 2) {
                        sndFXStartEx(0x1B1, 0x7F, 0x3F, 0);
                    } else {
                        sndFXStartEx(0x1E6, 0x7F, 0x3F, 0);
                    }
                } else if (flag >= requiredFlags) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x13D, flag + player * 5)->flags &= ~UI_FLAG_VISIBLE;
                }
            }
            TEAM_MANAGEMENT_RECORD_C(scene, 0xAB, player)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x99, player)->flags &= ~UI_FLAG_VISIBLE;
        }

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
        } else {
            isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
        }

        if ((u8)isSuperstar != 0 && !(team == 1 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x7E, player)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->playMode = UI_PLAY_FORWARD;
        } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                   g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x7E, player)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->playMode = UI_PLAY_STOP;
        } else {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x7E, player)->flags &= ~UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->flags &= ~UI_FLAG_VISIBLE;
        }

        TEAM_MANAGEMENT_RECORD_C(scene, 0x75, player)->flags &= ~UI_FLAG_VISIBLE;
    }
}

void fn_8005B760(MenuScene* scene, s32 port) {
    if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
        s8 selection = g_TeamManagement.teamManagement_cursorPos[port];

        if (selection != 0) {
            s32 index = selection - 1;
            u8 lineupPosition = lineUpInfoStruct[port][index][2];
            s32 i;

            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x75, i)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x35, i)->flags &= ~UI_FLAG_VISIBLE;
            }

            if (g_TeamManagement.teamMenuType[port] == TEAM_MENU_TYPE_FIELDER_SWAP) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x23, (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
            } else {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x63, index)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x51, index)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x51, index)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x51, index)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, index)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, index)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, index)->playMode = UI_PLAY_FORWARD;
            }

            TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, index)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, index)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, index)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, index)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, index)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, index)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)lineupPosition)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, index);
            TEAM_MANAGEMENT_RECORD(scene, 0xE)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, 0xE)->playMode = UI_PLAY_STOP;
        }

        makeCursorUnmovable(port);
        gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
    }
}

void challengeTeamManagementRelated(MenuScene* scene) {
    s32 team;
    s32 player;
    s32 orderFrame;
    s32 teamBase;

    for (team = 0, teamBase = 0; team < 2; team++, teamBase += 9) {
        for (player = 0, orderFrame = 0; player < 9; player++, orderFrame += 0x10000) {
            CharacterStats* stats = &inMemRoster[team][player];

            load_Icon(scene, 0x40 + teamBase + player, 1, 0x83, stats->stats.CharID);
            TEAM_MANAGEMENT_RECORD_C(scene, 0x2E, teamBase + player)->frame = orderFrame;
            if (team == 0) {
                BOOL isSuperstar;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xD0, player)->frame = inMemRoster[0][player].stats.CharacterClass << 16;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xAC, player)->frame =
                    (inMemRoster[0][player].stats.FieldingArm * 2 + inMemRoster[0][player].stats.BattingStance) << 16;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x64, player)->flags &= ~UI_FLAG_VISIBLE;
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                    isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
                } else {
                    isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
                }
                if ((u8)isSuperstar != 0 && team == 0) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x76, player)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player)->playMode = UI_PLAY_FORWARD;
                } else {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player)->flags &= ~UI_FLAG_VISIBLE;
                }
            } else {
                s32 requiredFlags;
                s32 flag;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xD0, teamBase + player)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xAC, teamBase + player)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x88, teamBase + player)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x64, teamBase + player)->flags &= ~UI_FLAG_VISIBLE;
                requiredFlags = (s8)g_Challenge.characters[inMemRoster[1][player].stats.CharID].scoutFlagPointer->flagsRequired[g_Challenge.difficulty][g_Challenge.captain];
                for (flag = 0; flag < 5; flag++) {
                    if (flag < requiredFlags) {
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x16D, flag + player * 5)->frame = 0;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x16D, flag + player * 5)->playMode = UI_PLAY_STOP;
                    } else if (flag >= requiredFlags) {
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x16D, flag + player * 5)->flags &= ~UI_FLAG_VISIBLE;
                    }
                }
            }
        }
        TEAM_MANAGEMENT_RECORD_C(scene, 8, team)->frame = Static_Stats_Tables.teamName[team] << 16;
        TEAM_MANAGEMENT_RECORD_C(scene, 0xC, team)->frame = Static_Stats_Tables.teamName[team] << 16;
    }
}

void teamManagementGraphics_fieldingAlignmentInfo(MenuScene* scene) {
    s32 team;
    s32 player;

    for (team = 0; team < 2; team++) {
        for (player = 0; player < 9; player++) {
            CharacterStats* stats = &inMemRoster[team][player];
            BOOL isSuperstar;

            load_Icon(scene, 0x10A + lineUpInfoStruct[team][player][2] + team * 9, 1, 0x83, stats->stats.CharID);
            TEAM_MANAGEMENT_RECORD_C(scene, 0xE6, team * 9 + player)->flags &= ~UI_FLAG_VISIBLE;

            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
            } else {
                isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
            }

            if ((u8)isSuperstar != 0) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x140, lineUpInfoStruct[team][player][2] + team * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x152, lineUpInfoStruct[team][player][2] + team * 9)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x152, lineUpInfoStruct[team][player][2] + team * 9)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x152, lineUpInfoStruct[team][player][2] + team * 9)->playMode = UI_PLAY_FORWARD;
            } else if (superstarUnlocked[stats->stats.CharID] != 0) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x140, lineUpInfoStruct[team][player][2] + team * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x152, lineUpInfoStruct[team][player][2] + team * 9)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x152, lineUpInfoStruct[team][player][2] + team * 9)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x152, lineUpInfoStruct[team][player][2] + team * 9)->playMode = UI_PLAY_STOP;
            } else {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x152, lineUpInfoStruct[team][player][2] + team * 9)->flags &= ~UI_FLAG_VISIBLE;
            }

            TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, team * 9 + player)->flags &= ~UI_FLAG_VISIBLE;
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && team != 0) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, team * 9 + player)->elementIndex = 0x1E + (Static_Stats_Tables.playerNumberByPort[0] == 0);
            } else {
                TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, team * 9 + player)->elementIndex = 0x1E + (s8)Static_Stats_Tables.playerNumberByPort[team];
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

            load_Icon(scene, 0x40 + player + team * 9, 1, 0x83, stats->stats.CharID);
            TEAM_MANAGEMENT_RECORD_C(scene, 0x2E, player + team * 9)->frame = orderFrame;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xD0, player + team * 9)->frame = stats->stats.CharacterClass << 16;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xAC, player + team * 9)->frame = (stats->stats.BattingStance + stats->stats.FieldingArm * 2) << 16;

            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                isSuperstar = g_Challenge.charIsSuperstar[stats->stats.CharID];
            } else {
                isSuperstar = Static_Stats_Tables.charIsStarred[team][player];
            }

            if ((u8)isSuperstar != 0) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x76, player + team * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player + team * 9)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player + team * 9)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player + team * 9)->playMode = UI_PLAY_FORWARD;
            } else if (superstarUnlocked[stats->stats.CharID] != 0) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x76, player + team * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player + team * 9)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player + team * 9)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player + team * 9)->playMode = UI_PLAY_STOP;
            } else {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x88, player + team * 9)->flags &= ~UI_FLAG_VISIBLE;
            }

            TEAM_MANAGEMENT_RECORD_C(scene, 0x64, player + team * 9)->flags &= ~UI_FLAG_VISIBLE;
        }

        TEAM_MANAGEMENT_RECORD_C(scene, 8, team)->frame =
            Static_Stats_Tables.teamName[team] << 16;
        TEAM_MANAGEMENT_RECORD_C(scene, 0xC, team)->frame =
            Static_Stats_Tables.teamName[team] << 16;
    }
}

void fn_8005C5C4(MenuScene* scene, s32 port) {
    if (!isAnimStepStart(gameSetUpStep[0x37 + port])) {
        return;
    }

    if (g_d_GameSettings._06 == 2) {
        TEAM_MANAGEMENT_RECORD(scene, 0)->frame = 0x00140000;
        TEAM_MANAGEMENT_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        TEAM_MANAGEMENT_RECORD(scene, 0)->frame = 0x00140000;
        TEAM_MANAGEMENT_RECORD(scene, 1)->frame = 0x00140000;
        TEAM_MANAGEMENT_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
        TEAM_MANAGEMENT_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        if (port != 0) {
            TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x00140000;
            TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_BACKWARD;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x001E0000;
            TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
        }
    } else {
        if (((u32)TEAM_MANAGEMENT_RECORD(scene, port)->frame >> 16) == 0x1E) {
            TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x001E0000;
            TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x00140000;
            TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_BACKWARD;
        }
    }

    TEAM_MANAGEMENT_RECORD_C(scene, 0x16, port)->frame = 0x000A0000;
    TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->playMode = UI_PLAY_BACKWARD;
    TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->frame = 0x00140000;
    TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->playMode = UI_PLAY_FORWARD;
    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
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

            if (g_TeamManagement.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
                if (g_d_GameSettings._06 != 2) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x52, rosterIndex + (port * 9))->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x52, rosterIndex + (port * 9))->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x64, rosterIndex + (port * 9))->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x64, rosterIndex + (port * 9))->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x64, rosterIndex + (port * 9))->playMode = UI_PLAY_FORWARD;
                } else {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x35, lineUpInfoStruct[port][rosterIndex][2])->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x35, lineUpInfoStruct[port][rosterIndex][2])->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x35, lineUpInfoStruct[port][rosterIndex][2])->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x35, lineUpInfoStruct[port][rosterIndex][2])->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, rosterIndex)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, rosterIndex)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, rosterIndex)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x75, rosterIndex)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x75, rosterIndex)->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x75, rosterIndex)->playMode = UI_PLAY_FORWARD;
                }
            } else {
                if (g_d_GameSettings._06 != 2) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, lineUpInfoStruct[port][rosterIndex][2] + (port * 9))->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, lineUpInfoStruct[port][rosterIndex][2] + (port * 9))->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, lineUpInfoStruct[port][rosterIndex][2] + (port * 9))->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, lineUpInfoStruct[port][rosterIndex][2] + (port * 9))->playMode = UI_PLAY_FORWARD;
                } else {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x35, lineUpInfoStruct[port][rosterIndex][2])->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x35, lineUpInfoStruct[port][rosterIndex][2])->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x35, lineUpInfoStruct[port][rosterIndex][2])->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x35, lineUpInfoStruct[port][rosterIndex][2])->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, rosterIndex)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, rosterIndex)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, rosterIndex)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x75, rosterIndex)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x75, rosterIndex)->elementIndex = 0x2B;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x75, rosterIndex)->playMode = UI_PLAY_FORWARD;
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

    if (!isAnimStepStart(gameSetUpStep[0x37 + port])) {
        return;
    }
    selection = g_TeamManagement.teamManagement_cursorPos[port] - 1;
    swapSelection = g_TeamManagement.charSelectedToBeSwappedCharID[port];
    position = lineUpInfoStruct[port][selection][2];
    swapPosition = lineUpInfoStruct[port][swapSelection][2];

    if (g_TeamManagement.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {

        if (selection != swapSelection) {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, swapSelection + (port * 9))->frame = 0x000A0000;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, swapSelection + (port * 9))->playMode = UI_PLAY_BACKWARD;
        }
        TEAM_MANAGEMENT_RECORD_C(scene, 0x40, swapSelection + (port * 9))->playMode = UI_PLAY_BACKWARD;
        load_Icon(scene, 0x40 + selection + (port * 9), 1, 0x83, inMemRoster[port][selection].stats.CharID);
        load_Icon(scene, 0x40 + swapSelection + (port * 9), 1, 0x83, inMemRoster[port][swapSelection].stats.CharID);
        TEAM_MANAGEMENT_RECORD_C(scene, 0xD0, selection + (port * 9))->frame = inMemRoster[port][selection].stats.CharacterClass << 16;
        TEAM_MANAGEMENT_RECORD_C(scene, 0xD0, swapSelection + (port * 9))->frame = inMemRoster[port][swapSelection].stats.CharacterClass << 16;
        TEAM_MANAGEMENT_RECORD_C(scene, 0xAC, selection + (port * 9))->frame =
        (inMemRoster[port][selection].stats.FieldingArm * 2 + inMemRoster[port][selection].stats.BattingStance) << 16;
        TEAM_MANAGEMENT_RECORD_C(scene, 0xAC, swapSelection + (port * 9))->frame =
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
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76), player)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76), player)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88), player)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88), player)->frame = 0x000F0000;
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88), player)->playMode = UI_PLAY_FORWARD;
            } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76), player)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76), player)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88), player)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88), player)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88), player)->playMode = UI_PLAY_STOP;
            } else {
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76), player)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88), player)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x75 : (port * 9) + 0x64), player)->flags &= ~UI_FLAG_VISIBLE;
        }
        TEAM_MANAGEMENT_RECORD_C(scene, 0x64, selection + (port * 9))->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD_C(scene, 0x64, selection + (port * 9))->elementIndex = 0x2A;
        TEAM_MANAGEMENT_RECORD_C(scene, 0x64, selection + (port * 9))->playMode = UI_PLAY_FORWARD;
        fn_8005C830(scene, port, selection);
    } else {
        if (g_d_GameSettings._06 != 2) {

            load_Icon(scene, 0x10A + (s8)swapPosition + (port * 9), 1, 0x83, inMemRoster[port][swapSelection].stats.CharID);
            load_Icon(scene, 0x10A + (s8)position + (port * 9), 1, 0x83, inMemRoster[port][selection].stats.CharID);
            TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)position + (port * 9))->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)position + (port * 9))->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)swapPosition + (port * 9))->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)swapPosition + (port * 9))->playMode = UI_PLAY_FORWARD;
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
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x3E : (port * 9) + 0x140), (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x3E : (port * 9) + 0x140), (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152), (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152), (s8)lineupPosition)->frame = 0x000F0000;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152), (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
                } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                    g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x3E : (port * 9) + 0x140), (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x3E : (port * 9) + 0x140), (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152), (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152), (s8)lineupPosition)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152), (s8)lineupPosition)->playMode = UI_PLAY_STOP;
                } else {
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x3E : (port * 9) + 0x140), (s8)lineupPosition)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x47 : (port * 9) + 0x152), (s8)lineupPosition)->flags &= ~UI_FLAG_VISIBLE;
                }
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, player + (port * 9))->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)swapPosition + (port * 9))->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)swapPosition + (port * 9))->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)swapPosition + (port * 9))->playMode = UI_PLAY_FORWARD;
        } else {

            load_Icon(scene, 0x23 + (s8)swapPosition, 1, 0x83, inMemRoster[port][swapSelection].stats.CharID);
            load_Icon(scene, 0x23 + (s8)position, 1, 0x83, inMemRoster[port][selection].stats.CharID);
            TEAM_MANAGEMENT_RECORD_C(scene, 0x23, (s8)position)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, (s8)position)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x23, (s8)swapPosition)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, (s8)swapPosition)->playMode = UI_PLAY_FORWARD;
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
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x3E, (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x3E, (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x47, (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x47, (s8)lineupPosition)->frame = 0x000F0000;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x47, (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x7E, player)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x7E, player)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->frame = 0x000F0000;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->playMode = UI_PLAY_FORWARD;
                } else if (superstarUnlocked[stats->stats.CharID] != 0 &&
                    g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x3E, (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x3E, (s8)lineupPosition)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x47, (s8)lineupPosition)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x47, (s8)lineupPosition)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x47, (s8)lineupPosition)->playMode = UI_PLAY_STOP;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x7E, player)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x7E, player)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x87, player)->playMode = UI_PLAY_STOP;
                } else {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x3E, (s8)lineupPosition)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x47, (s8)lineupPosition)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x7E : (port * 9) + 0x76), player)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, (g_d_GameSettings._06 == 2 ? 0x87 : (port * 9) + 0x88), player)->flags &= ~UI_FLAG_VISIBLE;
                }
                TEAM_MANAGEMENT_RECORD_C(scene, 0x35, player)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x75, player)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, swapSelection)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, swapSelection)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, swapSelection)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)swapPosition)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)swapPosition)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)swapPosition)->playMode = UI_PLAY_FORWARD;
        }
        fn_8005C830(scene, port, swapSelection);
        g_TeamManagement.teamManagement_cursorPos[port] = lineupOrderChangeRelated((u8)port, lineUpInfoStruct[port][swapSelection][2]);
    }
    g_TeamManagement.charSelectedToBeSwappedCharID[port] = (u8)CHAR_ID_NONE;
    gameSetUpStep[0x5D + port] = 0;
    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
}


void fn_8005DE14(MenuScene* scene, s32 port) {
    s32 selection;
    s32 previousSelection;
    s32 swapSelection;
    u8 position;
    u8 previousPosition;
    u8 swapPosition;
    s32 i;

    if (!isAnimStepStart(gameSetUpStep[0x37 + port])) {
        return;
    }
    selection = (s8)(g_TeamManagement.teamManagement_cursorPos[port] - 1);
    previousSelection = (s8)(g_TeamManagement.teamManagement_prevCursorPos[port] - 1);
    swapSelection = (s8)g_TeamManagement.charSelectedToBeSwappedCharID[port];

    if (g_TeamManagement.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
        if (g_d_GameSettings._06 != 2) {
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x64, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD_C(scene, 0x40, selection + port * 9)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x40, selection + port * 9)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, selection + port * 9)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, selection + port * 9)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x52, selection + port * 9)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x52, selection + port * 9)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x64, selection + port * 9)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x64, selection + port * 9)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x64, selection + port * 9)->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            TEAM_MANAGEMENT_RECORD_C(scene, 0x40, previousSelection + port * 9)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x40, previousSelection + port * 9)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, previousSelection + port * 9)->frame = 0x000A0000;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, previousSelection + port * 9)->playMode = UI_PLAY_BACKWARD;
            if (swapSelection != CHAR_ID_NONE) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, swapSelection + port * 9)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, swapSelection + port * 9)->playMode = UI_PLAY_STOP;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x40, swapSelection + port * 9)->playMode = UI_PLAY_FORWARD;
            }
        } else {
            position = lineUpInfoStruct[port][selection][2];
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x75, i)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x35, i)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD_C(scene, 0x63, selection)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x63, selection)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x51, selection)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x51, selection)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, selection)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, selection)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, selection)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, selection)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, selection)->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            TEAM_MANAGEMENT_RECORD_C(scene, 0x63, previousSelection)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x63, previousSelection)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x51, previousSelection)->frame = 0x000A0000;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x51, previousSelection)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)position)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)position)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)position)->playMode = UI_PLAY_FORWARD;
            if (swapSelection != CHAR_ID_NONE) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x51, swapSelection)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x51, swapSelection)->playMode = UI_PLAY_STOP;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x63, swapSelection)->playMode = UI_PLAY_FORWARD;
            }
        }
    } else {
        position = lineUpInfoStruct[port][selection][2];
        previousPosition = lineUpInfoStruct[port][previousSelection][2];
        swapPosition = lineUpInfoStruct[port][swapSelection][2];
        if (g_d_GameSettings._06 != 2) {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)position + port * 9)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)position + port * 9)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xE6, (s8)position + port * 9)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)previousPosition + port * 9)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)previousPosition + port * 9)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xE6, (s8)previousPosition + port * 9)->flags &= ~UI_FLAG_VISIBLE;
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)position + port * 9)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)position + port * 9)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)position + port * 9)->playMode = UI_PLAY_FORWARD;
            fn_8005C830(scene, port, selection);
            if (swapSelection != CHAR_ID_NONE) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)swapPosition + port * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)swapPosition + port * 9)->playMode = UI_PLAY_FORWARD;
            }
        } else {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x23, (s8)position)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, (s8)position)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x11, (s8)position)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x23, (s8)previousPosition)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, (s8)previousPosition)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x11, (s8)previousPosition)->flags &= ~UI_FLAG_VISIBLE;
            for (i = 0; i < 9; i++) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x35, i)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x75, i)->flags &= ~UI_FLAG_VISIBLE;
            }
            TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, selection)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, selection)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x6C, selection)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, selection)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, selection)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, selection)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)position)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)position)->elementIndex = 0x2A;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, (s8)position)->playMode = UI_PLAY_FORWARD;
            if (swapSelection != CHAR_ID_NONE) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x23, (s8)swapPosition)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, (s8)swapPosition)->playMode = UI_PLAY_FORWARD;
            }
            fn_8005C830(scene, port, selection);
        }
    }
    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
}

void fn_8005E9D8(MenuScene* scene, s32 port) {
    s8 currentSelection = g_TeamManagement.teamManagement_cursorPos[port];
    s8 previousSelection = g_TeamManagement.teamManagement_prevCursorPos[port];

    if (currentSelection != previousSelection) {
        fn_8005DE14(scene, port);
        if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
            makeCursorMovable(port);
            gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
        }
    } else if (g_TeamManagement.charSelectedToBeSwapped[port] != 0) {
        if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
            s32 selection = g_TeamManagement.charSelectedToBeSwappedCharID[port];
            u8 mode = g_TeamManagement.rosterView[port];
            u8 position = ((u8*)lineUpInfoStruct)[port * 0x24 + (u8)selection * 4 + 2];

            if (mode == ROSTER_VIEW_BATTING_ORDER) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, selection + port * 9)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, selection + port * 9)->playMode = UI_PLAY_STOP;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x40, selection + port * 9)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x40, selection + port * 9)->playMode = UI_PLAY_FORWARD;
            } else if (g_d_GameSettings._06 != 2) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)position + port * 9)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)position + port * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)position + port * 9)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)position + port * 9)->playMode = UI_PLAY_FORWARD;
            } else {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x23, (s8)position)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x23, (s8)position)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, (s8)position)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, (s8)position)->playMode = UI_PLAY_FORWARD;
            }
            gameSetUpStep[0x5D + port] = 0;
            gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
        }
    } else if (g_TeamManagement.charSelectedToBeSwapped[port] == 0) {
        fn_8005CCE4(scene, port);
    }
}

void fn_8005EC88(MenuScene* scene, s32 port) {
    u8 lineupPosition;
    s32 i;

    if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
        if (g_TeamManagement.teamManagement_cursorPos[port] != 0) {
            s32 index = (s8)g_TeamManagement.teamManagement_cursorPos[port] - 1;
            lineupPosition = lineUpInfoStruct[port][index][2];
            for (i = 0; i < 9; i += 3) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x64, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x65, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12F, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x66, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x130, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
            }

            switch (g_TeamManagement.rosterView[port]) {
            case ROSTER_VIEW_BATTING_ORDER:
                TEAM_MANAGEMENT_RECORD_C(scene, 0x40, index + port * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, index + port * 9)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, index + port * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x52, index + port * 9)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x52, index + port * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x64, index + port * 9)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x64, index + port * 9)->elementIndex = 0x2A;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x64, index + port * 9)->playMode = UI_PLAY_FORWARD;
                fn_8005C830(scene, port, index);
                break;
            case ROSTER_VIEW_DEFENSIVE_ALIGNMENT:
                TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)lineupPosition + port * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)lineupPosition + port * 9)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)lineupPosition + port * 9)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)lineupPosition + port * 9)->elementIndex = 0x2A;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)lineupPosition + port * 9)->playMode = UI_PLAY_FORWARD;
                fn_8005C830(scene, port, index);
                break;
            }
        }

        TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->frame = 0x000A0000;
        TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->playMode = UI_PLAY_BACKWARD;
        makeCursorUnmovable(port);
        gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
    }
}

void fn_8005F068(MenuScene* scene, s32 port) {
    s8 selection;
    u8 selectedPosition;
    s8 swapSelection;
    u8 swapPosition;
    s32 i;

    if (!isAnimStepStart(gameSetUpStep[0x37 + port])) {
        return;
    }

    selection = (s8)(g_TeamManagement.teamManagement_cursorPos[port] - 1);
    selectedPosition = lineUpInfoStruct[port][selection][2];
    if (g_TeamManagement.charSelectedToBeSwappedCharID[port] != (u8)CHAR_ID_NONE) {
        swapSelection = g_TeamManagement.charSelectedToBeSwappedCharID[port];
        swapPosition = lineUpInfoStruct[port][swapSelection][2];
    }

    switch (g_TeamManagement.rosterView[port]) {
    case ROSTER_VIEW_BATTING_ORDER: {
            if (g_TeamManagement.prevRosterView[port] == ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
                TEAM_MANAGEMENT_RECORD_C(scene, 0x14, port)->frame = 0x00140000;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x14, port)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, port)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xE2, port)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xE4, port)->playMode = UI_PLAY_BACKWARD;
                for (i = 0; i < 9; i++) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x64, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, i + port * 9)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, i + port * 9)->playMode = UI_PLAY_STOP;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x40, i + port * 9)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x40, i + port * 9)->playMode = UI_PLAY_STOP;
                }
                if (selection >= 0 && selection < 9) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, selection + port * 9)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, selection + port * 9)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x52, selection + port * 9)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x52, selection + port * 9)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x64, selection + port * 9)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x64, selection + port * 9)->elementIndex = 0x2A;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x64, selection + port * 9)->playMode = UI_PLAY_FORWARD;
                    fn_8005C830(scene, port, selection);
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x40, selection + port * 9)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x40, selection + port * 9)->playMode = UI_PLAY_FORWARD;
                    if (g_TeamManagement.charSelectedToBeSwappedCharID[port] != (u8)CHAR_ID_NONE) {
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, swapSelection + port * 9)->frame = 0x000A0000;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, swapSelection + port * 9)->playMode = UI_PLAY_STOP;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x40, swapSelection + port * 9)->frame = 0;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x40, swapSelection + port * 9)->playMode = UI_PLAY_FORWARD;
                    }
                }
            }
            break;
        }
    case ROSTER_VIEW_DEFENSIVE_ALIGNMENT: {
            if (g_TeamManagement.prevRosterView[port] != ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
                for (i = 0; i < 9; i++) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, i + port * 9)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, i + port * 9)->playMode = UI_PLAY_STOP;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, i + port * 9)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, i + port * 9)->playMode = UI_PLAY_STOP;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0xE6, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, i + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                }
                TEAM_MANAGEMENT_RECORD_C(scene, 0x14, port)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x14, port)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, port)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xE2, port)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xE4, port)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xE2, port)->flags |= UI_FLAG_VISIBLE;
                TEAM_MANAGEMENT_RECORD_C(scene, 0xE4, port)->flags |= UI_FLAG_VISIBLE;
                if (selection >= 0 && selection < 9) {
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)selectedPosition + port * 9)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)selectedPosition + port * 9)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0xE6, (s8)selectedPosition + port * 9)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)selectedPosition + port * 9)->flags |= UI_FLAG_VISIBLE;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)selectedPosition + port * 9)->elementIndex = 0x2A;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, (s8)selectedPosition + port * 9)->playMode = UI_PLAY_FORWARD;
                    fn_8005C830(scene, port, selection);
                    if (g_TeamManagement.charSelectedToBeSwappedCharID[port] != (u8)CHAR_ID_NONE) {
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)swapPosition + port * 9)->playMode = UI_PLAY_FORWARD;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)swapPosition + port * 9)->playMode = UI_PLAY_FORWARD;
                    }
                }
            }
            break;
        }
    }

    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
}

void fn_8005F734(MenuScene* scene, s32 port) {
    if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
        TEAM_MANAGEMENT_RECORD(scene, port)->elementIndex = 0x49;
        TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x00320000;
        TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_BACKWARD;

        TEAM_MANAGEMENT_RECORD_C(scene, 2, port)->elementIndex = 0x52;
        TEAM_MANAGEMENT_RECORD_C(scene, 2, port)->frame = 0;
        TEAM_MANAGEMENT_RECORD_C(scene, 2, port)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD_C(scene, 4, port)->frame = 0;
        TEAM_MANAGEMENT_RECORD_C(scene, 4, port)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD_C(scene, 6, port)->frame = 0x000E0000;
        TEAM_MANAGEMENT_RECORD_C(scene, 6, port)->playMode = UI_PLAY_FORWARD;

        TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->frame = 0;
        TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->playMode = UI_PLAY_FORWARD;

        TEAM_MANAGEMENT_RECORD_C(scene, 0x14, port)->frame = 0;
        TEAM_MANAGEMENT_RECORD_C(scene, 0x14, port)->playMode = UI_PLAY_FORWARD;

        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port == 0) {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->frame = 0x001E0000;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->playMode = UI_PLAY_STOP;
        } else {
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->playMode = UI_PLAY_FORWARD;
        }

        makeCursorUnmovable(port);
        gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
    }
}

void fn_8005F9D0(MenuScene* scene, s32 port) {
    s32 requiredCount;
    s32 completeCount;
    u8* steps = &gameSetUpStep[0x37];

    if (!isAnimStepPlaying(steps[port])) {
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
        g_TeamManagement.entryAnimDone[port] = TRUE;
        if (g_TeamManagement.entryAnimDone[0] == 0 || g_TeamManagement.entryAnimDone[1] == 0) {
            return;
        }
        g_TeamManagement.entryAnimDone[0] = FALSE;
        g_TeamManagement.entryAnimDone[1] = FALSE;
        makeCursorMovable(0);
        makeCursorMovable(1);
        gameSetUpStep[0x37] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
        gameSetUpStep[0x38] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            updateCharacterSelectProcessCode(0, CHAR_SELECT_PROCESS_TM_SHOW_SCOUT_FLAGS);
        }
    } else {
        makeCursorMovable(port);
        steps[port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
    }
}

void fn_8005FCA0(MenuScene* scene, s32 port) {
    if (!isAnimStepStart(gameSetUpStep[0x37 + port])) {
        return;
    }

    TEAM_MANAGEMENT_RECORD_C(scene, 4, port)->frame = 0;
    TEAM_MANAGEMENT_RECORD_C(scene, 4, port)->playMode = UI_PLAY_FORWARD;
    TEAM_MANAGEMENT_RECORD_C(scene, 6, port)->frame = 0x000E0000;
    TEAM_MANAGEMENT_RECORD_C(scene, 6, port)->playMode = UI_PLAY_FORWARD;
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port != 0) {
            TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 2, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 2, port)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->frame = 0x001E0000;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->playMode = UI_PLAY_BACKWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x14, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x14, port)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->playMode = UI_PLAY_STOP;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->playMode = UI_PLAY_FORWARD;
        } else {
            TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 2, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 2, port)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 2, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 2, port)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->playMode = UI_PLAY_FORWARD;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x14, port)->frame = 0;
            TEAM_MANAGEMENT_RECORD_C(scene, 0x14, port)->playMode = UI_PLAY_FORWARD;
        }
    } else {
        TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->flags |= UI_FLAG_VISIBLE;
        TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->frame = 0;
        TEAM_MANAGEMENT_RECORD_C(scene, 0xA, port)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, 0x12)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, 0x12)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, 0x14)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, 0x14)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, 2)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
        TEAM_MANAGEMENT_RECORD(scene, 3)->frame = 0;
        TEAM_MANAGEMENT_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
        if (g_TeamManagement.unkCF70 == 0) {
            TEAM_MANAGEMENT_RECORD(scene, 0x1D2)->flags |= UI_FLAG_VISIBLE;
            TEAM_MANAGEMENT_RECORD(scene, 0x1D2)->frame = 0x000A0000;
            TEAM_MANAGEMENT_RECORD(scene, 0x1D2)->playMode = UI_PLAY_FORWARD;
        }
    }

    makeCursorUnmovable(port);
    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
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
        case CHAR_SELECT_PROCESS_TM_LOAD:
            if (g_d_GameSettings._06 != 2) {
                fn_8005FCA0(scene, port);
                fn_8005F9D0(scene, port);
            } else {
                if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
                    TEAM_MANAGEMENT_RECORD(scene, 0)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                    if (g_TeamManagement.teamMenuType[port] != TEAM_MENU_TYPE_BATTER_SWAP) {
                        TEAM_MANAGEMENT_RECORD(scene, 1)->frame = 0;
                        TEAM_MANAGEMENT_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
                    }
                    TEAM_MANAGEMENT_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
                    TEAM_MANAGEMENT_RECORD(scene, 0xE)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, 0xE)->playMode = UI_PLAY_FORWARD;
                    makeCursorUnmovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
                }
                if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                    requiredCount = 1;
                    completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0x14) != 0;
                    if (g_TeamManagement.teamMenuType[port] != TEAM_MENU_TYPE_BATTER_SWAP) {
                        requiredCount = 2;
                        completeCount += maybeCheckAndResetGrapicsElement(scene, 1, 0x14) != 0;
                    }
                    if (completeCount == requiredCount) {
                        makeCursorMovable(port);
                        gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                    }
                }
            }
            break;
        case 0x39:
            if (g_d_GameSettings._06 == 2) {
                break;
            }
            fn_8005F734(scene, port);
            if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
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
                        g_TeamManagement.entryAnimDone[port] = TRUE;
                        if (g_TeamManagement.entryAnimDone[0] != 0 && g_TeamManagement.entryAnimDone[1] != 0) {
                            g_TeamManagement.entryAnimDone[1] = FALSE;
                            g_TeamManagement.entryAnimDone[0] = FALSE;
                            makeCursorMovable(0);
                            makeCursorMovable(1);
                            gameSetUpStep[0x37] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                            gameSetUpStep[0x38] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                        }
                    } else {
                        makeCursorMovable(port);
                        gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                    }
                }
            }
            break;
        case CHAR_SELECT_PROCESS_TM_RETURN_TO_CSS:
            if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
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
                gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
            }
            if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
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
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            }
            break;
        case CHAR_SELECT_PROCESS_TM_CURSOR_MOVE:
            fn_8005E9D8(scene, port);
            break;
        case CHAR_SELECT_PROCESS_TM_CHANGE_ROSTER_VIEW:
            if (g_d_GameSettings._06 == 2) {
                break;
            }
            fn_8005F068(scene, port);
            if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                completeCount = 0;
                requiredCount = 0;
                switch (g_TeamManagement.rosterView[port]) {
                case ROSTER_VIEW_BATTING_ORDER:
                    if (g_TeamManagement.prevRosterView[port] == ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
                        requiredCount = 1;
                        completeCount = maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0xA) != 0;
                    }
                    break;
                case ROSTER_VIEW_DEFENSIVE_ALIGNMENT:
                    if (g_TeamManagement.prevRosterView[port] != ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
                        requiredCount = 1;
                        completeCount = maybeCheckAndResetGrapicsElement(scene, port + 0x14, 0x14) != 0;
                    }
                    break;
                }
                if (completeCount == requiredCount) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            }
            break;
        case CHAR_SELECT_PROCESS_TM_CURSOR_ENTER_ROSTER:
            if (g_d_GameSettings._06 != 2) {
                fn_8005EC88(scene, port);
                if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            } else {
                fn_8005B760(scene, port);
                if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            }
            break;
        case CHAR_SELECT_PROCESS_TM_CURSOR_TO_CONFIRM:
            if (g_d_GameSettings._06 != 2) {
                if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
                    if ((s8)g_TeamManagement.teamManagement_cursorPos[port] == 0) {
                        previousSelection = (s8)(g_TeamManagement.teamManagement_prevCursorPos[port] - 1);
                        position = lineUpInfoStruct[port][previousSelection][2];
                        switch (g_TeamManagement.rosterView[port]) {
                        case ROSTER_VIEW_BATTING_ORDER:
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x40, previousSelection + port * 9)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, previousSelection + port * 9)->frame = 0x000A0000;
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, previousSelection + port * 9)->playMode = UI_PLAY_BACKWARD;
                            for (player = 0; player < 9; player++) {
                                TEAM_MANAGEMENT_RECORD_C(scene, 0x64, player + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                            }
                            break;
                        case ROSTER_VIEW_DEFENSIVE_ALIGNMENT:
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)position + port * 9)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)position + port * 9)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD_C(scene, 0xE6, (s8)position + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                            for (player = 0; player < 9; player++) {
                                TEAM_MANAGEMENT_RECORD_C(scene, 0x12E, player + port * 9)->flags &= ~UI_FLAG_VISIBLE;
                            }
                            break;
                        }
                    }
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->frame = 0;
                    TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->playMode = UI_PLAY_FORWARD;
                    makeCursorUnmovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
                }
                if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            } else {
                if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
                    switch (g_TeamManagement.rosterView[port]) {
                    case ROSTER_VIEW_BATTING_ORDER:
                        previousSelection = (s8)(g_TeamManagement.teamManagement_prevCursorPos[port] - 1);
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x63, previousSelection)->playMode = UI_PLAY_BACKWARD;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x51, previousSelection)->frame = 0x000A0000;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x51, previousSelection)->playMode = UI_PLAY_BACKWARD;
                        for (player = 0; player < 9; player++) {
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, player)->flags &= ~UI_FLAG_VISIBLE;
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, player)->flags &= ~UI_FLAG_VISIBLE;
                        }
                        break;
                    case ROSTER_VIEW_DEFENSIVE_ALIGNMENT:
                        previousSelection = (s8)(g_TeamManagement.teamManagement_prevCursorPos[port] - 1);
                        position = lineUpInfoStruct[port][previousSelection][2];
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x23, (s8)position)->playMode = UI_PLAY_BACKWARD;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, (s8)position)->playMode = UI_PLAY_BACKWARD;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x11, (s8)position)->flags &= ~UI_FLAG_VISIBLE;
                        for (player = 0; player < 9; player++) {
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x35, player)->flags &= ~UI_FLAG_VISIBLE;
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x75, player)->flags &= ~UI_FLAG_VISIBLE;
                        }
                        break;
                    }
                    TEAM_MANAGEMENT_RECORD(scene, 0xE)->frame = 0;
                    TEAM_MANAGEMENT_RECORD(scene, 0xE)->playMode = UI_PLAY_FORWARD;
                    makeCursorUnmovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
                }
                if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            }
            break;
        case CHAR_SELECT_PROCESS_TM_1P_TO_CPU_TEAM:
            if (g_d_GameSettings._06 == 2) {
                break;
            }
            if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
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
                gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
            }
            if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0x1E) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 1, 0x14) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x12, 0x14) != 0;
                requiredCount = 4;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x13, 0xA) != 0;
                if (completeCount == requiredCount) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            }
            break;
        case CHAR_SELECT_PROCESS_TM_1P_TO_OWN_TEAM:
            if (g_d_GameSettings._06 == 2) {
                break;
            }
            if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
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
                gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
            }
            if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                completeCount = maybeCheckAndResetGrapicsElement(scene, 0, 0x14) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 1, 0x1E) != 0;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x12, 0xA) != 0;
                requiredCount = 4;
                completeCount += maybeCheckAndResetGrapicsElement(scene, 0x13, 0x14) != 0;
                if (completeCount == requiredCount) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            }
            break;
        case CHAR_SELECT_PROCESS_TM_WAIT_FOR_OTHER_TEAM:
            if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
                TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x00140000;
                TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->frame = 0x000A0000;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->playMode = UI_PLAY_FORWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
            }
            if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                completeCount = fn_80042D68(scene, port, 0x1E) != 0;
                requiredCount = 2;
                completeCount += fn_80042D68(scene, port + 0x12, 0x14) != 0;
                if (completeCount == requiredCount) {
                    g_TeamManagement.waitingForOtherTeam[port] = FALSE;
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            }
            break;
        case CHAR_SELECT_PROCESS_TM_CANCEL_CONFIRM:
            if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
                TEAM_MANAGEMENT_RECORD(scene, port)->frame = 0x001E0000;
                TEAM_MANAGEMENT_RECORD(scene, port)->playMode = UI_PLAY_BACKWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->frame = 0;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x18, port)->playMode = UI_PLAY_FORWARD;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->frame = 0x00140000;
                TEAM_MANAGEMENT_RECORD_C(scene, 0x12, port)->playMode = UI_PLAY_BACKWARD;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
            }
            if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                completeCount = maybeCheckAndResetGrapicsElement(scene, port, 0x14) != 0;
                requiredCount = 2;
                completeCount += maybeCheckAndResetGrapicsElement(scene, port + 0x12, 0xA) != 0;
                if (completeCount == requiredCount) {
                    makeCursorMovable(port);
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            }
            break;
        case CHAR_SELECT_PROCESS_TM_EXIT:
            fn_8005C5C4(scene, port);
            if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
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
                    gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
                }
            }
            break;
        case CHAR_SELECT_PROCESS_TM_CANCEL_SWAP:
            if (isAnimStepStart(gameSetUpStep[0x37 + port])) {
                selection = (s8)(g_TeamManagement.teamManagement_cursorPos[port] - 1);
                previousSelection = (s8)g_TeamManagement.charSelectedToBeSwappedCharID[port];
                if (g_TeamManagement.rosterView[port] == ROSTER_VIEW_BATTING_ORDER) {
                    if (previousSelection != CHAR_ID_NONE && previousSelection != selection) {
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, previousSelection + port * 9)->frame = 0x000A0000;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x1C, previousSelection + port * 9)->playMode = UI_PLAY_BACKWARD;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x40, previousSelection + port * 9)->frame = 0x000A0000;
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x40, previousSelection + port * 9)->playMode = UI_PLAY_BACKWARD;
                    }
                } else {
                    position = lineUpInfoStruct[port][selection][2];
                    swapPosition = lineUpInfoStruct[port][previousSelection][2];
                    if (g_d_GameSettings._06 != 2) {
                        if (previousSelection != CHAR_ID_NONE && (s8)swapPosition != (s8)position) {
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x10A, (s8)swapPosition + port * 9)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD_C(scene, 0xF8, (s8)swapPosition + port * 9)->playMode = UI_PLAY_BACKWARD;
                        }
                    } else {
                        if (previousSelection != CHAR_ID_NONE && (s8)swapPosition != (s8)position) {
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x23, (s8)swapPosition)->playMode = UI_PLAY_BACKWARD;
                            TEAM_MANAGEMENT_RECORD_C(scene, 0x1A, (s8)swapPosition)->playMode = UI_PLAY_BACKWARD;
                        }
                    }
                }
                g_TeamManagement.charSelectedToBeSwappedCharID[port] = (u8)CHAR_ID_NONE;
                makeCursorUnmovable(port);
                gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
            }
            if (isAnimStepPlaying(gameSetUpStep[0x37 + port])) {
                makeCursorMovable(port);
                gameSetUpStep[0x37 + port] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
            }
            break;
        case CHAR_SELECT_PROCESS_TM_SHOW_SCOUT_FLAGS:
            if (isAnimStepStart(gameSetUpStep[0x37])) {
                BOOL playedFlag = FALSE;
                for (player = 0; player < 9; player++) {
                    s32 flags = (s8)g_Challenge.characters[inMemRoster[1][player].stats.CharID].scoutFlagsAchieved;
                    s32 flag;
                    for (flag = 0; flag < flags; flag++) {
                        TEAM_MANAGEMENT_RECORD_C(scene, 0x16D, flag + player * 5)->playMode = UI_PLAY_FORWARD;
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
                gameSetUpStep[0x37] = TEAM_MANAGEMENT_ANIM_STEP_PLAYING;
            }
            if (isAnimStepPlaying(gameSetUpStep[0x37])) {
                makeCursorMovable(0);
                gameSetUpStep[0x37] = TEAM_MANAGEMENT_ANIM_STEP_DONE;
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
    if (g_TeamManagement.removeSceneRequested != 0) {
        g_TeamManagement.removeSceneRequested = FALSE;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}
