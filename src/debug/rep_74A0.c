#define REP_HEADER_DATA_FN getRepHeaderData_rep74A0
#include "debug/rep_74A0.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/DisplayObject.h"
#include "Unknown/File_0x800bdd74.h"
#include "game/stadium/stadium_framework.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x80033794.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800bd8c4.h"
#include "Unknown/File_0x800b0724.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x80034220.h"
#include "Unknown/sub.h"
#include "static/UnknownHomes_Static.h"
#include "C3/control.h"
#include "C3/anim.h"
#include "Unknown/File_0x800bfe90.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x800bcd60.h"
#include "Unknown/File_0x800bce38.h"
#include "Unknown/File_0x800bd190.h"
#include "Unknown/File_0x800bd3ec.h"
#include "Dolphin/gx.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/rand.h"
#include "stl/math.h"
#include "stl/mem.h"

extern DbgAnim hugeAnimStruct;
extern u8 drawStadiumRelated;
extern void fn_800A7D4C(s32 arg0, void *arg1);
extern u8 lbl_80366158[0x30];
typedef struct _StadiumLightInput {
    Vec pos;
    GXColor color;
} StadiumLightInput;
extern StadiumLightInput lbl_80367318[4];


extern void fn_800BD670(ActorObjectTable *table, Mtx m);
extern void fn_800B2D5C(void *obj);
extern void fn_800B2C08(void *actor, int arg1);
extern void fn_800B2C88(void *model, u16 idx, void *out);
extern void fn_800B806C(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
extern void LITInitAttn(void *light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
extern void LITInitPos(void *light, f32 x, f32 y, f32 z);
extern void LITInitColor(void *light, GXColor color);
extern void LITInitDir(void *light, f32 x, f32 y, f32 z);
extern void LITXForm(void *light, Mtx m);

#define DBG_SCENE() ((DbgScene *)currentDrawingItem)
#define PAD_U16(off) (*(u16 *)((u8 *)&AtBat_ButtonInput1 + (off)))
#define PAD_S8(off) (*(s8 *)((u8 *)&AtBat_ButtonInput1 + (off)))
#define PAD_U8(off) (*(u8 *)((u8 *)&AtBat_ButtonInput1 + (off)))
#define PAD_CUR PAD_U16(0x0)
#define PAD_NEW PAD_U16(0x2)
#define PAD_PROC PAD_U16(0x4)

#define PARTICLE_SLOT_COUNT 24


static char gModeNames[7][0x20] = {"CAMERA", "MODEL", "OFF", "ON", "MIX", "BONE_ONLY", "MODEL_ONLY"};

static u32 gModelFiles[24][4] = {
    {0x40B, 0x40021A48, 0xE67B800, 0x18844},
    {0x40B, 0x4001C1FC, 0xE694800, 0x16E90},
    {0x40B, 0x4001E21C, 0xE6AB800, 0x146D0},
    {0x40B, 0x4001ED7C, 0xE6C0000, 0x11D04},
    {0x40B, 0x40011A3C, 0xE6D2000, 0xA890},
    {0x40B, 0x4001F938, 0xE6DD000, 0x158FC},
    {0x40B, 0x4001A89C, 0xE6F3000, 0x1275C},
    {0x40B, 0x4001C1FC, 0xE705800, 0x16E90},
    {0x40B, 0x400347F8, 0xE71C800, 0x1432C},
    {0x40B, 0x4002511C, 0xE731000, 0x1304C},
    {0x40B, 0x4001A9C4, 0xE744800, 0x160C0},
    {0x40B, 0x400253B4, 0xE75B000, 0x1CEB0},
    {0x40B, 0x40016040, 0xE778000, 0xDCBC},
    {0x40B, 0x4001B060, 0xE786000, 0x1235C},
    {0x40B, 0x4002573C, 0xE798800, 0x1D2B0},
    {0x40B, 0x40021FCC, 0xE7B6000, 0x16FBC},
    {0x40B, 0x4000FEAC, 0xE7CD000, 0xB05C},
    {0x40B, 0x400B0ADC, 0xE7D8800, 0x52EB0},
    {0x40B, 0x400B0A88, 0xE82B800, 0x52E98},
    {0x40B, 0x400B0ABC, 0xE87E800, 0x52EAC},
    {0x40B, 0x400B0D7C, 0xE8D1800, 0x52F34},
    {0x40B, 0x400AA97C, 0xE924800, 0x50DF4},
    {0x40B, 0x4000289C, 0xE975800, 0x1C28},
    {0x40B, 0x40006588, 0xE977800, 0x2F60},
};

static DbgDrawEntry gBackdropDraw[2] = {{0, fn_1_1ADA4}, {0, NULL}};
static DbgDrawEntry gBoundsDraw[2] = {{0, fn_1_1A774}, {0, NULL}};
static GXColor gFogColor = {0xFF, 0xFF, 0xFF, 0xFF};
static Vec gUpVec = {0.0f, 1.0f, 0.0f};
static Vec gRotAccum = {0.0f, 0.0f, 0.0f};
static s32 gParticleCfg[6] = {0x32, 0x7D0, 0x124F80, 0x186A0, 0x186A0, 0x3C};

static DbgCamera gCamera;
static DbgTexHeader *gTexTable[52];
static E(u8, BOOL) gIsModel[PARTICLE_SLOT_COUNT];
static DbgView gView;
static u8 gColor3;
static u8 gColor2;
static u8 gColor1;
static u8 gColor0;
static u8 gFlag5;
static u8 gFlag4;
static u8 gFlag3;
static u8 gSlot;
static u16 gIndex;

// .text:0x0001D514 size:0x7C
void fn_1_1D514(void) {
    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    currentDrawingItem->state = 0;
    currentDrawingItem->func = fn_1_1D470;
    gColor0 = 0xFF;
    gColor1 = 0xFF;
    gColor2 = 0xFF;
    gColor3 = 0xFF;
    gFlag5 = 0;
    gFlag3 = 0;
}

// .text:0x0001D470 size:0xA4
void fn_1_1D470(void) {
    DbgScene *scene = DBG_SCENE();
    s32 i;

    for (i = 0; i < PARTICLE_SLOT_COUNT; i++) {
        gView.visible[i] = 0;
    }
    scene->cursor = 0;
    currentDrawingItem->func = fn_1_1D450;
}

// .text:0x0001D450 size:0x20
void fn_1_1D450(void) {
    fn_1_1CBE4();
}

// .text:0x0001D110 size:0x340
void fn_1_1D110(void) {
    DbgScene *scene = DBG_SCENE();
    ActorObjectEntry *entry;
    DbgSlot *slot;
    int i;
    f32 radToDeg;

    fn_1_1B038();
    radToDeg = 57.295776f;
    for (i = 0; i < PARTICLE_SLOT_COUNT; i++) {
        slot = &hugeAnimStruct.slots[i];
        entry = &hugeAnimStruct.table->entries[i];
        entry->applyControl = (scene->mode16 != 1) & (i == scene->slot);
        CTRLSetTranslation(&entry->control, slot->pos.x, slot->pos.y, slot->pos.z);
        CTRLSetRotation(&entry->control, radToDeg * slot->rot.x, radToDeg * slot->rot.y, radToDeg * slot->rot.z);
        entry->speed = slot->speed;
        entry->speedPending = TRUE;
    }
    if (gFlag5 == 0) {
        fn_800BD670(hugeAnimStruct.table, gView.mtx);
    } else {
        fn_1_1A290(hugeAnimStruct.table, gView.mtx);
    }
    for (i = 0; i < (s32)PARTICLE_SLOT_COUNT; i++) { // long bound: the guard tests i itself (cmpwi r5)
        entry = &hugeAnimStruct.table->entries[i];
        entry->applyControl = TRUE;
    }
    fn_800BD8C4(hugeAnimStruct.table, gView.mtx);
}

// .text:0x0001D10C size:0x4
void fn_1_1D10C(void) {
}

// .text:0x0001D0E8 size:0x24
void fn_1_1D0E8(ActorObjectEntry *entry) {
    setLITLightPtr((void *)entry->drawArgs[0]);
}

// .text:0x0001CBE4 size:0x504
void fn_1_1CBE4(void) {
    DbgScene *scene = DBG_SCENE();
    int i;
    u32 *file;

    switch (currentDrawingItem->state) {
    case 0:
        for (i = 0; i < PARTICLE_SLOT_COUNT; i++) {
            gIsModel[i] = FALSE;
        }
        scene->slot = 0;
        scene->mode16 = 0;
        scene->mode17 = 0;
        scene->mode18 = 1;
        fn_1_1B6BC();
        fn_1_1B0FC();
        currentDrawingItem->state = 2;
        break;
    case 1:
        scene->slot++;
        if (scene->slot == PARTICLE_SLOT_COUNT) {
            currentDrawingItem->state = 8;
        } else {
            currentDrawingItem->state = 2;
        }
        break;
    case 2:
        file = gModelFiles[scene->slot];
        if ((char *)file[0] == "test/obj/skin/mario/model11.dat" || (char *)file[0] == "test/obj/skin/test01/model11.dat"
            || (char *)file[0] == "test/obj/skin/test02/model11.dat" || (char *)file[0] == "test/obj/skin/test03/model11.dat"
            || (char *)file[0] == "test/obj/skin/test04/model11.dat" || (char *)file[0] == "test/obj/skin/test05/model11.dat"
            || (char *)file[0] == "test/obj/skin/test06/model11.dat" || (char *)file[0] == "test/obj/skin/test07/model11.dat") {
            gIsModel[scene->slot] = TRUE;
        }
        hugeAnimStruct.slots[scene->slot].file = ARAMTransfer(gModelFiles[scene->slot], 0, 0, 0);
        currentDrawingItem->state++;
        break;
    case 3:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            scene->state = 1;
        }
        break;
    case 8:
        scene->slot = 0;
        currentDrawingItem->state = 0;
        currentDrawingItem->func = fn_1_1C8C0;
        break;
    }
}

// .text:0x0001C8C0 size:0x324
void fn_1_1C8C0(void) {
    u32 *file;
    void *geo;
    void *tex;
    void *layout;
    void *skn;
    u32 i;
    u32 k;
    int anim;
    DbgSlot *slot;
    ActorObjectEntry *entry;

    hugeAnimStruct.table = ActorObjectInitTable(PARTICLE_SLOT_COUNT);
    for (i = 0; i < PARTICLE_SLOT_COUNT; i++) {
        if (i < PARTICLE_SLOT_COUNT) {
            file = hugeAnimStruct.slots[i].file;
            if (gIsModel[i]) {
                for (k = 0; k < 5; k++) {
                    if (k == 4) {
                        hugeAnimStruct.slots[i].anim = (u8 *)file + file[k];
                        ANIMGet(hugeAnimStruct.slots[i].anim);
                    } else {
                        hugeAnimStruct.slots[i].file[k] = (u32)file + file[k];
                    }
                }
            } else {
                file[0] = (u32)file + file[0];
                hugeAnimStruct.slots[i].file[1] = (u32)file + file[1];
                hugeAnimStruct.slots[i].file[2] = (u32)file + file[2];
            }
            tex = (void *)hugeAnimStruct.slots[i].file[0];
            geo = (void *)hugeAnimStruct.slots[i].file[1];
            layout = (void *)hugeAnimStruct.slots[i].file[2];
            if (gIsModel[i]) {
                skn = (void *)hugeAnimStruct.slots[i].file[3];
            } else {
                skn = NULL;
            }
            convertTextureHeader(tex);
            LoadActorLayout(layout);
            if (gIsModel[i]) {
                convertGeometryAndSknHeader(geo, skn);
            } else {
                AdjustGEOPalettePointers(geo);
            }
            gTexTable[i] = tex;
            haveActLayoutPointToGeoHeader(layout, geo);
            UpdateTexturePalettePointers(geo, tex);
        }
        if (gIsModel[i]) {
            anim = (int)hugeAnimStruct.slots[i].anim;
        } else {
            anim = 0;
        }
        slot = &hugeAnimStruct.slots[i];
        animateBallRelated(hugeAnimStruct.table, (u16)i, (u16)i, layout, anim, (int)skn);
        fn_800BD548(&hugeAnimStruct.table->entries[i], 3, hugeAnimStruct.lights[0], hugeAnimStruct.lights[1], hugeAnimStruct.lights[2],
                    hugeAnimStruct.lights[3]);
        CTRLSetTranslation(&hugeAnimStruct.table->entries[i].control, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&hugeAnimStruct.table->entries[i].control, 0.0f, 0.0f, 0.0f);
        entry = &hugeAnimStruct.table->entries[i];
        entry->speed = 0.5f;
        entry->speedPending = TRUE;
        hugeAnimStruct.table->entries[i].actor->unk98 |= 4;
        if (i == 1) {
            fn_800B2C08(hugeAnimStruct.table->entries[i].actor, 0);
        } else {
            fn_800B2C08(hugeAnimStruct.table->entries[i].actor, 1);
        }
        slot->actor = hugeAnimStruct.table->entries[i].actor;
        slot->pos.x = 0.0f;
        slot->pos.y = 0.0f;
        slot->pos.z = 10.0f;
        slot->speed = 0.5f;
        slot->isFirst = (i == 0);
        hugeAnimStruct.table->entries[i].callback = fn_1_1D0E8;
    }
    currentDrawingItem->func = fn_1_1C3CC;
}

// .text:0x0001C3CC size:0x4F4
void fn_1_1C3CC(void) {
    DbgScene *scene = DBG_SCENE();
    Mtx44 proj;

    C_MTXFrustum(proj, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_1_1B7DC();
    if (scene->mode17 != 0) {
        fn_1_1B2C8();
    } else {
        fn_1_1B424();
    }
    PSMTXCopy(gCamera.view, gView.mtx);
    gSlot = scene->slot;
    fn_800A7D4C(0, &gBackdropDraw[drawStadiumRelated]);
    if (scene->mode16 != 2) {
        fn_800A7D4C(0, &gBoundsDraw[drawStadiumRelated]);
    }
    fn_1_1D110();
    if (scene->mode18 != 0) {
        fn_1_1A3B4();
    }
}

// .text:0x0001B7DC size:0xBF0
void fn_1_1B7DC(void) {
    DbgScene *scene = DBG_SCENE();
    GXColor fogOff = {0, 0, 0, 0};
    u16 proc;

    if (PAD_NEW & INPUT_BUTTON_B) {
        fn_800AD038(*(void **)(lbl_80366158 + 0x8));
        SetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, fogOff);
        DBG_SCENE()->parent->state = 1;
        minigamesSetSomePointers();
        return;
    }
    proc = PAD_PROC;
    if (proc & INPUT_BUTTON_UP) {
        if (scene->cursor != 0) {
            scene->cursor--;
        } else if (gFlag5 != 0) {
            scene->cursor = 10;
        } else {
            scene->cursor = 6;
        }
    } else if (proc & INPUT_BUTTON_DOWN) {
        scene->cursor++;
        if (scene->cursor > 6 && scene->cursor < 11 && gFlag5 == 0) {
            scene->cursor = 0;
        }
        if (scene->cursor == 11) {
            scene->cursor = 0;
        }
    } else if (proc & INPUT_BUTTON_LEFT) {
        switch (scene->cursor) {
        case 0:
            if (scene->slot != 0) {
                scene->slot--;
            } else {
                scene->slot = 0x17;
            }
            break;
        case 1:
            if (scene->mode16 != 0) {
                scene->mode16--;
            } else {
                scene->mode16 = 2;
            }
            break;
        case 2:
            if (scene->mode17 != 0) {
                scene->mode17--;
            } else {
                scene->mode17 = 1;
            }
            break;
        case 3:
            if (scene->mode18 != 0) {
                scene->mode18--;
            } else {
                scene->mode18 = 1;
            }
            break;
        case 4:
            gFlag4 = !gFlag4;
            if (gFlag4) {
                SetFog(GX_FOG_EXPONENT, 0.0f, 500.0f, 1.0f, 512.0f, gFogColor);
            } else {
                SetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, fogOff);
            }
            break;
        case 6:
            gFlag5 = !gFlag5;
            break;
        case 7:
            if (gFlag5 != 0) {
                gColor3--;
            }
            break;
        case 8:
            if (gFlag5 != 0) {
                gColor2--;
            }
            break;
        case 9:
            if (gFlag5 != 0) {
                gColor1--;
            }
            break;
        case 10:
            if (gFlag5 != 0) {
                gColor0--;
            }
            break;
        case 5:
            gFlag3 = !gFlag3;
            if (gFlag3) {
                fn_1_1957C();
            } else {
                minigamesSetSomePointers();
            }
            break;
        }
    } else if (proc & INPUT_BUTTON_RIGHT) {
        switch (scene->cursor) {
        case 0:
            scene->slot++;
            if (scene->slot == PARTICLE_SLOT_COUNT) {
                scene->slot = 0;
            }
            break;
        case 1:
            scene->mode16++;
            if (scene->mode16 == 3) {
                scene->mode16 = 0;
            }
            break;
        case 2:
            scene->mode17++;
            if (scene->mode17 == 2) {
                scene->mode17 = 0;
            }
            break;
        case 3:
            scene->mode18++;
            if (scene->mode18 == 2) {
                scene->mode18 = 0;
            }
            break;
        case 4:
            gFlag4 = !gFlag4;
            if (gFlag4) {
                SetFog(GX_FOG_EXPONENT, 0.0f, 500.0f, 1.0f, 512.0f, gFogColor);
            } else {
                SetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, fogOff);
            }
            break;
        case 6:
            gFlag5 = !gFlag5;
            break;
        case 7:
            if (gFlag5 != 0) {
                gColor3++;
            }
            break;
        case 8:
            if (gFlag5 != 0) {
                gColor2++;
            }
            break;
        case 9:
            if (gFlag5 != 0) {
                gColor1++;
            }
            break;
        case 10:
            if (gFlag5 != 0) {
                gColor0++;
            }
            break;
        case 5:
            gFlag3 = !gFlag3;
            if (gFlag3) {
                fn_1_1994C();
            } else {
                minigamesSetSomePointers();
            }
            break;
        }
    }
}

