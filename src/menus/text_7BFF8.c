#include "menus/text_7BFF8.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/orderchange.h"
#include "static/UnknownHomes_Static.h"
#include "text/text.h"
#include "menus/yd_step.h"
#include "game/challenge/challenge_state.h"
#include "Unknown/File_0x800363d8.h"

typedef struct {
    u8 _00[0xD];
    u8 unk0D[4];
} CssStepFlags;
extern CssStepFlags gameSetUpStep;
extern u8 lbl_2_bss_F468[0xC4C];
void updateCharacterSelectProcessCode(int port, u8 process);
void gfx_cssCharStatBars_and_sthgElse(MenuScene *scene, s32 slot);
void teamSelectionSetChemStars(MenuScene *scene, u8 slot);
extern int menuCursors[0x16];
extern u8 captainIDMappings[12];
extern u8 lbl_2_data_2B3A4[];
extern menuControlStruct *menuControlVariables;

#define SCENE_RECORD(scene, index) ((UIRecord *)graphicsRelatedArray[(scene)->firstHandle + (index)].object)
#define TEAM_RECORD(scene, position, slot, base) SCENE_RECORD(scene, (position) + (slot) * 9 + (base))

static inline BOOL isStepActive(u8 step) {
    return step == 1 ? TRUE : FALSE;
}

static inline BOOL isStepClear(u8 step) {
    return step == 0 ? TRUE : FALSE;
}

static inline void setCaptainStarIcons(MenuScene *scene, int slot) {
    E(int, CHAR_ID) current;
    E(int, CHAR_ID) previous;
    u8 currentStar;
    u8 previousStar;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        current = mapCaptainCursorPositionToCharID[menuCursors[slot + 4]];
        previous = mapCaptainCursorPositionToCharID[cursorPositions.cursor[slot]];
    } else if (slot != 0) {
        previous = *(s8 *)&g_Challenge.opponentCaptainCharID;
        current = previous;
    } else {
        previous = g_Challenge.captainCharID;
        current = previous;
    }
    currentStar = Static_Stats_Tables.characterStats[current / 9][current % 9].stats.CaptainStarHitPitch;
    previousStar = Static_Stats_Tables.characterStats[previous / 9][previous % 9].stats.CaptainStarHitPitch;
    SCENE_RECORD(scene, slot + 0x82)->frame = lbl_2_data_2B3A4[currentStar] << 16;
    SCENE_RECORD(scene, slot + 0x7E)->frame = lbl_2_data_2B3A4[currentStar] << 16;
    load_Icon(scene, slot + 0x89, 1, 3, lbl_2_data_2B3A4[currentStar]);
    load_Icon(scene, slot + 0x8B, 1, 3, lbl_2_data_2B3A4[previousStar]);
}

static inline void setRosterCharacterGraphics(MenuScene *scene, int slot, int position) {
    E(s8, CHAR_ID) character = cursorPositions.roster.rosterCharID[slot][position];
    u8 mappedPosition;

    if (character != CHAR_ID_NONE) {
        TEAM_RECORD(scene, position, slot, 0x34)->flags |= UI_FLAG_VISIBLE;
        if (position == ((s32 *)lbl_2_bss_F468)[slot]) {
            TEAM_RECORD(scene, position, slot, 0x34)->frame = 10 << 16;
            TEAM_RECORD(scene, position, slot, 0x34)->playMode = UI_PLAY_STOP;
        } else {
            TEAM_RECORD(scene, position, slot, 0x34)->frame = 20 << 16;
            TEAM_RECORD(scene, position, slot, 0x34)->playMode = UI_PLAY_STOP;
        }
        mappedPosition = cursorPositions.roster.positionSwapMapping[slot][position];
        TEAM_RECORD(scene, mappedPosition, slot, 0x58)->frame = cursorPositions.roster.rosterCharID[slot][position] << 16;
        TEAM_RECORD(scene, mappedPosition, slot, 0x58)->playMode = UI_PLAY_STOP;
    } else {
        TEAM_RECORD(scene, position, slot, 0x34)->flags &= ~UI_FLAG_VISIBLE;
    }
}

