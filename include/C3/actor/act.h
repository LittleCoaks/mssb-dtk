#ifndef _C3_ACTOR_ACT_H_
#define _C3_ACTOR_ACT_H_

#include "mssbTypes.h"
#include "C3/actor.h"
#include "charPipeline/structures/List.h"
#include "Dolphin/mtx.h"

void ProcessActorBonesForShadows(ActorLayoutFile* layout);

typedef struct _UnkB2B4CEntry {
    /*0x000*/ u8 _000[0x134];
    /*0x134*/ u16 value134;
} UnkB2B4CEntry;

typedef struct _UnkB2B4C {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ UnkB2B4CEntry** entries;
    /*0x1C*/ u8 _1C[0x70 - 0x1C];
    /*0x70*/ DSList drawPriorityList;
    /*0x7C*/ u8 _7C[0x88 - 0x7C];
    /*0x88*/ s32 value88;
    /*0x8C*/ u8 _8C[0x90 - 0x8C];
    /*0x90*/ f32 value90;
} UnkB2B4C;

void fn_800B2B4C(UnkB2B4C* obj, f32 value);
void fn_800B2B54(UnkB2B4C* obj, u16 index, u8 value);
void Set_FUN_800b2b6c(UnkB2B4C* obj, s32 value);

void callDSInsertListObject(UnkB2B4C* obj, u16 index);

void maybeTransformVectorByAnimationMatrix(void* actor, u16 boneIndex, Vec* out);

void actorBoneRelated(void);

void f_BuildBoneSkinOrientationMatrix(sBone* root, MtxPtr out);

BOOL maybeBallRelated(Actor** actor, ActorLayout* layout, u16 actorID);

void InitBone(sBone* parent, ActorBone* node, Actor* actor, u16* index, sBone* bones);

Actor* maybeProcessActLayout(ActorLayout* layout);

void renderingRelated(void);

void haveActLayoutPointToGeoHeader(void* layout, void* geo);
void LoadActorLayout(void* layout);
void AdjustActorPointers(void* layout);

#endif // _C3_ACTOR_ACT_H_
