#ifndef __UNUSED_REL_REP_74A0_H_
#define __UNUSED_REL_REP_74A0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTypes.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800b0a14.h"

typedef struct Particle {
    /*0x00*/ struct Particle *next;
    /*0x04*/ Vec pos;
    /*0x10*/ Vec vel;
    /*0x1C*/ Vec rot;
    /*0x28*/ Vec rotVel;
    /*0x34*/ f32 unk34;
    /*0x38*/ f32 sizeX;
    /*0x3C*/ f32 sizeY;
    /*0x40*/ union {
        u32 word;
        u8 b[4];
    } col0;
    /*0x44*/ union {
        u32 word;
        u8 b[4];
    } col1;
    /*0x48*/ s16 life;
    /*0x4A*/ s16 index;
} Particle;

typedef struct ParticleEffect {
    /*0x00*/ u8 pad00[0xC];
    /*0x0C*/ Particle *head;
    /*0x10*/ u8 pad10[4];
    /*0x14*/ u16 flags;
} ParticleEffect;

typedef struct ParticleSortEntry {
    Particle *particle;
    f32 depth;
} ParticleSortEntry;

typedef struct DbgScene {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 pad04[8];
    /*0x0C*/ DrawingSceneStruct *parent;
    /*0x10*/ s16 state;
    /*0x12*/ u8 pad12[2];
    /*0x14*/ u8 slot;
    /*0x15*/ u8 cursor;
    /*0x16*/ u8 mode16;
    /*0x17*/ u8 mode17;
    /*0x18*/ u8 mode18;
} DbgScene;

typedef struct DbgSlot {
    /*0x000*/ u8 pad000[4];
    /*0x004*/ void *actor;
    /*0x008*/ u32 *file;
    /*0x00C*/ u8 pad00C[4];
    /*0x010*/ void *anim;
    /*0x014*/ u8 pad014[0x20];
    /*0x034*/ Vec pos;
    /*0x040*/ Vec rot;
    /*0x04C*/ f32 speed;
    /*0x050*/ u8 pad050[0x20D];
    /*0x25D*/ u8 isFirst;
    /*0x25E*/ u8 pad25E[0x1E];
} DbgSlot;

typedef struct DbgAnim {
    /*0x000*/ u8 pad000[0x60];
    /*0x060*/ ActorObjectTable *table;
    /*0x064*/ u8 pad064[0x48];
    /*0x0AC*/ void *lights[4];
    /*0x0BC*/ u8 pad0BC[0xC04 - 0xBC];
    /*0xC04*/ DbgSlot slots[24];
} DbgAnim;

typedef struct DbgCamera {
    /*0x00*/ Mtx view;
    /*0x30*/ u16 yaw;
    /*0x32*/ u16 pitch;
    /*0x34*/ f32 strafe;
    /*0x38*/ f32 forward;
    /*0x3C*/ Vec target;
    /*0x48*/ Vec eye;
    /*0x54*/ u8 pad54[8];
} DbgCamera;

typedef struct DbgView {
    /*0x00*/ u8 pad00[0x10];
    /*0x10*/ Mtx mtx;
    /*0x40*/ u8 visible[24];
    /*0x58*/ u8 pad58[0x40];
} DbgView;

typedef struct DbgTexEntry {
    /*0x00*/ void *data;
    /*0x04*/ void *clut;
    /*0x08*/ u16 height;
    /*0x0A*/ u16 width;
    /*0x0C*/ u8 pad0C[0xB];
    /*0x17*/ u8 format;
    /*0x18*/ u16 clutCount;
    /*0x1A*/ u8 clutFormat;
    /*0x1B*/ u8 pad1B[5];
} DbgTexEntry;

typedef struct DbgTexHeader {
    /*0x00*/ u16 count;
    /*0x02*/ u8 pad02[0x1E];
    /*0x20*/ u16 index;
    /*0x22*/ u8 pad22[2];
} DbgTexHeader;

typedef struct DbgVtxArray {
    /*0x00*/ void *data;
    /*0x04*/ u8 pad04[2];
    /*0x06*/ u8 format;
    /*0x07*/ u8 stride;
    /*0x08*/ u8 pad08[8];
} DbgVtxArray;

typedef struct DbgDrawListEntry {
    /*0x00*/ u8 kind;
    /*0x01*/ u8 pad01[3];
    /*0x04*/ u32 vtxDescBits;
    /*0x08*/ void *displayList;
    /*0x0C*/ u32 displayListSize;
} DbgDrawListEntry;

typedef struct DbgDrawList {
    /*0x00*/ u8 pad00[4];
    /*0x04*/ DbgDrawListEntry *entries;
    /*0x08*/ u16 count;
} DbgDrawList;

typedef struct DbgDispObj {
    /*0x00*/ DbgVtxArray *vertices;
    /*0x04*/ u8 pad04[4];
    /*0x08*/ DbgVtxArray *texData;
    /*0x0C*/ u8 pad0C[4];
    /*0x10*/ DbgDrawList *drawList;
    /*0x14*/ u8 numTex;
    /*0x15*/ u8 pad15[3];
    /*0x18*/ Mtx mtx;
} DbgDispObj;

/* ActorObjectEntry.callback is declared void(void) in the shared header, but it
 * is invoked with the entry itself as the argument (see fn_1_1D0E8). */
typedef void (*DbgEntryCallback)(ActorObjectEntry *entry);

typedef struct DbgDrawEntry {
    u32 tag;
    void (*func)(void);
} DbgDrawEntry;

int fn_1_19D1C(u8 fmt);
void fn_1_182C0(Particle *p);
int fn_1_1857C(ParticleEffect *effect);
void fn_1_18E04(Particle *p, f32 angle);
void fn_1_18EE4(Particle *p);
void fn_1_191DC(ParticleEffect *effect);
void fn_1_1957C(void);
void fn_1_1994C(void);
void fn_1_19D60(DbgDispObj *obj, Mtx cam);
void fn_1_1A1EC(ActorObjectEntry *entry, Mtx cam);
void fn_1_1A290(ActorObjectTable *table, Mtx cam);
void fn_1_1A3B4(void);
void fn_1_1A774(void);
void fn_1_1A850(Mtx obj, Mtx cam, u8 r, u8 g, u8 b, u8 a);
void fn_1_1ADA4(void);
void fn_1_1B038(void);
void fn_1_1B0FC(void);
void fn_1_1B2C8(void);
void fn_1_1B424(void);
void fn_1_1B6BC(void);
void fn_1_1B7DC(void);
void fn_1_1C3CC(void);
void fn_1_1C8C0(void);
void fn_1_1CBE4(void);
void fn_1_1D0E8(ActorObjectEntry *entry);
void fn_1_1D10C(void);
void fn_1_1D110(void);
void fn_1_1D450(void);
void fn_1_1D470(void);
void fn_1_1D514(void);

#endif // !__UNUSED_REL_REP_74A0_H_
