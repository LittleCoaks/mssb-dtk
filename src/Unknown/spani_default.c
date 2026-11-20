#include "Unknown/spani_default.h"
#include "text/text.h"
#include "Unknown/File_0x8000ba3c.h"
#include "Unknown/File_0x80009e94.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/sprt.h"
#include "text/text_draw_conditional.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/os.h"
#include "Unknown/dvdsys.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800c0770.h"

void removeGraphicsElementFromScene(DrawingSceneStruct* node) {
    MenuScene* scene = (MenuScene*)node;
    UIRecord* rec;
    int first = scene->firstHandle;
    int i;
    int j;

    for (i = 0; i < scene->handleCount; i++) {
        rec = (UIRecord*)graphicsRelatedArray[first + i].object;
        if (rec != NULL) {
            rec->flags = 0;
        }
    }
    i += first;
    for (j = first; i < UI_RECORD_COUNT; i++, j++) {
        graphicsRelatedArray[j].object = graphicsRelatedArray[i].object;
        graphicsRelatedArray[j].unk4 = graphicsRelatedArray[i].unk4;
        if (graphicsRelatedArray[j].unk4 != 0) {
            ((MenuScene*)graphicsRelatedArray[j].unk4)->firstHandle = j;
        }
    }
    for (; j < UI_RECORD_COUNT; j++) {
        graphicsRelatedArray[j].object = NULL;
        graphicsRelatedArray[j].unk4 = 0;
    }
}

void addGraphicsElementToScene(DrawingSceneStruct* node, const UIRecordDescriptor* descriptors) {
    MenuScene* scene = (MenuScene*)node;
    GraphicsArrayEntry* first;
    int count = 0;
    const UIRecordDescriptor* desc;
    int i;
    s32 j;

    for (i = 0; i < UI_RECORD_COUNT; i++) {
        if (graphicsRelatedArray[i].object == NULL) {
            scene->firstHandle = i;
            first = &graphicsRelatedArray[i];
            first->unk4 = (u32)node;
            break;
        }
    }
    desc = descriptors;
    while (1) {
        int handle = count + i;
        UIRecord* rec;
        int parent;

        if (desc->type == UI_DESC_END) break;
        graphicsRelatedArray[handle].object = (TextGraphicsObject*)allocateGraphicsSlot(desc);
        parent = desc->parent;
        rec = (UIRecord*)graphicsRelatedArray[handle].object;
        if (parent == UI_NO_PARENT || count == 0) {
            rec->parent = NULL;
        } else {
            rec->parent = (UIRecord*)first[parent].object;
            rec->next = rec->parent->firstChild;
            rec->parent->firstChild = rec;
        }
        for (j = 0; j < 10; j++) {
            rec->textureOverride[j] = UI_NO_OVERRIDE;
        }
        desc++;
        count++;
    }
    scene->handleCount = count;
}

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

extern u8 lbl_800F78E0[0xC0];
extern u8 lbl_801F8640[0x40];
extern u8 lbl_801F8680[0x40];
extern UIRecord* lbl_803CBC9C;
extern f32 lbl_803CBBE0;
extern u8 lbl_803CBBE4;
extern f32 lbl_803CC6E8;
extern f32 lbl_803CC6EC;
extern f32 lbl_803CC6F0;
extern f32 lbl_803CC6F4;
extern f32 lbl_803CC6F8;

void fn_80034BCC(void);
void fn_8000F534(UIRecord* rec, s32 arg);
void fn_8000CC4C(void* layout, void* part, u16* override, s32 arg4, s32 arg5);
void fn_800B24D4(s32 arg);
void fn_800B27DC(void* proj, s32 arg);

