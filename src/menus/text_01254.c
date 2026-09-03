#include "menus/text_01254.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"
#include "musyx/musyx.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

extern u32 lbl_803CB750[4];
extern u8 gameSetUpStep[0x64];
extern u8 menuNumber[0x28];
extern u8 lbl_800EFBA4[0x10];
extern int lbl_2_bss_F410[0x16];
extern u8 *menuControlVariables;
extern u8 lbl_80366158[0x30];
extern u8 lineUpInfoStruct[0x48];
extern s16 lbl_2_data_E64[18];
extern s16 lbl_2_data_E88[18];
extern u8 lbl_2_bss_20[0x380];
extern u8 lbl_803CBCD0[0x18];
extern u8 lbl_803C50E8[0x5C];
extern u8 lbl_800EF808[0x39C];
extern u8 lbl_2_data_180[0x4A4];
extern u8 superstarUnlocked[0x130];
extern u8 lbl_803C6714[0x10];
extern u8 *currentDrawingItem;

void settingValuesTo0(void);
void initializeUnknown(void);
void fn_80062764(void *arg0);
int fn_80022B68(void);
void fn_2_12988(void);
int fn_800697B0(void);
s32 diskReadRelated(void *arg0, s32 arg1);
void fn_8003F23C(void);
void relatedToReturningToPracticeMenu(void);
void *insertGraphicDrawingFunction(void (*func)(void), u32 priority);

void fn_2_74D8C(void);
void fn_80021AC8(void);
void relatedToTeamSelection4(void);
void fn_80062A74(void);
void fn_80035B50(int arg0);
void fn_800AD054(int arg0, int arg1);
void maybeLoadsGameSoundFiles(void);
void fn_800ACFB0(void *arg0);
void changeScreenVariables(u16 screen);

void changeScene(u8 scene, u16 arg1);
void updateCharacterSelectProcessCode(int arg0, int arg1);
void fn_800670A0(u8 arg0);

extern u8 unlockableCharacter_noDupeNoGapCharID[0x8];
extern u8 characterStaticIndexes[0x144];

void fn_800684A4(void);
void fn_800649BC(void);
void DraftRandomTeamDemo(int team);
void copyInfoToInMemRoster(void);
void teamLogoDetermination(int team);
void unsure_FillRosterPositions(int team);
void characterSelectScreen(int team);
void setCaptainLocInRoster(void);
void selectRandomStadium(void);

// .text:0x00001254 size:0x4 mapped:0x806402E8
void fn_2_1254(void) {
    return;
}

// .text:0x00001258 size:0x48 mapped:0x806402EC
u32 fn_2_1258(u8 *p, int off, int type) {
    u32 val = 0;

    switch (type) {
    case 1:
        val = p[off];
        break;
    case 2:
        val = *(u16 *)(p + off);
        break;
    case 4:
        val = *(u32 *)(p + off);
        break;
    }

    return val;
}

// .text:0x000012A0 size:0x2C mapped:0x80640334
void fn_2_12A0(s16 *p, int v) {
    if (*p < 0x7FFF - (s16)v) {
        *p = *p + v;
    } else {
        *p = 0x7FFF;
    }
}

// .text:0x000012CC size:0x2C mapped:0x80640360
void fn_2_12CC(u8 *p, int v) {
    if (*p + (u16)v > 0xFF) {
        *p = 0xFF;
    } else {
        *p = *p + v;
    }
}

// .text:0x000012F8 size:0x30 mapped:0x8064038C
void fn_2_12F8(u16 *p, int v) {
    if (*p + (u16)v > 0xFFFF) {
        *p = 0xFFFF;
    } else {
        *p = *p + v;
    }
}

// .text:0x00001328 size:0x2C mapped:0x806403BC
void fn_2_1328(u32 *p, u16 v) {
    if (*p + v > 0x7FFFFFFF) {
        *p = 0x7FFFFFFF;
    } else {
        *p = *p + v;
    }
}

// .text:0x00001354 size:0x108 mapped:0x806403E8
void fn_2_1354(Unk8Rec *arr, int n, int desc) {
    u32 i;
    u32 j;

    if (n < 2) {
        return;
    }

    if (desc == 0) {
        for (i = 0; i < n; i++) {
            j = i;
            while (j >= 1 && arr[j - 1].unk4 > arr[j].unk4) {
                Unk8Rec tmp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp;
                j--;
            }
        }
    } else {
        for (i = 0; i < n; i++) {
            j = i;
            while (j >= 1 && arr[j - 1].unk4 < arr[j].unk4) {
                Unk8Rec tmp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp;
                j--;
            }
        }
    }
}

