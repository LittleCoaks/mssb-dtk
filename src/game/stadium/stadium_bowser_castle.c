#define SQRT2_LINKAGE static
#include "game/stadium/stadium_bowser_castle.h"
#include "header_rep_data.h"
#include "game/stadium/stadium_framework.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "Dolphin/gx.h"
#include "stl/math.h"
#include "Dolphin/rand.h"
#include "game/math/game_math.h"
#include "game/ball/collision_primitives.h"
#include "Dolphin/mtxext.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Dolphin/stl.h"
#include "C3/control.h"
#include "Dolphin/os.h"
#include "game/fielding/fielder.h"
#include "Unknown/File_0x800b4b38.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80025ddc.h"
#include "Unknown/File_0x80033794.h"
#include "Unknown/File_0x8004c094.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x800bf038.h"
#include "Unknown/File_0x8001b728.h"
#include "game/stadium/rep_23E8.h"
#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"
#include "game/ball/ball_physics.h"
#include "game/sound/m_sound.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"

typedef struct _CastleMaterialFlags {
    /*0x00*/ u8 _00[4];
    /*0x04*/ u32 animState;
    /*0x08*/ u8 _08[0x74 - 0x08];
    /*0x74*/ u32 flags;
} CastleMaterialFlags;

typedef struct _CastleModelLevel4 {
    /*0x00*/ u8 _00[4];
    /*0x04*/ CastleMaterialFlags* next;
} CastleModelLevel4;

typedef struct _CastleModelLevel3 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ CastleModelLevel4* next;
} CastleModelLevel3;

typedef struct _CastleModelLevel2 {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ CastleModelLevel3* next;
} CastleModelLevel2;

typedef struct _CastleModelLevel1 {
    /*0x00*/ u8 _00[4];
    /*0x04*/ CastleModelLevel2* flameMat;
    /*0x08*/ u8 _08[0x34 - 0x08];
    /*0x34*/ CastleModelLevel2* thwompMat;
} CastleModelLevel1;

typedef struct _CastleModelRoot {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ CastleModelLevel1* next;
} CastleModelRoot;

typedef struct _CastleHazardObj {
    /*0x00*/ u8 _00[0xA9];
    /*0xA9*/ u8 hazardType;
    /*0xAA*/ u8 _AA[0xB0 - 0xAA];
    /*0xB0*/ u8 hasBounced;
} CastleHazardObj;

// A DrawingSceneStruct-owned per-frame render scratch entry: the node's
// firstHandle field (+0x14) indexes into graphicsRelatedArray to fetch the
// CastleGfxObject to update.
typedef struct _CastleGfxScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
} CastleGfxScene;

typedef struct _CastleGfxObject {
    /*0x00*/ u8 _00[0x48];
    /*0x48*/ Vec pos;
} CastleGfxObject;

typedef struct _CastleGfxSceneHolder {
    /*0x00*/ CastleGfxScene* scene;
    /*0x04*/ u8 _04[0xBC - 0x04];
} CastleGfxSceneHolder;

// Per-camera-slot scratch entry (2 of these; index by drawStadiumRelated).
typedef struct _CastleCameraSlot {
    /*0x00*/ u8 _00[8];
    /*0x08*/ Mtx mtx;
    /*0x38*/ DrawingSceneStruct* item;
} CastleCameraSlot; // size 0x3C

typedef struct _CastleMaterialEntry {
    /*0x00*/ u8 kind;
    /*0x01*/ u8 _01[3];
    /*0x04*/ u32 animState;
    /*0x08*/ u8 _08[0x10 - 0x08];
} CastleMaterialEntry; // size 0x10

typedef struct _CastleMaterialList {
    /*0x00*/ u8 _00[4];
    /*0x04*/ CastleMaterialEntry* entries;
    /*0x08*/ u16 count;
} CastleMaterialList;

typedef struct _CastleMaterialListHolder {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ CastleMaterialList* list;
} CastleMaterialListHolder;

typedef struct _CastleMaterialGroupNode {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ CastleMaterialListHolder* holder;
} CastleMaterialGroupNode;

