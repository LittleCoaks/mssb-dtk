#include "mssbTypes.h"
#include "charPipeline/structures/List.h"

void DSInitList(DSListPtr list, Ptr obj, DSLinkPtr link) {
    list->Head = NULL;
    list->Tail = NULL;
    list->Offset = (u32)link - (u32)obj;
}

void DSInsertListObject(DSListPtr list, Ptr cursor, Ptr obj) {
    DSLinkPtr link = (DSLinkPtr)(obj + list->Offset);
    DSLinkPtr cursorLink;
    DSLinkPtr prevLink;

    if (list->Head) {
        if (!cursor) {
            ((DSLinkPtr)(list->Tail + list->Offset))->Next = obj;
            link->Prev = list->Tail;
            link->Next = NULL;
            list->Tail = obj;
            return;
        }
        cursorLink = (DSLinkPtr)(cursor + list->Offset);
        if (cursor == list->Head) {
            list->Head = obj;
            link->Next = cursor;
            cursorLink->Prev = obj;
            return;
        }
        prevLink = (DSLinkPtr)(cursorLink->Prev + list->Offset);
        link->Next = cursor;
        link->Prev = cursorLink->Prev;
        cursorLink->Prev = obj;
        prevLink->Next = obj;
        return;
    }

    list->Tail = obj;
    list->Head = obj;
    link->Prev = NULL;
    link->Next = NULL;
}
