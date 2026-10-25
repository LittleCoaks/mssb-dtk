#include "menus/text_579B4.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
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

static inline void nodeShow(TextGraphicsObject *node) {
    node->flags |= UI_FLAG_VISIBLE;
}

static inline void nodeHide(TextGraphicsObject *node) {
    node->flags &= ~UI_FLAG_VISIBLE;
}

static inline void nodeSetPlayMode(TextGraphicsObject *node, u8 value) {
    ((UIRecord *)node)->playMode = value;
}

static inline u32 nodeFrame(TextGraphicsObject *node) {
    return ((UIRecord *)node)->frame;
}

static inline void nodeSetFrame(TextGraphicsObject *node, u32 value) {
    ((UIRecord *)node)->frame = value;
}

// Shared lookup: lbl_2_data_1FD84[work.s16(0x76FA) + work.s16(0x76FE)].
static inline s16 workTableLookup(void) {
    return lbl_2_data_1FD84[workS16(0x76FA) + workS16(0x76FE)];
}

static inline u8 *recordCopyDestination(s32 fieldOffset, s32 recordOffset, s32 base) {
    u8 *address = lbl_2_bss_1A824C + fieldOffset;
    address += base;
    address += recordOffset;
    return address;
}

// .text:0x000587F8 size:0xFA4 mapped:0x8069788C
void fn_2_587F8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 state = (s8)ITEM_STATE(item);
    s32 i;
    u8 *settings = g_d_GameSettings;
    u8 *characterFlags = lbl_80354768;

    switch (state) {
    case 0:
        WORK_S32(0x76A4) = 0;
        WORK_S32(0x76A0) = 0;
        ITEM_STATE(item) = 1;
        break;
    case 1:
        fn_2_1FFC4(8);
        for (i = 0; i < 8; i++) {
            fn_2_1FF10(i);
            switch (i) {
            case 0:
                if (WORK_S32(0x76A0) == i) {
                    if ((atBatButtons() & INPUT_BUTTON_A) || (s8)AtBat_ButtonInput1[0x13] > 0x32) {
                        ITEM_STATE(item) = 4;
                    }
                }
                break;
            case 1:
                if (WORK_S32(0x76A0) == i && (atBatButtons() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT))) {
                    lbl_2_bss_1A8244[0xF4] ^= 1;
                    fn_2_5EB78();
                }
                break;
            case 2:
                if (WORK_S32(0x76A0) == i) {
                    u16 buttons = atBatButtons();
                    if (buttons & INPUT_BUTTON_LEFT) {
                        for (i = 0; i < 0x20; i++) {
                            lbl_2_bss_1A8240[0x400 + i] = ((s8)lbl_2_bss_1A8240[0x400 + i] + 3) % 4;
                        }
                    } else if (buttons & INPUT_BUTTON_RIGHT) {
                        for (i = 0; i < 0x20; i++) {
                            lbl_2_bss_1A8240[0x400 + i] = ((s8)lbl_2_bss_1A8240[0x400 + i] + 1) % 4;
                        }
                    }
                }
                if (atBatButtons() & INPUT_TRIGGER_R) {
                    for (i = 0; i < 0x20; i++) {
                        lbl_2_bss_1A8240[0x153 + 0x16 * i] = 0x46;
                    }
                }
                if (atBatButtons() & INPUT_TRIGGER_L) {
                    for (i = 0; i < 0x20; i++) {
                        lbl_2_bss_1A8240[0x153 + 0x16 * i] = 0x00;
                    }
                }
                break;
            case 3:
                if (WORK_S32(0x76A0) == i && (atBatButtons() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT))) {
                    WORK_U8(0x785E) = ((s8)WORK_U8(0x785E) + 1) % 5;
                    fn_2_5EB78();
                }
                break;
            case 4:
                if (WORK_S32(0x76A0) == i && (atBatButtons() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT))) {
                    for (i = 0; i < 0x36; i++) {
                        characterFlags[0xCF18 + i] = (characterFlags[0xCF18 + i] + 1) % 2;
                    }
                }
                break;
            case 5:
                if (WORK_S32(0x76A0) == i) {
                    u16 buttons = atBatButtons();
                    if (buttons & INPUT_BUTTON_LEFT) {
                        settings[0x12] = (settings[0x12] + 2) % 3;
                        fn_2_5EB78();
                    } else if (buttons & INPUT_BUTTON_RIGHT) {
                        settings[0x12] = (settings[0x12] + 1) % 3;
                        fn_2_5EB78();
                    }
                }
                break;
            case 6:
                if (WORK_S32(0x76A0) == i && (atBatButtons() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT))) {
                    WORK_U8(0x7862) ^= 1;
                    fn_2_5EB78();
                    {
                        s32 recordOffset = 0;
                        s32 record;
                        s32 fieldOffset;

                        record = 0;

                        do {
                            if (record == 6) {
                                *(u32 *)(lbl_2_bss_1A824C + recordOffset + 0x1972EC) = *(u32 *)(lbl_2_bss_1A8240 + 0x118);
                                *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x1972F0) = *(s16 *)(lbl_2_bss_1A8240 + 0x11C);
                                *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x1972F2) = *(s16 *)(lbl_2_bss_1A8240 + 0x11E);
                                *(u32 *)(lbl_2_bss_1A824C + recordOffset + 0x1972F4) = *(u32 *)(lbl_2_bss_1A8240 + 0x120);
                                *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x1972F8) = *(s16 *)(lbl_2_bss_1A8240 + 0x124);
                                *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x1972FA) = *(s16 *)(lbl_2_bss_1A8240 + 0x126);
                                *(u32 *)(lbl_2_bss_1A824C + recordOffset + 0x1972FC) = *(u32 *)(lbl_2_bss_1A8240 + 0x128);
                                *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x197300) = *(s16 *)(lbl_2_bss_1A8240 + 0x12C);
                                *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x197302) = *(s16 *)(lbl_2_bss_1A8240 + 0x12E);
                                *(u32 *)(lbl_2_bss_1A824C + recordOffset + 0x197304) = *(u32 *)(lbl_2_bss_1A8240 + 0x130);
                                *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x197308) = *(s16 *)(lbl_2_bss_1A8240 + 0x134);
                                *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x19730A) = *(s16 *)(lbl_2_bss_1A8240 + 0x136);
                                *(u32 *)(lbl_2_bss_1A824C + recordOffset + 0x19730C) = *(u32 *)(lbl_2_bss_1A8240 + 0x138);
                                *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x197310) = *(s16 *)(lbl_2_bss_1A8240 + 0x13C);
                                *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x197312) = *(s16 *)(lbl_2_bss_1A8240 + 0x13E);
                            } else {
                                for (fieldOffset = 0; fieldOffset < 0x28; fieldOffset += 8) {
                                    *(u32 *)recordCopyDestination(fieldOffset, recordOffset, 0x1972EC) =
                                        *(u32 *)(lbl_2_bss_1A8240 + lbl_2_data_20C48[record] * 0x28 + fieldOffset + 0x28);
                                    *(s16 *)recordCopyDestination(fieldOffset, recordOffset, 0x1972F0) =
                                        *(s16 *)(lbl_2_bss_1A8240 + lbl_2_data_20C48[record] * 0x28 + fieldOffset + 0x2C);
                                    *(s16 *)recordCopyDestination(fieldOffset, recordOffset, 0x1972F2) =
                                        *(s16 *)(lbl_2_bss_1A8240 + lbl_2_data_20C48[record] * 0x28 + fieldOffset + 0x2E);
                                }
                            }
                            record++;
                            recordOffset += 0x28;
                        } while (record < 7);
                    }
                    *(u32 *)(lbl_2_bss_1A824C + 0x1972C4) = *(u32 *)(lbl_2_bss_1A8240 + 0x0);
                    *(s16 *)(lbl_2_bss_1A824C + 0x1972CA) = *(s16 *)(lbl_2_bss_1A8240 + 0x6);
                    *(u32 *)(lbl_2_bss_1A824C + 0x1972CC) = *(u32 *)(lbl_2_bss_1A8240 + 0x8);
                    *(s16 *)(lbl_2_bss_1A824C + 0x1972D2) = *(s16 *)(lbl_2_bss_1A8240 + 0xE);
                    *(u32 *)(lbl_2_bss_1A824C + 0x1972D4) = *(u32 *)(lbl_2_bss_1A8240 + 0x10);
                    *(s16 *)(lbl_2_bss_1A824C + 0x1972DA) = *(s16 *)(lbl_2_bss_1A8240 + 0x16);
                    *(u32 *)(lbl_2_bss_1A824C + 0x1972DC) = *(u32 *)(lbl_2_bss_1A8240 + 0x18);
                    *(s16 *)(lbl_2_bss_1A824C + 0x1972E2) = *(s16 *)(lbl_2_bss_1A8240 + 0x1E);
                    *(u32 *)(lbl_2_bss_1A824C + 0x1972E4) = *(u32 *)(lbl_2_bss_1A8240 + 0x20);
                    *(s16 *)(lbl_2_bss_1A824C + 0x1972EA) = *(s16 *)(lbl_2_bss_1A8240 + 0x26);

                }
                break;
            case 7:
                if (WORK_S32(0x76A0) == i && (atBatButtons() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT))) {
                    for (i = 0; i < 0x36; i++) {
                        u8 idx = lbl_800E869C[i];
                        lbl_2_bss_1A8244[idx] = (lbl_2_bss_1A8244[idx] + 1) % 2;
                    }
                }
                break;
            }
        }

        if ((atBatButtons() & INPUT_BUTTON_B) || (s8)AtBat_ButtonInput1[0x13] > 0x32) {
            ITEM_STATE(item) = 4;
        }
        break;
    case 4:
        item->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        ITEM_STATE(item) = 0;
        break;
    }
}

