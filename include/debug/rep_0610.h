#ifndef __UNUSED_REL_REP_0610_H_
#define __UNUSED_REL_REP_0610_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTypes.h"
#include "C3/control.h"

typedef struct DbgActorExt DbgActorExt;
typedef struct DbgLight DbgLight;

typedef struct DbgPartData {
    /*0x00*/ f32 value;
    /*0x04*/ u8 pad4[8];
    /*0x0C*/ u32 flag;
} DbgPartData;

typedef struct DbgPart {
    /*0x00*/ u16 h0;
    /*0x02*/ u8 pad2[0x12];
    /*0x14*/ u32 f14;
    /*0x18*/ u8 pad18[0x64 - 0x18];
    /*0x64*/ f32 f64;
    /*0x68*/ f32 f68;
    /*0x6C*/ f32 f6C;
    /*0x70*/ u8 pad70[0xE8 - 0x70];
    /*0xE8*/ DbgPartData *data;
    /*0xEC*/ u8 padEC[0x136 - 0xEC];
    /*0x136*/ u8 fb136;
} DbgPart;

typedef struct DbgModel {
    /*0x00*/ u8 pad0[6];
    /*0x06*/ u16 count;
    /*0x08*/ u8 pad8[8];
    /*0x10*/ u32 f10;
    /*0x14*/ u8 pad14[4];
    /*0x18*/ DbgPart **parts;
    /*0x1C*/ u8 pad1C[0x98 - 0x1C];
    /*0x98*/ u8 f98;
} DbgModel;

/* Same layout as ActorObjectEntry (Unknown/File_0x800bdd74.h), with the actor typed as the model view used here. */
typedef struct DbgActorEnt {
    /*0x00*/ DbgModel *model;
    /*0x04*/ void *anim;
    /*0x08*/ u8 pad8[6];
    /*0x0E*/ u16 seqNum;
    /*0x10*/ Control control;
    /*0x54*/ f32 speed;
    /*0x58*/ u8 animPending;
    /*0x59*/ u8 framePending;
    /*0x5A*/ u8 speedPending;
    /*0x5B*/ u8 boneParam;
    /*0x5C*/ f32 frame;
    /*0x60*/ f32 blendTime;
    /*0x64*/ u8 pad64[4];
    /*0x68*/ u32 unk68;
    /*0x6C*/ u8 applyControl;
    /*0x6D*/ u8 pad6D[0x90 - 0x6D];
} DbgActorEnt; // size 0x90

/* Table returned by ActorObjectInitTable(n): a count header, then n entries from +0x34. */
typedef struct DbgActorTbl {
    /*0x00*/ u16 count;
    /*0x02*/ u8 pad2[0x34 - 0x2];
    /*0x34*/ DbgActorEnt e[1];
} DbgActorTbl;

typedef struct DbgAnimTrack {
    /*0x0*/ u32 f0;
    /*0x4*/ f32 *keys;
    /*0x8*/ u16 count;
} DbgAnimTrack; // size 0xC

typedef struct DbgAnimEntry {
    /*0x00*/ u8 pad0[4];
    /*0x04*/ DbgAnimTrack *p4;
    /*0x08*/ u16 f8;
    /*0x0A*/ u16 count;
} DbgAnimEntry;

typedef struct DbgActor {
    /*0x000*/ DbgModel *model;
    /*0x004*/ DbgModel *p4;
    /*0x008*/ DbgModel *p8;
    /*0x00C*/ u8 padC[4];
    /*0x010*/ DbgAnimEntry *tbl[(0x30 - 0x10) / 4];
    /*0x030*/ DbgActorExt *ext;
    /*0x034*/ Vec pos;
    /*0x040*/ f32 rotX;
    /*0x044*/ f32 rotY;
    /*0x048*/ f32 rotZ;
    /*0x04C*/ u8 pad4C[0x62 - 0x4C];
    /*0x062*/ u16 h62;
    /*0x064*/ u8 pad64[0x162 - 0x64];
    /*0x162*/ u16 partIdx[0x78]; // model part index by part id, 0xFFFF = none
    /*0x252*/ s8 f252;
    /*0x253*/ u8 pad253;
    /*0x254*/ u8 f254;
    /*0x255*/ u8 f255;
    /*0x256*/ u8 pad256[0x25A - 0x256];
    /*0x25A*/ u8 f25A;
    /*0x25B*/ u8 f25B;
    /*0x25C*/ u8 pad25C[0x276 - 0x25C];
    /*0x276*/ u8 flags;
    /*0x277*/ u8 f277;
    /*0x278*/ u8 f278;
    /*0x279*/ u8 pad279[0x27C - 0x279];
} DbgActor; // size 0x27C

