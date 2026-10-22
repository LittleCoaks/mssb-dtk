#include "menus/stadium_select.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#define REP_HEADER_DATA_FN getRepHeaderData_menus_stadium_select
#include "header_rep_data.h"
#include "menus/debug_menu_text.h"
#include "game/match_setup/match_loading.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "musyx/musyx.h"
#include "menus/captain_select/captain_select.h"
#include "menus/text_01254.h"
#include "menus/main_menu.h"
#include "menus/yd_step.h"
#include "game/challenge/challenge_state.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800625a4.h"

extern u8 gameSetUpStep[0x64];
extern u8 menuNumber[0x28];
extern u8 lineUpInfoStruct[0x48];
extern u8 lbl_8037169C[0x1C];
extern u8* menuControlVariables;
extern u8 lbl_2_bss_F468[0xC4C];
extern u8 lbl_2_bss_100B4;
extern u8 lbl_803CBCD8[0x8];
extern int menuCursors[0x16];
extern u8 lbl_800EFBA4[0x10];
extern u8 superstarUnlocked[0x130];
extern u8 lbl_803CBBC4[8];
extern u8 cardCheck[0x5C];
extern u8 lbl_800FEF70[0x5D0];
extern u8 lbl_2_bss_758[0x388];

void fn_2_836A4(void);
void loadStadiumScreen_maybe(void);
s32 exitMenu(u16 arg0);
void set803c5f77(void);
void unregisterObjectByID(s32 id);
void fn_8004D0F0(void);
void fn_80062A74(void);

void fn_800AD038(void *arg0);
void fn_8004EEF4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void fn_2_328(void);
void bPressOnStadSelectScreen(void);


DebugMenuText lbl_2_data_1000 = {
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

/* Unreferenced; the same 0x28 bytes follow the debug table in teamselect.c. */
u8 lbl_2_data_12C4[0x28] = {
    2, 5, 4, 3, 8, 3, 4, 5, 2, 6, 0, 1, 8, 6, 7, 1, 2, 0, 7, 4,
    4, 3, 1, 2, 5, 1, 2, 4, 6, 8, 7, 6, 8, 5, 3, 3, 5, 7, 4, 6,
};

/* Unreferenced. */
u8 lbl_2_data_12EC[0x20] = { 0, 3 };

/* Stadium-select cursor slot -> STADIUM_ID. */
u8 cursorToStadIDMapping[6] = { 0, 4, 2, 3, 5, 1 };

/* Unreferenced stadium file descriptors; an identical copy is in teamselect.c. */
MatchFileDescriptor lbl_2_data_1314[16] = {
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

/* Unreferenced debug names of the six stadiums and six other scenes. */
char lbl_2_data_1414[12][0x20] = {
    "MARIO   STA", "KOOPA   STA", "WARIO   STA", "YOSHI   STA", "PEACH   STA", "DONKEY  STA",
    "YAKYUBAN", "KINOKO", "FLOWER", "STAR  ", "SPECIAL", "MIRACLE",
};

// .text:0x0001216C size:0xCC mapped:0x80651200
void fn_2_1216C(void) {
    s8 buf[4];

    memset(buf, 2, 4);

    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        buf[Static_Stats_Tables.playerNumberByPort[0]] = 1;
        if (Static_Stats_Tables.playerNumberByPort[0] == 0) {
            buf[1] = 2;
        } else {
            buf[0] = 2;
        }
    } else {
        buf[Static_Stats_Tables.playerNumberByPort[1]] = 1;
        buf[Static_Stats_Tables.playerNumberByPort[0]] = 1;
    }

    fn_8004EEF4(buf[0], buf[1], buf[2], buf[3], 1);
}

// .text:0x000120D0 size:0x9C mapped:0x80651164
void fn_2_120D0(void) {
    Static_Stats_Tables._48AD = 1;
    Static_Stats_Tables._4744[0x4755 - 0x4744] = 3;
    gameSetUpStep[0] = 0;
    gameSetUpStep[0x5A] = 0;
    gameSetUpStep[0x59] = 0;
    Static_Stats_Tables.sceneAlive = 0xFF;
    Static_Stats_Tables._48AF[0] = 1;
    Static_Stats_Tables._48AF[2] = 1;
    memset(&gameSetUpStep[1], 0, 6);
    menuNumber[0x26] = 1;
    fn_800AD038(Static_Stats_Tables._46E8[0]);
    g_d_GameSettings.p2_CPU_match_code = P2_CPU_CODE_1_PLAYER_GAME;
}

// .text:0x00011EA8 size:0x228 mapped:0x80650F3C
void fn_2_11EA8(void) {
    CharacterStats* dst;
    CharacterStats* src;
    int i;
    s8 id;

    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        id = cursorPositions.roster.rosterCharID[0][i];
        src = &Static_Stats_Tables.characterStats[id / 9][id % 9];
        dst = &inMemRoster[0][i];

        memcpy(&dst->stats, &src->stats, 0x1E);

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

        lineUpInfoStruct[i * 4 + 0] = lineUpInfoStruct[i * 4 + 1] = lineUpInfoStruct[i * 4 + 2] = i;
    }
}

