#include "menus/text_636A4.h"
#include "text/text.h"

// Local prototypes for symbols owned by other units.
s16 fn_2_53BC8(void *arg0);
void load_Icon(void *scene, s32 handle, u32 part, u32 element, s32 frame);

extern u8 lbl_800E869C[];
extern u8 lbl_80354768[];

static void clearRecFlag2(TextScene *scene, TextHandleRec *rec) {
    graphicsRelatedArray[scene->firstHandle + rec->handle].object->flags &= ~2;
}

static void setRecFlag2(TextScene *scene, TextHandleRec *rec) {
    graphicsRelatedArray[scene->firstHandle + rec->handle].object->flags |= 2;
}

static void setRecObjectField5C(TextScene *scene, TextHandleRec *rec, u32 value) {
    GraphicsArrayEntry *entry = &graphicsRelatedArray[scene->firstHandle + rec->handle];

    *(u32 *)((u8 *)entry->object + 0x5C) = value;
}

static void setRecObject68(TextScene *scene, TextHandleRec *rec, u8 value) {
    GraphicsArrayEntry *entry = &graphicsRelatedArray[scene->firstHandle + rec->handle];

    *(u8 *)((u8 *)entry->object + 0x68) = value;
}

static void tickRecTimer(TextScene *scene, TextHandleRec *rec) {
    s16 *timer = (s16 *)((u8 *)rec + 0x6);
    s16 prev = *timer;

    *timer = prev - 1;
    if (prev <= 0) {
        clearRecFlag2(scene, rec);
    }
}

static void stepRecObjLevelState(TextScene *scene, TextHandleRec *rec) {
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
        setRecObjectField5C(scene, rec, 0);
        setRecFlag2(scene, rec);
        setRecObject68(scene, rec, 1);
        rec->state = 0x25;
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
    case 0x25:
        break;
    }
}

// .text:0x000636A4 size:0x1D0 mapped:0x806A2738
void fn_2_636A4(TextScene *scene, TextHandleRec *rec) {
    stepRecObjLevelState(scene, rec);
}

// .text:0x00063874 size:0x1F0 mapped:0x806A2908
void fn_2_63874(TextScene *scene, TextHandleRec *rec) {
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
        setRecObjectField5C(scene, rec, 0);
        load_Icon(scene, rec->handle, 1, 0x12, rec->unkA);
        setRecFlag2(scene, rec);
        setRecObject68(scene, rec, 1);
        rec->state = 0x25;
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
    case 0x25:
        break;
    }
}

// .text:0x00063A64 size:0x188 mapped:0x806A2AF8
void fn_2_63A64(TextScene *scene, TextHandleRec *rec) {
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
        setRecObjectField5C(scene, rec, 0);
        setRecFlag2(scene, rec);
        setRecObject68(scene, rec, 1);
        rec->state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)rec + 0x6) = 0x19;
        rec->state = 6;
        break;
    case 6:
        tickRecTimer(scene, rec);
        break;
    case 0x25:
        break;
    }
}

// .text:0x00063BEC size:0x1D0 mapped:0x806A2C80
void fn_2_63BEC(TextScene *scene, TextHandleRec *rec) {
    stepRecObjLevelState(scene, rec);
}

// .text:0x00063DBC size:0x19C mapped:0x806A2E50
void fn_2_63DBC(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s16 *timer;
    s16 prev;

    if (result != -1) {
        rec->state = result;
    }
    if (rec->state == 0) {
        clearRecFlag2(scene, rec);
        rec->state = 0x26;
    } else if (rec->state == 2) {
        setRecObjectField5C(scene, rec, 0);
        setRecFlag2(scene, rec);
        setRecObject68(scene, rec, 1);
        rec->state = 0x25;
    } else if (rec->state == 0x11) {
        rec->state = 0x25;
    } else if (rec->state == 5) {
        *(s16 *)((u8 *)rec + 0x6) = 0x1A;
        rec->state = 6;
    } else if (rec->state == 6) {
        timer = (s16 *)((u8 *)rec + 0x6);
        prev = *timer;
        *timer = prev - 1;
        if (prev <= 0) {
            setRecObject68(scene, rec, 0);
            rec->state = 7;
        }
    } else if (rec->state == 7) {
        clearRecFlag2(scene, rec);
    }
}

