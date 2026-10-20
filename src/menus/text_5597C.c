#include "menus/text_5597C.h"
#include "menus/text_35EC0.h"
#include "text/text.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x8001f228.h"

// Local prototypes and externs for symbols owned by other units.
void fn_2_4E7EC(void);
s16 fn_2_53BC8(void *arg);
void fn_80035B50(s32 arg);
void fn_80036134(void *scene, s32 a, s32 b, s32 c);
void load_Icon(void *scene, s32 handle, u32 part, u32 element, s32 frame);
s32 fn_80036214(void *scene, s32 a, s32 b, s32 c);

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A823C;
extern s16 lbl_2_data_1FD84[];
extern s16 lbl_2_data_1FBB4[];

// Work area behind lbl_2_bss_1A824C (the 0x190000 window).
#define WORK_BASE() (lbl_2_bss_1A824C + 0x190000)
#define WORK_U8(off) (*(u8 *)(WORK_BASE() + (off)))
#define REC_S16(rec, off) (*(s16 *)((u8 *)(rec) + (off)))

static inline s16 workS16(s32 off) {
    return *(s16 *)(WORK_BASE() + off);
}

// Table row for the current work-area pair (+0x76FA, +0x76FE).
static inline s16 lookupFD84(void) {
    return lbl_2_data_1FD84[workS16(0x76FA) + workS16(0x76FE)];
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

static inline u32 nodeW5C(TextGraphicsObject *node) {
    return *(u32 *)((u8 *)node + 0x5C);
}

static inline void nodeSetW5C(TextGraphicsObject *node, u32 value) {
    *(u32 *)((u8 *)node + 0x5C) = value;
}

static inline u32 nodeW58(TextGraphicsObject *node) {
    return *(u32 *)((u8 *)node + 0x58);
}

static inline void nodeSetW58(TextGraphicsObject *node, u32 value) {
    *(u32 *)((u8 *)node + 0x58) = value;
}

static inline void nodeSetByte68(TextGraphicsObject *node, u8 value) {
    *(u8 *)((u8 *)node + 0x68) = value;
}

// .text:0x0005786C size:0x148 mapped:0x80696900
void fn_2_5786C(TextScene *scene, TextHandleRec *rec) {
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
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 0x26;
        break;
    case 8:
    case 0x24:
    case 0x25:
        break;
    }
}

// .text:0x00057724 size:0x148 mapped:0x806967B8
void fn_2_57724(TextScene *scene, TextHandleRec *rec) {
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
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 0x26;
        break;
    case 8:
    case 0x24:
    case 0x25:
        break;
    }
}

// .text:0x0005754C size:0x1D8 mapped:0x806965E0
void fn_2_5754C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x26;
        break;
    case 2:
        nodeSetFlag2(nodeOf(scene, rec));
        fn_80036134(scene, 0x1D, workS16(0x76FA), 0x0E);
        nodeSetW5C(nodeOf(scene, rec), 0);
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 0x25:
        fn_80036134(scene, 0x1D, workS16(0x76FA), 0x0E);
        break;
    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 4:
        break;
    }
}

// .text:0x00057294 size:0x2B8 mapped:0x80696328
void fn_2_57294(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        fn_80036134(scene, 0x1B, REC_S16(rec, 0xA), REC_S16(rec, 0xA) + 0xF);
        nodeSetW5C(nodeOf(scene, rec), 0);
        load_Icon(scene, rec->handle, 1, 0x15, REC_S16(rec, 0xA));
        REC_S16(rec, 6) = REC_S16(rec, 0xA);
        rec->state = 0x26;
        break;
    case 2:
        if (REC_S16(rec, 6)-- <= 0) {
            nodeSetFlag2(nodeOf(scene, rec));
            nodeSetByte68(nodeOf(scene, rec), 1);
            rec->state = 3;
        }
        break;
    case 3:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 5) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 0x25;
        }
        break;
    case 0x25:
        if (REC_S16(rec, 0xA) == workS16(0x76F4)) {
            if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 0xF) {
                nodeSetW5C(nodeOf(scene, rec), 0xF << 16);
            } else {
                nodeSetByte68(nodeOf(scene, rec), 1);
            }
        } else {
            if ((nodeW5C(nodeOf(scene, rec)) >> 16) <= 5) {
                nodeSetW5C(nodeOf(scene, rec), 5 << 16);
            } else {
                nodeSetByte68(nodeOf(scene, rec), 4);
            }
        }
        break;
    case 5:
        nodeSetW5C(nodeOf(scene, rec), 0);
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 0x26;
        break;
    }
}

