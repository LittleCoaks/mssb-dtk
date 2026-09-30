#include "Unknown/File_0x8006cbe4.h"
#include "game/UnknownHomes_Game.h"

extern u8 characterStaticIndexes[0x144];
extern s16 starMissionsUnlockedDifficulty[][11];

BOOL challengeStarRelatedInd(int charID, int mission);

static inline int countStarMissions(int charID) {
    int i;
    int count;

    if (characterStaticIndexes[charID * 6 + 3] == 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 10; i++) {
        if (challengeStarRelatedInd(charID, i)) {
            count++;
        }
    }
    return count;
}

s16 challengeRelated(int charID) {
    ChallengeTrackingStruct* tracker = &starMissionCompletionTracker[charID];

    return starMissionsUnlockedDifficulty[tracker->variantClassification][countStarMissions(charID)];
}