// .text:0x0007E194 size:0x1EC mapped:0x806BD228
void fn_2_7E194(MenuScene* scene, s32 slot) {
    s32 count;
    s32 threshold;
    s8 swapIdx;
    s32 captainID;
    s8* cursor;

    if (isStepActive(gameSetUpStep.unk0D[slot])) {
        count = maybeCheckAndResetGrapicsElement(scene, slot + 0x1C, 10) != 0;
        count += maybeCheckAndResetGrapicsElement(scene, slot + 0x6A, 10) != 0;
        threshold = 3;
        count += maybeCheckAndResetGrapicsElement(scene, slot + 0x89, 5) != 0;
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && slot == 0) {
            cursor = (s8*)&cursorPositions;
            captainID = Static_Stats_Tables.captainSelectedID[1];
            if (cursor[0xB] == captainID) swapIdx = cursor[0x1D];
            if (cursor[0xC] == captainID) swapIdx = cursor[0x1E];
            if (cursor[0xD] == captainID) swapIdx = cursor[0x1F];
            if (cursor[0xE] == captainID) swapIdx = cursor[0x20];
            if (cursor[0xF] == captainID) swapIdx = cursor[0x21];
            if (cursor[0x10] == captainID) swapIdx = cursor[0x22];
            if (cursor[0x11] == captainID) swapIdx = cursor[0x23];
            if (cursor[0x12] == captainID) swapIdx = cursor[0x24];
            if (cursor[0x13] == captainID) swapIdx = cursor[0x25];
            count += maybeCheckAndResetGrapicsElement(scene, swapIdx + 0x3D, 0x14) != 0;
            threshold = 4;
        }
        if (count == threshold) {
            makeCursorMovable(slot);
            gameSetUpStep.unk0D[slot] = 2;
        }
    }
}

