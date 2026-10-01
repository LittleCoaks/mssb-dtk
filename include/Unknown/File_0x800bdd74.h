#ifndef __UNKNOWN_FILE_0X800BDD74_H_
#define __UNKNOWN_FILE_0X800BDD74_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "C3/actor.h"

typedef struct {
    /* 0x00 */ Actor* actor;
    /* 0x04 */ void* anim;           // ANIMBank handed to ACTSetAnimation
    /* 0x08 */ void (*callback)(void); // run by sknRelated before drawing
    /* 0x0C */ u16 slot;
    /* 0x0E */ u16 seqNum;           // ACTSetAnimation sequence number
    /* 0x10 */ Control control;      // copied into actor->worldControl when applyControl is set
    /* 0x54 */ f32 speed;            // fn_800B4C04
    /* 0x58 */ u8 animPending;       // the four pending flags are consumed by fn_800BD8C4
    /* 0x59 */ u8 framePending;
    /* 0x5A */ u8 speedPending;
    /* 0x5B */ u8 boneParam;         // bit 1: pending, bit 0: value for updateBoneParam
    /* 0x5C */ f32 frame;            // setActorAnimFrame
    /* 0x60 */ f32 blendTime;        // ACTSetAnimation's time
    /* 0x64 */ u16 unk64;
    /* 0x66 */ u16 unk66;
    /* 0x68 */ u32 unk68;
    /* 0x6C */ u8 applyControl;
    /* 0x6D */ u8 drawArgCount;      // number of drawArgs sknRelated forwards (0-8)
    /* 0x6E */ u8 _6E[2];
    /* 0x70 */ u32 drawArgs[8];
} ActorObjectEntry; // size: 0x90

/* Allocated by ActorObjectInitTable with `count` entries. */
typedef struct {
    /* 0x00 */ u16 count;
    /* 0x04 */ Mtx mtx;
    /* 0x34 */ ActorObjectEntry entries[1];
} ActorObjectTable;

void* ActorObjectInitTable(u16 count);

#endif // !__UNKNOWN_FILE_0X800BDD74_H_
