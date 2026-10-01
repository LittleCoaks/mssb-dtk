#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800b4048.h"

void fn_800B4724(Actor* actor, int value);

void animateBallRelated(void* table, u16 index, u16 slot, void* data, int anim, int arg5) {
    ActorObjectTable* t = table;

    maybeBallRelated(&t->entries[index].actor, data, (u16)index);
    fn_800B4724(t->entries[index].actor, arg5);
    t->entries[index].unk0E = 0;
    t->entries[index].unk54 = 1.0f;
    t->entries[index].unk64 = 0;
    t->entries[index].unk66 = 0;
    t->entries[index].unk68 = 0;
    t->entries[index].unk6D = 0;
    t->entries[index].unk70[0] = 0;
    t->entries[index].unk70[1] = 0;
    t->entries[index].unk70[2] = 0;
    t->entries[index].unk70[3] = 0;
    t->entries[index].unk70[4] = 0;
    t->entries[index].unk70[5] = 0;
    t->entries[index].unk70[6] = 0;
    t->entries[index].unk70[7] = 0;
    t->entries[index].slot = slot;
    t->entries[index].unk6C = 1;
    if ((void*)anim != NULL) {
        t->entries[index].anim = (void*)anim;
        t->entries[index].unk58 = 1;
        t->entries[index].unk5A = 1;
        t->entries[index].unk59 = 1;
        t->entries[index].unk60 = 0.0f;
        if (t->entries[index].actor != NULL) {
            t->entries[index].actor->unk99 = 0;
        }
    }
    t->entries[index].unk08 = 0;
}
