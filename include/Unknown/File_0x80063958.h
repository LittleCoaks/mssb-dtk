#ifndef __UNKNOWN_FILE_0X80063958_H_
#define __UNKNOWN_FILE_0X80063958_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"

typedef struct FielderTerrainState {
    /*0x00*/ Vec pos0;
    /*0x0C*/ Vec pos1;
    /*0x18*/ s32 unk18;
    /*0x1C*/ u8 unk1C;
} FielderTerrainState; // size 0x20

extern FielderTerrainState lbl_802E4BC0[9];

void maybeUpdateFielderTerrainStatus(s8 fielderIndex);

#endif // !__UNKNOWN_FILE_0X80063958_H_