typedef struct _CastleMaterialRoot {
    /*0x00*/ u8 _00[6];
    /*0x06*/ u16 groupCount;
    /*0x08*/ u8 _08[0x18 - 0x08];
    /*0x18*/ CastleMaterialGroupNode** groups;
} CastleMaterialRoot;

typedef struct _CastleFireballTarget {
    /*0x00*/ u8 _00[0x9C];
    /*0x9C*/ Vec anchorPos;
} CastleFireballTarget;

// Per-node scratch view of DrawingSceneStruct's shared scratch region (see
// CastleGfxScene/CastleCameraSlot for other nodes' own views of the same
// region); this node stores a 6-entry emitter-handle array starting at 0x14.
typedef struct _CastleFireEmitterScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ struct _CastleFlameEmitter* handles[6];
} CastleFireEmitterScene;

typedef struct _CastleFlameParticle {
    /*0x00*/ struct _CastleFlameParticle* next;
    /*0x04*/ Vec origin;
    /*0x10*/ f32 velX;
    /*0x14*/ f32 _14;
    /*0x18*/ f32 velZ;
    /*0x1C*/ f32 scale;
    /*0x20*/ f32 _20;
    /*0x24*/ f32 alpha;
    /*0x28*/ u8 _28[0x38 - 0x28];
    /*0x38*/ f32 _38;
    /*0x3C*/ f32 _3C;
    /*0x40*/ u8 _40;
    /*0x41*/ u8 _41;
    /*0x42*/ u8 _42;
    /*0x43*/ u8 alphaByte;
    /*0x44*/ u8 _44[0x48 - 0x44];
    /*0x48*/ s16 _48;
    /*0x4A*/ s16 _4A;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 _4D;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
} CastleFlameParticle;

typedef struct _CastleFlameEmitter {
    /*0x00*/ u8 _00[0x08];
    /*0x08*/ u32 _08;
    /*0x0C*/ CastleFlameParticle* particles;
    /*0x10*/ u32 _10;
    /*0x14*/ u8 _14[0x18 - 0x14];
    /*0x18*/ Vec origin;
    /*0x24*/ u8 kind;
} CastleFlameEmitter;

extern void fn_800A7D4C(s32 arg0, void* arg1);
extern u8 drawStadiumRelated;
extern void fn_800528C0(f32 x, f32 y, f32 z, s16* outX, s16* outY);
extern u16 lbl_3_data_177F0;
extern void fn_800BDF70(StadiumModel* model);
extern CastleCameraSlot lbl_3_data_17804[2];
extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_3_data_84B8[0x3C];

static u8 lbl_3_bss_9D82;
static u32 lbl_3_bss_9D84;
static u32 lbl_3_bss_9D88;
static s32 lbl_3_bss_9D90;
static s32 lbl_3_bss_9D94;
static u32 lbl_3_bss_9D98;
static s32 lbl_3_bss_9D9C;
static u8 lbl_3_bss_9DE7;
static Vec lbl_3_bss_9DE8[8];
static u8 lbl_3_bss_9E48[8];
static CastleGfxSceneHolder lbl_3_bss_9E50;
static u32 lbl_3_bss_9F0C[5];

static const u8 lbl_3_rodata_2028[3] = { 0xA0, 0x46, 0x00 };
static const f32 const_pi_or_180 = 0.017453292f;
static const Vec lbl_3_rodata_202C[6] = {
    { -19.3f, -14.5f, 86.0f },
    { 19.3f, -14.5f, 86.0f },
    { -15.92f, -18.8f, 112.16f },
    { 15.92f, -18.8f, 112.16f },
    { -36.5f, -17.9f, -22.8f },
    { 36.5f, -17.9f, -22.8f },
};

// .text:0x000C1964 size:0x10 mapped:0x807009F8
void fn_3_C1964(void) {
    lbl_3_bss_9D9C = 1;
}

// .text:0x000C1974 size:0x54 mapped:0x80700A08
void fn_3_C1974(int offset) {
    DrawingSceneStruct* item = insertGraphicDrawingFunction(fn_3_C2644, 4);
    item->state = 0;
    lbl_3_bss_9D98 = offset + 0x3C4;
    lbl_3_bss_9D9C = 0;
}

// .text:0x000C19C8 size:0x250 mapped:0x80700A5C
void fn_3_C19C8(void) {
    return;
}

