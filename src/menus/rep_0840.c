#include "menus/rep_0840.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/mtx.h"

extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_data_3198[0x348];

extern void fn_2_72054(s32 arg0, s32 arg1);
extern void fn_2_92654(s32 arg0, s32 arg1);
extern void fn_80062890(s32 arg0);
extern s32 fn_2_6AF9C(s32 arg0);
extern void fn_2_6AF80(s32 arg0, s32 arg1);
extern void fn_2_6AABC(s32 arg0, Vec *arg1);
extern void *memcpy(void *dest, const void *src, size_t n);

// .text:0x0003BD88 size:0x2B4 mapped:0x8067AE1C
void fn_2_3BD88(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    switch (*(u8 *)((u8 *)item + 0x28)) {
        case 0:
            *(s16 *)((u8 *)item + 0x14) = 1;
            *(u8 *)((u8 *)item + 0x28) = 1;
            break;
        case 1:
            if (--*(s16 *)((u8 *)item + 0x14) != 0) {
                break;
            }
            fn_2_72054(0, 0x13);
            *(s16 *)((u8 *)item + 0x14) = 0x32;
            *(u8 *)((u8 *)item + 0x28) = 2;
            break;
        case 2:
            if (*(s16 *)((u8 *)item + 0x14) == 0xc) {
                if (*(s16 *)&lbl_2_bss_1A8248[0x16c2] == 0x12) {
                    fn_2_92654(0x19, 9);
                } else {
                    fn_2_92654(0x1a, 9);
                }
            }
            if (--*(s16 *)((u8 *)item + 0x14) == 0) {
                fn_80062890(0xb);
            }
            if (fn_2_6AF9C(0) == 1) {
                fn_2_6AF80(0, 0);
                *(u8 *)((u8 *)item + 0x28) = 3;
            }
            break;
        case 3:
            *(u8 *)((u8 *)item + 0x28) = 4;
            break;
        case 4: {
            Vec vec;

            if (*(s16 *)&lbl_2_bss_1A8248[0x16c0] == 0x30) {
                memcpy(&vec, &lbl_2_data_3198[0x208], sizeof(Vec));
                PSVECScale(&vec, 0.5f, &vec);
                fn_2_6AABC(0, &vec);
                fn_2_92654(0x1a, 9);
            } else {
                memcpy(&vec, &lbl_2_data_3198[0x1f4], sizeof(Vec));
                PSVECScale(&vec, 0.5f, &vec);
                fn_2_6AABC(0, &vec);
                fn_2_92654(0x19, 9);
            }
            *(u8 *)((u8 *)item + 0x28) = 5;
            break;
        }
        case 5:
            fn_2_72054(0, 0x14);
            *(u8 *)((u8 *)item + 0x28) = 6;
            break;
        case 6:
            if (fn_2_6AF9C(0) == 1) {
                fn_2_6AF80(0, 0);
                fn_2_72054(0, 4);
                if (*(s16 *)&lbl_2_bss_1A8248[0x16c0] == 0x30) {
                    *(s16 *)&lbl_2_bss_1A8248[0x16c2] = 0x32;
                    *(s16 *)&lbl_2_bss_1A8248[0x16c0] = 0x32;
                } else {
                    *(s16 *)&lbl_2_bss_1A8248[0x16c2] = 0x12;
                    *(s16 *)&lbl_2_bss_1A8248[0x16c0] = 0x12;
                }
                *(u8 *)((u8 *)item + 0x28) = 7;
            }
            break;
        case 7:
            item->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
            *(u8 *)((u8 *)item + 0x28) = 0;
            break;
    }

    if (lbl_2_bss_1A824C[0x190000 + 0x783f] == 1) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        *(u8 *)((u8 *)item + 0x28) = 0;
    }
}
