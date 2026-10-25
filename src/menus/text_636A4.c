#define SQRT2_LINKAGE static
#include "menus/text_636A4.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#include "static/UnknownHomes_Static.h"

typedef struct TextFadeRecord {
    TextHandleRec base;
    s16 fade;
    s16 channel;
} TextFadeRecord;

// Local prototypes for symbols owned by other units.
s16 fn_2_53BC8(void *arg0);
void load_Icon(void *scene, s32 handle, u32 part, u32 element, s32 frame);

extern u8 lbl_800E869C[];
extern u8 lbl_80354768[];
extern u8 *lbl_2_bss_1A824C;
extern s16 lbl_2_data_20C38[];
extern s16 lbl_2_data_20C58[];

static void hideRec(TextScene *scene, TextHandleRec *rec) {
    graphicsRelatedArray[scene->firstHandle + rec->handle].object->flags &= ~UI_FLAG_VISIBLE;
}

static void showRec(TextScene *scene, TextHandleRec *rec) {
    graphicsRelatedArray[scene->firstHandle + rec->handle].object->flags |= UI_FLAG_VISIBLE;
}

static void setRecFrame(TextScene *scene, TextHandleRec *rec, u32 value) {
    GraphicsArrayEntry *entry = &graphicsRelatedArray[scene->firstHandle + rec->handle];

    ((UIRecord *)entry->object)->frame = value;
}

static void setRecPlayMode(TextScene *scene, TextHandleRec *rec, u8 value) {
    GraphicsArrayEntry *entry = &graphicsRelatedArray[scene->firstHandle + rec->handle];

    ((UIRecord *)entry->object)->playMode = value;
}

static void tickRecTimer(TextScene *scene, TextHandleRec *rec) {
    s16 *timer = (s16 *)((u8 *)rec + 0x6);
    s16 prev = *timer;

    *timer = prev - 1;
    if (prev <= 0) {
        hideRec(scene, rec);
    }
}

// Level word source for the records that index the work area by unkA/unkC.
static s16 recLevelFromWork(TextHandleRec *rec) {
    s16 mode;
    s16 kind;

    if (*(s16 *)((u8 *)rec + 0xC) == 6) {
        return *(s16 *)&lbl_2_bss_1A824C[0x190000 + rec->unkA * 8 + 0x72CA];
    }
    mode = *(s16 *)(lbl_2_bss_1A824C + 0x1976FA);
    kind = rec->unkA;
    return *(s16 *)&lbl_2_bss_1A824C[0x190000 + mode * 0x28 + kind * 8 + 0x72F2];
}

// Shared body for case 2 and case 0x11 of fn_2_648CC.
static void stepRecSettingsLevel(TextScene *scene, TextHandleRec *rec) {
    s16 mode;

    if (*(s16 *)((u8 *)rec + 0xC) == 6) {
        setRecFrame(scene, rec, 0x60000);
    } else {
        mode = *(s16 *)(lbl_2_bss_1A824C + 0x1976FA);
        if (mode == 5 && g_d_GameSettings._12 == 0) {
            hideRec(scene, rec);
            rec->state = 0x25;
            return;
        }
        if (mode == 6 && g_d_GameSettings._12 <= 1) {
            hideRec(scene, rec);
            rec->state = 0x25;
            return;
        }
        setRecFrame(scene, rec, (u32)lbl_2_data_20C38[mode] << 16);
    }
    showRec(scene, rec);
    rec->state = 0x25;
}

// Reset playback after making the record visible.
static void stepRecLevelObjStateFlagFirst(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    TextGraphicsObject *obj;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        showRec(scene, rec);
        setRecFrame(scene, rec, 0);
        setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 5:
        setRecPlayMode(scene, rec, UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            setRecPlayMode(scene, rec, UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        hideRec(scene, rec);
        break;
    case 0x25:
        break;
    }
}

// Start playback from the record's existing frame.
static void stepRecObjState(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    TextGraphicsObject *obj;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        showRec(scene, rec);
        setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 5:
        setRecPlayMode(scene, rec, UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            setRecPlayMode(scene, rec, UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        hideRec(scene, rec);
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
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        showRec(scene, rec);
        setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 5:
        setRecPlayMode(scene, rec, UI_PLAY_STOP);
        rec->state = 6;
        break;
    case 6:
        hideRec(scene, rec);
        rec->state = 7;
        break;
    case 0x25:
        break;
    }
}

// Flag 2 and the object's +0x68 byte follow whether the work-area s16 at +0x197706 matches unk10.
static void syncRecFlag2(TextScene *scene, TextHandleRec *rec) {
    if (*(s16 *)(lbl_2_bss_1A824C + 0x197706) == rec->unk10) {
        showRec(scene, rec);
        setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
    } else {
        hideRec(scene, rec);
        setRecPlayMode(scene, rec, UI_PLAY_STOP);
    }
}

// Level-word body shared by fn_2_636A4, fn_2_63BEC, fn_2_63F58, fn_2_64128 and fn_2_64C50.
static void stepRecObjLevelState(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    TextGraphicsObject *obj;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        setRecFrame(scene, rec, 0);
        showRec(scene, rec);
        setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 5:
        setRecPlayMode(scene, rec, UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            setRecPlayMode(scene, rec, UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        hideRec(scene, rec);
        break;
    case 0x25:
        break;
    }
}

// .text:0x00065C84 size:0x1CC mapped:0x806A4D18
void fn_2_65C84(TextScene *scene, TextHandleRec *rec) {
    u8 *table = lbl_80354768;
    s16 result = fn_2_53BC8(rec);
    s16 *timer;
    s16 prev;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        if (table[0xCF18 + lbl_800E869C[rec->unk10]] == 1) {
            showRec(scene, rec);
            setRecFrame(scene, rec, 0x30000);
        } else {
            hideRec(scene, rec);
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
            hideRec(scene, rec);
        }
        break;
    case 0x25:
        break;
    }
}

// .text:0x00065A00 size:0x284 mapped:0x806A4A94
void fn_2_65A00(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s16 *timer;
    s16 prev;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        syncRecFlag2(scene, rec);
        rec->state = 0x25;
        break;
    case 0x25:
        syncRecFlag2(scene, rec);
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
            hideRec(scene, rec);
        }
        break;
    }
}

