#include "menus/text_65E50.h"
#include "text/text.h"

// Local prototypes for symbols owned by other units.
s16 fn_2_53BC8(void *arg0);
s32 fn_80062890(s32 arg);
void load_Icon(void *scene, s32 handle, u32 part, u32 element, s32 frame);

extern u8 *lbl_2_bss_1A8240;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 hugeAnimStruct[];
extern u8 lbl_800E869C[];
extern u8 lbl_80354768[];
extern s16 lbl_2_data_2E80[];

static void clearRecFlag2(TextScene *scene, TextHandleRec *rec) {
    graphicsRelatedArray[scene->firstHandle + rec->handle].object->flags &= ~2;
}

static void setRecFlag2(TextScene *scene, TextHandleRec *rec) {
    graphicsRelatedArray[scene->firstHandle + rec->handle].object->flags |= 2;
}

// Shared state machine body for the record handlers that also touch the
// object's byte at +0x68.
static void stepRecObjectState(TextScene *scene, TextHandleRec *rec) {
    TextGraphicsObject *obj;
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        setRecFlag2(scene, rec);
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        *(u8 *)((u8 *)obj + 0x68) = 1;
        rec->state = 0x25;
        break;
    case 5:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        *(u8 *)((u8 *)obj + 0x68) = 4;
        rec->state = 6;
        break;
    case 6:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *(u8 *)((u8 *)obj + 0x68) = 0;
            rec->state = 7;
        }
        break;
    case 7:
        clearRecFlag2(scene, rec);
        break;
    case 0x25:
        break;
    }
}

static void startRecTimer(TextHandleRec *rec) {
    *(s16 *)((u8 *)rec + 0x6) = 0x28;
    rec->state = 6;
}

static void tickRecTimer(TextScene *scene, TextHandleRec *rec) {
    s16 *timer = (s16 *)((u8 *)rec + 0x6);
    s16 prev = *timer;

    *timer = prev - 1;
    if (prev <= 0) {
        clearRecFlag2(scene, rec);
    }
}

static void setRecObjectField5C(TextScene *scene, TextHandleRec *rec, u32 value) {
    GraphicsArrayEntry *entry = &graphicsRelatedArray[scene->firstHandle + rec->handle];

    *(u32 *)((u8 *)entry->object + 0x5C) = value;
}

static void setRecObject68(TextScene *scene, TextHandleRec *rec, u8 value) {
    GraphicsArrayEntry *entry = &graphicsRelatedArray[scene->firstHandle + rec->handle];

    *(u8 *)((u8 *)entry->object + 0x68) = value;
}

// Flag 2 and the object's +0x68 byte both follow whether the work-area
// s16 at +0x197706 matches this record's unk10.
static void syncRecFlag2(TextScene *scene, TextHandleRec *rec) {
    if (*(s16 *)(lbl_2_bss_1A824C + 0x197706) == rec->unk10) {
        setRecFlag2(scene, rec);
        setRecObject68(scene, rec, 1);
    } else {
        clearRecFlag2(scene, rec);
        setRecObject68(scene, rec, 0);
    }
}

// Level byte for this record's object follows the work-area s16 at +0x1976FE.
static void syncRecLevel(TextScene *scene, TextHandleRec *rec) {
    TextGraphicsObject *obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
    u32 level = *(u32 *)((u8 *)obj + 0x5C) >> 16;

    if (*(s16 *)(lbl_2_bss_1A824C + 0x1976FE) == rec->unkA) {
        if (level < 5) {
            setRecObject68(scene, rec, 1);
        } else {
            *(u32 *)((u8 *)obj + 0x5C) = 0x50000;
            setRecObject68(scene, rec, 0);
        }
    } else {
        if (level != 0) {
            setRecObject68(scene, rec, 4);
        } else {
            *(u32 *)((u8 *)obj + 0x5C) = 0;
            setRecObject68(scene, rec, 0);
        }
    }
}

// Flag 2 follows whether the work-area s16 at +0x197730 is 2 or 5.
static void syncRecFlag2ByWork(TextScene *scene, TextHandleRec *rec) {
    s16 work = *(s16 *)(lbl_2_bss_1A824C + 0x197730);

    if (work == 2 || work == 5) {
        setRecFlag2(scene, rec);
    } else {
        clearRecFlag2(scene, rec);
    }
}

