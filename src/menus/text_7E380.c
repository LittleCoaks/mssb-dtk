#define SQRT2_LINKAGE static
#include "menus/text_7E380.h"
#include "game/UnknownHomes_Game.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80062674.h"
#include "text/text.h"
#include "static/UnknownHomes_Static.h"
#include "game/challenge/challenge_state.h"
#include "Unknown/File_0x800363d8.h"

extern u8 gameSetUpStep[0x64];
extern u8 lbl_2_bss_F468[];
void gfx_cssCharStatBars_and_sthgElse(MenuScene *scene, s32 channel);
BOOL maybeCheckAndResetGrapicsElement(MenuScene *scene, int handle, int frame);
void updateCharacterSelectProcessCode(int port, u8 process);
void fn_2_16A74(s32 port, s32 flag);
void fn_2_7630C(MenuScene *scene, u8 channel);
void fn_2_CCE0(u8 channel);
void teamSelectionSetChemStars(MenuScene *scene, u8 channel);
extern u8 lbl_2_bss_100B8[];
extern int menuCursors[0x16];
extern u8 lbl_2_data_2B3A4[];

#define SCENE_OBJECT(scene, n) (graphicsRelatedArray[(scene)->firstHandle + (n)].object)
#define SCENE_RECORD(scene, n) ((UIRecord *)SCENE_OBJECT(scene, n))

static inline UIRecord *rosterRecord(MenuScene *scene, s32 channel, s32 position, s32 offset) {
    s32 handle = scene->firstHandle + position;
    handle += channel * PLAYERS_PER_TEAM;
    handle += offset;
    return (UIRecord *)graphicsRelatedArray[handle].object;
}

static inline s32 rosterHandle(s32 channel, s32 position, s32 offset) {
    s32 handle = position;
    handle += channel * PLAYERS_PER_TEAM;
    handle += offset;
    return handle;
}

static inline BOOL resetRosterAnimation(MenuScene *scene, s32 channel, s32 position, s32 frame) {
    return maybeCheckAndResetGrapicsElement(scene, rosterHandle(channel, position, 0x34), frame) != 0;
}

static inline BOOL isStepClear(u8 step) {
    return step == 0 ? TRUE : FALSE;
}

static inline BOOL isStepActive(u8 step) {
    return step == 1 ? TRUE : FALSE;
}

static inline BOOL resetChemistryStarsCount(MenuScene *scene, s32 channel, s32 starCount) {
    s32 ready = 0;
    s32 expected = 0;
    s32 i;

    for (i = 0; i < starCount; i++) {
        s32 handle = i;
        handle += channel * 5;
        handle += 0x6E;
        expected++;
        ready += maybeCheckAndResetGrapicsElement(scene, handle, 30) != 0;
    }
    return ready == expected;
}

static inline BOOL resetChemistryStars(MenuScene *scene, s32 channel) {
    s32 starCount = Static_Stats_Tables.startingChemStars[channel];
    return resetChemistryStarsCount(scene, channel, starCount);
}

static inline void setCaptainStarIcons(MenuScene *scene, s32 channel) {
    E(s32, CHAR_ID) cursorCharacter;
    E(s32, CHAR_ID) previousCharacter;
    u8 cursorStar;
    u8 previousStar;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        cursorCharacter = mapCaptainCursorPositionToCharID[menuCursors[channel + 4]];
        previousCharacter = mapCaptainCursorPositionToCharID[cursorPositions.cursor[channel]];
    } else if (channel != 0) {
        previousCharacter = *(s8 *)&g_Challenge.opponentCaptainCharID;
        cursorCharacter = previousCharacter;
    } else {
        previousCharacter = g_Challenge.captainCharID;
        cursorCharacter = previousCharacter;
    }
    cursorStar = Static_Stats_Tables.characterStats[cursorCharacter / 9][cursorCharacter % 9].stats.CaptainStarHitPitch;
    previousStar = Static_Stats_Tables.characterStats[previousCharacter / 9][previousCharacter % 9].stats.CaptainStarHitPitch;
    SCENE_RECORD(scene, channel + 0x82)->frame = lbl_2_data_2B3A4[cursorStar] << 16;
    SCENE_RECORD(scene, channel + 0x7E)->frame = lbl_2_data_2B3A4[cursorStar] << 16;
    load_Icon(scene, channel + 0x89, 1, 3, lbl_2_data_2B3A4[cursorStar]);
    load_Icon(scene, channel + 0x8B, 1, 3, lbl_2_data_2B3A4[previousStar]);
}

