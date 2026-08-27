#include "menus/rep_0788.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "text/text_channel.h"
#include "text/text_block.h"
#include "static/UnknownHomes_Static.h"

extern DrawingSceneStruct *currentDrawingItem;
extern s16 lbl_2_data_3D30[][4];
extern u8 *lbl_2_bss_1A824C;

void fn_2_54354(void *arg0, int count);
void fn_2_54234(void *arg0, int count);
s16 fn_2_53BC8(void *arg0);
extern u8 lbl_2_data_1073C[0x80];
extern u8 lbl_2_data_105FC[0x20];
extern u8 lbl_2_data_F0EC[0x13A0];
extern u8 lbl_2_data_9FC8[0x2930];
extern u8 lbl_2_data_104EC[0x20];
extern u8 lbl_2_data_1061C[0x120];
extern u8 lbl_2_data_C96C[0x2780];
extern u8 *lbl_2_bss_1A8234;

void fn_2_4E878(void *arg0, void *arg1);
void fn_2_53F88(void *arg0);
void fn_2_54120(void);
void fn_2_53DF8(void *arg0);
void fn_8000F8F4(void *arg0);
void fn_2_4E858(void *arg0);

// .text:0x0001D440 size:0x2ACC mapped:0x8065C4D4
void fn_2_1D440(void) {
    return;
}

// .text:0x0001FF0C size:0x4 mapped:0x8065EFA0
void fn_2_1FF0C(void) {
    return;
}

// .text:0x0001FF10 size:0x4 mapped:0x8065EFA4
void fn_2_1FF10(void) {
    return;
}

// .text:0x0001FF14 size:0xB0 mapped:0x8065EFA8
void fn_2_1FF14(s32 arg0) {
    u8 *base = (u8 *)&AtBat_ButtonInput1 + 4;
    s8 port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    u16 value = *(u16 *)(base + port * 32);
    if (value & 8) {
        (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4])--;
        if (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4] < 0) {
            *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4] = arg0 - 1;
        }
    }
    port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    value = *(u16 *)(base + port * 32);
    if (!(value & 4)) {
        return;
    }
    (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4])++;
    if (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4] < arg0) {
        return;
    }
    *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4] = 0;
}

// .text:0x0001FFC4 size:0xB0 mapped:0x8065F058
void fn_2_1FFC4(s32 arg0) {
    u8 *base = (u8 *)&AtBat_ButtonInput1 + 4;
    s8 port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    u16 value = *(u16 *)(base + port * 32);
    if (value & 8) {
        (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0])--;
        if (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0] < 0) {
            *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0] = arg0 - 1;
        }
    }
    port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    value = *(u16 *)(base + port * 32);
    if (!(value & 4)) {
        return;
    }
    (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0])++;
    if (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0] < arg0) {
        return;
    }
    *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0] = 0;
}

// .text:0x00020074 size:0x70 mapped:0x8065F108
int fn_2_20074(void) {
    s8 port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    u16 value = *(u16 *)((u8 *)&AtBat_ButtonInput1 + port * 32);
    if (value & 8) {
        return 0;
    }
    if (value & 4) {
        return 1;
    }
    if (value & 1) {
        return 2;
    }
    if (value & 2) {
        return 3;
    }
    return -1;
}

// .text:0x000200E4 size:0x100 mapped:0x8065F178
void fn_2_200E4(void) {
    return;
}

// .text:0x000201E4 size:0x34 mapped:0x8065F278
s16 fn_2_201E4(s16 row, s16 col) {
    if (col < 0) {
        return -1;
    }
    return lbl_2_data_3D30[row][col];
}

// .text:0x00020218 size:0x40 mapped:0x8065F2AC
void fn_2_20218(void) {
    lbl_2_bss_1A824C[0x190000 + 0x782B] = 0;
    lbl_2_bss_1A824C[0x190000 + 0x782C] = 0;
    lbl_2_bss_1A824C[0x190000 + 0x782A] = 0;
    lbl_2_bss_1A824C[0x190000 + 0x7832] = 0;
}

// .text:0x00020258 size:0x4 mapped:0x8065F2EC
void fn_2_20258(void) {
    return;
}

// .text:0x0002025C size:0xCC mapped:0x8065F2F0
void fn_2_2025C(void) {
    return;
}

// .text:0x00020328 size:0x4D4 mapped:0x8065F3BC
void fn_2_20328(void) {
    return;
}

// .text:0x000207FC size:0x4B4 mapped:0x8065F890
void fn_2_207FC(void) {
    return;
}

