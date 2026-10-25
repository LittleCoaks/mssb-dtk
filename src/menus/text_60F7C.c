#include "menus/text_60F7C.h"
#include "text/text.h"

s16 fn_2_53BC8(void *arg0);
void load_Icon(void *scene, s32 handle, u32 part, u32 element, s32 frame);

extern u8 lbl_2_bss_33FBF0[];

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8244;
extern u8 lbl_800E869C[];
extern u8 g_d_GameSettings[];
s32 fn_8006C100(s16 arg);

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

static inline void nodeSetW5C(TextGraphicsObject *node, u32 value) {
    *(u32 *)((u8 *)node + 0x5C) = value;
}

static inline u32 nodeW5C(TextGraphicsObject *node) {
    return *(u32 *)((u8 *)node + 0x5C);
}

static inline u8 *workBase(void) {
    return lbl_2_bss_1A824C + 0x190000;
}

static inline s16 workS16(s32 off) {
    return *(s16 *)(workBase() + off);
}

static inline s32 workS32(s32 off) {
    return *(s32 *)(workBase() + off);
}

static inline s16 *recTimer(TextHandleRec *rec) {
    return (s16 *)((u8 *)rec + 0x6);
}

// .text:0x00063570 size:0x134 mapped:0x806A2604
void fn_2_63570(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    if (rec->state == 0) {
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
    } else if (rec->state == 2) {
        nodeSetFlag2(nodeOf(scene, rec));
        rec->state = 0x25;
    } else if (rec->state == 5) {
        *recTimer(rec) = 0x1A;
        rec->state = 6;
    } else if (rec->state == 6) {
        s16 timer = *recTimer(rec);
        *recTimer(rec) = timer - 1;
        if (timer <= 0) {
            nodeClearFlag2(nodeOf(scene, rec));
        }
    } else if (rec->state == 0x11) {
        rec->state = 0x25;
    }
}

