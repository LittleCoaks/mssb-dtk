#include "game/stadium/stadium_framework.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/gx.h"
#include "Dolphin/stl.h"
#include "Unknown/File_0x800acf14.h"
#include "static/UnknownHomes_Static.h"
#include "stl/math.h"
#include "Dolphin/rand.h"
#include "game/sound/m_sound.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x800b4d64.h"
#include "Unknown/File_0x8001e460.h"
#include "Unknown/File_0x80023b90.h"
#include "Unknown/File_0x80034220.h"
#include "Unknown/File_0x8003452c.h"
#include "Unknown/File_0x800348c8.h"
#include "Unknown/File_0x800bd3a0.h"
#include "Unknown/File_0x800bd3cc.h"
#include "Unknown/File_0x800bd3ec.h"
#include "Unknown/File_0x8003a538.h"
#include "Unknown/File_0x800bf038.h"
#include "Unknown/File_0x800bfe90.h"
#include "Unknown/File_0x800b508c.h"
#include "Unknown/File_0x800bcd60.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x800b9a9c.h"
#include "Unknown/File_0x800bd2b0.h"
#include "Unknown/File_0x800bd300.h"
#include "Unknown/File_0x800bda94.h"
#include "Unknown/File_0x800bd190.h"
#include "Unknown/File_0x800bea04.h"
#include "game/stadium/stadium_bowser_castle.h"
#include "game/stadium/stadium_yoshi_park.h"
#include "game/stadium/stadium_dk_jungle.h"
#include "game/stadium/stadium_toy_field.h"
#include "game/stadium/stadium_wario_palace.h"

typedef struct _StadiumBounds {
    Vec min;
    Vec max;
    f32 unused[6];
} StadiumBounds;

f32 lbl_3_data_11178[5] = {18.0f, 90.0f, 162.0f, 234.0f, 306.0f};

extern s8 lbl_803C6CF8[0x716];
extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;
typedef struct _StadiumPropEntry {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ void* handle;
    /*0x38*/ u8 _38[0x58];
} StadiumPropEntry; // size: 0x90

typedef struct _StadiumLightInput {
    Vec pos;
    GXColor color;
} StadiumLightInput;

extern struct {
    /*0x0000*/ u8 _00[8];
    /*0x0008*/ void* stadiumFile;
    /*0x000C*/ u8 _0C[0x60];
    /*0x006C*/ StadiumPropEntry* propEntries;
    /*0x0070*/ u8 _70[0x3088 - 0x70];
    /*0x3088*/ u8 objectsInitialized;
    /*0x3089*/ u8 _3089[0x3154 - 0x3089];
} hugeAnimStruct;
extern u8 inputParams[14][0x2c];
extern StadiumLightInput lbl_80367318[4];
extern u8 StadiumPropFiles[7][0x10];

static void (*cleanupFunction[4])(void);
static u8 lbl_3_bss_1940[0x8000];
static StadiumBounds minX;
static s32 lbl_3_bss_190C;
static f32 lbl_3_bss_1908;
static StadiumObject* stadiumObjBackup;
static u8 lbl_3_bss_1902;
static u8 lbl_3_bss_1901;

// .text:0x000B7FC8 size:0x108 mapped:0x806F705C
void randomizeAndLoadSoundEffect(int soundId, int arg) {
    Vec pos = {0.0f, 0.0f, 37.0f};
    f32 angle = 0.017453292f * lbl_3_data_11178[rand() % 5];

    pos.x = 100.0f * (f32)cos(angle) + pos.x;
    pos.y += -30.0f;
    pos.z = 100.0f * (f32)sin(angle) + pos.z;
    initializeStadiumObjectEmitter(soundId, &pos, NULL, arg);
}

