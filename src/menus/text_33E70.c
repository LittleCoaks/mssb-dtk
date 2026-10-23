#include "menus/text_33E70.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"

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

static inline u32 nodeRGBA(TextGraphicsObject *node) {
    return ((UIRecord *)node)->rgba;
}

static inline void nodeSetRGBA(TextGraphicsObject *node, u32 value) {
    ((UIRecord *)node)->rgba = value;
}

static inline s16 recTimer(TextHandleRec *rec) {
    return REC_S16(rec, 0x6);
}

static inline void recSetTimer(TextHandleRec *rec, s16 value) {
    REC_S16(rec, 0x6) = value;
}

static inline void screenBlockSet2F(s32 blockIndex, u8 value) {
    screenTextArray.blocks[blockIndex].justify = value;
}


// .text:0x00035DB4 size:0x10C mapped:0x80674E48
void fn_2_35DB4(TextScene *scene, TextHandleRec *rec) {
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
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
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
    s32 selected;
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        load_Icon(scene, rec->handle, 1, 0xCF, rec->unk10);
        nodeShow(nodeOf(scene, rec));
        nodeSetFrame(nodeOf(scene, rec), 0);
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 3;
        break;
    case 3:
        if ((nodeFrame(nodeOf(scene, rec)) >> 16) >= 3) {
            nodeSetFrame(nodeOf(scene, rec), 3 << 16);
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            rec->state = 0x25;
        }
        break;
    case 0x25:
        selected = workS16(0x76D8);
        if (selected == rec->unkA) {
            if ((nodeFrame(nodeOf(scene, rec)) >> 16) >= 8) {
                nodeSetFrame(nodeOf(scene, rec), 8 << 16);
                nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            } else {
                nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
            }
        } else if ((nodeFrame(nodeOf(scene, rec)) >> 16) <= 3) {
            nodeSetFrame(nodeOf(scene, rec), 3 << 16);
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
        } else {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
        }
        break;
    case 5:
        selected = workS16(0x76D8);
        if (selected == rec->unkA) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        } else {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
        }
        rec->state = 6;
        break;
    case 6:
        selected = workS16(0x76D8);
        if (selected == rec->unkA) {
            if ((nodeFrame(nodeOf(scene, rec)) >> 16) >= 0xB) {
                nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
                rec->state = 7;
            }
        } else if ((nodeFrame(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        if ((nodeFrame(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetFrame(nodeOf(scene, rec), 0);
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 3;
        break;
    case 3:
        if ((nodeFrame(nodeOf(scene, rec)) >> 16) >= 5) {
            rec->state = 0x25;
        }
        break;
    case 0x25:
        if (workS16(0x76DA) == 0) {
            if ((nodeFrame(nodeOf(scene, rec)) >> 16) <= 5) {
                nodeSetFrame(nodeOf(scene, rec), 5 << 16);
                nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            } else {
                nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
            }
        } else if ((nodeFrame(nodeOf(scene, rec)) >> 16) >= 0xA) {
            nodeSetFrame(nodeOf(scene, rec), 0xA << 16);
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
        } else {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        }
        break;
    case 5:
        if (workS16(0x76DA) == 0) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
        } else {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        }
        rec->state = 6;
        break;
    case 6:
        if (workS16(0x76DA) == 0) {
            if ((nodeFrame(nodeOf(scene, rec)) >> 16) == 0) {
                nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
                rec->state = 7;
            }
        } else if ((nodeFrame(nodeOf(scene, rec)) >> 16) >= 0xF) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        REC_S16(rec, 0x12) = 0xFF;
        REC_S16(rec, 0x14) = text_initializeNewChannel((UnkText988Arg *)scene, rec->handle,
                                                       (u16)rec->unk10, 4, 0x312, 0);
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    }
    nodeSetRGBA(nodeOf(scene, rec), (nodeRGBA(nodeOf(scene, rec)) & ~0xFF) | REC_S16(rec, 0x12));
}

// .text:0x00035088 size:0x1B4 mapped:0x8067411C
void fn_2_35088(TextScene *scene, TextHandleRec *rec) {
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
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        if ((nodeFrame(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 1:
    case 3:
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        rec->state = 0x25;
        break;
    case 5:
        nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        REC_S16(rec, 0x12) = 0xFF;
        REC_S16(rec, 0x14) = text_initializeNewChannel((UnkText988Arg *)scene, rec->handle,
                                                       (u16)rec->unk10, 4, 0x306, 0);
        rec->state = 0x26;
        break;
    case 2:
        text_setPtrToWhereCharsAreStored(REC_S16(rec, 0x14), 4, bank8248U8(0x4415) + 0x305);
        nodeShow(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    }
    screenBlockSet2F(REC_S16(rec, 0x14), 1);
    nodeSetRGBA(nodeOf(scene, rec), (nodeRGBA(nodeOf(scene, rec)) & ~0xFF) | REC_S16(rec, 0x12));
}

// .text:0x00034BCC size:0x1A4 mapped:0x80673C60
void fn_2_34BCC(TextScene *scene, TextHandleRec *rec) {
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
        nodeSetFrame(nodeOf(scene, rec), 0);
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
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
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeSetFrame(nodeOf(scene, rec), 0);
        load_Icon(scene, rec->handle, 1, 0xCD, bank8248U8(0x4415) - 1);
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
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
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        if ((nodeFrame(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
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
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        if ((nodeFrame(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
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
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
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
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        if ((nodeFrame(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
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
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        load_Icon(scene, rec->handle, 1, 0x2E,
                 *(s16 *)((u8 *)lbl_2_data_C924 + rec->unkA * 0x18 + workU8(0x785B) * 2));
        break;
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        if ((nodeFrame(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
        break;
    case 0x25:
        break;
    }
}
