#include "menus/text_579B4.h"
#include "text/text.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

// Local prototypes for symbols owned by other units.
s16 fn_2_53BC8(void *arg0);
void fn_80036134(void *scene, s32 a, s32 b, s32 c);
void fn_8006C2B4(void *dst, void *src);

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8240;
extern s16 lbl_2_data_1FD84[];

// Work area behind lbl_2_bss_1A824C (the 0x190000 window).
static inline u8 *workBase(void) {
    return lbl_2_bss_1A824C + 0x190000;
}

static inline s16 workS16(s32 off) {
    return *(s16 *)(lbl_2_bss_1A824C + 0x190000 + off);
}

static inline TextGraphicsObject *nodeOf(TextScene *scene, TextHandleRec *rec) {
    return graphicsRelatedArray[scene->firstHandle + rec->handle].object;
}

static inline void nodeSetFlag2(TextGraphicsObject *node) {
    node->flags |= 2;
}

static inline void nodeClearFlag2(TextGraphicsObject *node) {
    node->flags &= ~2;
}

static inline void nodeSetByte68(TextGraphicsObject *node, u8 value) {
    *(u8 *)((u8 *)node + 0x68) = value;
}

static inline u32 nodeW5C(TextGraphicsObject *node) {
    return *(u32 *)((u8 *)node + 0x5C);
}

static inline void nodeSetW5C(TextGraphicsObject *node, u32 value) {
    *(u32 *)((u8 *)node + 0x5C) = value;
}

// Shared lookup: lbl_2_data_1FD84[work.s16(0x76FA) + work.s16(0x76FE)].
static inline s16 workTableLookup(void) {
    return lbl_2_data_1FD84[workS16(0x76FA) + workS16(0x76FE)];
}

// .text:0x000579B4 size:0x244 mapped:0x80696A48
void fn_2_579B4(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeSetFlag2(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        if (workTableLookup() >= 2) {
            nodeSetFlag2(nodeOf(scene, rec));
        } else {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        rec->state = 0x25;
        break;
    case 0x25:
        if (workTableLookup() >= 2) {
            nodeSetFlag2(nodeOf(scene, rec));
        } else {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    }
}

// .text:0x00057BF8 size:0x358 mapped:0x80696C8C
void fn_2_57BF8(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeSetFlag2(nodeOf(scene, rec));
        nodeSetW5C(nodeOf(scene, rec), 0);
        fn_80036134(scene, 0x1E, rec->unkA, rec->unkA + 5);
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 3;
        break;
    case 3:
        if (workS16(0x76FA) == rec->unkA) {
            if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 0x14) {
                nodeSetW5C(nodeOf(scene, rec), 0x140000);
                nodeSetByte68(nodeOf(scene, rec), 0);
                rec->state = 0x25;
            }
        } else {
            if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 0xA) {
                nodeSetW5C(nodeOf(scene, rec), 0xA0000);
                nodeSetByte68(nodeOf(scene, rec), 0);
                rec->state = 0x25;
            }
        }
        break;
    case 0x25:
        if (workS16(0x76FA) == rec->unkA) {
            nodeSetByte68(nodeOf(scene, rec), 1);
            if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 0x14) {
                nodeSetW5C(nodeOf(scene, rec), 0x140000);
            }
        } else {
            nodeSetByte68(nodeOf(scene, rec), 4);
            if ((nodeW5C(nodeOf(scene, rec)) >> 16) <= 0xA) {
                nodeSetW5C(nodeOf(scene, rec), 0xA0000);
            }
        }
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 6;
        break;
    case 6:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetW5C(nodeOf(scene, rec), 0);
        }
        break;
    }
}

// .text:0x00057F50 size:0x148 mapped:0x80696FE4
void fn_2_57F50(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeSetFlag2(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 1:
    case 8:
    case 0x24:
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 0x26;
        break;
    }
}

// .text:0x00058098 size:0x148 mapped:0x8069712C
void fn_2_58098(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeSetFlag2(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 1:
    case 8:
    case 0x24:
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 0x26;
        break;
    }
}

