#include "Unknown/File_0x8004cc18.h"

extern Unk803C5F74 lbl_803C5F74;

void fn_8004CC18(void) {
    lbl_803C5F74.state = 4;
}

void set803c5f77(void) {
    if (lbl_803C5F74.state != 4) {
        lbl_803C5F74.state = 3;
    }
}

void fn_8004CC4C(u8 arg0, u8 arg1, u8 arg2, int arg3, u16 arg4) {
    int i;

    if (lbl_803C5F74.unk00 != 0) {
        return;
    }
    lbl_803C5F74.unk01 = arg0;
    lbl_803C5F74.unk02 = arg2;
    lbl_803C5F74.state = 0;
    lbl_803C5F74.unk04 = arg1;
    lbl_803C5F74.unk1E = 0;
    for (i = 0; i < 4; i++) {
        lbl_803C5F74.unk06[i] = 0;
        lbl_803C5F74.unk0E[i] = -1;
    }
    lbl_803C5F74.unk1B = 0;
    lbl_803C5F74.unk1C = 0;
    if (arg3 >= 0) {
        lbl_803C5F74.unk1A = arg3;
        lbl_803C5F74.unk18 = arg4;
    } else {
        lbl_803C5F74.unk1A = -1;
    }
}