// .text:0x000C1C18 size:0x62C mapped:0x80700CAC
void fn_3_C1C18(void) {
    return;
}

// .text:0x000C2244 size:0xCC mapped:0x807012D8
void fn_3_C2244(void) {
    DrawingSceneStruct* item = currentDrawingItem;

    if (lbl_3_bss_9D9C != 0) {
        lbl_3_bss_9D90 = 0;
        removeCurrentDrawingItem();
        return;
    }
    if (*((u8*)item + 0x2A) != 0) {
        fn_800A7D4C(1, &lbl_3_data_17804[drawStadiumRelated]);
        PSMTXCopy(fn_80052768_getCamera(0)->view, lbl_3_data_17804[drawStadiumRelated].mtx);
        lbl_3_data_17804[drawStadiumRelated].item = item;
    }
}

// .text:0x000C2310 size:0xD0 mapped:0x807013A4
void fn_3_C2310(StadiumModel* model, Mtx m) {
    Mtx world;
    Mtx local;
    StadiumModelNode* root;
    StadiumModelNode* child;

    CTRLBuildMatrix((Control*)lbl_3_bss_9D94, local);
    PSMTXConcat(m, local, world);
    root = model->root;
    child = root->firstChild;
    if (root->dispObj != NULL) {
        if (root->skinData != NULL) {
            fn_8003A8A0(root->dispObj, world, 1);
        } else {
            DOVARenderSkin(root->dispObj, world, root->skinMtxArray, root->skinInvTransposeMtxArray, 0,
                           NULL);
        }
    }
    for (; child != NULL; child = child->nextSibling) {
        if (child->dispObj != NULL) {
            DOSetWorldMatrix(child->dispObj, child->worldMtx);
            fn_8003A8A0(child->dispObj, world, 0);
        }
    }
}

// .text:0x000C23E0 size:0xC0 mapped:0x80701474
void fn_3_C23E0(void) {
    StadiumObject* obj;
    s32 i;

    fn_800BF058(fn_3_B8184);
    for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
        obj = &stadiumObjectCollision.objects[i];

        fn_3_B828C((s32)obj);
        if (i >= 1 && i < 0xB) {
            if (obj->hasShadow && obj->model != NULL) {
                obj->model->root->drawFlags = obj->nodeDrawFlags | 6;
                fn_800BDF70(obj->model);
            }
        }
    }
}

// .text:0x000C24A0 size:0x1A4 mapped:0x80701534
void fn_3_C24A0(void) {
    return;
}

// .text:0x000C2644 size:0x330 mapped:0x807016D8
void fn_3_C2644(void) {
    return;
}

// .text:0x000C2974 size:0x18 mapped:0x80701A08
void fn_3_C2974(void) {
    lbl_3_bss_9DE7 = 1;
    lbl_3_bss_9D82 = 1;
}

// .text:0x000C298C size:0x114 mapped:0x80701A20
void fn_3_C298C(void) {
    CastleFireEmitterScene* scene = (CastleFireEmitterScene*)currentDrawingItem;
    u32 i;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED || g_GameLogic.gameStatus >= GAME_STATUS_MINIGAME_POST_MENU) {
            if (g_Minigame._1A40 != 0 && g_Minigame._1A38 == 0) {
                removeCurrentDrawingItem();
            }
        }
    } else {
        if (g_GameLogic.exitingToMenu != 0 || *((u8*)&g_d_GameSettings + 0x13) != 0) {
            removeCurrentDrawingItem();
        }
    }
    for (i = 0; i < 6; i++) {
        CastleFlameEmitter* handle = scene->handles[i];

        if (handle == NULL || handle->_08 == 0) {
            scene->handles[i] = allocParticleEffect(fn_3_C30F0, 0x80, 0, 0x15, TRUE, 0);
            if (scene->handles[i] != NULL) {
                fn_3_C366C(scene->handles[i], i);
            }
        }
    }
}

// .text:0x000C2AA0 size:0x1E0 mapped:0x80701B34
void fn_3_C2AA0(void) {
    return;
}

// .text:0x000C2C80 size:0x25C mapped:0x80701D14
void fn_3_C2C80(void) {
    return;
}

