#ifndef __GAME_STADIUM_STADIUM_BOWSER_CASTLE_H_
#define __GAME_STADIUM_STADIUM_BOWSER_CASTLE_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/ball/collision_primitives.h"
#include "game/stadium/stadium_framework.h"
#include "static/UnknownHomes_Static.h"

void fn_3_C1964(void);
void fn_3_C1974(int offset);
void fn_3_C19C8(void);
void fn_3_C1C18(void);
void fn_3_C2244(void);
void fn_3_C2310(StadiumModel* model, Mtx m);
void fn_3_C23E0(void);
void fn_3_C24A0(void);
void fn_3_C2644(void);
void fn_3_C2974(void);
void fn_3_C298C(void);
BOOL fn_3_C2AA0(Vec* p, f32 w, f32 h);
void fn_3_C2C80(void);
void fn_3_C2EDC(struct _CastleFlameParticle* p);
void fn_3_C30F0(void);
void fn_3_C366C(void* handle, u8 idx);
void bowserCastleSomething(void);
void thwomp_screenShake(camera_803c639c_s* cam);
void fn_3_C3C2C(void);
void fn_3_C3E94(Vec* p, int idx);
void fn_3_C3F70(StadiumObject* obj);
void fn_3_C4068(StadiumObject* obj);
void fn_3_C40EC(StadiumObject* obj);
void bowserCastleStarPadsContaactFn(int offset);
void stadiumObjCollision_Castle(s32* idx, s32* count);
void fn_3_C444C(void);
BOOL fn_3_C4724(struct _CastleSparkEmitter* emitter);
void fn_3_C48D0(void);
void fn_3_C4B80(void);
void fn_3_C4CF4(struct _CastleFlameEmitter* emitter, u8 group);
void fn_3_C4F00(void);
void fn_3_C5304(struct _CastleFireballEmitter* handle, StadiumObject* obj);
void fn_3_C54D0(StadiumObject* obj);
void fn_3_C56E8(void);
void fn_3_C597C(void);
BOOL castleFireballMaybe(StadiumObject* obj);
void bowserCastleRelated(void);
BOOL fn_3_C625C(StadiumObject* obj);
void flameControl(void);
void stadiumObjRelated_Castle(void);
void fn_3_C7444(StadiumObject* obj);
void thwomp_bounceOffSoundAndVisualFx(void);
BOOL thwomp_smokeRelated(struct _CastleSmokeEmitter* smoke);
void fn_3_C77AC(void);
void thwomp_slamControl(void);
void fn_3_C805C(s32* idx, s32* count);
TriangleGroup* fn_3_C823C(int offset, Mtx m);
void fn_3_C82B4(void);
void loadBowserCastle(void);

#endif // !__GAME_STADIUM_STADIUM_BOWSER_CASTLE_H_
