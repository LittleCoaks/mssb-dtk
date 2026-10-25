#include "Unknown/objinit.h"
#include "Unknown/File_0x80023b04.h"
#include "C3/anim.h"
#include "C3/geoPalette.h"
#include "C3/skinning.h"
#include "string.h"

extern u8* lbl_8017EB40[28];
extern u32 lbl_803CBC58;

void fn_800B4724(Actor* actor, int value);
u8* fn_80023078(struct DODisplayObj* dispObj, DODisplayLayout* layout, u8* cursor);

#define COPY_WORDS8(dst, src)                                                                       \
    do {                                                                                            \
        ((u32*)(dst))[0] = ((const u32*)(src))[0];                                                  \
        ((u32*)(dst))[1] = ((const u32*)(src))[1];                                                  \
    } while (0)

#define COPY_WORDS12(dst, src)                                                                      \
    do {                                                                                            \
        COPY_WORDS8(dst, src);                                                                      \
        ((u32*)(dst))[2] = ((const u32*)(src))[2];                                                  \
    } while (0)

#define COPY_WORDS16(dst, src)                                                                      \
    do {                                                                                            \
        COPY_WORDS12(dst, src);                                                                     \
        ((u32*)(dst))[3] = ((const u32*)(src))[3];                                                  \
    } while (0)

u8* f_InitBone(sBone* parent, ActorBone* node, Actor* actor, u16* index, sBone* bones, u8* cursor) {
    sBone* bone;

    while (node != NULL) {
        bone = &bones[*index];
        bone->branch.Children = NULL;
        DSInsertBranchBelow(&actor->hierarchy, (Ptr)parent, (Ptr)bone);
        actor->boneArray[*index] = bone;

        bone->boneID = node->boneID;
        bone->inheritanceFlag = node->inheritanceFlag;
        bone->drawingPriority = node->drawingPriority;
        bone->orientationCtrl.type = 0;
        if (node->orientationCtrl != NULL) {
            bone->orientationCtrl = *node->orientationCtrl;
        }

        bone->dispObj = NULL;
        if (node->geoFileID != 0xFFFF) {
            if (node->geoFileID < actor->pal->numDescriptors) {
                bone->dispObj = (struct DODisplayObj*)cursor;
                cursor = fn_80023078(bone->dispObj, actor->pal->descriptorArray[node->geoFileID].layout, cursor + 0x80);
            } else {
                OSReport("Display object id %d is greater than number of objects %d", node->geoFileID,
                         actor->pal->numDescriptors);
            }
        }

        bone->unk18 = bone->dispObj;
        bone->animPipe = NULL;
        bone->animationCtrl.type = 0;
        bone->unkA4.type = 0;
        bone->animPipe = (struct ANIMPipe*)cursor;
        cursor += 0x20;
        bone->animPipe->time = 0.0f;
        bone->animPipe->unk04 = 0.0f;
        bone->animPipe->unk08 = 1.0f;
        bone->animPipe->currentTrack = NULL;
        bone->animPipe->control = NULL;
        bone->animPipe->unk14 = 0;
        bone->animPipe->replaceHierarchyCtrl = 0;
        bone->animPipe->unk17 = 1;
        bone->animPipe->unk18 = 1;

        bone->unk134 = 1;
        bone->unk136 = 0;
        bone->unk137 = 0;

        bone->forwardMtx = actor->forwardMtxArray + *index;
        PSMTXIdentity(bone->forwardMtx);
        if (actor->skinObject != NULL) {
            bone->skinMtx = actor->skinMtxArray + *index;
            PSMTXIdentity(bone->skinMtx);
            bone->orientationInvMtx = actor->orientationInvMtxArray + *index;
            PSMTXIdentity(bone->orientationInvMtx);
            if (actor->skinObject->lightingData != NULL) {
                bone->skinInvTransposeMtx = actor->skinInvTransposeMtxArray + *index;
                PSMTXIdentity(bone->skinInvTransposeMtx);
            } else {
                bone->skinInvTransposeMtx = NULL;
            }
        } else {
            bone->skinMtx = NULL;
            bone->orientationInvMtx = NULL;
            bone->skinInvTransposeMtx = NULL;
        }

        (*index)++;
        if (node->branch.Children != NULL) {
            cursor = f_InitBone(bone, (ActorBone*)node->branch.Children, actor, index, bones, cursor);
        }
        node = (ActorBone*)node->branch.Next;
    }
    return cursor;
}

