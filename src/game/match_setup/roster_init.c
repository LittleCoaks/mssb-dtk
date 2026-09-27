#include "game/match_setup/roster_init.h"
#include "header_rep_data.h"

#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 aILevel[4];
extern const u8 throwSpeedArray[];
extern int LERPToNewRange_Float(int value, int inMin, int inMax, int outMin, int outMax);
extern f32 runnerVelocityLookup[];
extern f32 lbl_3_data_4BC4[];
extern s16 lbl_3_data_4C54[];
extern u8 lbl_3_data_775C;
extern const f32 lbl_3_rodata_11D8;
extern const f32 lbl_3_rodata_11DC;
extern const f32 lbl_3_rodata_11E0;
extern s16 lbl_3_data_460C[6];
extern s8 lineUpInfoStruct[2][9][4];
extern f32 lbl_3_data_5FC4[12];
extern f32 ModifiedSpeedArray[2][22];
extern const s16 FielderHitboxConsts[55][8];
extern s16 barrelCollisionHitboxes[54];
extern const f32 _0_01_HitboxScaleMultiplier;
extern const f32 lbl_3_rodata_11FC;

// .text:0x0006D6D4 size:0x290 mapped:0x806AC768
void setRunnerSpeedConstants(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int lower = runner->speed / 10 * 10;
    int upper = lower + 10;

    runner->maximumBaseVelocity = LinearInterpolateToNewRange(
        runner->speed, lower, upper, runnerVelocityLookup[lower / 10], runnerVelocityLookup[upper / 10]);
    runner->baseAcceleration = LinearInterpolateToNewRange(
        runner->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC, lbl_3_data_4BC4[0], lbl_3_data_4BC4[1]);
    runner->baseAccelerationWhileChaingingDirection = LinearInterpolateToNewRange(
        runner->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC, lbl_3_data_4BC4[2], lbl_3_data_4BC4[3]);
    runner->maxMashVeloAdjustment = LinearInterpolateToNewRange(
        runner->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC, lbl_3_data_4BC4[4], lbl_3_data_4BC4[5]);
    runner->percentAddedPerMash =
        lbl_3_rodata_11E0 / LinearInterpolateToNewRange(runner->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC,
                                                         lbl_3_data_4BC4[6], lbl_3_data_4BC4[7]);
    runner->stamina_MashPercentTakenAwayPerFrame =
        lbl_3_rodata_11E0 / LinearInterpolateToNewRange(runner->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC,
                                                         lbl_3_data_4BC4[8], lbl_3_data_4BC4[9]);
    runner->FramesUntilNotSprinting = lbl_3_data_4C54[7];
}

