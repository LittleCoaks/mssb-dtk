#include "Unknown/File_0x8002399c.h"
#include "Unknown/File_0x800232e0.h"
#include "Unknown/File_0x80023b04.h"
#include "string.h"

void fn_800B4724(Actor* actor, int value);

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
    entry->applyControl = 1;
    if (anim != NULL) {
        entry->anim = anim;
        entry->animPending = 1;
        entry->speedPending = 1;
        entry->framePending = 1;
        entry->blendTime = 0.0f;
        if (entry->actor != NULL) {
            entry->actor->unk99 = 0;
        }
    }
    entry->callback = NULL;
}
