#ifndef __GAME_STADIUM_STADIUM_FRAMEWORK_H_
#define __GAME_STADIUM_STADIUM_FRAMEWORK_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"
#include "game/ball/collision_primitives.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "Unknown/File_0x800bc7e8.h"
#include "Unknown/File_0x800bc834.h"
#include "C3/control.h"

typedef struct _StadiumModelNode {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ struct DODisplayObj* dispObj;
    /*0x18*/ u8 _18[0x64 - 0x18];
    /*0x64*/ MtxPtr skinMtxArray;
    /*0x68*/ MtxPtr skinInvTransposeMtxArray;
    /*0x6C*/ u8 _6C[0x74 - 0x6C];
    /*0x74*/ struct _StadiumModelNode* firstChild;
    /*0x78*/ u8 _78[4];
    /*0x7C*/ void* skinData;
    /*0x80*/ u8 _80[0x98 - 0x80];
    /*0x98*/ u8 drawFlags;
    /*0x99*/ u8 _99[0xEC - 0x99];
    /*0xEC*/ MtxPtr worldMtx;
    /*0xF0*/ u8 _F0[0x100 - 0xF0];
    /*0x100*/ struct _StadiumModelNode* nextSibling;
} StadiumModelNode;

typedef struct _StadiumVertex {
    /*0x00*/ Vec pos;
    /*0x0C*/ u8 _0C[4];
} StadiumVertex; // size: 0x10

typedef struct _StadiumVertexGroup {
    /*0x00*/ u8 _00;
    /*0x01*/ u8 isTriangleStrip;
    /*0x02*/ u16 vertexCount;
    /*0x04*/ StadiumVertex vertices[1];
} StadiumVertexGroup;

typedef struct _StadiumMeshData {
    /*0x00*/ u8 _00[8];
    /*0x08*/ StadiumVertexGroup* groups;
} StadiumMeshData;

typedef struct _StadiumModel {
    /*0x00*/ StadiumModelNode* root;
    /*0x04*/ u8 _04[0x64 - 0x04];
    /*0x64*/ u16 _64;
    /*0x66*/ u16 _66;
} StadiumModel;

typedef struct _StadiumObjectEffect {
    /*0x00*/ u8 _00[0x0C];
    /*0x0C*/ u8 state[0x20];
    /*0x2C*/ void* handle;
} StadiumObjectEffect;

typedef struct _StadiumDrawOrder {
    /*0x00*/ f32 depth;
    /*0x04*/ s32 index;
} StadiumDrawOrder; // size: 0x8

typedef struct _StadiumLightBlock {
    /*0x00*/ u8 _00[0x58];
    /*0x58*/ Vec dir;
    /*0x64*/ u8 _64[0xC0 - 0x64];
} StadiumLightBlock; // size: 0xC0

typedef struct _StadiumLink {
    /*0x00*/ f32 weight;
    /*0x04*/ f32 mobility;
    /*0x08*/ f32 radius;
    /*0x0C*/ Vec pos;
    /*0x18*/ Vec prevPos;
    /*0x24*/ Vec vel;
    /*0x30*/ Vec accel;
    /*0x3C*/ u32 pinned;
} StadiumLink; // size: 0x40

