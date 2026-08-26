#include "Unknown/File_0x800b0cb8.h"
#include "Unknown/File_0x800b0a14.h"

// Local view of DrawingSceneStruct: the stepper calls each item's func with a
// pointer to caller-stack scratch, so here the callback type carries that arg.
typedef struct DrawScriptItem {
    /* 0x00 */ void (*func)(void *);
    /* 0x04 */ struct DrawScriptItem *prev;
    /* 0x08 */ struct DrawScriptItem *next;
} DrawScriptItem;

// .text:0x800B0CB8 size:0x70
void RunDrawScripts_with_stack_variables(void) {
    u32 rootScratch[5];
    u32 itemScratch[5];
    DrawScriptItem *item;

    currentDrawingItem = &lbl_80111300;
    ((DrawScriptItem *)&lbl_80111300)->func(rootScratch);
    item = (DrawScriptItem *)&DSS_Head1[DrawingStructArray_Count2 * 2];
    do {
        currentDrawingItem = (DrawingSceneStruct *)item;
        item->func(itemScratch);
        item = item->next;
    } while (item != NULL);
}
