#include "C3/actor/act.h"
#include "C3/skinning/SKNControl.h"
#include "C3/skinning/GQRSetup.h"
#include "C3/geoPalette.h"
#include "C3/geoPalette/DisplayObject.h"
#include "Unknown/File_0x800bde8c.h"
#include "C3/skinning.h"
#include "C3/actor.h"
#include "C3/anim.h"

void ProcessActorBonesForShadows(ActorLayoutFile* layout) {
    int i;
    DODisplayData* pal = (DODisplayData*)layout->header.geoPaletteName;
    struct DODisplayObj* obj;

    for (i = 0; i < layout->header.totalBones; i++) {
        if ((layout->bones[i].pad16 & 0x18) && layout->bones[i].geoFileID != 0xFFFF) {
            obj = (struct DODisplayObj*)pal->descriptorArray[layout->bones[i].geoFileID].layout;
            updateMemoryLocation(obj, ShouldDrawShadows()->unk08);
        }
    }
}

void fn_800B2B4C(UnkB2B4C* obj, f32 value) {
    obj->value90 = value;
}

void fn_800B2B54(UnkB2B4C* obj, u16 index, u8 value) {
    obj->entries[index]->value134 = value;
}

void Set_FUN_800b2b6c(UnkB2B4C* obj, s32 value) {
    obj->value88 = value;
}

void callDSInsertListObject(UnkB2B4C* obj, u16 index) {
    DSInsertListObject(&obj->drawPriorityList, obj->drawPriorityList.Tail, (Ptr)obj->entries[index]);
}

struct DODisplayObj* fn_800B2BA8(Actor* actor, u16 bone, Actor* src, u16 srcBone) {
    sBone* dst = actor->boneArray[bone];
    struct DODisplayObj* prev = dst->dispObj;

    if (src != NULL) {
        dst->dispObj = src->boneArray[srcBone]->dispObj;
    } else {
        dst->dispObj = NULL;
    }
    return prev;
}

void fn_800B2BE4(Actor* actor, u16 bone) {
    sBone* b = actor->boneArray[bone];

    b->dispObj = b->unk18;
}

void fn_800B2BFC(StadiumModelNode* node, u16 arg1, u16 arg2) {
    Actor* actor = (Actor*)node;

    actor->unk80 = arg1;
    actor->unk82 = arg2;
}

void fn_800B2C08(Actor* actor, u16 value) {
    actor->unk84 = value;
}

void fn_800B2C10(Actor* actor, u16 bone, Vec* vec) {
    PSMTXMultVec(((Mtx*)actor->forwardMtxArray)[bone], vec, vec);
}

/* MSSB's actor is larger than the SDK's `Actor` in C3/actor.h; the
 * per-bone forward matrix array sits at 0x60 here. */
typedef struct {
    /* 0x00 */ u8 _00[0x60];
    /* 0x60 */ Mtx* forwardMtxArray;
} ActorBoneMtxView;

void maybeTransformVectorByAnimationMatrix(void* actor, u16 boneIndex, Vec* out) {
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;
    PSMTXMultVec(((ActorBoneMtxView*)actor)->forwardMtxArray[boneIndex], out, out);
}

void fn_800B2C88(Actor* actor, u16 bone, Mtx out) {
    PSMTXCopy(((Mtx*)actor->forwardMtxArray)[bone], out);
}

void ACTSort(Actor* actor) {
    u16 i;
    Ptr cursor;

    actor->drawPriorityList.Head = NULL;
    actor->drawPriorityList.Tail = NULL;
    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->dispObj != NULL) {
            cursor = actor->drawPriorityList.Head;
            while (cursor != NULL) {
                if (((sBone*)cursor)->drawingPriority > actor->boneArray[i]->drawingPriority) {
                    break;
                }
                cursor = ((sBone*)cursor)->drawPriorityLink.Next;
            }
            DSInsertListObject(&actor->drawPriorityList, cursor, (Ptr)actor->boneArray[i]);
        }
    }
}

void fn_800B2D5C(Actor* actor) {
    GQRSetup5(8, 4, 8, 4);
    if (actor->skinObject->positionData->quantizeInfo == 0x40) {
        SKNIt(actor->boneArray, actor->skHeader, actor->skinObject->positionData->positionArray);
    } else {
        processModelDataRelated(actor->boneArray, actor->skHeader, actor->skinObject->positionData->positionArray);
    }
}

