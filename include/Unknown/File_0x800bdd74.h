#ifndef __UNKNOWN_FILE_0X800BDD74_H_
#define __UNKNOWN_FILE_0X800BDD74_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "C3/actor.h"

typedef struct {
    /* 0x00 */ Actor* actor;
    /* 0x04 */ void* anim;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u16 slot;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 _11[0x54 - 0x11];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59;
    /* 0x5A */ u8 unk5A;
    /* 0x5B */ u8 unk5B;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ u16 unk64;
    /* 0x66 */ u16 unk66;
    /* 0x68 */ u32 unk68;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 unk6D;
    /* 0x6E */ u8 _6E[2];
    /* 0x70 */ u32 unk70[8];
} ActorObjectEntry; // size: 0x90

/* Allocated by ActorObjectInitTable with `count` entries. */
typedef struct {
    /* 0x00 */ u16 count;
    /* 0x04 */ Mtx mtx;
    /* 0x34 */ ActorObjectEntry entries[1];
} ActorObjectTable;

void* ActorObjectInitTable(u16 count);

#endif // !__UNKNOWN_FILE_0X800BDD74_H_
