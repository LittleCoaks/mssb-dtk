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
    entry->unk0E = 0;
    entry->unk54 = 1.0f;
    entry->unk64 = 0;
    entry->unk66 = 0;
    entry->unk68 = 0;
    entry->unk6D = 0;
    entry->unk70[0] = 0;
    entry->unk70[1] = 0;
    entry->unk70[2] = 0;
    entry->unk70[3] = 0;
    entry->unk70[4] = 0;
    entry->unk70[5] = 0;
    entry->unk70[6] = 0;
    entry->unk70[7] = 0;
    entry->slot = slot;
    entry->unk6C = 1;
    if (anim != NULL) {
        entry->anim = anim;
        entry->unk58 = 1;
        entry->unk5A = 1;
        entry->unk59 = 1;
        entry->unk60 = 0.0f;
        if (entry->actor != NULL) {
            entry->actor->unk99 = 0;
        }
    }
    entry->unk08 = 0;
}
