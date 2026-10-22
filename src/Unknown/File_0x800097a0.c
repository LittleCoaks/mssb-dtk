#include "Unknown/File_0x800097a0.h"

#include "Dolphin/OS/OSCache.h"
#include "Dolphin/OS/OSModule.h"
#include "Dolphin/os.h"
#include "Dolphin/vi.h"
#include "musyx/musyx.h"
#include "static/UnknownHomes_Static.h"
#include "text/text.h"
#include "text/text_init.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80021308.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x80035838.h"
#include "Unknown/File_0x800bde8c.h"
#include "Unknown/dvdsys.h"

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 flags;
    /* 0x10 */ u8 _10[0x1C - 0x10];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 _1E[0x25 - 0x1E];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 _27[0x29 - 0x27];
    /* 0x29 */ u8 unk29;
} LoaderScratch;

extern LoaderScratch lbl_80366158;
extern u8 relFileTable[0x440];
extern s32 s32DataId;
extern s32 s32ProgId;

// The loader node's view of the DrawingSceneStruct it runs on.
typedef struct {
    /* 0x00 */ u8 _00[0x10];
    /* 0x10 */ s16 loaderFinished;
    /* 0x12 */ u8 _12[0x14 - 0x12];
    /* 0x14 */ OSModuleHeader* module;
    /* 0x18 */ u16 loaderState;
    /* 0x1A */ u8 _1A[0x1C - 0x1A];
    /* 0x1C */ u32 moduleSize;
} LoaderNode;

void fn_80009144(void);
void fn_80011000(void);
void fn_800111B4(void* arg0);
void fn_80021064(void);
void fn_8002158C(void);
void fn_800216F8(s32 arg0, void (*arg1)(void));
void fn_80022D58(void);
void fn_800227E4(void);
void fn_80023CF4(u32 arg0);
void fn_80023D44(s32 arg0);
s32 fn_800A8518(s32 arg0);
void fn_800A88C0(void);
void fn_800A8B78(void);

#define SCREEN_TEXT_SLOT(off) (*(void**)((u8*)&screenTextArray + (off)))
#define AT_BAT_BUTTON(off) (*(u16*)((u8*)&AtBat_ButtonInput1 + (off)))
#define RELFILE_U32(off) (*(u32*)(relFileTable + (off)))

