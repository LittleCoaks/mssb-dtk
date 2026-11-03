#ifndef __UNKNOWN_TEAM_MANAGEMENT_SCREENS_H_
#define __UNKNOWN_TEAM_MANAGEMENT_SCREENS_H_

#include "mssbTypes.h"
#include "Unknown/File_0x80034e20.h"

void starMissionRelated1(MenuScene* scene);
void battingOrderProcessInputs(MenuScene* scene, s32 port);
void teamManagementGraphics_fieldingAlignmentScreen(MenuScene* scene);
void teamManagementGraphics_battingOrderScreen(MenuScene* scene);
void challengeTeamManagementRelated(MenuScene* scene);
void teamManagementGraphics_fieldingAlignmentInfo(MenuScene* scene);
void teamManagementGraphics_battingOrderInfo(MenuScene* scene);
void teamManagementGraphics_steadyState(void);
void fn_80059458(MenuScene* scene, u8 port, u32 inputMask);
void fn_8005C5C4(MenuScene* scene, s32 port);
void fn_8005F734(MenuScene* scene, s32 port);
void fn_8005F9D0(MenuScene* scene, s32 port);
void fn_8005EC88(MenuScene* scene, s32 port);
void fn_8005C830(MenuScene* scene, s32 port, s32 selection);
void fn_8005FCA0(MenuScene* scene, s32 port);
void fn_8005B760(MenuScene* scene, s32 port);
void fn_800596D4(MenuScene* scene);
void fn_8005E9D8(MenuScene* scene, s32 port);
void fn_8005DE14(MenuScene* scene, s32 port);
void fn_8005CCE4(MenuScene* scene, s32 port);
void fn_8005F068(MenuScene* scene, s32 port);

#endif // !__UNKNOWN_TEAM_MANAGEMENT_SCREENS_H_
