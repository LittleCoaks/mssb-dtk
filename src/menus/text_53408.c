#include "menus/text_53408.h"
#include "text/text.h"
#include "menus/text_35EC0.h"
#include "Dolphin/GX/GXPixel.h"
#include "Unknown/File_0x80035838.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/dvdsys.h"

// Local prototypes and externs for symbols owned by other units.
extern u8 *menuControlVariables;
extern u8 *lbl_2_bss_1A8230;
extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_bss_33FBCC[];
extern u8 lbl_2_bss_9E08[];
extern u8 challengeMapTexturesFileDescriptor[];
extern u8 skyPanoramaFileDescriptorChallengeMap[];
extern u8 g_d_GameSettings[];
extern u8 Static_Stats_Tables[];
extern u8 inningSetting[];
extern u8 cardCheck[];
extern int menuCursors[];
extern u8 hugeAnimStruct[0x3154];
extern u8 menuNumber[];
extern u8 lbl_800FEF70[];
extern u8 lbl_2_data_205D4[];
extern u8 RecordsBookFiles[];
extern u8 recordsBookTexturesFileDescriptor[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_2_data_1FFB4[];
extern u8 AtBat_ButtonInput1[];
extern u8 lbl_2_bss_9E10[];

void fn_2_52690(void);
void fn_80035B50(int arg0);
void fn_80042D38(u16 screen);
void changeScene(u8 scene, u16 arg1);
void fn_2_68E68(void);
void fn_2_47FF8(void);
void fn_2_47CFC(void);
void fn_2_54474(void);
void fn_80053FE8(void);
void fn_2_8E8A4(void);
void fn_800111B4(void *bank);
void fn_800216F8(s32 id, void (*callback)(void));
void pushDictionaryAudioGroup(void);
void fn_2_5389C(void);
void fn_2_1FFC4(s32 arg);
void fn_2_1FF10(s32 arg);
void fn_2_1FF14(s32 arg);
void fn_2_1FF0C(s32 arg);
void fn_2_93C64(void);
void fn_2_489DC(void);
void fn_2_4E878(void *item, void *data);
void fn_2_4E858(void *item);
void fn_8000F8F4(void *item);

// One 0x18-byte entry of the per-table array at lbl_2_bss_1A8230 / 1A8234.
typedef struct Fn53Entry {
    /* 0x00 */ void *ptr;
    /* 0x04 */ u8 _04[0x0E - 0x04];
    /* 0x0E */ s16 index;
    /* 0x10 */ u8 _10[0x18 - 0x10];
} Fn53Entry;

// One 0x10-byte record of a source table that fills the 0x18-byte entries
// of lbl_2_bss_1A8230 / lbl_2_bss_1A8234.
typedef struct Fn54Rec {
    /* 0x00 */ void *ptr;
    /* 0x04 */ s16 j;
    /* 0x06 */ s16 f06;
    /* 0x08 */ s16 i;
    /* 0x0A */ s16 f0A;
    /* 0x0C */ s16 f0C;
    /* 0x0E */ u8 _0E[2];
} Fn54Rec;

// The 0x18-byte entry that Fn54Rec is copied into.
typedef struct Fn54Entry {
    /* 0x00 */ void *ptr;
    /* 0x04 */ s16 unknown04;
    /* 0x06 */ s16 unknown06;
    /* 0x08 */ s16 j;
    /* 0x0A */ s16 f06;
    /* 0x0C */ s16 i;
    /* 0x0E */ s16 f0A;
    /* 0x10 */ s16 f0C;
    /* 0x12 */ s16 unknown12;
    /* 0x14 */ s16 unknown14;
    /* 0x16 */ u8 _16[2];
} Fn54Entry;

// .text:0x00054BAC size:0x4 mapped:0x80693C40
void fn_2_54BAC(void) {
    return;
}

// .text:0x00054B38 size:0x74 mapped:0x80693BCC
void fn_2_54B38(void) {
    if (hugeAnimStruct[0x307A] == 2) {
        if (*(u8 *)(lbl_2_bss_1A8248 + 0x44F2) != 4) {
            fn_2_68E68();
        }
        fn_2_47FF8();
        if (*(u8 *)(lbl_2_bss_1A8248 + 0x44F2) != 4) {
            fn_2_47CFC();
        }
    }
    GXSetZCompLoc(FALSE);
}

// .text:0x000549B4 size:0x184 mapped:0x80693A48
void fn_2_549B4(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    switch (*(s8 *)((u8 *)item + 0x28)) {
    case 0:
        screenTextArray.textBanks[2] = ARAMTransfer(RecordsBookFiles, 0, 1, 0);
        *(u8 *)((u8 *)item + 0x28) = 1;
        break;
    case 1:
        if (lbl_803C6CF8[0x715] == 1) {
            fn_800111B4(screenTextArray.textBanks[2]);
            *(u8 *)((u8 *)item + 0x28) = 2;
        }
        break;
    case 2:
        if (diskReadRelated(recordsBookTexturesFileDescriptor, 0xA) != 0) {
            *(u8 *)((u8 *)item + 0x28) = 3;
        }
        break;
    case 3:
        *(s16 *)((u8 *)item + 0x10) = 0;
        fn_800216F8(4, pushDictionaryAudioGroup);
        *(u8 *)((u8 *)item + 0x28) = 4;
        break;
    case 4:
        if (*(s16 *)((u8 *)item + 0x10) != 0) {
            *(s16 *)((u8 *)item + 0x10) = 0;
            *(u8 *)((u8 *)item + 0x28) = 5;
        }
        break;
    case 5: {
        DrawingSceneStruct *inserted;

        *(s16 *)(lbl_2_bss_1A824C + 0x197746) = 1;
        inserted = insertGraphicDrawingFunction(fn_2_8E8A4, 2);
        *(u8 *)((u8 *)inserted + 0x28) = 0;
        *(s16 *)((u8 *)inserted + 0x16) = 0xC;
        *(s16 *)((u8 *)item + 0x10) = 0;
        *(u8 *)((u8 *)item + 0x28) = 6;
        break;
    }
    case 6:
        if (*(s16 *)((u8 *)item + 0x10) == 1) {
            *(s16 *)((u8 *)item->currentDrawingItem + 0x10) = 1;
            removeCurrentDrawingItem();
            *(u8 *)((u8 *)item + 0x28) = 0;
        }
        break;
    }
}

// .text:0x00054890 size:0x124 mapped:0x80693924
void fn_2_54890(void) {
    Fn54Rec *src = (Fn54Rec *)lbl_2_data_205D4;
    s32 k;
    DrawingSceneStruct *item;

    menuNumber[9] = menuNumber[8];
    menuNumber[0] = 0x5C;
    menuNumber[8] = *(u16 *)(lbl_800FEF70 + 0x5C8);
    insertGraphicDrawingFunction(fn_80053FE8, 0);
    item = insertGraphicDrawingFunction(fn_2_5389C, 0);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    *(s16 *)((u8 *)item + 0x1E) = 0;

    for (k = 0; k < 0x2B; k++) {
        Fn54Entry *dst = (Fn54Entry *)(lbl_2_bss_1A8234 + src[k].i * 0x5100 + src[k].j * 0x18);
        dst->ptr = src[k].ptr;
        dst->j = src[k].j;
        dst->f06 = src[k].f06;
        dst->i = src[k].i;
        dst->f0A = src[k].f0A;
        dst->f0C = src[k].f0C;
    }

    lbl_2_bss_1A8234[0x160000 + 0x2604] = 1;
    lbl_2_bss_1A8234[0x160000 + 0x2605] = 1;
    lbl_2_bss_1A8234[0x160000 + 0x2606] = 1;
    lbl_2_bss_1A8234[0x160000 + 0x2607] = 1;
    lbl_2_bss_1A8234[0x160000 + 0x260A] = 1;
}

// .text:0x00054874 size:0x1C mapped:0x80693908
void fn_2_54874(void) {
    *(s16 *)(lbl_2_bss_1A824C + 0x197754) = 0;
}

// .text:0x00054848 size:0x2C mapped:0x806938DC
void fn_2_54848(void) {
    *(s16 *)(lbl_2_bss_1A824C + 0x197754) = 1;
    *(s16 *)(lbl_2_bss_1A824C + 0x197752) = 10;
}

// .text:0x00054844 size:0x4 mapped:0x806938D8
void fn_2_54844(void) {
    return;
}

static inline void clearTableEntry(Fn54Entry *entry) {
    entry->ptr = NULL;
    entry->unknown04 = 0;
    entry->unknown06 = 0;
    entry->f0C = 0;
    entry->j = 0;
    entry->f06 = 0;
    entry->i = 0;
    entry->f0A = 0;
    entry->unknown12 = 0;
    entry->unknown14 = 0;
}

// .text:0x00054474 size:0x3D0 mapped:0x80693508
void fn_2_54474(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 0x46; i++) {
        for (j = 0; j < 0x360; j++) {
            Fn54Entry *dst = (Fn54Entry *)(lbl_2_bss_1A8234 + i * 0x5100 + j * 0x18);
            clearTableEntry(dst);
        }
    }
    for (i = 0; i < 0xA; i++) {
        for (j = 0; j < 0x360; j++) {
            Fn54Entry *dst = (Fn54Entry *)(lbl_2_bss_1A8230 + i * 0x5100 + j * 0x18);
            clearTableEntry(dst);
        }
    }
}