typedef struct _StadiumObject {
    /*0x00*/ u8 _00[0x44];
    /*0x44*/ Mtx worldMtx;
    /*0x74*/ StadiumModel* model;
    /*0x78*/ TriangleGroup* triangles;
    /*0x7C*/ void (*callback)(void);
    /*0x80*/ int (*func)(int idx, int arg2, void* arg3);
    /*0x84*/ void (*preDraw)(struct _StadiumObject* obj);
    /*0x88*/ void (*postDraw)(struct _StadiumObject* obj);
    /*0x8C*/ StadiumObjectEffect* effect;
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 _90b1 : 1;
    /*0x90*/ u8 fadeByDepth : 1;
    /*0x90*/ u8 customZMode : 1;
    /*0x90*/ u8 zCompare : 1;
    /*0x90*/ u8 zAlways : 1;
    /*0x90*/ u8 zUpdate : 1;
    /*0x90*/ u8 _90b7 : 1;
    /*0x91*/ u8 _91;
    /*0x92*/ u8 alpha;
    /*0x93*/ u8 nodeDrawFlags;
    /*0x94*/ u16 animActive;
    /*0x96*/ s16 animIndex;
    /*0x98*/ u8 drawPass;
    /*0x99*/ u8 _99;
    /*0x9A*/ u8 shadowEnabled;
    /*0x9B*/ u8 _9B;
    /*0x9C*/ u8 _9C;
    /*0x9D*/ u8 _9D[0xA0 - 0x9D];
    /*0xA0*/ Vec pos;
    /*0xAC*/ struct _StadiumLink* anchorA;
    /*0xB0*/ struct _StadiumLink* anchorB;
    /*0xB4*/ u8 _B4[0xC0 - 0xB4];
    /*0xC0*/ f32 yaw;
    /*0xC4*/ struct _StadiumLink* links;
    /*0xC8*/ u8 _C8[2];
    /*0xCA*/ u8 _CA;
    /*0xCB*/ u8 _CB[0xD0 - 0xCB];
    /*0xD0*/ s8 _D0;
    /*0xD1*/ u8 _D1;
    /*0xD2*/ u8 _D2[0xE8 - 0xD2];
} StadiumObject; // size: 0xE8

typedef struct _StadiumObjectCollision {
    /*0x00*/ StadiumObject* objects;
    /*0x04*/ StadiumObject* objectsRelated;
    /*0x08*/ void* _08;
    /*0x0C*/ void* _0C;
    /*0x10*/ u8 _10[4];
    /*0x14*/ StadiumDrawOrder* objectScratch;
    /*0x18*/ void (*preUpdateFunc)(void);
    /*0x1C*/ void (*updateFunc)(void);
    /*0x20*/ StadiumLightBlock* lights[4];
    /*0x30*/ s32 objectCount;
    /*0x34*/ void* _34;
    /*0x38*/ void* stadiumData;
    /*0x3C*/ s32* hazardData;
    /*0x40*/ u16* vertexOffsets;
    /*0x44*/ f32* vertexData;
    /*0x48*/ VecSrcDst* vertexDataArray;
    /*0x4C*/ u8 _4C[0x18];
    /*0x64*/ s16 boundingBoxCount;
    /*0x66*/ s16 rngConfig;
    /*0x68*/ s16 rngConfigSaved;
    /*0x6A*/ u8 objectsLoaded;
    /*0x6B*/ u8 _6B;
    /*0x6C*/ u8 gameStatusIsLiveBall;
    /*0x6D*/ u8 propCount;
    /*0x6E*/ u8 _6E[2];
} StadiumObjectCollision; // size: 0x70

typedef struct _ACTActor {
    /*0x00*/ void* actor;
    /*0x04*/ void* animBank;
    /*0x08*/ u8 _08[6];
    /*0x0E*/ u16 sequenceNum;
    /*0x10*/ u8 _10[0x44];
    /*0x54*/ f32 animSpeed;
    /*0x58*/ u8 applyAnimation;
    /*0x59*/ u8 applyFrame;
    /*0x5A*/ u8 applySpeed;
    /*0x5B*/ u8 applyFlags;
    /*0x5C*/ f32 animFrame;
    /*0x60*/ f32 animTime;
    /*0x64*/ u8 _64[4];
    /*0x68*/ s32 _68;
    /*0x6C*/ u8 _6C[4];
} ACTActor;

typedef struct _StadiumAnimRecord {
    /*0x00*/ f32 frame;
    /*0x04*/ f32 time;
    /*0x08*/ f32 speed;
    /*0x0C*/ s32 _0C;
    /*0x10*/ s32 _10;
    /*0x14*/ s16 _14;
    /*0x16*/ u8 _16;
    /*0x17*/ u8 _17;
    /*0x18*/ u8 _18;
    /*0x19*/ u8 _19[3];
} StadiumAnimRecord; // size: 0x1C

