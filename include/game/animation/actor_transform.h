#ifndef __GAME_ANIMATION_ACTOR_TRANSFORM_H_
#define __GAME_ANIMATION_ACTOR_TRANSFORM_H_

#include "mssbTypes.h"

struct _ActorTransformEntry;
struct _ActorTransformActor;

void fn_3_168414(struct _ActorTransformEntry* entry);
void fn_3_168704(void);
void fn_3_16892C(struct _ActorTransformActor* actor, f32 value, s16 arg);
void mUpdateActorTransformAndAnimation(struct _ActorTransformEntry* entry);
void fn_3_168CD8(struct _ActorTransformActor* actor, f32 value);
void fn_3_168DFC(void);
void displayChem_antiChemGraphics(int fielder, BOOL anti);
void fn_3_1690C0(void);
void fn_3_169150(void);

#endif // !__GAME_ANIMATION_ACTOR_TRANSFORM_H_
