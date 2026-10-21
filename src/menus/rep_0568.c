#include "menus/rep_0568.h"
#include "menus/captain_select/captain_select.h"
#include "menus/yd_step.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x80025ddc.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x8001d180.h"
#include "Unknown/File_0x8001fc4c.h"
#include "Unknown/File_0x80023b04.h"
#include "Unknown/File_0x800bd478.h"
#include "Unknown/File_0x800bd8c4.h"
#include "Unknown/File_0x800bda94.h"
#include "Unknown/File_0x800c0770.h"
#include "Unknown/objinit.h"
#include "C3/skinning.h"
#include "Unknown/dvdsys.h"
#include "C3/actor.h"
#include "C3/actor/act.h"
#include "C3/actor/actorAnim.h"
#include "C3/control.h"
#include "C3/anim.h"
#include "C3/geoPalette/geoPalette.h"
#include "C3/geoPalette/DisplayObject.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/stl.h"

#define CAP_MODEL_COUNT 13
#define CAP_PORT_COUNT 4

typedef struct {
    /* 0x00 */ u32 _00;
    /* 0x04 */ u32 sizeFlags; // low 28 bits: size of the file
    /* 0x08 */ u32 _08;
    /* 0x0C */ u32 _0C;
} ModelFileEntry; // size: 0x10

/* One of the two draw buffers of a CapEntry. */
typedef struct {
    /* 0x00 */ void *buffer;
    /* 0x04 */ u8 _04[0x10];
    /* 0x14 */ f32 scale;
    /* 0x18 */ u8 _18[0x60 - 0x18];
    /* 0x60 */ s8 index;
    /* 0x61 */ s8 _61;
    /* 0x62 */ u8 _62[2];
} CapBuffer; // size: 0x64

typedef struct {
    /* 0x00 */ CapBuffer bufs[2];
    /* 0xC8 */ u32 _C8;
    /* 0xCC */ u8 _CC;
    /* 0xCD */ u8 _CD;
    /* 0xCE */ u8 _CE;
    /* 0xCF */ s8 _CF;
    /* 0xD0 */ s8 _D0;
    /* 0xD1 */ s8 _D1;
    /* 0xD2 */ u8 _D2[2];
} CapEntry; // size: 0xD4

/* One loaded captain model. */
typedef struct {
    /* 0x000 */ void *actor;
    /* 0x004 */ u8 _004[4];
    /* 0x008 */ u32 *files;
    /* 0x00C */ u8 _00C[4];
    /* 0x010 */ void *_10[6];
    /* 0x028 */ u8 _028[4];
    /* 0x02C */ u8 *_2C;
    /* 0x030 */ CapEntry *entry;
    /* 0x034 */ f32 _34;
    /* 0x038 */ f32 _38;
    /* 0x03C */ f32 _3C;
    /* 0x040 */ f32 _40;
    /* 0x044 */ f32 _44;
    /* 0x048 */ f32 _48;
    /* 0x04C */ f32 _4C;
    /* 0x050 */ u8 _050[0x62 - 0x50];
    /* 0x062 */ s16 _62;
    /* 0x064 */ u8 _064[4];
    /* 0x068 */ s16 _68;
    /* 0x06A */ u8 _06A[0x162 - 0x6A];
    /* 0x162 */ u16 boneSlots[0x32];
    /* 0x1C6 */ u8 _1C6[0x252 - 0x1C6];
    /* 0x252 */ s8 charID;
    /* 0x253 */ u8 _253;
    /* 0x254 */ u8 _254;
    /* 0x255 */ s8 entryIdx;
    /* 0x256 */ u8 _256[0x25C - 0x256];
    /* 0x25C */ u8 _25C;
    /* 0x25D */ u8 _25D;
    /* 0x25E */ u8 _25E[0x265 - 0x25E];
    /* 0x265 */ u8 _265;
    /* 0x266 */ u8 _266[0x268 - 0x266];
    /* 0x268 */ u8 _268;
    /* 0x269 */ u8 _269[3];
    /* 0x26C */ u8 _26C;
    /* 0x26D */ u8 _26D[0x27C - 0x26D];
} CapSlot; // size: 0x27C