// .text:0x0006D964 size:0x4FC mapped:0x806AC9F8
void initializeInMemRunner(int rosterID, int runnerIdx) {
    CharacterStats* charStats = &inMemRoster[g_GameLogic.teamBatting][rosterID];
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    ChallengeTrackingStruct* starMissions = starMissionCompletionTracker;
    int index;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 ||
            g_Practice.practiceType_2 == 2 || g_Practice.practiceType_2 == 3) {
            charStats = &inMemRoster[g_GameLogic.teamBatting][rosterID];
        }
    } else if (g_d_GameSettings.minigamesEnabled) {
        charStats = &inMemRoster[0][rosterID];
    }

    runner->rosterID = rosterID;
    runner->charID = charStats->stats.CharID;
    runner->speed = charStats->stats.Speed;
    runner->weight = charStats->stats.Weight;
    runner->delayBeforeStartingToRun = lbl_3_data_775C;
    runner->aIStrength0Special3Weak =
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];
    runner->characterClass = charStats->stats.CharacterClass;

    if (runner->speed > 200) {
        runner->speed = 200;
    }

    if (!g_d_GameSettings.exhibitionMatchInd) {
        runner->unused_starMissionCharID = -1;
        for (index = 0; index < 54; index++) {
            if ((runner->charID == index) && (starMissions[index].variantClassification <= 3)) {
                runner->unused_starMissionCharID = index;
                break;
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled) {
        s8 idx = g_Minigame.minigameControlStruct[0].characterIndex[rosterID];
        if (g_Minigame.minigameControlStruct[0].battingHandedness[idx] != 0) {
            runner->aIStrength0Special3Weak = aILevel[g_Minigame.minigameControlStruct[0].aIStrength[idx]];
        }
    }

    setRunnerSpeedConstants(runnerIdx);
}

// .text:0x0006DE60 size:0x374 mapped:0x806ACEF4
void setInMemBatterConstants(int rosterID) {
    int battingOrderCounter;
    int index;
    int batterID;

    CharacterStats* char_stats = &inMemRoster[g_GameLogic.teamBatting][rosterID];
    ChallengeTrackingStruct* starMissions = starMissionCompletionTracker;
    g_Batter.easyBatting = 0;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2 ||
            g_Practice.practiceType_2 == 3) {
            char_stats = inMemRoster[g_GameLogic.teamBatting];
        }
    } else if (g_d_GameSettings.minigamesEnabled) {
        rosterID = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID];
        char_stats = &inMemRoster[0][rosterID];
    } else {
        g_Batter.easyBatting =
            inningSetting.controlOptions[g_d_GameSettings.PlayerPorts[g_GameLogic.teamBatting] % 4].easyBatting;
    }

    g_Batter.rosterID = rosterID;
    g_Batter.charID = char_stats->stats.CharID;
    g_Batter.contactSize_raw[BAT_CONTACT_TYPE_SLAP] = char_stats->stats.SlapContactSize;
    g_Batter.contactSize_raw[BAT_CONTACT_TYPE_CHARGE] = char_stats->stats.ChargeContactSize;
    g_Batter.hitPower_raw[BAT_CONTACT_TYPE_SLAP] = char_stats->stats.SlapHitPower;
    g_Batter.hitPower_raw[BAT_CONTACT_TYPE_CHARGE] = char_stats->stats.ChargeHitPower;
    g_Batter.buntingContactSize = char_stats->stats.BuntingContactSize;
    g_Batter.trajectoryPushPull = char_stats->stats.HitTrajectoryPushPull;
    g_Batter.trajectoryHighLow = char_stats->stats.HitTrajectoryHighLow;
    g_Batter.batterHand = char_stats->stats.BattingStance;
    g_Batter.characterClass = char_stats->stats.CharacterClass;
    g_Batter.trimmedBat = BatterHitbox[g_Batter.charID].TrimmedBat;
    g_Batter.chemLinksOnBase = 0;
    g_Batter.aiLevel = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];

    if (g_d_GameSettings.minigamesEnabled) {
        g_Batter.captainStarHitPitch = 0;
        g_Batter.noncaptainStarSwing = 0;
    } else {
        g_Batter.captainStarHitPitch = (char_stats->stats).CaptainStarHitPitch;
        g_Batter.noncaptainStarSwing = (char_stats->stats).NonCaptainStarSwing;
    }

    if (!g_d_GameSettings.exhibitionMatchInd) {
        g_Batter.charIDForScoutFlagMission = -1;
        for (index = 0; index < 54; index++) {
            if ((g_Batter.charID == index) && (starMissions[index].variantClassification <= 3)) {
                g_Batter.charIDForScoutFlagMission = index;
                break;
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled) {
        s8 bVar1;
        if (g_Minigame.battingHandedness[rosterID] & 1) {
            g_Batter.batterHand = 1;
        } else {
            g_Batter.batterHand = 0;
        }

        bVar1 = g_Minigame.minigameControlStruct[0].characterIndex[rosterID];

        if (g_Minigame.minigameControlStruct[0].battingHandedness[bVar1] != 0) {
            g_Pitcher.aiLevel = aILevel[g_Minigame.minigameControlStruct[0].aIStrength[bVar1]];
        }
    }
}

// .text:0x0006E1D4 size:0x78 mapped:0x806AD268
u8 getThrowSpeedBasedOnArmStrengthStat(u8 armStrength) {
    int lower = armStrength / 10 * 10;
    return LERPToNewRange_Float(armStrength, lower, lower + 10, throwSpeedArray[lower / 10],
                                 throwSpeedArray[(lower + 10) / 10]);
}

static inline u32 getFieldingAbilities(int rosterLoc) {
    int team = g_GameLogic.teamFielding;

    if (g_d_GameSettings.minigamesEnabled) {
        team = 0;
    }
    return inMemRoster[team][rosterLoc].stats.FieldingStats;
}

// .text:0x0006E24C size:0x968 mapped:0x806AD2E0
void setFielderValues(int rosterID, int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    CharacterStats* charStats = &inMemRoster[g_GameLogic.teamFielding][rosterID];
    ChallengeTrackingStruct* starMissions = starMissionCompletionTracker;
    s16 charID;
    int index;
    int lower;
    int upper;
    f32 width;
    f32 offset;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2 ||
            g_Practice.practiceType_2 == 3) {
            charStats = &inMemRoster[g_GameLogic.teamFielding][fielderIndex];
        }
    } else if (g_d_GameSettings.minigamesEnabled) {
        charStats = &inMemRoster[0][g_Minigame.minigameControlStruct[0].characterIndex[rosterID]];
    }

    fielder->rosterLocation = rosterID;
    fielder->CharID = charID = charStats->stats.CharID;
    fielder->throwingHandedness = charStats->stats.FieldingArm;
    fielder->Weight = charStats->stats.Weight;
    fielder->AILevel3Weak0Powerful =
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam];

    if ((getFieldingAbilities(fielder->rosterLocation) >> 7) & 1) {
        fielder->ModifiedWeightForMag = 5;
    } else {
        fielder->ModifiedWeightForMag = fielder->Weight;
    }

    if (!g_d_GameSettings.exhibitionMatchInd) {
        fielder->unused_missionRelated = -1;
        for (index = 0; index < 54; index++) {
            if ((fielder->CharID == index) && (starMissions[index].variantClassification <= 3)) {
                fielder->unused_missionRelated = index;
                break;
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled) {
        s8 idx = g_Minigame.minigameControlStruct[0].characterIndex[rosterID];
        if (g_Minigame.minigameControlStruct[0].battingHandedness[idx] != 0) {
            fielder->AILevel3Weak0Powerful = aILevel[g_Minigame.minigameControlStruct[0].aIStrength[idx]];
        }
    }

    if (g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamFielding] == fielder->rosterLocation) {
        fielder->rosterLocSkippingCap = 0;
    } else {
        fielder->rosterLocSkippingCap = ++g_GameLogic.rosterLoc_skippingCap;
    }

    if (g_d_GameSettings.minigamesEnabled) {
        if (g_Minigame.battingHandedness[rosterID] <= 1) {
            fielder->throwingHandedness = 0;
        } else {
            fielder->throwingHandedness = 1;
        }
    }

    fielder->speed = charStats->stats.Speed;
    if (fielder->speed > 200) {
        fielder->speed = 200;
    }

    lower = fielder->speed / 10 * 10;
    upper = lower + 10;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        fielder->joggingSpeed = LinearInterpolateToNewRange(fielder->speed, lower, upper,
                                                            ModifiedSpeedArray[1][lower / 10],
                                                            ModifiedSpeedArray[1][upper / 10]);
    } else {
        fielder->joggingSpeed = LinearInterpolateToNewRange(fielder->speed, lower, upper,
                                                            ModifiedSpeedArray[0][lower / 10],
                                                            ModifiedSpeedArray[0][upper / 10]);
    }
    fielder->runningAccelerationFactor = fielder->joggingSpeed / fielder->maxAccLength_ConstF;

    fielder->throwingArm = charStats->stats.ThrowingArm;
    fielder->modifiedThrowingArm = getThrowSpeedBasedOnArmStrengthStat(fielder->throwingArm);
    if (fielder->modifiedThrowingArm > 200) {
        fielder->modifiedThrowingArm = 200;
    }

    fielder->characterClass = charStats->stats.CharacterClass;
    fielder->wallActionAbility = 0;
    if (getFieldingAbilities(fielder->rosterLocation) & FIELDING_ABILITIES_WALL_SPLAT) {
        fielder->wallActionAbility = 1;
    } else if ((getFieldingAbilities(fielder->rosterLocation) >> 1) & 1) {
        fielder->wallActionAbility = 2;
    } else if (getFieldingAbilities(fielder->rosterLocation) & FIELDING_ABILITIES_CLAMBER) {
        fielder->wallActionAbility = 3;
    }

    fielder->hasSuperJump = 0;
    if (getFieldingAbilities(fielder->rosterLocation) & FIELDING_ABILITIES_SUPER_JUMP) {
        fielder->hasSuperJump = 1;
    }

    fielder->hitbox[0] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[charID][0] * charSizeMultipliers[charID][0];
    fielder->hitbox[1] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[charID][1] * charSizeMultipliers[charID][0];
    fielder->hitbox[2] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[charID][2] * charSizeMultipliers[charID][0];
    fielder->hitbox[3] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[charID][3] * charSizeMultipliers[charID][0];
    fielder->hitbox[6] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[charID][5] * charSizeMultipliers[charID][0];
    fielder->hitbox[7] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[charID][6] * charSizeMultipliers[charID][0];
    fielder->hitbox[8] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[charID][7] * charSizeMultipliers[charID][0];
    width = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[charID][2] * charSizeMultipliers[charID][0];
    offset = width / lbl_3_rodata_11FC;
    fielder->hitbox[4] = width + offset;
    fielder->hitbox[5] = width - offset;

    if (fielder->hitbox[0] < _0_01_HitboxScaleMultiplier * FielderHitboxConsts[54][0]) {
        fielder->hitbox[0] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[54][0];
    }
    if (fielder->hitbox[3] < _0_01_HitboxScaleMultiplier * FielderHitboxConsts[54][1]) {
        fielder->hitbox[3] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[54][1];
    }
    if (fielder->hitbox[6] < _0_01_HitboxScaleMultiplier * FielderHitboxConsts[54][3]) {
        fielder->hitbox[6] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[54][3];
    }
    if (fielder->hitbox[7] < _0_01_HitboxScaleMultiplier * FielderHitboxConsts[54][4]) {
        fielder->hitbox[7] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[54][4];
    }
    if (fielder->hitbox[8] < _0_01_HitboxScaleMultiplier * FielderHitboxConsts[54][5]) {
        fielder->hitbox[8] = _0_01_HitboxScaleMultiplier * FielderHitboxConsts[54][5];
    }

    fielder->hitbox_barrelCollisions =
        _0_01_HitboxScaleMultiplier * barrelCollisionHitboxes[charID] * charSizeMultipliers[charID][0];
}

