#include "menus/text_110B0.h"
#include "header_rep_data.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "musyx/musyx.h"
#include "menus/captain_select/captain_select.h"
#include "menus/text_01254.h"
#include "menus/yd_step.h"

extern u8 Static_Stats_Tables[0x5240];
extern u8 gameSetUpStep[0x64];
extern u8 menuNumber[0x28];
extern u8 g_d_GameSettings[0x58];
extern u8 cursorPositions[0x5C];
extern u8 lineUpInfoStruct[0x48];
extern u8 inMemRoster[0xB40];
extern u8 aiPosSwapInputs[0x24C98];
extern u8 lbl_8037169C[0x1C];
extern u8 starMissionCompletionTracker[0x4508];
extern u8* menuControlVariables;
extern u8 lbl_2_data_3CE0[0x8];
extern u8 lbl_2_bss_F468[0xC4C];
extern u8 lbl_2_bss_100B4;
extern u8 lbl_803CBCD0[0x18];
extern int lbl_2_bss_F410[0x16];
extern u8 lbl_800EFBA4[0x10];
extern u8 superstarUnlocked[0x130];
extern u8 cursorToStadIDMapping[0x288];
extern u8 lbl_803CBBC2[0xA];
extern u8 lbl_803C5EA4[0x3C];
extern u8 lbl_803C50E8[0x5C];
extern u8 lbl_800FEF70[0x5D0];
extern u8 lbl_2_bss_758[0x388];

void changeScene(s32 arg0, s32 arg1);
void fn_2_836A4(void);
void loadStadiumScreen_maybe(void);
s32 exitMenu(u16 arg0);
void set803c5f77(void);
void unregisterObjectByID(s32 id);
void fn_8004D0F0(void);
void fn_80062A74(void);

void fn_800AD038(void *arg0);
void fn_8004EEF4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

int stadiumRandomizer(int min, int max);
void cursorSndFx(u16 button);
void fn_2_328(void);
void bPressOnStadSelectScreen(void);

void challenge_setTransitionScreenCharacterPortrait(s32 arg0, s32 arg1);
void cssLoadingScreenRelated(void);
void cssResetRosterStruct(void);
void characterSelectScreenControlable(void);
void fn_2_72630(void);
void cssSelectCPUDifficulty(void);
void cssUnloadScreen(void);
void cssTransitionToNewScreen_maybe(void);
void cssChangeScreens(void);
void updateCharacterSelectProcessCode(int arg0, int arg1);

// .text:0x000110B0 size:0x244 mapped:0x80650144
void teamSelectScreenMain(void) {
    switch (*(u16*)(menuControlVariables + 4)) {
    case 0:
        if (g_d_GameSettings[7] == 5 || *(u16*)(menuControlVariables + 6) != 9) {
            *(u16*)(menuControlVariables + 4) = 5;
        } else {
            aiPosSwapInputs[0xCFA1] = 0;
            *(u16*)(menuControlVariables + 4) = 1;
        }
        break;
    case 1:
        if (g_d_GameSettings[7] == 5 && lbl_8037169C[0x12] == 0) {
            challenge_setTransitionScreenCharacterPortrait(
                0xA, (s8)lbl_2_data_3CE0[starMissionCompletionTracker[0x441E]]);
        }
        cssLoadingScreenRelated();
        cssResetRosterStruct();
        lbl_2_bss_F468[0x56] = 0;
        *(u16*)(menuControlVariables + 4) = 2;
        break;
    case 2:
        if ((g_d_GameSettings[7] == 5 ? lbl_8037169C[0x12] : 1) != 0) {
            characterSelectScreenControlable();
        }
        break;
    case 3:
        if ((s8)lbl_2_bss_F468[0x36] < 0 && gameSetUpStep[0x5D] == 0 &&
            gameSetUpStep[0x5E] == 0) {
            fn_2_72630();
            lbl_2_bss_F468[0x33] = 0;
            *(u16*)(menuControlVariables + 4) = 4;
        } else {
            lbl_2_bss_F468[0x36] = lbl_2_bss_F468[0x36] - 1;
        }
        break;
    case 4:
        cssSelectCPUDifficulty();
        break;
    case 5:
        cssUnloadScreen();
        break;
    case 6:
        cssTransitionToNewScreen_maybe();
        break;
    case 7:
        if ((s8)lbl_2_bss_F468[0x36] < 0) {
            updateCharacterSelectProcessCode(0, 0x13);
            updateCharacterSelectProcessCode(1, 0x13);
            lbl_2_bss_F468[0x4F] = 0;
            lbl_2_bss_F468[0x2E] = 0;
            lbl_2_bss_100B4 = 1;
            *(u16*)(menuControlVariables + 4) = 8;
        } else {
            lbl_2_bss_F468[0x36] = lbl_2_bss_F468[0x36] - 1;
        }
        break;
    case 8:
        cssChangeScreens();
        break;
    }
}