// .text:0x000B80D0 size:0xB4 mapped:0x806F7164
void maybeYoshiParkGXRelated(void) {
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

// .text:0x000B8184 size:0xF8 mapped:0x806F7218
void fn_3_B8184(StadiumModel* model, Mtx m) {
    Mtx world;
    Mtx local;
    StadiumModelNode* root;
    StadiumModelNode* child;

    CTRLBuildMatrix((Control*)lbl_3_bss_190C, local);
    if (local[1][3] > 0.0f && g_d_GameSettings.StadiumID == STADIUM_ID_BOWSERS_CASTLE) {
        return;
    }
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

// .text:0x000B827C size:0x10 mapped:0x806F7310
s32 fn_3_B827C(void) {
    return lbl_3_bss_190C;
}

// .text:0x000B828C size:0xC mapped:0x806F7320
void fn_3_B828C(s32 value) {
    lbl_3_bss_190C = value;
}

// .text:0x000B8298 size:0x17C mapped:0x806F732C
void fn_3_B8298(void) {
    Mtx local;
    Mtx world;
    u32 i;
    StadiumModelNode* root;
    StadiumModelNode* child;
    StadiumModel* model;
    MtxPtr view;
    StadiumObject* obj;
    ShadowState* shadow;

    switch (g_d_GameSettings.StadiumID) {
    case STADIUM_ID_YOHSI_PARK:
        updateFunctionPtr(maybeYoshiParkGXRelated);
        break;
    }
    for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
        obj = &stadiumObjectCollision.objects[i];
        if (obj->hasShadow && obj->model != NULL && obj->shadowEnabled != 0) {
            lbl_3_bss_190C = (s32)obj;
            shadow = ShouldDrawShadows();
            model = obj->model;
            view = shadow->camera->viewMtx;
            CTRLBuildMatrix((Control*)lbl_3_bss_190C, local);
            if (local[1][3] > 0.0f && g_d_GameSettings.StadiumID == STADIUM_ID_BOWSERS_CASTLE) {
                continue;
            }
            PSMTXConcat(view, local, world);
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
    }
    updateFunctionPtr(NULL);
}

// .text:0x000B8414 size:0x50 mapped:0x806F74A8
void storeBoundingBoxCoordinates(Vec* minDst, Vec* maxDst) {
    memcpy(minDst, &minX.min, sizeof(Vec));
    memcpy(maxDst, &minX.max, sizeof(Vec));
}

// .text:0x000B8464 size:0x110 mapped:0x806F74F8
void transformVectorsUpdateBoundingBox(Mtx m, StadiumMeshData* mesh) {
    int count;
    StadiumVertexGroup* p = mesh->groups;
    Vec out;
    u32 n;

    while (TRUE) {
        n = p->vertexCount;
        if (n == 0) {
            break;
        }
        if (p->isTriangleStrip != 0) {
            count = n + 2;
        } else {
            count = n * 3;
        }
        p = (StadiumVertexGroup*)p->vertices;
        do {
            PSMTXMultVec(m, (Vec*)p, &out);
            p = (StadiumVertexGroup*)((StadiumVertex*)p + 1);
            if (minX.min.x > out.x) {
                minX.min.x = out.x;
            }
            if (minX.min.y > out.y) {
                minX.min.y = out.y;
            }
            if (minX.min.z > out.z) {
                minX.min.z = out.z;
            }
            if (minX.max.x < out.x) {
                minX.max.x = out.x;
            }
            if (minX.max.y < out.y) {
                minX.max.y = out.y;
            }
            if (minX.max.z < out.z) {
                minX.max.z = out.z;
            }
        } while (--count != 0);
    }
}

// .text:0x000B8574 size:0x34 mapped:0x806F7608
void initBoundingBoxLimits(void) {
    minX.min.x = -10000.0f;
    minX.min.y = -10000.0f;
    minX.min.z = -10000.0f;
    minX.max.x = 10000.0f;
    minX.max.y = 10000.0f;
    minX.max.z = 10000.0f;
}

// .text:0x000B85A8 size:0x34 mapped:0x806F763C
s32 calculateHazardDataAddress(s32 idx, void** out) {
    *out = &stadiumObjectCollision.vertexData[stadiumObjectCollision.vertexOffsets[idx]];
    return stadiumObjectCollision.hazardData[idx];
}

// .text:0x000B85DC size:0x7C mapped:0x806F7670
void CopyOutVecSrcDst(int idx, Vec* a, Vec* b) {
    memcpy(a, &((Vec*)stadiumObjectCollision.vertexDataArray)[idx * 2], sizeof(Vec));
    memcpy(b, &((Vec*)stadiumObjectCollision.vertexDataArray)[idx * 2 + 1], sizeof(Vec));
}

// .text:0x000B8658 size:0x24 mapped:0x806F76EC
s32 fn_3_B8658(const f32* a, const f32* b) {
    f32 x = *a;
    f32 y = *b;
    if (x < y) {
        return -1;
    }
    return x > y;
}

// .text:0x000B867C size:0x1AC mapped:0x806F7710
void fn_3_B867C(Mtx view, StadiumDrawOrder* order) {
    StadiumDrawOrder* back;
    Vec pos;
    StadiumDrawOrder* front;
    StadiumDrawOrder* p;
    int remaining;
    int count;
    StadiumObject* obj;
    int i;

    if (stadiumObjectCollision.gameStatusIsLiveBall) {
        count = 0;
        p = order;
        i = stadiumObjectCollision.objectCount - 1;
        obj = &stadiumObjectCollision.objects[i];
        do {
            if (!obj->hasShadow) {
                p->depth = -512.0f;
                count++;
                p->index = i;
                p++;
            }
            obj--;
        } while (i-- != 0);

        remaining = stadiumObjectCollision.objectCount;
        i = stadiumObjectCollision.objectCount - 1;
        obj = &stadiumObjectCollision.objects[i];
        back = order + stadiumObjectCollision.objectCount;
        front = order + count;
        do {
            if (obj->hasShadow) {
                if (obj->fadeByDepth) {
                    CTRLGetTranslation((Control*)obj, &pos.x, &pos.y, &pos.z);
                    PSMTXMultVec(view, &pos, &pos);
                    remaining--;
                    back[-1].depth = pos.z;
                    back[-1].index = i;
                    back--;
                } else {
                    front->depth = -512.0f;
                    front->index = i;
                    front++;
                }
            }
            obj--;
        } while (i-- != 0);

        p = allocateAlignedMemoryBlock(32, (stadiumObjectCollision.objectCount - remaining) * sizeof(StadiumDrawOrder));
        fn_800C07BC(order + remaining, p, stadiumObjectCollision.objectCount - remaining, sizeof(StadiumDrawOrder),
                    fn_3_B8658);
        unkLoadingCleanupRelated(p);
    } else {
        p = order;
        for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
            p->index = i;
            p++;
        }
    }
}

// .text:0x000B8828 size:0x3E0 mapped:0x806F78BC
void loadStadiumObjectVisuals(Mtx view, int flag, u32 pass) {
    StadiumLightBlock lightCopy;
    Mtx local;
    Mtx world;
    Vec dir;
    GXColor ambient;
    GXColor restore;
    GXColor lightColor;
    int i;
    int j;
    f32 mag;
    StadiumObject* obj;
    StadiumLightInput* input;

    ambient = *(GXColor*)&inputParams[g_d_GameSettings._54][0x28];
    restore = ambient;
    input = lbl_80367318;
    if (hugeAnimStruct.objectsInitialized) {
        GXSetCullMode(GX_CULL_BACK);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        for (i = 0; i < 4; i++) {
            if (stadiumObjectCollision.lights[i] != NULL) {
                LITInitAttn(stadiumObjectCollision.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                LITInitPos(stadiumObjectCollision.lights[i], input[i].pos.x, input[i].pos.y, input[i].pos.z);
                lightColor = input[i].color;
                LITInitColor(stadiumObjectCollision.lights[i], &lightColor);
                dir.x = input[i].pos.x;
                dir.y = input[i].pos.y;
                dir.z = input[i].pos.z;
                mag = PSVECMag(&dir);
                if (mag != 0.0f) {
                    PSVECNormalize(&dir, &dir);
                    LITInitDir(stadiumObjectCollision.lights[i], dir.x, dir.y, dir.z);
                }
            }
        }
        GXSetProjection(fn_80052768_getCamera(returnsCurrentMode())->proj, GX_PERSPECTIVE);
        for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
            obj = &stadiumObjectCollision.objects[stadiumObjectCollision.objectScratch[i].index];
            if (obj->hasShadow && obj->model != NULL && pass == obj->drawPass) {
                if (pass == 1 && flag != obj->fadeByDepth) {
                    continue;
                }
                PSMTXConcat(view, obj->worldMtx, world);
                if (obj->fadeByDepth) {
                    ambient.a = (u8)(obj->alpha * stadiumObjectCollision.objectScratch[i].depth);
                } else {
                    ambient.a = obj->alpha;
                }
                adjustLightingParams(1, ambient);
                for (j = 0; j < 4; j++) {
                    LITXForm(stadiumObjectCollision.lights[j], view);
                }
                CTRLBuildMatrix((Control*)obj, local);
                PSMTXInverse(local, local);
                lightCopy = *stadiumObjectCollision.lights[0];
                PSMTXMultVecSR(local, &lightCopy.dir, &lightCopy.dir);
                setLITLightPtr(&lightCopy);
                obj->model->root->drawFlags = obj->nodeDrawFlags;
                if (obj->customZMode) {
                    GXSetZMode(obj->zCompare, obj->zAlways ? GX_ALWAYS : GX_LEQUAL, obj->zUpdate);
                } else if (flag != 0) {
                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                } else {
                    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
                }
                if (obj->preDraw != NULL) {
                    obj->preDraw(obj);
                }
                sknRelated(obj->model, world);
                for (j = 0; j < 16; j++) {
                    if (lbl_3_data_11168[j] != 0) {
                        GXSetTevDirect((GXTevStageID)j);
                        lbl_3_data_11168[j] = 0;
                    }
                }
                adjustLightingParams(1, restore);
                if (obj->postDraw != NULL) {
                    obj->postDraw(obj);
                }
            }
        }
        setLITLightPtr(stadiumObjectCollision.lights[0]);
    }
}

// .text:0x000B8C08 size:0x424 mapped:0x806F7C9C
void fn_3_B8C08(Mtx view) {
    Mtx local;
    Mtx world;
    StadiumObject* obj;
    StadiumDrawOrder* entry;
    int i;
    f32 nearZ;

    if (stadiumObjectCollision.stadiumData == NULL) {
        return;
    }
    fn_3_38E8(loadStadiumObjectVisuals);
    fn_8001E460(loadStadiumObjectVisuals);
    for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
        obj = &stadiumObjectCollision.objects[i];
        if (obj->hasShadow && obj->model != NULL) {
            StadiumModelNode* root = obj->model->root;
            fn_800B2BFC(root, obj->model->_64, obj->model->_66);
            fn_800B3F20(root);
            fn_800B313C(root);
            CTRLBuildMatrix((Control*)obj, local);
            PSMTXCopy(local, obj->worldMtx);
            PSMTXConcat(view, obj->worldMtx, world);
            if (obj->animActive != 0) {
                if (obj->animIndex == -1) {
                    fn_800117CC(obj->worldMtx, view, obj->worldMtx);
                } else {
                    fn_800116DC(obj->model, world, obj->animIndex);
                }
            }
            obj->nodeDrawFlags = (obj->nodeDrawFlags & 0xFC) | fn_800B3C04(0, obj->model->root, world);
            if (obj->shadowEnabled != 0) {
                Vec origin = {0.0f, 0.0f, 0.0f};
                PSMTXMultVec(local, &origin, &origin);
                setVectors(origin);
            }
            if (obj->effect != NULL && lbl_80366158._28 == 0 && obj->nodeDrawFlags != 0) {
                fn_80024DB0(obj->effect->state);
                fn_80024FA4(obj->model, obj->effect->handle, obj->effect->state, -1);
            }
        }
    }
    if (g_d_GameSettings.StadiumID == STADIUM_ID_WARIO_PALACE &&
        g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        processPalaceObjectCollisions(view, stadiumObjectCollision.objectScratch);
    } else if (g_d_GameSettings.StadiumID == STADIUM_ID_DK_JUNGLE &&
               g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        processJungleObjectCollisions(view, stadiumObjectCollision.objectScratch);
    } else if (g_d_GameSettings.StadiumID == STADIUM_ID_TOY_FIELD) {
        processToyFieldObjectCollisions(view, stadiumObjectCollision.objectScratch);
    } else {
        fn_3_B867C(view, stadiumObjectCollision.objectScratch);
        if (stadiumObjectCollision.gameStatusIsLiveBall) {
            Vec v;
            if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
                lbl_3_bss_1908 = 0.25f;
            } else {
                lbl_3_bss_1908 = 0.0f;
            }
            memcpy(&v, &g_Ball, sizeof(Vec));
            PSMTXMultVec(view, &v, &v);
            for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
                entry = &stadiumObjectCollision.objectScratch[i];
                if (stadiumObjectCollision.objects[entry->index].hasShadow) {
                    nearZ = 2.0f + v.z;
                    if (entry->depth < nearZ) {
                        entry->depth = 1.0f;
                    } else if (entry->depth > 22.0f + v.z) {
                        entry->depth = 1.0 - (1.0f - lbl_3_bss_1908);
                    } else {
                        entry->depth = 1.0 - (1.0f - lbl_3_bss_1908) * ((entry->depth - nearZ) / 20.0f);
                    }
                }
            }
        } else {
            for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
                stadiumObjectCollision.objectScratch[i].depth = 1.0f;
            }
        }
    }
}

