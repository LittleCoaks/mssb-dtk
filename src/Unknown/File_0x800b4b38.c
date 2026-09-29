#include "Unknown/File_0x800b4b38.h"
#include "C3/anim.h"
#include "C3/skinning.h"

void AnimateActorBones(void* obj) {
    Actor* actor = obj;
    u32 i;

    actor->unk8C += actor->unk90;
    if (actor->unk8C > 1.0f) {
        actor->unk8C = 1.0f;
    }
    for (i = 0; i < actor->totalBones; i++) {
        ANIMTick(actor->boneArray[i]->animPipe, actor->unk99);
    }
}
