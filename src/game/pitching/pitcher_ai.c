#include "game/pitching/pitcher_ai.h"
#include "game/pitching/pitcher.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/math/game_math.h"
#include "header_rep_data.h"

extern u8 aIMoundLocationProbabilities[4][6];
extern f32 lbl_3_data_4474[4];
extern u8 aiPitchWeakCurveProbabilities[4];
extern u8 pitchAIDelayPitchStartProbabilities[4][4];
extern f32 aIPitchCurveEndingXConstants[7];
extern u8 chargePitchProb[2][4][4];
extern u8 changeUpProb[4][4];
extern u8 perfectPitchProb[3][4];
extern u8 lbl_3_data_18C4[5][4];
extern s8 lbl_3_data_18D8[2];
extern u8 pickOffProb[4][4];
extern s16 lbl_3_data_1934[4];
extern u8 invertAILevels[8];

extern struct {
    u8 _00[0x42];
    s16 scoutCountdown;
    u8 _44[2];
    u8 scoutMissionID;
    u8 _47;
    u8 scoutFlag;
    u8 _49[5];
} lbl_3_common_bss_37400;

// .text:0x000219A0 size:0x2C mapped:0x80660A34
void resetPitcherPreAB(void) {
    g_AiLogic.nStarPitchesThrownThisAB = 0;
    g_AiLogic.aIMoundLocationX = 0.0f;
    g_AiLogic.aIMoundLocationIndex = 2;
    g_AiLogic.always0_AIPickoffRelated = 0;
}

// .text:0x00021768 size:0x238 mapped:0x806607FC
void pitcherAINewBatter(void) {
    int prob;

    g_AiLogic.pitcherAIPitchDownTheMiddleInd = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_2 == PRACTICE_TYPE_BATTING) {
            g_AiLogic.pitcherAIPitchDownTheMiddleInd = 1;
        } else if (g_Practice.practiceType_2 == PRACTICE_TYPE_FIELDING) {
            g_AiLogic.pitcherAIPitchDownTheMiddleInd = 1;
        } else if (g_Practice.practiceType_2 == PRACTICE_TYPE_BASERUNNING) {
            g_AiLogic.pitcherAIPitchDownTheMiddleInd = 1;
        } else if (g_Practice.practiceLevel == 4) {
            g_AiLogic.pitcherAIPitchDownTheMiddleInd = 1;
        }
    }
    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
        g_AiLogic.aiPitchCurveEndingX = 0.0f;
    }
    g_AiLogic.aIDifficultyInverse0Weak = invertAILevels[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam]];
    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
        g_AiLogic.AIFrameToBeginPitch = lbl_3_data_1934[2];
    } else {
        g_AiLogic.AIFrameToBeginPitch = RandomInt_Game_Range(lbl_3_data_1934[0], lbl_3_data_1934[1]);
    }
    if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400.scoutMissionID != 0 && g_Pitcher.nPitchesThisAB == 0) {
        g_AiLogic.AIFrameToBeginPitch = lbl_3_data_1934[1] + 60;
    }
    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd == 0) {
        g_AiLogic.aIPitcherPickOffInd = 0;
        if (g_RunningLogic._02 != 1 && g_RunningLogic._02 != 0x1111) {
            if (g_AiLogic.always0_AIPickoffRelated != 0) {
                prob = 5;
            } else {
                prob = pickOffProb[g_Pitcher.charClass][g_AiLogic.aIDifficultyInverse0Weak];
            }
            if (RandomInt_Game(100) < prob) {
                g_AiLogic.aIPitcherPickOffInd = 1;
            }
        }
    }
    g_AiLogic.aiPitchCurveType = 0;
    g_AiLogic.aiPitchDirectionInput = 0;
    g_AiLogic.pitchAIDelayCurveStart = 0;
    g_AiLogic.aIPerfectCharge = 0;
}

// .text:0x000215AC size:0x1BC mapped:0x80660640
void pitcherAI_prePitchSetConstants(void) {
    if (g_Pitcher.currentStateFrameCounter == 1) {
        pitcherAISelectMoundLocation();
    }
    movePitcherOnMound();
    if (g_Pitcher.currentStateFrameCounter >= g_AiLogic.AIFrameToBeginPitch && g_Batter.beginningOfABAnimationOccuring == 0) {
        pitcherAISelectPitch();
        pitcherAISetCurve();
        pitcherAITransitionFromPrePitchToWindup(PITCHER_ACTION_STATE_WINDUP);
        g_Stats._0038[0] = 1;
    }
}

