#include "Unknown/File_0x800b0a14.h"

void removeCurrentDrawingItem(void) {
    DrawingSceneStruct *prev;

    if (DrawingStructArray_Count1 == 0) {
        return;
    }

    prev = currentDrawingItem->prev;
    prev->next = currentDrawingItem->next;
    currentDrawingItem->next->prev = currentDrawingItem->prev;
    currentDrawingItem->func = NULL;
    DrawingStructArray_Count1--;
}

DrawingSceneStruct *insertGraphicDrawingFunction(void (*func)(void), u32 priority) {
    DrawingSceneStruct *prev;
    DrawingSceneStruct *next;
    DrawingSceneStruct *item;
    u16 idx;

    do {
        idx = DrawingStructArray_SearchIndex + 1;
        DrawingStructArray_SearchIndex = idx;
        idx = idx & 0x3F;
        DrawingStructArray_SearchIndex = idx;
    } while (DSS_Head1[idx].func != NULL);

    next = &DSS_Head1[DrawingStructArray_Count2 * 2];
    do {
        next = next->next;
    } while (next->priority < (u16)priority);

    prev = next->prev;
    item = &DSS_Head1[idx];
    next->prev = item;
    prev->next = item;
    item->func = func;
    item->prev = prev;
    item->next = next;
    item->currentDrawingItem = currentDrawingItem;
    item->state = 0;
    item->priority = priority;
    DrawingStructArray_Count1++;
    *(u32 *)&item->unk_14 = 0;
    item->unk_18 = 0;
    item->unk_20 = 0;
    item->unk_28 = 0;
    item->unk_30 = 0;
    item->unk_38 = 0;
    return item;
}

static inline void resetDrawingStructLists(void) {
    DrawingSceneStruct *p;
    int i;

    p = DSS_Head1;
    i = 3;
    do {
        p[0].prev = NULL;
        p[0].next = &p[1];
        p[0].currentDrawingItem = &lbl_80111300;
        p[0].state = 0;
        p[0].priority = 0;
        p[1].prev = &p[0];
        p[1].next = NULL;
        p[1].currentDrawingItem = &lbl_80111300;
        p[1].state = 0;
        p[1].priority = 0xFFFF;
        p += 2;
    } while (--i != 0);

    p = &DSS_Head1[6];
    i = 0x3A;
    do {
        p->func = NULL;
        p++;
    } while (--i != 0);

    DrawingStructArray_Count1 = 0;
    DrawingStructArray_Count2 = 0;
    DrawingStructArray_SearchIndex = 5;
}

void resetAllDrawingStructs_tonop(void) {
    int i;
    DrawingSceneStruct *p;

    resetDrawingStructLists();

    p = DSS_Head1;
    i = 6;
    do {
        p->func = nop_function;
        p++;
    } while (--i != 0);
}

void resetAllDrawingStructs(void) {
    int i;
    DrawingSceneStruct *p;

    p = DSS_Head1;
    i = 3;
    do {
        p[0].prev = NULL;
        p[0].next = &p[1];
        p[0].currentDrawingItem = &lbl_80111300;
        p[0].state = 0;
        p[0].priority = 0;
        p[1].prev = &p[0];
        p[1].next = NULL;
        p[1].currentDrawingItem = &lbl_80111300;
        p[1].state = 0;
        p[1].priority = 0xFFFF;
        p += 2;
    } while (--i != 0);

    p = &DSS_Head1[6];
    i = 0x3A;
    do {
        p->func = NULL;
        p++;
    } while (--i != 0);

    DrawingStructArray_Count1 = 0;
    DrawingStructArray_Count2 = 0;
    DrawingStructArray_SearchIndex = 5;
}

void setDrawingListHeadFunctions(void (*func)(void)) {
    DrawingSceneStruct *p;
    int i;

    if (func == NULL) {
        func = nop_function;
    }

    p = DSS_Head1;
    i = 3;
    do {
        p->func = func;
        p += 2;
    } while (--i != 0);
}

void nop_function(void) {
}
