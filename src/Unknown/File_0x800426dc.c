#include "Unknown/File_0x800426dc.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

extern SuperstarStatBonus stonNiceContactIncrement;
extern u8 superstarUnlocked[0x130];
extern u8 lbl_802E4B00[2][9];

static inline void copyCharacterStats(CharacterStats* dst, CharacterStats* src) {
    memcpy(dst, src, 0x1E);
    dst->stats.CharID = src->stats.CharID;
    dst->stats.FieldingArm = src->stats.FieldingArm;
    dst->stats.BattingStance = src->stats.BattingStance;
    memcpy(&dst->stats.SlapContactSize, &src->stats.SlapContactSize, 2);
    memcpy(&dst->stats.SlapHitPower, &src->stats.SlapHitPower, 2);
    dst->stats.BuntingContactSize = src->stats.BuntingContactSize;
    dst->stats.HitTrajectoryPushPull = src->stats.HitTrajectoryPushPull;
    dst->stats.HitTrajectoryHighLow = src->stats.HitTrajectoryHighLow;
    dst->stats.Speed = src->stats.Speed;
    dst->stats.ThrowingArm = src->stats.ThrowingArm;
    dst->stats.CharacterClass = src->stats.CharacterClass;
    dst->stats.Weight = src->stats.Weight;
    dst->stats.Captain = src->stats.Captain;
    dst->stats.CaptainStarHitPitch = src->stats.CaptainStarHitPitch;
    memcpy(&dst->stats.NonCaptainStarSwing, &src->stats.NonCaptainStarSwing, 2);
    dst->stats.FieldingStats = src->stats.FieldingStats;
    memcpy(&dst->stats.BattingStatBar, &src->stats.BattingStatBar, 4);
    memcpy(&dst->chemistry, &src->chemistry, sizeof(ChemistryTable));
    dst->BytesAfterChemistry[0] = src->BytesAfterChemistry[0];
    dst->UnusedShorts[0] = src->UnusedShorts[0];
    dst->UnusedShorts[1] = src->UnusedShorts[1];
    dst->UnusedShorts[2] = src->UnusedShorts[2];
    dst->UnusedShorts[3] = src->UnusedShorts[3];
    dst->UnusedShorts[4] = src->UnusedShorts[4];
    dst->UnusedShorts[5] = src->UnusedShorts[5];
    dst->UnusedShorts[6] = src->UnusedShorts[6];
    dst->UnusedShorts[7] = src->UnusedShorts[7];
    dst->UnusedShorts[8] = src->UnusedShorts[8];
    dst->UnusedShorts[9] = src->UnusedShorts[9];
    dst->UnusedShorts[10] = src->UnusedShorts[10];
    dst->UnusedShorts[11] = src->UnusedShorts[11];
    dst->UnusedShorts[12] = src->UnusedShorts[12];
    dst->UnusedShorts[13] = src->UnusedShorts[13];
    dst->UnusedShorts[14] = src->UnusedShorts[14];
    dst->UnusedShorts[15] = src->UnusedShorts[15];
    dst->UnusedShorts[16] = src->UnusedShorts[16];
    dst->UnusedShorts[17] = src->UnusedShorts[17];
    dst->UnusedShorts[18] = src->UnusedShorts[18];
    dst->UnusedShorts[19] = src->UnusedShorts[19];
    dst->UnusedShorts[20] = src->UnusedShorts[20];
}

void transferStatsToInMemRoster(u8 team) {
    int slot;
    s16 charID;
    u8 row;
    u8 col;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        return;
    }

    slot = aiPosSwapInputs.teamManagement_cursorPos[team] - 1;
    if (superstarUnlocked[inMemRoster[team][slot].stats.CharID] == 0) {
        return;
    }

    Static_Stats_Tables.unk4720[team]++;
    if (Static_Stats_Tables.unk4720[team] == 2) {
        Static_Stats_Tables.unk4720[team] = 0;
    }

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        Static_Stats_Tables.charIsStarred[team][slot] ^= 1;
        memcpy(lbl_802E4B00[team], Static_Stats_Tables.charIsStarred[team], sizeof(Static_Stats_Tables.charIsStarred[team]));
    } else {
        Static_Stats_Tables.charIsStarred[0][slot] = TRUE;
    }

    if (Static_Stats_Tables.charIsStarred[team][slot]) {
        inMemRoster[team][slot].stats.SlapContactSize += stonNiceContactIncrement.SlapContactSize;
        inMemRoster[team][slot].stats.ChargeContactSize += stonNiceContactIncrement.ChargeContactSize;
        inMemRoster[team][slot].stats.SlapHitPower += stonNiceContactIncrement.SlapHitPower;
        inMemRoster[team][slot].stats.ChargeHitPower += stonNiceContactIncrement.ChargeHitPower;
        inMemRoster[team][slot].stats.Speed += stonNiceContactIncrement.Speed;
        inMemRoster[team][slot].stats.ThrowingArm += stonNiceContactIncrement.ThrowingArm;
        inMemRoster[team][slot].stats.BuntingContactSize += stonNiceContactIncrement.BuntingContactSize;
        inMemRoster[team][slot].stats.CurveBallSpeed += stonNiceContactIncrement.CurveBallSpeed;
        inMemRoster[team][slot].stats.FastBallSpeed += stonNiceContactIncrement.FastBallSpeed;
        inMemRoster[team][slot].stats.cursedBall += stonNiceContactIncrement.cursedBall;
        inMemRoster[team][slot].stats.Curve += stonNiceContactIncrement.Curve;
        inMemRoster[team][slot].stats.curveControl += stonNiceContactIncrement.curveControl;

        inMemRoster[team][slot].stats.BattingStatBar += 2;
        if (inMemRoster[team][slot].stats.BattingStatBar > 10) {
            inMemRoster[team][slot].stats.BattingStatBar = 10;
        }
        inMemRoster[team][slot].stats.PitchingStatBar += 2;
        if (inMemRoster[team][slot].stats.PitchingStatBar > 10) {
            inMemRoster[team][slot].stats.PitchingStatBar = 10;
        }
        inMemRoster[team][slot].stats.RunningStatBar += 2;
        if (inMemRoster[team][slot].stats.RunningStatBar > 10) {
            inMemRoster[team][slot].stats.RunningStatBar = 10;
        }
        inMemRoster[team][slot].stats.FieldingStatBar += 2;
        if (inMemRoster[team][slot].stats.FieldingStatBar > 10) {
            inMemRoster[team][slot].stats.FieldingStatBar = 10;
        }
    } else {
        charID = inMemRoster[team][slot].stats.CharID;
        row = charID / 9;
        col = charID % 9;
        copyCharacterStats(&inMemRoster[team][slot], &Static_Stats_Tables.characterStats[row][col]);
    }
}