// .text:0x00054354 size:0x120 mapped:0x806933E8
void fn_2_54354(void *srcv, s32 count) {
    Fn54Rec *src = (Fn54Rec *)srcv;
    s32 k;

    for (k = 0; k < count; k++) {
        Fn54Entry *dst = (Fn54Entry *)(lbl_2_bss_1A8234 + src[k].i * 0x5100 + src[k].j * 0x18);
        dst->ptr = src[k].ptr;
        dst->j = src[k].j;
        dst->f06 = src[k].f06;
        dst->i = src[k].i;
        dst->f0A = src[k].f0A;
        dst->f0C = src[k].f0C;
    }
}

// .text:0x00054234 size:0x120 mapped:0x806932C8
void fn_2_54234(void *srcv, s32 count) {
    Fn54Rec *src = (Fn54Rec *)srcv;
    s32 k;

    for (k = 0; k < count; k++) {
        Fn54Entry *dst = (Fn54Entry *)(lbl_2_bss_1A8230 + src[k].i * 0x5100 + src[k].j * 0x18);
        dst->ptr = src[k].ptr;
        dst->j = src[k].j;
        dst->f06 = src[k].f06;
        dst->i = src[k].i;
        dst->f0A = src[k].f0A;
        dst->f0C = src[k].f0C;
    }
}

