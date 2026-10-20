#include "menus/text_33E70.h"
#include "text/text.h"

s16 fn_2_53BC8(void *arg0);
void load_Icon(void *scene, s32 handle, u32 part, u32 element, s32 frame);
s32 text_initializeNewChannel(UnkText988Arg *arg0, s32 indexOffset, u16 arg2, s32 arg3, s32 arg4, s32 useFlag8);
void text_setPtrToWhereCharsAreStored(s32 blockIndex, s32 bankIndex, s32 stringIndex);

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8248;
extern s16 lbl_2_data_C924[];

// Work area behind lbl_2_bss_1A824C (the 0x190000 window).
#define WORK_BASE() (lbl_2_bss_1A824C + 0x190000)

#define REC_S16(rec, off) (*(s16 *)((u8 *)(rec) + (off)))

static inline u8 workU8(s32 off) {
    return *(u8 *)(WORK_BASE() + off);
}

static inline s16 workS16(s32 off) {
    return *(s16 *)(WORK_BASE() + off);
}

static inline u8 bank8248U8(s32 off) {
    return *(u8 *)(lbl_2_bss_1A8248 + off);
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

static inline u32 nodeW58(TextGraphicsObject *node) {
    return *(u32 *)((u8 *)node + 0x58);
}

static inline void nodeSetW58(TextGraphicsObject *node, u32 value) {
    *(u32 *)((u8 *)node + 0x58) = value;
}

static inline s16 recTimer(TextHandleRec *rec) {
    return REC_S16(rec, 0x6);
}

static inline void recSetTimer(TextHandleRec *rec, s16 value) {
    REC_S16(rec, 0x6) = value;
}

static inline void screenBlockSet2F(s32 blockIndex, u8 value) {
    *(u8 *)((u8 *)&screenTextArray.blocks[blockIndex] + 0x2F) = value;
}


// .text:0x00035DB4 size:0x10C mapped:0x80674E48
void fn_2_35DB4(TextScene *scene, TextHandleRec *rec) {
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
        nodeSetByte68(nodeOf(scene, rec), 0);
        rec->state = 0x25;
        break;
    case 5:
    case 0x25:
        break;
    }
}

// .text:0x00035A14 size:0x3A0 mapped:0x80674AA8
void fn_2_35A14(TextScene *scene, TextHandleRec *rec) {
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
        load_Icon(scene, rec->handle, 1, 0xCF, rec->unk10);
        nodeSetFlag2(nodeOf(scene, rec));
        nodeSetW5C(nodeOf(scene, rec), 0);
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 3;
        break;
    case 3:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 3) {
            nodeSetW5C(nodeOf(scene, rec), 3 << 16);
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 0x25;
        }
        break;
    case 0x25:
        if (workS16(0x76D8) == rec->unkA) {
            if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 8) {
                nodeSetW5C(nodeOf(scene, rec), 8 << 16);
                nodeSetByte68(nodeOf(scene, rec), 0);
            } else {
                nodeSetByte68(nodeOf(scene, rec), 1);
            }
        } else if ((nodeW5C(nodeOf(scene, rec)) >> 16) <= 3) {
            nodeSetW5C(nodeOf(scene, rec), 3 << 16);
            nodeSetByte68(nodeOf(scene, rec), 0);
        } else {
            nodeSetByte68(nodeOf(scene, rec), 4);
        }
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), workS16(0x76D8) == rec->unkA ? 1 : 4);
        rec->state = 6;
        break;
    case 6:
        if (workS16(0x76D8) == rec->unkA) {
            if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 0xB) {
                nodeSetByte68(nodeOf(scene, rec), 0);
                rec->state = 7;
            }
        } else if ((nodeW5C(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 7;
        }
        break;
    case 7:
        nodeClearFlag2(nodeOf(scene, rec));
        break;
    }
}

// .text:0x00035860 size:0x1B4 mapped:0x806748F4
void fn_2_35860(TextScene *scene, TextHandleRec *rec) {
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

// .text:0x00035754 size:0x10C mapped:0x806747E8
void fn_2_35754(TextScene *scene, TextHandleRec *rec) {
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
        nodeSetByte68(nodeOf(scene, rec), 0);
        rec->state = 0x25;
        break;
    case 5:
    case 0x25:
        break;
    }
}

// .text:0x000353FC size:0x358 mapped:0x80674490
void fn_2_353FC(TextScene *scene, TextHandleRec *rec) {
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
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 3;
        break;
    case 3:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 5) {
            rec->state = 0x25;
        }
        break;
    case 0x25:
        if (workS16(0x76DA) == 0) {
            if ((nodeW5C(nodeOf(scene, rec)) >> 16) <= 5) {
                nodeSetW5C(nodeOf(scene, rec), 5 << 16);
                nodeSetByte68(nodeOf(scene, rec), 0);
            } else {
                nodeSetByte68(nodeOf(scene, rec), 4);
            }
        } else if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 0xA) {
            nodeSetW5C(nodeOf(scene, rec), 0xA << 16);
            nodeSetByte68(nodeOf(scene, rec), 0);
        } else {
            nodeSetByte68(nodeOf(scene, rec), 1);
        }
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), workS16(0x76DA) == 0 ? 4 : 1);
        rec->state = 6;
        break;
    case 6:
        if (workS16(0x76DA) == 0) {
            if ((nodeW5C(nodeOf(scene, rec)) >> 16) == 0) {
                nodeSetByte68(nodeOf(scene, rec), 0);
                rec->state = 7;
            }
        } else if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 0xF) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 7;
        }
        break;
    case 7:
        nodeClearFlag2(nodeOf(scene, rec));
        break;
    }
}

