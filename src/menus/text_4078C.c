#include "menus/text_4078C.h"
#include "text/text.h"
#include "game/match_setup/match_loading.h"
#include "Unknown/graphic.h"
#include "Dolphin/vec.h"
#include "Unknown/File_0x800b0a14.h"
#include "game/challenge/star_mission_data.h"
#include "game/UnknownHomes_Game.h"
#include "challenge/challenge_progress.h"
#include "menus/text_3A8FC.h"
#include "menus/text_3C03C.h"
#include "menus/text_3E38C.h"
#include "menus/text_37F04.h"
#include "menus/text_42BE8.h"
#include "menus/text_44F14.h"
#include "menus/text_50898.h"

// Local prototypes and externs for symbols owned by other units.
void fn_2_399C0(void);
void fn_2_3BD88(void);
void fn_2_72054(s32 index, u8 state);
void fn_80062890(s32 arg);
void fn_800111B4(void *bank);
void fn_2_20218(void);
void fn_2_1BF50(void);
void fn_2_1BFD0(void);
void *ARAMTransfer(void *file, s32 arg1, s32 arg2, s32 arg3);
void *memcpy(void *dest, const void *src, u32 n);

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A8230;
extern u8 lbl_803C6CF8[];
extern u8 AtBat_ButtonInput1[];
extern u8 hugeAnimStruct[];
extern u8 menuNumber[];
extern u8 challengeDialogueTextFileDescriptor[];
extern void *lbl_2_data_12C0C[];
extern void *lbl_2_data_12CE8[];
extern s16 lbl_2_data_36EC[];
extern u8 lbl_2_bss_15B8[];

void fn_2_38538(void);
void fn_2_38A40(void);
void fn_2_6AF80(s32 index, u8 value);
s32 fn_2_6AFD4(s32 index);
extern u8 *lbl_2_bss_1A823C;

static inline ChallengeState *challengeState(void) {
    return (ChallengeState *)lbl_2_bss_1A8248;
}

extern u8 CharacterHandFiles[];
extern u8 HandPoseEventSetFiles[];
void fn_2_487A0(void);

Vec lbl_2_data_12EA8 = {0.8f, 0.8f, 0.8f};
Vec lbl_2_data_12EB4 = {0.8f, 0.8f, 0.8f};

struct {
    MatchFileDescriptor files[54];
    void *handFiles;
    void *handPoseEventSets;
} lbl_2_data_12EC0 = {
    {
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x400431B4, 0x0EB1D800, 0x0002B22C},
        {0x0000040B, 0x400396A0, 0x0EB49000, 0x00026ED4},
        {0x0000040B, 0x4003ED8C, 0x0EB70000, 0x00028C4C},
        {0x0000040B, 0x40036944, 0x0EB99000, 0x00022DF4},
        {0x0000040B, 0x40039B44, 0x0EBBC000, 0x00026618},
        {0x0000040B, 0x400320E4, 0x0EBE2800, 0x00021E2C},
        {0x0000040B, 0x40030878, 0x0EC04800, 0x0001DD80},
        {0x0000040B, 0x4002D3C4, 0x0EC22800, 0x0001B3EC},
        {0x0000040B, 0x40035258, 0x0EC3E000, 0x000238DC},
        {0x0000040B, 0x40041ED0, 0x0EC62000, 0x00029B84},
        {0x0000040B, 0x400414AC, 0x0EC8C000, 0x0002D160},
        {0x0000040B, 0x4002E988, 0x0ECB9800, 0x0001E0BC},
        {0x0000040B, 0x4002FED0, 0x0ECD8000, 0x0001C398},
        {0x0000040B, 0x4001FF28, 0x0ECF4800, 0x00015000},
        {0x0000040B, 0x40032CF4, 0x0ED09800, 0x0001F4E4},
        {0x0000040B, 0x40021EF4, 0x0ED29000, 0x00015114},
        {0x0000040B, 0x40038998, 0x0ED3E800, 0x00023948},
        {0x0000040B, 0x4001CE38, 0x0ED62800, 0x00011B30},
        {0x0000040B, 0x40032FDC, 0x0ED74800, 0x00021154},
        {0x0000040B, 0x4002ED24, 0x0ED96000, 0x0001E94C},
        {0x0000040B, 0x40031490, 0x0EDB5000, 0x0001F824},
        {0x0000040B, 0x40030370, 0x0EDD5000, 0x0001EB70},
        {0x0000040B, 0x40030370, 0x0EDF4000, 0x0001EB70},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x40032428, 0x0EE58000, 0x0001F020},
        {0x0000040B, 0x40036CD8, 0x0EE77800, 0x00023828},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x40029748, 0x0F08B800, 0x0001ABF4},
        {0x0000040B, 0x40029748, 0x0F08B800, 0x0001ABF4},
        {0x0000040B, 0x40029748, 0x0F08B800, 0x0001ABF4},
        {0x0000040B, 0x40029748, 0x0F08B800, 0x0001ABF4},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
        {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    },
    CharacterHandFiles,
    HandPoseEventSetFiles
};