typedef struct {
    /* 0x0000 */ u8 _0000[0x60];
    /* 0x0060 */ ActorObjectTable *objTable;
    /* 0x0064 */ u8 _0064[0xAC - 0x64];
    /* 0x00AC */ u32 _AC[4];
    /* 0x00BC */ u8 _00BC[0x13C - 0xBC];
    /* 0x013C */ void *_13C;
    /* 0x0140 */ CapEntry entries[CAP_MODEL_COUNT];
    /* 0x0C04 */ CapSlot slots[CAP_MODEL_COUNT];
    /* 0x2C50 */ CapSlot *objects[CAP_MODEL_COUNT];
    /* 0x2C84 */ u8 _2C84[8];
    /* 0x2C8C */ u8 *modelPool;
    /* 0x2C90 */ u8 _2C90[0x2D94 - 0x2C90];
    /* 0x2D94 */ u8 *actorEntries;
    /* 0x2D98 */ u8 _2D98[0x3078 - 0x2D98];
    /* 0x3078 */ u16 actorCount;
    /* 0x307A */ u8 _307A;
    /* 0x307B */ u8 _307B;
    /* 0x307C */ u8 _307C;
    /* 0x307D */ u8 _307D[0x3154 - 0x307D];
} CapAnimView; // size: 0x3154

/* Scene state of the load-screen tasks; shares the DrawingSceneStruct header. */
typedef struct {
    /* 0x00 */ u8 _00[0x10];
    /* 0x10 */ s16 _10;
    /* 0x12 */ u8 _12[2];
    /* 0x14 */ CapSlot *slot;
    /* 0x18 */ u8 charIDs[CAP_PORT_COUNT];
    /* 0x1C */ u8 stage;
    /* 0x1D */ u8 step;
    /* 0x1E */ u8 index;
    /* 0x1F */ u8 _1F;
    /* 0x20 */ u8 _20;
    /* 0x21 */ u8 loadStep;
} CapLoadTask;

extern CapAnimView hugeAnimStruct;
extern u8 lbl_2_bss_100B8[0x54];
extern u8 lbl_2_bss_100B4;
extern u8 lbl_2_bss_1010C[0x58];
extern CapLoadTask *lbl_2_bss_1224;
extern u8 *lbl_2_bss_1228;
extern u8 *lbl_2_bss_122C;
extern CapBuffer lbl_2_bss_101AC[CAP_PORT_COUNT];

extern ModelFileEntry lbl_2_data_241C[54];
extern ModelFileEntry *lbl_2_data_277C;
extern ModelFileEntry *lbl_2_data_2780[3];
extern s32 lbl_2_data_278C[2];
extern u8 lbl_2_data_2794[0x3C8];
extern f32 lbl_2_data_20F8[][3];
extern int menuCursors[0x16];
extern menuControlStruct *menuControlVariables;
extern u8 superstarUnlocked[0x130];
extern u8 challengeCaptainCharIDArray[12];

typedef struct {
    /* 0x00 */ u8 _pad0[0x59];
    /* 0x59 */ u8 portCaptainSlot[4];
    /* 0x5D */ u8 _pad1[0x64 - 0x5D];
} CapGameSetUp; // size: 0x64

extern CapGameSetUp gameSetUpStep;

void *getAnimObjectActor(void *obj);
void fn_800B2C08(void *actor, s32 arg1);
void fn_800B2BA8(void *actor, u16 boneIdx, s32 arg2, s32 arg3);
void fn_800126EC(void *buf, void *tex, s32 *arg);
void fn_80014990(s32 idx, void *file0, void *file1);
void fn_800638B4(void *slot, void *entry);
void fn_8004B7B4(void *slot, void *entry);
void fn_80014204(s32 count);
void *fn_80023AA4(void);

void fn_2_1937C(ActorObjectTable *table, Mtx cam);
void fn_2_19224(ActorObjectTable *table);
void fn_2_190DC(ActorObjectTable *table);
void fn_2_17C88(void);
void fn_2_17AB8(void);
void fn_2_17648(void);
void fn_2_16F0C(u8 idx);
void fn_2_16D38(void);
void fn_2_190B8(ActorObjectEntry *entry);
void fn_2_18398(void);
void fn_2_18748(void);
void fn_2_188EC(void);
BOOL fn_2_18650(u8 port);
void fn_2_18148(CapLoadTask *task);
void fn_2_17ED8(void);
void fn_2_16F78(u8 idx);
void fn_2_16DA8(void);
void fn_2_16CE0(void);
void fn_2_16A98(int idx, int anim, u8 loop, u8 val, s16 frameScale, int unused, u8 speedDiv);

#define STATE lbl_2_bss_100B8
#define TASK ((CapLoadTask *)currentDrawingItem)

const f32 lbl_2_rodata_568[20] = {
    1.0f, 1.5707964f, 1.0f, -1.0f, 4.712389f, 3.1415927f, -1.0f, 0.0f, -1.0f, 1.0f,
    1.0f, 1.5707964f, 1.0f, -1.0f, 4.712389f, 3.1415927f, -1.0f, 0.0f, -1.0f, 1.0f,
};