// .text:0x000112F4 size:0x4C mapped:0x80650388
s32 fn_2_112F4(UnkText988Arg* arg0, s32 indexOffset, s32 arg2, u16* arg3, u16 arg4) {
    TextGraphicsObject* obj = graphicsRelatedArray[arg0->unk14 + indexOffset].object;

    if ((s32)(*(u32*)&obj->unk58[4] >> 16) == arg3[arg2 + 1] - 1) {
        *(u16*)&obj->unk58[0xC] = arg4;
        return 1;
    }
    return 0;
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

    flag = 0;

    if (lbl_803CBCD0[8] != 0) {
        cur = lbl_2_bss_F410[0x11];

        do {
            if (superstarUnlocked[0xF5] != 0) {
                r = stadiumRandomizer(0, 5);
            } else {
                r = stadiumRandomizer(0, 4);
            }
        } while (cur == r);

        lbl_2_bss_F410[0x11] = r;
        lbl_803CBCD0[9] = lbl_803CBCD0[9] - 1;
        updateCharacterSelectProcessCode(0, 0x28);
        return;
    }

    if (gameSetUpStep[0x55] != 0) {
        return;
    }

    if (g_d_GameSettings[7] != 5) {
        p = Static_Stats_Tables[idx + 0x46F8];

        if (g_d_GameSettings[0x50] == p) {
            flag = 1;
        }
        if (g_d_GameSettings[0x51] == p) {
            flag = 1;
        }
        Static_Stats_Tables[idx + 0x46F8] = p;

        if (flag == 0) {
            return;
        }
    } else if (idx != 0) {
        return;
    }

    input0 = *(u16*)&Static_Stats_Tables[idx * 6 + 0x4730];
    input1 = *(u16*)&Static_Stats_Tables[idx * 6 + 0x472E];

    if (input0 & 1) {
        if (gameSetUpStep[0x5D] != 0x24) {
            v = lbl_2_bss_F410[0x11] - 1;
            if (v < 0) {
                v = 5;
            }
            lbl_2_bss_F410[0x11] = v;
            updateCharacterSelectProcessCode(0, 0x28);
            cursorSndFx(1);
        }
    } else if (input0 & 2) {
        if (gameSetUpStep[0x5D] != 0x24) {
            v = lbl_2_bss_F410[0x11] + 1;
            if (v == 6) {
                v = 0;
            }
            lbl_2_bss_F410[0x11] = v;
            updateCharacterSelectProcessCode(0, 0x28);
            cursorSndFx(2);
        }
    } else if (input1 & 0x20) {
        if (g_d_GameSettings[7] != 5) {
            lbl_803CBCD0[8] = 1;
            lbl_803CBCD0[9] = 6;
        }
    } else if (input1 & 0x100) {
        if (lbl_2_bss_F410[0x11] < 6) {
            if (superstarUnlocked[0xF5] == 0 &&
                cursorToStadIDMapping[lbl_2_bss_F410[0x11]] == 1) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if (gameSetUpStep[0x5D] == 0) {
                g_d_GameSettings[9] = cursorToStadIDMapping[lbl_2_bss_F410[0x11]];
                lbl_2_bss_F468[0x58] = 1;
                fn_2_328();
                cursorSndFx(0x100);
                updateCharacterSelectProcessCode(0, 0x25);
                *(u16*)(menuControlVariables + 4) = 4;
            }
        }
    } else if (input1 & 0x200) {
        if (lbl_803CBCD0[8] == 0 && gameSetUpStep[0x5D] == 0) {
            bPressOnStadSelectScreen();
            cursorSndFx(0x200);
            *(u16*)(menuControlVariables + 6) = 0xC;
            updateCharacterSelectProcessCode(0, 0x24);
            *(u16*)(menuControlVariables + 4) = 3;
        }
    }
}