DrawCallbackNode lbl_2_data_13228[2] = {{2, fn_2_487A0}, {2, fn_2_487A0}};
u16 lbl_2_data_13238[2] = {22, 11};

MatchFileDescriptor lbl_2_data_1323C =
    {0x0000040B, 0x400B2CB8, 0x18E3F000, 0x00053454};

MatchFileDescriptor menuBarsFileDescriptor =
    {0x0000040B, 0x40076AE0, 0x18ED7000, 0x00036BC8};

MatchFileDescriptor stadiumPreviewsFileDescriptor =
    {0x0000040B, 0x4011EC24, 0x18F0E000, 0x000D8818};

MatchFileDescriptor ChallengeTexFiles[7] = {
    {0x0000040B, 0x40069DFC, 0x18E92800, 0x000408D0},
    {0x0000040B, 0x4009947C, 0x18FE7000, 0x0002F758},
    {0x0000040B, 0x4006DC60, 0x19016800, 0x00024F50},
    {0x0000040B, 0x400A2AB4, 0x1903B800, 0x000371F8},
    {0x0000040B, 0x400A97F4, 0x19073000, 0x00048EEC},
    {0x0000040B, 0x4007B2D0, 0x190BC000, 0x0002B520},
    {0x0000040B, 0x400AF4E8, 0x190E7800, 0x0004D804},
};

MatchFileDescriptor menuFontFileDescriptor =
    {0x0000040B, 0x4023491C, 0x19135800, 0x00082928};


Vec lbl_2_data_132EC = {0.0f, 0.0f, 0.0f};
Vec lbl_2_data_132F8 = {0.0f, 0.0f, 0.0f};
Vec lbl_2_data_13304 = {0.0f, 0.0f, 0.0f};

// Work area behind lbl_2_bss_1A824C (the 0x190000 window).
#define WORK_BASE() (lbl_2_bss_1A824C + 0x190000)
#define UI_1A8234() (lbl_2_bss_1A8234 + 0x160000)
#define UI_1A8230() (lbl_2_bss_1A8230 + 0x30000)

// Per-frame scene scratch: the linked parent is notified through its state;
// this node owns the signed timer, child completion flag and phase byte.
typedef struct MenuDrawItem {
    /* 0x00 */ u8 unk00[0x0C];
    /* 0x0C */ DrawingSceneStruct *node;
    /* 0x10 */ s16 childDone;
    /* 0x12 */ u16 priority;
    /* 0x14 */ s16 timer;
    /* 0x16 */ u8 unk16[0x28 - 0x16];
    /* 0x28 */ s8 state;
} MenuDrawItem;