// State machine shared by fn_2_67390 and fn_2_67588.
static void stepRecWorkState(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s16 *timer;
    s16 prev;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        syncRecFlag2ByWork(scene, rec);
        setRecObject68(scene, rec, 1);
        rec->state = 0x25;
        break;
    case 8:
    case 30:
    case 33:
        *(s16 *)((u8 *)rec + 0x6) = 1;
        rec->state++;
        break;
    case 9:
    case 31:
    case 34:
        timer = (s16 *)((u8 *)rec + 0x6);
        prev = *timer;
        *timer = prev - 1;
        if (prev <= 0) {
            syncRecFlag2ByWork(scene, rec);
            rec->state = 0x25;
        }
        break;
    case 0x25:
        break;
    }

}

static void loadIconFromWork(TextScene *scene, TextHandleRec *rec) {
    s16 work = *(s16 *)(lbl_2_bss_1A824C + 0x197730);

    load_Icon(scene, rec->handle, 1, 0x41, work);
}

// Upper halfword of the object's +0x5C word (the level).
static u32 recObjectLevel(TextScene *scene, TextHandleRec *rec) {
    GraphicsArrayEntry *entry = &graphicsRelatedArray[scene->firstHandle + rec->handle];

    return *(u32 *)((u8 *)entry->object + 0x5C) >> 16;
}

// Shared state machine body for the record handlers that toggle flag 2.
static void stepRecFlag2State(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s16 *timer;
    s16 prev;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        setRecFlag2(scene, rec);
        rec->state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)rec + 0x6) = 0x28;
        rec->state = 6;
        break;
    case 6:
        timer = (s16 *)((u8 *)rec + 0x6);
        prev = *timer;
        *timer = prev - 1;
        if (prev <= 0) {
            clearRecFlag2(scene, rec);
        }
        break;
    case 0x25:
        break;
    }

}

// .text:0x00065E50 size:0x1E8 mapped:0x806A4EE4
void fn_2_65E50(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    TextGraphicsObject *obj;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        load_Icon(scene, rec->handle, 1, 0x43, rec->unk10);
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if (lbl_80354768[0xCF18 + lbl_800E869C[rec->unk10]] == 1) {
            *(u32 *)((u8 *)obj + 0x5C) = 0;
        } else {
            *(u32 *)((u8 *)obj + 0x5C) = 0x10000;
        }
        setRecFlag2(scene, rec);
        rec->state = 0x25;
        break;
    case 5:
        startRecTimer(rec);
        break;
    case 6:
        tickRecTimer(scene, rec);
        break;
    case 0x25:
        break;
    }

}

// .text:0x00066038 size:0x150 mapped:0x806A50CC
void fn_2_66038(TextScene *scene, TextHandleRec *rec) {
    stepRecFlag2State(scene, rec);
}

// .text:0x00066188 size:0x1B4 mapped:0x806A521C
void fn_2_66188(TextScene *scene, TextHandleRec *rec) {
    stepRecObjectState(scene, rec);
}

// .text:0x0006633C size:0x284 mapped:0x806A53D0
void fn_2_6633C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        syncRecFlag2(scene, rec);
        rec->state = 0x25;
        break;
    case 5:
        startRecTimer(rec);
        break;
    case 0x25:
        syncRecFlag2(scene, rec);
        break;
    case 6:
        tickRecTimer(scene, rec);
        break;
    }
}

// .text:0x000665C0 size:0x19C mapped:0x806A5654
void fn_2_665C0(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        if (lbl_2_bss_1A8240[rec->unk10 + 0x400] == 3) {
            clearRecFlag2(scene, rec);
        } else {
            setRecFlag2(scene, rec);
        }
        rec->state = 0x25;
        break;
    case 5:
        startRecTimer(rec);
        break;
    case 6:
        tickRecTimer(scene, rec);
        break;
    case 0x25:
        break;
    }

}

