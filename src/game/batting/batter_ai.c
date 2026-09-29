#include "game/batting/batter_ai.h"
#include "game/UnknownHomes_Game.h"
#include "game/math/game_math.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"

// .text:0x0001E4B8 size:0x26C mapped:0x8065D54C
void fn_3_1E4B8(void) {
    int roll;
    u32 difficulty;
    int pitches;
    int runner;
    f32 chance;
    g_AiLogic.batterAIStealIndicator = 0;
    roll = RandomInt_Game(100);
    difficulty = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];
    if (roll < batterAIPerfectStealProb[difficulty]) {
        g_AiLogic.batterAIStealingStartFrame = lbl_3_data_4B90[2] - 1;
    } else {
        g_AiLogic.batterAIStealingStartFrame = lbl_3_data_4B90[3] - 1;
    }
    pitches = g_Pitcher.nPitchesThisAB;
    if (pitches > 2) {
        pitches = 2;
    }
    if (g_RunningLogic._02 & 0x100) {
        if (g_RunningLogic._02 & 0x1000) {
            return;
        }
        chance = lbl_3_data_1C98[1][difficulty][pitches][g_Runners[2].characterClass];
        runner = 2;
    } else if (g_RunningLogic._02 & 0x10) {
        chance = lbl_3_data_1C98[1][difficulty][pitches][g_Runners[1].characterClass];
        runner = 1;
    } else {
        return;
    }
    chance *= batterAIBatterClassMultOnStealing[g_Batter.characterClass];
    if (g_Strikes.balls == 3) {
        chance *= batterAIBatterClassMultOnStealing[4];
    }
    if (g_Runners[runner].speed >= 50) {
        chance *= batterAIBatterClassMultOnStealing[5] * (f32)((g_Runners[runner].speed - 50) / 10) + lbl_3_rodata_918;
    }
    if (RandomInt_Game(100) < (int)chance) {
        g_AiLogic.batterAIStealIndicator = 1;
    }
}

// .text:0x0001E724 size:0xD0 mapped:0x8065D7B8
BOOL batterAIBuntDecision(void) {
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_FIELDING) {
        return batterAI_buntForPractice() != 0;
    }
    if (g_AiLogic.batterAIBuntInd != 1) {
        return 0;
    }
    if (g_AiLogic.aISwingDecisionRelated_noSwingOverride != 0) {
        return 0;
    }
    if (g_Ball.pitchHangtimeCounter <= 0) {
        return 1;
    }
    if (g_Pitcher.framesUntilBallReachesBatterZ == g_AiLogic.batterAIZPosition && batterAIBallLocRelated() == 0) {
        g_AiLogic.aISwingDecisionRelated_noSwingOverride = 1;
        return 0;
    }
    return 1;
}

// .text:0x0001E7F4 size:0x2B4 mapped:0x8065D888
BOOL batterAIBallLocRelated(void) {
    int zone;
    int fromMid;
    int prob;
    if (g_Pitcher.starPitchType == 3 || g_Pitcher.starPitchType == 4) {
        fromMid = 0;
    } else if (g_Pitcher.starPitchType == 11 || g_Pitcher.starPitchType == 12) {
        fromMid = 0;
    } else if (g_Pitcher.starPitchType == 1 || g_Pitcher.starPitchType == 2) {
        fromMid = 0;
    } else {
        for (zone = 0; zone < 4; zone++) {
            if (g_Pitcher.pitchXPosition < lbl_3_data_19CC[zone]) {
                break;
            }
        }
        if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
            zone = 4 - zone;
        }
        if (zone == 1 || zone == 3) {
            fromMid = 1;
        } else if (zone == 2) {
            fromMid = 0;
        } else {
            fromMid = 2;
        }
        if (g_AiLogic.batterAIBuntInd != 1) {
            if (g_AiLogic.aIBatterTrackingCode != 0 || fromMid == 0 || g_AiLogic.lastPitchBallLocZone == zone) {
                if (g_AiLogic.batterAISwingEarly1OrLate2 == 0) {
                    prob = lbl_3_data_1ADC[1][g_AiLogic.aIBatterDifficulty];
                } else {
                    prob = lbl_3_data_1ADC[3][g_AiLogic.aIBatterDifficulty];
                }
            } else if (g_AiLogic.batterAISwingEarly1OrLate2 == 0) {
                prob = lbl_3_data_1ADC[0][g_AiLogic.aIBatterDifficulty];
            } else {
                prob = lbl_3_data_1ADC[2][g_AiLogic.aIBatterDifficulty];
            }
            if (RandomInt_Game(100) >= prob) {
                return 0;
            }
        }
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        fromMid = lbl_3_data_1AEC[fromMid + 3][g_Batter.characterClass][g_AiLogic.aIBatterDifficulty];
    } else {
        fromMid = lbl_3_data_1AEC[fromMid][g_Batter.characterClass][g_AiLogic.aIBatterDifficulty];
    }
    if (g_AiLogic.batterAIBuntInd == 1) {
        fromMid += lbl_3_data_1B4C[0];
    } else if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 2) {
        fromMid += lbl_3_data_1B4C[1];
    }
    return RandomInt_Game(100) < fromMid;
}

