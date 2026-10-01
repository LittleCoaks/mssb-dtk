#include "Unknown/File_0x8003649c.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800363d8.h"
#include "text/text_channel.h"

void fn_8000CC4C(void* layout, void* part, void* data, u32 size, u32 count);

#define ICON_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[((MenuScene*)(scene))->firstHandle + (i)].object)

void setIndicatorSlotState(DrawingSceneStruct* node, int slot, int handle, int elementBase, int state) {
    u16 texture;
    LayoutFrameInfo info;
    UIRecord* record;
    u16 element;
    int slotIndex;
    u8* part;
    u8* sub;

    record = ICON_RECORD(node, slot);
    element = record->elementIndex;
    slotIndex = record->textureSlot;
    if (fn_8000CEF0(textureContainerSlots[slotIndex].layout, elementBase, 0, state, &info)) {
        texture = info.textureIndex;
    } else {
        texture = 0;
    }
    handle = handle * 4 + 8;
    part = *(u8**)(*(u8**)(*(u8**)((u8*)textureContainerSlots[slotIndex].layout + 8) + element * 4 + 8) + handle);
    sub = part + 4;
    fn_8000CC4C(textureContainerSlots[slotIndex].layout, part, &texture, (u32)(sub + 6) - (u32)sub, 2);
}
