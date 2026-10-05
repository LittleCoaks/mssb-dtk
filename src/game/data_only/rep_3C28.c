#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_rep3C28
#include "game/data_only/rep_3C28.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"

typedef struct {
    void* sceneItem;
    u32 texture;
    u8 _08[0x438];
    VecXYZ position;
    VecXYZ previousPosition;
} Rep3C28SceneFx;

extern Rep3C28SceneFx lbl_3_common_bss_35154;
extern struct { u8 _00[0x28]; u8 _28; } lbl_80366158;

typedef struct {
    u32 texture;
    s32 params[15];
} Rep3C28Effect;

static Rep3C28Effect lbl_3_data_27C98[3] = {
    {0, {4, 6, 110000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xFFFFFF00, 0, 50000, 20000}},
    {0, {4, 6, 110000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xFFFFFF00, 0, 50000, 20000}},
    {0, {4, 6, 150000, 1000, 90000, 40, 1, 102000, 101000, 100, 2000000, 0xFFFFFF00, 0, 50000, 20000}},
};

extern void fn_8002C2D0(VecXYZ*, VecXYZ*, void*);

// .text:0x0015F574 size:0xD4 mapped:0x8079E608
void fn_3_15F574(void) {
    VecXYZ delta;
    VecXYZ* position;
    int effectIndex;

    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        effectIndex = 2;
    } else {
        int frames = g_Ball.framesSinceHit;
        effectIndex = frames > 0;
    }

    position = &lbl_3_common_bss_35154.position;
    PSVECSubtract((Vec*)&lbl_3_common_bss_35154.previousPosition, (Vec*)position, (Vec*)&delta);
    if (PSVECMag((Vec*)&delta)) {
        lbl_3_data_27C98[effectIndex].texture = lbl_3_common_bss_35154.texture;
        if (lbl_80366158._28 == FALSE) {
            fn_8002C2D0(position, &delta, &lbl_3_data_27C98[effectIndex]);
        }
    }
}