// .text:0x0001EAA8 size:0x53C mapped:0x8065DB3C
void batterAIFrameToSwingAndStickInput(void) {
    int idx;
    int flag;
    int adj;
    if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 3) {
        return;
    }
    if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 0) {
        idx = RandomIndexFromWeights(lbl_3_data_1B50[g_AiLogic.aIBatterDifficulty][0], 9);
        flag = 0;
    } else {
        idx = RandomIndexFromWeights(lbl_3_data_1B50[g_AiLogic.aIBatterDifficulty][1], 9);
        flag = 1;
    }
    g_AiLogic.aIDesiredFrameToSwing = g_AiLogic.frameToStartSwing = g_Pitcher.framesUntilBallReachesBatterZ + g_Ball.pitchHangtimeCounter - swingSoundFrame[flag][1];
    g_AiLogic.frameToStartSwing = idx - 4 + g_AiLogic.aIDesiredFrameToSwing;
    if (g_Pitcher.starPitchType == 7 || g_Pitcher.starPitchType == 8) {
        if (RandomInt_Game(100) >= lbl_3_data_1BD4[g_AiLogic.aIBatterDifficulty]) {
            g_AiLogic.frameToStartSwing += g_Pitcher.bulletPitchLoopFrames;
        }
    }
    if (g_Pitcher.starPitchType == 1 || g_Pitcher.starPitchType == 2) {
        adj = RandomInt_Game_Range(lbl_3_data_1BC4[g_AiLogic.aIBatterDifficulty][0], lbl_3_data_1BC4[g_AiLogic.aIBatterDifficulty][1]);
        if (adj > 5) {
            adj = 5;
        }
        g_AiLogic.frameToStartSwing += adj;
    } else if (g_Pitcher.starPitchType == 0xB || g_Pitcher.starPitchType == 0xC) {
        g_AiLogic.frameToStartSwing += RandomInt_Game_Range(lbl_3_data_1BBC[g_AiLogic.aIBatterDifficulty][0], lbl_3_data_1BBC[g_AiLogic.aIBatterDifficulty][1]);
    } else if (g_Pitcher.starPitchType == 9 || g_Pitcher.starPitchType == 0xA) {
        g_AiLogic.frameToStartSwing += RandomInt_Game_Range(lbl_3_data_1BCC[g_AiLogic.aIBatterDifficulty][0], lbl_3_data_1BCC[g_AiLogic.aIBatterDifficulty][1]);
    } else if (g_AiLogic.batterAISwingEarly1OrLate2 == 0) {
        if (RandomInt_Game(100) < lbl_3_data_1B98[g_Batter.characterClass][g_AiLogic.aIBatterDifficulty]) {
            g_AiLogic.frameToStartSwing += lbl_3_data_1BA8[g_AiLogic.aIBatterDifficulty];
        }
    } else {
        g_AiLogic.frameToStartSwing += RandomInt_Game_Range(lbl_3_data_1BAC[g_AiLogic.batterAISwingEarly1OrLate2 != 1][g_AiLogic.aIBatterDifficulty][0], lbl_3_data_1BAC[g_AiLogic.batterAISwingEarly1OrLate2 != 1][g_AiLogic.aIBatterDifficulty][1]);
    }
    g_AiLogic.batterAILeftRightInput = RandomIndexFromWeights(lbl_3_data_1BD8[g_Batter.characterClass], 3);
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        int ia = ((s8*)g_Minigame.minigameFielderIndex)[(s8)g_Minigame.minigameControlStruct[1].aIStrength[3]];
        int ib = ((s8*)g_Minigame.minigameFielderIndex)[(s8)g_Minigame.minigameControlStruct[1]._14];
        if (g_Fielders[ia].pos.x < 0.0f && g_Fielders[ib].pos.x < 0.0f) {
            if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
                g_AiLogic.batterAILeftRightInput = 0;
            } else {
                g_AiLogic.batterAILeftRightInput = 2;
            }
        } else if (g_Fielders[ia].pos.x > 0.0f && g_Fielders[ib].pos.x > 0.0f) {
            if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
                g_AiLogic.batterAILeftRightInput = 2;
            } else {
                g_AiLogic.batterAILeftRightInput = 0;
            }
        } else {
            int r = fn_3_E587C();
            if (r >= 4) {
                if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
                    g_AiLogic.batterAILeftRightInput = 0;
                } else {
                    g_AiLogic.batterAILeftRightInput = 2;
                }
            } else if (r != 3 && r >= 0) {
                if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
                    g_AiLogic.batterAILeftRightInput = 2;
                } else {
                    g_AiLogic.batterAILeftRightInput = 0;
                }
            }
        }
    } else if (g_Strikes.outs <= 1 && (g_RunningLogic._02 & 0x1000) && g_AiLogic.aIBatterDifficulty >= 1) {
        if (g_Batter.characterClass == CHARACTER_CLASS_POWER) {
            g_AiLogic.batterAIUpDownInput = RandomIndexFromWeights(lbl_3_data_1BF0[0][g_AiLogic.aIBatterDifficulty], 3);
        } else {
            g_AiLogic.batterAIUpDownInput = RandomIndexFromWeights(lbl_3_data_1BF0[1][g_AiLogic.aIBatterDifficulty], 3);
        }
    } else {
        g_AiLogic.batterAIUpDownInput = RandomIndexFromWeights(lbl_3_data_1BE4[g_Batter.characterClass], 3);
    }
}

