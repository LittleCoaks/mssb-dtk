#include "game/minigame/barrel_batter.h"
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "musyx/musyx.h"
#include "game/match_setup/roster_init.h"
#include "game/ball/ball_physics.h"
#include "game/pitching/pitcher.h"
#include "game/batting/batter.h"
#include "game/baserunning/runner.h"
#include "game/fielding/fielder.h"
#include "game/animation/scene_effects.h"
#include "Dolphin/stl.h"
#include "game/math/game_math.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800204cc.h"

extern void SetGameStatus(GAME_STATUS status);
extern u8 lbl_800EFBA4[0x10];
extern s16 lbl_3_data_18C48[10];
extern u8 lbl_8037169C[0x1C];
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern BOOL checkForButtonPressToSkip(int a, int b);
extern u8 highLevelSimulationFlag[3];
extern u8 us80893314[8];
extern u8 cost_15_bB_pitchesPerRound_solo[12];
extern u8 animRelated[0x124];
extern void fn_3_10AD48(void);
extern void fn_3_10F550(int a, int b);

typedef struct {
    u8 _00[5];
    u8 _05;
    u8 _06;
    u8 _07[5];
} UnkSimulationStruct_31AC0;
extern UnkSimulationStruct_31AC0 g_UnkSimulation_31AC0;

extern float lbl_3_data_21770[6];
extern void fn_8004C108(VecXYZ *pos, BOOL flag);
extern void callSfx(int soundId);

typedef struct {
    s16 baseBlowUpDelay;
    s16 blowUpDelayIncrement;
    s16 bombBarrelThreshold;
} BB_dropConstsStruct;
extern BB_dropConstsStruct lbl_3_data_21788;
extern VecXYZ barrelBaseCoordinates[15];
extern s16 lbl_3_data_217A4[12];
extern s16 lbl_3_common_bss_37400[0x27];
extern void starMissionsMinigamesSpecialAction(int missionType, int points, int barrelsHit);

// .text:0x0012E8FC size:0x214 mapped:0x8076D990
void bB_chooseBombBarrel_dropNewBarrels(void) {
    BOOL bombBarrelChosen = FALSE;
    int barrelsUntilBomb;
    int i;

    if (g_Minigame.barrelBatterChargeMeter >= lbl_3_data_21788.bombBarrelThreshold) {
        int emptyCount = 0;
        for (i = 0; i < 15; i++) {
            if (g_Minigame.barrels[i].barrelState == BB_BARREL_STATE_EMPTY) {
                emptyCount++;
            }
        }
        barrelsUntilBomb = random_fn_3_9EE24(emptyCount);
        g_Minigame.barrelBatterChargeMeter = 0;
        bombBarrelChosen = TRUE;
    }

    for (i = 0; i < 15; i++) {
        if (g_Minigame.barrels[i].barrelState == BB_BARREL_STATE_EMPTY) {
            int rollY;
            g_Minigame.barrels[i].barrelState = BB_BARREL_STATE_DROPPING;
            g_Minigame.barrels[i].animationCounter = 0;
            g_Minigame.barrels[i].currentPos.x = barrelBaseCoordinates[i].x;
            g_Minigame.barrels[i].currentPos.y = barrelBaseCoordinates[i].y;
            g_Minigame.barrels[i].currentPos.z = barrelBaseCoordinates[i].z;
            g_Minigame.barrels[i].currentPos.y += lbl_3_data_21770[0];
            rollY = random_fn_3_9EE24(0x65);
            g_Minigame.barrels[i].currentPos.y += (i % 3) * 10 - (rollY * 5) / 100.0;
            g_Minigame.barrels[i].barrelColour = random_fn_3_9EE24(3);
            if (bombBarrelChosen) {
                if (barrelsUntilBomb == 0) {
                    barrelsUntilBomb = -1;
                    g_Minigame.barrels[i].barrelColour = BB_BARREL_COLOUR_BROWN;
                    g_Minigame.bB_bombBarrelID = (s16)i;
                } else if (barrelsUntilBomb > 0) {
                    barrelsUntilBomb--;
                }
            }
        }
    }
}