// .text:0x000570E4 size:0x1B0 mapped:0x80696178
void fn_2_570E4(TextScene *scene, TextHandleRec *rec) {
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
        nodeSetW5C(nodeOf(scene, rec), 0);
        nodeSetFlag2(nodeOf(scene, rec));
        fn_80036134(scene, 0x1C, workS16(0x76F4), 0x1A);
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 0x25:
        fn_80036134(scene, 0x1C, workS16(0x76F4), 0x1A);
        break;
    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    }
}

// .text:0x00056E8C size:0x258 mapped:0x80695F20
void fn_2_56E8C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        REC_S16(rec, 0x12) = 0;
        REC_S16(rec, 0x14) = text_initializeNewChannel((UnkText988Arg *)scene, rec->handle, (u16)REC_S16(rec, 0x10), 2,
                                                       0x215, 0);
        rec->state = 0x26;
        break;
    case 2:
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, REC_S16(rec, 0xA) + 0x215);
        nodeSetFlag2(nodeOf(scene, rec));
        rec->state = 3;
        break;
    case 3:
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + (0xFF - REC_S16(rec, 0x12)) / 4;
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + 1;
        if (REC_S16(rec, 0x12) > 0xFF) {
            REC_S16(rec, 0x12) = 0xFF;
        }
        if (REC_S16(rec, 0x12) >= 0xFF) {
            rec->state = 0x25;
        }
        break;
    case 0x25:
        rec->state = 0x25;
        break;
    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 6;
        break;
    case 6:
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + (-REC_S16(rec, 0x12)) / 4;
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) - 1;
        if (REC_S16(rec, 0x12) < 0) {
            REC_S16(rec, 0x12) = 0;
        }
        break;
    }

    screenTextArray.blocks[REC_S16(rec, 0x14)].justify = 1;
    nodeSetW58(nodeOf(scene, rec), (nodeW58(nodeOf(scene, rec)) & ~0xFF) | REC_S16(rec, 0x12));
}

// .text:0x00056C34 size:0x258 mapped:0x80695CC8
void fn_2_56C34(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        REC_S16(rec, 0x12) = 0;
        REC_S16(rec, 0x14) = text_initializeNewChannel((UnkText988Arg *)scene, rec->handle, (u16)REC_S16(rec, 0x10), 2,
                                                       0x213, 0);
        rec->state = 0x26;
        break;
    case 2:
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, REC_S16(rec, 0xA) + 0x213);
        nodeSetFlag2(nodeOf(scene, rec));
        rec->state = 3;
        break;
    case 3:
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + (0xFF - REC_S16(rec, 0x12)) / 4;
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + 1;
        if (REC_S16(rec, 0x12) > 0xFF) {
            REC_S16(rec, 0x12) = 0xFF;
        }
        if (REC_S16(rec, 0x12) >= 0xFF) {
            rec->state = 0x25;
        }
        break;
    case 0x25:
        rec->state = 0x25;
        break;
    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 6;
        break;
    case 6:
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + (-REC_S16(rec, 0x12)) / 4;
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) - 1;
        if (REC_S16(rec, 0x12) < 0) {
            REC_S16(rec, 0x12) = 0;
        }
        break;
    }

    screenTextArray.blocks[REC_S16(rec, 0x14)].justify = 1;
    nodeSetW58(nodeOf(scene, rec), (nodeW58(nodeOf(scene, rec)) & ~0xFF) | REC_S16(rec, 0x12));
}

// .text:0x0005699C size:0x298 mapped:0x80695A30
void fn_2_5699C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s32 v5;

    if (result != -1) {
        rec->state = result;
    }
    v5 = (s16)(workS16(0x76FE) + workS16(0x76FA));
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        REC_S16(rec, 0x12) = 0;
        REC_S16(rec, 0x14) = text_initializeNewChannel((UnkText988Arg *)scene, rec->handle, (u16)REC_S16(rec, 0x10), 2,
                                                       0, 0);
        rec->state = 0x26;
        break;
    case 2:
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, v5);
        nodeSetFlag2(nodeOf(scene, rec));
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, v5);
        rec->state = 3;
        break;
    case 3:
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + (0xFF - REC_S16(rec, 0x12)) / 4;
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + 1;
        if (REC_S16(rec, 0x12) > 0xFF) {
            REC_S16(rec, 0x12) = 0xFF;
        }
        if (REC_S16(rec, 0x12) >= 0xFF) {
            rec->state = 0x25;
        }
        break;
    case 0x25:
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, v5);
        rec->state = 0x25;
        break;
    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 6;
        break;
    case 6:
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + (-REC_S16(rec, 0x12)) / 4;
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) - 1;
        if (REC_S16(rec, 0x12) < 0) {
            REC_S16(rec, 0x12) = 0;
        }
        break;
    }

    screenTextArray.blocks[REC_S16(rec, 0x14)].justify = 1;
    nodeSetW58(nodeOf(scene, rec), (nodeW58(nodeOf(scene, rec)) & ~0xFF) | REC_S16(rec, 0x12));
}

