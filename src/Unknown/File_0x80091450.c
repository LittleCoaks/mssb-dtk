#include "Unknown/File_0x80091450.h"

TEXDescriptorPtr TEXGet(TEXPalettePtr pal, u32 id) {
    return &pal->descriptorArray[id];
}

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

s8 Strcmp(char* str1, char* str2) {
    do {
        if (*str1 < *str2) {
            return 1;
        }
        if (*str1 > *str2) {
            return -1;
        }
        str1++;
        str2++;
    } while (*str1 && *str2);
    return 0;
}

void DSInitTree(DSTreePtr tree, Ptr obj, DSBranchPtr branch) {
    tree->Root = NULL;
    tree->Offset = (u32)branch - (u32)obj;
}

void DSInsertBranchBelow(DSTreePtr tree, Ptr cursor, Ptr obj) {
    DSBranchPtr branch = (DSBranchPtr)(obj + tree->Offset);
    Ptr sibling = NULL;

    if (cursor) {
        DSBranchPtr cursorBranch = (DSBranchPtr)(cursor + tree->Offset);
        if (cursorBranch->Children) {
            sibling = cursorBranch->Children;
        } else {
            cursorBranch->Children = obj;
        }
    } else {
        if (tree->Root) {
            sibling = tree->Root;
        } else {
            tree->Root = obj;
        }
    }

    if (sibling) {
        while (((DSBranchPtr)(sibling + tree->Offset))->Next) {
            sibling = ((DSBranchPtr)(sibling + tree->Offset))->Next;
        }
        ((DSBranchPtr)(sibling + tree->Offset))->Next = obj;
        branch->Prev = sibling;
    } else {
        branch->Prev = NULL;
    }
    branch->Next = NULL;
    branch->Parent = cursor;
}