// .text:0x00020CB0 size:0x58 mapped:0x8065FD44
int fn_2_20CB0(u32 x) {
    int result = 0;
    switch (x) {
        case 0:
            result = 0;
            break;
        case 4:
            result = 1;
            break;
        case 10:
            result = 2;
            break;
        case 2:
            result = 3;
            break;
        case 6:
            result = 4;
            break;
        case 9:
            result = 5;
            break;
    }
    return result;
}

// .text:0x00020D08 size:0x3464 mapped:0x8065FD9C
void fn_2_20D08(void) {
    return;
}

// .text:0x0002416C size:0xCC mapped:0x80663200
void fn_2_2416C(void) {
    DrawingSceneStruct *item;
    switch (*(u16 *)((u8 *)currentDrawingItem + 0x1C)) {
    case 1:
        break;
    case 0:
        fn_2_4E878(currentDrawingItem, lbl_2_data_1061C);
        *(s16 *)((u8 *)currentDrawingItem + 0x1C) = 1;
        *(s16 *)((u8 *)currentDrawingItem + 0x18) = 0;
        break;
    }
    item = currentDrawingItem;
    fn_2_53F88(item);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0x160000 + 0x2992] != 0) {
        text_freeAllBlocks();
        fn_2_53DF8(item);
        fn_8000F8F4(item);
        fn_2_4E858(item);
        removeCurrentDrawingItem();
        *(s16 *)((u8 *)item + 0x1C) = 0;
        lbl_2_bss_1A8234[0x160000 + 0x2992] = 0;
    }
}

// .text:0x00024238 size:0xC4 mapped:0x806632CC
void fn_2_24238(void) {
    return;
}

// .text:0x000242FC size:0xC0 mapped:0x80663390
void fn_2_242FC(void) {
    return;
}

// .text:0x000243BC size:0xCC mapped:0x80663450
void fn_2_243BC(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    switch (*(u16 *)((u8 *)item + 0x1C)) {
    case 1:
        break;
    case 0:
        fn_2_4E878(item, lbl_2_data_C96C);
        *(s16 *)((u8 *)item + 0x1C) = 1;
        *(s16 *)((u8 *)item + 0x18) = 0;
        break;
    }
    fn_2_53F88(item);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0x160000 + 0x2992] != 0) {
        text_freeAllBlocks();
        fn_2_53DF8(item);
        fn_8000F8F4(item);
        fn_2_4E858(item);
        removeCurrentDrawingItem();
        *(s16 *)((u8 *)item + 0x1C) = 0;
        lbl_2_bss_1A8234[0x160000 + 0x2992] = 0;
    }
}

// .text:0x00024488 size:0x140 mapped:0x8066351C
void fn_2_24488(void) {
    return;
}

// .text:0x000245C8 size:0x44 mapped:0x8066365C
void fn_2_245C8(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_2_2416C, 2);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    fn_2_54354(lbl_2_data_1073C, 8);
}

// .text:0x0002460C size:0x44 mapped:0x806636A0
void fn_2_2460C(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_2_24238, 2);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    fn_2_54354(lbl_2_data_105FC, 2);
}

// .text:0x00024650 size:0x4C mapped:0x806636E4
void fn_2_24650(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_2_242FC, 2);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    *(s16 *)((u8 *)item + 0x1E) = 0;
    fn_2_54234(lbl_2_data_104EC, 2);
}

// .text:0x0002469C size:0x44 mapped:0x80663730
void fn_2_2469C(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_2_243BC, 2);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    fn_2_54354(lbl_2_data_F0EC, 0x13A);
}

// .text:0x000246E0 size:0x44 mapped:0x80663774
void fn_2_246E0(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_2_24488, 2);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    fn_2_54354(lbl_2_data_9FC8, 0x293);
}

// .text:0x00024724 size:0x4 mapped:0x806637B8
void fn_2_24724(void) {
    return;
}

// .text:0x00024728 size:0xD8 mapped:0x806637BC
void fn_2_24728(void) {
    return;
}

// .text:0x00024800 size:0x69C mapped:0x80663894
void fn_2_24800(void) {
    return;
}

// .text:0x00024E9C size:0x14 mapped:0x80663F30
s16 fn_2_24E9C(void) {
    return currentDrawingItem->state;
}

// .text:0x00024EB0 size:0x14 mapped:0x80663F44
void fn_2_24EB0(s16 state) {
    currentDrawingItem->state = state;
}