// .text:0x0001EFE4 size:0x1E8 mapped:0x8065E078
BOOL batterAISwingInd(void) {
    int estFrames;
    int remaining;
    if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 3) {
        return 0;
    }
    if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 1) {
        if (g_AiLogic.batterAIInd2 != 0 && g_AiLogic.lastPitchType != 0xFF) {
            estFrames = (&g_Pitcher.windupCountdownUntilBallReleased)[2 - g_AiLogic.lastPitchType] + g_AiLogic.lastPitchFramesUntilPitchGetsToBatter;
            estFrames -= lbl_3_data_19C4[4];
        } else {
            estFrames = g_Pitcher.curvePitchWindupFrames + 20;
        }
        remaining = estFrames - g_Pitcher.pitchTotalTimeCounter;
        remaining -= g_Batter.frameFullyCharged;
        if (remaining <= 0 ||
            g_Pitcher.windupCountdownUntilBallReleased < 8) {
            g_Batter.chargeStatus = CHARGE_SWING_STAGE_CHARGEUP;
            g_Batter.hitGeneralType = BAT_CONTACT_TYPE_CHARGE;
        }
    }
    if (g_Ball.pitchHangtimeCounter <= 0) {
        return 0;
    }
    if (g_AiLogic.batterAISwingInd != 0) {
        return 0;
    }
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_FIELDING) {
        fieldingPracticeAISwingDecision();
    } else {
        if (g_AiLogic.aISwingDecisionRelated_noSwingOverride != 0) {
            return 0;
        }
        if (g_Ball.pitchHangtimeCounter == 1) {
            batterAIFrameToSwingAndStickInput();
        }
        if (g_Pitcher.framesUntilBallReachesBatterZ == g_AiLogic.batterAIZPosition && batterAIBallLocRelated() == 0) {
            g_AiLogic.someNotAISwingInd = 1;
        }
        if (g_Ball.pitchHangtimeCounter == g_AiLogic.frameToStartSwing + 1 && g_AiLogic.frameToStartSwing != 0 &&
            g_AiLogic.someNotAISwingInd == 0) {
            g_AiLogic.batterAISwingInd = 1;
        }
    }
    return g_AiLogic.batterAISwingInd != 0;
}

// .text:0x0001F1CC size:0x184 mapped:0x8065E260
void fn_3_1F1CC(void) {
    f32 amount;
    if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch == 3) {
        g_AiLogic.batterAIDesiredXPosInBox = g_AiLogic.boxHorizontalPoint;
    } else if (g_Batter.characterClass == CHARACTER_CLASS_SPEED) {
        if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch != 1) {
            if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch == 2 && g_AiLogic._6B != 0) {
                g_AiLogic._6B--;
            } else {
                g_AiLogic.batterAIDesiredXPosInBox = RandomF32_Game_Range(lbl_3_data_19DC[0][0], lbl_3_data_19DC[4][1]);
                amount = RandomF32_Game_Range(lbl_3_data_1A04[1], lbl_3_data_1A04[0] + lbl_3_data_1A04[0]);
                if (RandomInt_Game(2) != 0) {
                    g_AiLogic.batterAIDesiredXPosInBox += amount;
                } else {
                    g_AiLogic.batterAIDesiredXPosInBox -= amount;
                }
                if (g_AiLogic.batterAIDesiredXPosInBox < -lbl_3_data_1A04[0]) {
                    g_AiLogic.batterAIDesiredXPosInBox = -lbl_3_data_1A04[0];
                } else if (g_AiLogic.batterAIDesiredXPosInBox > lbl_3_data_1A04[0]) {
                    g_AiLogic.batterAIDesiredXPosInBox = lbl_3_data_1A04[0];
                }
                g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 1;
                g_AiLogic._6B = RandomInt_Game(0x2d) + 0xf;
            }
        }
    } else if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch == 0) {
        g_AiLogic.batterAIDesiredXPosInBox = RandomF32_Game_Range(lbl_3_data_19DC[g_AiLogic.batterAIInd9PrincessStarHit + 1][0], lbl_3_data_19DC[g_AiLogic.batterAIInd9PrincessStarHit + 1][1]);
        g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 1;
    }
}