static inline s32 previousPosition(s32 channel) {
    return ((s32 *)lbl_2_bss_F468)[channel + 2];
}

static inline UIRecord *readyChannelRecord(MenuScene *scene, s32 channel, s32 index) {
    s32 handle = scene->firstHandle;
    handle += channel;
    handle += index;
    return (UIRecord *)graphicsRelatedArray[handle].object;
}

static inline UIRecord *cpuRosterCursorRecord(MenuScene *scene, s32 position) {
    s32 handle = scene->firstHandle;
    handle += position;
    handle += 0x22;
    return (UIRecord *)graphicsRelatedArray[handle + PLAYERS_PER_TEAM].object;
}

static inline s8 findRosterSlot(s32 channel, s8 position) {
    s8 slot;
    s32 i;

    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if ((s8)cursorPositions.roster.positionSwapMapping[channel][i] == position) {
            slot = i;
            break;
        }
    }
    return slot;
}

// .text:0x000805DC size:0x250 mapped:0x806BF670
void fn_2_805DC(MenuScene *scene, s32 channel) {
    u8 ready;

    if (isStepClear(gameSetUpStep[channel + 0xD])) {
        u8 isZero;

        SCENE_RECORD(scene, 0x81)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x84)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x84)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, 0x98)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x86)->frame = 10 << 16;
        SCENE_RECORD(scene, 0x86)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, 0x8A)->frame = 5 << 16;
        SCENE_RECORD(scene, 0x8A)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, 0x79)->frame = 20 << 16;
        SCENE_RECORD(scene, 0x79)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, 0x7D)->frame = 20 << 16;
        SCENE_RECORD(scene, 0x7D)->playMode = UI_PLAY_BACKWARD;
        isZero = Static_Stats_Tables.playerNumberByPort[0] == 0;
        SCENE_RECORD(scene, 0x7B)->frame = isZero << 16;
        SCENE_RECORD(scene, 0x19)->frame = (isZero + 4) << 16;
        makeCursorUnmovable(channel);
        gameSetUpStep[channel + 0xD] = 1;
    }
    if (gameSetUpStep[channel + 0xD] == 1) {
        ready = maybeCheckAndResetGrapicsElement(scene, 0x86, 0) != 0;
        if (ready + (maybeCheckAndResetGrapicsElement(scene, 0x8A, 0) != 0) == 2) {
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_2_PLAYER_GAME && lbl_2_bss_100B8[0x10] == 0) {
                fn_2_16A74(1, 0);
            }
            makeCursorMovable(channel);
            gameSetUpStep[channel + 0xD] = 2;
            g_d_GameSettings.p2_CPU_match_code = P2_CPU_CODE_1_PLAYER_GAME;
        }
    }
}

// .text:0x00080500 size:0xDC mapped:0x806BF594
void fn_2_80500(MenuScene *scene, s32 channel) {

    if (isStepClear(gameSetUpStep[channel + 0xD])) {
        u8 isZero = Static_Stats_Tables.playerNumberByPort[0] == 0;

        SCENE_RECORD(scene, 0x7B)->frame = isZero << 16;
        SCENE_RECORD(scene, 0x19)->frame = (isZero + 4) << 16;
        makeCursorUnmovable(channel);
        gameSetUpStep[channel + 0xD] = 1;
    }
    if (gameSetUpStep[channel + 0xD] == 1) {
        makeCursorMovable(channel);
        gameSetUpStep[channel + 0xD] = 2;
        g_d_GameSettings.p2_CPU_match_code = P2_CPU_CODE_1_PLAYER_GAME;
    }
}

