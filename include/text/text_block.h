#ifndef __TEXT_TEXT_BLOCK_H_
#define __TEXT_TEXT_BLOCK_H_

#include "mssbTypes.h"

void fn_8000FD54(s32 blockIndex, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void text_setInsertedValues(s32 blockIndex, u16 arg1, u16 arg2, u16 arg3, u16 arg4);
void practiceTextRelated(s32 blockIndex, s32 arg1, s32 maxLetters);
void text_setPtrToWhereCharsAreStored(s32 blockIndex, s32 bankIndex, s32 stringIndex);
void text_freeAllBlocks(void);
void text_freeBlock(s32 blockIndex);

#endif // !__TEXT_TEXT_BLOCK_H_