// .text:0x0001937C size:0x140 mapped:0x80658410
void fn_2_1937C(ActorObjectTable *table, Mtx cam) {
    Mtx44 proj;
    u16 i;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < table->count; i++) {
        CapSlot *obj = hugeAnimStruct.objects[i];
        if (obj != NULL) {
            ActorObjectEntry *e = &table->entries[i];
            if (e->actor != NULL && e->applyControl != 0) {
                f32 w = obj->_34 / 1280.0f;
                f32 h = obj->_38 / 1280.0f;
                C_MTXFrustum(proj, -0.175f + h, 0.175f + h, 0.25f + w, -0.25f + w, 1.0f, 512.0f);
                GXSetProjection(proj, GX_PERSPECTIVE);
                sknRelated(e, cam);
            }
        }
    }
}

// .text:0x00019224 size:0x158 mapped:0x806582B8
void fn_2_19224(ActorObjectTable *table) {
    u16 i;

    for (i = 0; i < table->count; i++) {
        CapSlot *obj = hugeAnimStruct.objects[i];
        if (obj != NULL && obj->_25D != 0) {
            ActorObjectEntry *e = &table->entries[i];
            if (e->actor != NULL) {
                if (e->animPending != 0) {
                    ACTSetAnimation(e->actor, e->anim, NULL, e->seqNum, 0.0f, e->blendTime);
                }
                if (e->framePending != 0) {
                    setActorAnimFrame(e->actor, e->frame);
                }
                if (e->speedPending != 0) {
                    ACTSetSpeed(e->actor, e->speed);
                }
                if (e->boneParam & 2) {
                    updateBoneParam(e->actor, e->boneParam & 1);
                }
                Set_FUN_800b2b6c((UnkB2B4C *)e->actor, e->unk68);
                if (e->applyControl != 0) {
                    fn_800BDA24(e);
                }
                e->actor->unk98 = 1;
                e->animPending = 0;
                e->framePending = 0;
                e->speedPending = 0;
                e->boneParam &= 1;
            }
        }
    }
}

// .text:0x000190DC size:0x148 mapped:0x80658170
void fn_2_190DC(ActorObjectTable *table) {
    u16 i;

    for (i = 0; i < table->count; i++) {
        if (hugeAnimStruct.actorEntries + i * 0x28 != NULL) {
            ActorObjectEntry *e = &table->entries[i];
            if (e->actor != NULL) {
                if (e->animPending != 0) {
                    ACTSetAnimation(e->actor, e->anim, NULL, e->seqNum, 0.0f, e->blendTime);
                }
                if (e->framePending != 0) {
                    setActorAnimFrame(e->actor, e->frame);
                }
                if (e->speedPending != 0) {
                    ACTSetSpeed(e->actor, e->speed);
                }
                if (e->boneParam & 2) {
                    updateBoneParam(e->actor, e->boneParam & 1);
                }
                Set_FUN_800b2b6c((UnkB2B4C *)e->actor, e->unk68);
                if (e->applyControl != 0) {
                    fn_800BDA24(e);
                }
                e->actor->unk98 = 1;
                e->animPending = 0;
                e->framePending = 0;
                e->speedPending = 0;
                e->boneParam &= 1;
            }
        }
    }
}

// .text:0x000190B8 size:0x24 mapped:0x8065814C
void fn_2_190B8(ActorObjectEntry *entry) {
    setLITLightPtr((void *)entry->drawArgs[0]);
}

// .text:0x00018FBC size:0xFC mapped:0x80658050
void captainSelectLoadScreen(void) {
    DrawingSceneStruct *task = insertGraphicDrawingFunction(fn_2_188EC, 0x6000);
    int i;

    STATE[0x19] = 0;
    STATE[0x1B] = 1;
    if (Static_Stats_Tables._4700[1] == 0) {
        for (i = 0; i < STATE[0x2D]; i++) {
            STATE[0x27 + i] = -1;
        }
        ((CapLoadTask *)task)->stage = 0;
    } else {
        for (i = 0; i < STATE[0x2D]; i++) {
            STATE[0x14 + i] = 0;
        }
        ((CapLoadTask *)task)->stage = 0;
    }
    STATE[0] = 0;
    STATE[1] = 0;
    if (STATE[0] < 10) {
        STATE[2] = -1;
        STATE[3] = -1;
        STATE[4] = -1;
        STATE[5] = -1;
        STATE[6] = -1;
        STATE[7] = -1;
        STATE[8] = -1;
        STATE[9] = -1;
        STATE[10] = -1;
        STATE[11] = -1;
    }
}