// .text:0x000B902C size:0x60 mapped:0x806F80C0
void fn_3_B902C(void) {
    if (stadiumObjBackup != NULL) {
        memcpy(stadiumObjectCollision.objects, stadiumObjBackup,
               stadiumObjectCollision.objectCount * sizeof(StadiumObject));
        fn_800ACFB0(stadiumObjBackup);
        stadiumObjBackup = NULL;
    }
}

// .text:0x000B908C size:0x98 mapped:0x806F8120
void initStadiumObjectData(void) {
    if (stadiumObjBackup == NULL) {
        stadiumObjBackup =
            _OSAllocFromHeap(0x20, stadiumObjectCollision.objectCount * sizeof(StadiumObject));
        memcpy(stadiumObjBackup, stadiumObjectCollision.objects,
               stadiumObjectCollision.objectCount * sizeof(StadiumObject));
    }
    memcpy(stadiumObjectCollision.objects, stadiumObjectCollision.objectsRelated,
           stadiumObjectCollision.objectCount * sizeof(StadiumObject));
    stadiumObjectCollision.rngConfig = stadiumObjectCollision.rngConfigSaved;
}

// .text:0x000B9124 size:0x48 mapped:0x806F81B8
void updateStadiumObjCollision(void) {
    memcpy(stadiumObjectCollision.objectsRelated, stadiumObjectCollision.objects,
           stadiumObjectCollision.objectCount * sizeof(StadiumObject));
    stadiumObjectCollision.rngConfigSaved = stadiumObjectCollision.rngConfig;
}

