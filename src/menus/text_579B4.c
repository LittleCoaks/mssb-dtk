#include "menus/text_579B4.h"
#include "text/text.h"
#include "Unknown/File_0x800b0a14.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

// Local prototypes for symbols owned by other units.
s16 fn_2_53BC8(void *arg0);
void fn_2_1FF10(s32 arg0);
void fn_2_1FFC4(s32 arg0);
void fn_2_5EB78(void);
void fn_80036134(void *scene, s32 a, s32 b, s32 c);
void fn_8006C2B4(void *dst, void *src);

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8240;
extern u8 *lbl_2_bss_1A8244;
extern s16 lbl_2_data_1FD84[];
extern s16 lbl_2_data_20C48[];
extern u8 lbl_800E869C[];
extern u8 lbl_80354768[];
extern u8 g_d_GameSettings[];
extern u8 AtBat_ButtonInput1[];

#define ITEM_STATE(item) (*(u8 *)((u8 *)(item) + 0x28))
#define WORK_S32(off) (*(s32 *)(workBase() + (off)))
#define WORK_U8(off) (*(u8 *)(workBase() + (off)))

// Work area behind lbl_2_bss_1A824C (the 0x190000 window).
static inline u8 *workBase(void) {
    return lbl_2_bss_1A824C + 0x190000;
}

static inline s16 workS16(s32 off) {
    return *(s16 *)(lbl_2_bss_1A824C + 0x190000 + off);
}