// .text:0x00054120 size:0x114 mapped:0x806931B4
void fn_2_54120(void) {
    s32 i;

    for (i = 0; i < 0x46; i++) {
        lbl_2_bss_1A8234[i + 0x160000 + 0x2604] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x264A] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x2690] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x26D6] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x271C] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x2762] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x27A8] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x27EE] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x2834] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x287A] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x28C0] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x2906] = 0;
        lbl_2_bss_1A8234[i + 0x160000 + 0x294C] = 0;
    }
}

// .text:0x0005400C size:0x114 mapped:0x806930A0
void fn_2_5400C(void) {
    s32 i;

    for (i = 0; i < 0xA; i++) {
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A04] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A0E] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A18] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A22] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A2C] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A36] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A40] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A4A] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A54] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A5E] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A68] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A72] = 0;
        lbl_2_bss_1A8230[i + 0x30000 + 0x2A7C] = 0;
    }
}

static inline void updateEntry(void *arg, Fn53Entry *entry) {
    void (*fn)(void *, Fn53Entry *) = (void (*)(void *, Fn53Entry *))entry->ptr;
    if (fn != NULL) {
        fn(arg, entry);
    }
}

// .text:0x00053F88 size:0x84 mapped:0x8069301C
void fn_2_53F88(void *arg) {
    s32 i;
    s32 j;

    for (i = 0; i < 0x46; i++) {
        for (j = 0; j < 0x360; j++) {
            updateEntry(arg, (Fn53Entry *)(lbl_2_bss_1A8234 + i * 0x5100 + j * sizeof(Fn53Entry)));
        }
    }
}

