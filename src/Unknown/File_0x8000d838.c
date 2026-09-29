#include "Unknown/File_0x8000d838.h"
#include "Unknown/File_0x8000ba3c.h"
#include "Unknown/File_0x8000c194.h"
#include "Unknown/File_0x8000d164.h"

void handleUIAction(u32* frame, UILayout* layout, int elementIndex, Mtx mtx, u32 arg4, u32 arg5, u32* arg6,
                    TextureHeader* textures) {
    s16 path[60];

    if (layout->unk6 == 0) {
        triggerDefaultHUDAction(frame, layout, elementIndex, mtx, arg4, arg5, arg6, textures);
    } else if ((*(UILayoutElement**)(layout->elementTable + elementIndex * 4 + 8))->flags & 0x80000000) {
        path[0] = -1;
        path[1] = 0;
        updateMenuOrBackgroundUI(frame, layout, elementIndex, mtx, arg4, arg5, arg6, &path[2]);
    } else {
        updateHUDRelatedUI(frame, layout, elementIndex, mtx, arg4, arg5, arg6, textures);
    }
}