// .text:0x0003523C size:0x1C0 mapped:0x806742D0
void fn_2_3523C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        REC_S16(rec, 0x12) = 0xFF;
        REC_S16(rec, 0x14) = text_initializeNewChannel((UnkText988Arg *)scene, rec->handle,
                                                       (u16)rec->unk10, 4, 0x312, 0);
        rec->state = 0x26;
        break;
    case 2:
        nodeSetFlag2(nodeOf(scene, rec));
        screenBlockSet2F(REC_S16(rec, 0x14), 1);
        rec->state = 3;
        break;
    case 3:
        rec->state = 0x25;
        break;
    case 0x25:
        rec->state = 0x25;
        break;
    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    }
    nodeSetW58(nodeOf(scene, rec), (nodeW58(nodeOf(scene, rec)) & ~0xFF) | REC_S16(rec, 0x12));
}

// .text:0x00035088 size:0x1B4 mapped:0x8067411C
void fn_2_35088(TextScene *scene, TextHandleRec *rec) {
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

// .text:0x00034F6C size:0x11C mapped:0x80674000
void fn_2_34F6C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 1:
    case 3:
        break;
    case 2:
        nodeSetFlag2(nodeOf(scene, rec));
        rec->state = 0x25;
        break;
    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        break;
    case 0x25:
        break;
    }
}

// .text:0x00034D70 size:0x1FC mapped:0x80673E04
void fn_2_34D70(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        REC_S16(rec, 0x12) = 0xFF;
        REC_S16(rec, 0x14) = text_initializeNewChannel((UnkText988Arg *)scene, rec->handle,
                                                       (u16)rec->unk10, 4, 0x306, 0);
        rec->state = 0x26;
        break;
    case 2:
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 4, bank8248U8(0x4415) + 0x305);
        nodeSetFlag2(nodeOf(scene, rec));
        screenBlockSet2F(REC_S16(rec, 0x14), 1);
        rec->state = 3;
        break;
    case 3:
        rec->state = 0x25;
        break;
    case 0x25:
        rec->state = 0x25;
        break;
    case 5:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    }
    screenBlockSet2F(REC_S16(rec, 0x14), 1);
    nodeSetW58(nodeOf(scene, rec), (nodeW58(nodeOf(scene, rec)) & ~0xFF) | REC_S16(rec, 0x12));
}

// .text:0x00034BCC size:0x1A4 mapped:0x80673C60
void fn_2_34BCC(TextScene *scene, TextHandleRec *rec) {
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
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 5:
        recSetTimer(rec, 3);
        rec->state = 6;
        break;
    case 6: {
        s16 oldTimer = recTimer(rec);
        recSetTimer(rec, oldTimer - 1);
        if (oldTimer <= 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x000349F8 size:0x1D4 mapped:0x80673A8C
void fn_2_349F8(TextScene *scene, TextHandleRec *rec) {
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
        load_Icon(scene, rec->handle, 1, 0xCD, bank8248U8(0x4415) - 1);
        nodeSetFlag2(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 5:
        recSetTimer(rec, 3);
        rec->state = 6;
        break;
    case 6: {
        s16 oldTimer = recTimer(rec);
        recSetTimer(rec, oldTimer - 1);
        if (oldTimer <= 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00034844 size:0x1B4 mapped:0x806738D8
void fn_2_34844(TextScene *scene, TextHandleRec *rec) {
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

// .text:0x000346D8 size:0x16C mapped:0x8067376C
void fn_2_346D8(TextScene *scene, TextHandleRec *rec) {
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
        rec->state = 0x25;
        break;
    case 5:
        recSetTimer(rec, 0x29);
        rec->state = 6;
        break;
    case 6: {
        s16 oldTimer = recTimer(rec);
        recSetTimer(rec, oldTimer - 1);
        if (oldTimer <= 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00034524 size:0x1B4 mapped:0x806735B8
void fn_2_34524(TextScene *scene, TextHandleRec *rec) {
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

// .text:0x0003439C size:0x188 mapped:0x80673430
void fn_2_3439C(TextScene *scene, TextHandleRec *rec) {
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
        recSetTimer(rec, 0x29);
        rec->state = 6;
        break;
    case 6: {
        s16 oldTimer = recTimer(rec);
        recSetTimer(rec, oldTimer - 1);
        if (oldTimer <= 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00034214 size:0x188 mapped:0x806732A8
void fn_2_34214(TextScene *scene, TextHandleRec *rec) {
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
        recSetTimer(rec, 0x29);
        rec->state = 6;
        break;
    case 6: {
        s16 oldTimer = recTimer(rec);
        recSetTimer(rec, oldTimer - 1);
        if (oldTimer <= 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00034060 size:0x1B4 mapped:0x806730F4
void fn_2_34060(TextScene *scene, TextHandleRec *rec) {
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

// .text:0x00033E70 size:0x1F0 mapped:0x80672F04
void fn_2_33E70(TextScene *scene, TextHandleRec *rec) {
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
        load_Icon(scene, rec->handle, 1, 0x2E,
                 *(s16 *)((u8 *)lbl_2_data_C924 + rec->unkA * 0x18 + workU8(0x785B) * 2));
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