// .text:0x00053F04 size:0x84 mapped:0x80692F98
void fn_2_53F04(void *arg) {
    s32 i;
    s32 j;

    for (i = 0; i < 0xA; i++) {
        for (j = 0; j < 0x360; j++) {
            updateEntry(arg, (Fn53Entry *)(lbl_2_bss_1A8230 + i * 0x5100 + j * sizeof(Fn53Entry)));
        }
    }
}

static inline TextGraphicsObject *entryObject(void *arg, Fn53Entry *entry) {
    return graphicsRelatedArray[((TextScene *)arg)->firstHandle + entry->index].object;
}

static inline void clearEntryObject(void *arg, Fn53Entry *entry) {
    if (entry->ptr != NULL) {
        *((u8 *)entryObject(arg, entry) + 0x68) = 0;
        entryObject(arg, entry)->flags &= ~0x2;
    }
}

// .text:0x00053DF8 size:0x10C mapped:0x80692E8C
void fn_2_53DF8(void *arg) {
    s32 i;
    s32 j;

    for (i = 0; i < 0x46; i++) {
        for (j = 0; j < 0x360; j++) {
            clearEntryObject(arg, (Fn53Entry *)(lbl_2_bss_1A8234 + i * 0x5100 + j * sizeof(Fn53Entry)));
        }
    }
}

// .text:0x00053CEC size:0x10C mapped:0x80692D80
void fn_2_53CEC(void *arg) {
    s32 i;
    s32 j;

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 0x360; j++) {
            clearEntryObject(arg, (Fn53Entry *)(lbl_2_bss_1A8230 + i * 0x5100 + j * sizeof(Fn53Entry)));
        }
    }
}

static inline u8 *entryFlagRow(u8 **table, s16 index, s32 offset) {
    return *table + offset + index;
}

// .text:0x00053BC8 size:0x124 mapped:0x80692C5C
s16 fn_2_53BC8(void *arg) {
    s32 result = -1;
    s16 index = *(s16 *)((u8 *)arg + 0xC);
    u8 *row = entryFlagRow(&lbl_2_bss_1A8234, index, 0x160000);

    if (row[0x2604] != 0) {
        result = 0;
    } else if (row[0x264A] != 0) {
        result = 2;
    } else if (row[0x2834] != 0) {
        result = 5;
    } else if (row[0x2690] != 0) {
        result = 0x17;
    } else if (row[0x26D6] != 0) {
        result = 8;
    } else if (row[0x271C] != 0) {
        result = 0xB;
    } else if (row[0x2762] != 0) {
        result = 0xE;
    } else if (row[0x27A8] != 0) {
        result = 0x11;
    } else if (row[0x27EE] != 0) {
        result = 0x14;
    } else if (row[0x287A] != 0) {
        result = 0x18;
    } else if (row[0x28C0] != 0) {
        result = 0x1B;
    } else if (row[0x2906] != 0) {
        result = 0x1E;
    } else if (row[0x294C] != 0) {
        result = 0x21;
    }
    return result;
}

