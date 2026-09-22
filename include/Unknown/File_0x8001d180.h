#ifndef __UNKNOWN_FILE_0X8001D180_H_
#define __UNKNOWN_FILE_0X8001D180_H_

#include "mssbTypes.h"

// Hangs hand/bat model `slot` of player `playerIdx` on its body bone (bone+0x14);
// attach == 0 detaches it. Slot -> bone id: handAttachBoneIDs.
void setHandModelAttached(s32 playerIdx, s32 slot, BOOL attach);

#endif // !__UNKNOWN_FILE_0X8001D180_H_
