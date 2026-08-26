#include "text/text_block.h"

#include "text/text_channel.h"

void fn_8000FD54(s32 blockIndex, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    ScreenText* block = &screenTextArray.blocks[blockIndex];

    block->unk20 = arg1;
    block->unk22 = arg2;
    block->unk24 = arg3;
    block->unk26 = arg4;
}

void text_setInsertedValues(s32 blockIndex, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    ScreenText* block = &screenTextArray.blocks[blockIndex];

    block->insertedValues[0] = arg1;
    block->insertedValues[1] = arg2;
    block->insertedValues[2] = arg3;
    block->insertedValues[3] = arg4;
}

void practiceTextRelated(s32 blockIndex, s32 arg1, s32 maxLetters) {
    if (arg1 == 0) {
        screenTextArray.blocks[blockIndex].maxLettersToDraw = -1;
        screenTextArray.blocks[blockIndex].unk31 = 0;
        screenTextArray.blocks[blockIndex].unk32 = 0;
        return;
    }
    if (maxLetters >= 0) {
        screenTextArray.blocks[blockIndex].maxLettersToDraw = maxLetters;
    }
    screenTextArray.blocks[blockIndex].unk31 = arg1;
    screenTextArray.blocks[blockIndex].unk32 = 0;
}

void text_setPtrToWhereCharsAreStored(s32 blockIndex, s32 bankIndex, s32 stringIndex) {
    ScreenText* block = &screenTextArray.blocks[blockIndex];

    block->bankText = screenTextArray.textBanks[bankIndex]->strings[stringIndex];
    if (block->maxLettersToDraw < 0) {
        return;
    }
    block->maxLettersToDraw = 0;
    block->unk34 = 0;
    block->unk35 = 0;
}

void text_freeAllBlocks(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        screenTextArray.blocks[i].state = 0;
    }
}

void text_freeBlock(s32 blockIndex) {
    screenTextArray.blocks[blockIndex].state = 0;
}