// .text:0x00053AA4 size:0x124 mapped:0x80692B38
s16 fn_2_53AA4(void *arg) {
    s32 result = -1;
    s16 index = *(s16 *)((u8 *)arg + 0xC);
    u8 *row = entryFlagRow(&lbl_2_bss_1A8230, index, 0x30000);

    if (row[0x2A04] != 0) {
        result = 0;
    } else if (row[0x2A0E] != 0) {
        result = 2;
    } else if (row[0x2A54] != 0) {
        result = 5;
    } else if (row[0x2A18] != 0) {
        result = 0x17;
    } else if (row[0x2A22] != 0) {
        result = 8;
    } else if (row[0x2A2C] != 0) {
        result = 0xB;
    } else if (row[0x2A36] != 0) {
        result = 0xE;
    } else if (row[0x2A40] != 0) {
        result = 0x11;
    } else if (row[0x2A4A] != 0) {
        result = 0x14;
    } else if (row[0x2A5E] != 0) {
        result = 0x18;
    } else if (row[0x2A68] != 0) {
        result = 0x1B;
    } else if (row[0x2A72] != 0) {
        result = 0x1E;
    } else if (row[0x2A7C] != 0) {
        result = 0x21;
    }
    return result;
}

// .text:0x0005389C size:0x208 mapped:0x80692930
void fn_2_5389C(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    switch (*(u16 *)((u8 *)item + 0x1C)) {
    case 0:
        fn_2_4E878(item, lbl_2_data_1FFB4);
        *(u16 *)((u8 *)item + 0x1C) = 1;
        *(u16 *)((u8 *)item + 0x18) = 0;
        break;
    case 1:
        break;
    }

    fn_2_53F88(item);

    fn_2_54120();

    if (lbl_2_bss_1A8234[0x162992] != 0) {
        fn_8000F8F4(item);
        text_freeAllBlocks();
        fn_2_4E858(item);
        removeCurrentDrawingItem();
        *(u16 *)((u8 *)item + 0x1C) = 0;
        *(u16 *)((u8 *)item + 0x1E) = 0;
        lbl_2_bss_1A8234[0x162992] = 0;
    }
}