// .text:0x0006675C size:0x128 mapped:0x806A57F0
void fn_2_6675C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s16 *timer;
    s16 prev;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        rec->state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)rec + 0x6) = 0x28;
        rec->state = 6;
        break;
    case 6:
        timer = (s16 *)((u8 *)rec + 0x6);
        prev = *timer;
        *timer = prev - 1;
        if (prev <= 0) {
            clearRecFlag2(scene, rec);
        }
        break;
    case 0x25:
        break;
    }

}

// .text:0x00066884 size:0x268 mapped:0x806A5918
void fn_2_66884(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s8 kind;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        kind = lbl_2_bss_1A8240[rec->unk10 + 0x400];
        switch (kind) {
        case 0:
            clearRecFlag2(scene, rec);
            break;
        case 1:
            setRecFlag2(scene, rec);
            setRecObjectField5C(scene, rec, 0x20000);
            break;
        case 2:
            setRecFlag2(scene, rec);
            setRecObjectField5C(scene, rec, 0x10000);
            break;
        case 3:
            setRecFlag2(scene, rec);
            setRecObjectField5C(scene, rec, 0);
            break;
        }
        rec->state = 0x25;
        break;
    case 5:
        startRecTimer(rec);
        break;
    case 6:
        tickRecTimer(scene, rec);
        break;
    case 0x25:
        break;
    }

}

// .text:0x00066AEC size:0x1D8 mapped:0x806A5B80
void fn_2_66AEC(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    GraphicsArrayEntry *entry;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        load_Icon(scene, rec->handle, 1, 0x43, rec->unk10);
        entry = &graphicsRelatedArray[scene->firstHandle + rec->handle];
        if (lbl_2_bss_1A8240[rec->unk10 * 0x16 + 0x153] > 0) {
            *(u32 *)((u8 *)entry->object + 0x5C) = 0;
        } else {
            *(u32 *)((u8 *)entry->object + 0x5C) = 0x10000;
        }
        setRecFlag2(scene, rec);
        rec->state = 0x25;
        break;
    case 5:
        startRecTimer(rec);
        break;
    case 6:
        tickRecTimer(scene, rec);
        break;
    case 0x25:
        break;
    }

}

// .text:0x00066CC4 size:0x150 mapped:0x806A5D58
void fn_2_66CC4(TextScene *scene, TextHandleRec *rec) {
    stepRecFlag2State(scene, rec);
}

// .text:0x00066E14 size:0x1B4 mapped:0x806A5EA8
void fn_2_66E14(TextScene *scene, TextHandleRec *rec) {
    stepRecObjectState(scene, rec);
}

// .text:0x00066FC8 size:0x214 mapped:0x806A605C
void fn_2_66FC8(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    TextGraphicsObject *obj;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        load_Icon(scene, rec->handle, 2, 0x3A, rec->unkA);
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        setRecFlag2(scene, rec);
        *(u32 *)((u8 *)obj + 0x5C) = 0;
        rec->state = 0x25;
        break;
    case 1:
    case 5:
        break;
    case 0x25:
        syncRecLevel(scene, rec);
        load_Icon(scene, rec->handle, 2, 0x3A, rec->unkA);
        break;
    }
}

// .text:0x000671DC size:0x1B4 mapped:0x806A6270
void fn_2_671DC(TextScene *scene, TextHandleRec *rec) {
    stepRecObjectState(scene, rec);
}

// .text:0x00067390 size:0x1F8 mapped:0x806A6424
void fn_2_67390(TextScene *scene, TextHandleRec *rec) {
    stepRecWorkState(scene, rec);
}

// .text:0x00067588 size:0x1F8 mapped:0x806A661C
void fn_2_67588(TextScene *scene, TextHandleRec *rec) {
    stepRecWorkState(scene, rec);
}