// .text:0x000188EC size:0x6D0 mapped:0x80657980
void fn_2_188EC(void) {
    CapLoadTask *task;
    CapAnimView *view = &hugeAnimStruct;
    int i;

    task = TASK;
    view->_307A = 0;
    view->_307C = 0;
    switch (task->stage) {
    case 0:
        fn_2_166CC();
        captainSelect_setupCameraProjection();
        fn_2_17ED8();
        fn_2_16DA8();
        task->stage++;
        break;
    case 1: {
        CapLoadTask *t = (CapLoadTask *)insertGraphicDrawingFunction(fn_2_18748, 0);
        t->step = 0;
        t->_1F = 0;
        t->index = 0;
        task->stage++;
        break;
    }
    case 2:
        if (lbl_2_bss_100B4 != 0) {
            for (i = 0; i < STATE[0x2D]; i++) {
                if (STATE[0x40 + i] == 0) {
                    goto notDone;
                }
            }
            for (i = 0; i < STATE[0x2D]; i++) {
                view->objects[i] = NULL;
            }
            removeCurrentDrawingItem();
            break;
        }
    notDone:
        if (STATE[0x19] != 0) {
            for (i = 0; i < STATE[0x2D]; i++) {
                if (STATE[0x14 + i] != 0) {
                    if (fn_2_18650(i)) {
                        STATE[0x14 + i] = 0;
                    }
                }
            }
            view->_307A = 5;
            view->_307C = 1;
            fn_2_16460();
            PSMTXCopy((f32(*)[4])lbl_2_bss_1010C, fn_80052768_getCamera(0)->view);
            fn_2_16CE0();
        }
        break;
    }
}

// .text:0x00018748 size:0x1A4 mapped:0x806577DC
void fn_2_18748(void) {
    CapLoadTask *task = TASK;
    int i;

    switch (task->step) {
    case 0:
        for (i = 0; i < STATE[0x2D]; i++) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                task->charIDs[i] = challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6 + menuCursors[4 + task->index]];
            } else {
                task->charIDs[i] = mapCaptainCursorPositionToCharID[menuCursors[4 + task->index]];
            }
            if (task->index == 2) {
                task->index = 0;
            }
        }
        task->_10 = 0;
        task->loadStep = 0;
        task->step++;
    case 1:
        fn_2_18148(task);
        if (STATE[0x18] != 0) {
            STATE[0x18] = 0;
            STATE[0x32] = 0;
            task->loadStep = 0;
            task->_10 = 0;
            task->index++;
            if (task->index >= STATE[0x2D]) {
                task->index = 0;
                task->step = 0;
                STATE[0x19] = 1;
                removeCurrentDrawingItem();
            } else {
                task->step = 0;
            }
        } else if (lbl_2_bss_100B4 != 0) {
            task->index = 0;
            task->step = 0;
            removeCurrentDrawingItem();
        }
        break;
    }
}

// .text:0x00018650 size:0xF8 mapped:0x806576E4
BOOL fn_2_18650(u8 port) {
    int head = ((s8)STATE[0] + 1) % 10;

    if (head == (s8)STATE[1]) {
        return FALSE;
    }
    if (lbl_2_bss_1224 == NULL) {
        if ((lbl_2_bss_1224 = (CapLoadTask *)insertGraphicDrawingFunction(fn_2_18398, 0xFFFF)) != NULL) {
            lbl_2_bss_1224->stage = 0;
            lbl_2_bss_1224->step = 0;
        } else {
            return FALSE;
        }
    }
    STATE[2 + (s8)STATE[0]] = port;
    STATE[0] = head;
    STATE[0x42 + port] = 1;
    return TRUE;
}

