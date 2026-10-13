#include "mssbTypes.h"
#include "charPipeline/structures/Tree.h"

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
