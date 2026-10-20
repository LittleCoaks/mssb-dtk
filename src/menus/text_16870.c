#include "menus/text_16870.h"

#include "Dolphin/mtx.h"
#include "Unknown/File_0x800b0a14.h"

extern u8 lbl_2_bss_100B8[];
extern DrawingSceneStruct *lbl_2_bss_1224;
extern Mtx lbl_2_bss_1010C;
extern u8 hugeAnimStruct[];

void fn_2_18398(void);
void fn_2_16460(void);
u8 *fn_80052768_getCamera(s32 mode);

// .text:0x00016A74 size:0x24 mapped:0x80655B08
void fn_2_16A74(s32 idx, s32 flag) {
    hugeAnimStruct[idx * 0x27C + 0xE61] = (flag != 0);
}

// .text:0x00016A5C size:0x18 mapped:0x80655AF0
u8 fn_2_16A5C(s32 idx) {
    return hugeAnimStruct[idx * 0x27C + 0xE61];
}

// .text:0x00016A48 size:0x14 mapped:0x80655ADC
void set807518de(s32 idx, u8 value) {
    lbl_2_bss_100B8[idx + 0x46] = value;
}

// .text:0x00016A34 size:0x14 mapped:0x80655AC8
u8 fn_2_16A34(s32 idx) {
    return lbl_2_bss_100B8[idx + 0x46];
}

// .text:0x00016870 size:0x1C4 mapped:0x80655904
void fn_2_16870(void) {
    s32 i;
    s32 j;
    s32 next;
    DrawingSceneStruct *node;
    u8 *base = lbl_2_bss_100B8;
    u8 *entry;
    u8 *camera;

    for (i = 0; i < base[0x2D]; i++) {
        entry = base + i;
        if (entry[0x14] != 0) {
            next = ((s8)base[0] + 1) % 10;
            if (next != (s8)base[1]) {
                node = lbl_2_bss_1224;
                if (node == NULL) {
                    node = insertGraphicDrawingFunction(fn_2_18398, 0xFFFF);
                    lbl_2_bss_1224 = node;
                    if (node != NULL) {
                        *((u8 *)node + 0x1C) = 0;
                        *((u8 *)node + 0x1D) = 0;
                    }
                }
                if (node != NULL) {
                    base[(s8)base[0] + 2] = (u8)i;
                    base[0] = (u8)next;
                    entry[0x42] = TRUE;
                    entry[0x14] = 0;
                }
            }
        }
    }

    hugeAnimStruct[0x307A] = 5;
    hugeAnimStruct[0x307C] = 1;
    fn_2_16460();
    camera = fn_80052768_getCamera(0);
    PSMTXCopy(lbl_2_bss_1010C, (void *)(camera + 0x40));

    for (j = 0; j < base[0x2D]; j++) {
        u8 *obj = *(u8 **)(hugeAnimStruct + 0x2C50 + j * 4);

        if (obj != NULL && *(s16 *)(obj + 0x62) == 0x6B) {
            base[0x40 + j] = TRUE;
        }
    }
}
