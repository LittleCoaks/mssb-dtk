#include "menus/rep_0F60.h"
#include "header_rep_data.h"

typedef struct Rep0F60Obj {
    u8 _00[0x62];
    s16 _62;
    s16 _64;
    s16 _66;
    s16 _68;
    u8 _6A[0x6C - 0x6A];
    s16 _6C;
    u8 _6E[0x25D - 0x6E];
    u8 _25D;
    u8 _25E;
    u8 _25F[0x260 - 0x25F];
    u8 _260;
    u8 _261[0x263 - 0x261];
    u8 _263;
    u8 _264[0x266 - 0x264];
    u8 _266;
    u8 _267[0x26A - 0x267];
    u8 _26A;
    u8 _26B[0x26D - 0x26B];
    u8 _26D;
} Rep0F60Obj;

typedef struct Rep0F60Huge {
    u8 _0000[0x68];
    u8 *unk68;
    u8 _006C[0x2C50 - 0x6C];
    Rep0F60Obj *objects[13];
    u8 _2C84[0x2C88 - 0x2C84];
    u8 *unk2C88;
    u8 *unk2C8C;
    u32 unk2C90;
    u8 _2C94[0x2D94 - 0x2C94];
    u8 *unk2D94;
    u8 _2D98[0x3078 - 0x2D98];
    u16 unk3078;
    u8 _307A;
} Rep0F60Huge;

extern Rep0F60Huge hugeAnimStruct;
extern Rep0F60Huge *lbl_2_bss_340140;

typedef struct Rep0F60ChallengeFile {
    u32 _00;
    u32 _04;
    u32 _08;
    u32 _0C;
} Rep0F60ChallengeFile;

extern Rep0F60ChallengeFile ChallengeMapCharacterFiles[13];
extern void *lbl_2_bss_1A824C;
extern u8 lbl_2_data_3CD0[];
extern u8 lbl_800E869C[];

void setLITLightPtr(void *light);
void *_OSAllocFromHeap(s32 alignment, s32 size);
void *ActorObjectInitTable(s32 count);
void LoadActorLayout(void *a);
void convertGeometryAndSknHeader(void *a, s32 b);
void haveActLayoutPointToGeoHeader(void *a, void *b);
void convertTextureHeader(void *a);
void UpdateTexturePalettePointers(void *a, void *b);
void animateBallRelated(void *table, u16 index, u16 slot, void *data, int anim, int arg5);
void fn_800BD548(void *actor, int mode, ...);
void CTRLSetTranslation(void *control, f32 x, f32 y, f32 z);
void CTRLSetRotation(void *control, f32 x, f32 y, f32 z);