// .text:0x0000145C size:0x30 mapped:0x806404F0
int fn_2_145C(u16 *a, u16 *b) {
    u16 ca;
    u16 cb;

    do {
        ca = *a++;
        cb = *b++;
        if (ca != cb) {
            return 0;
        }
    } while (ca != 0x4000);

    return 1;
}

// .text:0x0000148C size:0x6C mapped:0x80640520
int fn_2_148C(u16 *s) {
    int width = 0;
    u16 c;

    while (1) {
        c = *s++;
        if (c & 0x4000) {
            switch (c & 0x3FFF) {
            case 0:
                goto done;
            case 2:
                width += 0xB;
                break;
            case 3:
                width += 0x16;
                break;
            }
        } else if (c & 0x8000) {
            width += 0x16;
        } else {
            width += 0xB;
        }
    }

done:
    return width;
}

// .text:0x000014F8 size:0x5C mapped:0x8064058C
int stadiumRandomizer(int a, int b) {
    int lo;
    int hi;

    if (a == b) {
        return a;
    }

    if (a <= b) {
        lo = a;
        hi = b;
    } else {
        lo = b;
        hi = a;
    }

    lbl_803CB750[0] = lbl_803CB750[0] * 0x5D588B65 + 1;
    return (int)(lbl_803CB750[0] >> 16) % (hi - lo + 1) + lo;
}

// .text:0x00001554 size:0x24 mapped:0x806405E8
u32 fn_2_1554(void) {
    return (lbl_803CB750[0] = lbl_803CB750[0] * 0x5D588B65 + 1);
}

