#include "menus/rep_0F60.h"
#include "header_rep_data.h"

typedef struct Rep0F60Obj {
    u8 _00[0x8];
    void *_08;
    u8 _0C[0x10 - 0xC];
    void *_10;
    u8 _14[0x2C - 0x14];
    void *_2C;
    void *_30;
    u8 _34[0x4C - 0x34];
    f32 _4C;
    u8 _50[0x60 - 0x50];
    s16 _60;
    s16 _62;
    s16 _64;
    s16 _66;
    s16 _68;
    s16 _6A;
    s16 _6C;
    s16 _6E;
    u8 _70[0x16A - 0x70];
    u16 _16A;
    u8 _16C[0x252 - 0x16C];
    u8 _252;
    u8 _253;
    u8 _254;
    u8 _255;
    u8 _256[0x25D - 0x256];
    u8 _25D;
    u8 _25E;
    u8 _25F;
    u8 _260;
    u8 _261;
    u8 _262;
    u8 _263;
    u8 _264;
    u8 _265;
    u8 _266;
    u8 _267;
    u8 _268;
    u8 _269;
    u8 _26A;
    u8 _26B;
    u8 _26C;
    u8 _26D;
    u8 _26E;
    u8 _26F;
    u8 _270[0x27C - 0x270];
} Rep0F60Obj;

typedef struct Rep0F60Slot {
    void *layout;
    void *geometry;
    void *texture;
} Rep0F60Slot;

typedef struct Rep0F60Huge {
    u8 _0000[0x68];
    u8 *unk68;
    u8 _006C[0xC04 - 0x6C];
    Rep0F60Obj records[13];
    Rep0F60Obj *objects[13];
    u8 _2C84[0x2C88 - 0x2C84];
    u8 *unk2C88;
    u8 *unk2C8C;
    u32 unk2C90;
    u8 _2C94[0x2D6A - 0x2C94];
    s8 unk2D6A[0x2D94 - 0x2D6A];
    u8 *unk2D94;
    u8 _2D98[0x2D9C - 0x2D98];
    u8 *unk2D9C;
    Rep0F60Slot slots[19];
    u8 _2E84[0x3078 - 0x2E84];
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
extern u8 lbl_2_data_2FA60[];
extern u32 lbl_2_data_2FDC0[];

void setLITLightPtr(void *light);
void *_OSAllocFromHeap(s32 alignment, s32 size);
void *ActorObjectInitTable(s32 count);
void LoadActorLayout(void *a);
void convertGeometryAndSknHeader(void *a, s32 b);
void haveActLayoutPointToGeoHeader(void *a, void *b);
void convertTextureHeader(void *a);
void UpdateTexturePalettePointers(void *a, void *b);
void animateBallRelated(void *table, u16 index, u16 slot, void *data, int anim, int arg5);
void *ARAMTransfer(void *file, s32 arg1, s32 arg2, s32 arg3);
void removeCurrentDrawingItem(void);
void fn_2_4E824(void);
void fn_80052D70(void);
void fn_2_48DB4(void);
void fn_2_93C64(void);
extern void *currentDrawingItem;
extern s8 lbl_803C6CF8[];
extern u8 lbl_80366158[];
extern u8 highLevelSimulationFlag;
extern u8 challengeMapModelsFileDescriptor[];
extern u8 cupModelsFileDescriptorChallengeMap[];
extern u8 lbl_2_data_2FE7C[];
void *memset(void *dst, s32 value, u32 size);
void characterAndBallDisplayRelated(void *actor, s32 a, u8 idx, void *b, void *c, void *d);
void callDSInsertListObject(void *actor, u16 value);
void fn_800B2BA8(void *actor, u16 bone, s32 a, s32 b);
void setHandModelAttached(s32 idx, s32 hand, s32 flag);
void adjustInternalPointers(void *p);
void fn_80014990(s32 idx, void *a, void *b);
void ACTActorRelated(void *a, void *b);
void fn_800B2C08(void *a, u16 b);
void initShortsHandleCompressedDiskReads(void *rec);
void fn_800126EC(void *dst, void *src, void *tbl);
void fn_800638B4(void *rec, void *actor);
void fn_80063010(void *rec, void *actor);
void fn_8004B7B4(void *rec, void *actor);
void fn_800637BC(void *rec, void *actor);
void fn_800637D4(void *rec, void *actor);
void fn_80052634(void *rec, void *actor);
void fn_80062ED4(void *rec, void *actor);
void initSpecialHandBones(void *rec, void *actor);
extern u32 lbl_2_data_2FE84[];
extern u32 lbl_2_data_2FEAC[];
void initActorArray(void);
void ANIMGet(void *anim);
void fn_80014204(s32 count);
void *fn_80023AA4(void);
extern void *lbl_2_bss_1A8248;
void fn_2_94854(s32 a);
void fn_2_9461C(s32 a);
void fn_2_94604(s32 a);
void fn_2_94634(s32 a);
void fn_800B2B54(void *actor, u16 bone, s32 mode);
void fn_800B2B4C(void *actor, f32 value);
void actorRelated(void *a, u32 b, u32 c);
void fn_8001B5EC(s32 slot, u8 value);
void fn_8001B308(s32 slot, u8 value);
extern u8 lbl_2_bss_1A81D4[];
u8 *fn_80052768_getCamera(s32 idx);
void PSMTXCopy(void *src, void *dst);
void fn_2_190DC(void *a, void *b);
void *getAnimObjectActor(void *obj);
f32 getActorBoneAnimTime(void *actor, u16 bone);
typedef struct Rep0F60AnimSet {
    u8 _00[0x10];
    void *anims10[7];
    void *anims2C[2];
    void *anims34[7];
    u8 unk50[0x1D];
} Rep0F60AnimSet;

extern Rep0F60AnimSet lbl_2_bss_3401C0;
extern Rep0F60AnimSet *lbl_2_bss_3401BC;
extern f32 lbl_2_bss_B2B8;
extern f32 lbl_2_data_2FEE0[3];
extern f32 lbl_2_data_2FED4[3];
void *memcpy(void *dst, const void *src, u32 size);
void PSVECSubtract(f32 *a, f32 *b, f32 *out);
f32 fn_2_4A1E8(f32 x);
void fn_800BD548(void *actor, int mode, ...);
void CTRLSetTranslation(void *control, f32 x, f32 y, f32 z);
void CTRLSetRotation(void *control, f32 x, f32 y, f32 z);


// .text:0x0008EA80 size:0x2CC mapped:0x806CDB14
void fn_2_8EA80(void) {
    s32 i;
    u8 *item = (u8 *)currentDrawingItem;

    switch ((s8)item[0x28]) {
    case 0:
        lbl_2_bss_340140 = (Rep0F60Huge *)&hugeAnimStruct;
        lbl_2_bss_3401BC = &lbl_2_bss_3401C0;
        *(s16 *)(item + 0x14) = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_8DCD8();
        fn_2_48DB4();
        fn_2_93C64();
        item[0x28] = 1;
        break;
    case 1:
        lbl_2_bss_340140->records[*(s16 *)(item + 0x14)]._08 = ARAMTransfer(&ChallengeMapCharacterFiles[*((u8 *)lbl_2_bss_1A8248 + 0x441C)], 0, 0, 0);
        *(s16 *)(item + 0x14) += 1;
        item[0x28] = 2;
        break;
    case 2:
        if (lbl_803C6CF8[0x715] == 1) {
            item[0x28] = 3;
        }
        break;
    case 3:
        lbl_2_bss_340140->records[*(s16 *)(item + 0x14)]._08 = ARAMTransfer(&ChallengeMapCharacterFiles[*(s16 *)(item + 0x14) + 5], 0, 0, 0);
        *(s16 *)(item + 0x14) += 1;
        item[0x28] = 4;
        break;
    case 4:
        if (lbl_803C6CF8[0x715] == 1) {
            if (*(s16 *)(item + 0x14) == *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746)) {
                item[0x28] = 5;
            } else {
                item[0x28] = 3;
            }
        }
        break;
    case 5:
        for (i = 0; i < *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746); i++) {
            lbl_2_bss_340140->objects[i] = &hugeAnimStruct.records[i];
            lbl_2_bss_340140->objects[i]->_255 = i;
            lbl_2_bss_340140->objects[i]->_254 = i;
            lbl_2_bss_340140->objects[i]->_252 = lbl_2_data_3CD0[i];
            fn_2_8D270((u8)i);
        }
        item[0x28] = 6;
        break;
    case 6:
        item[0x28] = 7;
        break;
    case 7:
        fn_2_94854(0xB);
        fn_2_9461C(0);
        fn_2_94604(0);
        fn_2_94634(1);
        fn_2_93C64();
        lbl_2_bss_340140->_307A = 2;
        *(s16 *)(*(u8 **)((u8 *)currentDrawingItem + 0x0C) + 0x10) = 1;
        removeCurrentDrawingItem();
        item[0x28] = 0;
        break;
    }
}