void actorBoneRelated(Actor* actor, sBone* bone, MtxPtr parentMtx) {
    Mtx local;
    Mtx tmp;
    Mtx rot;
    sBone* parent;
    sBone* parentBone;
    f32 weight;
    u16 index;
    u8 axis;

    switch (bone->unk134 & 3) {
    case 0:
        weight = 1.0f;
        break;
    case 1:
        weight = actor->unk8C;
        break;
    case 2:
        weight = actor->unk8C * actor->unk8C;
        break;
    default:
        weight = 1.0f;
        break;
    }

    for (index = 0; index < actor->totalBones; index++) {
        if (actor->boneArray[index]->boneID == bone->boneID) {
            break;
        }
    }

    parent = (sBone*)bone->branch.Parent;
    if (parent != NULL) {
        actorBoneRelated(actor, parent, parentMtx);
    }

    if (bone->unk134 & 0x20) {
        if (bone->unk134 & 0x4) {
            *(f32*)((u8*)bone + 0xC4) = *(f32*)((u8*)bone + 0x80);
        }
        if (bone->unk134 & 0x8) {
            *(f32*)((u8*)bone + 0xC8) = *(f32*)((u8*)bone + 0x84);
        }
        if (bone->unk134 & 0x10) {
            *(f32*)((u8*)bone + 0xCC) = *(f32*)((u8*)bone + 0x88);
        }
    }

    if (bone->animationCtrl.type == 0) {
        CTRLBuildMatrix(&bone->orientationCtrl, local);
    } else {
        if (actor->unk88 == NULL) {
            fn_800B84AC(&bone->animationCtrl, &bone->unkA4, &bone->animationCtrl, weight);
            CTRLBuildMatrix(&bone->animationCtrl, local);
        } else {
            parentBone = actor->boneArray[actor->unk88[index]];
            if (actor->unk94 == NULL || actor->unk94(bone, parentBone, local, weight) == 0) {
                parentBone = actor->boneArray[actor->unk88[index]];
                fn_800B84AC(&parentBone->animationCtrl, &parentBone->unkA4, &parentBone->animationCtrl, weight);
                if (parent != NULL) {
                    CTRLBuildMatrix_FlipY(&parentBone->animationCtrl, local);
                } else {
                    CTRLBuildMatrix_FlipX(&parentBone->animationCtrl, local);
                }

                axis = bone->unk137;
                if (axis == 1) {
                    PSMTXRotRad(rot, 'X', 3.1415927f);
                    PSMTXConcat(rot, local, local);
                } else if (axis == 2) {
                    PSMTXRotRad(rot, 'Y', 3.1415927f);
                    PSMTXConcat(rot, local, local);
                } else if (axis == 3) {
                    PSMTXRotRad(rot, 'Z', 3.1415927f);
                    PSMTXConcat(rot, local, local);
                }
            }
        }

        if (bone->animPipe->replaceHierarchyCtrl == 0) {
            CTRLBuildMatrix(&bone->orientationCtrl, tmp);
            PSMTXConcat(tmp, local, local);
        }
    }

    if (bone->inheritanceFlag == 1 && parent != NULL) {
        PSMTXConcat(parent->forwardMtx, local, bone->forwardMtx);
    } else {
        PSMTXConcat(parentMtx, local, bone->forwardMtx);
    }
}

void f_BuildBoneSkinOrientationMatrix(sBone* root, MtxPtr out) {
    sBone* node;
    Mtx local;
    Mtx world;

    for (node = root; node != NULL; node = (sBone*)node->branch.Next) {
        if (node->inheritanceFlag == 1) {
            CTRLBuildMatrix(&node->orientationCtrl, local);
            PSMTXConcat(out, local, world);
            PSMTXInverse(world, node->orientationInvMtx);
        } else {
            CTRLBuildInverseMatrix(&node->orientationCtrl, node->orientationInvMtx);
        }
        if (node->branch.Children != NULL) {
            f_BuildBoneSkinOrientationMatrix((sBone*)node->branch.Children, world);
        }
    }
}