// .text:0x0007DAB8 size:0x6DC mapped:0x806BCB4C
void fn_2_7DAB8(MenuScene *scene, s32 slot) {
    int current;
    int previous;
    int currentSlot;
    int previousSlot;
    int savedSlot;
    int i;
    s8 saved;
    E(s8, CHAR_ID) character;

    if (isStepClear(gameSetUpStep.unk0D[slot])) {
        previous = ((s32 *)lbl_2_bss_F468)[slot + 2];
        current = ((s32 *)lbl_2_bss_F468)[slot];
        for (i = 0; i < 9; i++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[slot][i] == current) currentSlot = i;
            if ((s8)cursorPositions.roster.positionSwapMapping[slot][i] == previous) previousSlot = i;
        }
        if (previous != 9 && previous != 10 && previous < 9) {
            if (previous != (s8)lbl_2_bss_F468[slot + 0x61]) {
                TEAM_RECORD(scene, previous, slot, 0x46)->frame = 15 << 16;
                TEAM_RECORD(scene, previous, slot, 0x46)->playMode = UI_PLAY_BACKWARD;
                character = cursorPositions.roster.rosterCharID[slot][previousSlot];
                if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS) {
                    TEAM_RECORD(scene, previous, slot, 0x34)->frame = 10 << 16;
                    TEAM_RECORD(scene, previous, slot, 0x34)->playMode = UI_PLAY_FORWARD;
                }
            }
            TEAM_RECORD(scene, previous, slot, 0x22)->flags &= ~UI_FLAG_VISIBLE;
        }
        if (current != 9 && current != 10 && current < 9 && current != (s8)lbl_2_bss_F468[slot + 0x61]) {
            TEAM_RECORD(scene, current, slot, 0x46)->frame = 0;
            TEAM_RECORD(scene, current, slot, 0x46)->playMode = UI_PLAY_FORWARD;
            character = cursorPositions.roster.rosterCharID[slot][currentSlot];
            if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS) {
                TEAM_RECORD(scene, current, slot, 0x34)->frame = 20 << 16;
                TEAM_RECORD(scene, current, slot, 0x34)->playMode = UI_PLAY_BACKWARD;
            }
            if (lbl_2_bss_F468[slot + 0x41] == 0) {
                TEAM_RECORD(scene, current, slot, 0x22)->flags |= UI_FLAG_VISIBLE;
                TEAM_RECORD(scene, current, slot, 0x22)->playMode = UI_PLAY_FORWARD;
            }
        }
        gfx_cssCharStatBars_and_sthgElse(scene, slot);
        if (current == 9) {
            SCENE_RECORD(scene, slot + 0x95)->playMode = UI_PLAY_FORWARD;
        } else if (current == 10) {
            SCENE_RECORD(scene, slot + 0x91)->playMode = UI_PLAY_FORWARD;
        } else {
            if ((SCENE_RECORD(scene, slot + 0x95)->frame >> 16) > 10) {
                SCENE_RECORD(scene, slot + 0x95)->frame = 10 << 16;
                SCENE_RECORD(scene, slot + 0x95)->playMode = UI_PLAY_BACKWARD;
            }
            if ((SCENE_RECORD(scene, slot + 0x91)->frame >> 16) > 10 || previous == 10) {
                SCENE_RECORD(scene, slot + 0x91)->frame = 10 << 16;
                SCENE_RECORD(scene, slot + 0x91)->playMode = UI_PLAY_BACKWARD;
            }
        }
        if (lbl_2_bss_F468[slot + 0x5F] != 0) {
            saved = lbl_2_bss_F468[slot + 0x61];
            if (previous == saved || current == saved) {
                for (i = 0; i < 9; i++) {
                    if ((s8)cursorPositions.roster.positionSwapMapping[slot][i] == saved) savedSlot = i;
                }
                lbl_2_bss_F468[slot + 0x61] = saved;
                character = cursorPositions.roster.rosterCharID[slot][savedSlot];
                if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS) {
                    TEAM_RECORD(scene, (s8)lbl_2_bss_F468[slot + 0x61], slot, 0x34)->frame = 10 << 16;
                    TEAM_RECORD(scene, (s8)lbl_2_bss_F468[slot + 0x61], slot, 0x34)->playMode = UI_PLAY_STOP;
                }
                TEAM_RECORD(scene, (s8)lbl_2_bss_F468[slot + 0x61], slot, 0x46)->frame = 15 << 16;
                TEAM_RECORD(scene, (s8)lbl_2_bss_F468[slot + 0x61], slot, 0x46)->playMode = UI_PLAY_STOP;
                if (current == (s8)lbl_2_bss_F468[slot + 0x61]) {
                    TEAM_RECORD(scene, (s8)lbl_2_bss_F468[slot + 0x61], slot, 0x22)->flags |= UI_FLAG_VISIBLE;
                }
            } else {
                TEAM_RECORD(scene, saved, slot, 0x22)->flags &= ~UI_FLAG_VISIBLE;
            }
        }
        makeCursorUnmovable(slot);
        gameSetUpStep.unk0D[slot] = 1;
    }
}

