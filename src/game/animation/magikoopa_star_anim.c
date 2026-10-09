#define SQRT2_LINKAGE static
#include "game/animation/magikoopa_star_anim.h"
#define REP_HEADER_DATA_FN getRepHeaderData_magikoopa_star_anim
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x8001b728.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/mtx.h"
#include "Dolphin/rand.h"
#include "Dolphin/stl.h"
#include "stl/math.h"

// One 0x50-byte spark record, copied from a .data template and handed to fn_80026998.
typedef struct _StarSparkParams {
    /*0x00*/ void* texture;
    /*0x04*/ u32 _04[3];
    /*0x10*/ Vec vel;
    /*0x1C*/ f32 unk1C;
    /*0x20*/ f32 unk20;
    /*0x24*/ f32 unk24;
    /*0x28*/ f32 unk28;
    /*0x2C*/ f32 unk2C;
    /*0x30*/ f32 scaleStart;
    /*0x34*/ f32 scaleEnd;
    /*0x38*/ u32 _38[2];
    /*0x40*/ Vec pos;
    /*0x4C*/ u8 color[3];
    /*0x4F*/ u8 _4F;
} StarSparkParams; // size: 0x50

// Spark template, copied into a local record before every spawn.
static StarSparkParams lbl_3_data_28508 = {
    0, { 0x20, 0x1, 0x24 }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.25f, { 0xFF, 0 },
    { 0.0f, 0.0f, 0.0f }, { 0xFF, 0xFF, 0xFF }, 0,
};
// Bone node ids picked at random for the star-spark collision offset (23 entries + pad byte).
static u8 lbl_3_data_28558[0x18] = {
    0x04, 0x05, 0x06, 0x07, 0x08, 0x10, 0x11, 0x12, 0x13, 0x14, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x00,
};
extern void* lbl_803CBD0C;
extern void fn_80026998(StarSparkParams* params);

// The animated character a drawing item follows.
typedef struct _MagiAnimObj {
    /*0x00*/ u8 _00[0x44];
    /*0x44*/ f32 rot;
    /*0x48*/ u8 _48[0x62 - 0x48];
    /*0x62*/ s16 animId;
    /*0x64*/ u8 _64[0x254 - 0x64];
    /*0x254*/ s8 charIdx;
} MagiAnimObj;

typedef struct _MagiDrawItem {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ MagiAnimObj* obj;
    /*0x18*/ s16 frame;
    /*0x1A*/ u8 _1A;
    /*0x1B*/ E(u8, BOOL) started;
} MagiDrawItem;

typedef struct _MagiBallModel {
    /*0x00*/ u8 _00[4];
    /*0x04*/ Vec pos;
    /*0x10*/ u8 _10[0x28 - 0x10];
} MagiBallModel; // size: 0x28

extern struct {
    /*0x0000*/ u8 _0000[0x2D90];
    /*0x2D90*/ MagiBallModel* ballModels;
} hugeAnimStruct;

typedef struct _MagiSharedBlock {
    /*0x000*/ u8 _000[0x479];
    /*0x479*/ u8 effectsDisabled;
    /*0x47A*/ u8 _47A[0x480 - 0x47A];
} MagiSharedBlock;

extern MagiSharedBlock lbl_3_common_bss_35154;

static struct {
    s8 count;
    u8 _pad[0x1F];
} lbl_3_bss_B9E0;

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