#define WORK_U32(off) (*(u32 *)(WORK_BASE() + (off)))
#define WORK_S16(off) (*(s16 *)(WORK_BASE() + (off)))
#define SCRIPT() (*(u32 **)(WORK_BASE() + 0x7684))

static inline void advanceScript(s32 words) {
    SCRIPT() += words;
}

static inline void startScriptChild(MenuDrawItem *item, void (*callback)(void)) {
    MenuDrawItem *child = (MenuDrawItem *)insertGraphicDrawingFunction(callback, 2);
    child->state = 0;
    item->childDone = 0;
}

static inline void startScriptDialogue(MenuDrawItem *item, s16 line, s32 words) {
    fn_2_50CC0(line);
    item->childDone = 0;
    advanceScript(words);
}

// .text:0x00042708 size:0x4E0 mapped:0x8068179C
void fn_2_42708(void) {
    E(s32, CHAR_ID) charID;
    s32 mission;
    for (charID = 0; charID < ARRAY_COUNT(characterStaticIndexes); charID++) {
        if (characterStaticIndexes[charID].hasOwnStarMissions == TRUE &&
            challengeState()->characters[charID].recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
            ChallengeTrackingStruct *character = &challengeState()->characters[charID];
            for (mission = 0; mission < STAR_MISSIONS_PER_CHARACTER; mission++) {
                StarMissionDisplayRule *rule = &starMissionDisplayRules[characterStaticIndexes[charID].requirementRow][mission];
                E(s16, STAR_MISSION_TYPE) type = starMissionRequirementsTable[characterStaticIndexes[charID].requirementRow][mission].type;
                s16 mode = rule->mode;
                s16 minStars = rule->minStars;
                s16 minScoutRow = rule->minScoutRow;
                s16 difficulty = rule->_8;
                if (mode != -1 && (s8)character->inGameMissionTracker[mission].shownOnPauseMenu == FALSE) {
                    switch (mode) {
                    case 0:
                    case 2:
                    case 18:
                    case 19:
                        break;
                    case 1:
                        if (fn_8006CDC0(charID) >= minStars && challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 3:
                        if ((lbl_2_bss_1A8248[0x4428] & 1) && challengeState()->difficulty >= minStars)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 4:
                        if ((lbl_2_bss_1A8248[0x4428] & 2) && challengeState()->difficulty >= minStars)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 5:
                        if ((lbl_2_bss_1A8248[0x4428] & 4) && challengeState()->difficulty >= minStars)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 6:
                        if ((lbl_2_bss_1A8248[0x4428] & 8) && challengeState()->difficulty >= minStars)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 7:
                        if ((lbl_2_bss_1A8248[0x4428] & 16) && challengeState()->difficulty >= minStars)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 8:
                        if ((lbl_2_bss_1A8248[0x4428] & 1) && challengeState()->captain == minStars &&
                            challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 9:
                        if ((lbl_2_bss_1A8248[0x4428] & 2) && challengeState()->captain == minStars &&
                            challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 10:
                        if ((lbl_2_bss_1A8248[0x4428] & 4) && challengeState()->captain == minStars &&
                            challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 11:
                        if ((lbl_2_bss_1A8248[0x4428] & 8) && challengeState()->captain == minStars &&
                            challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 12:
                        if ((lbl_2_bss_1A8248[0x4428] & 16) && challengeState()->captain == minStars &&
                            challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    case 13: {
                        BOOL recruited = challenge_isCharRecruited(charID);
                        if ((lbl_2_bss_1A8248[0x4428] & 1) && recruited == TRUE &&
                            challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    }
                    case 14: {
                        BOOL recruited = challenge_isCharRecruited(charID);
                        if ((lbl_2_bss_1A8248[0x4428] & 2) && recruited == TRUE &&
                            challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    }
                    case 15: {
                        BOOL recruited = challenge_isCharRecruited(charID);
                        if ((lbl_2_bss_1A8248[0x4428] & 4) && recruited == TRUE &&
                            challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    }
                    case 16: {
                        BOOL recruited = challenge_isCharRecruited(charID);
                        if ((lbl_2_bss_1A8248[0x4428] & 8) && recruited == TRUE &&
                            challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    }
                    case 17: {
                        BOOL recruited = challenge_isCharRecruited(charID);
                        if ((lbl_2_bss_1A8248[0x4428] & 16) && recruited == TRUE &&
                            challengeState()->difficulty >= minScoutRow)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    }
                    case 20:
                        if (challengeState()->captain == minStars && *(s16 *)(lbl_2_bss_1A8248 + 0x43BC) >= minScoutRow &&
                            challengeState()->difficulty >= difficulty)
                            character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
                        break;
                    }
                }
                if (type != STAR_MISSION_TYPE_NONE && character->inGameMissionTracker[mission].starMissionStatus < 0)
                    character->inGameMissionTracker[mission].shownOnPauseMenu = TRUE;
            }
        }
    }
}

// .text:0x00042638 size:0xD0 mapped:0x806816CC
void fn_2_42638(void) {
    s32 i;
    for (i = 0; i < 20; i++) {
        lbl_2_bss_1A824C[0x1978C7 + i] = lbl_2_bss_1A8248[0x43C2 + i];
    }
}

// .text:0x00042490 size:0x1A8 mapped:0x80681524
void fn_2_42490(void) {
    s32 i;
    s32 count;
    s16 *eligible;

    for (i = 0; i < 20; i++) {
        lbl_2_bss_1A824C[0x1978DB + i] = 0;
    }

    count = 0;
    eligible = lbl_2_data_36EC;
    for (i = 0; i < 20; i++) {
        if (*(s8 *)(WORK_BASE() + 0x78C7 + i) == 0 &&
            challengeState()->_43C2[i] == 1 && *eligible == 1) {
            *(u8 *)(WORK_BASE() + 0x78DB + count++) = i;
        }
        eligible++;
    }
    *(u8 *)(WORK_BASE() + 0x78EF) = count;
}

// .text:0x00042474 size:0x1C mapped:0x80681508
void fn_2_42474(void) {
    *(s16 *)(WORK_BASE() + 0x76E4) = 0x78;
}

// .text:0x00042388 size:0xEC mapped:0x8068141C
void fn_2_42388(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        *(s16 *)(WORK_BASE() + 0x76E4) = 0x78;
        item->state = 1;
        break;
    case 1:
        if (fn_2_40CB8() != FALSE) {
            item->state = 2;
        }
        break;
    case 2:
        item->node->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }

    if (*(u8 *)(WORK_BASE() + 0x783F) == TRUE) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
    }
}

// .text:0x000422FC size:0x8C mapped:0x80681390
void fn_2_422FC(s32 index) {
    *(u32 *)(WORK_BASE() + 0x7694) = 0;
    *(u32 *)(WORK_BASE() + 0x768C) = 0;
    *(u32 *)(WORK_BASE() + 0x7690) = 0;
    memcpy(lbl_2_bss_15B8, lbl_2_data_12C0C[index], 0x4000);
    *(u8 **)(WORK_BASE() + 0x7684) = lbl_2_bss_15B8;
}

// .text:0x00042270 size:0x8C mapped:0x80681304
void fn_2_42270(s32 index) {
    *(u32 *)(WORK_BASE() + 0x7694) = 0;
    *(u32 *)(WORK_BASE() + 0x768C) = 0;
    *(u32 *)(WORK_BASE() + 0x7690) = 0;
    memcpy(lbl_2_bss_15B8, lbl_2_data_12CE8[index], 0x4000);
    *(u8 **)(WORK_BASE() + 0x7684) = lbl_2_bss_15B8;
}

// .text:0x00040CB8 size:0x15B8 mapped:0x8067FD4C
s32 fn_2_40CB8(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;
    if (WORK_U32(0x768C) != 0) {
        WORK_U32(0x768C)--;
        return FALSE;
    }
    for (;;) {
        switch (SCRIPT()[0]) {
        case 0:
        case 4:
        case 92:
        case 93:
            return FALSE;
        case 1:
            WORK_U32(0x7694) = 0;
            advanceScript(1);
            continue;
        case 2:
            WORK_U32(0x7694) = 1;
            return TRUE;
        case 3:
            WORK_U32(0x768C) = SCRIPT()[1];
            advanceScript(2);
            return FALSE;
        case 5:
            startScriptDialogue(item, SCRIPT()[1], 2);
            continue;
        case 27: {
            s16 line;
            ChallengeState *challenge = challengeState();
            if (challenge->_44EF == 0) {
                s32 opponent = challenge->opponentCaptain;
                u32 mask = 1 << opponent;
                if (!(lbl_2_bss_1A8248[0x4427] & mask))
                    line = 0x4B + challenge->captain * 6 + opponent;
                else if (!(lbl_2_bss_1A8248[0x4426] & mask))
                    line = 0x93 + challenge->captain * 6 + opponent;
                else if ((s8)lbl_2_bss_1A8248[0x44FE + opponent] == 0)
                    line = 3 + challenge->captain * 6 + opponent;
                else
                    line = 0x93 + challenge->captain * 6 + opponent;
            } else {
                line = challenge->_44F0 == 0 ? 0x22C : 0x22D;
            }
            startScriptDialogue(item, line, 1);
            continue;
        }
        case 28: {
            s16 line;
            if (fn_2_45938(challengeState()->_16C2) == TRUE)
                line = 0x124 + challengeState()->captain * 6 + challengeState()->opponentCaptain;
            else
                line = 0x148 + challengeState()->captain * 6 + challengeState()->opponentCaptain;
            startScriptDialogue(item, line, 1);
            continue;
        }
        case 72: {
            s16 line;
            if (challengeState()->_44EF == 0)
                line = 0x190 + challengeState()->captain * 6 + challengeState()->opponentCaptain;
            else
                line = 0x232;
            startScriptDialogue(item, line, 1);
            continue;
        }
        case 29: {
            s16 line;
            if (challengeState()->_44EF == 0)
                line = 0x16C + challengeState()->captain * 6 + challengeState()->opponentCaptain;
            else
                line = 0x231;
            startScriptDialogue(item, line, 1);
            continue;
        }
        case 30: {
            s16 line;
            if ((s8)lbl_2_bss_1A8248[0x4504] == 0)
                line = 0x1B4 + lbl_2_bss_1A8248[0x442C] * 6 + challengeState()->captain;
            else
                line = 0x1CC + lbl_2_bss_1A8248[0x442D] * 6 + challengeState()->captain;
            startScriptDialogue(item, line, 1);
            continue;
        }
        case 31:
            startScriptDialogue(item, 0x1E4 + lbl_2_bss_1A8248[0x442C] * 6 + challengeState()->captain, 1);
            continue;
        case 32:
            startScriptDialogue(item, 0x1FC + lbl_2_bss_1A8248[0x442D] * 6 + challengeState()->captain, 1);
            continue;
        case 73:
            startScriptDialogue(item, 0x214 + lbl_2_bss_1A8248[0x442E] * 6 + challengeState()->captain, 1);
            continue;
        case 6:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 7:
            *(u8 *)(WORK_BASE() + 0x783D) = TRUE;
            if (*(s16 *)(lbl_2_bss_1A823C + 0x30) == 4) {
                fn_2_72054(0, 12);
                challengeState()->_16C0 = *(s16 *)(lbl_2_bss_1A8248 + 0x16BE);
            } else {
                fn_2_6AF80(0, 1);
            }
            advanceScript(1);
            continue;
        case 8:
            if (fn_2_6AFD4(0) == 1) advanceScript(1);
            return FALSE;
        case 9:
            startScriptChild(item, fn_2_405B4);
            advanceScript(1);
            continue;
        case 10:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 15:
            startScriptChild(item, fn_2_4041C);
            advanceScript(1);
            continue;
        case 16:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 11:
            advanceScript(1);
            continue;
        case 12:
            advanceScript(1);
            return FALSE;
        case 13:
            advanceScript(1);
            continue;
        case 14:
            advanceScript(1);
            return FALSE;
        case 33:
            if (*(s16 *)(lbl_2_bss_1A8248 + 0x43BE) < 999) {
                startScriptChild(item, fn_2_3FA14);
            } else {
                WORK_S16(0x7740) = 1;
                item->childDone = 1;
            }
            advanceScript(1);
            continue;
        case 34:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 35:
            if (*(s16 *)(lbl_2_bss_1A8248 + 0x43BE) > 0) {
                startScriptChild(item, fn_2_3F66C);
            } else {
                WORK_S16(0x7740) = 1;
                item->childDone = 1;
            }
            advanceScript(1);
            continue;
        case 36:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 37:
            startScriptChild(item, fn_2_3F55C);
            advanceScript(1);
            continue;
        case 38:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 39:
            startScriptChild(item, fn_2_3F44C);
            advanceScript(1);
            continue;
        case 40:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 17:
            startScriptChild(item, fn_2_3FDE0);
            advanceScript(1);
            continue;
        case 18:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 19:
            fn_2_72054(1, 14);
            advanceScript(1);
            continue;
        case 20:
            if (fn_2_6AFD4(1) == 1) advanceScript(1);
            return FALSE;
        case 107:
            if (WORK_S16(0x7740) == 1) {
                WORK_S16(0x7740) = 0;
                advanceScript(1);
            }
            return FALSE;
        case 21:
            fn_2_72054(0, 2);
            advanceScript(1);
            continue;
        case 22:
            if (fn_2_6AFD4(0) == 1) advanceScript(1);
            return FALSE;
        case 23:
            startScriptChild(item, fn_2_38A40);
            WORK_U32(0x7688) = SCRIPT()[0];
            SCRIPT()[0] = 24;
            continue;
        case 24:
            if (item->childDone == 1) {
                SCRIPT()[0] = WORK_U32(0x7688);
                advanceScript(1);
            }
            return FALSE;
        case 25:
            *(u8 *)(WORK_BASE() + 0x7844) = 2;
            *(u8 *)(UI_1A8234() + 0x2871) = TRUE;
            *(u8 *)(UI_1A8234() + 0x2872) = TRUE;
            startScriptChild(item, fn_2_38538);
            WORK_U32(0x7688) = SCRIPT()[0];
            SCRIPT()[0] = 26;
            continue;
        case 26:
            if (item->childDone == 1) {
                SCRIPT()[0] = WORK_U32(0x7688);
                advanceScript(1);
            }
            return FALSE;
        case 41:
            startScriptChild(item, fn_2_3F29C);
            WORK_U32(0x7688) = SCRIPT()[0];
            advanceScript(1);
            continue;
        case 42:
            if (item->childDone == 1) {
                SCRIPT()[0] = WORK_U32(0x7688);
                advanceScript(1);
            }
            return FALSE;
        case 43:
            startScriptChild(item, fn_2_3EA44);
            advanceScript(1);
            continue;
        case 44:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 45:
            startScriptChild(item, fn_2_3E7EC);
            advanceScript(1);
            continue;
        case 46:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 47:
            startScriptChild(item, fn_2_3E918);
            advanceScript(1);
            continue;
        case 48:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 49:
            startScriptChild(item, fn_2_3F188);
            advanceScript(1);
            continue;
        case 50:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 51:
            startScriptChild(item, fn_2_3F004);
            advanceScript(1);
            continue;
        case 52:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 53:
            startScriptChild(item, fn_2_3EEF0);
            advanceScript(1);
            continue;
        case 54:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 55:
            startScriptChild(item, fn_2_3EDD8);
            advanceScript(1);
            continue;
        case 56:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 57:
            startScriptChild(item, fn_2_3ECC0);
            advanceScript(1);
            continue;
        case 58:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 59:
            startScriptChild(item, fn_2_3EBA8);
            advanceScript(1);
            continue;
        case 60:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 61:
            startScriptChild(item, fn_2_408BC);
            advanceScript(1);
            continue;
        case 62:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 63:
            WORK_S16(0x774C) = SCRIPT()[1];
            *(u8 *)(UI_1A8234() + 0x264e) = TRUE;
            advanceScript(2);
            continue;
        case 65:
            WORK_S16(0x774C) = SCRIPT()[1];
            *(u8 *)(UI_1A8234() + 0x264f) = TRUE;
            advanceScript(2);
            continue;
        case 64:
            *(u8 *)(UI_1A8234() + 0x2838) = TRUE;
            advanceScript(1);
            continue;
        case 85:
            *(u8 *)(UI_1A8234() + 0x2839) = TRUE;
            advanceScript(1);
            continue;
        case 66:
            *(u8 *)(WORK_BASE() + 0x7859) = FALSE;
            *(u8 *)(WORK_BASE() + 0x7857) = SCRIPT()[1];
            *(u8 *)(UI_1A8234() + 0x264B) = TRUE;
            item->childDone = 0;
            advanceScript(2);
            continue;
        case 67:
            if (*(u8 *)(WORK_BASE() + 0x7859) == TRUE) advanceScript(1);
            return FALSE;
        case 68:
            if (WORK_S16(0x774E) == (s32)SCRIPT()[1]) advanceScript(2);
            return FALSE;
        case 69:
            *(u8 *)(UI_1A8234() + 0x264D) = TRUE;
            item->childDone = 0;
            advanceScript(1);
            continue;
        case 70:
            startScriptChild(item, fn_2_3BA40);
            advanceScript(1);
            continue;
        case 71:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 74:
            fn_2_72054(0, 3);
            advanceScript(1);
            continue;
        case 75:
            fn_2_72054(0, 3);
            advanceScript(1);
            continue;
        case 76:
            fn_2_72054(0, 3);
            fn_2_72054(challengeState()->opponentCaptain, 7);
            advanceScript(1);
            continue;
        case 77:
            fn_2_72054(0, 3);
            advanceScript(1);
            continue;
        case 78:
            startScriptChild(item, fn_2_3C3EC);
            advanceScript(1);
            continue;
        case 79:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 80:
            startScriptChild(item, fn_2_3C168);
            advanceScript(1);
            continue;
        case 81:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 82:
            startScriptChild(item, fn_2_3C03C);
            advanceScript(1);
            continue;
        case 83:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 84:
            startScriptDialogue(item, 0x23A + challengeState()->captain, 1);
            continue;
        case 86: {
            MenuDrawItem *child = (MenuDrawItem *)insertGraphicDrawingFunction(fn_2_3E38C, 2);
            child->state = 0;
            *(s16 *)((u8 *)child + 0x16) = 0;
            item->childDone = 0;
            advanceScript(1);
            continue;
        }
        case 87:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 96: {
            MenuDrawItem *child = (MenuDrawItem *)insertGraphicDrawingFunction(fn_2_3E058, 2);
            child->state = 0;
            *(s16 *)((u8 *)child + 0x16) = 0;
            item->childDone = 0;
            advanceScript(1);
            continue;
        }
        case 97:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 88:
            startScriptChild(item, fn_2_3D5C4);
            advanceScript(1);
            continue;
        case 89:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 90:
            startScriptChild(item, fn_2_3DF28);
            advanceScript(1);
            continue;
        case 91:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 94:
            startScriptChild(item, fn_2_3CD34);
            advanceScript(1);
            continue;
        case 95:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 98:
            startScriptChild(item, fn_2_3BD88);
            advanceScript(1);
            continue;
        case 99:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 100:
            startScriptChild(item, fn_2_3BD88);
            advanceScript(1);
            continue;
        case 101:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 102:
            startScriptChild(item, fn_2_3BC24);
            advanceScript(1);
            continue;
        case 103:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 104:
            startScriptChild(item, fn_2_399C0);
            advanceScript(1);
            continue;
        case 105:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        case 106:
            fn_2_43404();
            fn_2_42708();
            fn_2_432EC();
            advanceScript(1);
            continue;
        case 108:
            startScriptChild(item, fn_2_37F04);
            advanceScript(1);
            continue;
        case 109:
            if (item->childDone == 1) advanceScript(1);
            return FALSE;
        default:
            return FALSE;
        }
    }
}

// .text:0x00040B90 size:0x128 mapped:0x8067FC24
void fn_2_40B90(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        *(u8 *)(WORK_BASE() + 0x78F3) = 0;
        item->state = 1;
        break;
    case 1:
        hugeAnimStruct[0x307A] = 0;
        fn_2_20218();
        *(u8 *)(UI_1A8234() + 0x2992) = 1;
        *(u8 *)(UI_1A8230() + 0x2A86) = 1;
        item->state = 2;
        break;
    case 2:
        item->state = 3;
        break;
    case 3:
        fn_2_1BFD0();
        item->state = 4;
        break;
    case 4:
        menuNumber[0x26] = 1;
        item->state = 5;
        break;
    case 5:
        item->node->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }
}

// .text:0x00040A9C size:0xF4 mapped:0x8067FB30
void fn_2_40A9C(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        *(u8 *)(WORK_BASE() + 0x78F3) = 0;
        item->state = 1;
        break;
    case 1:
        hugeAnimStruct[0x307A] = 0;
        fn_2_20218();
        *(u8 *)(UI_1A8234() + 0x2992) = 1;
        *(u8 *)(UI_1A8230() + 0x2A86) = 1;
        item->state = 2;
        break;
    case 2:
        fn_2_1BF50();
        item->state = 3;
        break;
    case 3:
        item->node->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }
}

// .text:0x000409CC size:0xD0 mapped:0x8067FA60
void fn_2_409CC(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        screenTextArray.textBanks[4] =
            (TextBank *)ARAMTransfer(challengeDialogueTextFileDescriptor, 0, 1, 0);
        item->state = 1;
        break;
    case 1:
        if (lbl_803C6CF8[0x715] == 1) {
            fn_800111B4(screenTextArray.textBanks[4]);
            item->state = 2;
        }
        break;
    case 2:
        item->node->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }
}

// .text:0x000408BC size:0x110 mapped:0x8067F950
void fn_2_408BC(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        item->timer = 0x3C;
        *(u8 *)(WORK_BASE() + 0x782C) = 1;
        fn_2_72054(1, 0xD);
        fn_80062890(9);
        item->state = 1;
        break;
    case 1:
        if (item->timer-- == 0) {
            item->state = 2;
        }
        break;
    case 2:
        item->node->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }

    if (*(u8 *)(WORK_BASE() + 0x783F) == 1) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
    }
}

// .text:0x0004078C size:0x130 mapped:0x8067F820
void fn_2_4078C(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        *(u8 *)(WORK_BASE() + 0x783E) = 0;
        item->state = 1;
        break;
    case 1:
        if (*(u16 *)(AtBat_ButtonInput1 + (*(s8 *)(WORK_BASE() + 0x7863) << 5) + 2) & INPUT_BUTTON_A) {
            item->state = 2;
        }
        break;
    case 2:
        *(u8 *)(WORK_BASE() + 0x783E) = 1;
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }

    if (*(u8 *)(WORK_BASE() + 0x783F) == 1) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
    }
}
