#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80034f50.h"
#include "text/text_channel.h"

void addGraphicsElementToScene(DrawingSceneStruct* node, const UIRecordDescriptor* descriptors) {
    MenuScene* scene = (MenuScene*)node;
    GraphicsArrayEntry* first;
    int count = 0;
    const UIRecordDescriptor* desc;
    int i;
    s32 j;

    for (i = 0; i < UI_RECORD_COUNT; i++) {
        if (graphicsRelatedArray[i].object == NULL) {
            scene->firstHandle = i;
            first = &graphicsRelatedArray[i];
            first->unk4 = (u32)node;
            break;
        }
    }
    desc = descriptors;
    while (1) {
        int handle = count + i;
        UIRecord* rec;
        int parent;

        if (desc->type == UI_DESC_END) break;
        graphicsRelatedArray[handle].object = (TextGraphicsObject*)allocateGraphicsSlot(desc);
        parent = desc->parent;
        rec = (UIRecord*)graphicsRelatedArray[handle].object;
        if (parent == UI_NO_PARENT || count == 0) {
            rec->parent = NULL;
        } else {
            rec->parent = (UIRecord*)first[parent].object;
            rec->next = rec->parent->firstChild;
            rec->parent->firstChild = rec;
        }
        for (j = 0; j < 10; j++) {
            rec->textureOverride[j] = UI_NO_OVERRIDE;
        }
        desc++;
        count++;
    }
    scene->handleCount = count;
}