// .text:0x0008E8A4 size:0x1DC mapped:0x806CD938
void fn_2_8E8A4(void) {
    s32 i;
    u8 *item = (u8 *)currentDrawingItem;

    switch ((s8)item[0x28]) {
    case 0:
        lbl_2_bss_340140 = (Rep0F60Huge *)&hugeAnimStruct;
        *(s16 *)(item + 0x14) = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_8DCD8();
        fn_2_48DB4();
        fn_2_93C64();
        item[0x28] = 1;
        break;
    case 1:
        lbl_2_bss_340140->records[*(s16 *)(item + 0x14)]._08 = ARAMTransfer(&ChallengeMapCharacterFiles[*(s16 *)(item + 0x16)], 0, 0, 0);
        *(s16 *)(item + 0x14) += 1;
        item[0x28] = 2;
        break;
    case 2:
        if (lbl_803C6CF8[0x715] == 1) {
            item[0x28] = 5;
        }
        break;
    case 5:
        for (i = 0; i < *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746); i++) {
            lbl_2_bss_340140->objects[i] = &hugeAnimStruct.records[i];
            lbl_2_bss_340140->objects[i]->_255 = i;
            lbl_2_bss_340140->objects[i]->_254 = i;
            lbl_2_bss_340140->objects[i]->_252 = 0x1C;
            fn_2_8D270((u8)i);
        }
        item[0x28] = 6;
        break;
    case 6:
        lbl_2_bss_340140->_307A = 2;
        *(s16 *)(*(u8 **)((u8 *)currentDrawingItem + 0x0C) + 0x10) = 1;
        removeCurrentDrawingItem();
        item[0x28] = 0;
        break;
    }
}