// .text:0x000535B0 size:0x2EC mapped:0x80692644
void fn_2_535B0(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 state = *(s8 *)((u8 *)item + 0x28);
    s32 i;

    switch (state) {
    case 0:
        *(u32 *)(lbl_2_bss_1A824C + 0x190000 + 0x76A4) = 0;
        *(u32 *)(lbl_2_bss_1A824C + 0x190000 + 0x76A0) = 0;
        *((u8 *)item + 0x28) = 1;
        break;
    case 1:
        fn_2_1FFC4(2);
        for (i = 0; i < 2; i++) {
            fn_2_1FF10(i);
            switch (i) {
            case 0:
                if (*(u32 *)(lbl_2_bss_1A824C + 0x190000 + 0x76A0) == i) {
                    u8 *entry = AtBat_ButtonInput1 + *(s8 *)(lbl_2_bss_1A824C + 0x190000 + 0x7863) * 0x20;
                    if ((*(u16 *)(entry + 2) & 0x100) || (*(s8 *)(AtBat_ButtonInput1 + 0x13) > 0x32)) {
                        *((u8 *)item + 0x28) = 3;
                    }
                }
                break;
            case 1:
                if (*(u32 *)(lbl_2_bss_1A824C + 0x190000 + 0x76A0) == i) {
                    u8 *entry = AtBat_ButtonInput1 + *(s8 *)(lbl_2_bss_1A824C + 0x190000 + 0x7863) * 0x20;
                    if (*(u16 *)(entry + 2) & 0x102) {
                        lbl_2_bss_1A824C[0x190000 + 0x784A] = 1;
                        lbl_2_bss_1A824C[0x190000 + 0x7846] = 0;
                        lbl_2_bss_1A824C[0x190000 + 0x7845] = 1;
                        lbl_2_bss_9E10[0] = 1;
                        *((u8 *)item + 0x28) = 2;
                    }
                }
                break;
            }
        }
        {
            u8 *entry = AtBat_ButtonInput1 + *(s8 *)(lbl_2_bss_1A824C + 0x190000 + 0x7863) * 0x20;
            if ((*(u16 *)(entry + 2) & 0x200) || (*(s8 *)(AtBat_ButtonInput1 + 0x13) > 0x32)) {
                *((u8 *)item + 0x28) = 3;
            }
        }
        break;
    case 2:
        fn_2_1FF14(1);
        for (i = 0; i < 1; i++) {
            fn_2_1FF0C(i);
            switch (i) {
            case 0:
                if (*(u32 *)(lbl_2_bss_1A824C + 0x190000 + 0x76A4) == i) {
                    u8 *entry = AtBat_ButtonInput1 + *(s8 *)(lbl_2_bss_1A824C + 0x190000 + 0x7863) * 0x20;
                    u16 flags = *(u16 *)(entry + 2);

                    if (flags & 0x200) {
                        lbl_2_bss_1A824C[0x190000 + 0x784A] = 0;
                        lbl_2_bss_1A824C[0x190000 + 0x7846] = 0;
                        *(u32 *)(lbl_2_bss_1A824C + 0x190000 + 0x76A4) = 0;
                        lbl_2_bss_1A824C[0x190000 + 0x7845] = 0;
                        *((u8 *)item + 0x28) = 1;
                    } else if (flags & 0x100) {
                        lbl_2_bss_9E10[0] ^= 1;
                    } else if (flags & 0x1000) {
                        fn_2_93C64();
                    }
                    if ((s8)lbl_2_bss_9E10[0] != 0) {
                        fn_2_489DC();
                    }
                }
                break;
            }
        }
        break;
    case 3:
        ((DrawingSceneStruct *)item->currentDrawingItem)->state = 1;
        removeCurrentDrawingItem();
        *((u8 *)item + 0x28) = 0;
        break;
    }
}

// .text:0x00053408 size:0x1A8 mapped:0x8069249C
void challengeMap(void) {
    switch ((*(u16 *)lbl_2_bss_33FBCC)) {
    case 0:
        if (diskReadRelated(challengeMapTexturesFileDescriptor, 8) != 0) {
            lbl_2_bss_33FBCC[0xD] = 0;
            if (*(u16 *)(menuControlVariables + 0x6) == 0x10) {
                (*(u16 *)lbl_2_bss_33FBCC) = 1;
                Static_Stats_Tables[0x4756] = 1;
            } else {
                (*(u16 *)lbl_2_bss_33FBCC) = 2;
            }
            if (*(s16 *)(inningSetting + 0x58) == 0xA && cardCheck[0x47] != 0) {
                changeScene(6, 6);
                changeScene(3, 6);
                fn_80035B50(8);
                *(s16 *)(inningSetting + 0x58) = 9;
                *(s16 *)(inningSetting + 0x5A) = 0;
                fn_80042D38(5);
                menuCursors[0x14] = 0;
                *(u16 *)lbl_2_bss_33FBCC = 0;
                *(s16 *)lbl_2_bss_9E08 = 0;
                cardCheck[0x52] = 0;
            }
        }
        break;
    case 1:
        if (diskReadRelated(skyPanoramaFileDescriptorChallengeMap, 6) != 0) {
            (*(u16 *)lbl_2_bss_33FBCC) = 2;
        }
        break;
    case 2:
        insertGraphicDrawingFunction(fn_2_52690, 0x2000);
        Static_Stats_Tables[0x472B] = g_d_GameSettings[0x6];
        (*(u16 *)lbl_2_bss_33FBCC) = (*(u16 *)lbl_2_bss_33FBCC) + 1;
        break;
    case 3:
        break;
    }
}