// .text:0x0001F350 size:0x128 mapped:0x8065E3E4
void batterAIGuessPitchLocation(void) {
    if (g_Pitcher.windupCountdownUntilBallReleased == lbl_3_data_1A3C[g_AiLogic.aIBatterDifficulty]) {
        if (g_AiLogic.lastPitchBallLocZone != 0xFF && RandomInt_Game(100) < lbl_3_data_1A24[g_Batter.characterClass]) {
            g_AiLogic.batterAI_GuessedPitchLocZone = g_AiLogic.lastPitchBallLocZone;
            if (g_AiLogic.batterAI_GuessedPitchLocZone == 0) {
                g_AiLogic.batterAI_GuessedPitchLocZone = 1;
            } else if (g_AiLogic.batterAI_GuessedPitchLocZone == 4) {
                g_AiLogic.batterAI_GuessedPitchLocZone = 3;
            }
        } else {
            g_AiLogic.batterAI_GuessedPitchLocZone = RandomIndexFromWeights(lbl_3_data_1A28[g_Batter.characterClass], 5);
        }
        g_AiLogic.batterAIDesiredXPosInBox = RandomF32_Game_Range(lbl_3_data_19DC[g_AiLogic.batterAI_GuessedPitchLocZone][0], lbl_3_data_19DC[g_AiLogic.batterAI_GuessedPitchLocZone][1]);
        g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 1;
    }
}

// .text:0x0001F478 size:0x520 mapped:0x8065E50C
void batterTrackBallInBox(void) {
    int downMiddle = 0;
    int prob;
    int zone;
    f32 pitchX;
    f32 step;
    f32 edge;
    if (g_Ball.pitchHangtimeCounter < g_AiLogic.batterAIInd8_FrameBtwn10And16) {
        batterAIGuessPitchLocation();
    } else if (g_Ball.pitchHangtimeCounter == g_AiLogic.batterAIInd8_FrameBtwn10And16) {
        if (g_Pitcher.starPitchType == 3 || g_Pitcher.starPitchType == 4) {
            g_AiLogic._73 = RandomInt_Game(2);
            prob = lbl_3_data_1A40[5][g_AiLogic.aIBatterDifficulty];
        } else if (g_Pitcher.starPitchType == 0xB || g_Pitcher.starPitchType == 0xC) {
            g_AiLogic.batterAITrackBallPoorlyOffset = RandomF32_Game_Range(-lbl_3_data_1AA8, lbl_3_data_1AA8);
            g_AiLogic.aIBatterTrackingCode = 2;
            return;
        } else if (g_Pitcher.pitchXPosition2 >= lbl_3_data_19CC[1] && g_Pitcher.pitchXPosition2 < lbl_3_data_19CC[2]) {
            downMiddle = 1;
            prob = lbl_3_data_1A40[4][g_AiLogic.aIBatterDifficulty];
        } else {
            prob = lbl_3_data_1A40[g_Batter.characterClass][g_AiLogic.aIBatterDifficulty];
        }
        if (RandomInt_Game(100) >= prob) {
            return;
        }
        step = (lbl_3_data_4474[1] - lbl_3_data_4474[0]) / lbl_3_rodata_934;
        edge = lbl_3_data_4474[0];
        for (zone = 0; zone < 4; zone++) {
            edge += step;
            if (g_Pitcher.pitcher.x < edge) {
                break;
            }
        }
        if (g_Pitcher.starPitchType == 3 || g_Pitcher.starPitchType == 4) {
            prob = lbl_3_data_1A58[0][g_Batter.characterClass][g_AiLogic.aIBatterDifficulty];
        } else if (downMiddle != 0) {
            prob = lbl_3_data_1A58[2][g_Batter.characterClass][g_AiLogic.aIBatterDifficulty];
        } else if (g_AiLogic.lastPitchMoundZone == zone) {
            prob = lbl_3_data_1A58[1][g_Batter.characterClass][g_AiLogic.aIBatterDifficulty];
        } else {
            prob = lbl_3_data_1A58[0][g_Batter.characterClass][g_AiLogic.aIBatterDifficulty];
        }
        if (RandomInt_Game(100) < prob) {
            g_AiLogic.batterAITrackBallPoorlyOffset = RandomF32_Game_Range(lbl_3_data_1A88[g_AiLogic.aIBatterDifficulty][0], lbl_3_data_1A88[g_AiLogic.aIBatterDifficulty][1]);
            if (RandomInt_Game(2) != 0) {
                g_AiLogic.batterAITrackBallPoorlyOffset = -g_AiLogic.batterAITrackBallPoorlyOffset;
            }
            g_AiLogic.aIBatterTrackingCode = 1;
        } else {
            g_AiLogic.aIBatterTrackingCode = 2;
            g_AiLogic.batterAITrackBallPoorlyOffset = lbl_3_rodata_930;
        }
    } else if (g_AiLogic.aIBatterTrackingCode != 0) {
        if (g_Pitcher.starPitchType == 0xB || g_Pitcher.starPitchType == 0xC) {
            g_AiLogic.batterAIDesiredXPosInBox = g_AiLogic.batterAITrackBallPoorlyOffset;
        } else {
            pitchX = g_Pitcher.pitchXPosition;
            if (g_Pitcher.starPitchType == 3 || g_Pitcher.starPitchType == 4) {
                if (g_Pitcher.warioWaluStarPitchRightLeft == 0) {
                    pitchX += lbl_3_data_5EB8[0];
                } else {
                    pitchX -= lbl_3_data_5EB8[0];
                }
                if (g_AiLogic._73 == 0) {
                    pitchX = -pitchX;
                }
            }
            if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
                g_AiLogic.batterAIDesiredXPosInBox = -pitchX - g_AiLogic.batterAITrackBallPoorlyOffset;
            } else {
                g_AiLogic.batterAIDesiredXPosInBox = pitchX + g_AiLogic.batterAITrackBallPoorlyOffset;
            }
        }
    }
}