// .text:0x00065850 size:0x1B0 mapped:0x806A48E4
void fn_2_65850(TextScene *scene, TextHandleRec *rec) {
    u8 *table = lbl_80354768;
    s16 result = fn_2_53BC8(rec);
    s16 *timer;
    s16 prev;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        if (table[0xCF18 + lbl_800E869C[rec->unk10]] == 0) {
            showRec(scene, rec);
        } else {
            hideRec(scene, rec);
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
            hideRec(scene, rec);
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
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        showRec(scene, rec);
        setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 0x25:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if ((((UIRecord *)obj)->frame >> 16) >= 0x78) {
            ((UIRecord *)obj)->frame = 0xD0000;
        }
        break;
    case 5:
        setRecFrame(scene, rec, 0xC0000);
        setRecPlayMode(scene, rec, UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            setRecPlayMode(scene, rec, UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        hideRec(scene, rec);
        break;
    }
}

// .text:0x000653D4 size:0x274 mapped:0x806A4468
void fn_2_653D4(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    TextGraphicsObject *obj;
    TextFadeRecord *fadeRecord = (TextFadeRecord *)rec;
    s16 *timer;
    s16 prev;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        fadeRecord->fade = 0;
        fadeRecord->channel = text_initializeNewChannel((UnkText988Arg *)scene, rec->handle, rec->unk10, 2, 0x217, 0);
        rec->state = 0x26;
        break;
    case 2:
        text_setPtrToWhereCharsAreStored(fadeRecord->channel, 2,
                                         *(s16 *)(lbl_2_bss_1A824C + 0x197706) + 0x217);
        *(s16 *)((u8 *)rec + 0x6) = 8;
        rec->state = 3;
        break;
    case 3:
        timer = (s16 *)((u8 *)rec + 0x6);
        prev = *timer;
        *timer = prev - 1;
        if (prev <= 0) {
            showRec(scene, rec);
            rec->state = 4;
        }
        break;
    case 4:
        fadeRecord->fade += (0xFF - fadeRecord->fade) / 4;
        fadeRecord->fade++;
        if (fadeRecord->fade > 0xFF) {
            fadeRecord->fade = 0xFF;
        }
        if (fadeRecord->fade >= 0xFF) {
            rec->state = 0x25;
        }
        break;
    case 0x25:
        rec->state = 0x25;
        break;
    case 5:
        hideRec(scene, rec);
        rec->state = 6;
        break;
    case 6:
        fadeRecord->fade += (-fadeRecord->fade) / 4;
        fadeRecord->fade--;
        if (fadeRecord->fade < 0) {
            fadeRecord->fade = 0;
        }
        break;
    }

    obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
    ((UIRecord *)obj)->rgba = (((UIRecord *)obj)->rgba & ~0xFF) | (u32)fadeRecord->fade;
}

// .text:0x00065258 size:0x17C mapped:0x806A42EC
void fn_2_65258(TextScene *scene, TextHandleRec *rec) {
    stepRecFlagOnlyState(scene, rec);
}

// .text:0x000650A4 size:0x1B4 mapped:0x806A4138
void fn_2_650A4(TextScene *scene, TextHandleRec *rec) {
    stepRecObjState(scene, rec);
}

// .text:0x00064E20 size:0x284 mapped:0x806A3EB4
void fn_2_64E20(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    TextGraphicsObject *obj;
    s16 kind;
    s16 frame;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        kind = rec->unkA;
        frame = lbl_2_data_20C58[kind];
        if (kind == 5 && g_d_GameSettings._12 == 0) {
            frame = 7;
        } else if (kind == 6 && g_d_GameSettings._12 <= 1) {
            frame = 7;
        }
        load_Icon(scene, rec->handle, 1, 0x1D, frame);
        showRec(scene, rec);
        if (*(s16 *)(lbl_2_bss_1A824C + 0x1976FA) == kind) {
            setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
        }
        rec->state = 0x25;
        break;
    case 0x11:
        if (*(s16 *)(lbl_2_bss_1A824C + 0x1976FA) == rec->unkA) {
            setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
        } else {
            setRecPlayMode(scene, rec, UI_PLAY_BACKWARD);
        }
        break;
    case 5:
        setRecPlayMode(scene, rec, UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            setRecPlayMode(scene, rec, UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        hideRec(scene, rec);
        break;
    case 0x25:
        break;
    }
}

// .text:0x00064C50 size:0x1D0 mapped:0x806A3CE4
void fn_2_64C50(TextScene *scene, TextHandleRec *rec) {
    stepRecObjLevelState(scene, rec);
}

// .text:0x000648CC size:0x384 mapped:0x806A3960
void fn_2_648CC(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s16 *timer;
    s16 prev;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
    case 0x11:
        stepRecSettingsLevel(scene, rec);
        break;
    case 5:
        *(s16 *)((u8 *)rec + 0x6) = 0x1A;
        rec->state = 6;
        break;
    case 6:
        timer = (s16 *)((u8 *)rec + 0x6);
        prev = *timer;
        *timer = prev - 1;
        if (prev <= 0) {
            hideRec(scene, rec);
        }
        break;
    case 0x25:
        break;
    }
}

// .text:0x000646FC size:0x1D0 mapped:0x806A3790
void fn_2_646FC(TextScene *scene, TextHandleRec *rec) {
    stepRecLevelObjStateFlagFirst(scene, rec);
}

// .text:0x0006452C size:0x1D0 mapped:0x806A35C0
void fn_2_6452C(TextScene *scene, TextHandleRec *rec) {
    stepRecLevelObjStateFlagFirst(scene, rec);
}

// .text:0x000642F8 size:0x234 mapped:0x806A338C
void fn_2_642F8(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    s16 *timer;
    s16 prev;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        showRec(scene, rec);
        setRecFrame(scene, rec, (u32)recLevelFromWork(rec) << 16);
        rec->state = 0x25;
        break;
    case 0x11:
        setRecFrame(scene, rec, (u32)recLevelFromWork(rec) << 16);
        rec->state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)rec + 0x6) = 0x1A;
        rec->state = 6;
        break;
    case 6:
        timer = (s16 *)((u8 *)rec + 0x6);
        prev = *timer;
        *timer = prev - 1;
        if (prev <= 0) {
            hideRec(scene, rec);
        }
        break;
    case 0x25:
        break;
    }
}

