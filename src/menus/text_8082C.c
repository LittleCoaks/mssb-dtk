#define SQRT2_LINKAGE static
#include "menus/text_8082C.h"
#include "menus/text_7E380.h"
#include "menus/text_7BFF8.h"
#include "menus/text_78F78.h"
#include "menus/text_76874.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/challenge/challenge_state.h"
#include "text/text.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/orderchange.h"

extern u8 gameSetUpStep[];
extern u8 superstarUnlocked[];
extern u8 lbl_2_bss_100B8[];
extern u8 lbl_2_bss_F468[];
extern int menuCursors[];
extern E(u8, CHAR_ID) challengeCaptainCharIDArray[12];
extern u8 lbl_2_data_2B3A4[];
extern UIRecordDescriptor lbl_2_data_2B59C[];
void fn_2_7630C(MenuScene *scene, u8 channel);
void gfx_cssCharStatBars_and_sthgElse(MenuScene *scene, s32 channel);
void fn_2_CCE0(u8 channel);
void updateCharacterSelectProcessCode(int port, u8 process);

#define SCENE_RECORD(scene, handle) ((UIRecord *)graphicsRelatedArray[(scene)->firstHandle + (handle)].object)
#define STATS_U8(offset) (*(u8 *)((u8 *)&Static_Stats_Tables + (offset)))
#define STATS_SCENE (*(MenuScene **)((u8 *)&Static_Stats_Tables + 0x474C))
#define TEAM_POSITION(index) (((s32 *)lbl_2_bss_F468)[index])
#define PREVIOUS_POSITION(index) (((s32 *)lbl_2_bss_F468)[(index) + 2])
#define FIELD_OFFSET(type, member) ((s32)&(((type *)0)->member))

static inline BOOL isStepClear(u8 step) { return step == 0 ? TRUE : FALSE; }
static inline BOOL isStepActive(u8 step) { return step == 1 ? TRUE : FALSE; }

static inline UIRecord *channelRecord(MenuScene *scene, s32 channel, s32 offset) {
    s32 handle = scene->firstHandle;
    handle += channel;
    handle += offset;
    return (UIRecord *)graphicsRelatedArray[handle].object;
}

static inline UIRecord *rosterRecord(MenuScene *scene, s32 channel, s32 position, s32 offset) {
    s32 handle = scene->firstHandle + position;
    handle += channel * PLAYERS_PER_TEAM;
    handle += offset;
    return (UIRecord *)graphicsRelatedArray[handle].object;
}

static inline s8 captainRosterPosition(s32 channel, E(s32, CHAR_ID) captain) {
    s8 position;
    s32 i;
    s8 *cursor = (s8 *)&cursorPositions;
    for (i = 0; i < PLAYERS_PER_TEAM; i++, cursor++) {
        if (cursor[channel * PLAYERS_PER_TEAM + FIELD_OFFSET(CursorPositions_s, roster.rosterCharID)] == captain) {
            position = cursor[channel * PLAYERS_PER_TEAM + FIELD_OFFSET(CursorPositions_s, roster.positionSwapMapping)];
        }
    }
    return position;
}

static inline s32 findRosterSlot(s32 channel, s32 position) {
    s32 slot;
    s32 i;
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if ((s8)cursorPositions.roster.positionSwapMapping[channel][i] == position) {
            slot = i;
            break;
        }
    }
    return slot;
}

static inline s8 currentRosterPosition(s32 channel) {
    s8 position;
    s32 i;
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if ((s8)cursorPositions.roster.positionSwapMapping[channel][i] == (s8)TEAM_POSITION(channel)) {
            position = (s8)cursorPositions.roster.positionSwapMapping[channel][i];
            break;
        }
    }
    return position;
}

static inline BOOL resetChemStars(MenuScene *scene, s32 channel) {
    s32 count = 0;
    s32 expected = 0;
    s32 i;
    s32 stars = Static_Stats_Tables.startingChemStars[channel];
    for (i = 0; i < stars; i++) {
        expected++;
        count += maybeCheckAndResetGrapicsElement(scene, i + channel * 5 + 0x6E, 30) != 0;
    }
    return count == expected;
}