// .text:0x00067780 size:0x414 mapped:0x806A6814
void fn_2_67780(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        setRecFlag2(scene, rec);
        setRecObjectField5C(scene, rec, 0x50000);
        loadIconFromWork(scene, rec);
        rec->state = 0x25;
        break;
    case 30:
        setRecObjectField5C(scene, rec, 0x50000);
        setRecObject68(scene, rec, 4);
        rec->state = 0x1F;
        break;
    case 31:
        if (recObjectLevel(scene, rec) == 0) {
            loadIconFromWork(scene, rec);
            setRecObjectField5C(scene, rec, 0xA0000);
            setRecObject68(scene, rec, 4);
            rec->state = 0x20;
        }
        break;
    case 32:
        if (recObjectLevel(scene, rec) <= 5) {
            setRecObjectField5C(scene, rec, 0x50000);
            setRecObject68(scene, rec, 0);
            rec->state = 0x26;
        }
        break;
    case 33:
        setRecObjectField5C(scene, rec, 0x50000);
        setRecObject68(scene, rec, 1);
        rec->state = 0x22;
        break;
    case 34:
        if (recObjectLevel(scene, rec) >= 0xA) {
            loadIconFromWork(scene, rec);
            setRecObjectField5C(scene, rec, 0);
            setRecObject68(scene, rec, 1);
            rec->state = 0x23;
        }
        break;
    case 35:
        if (recObjectLevel(scene, rec) >= 5) {
            setRecObjectField5C(scene, rec, 0x50000);
            setRecObject68(scene, rec, 0);
            rec->state = 0x26;
        }
        break;
    case 8:
        loadIconFromWork(scene, rec);
        setRecObjectField5C(scene, rec, 0x50000);
        rec->state = 0x26;
        break;
    case 5:
        setRecObjectField5C(scene, rec, 0x50000);
        break;
    case 0x25:
        break;
    }

}

// .text:0x00067B94 size:0x1B4 mapped:0x806A6C28
void fn_2_67B94(TextScene *scene, TextHandleRec *rec) {
    stepRecObjectState(scene, rec);
}

// .text:0x00067D48 size:0x2A4 mapped:0x806A6DDC
void fn_2_67D48(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    TextGraphicsObject *obj;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        setRecFlag2(scene, rec);
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        *(u32 *)((u8 *)obj + 0x5C) = 0;
        rec->state = 0x25;
        break;
    case 0x25:
        syncRecLevel(scene, rec);
        break;
    case 5:
        setRecObject68(scene, rec, 4);
        rec->state = 6;
        break;
    case 6:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            setRecObject68(scene, rec, 0);
            rec->state = 7;
        }
        break;
    case 7:
        clearRecFlag2(scene, rec);
        break;
    }
    load_Icon(scene, rec->handle, 2, 0x3A, rec->unkA);
}

// .text:0x00067FEC size:0x1B4 mapped:0x806A7080
void fn_2_67FEC(TextScene *scene, TextHandleRec *rec) {
    stepRecObjectState(scene, rec);
}

// .text:0x000681A0 size:0x94 mapped:0x806A7234
void fn_2_681A0(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        rec->state = 0x26;
        break;
    case 1:
    case 3:
    case 5:
        break;
    case 2:
        rec->state = 0x25;
        break;
    case 0x25:
        break;
    }

}

// .text:0x00068234 size:0x2C mapped:0x806A72C8
void fn_2_68234(TextScene *scene, TextHandleRec *rec) {
    clearRecFlag2(scene, rec);
}

// .text:0x00068260 size:0xA8 mapped:0x806A72F4
void fn_2_68260(u8 *obj) {
    s16 *row;
    s32 dx;
    s32 dy;
    u8 idx;
    u8 *huge;
    s16 v;

    idx = lbl_2_bss_1A8248[0x441C];
    row = &lbl_2_data_2E80[idx * 3];
    dx = row[0] * 2 - row[2] * 2;
    dy = row[0] * 2 - row[1] * 2;

    if (*(s32 *)(obj + 0x80) == 0) {
        huge = hugeAnimStruct + 0xC04;
        if (huge != NULL) {
            v = *(s16 *)(huge + 0x68);
            if (v == dx || v == dy) {
                if (idx == 5) {
                    fn_80062890(1);
                } else {
                    fn_80062890(0);
                }
            }
        }
    }
}

// .text:0x00068308 size:0x24 mapped:0x806A739C
void fn_2_68308(void) {
    lbl_2_bss_1A8248[0x17AB] = 0;
    *(s16 *)(lbl_2_bss_1A8248 + 0x177C) = 0;
    lbl_2_bss_1A8248[0x442F] = 0;
}
