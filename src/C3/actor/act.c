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

void actorBoneRelated(void) {
    return;
}

void f_BuildBoneSkinOrientationMatrix(void) {
    return;
}

BOOL maybeBallRelated(Actor** actor, ActorLayout* layout, u16 actorID) {
    layout->actorID = actorID;
    *actor = maybeProcessActLayout(layout);
    return TRUE;
}

void InitBone(void) {
    return;
}

Actor* maybeProcessActLayout(ActorLayout* layout) {
    return NULL;
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
