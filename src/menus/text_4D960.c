#include "menus/text_4D960.h"
#include "game/challenge/challenge_state.h"
#include "Unknown/File_0x800b0a14.h"
#include "text/text.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/pad.h"
#include "musyx/musyx.h"
#include "menus/text_37F04.h"
#include "menus/rep_08E8.h"

extern u8 *lbl_2_bss_1A8234;
typedef struct MenuScriptWork {
    u8 _00[0x18];
    s32 script[0x1000];
    u16 formattedCounts[2];
    u16 textCounts[2];
    u16 formattedText[2][0x100];
    u16 text[2][0x100];
} MenuScriptWork;

extern MenuScriptWork lbl_2_bss_55E8;
extern void *lbl_2_data_1E99C[];
extern s16 lbl_2_data_38CC[];
extern u8 lbl_800EFBA4[];

void *memcpy(void *destination, const void *source, u32 size);
void *_OSAllocFromHeap(s32 alignment, s32 size);
void fn_800ACFB0(void *block);

extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_data_12EA8[];
extern u8 lbl_2_data_1323C[];
extern u8 challengeCaptainCharIDs[];
extern u8 menuFontFileDescriptor[];
extern u8 ChallengeTexFiles[];
extern u8 stadiumPreviewsFileDescriptor[];
extern u8 menuBarsFileDescriptor[];
extern u32 memoryUsedOrStorage[];

void fn_8003BF54(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void fn_800AD054(s32 lo, s32 hi);
void fn_80035B50(s32 id);
s32 diskReadRelated(void *arg0, s32 arg1);
void removeGraphicsElementFromScene(void *node);
void addGraphicsElementToScene(void *node, const void *descriptors);
void fn_2_4C3EC(void);

static inline ChallengeTrackingStruct *getChallengeRecord(s32 index) {
    return &((ChallengeState *)lbl_2_bss_1A8248)->characters[index];
}

static inline void backupScoutFlags(void) {
    s32 i;
    for (i = 0; i < 54; i++) {
        ChallengeTrackingStruct *record = getChallengeRecord(i);
        record->_7 = record->scoutFlagsAchieved;
    }
}

static inline void backupMissionRecords(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        ChallengeTrackingStruct *record = getChallengeRecord(i);
        for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
            record->saveFileMissionTracker[j].starMissionStatus = record->inGameMissionTracker[j].starMissionStatus;
            record->saveFileMissionTracker[j].shownOnPauseMenu = record->inGameMissionTracker[j].shownOnPauseMenu;
        }
    }
}

// .text:0x0004D960 size:0x2C4 mapped:0x8068C9F4
void fn_2_4D960(void) {
    *(s8 *)(lbl_2_bss_1A824C + 0x197843) = -1;
    ((ChallengeState *)lbl_2_bss_1A8248)->opponentCaptain = CHALLENGE_CAPTAIN_PEACH;
    backupScoutFlags();
    backupMissionRecords();
}

// .text:0x0004DC24 size:0x2C4 mapped:0x8068CCB8
void fn_2_4DC24(void) {
    *(s8 *)(lbl_2_bss_1A824C + 0x197843) = -1;
    ((ChallengeState *)lbl_2_bss_1A8248)->opponentCaptain = CHALLENGE_CAPTAIN_PEACH;
    backupScoutFlags();
    backupMissionRecords();
}

// .text:0x0004DEE8 size:0x2D8 mapped:0x8068CF7C
void fn_2_4DEE8(void) {
    *(s8 *)(lbl_2_bss_1A824C + 0x197843) = -1;
    ((ChallengeState *)lbl_2_bss_1A8248)->opponentCaptain = CHALLENGE_CAPTAIN_PEACH;
    ((ChallengeState *)lbl_2_bss_1A8248)->opponentCaptainCharID = CHAR_ID_BOWSERJR;
    lbl_2_bss_1A8248[0x444A] = 0;
    backupScoutFlags();
    backupMissionRecords();
}