// .text:0x0001F998 size:0x3F4 mapped:0x8065EA2C
void batterAIMoveBatter(void) {
    BatterReachStruct* hitbox = &BatterHitbox[g_Batter.charID];
    f32* veloLimits = lbl_3_data_1A0C;
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_FIELDING) {
        return;
    }
    if (g_Pitcher.windupCountdownUntilBallReleased <= lbl_3_data_1A3C[g_AiLogic.aIBatterDifficulty]) {
        batterTrackBallInBox();
    } else {
        fn_3_1F1CC();
    }
    if (g_AiLogic.batterAIDesiredXPosInBox < g_AiLogic.boxHorizontalPoint) {
        g_AiLogic.batterAIBoxPosXVelo -= veloLimits[1];
        if (g_AiLogic.batterAIBoxPosXVelo < -veloLimits[0]) {
            g_AiLogic.batterAIBoxPosXVelo = -veloLimits[0];
        }
        g_AiLogic.boxHorizontalPoint += g_AiLogic.batterAIBoxPosXVelo;
        if (g_AiLogic.batterAIDesiredXPosInBox > g_AiLogic.boxHorizontalPoint) {
            g_AiLogic.boxHorizontalPoint = g_AiLogic.batterAIDesiredXPosInBox;
        }
    } else if (g_AiLogic.batterAIDesiredXPosInBox > g_AiLogic.boxHorizontalPoint) {
        g_AiLogic.batterAIBoxPosXVelo += veloLimits[1];
        if (g_AiLogic.batterAIBoxPosXVelo > veloLimits[0]) {
            g_AiLogic.batterAIBoxPosXVelo = veloLimits[0];
        }
        g_AiLogic.boxHorizontalPoint += g_AiLogic.batterAIBoxPosXVelo;
        if (g_AiLogic.batterAIDesiredXPosInBox < g_AiLogic.boxHorizontalPoint) {
            g_AiLogic.boxHorizontalPoint = g_AiLogic.batterAIDesiredXPosInBox;
        }
    } else {
        g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 2;
        g_AiLogic.batterAIBoxPosXVelo = lbl_3_rodata_930;
    }
    if (g_AiLogic.boxHorizontalPoint < hitbox->HorizontalRangeNear) {
        g_AiLogic.boxHorizontalPoint = hitbox->HorizontalRangeNear;
    }
    if (g_AiLogic.boxHorizontalPoint > hitbox->HorizontalRangeFar) {
        g_AiLogic.boxHorizontalPoint = hitbox->HorizontalRangeFar;
    }
    if (g_AiLogic.batterAIDesiredZPosInBox < g_AiLogic.boxVerticalPoint) {
        g_AiLogic.batterAIBoxPosZVelo -= veloLimits[1];
        if (g_AiLogic.batterAIBoxPosZVelo < -veloLimits[0]) {
            g_AiLogic.batterAIBoxPosZVelo = -veloLimits[0];
        }
        g_AiLogic.boxVerticalPoint += g_AiLogic.batterAIBoxPosZVelo;
        if (g_AiLogic.batterAIDesiredZPosInBox > g_AiLogic.boxVerticalPoint) {
            g_AiLogic.boxVerticalPoint = g_AiLogic.batterAIDesiredZPosInBox;
        }
    } else if (g_AiLogic.batterAIDesiredZPosInBox > g_AiLogic.boxVerticalPoint) {
        g_AiLogic.batterAIBoxPosZVelo += veloLimits[1];
        if (g_AiLogic.batterAIBoxPosZVelo > veloLimits[0]) {
            g_AiLogic.batterAIBoxPosZVelo = veloLimits[0];
        }
        g_AiLogic.boxVerticalPoint += g_AiLogic.batterAIBoxPosZVelo;
        if (g_AiLogic.batterAIDesiredZPosInBox < g_AiLogic.boxVerticalPoint) {
            g_AiLogic.boxVerticalPoint = g_AiLogic.batterAIDesiredZPosInBox;
        }
    } else {
        g_AiLogic.batterAIBoxPosZVelo = lbl_3_rodata_930;
    }
    if (g_AiLogic.boxVerticalPoint < hitbox->VerticalRangeFront) {
        g_AiLogic.boxVerticalPoint = hitbox->VerticalRangeFront;
    }
    if (g_AiLogic.boxVerticalPoint > hitbox->VerticalRangeBack) {
        g_AiLogic.boxVerticalPoint = hitbox->VerticalRangeBack;
    }
    g_Batter.batPosition2.x = g_AiLogic.boxHorizontalPoint;
    g_Batter.batPosition2.z = g_AiLogic.boxVerticalPoint;
    g_Batter.batterPos.x = g_Batter.batPosition2.x + hitbox->batOffsetFromBatterX;
    g_Batter.batterPos.z = g_Batter.batPosition2.z + hitbox->batOffsetFromBatterZ;
    if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
        g_Batter.batterPos.x = -g_Batter.batterPos.x;
    }
}

