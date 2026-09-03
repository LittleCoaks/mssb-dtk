#ifndef __MENUS_TEXT_0323C_H_
#define __MENUS_TEXT_0323C_H_

#include "mssbTypes.h"

void cssTransitionToNewScreen_maybe(void);
s32 fn_2_33BC(void);
void fn_2_348C(void);
bool stopShowingCaptainProfile(u8 port);
void fn_2_3624(u8 team);
void fn_2_4970(u8 team, s32 charID);
void fn_2_5184(s32 port);
void fn_2_52CC(void);
void teamReady1(u8 port);
s32 fn_2_57E8(s32 arg0, s32 arg1);
void fn_2_57F0(u8 playerIndex, s32 unused, u16 flagsA, u16 flagsB);
void fn_2_5F80(void);
void fn_2_6098(u8 port);
s32 fn_2_60D4(u8 port);
void fn_2_6138(void);
void cssChangeScreens(void);
void cssSelectCPUDifficulty(void);
void characterSelectScreenControlable(void);
void fn_2_6784(void);
void fn_2_6884(void);
void fn_2_6AF4(void);
void cssUnloadScreen(void);
void cssResetRosterStruct(void);
void fn_2_7D44(void);
void cssLoadingScreenRelated(void);
void fn_2_86EC(void);
s32 fn_2_8780(s32 arg0);
s32 fn_2_8794(s32 arg0, s32 arg1);
void fn_2_87A8(void);
void fn_2_893C(void);
void copyInfoToInMemRoster(void);
void fn_2_8CF8(u16 team);
void fn_2_95D8(void);
void fn_2_9ACC(u16 team);
s32 fn_2_9F70(s8 port);
void fn_2_A040(s32 row, s32 slot, u8 y, u8 x);
void fn_2_A1A0(u8 arg0, u8 arg1);
void fn_2_A288(void);
s32 fn_2_A50C(void);
s32 fn_2_A62C(void);
void fn_2_A6E0(void);
void fn_2_ABC0(s32 port);
void fn_2_AEE8(void);
void fn_2_B324(void);
void fn_2_B508(void);
void fn_2_B66C(void);
void fn_2_B920(void);
void challengeSetRoster(void);
s8 fn_2_C324(s32 id);
void fn_2_C484(s32 charId, s16 target);
void fn_2_C698(s32 idx, u8 port);
void fn_2_C7DC(s32 a, s32 b);
void fn_2_CA60(s32 a, s32 b);
void fn_2_CCBC(void);
void fn_2_CCE0(u8 port);
void cssReturnToCapSelect_maybe(s32 team);
void characterSelectAPress(s32 team);
void fn_2_EAE0(void);
void fn_2_EC34(void);
void fn_2_EC54(s32 port);
s32 characterSelectABDirectionInputs(u8 team, s32 unused, u16 flagsA, u16 flagsB);
void randCharBasedOnClass(s32 port);
void randCharacter1(s32 port);
void randCharAlgo2(s32 port);
void starHitSetting_Unused_maybe(s32 team);
void characterSelectControls(u16 team);

#endif // !__MENUS_TEXT_0323C_H_
