#ifndef __UNKNOWN_MB_SUBFUNC_H_
#define __UNKNOWN_MB_SUBFUNC_H_

#include "mssbTypes.h"

int translateStarPitchHitIndex(u8 starHitType);
u8 translateStarPitch(u8 starPitch);
u8 translateStarSwing(u8 starSwing);
int fn_80064918(s16 charID);
void setPortOfEachPlayer(void);
void fn_800649BC(void);
void unsure_FillRosterPositions(u8 team);
void characterSelectScreen(u8 team);
void fn_80066EAC(u8 team);
void fn_800670A0(u8 arg0);
void selectRandomStadium(void);
u8 teamClassTypeLogos(int team, int captain);
u8 teamCompositionLogos(int team, int captain);
void teamLogoDetermination(int team);
s16 fn_80067AC8(s16 charID, s8 col);
u8 addRemoveCharVariantRelated(u8 port, u8 charID, u8 flag);
void fn_80067C48(u8 team);
void DraftRandomTeamDemo(u8 team);
void fn_800684A4(void);
BOOL fn_80068514(u32 frames, u32 target);
BOOL fn_8006862C(u32 frames, u32 target);
void fn_80068720(u8 index);
void playStream(u8 streamId);
void unknownSettingTeamValues(void);
BOOL fn_800697B0(void);
void setCaptainLocInRoster(void);
int findCharacterID(int charID);

#endif // !__UNKNOWN_MB_SUBFUNC_H_
