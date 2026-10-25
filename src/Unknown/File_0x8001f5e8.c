#include "Unknown/File_0x8001f5e8.h"

#include "C3/actor/act.h"
#include "C3/control.h"
#include "C3/geoPalette/geoPalette.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800bd478.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800c0770.h"
#include "game/minigame/minigame_models.h"

typedef struct {
    void* data;
    void* geo;
    void* tex;
} PMModelSource;

typedef struct {
    u8 _0000[0x68];
    u8* modelTable;
    u8 _006C[0xAC - 0x6C];
    void* _AC[4];
    u8 _00BC[0x2D94 - 0xBC];
    PMEffect* effects;
    u8 _2D98[0x2D9C - 0x2D98];
    u32* archive;
    PMModelSource sources[27];
    u8 _2EE4[0x3078 - 0x2EE4];
    u16 effectCount;
    u8 _307A[4];
    u8 _307E;
} PMHugeAnimStruct;

extern PMHugeAnimStruct hugeAnimStruct;

void somethingFileHandlingLoadingRelated(void) {
    u32* archive;
    void* data;
    void* geo;
    void* tex;
    int i;
    s32 count;
    int off;

    count = 30;
    hugeAnimStruct.effectCount = count;

    archive = hugeAnimStruct.archive;
    hugeAnimStruct.sources[0].data = (u8*)archive + archive[0];
    hugeAnimStruct.sources[0].geo = (u8*)archive + archive[1];
    hugeAnimStruct.sources[0].tex = (u8*)archive + archive[2];
    data = hugeAnimStruct.sources[0].data;
    geo = hugeAnimStruct.sources[0].geo;
    tex = hugeAnimStruct.sources[0].tex;

    LoadActorLayout(data);
    convertGeometryAndSknHeader(geo, 0);
    haveActLayoutPointToGeoHeader(data, geo);
    convertTextureHeader(tex);
    UpdateTexturePalettePointers(geo, tex);

    hugeAnimStruct.modelTable = ActorObjectInitTable(count);

    for (i = 0, off = 0; i < 30; i++, off += 0x90) {
        animateBallRelated(hugeAnimStruct.modelTable, i, i, hugeAnimStruct.sources[0].data, 0, 0);
        fn_800BD548(hugeAnimStruct.modelTable + off + 0x34, 4, hugeAnimStruct._AC[0], hugeAnimStruct._AC[1],
                    hugeAnimStruct._AC[2], hugeAnimStruct._AC[3]);
        CTRLSetTranslation((Control*)(hugeAnimStruct.modelTable + off + 0x44), 0.0f, 0.0f, 0.0f);
        CTRLSetRotation((Control*)(hugeAnimStruct.modelTable + off + 0x44), 0.0f, 0.0f, 0.0f);
    }

    hugeAnimStruct.effects = _OSAllocFromHeap(0x20, count * sizeof(PMEffect));
    for (i = 0; i < 30; i++) {
        PMEffect* fx = &hugeAnimStruct.effects[i];
        fx->update = 0;
        fx->pos.x = 0.0f;
        fx->pos.y = 0.0f;
        fx->pos.z = 0.0f;
        fx->rot.x = 0.0f;
        fx->rot.y = 0.0f;
        fx->rot.z = 0.0f;
        fx->visible = FALSE;
    }
}
