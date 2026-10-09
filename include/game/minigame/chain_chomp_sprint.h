#ifndef __GAME_MINIGAME_CHAIN_CHOMP_SPRINT_H_
#define __GAME_MINIGAME_CHAIN_CHOMP_SPRINT_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

void fn_3_13C790(void);
void fn_3_13C7BC(void);
u8 fn_3_13D578(s8 player);
int fn_3_13D5E8(f32* a, f32* b);
f32 fn_3_13D618(f32 target, s8 runnerIdx, u8* direction);
int fn_3_13DA20(f32* a, f32* b);
f32 fn_3_13DA50(f32 target, s8 runnerIdx, u8* direction);
void fn_3_13DC48(s8 runnerIdx, f32 target, f32* forward, f32* backward);
f32 fn_3_13DDE0(u8 forward, f32 from, f32 to);
void fn_3_13DEA4(void);
void fn_3_13DFBC(camera_803c639c_s* cam);
void fn_3_13E174(u8 type);
void fn_3_13E21C(MinigamePowerupStruct* powerup);
void fn_3_13E3A4(MinigamePowerupStruct* powerup);
void fn_3_13E670(void);
void fn_3_13E6D4(void);
void fn_3_13E7D4(int player);
void chainChompSpringPoints(void);
void fn_3_13EC44(int item);
void fn_3_13F484(void);
void fn_3_13F6C8(void);
void fn_3_13F7E4(void);
void fn_3_13F8C4(void);
void fn_3_13FC24(void);
void fn_3_140284(void);
void fn_3_140484(void);
void fn_3_1405D8(void);
void fn_3_1406F4(void);
void fn_3_1409AC(void);
void fn_3_140BCC(void);
void chainChompSpringMainFun(void);
void chainChompSprintEndGame(void);
void fn_3_1412BC(void);
void fn_3_1413E4(void);
void chainChompSprintRelated(void);
void ccs_EmptyHook(void);
void chainChompSprintSwitcher(void);

#endif // !__GAME_MINIGAME_CHAIN_CHOMP_SPRINT_H_
