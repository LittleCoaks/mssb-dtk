#ifndef __UNKNOWN_HOMES_STATIC_H_
#define __UNKNOWN_HOMES_STATIC_H_

#include "mssbTypes.h"
#include "Dolphin/pad.h"
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
    artificial_padding(0x22, 0x42, u16);
    /* 0x42 */ u16 _42;
    artificial_padding(0x42, 0x62, u16);
    /* 0x62 */ u16 _62;
} lbl_803C77B8_s;
extern lbl_803C77B8_s AtBat_ButtonInput1;

/* ---- Static_Stats_Tables (0x8034E9A0, 0x5240 bytes) ------------------------
 * Layouts from the Ghidra type export (Static_MSSB_Data); only the members
 * that are known are named, the rest is explicit padding. */
typedef struct {
    /* 0x0 */ u16 currentHeldInput;
    /* 0x2 */ u16 newInput;
    /* 0x4 */ u16 processedInput;
} controllerInputStruct; // size: 0x6

typedef struct {
    /* 0x00 */ s16 _00;
    /* 0x02 */ u8 onFieldForAPitch;
    /* 0x03 */ u8 plateAppearances;
    /* 0x04 */ u8 AtBats;
    /* 0x05 */ u8 Hits;
    /* 0x06 */ u8 Singles;
    /* 0x07 */ u8 Doubles;
    /* 0x08 */ u8 Triples;
    /* 0x09 */ u8 HomeRuns;
    /* 0x0A */ u8 BuntSuccesses;
    /* 0x0B */ u8 SacFlies;
    /* 0x0C */ u8 GIDP;
    /* 0x0D */ u8 Strikeouts;
    /* 0x0E */ u8 Walks_4Balls;
    /* 0x0F */ u8 Walks_Hit;
    /* 0x10 */ u8 RBI;
    /* 0x11 */ u8 runs;
    /* 0x12 */ u8 BasesStolen;
    /* 0x13 */ u8 AB_W_RISP;
    /* 0x14 */ u8 hits_W_RISP;
    /* 0x15 */ u8 runnersAdvancedAgainst;
    /* 0x16 */ u8 fielder_playsInvolvedIn;
    /* 0x17 */ u8 RBI_W_RISP;
    /* 0x18 */ u8 HR_W_RISP;
    /* 0x19 */ u8 _19;
    /* 0x1A */ u8 currentPosition[9];
    /* 0x23 */ u8 BigPlays;
    /* 0x24 */ u8 StarHitsActivated;
    /* 0x25 */ u8 _25;
} StatisticsBatter; // size: 0x26

typedef struct {
    /* 0x0000 */ u8 _0000[0x46E0];
    /* 0x46E0 */ int captainSelectedID[2];
    /* 0x46E8 */ void* _46E8[4];
    /* 0x46F8 */ s8 playerNumberByPort[4];
    /* 0x46FC */ s8 portsActiveInMatch[4];
    /* 0x4700 */ u8 _4700[4];
    /* 0x4704 */ u8 unk4704;
    /* 0x4705 */ u8 _4705[3];
    /* 0x4708 */ u8 mainMenuOptionSelectedIndex;
    /* 0x4709 */ u8 capLocationInOrder[2];
    /* 0x470B */ u8 _470B[2];
    /* 0x470D */ u8 teamName[2];
    /* 0x470F */ u8 startingChemStars[2];
    /* 0x4711 */ u8 _4711[0x4728 - 0x4711];
    /* 0x4728 */ u8 mode;
    /* 0x4729 */ u8 player2Ind;
    /* 0x472A */ u8 _472A[2];
    /* 0x472C */ controllerInputStruct controllerInputs[4];
    /* 0x4744 */ u8 _4744[0x4757 - 0x4744];
    /* 0x4757 */ u8 charOnCharacterGridSelected[54];
    /* 0x478D */ u8 battingOrderIndex[9];
    /* 0x4796 */ u8 _4796[0x489B - 0x4796];
    /* 0x489B */ u8 charIsStarred[9];
    /* 0x48A4 */ u8 _48A4[0x4E44 - 0x48A4];
    /* 0x4E44 */ StatisticsBatter batterStats[2][9];
    /* 0x50F0 */ u8 _50F0[0x5240 - 0x50F0];
} Static_MSSB_Data; // size: 0x5240

extern Static_MSSB_Data Static_Stats_Tables;

/* Captain-select grid position -> character id (0x800FE5D4). */
extern u8 mapCaptainCursorPositionToCharID[0x350];

/* ---- cursorPositions (0x803C6724, 0x5C bytes) ------------------------------
 * Two per-port cursor bytes, then the drafted rosters. */
typedef struct {
    /* 0x00 */ u8 rosterCharID[2][9];
    /* 0x12 */ u8 positionSwapMapping[2][9];
    /* 0x24 */ u8 chemWCaptain[2][9];
    /* 0x36 */ u8 unused[2][9];
    /* 0x48 */ u8 rosterSpotFilledInd[2][9];
} structCharSelect; // size: 0x5A

typedef struct {
    /* 0x00 */ u8 cursor[2];
    /* 0x02 */ structCharSelect roster;
} CursorPositions_s; // size: 0x5C

extern CursorPositions_s cursorPositions;

/* ---- g_MatchInfo (0x803C5EA4, 0x3C bytes) --------------------------------- */
typedef struct {
    /* 0x00 */ u8 _00[5];
    /* 0x05 */ u8 player2Ind2;
    /* 0x06 */ u8 _06[0x3C - 0x06];
} MatchInfo_s; // size: 0x3C

extern MatchInfo_s g_MatchInfo;

/* ---- aiPosSwapInputs (0x803297E0, 0x24C98 bytes) ---------------------------
 * A large, mostly unlabelled block; only the members in use are named. */
typedef struct {
    /* 0x0000 */ u8 _0000[0xCF46];
    /* 0xCF46 */ u8 teamManagement_cursorPos[2];
    /* 0xCF48 */ u8 _CF48[0xCF5D - 0xCF48];
    /* 0xCF5D */ u8 unkCF5D[2];
    /* 0xCF5F */ u8 _CF5F[0x24C98 - 0xCF5F];
} AiPosSwapInputs_s; // size: 0x24C98

extern AiPosSwapInputs_s aiPosSwapInputs;

/* ---- g_InputBuffer (0x802E9F20, 0x60 bytes) --------------------------------
 * The four PADStatus records PADRead fills each frame sit at +0x20. */
typedef struct {
    /* 0x00 */ u8 _00[0x20];
    /* 0x20 */ PADStatus pads[4];
    /* 0x50 */ u8 _50[0x10];
} InputBuffer_s; // size: 0x60

extern InputBuffer_s g_InputBuffer;

#endif // !__UNKNOWN_HOMES_STATIC_H_