typedef struct DbgHuge {
    /*0x000*/ u8 pad0[0x60];
    /*0x060*/ DbgActorTbl *objs;
    /*0x064*/ u8 pad64[0xAC - 0x64];
    /*0x0AC*/ DbgLight *lights[4];
    /*0x0BC*/ u8 padBC[0xC04 - 0xBC];
    /*0xC04*/ DbgActor slots[4];
    /*0x15F4*/ u8 pad15F4[0x2C50 - 0x15F4];
    /*0x2C50*/ DbgActor *actors[13];
    /*0x2C84*/ void *f2C84;
    /*0x2C88*/ u8 pad2C88[0x3083 - 0x2C88];
    /*0x3083*/ u8 f3083;
    /*0x3084*/ u8 f3084;
} DbgHuge;

extern DbgHuge hugeAnimStruct;

typedef struct DbgGauge {
    /*0x00*/ u8 pad0[0x54];
    /*0x54*/ f32 value;
    /*0x58*/ u8 pad58[2];
    /*0x5A*/ u8 dirty;
} DbgGauge;

typedef struct DbgGaugeLink {
    /*0x00*/ u8 pad0[4];
    /*0x04*/ f32 value;
    /*0x08*/ u8 pad8[9];
    /*0x11*/ u8 bits0 : 3;
    u8 mode : 2;
    u8 bits1 : 3;
} DbgGaugeLink;

typedef struct DbgScene {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct DbgScene *prev;
    /*0x08*/ struct DbgScene *next;
    /*0x0C*/ struct DbgScene *parent;
    /*0x10*/ s16 state;
    /*0x12*/ u16 priority;
    /*0x14*/ void *data;
    /*0x18*/ u16 count;
    /*0x1A*/ u8 pad1A[2];
    /*0x1C*/ u32 tick;
} DbgScene;

typedef struct DbgSceneB {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 pad4[0xC];
    /*0x10*/ s16 state;
    /*0x12*/ u16 priority;
    /*0x14*/ u8 b14;
    /*0x15*/ s8 b15;
    /*0x16*/ u8 pad16[0xA];
    /*0x20*/ u8 b20;
} DbgSceneB;

typedef struct DbgSceneT {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 pad4[0xC];
    /*0x10*/ s16 state;
    /*0x12*/ u16 priority;
    /*0x14*/ u8 pad14[0xC];
    /*0x20*/ s32 w20;
    /*0x24*/ s32 w24;
} DbgSceneT;

typedef struct DbgLightHolder {
    /*0x00*/ u8 pad0[0x70];
    /*0x70*/ void *light70;
} DbgLightHolder;

typedef struct DbgRowEnt {
    /*0x0*/ u8 kind;
    /*0x1*/ u8 c;
    /*0x2*/ s16 a;
    /*0x4*/ s16 b;
    /*0x6*/ s16 d;
} DbgRowEnt;

typedef struct DbgRow {
    /*0x00*/ char name[0x10];
    /*0x10*/ DbgRowEnt ent[8];
} DbgRow; // size 0x50

typedef struct DbgSlotEnt {
    /*0x0*/ s16 f0;
    /*0x2*/ s16 f2;
    /*0x4*/ s16 f4;
    /*0x6*/ s16 f6;
} DbgSlotEnt;

typedef struct DbgRowTbl {
    /*0x0*/ s16 cur;
    /*0x2*/ s16 sel;
    /*0x4*/ DbgRow *tbl;
} DbgRowTbl;

typedef struct DbgDrawRow {
    /*0x00*/ s32 id;
    /*0x04*/ void *fn;
    /*0x08*/ Mtx mtx;
} DbgDrawRow; // size 0x38

typedef struct DbgCallRow {
    /*0x0*/ s32 id;
    /*0x4*/ void (*fn)(void);
} DbgCallRow; // size 0x8

typedef struct DbgSel {
    /*0x00*/ u8 pad0[0x44];
    /*0x44*/ u8 f44;
    /*0x45*/ u8 f45;
    /*0x46*/ u8 f46;
    /*0x47*/ u8 pad47;
} DbgSel; // size 0x48

typedef struct DbgBuf30C0 {
    /*0x00*/ f32 f0[6];
    /*0x18*/ u8 pad18[0x38];
    /*0x50*/ f32 f50;
    /*0x54*/ u8 pad54[4];
    /*0x58*/ Mtx mtx58;
    /*0x88*/ u8 pad88[0xA0];
    /*0x128*/ Vec v128;
    /*0x134*/ u8 pad134[0xC];
    /*0x140*/ Vec v140;
    /*0x14C*/ u8 pad14C[8];
} DbgBuf30C0; // size 0x154

