#ifndef __MENUS_REP_1028_H_
#define __MENUS_REP_1028_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ u8 _pad0[0x78 - 0x48];
    /* 0x78 */ int index;
    /* 0x7C */ int unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ s16 state;
    /* 0x92 */ s16 unk92;
    /* 0x94 */ s16 unk94;
    /* 0x96 */ u8 _pad1[0x9C - 0x96];
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ u8 _pad2[2];
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ u8 _pad3[4];
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ u8 unkA8;
    /* 0xA9 */ u8 unkA9;
    /* 0xAA */ u8 unkAA;
    /* 0xAB */ u8 unkAB;
    /* 0xAC */ u8 unkAC;
    /* 0xAD */ u8 unkAD;
    /* 0xAE */ u8 unkAE;
    /* 0xAF */ u8 _pad4[0xB2 - 0xAF];
    /* 0xB2 */ u8 unkB2;
    /* 0xB3 */ u8 unkB3;
    /* 0xB4 */ u8 unkB4;
    /* 0xB5 */ u8 unkB5;
    /* 0xB6 */ u8 _pad5[0xBC - 0xB6];
} UnkObjBC; // size 0xBC

typedef struct {
    /* 0x0000 */ u8 _pad0[0x1610];
    /* 0x1610 */ Vec unk1610;
    /* 0x161C */ u8 _pad1[0x16E8 - 0x161C];
    /* 0x16E8 */ Vec unk16E8;
    /* 0x16F4 */ u8 _pad2[0x21E0 - 0x16F4];
    /* 0x21E0 */ UnkObjBC objs[29];
    /* 0x372C */ u8 _pad3[0x43BE - 0x372C];
    /* 0x43BE */ s16 unk43BE;
} Unk1A8248;   // only the objs[]/unk1610/unk16E8/unk43BE regions are known; element count unverified

typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ int unk4;
    /* 0x08 */ u8 _pad0[0x0E - 0x08];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 _pad1[0x54 - 0x10];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59;
    /* 0x5A */ u8 unk5A;
    /* 0x5B */ u8 unk5B;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ u8 _pad2[0x90 - 0x64];
} UnkElem90; // size 0x90

typedef struct {
    /* 0x00 */ u8 _pad0[0x34];
    /* 0x34 */ UnkElem90 elems[16];
} Unk340140Inner;

typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u8 unk4[0x0C];
    /* 0x10 */ u8 _pad0[4];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 _pad1[0x26 - 0x18];
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 _pad2;
} UnkRec28; // size 0x28

typedef struct {
    /* 0x0000 */ u8 _pad0[0x68];
    /* 0x0068 */ Unk340140Inner *unk68;
    /* 0x006C */ u8 _pad1[0x2D94 - 0x6C];
    /* 0x2D94 */ UnkRec28 *unk2D94;
    /* 0x2D98 */ u8 _pad2[0x3078 - 0x2D98];
    /* 0x3078 */ u16 unk3078;
} Unk340140;

typedef struct {
    /* 0x00 */ u8 _pad0[0x0C];
    /* 0x0C */ int unkC[10];
    /* 0x34 */ int unk34;
    /* 0x38 */ int unk38;
    /* 0x3C */ int unk3C;
    /* 0x40 */ int unk40;
    /* 0x44 */ int unk44;
    /* 0x48 */ int unk48;
    /* 0x4C */ int unk4C;
} Unk3401BC;

typedef struct {
    /* 0x00 */ u8 data[0x0C];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 _pad0[4];
} UnkRec14; // size 0x14