void maybeProcessUIUpdates(void) {
    UIRecord* rec;
    s32 i;
    s32 j;
    s32 k;
    u16 held;
    Mtx mtxA;
    Mtx mtxB;
    u32 arg6;
    void* baseMtx;
    f32 scale;
    Vec* trans;
    TextureContainerSlot* slot;
    u32* elementTable;
    u32* element;
    u32 part;
    u32 rgba;
    u8 result;

    if (AtBat_ButtonInput1._00 & INPUT_BUTTON_START) {
        held = *(u16*)((u8*)&AtBat_ButtonInput1 + 0x64);
        if (held & 1) {
            if ((s32)uiDrawLoopEnd > (s32)uiDrawLoopStart) {
                uiDrawLoopEnd--;
            }
        } else if (held & 2) {
            if ((s32)uiDrawLoopEnd < 0x360) {
                uiDrawLoopEnd++;
            }
        }
        if (held & 4) {
            if ((s32)uiDrawLoopStart > 0) {
                uiDrawLoopStart--;
            }
        } else if (held & 8) {
            if ((s32)uiDrawLoopStart < (s32)uiDrawLoopEnd) {
                uiDrawLoopStart++;
            }
        }
    }

    fn_8000A094((u32)fn_80034BCC);

    i = (s32)uiDrawLoopStart;
    rec = &menuGraphicsStructures[i];

    for (; i < (s32)uiDrawLoopEnd; i++, rec++) {
        if (rec->flags == 0) {
            continue;
        }
        if (!(rec->flags & UI_FLAG_VISIBLE) || (rec->parent != NULL && rec->attachedThisFrame == 0)) {
            if (rec->flags & UI_FLAG_TEXT) {
                fn_8000F534(rec, 0);
            }
            continue;
        }

        fn_800B24D4(rec->layer);

        if (rec->playMode != UI_PLAY_STOP) {
            fn_800B27DC(lbl_801F8640, 0);
            fn_800B21A8(rec->unk69[8]);
            baseMtx = lbl_800F78E0;
        } else {
            fn_800B27DC(lbl_801F8680, 0);
            if (rec->layer == 0x15) {
                baseMtx = (u8*)lbl_800F78E0 + 0x90;
                lbl_803CBBE0 = lbl_803CC6EC;
                fn_800B216C(GX_TRUE, GX_LEQUAL, GX_FALSE);
            } else {
                if (rec->layer >= 0xf && rec->layer <= 0x16) {
                    lbl_803CBBE0 = lbl_803CC6F0;
                    baseMtx = (u8*)lbl_800F78E0 + 0x30;
                } else {
                    lbl_803CBBE0 = lbl_803CC6F4;
                    baseMtx = (u8*)lbl_800F78E0 + 0x60;
                }
                fn_800B21A8(rec->unk69[8]);
            }
        }

        trans = (Vec*)&rec->unkC[0x30];
        trans->x = rec->pos.x;
        trans->y = rec->pos.y;
        trans->z = rec->pos.z;

        if (rec->playMode != UI_PLAY_STOP) {
            scale = *(f32*)&rec->unk69[3];
            PSMTXScale((void*)rec->unkC, -scale, scale, lbl_803CC6F8);
            PSMTXInverse(returnFloatFromModeIndex(0)->view, mtxB);
            mtxB[0][3] = lbl_803CC6E8;
            mtxB[1][3] = lbl_803CC6E8;
            mtxB[2][3] = lbl_803CC6E8;
            PSMTXConcat(mtxB, (void*)rec->unkC, (void*)rec->unkC);
            PSMTXTrans(mtxB, trans->x, trans->y, trans->z);
            PSMTXConcat(mtxB, (void*)rec->unkC, (void*)rec->unkC);
            PSMTXConcat(returnFloatFromModeIndex(0)->view, (void*)rec->unkC, (void*)rec->unkC);
            *(u32*)rec->unk74 = rec->rgba;
        } else {
            if (rec->parent == NULL) {
                slot = &textureContainerSlots[rec->textureSlot];
                trans->x = trans->x - (f32)(((u16*)slot->layout)[0] >> 1);
                trans->y = trans->y - (f32)(((u16*)slot->layout)[1] >> 1);
                *(u32*)rec->unk74 = rec->rgba;
                PSMTXIdentity(rec->anchor);
            }
            trans->z = lbl_803CC6E8;
            PSMTXTrans((void*)rec->unkC, trans->x, trans->y, lbl_803CC6E8);
            PSMTXConcat(rec->anchor, (void*)rec->unkC, (void*)rec->unkC);
        }

        lbl_803CBBE4 = rec->playMode;
        rgba = *(u32*)rec->unk74;

        for (j = 0; j < 10; j++) {
            if (rec->textureOverride[j] != UI_NO_OVERRIDE) {
                slot = &textureContainerSlots[rec->textureSlot];
                elementTable = *(u32**)((u8*)slot->layout + 8);
                element = (u32*)elementTable[2 + rec->elementIndex];
                part = element[2 + j];
                fn_8000CC4C(slot->layout, (void*)part, &rec->textureOverride[j], 6, 2);
            }
        }

        if (rec->parent == NULL) {
            PSMTXConcat(baseMtx, (void*)rec->unkC, mtxA);
        } else {
            PSMTXCopy((void*)rec->unkC, mtxA);
        }

        lbl_803CBC9C = rec;
        if (!(rec->flags & UI_FLAG_TEXT)) {
            slot = &textureContainerSlots[rec->textureSlot];
            result = handleUIAction(&rec->frame, slot->layout, rec->elementIndex, mtxA, 0, rgba, &arg6,
                                    slot->textures);
            rec->unk69[0] = result;
        }

        rec->attachedThisFrame = 0;
        if (rec->playMode == UI_PLAY_FORWARD) {
            result = rec->unk69[0];
            if (result == 1) {
                rec->frame = 0;
            } else if (result != 2 && result != 3) {
                rec->frame += rec->rate;
            }
        } else if (rec->playMode == UI_PLAY_BACKWARD) {
            if (rec->frame > rec->rate) {
                rec->frame -= rec->rate;
            } else {
                rec->frame = 0;
            }
        }

        if (rec->flags & UI_FLAG_TEXT) {
            fn_8000F534(rec, 1);
        }
    }

    k = 1;
    do {
        fn_800B24D4(k);
        fn_800B21A8(0);
        DrawTextOnCondition(k);
        k++;
    } while (k < 9);
    fn_800B24D4(2);
}

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
