#include "Unknown/File_0x800bd8c4.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800b2b4c.h"
#include "Unknown/File_0x800b4048.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x800b4b38.h"
#include "Unknown/File_0x800b4bc8.h"
#include "game/stadium/stadium_framework.h"
#include "Dolphin/os.h"
#include "string.h"

void fn_800B4724(Actor* actor, int value);
void fn_800B3A78(Actor* actor, Mtx m, int count, ...);

static inline void applyEntryControl(ActorObjectEntry* entry) {
    Control* dst = &entry->actor->worldControl;
    Actor* actor = entry->actor;

    memcpy(dst, &entry->control, sizeof(Control));
    fn_800B2BFC((StadiumModelNode*)entry->actor, entry->unk64, entry->unk66);
    AnimateActorBones(actor);
    fn_800B3F20((StadiumModelNode*)actor);
    fn_800B313C((StadiumModelNode*)actor);
}

static inline void updateDrawFlags(Actor* actor, Mtx m) {
    actor->unk98 = (actor->unk98 & 0xFC) | fn_800B3C04(0, (StadiumModelNode*)actor, m);
}

void fn_800BD8C4(ActorObjectTable* table, Mtx m) {
    u16 i;

    for (i = 0; i < table->count; i++) {
        if (table->entries[i].actor != NULL) {
            if (table->entries[i].animPending) {
                ACTSetAnimation(table->entries[i].actor, table->entries[i].anim, NULL, table->entries[i].seqNum,
                                0.0f, table->entries[i].blendTime);
            }
            if (table->entries[i].framePending) {
                setActorAnimFrame(table->entries[i].actor, table->entries[i].frame);
            }
            if (table->entries[i].speedPending) {
                fn_800B4C04(table->entries[i].actor, table->entries[i].speed);
            }
            if (table->entries[i].boneParam & 2) {
                updateBoneParam(table->entries[i].actor, (table->entries[i].boneParam & 1) != 0);
            }
            Set_FUN_800b2b6c((UnkB2B4C*)table->entries[i].actor, table->entries[i].unk68);
            if (table->entries[i].applyControl) {
                applyEntryControl(&table->entries[i]);
            }
            updateDrawFlags(table->entries[i].actor, m);
            table->entries[i].animPending = FALSE;
            table->entries[i].framePending = FALSE;
            table->entries[i].speedPending = FALSE;
            table->entries[i].boneParam &= 1;
        }
    }
}

void fn_800BDA24(ActorObjectEntry* entry) {
    Control* dst = &entry->actor->worldControl;
    Actor* actor = entry->actor;

    memcpy(dst, &entry->control, sizeof(Control));
    fn_800B2BFC((StadiumModelNode*)entry->actor, entry->unk64, entry->unk66);
    AnimateActorBones(actor);
    fn_800B3F20((StadiumModelNode*)actor);
    fn_800B313C((StadiumModelNode*)actor);
}

void sknRelated(void* model, Mtx m) {
    ActorObjectEntry* entry = model;
    Actor* actor = entry->actor;

    if (entry->callback != NULL) {
        entry->callback();
    }
    switch (entry->drawArgCount) {
    case 0:
        fn_800B3A78(actor, m, 0);
        break;
    case 1:
        fn_800B3A78(actor, m, 1, entry->drawArgs[0]);
        break;
    case 2:
        fn_800B3A78(actor, m, 2, entry->drawArgs[0], entry->drawArgs[1]);
        break;
    case 3:
        fn_800B3A78(actor, m, 3, entry->drawArgs[0], entry->drawArgs[1], entry->drawArgs[2]);
        break;
    case 4:
        fn_800B3A78(actor, m, 4, entry->drawArgs[0], entry->drawArgs[1], entry->drawArgs[2], entry->drawArgs[3]);
        break;
    case 5:
        fn_800B3A78(actor, m, 5, entry->drawArgs[0], entry->drawArgs[1], entry->drawArgs[2], entry->drawArgs[3],
                    entry->drawArgs[4]);
        break;
    case 6:
        fn_800B3A78(actor, m, 6, entry->drawArgs[0], entry->drawArgs[1], entry->drawArgs[2], entry->drawArgs[3],
                    entry->drawArgs[4], entry->drawArgs[5]);
        break;
    case 7:
        fn_800B3A78(actor, m, 7, entry->drawArgs[0], entry->drawArgs[1], entry->drawArgs[2], entry->drawArgs[3],
                    entry->drawArgs[4], entry->drawArgs[5], entry->drawArgs[6]);
        break;
    case 8:
        fn_800B3A78(actor, m, 8, entry->drawArgs[0], entry->drawArgs[1], entry->drawArgs[2], entry->drawArgs[3],
                    entry->drawArgs[4], entry->drawArgs[5], entry->drawArgs[6], entry->drawArgs[7]);
        break;
    }
}

