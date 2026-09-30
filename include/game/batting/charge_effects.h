#ifndef __GAME_BATTING_CHARGE_EFFECTS_H_
#define __GAME_BATTING_CHARGE_EFFECTS_H_

#include "mssbTypes.h"

struct _ChargeGlowEntry;

void fn_3_C0854(void);
void fn_3_C095C(struct _ChargeGlowEntry* entry);
void fn_3_C0AD8(void);
void fn_3_C0C4C(int slot);
void fn_3_C0CE8(int pitch, f32 x, f32 y, f32 z);
void fn_3_C0D10(int row, u8 r, u8 g, u8 b, u8 a);
void fn_3_C0F8C(void);
void fn_3_C1004(void);
void fn_3_C11CC(int actorIndex, BOOL immediate);
void applyChargeAnimationEffect(int actorIndex, f32 charge, f32 release, BOOL fullyCharged);
void maybeConfigureChargeEffectGraphics(int actorIndex);

#endif // !__GAME_BATTING_CHARGE_EFFECTS_H_