// .text:0x000802EC size:0x214 mapped:0x806BF380
void fn_2_802EC(MenuScene *scene) {
    s32 ready;

    if (isStepClear(gameSetUpStep[0xE])) {
        SCENE_RECORD(scene, 0x81)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x81)->frame = 0;
        SCENE_RECORD(scene, 0x81)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, 0x84)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x84)->playMode = UI_PLAY_STOP;
        SCENE_RECORD(scene, 0x7D)->frame = 0;
        SCENE_RECORD(scene, 0x7D)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, 0x98)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x86)->frame = 0;
        SCENE_RECORD(scene, 0x86)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, 0x8A)->frame = 0;
        SCENE_RECORD(scene, 0x8A)->playMode = UI_PLAY_FORWARD;
        fn_2_7630C(scene, 1);
        gfx_cssCharStatBars_and_sthgElse(scene, 1);
        makeCursorUnmovable(1);
        gameSetUpStep[0xE] = 1;
    }
    if (gameSetUpStep[0xE] == 1) {
        ready = maybeCheckAndResetGrapicsElement(scene, 0x81, 20) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, 0x7D, 20) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, 0x86, 10) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, 0x8A, 5) != 0;
        if (ready == 4) {
            makeCursorMovable(1);
            gameSetUpStep[0xE] = 2;
        }
    }
}

// .text:0x000800B0 size:0x23C mapped:0x806BF144
void captainSelectUnloadCSSLoadRelated(MenuScene *scene, s32 channel) {
    s32 ready;

    if (isStepClear(gameSetUpStep[channel + 0xD])) {
        SCENE_RECORD(scene, channel)->frame = 20 << 16;
        SCENE_RECORD(scene, channel + 2)->frame = 20 << 16;
        SCENE_RECORD(scene, channel)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 2)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 0x80)->frame = 20 << 16;
        SCENE_RECORD(scene, channel + 0x80)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0x78)->frame = 20 << 16;
        SCENE_RECORD(scene, channel + 0x78)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0x7C)->frame = 20 << 16;
        SCENE_RECORD(scene, channel + 0x7C)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0x97)->elementIndex = 0x77;
        SCENE_RECORD(scene, channel + 0x97)->frame = 0;
        SCENE_RECORD(scene, channel + 0x97)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, channel + 0xB0)->flags &= ~UI_FLAG_VISIBLE;
        makeCursorUnmovable(channel);
        gameSetUpStep[channel + 0xD] = 1;
    }
    if (gameSetUpStep[channel + 0xD] == 1) {
        ready = maybeCheckAndResetGrapicsElement(scene, channel, 30) != 0;
        if (ready + (maybeCheckAndResetGrapicsElement(scene, channel + 2, 30) != 0) == 2) {
            makeCursorMovable(channel);
            gameSetUpStep[channel + 0xD] = 2;
        }
    }
}

// .text:0x0007FAFC size:0x5B4 mapped:0x806BEB90
void fn_2_7FAFC(MenuScene *scene, s32 channel) {
    u8 first;
    s32 ready;

    if (isStepClear(gameSetUpStep[channel + 0xD])) {
        SCENE_RECORD(scene, channel)->frame = 30 << 16;
        SCENE_RECORD(scene, channel + 2)->frame = 30 << 16;
        SCENE_RECORD(scene, channel)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 2)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 4)->elementIndex = 0x50;
        SCENE_RECORD(scene, channel + 4)->frame = 0;
        SCENE_RECORD(scene, channel + 4)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 0x85)->frame = 20 << 16;
        SCENE_RECORD(scene, channel + 0x85)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0x89)->frame = 10 << 16;
        SCENE_RECORD(scene, channel + 0x89)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0x82)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, channel + 0x7A)->flags |= UI_FLAG_VISIBLE;
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && channel != 0) {
            if (Static_Stats_Tables.playerNumberByPort[0] == 0) {
                SCENE_RECORD(scene, channel + 0x7A)->frame = 1 << 16;
            } else {
                SCENE_RECORD(scene, channel + 0x7A)->frame = 0;
            }
        } else {
            SCENE_RECORD(scene, channel + 0x7A)->frame = Static_Stats_Tables.playerNumberByPort[channel] << 16;
        }
        setCaptainStarIcons(scene, channel);
        SCENE_RECORD(scene, channel + 0x80)->frame = 0;
        SCENE_RECORD(scene, channel + 0x80)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 0x78)->frame = 0;
        SCENE_RECORD(scene, channel + 0x78)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 0x7C)->frame = 0;
        SCENE_RECORD(scene, channel + 0x7C)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 0x97)->elementIndex = 0x78;
        SCENE_RECORD(scene, channel + 0x97)->frame = 0;
        SCENE_RECORD(scene, channel + 0x97)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 0x99)->elementIndex = 0x79;
        gfx_cssCharStatBars_and_sthgElse(scene, channel);
        SCENE_RECORD(scene, channel + 0xAC)->playMode = UI_PLAY_BACKWARD;
        makeCursorUnmovable(channel);
        gameSetUpStep[channel + 0xD] = 1;
    }
    if (gameSetUpStep[channel + 0xD] == 1) {
        first = maybeCheckAndResetGrapicsElement(scene, channel, 20) != 0;
        ready = first + (maybeCheckAndResetGrapicsElement(scene, channel + 2, 20) != 0);
        ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x85, 10) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x89, 5) != 0;
        if (ready == 4) {
            makeCursorMovable(channel);
            gameSetUpStep[channel + 0xD] = 2;
        }
    }
}