// .text:0x00064128 size:0x1D0 mapped:0x806A31BC
void fn_2_64128(TextScene *scene, TextHandleRec *rec) {
    stepRecObjLevelState(scene, rec);
}

// .text:0x00063F58 size:0x1D0 mapped:0x806A2FEC
void fn_2_63F58(TextScene *scene, TextHandleRec *rec) {
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
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        setRecFrame(scene, rec, 0);
        showRec(scene, rec);
        setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 0x11:
        rec->state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)rec + 0x6) = 0x1A;
        rec->state = 6;
        break;
    case 6:
        timer = (s16 *)((u8 *)rec + 0x6);
        prev = *timer;
        *timer = prev - 1;
        if (prev <= 0) {
            setRecPlayMode(scene, rec, UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        hideRec(scene, rec);
        break;
    case 0x25:
        break;
    }
}

// .text:0x00063BEC size:0x1D0 mapped:0x806A2C80
void fn_2_63BEC(TextScene *scene, TextHandleRec *rec) {
    stepRecObjLevelState(scene, rec);
}

// .text:0x00063A64 size:0x188 mapped:0x806A2AF8
void fn_2_63A64(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        setRecFrame(scene, rec, 0);
        showRec(scene, rec);
        setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
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

// .text:0x00063874 size:0x1F0 mapped:0x806A2908
void fn_2_63874(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    TextGraphicsObject *obj;

    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRec(scene, rec);
        rec->state = 0x26;
        break;
    case 2:
        setRecFrame(scene, rec, 0);
        load_Icon(scene, rec->handle, 1, 0x12, rec->unkA);
        showRec(scene, rec);
        setRecPlayMode(scene, rec, UI_PLAY_FORWARD);
        rec->state = 0x25;
        break;
    case 5:
        setRecPlayMode(scene, rec, UI_PLAY_BACKWARD);
        rec->state = 6;
        break;
    case 6:
        obj = graphicsRelatedArray[scene->firstHandle + rec->handle].object;
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            setRecPlayMode(scene, rec, UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    case 7:
        hideRec(scene, rec);
        break;
    case 0x25:
        break;
    }
}

// .text:0x000636A4 size:0x1D0 mapped:0x806A2738
void fn_2_636A4(TextScene *scene, TextHandleRec *rec) {
    stepRecObjLevelState(scene, rec);
}