// .text:0x000642F8 size:0x234 mapped:0x806A338C
void fn_2_642F8(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x000648CC size:0x384 mapped:0x806A3960
void fn_2_648CC(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00064E20 size:0x284 mapped:0x806A3EB4
void fn_2_64E20(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x000653D4 size:0x274 mapped:0x806A4468
void fn_2_653D4(TextScene *scene, TextHandleRec *rec) {
    return;
}

// .text:0x00065A00 size:0x284 mapped:0x806A4A94
void fn_2_65A00(TextScene *scene, TextHandleRec *rec) {
    return;
}

// Case 2 sets flag 2 before zeroing the level word.
static void stepRecLevelObjStateFlagFirst(TextScene *scene, TextHandleRec *rec) {
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
        setRecObjectField5C(scene, rec, 0);
        setRecObject68(scene, rec, 1);
        rec->state = 0x25;
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
    case 0x25:
        break;
    }
}

// Like stepRecLevelObjState but case 2 leaves the level word alone.
static void stepRecObjState(TextScene *scene, TextHandleRec *rec) {
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
        setRecObject68(scene, rec, 1);
        rec->state = 0x25;
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
    case 0x25:
        break;
    }
}

// Flag-only record: case 5 clears the object's +0x68 byte, case 6 clears flag 2 and moves to 7.
static void stepRecFlagOnlyState(TextScene *scene, TextHandleRec *rec) {
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
        setRecObject68(scene, rec, 1);
        rec->state = 0x25;
        break;
    case 5:
        setRecObject68(scene, rec, 0);
        rec->state = 6;
        break;
    case 6:
        clearRecFlag2(scene, rec);
        rec->state = 7;
        break;
    case 0x25:
        break;
    }
}

// .text:0x00063F58 size:0x1D0 mapped:0x806A2FEC
void fn_2_63F58(TextScene *scene, TextHandleRec *rec) {
    stepRecObjLevelState(scene, rec);
}

// .text:0x00064128 size:0x1D0 mapped:0x806A31BC
void fn_2_64128(TextScene *scene, TextHandleRec *rec) {
    stepRecObjLevelState(scene, rec);
}

// .text:0x0006452C size:0x1D0 mapped:0x806A35C0
void fn_2_6452C(TextScene *scene, TextHandleRec *rec) {
    stepRecLevelObjStateFlagFirst(scene, rec);
}

// .text:0x000646FC size:0x1D0 mapped:0x806A3790
void fn_2_646FC(TextScene *scene, TextHandleRec *rec) {
    stepRecLevelObjStateFlagFirst(scene, rec);
}

// .text:0x00064C50 size:0x1D0 mapped:0x806A3CE4
void fn_2_64C50(TextScene *scene, TextHandleRec *rec) {
    stepRecObjLevelState(scene, rec);
}

// .text:0x000650A4 size:0x1B4 mapped:0x806A4138
void fn_2_650A4(TextScene *scene, TextHandleRec *rec) {
    stepRecObjState(scene, rec);
}

// .text:0x00065258 size:0x17C mapped:0x806A42EC
void fn_2_65258(TextScene *scene, TextHandleRec *rec) {
    stepRecFlagOnlyState(scene, rec);
}

// .text:0x00065850 size:0x1B0 mapped:0x806A48E4
void fn_2_65850(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    u8 *table = lbl_80354768;
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
        if (table[0xCF18 + lbl_800E869C[rec->unk10]] == 0) {
            setRecFlag2(scene, rec);
        } else {
            clearRecFlag2(scene, rec);
        }
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

// .text:0x00065C84 size:0x1CC mapped:0x806A4D18
void fn_2_65C84(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    u8 *table = lbl_80354768;
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
        if (table[0xCF18 + lbl_800E869C[rec->unk10]] == 1) {
            setRecFlag2(scene, rec);
            setRecObjectField5C(scene, rec, 0x30000);
        } else {
            clearRecFlag2(scene, rec);
        }
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

// .text:0x00065648 size:0x208 mapped:0x806A46DC
void fn_2_65648(TextScene *scene, TextHandleRec *rec) {
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
        setRecObject68(scene, rec, 1);
        rec->state = 0x25;
        break;
    case 5:
        setRecObjectField5C(scene, rec, 0xC0000);
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
    case 0x25:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) >= 0x78) {
            *(u32 *)((u8 *)obj + 0x5C) = 0xD0000;
        }
        break;
    }
}
