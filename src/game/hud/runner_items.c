#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_runnerItems
#include "header_rep_data.h"
#include "game/hud/runner_items.h"
#include "game/animation/animation_init.h"
#include "game/camera/camera.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b0a14.h"

/* The drawing-script node in currentDrawingItem, with the fields this file uses. */
typedef struct RunnerDrawingNode {
    /*0x00*/ u8 _00[0x0C];
    /*0x0C*/ struct RunnerDrawingNode *currentDrawingItem;
    /*0x10*/ s16 _10;
    /*0x12*/ u8 _12[0x18 - 0x12];
    /*0x18*/ s16 _18;
    /*0x1A*/ u8 _1A[0x22 - 0x1A];
    /*0x22*/ s16 _22;
} RunnerDrawingNode;

extern AnimScreenState *lbl_3_common_bss_1323C;
extern AnimActorView hugeAnimStruct;

// .text:0x00021C7C size:0x14
void fn_3_21C7C(int slot, int value) {
    lbl_3_common_bss_1323C->_261[slot] = value;
}

// .text:0x00021BDC size:0xA0
void fn_3_21BDC(void) {
    RunnerDrawingNode *node = (RunnerDrawingNode *)currentDrawingItem;

    switch (node->_22) {
    case 0:
        node->_22 = 1;
        node->_18 = 0x5A;
        break;
    case 1:
        if (node->_18-- == 0) {
            node->_22 = 2;
        }
        break;
    case 2:
        node->currentDrawingItem->_10 = 1;
        removeCurrentDrawingItem();
        node->_22 = 0;
        break;
    }
}

// .text:0x00021AA8 size:0x134
void fn_3_21AA8(void) {
    RunnerDrawingNode *node = (RunnerDrawingNode *)currentDrawingItem;
    AnimObject *obj = hugeAnimStruct.objects[9];
    InMemRunnerType *runner = &g_Runners[0];

    switch (node->_22) {
    case 0:
        if (runner->charID == CHAR_ID_DK || runner->charID == CHAR_ID_BOWSER) {
            node->_22 = 1;
        } else {
            node->_22 = 3;
        }
        break;
    case 1:
        if (node->_18-- == 0) {
            node->_22 = 2;
        }
        break;
    case 2:
        if ((obj->_279 & 2) || (obj->_279 & 1)) {
            fn_3_14E50();
        }
        if (lbl_3_common_bss_1323C->_27E == 0) {
            node->_22 = 3;
        }
        break;
    case 3:
        fn_3_14E1C();
        lbl_3_common_bss_1323C->_27E = 0;
        ((RunnerDrawingNode *)currentDrawingItem)->currentDrawingItem->_10 = 1;
        removeCurrentDrawingItem();
        node->_22 = 0;
        break;
    }
}

// .text:0x000219CC size:0xDC
void fn_3_219CC(void) {
    int count = 0;
    int i;

    for (i = 0; i < 9; i++) {
        if (hugeAnimStruct.objects[i]->_257 == g_GameLogic.Team_CaptainRosterLoc[g_d_GameSettings.humanTeamNumber]) {
            g_Fielders[i].rosterLocSkippingCap = 0;
        } else {
            g_Fielders[i].rosterLocSkippingCap = ++count;
        }
    }
}
