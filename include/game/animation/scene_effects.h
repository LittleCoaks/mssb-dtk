#ifndef __GAME_ANIMATION_SCENE_EFFECTS_H_
#define __GAME_ANIMATION_SCENE_EFFECTS_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"

struct _SceneQuad;

typedef struct _SceneQuad SceneQuad;
typedef struct _SceneParticle SceneParticle;
typedef struct _SceneActor SceneActor;
typedef struct _HudNode HudNode;
typedef struct _HudObj HudObj;
typedef struct _HudKey HudKey;
typedef f32 (*HudEvalFn)(HudNode* node, int frame, Mtx out, f32 t);
typedef struct _ContactWordBuf ContactWordBuf;
typedef struct _SceneEffect SceneEffect;
void fn_3_BA538(SceneQuad* quad);
void fn_3_BA3EC(void);
void fn_3_BA268(void);
SceneParticle* fn_3_BA1A0(SceneParticle* head, int count);
void fn_3_BA150(void);
int fn_3_BA7F4(SceneEffect* effect);
void fn_3_BB07C(SceneParticle* p, f32 angle);
void fn_3_BB15C(SceneParticle* p);
void fn_3_BB454(SceneEffect* effect);
void fn_3_BB7F4(void);
void fn_3_BBBC4(void);
void spriteAnimations(void);
void fn_3_BC224(void);
void fn_3_BC25C(void);
BOOL fn_3_BC274(SceneActor* actor, VecXYZ* a, VecXYZ* b);
void animateDustCloudsBehindFielder_Runner(void);
void maybeFireworks(int a, int b, int index, int c);
void fn_3_BC850(int arg, int index);
void fn_3_BC888(void);
void drawSun(void);
void fn_3_BD1D4(void);
void sunRelated(Mtx view);
void setSunLocation(int a, int b);
void fn_3_BD4F0(void);
void animationRelated(f32 x, f32 y, f32 z, BOOL isBatter);
void fn_3_BD6AC(BOOL isBatter, f32 x, f32 y, f32 z);
void fn_3_BD758(void);
BOOL fn_3_BD7D0(void);
void fn_3_BD7D8(void);
void fn_3_BD7DC(int arg);
void fn_3_BD80C(int arg);
void fn_3_BD8D8(void);
void fn_3_BD8FC(ContactWordBuf* buf);
void fn_3_BDCA4(void);
void fn_3_BDE14(void);
void fn_3_BDF74(void);
void fn_3_BE140(void);
void setContactWordSprite(int kind, f32 x, f32 y, f32 z);
void fn_3_BE1D4(void);
void fn_3_BEFF8(void);
void fn_3_BF070(void);
void pauseStateOnStadiums(void);
void pauseAnimations(void);
void fn_3_BF20C(void);
void fn_3_BF238(void);
void maybeHudRelated(void);
BOOL maybeLoadHUDObjectFromMemory(void);
void fn_3_BF8F8(HudObj* obj, Mtx view, Vec* origin, HudEvalFn eval);
f32 fn_3_BFB3C(HudNode* node, int frame, Mtx out, f32 t);
f32 fn_3_BFDA4(HudKey* keys, int count, int endFrame, u8 index, u8* outIndex, f32 t);
int fn_3_C0134(void);
void fn_3_C0770(void);
void chargeAnimRelated(void);
void fn_3_C07B0(void);

#endif // !__GAME_ANIMATION_SCENE_EFFECTS_H_
