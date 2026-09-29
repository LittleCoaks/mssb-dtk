#ifndef __UNKNOWN_FILE_0X800B2B4C_H_
#define __UNKNOWN_FILE_0X800B2B4C_H_

#include "mssbTypes.h"

typedef struct _UnkB2B4CEntry {
    /*0x000*/ u8 _000[0x134];
    /*0x134*/ u16 value134;
} UnkB2B4CEntry;

typedef struct _UnkB2B4C {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ UnkB2B4CEntry** entries;
    /*0x1C*/ u8 _1C[0x88 - 0x1C];
    /*0x88*/ s32 value88;
    /*0x8C*/ u8 _8C[0x90 - 0x8C];
    /*0x90*/ f32 value90;
} UnkB2B4C;

void fn_800B2B4C(UnkB2B4C* obj, f32 value);
void fn_800B2B54(UnkB2B4C* obj, u16 index, u8 value);
void Set_FUN_800b2b6c(UnkB2B4C* obj, s32 value);

#endif // !__UNKNOWN_FILE_0X800B2B4C_H_