// .text:0x0001FD8C size:0x1BC mapped:0x8065EE20
void batterAIControlled(void) {
    BOOL bunt;
    if (g_Batter.swingInd == 0 && g_Batter.buntStatus == BUNT_STATUS_NONE) {
        if (batterAISwingInd() != 0) {
            g_Batter.swingInd = 1;
            g_Batter.framesSinceStartOfSwing = 0;
        }
    }
    if (g_Batter.swingInd == 0 && g_Batter.buntStatus != BUNT_STATUS_STRIKE) {
        batterAIMoveBatter();
    }
    if (g_Batter.swingInd == 0 && g_Batter.buntStatus != BUNT_STATUS_STRIKE && g_Batter.buntStatus != BUNT_STATUS_6) {
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_FIELDING) {
            if (batterAI_buntForPractice() != 0) {
                bunt = 1;
            } else {
                bunt = 0;
            }
        } else if (g_AiLogic.batterAIBuntInd != 1) {
            bunt = 0;
        } else if (g_AiLogic.aISwingDecisionRelated_noSwingOverride != 0) {
            bunt = 0;
        } else if (g_Ball.pitchHangtimeCounter <= 0) {
            bunt = 1;
        } else if (g_Pitcher.framesUntilBallReachesBatterZ == g_AiLogic.batterAIZPosition && batterAIBallLocRelated() == 0) {
            g_AiLogic.aISwingDecisionRelated_noSwingOverride = 1;
            bunt = 0;
        } else {
            bunt = 1;
        }
        if (bunt) {
            g_Batter.isBunting = 1;
            g_Batter.hitGeneralType = BAT_CONTACT_TYPE_BUNT;
            if (g_Batter.buntStatus == BUNT_STATUS_NONE) {
                g_Batter.buntStatus = BUNT_STATUS_STARTING;
                g_Batter.framesBuntHeld = 0;
            }
        } else {
            g_Batter.isBunting = 0;
        }
    }
}

// .text:0x0001FF48 size:0x11C mapped:0x8065EFDC
void trackLastPitchInfo2(void) {
    int zone;
    f32 step;
    f32 edge;
    if (g_Pitcher.starPitchType != 0) {
        return;
    }
    g_AiLogic.lastPitchFramesUntilPitchGetsToBatter = g_Pitcher.framesUntilPitchGetsToBatter;
    g_AiLogic.lastPitchType = g_Pitcher.TypeOfPitch;
    for (zone = 0; zone < 4; zone++) {
        if (g_Pitcher.pitchXPosition < lbl_3_data_19CC[zone]) {
            break;
        }
    }
    if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
        zone = 4 - zone;
    }
    g_AiLogic.lastPitchBallLocZone = zone;
    step = (lbl_3_data_4474[1] - lbl_3_data_4474[0]) / lbl_3_rodata_934;
    edge = lbl_3_data_4474[0];
    for (zone = 0; zone < 4; zone++) {
        edge += step;
        if (g_Pitcher.pitcher.x < edge) {
            break;
        }
    }
    g_AiLogic.lastPitchMoundZone = zone;
}