// .text:0x0008E6A4 size:0x200 mapped:0x806CD738
void fn_2_8E6A4(void) {
    s32 i;
    u8 *item = (u8 *)currentDrawingItem;

    switch ((s8)item[0x28]) {
    case 0:
        lbl_2_bss_340140 = (Rep0F60Huge *)&hugeAnimStruct;
        *(s16 *)(item + 0x14) = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_8DCD8();
        fn_2_48DB4();
        fn_2_93C64();
        item[0x28] = 1;
        break;
    case 1:
        lbl_2_bss_340140->records[*(s16 *)(item + 0x14)]._08 = ARAMTransfer(lbl_2_data_2FA60 + lbl_2_data_2FDC0[*(s16 *)(item + 0x16)] * 0x10, 0, 0, 0);
        *(s16 *)(item + 0x14) += 1;
        item[0x28] = 2;
        break;
    case 2:
        if (lbl_803C6CF8[0x715] == 1) {
            item[0x28] = 5;
        }
        break;
    case 5:
        for (i = 0; i < *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746); i++) {
            lbl_2_bss_340140->objects[i] = &hugeAnimStruct.records[i];
            lbl_2_bss_340140->objects[i]->_255 = i;
            lbl_2_bss_340140->objects[i]->_254 = i;
            lbl_2_bss_340140->objects[i]->_252 = lbl_800E869C[*(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197706)];
            fn_2_8D270((u8)i);
        }
        item[0x28] = 6;
        break;
    case 6:
        lbl_2_bss_340140->_307A = 2;
        *(s16 *)(*(u8 **)((u8 *)currentDrawingItem + 0x0C) + 0x10) = 1;
        removeCurrentDrawingItem();
        item[0x28] = 0;
        break;
    }
}

// .text:0x0008E478 size:0x22C mapped:0x806CD50C
void fn_2_8E478(void) {
    u8 *item = (u8 *)currentDrawingItem;

    switch ((s8)item[0x28]) {
    case 0:
        lbl_2_bss_340140 = (Rep0F60Huge *)&hugeAnimStruct;
        *(s16 *)(item + 0x14) = 0;
        item[0x28] = 1;
        break;
    case 1:
        lbl_2_bss_340140->unk2D9C = ARAMTransfer(challengeMapModelsFileDescriptor, 0, 0, 0);
        *(s16 *)(item + 0x14) += 1;
        item[0x28] = 2;
        break;
    case 2:
        if (lbl_803C6CF8[0x715] == 1) {
            item[0x28] = 5;
        }
        break;
    case 5:
        fn_2_8C910();
        item[0x28] = 6;
        break;
    case 6:
        fn_2_8B418();
        fn_2_8C724();
        fn_80052D70();
        *((u8 *)lbl_2_bss_1A824C + 0x1978F3) = 1;
        lbl_2_bss_340140->_307A = 4;
        *(s16 *)(*(u8 **)((u8 *)currentDrawingItem + 0x0C) + 0x10) = 1;
        removeCurrentDrawingItem();
        item[0x28] = 0;
        break;
    }
}

// .text:0x0008DFB0 size:0x4C8 mapped:0x806CD044
void fn_2_8DFB0(void) {
    u8 *item = (u8 *)currentDrawingItem;

    switch ((s8)item[0x28]) {
    case 0:
        lbl_2_bss_340140 = (Rep0F60Huge *)&hugeAnimStruct;
        *(s16 *)(item + 0x14) = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_48DB4();
        fn_2_93C64();
        item[0x28] = 1;
        break;
    case 1:
        *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746) = 0;
        lbl_2_bss_340140->unk2D9C = ARAMTransfer(cupModelsFileDescriptorChallengeMap, 0, 0, 0);
        *(s16 *)(item + 0x14) += 1;
        item[0x28] = 2;
        break;
    case 2:
        if (lbl_803C6CF8[0x715] == 1) {
            item[0x28] = 5;
        }
        break;
    case 5:
        fn_2_8B2C0();
        item[0x28] = 6;
        break;
    case 6:
        fn_2_8B158();
        fn_2_8C724();
        fn_80052D70();
        item[0x28] = 7;
        break;
    case 7:
        item[0x28] = 8;
        break;
    case 8:
        lbl_2_bss_340140->_307A = 3;
        item[0x28] = 9;
        break;
    case 9:
        item[0x28] = 10;
        break;
    case 10:
        lbl_2_bss_340140->_307A = 3;
        *(s16 *)(*(u8 **)((u8 *)currentDrawingItem + 0x0C) + 0x10) = 1;
        removeCurrentDrawingItem();
        item[0x28] = 0;
        break;
    }
}

// .text:0x0008DCD8 size:0x2D8 mapped:0x806CCD6C
#pragma dont_inline on
void fn_2_8DCD8(void) {
    s32 i;

    fn_2_8DC00();
    fn_2_8DB14();

    initActorArray();
    fn_80014204(*(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746));
    *(void **)((u8 *)lbl_2_bss_340140 + 0x13C) = fn_80023AA4();

    for (i = 0; i < *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746); i++) {
        *((u8 *)lbl_2_bss_340140 + 0xE59 + i * 0x27C) = i;
        lbl_2_bss_340140->objects[i] = NULL;
        lbl_2_bss_340140->unk2D6A[i] = -1;
        *((s8 *)lbl_2_bss_340140 + 0xE5B + i * 0x27C) = -1;
    }

    for (i = 0; i < 9; i++) {
        *((s8 *)lbl_2_bss_340140 + 0x2D7F + i) = -1;
    }
    for (i = 0; i < 4; i++) {
        *((s8 *)lbl_2_bss_340140 + 0x2D89 + i) = -1;
    }
    *((u8 *)lbl_2_bss_340140 + 0x2D77) = 0;
    *((u8 *)lbl_2_bss_340140 + 0x2D7B) = 0;
}
#pragma dont_inline reset

