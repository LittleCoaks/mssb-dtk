#include "Unknown/File_0x80023b04.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800bdd74.h"

// This unit's view of hugeAnimStruct (0x3154 bytes).
extern struct {
    /* 0x00 */ u8 _00[0x60];
    /* 0x60 */ void* actorObjectTable;
} hugeAnimStruct;

void initActorArray(int count) {
    int i;

    lbl_8017EBB0[0] = _OSAllocFromHeap(0x20, count * ACTOR_BUFFER_SIZE);
    i = 1;
    do {
        lbl_8017EBB0[i] = lbl_8017EBB0[i - 1] + ACTOR_BUFFER_SIZE;
    } while (++i < count);
    actorSize = ACTOR_BUFFER_SIZE;
    hugeAnimStruct.actorObjectTable = ActorObjectInitTable(13);
}