// .text:0x0005853C size:0x2BC mapped:0x806975D0
void fn_2_5853C(void) {
    s32 off = workS16(0x7706) * 0x16;

    *(s16 *)(workBase() + 0x7404) = *(s16 *)&lbl_2_bss_1A8240[off + 0x140];
    *(u8 *)(workBase() + 0x7410) = lbl_2_bss_1A8240[off + 0x14C];
    *(s16 *)(workBase() + 0x7406) = *(s16 *)&lbl_2_bss_1A8240[off + 0x142];
    *(u8 *)(workBase() + 0x7411) = lbl_2_bss_1A8240[off + 0x14D];
    *(s16 *)(workBase() + 0x7408) = *(s16 *)&lbl_2_bss_1A8240[off + 0x144];
    *(u8 *)(workBase() + 0x7412) = lbl_2_bss_1A8240[off + 0x14E];
    *(s16 *)(workBase() + 0x740A) = *(s16 *)&lbl_2_bss_1A8240[off + 0x146];
    *(u8 *)(workBase() + 0x7413) = lbl_2_bss_1A8240[off + 0x14F];
    *(s16 *)(workBase() + 0x740C) = *(s16 *)&lbl_2_bss_1A8240[off + 0x148];
    *(u8 *)(workBase() + 0x7414) = lbl_2_bss_1A8240[off + 0x150];
    *(s16 *)(workBase() + 0x740E) = *(s16 *)&lbl_2_bss_1A8240[off + 0x14A];
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
    nodeHide(nodeOf(scene, rec));
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
    case 0x25:
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 8:
    case 0x24:
    case 0x25:
        break;
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 8:
    case 0x24:
    case 0x25:
        break;
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 8:
    case 0x24:
    case 0x25:
        break;
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 8:
    case 0x24:
    case 0x25:
        break;
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetFrame(nodeOf(scene, rec), 0);
        fn_80036134(scene, 0x1E, rec->unkA, rec->unkA + 5);
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 3;
        break;
    case 3: {
        s32 selected = workS16(0x76FA);
        if (selected == rec->unkA) {
            if ((nodeFrame(nodeOf(scene, rec)) >> 16) >= 0x14) {
                nodeSetFrame(nodeOf(scene, rec), 0x140000);
                nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
                rec->state = 0x25;
            }
        } else {
            if ((nodeFrame(nodeOf(scene, rec)) >> 16) >= 0xA) {
                nodeSetFrame(nodeOf(scene, rec), 0xA0000);
                nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
                rec->state = 0x25;
            }
        }
        break;
    }
    case 0x25: {
        s32 selected = workS16(0x76FA);
        if (selected == rec->unkA) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
            if ((nodeFrame(nodeOf(scene, rec)) >> 16) >= 0x14) {
                nodeSetFrame(nodeOf(scene, rec), 0x140000);
            }
        } else {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
            if ((nodeFrame(nodeOf(scene, rec)) >> 16) <= 0xA) {
                nodeSetFrame(nodeOf(scene, rec), 0xA0000);
            }
        }
        break;
    }
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        if ((nodeFrame(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetFrame(nodeOf(scene, rec), 0);
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        if (workTableLookup() >= 2) {
            nodeShow(nodeOf(scene, rec));
        } else {
            nodeHide(nodeOf(scene, rec));
        }
        rec->state = 0x25;
        break;
    case 0x25:
        if (workTableLookup() >= 2) {
            nodeShow(nodeOf(scene, rec));
        } else {
            nodeHide(nodeOf(scene, rec));
        }
        break;
    case 5:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    }
}