// .text:0x0001B6BC size:0x120
void fn_1_1B6BC(void) {
    Mtx44 proj;

    gCamera.eye.x = 0.0f;
    gCamera.eye.y = -0.8f;
    gCamera.eye.z = 0.0f;
    gCamera.target.x = 0.0f;
    gCamera.target.y = 0.0f;
    gCamera.target.z = 10.0f;
    C_MTXFrustum(proj, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -1.0f, 1280.0f);
}

// .text:0x0001B424 size:0x298
void fn_1_1B424(void) {
    Vec scaled;
    Vec dir = {0.0f, 0.0f, 100.0f};
    Mtx rotX;
    Mtx rotY;
    Mtx rot;
    f32 c;
    f32 s;

    if (!(PAD_CUR & INPUT_TRIGGER_Z)) {
        gCamera.yaw -= PAD_S8(0x13);
        gCamera.pitch += PAD_S8(0x12);
        gCamera.strafe = (f32)PAD_S8(0x10) / -256.0f;
        gCamera.forward = (f32)PAD_S8(0x11) / 256.0f;
        gCamera.eye.y += (f32)PAD_U8(0x15) / 1024.0f;
        gCamera.eye.y -= (f32)PAD_U8(0x14) / 1024.0f;
    }
    scaled.x = gCamera.yaw;
    scaled.y = gCamera.pitch;
    scaled.z = 0.0f;
    PSVECScale(&scaled, 0.0000958738f, &scaled);
    PSMTXRotRad(rotX, 'X', scaled.x);
    PSMTXRotRad(rotY, 'Y', scaled.y);
    s = rotY[0][2];
    c = rotY[0][0];
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &dir, &gCamera.target);
    gCamera.eye.x += gCamera.forward * s - gCamera.strafe * c;
    gCamera.eye.z += gCamera.forward * c + gCamera.strafe * s;
    gCamera.target.x += gCamera.eye.x;
    gCamera.target.y += gCamera.eye.y;
    gCamera.target.z += gCamera.eye.z;
    makeLookAtMatrix(gCamera.view, &gCamera.eye, &gUpVec, &gCamera.target);
}