// .text:0x0007D85C size:0x25C mapped:0x806BC8F0
void fn_2_7D85C(MenuScene* scene, s32 slot) {
    s32 attempts;
    s32 successes;
    s32 idxA;
    s32 idxB;
    s32 valA;
    s32 valB;
    s32 ch;
    s32 i;
    s32* pair;

    pair = (s32*)lbl_2_bss_F468;
    if (gameSetUpStep.unk0D[slot] == 1) {
        valB = pair[slot + 2];
        valA = pair[slot];
        attempts = 0;
        successes = 0;
        for (i = 0; i < 9; i++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[slot][i] == valA) {
                idxA = i;
            }
            if ((s8)cursorPositions.roster.positionSwapMapping[slot][i] == valB) {
                idxB = i;
            }
        }
        if (valB != 9 && valB != 10 && valB < 9) {
            ch = cursorPositions.roster.rosterCharID[slot][idxB];
            if (ch != -1 && ch != 0x36 && valB != (s8)lbl_2_bss_F468[0x61 + slot] && valB != valA) {
                attempts = 1;
                successes = maybeCheckAndResetGrapicsElement(scene, valB + slot * 9 + 0x34, 0x14) != 0;
            }
        }
        if (valA != 9 && valA != 10 && valA < 9) {
            ch = cursorPositions.roster.rosterCharID[slot][idxA];
            if (ch != -1 && ch != 0x36 && valA != (s8)lbl_2_bss_F468[0x61 + slot]) {
                attempts++;
                successes += maybeCheckAndResetGrapicsElement(scene, valA + slot * 9 + 0x34, 0x14) != 0;
            }
        }
        if (successes == attempts) {
            pair[slot + 2] = valA;
            makeCursorMovable(slot);
            gameSetUpStep.unk0D[slot] = 2;
            if (lbl_2_bss_F468[0x63 + slot] != 0) {
                lbl_2_bss_F468[0x63 + slot] = 0;
                updateCharacterSelectProcessCode(slot, 0x1A);
            }
        }
    }
}

