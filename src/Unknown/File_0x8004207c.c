#include "Unknown/File_0x8004207c.h"
#include "game/UnknownHomes_Game.h"
#include "game/challenge/challenge_state.h"
#include "challenge/challenge_progress.h"

static u8 scaleStat(f32 scale, u8 value) {
    s32 scaled = scale * (f32)value;
    return scaled > 100 ? 100 : scaled;
}

void capApplicationFunction(void) {
    s32 team;
    s32 player;
    s32 k;
    s8 variant;
    s32 bonus = 0;
    u8 mode = 0;
    f32 scale;
    CharacterStats* row;
    u8* chem;

    for (team = 0; team < 2; team++) {
        row = inMemRoster[team];
        for (player = 0; player < 9; player++, row++) {
            if (team == 0) {
                scale = (100.0f + intermediateStatBuffForCompletedMissions(row->stats.CharID)) / 100.0f;
            } else {
                scale = (100.0f + intermediateStatBuffForScoutFlags()) / 100.0f;
            }

            row->stats.SlapContactSize = scaleStat(scale, row->stats.SlapContactSize);
            row->stats.ChargeContactSize = scaleStat(scale, row->stats.ChargeContactSize);
            row->stats.SlapHitPower = scaleStat(scale, row->stats.SlapHitPower);
            row->stats.ChargeHitPower = scaleStat(scale, row->stats.ChargeHitPower);
            row->stats.BuntingContactSize = scaleStat(scale, row->stats.BuntingContactSize);
            row->stats.Speed = scaleStat(scale, row->stats.Speed);
            row->stats.ThrowingArm = scaleStat(scale, row->stats.ThrowingArm);

            row->stats.CurveBallSpeed += 10;
            if (row->stats.CurveBallSpeed > 200) {
                row->stats.CurveBallSpeed = 200;
            }
            row->stats.FastBallSpeed += 10;
            if (row->stats.FastBallSpeed > 200) {
                row->stats.FastBallSpeed = 200;
            }

            row->stats.Curve = scaleStat(scale, row->stats.Curve);
            row->stats.curveControl = scaleStat(scale, row->stats.curveControl);

            if (team == 0) {
                mode = *(u32*)((u8*)&g_Challenge + 0x42EC);
                chem = (u8*)&row->chemistry;
                for (k = 0; k < 54; k++) {
                    chem[k] += mode * 5;
                    if (chem[k] > 100) {
                        chem[k] = 100;
                    }
                }
            }

            switch (mode) {
                case 0:
                    bonus = -1;
                    break;
                case 1:
                    bonus = 0;
                    break;
                case 2:
                    bonus = 1;
                    break;
                case 3:
                    variant = g_Challenge.characters[row->stats.CharID].variantClassification;
                    if (variant == 0 || variant == 1) {
                        bonus = 2;
                    } else {
                        bonus = 1;
                    }
                    break;
                case 4:
                    variant = g_Challenge.characters[row->stats.CharID].variantClassification;
                    if (variant == 0) {
                        bonus = 3;
                    } else if (variant == 1) {
                        bonus = 2;
                    } else {
                        bonus = 1;
                    }
                    break;
            }

            row->stats.BattingStatBar += bonus;
            if (row->stats.BattingStatBar > 10) {
                row->stats.BattingStatBar = 10;
            }
            row->stats.PitchingStatBar += bonus;
            if (row->stats.PitchingStatBar > 10) {
                row->stats.PitchingStatBar = 10;
            }
            row->stats.RunningStatBar += bonus;
            if (row->stats.RunningStatBar > 10) {
                row->stats.RunningStatBar = 10;
            }
            row->stats.FieldingStatBar += bonus;
            if (row->stats.FieldingStatBar > 10) {
                row->stats.FieldingStatBar = 10;
            }
        }
    }
}
