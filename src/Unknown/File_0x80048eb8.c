#include "Unknown/File_0x80048eb8.h"
#include "Unknown/File_0x8004a2bc.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/File_0x80062a50.h"
#include "Unknown/File_0x80035ca4.h"
#include "Unknown/File_0x8004207c.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/orderchange.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/os.h"

typedef struct MenuLabel {
    /* 0x0 */ u8 _0[8];
    /* 0x8 */ u16 label;
    /* 0xA */ u8 _A[6];
} MenuLabel;

extern u8 menuNumber[0x28];
extern MenuLabel lbl_800FEF70[];
extern u8 lbl_803C5EE0[0x18];
extern u8 gameSetUpStep[];
extern char lbl_800E6950[];

void startGameRelated(void) {
    u8 *gs = (u8 *)&gameSettings;
    s32 i;
    s32 step = gs[0x35];
    if (step != 1) {
        if (step >= 2) {
            return;
        }
        ((u8 *)lbl_803C5EE0)[0x15] = 1;
        ((u8 *)&Static_Stats_Tables)[0x48AF] = 1;
        menuNumber[0x26] = 1;
        fn_80062A74();
        maybeLoadsGameSoundFiles();
        gs[0x35]++;
        return;
    }

    if (gameSetUpStep[0x55] != 0 || gameSetUpStep[0x56] != 0) {
        if (gameSetUpStep[0x5D] == 0x31 && gameSetUpStep[0x5E] != 0) {
            makeCursorMovable(1);
        }
        return;
    }

    for (i = 0; i < 2; i++) {
        u8 b = ((u8 *)&g_d_GameSettings)[0x50 + i];
        u8 *src = gs + 4 * i;
        u8 *dst = (b < 4) ? ((u8 *)&inningSetting) + 7 * b : ((u8 *)&inningSetting) + 7 * i;

        dst[0xD] = src[0x45];
        dst[0xA] = src[0x46];
        dst[0x9] = src[0x47];
        dst[0xB] = src[0x48];
    }

    ((u8 *)&inningSetting)[0x00] = (u8)(((s8)gs[0x3E]) * 2 + 1);
    ((u8 *)&g_d_GameSettings)[0x0E] = gs[0x3C];
    ((u8 *)&inningSetting)[0x04] = gs[0x3D];
    ((u8 *)&inningSetting)[0x05] = (gs[0x3F] != 0) ? 10 : 0;

    ((u8 *)&inningSetting)[0x06] = 0;
    if (gs[0x34] == 1) {
        if (((u8 *)&g_d_GameSettings)[0x07] != 5) {
            unregisterObjectByID(0xF);
            unregisterObjectByID(0x12);
            unregisterObjectByID(0x9);
            unregisterObjectByID(0x6);
            ((u8 *)&g_MatchInfo)[0xF] = 0;
            OSReport(lbl_800E6950);
            fn_80042D38(4);
        } else {
            transferStatsToInMemRoster(0);
            capApplicationFunction();
            unregisterObjectByID(0xF);
            unregisterObjectByID(0x9);
            unregisterObjectByID(0x6);
            maybeLoadsGameSoundFiles();
            g_TeamManagement.unkCF40 = 0;
            ((u8 *)&g_MatchInfo)[0xF] = 0;
            changeScene(0xF, 6);
            ((u8 *)&g_MatchInfo)[0x11] = 0;
            ((u8 *)&Static_Stats_Tables)[0x48AF] = 1;
            menuNumber[0x26] = 1;
            fn_80042D38(4);
        }
    } else {
        if (((u8 *)&g_d_GameSettings)[0x07] != 5) {
            ((u8 *)&g_MatchInfo)[0x36] = 1;
            ((u8 *)&g_MatchInfo)[0x37] = ((u8 *)&g_MatchInfo)[0x38];
            ((u8 *)&g_MatchInfo)[0x38] = 2;
            menuNumber[0x00] = 5;
            menuNumber[0x09] = menuNumber[0x08];
            menuNumber[0x08] = (u8)lbl_800FEF70[5].label;
            fn_80042D38(0xC);
        } else {
            gs[0x32] = 0;
            ((u8 *)lbl_803C5EE0)[0x15] = 1;
            fn_80042D38(0xB);
        }
    }

    gs[0x35] = 0;
    gameSettings.step = 0;
    removeCurrentDrawingItem();
}