BOOL maybeBallRelated(Actor** actor, ActorLayout* layout, u16 actorID) {
    layout->actorID = actorID;
    *actor = maybeProcessActLayout(layout);
    return TRUE;
}

void InitBone(sBone* parent, ActorBone* node, Actor* actor, u16* index, sBone* bones) {
    sBone* bone;
    u32* dst;
    u32* src;
    s32 k;

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
            dst = (u32*)&bone->orientationCtrl;
            src = (u32*)node->orientationCtrl;
            for (k = 0; k < 9; k++) {
                dst[k] = src[k];
            }
        }

        bone->dispObj = NULL;
        if (node->geoFileID != 0xFFFF) {
            DOGet(&bone->dispObj, actor->pal, node->geoFileID, NULL);
        }
        bone->unk18 = bone->dispObj;
        bone->animPipe = NULL;
        bone->animationCtrl.type = 0;
        bone->unkA4.type = 0;
        bone->unk134 = 1;
        bone->unk136 = 0;
        bone->unk137 = 0;

        bone->forwardMtx = (MtxPtr)((u8*)actor->forwardMtxArray + *index * 0x30);
        PSMTXIdentity(bone->forwardMtx);
        if (actor->skinObject != NULL) {
            bone->skinMtx = (MtxPtr)((u8*)actor->skinMtxArray + *index * 0x30);
            PSMTXIdentity(bone->skinMtx);
            bone->orientationInvMtx = (MtxPtr)((u8*)actor->orientationInvMtxArray + *index * 0x30);
            PSMTXIdentity(bone->orientationInvMtx);
            if (actor->skinObject->lightingData != NULL) {
                bone->skinInvTransposeMtx = (MtxPtr)((u8*)actor->skinInvTransposeMtxArray + *index * 0x30);
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
            InitBone(bone, (ActorBone*)node->branch.Children, actor, index, bones);
        }
        node = (ActorBone*)node->branch.Next;
    }
}

static u32 align32(u32 size) {
    return (size + 0x1F) & ~0x1F;
}

Actor* maybeProcessActLayout(ActorLayout* layout) {
    Actor* actor;
    struct DODisplayObj* skin = NULL;
    Mtx worldMtx;
    u16 boneCount = 0;
    u16 i;
    u32 mtxBytes = align32(layout->totalBones * 0x30);
    u32 boneArrayBytes = align32(layout->totalBones * 4);
    u32 skinBytes = 0;
    u32 lightingBytes = 0;
    u32 totalBytes;
    sBone** boneArray;
    sBone* bones;
    sBone* bone;
    MtxPtr forwardMtxArray;

    if (layout->skinFileID != 0xFFFF) {
        DOGet(&skin, (DODisplayDataPtr)layout->geoPaletteName, layout->skinFileID, NULL);
        skinBytes = mtxBytes;
        if (skin->lightingData != NULL) {
            lightingBytes = mtxBytes;
        }
    }

    totalBytes = boneArrayBytes + mtxBytes + skinBytes + skinBytes + lightingBytes
               + align32(layout->totalBones * sizeof(sBone)) + sizeof(Actor);
    actor = (Actor*)_OSAllocFromHeap(0x20, totalBytes);

    boneArray = (sBone**)((u8*)actor + sizeof(Actor));
    forwardMtxArray = (MtxPtr)((u8*)boneArray + boneArrayBytes);

    actor->layout = layout;
    actor->boneArray = boneArray;
    actor->forwardMtxArray = forwardMtxArray;
    actor->skHeader = NULL;
    actor->actorID = layout->actorID;
    actor->totalBones = layout->totalBones;
    DSInitTree(&actor->hierarchy, NULL, (DSBranchPtr)4);
    DSInitList(&actor->drawPriorityList, NULL, (DSLinkPtr)0xFC);
    PSMTXIdentity(actor->worldControl.controlParams.m);
    actor->pal = (DODisplayDataPtr)layout->geoPaletteName;

    if (layout->skinFileID != 0xFFFF) {
        actor->skinObject = skin;
        actor->skinMtxArray = (MtxPtr)((u8*)forwardMtxArray + mtxBytes);
        actor->orientationInvMtxArray = (MtxPtr)((u8*)actor->skinMtxArray + skinBytes);
        actor->skinInvTransposeMtxArray = (MtxPtr)((u8*)actor->orientationInvMtxArray + skinBytes);
        DOSetWorldMatrix(actor->skinObject, worldMtx);
    } else {
        actor->skinObject = NULL;
        actor->skinMtxArray = NULL;
        actor->orientationInvMtxArray = NULL;
        actor->skinInvTransposeMtxArray = NULL;
    }

    bones = (sBone*)((u8*)forwardMtxArray + mtxBytes + skinBytes + skinBytes + lightingBytes);
    InitBone(NULL, (ActorBone*)layout->hierarchy.Root, actor, &boneCount, bones);
    if (boneCount != layout->totalBones) {
        OSPanic("actorlayout", 0x1F0, "bone count mismatch");
    }

    if (actor->skinObject != NULL) {
        f_BuildBoneSkinOrientationMatrix((sBone*)actor->hierarchy.Root, worldMtx);
    }

    actor->unk80 = 0;
    actor->unk82 = 0;
    actor->unk84 = 0;
    actor->unk88 = NULL;
    actor->unk8C = 1.0f;
    actor->unk90 = 0.0f;
    actor->unk94 = 0;
    actor->unk98 = 0;
    actor->unk99 = 0;

    for (i = 0; i < actor->totalBones; i++) {
        bone = boneArray[i];
        if (bone->dispObj != NULL) {
            DSListPtr list = &actor->drawPriorityList;
            Ptr cursor = list->Head;

            while (cursor != NULL && ((sBone*)cursor)->drawingPriority <= bone->drawingPriority) {
                cursor = ((sBone*)cursor)->drawPriorityLink.Next;
            }
            DSInsertListObject(list, cursor, (Ptr)bone);
        }
    }

    PSMTXIdentity(worldMtx);
    return actor;
}

