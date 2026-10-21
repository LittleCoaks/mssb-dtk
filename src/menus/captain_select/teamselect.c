#include "menus/captain_select/teamselect.h"
#include "menus/yd_step.h"
#include "game/challenge/challenge_state.h"
#include "Unknown/mb_subfunc.h"
#include "Dolphin/os.h"
#include "menus/captain_select/captain_model_load.h"
#include "Unknown/File_0x800625a4.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x80035ca4.h"
#include "Unknown/File_0x80062a50.h"
#include "Unknown/File_0x80062578.h"
#include "Unknown/File_0x8004cc18.h"
#include "header_rep_data.h"
#include "menus/debug_menu_text.h"
#include "game/match_setup/match_loading.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800628d4.h"
#include "menus/captain_select/captain_select.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

extern u8 lbl_2_bss_100B8[0x54];
extern u8 lbl_2_bss_100B4;
extern u16 lbl_2_bss_AE0;
extern int menuCursors[0x16];
extern menuControlStruct* menuControlVariables;
extern u8 superstarUnlocked[0x130];
extern u8 challengeCaptainCharIDArray[12];
extern u8 captainIDOrderedOnCapSS[12];
typedef struct {
    u8 _00;
    u8 _01[0xD];
    u8 unk0E;
    u8 _0F[0x46];
    u8 unk55[4];
    u8 portCaptainSlot[4];
    u8 _5D[7];
} CaptainGameSetUp;
extern CaptainGameSetUp gameSetUpStep;
void fn_8004D990(s32 port, s32 team, s32 challengeCaptain);
void fn_8004D460(s32 team, s32 selection);
extern u8 lbl_803CBBC4[8];
void relatedToTeamSelection4(void);
void fn_2_73758(void);
void set807518de(u8 port, s32 active);
void fn_8004EEF4(s32 port0, s32 port1, s32 port2, s32 port3, s32 active);
void add_or_RemoveCharToATeam(s32 port, s32 characterID, s32 add);
extern u8 menuNumber[0x28];
extern u8 cardCheck[0x5C];
extern u8 lbl_803CBCD8[0x8];
extern u8 lbl_803CBD24[0xC];
extern u8 hugeAnimStruct[0x3154];
DebugMenuText lbl_2_data_15C8 = {
    { "BAT FIRST", "BAT LAST" },
    "FL",
    "PC",
    { "RR", "RL", "LR", "LL" },
    { "OFF", "ON" },
    { "SELECT DEBUG MENU", "HIDE CHARA SET", "STAR PLAYER SET", "KOOPA STA FLAG SET", "CHALLE LEVEL FREE SET" },
    { "1P >", "COM1>", "2P >", "COM2>", "3P >", "COM3>", "4P >", "COM4>" },
    { 0x0000FF0F, 0x0000880F, 0x00000FFF, 0x0000088F, 0x0000F0FF, 0x0000808F, 0x0000F00F, 0x0000800F },
    { 0, 4, 10, 6, 2, 9, 1, 5, 11, 17, 3, 19 },
    { 0, 2, 6, 8, 4, 10, 1, 3, 7, 5, 9, 11 },
    { 0, 0, 6, 2, 8, 4, 10, 5, 11, 3, 9, 1, 7, 0, 0, 0 },
};

/* Unreferenced; the same 0x28 bytes follow the debug table in stadium_select.c. */
u8 lbl_2_data_188C[0x28] = {
    2, 5, 4, 3, 8, 3, 4, 5, 2, 6, 0, 1, 8, 6, 7, 1, 2, 0, 7, 4,
    4, 3, 1, 2, 5, 1, 2, 4, 6, 8, 7, 6, 8, 5, 3, 3, 5, 7, 4, 6,
};