// .text:0x000C2EDC size:0x214 mapped:0x80701F70
void fn_3_C2EDC(void) {
    return;
}

// .text:0x000C30F0 size:0x57C mapped:0x80702184
void fn_3_C30F0(void) {
    return;
}

// .text:0x000C366C size:0x35C mapped:0x80702700
void fn_3_C366C(void* handlePtr, u8 idx) {
    CastleFlameEmitter* handle = (CastleFlameEmitter*)handlePtr;
    s16 i = 0;
    CastleFlameParticle* p = handle->particles;
    f32 ang;
    f32 alpha;

    handle->_10 = lbl_3_bss_9F0C[0];
    handle->origin = lbl_3_rodata_202C[idx];
    handle->kind = idx;
    alpha = 255.0f;

    for (; p != NULL; p = p->next) {
        ang = const_pi_or_180 * (f32)(rand() % 360);
        p->velX = 0.01 * cosf_kludge(ang);
        p->velZ = 0.01 * sinf_kludge(ang);
        p->_14 = 0.08f;
        p->_48 = i;
        p->scale = 0.5f;
        p->scale = p->scale + (f64)((u32)rand() % 2500) / 1000.0;
        p->_38 = p->scale;
        p->_3C = 2.0 * p->scale;
        p->_20 = (f64)(rand() % 101) / 100.0;
        p->origin.x = handle->origin.x;
        p->origin.y = handle->origin.y;
        p->origin.z = handle->origin.z;
        p->_40 = lbl_3_rodata_2028[0];
        p->_41 = lbl_3_rodata_2028[1];
        p->_42 = lbl_3_rodata_2028[2];
        p->alpha = alpha;
        p->alphaByte = alpha;
        p->_4F = p->_4A = rand() % 24 + 0x48;
        p->_4D = 0x1D;
        p->_4E = 0;
        i += 4;
    }
}

// .text:0x000C39C8 size:0x70 mapped:0x80702A5C
void bowserCastleSomething(void) {
    u32 i;

    for (i = 0; i < 6; i++) {
        void* handle = allocParticleEffect(fn_3_C30F0, 0x80, 0, 0x15, TRUE, 0);
        if (handle != NULL) {
            fn_3_C366C(handle, i);
        }
    }
}

// .text:0x000C3A38 size:0x1F4 mapped:0x80702ACC
void thwomp_screenShake(void) {
    return;
}

// .text:0x000C3C2C size:0x268 mapped:0x80702CC0
void fn_3_C3C2C(void) {
    return;
}

// .text:0x000C3E94 size:0xDC mapped:0x80702F28
void fn_3_C3E94(Vec* p, int idx) {
    s16 sx;
    s16 sy;

    fn_800528C0(p->x, p->y, p->z, &sx, &sy);
    ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + idx].object)->pos.x = sx;
    ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + idx].object)->pos.y = sy;
    ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + idx].object)->pos.z = 0.0f;
}

// .text:0x000C3F70 size:0xF8 mapped:0x80703004
void fn_3_C3F70(StadiumObject* obj) {
    CastleMaterialRoot* root = (CastleMaterialRoot*)obj->model->root;
    u32 i;

    if (lbl_3_bss_9D88++ > 4) {
        lbl_3_data_177F0++;
        if (lbl_3_data_177F0 > 0x13) {
            lbl_3_data_177F0 = 4;
        }
        lbl_3_bss_9D88 = 0;
    }
    if (lbl_3_bss_9D88 != 0) {
        return;
    }
    for (i = 0; i < root->groupCount; i++) {
        CastleMaterialListHolder* holder = root->groups[i]->holder;

        if (holder != NULL) {
            CastleMaterialEntry* entry = holder->list->entries;
            u32 j;

            for (j = 0; j < holder->list->count; entry++, j++) {
                if (entry->kind == 1) {
                    entry->animState &= ~0x1FFF;
                    entry->animState |= lbl_3_data_177F0;
                }
            }
        }
    }
}

