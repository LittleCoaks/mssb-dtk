#include "Unknown/File_0x80023b04.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800bdd74.h"
#include "HugeAnimStruct.h"


void initActorArray(int count) {
    int i;

    lbl_8017EBB0[0] = _OSAllocFromHeap(0x20, count * ACTOR_BUFFER_SIZE);
    i = 1;
    do {
        lbl_8017EBB0[i] = lbl_8017EBB0[i - 1] + ACTOR_BUFFER_SIZE;
    } while (++i < count);
    actorSize = ACTOR_BUFFER_SIZE;
    hugeAnimStruct.actorTables[0] = ActorObjectInitTable(13);
}
