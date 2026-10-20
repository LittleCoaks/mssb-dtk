#include "menus/text_92394.h"

#include "C3/light/light.h"

extern u8 *lbl_2_bss_340140;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern Text92394Fn lbl_2_data_30804[];
extern Text92394Fn lbl_2_data_307F0[];
extern Text92394Fn lbl_2_data_307F8[];
extern Text92394Fn lbl_2_data_308B4[];
extern u32 lbl_2_data_30900[];
extern u8 inputParams[];

void fn_2_8AC84(s32 slot, s32 flag);
void removeCurrentDrawingItem(void);

// .text:0x0009267C size:0x14C mapped:0x806D1710
void fn_2_9267C(Vec *out, Vec *a, Vec *b, Vec *c, f32 t, f32 kA, f32 kB, f32 kC) {
    Vec ab;
    Vec scaled;
    Vec cb;
    f32 dist;
    f32 proj;

    PSVECSubtract(a, b, &ab);
    dist = PSVECDistance(a, b);
    PSVECSubtract(c, b, &cb);
    PSVECScale(&cb, t, &scaled);
    proj = PSVECDotProduct(&scaled, &ab);
    proj = kB * (proj / dist);
    dist = kA * (kC - dist) + proj;
    PSVECNormalize(&ab, &ab);
    PSVECScale(&ab, dist * t, &ab);
    PSVECAdd(a, &ab, a);
    *out = *a;
}

// .text:0x00092654 size:0x28 mapped:0x806D16E8
void fn_2_92654(s32 slot, u8 value) {
    Text92394Entry *entry;

    entry = (Text92394Entry *)(lbl_2_bss_1A8248 + 0x21E0 + slot * 0xBC);
    entry->unkAB = value;
    entry->state = 0;
}

// .text:0x0009257C size:0xD8 mapped:0x806D1610
void fn_2_9257C(void) {
    s32 i;
    Text92394Entry *entry;
    u8 *flagBase;
    u8 mode;

    mode = lbl_2_bss_1A8248[0x44F2];
    if (mode != 1 && mode != 2 && mode != 3) {
        for (i = 0; i < 0x1D; i++) {
            entry = (Text92394Entry *)(lbl_2_bss_1A8248 + 0x21E0 + i * 0xBC);
            entry->unkB8 = lbl_2_data_308B4[entry->unkAB];
            entry->unkB8(entry);
        }
        flagBase = lbl_2_bss_1A824C + 0x190000;
        if (flagBase[0x72C0] != 0) {
            flagBase[0x72C0] = 0;
            removeCurrentDrawingItem();
        }
    }
}

// .text:0x0009253C size:0x40 mapped:0x806D15D0
void fn_2_9253C(Text92394Entry *entry) {
    entry->unkB8 = lbl_2_data_308B4[entry->unkAB];
    entry->unkB8(entry);
}

// .text:0x00092504 size:0x38 mapped:0x806D1598
void fn_2_92504(Text92394Entry *entry) {
    lbl_2_data_307F0[entry->state](entry);
}

// .text:0x000924B0 size:0x54 mapped:0x806D1544
void fn_2_924B0(Text92394Entry *entry) {
    u32 packed;
    GXColor color;

    packed = *(u32 *)(inputParams + 0x28);
    fn_2_8AC84(entry->slot, 0);
    ((GXColor *)&packed)->a = 0xFF;
    color = *(GXColor *)&packed;
    adjustLightingParams(FALSE, color);
}

// .text:0x000924A4 size:0xC mapped:0x806D1538
void fn_2_924A4(Text92394Entry *entry) {
    entry->state = 1;
}

// .text:0x0009246C size:0x38 mapped:0x806D1500
void fn_2_9246C(Text92394Entry *entry) {
    lbl_2_data_307F8[entry->state](entry);
}

// .text:0x000923E4 size:0x88 mapped:0x806D1478
void fn_2_923E4(Text92394Entry *entry) {
    s32 slot;
    u8 *rec;
    Text92394Entry *slotEntry;

    fn_2_8AC84(entry->slot, 1);
    slot = entry->slot;
    slotEntry = (Text92394Entry *)(lbl_2_bss_1A8248 + 0x21E0 + slot * 0xBC);
    rec = *(u8 **)(lbl_2_bss_340140 + 0x2D94);
    if (rec != NULL) {
        slotEntry->unkA6 = 0;
        *(u32 *)(rec + slot * 0x28) = lbl_2_data_30900[0];
    }
    entry->state = 1;
}

// .text:0x000923D8 size:0xC mapped:0x806D146C
void fn_2_923D8(Text92394Entry *entry) {
    entry->state = 2;
}

// .text:0x000923CC size:0xC mapped:0x806D1460
void fn_2_923CC(Text92394Entry *entry) {
    entry->state = 2;
}

// .text:0x00092394 size:0x38 mapped:0x806D1428
void fn_2_92394(Text92394Entry *entry) {
    lbl_2_data_30804[entry->state](entry);
}