// .text:0x000581E0 size:0x148 mapped:0x80697274
void fn_2_581E0(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeSetFlag2(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 1:
    case 8:
    case 0x24:
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 0x26;
        break;
    }
}

// .text:0x00058328 size:0x148 mapped:0x806973BC
void fn_2_58328(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeSetFlag2(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 1:
    case 8:
    case 0x24:
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 0x26;
        break;
    }
}

// .text:0x00058470 size:0xA0 mapped:0x80697504
void fn_2_58470(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        rec->state = 0x26;
        break;
    case 1:
    case 5:
    case 8:
    case 0x24:
        break;
    case 2:
        rec->state = 0x25;
        break;
    }
}

// .text:0x00058510 size:0x2C mapped:0x806975A4
void fn_2_58510(TextScene *scene, TextHandleRec *rec) {
    nodeClearFlag2(nodeOf(scene, rec));
}

// .text:0x0005853C size:0x2BC mapped:0x806975D0
void fn_2_5853C(void) {
    s32 off = workS16(0x7706) * 0x16;

    *(s16 *)(workBase() + 0x7404) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x140);
    *(u8 *)(workBase() + 0x7410) = lbl_2_bss_1A8240[off + 0x14C];
    *(s16 *)(workBase() + 0x7406) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x142);
    *(u8 *)(workBase() + 0x7411) = lbl_2_bss_1A8240[off + 0x14D];
    *(s16 *)(workBase() + 0x7408) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x144);
    *(u8 *)(workBase() + 0x7412) = lbl_2_bss_1A8240[off + 0x14E];
    *(s16 *)(workBase() + 0x740A) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x146);
    *(u8 *)(workBase() + 0x7413) = lbl_2_bss_1A8240[off + 0x14F];
    *(s16 *)(workBase() + 0x740C) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x148);
    *(u8 *)(workBase() + 0x7414) = lbl_2_bss_1A8240[off + 0x150];
    *(s16 *)(workBase() + 0x740E) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x14A);
    *(u8 *)(workBase() + 0x7415) = lbl_2_bss_1A8240[off + 0x151];
    *(u8 *)(workBase() + 0x7417) = lbl_2_bss_1A8240[off + 0x153];
    *(u8 *)(workBase() + 0x7418) = lbl_2_bss_1A8240[off + 0x154];
    *(u8 *)(workBase() + 0x7416) = lbl_2_bss_1A8240[off + 0x152];

    fn_8006C2B4(workBase() + 0x7430, workBase() + 0x7404);
    memcpy(workBase() + 0x741A, workBase() + 0x7404, 0x16);
    memcpy(workBase() + 0x7440, workBase() + 0x7430, 0x10);

    *(s16 *)(workBase() + 0x7404) = *(s16 *)(workBase() + 0x741A);
    *(s16 *)(workBase() + 0x7406) = *(s16 *)(workBase() + 0x741C);
    *(s16 *)(workBase() + 0x7408) = *(s16 *)(workBase() + 0x7420);
    *(s16 *)(workBase() + 0x740A) = *(s16 *)(workBase() + 0x7422);
    *(s16 *)(workBase() + 0x740C) = *(s16 *)(workBase() + 0x741E);
    *(s16 *)(workBase() + 0x740E) = *(s16 *)(workBase() + 0x7424);
    *(s16 *)(workBase() + 0x7430) = *(s16 *)(workBase() + 0x7440);
    *(s16 *)(workBase() + 0x7432) = *(s16 *)(workBase() + 0x7442);
    *(s16 *)(workBase() + 0x7434) = *(s16 *)(workBase() + 0x7446);
    *(s16 *)(workBase() + 0x7436) = *(s16 *)(workBase() + 0x7448);
    *(s16 *)(workBase() + 0x7438) = *(s16 *)(workBase() + 0x7444);
    *(s16 *)(workBase() + 0x743A) = *(s16 *)(workBase() + 0x744A);
}

// .text:0x000587F8 size:0xFA4 mapped:0x8069788C
void fn_2_587F8(void) {
    return;
}
