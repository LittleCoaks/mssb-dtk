#ifndef _DOLPHIN_CP_ACTOR_H_
#define _DOLPHIN_CP_ACTOR_H_

#include "C3/control.h"
#include "charPipeline/structures/Tree.h"
#include "charPipeline/structures/List.h"

typedef struct DODisplayData *DODisplayDataPtr;
typedef struct sBone sBone;
typedef struct sHdr sHdr;
typedef struct ANIMBank ANIMBank;

typedef struct {
    /* 0x00 */ u32 versionNumber;
    /* 0x04 */ u16 actorID;
    /* 0x06 */ u16 totalBones;
    /* 0x08 */ DSTree hierarchy;
    /* 0x10 */ char * geoPaletteName;
    /* 0x14 */ u16 skinFileID;
    /* 0x16 */ u16 pad16;
    /* 0x18 */ u32 userDataSize;
    /* 0x1C */ char * userData;
} ActorLayout;

typedef struct {
    /* 0x00 */ Control * orientationCtrl;
    /* 0x04 */ DSBranch branch;
    /* 0x14 */ u16 geoFileID;
    /* 0x16 */ u16 boneID;
    /* 0x18 */ u8 inheritanceFlag;
    /* 0x19 */ u8 drawingPriority;
    /* 0x1A */ u16 pad16;
} ActorBone;

// An ActorLayout as it sits in memory after loading: the bone table follows
// the header directly.
typedef struct {
    /* 0x00 */ ActorLayout header;
    /* 0x20 */ ActorBone bones[1]; // header.totalBones entries
} ActorLayoutFile;

typedef struct {
    /* 0x00 */ ActorLayout *layout;
    /* 0x04 */ u16 actorID;
    /* 0x06 */ u16 totalBones;
    /* 0x08 */ DSTree hierarchy;
    /* 0x10 */ DODisplayDataPtr pal;
    /* 0x14 */ struct DODisplayObj *skinObject;
    /* 0x18 */ sBone **boneArray;
    /* 0x1C */ Control worldControl;
    /* 0x60 */ MtxPtr forwardMtxArray;
    /* 0x64 */ MtxPtr skinMtxArray;
    /* 0x68 */ MtxPtr skinInvTransposeMtxArray;
    /* 0x6C */ MtxPtr orientationInvMtxArray;
    /* 0x70 */ DSList drawPriorityList;
    /* 0x7C */ sHdr * skHeader;
    /* 0x80 */ u8 unk80[0x8C - 0x80];
    /* 0x8C */ f32 unk8C; // advanced by unk90 each tick, capped at 1.0
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u32 unk94;
    /* 0x98 */ u8 unk98;
    /* 0x99 */ u8 unk99; // passed to ANIMTick for every bone
    /* 0x9A */ u8 unk9A[0xA0 - 0x9A];
} Actor; // size: 0xA0 (MSSB)

// actor.c
void ACTGet(Actor **actor, char *name);
void ACTRelease(Actor **actor);
void ACTRender(Actor *actor, MtxPtr camera, u8 numLights, ...);
void ACTHide(Actor *actor);
void ACTShow(Actor *actor);
void ACTBuildMatrices(Actor *actor);
Control *ACTGetControl(Actor *actor);
void ACTSetInheritance(Actor *actor, u8 inheritanceFlag);
void ACTSetAmbientPercentage(Actor *actor, f32 percent);
void ACTSort(Actor *actor);
void ACTSetEffectsShader(Actor *actor, char *shaderFunc, char *data);
u32 ACTGetUserDataSize(Actor *actor);
char *ACTGetUserData(Actor *actor);

// actorAnim.c
void ACTSetAnimation(Actor *actor, ANIMBank *animBank, char *sequenceName, u16 seqNum, f32 startFrame, f32 time);
void ACTSetTime(Actor *actor, f32 time);
void ACTSetSpeed(Actor *actor, f32 speed);
void ACTTick(Actor *actor);

// boneAnim.c
void ACTSetBoneTime(sBone *bone, f32 time);
void ACTSetBoneSpeed(sBone *bone, f32 speed);
void ACTTickBone(sBone *bone);
void ACTSetBoneTrack(sBone *bone, struct ANIMAnimTrack *track, f32 time, BOOL blend);

#endif // _DOLPHIN_CP_ACTOR_H_
