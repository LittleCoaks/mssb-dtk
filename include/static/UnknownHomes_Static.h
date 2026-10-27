#ifndef __UNKNOWN_HOMES_STATIC_H_
#define __UNKNOWN_HOMES_STATIC_H_

#include "mssbTypes.h"
#include "Dolphin/pad.h"
#include "Dolphin/mtx.h"
#include "game/character_stats.h"   // CharacterStats
#include "game/challenge/challenge_items.h"

typedef enum _P2_CPU_CODE {
    /* 0 */ P2_CPU_CODE_1_PLAYER_GAME,   // team 1 (P2 side) is the CPU
    /* 1 */ P2_CPU_CODE_2_PLAYER_GAME,   // both sides human
    /* 2 */ P2_CPU_CODE_CPU_VS_CPU,      // both teams AI; transitions auto-advance like the demo
    /* 3 */ P2_CPU_CODE_CPU_VS_1_PLAYER, // team 0 (P1 side) is the CPU, the human plays team 1
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
    /*0x0C*/ u8 maybeHomeAway[2];
    /*0x0E*/ u8 home_AwaySetting;   // "bats first" setting (0x800E870A)
    /*0x0F*/ u8 _0F;
    /*0x10*/ E(u8, P2_CPU_CODE) p2_CPU_match_code;
    /*0x11*/ bool minigamesEnabled;
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13;
    artificial_padding(0x13, 0x1A, u8);
    /*0x1A*/ u8 characterUnlocked[6]; // indexed like unlockableCharacter_noDupeNoGapCharID
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
    /*0x3C*/ E(s8, BOOL) challengeShopItemActive[CHALLENGE_SHOP_ITEM_COUNT];
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
//   0x800E8758 -> +0x04, 0x800E8759 -> +0x05, 0x800E877C -> +0x28,
//   0x800E877E -> +0x2A, 0x800E8782 -> +0x2E
typedef struct _GameControlOptions {
    /*0x000*/ bool _0;
    /*0x001*/ bool _1;
    /*0x002*/ bool autoRunning;
    /*0x003*/ bool autoFielding;
    /*0x004*/ bool dropSpot;
    /*0x005*/ bool _5;
    /*0x006*/ bool easyBatting;
} GameControlOptions; // size: 0x7

typedef struct _InningSettings {
    /*0x00*/ u8 inningCount;
    u8 _pad_1[0x2];
    /*0x03*/ u8 aiDifficulty;
    /*0x04*/ u8 starSkillsSetting;
    /*0x05*/ u8 runsNeededForMercy;
    u8 _pad_6[0x1];
    /*0x07*/ GameControlOptions controlOptions[4];
    u8 _pad_23[0x5];
    /*0x28*/ s16 rel;           // which REL is resident: 0 boot, 4 menu, 5 match
    /*0x2A*/ u16 currentScene;  // the menu screenCode (5 main menu, 6 options, ...)
    /*0x2C*/ u16 _2C;
    /*0x2E*/ u16 previousScene;
    u8 _pad_30[0x30];
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

/* The four camera blocks at 0x803C639C (0x2A0 bytes); cameras[2].proj
 * (0x803C64EC) is the projection the menus' 3D previews are drawn with. */
extern camera_803c639c_s cameras[4];

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
    artificial_padding(0x62, 0x70, u16);
    /* 0x70 */ s8 _70; // controller 4 stickX
    /* 0x71 */ s8 _71; // controller 4 stickY
    /* 0x72 */ s8 _72; // controller 4 substickX
    /* 0x73 */ s8 _73; // controller 4 substickY
    /* 0x74 */ u8 _74; // controller 4 triggerL
    /* 0x75 */ u8 _75; // controller 4 triggerR
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
    /* 0x1A */ u8 currentPosition[8];
    /* 0x22 */ u8 _22; // never written outside the reset in initializeStats; MVPCalculation weights it 5 points
    /* 0x23 */ u8 BigPlays;
    /* 0x24 */ u8 StarHitsActivated;
    /* 0x25 */ u8 _25;
} StatisticsBatter; // size: 0x26

typedef struct {
    /* 0x00 */ u16 battersFaced;
    /* 0x02 */ u16 runsAllowed;
    /* 0x04 */ u16 earnedRunsAllowed;
    /* 0x06 */ u16 walks;
    /* 0x08 */ u16 battersHit;
    /* 0x0A */ u16 hitsAllowed;
    /* 0x0C */ u16 homeRunsAllowed;
    /* 0x0E */ u16 pitchesThrown;
    /* 0x10 */ u16 stamina;
    /* 0x12 */ u8 wasPitcher;
    /* 0x13 */ u8 _13[7];
    /* 0x1A */ u8 outsAsPitcher;
    /* 0x1B */ u8 maxPitchSpeed;
    /* 0x1C */ u8 strikeouts;
    /* 0x1D */ u8 starPitchesThrown;
} StatisticsPitcher; // size: 0x1E

// One saved Challenge-mode team (Ghidra: challengeRostersStruct).
typedef struct {
    /* 0x00 */ u8 charID[9];
    /* 0x09 */ u8 _09[0x12 - 0x09];
    /* 0x12 */ u8 characterTypes[9];
    /* 0x1B */ u8 _1B[0x48 - 0x1B];
} ChallengeRoster; // size: 0x48

// lbl_80353260: one entry per roster slot, per team.
typedef struct {
    /* 0x0 */ u8 a : 5;
    u8 : 3;
    u8 : 2;
    /* 0x1 */ u8 b : 4;
    u8 : 2;
    /* 0x2 */ u8 c : 4;
    u8 d : 4;
    /* 0x3 */ u8 e : 4;
    u8 f : 4;
} StatsTableEntryA; // size: 0x4

// lbl_803532A8: 100 entries per team.
typedef struct {
    /* 0x0 */ u16 a : 5;
    u16 b : 4;
    u16 c : 4;
    u16 d : 3;
    /* 0x2 */ s8 e;
    /* 0x3 */ u8 f;
} StatsTableEntryB; // size: 0x4

typedef struct {
    /* 0x0000 */ CharacterStats characterStats[NUM_CHOOSABLE_CHARACTERS / 9][9]; // the master stat table, indexed [charID / 9][charID % 9] (copied into inMemRoster)
    /* 0x21C0 */ u8 _21C0[0x4380 - 0x21C0];
    /* 0x4380 */ ChallengeRoster challengeRosters[12]; // captain-select order; [11] is Bowser Jr.'s (Ghidra: bjChallengeRoster)
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
    /* 0x4711 */ u8 _4711[0x4720 - 0x4711];
    /* 0x4720 */ int unk4720[2];
    /* 0x4728 */ u8 mode;
    /* 0x4729 */ u8 player2Ind;
    /* 0x472A */ u8 sceneAlive;     // 0x803530CA: nonzero while a menu scene is up
    /* 0x472B */ u8 _472B;
    /* 0x472C */ controllerInputStruct controllerInputs[4];
    /* 0x4744 */ u8 _4744[0x4757 - 0x4744];
    /* 0x4757 */ u8 charOnCharacterGridSelected[54]; // "taken" table, one byte per CHAR_ID (0x803530F7)
    /* 0x478D */ u8 captainChemistryOrder[2][54]; // every CHAR_ID, sorted by chemistry with the team's captain (Ghidra: battingOrderIndex[9])
    /* 0x47F9 */ s8 highChemTeammates[2][9][9]; // per roster slot: teammates whose chemistry with it is >= 90 (100 excluded), -1 elsewhere, sorted ascending
    /* 0x489B */ u8 charIsStarred[2][9];
    /* 0x48AD */ u8 _48AD;
    /* 0x48AE */ u8 unk48AE; // set before findCharacterID; makes it return the alternate index for slot 0x11, then cleared
    /* 0x48AF */ u8 _48AF[0x48B3 - 0x48AF];
    /* 0x48B3 */ u8 unk48B3;
    /* 0x48B4 */ u8 _48B4[0x48C0 - 0x48B4];
} Static_MSSB_Data; // size: 0x48C0

extern Static_MSSB_Data Static_Stats_Tables;

/* Two objects split out of the tail of the old 0x4C28-byte Static_Stats_Tables
 * symbol: references to them carry their own @ha/@l relocation in the target. */
extern StatsTableEntryA lbl_80353260[2][9];
extern StatsTableEntryB lbl_803532A8[2][100];

/* The original symbol table gave Static_Stats_Tables a size of 0x51F8, but
 * every reference past 0x4C28 is to exactly +0x4C28, +0x4E44 or +0x50F0:
 * three separate globals that follow it in .bss. Split out in
 * config/GYQE01/symbols.txt so references get their own @ha/@l relocation. */
extern StatisticsPitcher PitcherStats_P1_P2[2][9]; // 0x803535C8
extern StatisticsBatter BatterStats_P1_P2[2][9];   // 0x803537E4

typedef struct {
    /* 0x00 */ u16 total;
    /* 0x02 */ u16 byInning[18];
} StatsScreenScore; // size: 0x26

// Copies of g_Scores kept for the stats screens (0x80353A90).
typedef struct {
    /* 0x00 */ u8 _00[8];
    /* 0x08 */ StatsScreenScore scores[2];
    /* 0x54 */ StatsScreenScore hits[2];
    /* 0xA0 */ s8 _A0[0xBE - 0xA0];
    /* 0xBE */ struct {
        s8 pitcher;
        u8 inning;
    } pitcherLog[2][10];
    /* 0xE6 */ s8 catcherLog[2][5];
    /* 0xF0 */ u8 stealsAgainst[2];
    /* 0xF2 */ u8 winnerSlot;
    /* 0xF3 */ s8 winningPitcher;
    /* 0xF4 */ s8 losingPitcher;
    /* 0xF5 */ s8 savePitcher;
    /* 0xF6 */ u8 inning;
    /* 0xF7 */ u8 noHitterKind;
    /* 0xF8 */ s8 goAheadRunPitcher;    // pitcher who allowed the latest go-ahead run
    /* 0xF9 */ s8 walkOffRunner;        // runner who scored the walk-off winning run
    /* 0xFA */ s8 walkOffBatter;        // batter at the plate for the walk-off
    /* 0xFB */ s8 walkOffHomeRunBatter; // batter, only if the walk-off was a home run
    /* 0xFC */ s8 lateGoAheadHitTeam;   // unsure: gated on g_Scores._pad_AC >= 3
    /* 0xFD */ s8 lateGoAheadHitBatter; // unsure: same gate
    /* 0xFE */ s8 goAheadRbiTeam;       // batting team on the latest go-ahead play
    /* 0xFF */ s8 goAheadRbiBatter;     // batter on the latest go-ahead play
    /* 0x100 */ s8 goAheadRbiWasHit; // 1 if goAheadRbiBatter reached base on the play
    /* 0x101 */ s8 mvpRosterLoc[2];
    /* 0x103 */ s8 mvpCharID;
    /* 0x104 */ u8 mvpKind;
    /* 0x105 */ s8 _105[0x108 - 0x105];
} StatsScreenScoresStruct; // size: 0x108

extern StatsScreenScoresStruct StatsScreenScores;

/* The original symbol table gave Static_Stats_Tables a size of 0x5240,
 * but its last 0x48 bytes (0x80353B98) are a separate global: the menus
 * REL's fn_2_B508 (src/menus/text_0323C.c) writes the identical field
 * offsets (0x2a/0x2e/0x32/.../0x46) into both this object and the
 * unrelated lineUpInfoStruct just past it, which only produces the
 * target's distinct @ha/@l relocation if it is its own symbol. Split out
 * in config/GYQE01/symbols.txt as lbl_80353B98; declared raw here since,
 * like lineUpInfoStruct, no header currently types it. */
extern u8 lbl_80353B98[0x48];

/* Captain-select grid position -> character id (0x800FE5D4). */
extern u8 mapCaptainCursorPositionToCharID[0x350];

/* ---- cursorPositions (0x803C6724, 0x5C bytes) ------------------------------
 * Two per-port cursor bytes, then the drafted rosters. */
typedef struct {
    /* 0x00 */ E(s8, CHAR_ID) rosterCharID[2][9];
    /* 0x12 */ u8 positionSwapMapping[2][9];
    /* 0x24 */ u8 chemWCaptain[2][9];
    /* 0x36 */ u8 unused[2][9];
    /* 0x48 */ u8 rosterSpotFilledInd[2][9];
} structCharSelect; // size: 0x5A

typedef struct {
    /* 0x00 */ u8 cursor[2];
    /* 0x02 */ structCharSelect roster;   // rosterCharID[p][0] (0x803C6726 / 0x803C672F) is player p's captain
} CursorPositions_s; // size: 0x5C

extern CursorPositions_s cursorPositions;

/* ---- g_MatchInfo (0x803C5EA4, 0x3C bytes) --------------------------------- */
typedef struct {
    /* 0x00 */ u8 _00[5];
    /* 0x05 */ u8 player2Ind2;
    /* 0x06 */ u8 _06[0x36 - 0x06];
    /* 0x36 */ u8 unk36;        // stadiumSelect sets 1
    /* 0x37 */ u8 unk37;        // stadiumSelect copies unk38 here before overwriting it
    /* 0x38 */ u8 unk38;        // stadiumSelect sets 3
    /* 0x39 */ u8 _39[0x3C - 0x39];
} MatchInfo_s; // size: 0x3C

extern MatchInfo_s g_MatchInfo;

/* ---- g_TeamManagement (0x803297E0, 0x24C98 bytes) ---------------------------
 * State of the pre-game and pause-menu team-management screens (roster
 * order, fielding alignment, Z info window, star/scout-flag/check-stars
 * menus) plus a few neighbouring menu flags (captain-select random cursor,
 * loadMatchRelInd). playerInputs[] at 0 are the controller inputs those
 * screens read while paused. Formerly aiPosSwapInputs, after Ghidra's
 * 32-byte "aiPosSwapInputs?" at 0x803297E0; dtk sized the symbol over the
 * whole block, which still holds unlabelled bss (Ghidra has byte arrays at
 * +0x6820, +0xA820 and +0x10000 onward). */

/* g_TeamManagement.teamManagementProcessID (Ghidra: teamManagementMenuProcesses). */
typedef enum _TEAM_MANAGEMENT_PROCESS {
    TEAM_MANAGEMENT_PROCESS_INITIALIZE = 0,
    TEAM_MANAGEMENT_PROCESS_LOAD = 1,
    TEAM_MANAGEMENT_PROCESS_ON_SCREEN = 2,
    TEAM_MANAGEMENT_PROCESS_STAR_MENU_UNUSED = 3,
    TEAM_MANAGEMENT_PROCESS_SCOUT_FLAGS_MENU = 4,
    TEAM_MANAGEMENT_PROCESS_CHALLENGE_STARS_MENU = 5,
    TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_2 = 10,
    TEAM_MANAGEMENT_PROCESS_RETURN_TO_CSS_1 = 12,
    TEAM_MANAGEMENT_PROCESS_RETURN_TO_CSS_2 = 13,
    TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1 = 14,
} TEAM_MANAGEMENT_PROCESS;

/* g_TeamManagement.challengeCheckStarsMenuSceneLoadingNumber
 * (Ghidra: challengeCheckStarsLoadingScreenNum). */
typedef enum _CHECK_STARS_SCENE {
    CHECK_STARS_SCENE_NONE = 0,
    CHECK_STARS_SCENE_LOAD = 1,
    CHECK_STARS_SCENE_EXIT = 2,
    CHECK_STARS_SCENE_MOVE_IN_CHAR_LIST = 3,
    CHECK_STARS_SCENE_MOVE_IN_STAR_LIST = 4,
    CHECK_STARS_SCENE_LOAD_CHAR_VIEW = 5,
    CHECK_STARS_SCENE_EXIT_CHAR_VIEW = 6,
} CHECK_STARS_SCENE;

/* g_TeamManagement.teamMenuType[port] (Ghidra: enumSwapMenuType,
 * teamManagement_menuType): written by the pause menu's positionSwap from
 * the chosen option, read by pauseMenu_openTeamManagement (match_scene.c)
 * to pick the menu. */
typedef enum _TEAM_MENU_TYPE {
    /* 0 */ TEAM_MENU_TYPE_FIELDER_SWAP, // also the regular pre-game menu
    /* 1 */ TEAM_MENU_TYPE_BATTER_SWAP,  // R/L/X and in-game A on a player are refused
    /* 2 */ TEAM_MENU_TYPE_SCOUT_FLAGS,  // challenge scout flag menu
    /* 3 */ TEAM_MENU_TYPE_STAR_MISSIONS, // challenge star menu
} TEAM_MENU_TYPE;

/* g_TeamManagement.starMenuDrawStep: the request battingOrderProcessInputs
 * services, then clears. */
typedef enum _STAR_MENU_DRAW_STEP {
    /* 0 */ STAR_MENU_DRAW_STEP_NONE,
    /* 1 */ STAR_MENU_DRAW_STEP_OPEN,         // Y in challenge mode -> starMissionRelated1
    /* 2 */ STAR_MENU_DRAW_STEP_CURSOR_MOVED, // starMenuCursor -> fn_800596D4
    /* 3 */ STAR_MENU_DRAW_STEP_CLOSE,        // A/B in starMenuCursor
} STAR_MENU_DRAW_STEP;

/* g_TeamManagement.zMenuPage[team]: Z opens on page 0; left/right switch. */
typedef enum _Z_MENU_PAGE {
    /* 0 */ Z_MENU_PAGE_MAIN,
    /* 1 */ Z_MENU_PAGE_STAR_MOVES, // star swing/pitch (fn_80058B20, zMenuLoadGraphics)
} Z_MENU_PAGE;

/* g_TeamManagement.scoutFlagMenuState: fn_80057CAC's state machine. */
typedef enum _SCOUT_FLAG_MENU_STATE {
    /* 0 */ SCOUT_FLAG_MENU_STATE_IDLE,
    /* 1 */ SCOUT_FLAG_MENU_STATE_OPEN,       // set on entry (initTeamManagementScreen)
    /* 2 */ SCOUT_FLAG_MENU_STATE_SHOW_FLAGS, // after the open animation: plays the flag animations
    /* 3 */ SCOUT_FLAG_MENU_STATE_CLOSE,      // B (pauseMenuSelection); then requests scene removal
} SCOUT_FLAG_MENU_STATE;

/* Per-port process codes passed to updateCharacterSelectProcessCode and
 * dispatched on by teamManagementGraphics_steadyState via
 * gameSetUpStep[0x5D + i]. The value space is shared with the
 * character-select screens; only the team-management codes are named.
 * 0x39 (initTeamManagementScreen, 1P game not entered from screen 0xA)
 * and 0x46 (unkCF70 dismissed) are left as literals. */
typedef enum _CHAR_SELECT_PROCESS {
    /* 0x38 */ CHAR_SELECT_PROCESS_TM_LOAD = 0x38,             // initTeamManagementScreen
    /* 0x3A */ CHAR_SELECT_PROCESS_TM_RETURN_TO_CSS = 0x3A,    // B on the confirm row
    /* 0x3B */ CHAR_SELECT_PROCESS_TM_CURSOR_MOVE = 0x3B,      // cursor moved or player picked for a swap
    /* 0x3C */ CHAR_SELECT_PROCESS_TM_CHANGE_ROSTER_VIEW = 0x3C, // L/R
    /* 0x3D */ CHAR_SELECT_PROCESS_TM_CURSOR_ENTER_ROSTER = 0x3D, // off the confirm row into the roster
    /* 0x3E */ CHAR_SELECT_PROCESS_TM_CURSOR_TO_CONFIRM = 0x3E, // cursor onto the confirm row (position 0)
    /* 0x3F */ CHAR_SELECT_PROCESS_TM_1P_TO_CPU_TEAM = 0x3F,   // 1P game: own team confirmed, edit the CPU team
    /* 0x40 */ CHAR_SELECT_PROCESS_TM_1P_TO_OWN_TEAM = 0x40,   // 1P game: B back from the CPU team
    /* 0x41 */ CHAR_SELECT_PROCESS_TM_WAIT_FOR_OTHER_TEAM = 0x41, // 2P game: confirmed first
    /* 0x42 */ CHAR_SELECT_PROCESS_TM_CANCEL_CONFIRM = 0x42,
    /* 0x43 */ CHAR_SELECT_PROCESS_TM_EXIT = 0x43,
    /* 0x44 */ CHAR_SELECT_PROCESS_TM_CANCEL_SWAP = 0x44,
    /* 0x45 */ CHAR_SELECT_PROCESS_TM_SHOW_SCOUT_FLAGS = 0x45, // challenge, 1P: after both entry animations
} CHAR_SELECT_PROCESS;

/* gameSetUpStep[0x37 + port] in team_management_screens.c: each
 * steady-state process starts its animation and locks the cursor (START),
 * waits for it (PLAYING), then unlocks the cursor (DONE). gameSetUpStep
 * itself has no shared type yet. */
typedef enum _TEAM_MANAGEMENT_ANIM_STEP {
    /* 0 */ TEAM_MANAGEMENT_ANIM_STEP_START,
    /* 1 */ TEAM_MANAGEMENT_ANIM_STEP_PLAYING, // after makeCursorUnmovable
    /* 2 */ TEAM_MANAGEMENT_ANIM_STEP_DONE,    // after makeCursorMovable
} TEAM_MANAGEMENT_ANIM_STEP;

/* g_TeamManagement.rosterView (Ghidra: enum_rosterView). */
typedef enum _ROSTER_VIEW {
    ROSTER_VIEW_BATTING_ORDER = 0,
    ROSTER_VIEW_DEFENSIVE_ALIGNMENT = 1,
} ROSTER_VIEW;

typedef struct {
    /* 0x0000 */ controllerInputStruct playerInputs[4]; // indexed by Static_Stats_Tables.playerNumberByPort
    /* 0x0018 */ u8 _0018[0xCF38 - 0x18];
    /* 0xCF38 */ E(u16, TEAM_MANAGEMENT_PROCESS) teamManagementProcessID; // 0x80336718
    /* 0xCF3A */ s8 teamThatPaused;                 // -1 before a team is chosen
    /* 0xCF3B */ u8 playerWhoPaused;
    /* 0xCF3C */ u8 charSelectedToBeSwapped[2];
    /* 0xCF3E */ u8 charSelectedToBeSwappedCharID[2];
    /* 0xCF40 */ u8 unkCF40;                        // 1P game: set with onePlayerEditingTeam when P1 moves on to the CPU team
    /* 0xCF41 */ u8 unkCF41;                        // only ever cleared (initTeamManagementScreen)
    /* 0xCF42 */ u8 onMainPauseMenu;
    /* 0xCF43 */ u8 onePlayerEditingTeam;           // 1P game: team index player 1 is editing (0 = own, 1 = CPU)
    /* 0xCF44 */ u8 _CF44;
    /* 0xCF45 */ E(u8, BOOL) removeSceneRequested;  // set on exit; teamManagementGraphics_steadyState removes the scene
    /* 0xCF46 */ s8 teamManagement_cursorPos[2];
    /* 0xCF48 */ s8 teamManagement_prevCursorPos[2];
    /* 0xCF4A */ u8 onFieldingAlignmentScreen2[2];
    /* 0xCF4C */ u8 unkCF4C[2];                     // copy of onFieldingAlignmentScreen2 before a left/right press
    /* 0xCF4E */ E(u8, BOOL) teamConfirmed[2];      // A on "done"; input is then masked to B only
    /* 0xCF50 */ E(u8, BOOL) waitingForOtherTeam[2]; // 2P game: confirmed while the other team was not
    /* 0xCF52 */ E(u8, ROSTER_VIEW) rosterView[2];
    /* 0xCF54 */ E(u8, ROSTER_VIEW) prevRosterView[2]; // rosterView before an L/R press
    /* 0xCF56 */ E(u8, BOOL) swapCompleted[2];      // set when the second A completes a swap
    /* 0xCF58 */ E(u8, BOOL) stanceChangeRequested[2]; // X: battingOrderProcessInputs cycles the stance
    /* 0xCF5A */ u8 _CF5A;
    /* 0xCF5B */ E(u8, BOOL) entryAnimDone[2];      // 1P game: both must finish before the cursors unlock
    /* 0xCF5D */ E(u8, BOOL) capSS_isRandomizingCursor[2]; // per captain slot: R in captain select
    /* 0xCF5F */ u8 loadMatchRelInd;                 // non-zero: leaving returns to screen 4; main_menu passes it to loadDemoMatch
    /* 0xCF60 */ u8 _CF60;
    /* 0xCF61 */ E(u8, BOOL) zMenuOpen[2];          // Z toggles the per-character info window
    /* 0xCF63 */ E(u8, BOOL) zMenuPageLoaded[2];
    /* 0xCF65 */ E(u8, BOOL) zMenuActive[2];        // window open or still animating closed
    /* 0xCF67 */ E(u8, Z_MENU_PAGE) zMenuPage[2];
    /* 0xCF69 */ u8 _CF69[0xCF6B - 0xCF69];
    /* 0xCF6B */ u8 unkCF6B;                        // set when unkCF70 is dismissed with A/B
    /* 0xCF6C */ u8 _CF6C[0xCF70 - 0xCF6C];
    /* 0xCF70 */ u8 unkCF70;                        // challenge: set on resuming saved teams; blocks input until A/B
    /* 0xCF71 */ E(u8, BOOL) starMenuOpen;          // Y in challenge mode
    /* 0xCF72 */ E(u8, BOOL) starMenuActive;        // cleared once the close step finishes
    /* 0xCF73 */ E(u8, BOOL) starMenuStepStarted;   // the current starMenuDrawStep has done its setup
    /* 0xCF74 */ E(u8, STAR_MENU_DRAW_STEP) starMenuDrawStep;
    /* 0xCF75 */ s8 starMenuCursorPos;
    /* 0xCF76 */ s8 starMenuPrevCursorPos;
    /* 0xCF77 */ u8 _CF77;
    /* 0xCF78 */ E(s16, CHAR_ID) starMenuCharID;
    /* 0xCF7A */ u8 textBlocks[3];                  // text_initializeNewChannel handles, freed with text_freeBlock
    /* 0xCF7D */ E(u8, SCOUT_FLAG_MENU_STATE) scoutFlagMenuState;
    /* 0xCF7E */ E(u8, BOOL) scoutFlagMenuStepStarted; // fn_80057CAC: current state has done its setup
    /* 0xCF7F */ E(u8, BOOL) scoutFlagMenuRemoveRequested; // set when the close animation ends
    /* 0xCF80 */ s8 scoutFlagsRequired[9];          // per inMemRoster[1] player
    /* 0xCF89 */ s8 scoutFlagsAchieved[9];
    /* 0xCF92 */ E(u8, CHECK_STARS_SCENE) challengeCheckStarsMenuSceneLoadingNumber;
    /* 0xCF93 */ u8 challengeCheckStarsMenuLoadingInd;
    /* 0xCF94 */ u8 _CF94;
    /* 0xCF95 */ s8 checkStarsMenuPrevCharIndex;
    /* 0xCF96 */ s8 checkStarsMenuCharIndex;
    /* 0xCF97 */ s8 checkStarsMenuPrevStarIndex;
    /* 0xCF98 */ s8 checkStarsMenuStarIndex;
    /* 0xCF99 */ E(u8, BOOL) checkStarsMenuCharViewOpen;
    /* 0xCF9A */ u8 numberOfChallengeStarsForPlayer;
    /* 0xCF9B */ u8 _CF9B;
    /* 0xCF9C */ s16 playerIndexNoVariants;         // index into g_Challenge
    /* 0xCF9E */ E(u8, BOOL) inProgress_superStarAPlayer[2]; // 0x8033677E; Y on an unlocked superstar
    /* 0xCFA0 */ u8 _CFA0;
    /* 0xCFA1 */ E(u8, BOOL) challengeLoadingNormalMatchInd; // challenge: set on resuming saved teams, cleared once copied back
    /* 0xCFA2 */ E(u8, TEAM_MENU_TYPE) teamMenuType[4];   // per port
    /* 0xCFA6 */ u8 _CFA6[0x24C98 - 0xCFA6];
} TeamManagementState_s; // size: 0x24C98

// A unit may define TEAM_MANAGEMENT_LOCAL_VIEW and declare its own, smaller
// view of this object: MWCC 2.6 only keeps loads of other globals ordered
// after stores into an object whose declared size is below 0xFFFF bytes.
#ifndef TEAM_MANAGEMENT_LOCAL_VIEW
extern TeamManagementState_s g_TeamManagement;
#endif

/* ---- g_InputBuffer (0x802E9F20, 0x60 bytes) --------------------------------
 * The four PADStatus records PADRead fills each frame sit at +0x20. */
typedef struct {
    /* 0x00 */ u8 _00[0x20];
    /* 0x20 */ PADStatus pads[4];
    /* 0x50 */ u8 _50[0x10];
} InputBuffer_s; // size: 0x60

extern InputBuffer_s g_InputBuffer;

#endif // !__UNKNOWN_HOMES_STATIC_H_