/* Unreferenced stadium file descriptors; an identical copy is in stadium_select.c. */
MatchFileDescriptor lbl_2_data_18B4[16] = {
    { 0x0000040B, 0x4037CF5C, 0x18B3A800, 0x00208AF0 },
    { 0x0000040B, 0x400ADFFC, 0x18AEE800, 0x0004BAB0 },
    { 0x0000040B, 0x400193E8, 0x191B8800, 0x000089D8 },
    { 0x0000040B, 0x4010E5A0, 0x0E97A800, 0x0009BCAC },
    { 0x0000040B, 0x40016980, 0x0EA16800, 0x0000D6C4 },
    { 0x0000040B, 0x40016980, 0x0EA24000, 0x0000C944 },
    { 0x0000040B, 0x40016980, 0x0EA31000, 0x0000E700 },
    { 0x0000040B, 0x40016980, 0x0EA3F800, 0x0000D64C },
    { 0x0000040B, 0x40016980, 0x0EA4D000, 0x0000C900 },
    { 0x0000040B, 0x40016980, 0x0EA5A000, 0x0000CFFC },
    { 0x0000040B, 0x40016980, 0x0EA67000, 0x0000D720 },
    { 0x0000040B, 0x40016980, 0x0EA74800, 0x0000D6CC },
    { 0x0000040B, 0x40016980, 0x0EA82000, 0x0000D21C },
    { 0x0000040B, 0x40016980, 0x0EA8F800, 0x0000D0BC },
    { 0x0000040B, 0x40016980, 0x0EA9D000, 0x0000B544 },
    { 0x0000040B, 0x40016980, 0x0EAA8800, 0x0000C4F8 },
};

void fn_2_738C8(void);
void fn_2_11EA8(void);
BOOL challengeTransitionRelated(s32 direction);
BOOL relatedToTransitions(s32 direction);
void settingValuesTo0(void);
void fn_80021AC0(s32 port, s32 state);
void fn_80021AC4(void);
void fn_80035B50(s32 id);
void fn_8004D0F0(void);
s32 exitMenu(u16 input);

static inline void setCaptainControllerFlags(void) {
    s8 controllers[4];
    memset(controllers, 2, sizeof(controllers));
    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        controllers[Static_Stats_Tables.playerNumberByPort[0]] = 1;
        if (Static_Stats_Tables.playerNumberByPort[0] == 0) {
            controllers[1] = 2;
        } else {
            controllers[0] = 2;
        }
    } else {
        controllers[Static_Stats_Tables.playerNumberByPort[1]] = 1;
        controllers[Static_Stats_Tables.playerNumberByPort[0]] = 1;
    }
    fn_8004EEF4(controllers[0], controllers[1], controllers[2], controllers[3], 1);
}

