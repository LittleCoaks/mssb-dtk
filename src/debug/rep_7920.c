#include "debug/rep_7920.h"
#include "header_rep_data.h"

extern RepSlot lbl_1_common_bss_4BC30[];
extern RepRef lbl_1_common_bss_4C6F8[];
extern u8 lbl_1_data_108E0;
/* MWCC lays .bss out in reverse declaration order: 47050 must be declared last. */
u16 lbl_1_bss_47052;
u16 lbl_1_bss_47050;

// .text:0x00026C2C size:0xFC
RepSlot *fn_1_26C2C(RepSrc *src, s32 idx) {
    if (src == NULL) {
        return NULL;
    }
    if (lbl_1_data_108E0 != 0) {
        lbl_1_data_108E0 = 0;
    }
    fn_1_26B7C(&lbl_1_common_bss_4BC30[idx]);
    lbl_1_common_bss_4BC30[idx].a = src->a;
    lbl_1_common_bss_4BC30[idx].b = src->b;
    lbl_1_common_bss_4BC30[idx].c = src->c;
    lbl_1_bss_47052 = src->a;
    lbl_1_bss_47050 = src->b;
    return &lbl_1_common_bss_4BC30[idx];
}

// .text:0x00026BFC size:0x30
RepRef *fn_1_26BFC(RepSrc *src, s32 idx) {
    RepRef *ref = &lbl_1_common_bss_4C6F8[idx];
    ref->a = src->a;
    ref->b = src->b;
    ref->next = &src->c;
    return ref;
}

// .text:0x00026B7C size:0x80
void fn_1_26B7C(RepSlot *slot) {
    slot->x = 0.0f;
    slot->y = 1.0f;
    slot->unk8 = 1;
    slot->unkA = 0;
    slot->unkC = 0;
    slot->unkE = -1;
    slot->unk10 = 1;
    slot->unk14 = 0;
    slot->flags.flagA = 1;
    if (slot != NULL) {
        slot->flags.flagB = 3;
    }
    if (slot != NULL) {
        slot->flags.flagC = 3;
    }
}
