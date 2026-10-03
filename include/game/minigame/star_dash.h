#ifndef __GAME_MINIGAME_STAR_DASH_H_
#define __GAME_MINIGAME_STAR_DASH_H_

#include "mssbTypes.h"
#include "Dolphin/gx.h"
#include "game/UnknownHomes_Game.h"
#include "game/ball/collision_primitives.h"
#include "static/UnknownHomes_Static.h"

typedef struct {
    /*0x00*/ f32 score;
    /*0x04*/ s32 coin;
    /*0x08*/ f32 x;
    /*0x0C*/ f32 z;
    /*0x10*/ u8 quadrant;
    /*0x11*/ u8 valid;
    /*0x12*/ u8 _12[2];
} SDCoinEntry; // size: 0x14

typedef struct _SDItem {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ VecXYZ vel;
    /*0x18*/ VecXYZ rot;
    /*0x24*/ VecXYZ rotVel;
    /*0x30*/ f32 _30;
    /*0x34*/ f32 _34;
    /*0x38*/ s16 timer;
    /*0x3A*/ s16 frames;
    /*0x3C*/ s8 owner;
    /*0x3D*/ u8 state;
    /*0x3E*/ u8 _3E;
    /*0x3F*/ u8 _3F;
} SDItem; // size: 0x40

void fn_3_132EDC(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords);
void fn_3_1330E4(void);
void fn_3_133200(void);
void fn_3_133320(void);
void fn_3_13334C(void);
BOOL fn_3_1344BC(int a, int b);
s16 fn_3_1345AC(s16 a, s16 b, u32 c);
void fn_3_134658(u32 target, f32* outX, f32* outZ, u32* outQuadrant);
int fn_3_13493C(u32 player, f32* targetX, f32* targetZ, u32 depth);
BOOL fn_3_134C80(u32 player, int a, u32 b, f32 x, f32 z);
u32 fn_3_134D4C(f32 cx, f32 cz, f32 radius, f32 ax, f32 az, f32 bx, f32 bz);
SDCoinEntry* fn_3_1350BC(u32 player, u32 quadrant, u32 count, SDCoinEntry* entries);
BOOL fn_3_1354BC(u32 item, f32 x, f32 z);
u32 fn_3_135520(f32 x, f32 z, f32 radius);
void fn_3_135600(f32 x, f32 z, f32* outX, f32* outZ);
int fn_3_13564C(f32 x, f32 z);
int fn_3_135698(const void* a, const void* b);
void fn_3_1356F8(void);
void fn_3_1357A4(Vec* out, Vec* dir);
void fn_3_13583C(Vec* pos);
void fn_3_135924(void);
void fn_3_135A64(void);
void fn_3_135C18(void);
void fn_3_135E38(void);
void fn_3_135E98(void);
void fn_3_135F4C(void);
void fn_3_135FF4(void);
void fn_3_136048(void);
void fn_3_1360BC(int player);
void fn_3_136220(void);
void fn_3_13688C(MinigamePowerupStruct* powerup);
void fn_3_136CF4(MinigamePowerupStruct* powerup);
void fn_3_136EA4(void);
void fn_3_1370A0(camera_803c639c_s* cam);
void fn_3_1371E8(void);
void fn_3_137224(Vec* pos);
u8 fn_3_1373E0(VecSrcDst* segment, Vec* velocity, CollisionStruct* out, f32 radius);
BOOL fn_3_1379A0(int fielderIndex);
u8 fn_3_137B10(SDItem* item);
void fn_3_137CF8(SDItem* item);
void fn_3_137DE4(SDItem* item);
void fn_3_137F14(SDItem* item);
void fn_3_13802C(SDItem* item);
void fn_3_1382E0(SDItem* item);
void fn_3_138448(SDItem* item);
void fn_3_1384B4(SDItem* item);
void fn_3_138AA4(void);
void fn_3_1391C0(void);
void fn_3_139700(void);
void fn_3_13974C(void);
void fn_3_139808(void);
void fn_3_139CA0(void);
void fn_3_139F84(void);
void minigame_transferPoints(int toTeam, int fromTeam);
void starDashRelated(void);
void fn_3_13A724(void);
void fn_3_13A89C(void);
void fn_3_13AA78(void);
void fn_3_13ACB4(CollisionStruct* hit);
void fn_3_13ADC0(Vec* out, Vec* in, Vec* normal);
void fn_3_13AE1C(void);
void fn_3_13AFE4(void);
void starDashLiveBall(void);
void fn_3_13B9C4(void);
void fn_3_13BB30(void);
void fn_3_13BBF4(void);
void starDashSomething(void);
void fn_3_13C464(void);
void starDashSwitcher(void);

#endif // !__GAME_MINIGAME_STAR_DASH_H_