// .text:0x0007F8BC size:0x240 mapped:0x806BE950
void cssSelectCharacter(MenuScene *scene, s32 channel) {
    s8 selected;
    s8 slot;
    E(s8, CHAR_ID) character;

    if (isStepClear(gameSetUpStep[channel + 0xD])) {
        selected = (s8)((s32 *)lbl_2_bss_F468)[channel];
        slot = findRosterSlot(channel, selected);
        character = cursorPositions.roster.rosterCharID[channel][slot];
        rosterRecord(scene, channel, selected, 0x34)->flags |= UI_FLAG_VISIBLE;
        rosterRecord(scene, channel, selected, 0x34)->frame = 0;
        rosterRecord(scene, channel, selected, 0x34)->playMode = UI_PLAY_FORWARD;
        rosterRecord(scene, channel, selected, 0x58)->frame = character << 16;
        teamSelectionSetChemStars(scene, channel);
        gfx_cssCharStatBars_and_sthgElse(scene, channel);
        makeCursorUnmovable(channel);
        gameSetUpStep[channel + 0xD] = 1;
    }
}

// .text:0x0007F714 size:0x1A8 mapped:0x806BE7A8
void fn_2_7F714(MenuScene *scene, s32 channel) {
    s32 selected;
    BOOL ready;

    if (gameSetUpStep[channel + 0xD] == 1) {
        selected = (s8)((s32 *)lbl_2_bss_F468)[channel];
        findRosterSlot(channel, selected);
        ready = maybeCheckAndResetGrapicsElement(scene, rosterHandle(channel, selected, 0x34), 10) != 0;
        if (resetChemistryStarsCount(scene, channel, Static_Stats_Tables.startingChemStars[channel]) && ready == TRUE) {
            makeCursorMovable(channel);
            fn_2_CCE0((u8)channel);
        }
    }
}

