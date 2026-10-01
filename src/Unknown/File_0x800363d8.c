#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x80034e20.h"
#include "text/text_channel.h"

#define ICON_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[((MenuScene*)(scene))->firstHandle + (i)].object)

void load_Icon(void* scene, int handle, u32 part, u32 element, int frame) {
    LayoutFrameInfo info;
    u16 texture;
    u16* overrides;

    if (part < 10) {
        if (fn_8000CEF0(textureContainerSlots[ICON_RECORD(scene, handle)->textureSlot].layout, element, 0, frame, &info)) {
            texture = info.textureIndex;
        } else {
            texture = 0;
        }
        overrides = ICON_RECORD(scene, handle)->textureOverride;
        overrides[part] = texture;
    }
}