typedef struct DbgBuf68FC {
    /*0x00*/ u8 pad0[0x10];
    /*0x10*/ Mtx mtx10;
    /*0x40*/ E(u8, CHAR_ID) f40[4]; // character per player slot
} DbgBuf68FC; // size 0x44

typedef struct DbgBuf67E0 {
    /*0x00*/ Mtx mtx0;
    /*0x30*/ u8 light30[0xC0];
    /*0xF0*/ u16 fF0;
    /*0xF2*/ u16 fF2;
    /*0xF4*/ f32 fF4;
    /*0xF8*/ f32 fF8;
    /*0xFC*/ f32 fFC;
    /*0x100*/ f32 f100;
    /*0x104*/ f32 f104;
    /*0x108*/ f32 f108;
    /*0x10C*/ f32 f10C;
    /*0x110*/ f32 f110;
    /*0x114*/ u32 f114;
    /*0x118*/ u8 f118;
    /*0x119*/ u8 pad119[3];
} DbgBuf67E0; // size 0x11C

typedef struct DbgBlob {
    /*0x00*/ u8 pad0[8];
    /*0x08*/ Mtx mtx8;
} DbgBlob;

struct DbgLight {
    /*0x00*/ u8 pad0[0x40];
    /*0x40*/ f32 f40;
    /*0x44*/ f32 f44;
    /*0x48*/ f32 f48;
    /*0x4C*/ u8 pad4C[0xC];
    /*0x58*/ f32 f58;
    /*0x5C*/ f32 f5C;
    /*0x60*/ f32 f60;
    /*0x64*/ u8 pad64[0xC];
    /*0x70*/ u8 r;
    /*0x71*/ u8 g;
    /*0x72*/ u8 b;
};

typedef struct DbgPairObj {
    /*0x000*/ u8 pad0[0x72];
    /*0x072*/ u16 a[0x78];
    /*0x162*/ u16 b[0x78];
} DbgPairObj;

typedef struct DbgSceneP {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 pad4[0xC];
    /*0x10*/ s16 state;
    /*0x12*/ u16 priority;
    /*0x14*/ Vec pos;
    /*0x20*/ Vec vel;
    /*0x2C*/ Vec acc;
    /*0x38*/ s32 w38;
    /*0x3C*/ u16 h3C;
    /*0x3E*/ E(u8, BOOL) b3E;
    /*0x3F*/ E(u8, BOOL) b3F;
} DbgSceneP;

struct DbgActorExt {
    /*0x00*/ u8 pad0[4];
    /*0x04*/ u8 blk4[0x5C];
    /*0x60*/ u8 b60;
    /*0x61*/ u8 pad61[7];
    /*0x68*/ u8 blk68[0x5C];
    /*0xC4*/ u8 bC4;
    /*0xC5*/ u8 padC5[8];
    /*0xCD*/ u8 bCD;
    /*0xCE*/ u8 bCE;
    /*0xCF*/ u8 bCF;
    /*0xD0*/ u8 bD0;
};

typedef struct DbgPtc {
    /*0x00*/ f32 f0;
    /*0x04*/ u8 pad4[4];
    /*0x08*/ u16 h8;
    /*0x0A*/ u8 padA[2];
    /*0x0C*/ u16 hC;
    /*0x0E*/ u8 padE[0xA];
    /*0x18*/ u16 h18;
    /*0x1A*/ u16 h1A;
    /*0x1C*/ void *p1C;
} DbgPtc; // size 0x20

typedef struct DbgFog {
    /*0x00*/ f32 f0;
    /*0x04*/ f32 f4;
    /*0x08*/ f32 f8;
    /*0x0C*/ f32 fC;
    /*0x10*/ u8 pad10[4];
    /*0x14*/ u16 h14;
    /*0x16*/ u8 pad16;
    /*0x17*/ u8 f17;
    /*0x18*/ u8 pad18[5];
    /*0x1D*/ u8 f1D;
} DbgFog;

typedef struct DbgData1F1A {
    /*0x00*/ u8 f0;
    /*0x01*/ u8 f1;
} DbgData1F1A;

typedef struct DbgFx {
    /*0x00*/ u32 f0;
    /*0x04*/ s32 f4;
    /*0x08*/ f32 f8;
    /*0x0C*/ u32 fC;
    /*0x10*/ f32 f10;
    /*0x14*/ Vec v14;
    /*0x20*/ s16 h20;
    /*0x22*/ s16 h22;
    /*0x24*/ Vec v24;
} DbgFx;

typedef struct DbgTreeNode {
    /*0x00*/ u8 pad0[8];
    /*0x08*/ struct DbgTreeNode *sibling;
    /*0x0C*/ u8 padC[4];
    /*0x10*/ struct DbgTreeNode *child;
} DbgTreeNode;