// .text:0x000C4068 size:0x84 mapped:0x807030FC
void fn_3_C4068(StadiumObject* obj) {
    CastleModelRoot* root = (CastleModelRoot*)obj->model->root;
    CastleMaterialFlags* mat = root->next->flameMat->next->next->next;
    u16 value = mat->animState & 0x1FFF;

    if (lbl_3_bss_9D84++ > 4) {
        value++;
        if (value > 0x13) {
            value = 4;
        }
        lbl_3_bss_9D84 = 0;
    }
    mat->animState &= ~0x1FFF;
    mat->animState |= value;
}

// .text:0x000C40EC size:0x60 mapped:0x80703180
void fn_3_C40EC(StadiumObject* obj) {
    CastleModelRoot* root = (CastleModelRoot*)obj->model->root;
    CastleMaterialFlags* mat = root->next->flameMat->next->next->next;

    if (((CastleHazardObj*)obj)->hazardType != 6) {
        mat->animState &= ~0x1FFF;
        mat->animState |= 0x19;
    } else {
        mat->animState &= ~0x1FFF;
        mat->animState |= 0x1A;
    }
}

// .text:0x000C414C size:0x158 mapped:0x807031E0
void bowserCastleStarPadsContaactFn(int offset) {
    StadiumObject* obj = &stadiumObjectCollision.objects[offset];
    Vec trans;
    BOOL awarded = FALSE;

    CTRLGetTranslation((Control*)obj, &trans.x, &trans.y, &trans.z);
    if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_FIELDED) {
        if (((CastleHazardObj*)obj)->hazardType == 5) {
            if (inningSetting.starSkillsSetting != 0) {
                stadiumStarAwarded(trans.x, trans.y - 5.0f, trans.z);
                ((CastleHazardObj*)obj)->hazardType = 6;
                awarded = TRUE;
            }
        } else if (((CastleHazardObj*)obj)->hazardType == 4) {
            if (inningSetting.starSkillsSetting != 0) {
                stadiumStarAwarded(trans.x, trans.y, trans.z - 5.0f);
                ((CastleHazardObj*)obj)->hazardType = 6;
                awarded = TRUE;
            }
        }
    }
    if (awarded) {
        int idx = (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 6;

        lbl_3_bss_9E48[idx] = 1;
        lbl_3_bss_9DE8[idx].x = g_Ball.AtBat_Contact_BallPos.x;
        lbl_3_bss_9DE8[idx].y = -g_Ball.AtBat_Contact_BallPos.y;
        lbl_3_bss_9DE8[idx].z = g_Ball.AtBat_Contact_BallPos.z;
    }
}

// .text:0x000C42A4 size:0x1A8 mapped:0x80703338
void stadiumObjCollision_Castle(void) {
    return;
}

// .text:0x000C444C size:0x2D8 mapped:0x807034E0
void fn_3_C444C(void) {
    return;
}

// .text:0x000C4724 size:0x1AC mapped:0x807037B8
void fn_3_C4724(void) {
    return;
}

// .text:0x000C48D0 size:0x2B0 mapped:0x80703964
void fn_3_C48D0(void) {
    return;
}

