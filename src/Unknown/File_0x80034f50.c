#include "Unknown/File_0x80034f50.h"

extern f32 lbl_803CC6E8;

UIRecord* allocateGraphicsSlot(const UIRecordDescriptor* desc) {
    UIRecord* rec;
    s32 i;
    s32 slot;

    for (i = 0; i < UI_RECORD_COUNT; i++) {
        if (menuGraphicsStructures[i].flags == 0) {
            for (slot = 0; slot < 0x360; slot++) {
                if (desc->tag == textureContainerTags[slot]) {
                    break;
                }
            }

            rec = &menuGraphicsStructures[i];
            rec->flags = 1;
            if (desc->type == 1) {
                rec->flags |= UI_FLAG_TEXT;
            }

            rec->rgba = desc->rgba;
            *(u32*)rec->unk74 = desc->rgba;
            rec->elementIndex = desc->elementIndex;
            rec->layer = desc->layer;
            rec->textureSlot = slot;
            rec->pos.x = *(const f32*)&desc->unk4[0];
            rec->pos.y = *(const f32*)&desc->unk4[4];
            rec->pos.z = lbl_803CC6E8;
            *(f32*)&rec->unk69[3] = *(const f32*)&desc->unk15[3];
            rec->unk69[7] = ((const u8*)desc)[0x1C];
            rec->next = NULL;
            rec->firstChild = NULL;
            rec->anchorSub = desc->anchorSub;
            rec->unk69[8] = ((const u8*)desc)[0x1D];

            if (desc->mode == 2) {
                rec->playMode = UI_PLAY_STOP;
            } else if (desc->mode == 3) {
                rec->playMode = UI_PLAY_FORWARD;
            } else {
                rec->playMode = desc->mode;
                rec->flags |= UI_FLAG_VISIBLE;
            }

            rec->frame = 0;
            rec->rate = 0x10000;
            rec->attachedThisFrame = 0;
            PSMTXIdentity((void*)rec->unkC);

            return rec;
        }
    }

    return NULL;
}