void handleLoadingProcess(void) {
    LoaderNode* node;
    OSModuleHeader* module;
    u32 flags;
    BOOL skipPrompt;

    lbl_80366158.unk26 = 0;
    lbl_80366158.unk25 = 0;
    node = (LoaderNode*)currentDrawingItem;

    switch (node->loaderState) {
    case 0:
        g_d_GameSettings.highLevelMenuScene = HIGH_LEVEL_MENU_SCENE_NONE;
        fn_800AD054((int)lbl_80366158.unk00, (int)lbl_80366158.unk04);
        soundOrMusicRelated();
        lbl_803C6CF8.entryNum = s32DataId;
        SCREEN_TEXT_SLOT(0x780) = ARAMTransfer(relFileTable + 0x30, 0, 0, 0);
        node->loaderState = 1;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            break;
        }
        SCREEN_TEXT_SLOT(0x794) = ARAMTransfer(relFileTable + 0x50, 0, 1, 0);
        node->loaderState = 2;
        break;
    case 2:
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            break;
        }
        fn_80011000();
        screenTextArray.textBanks[0] = ARAMTransfer(relFileTable + 0x40, 0, 1, 0);
        node->loaderState = 3;
        break;
    case 3:
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            break;
        }
        fn_800111B4(screenTextArray.textBanks[0]);
        initTextRendering();
        node->loaderState = 4;
        break;
    case 4:
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            break;
        }
        node->loaderState = 5;
        break;
    case 5:
        if (diskReadRelated(relFileTable + 0x2B0, 0) == 0) {
            break;
        }
        setDrawingListHeadFunctions(fn_80021064);
        node->loaderState = 6;
        break;
    case 6:
        if (diskReadRelated(relFileTable + 0x150, 1) == 0) {
            break;
        }
        fn_800216F8(0, fn_8002158C);
        node->loaderFinished = 0;
        node->loaderState = 7;
        break;
    case 7:
        if (node->loaderFinished == 0) {
            break;
        }
        lbl_80366158.unk00 = (u32)memoryUsedOrStorage.lo;
        flags = lbl_80366158.flags;
        if ((flags & 1) != 0 && (flags & 0x80000000) != 0) {
            fn_80023CF4((flags >> 1) & 1);
            skipPrompt = FALSE;
        } else if (VIGetDTVStatus() == 0) {
            fn_80023D44(0);
            skipPrompt = FALSE;
        } else {
            skipPrompt = FALSE;
            if (OSGetProgressiveMode() == 1 ||
                ((AT_BAT_BUTTON(0x00) | AT_BAT_BUTTON(0x20) | AT_BAT_BUTTON(0x40) | AT_BAT_BUTTON(0x60)) & 0x200)) {
                skipPrompt = TRUE;
            }
        }
        if (skipPrompt) {
            lbl_80366158.unk1D = 0;
        } else {
            lbl_80366158.unk1D = 9;
        }
        flags = lbl_80366158.flags;
        if ((flags & 1) != 0 && (flags & 0x80000000) != 0) {
            lbl_80366158.unk29 = 1;
        } else {
            lbl_80366158.unk29 = 0;
        }
        fn_800AD01C((void*)lbl_80366158.unk04);
        fn_80022D58();
        fn_800227E4();
        fn_80009144();
        /* fall through */
    case 8:
        g_d_GameSettings.highLevelMenuScene = HIGH_LEVEL_MENU_SCENE_MENUS;
        fn_800AD038((void*)lbl_80366158.unk00);
        lbl_803C6CF8.entryNum = s32ProgId;
        node->module = (OSModuleHeader*)ARAMTransfer(relFileTable, 0, 0, 0);
        node->moduleSize = RELFILE_U32(0x4) & 0x0FFFFFFF;
        OSReport("Load dll. (%d) at %x\n", 0, node->module);
        node->loaderState = 9;
        break;
    case 9:
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            break;
        }
        module = node->module;
        lbl_803C6CF8.entryNum = s32DataId;
        OSLink((OSModuleInfo*)module, _OSAllocFromHeap(0x20, module->bssSize));
        ICInvalidateRange(node->module, node->moduleSize);
        lbl_80366158.unk08 = (u32)memoryUsedOrStorage.lo;
        ((void (*)(void))module->prolog)();
        node->loaderFinished = 0;
        OSReport("Call first function of the current dll.\n");
        node->loaderState = 10;
        break;
    case 10:
        if (node->loaderFinished == 0) {
            break;
        }
        maybeLoadsGameSoundFiles();
        resetAllDrawingStructs();
        fn_80009144();
        module = node->module;
        ((void (*)(void))module->epilog)();
        OSUnlink((OSModuleInfo*)module);
        if (node->loaderFinished != 1) {
            break;
        }
        node->loaderState = 11;
        break;
    case 11:
        g_d_GameSettings.highLevelMenuScene = HIGH_LEVEL_MENU_SCENE_IN_GAME;
        fn_800AD038((void*)lbl_80366158.unk00);
        lbl_803C6CF8.entryNum = s32ProgId;
        node->module = (OSModuleHeader*)ARAMTransfer(relFileTable + 0x10, 0, 0, 0);
        node->moduleSize = RELFILE_U32(0x14) & 0x0FFFFFFF;
        OSReport("Load dll. (%d) at %x\n", 1, node->module);
        node->loaderState = 12;
        lbl_80366158.unk1C = 0;
        break;
    case 12:
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            break;
        }
        module = node->module;
        lbl_803C6CF8.entryNum = s32DataId;
        OSLink((OSModuleInfo*)module, _OSAllocFromHeap(0x20, module->bssSize));
        ICInvalidateRange(node->module, node->moduleSize);
        lbl_80366158.unk08 = (u32)memoryUsedOrStorage.lo;
        ((void (*)(void))module->prolog)();
        node->loaderFinished = 0;
        OSReport("Call first function of the current dll.\n");
        node->loaderState = 13;
        break;
    case 13:
        if (lbl_80366158.unk1C != 0) {
            DrawShadows(0);
            sndSilence();
        }
        node->loaderState = 14;
        /* fall through */
    case 14:
        if (lbl_80366158.unk1C == 0) {
            break;
        }
        if (fn_800A8518(3) == 0) {
            break;
        }
        fn_800A88C0();
        fn_800A8B78();
        maybeLoadsGameSoundFiles();
        resetAllDrawingStructs();
        fn_80009144();
        module = node->module;
        ((void (*)(void))module->epilog)();
        OSUnlink((OSModuleInfo*)module);
        node->loaderState = 8;
        g_d_GameSettings.miniGameStadiumIndicator = 0;
        if (g_d_GameSettings.GameModeSelected == 4) {
            lbl_80366158.unk1D = 7;
            lbl_80366158.unk29 = 2;
        } else if (g_d_GameSettings.exhibitionMatchInd == 0) {
            if (g_d_GameSettings.GameModeSelected == 5 && g_d_GameSettings.bJMatchInd == 0) {
                lbl_80366158.unk1D = 1;
            } else {
                g_d_GameSettings.GameModeSelected = 5;
            }
        } else {
            if ((u8)(g_d_GameSettings.GameModeSelected - 6) <= 1 || g_d_GameSettings.GameModeSelected == 2) {
                lbl_80366158.unk1D = 1;
            } else if (lbl_80366158.unk1C == 1) {
                lbl_80366158.unk1D = 1;
            } else {
                lbl_80366158.unk1D = 1;
            }
        }
        break;
    }
}