// .text:0x00018398 size:0x2B8 mapped:0x8065742C
void fn_2_18398(void) {
    CapLoadTask *task = TASK;

    switch (task->step) {
    case 0: {
        u8 port = STATE[2 + (s8)STATE[1]];
        if ((s8)port == -1) {
            STATE[0x18] = 0;
            STATE[0x1B] = 1;
            STATE[0x1A] = 0;
            STATE[0x32] = 0;
            lbl_2_bss_1224 = NULL;
            removeCurrentDrawingItem();
            break;
        }
        task->index = port;
        STATE[2 + (s8)STATE[1]] = -1;
        STATE[0x1A] = 1;
        STATE[0x1B] = 0;
        STATE[1] = ((s8)STATE[1] + 1) % 10;
        STATE[0x27 + task->index] = task->index;
        task->step = 1;
        task->_10 = 0;
        if (Static_Stats_Tables._4744[0x11] == 0) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                task->charIDs[task->index] = challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6 + menuCursors[4 + (u8)task->index]];
            } else {
                task->charIDs[task->index] = mapCaptainCursorPositionToCharID[menuCursors[4 + (u8)task->index]];
            }
            if (task->index == 2) {
                task->index = 0;
            }
        } else if (Static_Stats_Tables._4744[0x11] == 1) {
            switch ((s8)task->index) {
            case 0:
            case 1:
                task->charIDs[task->index] = inMemRoster[task->index][menuCursors[12 + task->index] - (task->index * 11 + 2)].stats.CharID;
                break;
            case 2:
            case 3:
                task->charIDs[task->index] = menuCursors[6 + task->index];
                break;
            }
        }
    }
    case 1:
        fn_2_18148(task);
        if (lbl_2_bss_100B4 != 0 && ((u8 *)&lbl_2_bss_100B4)[1] == 0) {
            lbl_2_bss_1224 = NULL;
            STATE[0x18] = 0;
            STATE[0x1B] = 1;
            STATE[0x1A] = 0;
            STATE[0x32] = 0;
            task->step = 0;
            removeCurrentDrawingItem();
        } else if (STATE[0x18] != 0) {
            STATE[0x18] = 0;
            STATE[0x1A] = 0;
            task->step = 0;
        }
        break;
    }
}

// .text:0x00018148 size:0x250 mapped:0x806571DC
void fn_2_18148(CapLoadTask *task) {
    switch (task->loadStep) {
    case 0:
        task->slot = &hugeAnimStruct.slots[task->index];
        task->slot->charID = task->charIDs[task->index];
        task->_20 = STATE[0x46 + task->index];
        hugeAnimStruct.slots[task->index]._25D = 0;
        task->slot->_68 = -1;
        ((u8 *)&lbl_2_bss_100B4)[1] = 1;
        task->loadStep++;
        break;
    case 1:
        ARAMTransfer(&lbl_2_data_241C[(s8)task->charIDs[task->index]], (s32)task->slot->files, 0, 0);
        task->loadStep++;
        break;
    case 2:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            u8 cpuCode;

            fn_2_16F78(task->index);
            cpuCode = g_d_GameSettings.p2_CPU_match_code;
            if (cpuCode == 0 && gameSetUpStep.portCaptainSlot[0] == 0 && task->index == 1) {
                hugeAnimStruct.slots[task->index]._25D = 0;
            } else {
                hugeAnimStruct.slots[task->index]._25D = task->_20 != 0;
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE || cpuCode != 0 ||
                menuControlVariables->previousScreen == 5) {
                fn_2_14BB8(task->index, 1);
            } else if (STATE[0x10] != 0) {
                fn_2_14BB8(task->index, task->index != 0);
            }
            task->loadStep = 0;
            ((u8 *)&lbl_2_bss_100B4)[1] = 0;
            STATE[0x32] = 1;
            STATE[0x18] = 1;
            STATE[0x42 + task->index] = 0;
        }
        break;
    }
}

// .text:0x00017ED8 size:0x270 mapped:0x80656F6C
void fn_2_17ED8(void) {
    u32 maxSize = 0;
    u32 size;
    int t, j, i;

    for (t = 0; t < 12; t++) {
        for (j = 0; j < 9; j++) {
            u32 sz;
            if (t * 9 + j == 0x35) {
                goto done;
            }
            sz = lbl_2_data_241C[Static_Stats_Tables.characterStats[t][j].stats.CharID].sizeFlags & 0x0FFFFFFF;
            if (maxSize < sz) {
                maxSize = sz;
            }
        }
    }
done:
    size = (maxSize + 31) & ~31;
    hugeAnimStruct.modelPool = _OSAllocFromHeap(32, size * STATE[0x2D]);
    for (i = 0; i < STATE[0x2D]; i++) {
        hugeAnimStruct.slots[i].files = (u32 *)(hugeAnimStruct.modelPool + size * i);
    }
    fn_80014204(STATE[0x2D]);
    hugeAnimStruct._13C = fn_80023AA4();
    initActorArray(4);
}

