#include "Unknown/File_0x800b2b74.h"

void callDSInsertListObject(UnkB2B4C* obj, u16 index) {
    DSInsertListObject(&obj->drawPriorityList, obj->drawPriorityList.Tail, (Ptr)obj->entries[index]);
}
