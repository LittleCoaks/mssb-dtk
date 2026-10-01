#include "Unknown/File_0x800b4bc8.h"
#include "C3/actor.h"
#include "C3/anim.h"
#include "C3/skinning.h"

void setAllBoneEventFlags(void* obj, BOOL flag) {
    Actor* actor = obj;
    u32 i;

    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->animPipe != NULL) {
            actor->boneArray[i]->animPipe->unk17 = flag;
        }
    }
}

void fn_800B4C04(void* obj, f32 speed) {
    Actor* actor = obj;
    u32 i;

    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->animPipe != NULL) {
            actor->boneArray[i]->animPipe->unk08 = speed;
        }
    }
}

f32 fn_800B4C40(void* obj) {
    Actor* actor = obj;
    u32 i;

    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->animPipe != NULL && actor->boneArray[i]->animPipe->currentTrack != NULL) {
            return actor->boneArray[i]->animPipe->time;
        }
    }
    return 0.0f;
}

void setActorAnimFrame(void* obj, f32 frame) {
    Actor* actor = obj;
    u32 i;

    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->animPipe != NULL) {
            actor->boneArray[i]->animPipe->time = frame;
        }
    }
}
