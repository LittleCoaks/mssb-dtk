#include "Unknown/File_0x8006c7c4.h"
#include "game/UnknownHomes_Game.h"

u8 challengeCaptainCharIDs[6] = {
    CHAR_ID_MARIO, CHAR_ID_PEACH, CHAR_ID_WARIO, CHAR_ID_DK, CHAR_ID_YOSHI, CHAR_ID_BOWSER,
};

void challenge_leftoverTeammatesJoinBowserJr(void) {
    BOOL captainJoined[6];
    ChallengeState* cs = &starMissionCompletionTracker;
    ChallengeTrackingStruct* t;
    u8 captain = cs->captain;
    int c;
    int k;

    for (k = 0; k < 6; k++) {
        captainJoined[k] = FALSE;
    }
    for (c = 0; c < NUM_CHOOSABLE_CHARACTERS; c++) {
        t = &cs->characters[c];
        for (k = 0; k < 6; k++) {
            if (c == challengeCaptainCharIDs[k] && (int)t->_31 == CHALLENGE_RECRUITMENT_CD_RECRUITED && k != captain) {
                captainJoined[k] = TRUE;
            }
        }
    }
    for (k = 0; k < 6; k++) {
        if (captainJoined[k] && (s8)t->_31 == 0) {
            for (c = 0; c < NUM_CHOOSABLE_CHARACTERS; c++) {
                if ((s8)cs->characters[c]._31 == 0 && k == (s8)cs->characters[c].challengeCaptain) {
                    cs->characters[c]._31 = CHALLENGE_RECRUITMENT_CD_ON_BJ_TEAM;
                }
            }
        }
    }
}
