#include "menus/text_01254.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"
#include "musyx/musyx.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80035838.h"
#include "Unknown/File_0x800625a4.h"
#include "Unknown/File_0x80067f70.h"
#include "Unknown/File_0x800acf14.h"

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
void fn_8003F23C(void);
void relatedToReturningToPracticeMenu(void);
void *insertGraphicDrawingFunction(void (*func)(void), u32 priority);

void fn_2_74D8C(void);
void fn_80021AC8(void);
void relatedToTeamSelection4(void);
void fn_80062A74(void);
void fn_80035B50(int arg0);
void maybeLoadsGameSoundFiles(void);
void changeScreenVariables(u16 screen);

void fn_800670A0(u8 arg0);

extern u8 unlockableCharacter_noDupeNoGapCharID[0x8];
extern u8 characterStaticIndexes[0x144];

void fn_800684A4(void);
void fn_800649BC(void);
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