static inline void fieldingSpawnSpark(FieldingDrawItem *item) {
    StarSparkParams spark;
    s8 node;
    FieldingAnimObj *obj;
    Vec offset;

    node = (s8)lbl_3_data_28558[(u32)rand() % 23];
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

// .text:0x001678A8 size:0x41C mapped:0x807A693C
void fn_3_1678A8(void) {
    MagiDrawItem* item = (MagiDrawItem*)currentDrawingItem;
    int i;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        removeCurrentDrawingItem();
    } else {
        s16 state = item->obj->animId;
        if ((state >= 8 && state <= 0xE) || (state >= 0x11 && state <= 0x1B)) {
            StarSparkParams p;
            Vec offset = { 0.0f, 0.0f, 0.0f };
            Vec v;
            f32 angle;
            f32 scale;

            memcpy(&p, &lbl_3_data_28508, sizeof(p));
            for (i = 0; i < 1; i++) {
                p.texture = lbl_803CBD0C;
                p.scaleEnd = p.scaleStart;
                angle = 0.017453292f *
                        ((f32)(45.0 * (2.0 * ((f32)rand() / 32767.0f - 0.5)) + 0.0f) - 57.29578f * item->obj->rot);
                v.x = -(f32)sin(angle);
                v.y = 1.0f;
                v.z = (f32)cos(angle);
                scale = (f32)(0.03f * (2.0 * ((f32)rand() / 32767.0f - 0.5)) + 0.1f);
                v.x *= scale;
                v.z *= scale;
                v.y *= (f32)(0.03f * (2.0 * ((f32)rand() / 32767.0f - 0.5)) + 0.1f);
                memcpy(&p.vel, &v, sizeof(Vec));
                p.unk1C = 1.0f;
                p.unk28 = 0.0f;
                p.unk20 = 0.0f;
                p.unk24 = 1.0f;
                p.unk2C = -0.0044f;
                getAnimationCollisionOffset(item->obj->charIdx, (s8)lbl_3_data_28558[(u32)rand() % 23], &offset);
                memcpy(&p.pos, &offset, sizeof(Vec));
                memset(&offset, 0, sizeof(Vec));
                p.color[0] = rand() % 256;
                p.color[1] = rand() % 256;
                p.color[2] = rand() % 256;
                fn_80026998(&p);
            }
            item->started = TRUE;
        } else if (item->started != FALSE) {
            removeCurrentDrawingItem();
        }
    }
}

// .text:0x001674D0 size:0x3D8 mapped:0x807A6564
void fn_3_1674D0(void) {
    MagiDrawItem* item = (MagiDrawItem*)currentDrawingItem;
    u32 i;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        removeCurrentDrawingItem();
    } else {
        s16 state = item->obj->animId;
        if (state == 0x1B || state == 0x1A) {
            if (g_Ball.ballState == BALL_STATE_HIT) {
                StarSparkParams p;
                Mtx mtx;
                Vec offset = { 0.0f, 0.0f, 0.0f };
                Vec vel;
                Vec tmp;
                getAnimationCollisionOffset(item->obj->charIdx, 0x2F, &offset);
                vel.x = -1.0f * -(f32)sin(-item->obj->rot);
                vel.z = -1.0f * (f32)cos(-item->obj->rot);
                vel.y = -g_Ball.AtBat_Contact_BallPos.y - offset.y;
                vel.x = 5.0f * vel.x * ((f32)item->frame / 10.0f);
                vel.z = 5.0f * vel.z * ((f32)item->frame / 10.0f);
                vel.y = vel.y * ((f32)item->frame / 10.0f);
                PSVECAdd(&vel, &offset, &vel);
                memcpy(&p, &lbl_3_data_28508, sizeof(p));
                p.texture = lbl_803CBD0C;
                PSMTXInverse(fn_80052768_getCamera(0)->view, mtx);
                for (i = 0; i < 5; i++) {
                    tmp.x = 0.5f * (2.0f * (((f32)rand() / 32767.0f) - 0.5f));
                    tmp.y = 0.5f * (2.0f * (((f32)rand() / 32767.0f) - 0.5f));
                    tmp.z = 0.0f;
                    PSMTXMultVecSR(mtx, &tmp, &tmp);
                    PSVECAdd(&tmp, &vel, &tmp);
                    memcpy(&p.pos, &tmp, sizeof(Vec));
                    p.color[0] = rand() % 256;
                    p.color[1] = rand() % 256;
                    p.color[2] = rand() % 256;
                    fn_80026998(&p);
                }
            } else {
                removeCurrentDrawingItem();
            }
            item->started = TRUE;
            item->frame++;
        } else if (item->started != FALSE) {
            removeCurrentDrawingItem();
        }
    }
}