static inline void rep0F60SetupSlots(int slot, int start, int count, int animA, int animB) {
    int i;
    int end = start + count;

    for (i = start; i < end; i++) {
        animateBallRelated(lbl_2_bss_340140->unk68, (u16)i, (u16)i,
                           *(void **)((u8 *)lbl_2_bss_340140 + 0x2DA0 + slot * 0xC), animA, animB);
        *(u8 *)(*(u8 **)(lbl_2_bss_340140->unk68 + 0x34 + i * 0x90) + 0x99) = 1;
        fn_800BD548(lbl_2_bss_340140->unk68 + 0x34 + i * 0x90, 4,
                    *(int *)((u8 *)lbl_2_bss_340140 + 0xAC), *(int *)((u8 *)lbl_2_bss_340140 + 0xB0),
                    *(int *)((u8 *)lbl_2_bss_340140 + 0xB4), *(int *)((u8 *)lbl_2_bss_340140 + 0xB8));
        CTRLSetTranslation(lbl_2_bss_340140->unk68 + 0x44 + i * 0x90, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(lbl_2_bss_340140->unk68 + 0x44 + i * 0x90, 0.0f, 0.0f, 0.0f);
    }
}

// .text:0x0008ACE0 size:0x200 mapped:0x806C9D74
void fn_2_8ACE0(void) {
    return;
}

// .text:0x0008AEE0 size:0x238 mapped:0x806C9F74
void fn_2_8AEE0(void) {
    return;
}

// .text:0x0008B118 size:0x40 mapped:0x806CA1AC
void fn_2_8B118(f32 x) {
    if (x != 0.0f) {
        lbl_2_bss_340140->_307A = 3;
    } else {
        lbl_2_bss_340140->_307A = 0;
    }
}

// .text:0x0008B158 size:0x168 mapped:0x806CA1EC
void fn_2_8B158(void) {
    s32 i;

    lbl_2_bss_340140->unk3078 = 4;
    lbl_2_bss_340140->unk2D94 = _OSAllocFromHeap(32, lbl_2_bss_340140->unk3078 * 0x28);
    lbl_2_bss_340140->unk68 = ActorObjectInitTable(lbl_2_bss_340140->unk3078);
    for (i = 0; i < lbl_2_bss_340140->unk3078; i++) {
        rep0F60SetupSlots(i, i, 1, 0, 0);
    }
}

// .text:0x0008B2C0 size:0x158 mapped:0x806CA354
void fn_2_8B2C0(void) {
    s32 i;
    s32 k;
    u8 *base;

    lbl_2_bss_340140->unk3078 = 0;
    base = *(u8 **)((u8 *)lbl_2_bss_340140 + 0x2D9C);
    for (k = 0; k < 12; k++) {
        *(u8 **)((u8 *)lbl_2_bss_340140 + 0x2DA0 + k * 4) = base + *(u32 *)(base + k * 4);
    }
    for (i = 0; i < 4; i++) {
        u8 *a = *(u8 **)((u8 *)lbl_2_bss_340140 + 0x2DA0 + i * 0xC);
        u8 *b = *(u8 **)((u8 *)lbl_2_bss_340140 + 0x2DA4 + i * 0xC);
        u8 *c = *(u8 **)((u8 *)lbl_2_bss_340140 + 0x2DA8 + i * 0xC);

        LoadActorLayout(a);
        convertGeometryAndSknHeader(b, 0);
        haveActLayoutPointToGeoHeader(a, b);
        convertTextureHeader(c);
        UpdateTexturePalettePointers(b, c);
    }
}

// .text:0x0008B418 size:0x130C mapped:0x806CA4AC
void fn_2_8B418(void) {
    return;
}

// .text:0x0008C724 size:0xE8 mapped:0x806CB7B8
void fn_2_8C724(void) {
    int i;

    for (i = 0; i < lbl_2_bss_340140->unk3078; i++) {
        *(f32 *)(lbl_2_bss_340140->unk2D94 + i * 0x28 + 0x04) = 0.0f;
        *(f32 *)(lbl_2_bss_340140->unk2D94 + i * 0x28 + 0x08) = 0.0f;
        *(f32 *)(lbl_2_bss_340140->unk2D94 + i * 0x28 + 0x0C) = 0.0f;
        *(f32 *)(lbl_2_bss_340140->unk2D94 + i * 0x28 + 0x10) = 0.0f;
        *(f32 *)(lbl_2_bss_340140->unk2D94 + i * 0x28 + 0x14) = 0.0f;
        *(f32 *)(lbl_2_bss_340140->unk2D94 + i * 0x28 + 0x18) = 0.0f;
        (lbl_2_bss_340140->unk2D94 + i * 0x28)[0x26] = 0;
        *(void **)(lbl_2_bss_340140->unk2D94 + i * 0x28) = NULL;
        lbl_2_bss_340140->unk68[i * 0x90 + 0xA0] = 0;
    }
}

// .text:0x0008C80C size:0x104 mapped:0x806CB8A0
void fn_2_8C80C(int slot, int start, int count, int animA, int animB) {
    rep0F60SetupSlots(slot, start, count, animA, animB);
}

// .text:0x0008C910 size:0x378 mapped:0x806CB9A4
void fn_2_8C910(void) {
    return;
}

// .text:0x0008CC88 size:0x24 mapped:0x806CBD1C
BOOL fn_2_8CC88(int slot) {
    return hugeAnimStruct.objects[slot]->_68 == 0;
}

// .text:0x0008CCAC size:0x20 mapped:0x806CBD40
void fn_2_8CCAC(int idx, u8 val) {
    u8 *rec = (u8 *)lbl_2_bss_340140 + idx * 0x27C + 0xC04;

    if (rec != NULL) {
        rec[0x25D] = val;
    }
}

// .text:0x0008CCCC size:0x8C mapped:0x806CBD60
void fn_2_8CCCC(int slot, int a, u8 b, u8 mode, u8 c, s16 e, u8 f, int g) {
    Rep0F60Obj *obj = lbl_2_bss_340140->objects[slot];

    if (obj == NULL) {
        return;
    }
    if (mode == 1 && obj->_62 == a) {
        return;
    }
    if (mode == 3) {
        mode = 1;
        obj->_64 = a;
    }
    obj->_6C = e;
    obj->_260 = b;
    obj->_25E = mode;
    obj->_263 = c;
    obj->_266 = f;
    obj->_26D = 0;
    if (g == -1) {
        obj->_26A = 5;
    } else {
        obj->_26A = g;
    }
    obj->_66 = -1;
}

// .text:0x0008CD58 size:0x2CC mapped:0x806CBDEC
void fn_2_8CD58(void) {
    return;
}

// .text:0x0008D024 size:0x228 mapped:0x806CC0B8
void fn_2_8D024(void) {
    return;
}

// .text:0x0008D24C size:0x24 mapped:0x806CC2E0
void fn_2_8D24C(void *obj) {
    setLITLightPtr(*(void **)((u8 *)obj + 0x70));
}

// .text:0x0008D270 size:0x76C mapped:0x806CC304
void fn_2_8D270(u8 idx) {
    return;
}

// .text:0x0008D9DC size:0x138 mapped:0x806CCA70
void fn_2_8D9DC(s32 mode) {
    s32 i;
    s32 count = *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746);

    for (i = 0; i < count; i++) {
        u8 *obj;

        lbl_2_bss_340140->objects[i] = (Rep0F60Obj *)((u8 *)&hugeAnimStruct + 0xC04 + i * 0x27C);
        obj = (u8 *)lbl_2_bss_340140->objects[i];
        obj[0x255] = i;
        obj[0x254] = i;
        switch (mode) {
        case 0:
            obj[0x252] = lbl_2_data_3CD0[i];
            break;
        case 1:
            obj[0x252] = lbl_800E869C[*(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197706)];
            fn_2_8D270((u8)i);
            break;
        case 2:
            obj[0x252] = 0x1C;
            break;
        }
    }
}

// .text:0x0008DB14 size:0xEC mapped:0x806CCBA8
void fn_2_8DB14(void) {
    return;
}

// .text:0x0008DC00 size:0xD8 mapped:0x806CCC94
void fn_2_8DC00(void) {
    return;
}

// .text:0x0008DCD8 size:0x2D8 mapped:0x806CCD6C
void fn_2_8DCD8(void) {
    return;
}

// .text:0x0008DFB0 size:0x4C8 mapped:0x806CD044
void fn_2_8DFB0(void) {
    return;
}

// .text:0x0008E478 size:0x22C mapped:0x806CD50C
void fn_2_8E478(void) {
    return;
}

// .text:0x0008E6A4 size:0x200 mapped:0x806CD738
void fn_2_8E6A4(void) {
    return;
}

// .text:0x0008E8A4 size:0x1DC mapped:0x806CD938
void fn_2_8E8A4(void) {
    return;
}

// .text:0x0008EA80 size:0x2CC mapped:0x806CDB14
void fn_2_8EA80(void) {
    return;
}
