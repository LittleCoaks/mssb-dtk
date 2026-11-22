#include <string.h>
#include "Unknown/spani_default.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x8004cc18.h"
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

typedef struct UIAnchorQuery {
    /* 0x00 */ u8 _00[0x64];
    /* 0x64 */ Mtx* matrix;
    /* 0x68 */ u8 rgba[4];
    /* 0x6C */ s16* key; // {parent element index, anchorSub}
} UIAnchorQuery;

extern UIRecord* lbl_803CBC9C;

int fn_80034BCC(UIAnchorQuery* query) {
    UIRecord* child;

    for (child = lbl_803CBC9C->firstChild; child != NULL; child = child->next) {
        if (child->parent->elementIndex == query->key[0] && child->anchorSub == query->key[1]) {
            PSMTXCopy(*query->matrix, (MtxPtr)((u8*)child + 0x78));
            child->unk74[0] = query->rgba[0] * ((u8*)&child->rgba)[0] / 255;
            child->unk74[1] = query->rgba[1] * ((u8*)&child->rgba)[1] / 255;
            child->unk74[2] = query->rgba[2] * ((u8*)&child->rgba)[2] / 255;
            child->unk74[3] = query->rgba[3] * ((u8*)&child->rgba)[3] / 255;
            child->attachedThisFrame = 1;
        }
    }
    return 0;
}

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

void fn_80011140(void);
extern Unk803C5F74 lbl_803C5F74;

void fn_800356B8(void) {
    int i;

    for (i = 0; i < UI_RECORD_COUNT; i++) {
        menuGraphicsStructures[i].parent = NULL;
        menuGraphicsStructures[i].next = NULL;
        menuGraphicsStructures[i].firstChild = NULL;
        menuGraphicsStructures[i].flags = 0;
        PSMTXIdentity((MtxPtr)menuGraphicsStructures[i].unkC);
        graphicsRelatedArray[i].object = NULL;
        graphicsRelatedArray[i].unk4 = 0;
    }
    fn_80011140();
    lbl_803C5F74.unk00 = 0;
}

