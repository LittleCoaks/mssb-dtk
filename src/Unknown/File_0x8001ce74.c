#include "Unknown/File_0x8001ce74.h"

#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "C3/light/light.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800bd478.h"
#include "Unknown/File_0x800bde8c.h"
#include "Unknown/File_0x80023b90.h"

typedef struct _StadiumLightInput {
    Vec pos;
    GXColor color;
} StadiumLightInput;

typedef struct _StadiumLightParams {
    u8 lights[4][10];
    GXColor ambient;
} StadiumLightParams;

extern StadiumLightParams inputParams[14];
extern StadiumLightInput lbl_80367318[4];
extern f32 lbl_803CC4B8;
extern f32 lbl_803CC4F0;

extern struct {
    /*0x0000*/ u8 _00[0x6C];
    /*0x006C*/ void* propEntries;
    /*0x0070*/ u8 _70[0xAC - 0x70];
    /*0x00AC*/ void* lights[4];
    /*0x00BC*/ u8 _BC[0x3085 - 0xBC];
    /*0x3085*/ u8 _3085;
    /*0x3086*/ u8 _3086[0x3154 - 0x3086];
} hugeAnimStruct;

void stadiumSetupRelated(void) {
    StadiumLightParams* params;
    s32 stadium;
    s32 i;
    Vec dir;
    GXColor color;

    hugeAnimStruct._3085 = 4;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        stadium = g_d_GameSettings.StadiumID + 7;
    } else {
        stadium = g_d_GameSettings.StadiumID;
    }
    params = &inputParams[(u8)stadium];
    g_d_GameSettings._54 = stadium;

    for (i = 0; i < 4; i++) {
        characterLightingRelated(params->lights[i], &lbl_80367318[i]);
    }

    dir.x = lbl_80367318[0].pos.x;
    dir.y = lbl_80367318[0].pos.y;
    dir.z = lbl_80367318[0].pos.z;
    PSVECNormalize(&dir, &dir);
    updateVectorInArray(0, dir);
    fn_800BD2DC();

    if (inputParams[g_d_GameSettings._54].ambient.a != 0) {
        adjustLightingParams(1, inputParams[g_d_GameSettings._54].ambient);
    }

    for (i = 0; i < 4; i++) {
        LITAlloc(&hugeAnimStruct.lights[i]);
        LITInitAttn(hugeAnimStruct.lights[i], lbl_803CC4F0, lbl_803CC4B8, lbl_803CC4B8, lbl_803CC4F0,
                    lbl_803CC4B8, lbl_803CC4B8);
        LITInitPos(hugeAnimStruct.lights[i], lbl_80367318[i].pos.x, lbl_80367318[i].pos.y,
                   lbl_80367318[i].pos.z);
        color = lbl_80367318[i].color;
        LITInitColor(hugeAnimStruct.lights[i], &color);
    }

    if (hugeAnimStruct.propEntries != NULL) {
        for (i = 0; i < *(u16*)hugeAnimStruct.propEntries; i++) {
            fn_800BD548((u8*)hugeAnimStruct.propEntries + i * 0x90 + 0x34, 4, hugeAnimStruct.lights[0],
                        hugeAnimStruct.lights[1], hugeAnimStruct.lights[2], hugeAnimStruct.lights[3]);
        }
    }
}
