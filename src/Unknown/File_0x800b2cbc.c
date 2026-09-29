#include "Unknown/File_0x800b2cbc.h"
#include "C3/skinning.h"

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
