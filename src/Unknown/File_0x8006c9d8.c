#define SQRT2_LINKAGE static
#include "Unknown/File_0x8006c9d8.h"
#include "game/UnknownHomes_Game.h"

typedef struct ScoutFlagTable {
    /*0x0*/ u8 _0[4];
    /*0x4*/ s8 required[4][6];
} ScoutFlagTable;

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

    cs = &starMissionCompletionTracker;
    diff = cs->difficulty;
    cap = cs->captain;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct* t = &cs->characters[i];
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
    return challengeIntermediateStarBUffs_CPU[starMissionCompletionTracker.difficulty][starMissionCompletionTracker.stage];
}

f32 intermediateStatBuffForCompletedMissions(int charID) {
    ChallengeTrackingStruct* t = &starMissionCompletionTracker.characters[charID];
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
