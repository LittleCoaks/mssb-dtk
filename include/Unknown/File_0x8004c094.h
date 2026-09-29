#ifndef __UNKNOWN_FILE_0X8004C094_H_
#define __UNKNOWN_FILE_0X8004C094_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"

/* One 0x50-byte particle-burst record, as fn_80031CA4 consumes it. The
 * defaults live in a .data table (lbl_800FC720) reached through lbl_803CB860. */
typedef struct ParticleBurstParams {
    /* 0x00 */ void* texture;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x3C];
} ParticleBurstParams; // size 0x50

extern ParticleBurstParams* lbl_803CB860;
extern void* lbl_803CBD0C;

void fn_80031CA4(Vec* pos, ParticleBurstParams* params);
void spawnDust(Vec* pos);

#endif // !__UNKNOWN_FILE_0X8004C094_H_
