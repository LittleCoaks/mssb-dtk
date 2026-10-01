#include "Unknown/File_0x8006c48c.h"
#include "Unknown/File_0x800247e4.h"
#include "game/UnknownHomes_Game.h"

typedef struct CharStaticIndex {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 trackerIdx;
    /*0x2*/ u8 requirementRow;
    /*0x3*/ u8 _3;
    /*0x4*/ u8 _4[2];
} CharStaticIndex; // size: 0x6

/* Per-mission rule for showing a star mission on the pause/mission menu.
 * Same shape as starMissionRequirementsTable, which immediately precedes it. */
typedef struct StarMissionDisplayRule {
    /*0x0*/ s16 _0;
    /*0x2*/ s16 mode;     // 0 = always shown, 1 = shown once enough stars are earned
    /*0x4*/ s16 minStars;
    /*0x6*/ s16 minScoutRow;
    /*0x8*/ s16 _8;
} StarMissionDisplayRule; // size: 0xA

extern CharStaticIndex characterStaticIndexes[54];
extern StarMissionDisplayRule lbl_8010A768[32][10];

static inline int countStarMissions(int charID) {
    int i;
    int count;

    if (characterStaticIndexes[charID]._3 == 0) {
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

void challengeDrawStarsOnMissionMenu(void) {
    int c;
    int m;
    StarMissionDisplayRule* rule;
    int mode;
    int minStars;
    int minScoutRow;
    int scoutRow;

    scoutRow = ((u8*)starMissionCompletionTracker)[0x4415];
    for (c = 0; c < 54; c++) {
        if (characterStaticIndexes[c]._3 == 1 && (int)starMissionCompletionTracker[c]._31 == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
            for (m = 0; m < 10; m++) {
                rule = &lbl_8010A768[characterStaticIndexes[c].requirementRow][m];
                mode = rule->mode;
                minStars = rule->minStars;
                minScoutRow = rule->minScoutRow;
                if (mode == 0) {
                    starMissionCompletionTracker[c].inGameMissionTracker[m].shownOnPauseMenu = TRUE;
                }
                if (challengeStarRelatedInd(c, m)) {
                    starMissionCompletionTracker[c].inGameMissionTracker[m].shownOnPauseMenu = TRUE;
                }
                if (mode == 1 && countStarMissions(c) >= minStars && scoutRow >= minScoutRow) {
                    starMissionCompletionTracker[c].inGameMissionTracker[m].shownOnPauseMenu = TRUE;
                }
            }
        }
    }
}