// .text:0x00011698 size:0x810 mapped:0x8065072C
void selectStadiumScreen(void) {
    s8 best;
    int i;
    u32 v;
    int* cursor;
    u8* ss;
    u8* cb;

    best = -1;

    switch (*(u16*)(menuControlVariables + 4)) {
    case 0:
        if (*(u16*)(menuControlVariables + 6) == 0xD) {
            updateCharacterSelectProcessCode(0, 0x26);
            *(u16*)(menuControlVariables + 4) = 1;
        } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            changeScene(1, 6);
            fn_2_836A4();
            lbl_2_bss_F468[0x57] = 0;

            for (i = 0; i < 4; i++) {
                if (superstarUnlocked[0xE4 + i] != 0 && best < i) {
                    best = i;
                }
            }

            if (best != -1) {
                lbl_2_bss_F468[0x57] = best + 1;
                if (lbl_2_bss_F468[0x57] > 3) {
                    lbl_2_bss_F468[0x57] = 3;
                }
            }
            *(u16*)(menuControlVariables + 4) = 5;
        } else {
            loadStadiumScreen_maybe();

            if (gameSetUpStep[0x55] == 0 && gameSetUpStep[0x56] == 0) {
                menuNumber[0] = 5;
                menuNumber[9] = menuNumber[8];
                menuNumber[8] = *(u16*)&lbl_800FEF70[0x58];
                g_MatchInfo.unk36 = 1;
                g_MatchInfo.unk37 = g_MatchInfo.unk38;
                g_MatchInfo.unk38 = 2;
                gameSetUpStep[0] = 4;

                if (Static_Stats_Tables._4700[3] == 0) {
                    menuCursors[0x11] = 0;
                    menuCursors[0x11] = 0;
                }

                Static_Stats_Tables._4700[3] = 1;
                updateCharacterSelectProcessCode(0, 0x27);
                *(u16*)(menuControlVariables + 4) = 1;
            }
        }
        break;

    case 1:
        if (gameSetUpStep[0x55] == 0 && gameSetUpStep[0x56] == 0) {
            *(u16*)(menuControlVariables + 4) = 2;
        }
        break;

    case 2:
        for (i = 0; i < 2; i++) {
            stadiumSelectControls(i);
        }
        break;

    case 3:
        ss = lbl_803CBCD8;
        if (ss[4] == 0 && gameSetUpStep[0x5D] == 0) {
            gameSetUpStep[0] = 3;
            *(u16*)(menuControlVariables + 4) = 0xB;
        }
        break;

    case 4:
        if (gameSetUpStep[0x5D] == 0) {
            lbl_2_bss_100B4 = 1;
            *(u16*)(menuControlVariables + 4) = 0xC;
        }
        break;

    case 5:
        if (gameSetUpStep[0x55] == 0) {
            cb = lbl_803CBBC4;
            cb[0] = 0;
            cb[2] = 0;
            cb[3] = 0;
            cb[4] = 0;
            menuCursors[0x11] = 0;
            changeScene(1, 6);
            g_MatchInfo.unk36 = 1;
            g_MatchInfo.unk37 = g_MatchInfo.unk38;
            g_MatchInfo.unk38 = 4;
            cb[0] = 0x5D;
            cb[5] = 0;
            *(u16*)(menuControlVariables + 4) = 6;
        }
        break;

    case 6:
        if (gameSetUpStep[0x55] == 0) {
            cb = lbl_803CBBC4;
            cursor = &menuCursors[0x11];
            cb[1] = *cursor;
            fn_2_15A90(cursor, 0, lbl_2_bss_F468[0x57]);
            Static_Stats_Tables._4711[0] = *cursor;

            if (cb[1] != Static_Stats_Tables._4711[0]) {
                lbl_803CBBC4[0] = 0x5E;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }

            if (Static_Stats_Tables.controllerInputs[0].newInput & INPUT_BUTTON_A) {
                if (*cursor < 6) {
                    v = Static_Stats_Tables._4711[0];

                    if (superstarUnlocked[0xE3 + v] == 0 && v != 0) {
                        sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                    } else {
                        lbl_803CBBC4[0] = 0x60;
                        Static_Stats_Tables.sceneAlive = 1;
                        cursorSndFx(INPUT_BUTTON_A);
                        *(u16*)(menuControlVariables + 4) = 7;
                    }
                }
            } else if (Static_Stats_Tables.controllerInputs[0].newInput & INPUT_BUTTON_B) {
                cursorSndFx(INPUT_BUTTON_B);
                lbl_803CBBC4[0] = 0x60;
                Static_Stats_Tables.sceneAlive = 1;
                *(u16*)(menuControlVariables + 4) = 8;
            }
        }
        break;

    case 7:
        cb = lbl_803CBBC4;
        if (cb[5] != 0) {
            cb[5] = 0;
            lbl_2_bss_100B4 = 1;
            *(u16*)(menuControlVariables + 4) = 0xC;
        }
        break;

    case 8:
        cb = lbl_803CBBC4;
        if (cb[5] != 0) {
            *(u16*)(menuControlVariables + 4) = 0xB;
        }
        break;

    case 9:
        insertGraphicDrawingFunction(fn_8004D0F0, 0x3000);
        *(u16*)(menuControlVariables + 4) = 0xA;
        break;

    case 10:
        switch (exitMenu(Static_Stats_Tables.controllerInputs[0].newInput)) {
        case 0:
            break;

        case 1:
            set803c5f77();
            break;

        case 3:
            loadDemoMatch(0xC, 1, 1);
            ss = lbl_803CBCD8;
            ss[4] = 1;
            unregisterObjectByID(0xF);
            unregisterObjectByID(0x12);
            unregisterObjectByID(9);
            unregisterObjectByID(6);
            Static_Stats_Tables._48AF[0] = 1;
            Static_Stats_Tables._48AF[2] = 1;
            menuNumber[0x26] = 1;
            changeScene(0xF, 6);
            *(u16*)(menuControlVariables + 4) = 0xC;
            lbl_2_bss_758[0] = 1;
            break;

        case 2:
            set803c5f77();
            break;

        case 4:
            aiPosSwapInputs.loadMatchRelInd = 0;
            *(u16*)(menuControlVariables + 4) = 2;
            break;
        }
        break;

    case 11:
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            ss = lbl_803CBCD8;

            if (ss[4] != 0) {
                break;
            }
            if (gameSetUpStep[0x5D] != 0) {
                break;
            }
            ss[1] = 0;
            ss[0] = 0;
            changeScreenVariables(0xB);
        } else {
            cb = lbl_803CBBC4;
            cb[4] = 1;

            if (cardCheck[0x47] == 0) {
                changeScreenVariables(0xF);
            } else {
                menuNumber[0x26] = 1;
                Static_Stats_Tables._48AF[0] = 1;
                changeScreenVariables(5);
            }
        }
        *(u16*)(menuControlVariables + 8) = 0;
        break;

    case 12:
        if (lbl_2_bss_758[0] != 0) {
            if (menuNumber[0x24] == 0) {
                fn_80062A74();
                lbl_2_bss_758[0] = 0;
                changeScene(0xF, 6);
                changeScreenVariables(4);
            }
        } else if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            ss = lbl_803CBCD8;
            ss[4] = 0;
            lbl_2_bss_F468[0x58] = 0;
            changeScreenVariables(0xD);
        } else {
            cb = lbl_803CBBC4;

            if (cb[3] != 1) {
                cb[4] = 1;
                changeScreenVariables(9);
            }
        }
        break;
    }
}