// .text:0x0007F2BC size:0x458 mapped:0x806BE350
void cssRemoveCharacter1(MenuScene *scene, s32 channel) {
    s32 selected;
    s32 previous;
    s32 slot;
    s32 oldSlot;
    s32 i;
    E(s8, CHAR_ID) character;

    if (isStepClear(gameSetUpStep[channel + 0xD])) {
        previous = previousPosition(channel);
        selected = ((s32 *)lbl_2_bss_F468)[channel];
        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[channel][i] == selected) slot = i;
            if ((s8)cursorPositions.roster.positionSwapMapping[channel][i] == previous) oldSlot = i;
        }
        if (selected != 9 && selected != 10) {
            character = cursorPositions.roster.rosterCharID[channel][slot];
            if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS) {
                rosterRecord(scene, channel, selected, 0x34)->frame = 0;
                rosterRecord(scene, channel, selected, 0x34)->playMode = UI_PLAY_FORWARD;
            }
            rosterRecord(scene, channel, selected, 0x46)->frame = 0;
            rosterRecord(scene, channel, selected, 0x46)->playMode = UI_PLAY_FORWARD;
            rosterRecord(scene, channel, selected, 0x22)->flags |= UI_FLAG_VISIBLE;
        }
        if (previous != 9 && previous != 10) {
            if (previousPosition(channel) != ((s32 *)lbl_2_bss_F468)[channel]) {
                rosterRecord(scene, channel, previous, 0x46)->frame = 15 << 16;
                rosterRecord(scene, channel, previous, 0x46)->playMode = UI_PLAY_BACKWARD;
                if (Static_Stats_Tables.captainSelectedID[channel] == cursorPositions.roster.rosterCharID[channel][oldSlot]) {
                    rosterRecord(scene, channel, previous, 0x34)->playMode = UI_PLAY_FORWARD;
                } else {
                    rosterRecord(scene, channel, previous, 0x34)->playMode = UI_PLAY_BACKWARD;
                }
            }
            rosterRecord(scene, channel, previous, 0x22)->flags &= ~UI_FLAG_VISIBLE;
        }
        teamSelectionSetChemStars(scene, channel);
        gfx_cssCharStatBars_and_sthgElse(scene, channel);
        if ((readyChannelRecord(scene, channel, 0x93)->frame >> 16) == 10 &&
            Static_Stats_Tables.captainSelectedID[channel] != cursorPositions.roster.rosterCharID[channel][oldSlot]) {
            readyChannelRecord(scene, channel, 0x93)->frame = 10 << 16;
            readyChannelRecord(scene, channel, 0x93)->playMode = UI_PLAY_BACKWARD;
            readyChannelRecord(scene, channel, 0x95)->frame = 10 << 16;
            readyChannelRecord(scene, channel, 0x95)->playMode = UI_PLAY_BACKWARD;
        } else if ((readyChannelRecord(scene, channel, 0x8F)->frame >> 16) == 10 && selected == 10) {
            readyChannelRecord(scene, channel, 0x91)->frame = 10 << 16;
            readyChannelRecord(scene, channel, 0x91)->playMode = UI_PLAY_BACKWARD;
        }
        if (selected == previous) {
            rosterRecord(scene, channel, selected, 0x34)->playMode = UI_PLAY_BACKWARD;
        }
        makeCursorUnmovable(channel);
        gameSetUpStep[channel + 0xD] = 1;
    }
}

// .text:0x0007F030 size:0x28C mapped:0x806BE0C4
void cssRemoveCharacter2(MenuScene *scene, s32 channel) {
    s32 selected = ((s32 *)lbl_2_bss_F468)[channel];
    s32 previous = ((s32 *)lbl_2_bss_F468)[channel + 2];
    s32 slot;
    s32 oldSlot;
    s32 ready;
    s32 expected;
    s32 i;
    E(s8, CHAR_ID) character;

    if (isStepActive(gameSetUpStep[channel + 0xD])) {
        ready = 0;
        expected = 0;
        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[channel][i] == selected) slot = i;
            if ((s8)cursorPositions.roster.positionSwapMapping[channel][i] == previous) oldSlot = i;
        }
        if (selected == previous) {
            expected = 1;
            ready = resetRosterAnimation(scene, channel, selected, 0);
        } else {
            character = cursorPositions.roster.rosterCharID[channel][slot];
            if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS) {
                expected = 1;
                ready = resetRosterAnimation(scene, channel, selected, 10);
            }
        }
        if (Static_Stats_Tables.captainSelectedID[channel] == cursorPositions.roster.rosterCharID[channel][oldSlot]) {
            expected++;
            ready += resetRosterAnimation(scene, channel, previous, 20);
        }
        if (resetChemistryStars(scene, channel) && ready == expected) {
            if (selected == previous) {
                rosterRecord(scene, channel, selected, 0x34)->flags &= ~UI_FLAG_VISIBLE;
            }
            makeCursorMovable(channel);
            gameSetUpStep[channel + 0xD] = 2;
        }
    }
}

// .text:0x0007EF68 size:0xC8 mapped:0x806BDFFC
void fn_2_7EF68(MenuScene *scene, s32 channel) {
    s32 k;

    for (k = 0; k < PLAYERS_PER_TEAM; k++) {
        if (k == ((s32 *)lbl_2_bss_F468)[channel]) {
            s32 handle = scene->firstHandle + k;
            handle += channel * PLAYERS_PER_TEAM;
            handle += 0x22;
            graphicsRelatedArray[handle].object->flags |= UI_FLAG_VISIBLE;
        }
    }
}

