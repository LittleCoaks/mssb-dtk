#include "menus/text_33E70.h"
#include "text/text.h"

s16 fn_2_53BC8(void *arg0);
void load_Icon(void *scene, s32 handle, u32 part, u32 element, s32 frame);

extern u8 *lbl_2_bss_1A824C;
extern s16 lbl_2_data_C924[];

// Work area behind lbl_2_bss_1A824C (the 0x190000 window).
#define WORK_BASE() (lbl_2_bss_1A824C + 0x190000)

static inline u8 workU8(s32 off) {
    return *(u8 *)(WORK_BASE() + off);
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

static inline s16 recTimer(TextHandleRec *rec) {
    return *(s16 *)((u8 *)rec + 0x6);
}

static inline void recSetTimer(TextHandleRec *rec, s16 value) {
    *(s16 *)((u8 *)rec + 0x6) = value;
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
        load_Icon(scene, rec->handle, 1, 0x2E, lbl_2_data_C924[rec->unkA * 12 + workU8(0x785B)]);
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
    }
}

// .text:0x00034524 size:0x1B4 mapped:0x806735B8
void fn_2_34524(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x000346D8 size:0x16C mapped:0x8067376C
void fn_2_346D8(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00034844 size:0x1B4 mapped:0x806738D8
void fn_2_34844(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x000349F8 size:0x1D4 mapped:0x80673A8C
void fn_2_349F8(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00034BCC size:0x1A4 mapped:0x80673C60
void fn_2_34BCC(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00034D70 size:0x1FC mapped:0x80673E04
void fn_2_34D70(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00034F6C size:0x11C mapped:0x80674000
void fn_2_34F6C(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00035088 size:0x1B4 mapped:0x8067411C
void fn_2_35088(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x0003523C size:0x1C0 mapped:0x806742D0
void fn_2_3523C(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x000353FC size:0x358 mapped:0x80674490
void fn_2_353FC(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00035754 size:0x10C mapped:0x806747E8
void fn_2_35754(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00035860 size:0x1B4 mapped:0x806748F4
void fn_2_35860(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00035A14 size:0x3A0 mapped:0x80674AA8
void fn_2_35A14(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00035DB4 size:0x10C mapped:0x80674E48
void fn_2_35DB4(TextScene *scene, TextHandleRec *rec) {
    return;
}