// .text:0x000212A0 size:0x30C mapped:0x80660334
void pitcherAISelectPitch(void) {
    int prob;
    BOOL starSituation;

    g_AiLogic.aIPitchType = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        return;
    }
    if (g_d_GameSettings.minigamesEnabled == 0 && g_GameLogic.TeamStars[g_GameLogic.teamFielding] != 0) {
        starSituation = FALSE;
        /* Compares the addresses of the two ScoreStruct entries, not their totals. */
        if (g_Scores.Inning >= g_Scores.inningLimit &&
            &g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam] > &g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam] &&
            g_Strikes.outs >= 2) {
            starSituation = TRUE;
        } else if (g_Scores.Inning >= g_Scores.maxNumberOfExtraInnings && g_Scores.halfInning != 0 && g_Strikes.outs >= 2) {
            starSituation = TRUE;
        } else if (g_RunningLogic._02 == 0x101 || g_RunningLogic._02 == 0x1101 || g_RunningLogic._02 == 0x1111) {
            starSituation = TRUE;
        }
        if (starSituation) {
            prob = lbl_3_data_18C4[g_GameLogic.TeamStars[g_GameLogic.teamFielding] - 1][g_AiLogic.aIDifficultyInverse0Weak];
            if (g_AiLogic.nStarPitchesThrownThisAB != 0) {
                prob += lbl_3_data_18D8[0];
            } else if (g_Strikes.strikes != 0) {
                prob += g_Strikes.strikes * lbl_3_data_18D8[1];
            }
            if (RandomInt_Game(100) < prob) {
                g_AiLogic.aIPitchType = 2;
                g_Pitcher.starPitchInd = 1;
                return;
            }
        }
    }
    if (g_RunningLogic._00 == 1 || g_RunningLogic._00 == 0x1101 || g_RunningLogic._00 == 0x1111 || g_RunningLogic._00 == 0x1001) {
        prob = chargePitchProb[0][g_Pitcher.charClass][g_AiLogic.aIDifficultyInverse0Weak];
    } else {
        prob = chargePitchProb[1][g_Pitcher.charClass][g_AiLogic.aIDifficultyInverse0Weak];
    }
    if (RandomInt_Game(100) < prob) {
        g_AiLogic.aIPitchType = 1;
        if (RandomInt_Game(100) < changeUpProb[g_Pitcher.charClass][g_AiLogic.aIDifficultyInverse0Weak]) {
            g_AiLogic.aIPitchType = 3;
            g_Pitcher.TypeOfPitch = 2;
        } else {
            prob = perfectPitchProb[g_Strikes.strikes][g_AiLogic.aIDifficultyInverse0Weak];
            if (RandomInt_Game(100) < prob) {
                g_AiLogic.aIPerfectCharge = 1;
            }
        }
    }
}

// .text:0x00020FB0 size:0x2F0 mapped:0x80660044
void pitcherAISetCurve(void) {
    int tries;
    int loc;
    int skip;
    int base;
    int prob;
    int i;

    if (g_AiLogic.aiPitchCurveType == 0) {
        g_AiLogic.aiPitchCurveType = 3;
        if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
            g_AiLogic.aiPitchCurveType = 1;
        }
    }
    if (g_AiLogic.aiPitchCurveType == 1) {
        g_AiLogic.aiPitchCurveEndingX = 0.0f;
    } else if (g_AiLogic.aiPitchCurveType == 2) {
        g_AiLogic.aiPitchCurveEndingX = 0.01f * RandomInt_Game_Range(-10, 10);
    } else if (g_AiLogic.aiPitchCurveType == 3) {
        tries = 0;
        if (RandomInt_Game(100) < aiPitchWeakCurveProbabilities[g_AiLogic.aIDifficultyInverse0Weak]) {
            for (;;) {
                loc = g_AiLogic.aIMoundLocationIndex + RandomInt_Game(3);
                if (g_AiLogic.aIPitchDesiredEndingLocIndex != loc || tries >= 2) {
                    break;
                }
                tries++;
            }
        } else {
            for (;;) {
                skip = RandomInt_Game(4);
                base = g_AiLogic.aIMoundLocationIndex;
                for (i = 0; i < 7; i++) {
                    if (i != base && i != base + 1 && i != base + 2) {
                        if (skip == 0) {
                            break;
                        }
                        skip--;
                    }
                }
                loc = i;
                if (g_AiLogic.aIPitchDesiredEndingLocIndex != loc || tries >= 2) {
                    break;
                }
                tries++;
            }
        }
        g_AiLogic.aIPitchDesiredEndingLocIndex = loc;
        g_AiLogic.aiPitchCurveEndingX = aIPitchCurveEndingXConstants[loc];
    }
    g_AiLogic.pitchAIDelayCurveStart = 0;
    prob = pitchAIDelayPitchStartProbabilities[g_Pitcher.charClass][g_AiLogic.aIDifficultyInverse0Weak];
    if (prob < RandomInt_Game(100)) {
        g_AiLogic.pitchAIDelayCurveStart = 1;
    }
}