// .text:0x0004E1C0 size:0x5E4 mapped:0x8068D254
void fn_2_4E1C0(void) {
    if (((ChallengeState *)lbl_2_bss_1A8248)->_44EF == 0) {
        *(s8 *)(lbl_2_bss_1A824C + 0x197843) = -1;
        ((ChallengeState *)lbl_2_bss_1A8248)->opponentCaptain =
            lbl_2_bss_1A8248[((ChallengeState *)lbl_2_bss_1A8248)->_16C2 * 10 + 0x40F3];
        ((ChallengeState *)lbl_2_bss_1A8248)->opponentCaptainCharID =
            challengeCaptainCharIDs[((ChallengeState *)lbl_2_bss_1A8248)->opponentCaptain];
        fn_2_4C3EC();
        lbl_2_bss_1A8248[0x444A] = 0;
        backupScoutFlags();
        backupMissionRecords();
    } else {
        *(s8 *)(lbl_2_bss_1A824C + 0x197843) = -1;
        ((ChallengeState *)lbl_2_bss_1A8248)->opponentCaptain = CHALLENGE_CAPTAIN_MARIO;
        ((ChallengeState *)lbl_2_bss_1A8248)->opponentCaptainCharID = CHAR_ID_MARIO;
        fn_2_4C3EC();
        lbl_2_bss_1A8248[0x444A] = 0;
        backupScoutFlags();
        backupMissionRecords();
    }
}

// .text:0x0004E7A4 size:0x48 mapped:0x8068D838
void fn_2_4E7A4(void) {
    fn_8003BF54(0, 0, 0, 1, 1, 4, 1, 3, 0);
}

// .text:0x0004E7EC size:0x38 mapped:0x8068D880
void fn_2_4E7EC(void) {
    fn_800AD054(*(s32 *)(lbl_2_bss_1A824C + 0x195424), *(s32 *)(lbl_2_bss_1A824C + 0x195428));
}

// .text:0x0004E824 size:0x34 mapped:0x8068D8B8
void fn_2_4E824(void) {
    *(u32 *)(lbl_2_bss_1A824C + 0x195424) = memoryUsedOrStorage[1];
    *(u32 *)(lbl_2_bss_1A824C + 0x195428) = memoryUsedOrStorage[2];
}

// .text:0x0004E858 size:0x20 mapped:0x8068D8EC
void fn_2_4E858(void *node) {
    removeGraphicsElementFromScene(node);
}

// .text:0x0004E878 size:0x20 mapped:0x8068D90C
void fn_2_4E878(void *node, const void *descriptors) {
    addGraphicsElementToScene(node, descriptors);
}

// .text:0x0004E898 size:0x24 mapped:0x8068D92C
void fn_2_4E898(void) {
    fn_80035B50(0x17);
}

// .text:0x0004E8BC size:0x24 mapped:0x8068D950
void fn_2_4E8BC(void) {
    fn_80035B50(0x18);
}

// .text:0x0004E8E0 size:0x24 mapped:0x8068D974
void fn_2_4E8E0(void) {
    fn_80035B50(0x17);
}

// .text:0x0004E904 size:0x24 mapped:0x8068D998
void fn_2_4E904(void) {
    fn_80035B50(0xC);
}

// .text:0x0004E928 size:0x24 mapped:0x8068D9BC
void fn_2_4E928(void) {
    fn_80035B50(0x15);
}

// .text:0x0004E94C size:0x24 mapped:0x8068D9E0
void fn_2_4E94C(void) {
    fn_80035B50(0x8);
}

// .text:0x0004E970 size:0x38 mapped:0x8068DA04
BOOL fn_2_4E970(void) {
    return diskReadRelated(menuFontFileDescriptor, 0x17) != 0;
}

