#ifndef __UNKNOWN_FILE_0X80021CA4_H_
#define __UNKNOWN_FILE_0X80021CA4_H_

#include "mssbTypes.h"

// Loads hand item `part` (0-5, see handItemPatterns) of character slot `charSlot` into `dest`
// (allocated when NULL), from ARAM (AramCharacterFiles) or disc (CharacterHandFiles).
void* loadCharacterHandItem(s32 charSlot, s32 part, void* dest);

#endif // !__UNKNOWN_FILE_0X80021CA4_H_