// .text:0x00017C88 size:0x250 mapped:0x80656D1C
void fn_2_17C88(void) {
    u32 maxSize = 0;
    u32 size;
    int t, j, i;

    for (t = 0; t < 12; t++) {
        for (j = 0; j < 9; j++) {
            u32 sz;
            if (t * 9 + j == 0x35) {
                goto done;
            }
            sz = lbl_2_data_241C[Static_Stats_Tables.characterStats[t][j].stats.CharID].sizeFlags & 0x0FFFFFFF;
            if (maxSize < sz) {
                maxSize = sz;
            }
        }
    }
done:
    size = (maxSize + 31) & ~31;
    hugeAnimStruct.modelPool = _OSAllocFromHeap(32, size * STATE[0x2D]);
    for (i = 0; i < STATE[0x2D]; i++) {
        hugeAnimStruct.slots[i].files = (u32 *)(hugeAnimStruct.modelPool + size * i);
    }
}

// .text:0x00017AB8 size:0x1D0 mapped:0x80656B4C
void fn_2_17AB8(void) {
    u32 size = ((lbl_2_data_2780[0]->sizeFlags & 0x0FFFFFFF) + 31) & ~31;
    int i;

    lbl_2_bss_122C = _OSAllocFromHeap(32, size * STATE[0x2D]);
    for (i = 0; i < STATE[0x2D]; i++) {
        lbl_2_bss_101AC[i].buffer = lbl_2_bss_122C + size * i;
        lbl_2_bss_101AC[i]._61 = -1;
        lbl_2_bss_101AC[i].index = -1;
    }
}

// .text:0x00017648 size:0x470 mapped:0x806566DC
void fn_2_17648(void) {
    u32 maxSize = 0;
    u32 size;
    int t, j, k, i;

    for (t = 0; t < 12; t++) {
        for (j = 0; j < 9; j++) {
            if (t * 9 + j == 0x35 || j != 0) {
                goto done;
            }
            for (k = 0; k < 6; k++) {
                u32 sz = lbl_2_data_277C[Static_Stats_Tables.characterStats[t][j].stats.CharID + k].sizeFlags & 0x0FFFFFFF;
                if (maxSize < sz) {
                    maxSize = sz;
                }
            }
        }
    }
done:
    size = (maxSize + 31) & ~31;
    lbl_2_bss_1228 = _OSAllocFromHeap(32, size * STATE[0x2D] * 2);
    for (i = 0; i < STATE[0x2D]; i++) {
        hugeAnimStruct.entries[i].bufs[0].buffer = lbl_2_bss_1228 + size * (i * 2);
        hugeAnimStruct.entries[i].bufs[1].buffer = lbl_2_bss_1228 + size * (i * 2 + 1);
    }
    for (i = 0; i < STATE[0x2D]; i++) {
        CapEntry *e = &hugeAnimStruct.entries[i];
        e->_CF = -1;
        e->_D1 = -1;
        e->_D0 = -1;
        e->_CD = 0xFF;
        e->_C8 = 0;
        e->_CC = 0;
        e->bufs[0].index = i * 2;
        e->bufs[1].index = i * 2 + 1;
    }
}

static inline BOOL isSpecialHandChar(s8 id) {
    return id == 0x12 || id == 0x26 || id == 0x28 || id == 0x29;
}