typedef struct _StadiumAnimObject {
    /*0x00*/ u8 _00[0xE8];
    /*0xE8*/ StadiumAnimRecord* animRecord;
} StadiumAnimObject;

typedef struct _StadiumAnimObjectList {
    /*0x00*/ u8 _00[6];
    /*0x06*/ u16 objectCount;
    /*0x08*/ u8 _08[0x10];
    /*0x18*/ StadiumAnimObject** objects;
} StadiumAnimObjectList;

typedef struct _StadiumAnimData {
    /*0x00*/ StadiumAnimObjectList* list;
} StadiumAnimData;

extern StadiumObjectCollision stadiumObjectCollision;
extern u8 lbl_3_data_11168[];
extern void (*callStadiumPointerFun[7])(void*);

void fn_3_35E4(int arg);
void fn_8001B200(void);
void fn_8001B214(void (*func)(void));
void fn_800B4278(void* arg);
void fn_3_38E8(void (*func)(Mtx view, int flag, u32 pass));
void fn_800B2BFC(StadiumModelNode* root, u16 a, u16 b);
void fn_800B3F20(StadiumModelNode* root);
void fn_800B313C(StadiumModelNode* root);
int fn_800B3C04(int arg, StadiumModelNode* root, Mtx m);
void fn_800117CC(Mtx a, Mtx b, Mtx out);
void fn_800116DC(StadiumModel* model, Mtx m, u16 idx);
void fn_80024DB0(u8* state);
void fn_80024FA4(StadiumModel* model, void* handle, u8* state, int arg);
void fn_3_C1964(void);
void fn_3_16E328(void);
void fn_800528B4(void);
extern f32 lbl_3_data_11178[5];

void randomizeAndLoadSoundEffect(int soundId, int arg);
void maybeYoshiParkGXRelated(void);
void fn_3_B8184(StadiumModel* model, Mtx m);
void fn_8003A8A0(struct DODisplayObj* dispObj, Mtx m, int arg);
s32 fn_3_B827C(void);
void fn_3_B828C(s32 value);
void fn_3_B8298(void);
void storeBoundingBoxCoordinates(Vec* minDst, Vec* maxDst);
void transformVectorsUpdateBoundingBox(Mtx m, StadiumMeshData* mesh);
void initBoundingBoxLimits(void);
s32 calculateHazardDataAddress(s32 idx, void** out);
void CopyOutVecSrcDst(int idx, Vec* a, Vec* b);
s32 fn_3_B8658(const f32* a, const f32* b);
void fn_3_B867C(Mtx view, StadiumDrawOrder* order);
void loadStadiumObjectVisuals(Mtx view, int flag, u32 pass);
void fn_800C07BC(void* base, void* scratch, int count, int size, s32 (*cmp)(const f32*, const f32*));
void fn_3_B8C08(Mtx view);
void fn_3_B902C(void);
void initStadiumObjectData(void);
void updateStadiumObjCollision(void);
int processStadiumObjectFunction(int, int, int, void*);
TriangleGroup* getStadiumHazardTriangles(int stadiumId, int offset, Mtx m);
void updateGameStatusFlag(void);
void fn_3_B93C4(void);
void fn_3_B93C8(void);
void hazardSimulationRelated(void);
void fn_800638CC(void);
void fn_3_B950C(void);
void fn_3_B9510(s32 idx);
void fn_3_B9524(void);
void* fn_3_B9534(int w, int h, GXTexObj* obj);
void cleanupMinigameResources(void);
void fn_3_B97C8(void (*func)(void));
void actorSetAnimBank(ACTActor* act, u32 animBankId);
void fn_3_B98E8(StadiumAnimData* d);
void calledWhileMatchIsLoading(void);
BOOL loadStadiumObjects(int stadiumId);
void processStadiumFileObjects(u8* types, int count, u8* base, u32* out);
void loadStadiumLighting(int stadiumType, void* stadiumData);

#endif // !__GAME_STADIUM_STADIUM_FRAMEWORK_H_