void captainSelectScreen_manager(void) {
    s32 team;
    s32 player;
    s32 transition;

    switch (menuControlVariables->currentState) {
    case 0:
        if (menuControlVariables->previousScreen == 12 &&
            g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && gameSetUpStep.unk55[0] != 0) {
            break;
        }
        captainSelectDefaultProcess();
        menuControlVariables->currentState++;
    case 1:
        menuControlVariables->currentState = 2;
        fn_2_12CD8();
        fn_2_738C8();
        if (menuControlVariables->previousScreen == 5 ||
            (menuControlVariables->previousScreen == 12 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
            onlySetPort1ToActiveOnInitialCapSSLoad();
        }
        changeScene(1, 6);
        break;
    case 2:
        fn_2_12B60();
        checkForNewPlayer();
        fn_2_12A70();
        break;
    case 4:
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            if (lbl_2_bss_100B8[0x40] == 0 || lbl_2_bss_100B8[0x41] == 0 ||
                gameSetUpStep.unk55[0] != 0 || gameSetUpStep.unk55[1] != 0) {
                break;
            }
            updateCharacterSelectProcessCode(0, 7);
            updateCharacterSelectProcessCode(1, 7);
        } else {
            if (lbl_2_bss_100B8[0x40] == 0) {
                break;
            }
            lbl_2_bss_100B4 = TRUE;
            lbl_803CBCD8[5] = 1;
            Static_Stats_Tables._48AF[2] = 1;
            changeScene(3, 6);
        }
        menuControlVariables->currentState = 5;
        break;
    case 5:
        if (((u8*)&lbl_2_bss_100B4)[1] != 0) {
            break;
        }
        if (aiPosSwapInputs._CF5F[0] != 0) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                transition = challengeTransitionRelated(0);
            } else {
                transition = relatedToTransitions(0);
            }
        } else {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                transition = challengeTransitionRelated(1);
            } else {
                transition = relatedToTransitions(2);
            }
        }
        if (transition == 0) {
            break;
        }
        menuControlVariables->currentState = 6;
    case 6:
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE && noActiveProcessInd() == 0) {
            break;
        }
        if (gameSetUpStep.unk55[0] != 0 || gameSetUpStep.unk55[1] != 0) {
            break;
        }
        if (aiPosSwapInputs._CF5F[0] != 0) {
            settingValuesTo0();
            Static_Stats_Tables._48AD = 1;
            gameSetUpStep._00 = 0;
            memset(&gameSetUpStep._01[0], 0, 6);
            ((u8*)&Static_Stats_Tables)[0x4755] = 3;
            fn_80062A74();
            maybeLoadsGameSoundFiles();
            unregisterObjectByID(15);
            unregisterObjectByID(18);
            unregisterObjectByID(9);
            unregisterObjectByID(6);
            Static_Stats_Tables._48AF[0] = 1;
            Static_Stats_Tables._48AF[2] = 1;
            menuNumber[0x26] = 1;
            aiPosSwapInputs._CF5F[0] = 0;
            changeScreenVariables(4);
        } else {
            Static_Stats_Tables._48AD = 1;
            gameSetUpStep._00 = 0;
            memset(&gameSetUpStep._01[0], 0, 6);
            ((u8*)&Static_Stats_Tables)[0x4755] = 3;
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                Static_Stats_Tables.sceneAlive = 0;
                fn_800AD038(Static_Stats_Tables._46E8[0]);
                settingValuesTo0();
                for (team = 0; team < 2; team++) {
                    for (player = 0; player < 9; player++) {
                        if (player == 0) {
                            cursorPositions.roster.rosterCharID[team][player] = Static_Stats_Tables.captainSelectedID[team];
                        } else {
                            cursorPositions.roster.rosterCharID[team][player] = CHAR_ID_NONE;
                        }
                    }
                }
                fn_80021AC0(0, 0);
                fn_80021AC0(1, 0);
                setPortOfEachPlayer();
                changeScreenVariables(10);
            } else {
                Static_Stats_Tables._48AF[0] = 1;
                setPortOfEachPlayer();
                if ((s8)hugeAnimStruct[0xE56] != Static_Stats_Tables.captainSelectedID[0]) {
                    lbl_2_bss_100B8[0x14] = 1;
                }
                fn_2_11EA8();
                changeScene(4, 6);
                Static_Stats_Tables._48AF[3] = 1;
                menuNumber[0x26] = 1;
                Static_Stats_Tables._48AF[0] = 1;
                fn_800AD038(Static_Stats_Tables._46E8[0]);
                settingValuesTo0();
                fn_80062A74();
                fn_80035B50(15);
                fn_80035B50(18);
                fn_80035B50(9);
                fn_80035B50(6);
                fn_800AD054((s32)Static_Stats_Tables._46E8[2], (s32)Static_Stats_Tables._46E8[3]);
                maybeLoadsGameSoundFiles();
                fn_800ACFB0(audioFileDescriptors.files[0x98 / 4]);
                *(u16*)((u8*)&inningSetting + 0x58) = 0;
                *(u16*)((u8*)&inningSetting + 0x5A) = 0;
                changeScreenVariables(16);
            }
        }
        break;
    case 8:
        if (((u8*)&lbl_2_bss_100B4)[1] != 0) {
            break;
        }
        lbl_2_bss_100B8[0x40] = 1;
        lbl_2_bss_100B8[0x41] = 1;
        if (gameSetUpStep.unk55[0] != 0 || gameSetUpStep.unk55[1] != 0) {
            break;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            transition = challengeTransitionRelated(0);
        } else {
            transition = relatedToTransitions(0);
        }
        if (transition == 0) {
            break;
        }
        menuControlVariables->currentState = 9;
    case 9:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            if (cardCheck[0x47] != 0) {
                menuNumber[0x26] = 1;
            }
            Static_Stats_Tables._48AF[2] = 1;
            lbl_803CBCD8[5] = 1;
            fn_800AD038(Static_Stats_Tables._46E8[0]);
            changeScreenVariables(12);
        } else {
            menuNumber[0x26] = 1;
            fn_80021AC4();
            Static_Stats_Tables._48AD = 1;
            ((u8*)&Static_Stats_Tables)[0x4755] = 3;
            gameSetUpStep._00 = 0;
            gameSetUpStep.portCaptainSlot[1] = 0;
            gameSetUpStep.portCaptainSlot[0] = 0;
            Static_Stats_Tables.sceneAlive = 0xFF;
            Static_Stats_Tables._48AF[0] = 1;
            Static_Stats_Tables._48AF[2] = 1;
            memset(&gameSetUpStep._01[0], 0, 6);
            menuNumber[0x26] = 1;
            fn_800AD038(Static_Stats_Tables._46E8[0]);
            g_d_GameSettings.p2_CPU_match_code = P2_CPU_CODE_1_PLAYER_GAME;
            changeScreenVariables(5);
        }
        break;
    case 10:
        insertGraphicDrawingFunction(fn_8004D0F0, 0x3000);
        menuControlVariables->currentState = 11;
        break;
    case 11:
        switch (exitMenu(Static_Stats_Tables.controllerInputs[Static_Stats_Tables.playerNumberByPort[lbl_803CBD24[4]]].newInput)) {
        case 0:
            break;
        case 1:
            set803c5f77();
            break;
        case 3:
            setPortOfEachPlayer();
            lbl_2_bss_100B8[0x40] = 1;
            lbl_2_bss_100B8[0x41] = 1;
            updateCharacterSelectProcessCode(0, 7);
            updateCharacterSelectProcessCode(1, 7);
            lbl_2_bss_100B4 = TRUE;
            lbl_803CBD24[4] = 0;
            lbl_2_bss_100B8[0x41] = 1;
            lbl_2_bss_100B8[0x40] = 1;
            changeScene(15, 6);
            menuControlVariables->currentState = 5;
            break;
        case 2:
            set803c5f77();
            break;
        case 4:
            lbl_803CBD24[4] = 0;
            menuControlVariables->currentState = 2;
            aiPosSwapInputs._CF5F[0] = 0;
            break;
        }
        break;
    }
}

