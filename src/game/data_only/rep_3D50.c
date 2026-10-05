#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_rep3D50
#include "game/data_only/rep_3D50.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"

typedef struct {
    u8 _00[0x440];
    VecXYZ position;
    VecXYZ previousPosition;
    u8 _458[0xC];
    s16 active;
    u8 _466[0x13];
    u8 enabled;
    u16 duration[2];
} Rep3D50Shared;

typedef struct {
    u8 _00[0x14];
    u8 side;
    u8 state;
    u8 delay;
    u8 remaining;
} Rep3D50Node;

extern Rep3D50Shared lbl_3_common_bss_35154;
extern u8 lbl_80366158[];
extern u8 lbl_3_data_281F0[];
extern u8 lbl_3_data_283F0[];
extern u8 lbl_3_data_28410[];
extern void fn_8002C2D0(VecXYZ*, VecXYZ*, void*);

struct {
    Rep3D50Node* volatile node;
    u8 _04[0x24];
} lbl_3_bss_B9B8;
static const f32 lbl_3_rodata_3DA0 = 0.0f;

void fn_3_160814(int side) {
    Rep3D50Node* node;
    Rep3D50Node* activeNode;
    u16 priority;
    int nodeSide;
    u8 tableSide;
    if (lbl_3_common_bss_35154.active == 0) {
        priority = currentDrawingItem->priority + 1;
        node = (Rep3D50Node*)insertGraphicDrawingFunction(fn_3_160578, priority);
        lbl_3_bss_B9B8.node = node;
        node->side = side == 4;
        activeNode = lbl_3_bss_B9B8.node;
        nodeSide = activeNode->side;
        activeNode->state = 0;
        lbl_3_bss_B9B8.node->delay = *(u32*)(lbl_3_data_283F0 + nodeSide * 0x10);
        lbl_3_bss_B9B8.node->remaining = 0;
        tableSide = lbl_3_bss_B9B8.node->side;
        lbl_3_common_bss_35154.duration[tableSide != 0] = *(u32*)(lbl_3_data_28410 + (tableSide << 2));
    }
}

void fn_3_160578(void) {
    Rep3D50Node* node = (Rep3D50Node*)currentDrawingItem;
    VecXYZ ballPosition;
    VecXYZ delta;
    int effectIndex;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.enabled != 0) {
        removeCurrentDrawingItem();
        return;
    }
    if (*(u8*)((u8*)&lbl_3_common_bss_35154 + 0x466) == 0) {
        lbl_3_bss_B9B8.node = 0;
        removeCurrentDrawingItem();
        return;
    }
    if (lbl_80366158[0x28] != 0) {
        return;
    }
    if (node->state == 0 && g_Ball.warioWaluGarlicIsActive != 0) {
        node->state = 1;
        node->remaining = 0;
    }
    if (node->remaining != 0) {
        node->remaining--;
        return;
    }
    if (node->state == 0) {
        effectIndex = g_GameLogic.bOD_framesInLiveBallScene >= 0;
    } else if (node->state == 1) {
        node->state = 2;
        effectIndex = 2;
    } else {
        effectIndex = 3;
    }
    if (node->side != 0) {
        effectIndex += 4;
    }
    PSVECSubtract((Vec*)&lbl_3_common_bss_35154.previousPosition, (Vec*)&lbl_3_common_bss_35154.position, (Vec*)&delta);
    if (PSVECMag((Vec*)&delta)) {
        *(u32*)(lbl_3_data_281F0 + effectIndex * 0x40) = *(u32*)((u8*)&lbl_3_common_bss_35154 + 4);
        fn_8002C2D0(&lbl_3_common_bss_35154.position, &delta, lbl_3_data_281F0 + effectIndex * 0x40);
    }
    ballPosition.x = *(f32*)((u8*)&g_Ball + 0x1A80);
    ballPosition.y = -*(f32*)((u8*)&g_Ball + 0x1A84);
    ballPosition.z = *(f32*)((u8*)&g_Ball + 0x1A88);
    if (effectIndex % 4 == 3) {
        PSVECSubtract((Vec*)&lbl_3_common_bss_35154._458, (Vec*)&ballPosition, (Vec*)&delta);
        if (PSVECMag((Vec*)&delta)) {
            if (g_Ball.framesUntilBallHitsGround == lbl_3_common_bss_35154.duration[node->side != 0]) {
                effectIndex--;
            }
            fn_8002C2D0(&ballPosition, &delta, lbl_3_data_281F0 + effectIndex * 0x40);
        }
    }
    if (node->state == 2) {
        memcpy(lbl_3_common_bss_35154._458, &ballPosition, sizeof(VecXYZ));
    }
    node->remaining = node->delay;
    if (node->delay != 0) {
        node->delay--;
    }
}