// .text:0x00011340 size:0x358 mapped:0x806503D4
void stadiumSelectControls(u8 idx) {
    u8 flag;
    int cur;
    int r;
    s8 p;
    u16 input0;
    u16 input1;
    int v;
    int i;

    flag = 0;

    if (lbl_803CBCD8[0] != 0) {
        cur = menuCursors[0x11];

        do {
            if (superstarUnlocked[0xF5] != 0) {
                r = stadiumRandomizer(0, 5);
            } else {
                r = stadiumRandomizer(0, 4);
            }
        } while (cur == r);

        menuCursors[0x11] = r;
        lbl_803CBCD8[1] = lbl_803CBCD8[1] - 1;
        updateCharacterSelectProcessCode(0, 0x28);
        return;
    }

    if (gameSetUpStep[0x55] != 0) {
        return;
    }

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        p = Static_Stats_Tables.playerNumberByPort[idx];

        for (i = 0; i < 2; i++) {
            if (g_d_GameSettings.PlayerPorts[i] == p) {
                flag = 1;
            }
        }
        Static_Stats_Tables.playerNumberByPort[idx] = p;

        if (flag == 0) {
            return;
        }
    } else if (idx != 0) {
        return;
    }

    input0 = Static_Stats_Tables.controllerInputs[idx].processedInput;
    input1 = Static_Stats_Tables.controllerInputs[idx].newInput;

    if (input0 & INPUT_BUTTON_LEFT) {
        if (gameSetUpStep[0x5D] != 0x24) {
            v = menuCursors[0x11] - 1;
            if (v < 0) {
                v = 5;
            }
            menuCursors[0x11] = v;
            updateCharacterSelectProcessCode(0, 0x28);
            cursorSndFx(INPUT_BUTTON_LEFT);
        }
    } else if (input0 & INPUT_BUTTON_RIGHT) {
        if (gameSetUpStep[0x5D] != 0x24) {
            v = menuCursors[0x11] + 1;
            if (v == 6) {
                v = 0;
            }
            menuCursors[0x11] = v;
            updateCharacterSelectProcessCode(0, 0x28);
            cursorSndFx(INPUT_BUTTON_RIGHT);
        }
    } else if (input1 & INPUT_TRIGGER_R) {
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            lbl_803CBCD8[0] = 1;
            lbl_803CBCD8[1] = 6;
        }
    } else if (input1 & INPUT_BUTTON_A) {
        if (menuCursors[0x11] < 6) {
            if (superstarUnlocked[0xF5] == 0 &&
                cursorToStadIDMapping[menuCursors[0x11]] == 1) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if (gameSetUpStep[0x5D] == 0) {
                g_d_GameSettings.StadiumID = cursorToStadIDMapping[menuCursors[0x11]];
                lbl_2_bss_F468[0x58] = 1;
                fn_2_328();
                cursorSndFx(INPUT_BUTTON_A);
                updateCharacterSelectProcessCode(0, 0x25);
                *(u16*)(menuControlVariables + 4) = 4;
            }
        }
    } else if (input1 & INPUT_BUTTON_B) {
        if (lbl_803CBCD8[0] == 0 && gameSetUpStep[0x5D] == 0) {
            bPressOnStadSelectScreen();
            cursorSndFx(INPUT_BUTTON_B);
            *(u16*)(menuControlVariables + 6) = 0xC;
            updateCharacterSelectProcessCode(0, 0x24);
            *(u16*)(menuControlVariables + 4) = 3;
        }
    }
}

// .text:0x000112F4 size:0x4C mapped:0x80650388
s32 fn_2_112F4(UnkText988Arg* arg0, s32 indexOffset, s32 arg2, u16* arg3, u16 arg4) {
    TextGraphicsObject* obj = graphicsRelatedArray[arg0->unk14 + indexOffset].object;

    if ((s32)(*(u32*)&obj->unk58[4] >> 16) == arg3[arg2 + 1] - 1) {
        *(u16*)&obj->unk58[0xC] = arg4;
        return TRUE;
    }
    return FALSE;
}