// .text:0x0012EB10 size:0x270 mapped:0x8076DBA4
void fn_3_12EB10(void) {
    int row;
    for (row = 0; row < 5; row++) {
        int pos = 0;
        while (pos < 2) {
            if (g_Minigame.barrels[row * 3 + pos].barrelState == BB_BARREL_STATE_BLOWN_UP) {
                int k;
                for (k = pos + 1; k < 3; k++) {
                    g_Minigame.barrels[row * 3 + k - 1].barrelState = g_Minigame.barrels[row * 3 + k].barrelState;
                    g_Minigame.barrels[row * 3 + k - 1].barrelColour = g_Minigame.barrels[row * 3 + k].barrelColour;
                    g_Minigame.barrels[row * 3 + k - 1].currentPos.x = g_Minigame.barrels[row * 3 + k].currentPos.x;
                    g_Minigame.barrels[row * 3 + k - 1].currentPos.y = g_Minigame.barrels[row * 3 + k].currentPos.y;
                    g_Minigame.barrels[row * 3 + k - 1].currentPos.z = g_Minigame.barrels[row * 3 + k].currentPos.z;
                    g_Minigame.barrels[row * 3 + k].barrelState = BB_BARREL_STATE_EMPTY;
                }
            } else {
                pos++;
            }
        }
    }

    if (g_Minigame.barrels[2].barrelState == BB_BARREL_STATE_BLOWN_UP) {
        g_Minigame.barrels[2].barrelState = BB_BARREL_STATE_EMPTY;
    }
    if (g_Minigame.barrels[5].barrelState == BB_BARREL_STATE_BLOWN_UP) {
        g_Minigame.barrels[5].barrelState = BB_BARREL_STATE_EMPTY;
    }
    if (g_Minigame.barrels[8].barrelState == BB_BARREL_STATE_BLOWN_UP) {
        g_Minigame.barrels[8].barrelState = BB_BARREL_STATE_EMPTY;
    }
    if (g_Minigame.barrels[11].barrelState == BB_BARREL_STATE_BLOWN_UP) {
        g_Minigame.barrels[11].barrelState = BB_BARREL_STATE_EMPTY;
    }
    if (g_Minigame.barrels[14].barrelState == BB_BARREL_STATE_BLOWN_UP) {
        g_Minigame.barrels[14].barrelState = BB_BARREL_STATE_EMPTY;
    }
}

// .text:0x0012ED80 size:0xE8 mapped:0x8076DE14
BOOL fn_3_12ED80(void) {
    int i;
    BB_barrelStruct *barrel = g_Minigame.barrels;
    for (i = 0; i < 5; i++, barrel += 3) {
        if (barrel[1].replacingBarrelInd) {
            return 0;
        }
        if (barrel[2].replacingBarrelInd) {
            return 0;
        }
    }
    return 1;
}

// .text:0x0012EE68 size:0x13C mapped:0x8076DEFC
void fn_3_12EE68(int barrelIndex) {
    int posInRow = barrelIndex % 3;
    BB_barrelStruct *barrel = &g_Minigame.barrels[barrelIndex];
    BB_barrelStruct *nextBarrel;

    if (posInRow == 2) {
        return;
    }

    nextBarrel = &g_Minigame.barrels[barrelIndex + 1];

    if (nextBarrel->barrelState == BB_BARREL_STATE_BLOWN_UP) {
        return;
    }
    if (nextBarrel->barrelState == BB_BARREL_STATE_READY_TO_BLOW_UP) {
        if (nextBarrel->desiredPos.y - barrel->desiredPos.y > lbl_3_data_21770[3] + 0.3) {
            return;
        }
    }

    nextBarrel->replacingBarrelInd = 1;
    nextBarrel->velo_bounceUpOnBlowUp = lbl_3_data_21770[4];

    if ((barrelIndex + 1) % 3 == 1) {
        nextBarrel->_28 = barrelBaseCoordinates[barrelIndex].y;
    } else {
        int flag = (g_Minigame.barrels[barrelIndex - 1].barrelState == BB_BARREL_STATE_NEUTRAL) |
                   (g_Minigame.barrels[barrelIndex].barrelState == BB_BARREL_STATE_NEUTRAL);
        nextBarrel->_28 = barrelBaseCoordinates[flag].y;
    }
}