// .text:0x00024EC4 size:0x18C mapped:0x80663F58
void fn_2_24EC4(void) {
    return;
}

// .text:0x00025050 size:0x1B0 mapped:0x806640E4
void fn_2_25050(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x399, 0);
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774C]);
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    }
}

// .text:0x00025200 size:0x1B0 mapped:0x80664294
void fn_2_25200(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x399, 0);
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774C]);
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    }
}

// .text:0x000253B0 size:0x174 mapped:0x80664444
void fn_2_253B0(void) {
    return;
}

// .text:0x00025524 size:0x258 mapped:0x806645B8
void fn_2_25524(void) {
    return;
}

// .text:0x0002577C size:0xD4 mapped:0x80664810
void fn_2_2577C(void) {
    return;
}

// .text:0x00025850 size:0x2C mapped:0x806648E4
void fn_2_25850(void *arg0, void *arg1) {
    u16 idx = *(u16 *)((u8 *)arg0 + 0x14);
    s16 offset = *(s16 *)((u8 *)arg1 + 0xE);
    graphicsRelatedArray[idx + offset].object->flags &= ~2;
}

// .text:0x0002587C size:0x1A0 mapped:0x80664910
void fn_2_2587C(void) {
    return;
}

// .text:0x00025A1C size:0x2C mapped:0x80664AB0
void fn_2_25A1C(void *arg0, void *arg1) {
    u16 idx = *(u16 *)((u8 *)arg0 + 0x14);
    s16 offset = *(s16 *)((u8 *)arg1 + 0xE);
    graphicsRelatedArray[idx + offset].object->flags &= ~2;
}

// .text:0x00025A48 size:0x324 mapped:0x80664ADC
void fn_2_25A48(void) {
    return;
}

// .text:0x00025D6C size:0x2C mapped:0x80664E00
void fn_2_25D6C(void *arg0, void *arg1) {
    u16 idx = *(u16 *)((u8 *)arg0 + 0x14);
    s16 offset = *(s16 *)((u8 *)arg1 + 0xE);
    graphicsRelatedArray[idx + offset].object->flags &= ~2;
}

// .text:0x00025D98 size:0x118 mapped:0x80664E2C
void fn_2_25D98(void) {
    return;
}

// .text:0x00025EB0 size:0x160 mapped:0x80664F44
void fn_2_25EB0(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        s16 idx = *(s16 *)((u8 *)arg1 + 0xA);
        s16 val = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x780E + idx * 2];
        TextGraphicsObject *obj;
        if (val != -1) {
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags |= 2;
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            *(u32 *)((u8 *)obj + 0x5C) = (u32)val << 16;
        } else {
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        *state = 0x25;
        break;
    }
    case 5:
    case 0x25:
        break;
    }
}

// .text:0x00026010 size:0x160 mapped:0x806650A4
void fn_2_26010(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        s16 idx = *(s16 *)((u8 *)arg1 + 0xA);
        s16 val = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7818 + idx * 2];
        TextGraphicsObject *obj;
        if (val != -1) {
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags |= 2;
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            *(u32 *)((u8 *)obj + 0x5C) = (u32)val << 16;
        } else {
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        *state = 0x25;
        break;
    }
    case 5:
    case 0x25:
        break;
    }
}

// .text:0x00026170 size:0x160 mapped:0x80665204
void fn_2_26170(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        s16 idx = *(s16 *)((u8 *)arg1 + 0xA);
        s16 val = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x77A2 + idx * 2];
        TextGraphicsObject *obj;
        if (val != -1) {
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags |= 2;
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            *(u32 *)((u8 *)obj + 0x5C) = (u32)val << 16;
        } else {
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        *state = 0x25;
        break;
    }
    case 5:
    case 0x25:
        break;
    }
}

// .text:0x000262D0 size:0x3B4 mapped:0x80665364
void fn_2_262D0(void) {
    return;
}

// .text:0x00026684 size:0xF0 mapped:0x80665718
void fn_2_26684(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5:
    case 0x25:
        break;
    }
}

// .text:0x00026774 size:0xF0 mapped:0x80665808
void fn_2_26774(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5:
    case 0x25:
        break;
    }
}

// .text:0x00026864 size:0x290 mapped:0x806658F8
void fn_2_26864(void) {
    return;
}

// .text:0x00026AF4 size:0x17C mapped:0x80665B88
void fn_2_26AF4(void) {
    return;
}

// .text:0x00026C70 size:0x310 mapped:0x80665D04
void fn_2_26C70(void) {
    return;
}