// .text:0x0007BFF8 size:0x1864 mapped:0x806BB08C
void cssAction_case9(MenuScene *scene, s32 slot) {
    int i;
    int captain;
    u8 captainPosition;
    BOOL cpuPlayer;
    int ready;
    int expected;
    int starsReady;
    int starsExpected;
    int starCount;
    u8 mode;

    if (isStepClear(gameSetUpStep.unk0D[slot])) {
        setCaptainStarIcons(scene, slot);
        SCENE_RECORD(scene, 6)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, 8)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, slot + 0x1A)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, slot + 0x1A)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, slot + 0x89)->frame = 0;
        SCENE_RECORD(scene, slot + 0x89)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, slot + 0x85)->frame = 0;
        SCENE_RECORD(scene, slot + 0x85)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, slot + 0x82)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, slot + 0x7A)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, slot + 0x82)->frame = captainIDMappings[Static_Stats_Tables.captainSelectedID[1]] << 16;
        SCENE_RECORD(scene, slot + 0x7E)->frame = menuCursors[slot + 4] << 16;
        SCENE_RECORD(scene, slot + 0x7A)->frame = Static_Stats_Tables.playerNumberByPort[1] << 16;
        SCENE_RECORD(scene, 0x84)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, slot + 0x97)->elementIndex = 0x77;
        SCENE_RECORD(scene, slot + 0x97)->frame = 0;
        SCENE_RECORD(scene, slot + 0x97)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, slot + 0xB0)->flags &= ~UI_FLAG_VISIBLE;
        for (i = 0; i < 9; i++) {
            TEAM_RECORD(scene, i, slot, 0x22)->flags &= ~UI_FLAG_VISIBLE;
        }
        SCENE_RECORD(scene, slot)->elementIndex = 0x48;
        SCENE_RECORD(scene, slot + 2)->elementIndex = 0x48;
        SCENE_RECORD(scene, slot + 4)->elementIndex = 0x51;
        SCENE_RECORD(scene, slot)->frame = 40 << 16;
        SCENE_RECORD(scene, slot + 2)->frame = 40 << 16;
        SCENE_RECORD(scene, slot + 4)->frame = 0;
        SCENE_RECORD(scene, slot)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, slot + 2)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, slot + 4)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, slot + 0x10)->frame = Static_Stats_Tables.teamName[slot] << 16;
        SCENE_RECORD(scene, slot + 0x14)->frame = Static_Stats_Tables.teamName[slot] << 16;
        SCENE_RECORD(scene, 0x1C)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x1D)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x1E)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x1F)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x78)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x79)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x7C)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x7D)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x80)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x81)->flags &= ~UI_FLAG_VISIBLE;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            SCENE_RECORD(scene, slot + 4)->frame = 0;
            SCENE_RECORD(scene, slot + 4)->playMode = UI_PLAY_FORWARD;
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && slot == 0) {
                SCENE_RECORD(scene, slot + 0x1C)->frame = 0;
                SCENE_RECORD(scene, slot + 0x1C)->playMode = UI_PLAY_STOP;
                SCENE_RECORD(scene, slot + 0xC)->frame = 20 << 16;
                SCENE_RECORD(scene, slot + 0xC)->playMode = UI_PLAY_BACKWARD;
                SCENE_RECORD(scene, slot + 0xE)->frame = 24 << 16;
                SCENE_RECORD(scene, slot + 0xE)->playMode = UI_PLAY_BACKWARD;
                SCENE_RECORD(scene, slot + 0x12)->frame = 20 << 16;
                SCENE_RECORD(scene, slot + 0x12)->playMode = UI_PLAY_BACKWARD;
            } else {
                SCENE_RECORD(scene, slot + 0x1C)->frame = 0;
                SCENE_RECORD(scene, slot + 0x1C)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, slot + 0x89)->frame = 0;
                SCENE_RECORD(scene, slot + 0x89)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, slot + 0x97)->flags &= ~UI_FLAG_VISIBLE;
                SCENE_RECORD(scene, slot + 0xC)->flags |= UI_FLAG_VISIBLE;
                SCENE_RECORD(scene, slot + 0x12)->flags |= UI_FLAG_VISIBLE;
                SCENE_RECORD(scene, slot + 0xC)->frame = 20 << 16;
                SCENE_RECORD(scene, slot + 0xC)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, slot + 0xE)->frame = 24 << 16;
                SCENE_RECORD(scene, slot + 0xE)->playMode = UI_PLAY_BACKWARD;
                SCENE_RECORD(scene, slot + 0x12)->frame = 20 << 16;
                SCENE_RECORD(scene, slot + 0x12)->playMode = UI_PLAY_FORWARD;
            }
            SCENE_RECORD(scene, slot + 0x6A)->frame = 0;
            SCENE_RECORD(scene, slot + 0x6A)->playMode = UI_PLAY_FORWARD;
            captain = Static_Stats_Tables.captainSelectedID[slot];
            for (i = 0; i < 9; i++) {
                if (cursorPositions.roster.rosterCharID[slot][i] == captain) {
                    captainPosition = cursorPositions.roster.positionSwapMapping[slot][i];
                }
            }
            Static_Stats_Tables.captainSelectedID[slot] = captain;
            for (i = 0; i < 9; i++) {
                if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && lbl_2_bss_F468[slot + 0x37] == 0 && slot == 1) {
                    if (i == captainPosition) {
                        cpuPlayer = Static_Stats_Tables.playerNumberByPort[0] == 0;
                        TEAM_RECORD(scene, i, slot, 0x46)->elementIndex = cpuPlayer + 0x11;
                        TEAM_RECORD(scene, i, slot, 0x46)->flags |= UI_FLAG_VISIBLE;
                    } else {
                        TEAM_RECORD(scene, i, slot, 0x46)->flags &= ~UI_FLAG_VISIBLE;
                    }
                } else {
                    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                        if (Static_Stats_Tables.playerNumberByPort[0] == 0) cpuPlayer = TRUE;
                        else cpuPlayer = FALSE;
                    }
                    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && slot != 0) {
                        TEAM_RECORD(scene, i, slot, 0x46)->elementIndex = cpuPlayer + 0x11;
                    } else {
                        TEAM_RECORD(scene, i, slot, 0x46)->elementIndex = Static_Stats_Tables.playerNumberByPort[slot] + 0x11;
                    }
                    TEAM_RECORD(scene, i, slot, 0x46)->frame = 0;
                    TEAM_RECORD(scene, i, slot, 0x46)->flags |= UI_FLAG_VISIBLE;
                    TEAM_RECORD(scene, i, slot, 0x46)->playMode = UI_PLAY_STOP;
                }
                setRosterCharacterGraphics(scene, slot, i);
            }
            teamSelectionSetChemStars(scene, slot);
            if (g_d_GameSettings.p2_CPU_match_code != P2_CPU_CODE_1_PLAYER_GAME || slot == 0) {
                SCENE_RECORD(scene, slot + 0x93)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, slot + 0x95)->frame = 0;
                SCENE_RECORD(scene, slot + 0x91)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, slot + 0x8F)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, slot + 0x91)->frame = 0;
                SCENE_RECORD(scene, slot + 0x91)->playMode = UI_PLAY_STOP;
            }
            SCENE_RECORD(scene, 0xAE)->flags |= UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0xAF)->flags |= UI_FLAG_VISIBLE;
        } else {
            SCENE_RECORD(scene, slot + 0x1C)->frame = 0;
            SCENE_RECORD(scene, slot + 0x1C)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, slot + 0x89)->frame = 0;
            SCENE_RECORD(scene, slot + 0x89)->playMode = UI_PLAY_FORWARD;
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                if (Static_Stats_Tables.playerNumberByPort[0] == 0) cpuPlayer = TRUE;
                else cpuPlayer = FALSE;
            }
            for (i = 0; i < 9; i++) {
                if (slot != 0) {
                    TEAM_RECORD(scene, i, slot, 0x46)->elementIndex = cpuPlayer + 0x11;
                } else {
                    TEAM_RECORD(scene, i, slot, 0x46)->elementIndex = Static_Stats_Tables.playerNumberByPort[slot] + 0x11;
                }
                TEAM_RECORD(scene, i, slot, 0x46)->frame = 0;
                if (i == ((s32 *)lbl_2_bss_F468)[slot]) {
                    TEAM_RECORD(scene, i, slot, 0x46)->flags |= UI_FLAG_VISIBLE;
                    TEAM_RECORD(scene, i, slot, 0x46)->playMode = UI_PLAY_FORWARD;
                } else {
                    TEAM_RECORD(scene, i, slot, 0x46)->flags |= UI_FLAG_VISIBLE;
                    TEAM_RECORD(scene, i, slot, 0x46)->playMode = UI_PLAY_STOP;
                }
                setRosterCharacterGraphics(scene, slot, i);
            }
            teamSelectionSetChemStars(scene, slot);
            SCENE_RECORD(scene, slot + 0x6A)->frame = 10 << 16;
            SCENE_RECORD(scene, slot + 0x6A)->playMode = UI_PLAY_FORWARD;
        }
        if (menuControlVariables->previousScreen == 11) {
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                if (slot == 0 && g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) mode = UI_PLAY_STOP;
                else mode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, slot + 0x93)->frame = 0;
                SCENE_RECORD(scene, slot + 0x93)->playMode = mode;
                SCENE_RECORD(scene, slot + 0x95)->frame = 0;
                SCENE_RECORD(scene, slot + 0x95)->playMode = mode;
                SCENE_RECORD(scene, slot + 0x8F)->frame = 0;
                SCENE_RECORD(scene, slot + 0x8F)->playMode = mode;
                SCENE_RECORD(scene, slot + 0x91)->frame = 0;
                SCENE_RECORD(scene, slot + 0x91)->playMode = UI_PLAY_STOP;
            } else {
                if (slot == 1) {
                    SCENE_RECORD(scene, slot + 0x93)->flags &= ~UI_FLAG_VISIBLE;
                } else {
                    SCENE_RECORD(scene, slot + 0x93)->flags |= UI_FLAG_VISIBLE;
                    SCENE_RECORD(scene, slot + 0x93)->frame = 0;
                    SCENE_RECORD(scene, slot + 0x93)->playMode = UI_PLAY_FORWARD;
                    SCENE_RECORD(scene, slot + 0x95)->frame = 0;
                    SCENE_RECORD(scene, slot + 0x95)->playMode = UI_PLAY_FORWARD;
                }
                SCENE_RECORD(scene, slot + 0x8F)->flags &= ~UI_FLAG_VISIBLE;
            }
        }
        if (lbl_2_bss_F468[0x3F] != 0 && lbl_2_bss_F468[0x37] != 0 && slot == 0 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE || slot == 0) {
                SCENE_RECORD(scene, slot + 0x93)->frame = 0;
                SCENE_RECORD(scene, slot + 0x93)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, slot + 0x95)->frame = 0;
                SCENE_RECORD(scene, slot + 0x95)->playMode = UI_PLAY_FORWARD;
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                SCENE_RECORD(scene, slot + 0x8F)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, slot + 0x91)->frame = 0;
                SCENE_RECORD(scene, slot + 0x91)->playMode = UI_PLAY_STOP;
            }
        }
        makeCursorUnmovable(slot);
        gameSetUpStep.unk0D[slot] = 1;
    }
    if (gameSetUpStep.unk0D[slot] == 1) {
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            ready = maybeCheckAndResetGrapicsElement(scene, slot, 20) != 0;
            ready += maybeCheckAndResetGrapicsElement(scene, slot + 2, 20) != 0;
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && slot == 0) {
                ready += maybeCheckAndResetGrapicsElement(scene, slot + 0x6A, 30) != 0;
                ready += maybeCheckAndResetGrapicsElement(scene, slot + 0xC, 10) != 0;
                ready += maybeCheckAndResetGrapicsElement(scene, slot + 0xE, 14) != 0;
                ready += maybeCheckAndResetGrapicsElement(scene, slot + 0x12, 10) != 0;
                expected = 6;
            } else {
                ready += maybeCheckAndResetGrapicsElement(scene, slot + 0x1C, 10) != 0;
                ready += maybeCheckAndResetGrapicsElement(scene, slot + 0x6A, 10) != 0;
                ready += maybeCheckAndResetGrapicsElement(scene, slot + 0xC, 30) != 0;
                ready += maybeCheckAndResetGrapicsElement(scene, slot + 0xE, 14) != 0;
                ready += maybeCheckAndResetGrapicsElement(scene, slot + 0x12, 30) != 0;
                ready += maybeCheckAndResetGrapicsElement(scene, slot + 0x89, 5) != 0;
                expected = 8;
            }
        } else {
            ready = maybeCheckAndResetGrapicsElement(scene, slot, 20) != 0;
            ready += maybeCheckAndResetGrapicsElement(scene, slot + 2, 20) != 0;
            ready += maybeCheckAndResetGrapicsElement(scene, slot + 0x1C, 10) != 0;
            ready += maybeCheckAndResetGrapicsElement(scene, slot + 0x6A, 10) != 0;
            ready += maybeCheckAndResetGrapicsElement(scene, slot + 0x89, 5) != 0;
            expected = 5;
        }
        ready += maybeCheckAndResetGrapicsElement(scene, slot + 0x85, 10) != 0;
        starsReady = 0;
        starsExpected = 0;
        starCount = Static_Stats_Tables.startingChemStars[slot];
        for (i = 0; i < starCount; i++) {
            starsExpected++;
            starsReady += maybeCheckAndResetGrapicsElement(scene, i + slot * 5 + 0x6E, 30) != 0;
        }
        if (starsReady == starsExpected && ready == expected + 1) {
            makeCursorMovable(slot);
            gameSetUpStep.unk0D[slot] = 2;
        }
    }
}