// .text:0x0007EE7C size:0xEC mapped:0x806BDF10
void fn_2_7EE7C(MenuScene *scene, s32 channel) {
    s32 k = ((s32 *)lbl_2_bss_F468)[channel];

    if (lbl_2_bss_F468[channel + 0x41]) {
        s32 handle = scene->firstHandle + k;
        handle += channel * PLAYERS_PER_TEAM;
        handle += 0x22;
        graphicsRelatedArray[handle].object->flags &= ~UI_FLAG_VISIBLE;
    } else {
        s32 handle = scene->firstHandle + k;
        handle += channel * PLAYERS_PER_TEAM;
        handle += 0x22;
        graphicsRelatedArray[handle].object->flags |= UI_FLAG_VISIBLE;
    }
    gfx_cssCharStatBars_and_sthgElse(scene, channel);
    gameSetUpStep[channel + 0x5D] = 0;
    if (lbl_2_bss_F468[channel + 0x59]) {
        updateCharacterSelectProcessCode(channel, 0x1A);
    }
}

// .text:0x0007E974 size:0x508 mapped:0x806BDA08
void cssReady(MenuScene *scene, s32 channel) {
    BOOL cpuPlayer;

    if (isStepClear(gameSetUpStep[channel + 0xD])) {
        readyChannelRecord(scene, channel, 0xC)->flags |= UI_FLAG_VISIBLE;
        readyChannelRecord(scene, channel, 0x12)->flags |= UI_FLAG_VISIBLE;
        readyChannelRecord(scene, channel, 0xC)->frame = 0;
        readyChannelRecord(scene, channel, 0xC)->playMode = UI_PLAY_FORWARD;
        readyChannelRecord(scene, channel, 0xE)->frame = 0;
        readyChannelRecord(scene, channel, 0xE)->playMode = UI_PLAY_FORWARD;
        readyChannelRecord(scene, channel, 0x10)->frame = Static_Stats_Tables.teamName[channel] << 16;
        readyChannelRecord(scene, channel, 0x12)->frame = 0;
        readyChannelRecord(scene, channel, 0x12)->playMode = UI_PLAY_FORWARD;
        readyChannelRecord(scene, channel, 0x14)->frame = Static_Stats_Tables.teamName[channel] << 16;
        readyChannelRecord(scene, channel, 0xB6)->flags &= ~UI_FLAG_VISIBLE;
        readyChannelRecord(scene, channel, 0x1C)->frame = 10 << 16;
        readyChannelRecord(scene, channel, 0x1C)->playMode = UI_PLAY_FORWARD;
        readyChannelRecord(scene, channel, 0x6A)->frame = 10 << 16;
        readyChannelRecord(scene, channel, 0x6A)->playMode = UI_PLAY_FORWARD;
        readyChannelRecord(scene, channel, 0x93)->frame = 10 << 16;
        readyChannelRecord(scene, channel, 0x93)->playMode = UI_PLAY_BACKWARD;
        readyChannelRecord(scene, channel, 0x8F)->frame = 10 << 16;
        readyChannelRecord(scene, channel, 0x8F)->playMode = UI_PLAY_BACKWARD;
        readyChannelRecord(scene, channel, 0x89)->frame = 5 << 16;
        readyChannelRecord(scene, channel, 0x89)->playMode = UI_PLAY_FORWARD;
        readyChannelRecord(scene, channel, 0x97)->playMode = UI_PLAY_BACKWARD;
        readyChannelRecord(scene, channel, 0xAC)->playMode = UI_PLAY_BACKWARD;
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
            cpuPlayer = Static_Stats_Tables.playerNumberByPort[0] == 0;
            if (lbl_2_bss_F468[0x38] != 0) {
                SCENE_RECORD(scene, 0x98)->playMode = UI_PLAY_BACKWARD;
            }
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && lbl_2_bss_F468[0x37] != 0 && channel == 0) {
            int i;
            for (i = 0; i < (s32)PLAYERS_PER_TEAM; i++) {
                SCENE_RECORD(scene, i + 0x4F)->flags |= UI_FLAG_VISIBLE;
                SCENE_RECORD(scene, i + 0x4F)->elementIndex = (s8)cpuPlayer + 0x11;
                SCENE_RECORD(scene, i + 0x4F)->frame = 0;
                SCENE_RECORD(scene, i + 0x4F)->playMode = UI_PLAY_STOP;
            }
            readyChannelRecord(scene, (s8)cpuPlayer, 0x8F)->playMode = UI_PLAY_FORWARD;
            readyChannelRecord(scene, (s8)cpuPlayer, 0x91)->frame = 0;
            readyChannelRecord(scene, (s8)cpuPlayer, 0x91)->playMode = UI_PLAY_FORWARD;
        }
        makeCursorUnmovable(channel);
        gameSetUpStep[channel + 0xD] = 1;
    }
}

