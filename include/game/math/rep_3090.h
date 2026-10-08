#ifndef __GAME_MATH_REP_3090_H_
#define __GAME_MATH_REP_3090_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

// One sampled step of the camera spline (0x40 bytes). v[0..2] position, v[3..4] extra channels, v[15] cumulative distance.
typedef struct CamSample {
    f32 v[16];
} CamSample;

// One control point of the camera spline (0x34 bytes).
typedef struct CamPoint {
    f32 v[13];
} CamPoint;

// Result block filled in by fn_3_104B3C (0x88 bytes).
typedef struct CamEval {
    f32 m[4][4];
    f32 _40;
    f32 _44;
    f32 _48;
    f32 _4C;
    f32 _50;
    f32 _54;
    VecXYZ _58;
    VecXYZ _64;
    VecXYZ _70;
    f32 _7C;
    f32 _80;
    u8 _84;
} CamEval; // size 0x88

// View description derived from an evaluated camera key (0x58 bytes).
typedef struct CamView {
    VecXYZ pos;
    VecXYZ tgt;
    VecXYZ axes[3];
    f32 fov;
    VecXYZ up;
    f32 _4C;
    f32 _50;
    u8 _54;
} CamView;

// Camera script interpreter state, one per camera view at g_Camera + 0x120 (0x9BC bytes each).
// BEGIN CamScript
typedef struct CamScript {
    /* 0x0000 */ s32* _0000;
    /* 0x0004 */ s32* _0004;
    /* 0x0008 */ s32 _0008;
    /* 0x000C */ s32 _000C;
    /* 0x0010 */ s32 _0010;
    /* 0x0014 */ s32 _0014;
    /* 0x0018 */ s32 _0018;
    /* 0x001C */ CamPoint* _001C;
    /* 0x0020 */ s32 _0020;
    /* 0x0024 */ s32 _0024;
    /* 0x0028 */ VecXYZ _0028;
    /* 0x0034 */ CamSample* _0034;
    /* 0x0038 */ s32 _0038;
    /* 0x003C */ s32 _003C;
    /* 0x0040 */ s32 _0040;
    /* 0x0044 */ s32 _0044;
    /* 0x0048 */ f32 _0048;
    /* 0x004C */ s32 _004C;
    /* 0x0050 */ s32 _0050;
    /* 0x0054 */ s32 _0054;
    /* 0x0058 */ s32 _0058;
    /* 0x005C */ s32 _005C;
    /* 0x0060 */ f32 _0060;
    /* 0x0064 */ VecXYZ _0064;
    u8 _pad0070[0x18];
    /* 0x0088 */ VecXYZ _0088;
    u8 _pad0094[0x4];
    /* 0x0098 */ VecXYZ* _0098;
    /* 0x009C */ f32* _009C;
    /* 0x00A0 */ f32 _00A0;
    /* 0x00A4 */ f32 _00A4;
    /* 0x00A8 */ f32 _00A8;
    /* 0x00AC */ VecXYZ _00AC;
    /* 0x00B8 */ VecXYZ _00B8;
    /* 0x00C4 */ VecXYZ _00C4;
    /* 0x00D0 */ VecXYZ _00D0;
    /* 0x00DC */ VecXYZ _00DC;
    /* 0x00E8 */ VecXYZ _00E8;
    u8 _pad00F4[0xC];
    /* 0x0100 */ f32 _0100;
    /* 0x0104 */ f32 _0104;
    /* 0x0108 */ f32 _0108;
    /* 0x010C */ f32 _010C;
    /* 0x0110 */ f32 _0110;
    /* 0x0114 */ f32 _0114;
    /* 0x0118 */ u32 _0118;
    /* 0x011C */ u32 _011C;
    /* 0x0120 */ s32 _0120;
    /* 0x0124 */ s32 _0124;
    /* 0x0128 */ s32 _0128[0x200];
    /* 0x0928 */ s32 _0928;
    /* 0x092C */ s32 _092C;
    u8 _pad0930[0x4];
    /* 0x0934 */ s32 _0934;
    /* 0x0938 */ s32 _0938;
    /* 0x093C */ s32 _093C;
    /* 0x0940 */ s16 _0940;
    /* 0x0942 */ s16 _0942;
    /* 0x0944 */ s16 _0944;
    /* 0x0946 */ s16 _0946;
    /* 0x0948 */ s16 _0948;
    /* 0x094A */ s16 _094A;
    /* 0x094C */ s16 _094C;
    /* 0x094E */ s16 _094E;
    /* 0x0950 */ s16 _0950;
    u8 _pad0952[0x2];
    /* 0x0954 */ s16 _0954;
    /* 0x0956 */ s16 _0956;
    /* 0x0958 */ s16 _0958;
    /* 0x095A */ s16 _095A;
    u8 _pad095C[0x2];
    /* 0x095E */ s16 _095E;
    /* 0x0960 */ s16 _0960;
    /* 0x0962 */ s16 _0962;
    u8 _pad0964[0x8];
    /* 0x096C */ s16 _096C[4];
    /* 0x0974 */ s16 _0974;
    /* 0x0976 */ s16 _0976;
    u8 _pad0978[0x4];
    /* 0x097C */ s16 _097C;
    u8 _pad097E[0x6];
    /* 0x0984 */ s16 _0984;
    /* 0x0986 */ s16 _0986;
    /* 0x0988 */ s16 _0988;
    u8 _pad098A[0x6];
    /* 0x0990 */ u8* _0990;
    u8 _pad0994[0x7];
    /* 0x099B */ u8 _099B[4];
    /* 0x099F */ u8 _099F;
    u8 _pad09A0[0x7];
    /* 0x09A7 */ u8 _09A7;
    /* 0x09A8 */ u8 _09A8;
    /* 0x09A9 */ u8 _09A9;
    /* 0x09AA */ u8 _09AA;
    /* 0x09AB */ u8 _09AB;
    /* 0x09AC */ u8 _09AC;
    /* 0x09AD */ u8 _09AD;
    /* 0x09AE */ u8 _09AE;
    /* 0x09AF */ u8 _09AF;
    /* 0x09B0 */ u8 _09B0;
    /* 0x09B1 */ u8 _09B1;
    /* 0x09B2 */ u8 _09B2;
    /* 0x09B3 */ u8 _09B3;
    /* 0x09B4 */ u8 _09B4;
    /* 0x09B5 */ u8 _09B5;
    /* 0x09B6 */ u8 _09B6;
    /* 0x09B7 */ u8 _09B7;
    u8 _pad09B8[0x1];
    /* 0x09B9 */ u8 _09B9;
    u8 _pad09BA[0x2];
} CamScript; // size 0x9BC
// END CamScript

