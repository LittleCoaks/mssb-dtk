#ifndef __UNKNOWN_FILE_0X80024BB4_H_
#define __UNKNOWN_FILE_0X80024BB4_H_

#include "mssbTypes.h"

typedef struct {
    /*0x000*/ u8 _000[0x252];
    /*0x252*/ s8 _252;
    u8 _253;
    /*0x254*/ s8 _254;
    artificial_padding(0x254, 0x25A, s8);
    /*0x25A*/ u8 _25A;
    artificial_padding(0x25A, 0x274, u8);
    /*0x274*/ u8 _274;
} fn_80024C6C_s;

f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);
BOOL isCharacterUnlocked(int charID);
int fn_80024C6C(fn_80024C6C_s* obj, int arg1);

#endif // !__UNKNOWN_FILE_0X80024BB4_H_