// .text:0x0008DC00 size:0xD8 mapped:0x806CCC94
void fn_2_8DC00(void) {
    s32 i;
    u32 max = 0;
    s32 stride;

    for (i = 0; i < 13; i++) {
        u32 v = ChallengeMapCharacterFiles[i]._04 & 0x0FFFFFFF;

        if (max < v) {
            max = v;
        }
    }
    stride = (max + 0x1F) & ~0x1F;
    lbl_2_bss_340140->unk2C8C = _OSAllocFromHeap(32, stride * *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746));
    for (i = 0; i < *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746); i++) {
        *(u8 **)((u8 *)lbl_2_bss_340140 + 0xC0C + i * 0x27C) = lbl_2_bss_340140->unk2C8C + i * stride;
    }
}

// .text:0x0008DB14 size:0xEC mapped:0x806CCBA8
void fn_2_8DB14(void) {
    s32 i;
    u32 max = 0;
    u32 stride;

    for (i = 0; i < *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746); i++) {
        u32 v = ChallengeMapCharacterFiles[i]._04 & 0x0FFFFFFF;

        if (max < v) {
            max = v;
        }
    }
    stride = (max + 0x1F) & ~0x1F;
    lbl_2_bss_340140->unk2C90 = stride;
    lbl_2_bss_340140->unk2C88 = _OSAllocFromHeap(32, stride * *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746));
    for (i = 0; i < *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746); i++) {
        *(u32 *)((u8 *)lbl_2_bss_340140 + 0xC14 + i * 0x27C) = 0;
    }
}

// .text:0x0008D9DC size:0x138 mapped:0x806CCA70
void fn_2_8D9DC(s32 mode) {
    s32 i;

    for (i = 0; i < *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746); i++) {
        lbl_2_bss_340140->objects[i] = &hugeAnimStruct.records[i];
        lbl_2_bss_340140->objects[i]->_255 = i;
        lbl_2_bss_340140->objects[i]->_254 = i;
        switch (mode) {
        case 0:
            lbl_2_bss_340140->objects[i]->_252 = lbl_2_data_3CD0[i];
            break;
        case 2:
            lbl_2_bss_340140->objects[i]->_252 = 0x1C;
            break;
        case 1:
            lbl_2_bss_340140->objects[i]->_252 = lbl_800E869C[*(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197706)];
            fn_2_8D270((u8)i);
            break;
        }
    }
}