// .text:0x0012EFA4 size:0x2E8 mapped:0x8076E038
void bB_likelyReplaceBlownUpBarrels(int barrelIndex) {
    BB_barrelStruct *barrel = &g_Minigame.barrels[barrelIndex];
    int posInRow;

    barrel->currentPos.y += barrel->velo_bounceUpOnBlowUp;
    posInRow = barrelIndex % 3;
    if (barrel->velo_bounceUpOnBlowUp > 0.0f && posInRow == 1) {
        BB_barrelStruct *next = &g_Minigame.barrels[barrelIndex + 1];
        if (next->barrelState != BB_BARREL_STATE_BLOWN_UP &&
            next->replacingBarrelInd == 0 &&
            posInRow != 2 &&
            (next->barrelState != BB_BARREL_STATE_READY_TO_BLOW_UP ||
             next->currentPos.y - barrel->currentPos.y <= 0.3 + lbl_3_data_21770[3])) {
            next->replacingBarrelInd = 1;
            next->velo_bounceUpOnBlowUp = lbl_3_data_21770[4];
            if ((barrelIndex + 1) % 3 == 1) {
                next->_28 = barrelBaseCoordinates[barrelIndex].y;
            } else {
                int flag = (g_Minigame.barrels[barrelIndex - 1].barrelState == BB_BARREL_STATE_NEUTRAL) |
                           (g_Minigame.barrels[barrelIndex].barrelState == BB_BARREL_STATE_NEUTRAL);
                next->_28 = barrelBaseCoordinates[flag].y;
            }
        }
        if (next->currentPos.y - barrel->currentPos.y < lbl_3_data_21770[3]) {
            barrel->velo_bounceUpOnBlowUp -= lbl_3_data_21770[5];
        }
    }

    barrel->velo_bounceUpOnBlowUp -= lbl_3_data_21770[5];
    if (barrel->velo_bounceUpOnBlowUp > 0.0f && posInRow == 2 &&
        barrel->currentPos.y - g_Minigame.barrels[barrelIndex - 1].currentPos.y < lbl_3_data_21770[3]) {
        barrel->velo_bounceUpOnBlowUp += lbl_3_data_21770[5];
    }

    if (barrel->currentPos.y < barrel->_28) {
        barrel->currentPos.y = barrel->_28;
        barrel->velo_bounceUpOnBlowUp = 0.0f;
        barrel->replacingBarrelInd = 0;
        if (barrel->barrelState != BB_BARREL_STATE_BLOWN_UP) {
            VecXYZ pos;
            pos.x = barrel->currentPos.x;
            pos.y = -barrel->currentPos.y;
            pos.z = barrel->currentPos.z - 1.0f;
            if (0.0f == barrel->_28) {
                fn_8004C108(&pos, TRUE);
                callSfx(0x2e4);
            } else {
                fn_8004C108(&pos, FALSE);
                callSfx(0x2e5);
            }
        }
    }
}

// .text:0x0012F28C size:0x198 mapped:0x8076E320
void fn_3_12F28C(int barrelIndex) {
    if (g_Minigame.barrels[barrelIndex].delayUntilBlownUp <= g_Minigame.barrels[barrelIndex].animationCounter) {
        g_Minigame.barrels[barrelIndex].barrelState = BB_BARREL_STATE_BLOWN_UP;
        g_Minigame.barrels[barrelIndex].animationCounter = 0;
        if (barrelIndex % 3 != 2) {
            fn_3_12EE68(barrelIndex);
        }
        setCharacterAnimations(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID], 0);
    }
}

// .text:0x0012F424 size:0x200 mapped:0x8076E4B8
void bB_connectingBarrels(int barrelNum, s16 blowUpDelay, int bombBarrelHitInd) {
    int barrelColour = g_Minigame.barrels[barrelNum].barrelColour;

    if (barrelNum % 3 != 2) {
        int barrelAbove = barrelNum + 1;
        if (g_Minigame.barrels[barrelAbove].barrelState == BB_BARREL_STATE_NEUTRAL) {
            if (barrelAbove != g_Minigame.bB_bombBarrelID) {
                if (g_Minigame.barrels[barrelAbove].barrelColour == barrelColour || bombBarrelHitInd != 0) {
                    g_Minigame.barrels[barrelAbove].barrelState = BB_BARREL_STATE_READY_TO_BLOW_UP;
                    g_Minigame.barrels[barrelAbove].animationCounter = 0;
                    g_Minigame.barrels[barrelAbove].delayUntilBlownUp = blowUpDelay;
                }
            }
        }
    }

    if (barrelNum != (barrelNum / 3) * 3) {
        int barrelBelow = barrelNum - 1;
        if (g_Minigame.barrels[barrelBelow].barrelState == BB_BARREL_STATE_NEUTRAL) {
            if (barrelBelow != g_Minigame.bB_bombBarrelID) {
                if (g_Minigame.barrels[barrelBelow].barrelColour == barrelColour || bombBarrelHitInd != 0) {
                    g_Minigame.barrels[barrelBelow].barrelState = BB_BARREL_STATE_READY_TO_BLOW_UP;
                    g_Minigame.barrels[barrelBelow].animationCounter = 0;
                    g_Minigame.barrels[barrelBelow].delayUntilBlownUp = blowUpDelay;
                }
            }
        }
    }

    if (barrelNum / 3 > 0) {
        int barrelToLeft = barrelNum - 3;
        if (g_Minigame.barrels[barrelToLeft].barrelState == BB_BARREL_STATE_NEUTRAL &&
            barrelToLeft != g_Minigame.bB_bombBarrelID &&
            (g_Minigame.barrels[barrelToLeft].barrelColour == barrelColour || bombBarrelHitInd != 0)) {
            g_Minigame.barrels[barrelToLeft].barrelState = BB_BARREL_STATE_READY_TO_BLOW_UP;
            g_Minigame.barrels[barrelToLeft].animationCounter = 0;
            g_Minigame.barrels[barrelToLeft].delayUntilBlownUp = blowUpDelay;
        }
    }

    if (barrelNum / 3 > 3) {
        return;
    }

    if (g_Minigame.barrels[barrelNum + 3].barrelState != BB_BARREL_STATE_NEUTRAL) {
        return;
    }
    if (barrelNum + 3 == g_Minigame.bB_bombBarrelID) {
        return;
    }
    if (g_Minigame.barrels[barrelNum + 3].barrelColour != barrelColour && bombBarrelHitInd == 0) {
        return;
    }
    g_Minigame.barrels[barrelNum + 3].barrelState = BB_BARREL_STATE_READY_TO_BLOW_UP;
    g_Minigame.barrels[barrelNum + 3].animationCounter = 0;
    g_Minigame.barrels[barrelNum + 3].delayUntilBlownUp = blowUpDelay;
}