// .text:0x00056688 size:0x314 mapped:0x8069571C
void fn_2_56688(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s32 v5;
    s32 ret;

    if (result != -1) {
        rec->state = result;
    }
    v5 = (s16)((workS16(0x76FE) + REC_S16(rec, 0xA)) % workS16(0x772E));
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        REC_S16(rec, 0x12) = 0;
        REC_S16(rec, 0x14) = text_initializeNewChannel((UnkText988Arg *)scene, rec->handle, (u16)REC_S16(rec, 0x10), 2,
                                                       0, 1);
        rec->state = 0x26;
        break;
    case 2:
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, v5);
        nodeSetFlag2(nodeOf(scene, rec));
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, v5);
        rec->state = 3;
        break;
    case 3:
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + (0xFF - REC_S16(rec, 0x12)) / 4;
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + 1;
        if (REC_S16(rec, 0x12) > 0xFF) {
            REC_S16(rec, 0x12) = 0xFF;
        }
        if (REC_S16(rec, 0x12) >= 0xFF) {
            rec->state = 0x25;
        }
        break;
    case 0x25:
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, v5);
        rec->state = 0x25;
        break;
    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 6;
        break;
    case 6:
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + (-REC_S16(rec, 0x12)) / 4;
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) - 1;
        if (REC_S16(rec, 0x12) < 0) {
            REC_S16(rec, 0x12) = 0;
        }
        break;
    }

    if (REC_S16(rec, 0xA) == workS16(0x76FA)) {
        ret = fn_80036214(scene, 0x25, 0, 1);
    } else {
        ret = fn_80036214(scene, 0x26, 0, 0);
    }
    nodeSetW58(nodeOf(scene, rec), (ret & ~0xFF) | (nodeW58(nodeOf(scene, rec)) & 0xFF));
    screenTextArray.blocks[REC_S16(rec, 0x14)].justify = 0;
    nodeSetW58(nodeOf(scene, rec), (nodeW58(nodeOf(scene, rec)) & ~0xFF) | REC_S16(rec, 0x12));
}

// .text:0x000563C0 size:0x2C8 mapped:0x80695454
void fn_2_563C0(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s32 v5;

    if (result != -1) {
        rec->state = result;
    }
    v5 = (s16)((s8)WORK_U8(0x7822) + lbl_2_data_1FBB4[workS16(0x76FE) + workS16(0x76FA)]);
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        REC_S16(rec, 0x12) = 0;
        REC_S16(rec, 0x14) = text_initializeNewChannel((UnkText988Arg *)scene, rec->handle, (u16)REC_S16(rec, 0x10), 2,
                                               lbl_2_data_1FBB4[0], 0);
        rec->state = 0x26;
        break;
    case 2:
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, v5);
        nodeSetFlag2(nodeOf(scene, rec));
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, v5);
        rec->state = 3;
        break;
    case 3:
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + (0xFF - REC_S16(rec, 0x12)) / 4;
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + 1;
        if (REC_S16(rec, 0x12) > 0xFF) {
            REC_S16(rec, 0x12) = 0xFF;
        }
        if (REC_S16(rec, 0x12) >= 0xFF) {
            rec->state = 0x25;
        }
        break;
    case 0x25:
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 2, v5);
        rec->state = 0x25;
        break;    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 6;
        break;
    case 6:
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) + (-REC_S16(rec, 0x12)) / 4;
        REC_S16(rec, 0x12) = REC_S16(rec, 0x12) - 1;
        if (REC_S16(rec, 0x12) < 0) {
            REC_S16(rec, 0x12) = 0;
        }
        break;

    }

    screenTextArray.blocks[REC_S16(rec, 0x14)].justify = 0;
    screenTextArray.blocks[REC_S16(rec, 0x14)].verticalAlign = 1;
    nodeSetW58(nodeOf(scene, rec), (nodeW58(nodeOf(scene, rec)) & ~0xFF) | REC_S16(rec, 0x12));
}