void fn_2_12CD8(void) {
    if (menuControlVariables->previousScreen == 5) {
        menuCursors[4] = 0;
        menuCursors[5] = 1;
    }
    Static_Stats_Tables._48AD = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        g_d_GameSettings.p2_CPU_match_code = P2_CPU_CODE_1_PLAYER_GAME;
        lbl_2_bss_100B8[0x2D] = 1;
    } else {
        lbl_2_bss_100B8[0x2D] = 2;
    }
    ((u8*)&Static_Stats_Tables)[0x4755] = 0;
    gameSetUpStep._00 = 1;
    fn_2_129AC();
    captainSelectLoadScreen();
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        challengeCaptainRelated();
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        fn_8004D990(Static_Stats_Tables.playerNumberByPort[0], 0, superstarUnlocked[0xF4]);
        fn_8004D460(0, menuCursors[4]);
    }
    ((u8*)&Static_Stats_Tables)[0x4701] = 1;
}

void fn_2_12C34(void) {
    s32 count;
    s32 cursor;
    s32 i;

    if (lbl_2_bss_100B8[0x4A] != 0) {
        return;
    }
    if (lbl_2_bss_100B8[0x20] == 1 || g_MatchInfo.player2Ind2 == 0) {
        if (lbl_2_bss_AE0 == 60000) {
            lbl_2_bss_AE0 = 0;
        }
        lbl_2_bss_AE0++;
    }
    count = 12;
    cursor = 4;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        count = 6;
    }
    for (i = 0; i < (u8)count; i++) {
        cursor++;
        if (cursor == 21) {
            cursor = 5;
        }
    }
}