// .text:0x00020064 size:0x124 mapped:0x8065F0F8
void batterAISwingEarlyOrLate(void) {
    g_AiLogic.batterAITrackBallPoorlyOffset = lbl_3_rodata_930;
    if (g_Pitcher.starPitchType != 0) {
        return;
    }
    if (g_Pitcher.TypeOfPitch == 0) {
        g_AiLogic.batterAISwingEarly1OrLate2 = 0;
    } else if (g_AiLogic.batterAIPitchGuessed != g_Pitcher.TypeOfPitch) {
        if (g_Pitcher.TypeOfPitch == 1) {
            if (RandomInt_Game(100) < lbl_3_data_1ABC[0][g_Batter.characterClass][g_AiLogic.aIBatterDifficulty]) {
                g_AiLogic.batterAISwingEarly1OrLate2 = 0;
            } else {
                g_AiLogic.batterAISwingEarly1OrLate2 = 1;
            }
        } else {
            if (RandomInt_Game(100) < lbl_3_data_1ABC[1][g_Batter.characterClass][g_AiLogic.aIBatterDifficulty]) {
                g_AiLogic.batterAISwingEarly1OrLate2 = 0;
            } else {
                g_AiLogic.batterAISwingEarly1OrLate2 = 2;
            }
        }
    } else {
        g_AiLogic.batterAISwingEarly1OrLate2 = 0;
    }
}

// .text:0x00020188 size:0x9C mapped:0x8065F21C
void batterAIGuessPitchType(void) {
    if (g_AiLogic.lastPitchType != 0xFF && RandomInt_Game(100) < lbl_3_data_1AAC[g_AiLogic.aIBatterDifficulty]) {
        g_AiLogic.batterAIPitchGuessed = g_AiLogic.lastPitchType;
    } else {
        g_AiLogic.batterAIPitchGuessed = RandomIndexFromWeights(lbl_3_data_1AB0[g_Pitcher.charClass], 3);
    }
}

