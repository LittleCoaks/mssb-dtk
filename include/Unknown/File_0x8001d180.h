#ifndef __UNKNOWN_FILE_0X8001D180_H_
#define __UNKNOWN_FILE_0X8001D180_H_

#include "mssbTypes.h"

// Shows the hand/bat model `slot` of player `playerIdx` by giving its body bone a
// display object (sBone.dispObj); attach == 0 clears it. Slot -> bone id:
// handAttachBoneIDs.
void setHandModelAttached(s32 playerIdx, s32 slot, BOOL attach);

#endif // !__UNKNOWN_FILE_0X8001D180_H_