// .text:0x0012F624 size:0x3B0 mapped:0x8076E6B8
void bB_checkIfBarrelHitAndCalculateScore(void) {
    if (g_Ball.framesSinceHit > 0) {
        if (g_Minigame.barrelBatter_scoreCalculatedInd == 0) {
            if (barrelBaseCoordinates[0].z - lbl_3_data_21770[2] <= g_Ball.AtBat_Contact_BallPos.z) {
                if (g_Batter.contactType != HIT_CONTACT_TYPE_RIGHT_SOUR && g_Batter.contactType < HIT_CONTACT_TYPE_LEFT_SOUR) {
                    int barrelRow = 0;

                    if (barrelBaseCoordinates[0].y + lbl_3_data_21770[3] <= g_Ball.AtBat_Contact_BallPos.y) {
                        barrelRow = 1;
                        if (barrelBaseCoordinates[1].y + lbl_3_data_21770[3] <= g_Ball.AtBat_Contact_BallPos.y) {
                            barrelRow = 2;
                            if (barrelBaseCoordinates[2].y + lbl_3_data_21770[3] <= g_Ball.AtBat_Contact_BallPos.y) {
                                barrelRow = 3;
                            }
                        }
                    }

                    if (barrelRow < 3 && barrelBaseCoordinates[0].x - lbl_3_data_21770[2] <= g_Ball.AtBat_Contact_BallPos.x) {
                        int barrelColumn = 0;

                        if (barrelBaseCoordinates[0].x + lbl_3_data_21770[2] <= g_Ball.AtBat_Contact_BallPos.x) {
                            barrelColumn = 3;
                            if (barrelBaseCoordinates[3].x + lbl_3_data_21770[2] <= g_Ball.AtBat_Contact_BallPos.x) {
                                barrelColumn = 6;
                                if (barrelBaseCoordinates[6].x + lbl_3_data_21770[2] <= g_Ball.AtBat_Contact_BallPos.x) {
                                    barrelColumn = 9;
                                    if (barrelBaseCoordinates[9].x + lbl_3_data_21770[2] <= g_Ball.AtBat_Contact_BallPos.x) {
                                        barrelColumn = 12;
                                        if (barrelBaseCoordinates[12].x + lbl_3_data_21770[2] <= g_Ball.AtBat_Contact_BallPos.x) {
                                            barrelColumn = 15;
                                        }
                                    }
                                }
                            }
                        }

                        if (barrelColumn < 15) {
                            int barrelHitFlags[15];
                            int barrelID;
                            int delayToBlowUp;
                            int loopAgainInd;
                            int counter;
                            int basePoints, barrelsHit;
                            BOOL challengeInd;

                            for (counter = 0; counter < 15; counter++) {
                                barrelHitFlags[counter] = 0;
                            }

                            g_Minigame.barrelBatter_hitBarrelID = (u8)(barrelColumn + barrelRow);
                            barrelID = (s8)g_Minigame.barrelBatter_hitBarrelID;

                            g_Minigame.barrels[barrelID].barrelState = BB_BARREL_STATE_READY_TO_BLOW_UP;
                            delayToBlowUp = lbl_3_data_21788.baseBlowUpDelay + lbl_3_data_21788.blowUpDelayIncrement;
                            g_Minigame.barrels[barrelID].animationCounter = 0;
                            g_Minigame.barrels[barrelID].delayUntilBlownUp = lbl_3_data_21788.baseBlowUpDelay;

                            if (g_Minigame.bB_bombBarrelID == barrelID && g_Minigame.barrels[barrelID].barrelColour == BB_BARREL_COLOUR_BROWN) {
                                g_Minigame.bB_bombBarrelHitInd = 1;
                            }

                            do {
                                loopAgainInd = 0;
                                for (counter = 0; counter < 15; counter++) {
                                    if (g_Minigame.barrels[counter].barrelState == BB_BARREL_STATE_READY_TO_BLOW_UP &&
                                        g_Minigame.barrels[counter].delayUntilBlownUp != delayToBlowUp &&
                                        barrelHitFlags[counter] == 0) {
                                        if (g_Minigame.bB_bombBarrelHitInd == 0) {
                                            bB_connectingBarrels(counter, (s16)delayToBlowUp, 0);
                                        } else {
                                            bB_connectingBarrels(counter, (s16)delayToBlowUp, 1);
                                        }
                                        barrelHitFlags[counter] = 1;
                                        loopAgainInd = 1;
                                        g_Minigame.barrelBatter_barrelsHit++;
                                    }
                                }
                                if (!loopAgainInd) {
                                    break;
                                }
                                delayToBlowUp += lbl_3_data_21788.blowUpDelayIncrement;
                            } while (TRUE);

                            if (g_Minigame.bB_bombBarrelHitInd == 0 && g_Minigame.barrelBatter_barrelsHit > 1) {
                                g_Minigame.barrelBatterChargeMeter = g_Minigame.barrelBatter_barrelsHit + g_Minigame.barrelBatterChargeMeter - 1;
                            }

                            barrelsHit = g_Minigame.barrelBatter_barrelsHit;
                            if ((u32)barrelsHit < 2) {
                                basePoints = lbl_3_data_217A4[5];
                            } else {
                                basePoints = (barrelsHit - 1) * lbl_3_data_217A4[5];
                            }

                            challengeInd = !g_d_GameSettings.exhibitionMatchInd;
                            *(s16 *)((u8 *)&g_Minigame + 0x1DF4) = (s16)(basePoints * barrelsHit);
                            g_Minigame.miniGameCurrentPoints[(s8)g_Minigame.rosterID] += (s16)(basePoints * barrelsHit);

                            if (challengeInd && (s8)g_Minigame.rosterID == lbl_3_common_bss_37400[0x20]) {
                                starMissionsMinigamesSpecialAction(2, basePoints * barrelsHit, g_Minigame.barrelBatter_barrelsHit);
                            }
                        }
                    }

                    g_Minigame.barrelBatter_scoreCalculatedInd = 1;
                }
            }
        }
    }
}