// .text:0x000B916C size:0x5C mapped:0x806F8200
int processStadiumObjectFunction(int stadiumId, int idx, int arg2, void* arg3) {
    if (idx < stadiumObjectCollision.objectCount) {
        if (stadiumObjectCollision.objects[idx].func != NULL) {
            return stadiumObjectCollision.objects[idx].func(idx, arg2, arg3);
        }
    }
}

// .text:0x000B91C8 size:0x1D4 mapped:0x806F825C
TriangleGroup* getStadiumHazardTriangles(int stadiumId, int offset, Mtx m) {
    if (stadiumId == STADIUM_ID_BOWSERS_CASTLE) {
        return fn_3_C823C(offset, m);
    } else if (stadiumId == STADIUM_ID_WARIO_PALACE) {
        if (g_Ball.AtBat_ContactResult >= BALL_RESULT_TYPE_FIELDED) {
            return NULL;
        }
        CTRLBuildMatrix((Control*)&stadiumObjectCollision.objects[offset], m);
        return stadiumObjectCollision.objects[offset].triangles;
    } else if (stadiumId == STADIUM_ID_YOHSI_PARK) {
        if ((g_Ball.currentStarSwing2 == 11) | (g_Ball.currentStarSwing2 == 12)) {
            return NULL;
        }
        return fn_3_E4BE8(offset, m);
    } else if (stadiumId == STADIUM_ID_PEACH_GARDEN) {
        if ((g_Ball.AtBat_ContactResult >= BALL_RESULT_TYPE_FIELDED) | (g_Ball.currentStarSwing2 == 11) |
            (g_Ball.currentStarSwing2 == 12)) {
            return NULL;
        }
        CTRLBuildMatrix((Control*)&stadiumObjectCollision.objects[offset], m);
        return stadiumObjectCollision.objects[offset].triangles;
    } else if (stadiumId == STADIUM_ID_DK_JUNGLE) {
        if (g_Ball.AtBat_ContactResult >= BALL_RESULT_TYPE_FIELDED) {
            return NULL;
        }
        return fn_3_F6504(offset, m);
    } else if (stadiumId == STADIUM_ID_TOY_FIELD) {
        return fn_3_E751C(offset, m);
    } else {
        CTRLBuildMatrix((Control*)&stadiumObjectCollision.objects[offset], m);
        return stadiumObjectCollision.objects[offset].triangles;
    }
}