// .text:0x00167178 size:0x358 mapped:0x807A620C
void fn_3_167178(void) {
    MagiDrawItem* item = (MagiDrawItem*)currentDrawingItem;
    StarSparkParams p;
    Mtx mtx;
    Vec offset = { 0.0f, 0.0f, 0.0f };
    Vec dir;
    u32 i;
    f32 angle;
    f32 speed;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        removeCurrentDrawingItem();
    } else {
        getAnimationCollisionOffset(item->obj->charIdx, 4, &offset);
        PSMTXInverse(fn_80052768_getCamera(0)->view, mtx);
        memcpy(&p, &lbl_3_data_28508, sizeof(p));
        memcpy(&p.pos, &offset, sizeof(Vec));
        p.texture = lbl_803CBD0C;
        p.scaleEnd = p.scaleStart;
        for (i = 0; i < 20; i++) {
            angle = 18.0 * i;
            angle += 9.0 * (2.0 * (((f32)rand() / 32767.0f) - 0.5));
            angle = 0.017453292f * angle;
            dir.x = (f32)cos(angle);
            dir.y = (f32)sin(angle);
            dir.z = 0.0f;
            PSMTXMultVecSR(mtx, &dir, &dir);
            speed = 0.03f * (2.0 * (((f32)rand() / 32767.0f) - 0.5)) + 0.1f;
            memcpy(&p.vel, &dir, sizeof(Vec));
            p.unk1C = speed;
            p.color[0] = rand() % 256;
            p.color[1] = rand() % 256;
            p.color[2] = rand() % 256;
            fn_80026998(&p);
        }
        removeCurrentDrawingItem();
    }
}

// .text:0x00166FCC size:0x1AC mapped:0x807A6060
void fn_3_166FCC(void) {
    MagiDrawItem* item = (MagiDrawItem*)currentDrawingItem;
    s16 state;
    s8 node;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        removeCurrentDrawingItem();
    } else {
        state = item->obj->animId;
        if (state == 0x26 || state == 0x27) {
            node = lbl_3_data_28558[(u32)rand() % 23];
            fn_3_166C30(item->obj, node);
        } else {
            removeCurrentDrawingItem();
        }
    }
}

// .text:0x00166E04 size:0x1C8 mapped:0x807A5E98
void fn_3_166E04(void) {
    MagiDrawItem* item = (MagiDrawItem*)currentDrawingItem;
    s16 state;
    s8 node;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        removeCurrentDrawingItem();
    } else {
        state = item->obj->animId;
        if (state == 0x22 || (g_Ball.ballState == BALL_STATE_HELD && (state == 5 || state == 7))) {
            node = lbl_3_data_28558[(u32)rand() % 23];
            fn_3_166C30(item->obj, node);
        } else {
            removeCurrentDrawingItem();
        }
    }
}

// .text:0x00166D40 size:0xC4 mapped:0x807A5DD4
void fn_3_166D40(void) {
    MagiDrawItem* item = (MagiDrawItem*)currentDrawingItem;
    s16 state;
    s8 node;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        removeCurrentDrawingItem();
    } else {
        state = item->obj->animId;
        if ((state == 0x1B || state == 0x1A) && g_Ball.ballState == BALL_STATE_HIT) {
            applyStarRelatedTransformations();
            item->started = TRUE;
        } else if (item->started != FALSE) {
            removeCurrentDrawingItem();
        }
    }
}

// .text:0x00166C30 size:0x110 mapped:0x807A5CC4
void fn_3_166C30(MagiAnimObj* obj, s8 node) {
    StarSparkParams p;
    Vec offset;

    memset(&offset, 0, sizeof(Vec));
    memcpy(&p, &lbl_3_data_28508, sizeof(p));
    p.texture = lbl_803CBD0C;
    if (!getAnimationCollisionOffset(obj->charIdx, node, &offset)) {
        memset(&offset, 0, sizeof(Vec));
        getAnimationCollisionOffset(obj->charIdx, 4, &offset);
    }
    memcpy(&p.pos, &offset, sizeof(Vec));
    p.color[0] = rand() % 256;
    p.color[1] = rand() % 256;
    p.color[2] = rand() % 256;
    fn_80026998(&p);
}