static inline BOOL resetChannelAnimation(MenuScene *scene, s32 channel, s32 offset, s32 frame) {
    s32 handle = channel;
    handle += offset;
    return maybeCheckAndResetGrapicsElement(scene, handle, frame) != 0;
}

void fn_2_8082C(MenuScene *scene, s32 channel) {
    if (isStepActive(gameSetUpStep[channel + 0xD])) {
        s32 count = resetChannelAnimation(scene, channel, 0x89, 5);
        if (count + (resetChannelAnimation(scene, channel, 0x8B, 10)) == 2) {
            makeCursorMovable(channel);
            gameSetUpStep[channel + 0xD] = 2;
        }
    }
}

#pragma dont_inline on
void fn_2_808D8(MenuScene *scene, s32 channel) {
    int *cursors = menuCursors;
    if (isStepClear(gameSetUpStep[channel + 0xD])) {
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            fn_2_7630C(scene, (u8)channel);
        } else {
            E(u8, CHAR_ID) *choices = challengeCaptainCharIDArray + superstarUnlocked[0xF4] * 6;
            E(s32, CHAR_ID) current = choices[cursors[4]];
            E(s32, CHAR_ID) previous = choices[cursorPositions.cursor[0]];
            u8 currentStar = Static_Stats_Tables.characterStats[current / 9][current % 9].stats.CaptainStarHitPitch;
            u8 previousStar = Static_Stats_Tables.characterStats[previous / 9][previous % 9].stats.CaptainStarHitPitch;
            SCENE_RECORD(scene, 0x82)->frame = lbl_2_data_2B3A4[currentStar] << 16;
            load_Icon(scene, 0x89, 1, 3, lbl_2_data_2B3A4[currentStar]);
            load_Icon(scene, 0x8B, 1, 3, lbl_2_data_2B3A4[previousStar]);
            SCENE_RECORD(scene, 0x7E)->frame = lbl_2_data_2B3A4[currentStar] << 16;
            SCENE_RECORD(scene, 0x80)->frame = 0;
            SCENE_RECORD(scene, 0x89)->frame = 0;
            SCENE_RECORD(scene, 0x8B)->frame = 10 << 16;
            SCENE_RECORD(scene, 0x78)->frame = 0;
            SCENE_RECORD(scene, 0x7C)->frame = 0;
            SCENE_RECORD(scene, 0x80)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, 0x89)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, 0x8B)->playMode = UI_PLAY_BACKWARD;
            SCENE_RECORD(scene, 0x78)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, 0x7C)->playMode = UI_PLAY_FORWARD;
        }
        gfx_cssCharStatBars_and_sthgElse(scene, channel);
        makeCursorUnmovable(channel);
        gameSetUpStep[channel + 0xD] = 1;
    }
}

#pragma dont_inline reset

void fn_2_80B5C(MenuScene *scene, s32 channel) {
    if (isStepActive(gameSetUpStep[channel + 0xD])) {
        s32 count = resetChannelAnimation(scene, channel, 0x0, 0);
        count += resetChannelAnimation(scene, channel, 2, 0);
        count += resetChannelAnimation(scene, channel, 0x89, 10);
        if (count == 3) {
            makeCursorMovable(channel);
            gameSetUpStep[channel + 0xD] = 2;
        }
    }
}