void fn_3_FC448(void);
void fn_3_FC938(void);
int fn_3_FCE38(int idx, f32 t);
void fn_3_FCEAC(void);
int fn_3_FCEB0(f32 t);
void fn_3_FCF20(void);
void fn_3_FCF24(void);
void fn_3_FD408(u32 idx, VecXYZ* outPos, f32* outExtra);
void fn_3_FD4DC(void);
void fn_3_FD51C(int idx);
void fn_3_FD5A8(void);
void fn_3_FD670(void);
BOOL fn_3_FD9FC(void);
void manageDrawingItemState(void);
BOOL fn_3_FDB30(void);
BOOL fn_3_100018(void);
void fn_3_100038(void);
BOOL unkPauseSimulationCheck(void);
void fn_3_1000D8(void);
void fn_3_101CC4(void);
void fn_3_103C30(VecXYZ* v);
void fn_3_103E7C(f32* angles);
void fn_3_1040D8(void);
void fn_3_104338(void);
void fn_3_1045A8(void);
void fn_3_104740(void);
void fn_3_1048E0(u8* script, u32 time, s16 a, u8 b, CamView* out);
void fn_3_104A3C(Vec* out, Mtx44 m);
void fn_3_104A88(Vec* out, Mtx44 m);
void fn_3_104AD4(Vec* out, Mtx44 m);
void fn_3_104B20(Vec* out, CamView* view);
void fn_3_104B3C(u8* script, u32 time, s16 a, u8 b, CamEval* out);
void fn_3_1054CC(void);
void fn_3_1054D0(u8* script, u32 time, s16 trackIdx);
void fn_3_105A10(Vec* out, Vec* a, Vec* b, f32 t);
void fn_3_105ACC(f32* quat, Mtx out);
void fn_3_105BD8(CamEval* e);
u32 fn_3_105C28(u8* script, u32 time);
void fn_3_105C84(u8* hdr);
void fn_3_105CDC(void);
void fn_3_105E00(s16 x, s16 y, s16 w, s16 h);
void fn_3_106014(f32 x, f32 y, f32 z);
void fn_3_1060D8(void);
BOOL fn_3_10617C(int idx, int bone, Vec* out);
void fn_3_106270(VecXYZ* v);
int fn_3_10698C(u32* table);
u8* fn_3_1069B0(u32* table, int idx);
void fn_3_1069C0(void);
void fn_3_106BA0(void);

#endif // !__GAME_MATH_REP_3090_H_
