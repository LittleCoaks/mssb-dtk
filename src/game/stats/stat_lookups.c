#define SQRT2_LINKAGE static
#include "game/stats/stat_lookups.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"

extern f32 lbl_3_data_5FC4[12];

// .text:0x0006D564 size:0xA0 mapped:0x806AC5F8
int getAdjustedPitcherStamina(int team, int rosterID, int amount) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_EXHIBITION_GAME ||
        g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (amount < 0 && PitcherStats_P1_P2[team][rosterID].stamina < -amount) {
            PitcherStats_P1_P2[team][rosterID].stamina = 0;
        } else {
            PitcherStats_P1_P2[team][rosterID].stamina += amount;
        }
    }
    return PitcherStats_P1_P2[team][rosterID].stamina;
}

// .text:0x0006D604 size:0x54 mapped:0x806AC698
BOOL checkFieldingStat(int team, int rosterID, int ability) {
    if (g_d_GameSettings.minigamesEnabled) {
        team = 0;
    }
    if ((1 << ability) & inMemRoster[team][rosterID].stats.FieldingStats) {
        return 1;
    }
    return 0;
}

// .text:0x0006D658 size:0x7C mapped:0x806AC6EC
int calculateChemistry(int team, int charIdA, int charIdB) {
    int chem = ((u8*)&((CharacterStats*)Static_Stats_Tables.characterStats)[charIdA].chemistry)[charIdB];

    if (!g_d_GameSettings.exhibitionMatchInd && g_d_GameSettings.humanTeamNumber == team &&
        g_d_GameSettings.challengeCaptainStarBought[5] != 0) {
        chem += (int)lbl_3_data_5FC4[10];
    }
    if (chem > 100) {
        chem = 100;
    }
    return chem;
}
