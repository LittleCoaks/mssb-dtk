#define SQRT2_LINKAGE static
#include "game/animation/fielding_animations.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/animation/magikoopa_star_anim.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8001b728.h"
#include "Dolphin/mtx.h"
#include "Dolphin/rand.h"
#include "Dolphin/stl.h"

// One 0x50-byte spark record, copied from a .data template and handed to fn_80026998.
typedef struct _StarSparkParams {
    /*0x00*/ void* texture;
    /*0x04*/ u8 _04[0x0C];
    /*0x10*/ Vec vel;
    /*0x1C*/ f32 unk1C;
    /*0x20*/ f32 unk20;
    /*0x24*/ f32 unk24;
    /*0x28*/ f32 unk28;
    /*0x2C*/ f32 unk2C;
    /*0x30*/ f32 scaleStart;
    /*0x34*/ f32 scaleEnd;
    /*0x38*/ u8 _38[0x08];
    /*0x40*/ Vec pos;
    /*0x4C*/ u8 color[3];
    /*0x4F*/ u8 _4F;
} StarSparkParams; // size: 0x50

extern StarSparkParams lbl_3_data_28508;
extern u8 lbl_3_data_28558[23];
extern void* lbl_803CBD0C;
extern void fn_80026998(StarSparkParams* params);

// The animated character a drawing item follows.
typedef struct _FieldingAnimObj {
    /*0x00*/ u8 _00[0x62];
    /*0x62*/ s16 animId;
    /*0x64*/ u8 _64[0x254 - 0x64];
    /*0x254*/ s8 charIdx;
} FieldingAnimObj;

typedef struct _FieldingDrawItem {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ FieldingAnimObj* obj;
    /*0x18*/ s16 frame;
    /*0x1A*/ s8 kind;
    /*0x1B*/ E(u8, BOOL) started;
} FieldingDrawItem;

typedef struct _FieldingSharedBlock {
    /*0x000*/ u8 _000[0x479];
    /*0x479*/ u8 effectsDisabled;
    /*0x47A*/ u8 _47A[0x480 - 0x47A];
} FieldingSharedBlock;

extern FieldingSharedBlock lbl_3_common_bss_35154;

static inline void fieldingSpawnSpark(FieldingDrawItem *item) {
    StarSparkParams spark;
    s8 node;
    FieldingAnimObj *obj;
    Vec offset;

    node = (s8)lbl_3_data_28558[(u32)rand() % ARRAY_COUNT(lbl_3_data_28558)];
    obj = item->obj;
    memset(&offset, 0, sizeof(offset));
    memcpy(&spark, &lbl_3_data_28508, sizeof(spark));
    spark.texture = lbl_803CBD0C;
    if (!getAnimationCollisionOffset(obj->charIdx, node, &offset)) {
        memset(&offset, 0, sizeof(offset));
        getAnimationCollisionOffset(obj->charIdx, 4, &offset);
    }
    memcpy(&spark.pos, &offset, sizeof(offset));
    spark.color[0] = (u8)(rand() % 256);
    spark.color[1] = (u8)(rand() % 256);
    spark.color[2] = (u8)(rand() % 256);
    fn_80026998(&spark);
    item->started = TRUE;
}

// .text:0x001682AC size:0x168
void fieldingRelatedAnimations(void *anim, s8 kind) {
    DrawingSceneStruct *item = NULL;

    if (anim == NULL) {
        return;
    }
    switch (kind) {
    case 1:
        item = insertGraphicDrawingFunction(fn_3_1680D4, 0xFFFA);
        break;
    case 2:
        item = insertGraphicDrawingFunction(fn_3_167F14, 0xFFFA);
        break;
    case 4:
        item = insertGraphicDrawingFunction(fn_3_167CC4, 0xFFFA);
        break;
    case 3:
        item = insertGraphicDrawingFunction(fn_3_167D4C, 0xFFFA);
        break;
    case 10:
        item = insertGraphicDrawingFunction(fn_3_1678A8, 0xFFFA);
        break;
    case 8:
        item = insertGraphicDrawingFunction(fn_3_1674D0, 0xFFFA);
        break;
    case 6:
        item = insertGraphicDrawingFunction(fn_3_166FCC, 0xFFFA);
        break;
    case 12:
        item = insertGraphicDrawingFunction(fn_3_167178, 0xFFFA);
        break;
    case 11:
        item = insertGraphicDrawingFunction(fn_3_166E04, 0xFFFA);
        break;
    case 7:
        item = insertGraphicDrawingFunction(fn_3_166D40, 0xFFFA);
        break;
    }
    if (item != NULL) {
        FieldingDrawItem *drawItem = (FieldingDrawItem *)item;

        drawItem->obj = anim;
        drawItem->frame = 0;
        drawItem->kind = kind;
        drawItem->started = FALSE;
    }
}

// .text:0x001680D4 size:0x1D8
void fn_3_1680D4(void) {
    FieldingDrawItem *item = (FieldingDrawItem *)currentDrawingItem;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        removeCurrentDrawingItem();
    } else if (item->obj->animId == 0x26 || (u16)(item->obj->animId - 0x28) <= 3 ||
               item->obj->animId == 0x2C) {
        fieldingSpawnSpark(item);
    } else if (item->started) {
        removeCurrentDrawingItem();
    }
}

// .text:0x00167F14 size:0x1C0
void fn_3_167F14(void) {
    FieldingDrawItem *item = (FieldingDrawItem *)currentDrawingItem;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        removeCurrentDrawingItem();
    } else if (item->obj->animId == 0x26) {
        fieldingSpawnSpark(item);
    } else if (item->started) {
        removeCurrentDrawingItem();
    }
}

// .text:0x00167D4C size:0x1C8
void fn_3_167D4C(void) {
    FieldingDrawItem *item = (FieldingDrawItem *)currentDrawingItem;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        removeCurrentDrawingItem();
    } else if (item->obj->animId == 0x1B || item->obj->animId == 0x1A) {
        fieldingSpawnSpark(item);
    } else if (item->started) {
        removeCurrentDrawingItem();
    }
}

// .text:0x00167CC4 size:0x88
void fn_3_167CC4(void) {
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        removeCurrentDrawingItem();
    } else if (g_Ball.ballState == BALL_STATE_THROWN) {
        applyStarRelatedTransformations();
    } else {
        removeCurrentDrawingItem();
    }
}