void animateBallRelated(void* table, u16 index, u16 slot, void* data, int anim, int arg5) {
    ActorObjectTable* t = table;

    maybeBallRelated(&t->entries[index].actor, data, (u16)index);
    fn_800B4724(t->entries[index].actor, arg5);
    t->entries[index].seqNum = 0;
    t->entries[index].speed = 1.0f;
    t->entries[index].unk64 = 0;
    t->entries[index].unk66 = 0;
    t->entries[index].unk68 = 0;
    t->entries[index].drawArgCount = 0;
    t->entries[index].drawArgs[0] = 0;
    t->entries[index].drawArgs[1] = 0;
    t->entries[index].drawArgs[2] = 0;
    t->entries[index].drawArgs[3] = 0;
    t->entries[index].drawArgs[4] = 0;
    t->entries[index].drawArgs[5] = 0;
    t->entries[index].drawArgs[6] = 0;
    t->entries[index].drawArgs[7] = 0;
    t->entries[index].slot = slot;
    t->entries[index].applyControl = 1;
    if ((void*)anim != NULL) {
        t->entries[index].anim = (void*)anim;
        t->entries[index].animPending = 1;
        t->entries[index].speedPending = 1;
        t->entries[index].framePending = 1;
        t->entries[index].blendTime = 0.0f;
        if (t->entries[index].actor != NULL) {
            t->entries[index].actor->unk99 = 0;
        }
    }
    t->entries[index].callback = NULL;
}

void* ActorObjectInitTable(u16 count) {
    ActorObjectTable* t;
    u16 i;

    if (count == 0) {
        OSReport("Warning : ActorObjectInitTable関数が引数0で呼ばれました。テーブルは作成されずにリターンします。\n");
        return NULL;
    }
    t = _OSAllocFromHeap(0x20, count * sizeof(ActorObjectEntry) + 0x34);
    t->count = count;
    PSMTXIdentity(t->mtx);
    for (i = 0; i < t->count; i++) {
        t->entries[i].actor = NULL;
        t->entries[i].anim = NULL;
        t->entries[i].callback = NULL;
        t->entries[i].seqNum = 0;
        t->entries[i].speed = 1.0f;
        t->entries[i].frame = 0.0f;
        t->entries[i].blendTime = 0.0f;
        t->entries[i].unk64 = 0;
        t->entries[i].unk66 = 0;
        t->entries[i].unk68 = 0;
        t->entries[i].drawArgCount = 0;
        t->entries[i].drawArgs[0] = 0;
        t->entries[i].drawArgs[1] = 0;
        t->entries[i].drawArgs[2] = 0;
        t->entries[i].drawArgs[3] = 0;
        t->entries[i].drawArgs[4] = 0;
        t->entries[i].drawArgs[5] = 0;
        t->entries[i].drawArgs[6] = 0;
        t->entries[i].drawArgs[7] = 0;
        t->entries[i].slot = 0;
        t->entries[i].applyControl = 0;
        t->entries[i].animPending = 0;
        t->entries[i].speedPending = 0;
        t->entries[i].framePending = 0;
        t->entries[i].boneParam = 1;
        t->entries[i].control.type = 0;
        t->entries[i].slot = i;
    }
    return t;
}
