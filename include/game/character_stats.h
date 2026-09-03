#ifndef __CHARACTER_STATS_H_
#define __CHARACTER_STATS_H_

// The per-character stat record: one row in the master stat table at the
// start of Static_Stats_Tables (54 rows, one per CHAR_ID) and in inMemRoster
// ([2][9]). Its own header so both the game and the static-data headers can
// name it without pulling each other in.

#include "mssbTypes.h"

typedef enum _FIELDING_ABILITIES {
    FIELDING_ABILITIES_WALL_SPLAT = 0x1,
    FIELDING_ABILITIES_WALL_JUMP = 0x2,
    FIELDING_ABILITIES_CLAMBER = 0x4,
    FIELDING_ABILITIES_SLIDING_CATCH = 0x8,
    FIELDING_ABILITIES_LASER = 0x10,
    FIELDING_ABILITIES_QUICK_THROW = 0x20,
    FIELDING_ABILITIES_SUPER_JUMP = 0x40,
    FIELDING_ABILITIES_MAGICAL_CATCH = 0x80,
    FIELDING_ABILITIES_TONGUE_CATCH = 0x100,
    FIELDING_ABILITIES_SUCTION = 0x200,
    FIELDING_ABILITIES_SUPER_CATCH = 0x400,
    FIELDING_ABILITIES_BALL_DASH = 0x800,
    FIELDING_ABILITIES_BODY_CHECK = 0x1000,
    FIELDING_ABILITIES_SUPER_CURVE = 0x2000,
    FIELDING_ABILITIES_UNASSIGNED = 0x4000,
    FIELDING_ABILITIES_UNASSIGNED2 = 0x8000,
} FIELDING_ABILITIES;

// 0x3B bytes in the game: the u32 at 0x20 sits on an aligned offset but
// nothing pads the tail, so the ChemistryTable that follows it in
// CharacterStats starts at 0x3B. Packed so C agrees (natural alignment would
// round it to 0x3C and shift every chemistry entry one byte late).
#pragma pack(push, 1)
typedef struct _StatTable {
    /*0x000*/ u8 CurveBallSpeed;
    /*0x001*/ u8 FastBallSpeed;
    /*0x002*/ u8 cursedBall;
    /*0x003*/ u8 Curve;
    /*0x004*/ u8 curveControl;
    /*0x005*/ u8 UnusedBytes[27];
    /*0x020*/ E(u32, FIELDING_ABILITIES) FieldingStats;
    /*0x024*/ s16 CharID;
    /*0x026*/ u8 FieldingArm;
    /*0x027*/ u8 BattingStance;
    /*0x028*/ u8 SlapContactSize;
    /*0x029*/ u8 ChargeContactSize;
    /*0x02A*/ u8 SlapHitPower;
    /*0x02B*/ u8 ChargeHitPower;
    /*0x02C*/ u8 BuntingContactSize;
    /*0x02D*/ u8 HitTrajectoryPushPull;
    /*0x02E*/ u8 HitTrajectoryHighLow;
    /*0x02F*/ u8 Speed;
    /*0x030*/ u8 ThrowingArm;
    /*0x031*/ E(u8, CHARACTER_CLASS) CharacterClass;
    /*0x032*/ u8 Weight;
    /*0x033*/ u8 Captain;
    /*0x034*/ u8 CaptainStarHitPitch;
    /*0x035*/ u8 NonCaptainStarSwing;
    /*0x036*/ u8 NonCaptainStarPitch;
    /*0x037*/ u8 BattingStatBar;
    /*0x038*/ u8 PitchingStatBar;
    /*0x039*/ u8 RunningStatBar;
    /*0x03A*/ u8 FieldingStatBar;
} StatTable; // size: 0x3B
#pragma pack(pop)

typedef struct _ChemistryTable {
    /*0x000*/ u8 Mario;
    /*0x001*/ u8 Luigi;
    /*0x002*/ u8 DK;
    /*0x003*/ u8 Diddy;
    /*0x004*/ u8 Peach;
    /*0x005*/ u8 Daisy;
    /*0x006*/ u8 Yoshi;
    /*0x007*/ u8 BabyMario;
    /*0x008*/ u8 BabyLuigi;
    /*0x009*/ u8 Bowser;
    /*0x00A*/ u8 Wario;
    /*0x00B*/ u8 Waluigi;
    /*0x00C*/ u8 RedKoopa;
    /*0x00D*/ u8 RedToad;
    /*0x00E*/ u8 Boo;
    /*0x00F*/ u8 Toadette;
    /*0x010*/ u8 RedShyGuy;
    /*0x011*/ u8 Birdo;
    /*0x012*/ u8 Monty;
    /*0x013*/ u8 BowserJr;
    /*0x014*/ u8 RedParatroopa;
    /*0x015*/ u8 BluePianta;
    /*0x016*/ u8 RedPianta;
    /*0x017*/ u8 YellowPianta;
    /*0x018*/ u8 BlueNoki;
    /*0x019*/ u8 RedNoki;
    /*0x01A*/ u8 GreenNoki;
    /*0x01B*/ u8 HammerBro;
    /*0x01C*/ u8 Toadsworth;
    /*0x01D*/ u8 BlueToad;
    /*0x01E*/ u8 YellowToad;
    /*0x01F*/ u8 GreenToad;
    /*0x020*/ u8 PurpleToad;
    /*0x021*/ u8 BlueMagikoopa;
    /*0x022*/ u8 RedMagikoopa;
    /*0x023*/ u8 GreenMagikoopa;
    /*0x024*/ u8 YellowMagikoopa;
    /*0x025*/ u8 KingBoo;
    /*0x026*/ u8 Petey;
    /*0x027*/ u8 Dixie;
    /*0x028*/ u8 Goomba;
    /*0x029*/ u8 Paragoomba;
    /*0x02A*/ u8 GreenKoopa;
    /*0x02B*/ u8 GreenParatroopa;
    /*0x02C*/ u8 BlueShyGuy;
    /*0x02D*/ u8 YellowShyGuy;
    /*0x02E*/ u8 GreenShyGuy;
    /*0x02F*/ u8 BlackShyGuy;
    /*0x030*/ u8 GrayDryBones;
    /*0x031*/ u8 GreenDryBones;
    /*0x032*/ u8 RedDryBones;
    /*0x033*/ u8 BlueDryBones;
    /*0x034*/ u8 FireBro;
    /*0x035*/ u8 BoomerangBro;
} ChemistryTable; // size: 0x36

typedef struct _CharacterStats {
    /*0x000*/ StatTable stats;
    /*0x03B*/ ChemistryTable chemistry;
    /*0x071*/ u8 BytesAfterChemistry[3];
    /*0x074*/ s16 UnusedShorts[22]; // through 0x9F: rows are 0xA0 apart (inMemRoster, the static table)
} CharacterStats; // size: 0xA0

#endif