u8* fn_80023078(struct DODisplayObj* dispObj, DODisplayLayout* layout, u8* cursor) {
    u8* next = cursor;

    if (layout->positionData != NULL) {
        dispObj->positionData = (PositionData*)cursor;
        COPY_WORDS8(dispObj->positionData, layout->positionData);
        next = cursor + 0x20;
    } else {
        dispObj->positionData = NULL;
    }

    if (layout->colorData != NULL) {
        dispObj->colorData = (ColorData*)next;
        next += 0x20;
        COPY_WORDS8(dispObj->colorData, layout->colorData);
    } else {
        dispObj->colorData = NULL;
    }

    if (layout->textureData != NULL && layout->numTextureChannels != 0) {
        u16 i;
        u8 count = layout->numTextureChannels;

        dispObj->textureData = (TextureData*)next;
        dispObj->numTextureChannels = count;
        next += (count * 0x10 + 0x1F) & ~0x1F;
        for (i = 0; i < count; i++) {
            COPY_WORDS16((u8*)dispObj->textureData + i * 0x10, (u8*)layout->textureData + i * 0x10);
        }
    } else {
        dispObj->textureData = NULL;
        dispObj->numTextureChannels = 0;
    }

    if (layout->lightingData != NULL) {
        dispObj->lightingData = (LightingData*)next;
        next += 0x20;
        COPY_WORDS12(dispObj->lightingData, layout->lightingData);
    } else {
        dispObj->lightingData = NULL;
    }

    if (layout->displayData != NULL) {
        dispObj->displayData = (DisplayData*)next;
        next += 0x20;
        COPY_WORDS12(dispObj->displayData, layout->displayData);
    } else {
        dispObj->displayData = NULL;
    }

    dispObj->visibility = 1;
    PSMTXIdentity(dispObj->worldMatrix);
    dispObj->shaderFunc = NULL;
    dispObj->shaderData = NULL;
    dispObj->pad8 = layout->pad8;
    memcpy(&dispObj->unk58, layout->unk20, 4);
    memcpy(&dispObj->unk54, layout->unk1C, 4);
    memcpy(&dispObj->unk60, layout->unk28, 4);
    memcpy(&dispObj->unk5C, layout->unk24, 4);
    memcpy(&dispObj->unk68, layout->unk30, 4);
    memcpy(&dispObj->unk64, layout->unk2C, 4);
    return next;
}

#pragma dont_inline on
Actor* f_InitActorWithLayout(ActorLayout* layout, void* buffer) {
    u8* cursor = buffer;
    Actor* actor;
    u16 boneCount = 0;
    Mtx worldMtx;
    struct DODisplayObj* skinObj = NULL;
    u32 skinMtxSize = 0;
    u32 orientationInvSize = 0;
    u32 skinInvTransposeSize = 0;
    u32 boneArraySize;
    u32 mtxSize;
    u32 total;
    u32 boneSize;
    sBone* bones;
    s32 normalOffset;
    u32 i;

    boneArraySize = (layout->totalBones * 4 + 0x1F) & ~0x1F;
    mtxSize = (layout->totalBones * 0x30 + 0x1F) & ~0x1F;

    if (layout->skinFileID != 0xFFFF) {
        DODisplayDataPtr pal = (DODisplayDataPtr)layout->geoPaletteName;

        if (layout->skinFileID < pal->numDescriptors) {
            skinObj = (struct DODisplayObj*)cursor;
            cursor = fn_80023078(skinObj, pal->descriptorArray[layout->skinFileID].layout, cursor + 0x80);
        } else {
            OSReport("Display object id %d is greater than number of objects %d", layout->skinFileID,
                     pal->numDescriptors);
            skinObj = NULL;
        }
        skinMtxSize = (layout->totalBones * 0x30 + 0x1F) & ~0x1F;
        orientationInvSize = skinMtxSize;
        if (skinObj->lightingData != NULL) {
            skinInvTransposeSize = skinMtxSize;
        }
    }

    actor = (Actor*)cursor;
    actor->boneArray = (sBone**)(cursor + 0xA0);
    actor->forwardMtxArray = (MtxPtr)((u8*)actor->boneArray + boneArraySize);
    actor->skinObject = skinObj;

    total = boneArraySize + mtxSize + skinMtxSize + orientationInvSize + skinInvTransposeSize;
    boneSize = (layout->totalBones * 0x140 + 0x1F) & ~0x1F;
    cursor += (total + boneSize + 0xBF) & ~0x1F;
    actor->skHeader = NULL;

    PSMTXIdentity(worldMtx);
    actor->actorID = layout->actorID;
    actor->layout = layout;
    actor->totalBones = layout->totalBones;
    DSInitTree(&actor->hierarchy, NULL, (DSBranchPtr)4);
    DSInitList(&actor->drawPriorityList, NULL, (DSLinkPtr)0xFC);
    actor->pal = NULL;
    if (layout->geoPaletteName != NULL) {
        actor->pal = (DODisplayDataPtr)layout->geoPaletteName;
    }

    if (layout->skinFileID != 0xFFFF) {
        DOSetWorldMatrix(actor->skinObject, worldMtx);
        actor->skinMtxArray = (MtxPtr)((u8*)actor->forwardMtxArray + mtxSize);
        actor->orientationInvMtxArray = (MtxPtr)((u8*)actor->skinMtxArray + skinMtxSize);

        {
            DODisplayDataPtr pal = (DODisplayDataPtr)layout->geoPaletteName;
            normalOffset = (char*)actor->skinObject->lightingData->normalArray -
                           (char*)actor->skinObject->positionData->positionArray;
            for (i = 0; i < pal->numDescriptors; i++) {
                PositionData* pos = pal->descriptorArray[i].layout->positionData;

                if (pos->compCount == 6) {
                    actor->skinObject->positionData->positionArray = pos->positionArray;
                    actor->skinObject->lightingData->normalArray = pos->positionArray + normalOffset;
                    break;
                }
            }
        }

        if (actor->skinObject->lightingData != NULL) {
            actor->skinInvTransposeMtxArray = (MtxPtr)((u8*)actor->orientationInvMtxArray + orientationInvSize);
        } else {
            actor->skinInvTransposeMtxArray = NULL;
        }
    } else {
        actor->skinObject = NULL;
        actor->skinMtxArray = NULL;
        actor->orientationInvMtxArray = NULL;
        actor->skinInvTransposeMtxArray = NULL;
    }

    actor->worldControl.type = 0;
    bones = (sBone*)((u8*)actor->forwardMtxArray + mtxSize + skinMtxSize + orientationInvSize + skinInvTransposeSize);
    if (layout->hierarchy.Root != NULL) {
        f_InitBone(NULL, (ActorBone*)layout->hierarchy.Root, actor, &boneCount, bones, cursor);
    }
    if (boneCount != actor->totalBones) {
        OSPanic("objinit.c", 521, "Incorrect number of bones in actor");
    }
    if (actor->skinObject != NULL) {
        BuildBoneSkinOrientationMatrix((sBone*)actor->hierarchy.Root, worldMtx);
    }

    ACTSort(actor);
    actor->unk80 = 0;
    actor->unk82 = 0;
    actor->unk84 = 0;
    actor->unk88 = NULL;
    actor->unk8C = 1.0f;
    actor->unk90 = 0.0f;
    actor->unk99 = 0;
    actor->unk98 = 0;
    actor->unk94 = NULL;
    return actor;
}
#pragma dont_inline reset