void fn_2_80C2C(MenuScene *scene, s32 channel) {
    if (isStepClear(gameSetUpStep[channel + 0xD])) {
        if (gameSetUpStep[channel + 0x55] != 0) {
            makeCursorMovable(channel);
            gameSetUpStep[channel + 0x5D] = 2;
        }
        SCENE_RECORD(scene, channel)->frame = 20 << 16;
        channelRecord(scene, channel, 2)->frame = 20 << 16;
        SCENE_RECORD(scene, channel)->playMode = UI_PLAY_BACKWARD;
        channelRecord(scene, channel, 2)->playMode = UI_PLAY_BACKWARD;
        channelRecord(scene, channel, 4)->frame = 30 << 16;
        channelRecord(scene, channel, 4)->playMode = UI_PLAY_BACKWARD;
        channelRecord(scene, channel, 0x89)->playMode = UI_PLAY_FORWARD;
        channelRecord(scene, channel, 0x80)->playMode = UI_PLAY_BACKWARD;
        channelRecord(scene, channel, 0x78)->playMode = UI_PLAY_BACKWARD;
        channelRecord(scene, channel, 0x7C)->playMode = UI_PLAY_BACKWARD;
        channelRecord(scene, channel, 0x97)->playMode = UI_PLAY_BACKWARD;
        channelRecord(scene, channel, 0xAC)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, 0x84)->flags &= ~UI_FLAG_VISIBLE;
        makeCursorUnmovable(channel);
        gameSetUpStep[channel + 0xD] = 1;
    }
}

void fn_2_80E0C(MenuScene *scene, s32 channel) {
    if (isStepActive(gameSetUpStep[channel + 0xD])) {
        s32 count = resetChannelAnimation(scene, channel, 0, 20);
        s32 expected = 2;
        count += resetChannelAnimation(scene, channel, 2, 20);
        if (channel == 0 || lbl_2_bss_100B8[0x10] != 0 || g_d_GameSettings.p2_CPU_match_code != P2_CPU_CODE_1_PLAYER_GAME) {
            count += resetChannelAnimation(scene, channel, 0x85, 10);
            count += resetChannelAnimation(scene, channel, 0x87, 10);
            count += resetChannelAnimation(scene, channel, 0x89, 5);
            expected = 6;
            count += resetChannelAnimation(scene, channel, 0x8B, 10);
        }
        if (count == expected) {
            makeCursorMovable(channel);
            gameSetUpStep[channel + 0xD] = 2;
        }
    }
}

