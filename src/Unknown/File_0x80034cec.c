#include "Unknown/File_0x80034cec.h"
#include "text/text_channel.h"

void removeGraphicsElementFromScene(DrawingSceneStruct* node) {
    MenuScene* scene = (MenuScene*)node;
    UIRecord* rec;
    int first = scene->firstHandle;
    int i;
    int j;

    for (i = 0; i < scene->handleCount; i++) {
        rec = (UIRecord*)graphicsRelatedArray[first + i].object;
        if (rec != NULL) {
            rec->flags = 0;
        }
    }
    i += first;
    for (j = first; i < UI_RECORD_COUNT; i++, j++) {
        graphicsRelatedArray[j].object = graphicsRelatedArray[i].object;
        graphicsRelatedArray[j].unk4 = graphicsRelatedArray[i].unk4;
        if (graphicsRelatedArray[j].unk4 != 0) {
            ((MenuScene*)graphicsRelatedArray[j].unk4)->firstHandle = j;
        }
    }
    for (; j < UI_RECORD_COUNT; j++) {
        graphicsRelatedArray[j].object = NULL;
        graphicsRelatedArray[j].unk4 = 0;
    }
}
