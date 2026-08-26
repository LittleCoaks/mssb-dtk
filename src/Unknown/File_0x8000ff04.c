#include "Unknown/File_0x8000ff04.h"

#include "Unknown/File_0x8000f988.h"

s32 initializeTextParameters(s32 bankIndex, s32 stringIndex, s32 x, s32 y, u8 drawGroup, s32 color, s32 style) {
    ScreenText* block;
    s32 i;

    for (i = 0; i < 30; i++) {
        if (screenTextArray.blocks[i].state == 0) {
            break;
        }
    }

    if (i >= 30) {
        return 0;
    }

    block = &screenTextArray.blocks[i];
    block->bankText = screenTextArray.textBanks[bankIndex]->strings[stringIndex];
    block->x = x;
    block->y = y;
    block->drawGroup = drawGroup;
    block->state = 2;
    block->style = style;
    block->color = color;
    block->insertedValues[0] = 0;
    block->insertedValues[1] = 0;
    block->insertedValues[2] = 0;
    block->insertedValues[3] = 0;
    block->unk2D = 0;
    block->lineSpacing = 2;
    block->justify = 0;
    block->verticalAlign = 0;
    block->text = NULL;
    block->maxLettersToDraw = -1;
    block->unk31 = 0;
    block->unk32 = 0;
    block->unk34 = 0;
    block->unk33 = 0;
    block->unk35 = 0;
    block->unk36 = 0;
    return i;
}