// .text:0x00016F78 size:0x6D0 mapped:0x8065600C
void fn_2_16F78(u8 idx) {
    CapSlot *slot = &hugeAnimStruct.slots[idx];
    ActorObjectEntry *entry;
    ActorObjectEntry *e;
    u32 *base;
    void *tex;
    void *layout;
    void *geo;
    void *skn;
    void *anim;
    int k;
    int handL;
    int handR;
    int bones;
    u16 id;
    u8 port;

    slot->entryIdx = idx;
    base = slot->files;
    for (k = 0; k < 15; k++) {
        if (slot->files[k] == 0) {
            break;
        }
        slot->files[k] = (u32)base + base[k];
    }
    tex = (void *)slot->files[0];
    layout = (void *)slot->files[1];
    geo = (void *)slot->files[2];
    skn = (void *)slot->files[3];
    convertTextureHeader(tex);
    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, skn);
    haveActLayoutPointToGeoHeader(layout, geo);
    UpdateTexturePalettePointers(geo, tex);
    anim = (void *)slot->files[4];
    slot->_10[5] = anim;
    ANIMGet(slot->_10[5]);
    entry = getAnimObjectActor(slot);
    characterAndBallDisplayRelated(entry, idx, idx, layout, anim, (int)skn);

    e = &hugeAnimStruct.objTable->entries[idx];
    e->anim = slot->_10[5];
    e->seqNum = 0;
    e->frame = 0.0f;
    e->animPending = 1;
    e->framePending = e->speedPending = slot->_10[5] != NULL;
    e->blendTime = 0.0f;
    memset(slot->boneSlots, 0xFF, sizeof(slot->boneSlots));
    bones = hugeAnimStruct.objTable->entries[idx].actor->totalBones;
    for (k = 0; k < bones; k++) {
        id = hugeAnimStruct.objTable->entries[idx].actor->boneArray[k]->boneID;
        if (id != 0xFFFF) {
            slot->boneSlots[id] = k;
        }
    }
    fn_800BD548(&hugeAnimStruct.objTable->entries[idx], 4, hugeAnimStruct._AC[0], hugeAnimStruct._AC[1],
                hugeAnimStruct._AC[2], hugeAnimStruct._AC[3]);
    slot->_40 = slot->_44 = slot->_48 = 0.0f;
    CTRLSetTranslation(&hugeAnimStruct.objTable->entries[idx].control, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&hugeAnimStruct.objTable->entries[idx].control, 0.0f, 0.0f, 0.0f);
    e = &hugeAnimStruct.objTable->entries[idx];
    e->speed = 0.5f;
    e->speedPending = 1;
    fn_800B2C08(hugeAnimStruct.objTable->entries[idx].actor,
                hugeAnimStruct.objects[idx] != NULL ? hugeAnimStruct.objects[idx]->boneSlots[4] : 0xFFFF);
    initShortsHandleCompressedDiskReads((ShortsTableOwner *)hugeAnimStruct.objects[idx]);
    slot->_34 = lbl_2_data_20F8[idx][0];
    slot->_38 = lbl_2_data_20F8[idx][1];
    slot->_3C = lbl_2_data_20F8[idx][2];
    slot->_4C = 0.5f;
    slot->_25D = 0;
    hugeAnimStruct.objTable->entries[idx].callback = (void (*)(void))fn_2_190B8;
    slot->actor = entry->actor;
    callDSInsertListObject((UnkB2B4C *)entry->actor, slot->boneSlots[19]);
    callDSInsertListObject((UnkB2B4C *)entry->actor, slot->boneSlots[25]);

    if (slot->boneSlots[3] != 0xFFFF) {
        fn_800B2B54(slot->actor, slot->boneSlots[3], 13);
    }
    id = slot->boneSlots[3];
    if (id != 0xFFFF) {
        fn_800B2BA8(entry->actor, id, 0, 0);
        *((u8 *)entry->actor->boneArray[id] + 0x136) = 1;
    }
    id = slot->boneSlots[2];
    if (id != 0xFFFF) {
        fn_800B2BA8(entry->actor, id, 0, 0);
        *((u8 *)entry->actor->boneArray[id] + 0x136) = 1;
    }
    id = slot->boneSlots[1];
    if (id != 0xFFFF) {
        fn_800B2BA8(entry->actor, id, 0, 0);
        *((u8 *)entry->actor->boneArray[id] + 0x136) = 1;
    }
    if (slot->boneSlots[36] != 0xFFFF) {
        fn_800B2BA8(entry->actor, slot->boneSlots[36], 0, 0);
    }
    id = slot->boneSlots[46];
    if (id != 0xFFFF) {
        fn_800B2BA8(entry->actor, id, 0, 0);
        *((u8 *)entry->actor->boneArray[id] + 0x136) = 1;
    }

    if (slot->files[5] != 0) {
        CapEntry *capEntry = &hugeAnimStruct.entries[slot->entryIdx];
        slot->entry = &hugeAnimStruct.entries[idx];
        capEntry->bufs[0].buffer = slot->files;
        fn_800126EC(capEntry, tex, &lbl_2_data_278C[0]);
        capEntry->bufs[1].buffer = slot->files;
        fn_800126EC(&capEntry->bufs[1], tex, &lbl_2_data_278C[1]);
    }

    if (isSpecialHandChar(slot->charID)) {
        switch (slot->charID) {
        case 0x12:
            handL = 4;
            handR = 5;
            break;
        case 0x26:
            handL = 2;
            handR = 3;
            break;
        case 0x28:
        case 0x29:
            handL = 6;
            handR = 7;
            break;
        }
    } else {
        handL = 1;
        handR = 0;
    }
    port = idx;
    setHandModelAttached(port, handL, TRUE);
    setHandModelAttached(port, handR, TRUE);
    if (slot->files[13] != 0 && slot->files[14] != 0) {
        adjustInternalPointers((void *)slot->files[13]);
        fn_80014990(port, (void *)slot->files[13], (void *)slot->files[14]);
        ACTActorRelated((void *)slot->files[13], entry);
    }
    slot->entry->_CC = 1;
    slot->entry->bufs[0].scale = 0.5f;
    slot->entry->bufs[1].scale = 0.5f;
    switch (slot->charID) {
    case 2:
        fn_800638B4(slot, entry);
        break;
    case 0x13:
        slot->_25C = 1;
        fn_8004B7B4(slot, entry);
        break;
    }
    fn_2_16A98(port, 0, 1, 0, 0, 0, 0);
}

