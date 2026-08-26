#include "Unknown/File_0x8000f988.h"

#include "Unknown/File_0x8000ff04.h"

s32 text_initializeNewChannel(UnkText988Arg* arg0, s32 indexOffset, u16 arg2, s32 arg3, s32 arg4, s32 useFlag8) {
    TextGraphicsObject* graphics;
    s32 i;

    graphics = graphicsRelatedArray[arg0->unk14 + indexOffset].object;
    graphics->flags |= 4;
    if (useFlag8 != 0) {
        graphics->flags |= 8;
    }

    for (i = 0; i < 30; i++) {
        if (screenTextArray.channels[i].graphics == NULL) {
            screenTextArray.channels[i].graphics = graphics;
            screenTextArray.channels[i].unk6 = arg2;
            screenTextArray.channels[i].blockIndex =
                initializeTextParameters(arg3, arg4, 0, 0, graphics->unk67, -1, 0);
            if (graphics->unk0 != 0) {
                screenTextArray.blocks[screenTextArray.channels[i].blockIndex].text = graphics->text;
            } else {
                screenTextArray.blocks[screenTextArray.channels[i].blockIndex].text = NULL;
            }
            return screenTextArray.channels[i].blockIndex;
        }
    }
    return -1;
}