void maybeBackgroundImagesForCaptain(MenuScene *scene, s32 channel) {
    u8 *steps = &gameSetUpStep[0xD];
    if (isStepClear(steps[channel])) {
        channelRecord(scene, channel, 0)->elementIndex = 0x47;
        channelRecord(scene, channel, 2)->elementIndex = 0x47;
        channelRecord(scene, channel, 4)->elementIndex = 0x50;
        channelRecord(scene, channel, 0)->frame = 0;
        channelRecord(scene, channel, 2)->frame = 0;
        channelRecord(scene, channel, 0)->playMode = UI_PLAY_FORWARD;
        channelRecord(scene, channel, 2)->playMode = UI_PLAY_FORWARD;
        channelRecord(scene, channel, 4)->frame = 0;
        channelRecord(scene, channel, 4)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, 6)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, 8)->playMode = UI_PLAY_FORWARD;
        channelRecord(scene, channel, 0x12)->flags &= ~UI_FLAG_VISIBLE;
        channelRecord(scene, channel, 0xC)->flags &= ~UI_FLAG_VISIBLE;
        channelRecord(scene, channel, 0x99)->elementIndex = 0x79;
        if (channel != 0 && lbl_2_bss_100B8[0x10] == 0 && g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
            channelRecord(scene, channel, 0x80)->flags &= ~UI_FLAG_VISIBLE;
            channelRecord(scene, channel, 0x7A)->playMode = UI_PLAY_STOP;
            channelRecord(scene, channel, 0x97)->flags &= ~UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x84)->flags |= UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x84)->playMode = UI_PLAY_FORWARD;
        } else {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                SCENE_RECORD(scene, 0x84)->flags &= ~UI_FLAG_VISIBLE;
                SCENE_RECORD(scene, 0x98)->flags &= ~UI_FLAG_VISIBLE;
                SCENE_RECORD(scene, 0xAD)->flags &= ~UI_FLAG_VISIBLE;
            } else if (channel != 0 && g_MatchInfo.player2Ind2 != 0) {
                channelRecord(scene, channel, 0)->elementIndex = 0x47;
                channelRecord(scene, channel, 2)->elementIndex = 0x47;
                channelRecord(scene, channel, 4)->elementIndex = 0x50;
                channelRecord(scene, channel, 0)->frame = 20 << 16;
                channelRecord(scene, channel, 2)->frame = 20 << 16;
                channelRecord(scene, channel, 0)->playMode = UI_PLAY_FORWARD;
                channelRecord(scene, channel, 2)->playMode = UI_PLAY_FORWARD;
                channelRecord(scene, channel, 4)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, 0x84)->flags &= ~UI_FLAG_VISIBLE;
                channelRecord(scene, channel, 0x97)->flags |= UI_FLAG_VISIBLE;
                channelRecord(scene, channel, 0x97)->frame = 0;
                channelRecord(scene, channel, 0x97)->playMode = UI_PLAY_FORWARD;
                channelRecord(scene, channel, 0x7A)->frame = Static_Stats_Tables.playerNumberByPort[1] << 16;
                SCENE_RECORD(scene, 0x19)->frame = Static_Stats_Tables.playerNumberByPort[1] << 16;
                channelRecord(scene, channel, 0x1A)->flags |= UI_FLAG_VISIBLE;
                channelRecord(scene, channel, 0x1A)->playMode = UI_PLAY_FORWARD;
                if (gameSetUpStep[0x5D] == 4 && gameSetUpStep[0xD] == 1) {
                    makeCursorMovable(0);
                    gameSetUpStep[0xD] = 2;
                }
            }
            fn_2_7630C(scene, (u8)channel);
            channelRecord(scene, channel, 0x80)->flags |= UI_FLAG_VISIBLE;
            channelRecord(scene, channel, 0x80)->frame = 0;
            channelRecord(scene, channel, 0x80)->playMode = UI_PLAY_FORWARD;
            channelRecord(scene, channel, 0x85)->frame = 0;
            channelRecord(scene, channel, 0x87)->frame = 0;
            channelRecord(scene, channel, 0x85)->playMode = UI_PLAY_FORWARD;
            channelRecord(scene, channel, 0x87)->playMode = UI_PLAY_FORWARD;
            channelRecord(scene, channel, 0x89)->frame = 0;
            channelRecord(scene, channel, 0x8B)->frame = 5 << 16;
            channelRecord(scene, channel, 0x89)->playMode = UI_PLAY_FORWARD;
            channelRecord(scene, channel, 0x8B)->playMode = UI_PLAY_FORWARD;
            channelRecord(scene, channel, 0x78)->frame = 0;
            channelRecord(scene, channel, 0x78)->playMode = UI_PLAY_FORWARD;
            channelRecord(scene, channel, 0x7C)->frame = 0;
            channelRecord(scene, channel, 0x7C)->playMode = UI_PLAY_FORWARD;
            gfx_cssCharStatBars_and_sthgElse(scene, channel);
            channelRecord(scene, channel, 0xAC)->flags &= ~UI_FLAG_VISIBLE;
        }
        makeCursorUnmovable(channel);
        steps[channel] = 1;
    }
}
void cssActions(void) {
    MenuScene *scene = STATS_SCENE;
    s32 channel;
    if (STATS_U8(0x48B2) != 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct *)scene);
        removeCurrentDrawingItem();
    }
    if (gameSetUpStep[0] == 1) {
        for (channel = 0; channel < 2; channel++) {
            switch (gameSetUpStep[channel + 0x5D]) {
            case 1:
                maybeBackgroundImagesForCaptain(scene, channel);
                fn_2_80E0C(scene, channel);
                break;
            case 2:
                fn_2_80C2C(scene, channel);
                fn_2_80B5C(scene, channel);
                break;
            case 3:
                fn_2_808D8(scene, channel);
                fn_2_8082C(scene, channel);
                break;
            case 4:
                fn_2_805DC(scene, channel);
                break;
            case 5:
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
                break;
            case 6:
                fn_2_802EC(scene);
                break;
            case 7:
                captainSelectUnloadCSSLoadRelated(scene, channel);
                break;
            case 8:
                fn_2_7FAFC(scene, channel);
                break;
            }
            removeAllPlayersFromTeam(scene, channel);
            if (channel != 0 && (SCENE_RECORD(scene, 6)->frame >> 16) == 60) {
                SCENE_RECORD(scene, 7)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, 9)->playMode = UI_PLAY_FORWARD;
            }
        }
    } else if (gameSetUpStep[0] == 2) {
        for (channel = 0; channel < 2; channel++) {
            switch (gameSetUpStep[channel + 0x5D]) {
            case 9:
                cssAction_case9(scene, channel);
                break;
            case 0xA:
                fn_2_7AE3C(scene, channel);
                fn_2_7AC64(scene, channel);
                break;
            case 0xB:
                fn_2_7A9D8(scene, channel);
                fn_2_7A748(scene, channel);
                break;
            case 0xE:
                fn_2_7DAB8(scene, channel);
                fn_2_7D85C(scene, channel);
                break;
            case 0xF:
                cssSelectCharacter(scene, channel);
                if (gameSetUpStep[channel + 0xD] == 1) {
                    s8 position = currentRosterPosition(channel);
                    s32 ready = maybeCheckAndResetGrapicsElement(scene, position + channel * PLAYERS_PER_TEAM + 0x34, 10) != 0;
                    if (resetChemStars(scene, channel) && ready == 1) {
                        makeCursorMovable(channel);
                        fn_2_CCE0((u8)channel);
                    }
                }
                break;
            case 0x10:
                cssRemoveCharacter1(scene, channel);
                cssRemoveCharacter2(scene, channel);
                break;
            case 0xC: {
                s32 i;
                for (i = 0; i < PLAYERS_PER_TEAM; i++) {
                    if (i == TEAM_POSITION(channel)) rosterRecord(scene, channel, i, 0x22)->flags |= UI_FLAG_VISIBLE;
                }
                break;
            }
            case 0xD:
                if (lbl_2_bss_F468[channel + 0x41] != 0) {
                    rosterRecord(scene, channel, TEAM_POSITION(channel), 0x22)->flags &= ~UI_FLAG_VISIBLE;
                } else {
                    rosterRecord(scene, channel, TEAM_POSITION(channel), 0x22)->flags |= UI_FLAG_VISIBLE;
                }
                gfx_cssCharStatBars_and_sthgElse(scene, channel);
                gameSetUpStep[channel + 0x5D] = 0;
                if (lbl_2_bss_F468[channel + 0x59] != 0) updateCharacterSelectProcessCode(channel, 0x1A);
                break;
            case 0x11:
                cssReady(scene, channel);
                if (gameSetUpStep[channel + 0xD] == 1) {
                    s32 ready = maybeCheckAndResetGrapicsElement(scene, channel + 0xC, 10) != 0;
                    ready += maybeCheckAndResetGrapicsElement(scene, channel + 0xE, 14) != 0;
                    ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x12, 10) != 0;
                    ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x1C, 20) != 0;
                    ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x6A, 30) != 0;
                    if (ready == 5) {
                        makeCursorMovable(channel);
                        gameSetUpStep[channel + 0xD] = 2;
                    }
                }
                break;
            case 0x12:
                cssUnready(scene, channel);
                if (gameSetUpStep[channel + 0xD] == 1) {
                    s32 ready = maybeCheckAndResetGrapicsElement(scene, channel + 0x1C, 10) != 0;
                    s32 expected = 3;
                    ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x6A, 10) != 0;
                    ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x89, 5) != 0;
                    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && channel == 0) {
                        s8 position = captainRosterPosition(1, Static_Stats_Tables.captainSelectedID[1]);
                        expected = 4;
                        ready += maybeCheckAndResetGrapicsElement(scene, position + 0x3D, 20) != 0;
                    }
                    if (ready == expected) {
                        makeCursorMovable(channel);
                        gameSetUpStep[channel + 0xD] = 2;
                    }
                }
                break;
            case 0x13:
                fn_2_7A5B8(scene, channel);
                if (gameSetUpStep[channel + 0xD] == 1) {
                    s32 ready = maybeCheckAndResetGrapicsElement(scene, channel, 40) != 0;
                    ready += maybeCheckAndResetGrapicsElement(scene, channel + 2, 40) != 0;
                    ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x85, 30) != 0;
                    ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x1C, 30) != 0;
                    ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x6A, 50) != 0;
                    if (ready == 5) {
                        channelRecord(scene, channel, 0xC)->flags &= ~UI_FLAG_VISIBLE;
                        channelRecord(scene, channel, 0x12)->flags &= ~UI_FLAG_VISIBLE;
                        makeCursorMovable(channel);
                        gameSetUpStep[channel + 0xD] = 2;
                    }
                }
                break;
            case 0x14:
                fn_2_7A194(scene, channel);
                if (gameSetUpStep[channel + 0xD] == 1) {
                    s32 ready = 0;
                    s32 expected = 0;
                    s8 slot = findRosterSlot(channel, PREVIOUS_POSITION(channel));
                    E(s32, CHAR_ID) character = cursorPositions.roster.rosterCharID[channel][slot];
                    if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS && PREVIOUS_POSITION(channel) < PLAYERS_PER_TEAM) {
                        expected = 1;
                        ready = maybeCheckAndResetGrapicsElement(scene, PREVIOUS_POSITION(channel) + channel * PLAYERS_PER_TEAM + 0x34, 20) != 0;
                    }
                    if (ready == expected) {
                        makeCursorMovable(channel);
                        gameSetUpStep[channel + 0xD] = 2;
                    }
                }
                break;
            case 0x15:
                fn_2_79CF8(scene, channel);
                if (gameSetUpStep[channel + 0xD] == 1) {
                    s32 ready = 0;
                    s32 expected = 0;
                    s8 position = TEAM_POSITION(channel);
                    s32 slot = findRosterSlot(channel, position);
                    if (cursorPositions.roster.rosterCharID[channel][slot] != CHAR_ID_NONE) {
                        expected = 1;
                        ready = maybeCheckAndResetGrapicsElement(scene, position + channel * PLAYERS_PER_TEAM + 0x34, 10) != 0;
                    }
                    if (ready == expected) {
                        makeCursorMovable(channel);
                        gameSetUpStep[channel + 0xD] = 2;
                    }
                }
                break;
            case 0x16:
                randomTeamMemberSelection(scene, channel);
                if (gameSetUpStep[channel + 0xD] == 1) {
                    s32 ready = 0;
                    s32 expected = 0;
                    s32 i;
                    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
                        expected++;
                        ready += maybeCheckAndResetGrapicsElement(scene, i + channel * PLAYERS_PER_TEAM + 0x34, 20) != 0;
                    }
                    if (resetChemStars(scene, channel) && ready == expected) {
                        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
                            if ((s8)cursorPositions.roster.rosterSpotFilledInd[channel][i] == 0) cursorPositions.roster.rosterSpotFilledInd[channel][i] = TRUE;
                        }
                        makeCursorMovable(channel);
                        gameSetUpStep[channel + 0xD] = 2;
                    }
                }
                break;
            case 0x17:
                if (gameSetUpStep[channel + 0xD] == 0) {
                    s32 i;
                    for (i = 0; i < PLAYERS_PER_TEAM; i++) rosterRecord(scene, channel, i, 0x46)->playMode = UI_PLAY_BACKWARD;
                    channelRecord(scene, channel, 0x95)->frame = 10 << 16;
                    channelRecord(scene, channel, 0x95)->playMode = UI_PLAY_FORWARD;
                }
                if (gameSetUpStep[channel + 0xD] == 1) {
                    makeCursorMovable(channel);
                    gameSetUpStep[channel + 0xD] = 2;
                }
                break;
            case 0x18: cssAction_0x18(scene, channel); break;
            case 0x19: cssAction_0x19(scene, channel); break;
            case 0x1A: cssAction_0x1a(scene, channel); break;
            case 0x1B: cssAction_0x1b(scene, channel); break;
            case 0x1C: cssAction_0x1c(scene, channel); break;
            case 0x1D: cssAction_0x1d(scene, channel); break;
            }
            removeAllPlayersFromTeam(scene, channel);
        }
        if (channel != 0 && (SCENE_RECORD(scene, 6)->frame >> 16) == 60) {
            SCENE_RECORD(scene, 7)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, 9)->playMode = UI_PLAY_FORWARD;
        }
    }
    if (STATS_U8(0x48B1) != 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct *)scene);
        removeCurrentDrawingItem();
    }
}
void relatedToTeamSelection3(void) {
    MenuScene *scene = (MenuScene *)currentDrawingItem;
    s32 channel;
    s32 i;
    STATS_SCENE = scene;
    addGraphicsElementToScene((DrawingSceneStruct *)scene, lbl_2_data_2B59C);
    for (channel = 0; channel < 2; channel++) {
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && channel != 0) {
            s8 port;
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                port = 1;
                if (Static_Stats_Tables.playerNumberByPort[0] != 0) port = 0;
            }
            channelRecord(scene, channel, 0x7A)->frame = port << 16;
            channelRecord(scene, channel, 0x18)->frame = (port + 4) << 16;
        } else {
            s32 frame;
            BOOL cpu = FALSE;
            channelRecord(scene, channel, 0x7A)->frame = Static_Stats_Tables.playerNumberByPort[channel] << 16;
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && channel != 0) cpu = TRUE;
            if (cpu) {
                s32 port = Static_Stats_Tables.playerNumberByPort[channel];
                if (port == -1) frame = (channel != 0) + 4;
                else frame = port + 4;
            } else {
                frame = Static_Stats_Tables.playerNumberByPort[channel];
            }
            channelRecord(scene, channel, 0x18)->frame = frame << 16;
        }
        channelRecord(scene, channel, 0x1A)->flags &= ~UI_FLAG_VISIBLE;
        channelRecord(scene, channel, 0xB2)->flags &= ~UI_FLAG_VISIBLE;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        E(s32, CHAR_ID) captain;
        u8 star;
        SCENE_RECORD(scene, 0x98)->flags &= ~UI_FLAG_VISIBLE;
        captain = (s16)g_Challenge.captainCharID;
        star = Static_Stats_Tables.characterStats[captain / 9][captain % 9].stats.CaptainStarHitPitch;
        load_Icon(scene, 0x89, 1, 3, lbl_2_data_2B3A4[star]);
        load_Icon(scene, 0x8B, 1, 3, lbl_2_data_2B3A4[star]);
        captain = (s8)g_Challenge.opponentCaptainCharID;
        star = Static_Stats_Tables.characterStats[captain / 9][captain % 9].stats.CaptainStarHitPitch;
        load_Icon(scene, 0x8A, 1, 3, lbl_2_data_2B3A4[star]);
        load_Icon(scene, 0x8C, 1, 3, lbl_2_data_2B3A4[star]);
    }
    for (i = 0; i < 10; i++) {
        channelRecord(scene, i, 0x6E)->frame = 0;
        channelRecord(scene, i, 0x6E)->playMode = UI_PLAY_STOP;
    }
    SCENE_RECORD(scene, 0x1C)->flags &= ~UI_FLAG_VISIBLE;
    SCENE_RECORD(scene, 0x1D)->flags &= ~UI_FLAG_VISIBLE;
    SCENE_RECORD(scene, 0x1E)->flags &= ~UI_FLAG_VISIBLE;
    SCENE_RECORD(scene, 0x1F)->flags &= ~UI_FLAG_VISIBLE;
    SCENE_RECORD(scene, 0x84)->flags &= ~UI_FLAG_VISIBLE;
    SCENE_RECORD(scene, 0xAE)->flags &= ~UI_FLAG_VISIBLE;
    SCENE_RECORD(scene, 0xAF)->flags &= ~UI_FLAG_VISIBLE;
    STATS_U8(0x48B2) = FALSE;
    STATS_U8(0x48B1) = FALSE;
    *(s16 *)((u8 *)&Static_Stats_Tables + 0x4760) = 0;
    currentDrawingItem->func = cssActions;
}