void fn_2_8F0F4(int idx);
void fn_2_8F27C(int idx);
void fn_2_8F3D4(int idx);
void fn_2_8F528(int idx);
void fn_2_8F640(void);
void fn_2_8F688(void);
void fn_2_8F6D0(int idx, int entryIdx);
int fn_2_8F720(int idx);
void fn_2_8F73C(int idx, u8 val);
void fn_2_8F758(int idx, u8 val);
void fn_2_8F774(int idx);
void fn_2_8F7B0(int idx, s16 arg1);
void fn_2_8F838(int idx, s16 arg1);
void fn_2_8F8C0(int idx, s16 arg1);
void fn_2_8F948(int idx, s16 arg1);
void fn_2_8F9D0(int idx, s16 arg1);
void fn_2_8FA58(int idx, s16 arg1);
void fn_2_8FAE0(int idx, s16 arg1);
void fn_2_8FB68(int idx, s16 arg1);
void fn_2_8FBF8(int idx, s16 arg1);
void fn_2_8FC88(int idx);
void fn_2_8FD14(void);
void fn_2_8FDB0(int idx);
void fn_2_8FE9C(int idx);
void fn_2_9007C(void);
void fn_2_9033C(int idx, void *src, f32 f);
void fn_2_903A8(int idx);
void fn_2_90428(int idx);
void fn_2_904A8(void);
void fn_2_90538(void);
void fn_2_9061C(UnkObjBC *obj);
void fn_2_90628(UnkObjBC *obj);
void fn_2_90698(UnkObjBC *obj);
void fn_2_90718(UnkObjBC *obj);
void fn_2_907F4(UnkObjBC *obj);
void fn_2_9082C(UnkObjBC *obj);
void fn_2_90838(UnkObjBC *obj);
void fn_2_90888(UnkObjBC *obj);
void fn_2_908FC(UnkObjBC *obj);
void fn_2_90934(UnkObjBC *obj);
void fn_2_90940(UnkObjBC *obj);
void fn_2_9094C(UnkObjBC *obj);
void fn_2_909F4(UnkObjBC *obj);
void fn_2_90A2C(UnkObjBC *obj);
void fn_2_90AB0(UnkObjBC *obj);
void fn_2_90ABC(UnkObjBC *obj);
void fn_2_90BD0(UnkObjBC *obj);
void fn_2_90C08(UnkObjBC *obj);
void fn_2_90C14(UnkObjBC *obj);
void fn_2_90C4C(UnkObjBC *obj);
void fn_2_90CD0(UnkObjBC *obj);
void fn_2_90DAC(UnkObjBC *obj);
void fn_2_90DE4(UnkObjBC *obj, f32 limit);
void fn_2_90E98(UnkObjBC *obj);
void fn_2_90EC4(UnkObjBC *obj);
void fn_2_91058(UnkObjBC *obj);
void fn_2_911E0(UnkObjBC *obj);
void fn_2_91218(UnkObjBC *obj);
void fn_2_9129C(UnkObjBC *obj);
void fn_2_912A8(UnkObjBC *obj);
void fn_2_91450(UnkObjBC *obj);
void fn_2_91488(UnkObjBC *obj);
void fn_2_9150C(UnkObjBC *obj);
void fn_2_91518(UnkObjBC *obj);
void fn_2_916C0(UnkObjBC *obj);
void fn_2_916F8(UnkObjBC *obj);
void fn_2_9177C(UnkObjBC *obj);
void fn_2_91788(UnkObjBC *obj);
void fn_2_918A4(UnkObjBC *obj);
void fn_2_918DC(UnkObjBC *obj);
void fn_2_918E8(UnkObjBC *obj);
void fn_2_918F4(UnkObjBC *obj);
void fn_2_9197C(UnkObjBC *obj);
void fn_2_919B4(UnkObjBC *obj);
void fn_2_919C0(UnkObjBC *obj);
void fn_2_919CC(UnkObjBC *obj);
void fn_2_91AE4(UnkObjBC *obj);
void fn_2_91B1C(UnkObjBC *obj);
void fn_2_91B28(void);
void fn_2_91B2C(UnkObjBC *obj);
void fn_2_91B38(UnkObjBC *obj);
void fn_2_91B70(UnkObjBC *obj);
void fn_2_91B7C(void);
void fn_2_91B80(UnkObjBC *obj);
void fn_2_91C08(UnkObjBC *obj);
void fn_2_91C40(UnkObjBC *obj);
void fn_2_91C4C(UnkObjBC *obj);
void fn_2_91D74(UnkObjBC *obj);

#endif // !__MENUS_REP_1028_H_