// .text:0x000B939C size:0x28 mapped:0x806F8430
void updateGameStatusFlag(void) {
    stadiumObjectCollision.gameStatusIsLiveBall = g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL;
}

// .text:0x000B93C4 size:0x4 mapped:0x806F8458
void fn_3_B93C4(void) {
    return;
}

// .text:0x000B93C8 size:0x4 mapped:0x806F845C
void fn_3_B93C8(void) {
    return;
}

// .text:0x000B93CC size:0x140 mapped:0x806F8460
void hazardSimulationRelated(void) {
    int i;

    if (g_d_GameSettings._55 != 0) {
        return;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        stadiumObjectCollision.rngConfig = rand();
    }
    if (lbl_80366158._28 != 0) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            if (stadiumObjectCollision.updateFunc != NULL) {
                stadiumObjectCollision.updateFunc();
            }
        }
    } else {
        if (stadiumObjectCollision.preUpdateFunc != NULL) {
            stadiumObjectCollision.preUpdateFunc();
        }
        if (stadiumObjectCollision.updateFunc != NULL) {
            stadiumObjectCollision.updateFunc();
        }
        if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
            fn_800638CC();
        }
        for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
            StadiumObject* obj = &stadiumObjectCollision.objects[i];
            if (obj->callback != NULL) {
                obj->callback();
            }
        }
    }
}