// .text:0x0007E860 size:0x114 mapped:0x806BD8F4
void fn_2_7E860(MenuScene *scene, s32 channel) {
    if (isStepActive(gameSetUpStep[channel + 0xD])) {
        s32 ready;

        ready = maybeCheckAndResetGrapicsElement(scene, channel + 0xC, 0xA) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, channel + 0xE, 0xE) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x12, 0xA) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x1C, 0x14) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x6A, 0x1E) != 0;
        if (ready == 5) {
            makeCursorMovable(channel);
            gameSetUpStep[channel + 0xD] = 2;
        }
    }
}

// .text:0x0007E380 size:0x4E0 mapped:0x806BD414
void cssUnready(MenuScene *scene, s32 channel) {
    s32 captainPosition;
    s32 i;

    if (isStepClear(gameSetUpStep[channel + 0xD])) {
        SCENE_RECORD(scene, channel + 0xC)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, channel + 0x12)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, channel + 0xC)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0xE)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0x12)->frame = 10 << 16;
        SCENE_RECORD(scene, channel + 0x12)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0xB6)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, channel + 0x1C)->frame = 20 << 16;
        SCENE_RECORD(scene, channel + 0x1C)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0x6A)->frame = 30 << 16;
        SCENE_RECORD(scene, channel + 0x6A)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0x93)->frame = 0;
        SCENE_RECORD(scene, channel + 0x93)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 0x95)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 0x8F)->frame = 0;
        SCENE_RECORD(scene, channel + 0x8F)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 0x89)->frame = 10 << 16;
        SCENE_RECORD(scene, channel + 0x89)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, channel + 0x97)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, channel + 0xAC)->playMode = UI_PLAY_FORWARD;
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && channel == 0) {
            for (i = 0; i < PLAYERS_PER_TEAM; i++) {
                if (cursorPositions.roster.rosterCharID[1][i] == Static_Stats_Tables.captainSelectedID[1]) {
                    captainPosition = cursorPositions.roster.positionSwapMapping[1][i];
                }
            }
            for (i = 0; i < PLAYERS_PER_TEAM; i++) {
                if (channel == 0) {
                    if (i != (s8)captainPosition) {
                        readyChannelRecord(scene, i, 0x4F)->flags &= ~UI_FLAG_VISIBLE;
                    } else {
                        readyChannelRecord(scene, (s8)captainPosition, 0x3D)->playMode = UI_PLAY_FORWARD;
                        readyChannelRecord(scene, (s8)captainPosition, 0x4F)->playMode = UI_PLAY_BACKWARD;
                        readyChannelRecord(scene, (s8)captainPosition, 0x4F)->flags |= UI_FLAG_VISIBLE;
                    }
                }
                cpuRosterCursorRecord(scene, i)->flags &= ~UI_FLAG_VISIBLE;
            }
            SCENE_RECORD(scene, 0x94)->playMode = UI_PLAY_BACKWARD;
            SCENE_RECORD(scene, 0x96)->playMode = UI_PLAY_BACKWARD;
            SCENE_RECORD(scene, 0x90)->playMode = UI_PLAY_BACKWARD;
            SCENE_RECORD(scene, 0x92)->playMode = UI_PLAY_BACKWARD;
            SCENE_RECORD(scene, 0x98)->flags &= ~UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0xAD)->flags &= ~UI_FLAG_VISIBLE;
        }
        makeCursorUnmovable(channel);
        gameSetUpStep[channel + 0xD] = 1;
    }
}
