#include "Unknown/File_0x80069a98.h"
#include "Unknown/File_0x80034cec.h"

extern DrawingSceneStruct* lbl_803CBD30;
extern u8 lbl_80366158[0x30];

void endDemo(void) {
    removeGraphicsElementFromScene(lbl_803CBD30);
    lbl_803CBD30 = NULL;
    lbl_80366158[0x2A] = 2;
}