void fn_2_12B60(void) {
    s32 previous[2];
    s32 slot;

    previous[0] = menuCursors[4];
    previous[1] = menuCursors[5];
    captainSelect_handleInputs(0);
    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_2_PLAYER_GAME) {
        captainSelect_handleInputs(1);
    }
    for (slot = 0; slot < 2; slot++) {
        while (loadNewCaptainModelOnCapSelectScreen(menuCursors[4 + slot], previous[slot], slot, 1) == 0 &&
               lbl_2_bss_100B8[0x10 + slot] != 0) {
            previous[slot] = menuCursors[4 + slot];
        }
    }
}

void fn_2_12A70(void) {
    if (lbl_2_bss_100B8[0x12] != 0) {
        lbl_2_bss_100B8[0x12] = 0;
        playPlayerSelectedSound(Static_Stats_Tables.captainSelectedID[0]);
    }
    if (lbl_2_bss_100B8[0x13] != 0) {
        lbl_2_bss_100B8[0x13] = 0;
        playPlayerSelectedSound(Static_Stats_Tables.captainSelectedID[1]);
    }
    if (lbl_2_bss_100B8[0x10] != 0 && lbl_2_bss_100B8[0x11] != 0) {
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            lbl_2_bss_100B4 = TRUE;
        }
        menuControlVariables->currentState = 4;
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
            lbl_2_bss_100B8[0x11] = 0;
            lbl_2_bss_100B8[0x13] = 0;
        }
    }
}

void fn_2_129D0(void) {
    memset(&lbl_2_bss_100B8[0x14], 0, lbl_2_bss_100B8[0x2D]);
    memset(&lbl_2_bss_100B8[0x1C], 0, lbl_2_bss_100B8[0x2D]);
    memset(&lbl_2_bss_100B8[0x23], -1, 2);
    lbl_2_bss_100B8[0x18] = 0;
    lbl_2_bss_100B8[0x19] = 0;
    lbl_2_bss_100B8[0x1A] = 0;
    lbl_2_bss_100B8[0x1B] = 0;
    lbl_2_bss_100B8[0x20] = 0;
    ((s8*)lbl_2_bss_100B8)[0x21] = -1;
    ((s8*)lbl_2_bss_100B8)[0x22] = -1;
    *(s32*)&lbl_2_bss_100B8[0xC] = -1;
    lbl_2_bss_100B8[0x2D] = 0;
}

void fn_2_129AC(void) {
    Static_Stats_Tables._46E8[0] = memoryUsedOrStorage.lo;
    Static_Stats_Tables._46E8[1] = memoryUsedOrStorage.hi;
}

void fn_2_12988(void) {
    Static_Stats_Tables._46E8[2] = memoryUsedOrStorage.lo;
    Static_Stats_Tables._46E8[3] = memoryUsedOrStorage.hi;
}