// .text:0x0004E9A8 size:0x114 mapped:0x8068DA3C
BOOL fn_2_4E9A8(void) {
    u8 *base = lbl_2_data_12EA8;

    switch (((ChallengeState *)lbl_2_bss_1A8248)->captain) {
        case CHALLENGE_CAPTAIN_MARIO:
            if (diskReadRelated(base + 0x3D4, 0x18) == 0) {
                return FALSE;
            }
            break;
        case CHALLENGE_CAPTAIN_PEACH:
            if (diskReadRelated(base + 0x3E4, 0x18) == 0) {
                return FALSE;
            }
            break;
        case CHALLENGE_CAPTAIN_WARIO:
            if (diskReadRelated(base + 0x3F4, 0x18) == 0) {
                return FALSE;
            }
            break;
        case CHALLENGE_CAPTAIN_DK:
            if (diskReadRelated(base + 0x404, 0x18) == 0) {
                return FALSE;
            }
            break;
        case CHALLENGE_CAPTAIN_YOSHI:
            if (diskReadRelated(base + 0x414, 0x18) == 0) {
                return FALSE;
            }
            break;
        case CHALLENGE_CAPTAIN_BOWSER:
            if (diskReadRelated(base + 0x424, 0x18) == 0) {
                return FALSE;
            }
            break;
        default:
            break;
    }
    return TRUE;
}

// .text:0x0004EABC size:0x38 mapped:0x8068DB50
BOOL fn_2_4EABC(void) {
    return diskReadRelated(ChallengeTexFiles, 0x17) != 0;
}

// .text:0x0004EAF4 size:0x38 mapped:0x8068DB88
BOOL fn_2_4EAF4(void) {
    return diskReadRelated(stadiumPreviewsFileDescriptor, 0xC) != 0;
}

// .text:0x0004EB2C size:0x38 mapped:0x8068DBC0
BOOL fn_2_4EB2C(void) {
    return diskReadRelated(menuBarsFileDescriptor, 0x15) != 0;
}

// .text:0x0004EB64 size:0x38 mapped:0x8068DBF8
BOOL fn_2_4EB64(void) {
    return diskReadRelated(lbl_2_data_1323C, 0x8) != 0;
}

// .text:0x0004EB9C size:0x1CFC mapped:0x8068DC30
#define SCRIPT_FIELD(type, offset) (*(type *)(lbl_2_bss_1A824C + 0x190000 + (offset)))
#define SCRIPT_PC SCRIPT_FIELD(s32 *, 0x6F1C)

static inline void advanceMenuScript(s32 words) {
    SCRIPT_PC += words;
}

static inline void waitMenuScript(s32 opcode) {
    SCRIPT_FIELD(s32, 0x6F20) = SCRIPT_PC[0];
    SCRIPT_PC[0] = opcode;
}

static inline void restoreMenuScript(void) {
    SCRIPT_PC[0] = SCRIPT_FIELD(s32, 0x6F20);
}

static inline void reloadMenuScript(MenuScriptWork *work) {
    memcpy(work->script, lbl_2_data_1E99C[SCRIPT_FIELD(s16, 0x6FD6)], 0x4000);
    SCRIPT_PC = work->script;
}

static inline void cancelMenuScript(MenuScriptWork *work) {
    SCRIPT_FIELD(u8, 0x7840) = TRUE;
    SCRIPT_FIELD(s16, 0x6FD6) = SCRIPT_FIELD(s16, 0x77A0);
    reloadMenuScript(work);
}

static inline u16 scriptButtonInput(s32 offset) {
    return *(u16 *)((u8 *)&AtBat_ButtonInput1 + SCRIPT_FIELD(s8, 0x7863) * 0x20 + offset);
}

static inline void markScriptWindow(s32 window) {
    if (window == 0) {
        lbl_2_bss_1A8234[0x162687] = TRUE;
    } else {
        lbl_2_bss_1A8234[0x162688] = TRUE;
    }
}

static inline void activateScriptScene(void) {
    lbl_2_bss_1A8234[0x162842] = TRUE;
    lbl_2_bss_1A8234[0x162871] = TRUE;
    lbl_2_bss_1A8234[0x162872] = TRUE;
}

