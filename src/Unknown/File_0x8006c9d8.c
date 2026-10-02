#define SQRT2_LINKAGE static
#include "Unknown/File_0x8006c9d8.h"
#include "game/UnknownHomes_Game.h"

typedef struct ChallengeState {
    /*0x0000*/ ChallengeTrackingStruct trackers[NUM_CHOOSABLE_CHARACTERS];
    /*0x0AF8*/ u8 _0AF8[0x4415 - 0xAF8];
    /*0x4415*/ u8 difficulty;
    /*0x4416*/ u8 _4416[0x441C - 0x4416];
    /*0x441C*/ E(u8, CHALLENGE_CAPTAIN) captain;
    /*0x441D*/ u8 _441D;
    /*0x441E*/ E(u8, CHALLENGE_CAPTAIN) opponentCaptain;
    /*0x441F*/ E(u8, CHAR_ID) opponentCaptainCharID;
    /*0x4420*/ u8 _4420[2];
    /*0x4422*/ u8 scoutFlagRow;
    /*0x4423*/ u8 _4423[0x444D - 0x4423];
    /*0x444D*/ E(u8, BOOL) recruitedChar[NUM_CHOOSABLE_CHARACTERS];
} ChallengeState;

typedef struct ScoutFlagTable {
    /*0x0*/ u8 _0[4];
    /*0x4*/ s8 required[4][6];
} ScoutFlagTable;

#define CHALLENGE ((ChallengeState*)starMissionCompletionTracker)

extern u8 characterStaticIndexes[NUM_CHOOSABLE_CHARACTERS][6];

f32 challengeIntermediateStarBuffs[5][11] = {
    {0.0f, 0.0f, 10.0f, 10.0f, 10.0f, 20.0f, 20.0f, 25.0f, 25.0f, 25.0f, 30.0f},
    {0.0f, 0.0f, 10.0f, 10.0f, 10.0f, 20.0f, 20.0f, 20.0f, 25.0f, 25.0f, 25.0f},
    {0.0f, 0.0f, 10.0f, 10.0f, 18.0f, 18.0f, 22.0f, 22.0f, 22.0f, 22.0f, 22.0f},
    {0.0f, 0.0f, 10.0f, 10.0f, 20.0f, 20.0f, 20.0f, 20.0f, 20.0f, 20.0f, 20.0f},
    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
};

f32 challengeIntermediateStarBUffs_CPU[4][7] = {
    {-10.0f, -10.0f, -5.0f, -5.0f, 10.0f, 10.0f, 0.0f},
    {0.0f, 0.0f, 5.0f, 5.0f, 15.0f, 15.0f, 0.0f},
    {5.0f, 5.0f, 10.0f, 10.0f, 20.0f, 20.0f, 0.0f},
    {10.0f, 10.0f, 15.0f, 15.0f, 25.0f, 25.0f, 0.0f},
};

void challenge_checkRecruitment(void) {
    int i;
    u8 diff;
    u8 cap;
    int recruited;
    ChallengeState* cs;

    cs = CHALLENGE;
    diff = cs->difficulty;
    cap = cs->captain;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct* t = &cs->trackers[i];
        recruited = (s8)t->_31;
        if (recruited == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
            continue;
        }
        if ((s8)t->scoutFlagsAchieved != ((ScoutFlagTable*)t->scoutFlagPointer)->required[diff][cap] ||
            ((ScoutFlagTable*)t->scoutFlagPointer)->required[diff][cap] == 0) {
            continue;
        }
        if ((int)cs->opponentCaptainCharID == CHAR_ID_BOWSERJR) {
            if (recruited == CHALLENGE_RECRUITMENT_CD_ON_BJ_TEAM) {
                t->_31 = CHALLENGE_RECRUITMENT_CD_RECRUITED;
                cs->recruitedChar[i] = TRUE;
            }
        } else if (recruited != CHALLENGE_RECRUITMENT_CD_ON_BJ_TEAM && (s8)t->challengeCaptain == cs->opponentCaptain) {
            t->_31 = CHALLENGE_RECRUITMENT_CD_RECRUITED;
            cs->recruitedChar[i] = TRUE;
        }
    }
}

f32 intermediateStatBuffForScoutFlags(void) {
    return challengeIntermediateStarBUffs_CPU[CHALLENGE->difficulty][CHALLENGE->scoutFlagRow];
}

f32 intermediateStatBuffForCompletedMissions(int charID) {
    ChallengeTrackingStruct* t = &starMissionCompletionTracker[charID];
    int count;
    int i;

    if (characterStaticIndexes[charID][3] == 0) {
        count = 0;
    } else {
        count = 0;
        for (i = 0; i < 10; i++) {
            if (t->inGameMissionTracker[i].starMissionStatus < 0) {
                count++;
            }
        }
    }
    return challengeIntermediateStarBuffs[t->variantClassification][count];
}
