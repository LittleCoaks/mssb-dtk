#ifndef __UNKNOWN_HOMES_STATIC_H_
#define __UNKNOWN_HOMES_STATIC_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef enum _P2_CPU_CODE {
    /* 0 */ P2_CPU_CODE_1_PLAYER_GAME,
    /* 1 */ P2_CPU_CODE_2_PLAYER_GAME,
} P2_CPU_CODE;

typedef struct _GameInitVariables {
    /*0x00*/ int _00;
    /*0x04*/ u16 FrameCountWhileNotAtMainMenu;
    /*0x06*/ u8 _06; // 1 Menu,2 InGame/Minigame/Practice/etc
    /*0x07*/ E(u8, GAME_TYPE) GameModeSelected;
    /*0x08*/ bool exhibitionMatchInd;
    /*0x09*/ E(u8, STADIUM_ID) StadiumID;
    /*0x0A*/ u8 miniGameStadiumIndicator;
    /*0x0B*/ u8 _0B;
    /*0x0C*/ u8 maybeHomeAway;
    /*0x0D*/ u8 maybeHomeAway2;
    /*0x0E*/ u8 home_AwaySetting;
    /*0x0F*/ u8 _0F;
    /*0x10*/ E(u8, P2_CPU_CODE) p2_CPU_match_code;
    /*0x11*/ bool minigamesEnabled;
    artificial_padding(0x11, 0x20, bool);
    /*0x20*/ s16 _20[4][2];
    /*0x30*/ s16 challengeMinigame_baseCoinsEarned;
    /*0x32*/ u8 bJMatchRelated;
    /*0x33*/ u8 _33;
    /*0x34*/ u8 humanTeamNumber;
    /*0x35*/ u8 _35;
    /*0x36*/ u8 _36;
    /*0x37*/ u8 challengeDifficulty; // unsure
    /*0x38*/ u8 _38;
    /*0x39*/ u8 bJMatchInd;
    /*0x3A*/ u8 _3A;
    /*0x3B*/ u8 someChallengeModeFlag;
    /*0x3C*/ u8 challengeCaptainStarBought[18];
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
    /*0x50*/ u8 PlayerPorts[2];
    /*0x52*/ u8 _52;
    /*0x53*/ u8 _53;
    /*0x54*/ E(u8, STADIUM_ID) _54;
    /*0x55*/ u8 _55;
    /*0x56*/ u8 _56;
    /*0x57*/ u8 _57;
} GameInitVariables; // size: 0x58

extern GameInitVariables g_d_GameSettings;

// The object immediately after g_d_GameSettings. symbols.txt records it as
// .data:0x800E8754 size:0x60. Offsets are anchored on memory, from the old
// Ghidra export's recorded addresses (see ProjectRio-ASM docs/rename_map.md):
//   0x800E8758 -> +0x04, 0x800E8759 -> +0x05, 0x800E877C -> +0x28
typedef struct _InningSettings {
    /*0x00*/ u8 inningCount;
    u8 _pad_1[0x3];
    /*0x04*/ u8 starSkillsSetting;
    /*0x05*/ u8 runsNeededForMercy;
    u8 _pad_6[0x22];
    /*0x28*/ s16 rel;   // which REL is resident: 0 boot, 4 menu, 5 match
    u8 _pad_2A[0x36];
} InningSettings; // size: 0x60

extern InningSettings inningSetting;

typedef struct {
    /*0x00*/ Mtx44 proj;
    /*0x40*/ Mtx view;
    /*0x70*/ Vec eye;
    /*0x7C*/ Vec target;
    /*0x88*/ Vec Up;
    artificial_padding(0x88, 0xa4, Vec);
    /*0xA4*/ f32 zoom; // unsure
} camera_803c639c_s; // size: 0xA8

typedef void (*fn_800528AC_parameter)(camera_803c639c_s*);

extern void fn_800528AC(fn_800528AC_parameter);
extern camera_803c639c_s* fn_80052768_getCamera(int);
extern int loadAndAnimateCharacter(int, int);
extern f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);

typedef struct {
    /* 0x00 */ u16 _00;
    /* 0x02 */ u16 _02;
    artificial_padding(2, 0x22, u16);
    /* 0x22 */ u16 _22;
} lbl_803C77B8_s;
extern lbl_803C77B8_s AtBat_ButtonInput1;

#endif // !__UNKNOWN_HOMES_STATIC_H_
