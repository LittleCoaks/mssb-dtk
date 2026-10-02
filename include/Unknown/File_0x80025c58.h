#ifndef __UNKNOWN_FILE_0X80025C58_H_
#define __UNKNOWN_FILE_0X80025C58_H_

#include "mssbTypes.h"

typedef struct ActorBindSubTarget {
    /* 0x00 */ u32 value;
    /* 0x04 */ u8 unk04[0xC];
} ActorBindSubTarget; // size 0x10

typedef struct ActorBindTargets {
    /* 0x00 */ u32* a;
    /* 0x04 */ u32* b;
    /* 0x08 */ ActorBindSubTarget* c;
    /* 0x0C */ u32* d;
} ActorBindTargets;

typedef struct ActorBindEntry {
    /* 0x00 */ ActorBindTargets* targets;
    /* 0x04 */ u32 unk04;
} ActorBindEntry;

typedef struct ActorBindNode {
    /* 0x00 */ u8 unk00[0x30];
    /* 0x30 */ u32 value;
    /* 0x34 */ u8 unk34[0x10];
} ActorBindNode; // size 0x44

typedef struct ActorBindExtra {
    /* 0x00 */ u8 unk00[0x8];
    /* 0x08 */ u32* ptrA;
    /* 0x0C */ u32* ptrB;
    /* 0x10 */ ActorBindNode* nodes;
} ActorBindExtra;

typedef struct ActorBindSkeleton {
    /* 0x00 */ u8 unk00[0x10];
    /* 0x10 */ ActorBindEntry* entries;
} ActorBindSkeleton;

typedef struct ActorBindData {
    /* 0x00 */ u8 unk00[0x10];
    /* 0x10 */ ActorBindSkeleton* skeleton;
    /* 0x14 */ u8 unk14[0x7C - 0x14];
    /* 0x7C */ ActorBindExtra* extra;
} ActorBindData;

typedef struct ActorBindActor {
    /* 0x00 */ ActorBindData* data;
} ActorBindActor;

typedef struct ActorBindTrack {
    /* 0x00 */ u16 index;
    /* 0x02 */ u8 flag : 1;
    /* 0x02 */ u8 type : 7;
    /* 0x03 */ u8 subType : 4;
    /* 0x03 */ u8 unk03 : 4;
    /* 0x04 */ u32* ptr;
    /* 0x08 */ u32 value;
    /* 0x0C */ u32 unk0C;
} ActorBindTrack; // size 0x10

typedef struct ActorBindFile {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u16 numTracks;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ ActorBindTrack* tracks;
    /* 0x10 */ ActorBindActor* actor;
} ActorBindFile;

void ACTActorRelated(void* file, void* actor);

#endif // !__UNKNOWN_FILE_0X80025C58_H_