// .text:0x00062D18 size:0x858 mapped:0x806A1DAC
void fn_2_62D18(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00062A38 size:0x2E0 mapped:0x806A1ACC
void fn_2_62A38(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 1:     case 3:     case 4:     case 8:     case 9:     case 0xA:     case 0xB:     case 0xC:
    case 0xD:     case 0xE:     case 0xF:     case 0x10:     case 0x12:     case 0x13:     case 0x14:     case 0x15:
    case 0x16:     case 0x17:     case 0x18:     case 0x19:     case 0x1A:     case 0x1B:     case 0x1C:     case 0x1D:
    case 0x1E:     case 0x1F:     case 0x20:     case 0x21:     case 0x22:     case 0x23:     case 0x24:     case 0x25:
        break;
    case 2:
    case 0x11: {
        s16 mode = workS16(0x76FA);
        if (mode == 0) {
            s16 value = workS16(0x72F0 + mode * 0x28 + rec->unkA * 8);
            nodeSetW5C(nodeOf(scene, rec), 0);
            nodeSetFlag2(nodeOf(scene, rec));
            nodeSetByte68(nodeOf(scene, rec), 1);
            load_Icon(scene, rec->handle, 3, 6, value % 10);
            load_Icon(scene, rec->handle, 4, 6, (value / 10) % 10);
            load_Icon(scene, rec->handle, 5, 6, (value / 100) % 10);
        } else {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        rec->state = 0x25;
        break;
    }
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

// .text:0x000627F4 size:0x244 mapped:0x806A1888
void fn_2_627F4(TextScene *scene, TextHandleRec *rec) {
    u8 *settings = g_d_GameSettings;
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 1:     case 3:     case 4:     case 8:     case 9:     case 0xA:     case 0xB:     case 0xC:
    case 0xD:     case 0xE:     case 0xF:     case 0x10:     case 0x12:     case 0x13:     case 0x14:     case 0x15:
    case 0x16:     case 0x17:     case 0x18:     case 0x19:     case 0x1A:     case 0x1B:     case 0x1C:     case 0x1D:
    case 0x1E:     case 0x1F:     case 0x20:     case 0x21:     case 0x22:     case 0x23:     case 0x24:     case 0x25:
        break;
    case 2:
    case 0x11:
        if (workS16(0x76FA) == 6) {
            if (settings[0x12] <= 1) {
                nodeClearFlag2(nodeOf(scene, rec));
                rec->state = 0x25;
            } else {
                nodeSetW5C(nodeOf(scene, rec), 0);
                nodeSetFlag2(nodeOf(scene, rec));
                nodeSetByte68(nodeOf(scene, rec), 1);
                rec->state = 0x25;
            }
        } else {
            nodeClearFlag2(nodeOf(scene, rec));
            rec->state = 0x25;
        }
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

// .text:0x000625B0 size:0x244 mapped:0x806A1644
void fn_2_625B0(TextScene *scene, TextHandleRec *rec) {
    u8 *settings = g_d_GameSettings;
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 1:     case 3:     case 4:     case 8:     case 9:     case 0xA:     case 0xB:     case 0xC:
    case 0xD:     case 0xE:     case 0xF:     case 0x10:     case 0x12:     case 0x13:     case 0x14:     case 0x15:
    case 0x16:     case 0x17:     case 0x18:     case 0x19:     case 0x1A:     case 0x1B:     case 0x1C:     case 0x1D:
    case 0x1E:     case 0x1F:     case 0x20:     case 0x21:     case 0x22:     case 0x23:     case 0x24:     case 0x25:
        break;
    case 2:
    case 0x11:
        if (workS16(0x76FA) == 6) {
            if (settings[0x12] <= 1) {
                nodeClearFlag2(nodeOf(scene, rec));
                rec->state = 0x25;
            } else {
                nodeSetW5C(nodeOf(scene, rec), 0);
                nodeSetFlag2(nodeOf(scene, rec));
                nodeSetByte68(nodeOf(scene, rec), 1);
                rec->state = 0x25;
            }
        } else {
            nodeClearFlag2(nodeOf(scene, rec));
            rec->state = 0x25;
        }
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

// .text:0x000623AC size:0x204 mapped:0x806A1440
void fn_2_623AC(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    if (rec->state == 0) {
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
    } else if (rec->state == 2 || rec->state == 0x11) {
        s16 mode = workS16(0x76FA);
        if (mode == 6 && g_d_GameSettings[0x12] > 1) {
            s16 arg = (s16)workS32(0x72EC + mode * 0x28 + rec->unkA * 8);
            nodeSetW5C(nodeOf(scene, rec), (u8)fn_8006C100(arg) << 16);
            nodeSetFlag2(nodeOf(scene, rec));
            rec->state = 0x25;
        } else {
            nodeClearFlag2(nodeOf(scene, rec));
            rec->state = 0x25;
        }
    } else if (rec->state == 5) {
        *recTimer(rec) = 0x1A;
        rec->state = 6;
    } else if (rec->state == 6) {
        s16 timer = *recTimer(rec);
        *recTimer(rec) = timer - 1;
        if (timer <= 0) {
            nodeClearFlag2(nodeOf(scene, rec));
        }
    }
}

// .text:0x00062110 size:0x29C mapped:0x806A11A4
void fn_2_62110(TextScene *scene, TextHandleRec *rec) {
    u8 *settings = g_d_GameSettings;
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeClearFlag2(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 1:     case 3:     case 4:     case 8:     case 9:     case 0xA:     case 0xB:     case 0xC:
    case 0xD:     case 0xE:     case 0xF:     case 0x10:     case 0x12:     case 0x13:     case 0x14:     case 0x15:
    case 0x16:     case 0x17:     case 0x18:     case 0x19:     case 0x1A:     case 0x1B:     case 0x1C:     case 0x1D:
    case 0x1E:     case 0x1F:     case 0x20:     case 0x21:     case 0x22:     case 0x23:     case 0x24:     case 0x25:
        break;
    case 2:
    case 0x11: {
        s16 mode = workS16(0x76FA);
        if ((mode == 5 && settings[0x12] == 0) || (mode == 6 && settings[0x12] <= 1)) {
            nodeSetW5C(nodeOf(scene, rec), 0);
            nodeSetFlag2(nodeOf(scene, rec));
            nodeSetByte68(nodeOf(scene, rec), 1);
        } else {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        rec->state = 0x25;
        break;
    }
    case 5:
        nodeSetW5C(nodeOf(scene, rec), 0xA0000);
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

// .text:0x00061F5C size:0x1B4 mapped:0x806A0FF0
void fn_2_61F5C(TextScene *scene, TextHandleRec *rec) {
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
    case 4:
    case 0x25:
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

// .text:0x00061D90 size:0x1CC mapped:0x806A0E24
void fn_2_61D90(TextScene *scene, TextHandleRec *rec) {
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
    case 4:
    case 0x25:
        break;
    case 2:
        load_Icon(scene, rec->handle, 1, 0x5F, rec->unkA);
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

// .text:0x00061B6C size:0x224 mapped:0x806A0C00
void fn_2_61B6C(TextScene *scene, TextHandleRec *rec) {
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
    case 4:
    case 0x25:
        break;
    case 2:
        if (lbl_2_bss_33FBF0[rec->unkA] == 1) {
            nodeSetFlag2(nodeOf(scene, rec));
            nodeSetByte68(nodeOf(scene, rec), 1);
            rec->state = 0x25;
        } else {
            nodeClearFlag2(nodeOf(scene, rec));
            rec->state = 0x25;
        }
        break;
    case 5:
        if (lbl_2_bss_33FBF0[rec->unkA] == 1) {
            nodeSetByte68(nodeOf(scene, rec), 4);
            rec->state = 6;
        } else {
            rec->state = 7;
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
    }
}

// .text:0x00061948 size:0x224 mapped:0x806A09DC
void fn_2_61948(TextScene *scene, TextHandleRec *rec) {
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
    case 4:
    case 0x25:
        break;
    case 2:
        if (lbl_2_bss_33FBF0[rec->unkA] == 1) {
            nodeClearFlag2(nodeOf(scene, rec));
            rec->state = 0x25;
        } else {
            nodeSetFlag2(nodeOf(scene, rec));
            nodeSetByte68(nodeOf(scene, rec), 1);
            rec->state = 0x25;
        }
        break;
    case 5:
        if (lbl_2_bss_33FBF0[rec->unkA] == 1) {
            rec->state = 7;
        } else {
            nodeSetByte68(nodeOf(scene, rec), 4);
            rec->state = 6;
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
    }
}

// .text:0x00061794 size:0x1B4 mapped:0x806A0828
void fn_2_61794(TextScene *scene, TextHandleRec *rec) {
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
    case 4:
    case 0x25:
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

// .text:0x00061644 size:0x150 mapped:0x806A06D8
void fn_2_61644(TextScene *scene, TextHandleRec *rec) {
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
    case 4:
    case 0x25:
        break;
    case 2:
        nodeSetFlag2(nodeOf(scene, rec));
        rec->state = 0x25;
        break;
    case 5:
        *recTimer(rec) = 0x28;
        rec->state = 6;
        break;
    case 6: {
        s16 timer = *recTimer(rec);
        *recTimer(rec) = timer - 1;
        if (timer <= 0) {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    }
}

// .text:0x00061468 size:0x1DC mapped:0x806A04FC
void fn_2_61468(TextScene *scene, TextHandleRec *rec) {
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
    case 4:
    case 0x25:
        break;
    case 2:
        load_Icon(scene, rec->handle, 1, 0x43, rec->unk10);
        if ((s32)lbl_2_bss_1A8244[lbl_800E869C[rec->unk10]] == 1) {
            nodeSetW5C(nodeOf(scene, rec), 0);
        } else {
            nodeSetW5C(nodeOf(scene, rec), 0x10000);
        }
        nodeSetFlag2(nodeOf(scene, rec));
        rec->state = 0x25;
        break;
    case 5:
        *recTimer(rec) = 0x28;
        rec->state = 6;
        break;
    case 6: {
        s16 timer = *recTimer(rec);
        *recTimer(rec) = timer - 1;
        if (timer <= 0) {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    }
}

// .text:0x000612A8 size:0x1C0 mapped:0x806A033C
void fn_2_612A8(TextScene *scene, TextHandleRec *rec) {
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
    case 4:
    case 0x25:
        break;
    case 2:
        if ((s32)lbl_2_bss_1A8244[lbl_800E869C[rec->unk10]] == 1) {
            nodeSetFlag2(nodeOf(scene, rec));
            nodeSetByte68(nodeOf(scene, rec), 1);
        } else {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        rec->state = 0x25;
        break;
    case 5:
        *recTimer(rec) = 0x28;
        rec->state = 6;
        break;
    case 6: {
        s16 timer = *recTimer(rec);
        *recTimer(rec) = timer - 1;
        if (timer <= 0) {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    }
}

// .text:0x00061104 size:0x1A4 mapped:0x806A0198
void fn_2_61104(TextScene *scene, TextHandleRec *rec) {
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
    case 4:
    case 0x25:
        break;
    case 2:
        if ((s32)lbl_2_bss_1A8244[lbl_800E869C[rec->unk10]] == 1) {
            nodeClearFlag2(nodeOf(scene, rec));
        } else {
            nodeSetFlag2(nodeOf(scene, rec));
        }
        rec->state = 0x25;
        break;
    case 5:
        *recTimer(rec) = 0x28;
        rec->state = 6;
        break;
    case 6: {
        s16 timer = *recTimer(rec);
        *recTimer(rec) = timer - 1;
        if (timer <= 0) {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    }
}

// .text:0x00060F7C size:0x188 mapped:0x806A0010
void fn_2_60F7C(TextScene *scene, TextHandleRec *rec) {
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
    case 4:
    case 0x25:
        break;
    case 2:
        nodeSetW5C(nodeOf(scene, rec), 0);
        nodeSetFlag2(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 5:
        *recTimer(rec) = 0xA;
        rec->state = 6;
        break;
    case 6: {
        s16 timer = *recTimer(rec);
        *recTimer(rec) = timer - 1;
        if (timer <= 0) {
            nodeClearFlag2(nodeOf(scene, rec));
        }
        break;
    }
    }
}