// .text:0x000B950C size:0x4 mapped:0x806F85A0
void fn_3_B950C(void) {
    return;
}

// .text:0x000B9510 size:0x14 mapped:0x806F85A4
void fn_3_B9510(s32 idx) {
    lbl_3_data_11168[idx] = 1;
}

// .text:0x000B9524 size:0x10 mapped:0x806F85B8
void fn_3_B9524(void) {
    lbl_3_bss_1902 = 0;
}

// .text:0x000B9534 size:0xB8 mapped:0x806F85C8
void* fn_3_B9534(int w, int h, GXTexObj* obj) {
    if (lbl_3_bss_1902 != 0 || obj == NULL) {
        return NULL;
    }
    lbl_3_bss_1902 = 1;
    GXInitTexObj(obj, lbl_3_bss_1940, w, h, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    return lbl_3_bss_1940;
}

// .text:0x000B95EC size:0x1DC mapped:0x806F8680
void cleanupMinigameResources(void) {
    u8 n;

    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
    if (cleanupFunction[0] != NULL) {
        cleanupFunction[0]();
        cleanupFunction[0] = NULL;
    }
    if (g_d_GameSettings.minigamesEnabled) {
        fn_8001B200();
        if (stadiumObjectCollision.objectScratch != NULL) {
            fn_800ACFB0(stadiumObjectCollision.objectScratch);
        }
        if (stadiumObjectCollision.vertexDataArray != NULL) {
            fn_800ACFB0(stadiumObjectCollision.vertexDataArray);
        }
        if (stadiumObjectCollision.objectsRelated != NULL) {
            fn_800ACFB0(stadiumObjectCollision.objectsRelated);
        }
        if (stadiumObjectCollision.objects != NULL) {
            fn_800ACFB0(stadiumObjectCollision.objects);
        }
        if (hugeAnimStruct.propEntries != NULL) {
            for (n = stadiumObjectCollision.propCount; n != 0; n--) {
                fn_800B4278(hugeAnimStruct.propEntries[n - 1].handle);
            }
            fn_800ACFB0(hugeAnimStruct.propEntries);
            hugeAnimStruct.propEntries = NULL;
        }
        if (stadiumObjectCollision._34 != NULL) {
            fn_800ACFB0(stadiumObjectCollision._34);
        }
        for (n = 4; n != 0; n--) {
            if (stadiumObjectCollision.lights[n - 1] != NULL) {
                fn_800ACFB0(stadiumObjectCollision.lights[n - 1]);
            }
        }
        if (stadiumObjectCollision.stadiumData != NULL) {
            fn_800ACFB0(stadiumObjectCollision.stadiumData);
        }
        hugeAnimStruct.objectsInitialized = 0;
        fn_3_C1964();
        fn_3_16E328();
        fn_800528B4();
        setNullPtrForStadiumObjs();
        lbl_3_bss_1902 = 0;
        memset(&stadiumObjectCollision, 0, sizeof(stadiumObjectCollision));
        lbl_3_bss_1901 = 1;
    }
}

// .text:0x000B97C8 size:0x14 mapped:0x806F885C
void fn_3_B97C8(void (*func)(void)) {
    if (func != NULL) {
        cleanupFunction[0] = func;
    }
}

// .text:0x000B97DC size:0x10C mapped:0x806F8870
void actorSetAnimBank(ACTActor* act, u32 animBankId) {
    if (act == NULL || animBankId == 0) {
        return;
    }
    act->animBank = (void*)animBankId;
    act->sequenceNum = 0;
    act->animFrame = 0.0f;
    act->applyAnimation = TRUE;
    act->applyFrame = animBankId != 0;
    act->applySpeed = animBankId != 0;
    act->animTime = 0.0f;
    act->applyFlags = 3;
    act->animFrame = 0.0f;
    act->applyFrame = TRUE;
    act->animSpeed = 1.0f;
    act->applySpeed = TRUE;
    act->_68 = 0;
    act->applyAnimation = TRUE;
    if (act->applyAnimation) {
        ACTSetAnimation(act->actor, act->animBank, NULL, act->sequenceNum, 0.0f, act->animTime);
        setAllBoneEventFlags(act->actor, TRUE);
    }
    if (act->applyFrame) {
        setActorAnimFrame(act->actor, act->animFrame);
    }
    if (act->applySpeed) {
        fn_800B4C04(act->actor, act->animSpeed);
    }
    if (act->applyFlags & 1) {
        updateBoneParam(act->actor, act->applyFlags & 1);
    }
}

// .text:0x000B98E8 size:0xFC mapped:0x806F897C
void fn_3_B98E8(StadiumAnimData* d) {
    u32 i;

    for (i = 0; i < d->list->objectCount; i++) {
        StadiumAnimObject* obj = d->list->objects[i];
        obj->animRecord = _OSAllocFromHeap(0x20, sizeof(StadiumAnimRecord));
        obj->animRecord->frame = 0.0f;
        obj->animRecord->time = 0.0f;
        obj->animRecord->speed = 1.0f;
        obj->animRecord->_0C = 0;
        obj->animRecord->_10 = 0;
        obj->animRecord->_16 = 0;
        obj->animRecord->_17 = 1;
        obj->animRecord->_18 = 1;
        obj->animRecord->_14 = 0;
    }
}

// .text:0x000B99E4 size:0x1D0 mapped:0x806F8A78
void calledWhileMatchIsLoading(void) {
    StadiumLightInput input;
    GXColor color;
    void* light;
    void* stadiumData;
    int stadiumType;
    int i;

    if (lbl_803C6CF8[0x715] == 1) {
        stadiumObjectCollision.objectsLoaded = 0;
        stadiumData = hugeAnimStruct.stadiumFile;
        stadiumType = g_d_GameSettings.StadiumID;
        setNullPtrForStadiumObjs();
        memset(&stadiumObjectCollision, 0, sizeof(stadiumObjectCollision));
        fn_3_35E4(0);
        if (stadiumData != NULL) {
            for (i = 0; i < 4; i++) {
                characterLightingRelated(&inputParams[g_d_GameSettings._54][i * 10], &input);
                LITAlloc(&light);
                LITInitAttn(light, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                LITInitPos(light, input.pos.x, input.pos.y, input.pos.z);
                color = input.color;
                LITInitColor(light, &color);
                stadiumObjectCollision.lights[i] = light;
            }
            stadiumObjectCollision.stadiumData = stadiumData;
            stadiumObjectCollision._08 = NULL;
            stadiumObjectCollision._0C = NULL;
            callStadiumPointerFun[stadiumType](stadiumData);
            stadiumObjectCollision.objectScratch =
                _OSAllocFromHeap(4, stadiumObjectCollision.objectCount << 3);
            fn_8001B214(fn_3_B8298);
            stadiumObjectCollision.rngConfig = rand();
            hugeAnimStruct.objectsInitialized = 1;
            lbl_3_bss_1901 = 0;
        }
        removeCurrentDrawingItem();
    }
}

// .text:0x000B9BB4 size:0x1B4 mapped:0x806F8C48
BOOL loadStadiumObjects(int stadiumId) {
    if (lbl_803C6CF8[0x715] == 1) {
        switch (stadiumId) {
        case STADIUM_ID_MARIO_STADIUM:
            hugeAnimStruct.stadiumFile = ARAMTransfer(StadiumPropFiles[STADIUM_ID_MARIO_STADIUM], 0, 0, 0);
            break;
        case STADIUM_ID_BOWSERS_CASTLE:
            hugeAnimStruct.stadiumFile = ARAMTransfer(StadiumPropFiles[STADIUM_ID_BOWSERS_CASTLE], 0, 0, 0);
            break;
        case STADIUM_ID_WARIO_PALACE:
            hugeAnimStruct.stadiumFile = ARAMTransfer(StadiumPropFiles[STADIUM_ID_WARIO_PALACE], 0, 0, 0);
            break;
        case STADIUM_ID_YOHSI_PARK:
            hugeAnimStruct.stadiumFile = ARAMTransfer(StadiumPropFiles[STADIUM_ID_YOHSI_PARK], 0, 0, 0);
            break;
        case STADIUM_ID_PEACH_GARDEN:
            hugeAnimStruct.stadiumFile = ARAMTransfer(StadiumPropFiles[STADIUM_ID_PEACH_GARDEN], 0, 0, 0);
            break;
        case STADIUM_ID_DK_JUNGLE:
            hugeAnimStruct.stadiumFile = ARAMTransfer(StadiumPropFiles[STADIUM_ID_DK_JUNGLE], 0, 0, 0);
            break;
        case STADIUM_ID_TOY_FIELD:
            hugeAnimStruct.stadiumFile = ARAMTransfer(StadiumPropFiles[STADIUM_ID_TOY_FIELD], 0, 0, 0);
            break;
        default:
            return -1;
        }
        insertGraphicDrawingFunction(calledWhileMatchIsLoading, 0);
        stadiumObjectCollision.objectsLoaded = TRUE;
        return TRUE;
    }
    return FALSE;
}

// .text:0x000B9D68 size:0x250 mapped:0x806F8DFC
void processStadiumFileObjects(u8* types, int count, u8* base, u32* out) {
    u32* outPtr = out;
    void* tex = NULL;
    void* skn = NULL;
    int k = 0;

    do {
        if (out != NULL) {
            *outPtr = k;
        }
        switch (*types) {
        case 1:
            tex = base + ((u32*)base)[k++];
            convertTextureHeader(tex);
            break;
        case 2:
        case 3:
        case 4:
        case 5: {
            u8* layout = base + ((u32*)base)[k++];
            u8* geo = base + ((u32*)base)[k++];
            if ((u8)(*types - 2) > 1) {
                ANIMGet(base + ((u32*)base)[k++]);
            }
            if (*types == 3 || *types == 5) {
                skn = base + ((u32*)base)[k++];
            }
            LoadActorLayout(layout);
            convertGeometryAndSknHeader(geo, skn);
            skn = NULL;
            UpdateTexturePalettePointers(geo, tex);
            haveActLayoutPointToGeoHeader(layout, geo);
            break;
        }
        case 6: {
            u8* hdr = base + ((u32*)base)[k++];
            int n = *(u16*)hdr;
            u32* entry = (u32*)(hdr + 4);
            for (; n >= 0; n--) {
                *entry++ += (u32)hdr;
            }
            break;
        }
        case 7:
            ANIMGet(base + ((u32*)base)[k++]);
            break;
        case 8:
        case 9:
        default:
            k++;
            break;
        }
        outPtr++;
        types++;
    } while (--count != 0);
    while (k-- != 0) {
        ((u32*)base)[k] += (u32)base;
    }
}

// .text:0x000B9FB8 size:0x198 mapped:0x806F904C
void loadStadiumLighting(int stadiumType, void* stadiumData) {
    StadiumLightInput input;
    void* light;
    GXColor color;
    int i;

    setNullPtrForStadiumObjs();
    memset(&stadiumObjectCollision, 0, sizeof(stadiumObjectCollision));
    fn_3_35E4(0);
    if (stadiumData != NULL) {
        for (i = 0; i < 4; i++) {
            characterLightingRelated(&inputParams[g_d_GameSettings._54][i * 10], &input);
            LITAlloc(&light);
            LITInitAttn(light, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
            LITInitPos(light, input.pos.x, input.pos.y, input.pos.z);
            color = input.color;
            LITInitColor(light, &color);
            stadiumObjectCollision.lights[i] = light;
        }
        stadiumObjectCollision.stadiumData = stadiumData;
        stadiumObjectCollision._08 = NULL;
        stadiumObjectCollision._0C = NULL;
        callStadiumPointerFun[stadiumType](stadiumData);
        stadiumObjectCollision.objectScratch = _OSAllocFromHeap(4, stadiumObjectCollision.objectCount << 3);
        fn_8001B214(fn_3_B8298);
        stadiumObjectCollision.rngConfig = rand();
        hugeAnimStruct.objectsInitialized = 1;
        lbl_3_bss_1901 = 0;
    }
}