// .text:0x00020EEC size:0xC4 mapped:0x8065FF80
void pitcherAISelectMoundLocation(void) {
    int idx;
    f32 step;

    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
        g_AiLogic.aIMoundLocationX = 0.0f;
        return;
    }
    idx = RandomIndexFromWeights(aIMoundLocationProbabilities[g_Pitcher.charClass], 6);
    if (idx != 5) {
        g_AiLogic.aIMoundLocationIndex = idx;
        step = lbl_3_data_4474[1] - lbl_3_data_4474[0];
        step /= 5.0f;
        g_AiLogic.aIMoundLocationX = step * idx + lbl_3_data_4474[0];
    }
}

// .text:0x00020E50 size:0x9C mapped:0x8065FEE4
void movePitcherOnMound(void) {
    f32 diff;

    if (g_Pitcher.currentStateFrameCounter < 30) {
        return;
    }
    if (g_AiLogic.aIMoundLocationX == g_Pitcher.pitcher.x) {
        return;
    }
    diff = g_AiLogic.aIMoundLocationX - g_Pitcher.pitcher.x;
    if (diff > 0.0f) {
        if (diff <= lbl_3_data_4474[2]) {
            g_Pitcher.pitcher.x = g_AiLogic.aIMoundLocationX;
        } else {
            g_Pitcher.pitcher.x += lbl_3_data_4474[2];
        }
    } else {
        if (diff >= -lbl_3_data_4474[2]) {
            g_Pitcher.pitcher.x = g_AiLogic.aIMoundLocationX;
        } else {
            g_Pitcher.pitcher.x -= lbl_3_data_4474[2];
        }
    }
}

// .text:0x00020CEC size:0x164 mapped:0x8065FD80
int aiPitchCurveDirection(f32 curve) {
    int frame;
    int remaining;
    f32 diff;
    f32 reach;

    frame = g_Ball.pitchHangtimeCounter;
    if (frame <= 1) {
        return 0;
    }
    if (0.0f == curve) {
        return 0;
    }
    diff = g_AiLogic.aiPitchCurveEndingX - g_Pitcher.pitchXPosition2;
    if (g_AiLogic.pitchAIDelayCurveStart != 0) {
        remaining = g_Pitcher.frameWhenUnhittable - frame;
        if (remaining <= 0) {
            return 0;
        }
        reach = curve * ((remaining / 2) * remaining);
        if (diff < 0.0f) {
            if (-diff < reach) {
                return 0;
            }
        } else if (diff < reach) {
            return 0;
        }
        g_AiLogic.pitchAIDelayCurveStart = 0;
    }
    if (diff > 0.03f) {
        if (g_AiLogic.aiPitchDirectionInput == -1) {
            return 0;
        }
        g_AiLogic.aiPitchDirectionInput = 1;
        return 1;
    } else if (diff < -0.03f) {
        if (g_AiLogic.aiPitchDirectionInput == 1) {
            return 0;
        }
        g_AiLogic.aiPitchDirectionInput = -1;
        return -1;
    }
    return 0;
}

// .text:0x00020C34 size:0xB8 mapped:0x8065FCC8
void pitcherAIDecidePickoff(void) {
    int prob;

    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd == 0) {
        g_AiLogic.aIPitcherPickOffInd = FALSE;
        if (g_RunningLogic._02 == 1 || g_RunningLogic._02 == 0x1111) {
            return;
        }
        if (g_AiLogic.always0_AIPickoffRelated != 0) {
            prob = 5;
        } else {
            prob = pickOffProb[g_Pitcher.charClass][g_AiLogic.aIDifficultyInverse0Weak];
        }
        if (RandomInt_Game(100) < prob) {
            g_AiLogic.aIPitcherPickOffInd = TRUE;
        }
    }
}

// .text:0x00020B30 size:0x104 mapped:0x8065FBC4
int aIPickoff(void) {
    if (g_AiLogic.aIPitcherPickOffInd == 0) {
        return FALSE;
    }
    if (g_Pitcher.currentStateFrameCounter > g_AiLogic.AIFrameToBeginPitch - 10) {
        if (g_RunningLogic._02 == 0x1011) {
            if (RandomInt_Game(3) == 0) {
                g_Pitcher.pickOffLoc = 3;
            } else {
                g_Pitcher.pickOffLoc = 1;
            }
        } else if (g_RunningLogic._02 == 0x1101) {
            g_Pitcher.pickOffLoc = 3;
        } else if (g_RunningLogic._02 == 0x111) {
            g_Pitcher.pickOffLoc = 2;
        } else if (g_RunningLogic._02 == 0x1001) {
            g_Pitcher.pickOffLoc = 3;
        } else if (g_RunningLogic._02 == 0x101) {
            g_Pitcher.pickOffLoc = 2;
        } else {
            g_Pitcher.pickOffLoc = 1;
        }
        return TRUE;
    }
    return FALSE;
}