// .text:0x00001578 size:0x288 mapped:0x8064060C
void fn_2_1578(void) {
    u16 input[3];

    memset(input, 0, 6);
    input[0] = Static_Stats_Tables.controllerInputs[0].currentHeldInput;
    input[1] = Static_Stats_Tables.controllerInputs[0].newInput;
    input[2] = Static_Stats_Tables.controllerInputs[0].processedInput;

    if (gameSetUpStep[0x55] != 0) {
        return;
    }

    if (input[1] & 0x100) {
        switch (lbl_2_bss_F410[0]) {
        case 0:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 0;
            ((u8 *)&g_d_GameSettings)[0x7] = 0;
            break;
        case 1:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 1;
            ((u8 *)&g_d_GameSettings)[0x7] = 5;
            break;
        case 3:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 3;
            ((u8 *)&g_d_GameSettings)[0x7] = 7;
            changeScene(4, 6);
            break;
        case 2:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 2;
            ((u8 *)&g_d_GameSettings)[0x7] = 6;
            changeScene(4, 6);
            break;
        case 4:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 4;
            ((u8 *)&g_d_GameSettings)[0x7] = 2;
            ((u8 *)&g_d_GameSettings)[0x9] = 0;
            ((u8 *)&g_d_GameSettings)[0xA] = 2;
            changeScene(4, 6);
            break;
        case 6:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 6;
            break;
        case 5:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 5;
            break;
        }

        *(u16 *)(menuControlVariables + 4) = 5;
        updateCharacterSelectProcessCode(0, 0x58);
        lbl_80366158[0x27] = 0;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        return;
    }

    if (input[1] & 0x200) {
        lbl_80366158[0x29] = 2;
        ((u8 *)&Static_Stats_Tables)[0x472A] = 0;
        *(u16 *)(menuControlVariables + 4) = 6;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        return;
    }

    if ((input[2] & 0x8) || (input[2] & 0x4)) {
        lbl_2_bss_F410[1] = lbl_2_bss_F410[0];

        if (input[2] & 0x8) {
            if (--lbl_2_bss_F410[0] < 0) {
                lbl_2_bss_F410[0] = 6;
            }
        } else if (input[2] & 0x4) {
            if (++lbl_2_bss_F410[0] == 7) {
                lbl_2_bss_F410[0] = 0;
            }
        }

        updateCharacterSelectProcessCode(0, 0x56);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// .text:0x00001800 size:0x288 mapped:0x80640894
void fn_2_1800(void) {
    u16 input[3];

    memset(input, 0, 6);
    input[0] = Static_Stats_Tables.controllerInputs[0].currentHeldInput;
    input[1] = Static_Stats_Tables.controllerInputs[0].newInput;
    input[2] = Static_Stats_Tables.controllerInputs[0].processedInput;

    if (gameSetUpStep[0x55] != 0) {
        return;
    }

    if (input[1] & 0x100) {
        switch (lbl_2_bss_F410[0]) {
        case 0:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 0;
            ((u8 *)&g_d_GameSettings)[0x7] = 0;
            break;
        case 1:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 1;
            ((u8 *)&g_d_GameSettings)[0x7] = 5;
            break;
        case 3:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 3;
            ((u8 *)&g_d_GameSettings)[0x7] = 7;
            changeScene(4, 6);
            break;
        case 2:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 2;
            ((u8 *)&g_d_GameSettings)[0x7] = 6;
            changeScene(4, 6);
            break;
        case 4:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 4;
            ((u8 *)&g_d_GameSettings)[0x7] = 2;
            ((u8 *)&g_d_GameSettings)[0x9] = 0;
            ((u8 *)&g_d_GameSettings)[0xA] = 2;
            changeScene(4, 6);
            break;
        case 6:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 6;
            break;
        case 5:
            Static_Stats_Tables.mainMenuOptionSelectedIndex = 5;
            break;
        }

        *(u16 *)(menuControlVariables + 4) = 5;
        updateCharacterSelectProcessCode(0, 0x58);
        lbl_80366158[0x27] = 0;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        return;
    }

    if (input[1] & 0x200) {
        lbl_80366158[0x29] = 2;
        ((u8 *)&Static_Stats_Tables)[0x472A] = 0;
        *(u16 *)(menuControlVariables + 4) = 6;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        return;
    }

    if ((input[2] & 0x8) || (input[2] & 0x4)) {
        lbl_2_bss_F410[1] = lbl_2_bss_F410[0];

        if (input[2] & 0x8) {
            if (--lbl_2_bss_F410[0] < 0) {
                lbl_2_bss_F410[0] = 6;
            }
        } else if (input[2] & 0x4) {
            if (++lbl_2_bss_F410[0] == 7) {
                lbl_2_bss_F410[0] = 0;
            }
        }

        updateCharacterSelectProcessCode(0, 0x56);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// .text:0x00001A88 size:0x124 mapped:0x80640B1C
void fn_2_1A88(void) {
    s8 *ports = (s8 *)&AtBat_ButtonInput1;
    u8 *tbl = (u8 *)&Static_Stats_Tables;
    int n;

    Static_Stats_Tables.playerNumberByPort[0] = 0;
    n = 1;

    if (ports[0x28] != -1) {
        Static_Stats_Tables.playerNumberByPort[1] = 1;
        n = 2;
    }
    if (ports[0x48] != -1) {
        Static_Stats_Tables.playerNumberByPort[n] = 2;
        n++;
    }
    if (ports[0x68] != -1) {
        Static_Stats_Tables.playerNumberByPort[n] = 3;
        n++;
    }

    while (n < 4) {
        ((s8 *)tbl)[n + 0x46F8] = -1;
        n++;
    }
}

// .text:0x00001BAC size:0x88 mapped:0x80640C40
void fn_2_1BAC(void) {
    memset(&gameSetUpStep[1], 0, 0x54);
    gameSetUpStep[0x56] = 0;
    gameSetUpStep[0x55] = 0;
    memset(&g_MatchInfo, 0, 0x3A);
    memset(Static_Stats_Tables.charIsStarred, 0, 0x12);
    memset(menuNumber, 0, 0x28);
}

// .text:0x00001C34 size:0xF4 mapped:0x80640CC8
void cursorSndFx(u16 button) {
    switch (button) {
    case 0x100:
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        break;
    case 0x200:
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        break;
    case 0x1:
    case 0x2:
    case 0x4:
    case 0x8:
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        break;
    case 0x20:
    case 0x40:
        break;
    case 0x400:
    case 0x800:
        break;
    }
}

// .text:0x00001D28 size:0x2C mapped:0x80640DBC
void fn_2_1D28(void) {
    ((u8 *)&Static_Stats_Tables)[0x472A] = 0xFF;
    ((u8 *)&Static_Stats_Tables)[0x4756] = 0;
    ((u8 *)&Static_Stats_Tables)[0x4754] = 0;
    ((u8 *)&Static_Stats_Tables)[0x4755] = 3;
    ((u8 *)&Static_Stats_Tables)[0x48B3] = 0;
}

// .text:0x00001D54 size:0x70 mapped:0x80640DE8
void fn_2_1D54(int *cursor, u8 port, int count) {
    u8 *base = (u8 *)&Static_Stats_Tables + 0x4730;
    u16 input = *(u16 *)(base + port * 6);

    if (input & 0x8) {
        *cursor = *cursor - 1;
        if (*cursor < 0) {
            *cursor = count - 1;
        }
    } else if (input & 0x4) {
        *cursor = *cursor + 1;
        if (*cursor == count) {
            *cursor = 0;
        }
    }
}

// .text:0x00001DC4 size:0x4 mapped:0x80640E58
void fn_2_1DC4(void) {
    return;
}

// .text:0x00001DC8 size:0x168 mapped:0x80640E5C
void fn_2_1DC8(void) {
    switch (lbl_2_bss_F410[0]) {
    case 0:
        Static_Stats_Tables.mainMenuOptionSelectedIndex = 0;
        ((u8 *)&g_d_GameSettings)[0x7] = 0;
        break;
    case 1:
        Static_Stats_Tables.mainMenuOptionSelectedIndex = 1;
        ((u8 *)&g_d_GameSettings)[0x7] = 5;
        break;
    case 3:
        Static_Stats_Tables.mainMenuOptionSelectedIndex = 3;
        ((u8 *)&g_d_GameSettings)[0x7] = 7;
        changeScene(4, 6);
        break;
    case 2:
        Static_Stats_Tables.mainMenuOptionSelectedIndex = 2;
        ((u8 *)&g_d_GameSettings)[0x7] = 6;
        changeScene(4, 6);
        break;
    case 4:
        Static_Stats_Tables.mainMenuOptionSelectedIndex = 4;
        ((u8 *)&g_d_GameSettings)[0x7] = 2;
        ((u8 *)&g_d_GameSettings)[0x9] = 0;
        ((u8 *)&g_d_GameSettings)[0xA] = 2;
        changeScene(4, 6);
        break;
    case 6:
        Static_Stats_Tables.mainMenuOptionSelectedIndex = 6;
        break;
    case 5:
        Static_Stats_Tables.mainMenuOptionSelectedIndex = 5;
        break;
    }

    *(u16 *)(menuControlVariables + 4) = 5;
    updateCharacterSelectProcessCode(0, 0x58);
}

// .text:0x00001F30 size:0x8B0 mapped:0x80640FC4
void mainMenuRelated(void) {
    s8 *ports;
    u8 *tbl;
    int n;
    u8 *p1;
    u8 *p2;
    u16 input[3];

    switch (*(u16 *)(menuControlVariables + 4)) {
    case 0:
        if (*(u16 *)(menuControlVariables + 6) < 5) {
            ports = (s8 *)&AtBat_ButtonInput1;
            tbl = (u8 *)&Static_Stats_Tables;

            Static_Stats_Tables.playerNumberByPort[0] = 0;
            n = 1;

            if (ports[0x28] != -1) {
                Static_Stats_Tables.playerNumberByPort[1] = 1;
                n = 2;
            }
            if (ports[0x48] != -1) {
                Static_Stats_Tables.playerNumberByPort[n] = 2;
                n++;
            }
            if (ports[0x68] != -1) {
                Static_Stats_Tables.playerNumberByPort[n] = 3;
                n++;
            }

            while (n < 4) {
                ((s8 *)tbl)[n + 0x46F8] = -1;
                n++;
            }
        }

        p1 = &gameSetUpStep[1];
        memset(p1, 0, 0x54);
        gameSetUpStep[0x56] = 0;
        gameSetUpStep[0x55] = 0;
        memset(&g_MatchInfo, 0, 0x3A);
        memset(Static_Stats_Tables.charIsStarred, 0, 0x12);
        memset(menuNumber, 0, 0x28);
        p2 = &((u8 *)&Static_Stats_Tables)[0x4712];
        memset(p2, 0, 2);
        lbl_2_bss_F410[0] = p2[0];
        lbl_2_bss_F410[1] = ((u8 *)&Static_Stats_Tables)[0x4713];
        ((u8 *)&g_d_GameSettings)[0x10] = 0;
        gameSetUpStep[0] = 0;
        memset(p1, 0, 6);
        ((u8 *)&Static_Stats_Tables)[0x472A] = 0xFF;
        fn_2_74D8C();
        updateCharacterSelectProcessCode(0, 0x54);
        *(u16 *)(menuControlVariables + 4) = *(u16 *)(menuControlVariables + 4) + 1;
        break;

    case 1:
        *(u16 *)(menuControlVariables + 4) = *(u16 *)(menuControlVariables + 4) + 1;
        break;

    case 2:
        memset(input, 0, 6);
        input[0] = Static_Stats_Tables.controllerInputs[0].currentHeldInput;
        input[1] = Static_Stats_Tables.controllerInputs[0].newInput;
        input[2] = Static_Stats_Tables.controllerInputs[0].processedInput;

        if (gameSetUpStep[0x55] != 0) {
            break;
        }

        if (input[1] & 0x100) {
            switch (lbl_2_bss_F410[0]) {
            case 0:
                Static_Stats_Tables.mainMenuOptionSelectedIndex = 0;
                ((u8 *)&g_d_GameSettings)[0x7] = 0;
                break;
            case 1:
                Static_Stats_Tables.mainMenuOptionSelectedIndex = 1;
                ((u8 *)&g_d_GameSettings)[0x7] = 5;
                break;
            case 3:
                Static_Stats_Tables.mainMenuOptionSelectedIndex = 3;
                ((u8 *)&g_d_GameSettings)[0x7] = 7;
                changeScene(4, 6);
                break;
            case 2:
                Static_Stats_Tables.mainMenuOptionSelectedIndex = 2;
                ((u8 *)&g_d_GameSettings)[0x7] = 6;
                changeScene(4, 6);
                break;
            case 4:
                Static_Stats_Tables.mainMenuOptionSelectedIndex = 4;
                ((u8 *)&g_d_GameSettings)[0x7] = 2;
                ((u8 *)&g_d_GameSettings)[0x9] = 0;
                ((u8 *)&g_d_GameSettings)[0xA] = 2;
                changeScene(4, 6);
                break;
            case 6:
                Static_Stats_Tables.mainMenuOptionSelectedIndex = 6;
                break;
            case 5:
                Static_Stats_Tables.mainMenuOptionSelectedIndex = 5;
                break;
            }

            *(u16 *)(menuControlVariables + 4) = 5;
            updateCharacterSelectProcessCode(0, 0x58);
            lbl_80366158[0x27] = 0;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            break;
        }

        if (input[1] & 0x200) {
            lbl_80366158[0x29] = 2;
            ((u8 *)&Static_Stats_Tables)[0x472A] = 0;
            *(u16 *)(menuControlVariables + 4) = 6;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            break;
        }

        if ((input[2] & 0x8) || (input[2] & 0x4)) {
            lbl_2_bss_F410[1] = lbl_2_bss_F410[0];

            if (input[2] & 0x8) {
                if (--lbl_2_bss_F410[0] < 0) {
                    lbl_2_bss_F410[0] = 6;
                }
            } else if (input[2] & 0x4) {
                if (++lbl_2_bss_F410[0] == 7) {
                    lbl_2_bss_F410[0] = 0;
                }
            }

            updateCharacterSelectProcessCode(0, 0x56);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        break;

    case 5:
        if (gameSetUpStep[0x55] != 0) {
            break;
        }
        ((u8 *)&Static_Stats_Tables)[0x4712] = lbl_2_bss_F410[0];
        ((u8 *)&Static_Stats_Tables)[0x4713] = lbl_2_bss_F410[1];

        switch (Static_Stats_Tables.mainMenuOptionSelectedIndex) {
        case 0:
            fn_80021AC8();
            relatedToTeamSelection4();
            changeScene(3, 6);
            *(u16 *)(menuControlVariables + 4) = 3;
            break;
        case 2:
        case 3:
        case 4:
            *(u16 *)(menuControlVariables + 4) = 4;
            break;
        case 6:
            ((u8 *)&Static_Stats_Tables)[0x48AF] = 1;
            ((u8 *)&Static_Stats_Tables)[0x48B1] = 1;
            changeScene(3, 6);
            *(u16 *)(menuControlVariables + 4) = 8;
            break;
        case 5:
            ((u8 *)&Static_Stats_Tables)[0x48AF] = 1;
            ((u8 *)&Static_Stats_Tables)[0x48B1] = 1;
            changeScene(3, 6);
            *(u16 *)(menuControlVariables + 4) = 0xA;
            break;
        case 1:
            ((u8 *)&Static_Stats_Tables)[0x4756] = 0;
            ((u8 *)&Static_Stats_Tables)[0x48AF] = 1;
            ((u8 *)&Static_Stats_Tables)[0x48B1] = 1;
            changeScene(3, 6);
            *(u16 *)(menuControlVariables + 4) = 3;
            break;
        }

        ((u8 *)&Static_Stats_Tables)[0x472A] = 0;
        break;

    case 6:
        lbl_803CBCD0[0x10] = 0;
        ((u8 *)&Static_Stats_Tables)[0x48B4] = 0;
        fn_80062A74();
        fn_80035B50(0xF);
        fn_80035B50(0x12);
        fn_80035B50(9);
        fn_80035B50(6);
        fn_800AD054(*(int *)&((u8 *)&Static_Stats_Tables)[0x46F0], *(int *)&((u8 *)&Static_Stats_Tables)[0x46F4]);
        changeScreenVariables(1);
        lbl_2_bss_20[0] = 0;
        break;

    case 7:
        ((u8 *)&Static_Stats_Tables)[0x472A] = 0;
        changeScreenVariables(1);
        lbl_803CBCD0[0x10] = 0;
        ((u8 *)&Static_Stats_Tables)[0x48B4] = 0;
        break;

    case 3:
        ((u8 *)&Static_Stats_Tables)[0x4728] = ((u8 *)&g_d_GameSettings)[0x7];
        ((u8 *)&Static_Stats_Tables)[0x4729] = ((u8 *)&g_d_GameSettings)[0x10];
        ((u8 *)&g_d_GameSettings)[0x8] = 1;

        if (((u8 *)&g_d_GameSettings)[0x7] == 0) {
            changeScreenVariables(9);
        } else if (((u8 *)&g_d_GameSettings)[0x7] == 5) {
            if (lbl_803C50E8[0x47] != 0) {
                ((u8 *)&g_d_GameSettings)[0x10] = 0;
                changeScreenVariables(0xC);
            } else {
                changeScreenVariables(0xF);
            }
        } else {
            fn_80062A74();
            fn_80035B50(0xF);
            fn_80035B50(0x12);
            fn_80035B50(9);
            fn_80035B50(6);
            fn_800AD054(*(int *)&((u8 *)&Static_Stats_Tables)[0x46F0], *(int *)&((u8 *)&Static_Stats_Tables)[0x46F4]);
            maybeLoadsGameSoundFiles();
            fn_800ACFB0(*(void **)&lbl_800EF808[0x98]);
            changeScreenVariables(4);
        }

        lbl_2_bss_20[0] = 0;
        break;

    case 4:
        ((u8 *)&Static_Stats_Tables)[0x48AF] = 1;
        ((u8 *)&Static_Stats_Tables)[0x48B1] = 1;
        *(u16 *)(menuControlVariables + 4) = 3;
        break;

    case 8:
        changeScreenVariables(6);
        lbl_2_bss_20[0] = 0;
        break;

    case 9:
        fn_80062A74();
        fn_80035B50(0xF);
        fn_80035B50(0x12);
        fn_80035B50(9);
        fn_80035B50(6);
        fn_800AD054(*(int *)&((u8 *)&Static_Stats_Tables)[0x46F0], *(int *)&((u8 *)&Static_Stats_Tables)[0x46F4]);
        maybeLoadsGameSoundFiles();
        fn_800ACFB0(*(void **)&lbl_800EF808[0x98]);
        changeScreenVariables(7);
        lbl_2_bss_20[0] = 0;
        break;

    case 10:
        fn_80035B50(0xF);
        fn_80035B50(0x12);
        fn_80035B50(9);
        fn_80035B50(6);
        fn_800AD054(*(int *)&((u8 *)&Static_Stats_Tables)[0x46F0], *(int *)&((u8 *)&Static_Stats_Tables)[0x46F4]);
        changeScreenVariables(8);
        lbl_2_bss_20[0] = 0;
        break;
    }
}

// .text:0x000027E0 size:0x3D8 mapped:0x80641874
void mainMenuScreen(void) {
    u8 state;
    s16 k;
    u8 *tbl = lbl_2_data_180;

    state = lbl_2_bss_20[0];

    switch (state) {
    case 0:
        settingValuesTo0();

        switch (*(u16 *)(menuControlVariables + 6)) {
        case 8:
            lbl_2_bss_20[0] = 3;
            return;
        case 6:
        case 9:
        case 12:
            lbl_2_bss_20[0] = 0xC;
            return;
        case 15:
            if (((u8 *)&Static_Stats_Tables)[0x4756] == 0) {
                lbl_2_bss_20[0] = 0xC;
                return;
            }
            break;
        }

        initializeUnknown();
        ((u8 *)&Static_Stats_Tables)[0x4700] = 0;
        ((u8 *)&Static_Stats_Tables)[0x472A] = 0xFF;
        ((u8 *)&Static_Stats_Tables)[0x4756] = 0;
        ((u8 *)&Static_Stats_Tables)[0x4754] = 0;
        ((u8 *)&Static_Stats_Tables)[0x4755] = 3;
        ((u8 *)&Static_Stats_Tables)[0x48B3] = 0;
        ((u8 *)&Static_Stats_Tables)[0x4701] = 0;
        ((u8 *)&Static_Stats_Tables)[0x4702] = 0;
        ((u8 *)&Static_Stats_Tables)[0x4703] = 0;
        ((u8 *)&Static_Stats_Tables)[0x4704] = 0;
        ((u8 *)&Static_Stats_Tables)[0x4705] = 0;
        ((u8 *)&Static_Stats_Tables)[0x4706] = 0;
        ((u8 *)&Static_Stats_Tables)[0x4707] = 0;
        ((u8 *)&Static_Stats_Tables)[0x4700] = 1;

        if (*(u16 *)(menuControlVariables + 6) != 1) {
            fn_80062764(currentDrawingItem);
        }

        lbl_2_bss_20[0]++;
        break;

    case 1:
        lbl_2_bss_20[0] = state + 1;
        /* fallthrough */
    case 2:
        if (fn_80022B68() != 0) {
            lbl_2_bss_20[0]++;
        }
        break;

    case 3:
        fn_2_12988();
        lbl_2_bss_20[0]++;
        break;

    case 4:
        if (fn_800697B0() == 0) {
            lbl_2_bss_20[0]++;
        }
        break;

    case 5:
        if (diskReadRelated(&tbl[0x2C4], 6) != 0) {
            lbl_2_bss_20[0]++;
        }
        break;

    case 6:
        if (diskReadRelated(&tbl[0x2D4], 9) != 0) {
            lbl_2_bss_20[0]++;
        }
        break;

    case 7:
        if (diskReadRelated(&tbl[0x2E4], 0x12) != 0) {
            lbl_2_bss_20[0]++;
        }
        break;

    case 8:
        if (diskReadRelated(&tbl[0x2F4], 0xF) != 0) {
            if (*(u16 *)(menuControlVariables + 6) == 1) {
                lbl_2_bss_20[0] = 0xB;
            } else {
                lbl_2_bss_20[0]++;
            }
        }
        break;

    case 9:
        if (((u8 *)&Static_Stats_Tables)[0x48B4] != 0) {
            if (lbl_803CBCD0[0x10] == 0) {
                fn_8003F23C();
            }
            lbl_2_bss_20[0]++;
        } else {
            lbl_2_bss_20[0] = 0xB;
        }
        break;

    case 10:
        if (lbl_803CBCD0[0x10] == 0) {
            k = *(s16 *)(currentDrawingItem + 0x10);
            if (k == 1 || k == 0xB) {
                lbl_803CBCD0[0x10] = 1;
                superstarUnlocked[0xDE] = 1;
                superstarUnlocked[0xDF] = 1;
                superstarUnlocked[0xE0] = 1;
                superstarUnlocked[0xE1] = 1;
                superstarUnlocked[0xE2] = 1;
                superstarUnlocked[0xE3] = 1;
                lbl_2_bss_20[0]++;
            }
        } else {
            lbl_2_bss_20[0] = state + 1;
        }
        break;

    case 11:
        if (*(u16 *)(menuControlVariables + 6) != 6 && lbl_803C6714[4] == 0) {
            insertGraphicDrawingFunction(relatedToReturningToPracticeMenu, 0x1000);
        }
        *(u16 *)(menuControlVariables + 4) = 0;
        lbl_2_bss_20[0]++;
        break;

    case 12:
        mainMenuRelated();
        break;
    }
}

// .text:0x00002BB8 size:0x164 mapped:0x80641C4C
void fn_2_2BB8(void) {
    int t;
    int i;
    int slot;
    s16 v;
    s16 *ep;
    u8 *cp;
    u8 *lp;
    int *slotp;

    for (t = 0; t < 2; t++) {
        ep = lbl_2_data_E88;
        cp = &((u8 *)&cursorPositions)[t * 9];
        lp = &lineUpInfoStruct[t * 0x24];
        slotp = (int *)&((u8 *)&Static_Stats_Tables)[0x46E0 + t * 4];

        for (i = 0; i < 9; i++) {
            slot = *slotp;

            if (slot == 0) {
                v = ep[0];
                cp[2] = v;
                cp[0x26] =
                    ((u8 *)&Static_Stats_Tables)[slot + (v / 9) * 0x5A0 + (v % 9) * 0xA0 + 0x3B];
            } else {
                v = ep[9];
                cp[2] = v;
                cp[0x26] =
                    ((u8 *)&Static_Stats_Tables)[slot + (v / 9) * 0x5A0 + (v % 9) * 0xA0 + 0x3B];
            }

            lp[0] = lp[1] = lp[2] = i;

            ep++;
            cp++;
            lp += 4;
        }

        fn_800670A0(t);
    }
}

// .text:0x00002D1C size:0x2A4 mapped:0x80641DB0
void fn_2_2D1C(void) {
    int t;
    int i;
    int slot;
    s16 v;
    int *slotp;
    s16 *ep;
    u8 *cp;
    u8 *lp;

    *(int *)&((u8 *)&Static_Stats_Tables)[0x46E0] = 10;
    *(int *)&((u8 *)&Static_Stats_Tables)[0x46E4] = 2;

    for (t = 0; t < 2; t++) {
        slotp = (int *)&((u8 *)&Static_Stats_Tables)[0x46E0 + t * 4];
        ep = &lbl_2_data_E64[t * 9];
        cp = &((u8 *)&cursorPositions)[t * 9];

        for (i = 0; i < 9; i++) {
            slot = *slotp;
            v = ep[i];
            cp[i + 2] = v;
            cp[i + 0x26] =
                ((u8 *)&Static_Stats_Tables)[slot + (v / 9) * 0x5A0 + (v % 9) * 0xA0 + 0x3B];
        }
    }

    lp = lineUpInfoStruct;

    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            lp[i * 4 + 0] = lp[i * 4 + 1] = lp[i * 4 + 2] = i;
        }
        lp += 0x24;
    }
}

// .text:0x00002FC0 size:0x244 mapped:0x80642054
void loadDemoMatch(u8 mode, int a, int b) {
    int v;
    u8 want;
    int j;
    int i;
    u8 *flags;

    switch (mode) {
    case 9:
        fn_800684A4();
        if (b == 0) {
            break;
        }
        /* fallthrough */
    case 0xA:
        flags = &((u8 *)&Static_Stats_Tables)[0x4757];
        memset(flags, 0, 0x36);
        flags[*(int *)&((u8 *)&Static_Stats_Tables)[0x46E0]] = 1;
        flags[*(int *)&((u8 *)&Static_Stats_Tables)[0x46E4]] = 1;

        for (i = 0; i < 6; i++) {
            v = (((u8 *)&g_d_GameSettings)[0x1A + i] == 0);
            want = unlockableCharacter_noDupeNoGapCharID[i];

            for (j = 0; j < 54; j++) {
                if (want == characterStaticIndexes[j * 6 + 2]) {
                    ((u8 *)&Static_Stats_Tables)[j + 0x4757] = v;
                }
            }

            unlockableCharacter_noDupeNoGapCharID[i] = want;
        }

        DraftRandomTeamDemo(0);
        DraftRandomTeamDemo(1);
        copyInfoToInMemRoster();
        teamLogoDetermination(0);
        teamLogoDetermination(1);
        unsure_FillRosterPositions(0);
        unsure_FillRosterPositions(1);
        characterSelectScreen(0);
        characterSelectScreen(1);
        setCaptainLocInRoster();

        if (b == 0) {
            break;
        }
        /* fallthrough */
    case 0xC:
        selectRandomStadium();
        if (a != 0) {
            fn_800649BC();
        }
        break;
    case 0xB:
        break;
    }
}

// .text:0x00003204 size:0x38 mapped:0x80642298
void fn_2_3204(void) {
    loadDemoMatch(((u8 *)&aiPosSwapInputs)[0xCF5F], 1, 1);
}