// .text:0x00056160 size:0x260 mapped:0x806951F4
void fn_2_56160(TextScene *scene, TextHandleRec *rec) {
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
    case 8:
    case 17:
        if (lookupFD84() > 1) {
            nodeSetW5C(nodeOf(scene, rec), 0);
            nodeSetFlag2(nodeOf(scene, rec));
            nodeSetByte68(nodeOf(scene, rec), 1);
        } else {
            nodeSetByte68(nodeOf(scene, rec), 4);
        }
        rec->state = 0x25;
        break;
    case 5:
        if (lookupFD84() > 1) {
            nodeSetByte68(nodeOf(scene, rec), 4);
            rec->state = 6;
        } else {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    case 6:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 7;
        }
        break;
    case 7:
        nodeClearFlag2(nodeOf(scene, rec));
        break;
    case 0x25:
        break;
    }
}

// .text:0x00055FD8 size:0x188 mapped:0x8069506C
void fn_2_55FD8(TextScene *scene, TextHandleRec *rec) {
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
    case 8:
    case 17:
        if (lookupFD84() > 1) {
            nodeSetFlag2(nodeOf(scene, rec));
        } else {
            nodeSetFlag2(nodeOf(scene, rec));
        }
        rec->state = 0x25;
        break;
    case 5:
        REC_S16(rec, 6) = 10;
        rec->state = 6;
        break;
    case 6: {
        s16 timer = REC_S16(rec, 6);

        REC_S16(rec, 6) = timer - 1;
        if (timer <= 0) {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00055DD8 size:0x200 mapped:0x80694E6C
void fn_2_55DD8(TextScene *scene, TextHandleRec *rec) {
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
    case 8:
    case 17:
        if (lookupFD84() > 1) {
            nodeSetW5C(nodeOf(scene, rec), 0);
            nodeSetFlag2(nodeOf(scene, rec));
            nodeSetByte68(nodeOf(scene, rec), 1);
        } else {
            nodeSetByte68(nodeOf(scene, rec), 1);
        }
        rec->state = 0x25;
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 6;
        break;
    case 6:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 7;
        }
        break;
    case 7:
        nodeClearFlag2(nodeOf(scene, rec));
        break;
    case 0x25:
        break;
    }
}

// .text:0x00055C5C size:0x17C mapped:0x80694CF0
void fn_2_55C5C(TextScene *scene, TextHandleRec *rec) {
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
    case 8:
    case 17: {
        s16 value = lookupFD84();

        if (value > 1) {
            nodeSetFlag2(nodeOf(scene, rec));
            nodeSetW5C(nodeOf(scene, rec), (u32)((s32)(value - 1) << 16));
        }
        rec->state = 0x25;
        break;
    }
    case 5:
        REC_S16(rec, 6) = 10;
        rec->state = 6;
        break;
    case 6: {
        s16 timer = REC_S16(rec, 6);

        REC_S16(rec, 6) = timer - 1;
        if (timer <= 0) {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00055AD4 size:0x188 mapped:0x80694B68
void fn_2_55AD4(TextScene *scene, TextHandleRec *rec) {
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
    case 8:
    case 17:
        if (lookupFD84() > 1) {
            nodeSetFlag2(nodeOf(scene, rec));
            nodeSetW5C(nodeOf(scene, rec), (u32)((s32)(s8)WORK_U8(0x7822) << 16));
        }
        rec->state = 0x25;
        break;
    case 5:
        REC_S16(rec, 6) = 10;
        rec->state = 6;
        break;
    case 6: {
        s16 timer = REC_S16(rec, 6);

        REC_S16(rec, 6) = timer - 1;
        if (timer <= 0) {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00055A40 size:0x94 mapped:0x80694AD4
void fn_2_55A40(void) {
    *(u8 *)(WORK_BASE() + 0x72BC) = 1;
    fn_2_4E7EC();
    resetGameStadiumStateOnExit();
    maybeLoadsGameSoundFiles();
    fn_800ACFB0(audioFileDescriptors.files[5]);
    fn_80035B50(10);
    if (screenTextArray.textBanks[2] != NULL) {
        fn_800ACFB0(screenTextArray.textBanks[2]);
        screenTextArray.textBanks[2] = NULL;
    }
    *(u8 *)(lbl_2_bss_1A823C + 0x34) = 0;
}

// .text:0x0005597C size:0xC4 mapped:0x80694A10
s32 fn_2_5597C(void) {
    s32 sum = workS16(0x76FE) + workS16(0x76FA);

    if (sum < 0x1A) {
        return 0;
    } else if (sum < 0x34) {
        return 1;
    } else if (sum < 0x6A) {
        return 2;
    } else if (sum < 0x8C) {
        return 3;
    } else if (sum < 0x91) {
        return 4;
    } else if (sum < 0xC1) {
        return 5;
    } else if (sum < 0xC3) {
        return 6;
    } else if (sum < 0xC4) {
        return 7;
    } else if (sum < 0xD2) {
        return 8;
    } else if (sum < 0xD5) {
        return 9;
    } else {
        return 10;
    }
}