// .text:0x00020224 size:0x83C mapped:0x8065F2B8
void batterAIRNGValueSetting(void) {
    int urgency;
    int roll;
    int pitchCat;
    int buntIdx;
    int zspan;
    u32 difficulty;
    int runner;
    f32 chance;
    if (g_Batter.aiControlledInd != 0) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.practiceType_2 != PRACTICE_TYPE_FREEPLAY) {
            g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 0;
            g_AiLogic.batterAIInd9PrincessStarHit = 1;
            g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 3;
        } else {
            g_AiLogic.aIBatterDifficulty = batterAIConstants[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
            g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 0;
            if (!g_d_GameSettings.minigamesEnabled && g_GameLogic.freeFieldingPracticeInd == 0) {
                if (g_AiLogic.batterAIABStrat < 0) {
                    g_AiLogic.batterAIABStrat = 0;
                    if (g_GameLogic.TeamStars[g_GameLogic.teamBatting] != 0) {
                        urgency = -1;
                        if (g_Scores.Inning >= g_Scores.inningLimit && g_Strikes.outs == 2 && g_Scores._A6 != 0) {
                            urgency = 0;
                        } else if ((g_RunningLogic._00 & 0x1000) || g_RunningLogic._10 >= 3) {
                            urgency = 1;
                        } else if (g_Scores._pad_AC >= 2 && g_Scores._A6 <= 1 &&
                                   g_AiLogic.starRelated[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
                            urgency = 2;
                        }
                        if (urgency >= 0 &&
                            RandomInt_Game(100) < lbl_3_data_1944[urgency][g_AiLogic.aIBatterDifficulty][g_GameLogic.TeamStars[g_GameLogic.teamBatting]]) {
                            g_AiLogic.batterAIABStrat = 1;
                        }
                    }
                }
                if (g_AiLogic.batterAIABStrat != 0) {
                    roll = RandomInt_Game(100);
                    if (g_Pitcher.nPitchesThisAB == 0) {
                        pitchCat = 0;
                    } else if (g_Pitcher.nPitchesThisAB >= 6) {
                        pitchCat = 4;
                    } else if (g_Strikes.strikes == 0) {
                        pitchCat = 1;
                    } else if (g_Strikes.strikes == 1) {
                        pitchCat = 2;
                    } else {
                        pitchCat = 3;
                    }
                    if (roll < lbl_3_data_198C[g_AiLogic.aIBatterDifficulty][pitchCat][0]) {
                        g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 2;
                    } else if (roll - lbl_3_data_198C[g_AiLogic.aIBatterDifficulty][pitchCat][0] < lbl_3_data_198C[g_AiLogic.aIBatterDifficulty][pitchCat][1]) {
                        g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 0;
                    } else {
                        g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 3;
                    }
                }
            }
            if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 2) {
                g_Batter.isStarSwing = 1;
            } else {
                g_Batter.isStarSwing = 0;
            }
            if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 0) {
                g_AiLogic.batterAIInd2 = 0;
                if (RandomInt_Game(100) < lbl_3_data_19B4[g_Batter.characterClass][g_AiLogic.aIBatterDifficulty]) {
                    g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 1;
                    if (g_AiLogic.lastPitchFramesUntilPitchGetsToBatter != 0 &&
                        RandomInt_Game(100) < lbl_3_data_19C4[g_AiLogic.aIBatterDifficulty]) {
                        g_AiLogic.batterAIInd2 = 1;
                    }
                }
            }
            if (g_AiLogic.batterAIBuntPossibility != 0) {
                g_AiLogic.batterAIBuntPossibility = 0;
                g_AiLogic.batterAIBuntInd = 0;
                if (g_Scores._A6 <= 2 && g_Scores._pad_AC >= 2 && g_Strikes.outs <= 1 &&
                    (g_RunningLogic._02 == 0x11 || g_RunningLogic._02 == 0x111) &&
                    RandomInt_Game(100) < lbl_3_data_1C10[g_Batter.characterClass][g_AiLogic.aIBatterDifficulty]) {
                    g_AiLogic.batterAIBuntInd = 1;
                }
            }
            g_AiLogic.batterAIStealIndicator = 0;
            roll = RandomInt_Game(100);
            difficulty = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];
            if (roll < batterAIPerfectStealProb[difficulty]) {
                g_AiLogic.batterAIStealingStartFrame = lbl_3_data_4B90[2] - 1;
            } else {
                g_AiLogic.batterAIStealingStartFrame = lbl_3_data_4B90[3] - 1;
            }
            pitchCat = g_Pitcher.nPitchesThisAB;
            if (pitchCat > 2) {
                pitchCat = 2;
            }
            do {
                if (g_RunningLogic._02 & 0x100) {
                    if (g_RunningLogic._02 & 0x1000) {
                        break;
                    }
                    chance = lbl_3_data_1C98[1][difficulty][pitchCat][g_Runners[2].characterClass];
                    runner = 2;
                } else if (g_RunningLogic._02 & 0x10) {
                    chance = lbl_3_data_1C98[1][difficulty][pitchCat][g_Runners[1].characterClass];
                    runner = 1;
                } else {
                    break;
                }
                chance *= batterAIBatterClassMultOnStealing[g_Batter.characterClass];
                if (g_Strikes.balls == 3) {
                    chance *= batterAIBatterClassMultOnStealing[4];
                }
                if (g_Runners[runner].speed >= 50) {
                    chance *= batterAIBatterClassMultOnStealing[5] * (f32)((g_Runners[runner].speed - 50) / 10) + lbl_3_rodata_918;
                }
                if (RandomInt_Game(100) < (int)chance) {
                    g_AiLogic.batterAIStealIndicator = 1;
                }
            } while (0);
            buntIdx = 0;
            if (g_AiLogic.batterAIBuntInd == 1) {
                buntIdx = 1;
            }
            zspan = lbl_3_data_1C08[buntIdx][1] - lbl_3_data_1C08[buntIdx][0];
            g_AiLogic.batterAIZPosition = (int)((f32)zspan * g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.homeTeamBattingInd_fieldingTeam]) + lbl_3_data_1C08[buntIdx][0];
            g_AiLogic.batterAIInd8_FrameBtwn10And16 = lbl_3_data_1C0C[0] +
                (int)((f32)(lbl_3_data_1C0C[1] - lbl_3_data_1C0C[0]) *
                      g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.homeTeamBattingInd_fieldingTeam]);
            g_AiLogic.batterAIInd9PrincessStarHit = RandomIndexFromWeights(lbl_3_data_1A14[g_Batter.characterClass], 3);
            g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 0;
            if (RandomInt_Game(100) < lbl_3_data_1A20[g_AiLogic.aIBatterDifficulty]) {
                g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 3;
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 3;
            }
            batterAIGuessPitchType();
        }
    }
    g_AiLogic.batterAIBoxPosXVelo = lbl_3_rodata_930;
    g_AiLogic.batterAIBoxPosZVelo = lbl_3_rodata_930;
    g_AiLogic.batterAISwingInd = 0;
    g_AiLogic.someNotAISwingInd = 0;
    g_AiLogic.aISwingDecisionRelated_noSwingOverride = 0;
    g_AiLogic.aIBatterTrackingCode = 0;
    g_AiLogic.batterAISwingEarly1OrLate2 = 0;
}