// .text:0x0016699C size:0x294 mapped:0x807A5A30
void applyStarRelatedTransformations(void) {
    StarSparkParams p;
    Mtx mtx;
    Vec offset;
    Vec tmp;
    MagiBallModel* model;

    memset(&offset, 0, sizeof(Vec));
    memcpy(&p, &lbl_3_data_28508, sizeof(p));
    p.texture = lbl_803CBD0C;
    offset.x = 2.0f * (((f32)rand() / 32767.0f) - 0.5f);
    offset.y = 0.5f * (2.0f * (((f32)rand() / 32767.0f) - 0.5f));
    PSMTXInverse(fn_80052768_getCamera(0)->view, mtx);
    PSMTXMultVecSR(mtx, &offset, &offset);
    switch (g_Ball.currentStarSwing) {
    case CAPTAIN_STAR_TYPE_DK:
        model = &hugeAnimStruct.ballModels[7];
        break;
    case CAPTAIN_STAR_TYPE_DIDDY:
        model = &hugeAnimStruct.ballModels[7];
        break;
    case CAPTAIN_STAR_TYPE_BOWSER:
        model = &hugeAnimStruct.ballModels[10];
        break;
    case CAPTAIN_STAR_TYPE_BOWSERJR:
        model = &hugeAnimStruct.ballModels[11];
        break;
    case CAPTAIN_STAR_TYPE_YOSHI:
        model = &hugeAnimStruct.ballModels[8];
        break;
    case CAPTAIN_STAR_TYPE_BIRDO:
        model = &hugeAnimStruct.ballModels[9];
        break;
    default:
        model = &hugeAnimStruct.ballModels[0];
        break;
    }
    memcpy(&tmp, &model->pos, sizeof(Vec));
    offset.x += tmp.x;
    offset.y += tmp.y;
    offset.z += tmp.z;
    memcpy(&p.pos, &offset, sizeof(Vec));
    p.color[0] = rand() % 256;
    p.color[1] = rand() % 256;
    p.color[2] = rand() % 256;
    fn_80026998(&p);
}

// .text:0x0016696C size:0x30 mapped:0x807A5A00
void magikoopaAnimationRelated(void) {
    insertGraphicDrawingFunction(fn_3_16689C, 0xFFFA);
}

// .text:0x0016689C size:0xD0 mapped:0x807A5930
void fn_3_16689C(void) {
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.effectsDisabled != 0) {
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL || g_GameLogic.framesOfExitingToMenu != 0 ||
               g_Ball.fielderWBallIndex < 0) {
        removeCurrentDrawingItem();
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_Minigame.TF_ballDespawnedInd != 0) {
        removeCurrentDrawingItem();
    } else if (g_Ball.ballState != BALL_STATE_HELD) {
        removeCurrentDrawingItem();
    } else {
        applyStarRelatedTransformations();
    }
}

// .text:0x001666B0 size:0x1EC mapped:0x807A5744
void fn_3_1666B0(Vec* pos) {
    StarSparkParams p;
    Vec v;

    if (++lbl_3_bss_B9E0.count >= 5) {
        memset(&p, 0, sizeof(p));
        memcpy(&p, &lbl_3_data_28508, sizeof(p));
        memcpy(&v, pos, sizeof(Vec));
        p.scaleEnd = 0.2f * p.scaleStart;
        if (v.y > 0.0f) {
            v.y *= -1.0f;
        }
        lbl_3_bss_B9E0.count = 0;
        p.texture = lbl_803CBD0C;
        v.x += 5.0f * ((f32)rand() / 32767.0f - 0.5f);
        v.y -= 3.0f * ((f32)rand() / 32767.0f);
        v.z -= 0.45f;
        memcpy(&p.pos, &v, sizeof(Vec));
        p.color[0] = rand() % 256;
        p.color[1] = rand() % 256;
        p.color[2] = rand() % 256;
        fn_80026998(&p);
    }
}