// .text:0x00016F0C size:0x6C mapped:0x80655FA0
void fn_2_16F0C(u8 idx) {
    CapSlot *slot = &hugeAnimStruct.slots[idx];
    CapEntry *e = &hugeAnimStruct.entries[idx];
    u8 a = slot->charID;
    u8 b = slot->_254;

    if (e->_D0 == -1) {
        e->_CF = a;
        e->_D1 = e->_D0;
        e->_D0 = b;
        e->_CD = slot->_265;
    }
    slot->entry = &hugeAnimStruct.entries[idx];
}

// .text:0x00016DA8 size:0x164 mapped:0x80655E3C
void fn_2_16DA8(void) {
    int i;

    hugeAnimStruct.actorCount = 0;
    for (i = 0; i < STATE[0x2D]; i++) {
        hugeAnimStruct.objects[i] = &hugeAnimStruct.slots[i];
    }
    for (i = 3; i >= 0; i--) {
        STATE[0x42 + i] = 0;
    }
    if (menuControlVariables->previousScreen == 5 || g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        STATE[0x46] = 1;
        STATE[0x47] = 0;
    } else {
        STATE[0x46] = 1;
        STATE[0x47] = 1;
    }
}

// .text:0x00016D38 size:0x70 mapped:0x80655DCC
void fn_2_16D38(void) {
    int i;

    for (i = 0; i < STATE[0x2D]; i++) {
        memset(hugeAnimStruct.slots[i].files, 0, 0x5C);
    }
}

// .text:0x00016CE0 size:0x58 mapped:0x80655D74
void fn_2_16CE0(void) {
    int i;

    for (i = 0; i < STATE[0x2D]; i++) {
        if (hugeAnimStruct.objects[i] != NULL && hugeAnimStruct.objects[i]->_62 == 0x6B) {
            STATE[0x40 + i] = 1;
        }
    }
}

// .text:0x00016A98 size:0x248 mapped:0x80655B2C
void fn_2_16A98(int idx, int anim, u8 loop, u8 val, s16 frameScale, int unused, u8 speedDiv) {
    CapSlot *obj;
    ActorObjectEntry *e;
    f32 speed = 0.0f;
    int boneKind;
    int animIdx;
    u8 seq;

    obj = hugeAnimStruct.objects[idx];
    if (obj != NULL) {
        e = getAnimObjectActor(obj);
        if (speedDiv != 0) {
            speed = 1.0f / speedDiv;
        }
        if (obj->_26C == 0) {
            fn_800B2B54(obj->actor,
                        hugeAnimStruct.objects[idx] != NULL ? hugeAnimStruct.objects[idx]->boneSlots[4] : 0xFFFF, 13);
        } else {
            fn_800B2B54(obj->actor,
                        hugeAnimStruct.objects[idx] != NULL ? hugeAnimStruct.objects[idx]->boneSlots[4] : 0xFFFF, 1);
        }
        if (anim < 3) {
            boneKind = 5;
            animIdx = anim;
        }
        seq = lbl_2_data_2794[animIdx];
        if (obj->_2C != NULL) {
            actorRelated(obj->_2C + 4, 5, seq);
        }
        if (obj->entry != NULL && obj->entry->_CC != 0) {
            actorRelated((u8 *)obj->entry + 0x68, 5, seq);
            actorRelated((u8 *)obj->entry + 4, 5, seq);
        }
        if (idx < STATE[0x2D]) {
            void *bank = obj->_10[boneKind];
            if (bank != NULL) {
                if (animIdx >= *(u16 *)((u8 *)bank + 0xA)) {
                    return;
                }
                e->anim = bank;
                e->seqNum = animIdx;
                e->frame = 0.0f;
                e->animPending = 1;
                e->framePending = bank != NULL;
                e->speedPending = bank != NULL;
                e->blendTime = speed;
            }
        }
        if (loop != 0) {
            e->boneParam = 3;
        } else {
            e->boneParam = 2;
        }
        e->frame = frameScale * obj->_4C;
        e->framePending = 1;
        obj->_268 = val;
    }
}