// .text:0x0008D270 size:0x76C mapped:0x806CC304
void fn_2_8D270(u8 idx) {
    u8 *rec = (u8 *)lbl_2_bss_340140 + idx * 0x27C + 0xC04;
    u8 *actor = getAnimObjectActor(rec);
    u32 *tbl = *(u32 **)(rec + 0x8);
    u8 *slot;
    u8 *layout;
    u16 count;
    s32 n;
    s32 handA;
    s32 handB;

    for (n = 0; n < 20; n++) {
        if (tbl[n] == 0) {
            break;
        }
        tbl[n] = (u32)tbl + tbl[n];
    }

    convertTextureHeader((void *)tbl[0]);
    if (tbl[1] != 0) {
        LoadActorLayout((void *)tbl[1]);
        convertGeometryAndSknHeader((void *)tbl[2], (s32)tbl[3]);
        haveActLayoutPointToGeoHeader((void *)tbl[1], (void *)tbl[2]);
        UpdateTexturePalettePointers((void *)tbl[2], (void *)tbl[0]);
    }
    *(u32 *)(rec + 0x10) = tbl[4];
    ANIMGet((void *)tbl[4]);
    characterAndBallDisplayRelated(actor, (s8)rec[0x255], idx, (void *)tbl[1], (void *)tbl[4], (void *)tbl[3]);

    slot = *(u8 **)((u8 *)lbl_2_bss_340140 + 0x60) + idx * 0x90 + 0x34;
    layout = *(u8 **)slot;
    memset(rec + 0x162, 0xFF, 0xF0);
    count = *(u16 *)(layout + 6);
    for (n = 0; n < count; n++) {
        u16 v = *(u16 *)(*(u8 **)(layout + 0x18) + n * 4);

        if (v != 0xFFFF) {
            *(s16 *)(rec + 0x162 + v * 2) = n;
        }
    }

    callDSInsertListObject(*(void **)actor, *(u16 *)(rec + 0x188));
    callDSInsertListObject(*(void **)actor, *(u16 *)(rec + 0x194));
    callDSInsertListObject(*(void **)actor, *(u16 *)(rec + 0x1AA));
    *(void **)rec = *(void **)actor;
    if (*(u16 *)(rec + 0x168) != 0xFFFF) {
        fn_800B2B54(*(void **)rec, *(u16 *)(rec + 0x168), 13);
    }
    fn_800BD548(actor, 4, *(s32 *)((u8 *)lbl_2_bss_340140 + 0xAC), *(s32 *)((u8 *)lbl_2_bss_340140 + 0xB0),
                *(s32 *)((u8 *)lbl_2_bss_340140 + 0xB4), *(s32 *)((u8 *)lbl_2_bss_340140 + 0xB8));
    *(f32 *)(rec + 0x48) = 0.0f;
    *(f32 *)(rec + 0x44) = 0.0f;
    *(f32 *)(rec + 0x40) = 0.0f;
    CTRLSetTranslation(actor + 0x10, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(actor + 0x10, 0.0f, 0.0f, 0.0f);
    *(f32 *)(actor + 0x54) = 0.5f;
    actor[0x5A] = 1;

    if (*(u16 *)(rec + 0x168) != 0xFFFF) {
        fn_800B2BA8(*(void **)actor, *(u16 *)(rec + 0x168), 0, 0);
        (*(u8 **)(*(u8 **)(*(u8 **)actor + 0x18) + *(u16 *)(rec + 0x168) * 4))[0x136] = 1;
    }
    if (*(u16 *)(rec + 0x166) != 0xFFFF) {
        fn_800B2BA8(*(void **)actor, *(u16 *)(rec + 0x166), 0, 0);
        (*(u8 **)(*(u8 **)(*(u8 **)actor + 0x18) + *(u16 *)(rec + 0x166) * 4))[0x136] = 1;
    }
    if (*(u16 *)(rec + 0x164) != 0xFFFF) {
        fn_800B2BA8(*(void **)actor, *(u16 *)(rec + 0x164), 0, 0);
        (*(u8 **)(*(u8 **)(*(u8 **)actor + 0x18) + *(u16 *)(rec + 0x164) * 4))[0x136] = 1;
    }
    if (*(u16 *)(rec + 0x1AA) != 0xFFFF) {
        fn_800B2BA8(*(void **)actor, *(u16 *)(rec + 0x1AA), 0, 0);
    }
    if (*(u16 *)(rec + 0x1BE) != 0xFFFF) {
        fn_800B2BA8(*(void **)actor, *(u16 *)(rec + 0x1BE), 0, 0);
        (*(u8 **)(*(u8 **)(*(u8 **)actor + 0x18) + *(u16 *)(rec + 0x1BE) * 4))[0x136] = 1;
    }

    if (tbl[5] != 0) {
        u8 *dst = (u8 *)lbl_2_bss_340140 + (s8)rec[0x255] * 0xD4 + 0x140;

        *(u8 **)(rec + 0x30) = (u8 *)lbl_2_bss_340140 + idx * 0xD4 + 0x140;
        *(u32 *)dst = (u32)tbl;
        fn_800126EC(dst, (void *)tbl[0], lbl_2_data_2FE7C);
        *(u32 *)(dst + 0x64) = (u32)tbl;
        fn_800126EC(dst + 0x64, (void *)tbl[0], lbl_2_data_2FE7C + 4);
    }

    if ((s8)rec[0x252] == 0x12) {
        handA = 4;
        handB = 5;
    } else if ((s8)rec[0x252] == 0x26) {
        handA = 2;
        handB = 3;
    } else if ((s8)rec[0x252] == 0x28 || (s8)rec[0x252] == 0x29) {
        handA = 6;
        handB = 7;
    } else {
        handA = 1;
        handB = 0;
    }
    setHandModelAttached(idx, handA, 1);
    setHandModelAttached(idx, handB, 1);
    *(void **)(rec + 0x2C) = NULL;

    if (tbl[13] != 0 && tbl[14] != 0) {
        adjustInternalPointers((void *)tbl[13]);
        fn_80014990(idx, (void *)tbl[13], (void *)tbl[14]);
        ACTActorRelated((void *)tbl[13], actor);
    }

    *(u8 *)(*(u8 **)(rec + 0x30) + 0xCC) = 1;
    *(f32 *)(*(u8 **)(rec + 0x30) + 0x78) = 0.5f;
    *(f32 *)(*(u8 **)(rec + 0x30) + 0x14) = 0.5f;
    fn_800B2C08(*(void **)actor, *(u16 *)(rec + 0x16A));
    initShortsHandleCompressedDiskReads(rec);
    *(void **)(actor + 0x8) = (void *)fn_2_8D24C;

    for (n = 0; n < 8; n++) {
        *(s16 *)(rec + 0x60 + n * 2) = -1;
    }
    rec[0x25D] = 0;
    rec[0x25E] = 0;
    rec[0x25F] = 0;
    rec[0x260] = 0;
    rec[0x261] = 0;
    rec[0x262] = 1;
    rec[0x263] = 1;
    rec[0x264] = 1;
    rec[0x265] = 0;
    rec[0x266] = 0;
    rec[0x267] = 0;
    rec[0x268] = 0;
    rec[0x269] = 0;
    rec[0x26A] = 0;
    rec[0x26B] = 0;
    rec[0x26C] = 0;
    rec[0x26D] = 0;
    rec[0x26E] = 0;
    rec[0x270] = 0;
    rec[0x271] = 0;
    rec[0x272] = 0;
    rec[0x273] = 0;
    rec[0x277] = 0xFF;
    *(u32 *)(rec + 0x5C) = 0;
    *(f32 *)(rec + 0x4C) = 0.5f;

    switch (rec[0x252]) {
    case 2:
        fn_800638B4(rec, actor);
        break;
    case 6:
    case 10:
    case 12:
    case 24:
    case 25:
    case 26:
    case 42:
        *(u8 *)(*(u8 **)actor + 0x99) = 1;
        break;
    case 14:
    case 37:
        fn_80052634(rec, actor);
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        fn_80062ED4(rec, actor);
        break;
    case 18:
    case 40:
        initSpecialHandBones(rec, actor);
        break;
    case 19:
        fn_8004B7B4(rec, actor);
        break;
    case 20:
    case 43:
        fn_800637BC(rec, actor);
        break;
    case 33:
    case 34:
    case 35:
    case 36:
        fn_80063010(rec, actor);
        break;
    case 38:
        *(u8 *)(*(u8 **)actor + 0x99) = 1;
        initSpecialHandBones(rec, actor);
        break;
    case 41:
        fn_800637D4(rec, actor);
        initSpecialHandBones(rec, actor);
        break;
    }

    fn_2_8CD58(idx, 0, 1, 1, 0, 0, 0);
}

// .text:0x0008D24C size:0x24 mapped:0x806CC2E0
void fn_2_8D24C(void *obj) {
    setLITLightPtr(*(void **)((u8 *)obj + 0x70));
}

// .text:0x0008D024 size:0x228 mapped:0x806CC0B8
void fn_2_8D024(void) {
    Rep0F60Obj *obj;
    s32 i;
    s32 boneIdx;
    f32 time;

    for (i = 0; i < *(s16 *)((u8 *)lbl_2_bss_1A824C + 0x197746); i++) {
        obj = lbl_2_bss_340140->objects[i];
        if (obj == NULL || obj->_25D == 0) {
            continue;
        }
        if (obj->_6A < 0x258 && lbl_80366158[0x28] == 0 && highLevelSimulationFlag == 0 && obj->_26F == 0) {
            obj->_6A++;
        }
        time = 1.0f;
        if (hugeAnimStruct.objects[i] != NULL) {
            boneIdx = hugeAnimStruct.objects[i]->_16A;
        } else {
            boneIdx = 0xFFFF;
        }
        if (boneIdx != 0xFFFF) {
            time = getActorBoneAnimTime(*(void **)getAnimObjectActor(obj), boneIdx);
        }
        obj->_68 = time / obj->_4C;

        if (obj->_25E == 1 || (obj->_25E == 2 && obj->_68 == 0 && obj->_6A > 1) || obj->_62 == -1) {
            if (obj->_64 >= 0) {
                fn_2_8CD58(i, obj->_64, obj->_260, obj->_263, obj->_6C, obj->_266, obj->_26A);
                obj->_60 = obj->_62;
                obj->_62 = obj->_64;
                obj->_64 = -1;
                obj->_25F = obj->_260;
                obj->_262 = obj->_263;
                obj->_265 = obj->_266;
                obj->_269 = obj->_26A;
                obj->_26C = obj->_26D;
                obj->_6A = 0;
                if (obj->_66 >= 0) {
                    obj->_64 = obj->_66;
                    obj->_6C = obj->_6E;
                    obj->_260 = obj->_261;
                    obj->_263 = obj->_264;
                    obj->_25E = 2;
                    obj->_266 = obj->_267;
                    obj->_26A = obj->_26B;
                    obj->_26D = obj->_26E;
                    obj->_66 = -1;
                    continue;
                }
            }
            obj->_25E = 0;
        }
    }
}

// .text:0x0008CD58 size:0x2CC mapped:0x806CBDEC
void fn_2_8CD58(int slot, int a, u8 b, int c, s16 d, int e, u8 f) {
    Rep0F60Obj *obj = lbl_2_bss_340140->objects[slot];
    u32 tableA;
    u32 tableB;
    u8 *actor;
    f32 scale = 0.0f;
    u16 bone;
    void *anim;

    if (slot == 4) {
        tableA = 1;
        tableB = 0;
    } else {
        tableA = lbl_2_data_2FE84[a];
        tableB = lbl_2_data_2FEAC[a];
    }
    if (obj == NULL) {
        return;
    }
    actor = getAnimObjectActor(obj);
    if (f != 0) {
        scale = 1.0f / (f32)f;
    }
    if (obj->_26C == 0) {
        bone = (hugeAnimStruct.objects[slot] != NULL) ? hugeAnimStruct.objects[slot]->_16A : 0xFFFF;
        fn_800B2B54(*(void **)obj, bone, 13);
    } else {
        bone = (hugeAnimStruct.objects[slot] != NULL) ? hugeAnimStruct.objects[slot]->_16A : 0xFFFF;
        fn_800B2B54(*(void **)obj, bone, 1);
        bone = (hugeAnimStruct.objects[slot] != NULL) ? hugeAnimStruct.objects[slot]->_16A : 0xFFFF;
        fn_800B2B54(*(void **)actor, bone, 1);
        fn_800B2B4C(*(void **)actor, 0.125f);
        *(f32 *)(*(u8 **)actor + 0x8C) = 0.0f;
    }
    if (obj->_2C != NULL) {
        actorRelated((u8 *)obj->_2C + 4, tableA, tableB);
    }
    if (obj->_30 != NULL && *((u8 *)obj->_30 + 0xCC) != 0) {
        actorRelated((u8 *)obj->_30 + 0x68, tableA, tableB);
        actorRelated((u8 *)obj->_30 + 4, tableA, tableB);
    }
    anim = obj->_10;
    if (anim != NULL) {
        if (a >= *(u16 *)((u8 *)anim + 0xA) || a < 0) {
            return;
        }
        *(void **)(actor + 4) = anim;
        *(s16 *)(actor + 0x0E) = a;
        actor[0x58] = 1;
        actor[0x59] = anim != NULL;
        actor[0x5A] = anim != NULL;
        *(f32 *)(actor + 0x5C) = 0.0f;
        *(f32 *)(actor + 0x60) = scale;
    }
    if (b != 0) {
        actor[0x5B] = 3;
    } else {
        actor[0x5B] = 2;
    }
    *(f32 *)(actor + 0x5C) = d * obj->_4C;
    actor[0x59] = 1;
    fn_8001B5EC(slot, c);
    fn_8001B308(slot, e);
    obj->_268 = c;
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

// .text:0x0008CCAC size:0x20 mapped:0x806CBD40
void fn_2_8CCAC(int idx, u8 val) {
    u8 *rec = (u8 *)lbl_2_bss_340140 + idx * 0x27C + 0xC04;

    if (rec != NULL) {
        rec[0x25D] = val;
    }
}

// .text:0x0008CC88 size:0x24 mapped:0x806CBD1C
BOOL fn_2_8CC88(int slot) {
    return hugeAnimStruct.objects[slot]->_68 == 0;
}

// .text:0x0008C910 size:0x378 mapped:0x806CB9A4
void fn_2_8C910(void) {
    s32 i;
    u8 *base;

    lbl_2_bss_340140->unk3078 = 0;
    base = lbl_2_bss_340140->unk2D9C;
    for (i = 0; i < 0x39; i++) {
        *(u8 **)((u8 *)lbl_2_bss_340140 + 0x2DA0 + i * 4) = base + *(u32 *)(base + i * 4);
    }
    for (i = 0; i < 7; i++) {
        *(u8 **)((u8 *)lbl_2_bss_3401BC + 0x10 + i * 4) = base + *(u32 *)(base + (0x39 + i) * 4);
        ANIMGet(*(void **)((u8 *)lbl_2_bss_3401BC + 0x10 + i * 4));
    }
    for (i = 0; i < 2; i++) {
        *(u8 **)((u8 *)lbl_2_bss_3401BC + 0x2C + i * 4) = base + *(u32 *)(base + (0x40 + i) * 4);
        ANIMGet(*(void **)((u8 *)lbl_2_bss_3401BC + 0x2C + i * 4));
    }
    for (i = 0; i < 7; i++) {
        *(u8 **)((u8 *)lbl_2_bss_3401BC + 0x34 + i * 4) = base + *(u32 *)(base + (0x42 + i) * 4);
        ANIMGet(*(void **)((u8 *)lbl_2_bss_3401BC + 0x34 + i * 4));
    }
    for (i = 0; i < 0x13; i++) {
        void *layout = lbl_2_bss_340140->slots[i].layout;
        void *geometry = lbl_2_bss_340140->slots[i].geometry;
        void *texture = lbl_2_bss_340140->slots[i].texture;

        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geometry, 0);
        haveActLayoutPointToGeoHeader(layout, geometry);
        convertTextureHeader(texture);
        UpdateTexturePalettePointers(geometry, texture);
    }
}

// .text:0x0008C80C size:0x104 mapped:0x806CB8A0
void fn_2_8C80C(int slot, int start, int count, int animA, int animB) {
    int end = start + count;
    int i;

    for (i = start; i < end; i++) {
        animateBallRelated(lbl_2_bss_340140->unk68, (u16)i, (u16)i,
                           lbl_2_bss_340140->slots[slot].layout, animA, animB);
        *(u8 *)(*(u8 **)(lbl_2_bss_340140->unk68 + 0x34 + i * 0x90) + 0x99) = 1;
        fn_800BD548(lbl_2_bss_340140->unk68 + 0x34 + i * 0x90, 4,
                    *(int *)((u8 *)lbl_2_bss_340140 + 0xAC), *(int *)((u8 *)lbl_2_bss_340140 + 0xB0),
                    *(int *)((u8 *)lbl_2_bss_340140 + 0xB4), *(int *)((u8 *)lbl_2_bss_340140 + 0xB8));
        CTRLSetTranslation(lbl_2_bss_340140->unk68 + 0x44 + i * 0x90, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(lbl_2_bss_340140->unk68 + 0x44 + i * 0x90, 0.0f, 0.0f, 0.0f);
    }
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

// .text:0x0008B418 size:0x130C mapped:0x806CA4AC
void fn_2_8B418(void) {
    lbl_2_bss_340140->unk3078 = 0x1D;
    lbl_2_bss_340140->unk2D94 = _OSAllocFromHeap(32, lbl_2_bss_340140->unk3078 * 0x28);
    lbl_2_bss_340140->unk68 = ActorObjectInitTable(lbl_2_bss_340140->unk3078);
    fn_2_8C80C(0, 0, 1, 0, 0);
    fn_2_8C80C(1, 1, 1, 0, 0);
    fn_2_8C80C(2, 2, 1, 0, 0);
    fn_2_8C80C(3, 3, 1, 0, 0);
    fn_2_8C80C(4, 4, 1, 0, 0);
    fn_2_8C80C(5, 5, 1, 0, 0);
    fn_2_8C80C(6, 6, 1, 0, 0);
    fn_2_8C80C(7, 7, 1, 0, 0);
    fn_2_8C80C(8, 8, 1, 0, 0);
    fn_2_8C80C(9, 9, 1, 0, 0);
    fn_2_8C80C(10, 10, 1, 0, 0);
    fn_2_8C80C(10, 11, 1, 0, 0);
    fn_2_8C80C(10, 12, 1, 0, 0);
    fn_2_8C80C(10, 13, 1, 0, 0);
    fn_2_8C80C(10, 14, 1, 0, 0);
    fn_2_8C80C(10, 15, 1, 0, 0);
    fn_2_8C80C(11, 16, 1, 0, 0);
    fn_2_8C80C(11, 17, 1, 0, 0);
    fn_2_8C80C(11, 18, 1, 0, 0);
    fn_2_8C80C(11, 19, 1, 0, 0);
    fn_2_8C80C(11, 20, 1, 0, 0);
    fn_2_8C80C(11, 21, 1, 0, 0);
    fn_2_8C80C(12, 22, 1, 0, 0);
    fn_2_8C80C(13, 23, 1, 0, 0);
    fn_2_8C80C(14, 24, 1, 0, 0);
    fn_2_8C80C(15, 25, 1, 0, 0);
    fn_2_8C80C(16, 26, 1, 0, 0);
    fn_2_8C80C(17, 27, 1, 0, 0);
    fn_2_8C80C(18, 28, 1, 0, 0);
}

// .text:0x0008B2C0 size:0x158 mapped:0x806CA354
void fn_2_8B2C0(void) {
    s32 i;
    u8 *base;

    lbl_2_bss_340140->unk3078 = 0;
    base = lbl_2_bss_340140->unk2D9C;
    lbl_2_bss_340140->slots[0].layout = base + ((u32 *)base)[0];
    lbl_2_bss_340140->slots[0].geometry = base + ((u32 *)base)[1];
    lbl_2_bss_340140->slots[0].texture = base + ((u32 *)base)[2];
    lbl_2_bss_340140->slots[1].layout = base + ((u32 *)base)[3];
    lbl_2_bss_340140->slots[1].geometry = base + ((u32 *)base)[4];
    lbl_2_bss_340140->slots[1].texture = base + ((u32 *)base)[5];
    lbl_2_bss_340140->slots[2].layout = base + ((u32 *)base)[6];
    lbl_2_bss_340140->slots[2].geometry = base + ((u32 *)base)[7];
    lbl_2_bss_340140->slots[2].texture = base + ((u32 *)base)[8];
    lbl_2_bss_340140->slots[3].layout = base + ((u32 *)base)[9];
    lbl_2_bss_340140->slots[3].geometry = base + ((u32 *)base)[10];
    lbl_2_bss_340140->slots[3].texture = base + ((u32 *)base)[11];
    for (i = 0; i < 4; i++) {
        void *layout = lbl_2_bss_340140->slots[i].layout;
        void *geometry = lbl_2_bss_340140->slots[i].geometry;
        void *texture = lbl_2_bss_340140->slots[i].texture;

        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geometry, 0);
        haveActLayoutPointToGeoHeader(layout, geometry);
        convertTextureHeader(texture);
        UpdateTexturePalettePointers(geometry, texture);
    }
}

// .text:0x0008B158 size:0x168 mapped:0x806CA1EC
void fn_2_8B158(void) {
    s32 i;

    lbl_2_bss_340140->unk3078 = 4;
    lbl_2_bss_340140->unk2D94 = _OSAllocFromHeap(32, lbl_2_bss_340140->unk3078 * 0x28);
    lbl_2_bss_340140->unk68 = ActorObjectInitTable(lbl_2_bss_340140->unk3078);
    for (i = 0; i < lbl_2_bss_340140->unk3078; i++) {
        fn_2_8C80C(i, i, 1, 0, 0);
    }
}

// .text:0x0008B118 size:0x40 mapped:0x806CA1AC
void fn_2_8B118(f32 x) {
    if (x) {
        lbl_2_bss_340140->_307A = 3;
    } else {
        lbl_2_bss_340140->_307A = 0;
    }
}

// .text:0x0008AEE0 size:0x238 mapped:0x806C9F74
void fn_2_8AEE0(void) {
    fn_2_8ACE0();
    PSMTXCopy(lbl_2_bss_1A81D4, fn_80052768_getCamera(0) + 0x40);
    fn_2_190DC(lbl_2_bss_340140->unk68, fn_80052768_getCamera(0) + 0x40);
}

// .text:0x0008ACE0 size:0x200 mapped:0x806C9D74
void fn_2_8ACE0(void) {
    u8 *rec;
    s32 i;
    f32 tmp[3];
    f32 delta[3];

    for (i = 0; i < lbl_2_bss_340140->unk3078; i++) {
        rec = lbl_2_bss_340140->unk2D94 + i * 0x28;
        memcpy(tmp, rec + 4, 12);
        PSVECSubtract(tmp, lbl_2_data_2FEE0, delta);
        delta[0] *= -1.0f;
        delta[2] *= -1.0f;
        if (delta[0] != 0.0f || delta[2] != 0.0f) {
            lbl_2_bss_B2B8 = fn_2_4A1E8(delta[2]);
        }
        memcpy(lbl_2_data_2FEE0, rec + 4, 12);
        if (tmp[0] != 0.0f) {
            *(f32 *)(rec + 4) = tmp[0] / 2;
        }
        if (tmp[1] != 0.0f) {
            *(f32 *)(rec + 8) = tmp[1] / 2;
        }
        if (tmp[2] != 0.0f) {
            *(f32 *)(rec + 0xC) = tmp[2] / 2;
        }
        lbl_2_data_2FED4[1] = *(f32 *)(rec + 0x14);
        CTRLSetTranslation(lbl_2_bss_340140->unk68 + i * 0x90 + 0x44, tmp[0], tmp[1], tmp[2]);
        CTRLSetRotation(lbl_2_bss_340140->unk68 + i * 0x90 + 0x44,
                        lbl_2_data_2FED4[0] * 57.2957763671875f,
                        lbl_2_data_2FED4[1] * 57.2957763671875f,
                        lbl_2_data_2FED4[2] * 57.2957763671875f);
        lbl_2_bss_340140->unk68[i * 0x90 + 0xA0] = lbl_2_bss_3401BC->unk50[i];
    }
}