// .text:0x00011698 size:0x810 mapped:0x8065072C
void selectStadiumScreen(void) {
    s8 best;
    int i;
    int v;
    int* cursor;
    u8* ss;
    u8* cb;

    best = -1;

    switch (*(u16*)(menuControlVariables + 4)) {
    case 0:
        if (*(u16*)(menuControlVariables + 6) == 0xD) {
            updateCharacterSelectProcessCode(0, 0x26);
            *(u16*)(menuControlVariables + 4) = 1;
        } else if (g_d_GameSettings[7] == 5) {
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
                lbl_803C5EA4[0x36] = 1;
                lbl_803C5EA4[0x37] = lbl_803C5EA4[0x38];
                lbl_803C5EA4[0x38] = 2;
                gameSetUpStep[0] = 4;

                if (Static_Stats_Tables[0x4703] == 0) {
                    lbl_2_bss_F410[0x11] = 0;
                    lbl_2_bss_F410[0x11] = 0;
                }

                Static_Stats_Tables[0x4703] = 1;
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
        ss = &lbl_803CBCD0[8];
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
            cb = &lbl_803CBBC2[2];
            cb[0] = 0;
            cb[2] = 0;
            cb[3] = 0;
            cb[4] = 0;
            lbl_2_bss_F410[0x11] = 0;
            changeScene(1, 6);
            lbl_803C5EA4[0x36] = 1;
            lbl_803C5EA4[0x37] = lbl_803C5EA4[0x38];
            lbl_803C5EA4[0x38] = 4;
            cb[0] = 0x5D;
            cb[5] = 0;
            *(u16*)(menuControlVariables + 4) = 6;
        }
        break;

    case 6:
        if (gameSetUpStep[0x55] == 0) {
            cb = &lbl_803CBBC2[2];
            cursor = &lbl_2_bss_F410[0x11];
            cb[1] = *cursor;
            fn_2_15A90(cursor, 0, lbl_2_bss_F468[0x57]);
            Static_Stats_Tables[0x4711] = *cursor;

            if (cb[1] != Static_Stats_Tables[0x4711]) {
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                cb[0] = 0x5E;
            }

            if (*(u16*)&Static_Stats_Tables[0x472E] & 0x100) {
                if (*cursor < 6) {
                    v = Static_Stats_Tables[0x4711];

                    if (superstarUnlocked[0xE3 + v] == 0 && v != 0) {
                        sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                    } else {
                        cb[0] = 0x60;
                        Static_Stats_Tables[0x472A] = 1;
                        cursorSndFx(0x100);
                        *(u16*)(menuControlVariables + 4) = 7;
                    }
                }
            } else if (*(u16*)&Static_Stats_Tables[0x472E] & 0x200) {
                cursorSndFx(0x200);
                cb[0] = 0x60;
                Static_Stats_Tables[0x472A] = 1;
                *(u16*)(menuControlVariables + 4) = 8;
            }
        }
        break;

    case 7:
        cb = &lbl_803CBBC2[2];
        if (cb[5] != 0) {
            cb[5] = 0;
            lbl_2_bss_100B4 = 1;
            *(u16*)(menuControlVariables + 4) = 0xC;
        }
        break;

    case 8:
        cb = &lbl_803CBBC2[2];
        if (cb[5] != 0) {
            *(u16*)(menuControlVariables + 4) = 0xB;
        }
        break;

    case 9:
        insertGraphicDrawingFunction(fn_8004D0F0, 0x3000);
        *(u16*)(menuControlVariables + 4) = 0xA;
        break;

    case 10:
        switch (exitMenu(*(u16*)&Static_Stats_Tables[0x472E])) {
        case 0:
            break;

        case 1:
            set803c5f77();
            break;

        case 3:
            loadDemoMatch(0xC, 1, 1);
            ss = &lbl_803CBCD0[8];
            ss[4] = 1;
            unregisterObjectByID(0xF);
            unregisterObjectByID(0x12);
            unregisterObjectByID(9);
            unregisterObjectByID(6);
            Static_Stats_Tables[0x48AF] = 1;
            Static_Stats_Tables[0x48B1] = 1;
            menuNumber[0x26] = 1;
            changeScene(0xF, 6);
            *(u16*)(menuControlVariables + 4) = 0xC;
            lbl_2_bss_758[0] = 1;
            break;

        case 2:
            set803c5f77();
            break;

        case 4:
            aiPosSwapInputs[0xCF5F] = 0;
            *(u16*)(menuControlVariables + 4) = 2;
            break;
        }
        break;

    case 11:
        if (g_d_GameSettings[7] != 5) {
            ss = &lbl_803CBCD0[8];

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
            cb = &lbl_803CBBC2[2];
            cb[4] = 1;

            if (lbl_803C50E8[0x47] == 0) {
                changeScreenVariables(0xF);
            } else {
                menuNumber[0x26] = 1;
                Static_Stats_Tables[0x48AF] = 1;
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
        } else if (g_d_GameSettings[7] != 5) {
            ss = &lbl_803CBCD0[8];
            ss[4] = 0;
            lbl_2_bss_F468[0x58] = 0;
            changeScreenVariables(0xD);
        } else {
            cb = &lbl_803CBBC2[2];

            if (cb[3] != 1) {
                cb[4] = 1;
                changeScreenVariables(9);
            }
        }
        break;
    }
}

// .text:0x00011EA8 size:0x228 mapped:0x80650F3C
void fn_2_11EA8(void) {
    u8* cp;
    u8* dst;
    u8* lp;
    u8* src;
    int i;
    s8 v;

    lp = lineUpInfoStruct;
    cp = cursorPositions;
    dst = inMemRoster;

    for (i = 0; i < 9; i++) {
        v = cp[2];
        src = Static_Stats_Tables + (v / 9) * 0x5A0 + (v % 9) * 0xA0;

        memcpy(dst, src, 0x1E);

        *(s16*)(dst + 0x24) = *(s16*)(src + 0x24);
        dst[0x26] = src[0x26];
        dst[0x27] = src[0x27];

        memcpy(dst + 0x28, src + 0x28, 2);
        memcpy(dst + 0x2A, src + 0x2A, 2);

        dst[0x2C] = src[0x2C];
        dst[0x2D] = src[0x2D];
        dst[0x2E] = src[0x2E];
        dst[0x2F] = src[0x2F];
        dst[0x30] = src[0x30];
        dst[0x31] = src[0x31];
        dst[0x32] = src[0x32];
        dst[0x33] = src[0x33];
        dst[0x34] = src[0x34];

        memcpy(dst + 0x35, src + 0x35, 2);

        *(u32*)(dst + 0x20) = *(u32*)(src + 0x20);

        memcpy(dst + 0x37, src + 0x37, 4);
        memcpy(dst + 0x3B, src + 0x3B, 0x36);

        dst[0x71] = src[0x71];

        *(u16*)(dst + 0x74) = *(u16*)(src + 0x74);
        *(u16*)(dst + 0x76) = *(u16*)(src + 0x76);
        *(u16*)(dst + 0x78) = *(u16*)(src + 0x78);
        *(u16*)(dst + 0x7A) = *(u16*)(src + 0x7A);
        *(u16*)(dst + 0x7C) = *(u16*)(src + 0x7C);
        *(u16*)(dst + 0x7E) = *(u16*)(src + 0x7E);
        *(u16*)(dst + 0x80) = *(u16*)(src + 0x80);
        *(u16*)(dst + 0x82) = *(u16*)(src + 0x82);
        *(u16*)(dst + 0x84) = *(u16*)(src + 0x84);
        *(u16*)(dst + 0x86) = *(u16*)(src + 0x86);
        *(u16*)(dst + 0x88) = *(u16*)(src + 0x88);
        *(u16*)(dst + 0x8A) = *(u16*)(src + 0x8A);
        *(u16*)(dst + 0x8C) = *(u16*)(src + 0x8C);
        *(u16*)(dst + 0x8E) = *(u16*)(src + 0x8E);
        *(u16*)(dst + 0x90) = *(u16*)(src + 0x90);
        *(u16*)(dst + 0x92) = *(u16*)(src + 0x92);
        *(u16*)(dst + 0x94) = *(u16*)(src + 0x94);
        *(u16*)(dst + 0x96) = *(u16*)(src + 0x96);
        *(u16*)(dst + 0x98) = *(u16*)(src + 0x98);
        *(u16*)(dst + 0x9A) = *(u16*)(src + 0x9A);
        *(u16*)(dst + 0x9C) = *(u16*)(src + 0x9C);

        lp[0] = lp[1] = lp[2] = i;

        cp++;
        lp += 4;
        dst += 0xA0;
    }
}

// .text:0x000120D0 size:0x9C mapped:0x80651164
void fn_2_120D0(void) {
    Static_Stats_Tables[0x48AD] = 1;
    Static_Stats_Tables[0x4755] = 3;
    gameSetUpStep[0] = 0;
    gameSetUpStep[0x5A] = 0;
    gameSetUpStep[0x59] = 0;
    Static_Stats_Tables[0x472A] = 0xFF;
    Static_Stats_Tables[0x48AF] = 1;
    Static_Stats_Tables[0x48B1] = 1;
    memset(&gameSetUpStep[1], 0, 6);
    menuNumber[0x26] = 1;
    fn_800AD038(*(void **)&Static_Stats_Tables[0x46E8]);
    g_d_GameSettings[0x10] = 0;
}

// .text:0x0001216C size:0xCC mapped:0x80651200
void fn_2_1216C(void) {
    s8 buf[4];

    memset(buf, 2, 4);

    if (g_d_GameSettings[0x10] == 0) {
        s8 p = (s8)Static_Stats_Tables[0x46F8];

        buf[p] = 1;
        if ((s8)Static_Stats_Tables[0x46F8] == 0) {
            buf[1] = 2;
        } else {
            buf[0] = 2;
        }
    } else {
        buf[(s8)Static_Stats_Tables[0x46F9]] = 1;
        buf[(s8)Static_Stats_Tables[0x46F8]] = 1;
    }

    fn_8004EEF4(buf[0], buf[1], buf[2], buf[3], 1);
}

