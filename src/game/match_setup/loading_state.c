#define SQRT2_LINKAGE static
#include "game/match_setup/loading_state.h"
#define REP_HEADER_DATA_FN getRepHeaderData_loadingState
#include "header_rep_data.h"
#include "Dolphin/os.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8001cbd4.h"
#include "game/hud/stadium_draw.h"
#include "game/match_setup/match_loading.h"
#include "game/minigame/minigame_framework.h"
#include "game/camera/camera_script.h"
#include "game/stadium/stadium_framework.h"
#include "static/UnknownHomes_Static.h"

extern struct {
    u8 _000[0x4];
    void* stadiumFile;
    u8 _008[0x3154 - 0x8];
} hugeAnimStruct;

extern struct {
    u8 _000[0x1CC];
    void* _1CC;
    u8 _1D0[0x578 - 0x1D0];
} lbl_803716B8;

extern MatchFileDescriptor StadiumFiles[];
extern u8 lbl_3_common_bss_35154[0x480];
extern u8 FrameCountOfEntireGame[0x14];
extern void fn_800229CC(void);

void manageLoadingState(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    switch (node->state) {
    case 0: {
        void* file;
        if (lbl_803716B8._1CC != NULL) {
            if (lbl_803C6CF8.cancel.bytes[1] != TRUE) {
                break;
            }
            file = ARAMTransfer(
                &StadiumFiles[g_d_GameSettings.StadiumID * 3 + g_d_GameSettings.miniGameStadiumIndicator],
                0, 3, (s32)lbl_803716B8._1CC);
            *(void**)&node->unk_14 = file;
            hugeAnimStruct.stadiumFile = file;
            OSReport("Sta %d-%d aram:%x -> mem:%x\n", g_d_GameSettings.StadiumID,
                     g_d_GameSettings.miniGameStadiumIndicator, lbl_803716B8._1CC, *(void**)&node->unk_14);
        } else {
            file = ARAMTransfer(
                &StadiumFiles[g_d_GameSettings.StadiumID * 3 + g_d_GameSettings.miniGameStadiumIndicator],
                0, 0, 0);
            *(void**)&node->unk_14 = file;
            hugeAnimStruct.stadiumFile = file;
        }
        node->state = 1;
        break;
    }
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == TRUE) {
            updateStadiumFileHeaders(*(void**)&node->unk_14);
            node->state = 2;
            fn_800229CC();
        }
        break;
    case 2:
        switch (loadStadiumObjects(g_d_GameSettings.StadiumID)) {
        case 1:
            node->state = 3;
            break;
        case -1:
            node->state = 4;
            break;
        }
        break;
    case 3:
        if (stadiumObjectCollision.objectsLoaded == 0) {
            node->state = 4;
        }
        break;
    case 4:
        if (maybeLoadHUDObjectFromMemory()) {
            node->state = 5;
        }
        break;
    case 5:
        if (lbl_3_common_bss_35154[0x3B0] == 0) {
            node->state = 6;
        }
        break;
    case 6:
        fn_3_BD7D8();
        node->state = 7;
        break;
    case 7:
        if (loadSomeDataFile()) {
            node->state = 8;
        }
        break;
    case 8:
        if (lbl_803C6CF8.cancel.bytes[1] == TRUE) {
            someAllocFunction();
            node->state = 9;
        }
        break;
    default:
        node->currentDrawingItem->state = 1;
        FrameCountOfEntireGame[0x10] = 1;
        removeCurrentDrawingItem();
        break;
    }
}

void manageStadiumLoading(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    switch (node->state) {
    case 0:
        initStadiumLighting();
        hugeAnimStruct.stadiumFile = ARAMTransfer(
            &StadiumFiles[g_d_GameSettings.StadiumID * 3 + g_d_GameSettings.miniGameStadiumIndicator],
            0, 0, 0);
        node->state++;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == TRUE) {
            updateStadiumFileHeaders(hugeAnimStruct.stadiumFile);
            node->state++;
        }
        break;
    case 2:
        switch (loadStadiumObjects(g_d_GameSettings.StadiumID)) {
        case 1:
            node->state = 3;
            break;
        case -1:
            node->state = 4;
            break;
        }
        break;
    case 3:
        if (stadiumObjectCollision.objectsLoaded == 0) {
            node->state++;
        }
        break;
    default:
        node->currentDrawingItem->state = 1;
        FrameCountOfEntireGame[0x10] = 1;
        removeCurrentDrawingItem();
        break;
    }
}