// .text:0x000C4B80 size:0x174 mapped:0x80703C14
void fn_3_C4B80(void) {
    camera_803c639c_s* cam;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    GXSetProjection(cam->proj, GX_PERSPECTIVE);
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

// .text:0x000C4CF4 size:0x20C mapped:0x80703D88
void fn_3_C4CF4(void) {
    return;
}

// .text:0x000C4F00 size:0x404 mapped:0x80703F94
void fn_3_C4F00(void) {
    return;
}

// .text:0x000C5304 size:0x1CC mapped:0x80704398
void fn_3_C5304(void) {
    return;
}

// .text:0x000C54D0 size:0x218 mapped:0x80704564
void fn_3_C54D0(void) {
    return;
}

// .text:0x000C56E8 size:0x294 mapped:0x8070477C
void fn_3_C56E8(void) {
    return;
}

// .text:0x000C597C size:0x364 mapped:0x80704A10
void fn_3_C597C(void) {
    return;
}

// .text:0x000C5CE0 size:0xFC mapped:0x80704D74
BOOL castleFireballMaybe(StadiumObject* obj) {
    Vec off = { 0.0f, 0.0f, 0.0f };
    Vec diff;
    f32 dist;
    u32 i;

    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_GameLogic.playOver) {
        return FALSE;
    }
    for (i = 0; i < 9; i++) {
        memset(&off, 0, sizeof(Vec));
        getAnimationCollisionOffset(i, 4, &off);
        PSVECSubtract(&off, &((CastleFireballTarget*)obj)->anchorPos, &diff);
        dist = PSVECMag(&diff);
        if (dist <= 2.6f) {
            maybeCastleFireballBurn(i, 1);
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x000C5DDC size:0x480 mapped:0x80704E70
void bowserCastleRelated(void) {
    return;
}

// .text:0x000C625C size:0x174 mapped:0x807052F0
BOOL fn_3_C625C(StadiumObject* obj) {
    Vec target = ((CastleFireballTarget*)obj)->anchorPos;
    Vec diff;
    f32 dist;
    u8 stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    if (g_Ball.ballState == BALL_STATE_HELD) {
        return FALSE;
    }
    if (!((g_Ball.currentStarSwing2 == 11) | (g_Ball.currentStarSwing2 == 12))) {
        return FALSE;
    }
    target.y = target.y * -1.0f;
    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, &target, &diff);
    dist = PSVECMag(&diff);
    if (dist <= 2.6f) {
        stadiumID = g_d_GameSettings.StadiumID;
        vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[4]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 4];
        voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 2, vol, 0x3f, 0);
        val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[5]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 5];
        sndFXCtrl(voice, 0x5b, val);
        return TRUE;
    }
    return FALSE;
}

// .text:0x000C63D0 size:0xDFC mapped:0x80705464
void flameControl(void) {
    return;
}

// .text:0x000C71CC size:0x278 mapped:0x80706260
void stadiumObjRelated_Castle(void) {
    return;
}

// .text:0x000C7444 size:0x58 mapped:0x807064D8
void fn_3_C7444(StadiumObject* obj) {
    CastleModelRoot* root = (CastleModelRoot*)obj->model->root;
    CastleMaterialFlags* mat = root->next->thwompMat->next->next->next;
    BOOL hasBounced = ((CastleHazardObj*)obj)->hasBounced;

    switch (hasBounced) {
    case 0:
        mat->animState &= ~0x1FFF;
        mat->animState |= 2;
        break;
    default:
        mat->animState &= ~0x1FFF;
        break;
    }
}

// .text:0x000C749C size:0x11C mapped:0x80706530
void thwomp_bounceOffSoundAndVisualFx(void) {
    int idx = (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 2;
    u8 stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    lbl_3_bss_9E48[idx] = 1;
    lbl_3_bss_9DE8[idx].x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_3_bss_9DE8[idx].y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_3_bss_9DE8[idx].z = g_Ball.AtBat_Contact_BallPos.z;

    stadiumID = g_d_GameSettings.StadiumID;
    vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD ? lbl_3_data_84B8[8]
                                                                    : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 8];
    voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 4, vol, 0x3f, 0);
    val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
              ? lbl_3_data_84B8[9]
              : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 9];
    sndFXCtrl(voice, 0x5b, val);
}

// .text:0x000C75B8 size:0x1F4 mapped:0x8070664C
void thwomp_smokeRelated(void) {
    return;
}

// .text:0x000C77AC size:0x260 mapped:0x80706840
void fn_3_C77AC(void) {
    return;
}

// .text:0x000C7A0C size:0x650 mapped:0x80706AA0
void thwomp_slamControl(void) {
    return;
}

// .text:0x000C805C size:0x1E0 mapped:0x807070F0
void fn_3_C805C(void) {
    return;
}

// .text:0x000C823C size:0x78 mapped:0x807072D0
TriangleGroup* fn_3_C823C(int offset, Mtx m) {
    StadiumObject* obj = &stadiumObjectCollision.objects[offset];

    CTRLBuildMatrix((Control*)obj, m);
    if (((CastleHazardObj*)obj)->hazardType == 5) {
        m[1][3] = 0.002f;
    }
    return stadiumObjectCollision.objects[offset].triangles;
}

// .text:0x000C82B4 size:0x39C mapped:0x80707348
void fn_3_C82B4(void) {
    return;
}

// .text:0x000C8650 size:0xD2C mapped:0x807076E4
void loadBowserCastle(void) {
    return;
}