typedef struct DbgFileEnt {
    /*0x0*/ const char *name;
    /*0x4*/ u32 w4;
    /*0x8*/ u32 w8;
    /*0xC*/ u32 wC;
} DbgFileEnt;

typedef struct DbgF570 {
    /*0x00*/ f32 scale;
    /*0x04*/ u32 colA;
    /*0x08*/ f32 f2;
    /*0x0C*/ f32 f3;
    /*0x10*/ u32 colB;
    /*0x14*/ u32 colC;
} DbgF570;

s32 fn_1_C2DC(DbgTreeNode *n, char *buf, s32 pos, s32 w, s32 ret, s32 *rows, s32 *skip, s32 *left);
void fn_1_C5A8(void);
void fn_1_C5AC(void);
void fn_1_C9E0(DbgBlob *blob);
void fn_1_CB9C(BOOL flag);
void fn_1_CC24(void);
void fn_1_CCC8(void);
void fn_1_CDC8(void);
void fn_1_D13C(void);
void fn_1_D2F0(void);
DbgActor *fn_1_D300(DbgActor *src);
void fn_1_D4BC(void);
void fn_1_D590(s32 a, s32 b, f32 v);
u8 fn_1_D638(void);
void fn_1_D650(void);
BOOL fn_1_D660(void);
void fn_1_D67C(u8 value);
void fn_1_D688(void);
void fn_1_D6B4(void);
const char *fn_1_D6E4(void);
f32 fn_1_D71C(s32 idx);
void fn_1_D7A4(s32 row);
void fn_1_D8A0(void);
void fn_1_D9B8(void);
void fn_1_DE1C(void);
void fn_1_DF14(void);
void fn_1_E098(void);
void fn_1_E8D4(void);
void fn_1_E9F8(DbgModel *m, s32 start, s32 count);
void fn_1_EA20(void);
void fn_1_ECF8(s32 idx, s32 kind, s32 flag);
void fn_1_F040(void);
void fn_1_F0D0(void);
void fn_1_F1D8(void);
void fn_1_F2F8(void);
void fn_1_F37C(void);
void fn_1_F50C(void);
void fn_1_F6E4(void);
void fn_1_F798(s32 *vals, u8 *map, s32 n);
void fn_1_FB98(void);
void fn_1_10044(void);
void fn_1_10458(void);
void fn_1_10560(void);
void fn_1_10670(void);
u32 fn_1_106A4(void);
void fn_1_106B4(void);
void fn_1_106C4(void);
void fn_1_1073C(DbgActor *a);
void fn_1_107B8(void);
void fn_1_10AA4(DbgGauge *g, f32 v);
void fn_1_10ACC(Mtx m, Vec *p, s32 unused, GXColor *c, f32 size);
void fn_1_10CEC(DbgBlob *blob);
void fn_1_10E2C(Mtx m, Mtx cam, u32 c0, u32 c1, u32 c2);
void fn_1_1125C(DbgBlob *blob);
void fn_1_116EC(void *tex);
void fn_1_11714(DbgBlob *blob);
void fn_1_11C98(void);
void fn_1_11D00(DbgBuf67E0 *p);
void fn_1_11F08(DbgBuf67E0 *p);
void fn_1_121D4(DbgBuf67E0 *p);
void fn_1_126CC(void);
void fn_1_12820(DbgActorTbl *objs, Mtx cam);
void fn_1_129D0(void);
void fn_1_12F18(DbgBlob *s);
void fn_1_12F8C(DbgActorTbl *objs, Mtx cam);
void fn_1_131E4(void);
void fn_1_1347C(void);
void fn_1_135C0(void);
void fn_1_14710(DbgPairObj *o);
void fn_1_14888(DbgLightHolder *h);
void fn_1_148CC(void);
void fn_1_14928(void);
void fn_1_1496C(void);
void fn_1_14FB8(void);
void fn_1_15170(void);
void fn_1_151F8(void);
void fn_1_1540C(void);
void fn_1_15760(void);
void fn_1_15CE0(void);
s32 fn_1_160D8(s8 a, s8 b);
void fn_1_160F8(s32 dir);
void fn_1_161D0(void);
void fn_1_1620C(void);
void fn_1_163FC(void);
void fn_1_16400(s8 delta);
void fn_1_1644C(void);
u32 fn_1_16558(s32 a, s32 b);
u32 fn_1_16590(void);
void fn_1_165E0(void);
void fn_1_168C8(void);
void fn_1_16978(void);
void fn_1_176EC(void);
void fn_1_1770C(void);
void fn_1_17954(void);
void fn_1_179CC(void);
void fn_1_17B5C(void);
void fn_1_17D90(void);

#endif // !__UNUSED_REL_REP_0610_H_
