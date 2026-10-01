#include "Unknown/File_0x80035ca4.h"

static inline int findTextureContainerSlot(int id) {
    int i;

    /* The scan bound is 0x360 entries, well past TEXTURE_SLOT_COUNT. */
    for (i = 0; i < 0x360; i++) {
        if (id == textureContainerTags[i]) {
            return i;
        }
    }
    return -1;
}

void unregisterObjectByID(int id) {
    int slot = findTextureContainerSlot(id);

    if (slot != -1) {
        textureContainerTags[slot] = -1;
        textureContainerSlots[slot].buffer = NULL;
        textureContainerSlots[slot].textures = NULL;
        textureContainerSlots[slot].layout = NULL;
        PSMTXIdentity(textureContainerSlots[slot].mtx);
    }
}