// .text:0x0012F9D4 size:0xF0 mapped:0x8076EA68
void fn_3_12F9D4(int barrelIndex) {
    BB_barrelStruct *barrel = &g_Minigame.barrels[barrelIndex];

    barrel->currentPos.y += lbl_3_data_21770[1];
    if (barrel->currentPos.y < barrel->desiredPos.y) {
        barrel->currentPos.y = barrel->desiredPos.y;
        if (barrel->posAtStartOfTurn.y != barrel->desiredPos.y) {
            VecXYZ pos;
            pos.x = barrel->currentPos.x;
            pos.y = -barrel->currentPos.y;
            pos.z = barrel->currentPos.z - 1.0f;
            if (barrel->currentPos.y <= 0.0f) {
                fn_8004C108(&pos, TRUE);
                callSfx(0x2e4);
            } else {
                fn_8004C108(&pos, FALSE);
                callSfx(0x2e5);
            }
        }
        barrel->barrelState = BB_BARREL_STATE_NEUTRAL;
    }
}

// .text:0x0012FAC4 size:0x2A8 mapped:0x8076EB58
void fn_3_12FAC4(void) {
    int i;

    bB_checkIfBarrelHitAndCalculateScore();
    for (i = 0; i < 15; i++) {
        BB_barrelStruct *barrel = &g_Minigame.barrels[i];

        if (barrel->animationCounter < 0x7ffe) {
            barrel->animationCounter++;
        } else {
            barrel->animationCounter = 0x7fff;
        }

        if (barrel->barrelState == BB_BARREL_STATE_DROPPING) {
            fn_3_12F9D4(i);
        }
        if (barrel->barrelState == BB_BARREL_STATE_READY_TO_BLOW_UP) {
            fn_3_12F28C(i);
        }
        if (barrel->replacingBarrelInd != 0) {
            bB_likelyReplaceBlownUpBarrels(i);
        }
    }
}