// .text:0x0001B2C8 size:0x15C
void fn_1_1B2C8(void) {
    DbgSlot *slot = &hugeAnimStruct.slots[DBG_SCENE()->slot];
    Vec pos;

    pos.x = slot->pos.x;
    pos.y = slot->pos.y;
    pos.z = slot->pos.z;
    pos.x += (f32)PAD_S8(0x10) / 768.0f;
    pos.z += (f32)PAD_S8(0x11) / 768.0f;
    pos.y += (f32)PAD_U8(0x15) / 768.0f;
    pos.y -= (f32)PAD_U8(0x14) / 768.0f;
    gRotAccum.y -= (f32)PAD_S8(0x12) / 512.0f;
    gRotAccum.x -= (f32)PAD_S8(0x13) / 512.0f;
    slot->pos.x = pos.x;
    slot->pos.y = pos.y;
    slot->pos.z = pos.z;
    slot->rot.x = gRotAccum.x;
    slot->rot.y = gRotAccum.y;
    slot->rot.z = gRotAccum.z;
}

// .text:0x0001B0FC size:0x1CC
void fn_1_1B0FC(void) {
    GXColor color0 = {0xFF, 0xFF, 0xFF, 0xFF};
    GXColor color1 = {0x00, 0x00, 0xFF, 0xFF};

    LITAlloc(&hugeAnimStruct.lights[0]);
    LITAlloc(&hugeAnimStruct.lights[1]);
    LITAlloc(&hugeAnimStruct.lights[2]);
    LITInitAttn(hugeAnimStruct.lights[0], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(hugeAnimStruct.lights[0], -100.0f, -100.0f, 100.0f);
    LITInitColor(hugeAnimStruct.lights[0], color0);
    LITInitAttn(hugeAnimStruct.lights[1], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(hugeAnimStruct.lights[1], 500.0f, -500.0f, 250.0f);
    LITInitColor(hugeAnimStruct.lights[1], color1);
    LITInitAttn(hugeAnimStruct.lights[2], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(hugeAnimStruct.lights[2], 0.0f, -500.0f, 250.0f);
    LITInitColor(hugeAnimStruct.lights[2], color1);
    LITInitDir(hugeAnimStruct.lights[0], 100.0f, 100.0f, -100.0f);
}

// .text:0x0001B038 size:0xC4
void fn_1_1B038(void) {
    GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    StadiumLightInput *light = lbl_80367318;
    int i;

    for (i = 0; i < 3; i++) {
        LITInitAttn(hugeAnimStruct.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(hugeAnimStruct.lights[i], light[i].pos.x, light[i].pos.y, light[i].pos.z);
        LITInitColor(hugeAnimStruct.lights[i], color);
        LITXForm(hugeAnimStruct.lights[i], gView.mtx);
    }
}

// .text:0x0001ADA4 size:0x294
void fn_1_1ADA4(void) {
    Mtx44 proj;
    int i;
    f32 f;

    C_MTXFrustum(proj, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    GXLoadPosMtxImm(gCamera.view, 0);
    GXSetCurrentMtx(0);
    GXSetColorUpdate(GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    for (i = -24; i < 25; i++) {
        f = i;
        GXBegin(GX_LINES, GX_VTXFMT0, 4);
        GXPosition3f32(-24.0f, 0.0f, f);
        GXColor4u8(0, 255, 0, 200);
        GXPosition3f32(24.0f, 0.0f, f);
        GXColor4u8(0, 255, 0, 200);
        GXPosition3f32(f, 0.0f, -24.0f);
        GXColor4u8(0, 255, 0, 200);
        GXPosition3f32(f, 0.0f, 24.0f);
        GXColor4u8(0, 255, 0, 200);
    }
}

// .text:0x0001A850 size:0x554
void fn_1_1A850(Mtx obj, Mtx cam, u8 r, u8 g, u8 b, u8 a) {
    GXCullMode cull;
    Mtx m;

    GXGetCullMode(&cull);
    PSMTXConcat(cam, obj, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetLineWidth(7, GX_TO_ZERO);
    GXBegin(GX_LINES, GX_VTXFMT0, 22);
    GXPosition3f32(-0.01f, 0.0f, 0.0f);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(0.2f, 0.0f, 0.0f);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(0.0f, 0.0f, 0.01f);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(0.2f, 0.0f, 0.0f);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(0.0f, 0.0f, -0.01f);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(0.2f, 0.0f, 0.0f);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(-0.01f, 0.0f, 0.0f);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(0.0f, 0.0f, 0.01f);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(-0.01f, 0.0f, 0.0f);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(0.0f, 0.0f, -0.01f);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor4u8(0, 255, 0, a);
    GXPosition3f32(0.0f, 0.05f, 0.0f);
    GXColor4u8(0, 255, 0, a);
    GXPosition3f32(-0.005f, 0.0f, 0.0f);
    GXColor4u8(0, 255, 0, a);
    GXPosition3f32(0.0f, 0.05f, 0.0f);
    GXColor4u8(0, 255, 0, a);
    GXPosition3f32(0.005f, 0.0f, 0.0f);
    GXColor4u8(0, 255, 0, a);
    GXPosition3f32(0.0f, 0.05f, 0.0f);
    GXColor4u8(0, 255, 0, a);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor4u8(255, 0, 255, a);
    GXPosition3f32(0.0f, 0.0f, 0.05f);
    GXColor4u8(255, 0, 255, a);
    GXPosition3f32(-0.005f, 0.0f, 0.0f);
    GXColor4u8(255, 0, 255, a);
    GXPosition3f32(0.0f, 0.0f, 0.05f);
    GXColor4u8(255, 0, 255, a);
    GXPosition3f32(0.005f, 0.0f, 0.0f);
    GXColor4u8(255, 0, 255, a);
    GXPosition3f32(0.0f, 0.0f, 0.05f);
    GXColor4u8(255, 0, 255, a);
    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetCullMode(cull);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
}

// .text:0x0001A774 size:0xDC
void fn_1_1A774(void) {
    int i;
    Mtx m;
    u8 r;
    u8 g;
    u8 b;
    u8 a;

    if (gIndex < hugeAnimStruct.table->entries[gSlot].actor->totalBones) {
        for (i = 0; i < hugeAnimStruct.table->entries[gSlot].actor->totalBones; i++) {
            if (i == gIndex) {
                r = 0;
                g = 255;
                b = 255;
                a = 255;
            } else {
                r = 0;
                g = 128;
                b = 128;
                a = 64;
            }
            fn_800B2C88(hugeAnimStruct.table->entries[gSlot].actor, i, m);
            fn_1_1A850(m, gCamera.view, r, g, b, a);
        }
    }
}

// .text:0x0001A3B4 size:0x3C0
void fn_1_1A3B4(void) {
    GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    DbgTexHeader *header = gTexTable[DBG_SCENE()->slot];
    DbgTexEntry *entries = (DbgTexEntry *)((u8 *)header + header->index * 0x20 + 4);
    DbgTexEntry *entry = entries;
    u32 count = header->count;
    GXTlutObj tlut;
    GXTexObj texObj;
    u32 i;

    if (entries->clut != NULL) {
        for (i = 0; i < count; i++) {
            GXInitTlutObj(&tlut, entry->clut, entry->clutFormat, entry->clutCount);
            GXLoadTlut(&tlut, 0);
            GXInitTexObjCI(&texObj, entry->data, entry->width, entry->height, entry->format, GX_CLAMP, GX_CLAMP, GX_FALSE, 0);
            GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            entry++;
        }
    } else {
        for (i = 0; i < count; i++) {
            GXInitTexObj(&texObj, entry->data, entry->width, entry->height, entry->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            entry++;
        }
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXSetCullMode(GX_CULL_NONE);
    GXLoadPosMtxImm(gCamera.view, 0);
    GXSetCurrentMtx(0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-3.0f, 0.0f, 20.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(-3.0f, -3.0f, 20.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(0.0f, -3.0f, 20.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(0.0f, 0.0f, 20.0f);
    GXTexCoord2f32(1.0f, 1.0f);
}

// .text:0x0001A290 size:0x124
void fn_1_1A290(ActorObjectTable *table, Mtx cam) {
    u16 i;
    ActorObjectEntry *entry;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < table->count; i++) {
        entry = &table->entries[i];
        if (entry->actor != NULL && table->entries[i].applyControl != 0) {
            fn_1_1A1EC(entry, cam);
        }
    }
}

// .text:0x0001A1EC size:0xA4
void fn_1_1A1EC(ActorObjectEntry *entry, Mtx cam) {
    StadiumModelNode *node = (StadiumModelNode *)entry->actor;

    if (entry->callback != NULL) {
        entry->callback(entry);
    }
    if (node->dispObj != NULL) {
        fn_800B2D5C(node);
        GXInvalidateVtxCache();
        fn_1_19D60((DbgDispObj *)node->dispObj, cam);
    } else {
        for (node = node->firstChild; node != NULL; node = node->nextSibling) {
            if (node->dispObj != NULL) {
                DOSetWorldMatrix(node->dispObj, node->worldMtx);
            }
            fn_1_19D60((DbgDispObj *)node->dispObj, cam);
        }
    }
}

// .text:0x00019D60 size:0x48C
void fn_1_19D60(DbgDispObj *obj, Mtx cam) {
    GXAttr texAttr;
    GXColor color;
    Mtx m;
    GXVtxDescList desc[GX_VA_MAX_ATTR + 1];
    DbgDrawListEntry *entry;
    int i;
    int j;
    int n;

    color.r = gColor3;
    color.g = gColor2;
    color.b = gColor1;
    color.a = gColor0;
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    PSMTXConcat(cam, obj->mtx, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXSetArray(GX_VA_POS, obj->vertices->data, obj->vertices->stride * fn_1_19D1C(obj->vertices->format));
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, obj->vertices->format >> 4, obj->vertices->format & 0xF);
    if (obj->texData != NULL) {
        for (i = 0; i < obj->numTex; i++) {
            u8 size = obj->texData[i].stride * fn_1_19D1C(obj->texData[i].format);

            texAttr = GX_VA_TEX0 + i;
            GXSetArray(texAttr, obj->texData[i].data, size);
            GXSetVtxAttrFmt(GX_VTXFMT0, texAttr, GX_TEX_ST, obj->texData[i].format >> 4, obj->texData[i].format & 0xF);
            GXSetTexCoordGen2(i, GX_TG_MTX2X4, GX_TG_TEX0 + i, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        }
    }
    entry = obj->drawList->entries;
    for (j = 0; j < obj->drawList->count; entry++, j++) {
        switch (entry->kind) {
        case 1:
        case 3:
            break;
        case 2:
            GXClearVtxDesc();
            n = 0;
            if ((entry->vtxDescBits & 3) != 0) {
                desc[n].mAttr = GX_VA_PNMTXIDX;
                desc[n].mType = entry->vtxDescBits & 3;
                n = 1;
            }
            {
                GXAttr attr;
                u32 shift;
                for (attr = GX_VA_POS, shift = 2; attr <= GX_VA_TEX7; attr++, shift += 2) {
                    u32 type = (entry->vtxDescBits >> shift) & 3;
                    if (type != 0) {
                        desc[n].mAttr = attr;
                        desc[n].mType = type;
                        n++;
                    }
                }
                {
                    u32 type = (entry->vtxDescBits >> 26) & 3;
                    if (type != 0) {
                        desc[n].mAttr = attr;
                        desc[n].mType = type;
                        n++;
                    }
                }
            }
            desc[n].mAttr = GX_VA_NULL;
            GXSetVtxDescv(desc);
            break;
        }
        if (entry->displayList != NULL) {
            GXCallDisplayList(entry->displayList, entry->displayListSize);
        }
    }
}

// .text:0x00019D1C size:0x44
int fn_1_19D1C(u8 fmt) {
    switch ((u8)(fmt >> 4)) {
    case 0:
    case 1:
        return 1;
    case 2:
    case 3:
        return 2;
    case 4:
        return 4;
    default:
        return 0;
    }
}

// .text:0x0001994C size:0x3D0
void fn_1_1994C(void) {
    ParticleEffect *effect = allocParticleEffect(fn_1_1857C, 0, 0, gParticleCfg[0], 1, 0x80);

    if (effect != NULL) {
        fn_1_191DC(effect);
    }
}

// .text:0x0001957C size:0x3D0
void fn_1_1957C(void) {
    ParticleEffect *effect = allocParticleEffect(fn_1_1857C, 0, 0, gParticleCfg[0], 1, 0x80);

    if (effect != NULL) {
        fn_1_191DC(effect);
    }
}

// .text:0x000191DC size:0x3A0
void fn_1_191DC(ParticleEffect *effect) {
    Particle *p = effect->head;
    u32 i = 0;
    s32 lifeSpan;

    do {
        p->index = i;
        p->sizeX = (f32)gParticleCfg[3] / 100000.0f;
        p->sizeY = (f32)gParticleCfg[4] / 100000.0f;
        fn_1_18EE4(p);
        lifeSpan = gParticleCfg[0] / 5;
        p->life = ((i % 5) * lifeSpan + rand() % lifeSpan) * 2;
        p = p->next;
        i++;
    } while (p != NULL);
}

// .text:0x00018EE4 size:0x2F8
void fn_1_18EE4(Particle *p) {
    u8 base = gParticleCfg[5];
    u8 range = 0xFF - gParticleCfg[5];
    f32 spin;

    p->pos.x = (f32)(p->index * 2) / (f32)gParticleCfg[0] - 1.0f;
    p->pos.y = -1.0f;
    p->pos.z = 50.0f * ((f32)rand() / 32767.0f) + 50.0f;
    fn_1_18E04(p, 0.0f);
    p->rot.x = p->rot.y = p->rot.z = 0.0f;
    spin = (f32)gParticleCfg[2] / 100000.0f;
    p->rotVel.x = spin * ((f32)rand() / 32767.0f);
    p->rotVel.y = spin * ((f32)rand() / 32767.0f);
    p->rotVel.z = spin * ((f32)rand() / 32767.0f);
    p->col1.b[3] = 0xFF;
    p->col0.b[3] = 0xFF;
    p->col0.b[1] = base + rand() % range;
    p->col0.b[2] = base + rand() % range;
    p->col1.b[0] = base + rand() % range;
    p->col1.b[1] = base + rand() % range;
    p->col1.b[2] = base + rand() % range;
}

// .text:0x00018E04 size:0xE0
void fn_1_18E04(Particle *p, f32 angle) {
    f32 s;
    f32 c;
    f32 rad;

    rad = 0.017453292f * angle;
    s = sinf_kludge(rad);
    c = cosf_kludge(rad);
    p->vel.x = s * (f32)gParticleCfg[1] / 100000.0f;
    p->vel.y = c * (f32)gParticleCfg[1] / 100000.0f;
    p->vel.z = 0.0f;
}

// .text:0x0001857C size:0x888
int fn_1_1857C(ParticleEffect *effect) {
    Vec up = {0.0f, 1.0f, 0.0f};
    Vec dir;
    Particle *p;
    f32 angle;
    f32 delta;

    fn_1_18174();
    p = sortParticlesByDepth(effect->head, effect->flags & 0xFFF);
    effect->head = p;
    do {
        if (p->life <= 0) {
            fn_1_182C0(p);
            PSVECAdd(&p->vel, &p->pos, &p->pos);
            PSVECAdd(&p->rotVel, &p->rot, &p->rot);
            if (fabs(p->pos.x) > 1.0) {
                p->pos.x = fabs(p->pos.x) / p->pos.x;
                p->vel.x *= -1.0f;
            } else if (rand() % 5 == 0) {
                memcpy(&dir, &p->vel, sizeof(Vec));
                PSVECNormalize(&dir, &dir);
                angle = 57.29578f * (f32)acos(PSVECDotProduct(&up, &dir));
                if (dir.x < 0.0f) {
                    angle *= -1.0f;
                }
                delta = 20.0 * (2.0 * ((f32)rand() / 32767.0f - 0.5));
                if (fabs(angle + delta) > 20.0) {
                    angle = 20.0 * (fabs(angle) / angle);
                } else {
                    angle = angle + delta;
                }
                fn_1_18E04(p, angle);
            }
            if (p->pos.y > 1.0f) {
                fn_1_18EE4(p);
            }
        } else {
            p->life--;
        }
        p = p->next;
    } while (p != NULL);
    fn_1_17FF0();
    return 0;
}

// .text:0x000182C0 size:0x2BC
void fn_1_182C0(Particle *p) {
    Control ctrl;
    Vec quad[4];
    Mtx mtx;
    Mtx44 proj;
    int i;
    f32 hx = p->sizeX / 2.0f;
    f32 hy = p->sizeY / 2.0f;

    ctrl.type = 0;
    quad[1].x = hx;
    quad[2].x = hx;
    quad[0].x = -hx;
    quad[0].y = -hy;
    quad[1].y = -hy;
    quad[2].y = hy;
    quad[3].x = -hx;
    quad[3].y = hy;
    quad[3].z = 0.0f;
    quad[2].z = 0.0f;
    quad[1].z = 0.0f;
    quad[0].z = 0.0f;
    CTRLSetRotation(&ctrl, p->rot.x, p->rot.y, p->rot.z);
    CTRLSetTranslation(&ctrl, 0.5f * p->pos.x / 2.0f * p->pos.z, 0.35f * p->pos.y / 2.0f * p->pos.z, -1.5f);
    CTRLBuildMatrix(&ctrl, mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
    C_MTXOrtho(proj, -0.175f * p->pos.z, 0.175f * p->pos.z, 0.25f * p->pos.z, -0.25f * p->pos.z, 1.0f, 512.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXSetCullMode(GX_CULL_BACK);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(quad[i].x, quad[i].y, quad[i].z);
        GXColor1u32(p->col0.word);
    }
    GXSetCullMode(GX_CULL_FRONT);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(quad[i].x, quad[i].y, quad[i].z);
        GXColor1u32(p->col1.word);
    }
}

// .text:0x00018174 size:0x14C
void fn_1_18174(void) {
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
}

// .text:0x00017FF0 size:0x184
void fn_1_17FF0(void) {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768_getCamera(0)->view, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(fn_80052768_getCamera(0)->proj, GX_PERSPECTIVE);
}

// .text:0x00017F28 size:0xC8
Particle *sortParticlesByDepth(Particle *head, u32 count) {
    ParticleSortEntry *arr;
    ParticleSortEntry *entry;
    Particle *p;

    arr = _OSAllocFromHeap(0x20, count * sizeof(ParticleSortEntry));
    entry = arr;
    p = head;
    while (p != NULL) {
        entry->particle = p;
        entry->depth = p->pos.z;
        entry++;
        p = p->next;
    }
    fn_800246D4(compareParticleDepth, arr, arr, sizeof(ParticleSortEntry), count);
    head = arr[0].particle;
    entry = arr;
    while (--count) {
        entry->particle->next = (entry + 1)->particle;
        entry++;
    }
    entry->particle->next = NULL;
    fn_800ACFB0(arr);
    return head;
}

// .text:0x00017EFC size:0x2C
int compareParticleDepth(const void *a, const void *b) {
    const ParticleSortEntry *ea = a;
    const ParticleSortEntry *eb = b;

    if (ea->depth < eb->depth) {
        return 1;
    }
    if (ea->depth > eb->depth) {
        return -1;
    }
    return 0;
}
