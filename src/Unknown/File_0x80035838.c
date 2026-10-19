#include "Unknown/File_0x80035838.h"
#include "Dolphin/os.h"
#include "Unknown/dvdsys.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800c0770.h"

s32 diskReadRelated(void *arg0, s32 arg1) {
    u8 loaded = 0;
    u8 i;
    s8 slot;

    if (diskReadState == 2) {
        diskReadState = 0;
        lbl_803CBC94 = NULL;
        lbl_803CB810 = -1;
    }

    switch (diskReadState) {
    case 0:
        slot = -1;
        for (i = 0; i < TEXTURE_SLOT_COUNT; i++) {
            if (textureContainerSlots[i].buffer == NULL) {
                slot = (s8)i;
                break;
            }
        }
        lbl_803CBC91 = slot;
        if (lbl_803CBC91 == -1) {
            OSReport(" SabNo = %d not to add  \n", lbl_803CBC91);
            OSPanic("spani_default.c", 0x45A, "gasSpani No Empty \n");
        }
        textureContainerTags[lbl_803CBC91] = (u8)arg1;
        textureContainerSlots[lbl_803CBC91].buffer = ARAMTransfer(arg0, 0, 0, 0);
        lbl_803CBC94 = arg0;
        lbl_803CB810 = (u8)arg1;
        diskReadState = diskReadState + 1;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            TextureContainerSlot *cur = &textureContainerSlots[lbl_803CBC91];
            cur->textures = (TextureHeader *)((u8 *)cur->buffer + *(u32 *)cur->buffer);
            cur->layout = (u8 *)cur->buffer + *((u32 *)cur->buffer + 1);
            convertTextureHeader(cur->textures);
            fn_8000B9C8(cur->layout);
            loaded = 1;
            diskReadState = diskReadState + 1;
        }
        break;
    }

    return loaded;
}