// .text:0x0012FD6C size:0x118 mapped:0x8076EE00
void fn_3_12FD6C(void) {
    int i;
    for (i = 0; i < 15; i++) {
        if (g_Minigame.barrels[i].barrelState != BB_BARREL_STATE_EMPTY) {
            g_Minigame.barrels[i].posAtStartOfTurn.x = g_Minigame.barrels[i].currentPos.x;
            g_Minigame.barrels[i].posAtStartOfTurn.y = g_Minigame.barrels[i].currentPos.y;
            g_Minigame.barrels[i].posAtStartOfTurn.z = g_Minigame.barrels[i].currentPos.z;
            g_Minigame.barrels[i].barrelState = BB_BARREL_STATE_DROPPING;
        }
        g_Minigame.barrels[i].animationCounter = 0;
    }
}

// .text:0x0012FE84 size:0x150 mapped:0x8076EF18
void fn_3_12FE84(void) {
    int i;
    for (i = 0; i < 15; i++) {
        int rollY;
        g_Minigame.barrels[i].barrelState = BB_BARREL_STATE_DROPPING;
        g_Minigame.barrels[i].animationCounter = 0;
        g_Minigame.barrels[i].replacingBarrelInd = 0;
        g_Minigame.barrels[i].desiredPos.x = barrelBaseCoordinates[i].x;
        g_Minigame.barrels[i].desiredPos.y = barrelBaseCoordinates[i].y;
        g_Minigame.barrels[i].desiredPos.z = barrelBaseCoordinates[i].z;
        g_Minigame.barrels[i].currentPos.x = barrelBaseCoordinates[i].x;
        g_Minigame.barrels[i].currentPos.y = barrelBaseCoordinates[i].y;
        g_Minigame.barrels[i].currentPos.z = barrelBaseCoordinates[i].z;
        g_Minigame.barrels[i].currentPos.y += lbl_3_data_21770[0];
        rollY = random_fn_3_9EE24(0x65);
        g_Minigame.barrels[i].currentPos.y += (i % 3) * 10 - (rollY * 5) / 100.0;
        g_Minigame.barrels[i].barrelColour = random_fn_3_9EE24(3);
    }
}

// .text:0x0012FFD4 size:0x2B4 mapped:0x8076F068
void fn_3_12FFD4(void) {
    int row;

    g_Minigame.bB_bombBarrelID = -1;
    for (row = 0; row < 5; row++) {
        int pos = 0;
        while (pos < 2) {
            if (g_Minigame.barrels[row * 3 + pos].barrelState == BB_BARREL_STATE_BLOWN_UP) {
                int k;
                for (k = pos + 1; k < 3; k++) {
                    g_Minigame.barrels[row * 3 + k - 1].barrelState = g_Minigame.barrels[row * 3 + k].barrelState;
                    g_Minigame.barrels[row * 3 + k - 1].barrelColour = g_Minigame.barrels[row * 3 + k].barrelColour;
                    g_Minigame.barrels[row * 3 + k - 1].currentPos.x = g_Minigame.barrels[row * 3 + k].currentPos.x;
                    g_Minigame.barrels[row * 3 + k - 1].currentPos.y = g_Minigame.barrels[row * 3 + k].currentPos.y;
                    g_Minigame.barrels[row * 3 + k - 1].currentPos.z = g_Minigame.barrels[row * 3 + k].currentPos.z;
                    g_Minigame.barrels[row * 3 + k].barrelState = BB_BARREL_STATE_EMPTY;
                }
            } else {
                pos++;
            }
        }
    }

    if (g_Minigame.barrels[2].barrelState == BB_BARREL_STATE_BLOWN_UP) {
        g_Minigame.barrels[2].barrelState = BB_BARREL_STATE_EMPTY;
    }
    if (g_Minigame.barrels[5].barrelState == BB_BARREL_STATE_BLOWN_UP) {
        g_Minigame.barrels[5].barrelState = BB_BARREL_STATE_EMPTY;
    }
    if (g_Minigame.barrels[8].barrelState == BB_BARREL_STATE_BLOWN_UP) {
        g_Minigame.barrels[8].barrelState = BB_BARREL_STATE_EMPTY;
    }
    if (g_Minigame.barrels[11].barrelState == BB_BARREL_STATE_BLOWN_UP) {
        g_Minigame.barrels[11].barrelState = BB_BARREL_STATE_EMPTY;
    }
    if (g_Minigame.barrels[14].barrelState == BB_BARREL_STATE_BLOWN_UP) {
        g_Minigame.barrels[14].barrelState = BB_BARREL_STATE_EMPTY;
    }

    bB_chooseBombBarrel_dropNewBarrels();
    if (g_Minigame.pointsTargetReachedInd == 0) {
        SetGameStatus(GAME_STATUS_DEFAULT);
    } else {
        SetGameStatus(GAME_STATUS_TRANSITION);
    }
}

