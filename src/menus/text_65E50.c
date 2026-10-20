#include "menus/text_65E50.h"
#include "text/text.h"

// Local prototypes for symbols owned by other units.
s16 fn_2_53BC8(void *arg0);
s32 fn_80062890(s32 arg);

extern u8 *lbl_2_bss_1A8248;
extern u8 hugeAnimStruct[];
extern s16 lbl_2_data_2E80[];

// .text:0x00065E50 size:0x1E8 mapped:0x806A4EE4
void fn_2_65E50(void) {
    return;
}

// .text:0x00066038 size:0x150 mapped:0x806A50CC
void fn_2_66038(void) {
    return;
}

// .text:0x00066188 size:0x1B4 mapped:0x806A521C
void fn_2_66188(void) {
    return;
}

// .text:0x0006633C size:0x284 mapped:0x806A53D0
void fn_2_6633C(void) {
    return;
}

// .text:0x000665C0 size:0x19C mapped:0x806A5654
void fn_2_665C0(void) {
    return;
}

// .text:0x0006675C size:0x128 mapped:0x806A57F0
void fn_2_6675C(void) {
    return;
}

// .text:0x00066884 size:0x268 mapped:0x806A5918
void fn_2_66884(void) {
    return;
}

// .text:0x00066AEC size:0x1D8 mapped:0x806A5B80
void fn_2_66AEC(void) {
    return;
}

// .text:0x00066CC4 size:0x150 mapped:0x806A5D58
void fn_2_66CC4(void) {
    return;
}

// .text:0x00066E14 size:0x1B4 mapped:0x806A5EA8
void fn_2_66E14(void) {
    return;
}

// .text:0x00066FC8 size:0x214 mapped:0x806A605C
void fn_2_66FC8(void) {
    return;
}

// .text:0x000671DC size:0x1B4 mapped:0x806A6270
void fn_2_671DC(void) {
    return;
}

// .text:0x00067390 size:0x1F8 mapped:0x806A6424
void fn_2_67390(void) {
    return;
}

// .text:0x00067588 size:0x1F8 mapped:0x806A661C
void fn_2_67588(void) {
    return;
}

// .text:0x00067780 size:0x414 mapped:0x806A6814
void fn_2_67780(void) {
    return;
}

// .text:0x00067B94 size:0x1B4 mapped:0x806A6C28
void fn_2_67B94(void) {
    return;
}

// .text:0x00067D48 size:0x2A4 mapped:0x806A6DDC
void fn_2_67D48(void) {
    return;
}

// .text:0x00067FEC size:0x1B4 mapped:0x806A7080
void fn_2_67FEC(void) {
    return;
}

// .text:0x000681A0 size:0x94 mapped:0x806A7234
void fn_2_681A0(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        rec->state = 0x26;
        break;
    case 2:
        rec->state = 0x25;
        break;
    }
}

// .text:0x00068234 size:0x2C mapped:0x806A72C8
void fn_2_68234(TextScene *scene, TextHandleRec *rec) {
    graphicsRelatedArray[scene->firstHandle + rec->handle].object->flags &= ~2;
}

// .text:0x00068260 size:0xA8 mapped:0x806A72F4
void fn_2_68260(u8 *obj) {
    s16 *row;
    s32 dx;
    s32 dy;
    u8 idx;
    u8 *huge;
    s16 v;

    idx = lbl_2_bss_1A8248[0x441C];
    row = &lbl_2_data_2E80[idx * 3];
    dx = row[0] * 2 - row[2] * 2;
    dy = row[0] * 2 - row[1] * 2;

    if (*(s32 *)(obj + 0x80) == 0) {
        huge = hugeAnimStruct + 0xC04;
        if (huge != NULL) {
            v = *(s16 *)(huge + 0x68);
            if (v == dx || v == dy) {
                if (idx == 5) {
                    fn_80062890(1);
                } else {
                    fn_80062890(0);
                }
            }
        }
    }
}

// .text:0x00068308 size:0x24 mapped:0x806A739C
void fn_2_68308(void) {
    lbl_2_bss_1A8248[0x17AB] = 0;
    *(s16 *)(lbl_2_bss_1A8248 + 0x177C) = 0;
    lbl_2_bss_1A8248[0x442F] = 0;
}