// .text:0x0006EBB4 size:0x368 mapped:0x806ADC48
void setPitcherStatsToInMemPitcher(int rosterIdx) {
    CharacterStats* char_stats = &inMemRoster[g_GameLogic.teamFielding][rosterIdx];
    ChallengeTrackingStruct* starMissions = starMissionCompletionTracker;
    int index;
    int idx = rosterIdx;

    if (rosterIdx < 0) {
        g_Pitcher.rosterID = 0;
        g_Pitcher.charID = 0;
        g_Pitcher.handedness = 0;
        g_Pitcher.curveBallSpeed = lbl_3_data_460C[0];
        g_Pitcher.fastBallSpeed = lbl_3_data_460C[1];
        g_Pitcher.cursedBallStat = lbl_3_data_460C[2];
        g_Pitcher.curveControlStat = lbl_3_data_460C[3];
        g_Pitcher.curveStat = lbl_3_data_460C[4];
        g_Pitcher.captainStarPitch = lbl_3_data_460C[5];
        return;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2 ||
            g_Practice.practiceType_2 == 3) {
            char_stats = &inMemRoster[g_GameLogic.teamFielding][(s8)g_Minigame.minigamePlayerSelectedOrder];
            idx = 0;
        }
    } else if (g_d_GameSettings.minigamesEnabled) {
        idx = g_Minigame.minigameControlStruct[0].characterIndex[(s8)g_Minigame.minigamePlayerSelectedOrder];
        char_stats = &inMemRoster[0][idx];
    }

    g_Pitcher.rosterID = idx;
    g_Pitcher.charID = (u8)char_stats->stats.CharID;
    g_Pitcher.handedness = char_stats->stats.FieldingArm;
    g_Pitcher.curveBallSpeed = char_stats->stats.CurveBallSpeed;
    g_Pitcher.fastBallSpeed = char_stats->stats.FastBallSpeed;
    g_Pitcher.cursedBallStat = char_stats->stats.cursedBall;
    g_Pitcher.curveControlStat = char_stats->stats.curveControl;
    g_Pitcher.curveStat = char_stats->stats.Curve;
    g_Pitcher.charClass = char_stats->stats.CharacterClass;
    g_Pitcher.aiLevel = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam];

    if (!g_d_GameSettings.exhibitionMatchInd) {
        g_Pitcher.scoutFlagRelated = -1;
        for (index = 0; index < 54; index++) {
            if ((g_Pitcher.charID == index) && (starMissions[index].variantClassification <= 3)) {
                g_Pitcher.scoutFlagRelated = index;
                break;
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled) {
        s8 idx2;

        g_Pitcher.captainStarPitch = 0;
        g_Pitcher.nonCaptainStarPitch = 0;

        if (g_Minigame.battingHandedness[idx] <= 1) {
            g_Pitcher.handedness = 0;
        } else {
            g_Pitcher.handedness = 1;
        }

        idx2 = g_Minigame.minigameControlStruct[0].characterIndex[idx];

        if (g_Minigame.minigameControlStruct[0].battingHandedness[idx2] != 0) {
            g_Pitcher.aiLevel = aILevel[g_Minigame.minigameControlStruct[0].aIStrength[idx2]];
        }
    } else {
        g_Pitcher.captainStarPitch = char_stats->stats.CaptainStarHitPitch;
        g_Pitcher.nonCaptainStarPitch = char_stats->stats.NonCaptainStarPitch;
    }
}

#define HUMAN_ROSTER_STATS(i) (inMemRoster[g_d_GameSettings.humanTeamNumber][(i)].stats)

// .text:0x0006EF1C size:0x5CC mapped:0x806ADFB0
void initRosterForMatch(void) {
    int team;
    int i;

    for (team = 0; team < 2; team++) {
        int t = team ^ g_GameLogic.homeTeamInd;

        g_GameLogic.battingOrderAndPositionMapping[t][0][1] = 0;
        for (i = 0; i < 9; i++) {
            if (lineUpInfoStruct[team][i][1] == 9) {
                g_GameLogic.battingOrderAndPositionMapping[t][0][0] = lineUpInfoStruct[team][i][0];
            } else {
                int pos = lineUpInfoStruct[team][i][1];

                g_GameLogic.battingOrderAndPositionMapping[t][pos + 1][0] = lineUpInfoStruct[team][i][0];
                g_GameLogic.battingOrderAndPositionMapping[t][pos + 1][1] = lineUpInfoStruct[team][i][2];
                if (lineUpInfoStruct[team][i][2] == 0) {
                    g_GameLogic.battingOrderAndPositionMapping[t][0][0] = lineUpInfoStruct[team][i][0];
                }
            }
        }
    }

    g_GameLogic.Team_CaptainRosterLoc[0] = Static_Stats_Tables.capLocationInOrder[0];
    g_GameLogic.Team_CaptainRosterLoc[1] = Static_Stats_Tables.capLocationInOrder[1];

    if (!g_d_GameSettings.exhibitionMatchInd) {
        for (i = 0; i < 9; i++) {
            if (g_d_GameSettings.challengeCaptainStarBought[0] != 0 || g_d_GameSettings._4F != 0) {
                HUMAN_ROSTER_STATS(i).SlapContactSize *= lbl_3_data_5FC4[0];
                HUMAN_ROSTER_STATS(i).ChargeContactSize *= lbl_3_data_5FC4[0];
            }
            if (g_d_GameSettings.challengeCaptainStarBought[1] != 0 || g_d_GameSettings._4F != 0) {
                HUMAN_ROSTER_STATS(i).SlapHitPower *= lbl_3_data_5FC4[2];
                HUMAN_ROSTER_STATS(i).ChargeHitPower *= lbl_3_data_5FC4[2];
            }
            if (g_d_GameSettings.challengeCaptainStarBought[2] != 0 ||
                g_d_GameSettings.challengeCaptainStarBought[2] != 0) {
                HUMAN_ROSTER_STATS(i).CurveBallSpeed += (u8)lbl_3_data_5FC4[4];
                HUMAN_ROSTER_STATS(i).FastBallSpeed += (u8)lbl_3_data_5FC4[4];
                HUMAN_ROSTER_STATS(i).Curve *= lbl_3_data_5FC4[5];
            }
            if (g_d_GameSettings.challengeCaptainStarBought[3] != 0 || g_d_GameSettings._4F != 0) {
                HUMAN_ROSTER_STATS(i).ThrowingArm *= lbl_3_data_5FC4[7];
            }
            if (g_d_GameSettings.challengeCaptainStarBought[4] != 0 || g_d_GameSettings._4F != 0) {
                HUMAN_ROSTER_STATS(i).Speed *= lbl_3_data_5FC4[8];
            }

            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_MARIO) {
                if (g_d_GameSettings.challengeCaptainStarBought[6] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_MARIO;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_LUIGI) {
                if (g_d_GameSettings.challengeCaptainStarBought[7] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_LUIGI;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_DK) {
                if (g_d_GameSettings.challengeCaptainStarBought[14] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_DK;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_DIDDY) {
                if (g_d_GameSettings.challengeCaptainStarBought[15] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_DIDDY;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_PEACH) {
                if (g_d_GameSettings.challengeCaptainStarBought[8] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_PEACH;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_DAISY) {
                if (g_d_GameSettings.challengeCaptainStarBought[9] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_DAISY;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_YOSHI) {
                if (g_d_GameSettings.challengeCaptainStarBought[12] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_YOSHI;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_BIRDO) {
                if (g_d_GameSettings.challengeCaptainStarBought[13] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_BIRDO;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_WARIO) {
                if (g_d_GameSettings.challengeCaptainStarBought[10] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_WARIO;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_WALUIGI) {
                if (g_d_GameSettings.challengeCaptainStarBought[11] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_WALUIGI;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_BOWSER) {
                if (g_d_GameSettings.challengeCaptainStarBought[16] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_BOWSER;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
            if (HUMAN_ROSTER_STATS(i).CharID == CHAR_ID_BOWSERJR) {
                if (g_d_GameSettings.challengeCaptainStarBought[17] != 0) {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_BOWSERJR;
                } else {
                    HUMAN_ROSTER_STATS(i).CaptainStarHitPitch = CAPTAIN_STAR_TYPE_NONE;
                }
            }
        }
    }
}