void captainSelectDefaultProcess(void) {
    memset(Static_Stats_Tables.charOnCharacterGridSelected, 0, 54);
    Static_Stats_Tables.startingChemStars[1] = 0;
    Static_Stats_Tables.startingChemStars[0] = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        g_MatchInfo.unk36 = 1;
        g_MatchInfo.unk37 = g_MatchInfo.unk38;
        g_MatchInfo.unk38 = 5;
    }
    if (menuControlVariables->previousScreen == 5 ||
        (menuControlVariables->previousScreen == 12 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
        fn_2_129D0();
        Static_Stats_Tables.sceneAlive = 0xFF;
        Static_Stats_Tables.captainSelectedID[1] = CHAR_ID_NONE;
        Static_Stats_Tables.captainSelectedID[0] = CHAR_ID_NONE;
        onlySetPort1ToActiveOnInitialCapSSLoad();
        switch (lbl_2_bss_100B8[0x20]) {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            Static_Stats_Tables.player2Ind = 0;
            g_d_GameSettings.p2_CPU_match_code = P2_CPU_CODE_1_PLAYER_GAME;
            g_MatchInfo.player2Ind2 = 0;
            break;
        }
        memset(lbl_2_bss_100B8, 0, 0x54);
        cursorPositions.cursor[1] = 0;
        cursorPositions.cursor[0] = 0;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            updateCharacterSelectProcessCode(0, 1);
            updateCharacterSelectProcessCode(1, 1);
        } else {
            relatedToTeamSelection4();
            insertGraphicDrawingFunction(fn_2_73758, 0x3000);
            updateCharacterSelectProcessCode(0, 1);
            lbl_803CBBC4[0] = 1;
        }
        gameSetUpStep.portCaptainSlot[0] = 0;
        gameSetUpStep.portCaptainSlot[1] = 1;
        menuCursors[4] = 0;
        menuCursors[5] = 1;
        set807518de(0, 1);
        set807518de(1, 0);
        setCaptainControllerFlags();
    } else {
        s32 slot;
        s32 cursor;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE &&
            g_d_GameSettings.p2_CPU_match_code != P2_CPU_CODE_1_PLAYER_GAME) {
            lbl_2_bss_100B8[0x10] = 0;
            lbl_2_bss_100B8[0x12] = 0;
            lbl_2_bss_100B8[0x11] = 0;
            lbl_2_bss_100B8[0x13] = 0;
        }
        for (slot = 0; slot < 2; slot++) {
            for (cursor = 0; cursor < 12; cursor++) {
                if (Static_Stats_Tables.captainSelectedID[slot] == mapCaptainCursorPositionToCharID[cursor]) {
                    menuCursors[4 + slot] = cursor;
                    break;
                }
            }
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                s32 previous = CHAR_ID_NONE;
                while (loadNewCaptainModelOnCapSelectScreen(menuCursors[4 + slot], previous, slot, 1) == 0) {
                    previous = menuCursors[4 + slot];
                }
            }
        }
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            setCaptainControllerFlags();
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME &&
            g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            lbl_2_bss_100B8[0x10] = 1;
            lbl_2_bss_100B8[0x12] = 1;
            gameSetUpStep.portCaptainSlot[0] = 1;
            add_or_RemoveCharToATeam(Static_Stats_Tables.playerNumberByPort[0], Static_Stats_Tables.captainSelectedID[0], 1);
        } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            lbl_2_bss_100B8[0x10] = 0;
            lbl_2_bss_100B8[0x12] = 0;
            gameSetUpStep.portCaptainSlot[0] = 0;
        }
        updateCharacterSelectProcessCode(0, 8);
        updateCharacterSelectProcessCode(1, 8);
    }
    lbl_2_bss_100B4 = FALSE;
    Static_Stats_Tables.sceneAlive = 0xFF;
}

void challengeCaptainRelated(void) {
    s32 captain;
    s32 i;
    u8* choices = &challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6];
    s32 selected = choices[menuCursors[4]];

    for (i = 0; i < 6; i++) {
        if (captainIDOrderedOnCapSS[i] == selected) {
            captain = i;
            break;
        }
    }
    if (i == 6) {
        OSPanic("teamselect.c", 0x459, " Captain Not Found ");
    }
    for (i = 0; i < 9; i++) {
        E(u8, CHAR_ID) characterID = Static_Stats_Tables.challengeRosters[captain].charID[i];
        g_Challenge.savedLineup[i].fieldingPosition = i;
        cursorPositions.roster.rosterCharID[0][i] = characterID;
        cursorPositions.roster.positionSwapMapping[0][i] = i;
    }
    teamLogoDetermination(0);
}