void BuildBoneSkinOrientationMatrix(sBone* node, MtxPtr out) {
    Mtx local;
    Mtx world;

    while (node != NULL) {
        if (node->inheritanceFlag == 1) {
            CTRLBuildMatrix(&node->orientationCtrl, local);
            PSMTXConcat(out, local, world);
            PSMTXInverse(world, node->orientationInvMtx);
        } else {
            CTRLBuildInverseMatrix(&node->orientationCtrl, node->orientationInvMtx);
        }
        if (node->branch.Children != NULL) {
            BuildBoneSkinOrientationMatrix((sBone*)node->branch.Children, world);
        }
        node = (sBone*)node->branch.Next;
    }
}

void fn_800238E0(ActorObjectTable* table, u16 index, u16 slot, ActorLayout* layout) {
    ActorObjectEntry* entry = &table->entries[index];

    memset(lbl_8017EB40[index], 0, lbl_803CBC58);
    layout->actorID = slot;
    entry->actor = f_InitActorWithLayout(layout, lbl_8017EB40[index]);
    entry->seqNum = 0;
    entry->speed = 1.0f;
    entry->unk64 = 0;
    entry->unk66 = 0;
    entry->unk68 = 0;
    entry->drawArgCount = 0;
    entry->drawArgs[0] = 0;
    entry->drawArgs[1] = 0;
    entry->drawArgs[2] = 0;
    entry->drawArgs[3] = 0;
    entry->drawArgs[4] = 0;
    entry->drawArgs[5] = 0;
    entry->drawArgs[6] = 0;
    entry->drawArgs[7] = 0;
    entry->slot = slot;
    entry->applyControl = 1;
    entry->callback = NULL;
}

void characterAndBallDisplayRelated(ActorObjectEntry* entry, u16 buffer, u16 slot, ActorLayout* layout, void* anim,
                                    int arg5) {
    memset(lbl_8017EBB0[buffer], 0, actorSize);
    layout->actorID = slot;
    entry->actor = f_InitActorWithLayout(layout, lbl_8017EBB0[(u16)buffer]);
    fn_800B4724(entry->actor, arg5);
    entry->seqNum = 0;
    entry->speed = 1.0f;
    entry->unk64 = 0;
    entry->unk66 = 0;
    entry->unk68 = 0;
    entry->drawArgCount = 0;
    entry->drawArgs[0] = 0;
    entry->drawArgs[1] = 0;
    entry->drawArgs[2] = 0;
    entry->drawArgs[3] = 0;
    entry->drawArgs[4] = 0;
    entry->drawArgs[5] = 0;
    entry->drawArgs[6] = 0;
    entry->drawArgs[7] = 0;
    entry->slot = slot;
    entry->applyControl = TRUE;
    if (anim != NULL) {
        entry->anim = anim;
        entry->animPending = TRUE;
        entry->speedPending = TRUE;
        entry->framePending = TRUE;
        entry->blendTime = 0.0f;
        if (entry->actor != NULL) {
            entry->actor->unk99 = 0;
        }
    }
    entry->callback = NULL;
}