// .text:0x00130288 size:0x548 mapped:0x8076F31C
void barrelBatterLiveBallSubFun(void) {
    return;
}

// .text:0x001307D0 size:0x2B0 mapped:0x8076F864
void fn_3_1307D0(void) {
    return;
}

// .text:0x00130A80 size:0x4C mapped:0x8076FB14
void fn_3_130A80(void) {
    g_Minigame.bB_bombBarrelID = -1;
    g_GameLogic.pre_PostMiniGameInd = TRUE;
    g_GameLogic.minigameLastTurnSuccessInd = TRUE;
    g_GameLogic.hudLoadingRelated = TRUE;
    SetGameStatus(GAME_STATUS_TRANSITION);
}

// .text:0x00130ACC size:0x1A0 mapped:0x8076FB60
void bobombDerbyRelated(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_NO_CONTACT) {
            if (g_Minigame.bB_pitchesRemainingInTurn == 0) {
                g_Minigame.turnOverStatus = 1;
                g_Minigame.pointsTargetReachedInd = 2;
            }
            g_Minigame.bB_bombBarrelHitInd = 0;
            g_Minigame.bB_bombBarrelID = -1;
        }
    } else {
        if (g_Minigame.turnOverStatus == 1) {
            g_Minigame.turnOverStatus = 2;
            g_GameLogic.CountdownUntilFade = lbl_3_data_217A4[0];
        }
        g_GameLogic.CountdownUntilFade--;
        if (g_Minigame.pointsTargetReachedInd != 0) {
            if (g_GameLogic.CountdownUntilFade <= 0) {
                g_Minigame.bB_bombBarrelID = -1;
                g_GameLogic.pre_PostMiniGameInd = 1;
                g_GameLogic.minigameLastTurnSuccessInd = 1;
                g_GameLogic.hudLoadingRelated = 1;
                SetGameStatus(GAME_STATUS_TRANSITION);
            }
        } else if (g_GameLogic.CountdownUntilFade <= 0) {
            SetGameStatus(GAME_STATUS_DEFAULT);
        }
        if (g_Minigame.pointsTargetReachedInd != 0 &&
            (g_Minigame.multiPlayerInd == 0 ||
             (g_Minigame.multiPlayerInd != 0 &&
              g_Minigame.turnNumberWithinRound + 1 >= g_Minigame.miniGameNumberOfParticipants &&
              g_Scores.Inning >= g_Scores.inningLimit)) &&
            g_Minigame._1A37 == 0 && g_GameLogic.CountdownUntilFade == 1) {
            sndFXStartEx(0x1be, lbl_800EFBA4[7], 0x3f, 0);
        }
    }
}

// .text:0x00130C6C size:0x4A8 mapped:0x8076FD00
void bB_AtBat(void) {
    return;
}

// .text:0x00131114 size:0x88 mapped:0x807701A8
void fn_3_131114(void) {
    setInMemBatterConstants(g_Minigame.rosterID);
    setDefaultInMemBall();
    setDefaultInMemPitcher();
    setDefaultInMemBatter();
    setDefaultInMemRunner();
    setDefaultInMemFielder();
    memset(&g_Minigame._1D7C, 0, 0x78);
    pauseAnimations();
    pauseStateOnStadiums();
    g_FieldingLogic.playOverCounter = 0;
    g_UnkSimulation_31AC0._05 = 0;
    g_UnkSimulation_31AC0._06 = 4;
}

// .text:0x0013119C size:0xF0 mapped:0x80770230
void fn_3_13119C(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        changeScene(1, 6);
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[2] ||
            (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[1] &&
             checkForButtonPressToSkip(1, 0x1100))) {
            changeScene(3, 6);
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        break;
    }
}

// .text:0x0013128C size:0x48 mapped:0x80770320
void fn_3_13128C(void) {
    if (g_Scores.Inning >= g_Scores.inningLimit) {
        SetGameStatus(GAME_STATUS_TRANSITION_MINIGAME_POSTGAME);
    } else {
        SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START);
    }
}

