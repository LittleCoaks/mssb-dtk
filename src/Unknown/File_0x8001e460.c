#include "Unknown/File_0x8001e460.h"

extern u8 drawStadiumRelated;
extern void (*lbl_803CB7AC[2])(Mtx view, int flag, u32 pass);

void fn_8001E460(void (*func)(Mtx view, int flag, u32 pass)) {
    lbl_803CB7AC[drawStadiumRelated] = func;
}

void setNullPtrForStadiumObjs(void) {
    lbl_803CB7AC[0] = NULL;
    lbl_803CB7AC[1] = NULL;
}
