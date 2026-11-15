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
#include "HugeAnimStruct.h"

#define PM_EFFECTS ((PMEffect*)hugeAnimStruct.actorEntries)
#define PM_MODEL_TABLE ((u8*)hugeAnimStruct.actorTables[2])

void somethingFileHandlingLoadingRelated(void) {
    u32* archive;
    void* data;
    void* geo;
    void* tex;
    int i;
    s32 count;
    int off;

    count = 30;
    hugeAnimStruct.actorCount = count;

    archive = hugeAnimStruct.archive;
    hugeAnimStruct.sources[0].layout = (u8*)archive + archive[0];
    hugeAnimStruct.sources[0].geometry = (u8*)archive + archive[1];
    hugeAnimStruct.sources[0].texture = (u8*)archive + archive[2];
    data = hugeAnimStruct.sources[0].layout;
    geo = hugeAnimStruct.sources[0].geometry;
    tex = hugeAnimStruct.sources[0].texture;

    LoadActorLayout(data);
    convertGeometryAndSknHeader(geo, 0);
    haveActLayoutPointToGeoHeader(data, geo);
    convertTextureHeader(tex);
    UpdateTexturePalettePointers(geo, tex);

    hugeAnimStruct.actorTables[2] = ActorObjectInitTable(count);

    for (i = 0, off = 0; i < 30; i++, off += 0x90) {
        animateBallRelated(PM_MODEL_TABLE, i, i, hugeAnimStruct.sources[0].layout, 0, 0);
        fn_800BD548(PM_MODEL_TABLE + off + 0x34, 4, hugeAnimStruct.lights[0], hugeAnimStruct.lights[1],
                    hugeAnimStruct.lights[2], hugeAnimStruct.lights[3]);
        CTRLSetTranslation((Control*)(PM_MODEL_TABLE + off + 0x44), 0.0f, 0.0f, 0.0f);
        CTRLSetRotation((Control*)(PM_MODEL_TABLE + off + 0x44), 0.0f, 0.0f, 0.0f);
    }

    hugeAnimStruct.actorEntries = _OSAllocFromHeap(0x20, count * sizeof(PMEffect));
    for (i = 0; i < 30; i++) {
        PMEffect* fx = &PM_EFFECTS[i];
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