// Button record of the currently active AtBat input slot (index in the work area).
static inline u16 atBatButtons(void) {
    return *(u16 *)(AtBat_ButtonInput1 + (s8)WORK_U8(0x7863) * 0x20 + 2);
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

// .text:0x000587F8 size:0xFA4 mapped:0x8069788C
void fn_2_587F8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 state = (s8)ITEM_STATE(item);
    s32 i;

    if (state == 1) {
        fn_2_1FFC4(8);
        for (i = 0; i < 8; i++) {
            fn_2_1FF10(i);
            switch (i) {
            case 0:
                if (WORK_S32(0x76A0) == i) {
                    if (atBatButtons() & 0x100) {
                        ITEM_STATE(item) = 4;
                    } else if ((s8)AtBat_ButtonInput1[0x13] > 0x32) {
                        ITEM_STATE(item) = 4;
                    }
                }
                break;
            case 1:
                if (WORK_S32(0x76A0) == i && (atBatButtons() & 0x102)) {
                    lbl_2_bss_1A8244[0xF4] ^= 1;
                    fn_2_5EB78();
                }
                break;
            case 2:
                if (WORK_S32(0x76A0) == i) {
                    u16 buttons = atBatButtons();
                    if (buttons & 0x1) {
                        for (i = 0; i < 0x20; i += 8) {
                            s32 k;
                            for (k = 0; k < 8; k++) {
                                lbl_2_bss_1A8240[0x400 + i + k] = ((s8)lbl_2_bss_1A8240[0x400 + i + k] + 3) % 4;
                            }
                        }
                    } else if (buttons & 0x2) {
                        for (i = 0; i < 0x20; i += 8) {
                            s32 k;
                            for (k = 0; k < 8; k++) {
                                lbl_2_bss_1A8240[0x400 + i + k] = ((s8)lbl_2_bss_1A8240[0x400 + i + k] + 1) % 4;
                            }
                        }
                    }
                }
                if (atBatButtons() & 0x20) {
                    s32 k, j;
                    for (i = 0, k = 0; k < 2; k++, i += 0x10) {
                        for (j = 0; j < 16; j++) {
                            lbl_2_bss_1A8240[0x153 + 0x160 * k + 0x16 * j] = 0x46;
                        }
                    }
                }
                if (atBatButtons() & 0x40) {
                    s32 k, j;
                    for (i = 0, k = 0; k < 2; k++, i += 0x10) {
                        for (j = 0; j < 16; j++) {
                            lbl_2_bss_1A8240[0x153 + 0x160 * k + 0x16 * j] = 0x00;
                        }
                    }
                }
                break;
            case 3:
                if (WORK_S32(0x76A0) == i && (atBatButtons() & 0x102)) {
                    WORK_U8(0x785E) = ((s8)WORK_U8(0x785E) + 1) % 5;
                    fn_2_5EB78();
                }
                break;
            case 4:
                if (WORK_S32(0x76A0) == i && (atBatButtons() & 0x102)) {
                    for (i = 0; i < 0x36; i++) {
                        lbl_80354768[0xCF18 + i] = (lbl_80354768[0xCF18 + i] + 1) & 1;
                    }
                }
                break;
            case 5:
                if (WORK_S32(0x76A0) == i) {
                    u16 buttons = atBatButtons();
                    if (buttons & 0x1) {
                        g_d_GameSettings[0x12] = (g_d_GameSettings[0x12] + 2) % 3;
                        fn_2_5EB78();
                    } else if (buttons & 0x2) {
                        g_d_GameSettings[0x12] = (g_d_GameSettings[0x12] + 1) % 3;
                        fn_2_5EB78();
                    }
                }
                break;
            case 6:
                if (WORK_S32(0x76A0) == i && (atBatButtons() & 0x102)) {
                    s32 lay;
                    WORK_U8(0x7862) ^= 1;
                    fn_2_5EB78();
                    for (lay = 0; lay < 7; lay++) {
                        s32 off = lay * 0x28;
                        if (lay == 6) {
                            u8 *src = lbl_2_bss_1A8240;
                            u8 *dst = workBase() + off;
                            *(u32 *)(dst + 0x72EC) = *(u32 *)(src + 0x118);
                            *(s16 *)(dst + 0x72F0) = *(s16 *)(src + 0x11C);
                            *(s16 *)(dst + 0x72F2) = *(s16 *)(src + 0x11E);
                            *(u32 *)(dst + 0x72F4) = *(u32 *)(src + 0x120);
                            *(s16 *)(dst + 0x72F8) = *(s16 *)(src + 0x124);
                            *(s16 *)(dst + 0x72FA) = *(s16 *)(src + 0x126);
                            *(u32 *)(dst + 0x72FC) = *(u32 *)(src + 0x128);
                            *(s16 *)(dst + 0x7300) = *(s16 *)(src + 0x12C);
                            *(s16 *)(dst + 0x7302) = *(s16 *)(src + 0x12E);
                            *(u32 *)(dst + 0x7304) = *(u32 *)(src + 0x130);
                            *(s16 *)(dst + 0x7308) = *(s16 *)(src + 0x134);
                            *(s16 *)(dst + 0x730A) = *(s16 *)(src + 0x136);
                            *(u32 *)(dst + 0x730C) = *(u32 *)(src + 0x138);
                            *(s16 *)(dst + 0x7310) = *(s16 *)(src + 0x13C);
                            *(s16 *)(dst + 0x7312) = *(s16 *)(src + 0x13E);
                        } else {
                            s16 v = lbl_2_data_20C48[lay];
                            s32 k;
                            for (k = 0; k < 5; k++) {
                                u8 *src = lbl_2_bss_1A8240 + v * 0x28 + k * 8;
                                u8 *dst = workBase() + off + k * 8;
                                *(u32 *)(dst + 0x72EC) = *(u32 *)(src + 0x28);
                                *(s16 *)(dst + 0x72F0) = *(s16 *)(src + 0x2C);
                                *(s16 *)(dst + 0x72F2) = *(s16 *)(src + 0x2E);
                            }
                        }
                    }
                    {
                        u8 *src = lbl_2_bss_1A8240;
                        u8 *dst = workBase();
                        *(u32 *)(dst + 0x72C4) = *(u32 *)(src + 0x00);
                        *(s16 *)(dst + 0x72CA) = *(s16 *)(src + 0x06);
                        *(u32 *)(dst + 0x72CC) = *(u32 *)(src + 0x08);
                        *(s16 *)(dst + 0x72D2) = *(s16 *)(src + 0x0E);
                        *(u32 *)(dst + 0x72D4) = *(u32 *)(src + 0x10);
                        *(s16 *)(dst + 0x72DA) = *(s16 *)(src + 0x16);
                        *(u32 *)(dst + 0x72DC) = *(u32 *)(src + 0x18);
                        *(s16 *)(dst + 0x72E2) = *(s16 *)(src + 0x1E);
                        *(u32 *)(dst + 0x72E4) = *(u32 *)(src + 0x20);
                        *(s16 *)(dst + 0x72EA) = *(s16 *)(src + 0x26);
                    }
                }
                break;
            case 7:
                if (WORK_S32(0x76A0) == i && (atBatButtons() & 0x102)) {
                    for (i = 0; i < 0x36; i++) {
                        u8 idx = lbl_800E869C[i];
                        lbl_2_bss_1A8244[idx] = (lbl_2_bss_1A8244[idx] + 1) & 1;
                    }
                }
                break;
            }
        }

        if ((atBatButtons() & 0x200) || (s8)AtBat_ButtonInput1[0x13] > 0x32) {
            ITEM_STATE(item) = 4;
        }
    } else if (state > 1) {
        if (state == 4) {
            item->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
            ITEM_STATE(item) = 0;
        }
    } else if (state == 0) {
        WORK_S32(0x76A4) = 0;
        WORK_S32(0x76A0) = 0;
        ITEM_STATE(item) = 1;
    }
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

// .text:0x00058510 size:0x2C mapped:0x806975A4
void fn_2_58510(TextScene *scene, TextHandleRec *rec) {
    nodeClearFlag2(nodeOf(scene, rec));
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