void fn_80035750(void* buffer, TextureHeader* textures, s32 id) {
    u8 i;
    s8 slot;

    i = 0;
    while (1) {
        if (textureContainerSlots[i].buffer == NULL) {
            slot = (s8)i;
            break;
        }
        i++;
        if (i >= TEXTURE_SLOT_COUNT) {
            slot = -1;
            break;
        }
    }
    if (slot == -1) {
        OSReport(" SabNo = %d not to add  \n", slot);
        OSPanic("spani_default.c", 0x49C, "gasSpani No Empty \n");
    }
    textureContainerSlots[slot].buffer = buffer;
    textureContainerSlots[slot].textures = textures;
    textureContainerSlots[slot].layout = buffer;
    textureContainerTags[slot] = id;
    convertTextureHeader(textureContainerSlots[slot].textures);
    fn_8000B9C8(textureContainerSlots[slot].layout);
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

void fn_80035A00(void) {
    int id;
    int slot;

    for (id = 0; id < 0x19; id++) {
        if (id > 1) {
            slot = findTextureContainerSlot(id);
            if (slot != -1) {
                textureContainerSlots[slot].buffer = NULL;
                textureContainerSlots[slot].textures = NULL;
                textureContainerTags[slot] = -1;
                textureContainerSlots[slot].layout = NULL;
                PSMTXIdentity(textureContainerSlots[slot].mtx);
            }
        }
    }
}

void fn_80035B50(int id) {
    int slot = findTextureContainerSlot(id);

    if (slot != -1) {
        textureContainerTags[slot] = -1;
        fn_800ACFB0(textureContainerSlots[slot].buffer);
        textureContainerSlots[slot].buffer = NULL;
        textureContainerSlots[slot].textures = NULL;
        textureContainerSlots[slot].layout = NULL;
        PSMTXIdentity(textureContainerSlots[slot].mtx);
    }
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

int fn_80035DD4(int id) {
    int i;

    for (i = 0; i < 0x360; i++) {
        if (id == textureContainerTags[i]) {
            return i;
        }
    }
    return -1;
}

void fn_80035ED0(int handle) {
    menuGraphicsStructures[handle].flags = 0;
}

void fn_80035EEC(int frame, int handle) {
    if (menuGraphicsStructures[handle].frame > (u32)(frame << 16)) {
        menuGraphicsStructures[handle].frame = frame << 16;
        menuGraphicsStructures[handle].playMode = 0;
    }
}

u8* fn_80035F20(int id, int handle, u16 index, s16 partSel) {
    int slot = findTextureContainerSlot(id);
    u8* elem;
    u32* partPtr;
    u8* part;
    u8* rec;
    s32 n;
    s32 cnt;

    if (slot == -1) {
        OSPanic("spani_default.c", 0x31C, "It is a number not registered. \n");
    }
    elem = *(u8**)(*(u8**)((u8*)textureContainerSlots[slot].layout + 8) + menuGraphicsStructures[handle].elementIndex * 4 + 8);
    n = *(u32*)elem - 1;
    partPtr = (u32*)(elem + n * 4 + 8);
    if (partSel == -1) {
        part = (u8*)*partPtr;
        cnt = *(u16*)part;
        rec = part + cnt * 0x50 + 4;
        do {
            rec -= 0x50;
        } while (--cnt != 0);
        return rec + index * 0x50;
    }
    do {
        part = (u8*)*partPtr;
        partPtr--;
        cnt = *(u16*)part;
        rec = part + cnt * 0x50 + 4;
        do {
            if (n == partSel) {
                goto found;
            }
            rec -= 0x50;
        } while (--cnt != 0);
    } while (--n != 0);
    return rec;
found:
    if (cnt != 0) {
        do {
            rec -= 0x50;
        } while (--cnt != 0);
    }
    return rec;
}

void fn_80036134(void* scene, int handle, u32 part, int handle2) {
    LayoutFrameInfo info;
    UIRecord* rec = ICON_RECORD(scene, handle);

    fn_8000CEF0(textureContainerSlots[rec->textureSlot].layout, rec->elementIndex, part, rec->frame >> 16, &info);
    ICON_RECORD(scene, handle2)->pos.x = *(s16*)((u8*)&info + 0x1C);
    ICON_RECORD(scene, handle2)->pos.y = *(s16*)((u8*)&info + 0x1E);
}

u32 fn_80036214(void* scene, int handle, u32 part, int frame) {
    LayoutFrameInfo info;
    UIRecord* rec = ICON_RECORD(scene, handle);

    fn_8000CEF0(textureContainerSlots[rec->textureSlot].layout, rec->elementIndex, part, frame, &info);
    return *(u32*)((u8*)&info + 0x1C);
}

void fn_80036270(void* scene, int handle, u32 part, int frame, s16* outX, s16* outY) {
    LayoutFrameInfo info;
    UIRecord* rec = ICON_RECORD(scene, handle);

    fn_8000CEF0(textureContainerSlots[rec->textureSlot].layout, rec->elementIndex, part, frame, &info);
    *outX = *(s16*)((u8*)&info + 0x1C);
    *outY = *(s16*)((u8*)&info + 0x1E);
}

void fn_800362F0(void* scene, int handle) {
    int i;

    for (i = 0; i < 10; i++) {
        ICON_RECORD(scene, handle)->textureOverride[i] = UI_NO_OVERRIDE;
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

void fn_8003656C(DrawingSceneStruct* node, int slot, int handle, int elementBase, int state) {
    u32 color;
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
        color = *(u32*)((u8*)&info + 0x1C);
    } else {
        color = 0;
    }
    handle = handle * 4 + 8;
    part = *(u8**)(*(u8**)(*(u8**)((u8*)textureContainerSlots[slotIndex].layout + 8) + element * 4 + 8) + handle);
    sub = part + 4;
    fn_8000CC4C(textureContainerSlots[slotIndex].layout, part, (u16*)&color, (u32)(sub + 0x1C) - (u32)sub, 4);
}

void fn_8003664C(int id, int handle, u16 value, s16 partSel) {
    int slot = findTextureContainerSlot(id);
    u8* elem;
    u32* partPtr;
    u8* part;
    u8* rec;
    s32 n;
    s32 cnt;

    if (slot == -1) {
        OSPanic("spani_default.c", 0x15E, "It is a number not registered. \n");
    }
    elem = *(u8**)(*(u8**)((u8*)textureContainerSlots[slot].layout + 8) + menuGraphicsStructures[handle].elementIndex * 4 + 8);
    n = *(u32*)elem - 1;
    partPtr = (u32*)(elem + n * 4 + 8);
    do {
        part = (u8*)*partPtr;
        partPtr--;
        cnt = *(u16*)part;
        rec = part + cnt * 0x50 + 4;
        do {
            rec -= 0x50;
            cnt--;
            if (rec[4] != 0 && n == partSel) {
                *(u16*)(rec + 6) = value;
            }
        } while (cnt != 0);
    } while (--n != 0);
}

u16 fn_80036824(int id, int handle, u16 index) {
    int slot = findTextureContainerSlot(id);
    u8* elem;
    u32* partPtr;
    u8* part;
    u8* rec;
    s32 n;
    s32 cnt;

    if (slot == -1) {
        OSPanic("spani_default.c", 0x12A, "It is a number not registered. \n");
    }
    elem = *(u8**)(*(u8**)((u8*)textureContainerSlots[slot].layout + 8) + handle * 4 + 8);
    n = *(u32*)elem - 1;
    partPtr = (u32*)(elem + n * 4 + 8);
    do {
        part = (u8*)*partPtr;
        partPtr--;
        cnt = *(u16*)part;
        rec = part + cnt * 0x50 + 4;
        do {
            cnt--;
            rec -= 0x50;
            if (cnt == index) {
                return *(u16*)(rec + 6);
            }
        } while (cnt != 0);
    } while (--n != 0);
    return 0;
}

extern u8 lbl_80366188[];
extern u8 lbl_801F86C0[];

void fn_800369DC(f32 scale) {
    f32 inv;

    if (0.0f != scale) {
        inv = 1.0f / scale;
        C_MTXFrustum((f32(*)[4])lbl_801F8640, -0.175f * inv, 0.175f * inv, 0.25f * inv, -0.25f * inv, 1.0f, 512.0f);
    }
}

void fn_800B2854(void* a, s32 b, void* c, s32 d, s32 e, s32* f, s32 g);
void fn_800B27A4(s32 a);
void fn_800B0D38(s32 a, s32 b);
extern f32 lbl_803CBBDC;

void fn_80036A3C(void) {
    s32 arr[0x17];
    s32 i;

    C_MTXFrustum((f32(*)[4])lbl_801F8680, -0.175f, 0.175f, -0.25f, 0.25f, 1.0f, 512.0f);
    for (i = 0; i < 0x17; i++) {
        if (i == 0) {
            arr[i] = 0xD;
        } else if (i >= 1 && i < 10) {
            arr[i] = 0xC;
        } else if (i == 10) {
            arr[i] = 0xB;
        } else if (i == 11) {
            arr[i] = 0xA;
        } else if (i == 12) {
            arr[i] = 9;
        } else if (i >= 13 && i < 15) {
            arr[i] = 0xB;
        } else {
            arr[i] = 0xC;
        }
    }
    fn_800B2854(lbl_801F86C0, 0x45000, lbl_801F8680, 0, 0x17, arr, 0);
    fn_800B27A4(10);
    for (i = 0xD; i < 0x17; i++) {
        fn_800B0D38(i, 2);
    }
    for (i = 0; i < UI_RECORD_COUNT; i++) {
        textureContainerTags[i] = -1;
    }
    lbl_803CBBE4 = 0;
    lbl_803CBBE0 = 2.0f;
    lbl_803CBBDC = 1280.0f;
    memset(menuGraphicsStructures, 0, sizeof(menuGraphicsStructures));
    lbl_80366188[0x84] = 0;
    lbl_80366188[0x88] = 0;
}
