#include "Unknown/File_0x8000f48c.h"
#include "Unknown/File_0x800bfe90.h"

extern u8 lbl_800E9920[0x3620];
extern void* lbl_803CBBE8;

void somethingSetTexturePointer(void) {
    lbl_803CBBE8 = lbl_800E9920;
    convertTextureHeader(lbl_800E9920);
}