static inline void copyScriptGlyphs(u16 *destination, u16 *count, const u16 *source) {
    u16 glyph;
    do {
        s32 index = *count;
        glyph = *source++;
        (*count)++;
        destination[index] = glyph;
    } while (*count != 0x100 && ((glyph & 0x4000) == 0 || (glyph & 0x3FFF) != 0));
}

static inline void appendScriptGlyphs(u16 *destination, u16 *count, const u16 *source) {
    if (*count != 0) {
        (*count)--;
    }
    copyScriptGlyphs(destination, count, source);
}

static inline void appendScriptString(MenuScriptWork *work, s32 window, s32 stringID) {
    u16 *source;
    TextBank *bank = screenTextArray.textBanks[SCRIPT_FIELD(u8, 0x72B8)];
    if (work->textCounts[window] != 0) {
        work->textCounts[window]--;
    }
    if (stringID == -1) {
        source = NULL;
    } else {
        source = bank->strings[stringID];
    }
    copyScriptGlyphs(work->text[window],
        &work->textCounts[window], source);
}

s16 fn_2_4EB9C(void) {
    MenuScriptWork *work = &lbl_2_bss_55E8;
    DrawingSceneStruct *owner = currentDrawingItem;
    s32 textHandles[2];

    if (SCRIPT_FIELD(s32, 0x6F24) != 0) {
        SCRIPT_FIELD(s32, 0x6F24)--;
        return FALSE;
    }
    textHandles[0] = SCRIPT_FIELD(s16, 0x72A0);
    textHandles[1] = SCRIPT_FIELD(s16, 0x72A2);
    for (;;) {
        switch ((u32)SCRIPT_PC[0]) {
        case 0:
            SCRIPT_FIELD(s16, 0x72B0) = 0;
            SCRIPT_FIELD(s16, 0x729A) = 0;
            SCRIPT_FIELD(s16, 0x7298) = 0;
            SCRIPT_FIELD(s16, 0x77A0) = 0;
            SCRIPT_FIELD(u8, 0x7840) = FALSE;
            advanceMenuScript(1);
            continue;
        case 1:
            SCRIPT_FIELD(u8, 0x7840) = FALSE;
            return TRUE;
        case 11: {
            s32 window = SCRIPT_PC[1];
            SCRIPT_FIELD(s32, 0x6FB8 + window * 4) = SCRIPT_PC[2];
            markScriptWindow(window);
            SCRIPT_FIELD(s16, 0x7298 + window * 2) = 0;
            SCRIPT_FIELD(s16, 0x6FC0) = window;
            waitMenuScript(13);
            break;
        }
        case 37: {
            s32 window = SCRIPT_PC[1];
            SCRIPT_FIELD(s32, 0x6FB8 + window * 4) = SCRIPT_PC[2];
            markScriptWindow(window);
            SCRIPT_FIELD(s16, 0x7298 + window * 2) = 0;
            SCRIPT_FIELD(s16, 0x6FC0) = window;
            waitMenuScript(38);
            break;
        }
        case 8:
            SCRIPT_FIELD(s32, 0x6FB8) = SCRIPT_PC[1];
            lbl_2_bss_1A8234[0x162687] = TRUE;
            SCRIPT_FIELD(s16, 0x7298) = 0;
            advanceMenuScript(2);
            continue;
        case 28:
            SCRIPT_FIELD(s32, 0x6FB8) = SCRIPT_PC[1];
            markScriptWindow(0);
            SCRIPT_FIELD(s16, 0x7298) = 0;
            SCRIPT_FIELD(s16, 0x6FC0) = 0;
            waitMenuScript(29);
            break;
        case 13:
            if (screenTextArray.blocks[textHandles[SCRIPT_FIELD(s16, 0x6FC0)]].unk34 == 1) {
                SCRIPT_PC[0] = 12;
            } else if ((scriptButtonInput(2) & PAD_BUTTON_START) && SCRIPT_FIELD(u8, 0x7842) == 1) {
                cancelMenuScript(work);
            }
            break;
        case 38:
            if (screenTextArray.blocks[textHandles[SCRIPT_FIELD(s16, 0x6FC0)]].unk34 == 1) {
                restoreMenuScript();
                advanceMenuScript(3);
            } else if ((scriptButtonInput(2) & PAD_BUTTON_START) && SCRIPT_FIELD(u8, 0x7842) == 1) {
                cancelMenuScript(work);
            }
            break;
        case 29:
            if (screenTextArray.blocks[textHandles[SCRIPT_FIELD(s16, 0x6FC0)]].unk34 == 1) {
                restoreMenuScript();
                advanceMenuScript(2);
            } else if ((scriptButtonInput(2) & PAD_BUTTON_START) && SCRIPT_FIELD(u8, 0x7842) == 1) {
                cancelMenuScript(work);
            }
            break;
        case 12: {
            s32 window = SCRIPT_FIELD(s16, 0x6FC0);
            u16 buttons;
            SCRIPT_FIELD(s16, 0x7298 + window * 2) = 1;
            buttons = scriptButtonInput(2);
            if (buttons & PAD_BUTTON_A) {
                SCRIPT_FIELD(s16, 0x6FCC) = 0;
                SCRIPT_FIELD(s16, 0x6FCA) = 0;
                SCRIPT_FIELD(s16, 0x7298 + window * 2) = 0;
                restoreMenuScript();
                advanceMenuScript(3);
            } else if ((buttons & PAD_BUTTON_START) && SCRIPT_FIELD(u8, 0x7842) == 1) {
                cancelMenuScript(work);
            }
            break;
        }
        case 20: {
            BOOL confirmed = FALSE;
            u16 buttons;
            SCRIPT_FIELD(s16, 0x72B2) = 1;
            buttons = scriptButtonInput(4);
            if (buttons & PAD_BUTTON_UP) {
                SCRIPT_FIELD(s16, 0x72B0) = (SCRIPT_FIELD(s16, 0x72B0) + 1) % 2;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (buttons & PAD_BUTTON_DOWN) {
                SCRIPT_FIELD(s16, 0x72B0) = (SCRIPT_FIELD(s16, 0x72B0) + 1) % 2;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            buttons = scriptButtonInput(2);
            if (buttons & PAD_BUTTON_A) {
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                confirmed = TRUE;
            } else if (buttons & PAD_BUTTON_B) {
                if (SCRIPT_FIELD(s16, 0x72B0) == 0) {
                    SCRIPT_FIELD(s16, 0x72B0) = 1;
                } else {
                    confirmed = TRUE;
                }
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
            if (confirmed) {
                SCRIPT_FIELD(s16, 0x6FCC) = 0;
                SCRIPT_FIELD(s16, 0x6FCA) = 0;
                SCRIPT_FIELD(s16, 0x72B2) = 0;
                advanceMenuScript(1);
            }
            break;
        }
        case 25: {
            BOOL confirmed = FALSE;
            u16 buttons;
            SCRIPT_FIELD(s16, 0x72B2) = 1;
            buttons = scriptButtonInput(4);
            if (buttons & PAD_BUTTON_UP) {
                SCRIPT_FIELD(s16, 0x72B0) = (SCRIPT_FIELD(s16, 0x72B0) + 2) % 3;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (buttons & PAD_BUTTON_DOWN) {
                SCRIPT_FIELD(s16, 0x72B0) = (SCRIPT_FIELD(s16, 0x72B0) + 1) % 3;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            buttons = scriptButtonInput(2);
            if (buttons & PAD_BUTTON_A) {
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                confirmed = TRUE;
            } else if (buttons & PAD_BUTTON_B) {
                if (SCRIPT_FIELD(s16, 0x72B0) == 0 || SCRIPT_FIELD(s16, 0x72B0) == 1) {
                    SCRIPT_FIELD(s16, 0x72B0) = 2;
                } else {
                    confirmed = TRUE;
                }
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
            if (confirmed) {
                SCRIPT_FIELD(s16, 0x6FCC) = 0;
                SCRIPT_FIELD(s16, 0x6FCA) = 0;
                SCRIPT_FIELD(s16, 0x72B2) = 0;
                advanceMenuScript(1);
            }
            break;
        }
        case 2:
            SCRIPT_FIELD(s32, 0x6F24) = SCRIPT_PC[1];
            advanceMenuScript(2);
            break;
        case 21:
            if (SCRIPT_FIELD(s32, 0x6F28)-- == 0) {
                restoreMenuScript();
            }
            break;
        case 22:
            if (owner->state == 1) {
                restoreMenuScript();
            }
            break;
        case 32: {
            s32 i;
            work->textCounts[1] = 0;
            work->textCounts[0] = 0;
            SCRIPT_FIELD(s16, 0x6FCC) = 1;
            SCRIPT_FIELD(s16, 0x6FCA) = 1;
            for (i = 0; i < 0x100; i++) {
                work->text[0][i] = 0;
                work->text[1][i] = 0;
            }
            advanceMenuScript(1);
            continue;
        }
        case 3: {
            s32 window = SCRIPT_PC[1];
            s32 i;
            work->textCounts[window] = 0;
            SCRIPT_FIELD(s16, 0x6FCA + window * 2) = 1;
            for (i = 0; i < 0x100; i++) {
                (work->text[window])[i] = 0;
            }
            advanceMenuScript(2);
            continue;
        }
        case 4:
            appendScriptString(work, SCRIPT_PC[1], SCRIPT_PC[2]);
            advanceMenuScript(3);
            continue;
        case 5:
            SCRIPT_FIELD(s32, 0x6F30) = 1;
            advanceMenuScript(1);
            continue;
        case 6:
            appendScriptString(work, SCRIPT_PC[1], SCRIPT_PC[2] + SCRIPT_FIELD(s32, 0x6F38 + SCRIPT_PC[3] * 4));
            advanceMenuScript(4);
            continue;
        case 7:
            appendScriptString(work, SCRIPT_PC[1], SCRIPT_PC[2] + SCRIPT_PC[3]);
            advanceMenuScript(4);
            continue;
        case 9:
            advanceMenuScript(4);
            continue;
        case 14: {
            DrawingSceneStruct *node = insertGraphicDrawingFunction(fn_2_38A40, 2);
            *(u8 *)&node->unk_28 = 0;
            SCRIPT_FIELD(s16, 0x729C) = SCRIPT_PC[1];
            SCRIPT_FIELD(s16, 0x729E) = SCRIPT_PC[2];
            SCRIPT_FIELD(s16, 0x72AA) = SCRIPT_PC[3];
            owner->state = 0;
            waitMenuScript(15);
            continue;
        }
        case 15:
            if (owner->state == 1) {
                if (SCRIPT_FIELD(s16, 0x729C) == 1) SCRIPT_FIELD(u8, 0x72B9) = 1;
                if (SCRIPT_FIELD(s16, 0x729E) == 1) SCRIPT_FIELD(u8, 0x72BA) = 1;
                restoreMenuScript();
                advanceMenuScript(4);
            }
            break;
        case 26: {
            DrawingSceneStruct *node = insertGraphicDrawingFunction(fn_2_38824, 2);
            *(u8 *)&node->unk_28 = 0;
            *(s16 *)((u8 *)node + 0x1A) = 0;
            *(s16 *)((u8 *)node + 0x18) = 0;
            if (SCRIPT_PC[1] == 0) {
                SCRIPT_FIELD(s16, 0x72A4) = 1;
                SCRIPT_FIELD(s16, 0x72AC) = SCRIPT_PC[2];
                *(s16 *)((u8 *)node + 0x18) = 1;
            } else if (SCRIPT_PC[1] == 1) {
                SCRIPT_FIELD(s16, 0x72A6) = 1;
                SCRIPT_FIELD(s16, 0x72AE) = SCRIPT_PC[2];
                *(s16 *)((u8 *)node + 0x1A) = 1;
            }
            owner->state = 0;
            waitMenuScript(27);
            continue;
        }
        case 27:
            if (owner->state == 1) {
                restoreMenuScript();
                advanceMenuScript(3);
            }
            break;
        case 16: {
            DrawingSceneStruct *node;
            if (SCRIPT_FIELD(s16, 0x729C) == 1) SCRIPT_FIELD(u8, 0x72B9) = 0;
            if (SCRIPT_FIELD(s16, 0x729E) == 1) SCRIPT_FIELD(u8, 0x72BA) = 0;
            activateScriptScene();
            node = insertGraphicDrawingFunction(fn_2_38538, 2);
            *(u8 *)&node->unk_28 = 0;
            owner->state = 0;
            waitMenuScript(17);
            continue;
        }
        case 17:
            if (owner->state == 1) {
                restoreMenuScript();
                advanceMenuScript(1);
            }
            break;
        case 18:
            lbl_2_bss_1A8234[0x162658] = 1;
            advanceMenuScript(1);
            continue;
        case 19:
            lbl_2_bss_1A8234[0x162842] = 1;
            advanceMenuScript(1);
            continue;
        case 47:
            lbl_2_bss_1A8234[0x162689] = 1;
            advanceMenuScript(1);
            continue;
        case 48:
            lbl_2_bss_1A8234[0x162873] = 1;
            advanceMenuScript(1);
            continue;
        case 23:
            reloadMenuScript(work);
            break;
        case 24:
            SCRIPT_FIELD(s16, 0x6FD6) = SCRIPT_PC[1];
            reloadMenuScript(work);
            break;
        case 30:
            if (SCRIPT_FIELD(s16, 0x72B0) == 0) {
                SCRIPT_FIELD(s16, 0x6FD6) = SCRIPT_PC[1];
                reloadMenuScript(work);
            } else {
                advanceMenuScript(2);
            }
            break;
        case 33: {
            s32 window = SCRIPT_PC[1];
            s32 variable = SCRIPT_PC[2];
            s32 format = SCRIPT_PC[3];
            s32 i;
            s32 value;
            u16 *temporary;
            u16 *formatted = work->formattedText[window];
            work->formattedCounts[window] = 0;
            for (i = 0; i < 0x100; i++) formatted[i] = 0;
            value = SCRIPT_FIELD(s32, 0x6F38 + variable * 4);
            temporary = _OSAllocFromHeap(0x10, 0xC);
            fn_2_4917C(temporary, value, format, 4, 1);
            appendScriptGlyphs(formatted, &work->formattedCounts[window], temporary);
            appendScriptGlyphs(work->text[window],
                &work->textCounts[window], formatted);
            if (temporary != NULL) fn_800ACFB0(temporary);
            advanceMenuScript(4);
            continue;
        }
        case 34: {
            DrawingSceneStruct *node;
            SCRIPT_FIELD(s16, 0x72B4) = SCRIPT_PC[1];
            SCRIPT_FIELD(u8, 0x72B6) = lbl_2_data_38CC[SCRIPT_FIELD(s16, 0x72B4)];
            SCRIPT_FIELD(u8, 0x72B7) = 0;
            node = insertGraphicDrawingFunction(fn_2_39408, 2);
            *(u8 *)&node->unk_28 = 0;
            owner->state = 0;
            advanceMenuScript(2);
            continue;
        }
        case 35:
            if (owner->state != 0) advanceMenuScript(1);
            break;
        case 36:
            if (owner->state == 1) {
                SCRIPT_FIELD(s16, 0x6FD6) = SCRIPT_PC[1];
                reloadMenuScript(work);
            } else if (owner->state == 2 || owner->state == 3) {
                SCRIPT_FIELD(s16, 0x6FD6) = SCRIPT_PC[2];
                reloadMenuScript(work);
            }
            break;
        case 39:
            if (SCRIPT_FIELD(s16, 0x72B0) == 0) {
                SCRIPT_FIELD(s16, 0x6FD6) = SCRIPT_PC[1];
                reloadMenuScript(work);
            } else {
                SCRIPT_FIELD(s16, 0x6FD6) = SCRIPT_PC[2];
                reloadMenuScript(work);
            }
            break;
        case 31:
            if (SCRIPT_FIELD(s16, 0x72B0) == 0) {
                SCRIPT_FIELD(s16, 0x6FD6) = SCRIPT_PC[1];
                reloadMenuScript(work);
            } else if (SCRIPT_FIELD(s16, 0x72B0) == 1) {
                SCRIPT_FIELD(s16, 0x6FD6) = SCRIPT_PC[2];
                reloadMenuScript(work);
            } else {
                SCRIPT_FIELD(s16, 0x6FD6) = SCRIPT_PC[3];
                reloadMenuScript(work);
            }
            break;
        case 40: {
            s32 value = SCRIPT_PC[1];
            DrawingSceneStruct *node = insertGraphicDrawingFunction(fn_2_382A0, 2);
            *(u8 *)&node->unk_28 = 0;
            *(s16 *)((u8 *)node + 0x16) = value;
            owner->state = 0;
            activateScriptScene();
            waitMenuScript(41);
            continue;
        }
        case 41:
            if (owner->state == 1) {
                restoreMenuScript();
                advanceMenuScript(2);
            }
            break;
        case 50: {
            DrawingSceneStruct *node = insertGraphicDrawingFunction(fn_2_382A0, 2);
            *(u8 *)&node->unk_28 = 0;
            *(s16 *)((u8 *)node + 0x16) = 2;
            owner->state = 0;
            activateScriptScene();
            waitMenuScript(51);
            continue;
        }
        case 51:
            if (owner->state == 1) {
                restoreMenuScript();
                advanceMenuScript(1);
            }
            break;
        case 42: {
            DrawingSceneStruct *node = insertGraphicDrawingFunction(fn_2_381A8, 2);
            *(u8 *)&node->unk_28 = 0;
            *(s16 *)((u8 *)node + 0x16) = 0;
            owner->state = 0;
            activateScriptScene();
            waitMenuScript(43);
            continue;
        }
        case 43:
            if (owner->state == 1) {
                restoreMenuScript();
                advanceMenuScript(1);
            }
            break;
        case 44: {
            DrawingSceneStruct *node;
            SCRIPT_FIELD(s16, 0x72AA) = SCRIPT_PC[1];
            node = insertGraphicDrawingFunction(fn_2_380B0, 2);
            *(u8 *)&node->unk_28 = 0;
            *(s16 *)((u8 *)node + 0x16) = 0;
            owner->state = 0;
            activateScriptScene();
            waitMenuScript(45);
            continue;
        }
        case 45:
            if (owner->state == 1) {
                restoreMenuScript();
                advanceMenuScript(2);
            }
            break;
        case 46:
            SCRIPT_FIELD(s16, 0x76DE) = 1;
            advanceMenuScript(1);
            continue;
        case 52:
            SCRIPT_FIELD(u8, 0x7842) = SCRIPT_PC[1];
            if (SCRIPT_FIELD(u8, 0x7842) == 1) SCRIPT_FIELD(s16, 0x77A0) = SCRIPT_PC[2];
            advanceMenuScript(3);
            continue;
        case 53:
            SCRIPT_FIELD(s16, 0x7298) = 1;
            advanceMenuScript(1);
            continue;
        case 54:
            SCRIPT_FIELD(s16, 0x7298) = 0;
            advanceMenuScript(1);
            continue;
        case 55:
            SCRIPT_FIELD(s16, 0x729A) = 1;
            advanceMenuScript(1);
            continue;
        case 56:
            SCRIPT_FIELD(s16, 0x729A) = 1;
            advanceMenuScript(1);
            continue;
        case 57:
            SCRIPT_FIELD(s16, 0x7298) = 0;
            SCRIPT_FIELD(s16, 0x729A) = 0;
            advanceMenuScript(1);
            continue;
        case 10:
        case 49:
        default:
            break;
        }
        return FALSE;
    }
}

