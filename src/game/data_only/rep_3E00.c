#define REP_HEADER_DATA_FN getRepHeaderData_rep_3E00
#include "game/data_only/rep_3E00.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x80025ddc.h"
#include "Unknown/File_0x800bdd74.h"
#include "Dolphin/stl.h"

typedef struct {
    u8 _00[0x68];
    void* actorTable;
    u8 _6C[0x2D94 - 0x6C];
    void* actorEntries;
    u8 _2D98[4];
    u32* packedFile;
    void* layout;
    void* geometry;
    void* texture;
    u8 _2DAC[0x3078 - 0x2DAC];
    u16 actorCount;
} Rep3E00AnimView;

typedef struct {
    void* animation;
    void* animationData;
    u8 _08[0xC];
    f32 speed;
    u8 _18[6];
    u16 active;
    u8 _20[0xD8 - 0x20];
    u8 loadStep;
} Rep3E00Effect;

extern Rep3E00AnimView hugeAnimStruct;
extern Rep3E00Effect animRelated;
extern void convertGeometryAndSknHeader(void*, void*);
extern void convertTextureHeader(void*);
extern void UpdateTexturePalettePointers(void*, void*);
extern void* _OSAllocFromHeap(s32, s32);
extern void mm_LoadModelAsset(s32, s32, s32, s32, s32);
static const f32 lbl_3_rodata_3E50 = 0.5f;
static u32 lbl_3_data_284E8[8] = {
    0x00000000, 0x00003C98, 0x08F21000, 0x00003C98, 0x0000040B, 0x4000EBBC, 0x08F25000, 0x00009570,
};

// .text:0x001665E4 size:0xCC
int fn_3_1665E4(void) {
    switch (animRelated.loadStep) {
    case 0:
        hugeAnimStruct.packedFile = ARAMTransfer(&lbl_3_data_284E8[4], 0, 0, 0);
        animRelated.loadStep++;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == TRUE) {
            animRelated.loadStep++;
        }
        break;
    case 2:
        fn_3_166448();
        animRelated.loadStep++;
        break;
    default:
        return TRUE;
    }
    return FALSE;
}

#pragma dont_inline on
// .text:0x00166448 size:0x19C mapped:0x807A54DC
void fn_3_166448(void) {
    u32* packed = hugeAnimStruct.packedFile;
    u32* offsets = packed + 3;
    void* layout;
    void* geometry;
    void* texture;
    int inactive;
    int active;

    hugeAnimStruct.layout = (u8*)packed + packed[0];
    hugeAnimStruct.geometry = (u8*)packed + packed[1];
    hugeAnimStruct.texture = (u8*)packed + packed[2];
    animRelated.animation = (u8*)packed + offsets[0];
    animRelated.animationData = (u8*)packed + offsets[1];
    layout = hugeAnimStruct.layout;
    geometry = hugeAnimStruct.geometry;
    texture = hugeAnimStruct.texture;

    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geometry, 0);
    haveActLayoutPointToGeoHeader(layout, geometry);
    convertTextureHeader(texture);
    UpdateTexturePalettePointers(geometry, texture);

    adjustInternalPointers(animRelated.animation);
    actRelated(animRelated.animation, &animRelated.animationData);
    actorRelated(&animRelated.animationData, 0, 0);
    inactive = 0;
    active = 1;
    if (inactive == 0) {
        animRelated.active = active;
    }

    hugeAnimStruct.actorCount = 1;
    hugeAnimStruct.actorEntries = _OSAllocFromHeap(0x20, hugeAnimStruct.actorCount * 0x28);
    memset(hugeAnimStruct.actorEntries, 0, hugeAnimStruct.actorCount * 0x28);
    hugeAnimStruct.actorTable = ActorObjectInitTable(hugeAnimStruct.actorCount);
    mm_LoadModelAsset(0, 0, 1, 0, 0);
    animRelated.speed = lbl_3_rodata_3E50;
    ACTActorRelated(animRelated.animation, (u8*)hugeAnimStruct.actorTable + 0x34);
}
#pragma dont_inline reset