void fn_800B4724(Actor* actor, int value) {
    actor->skHeader = (sHdr*)value;
}

void renderingRelated(void) {
    return;
}

void haveActLayoutPointToGeoHeader(void* layout, void* geo) {
    ((ActorLayout*)layout)->geoPaletteName = geo;
}

void LoadActorLayout(void* data) {
    ActorLayoutFile* layout = data;
    ActorBone* bone;
    u32 i;

    if (layout->header.userDataSize && layout->header.userData) {
        layout->header.userData = (char*)((u32)layout->header.userData + (u32)layout);
    }
    if (layout->header.hierarchy.Root) {
        layout->header.hierarchy.Root = (Ptr)((u32)layout->header.hierarchy.Root + (u32)layout);
    }
    if (layout->header.geoPaletteName) {
        layout->header.geoPaletteName = (char*)((u32)layout->header.geoPaletteName + (u32)layout);
    }
    bone = layout->bones;
    for (i = 0; i < layout->header.totalBones; i++) {
        if (bone->orientationCtrl) {
            bone->orientationCtrl = (Control*)((u32)layout + (u32)bone->orientationCtrl);
        }
        if (bone->branch.Prev) {
            bone->branch.Prev = (Ptr)((u32)layout + (u32)bone->branch.Prev);
        }
        if (bone->branch.Next) {
            bone->branch.Next = (Ptr)((u32)layout + (u32)bone->branch.Next);
        }
        if (bone->branch.Parent) {
            bone->branch.Parent = (Ptr)((u32)layout + (u32)bone->branch.Parent);
        }
        if (bone->branch.Children) {
            bone->branch.Children = (Ptr)((u32)layout + (u32)bone->branch.Children);
        }
        bone++;
    }
}

void AdjustActorPointers(void* data) {
    ActorLayoutFile* layout = data;
    int i;

    layout->header.hierarchy.Offset = (u32)layout + layout->header.hierarchy.Offset;
    layout->header.hierarchy.Root = (Ptr)((u32)layout + (u32)layout->header.hierarchy.Root);
    layout->header.geoPaletteName = (char*)((u32)layout + (u32)layout->header.geoPaletteName);
    layout->header.userData = (char*)((u32)layout + (u32)layout->header.userData);
    for (i = 0; i < layout->header.totalBones; i++) {
        layout->bones[i].orientationCtrl = (Control*)((u32)layout + (u32)layout->bones[i].orientationCtrl);
    }
}