// .text:0x00026F80 size:0x138 mapped:0x80666014
void fn_2_26F80(void) {
    return;
}

// .text:0x000270B8 size:0x204 mapped:0x8066614C
void fn_2_270B8(void) {
    return;
}

// .text:0x000272BC size:0x2C mapped:0x80666350
void fn_2_272BC(void *arg0, void *arg1) {
    u16 idx = *(u16 *)((u8 *)arg0 + 0x14);
    s16 offset = *(s16 *)((u8 *)arg1 + 0xE);
    graphicsRelatedArray[idx + offset].object->flags &= ~2;
}

// .text:0x000272E8 size:0x1B4 mapped:0x8066637C
void fn_2_272E8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002749C size:0x1C4 mapped:0x80666530
void fn_2_2749C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x1c7, 0);
        practiceTextRelated(*(s16 *)((u8 *)arg1 + 0x14), 1, 0);
        *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x72A2] = *(s16 *)((u8 *)arg1 + 0x14);
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x6FBC]);
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 0x25:
        break;
    }
    {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x00027660 size:0x1C4 mapped:0x806666F4
void fn_2_27660(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x1c7, 0);
        practiceTextRelated(*(s16 *)((u8 *)arg1 + 0x14), 1, 0);
        *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x72A0] = *(s16 *)((u8 *)arg1 + 0x14);
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x6FB8]);
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 0x25:
        break;
    }
    {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x00027824 size:0x1D0 mapped:0x806668B8
void fn_2_27824(void) {
    return;
}

// .text:0x000279F4 size:0x188 mapped:0x80666A88
void fn_2_279F4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj;
            *((u8 *)graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object + 0x68) = 0;
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00027B7C size:0x210 mapped:0x80666C10
void fn_2_27B7C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x35c, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        s8 *base = (s8 *)&lbl_2_bss_1A824C[0x190000];
        s8 b1 = base[0x78F0];
        s8 b2 = base[b1 + 0x78DB];
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, b2 + 0x35c);
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x00027D8C size:0x150 mapped:0x80666E20
void fn_2_27D8C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00027EDC size:0x1B4 mapped:0x80666F70
void fn_2_27EDC(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00028090 size:0x194 mapped:0x80667124
void fn_2_28090(void) {
    return;
}

// .text:0x00028224 size:0x138 mapped:0x806672B8
void fn_2_28224(void) {
    return;
}

// .text:0x0002835C size:0x154 mapped:0x806673F0
void fn_2_2835C(void) {
    return;
}

// .text:0x000284B0 size:0x2E4 mapped:0x80667544
void fn_2_284B0(void) {
    return;
}

// .text:0x00028794 size:0x1B4 mapped:0x80667828
void fn_2_28794(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00028948 size:0x3DC mapped:0x806679DC
void fn_2_28948(void) {
    return;
}

// .text:0x00028D24 size:0x17C mapped:0x80667DB8
void fn_2_28D24(void) {
    return;
}

// .text:0x00028EA0 size:0x3CC mapped:0x80667F34
void fn_2_28EA0(void) {
    return;
}

// .text:0x0002926C size:0x618 mapped:0x80668300
void fn_2_2926C(void) {
    return;
}

// .text:0x00029884 size:0x694 mapped:0x80668918
void fn_2_29884(void) {
    return;
}

// .text:0x00029F18 size:0x150 mapped:0x80668FAC
void fn_2_29F18(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x28;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002A068 size:0x1B4 mapped:0x806690FC
void fn_2_2A068(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002A21C size:0x11C mapped:0x806692B0
void fn_2_2A21C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002A338 size:0x444 mapped:0x806693CC
void fn_2_2A338(void) {
    return;
}

// .text:0x0002A77C size:0x310 mapped:0x80669810
void fn_2_2A77C(void) {
    return;
}

// .text:0x0002AA8C size:0x2A4 mapped:0x80669B20
void fn_2_2AA8C(void) {
    return;
}

// .text:0x0002AD30 size:0x1AC mapped:0x80669DC4
void fn_2_2AD30(void) {
    return;
}

// .text:0x0002AEDC size:0x188 mapped:0x80669F70
void fn_2_2AEDC(void) {
    return;
}

// .text:0x0002B064 size:0x1EC mapped:0x8066A0F8
void fn_2_2B064(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *(s16 *)((u8 *)arg1 + 0x6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0 || (*counter)-- <= 0) {
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002B250 size:0x1EC mapped:0x8066A2E4
void fn_2_2B250(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *(s16 *)((u8 *)arg1 + 0x6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0 || (*counter)-- <= 0) {
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002B43C size:0x218 mapped:0x8066A4D0
void fn_2_2B43C(void) {
    return;
}

// .text:0x0002B654 size:0x230 mapped:0x8066A6E8
void fn_2_2B654(void) {
    return;
}

// .text:0x0002B884 size:0x2B0 mapped:0x8066A918
void fn_2_2B884(void) {
    return;
}

// .text:0x0002BB34 size:0x270 mapped:0x8066ABC8
void fn_2_2BB34(void) {
    return;
}

// .text:0x0002BDA4 size:0x17C mapped:0x8066AE38
void fn_2_2BDA4(void) {
    return;
}

// .text:0x0002BF20 size:0x288 mapped:0x8066AFB4
void fn_2_2BF20(void) {
    return;
}

// .text:0x0002C1A8 size:0x1D0 mapped:0x8066B23C
void fn_2_2C1A8(void) {
    return;
}

// .text:0x0002C378 size:0x16C mapped:0x8066B40C
void fn_2_2C378(void) {
    return;
}

// .text:0x0002C4E4 size:0x1B4 mapped:0x8066B578
void fn_2_2C4E4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002C698 size:0x1C8 mapped:0x8066B72C
void fn_2_2C698(void) {
    return;
}

// .text:0x0002C860 size:0x1D0 mapped:0x8066B8F4
void fn_2_2C860(void) {
    return;
}

// .text:0x0002CA30 size:0x19C mapped:0x8066BAC4
void fn_2_2CA30(void) {
    return;
}

// .text:0x0002CBCC size:0x1D8 mapped:0x8066BC60
void fn_2_2CBCC(void) {
    return;
}

// .text:0x0002CDA4 size:0x1B4 mapped:0x8066BE38
void fn_2_2CDA4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002CF58 size:0x17C mapped:0x8066BFEC
void fn_2_2CF58(void) {
    return;
}

// .text:0x0002D0D4 size:0x434 mapped:0x8066C168
void fn_2_2D0D4(void) {
    return;
}

// .text:0x0002D508 size:0x138 mapped:0x8066C59C
void fn_2_2D508(void) {
    return;
}

// .text:0x0002D640 size:0x284 mapped:0x8066C6D4
void fn_2_2D640(void) {
    return;
}

// .text:0x0002D8C4 size:0x1E4 mapped:0x8066C958
void fn_2_2D8C4(void) {
    return;
}

// .text:0x0002DAA8 size:0x200 mapped:0x8066CB3C
void fn_2_2DAA8(void) {
    return;
}

// .text:0x0002DCA8 size:0x1D0 mapped:0x8066CD3C
void fn_2_2DCA8(void) {
    return;
}

// .text:0x0002DE78 size:0x150 mapped:0x8066CF0C
void fn_2_2DE78(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x28;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002DFC8 size:0x1B4 mapped:0x8066D05C
void fn_2_2DFC8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002E17C size:0x11C mapped:0x8066D210
void fn_2_2E17C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002E298 size:0x1B4 mapped:0x8066D32C
void fn_2_2E298(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002E44C size:0x17C mapped:0x8066D4E0
void fn_2_2E44C(void) {
    return;
}

// .text:0x0002E5C8 size:0x208 mapped:0x8066D65C
void fn_2_2E5C8(void) {
    return;
}

// .text:0x0002E7D0 size:0x414 mapped:0x8066D864
void fn_2_2E7D0(void) {
    return;
}

// .text:0x0002EBE4 size:0x3E8 mapped:0x8066DC78
void fn_2_2EBE4(void) {
    return;
}

// .text:0x0002EFCC size:0x578 mapped:0x8066E060
void fn_2_2EFCC(void) {
    return;
}

// .text:0x0002F544 size:0x1CC mapped:0x8066E5D8
void fn_2_2F544(void) {
    return;
}

// .text:0x0002F710 size:0x194 mapped:0x8066E7A4
void fn_2_2F710(void) {
    return;
}

// .text:0x0002F8A4 size:0x1D8 mapped:0x8066E938
void fn_2_2F8A4(void) {
    return;
}

// .text:0x0002FA7C size:0x150 mapped:0x8066EB10
void fn_2_2FA7C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 3:
    case 4:
        break;
    case 0x11:
        *state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x19;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002FBCC size:0x134 mapped:0x8066EC60
void fn_2_2FBCC(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 3:
    case 4:
        break;
    case 0x11:
        *state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x19;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002FD00 size:0x150 mapped:0x8066ED94
void fn_2_2FD00(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 3:
    case 4:
        break;
    case 0x11:
        *state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0xe;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002FE50 size:0x26C mapped:0x8066EEE4
void fn_2_2FE50(void) {
    return;
}

// .text:0x000300BC size:0x2E0 mapped:0x8066F150
void fn_2_300BC(void) {
    return;
}

// .text:0x0003039C size:0x33C mapped:0x8066F430
void fn_2_3039C(void) {
    return;
}

// .text:0x000306D8 size:0x1BC mapped:0x8066F76C
void fn_2_306D8(void) {
    return;
}

// .text:0x00030894 size:0x3B8 mapped:0x8066F928
void fn_2_30894(void) {
    return;
}

// .text:0x00030C4C size:0x134 mapped:0x8066FCE0
void fn_2_30C4C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 3:
    case 4:
        break;
    case 0x11:
        *state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0xe;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00030D80 size:0x178 mapped:0x8066FE14
void fn_2_30D80(void) {
    return;
}

// .text:0x00030EF8 size:0x1A4 mapped:0x8066FF8C
void fn_2_30EF8(void) {
    return;
}

// .text:0x0003109C size:0x1B4 mapped:0x80670130
void fn_2_3109C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031250 size:0x134 mapped:0x806702E4
void fn_2_31250(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 3:
    case 4:
        break;
    case 0x11:
        *state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0xe;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031384 size:0x1B4 mapped:0x80670418
void fn_2_31384(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031538 size:0x1C0 mapped:0x806705CC
void fn_2_31538(void) {
    return;
}

// .text:0x000316F8 size:0x188 mapped:0x8067078C
void fn_2_316F8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj;
            *((u8 *)graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object + 0x68) = 0;
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031880 size:0x210 mapped:0x80670914
void fn_2_31880(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x316, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        s8 *base = (s8 *)&lbl_2_bss_1A824C[0x190000];
        s8 b1 = base[0x7867];
        s8 b2 = base[b1 + 0x7868];
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, b2 + 0x316);
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x00031A90 size:0x150 mapped:0x80670B24
void fn_2_31A90(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031BE0 size:0x1B4 mapped:0x80670C74
void fn_2_31BE0(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031D94 size:0x1BC mapped:0x80670E28
void fn_2_31D94(void) {
    return;
}

// .text:0x00031F50 size:0x188 mapped:0x80670FE4
void fn_2_31F50(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj;
            *((u8 *)graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object + 0x68) = 0;
            obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x000320D8 size:0x20C mapped:0x8067116C
void fn_2_320D8(void) {
    return;
}

// .text:0x000322E4 size:0x150 mapped:0x80671378
void fn_2_322E4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
            obj->flags &= ~2;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00032434 size:0x1B4 mapped:0x806714C8
void fn_2_32434(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x000325E8 size:0x1EC mapped:0x8067167C
void fn_2_325E8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x30b, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x30b);
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x000327D4 size:0xF0 mapped:0x80671868
void fn_2_327D4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5:
    case 0x25:
        break;
    }
}

// .text:0x000328C4 size:0x1B4 mapped:0x80671958
void fn_2_328C4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00032A78 size:0x1EC mapped:0x80671B0C
void fn_2_32A78(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x30a, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x30a);
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x00032C64 size:0xF0 mapped:0x80671CF8
void fn_2_32C64(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        *state = 0x25;
        break;
    }
    case 5:
    case 0x25:
        break;
    }
}

// .text:0x00032D54 size:0x1B4 mapped:0x80671DE8
void fn_2_32D54(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00032F08 size:0x2C0 mapped:0x80671F9C
void fn_2_32F08(void) {
    return;
}

// .text:0x000331C8 size:0x44C mapped:0x8067225C
void fn_2_331C8(void) {
    return;
}

// .text:0x00033614 size:0x10C mapped:0x806726A8
void fn_2_33614(void) {
    return;
}

// .text:0x00033720 size:0x1B4 mapped:0x806727B4
void fn_2_33720(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags |= 2;
        obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = graphicsRelatedArray[*(u16 *)((u8 *)arg0 + 0x14) + *(s16 *)((u8 *)arg1 + 0xE)].object;
        obj->flags &= ~2;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x000338D4 size:0x59C mapped:0x80672968
void fn_2_338D4(void) {
    return;
}