// .text:0x001312D4 size:0x26C mapped:0x80770368
void fn_3_1312D4(void) {
    return;
}

// .text:0x00131540 size:0x748 mapped:0x807705D4
void barrelBatterTransitionToMainFunction(void) {
    return;
}

// .text:0x00131C88 size:0x23C mapped:0x80770D1C
void fn_3_131C88(void) {
    fn_3_131114();
    fn_3_12FD6C();

    g_Minigame._18A0 = 0;
    g_Minigame.bB_bombBarrelHitInd = 0;
    g_Minigame.turnOverStatus = 0;
    g_Minigame.barrelBatter_scoreCalculatedInd = 0;
    g_Minigame.barrelBatter_hitBarrelID = (u8)-1;
    g_Minigame.barrelBatter_barrelsHit = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_Ball.framesSinceHit = -1;
    *(s16 *)((u8 *)&g_Batter + 0x66) = 0;
    *((u8 *)&g_Batter + 0x8D) = 0;
    g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_217A4[7];

    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;

    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_AT_BAT);
}

// .text:0x00131EC4 size:0x138 mapped:0x80770F58
void fn_3_131EC4(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        g_Minigame.rosterID = g_Minigame.minigameControlStruct[0].aIStrength[g_Minigame.turnNumberWithinRound + 4];
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_Minigame.miniGameTurnCounter = 0;
        g_Minigame.pointsTargetReachedInd = 0;
        if (g_Minigame.multiPlayerInd == 0) {
            g_Minigame.bB_pitchesRemainingInTurn = cost_15_bB_pitchesPerRound_solo[g_Minigame.soloMinigameDifficulty];
        } else {
            g_Minigame.bB_pitchesRemainingInTurn = cost_15_bB_pitchesPerRound_solo[4];
        }
        resetBallValuesBetweenBatters();
        resetPitcherValuesBetweenBatters(0);
        setPitcherStatsToInMemPitcher(-1);
        setBatterContactConstants();
        setInMemBatterConstants(g_Minigame.rosterID);
        highLevelSimulationFlag[2] = 0;
        g_GameLogic._125++;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (someAnimationIndFunction() != 0) {
            us80893314[1] = 1;
            g_GameLogic._125++;
        }
        break;
    default:
        animRelated[0xB6] = 1;
        SetGameStatus(GAME_STATUS_DEFAULT);
        break;
    }
}

// .text:0x00131FFC size:0x80 mapped:0x80771090
void fn_3_131FFC(void) {
    g_Scores.Inning++;
    g_Minigame.turnNumberWithinRound = 0;

    if (g_Minigame.multiPlayerInd == 0) {
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        return;
    }

    fn_3_10F550(4, 0);
    if (g_Scores.Inning == 1) {
        fn_3_10AD48();
    }
    SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
}

// .text:0x0013207C size:0x40 mapped:0x80771110
void fn_3_13207C(void) {
    sndFXStartEx(0x1bd, lbl_800EFBA4[6], 0x3f, 0);
    SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START);
}

// .text:0x001320BC size:0x310 mapped:0x80771150
void bB_LoadGame(void) {
    return;
}

// .text:0x001323CC size:0x11C mapped:0x80771460
void fn_3_1323CC(void) {
    u32 i;
    VecXYZ pos;

    for (i = 0; i < 15; i++) {
        BB_barrelStruct *barrel = &g_Minigame.barrels[i];
        if (barrel->barrelState != BB_BARREL_STATE_DROPPING) {
            continue;
        }
        barrel->currentPos.y += lbl_3_data_21770[1];
        if (barrel->currentPos.y < barrel->desiredPos.y) {
            barrel->currentPos.y = barrel->desiredPos.y;
            if (barrel->posAtStartOfTurn.y != barrel->desiredPos.y) {
                pos.x = barrel->currentPos.x;
                pos.y = -barrel->currentPos.y;
                pos.z = barrel->currentPos.z - 1.0f;
                if (barrel->currentPos.y <= 0.0f) {
                    fn_8004C108(&pos, TRUE);
                    callSfx(0x2e4);
                } else {
                    fn_8004C108(&pos, FALSE);
                    callSfx(0x2e5);
                }
            }
            barrel->barrelState = BB_BARREL_STATE_NEUTRAL;
        }
    }
}

// .text:0x001324E8 size:0x9F4 mapped:0x8077157C
void barrelBatterSwitcher(void) {
    return;
}

