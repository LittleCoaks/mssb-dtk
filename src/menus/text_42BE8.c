#include "menus/text_42BE8.h"
#include "game/challenge/challenge_state.h"
#include "game/challenge/star_mission_data.h"
#include "challenge/challenge_progress.h"

extern ChallengeState *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;

// Number of saved lineup slots whose charID equals the argument.
static s32 savedLineupCountOf(s32 charID) {
    s32 count = 0;
    s32 k;
    for (k = 0; k < 9; k++) {
        if (lbl_2_bss_1A8248->savedLineup[k].charID == charID) {
            count++;
        }
    }
    return count;
}

void fn_2_42BE8(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < 10; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[cs->requirementRow][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 mode = rule->mode;
                    s32 type = req->type;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (mode != -1 && pair->shownOnPauseMenu == 0) {
                        switch (mode) {
                            case 1:
                                if (fn_8006CDC0(i) >= minStars && lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                                    pair->shownOnPauseMenu = 1;
                                }
                                break;
                            case 22:
                                if (challenge_isCharRecruited(minStars) == 1 &&
                                    lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                                    pair->shownOnPauseMenu = 1;
                                }
                                break;
                            case 24:
                                if (*((u8 *)lbl_2_bss_1A8248 + 0x4426) != 0 && lbl_2_bss_1A8248->captain == minStars &&
                                    lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                                    pair->shownOnPauseMenu = 1;
                                }
                                break;
                            case 25:
                                if ((*((u8 *)lbl_2_bss_1A8248 + 0x4426) & (1 << minScoutRow)) != 0 &&
                                    lbl_2_bss_1A8248->captain == minStars &&
                                    lbl_2_bss_1A8248->difficulty >= rule->_8) {
                                    pair->shownOnPauseMenu = 1;
                                }
                                break;
                            case 26:
                                if (savedLineupCountOf(minStars) != 0 &&
                                    lbl_2_bss_1A8248->opponentCaptain == minScoutRow &&
                                    lbl_2_bss_1A8248->difficulty >= rule->_8) {
                                    pair->shownOnPauseMenu = 1;
                                }
                                break;
                        }
                    }
                    if (type != -1 && pair->starMissionStatus < 0) {
                        pair->shownOnPauseMenu = 1;
                    }
                }
            }
        }
    }
}

void fn_2_42EB0(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < 10; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[cs->requirementRow][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 mode = rule->mode;
                    s32 type = req->type;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (mode != -1 && pair->shownOnPauseMenu == 0 && mode == 0x12 &&
                        lbl_2_bss_1A8248->difficulty >= minStars &&
                        *((u8 *)lbl_2_bss_1A8248 + 0x442A) == 1) {
                        pair->shownOnPauseMenu = 1;
                    }
                    if (type != -1 && pair->starMissionStatus < 0) {
                        pair->shownOnPauseMenu = 1;
                    }
                }
            }
        }
    }
}

void fn_2_42FC8(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < 10; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[cs->requirementRow][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 mode = rule->mode;
                    s32 type = req->type;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (mode != -1 && pair->shownOnPauseMenu == 0 && mode == 1 &&
                        fn_8006CDC0(i) >= minStars && lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                        pair->shownOnPauseMenu = 1;
                    }
                    if (type != -1 && pair->starMissionStatus < 0) {
                        pair->shownOnPauseMenu = 1;
                    }
                }
            }
        }
    }
}

void fn_2_430F4(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < 10; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[cs->requirementRow][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 mode = rule->mode;
                    s32 type = req->type;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (mode != -1 && pair->shownOnPauseMenu == 0) {
                        if (mode == 0x15) {
                            if (savedLineupCountOf(minStars) != 0 &&
                                lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                                pair->shownOnPauseMenu = 1;
                            }
                        } else if (mode == 2) {
                            if (lbl_2_bss_1A8248->difficulty >= minStars) {
                                pair->shownOnPauseMenu = 1;
                            }
                        }
                    }
                    if (type != -1 && pair->starMissionStatus < 0) {
                        pair->shownOnPauseMenu = 1;
                    }
                }
            }
        }
    }
}

void fn_2_432EC(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < 10; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[cs->requirementRow][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 mode = rule->mode;
                    s32 type = req->type;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (type != -1 && pair->starMissionStatus < 0) {
                        pair->shownOnPauseMenu = 1;
                    }
                    if (mode == 1 && fn_8006CDC0(i) >= minStars &&
                        lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                        pair->shownOnPauseMenu = 1;
                    }
                }
            }
        }
    }
}

void fn_2_43404(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < 10; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 target = req->target;
                    s32 minDifficulty = req->_6[0];
                    s32 minPoints = req->_6[1];
                    if (type != -1 && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED &&
                        type == 0x46 && lbl_2_bss_1A8248->captain == target &&
                        *(s16 *)((u8 *)lbl_2_bss_1A8248 + 0x43BC) >= minPoints * 100 &&
                        lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                        pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                    }
                }
            }
        }
    }
}

void fn_2_43E8C(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < 10; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 minDifficulty = req->_6[0];
                    if (type != -1 && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED &&
                        type == 0x3B && lbl_2_bss_1A824C[0x1978F4] == 1 &&
                        lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                        pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                    }
                }
            }
        }
    }
    lbl_2_bss_1A824C[0x1978F4] = 0;
}

void fn_2_44014(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < 10; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 target = req->target;
                    s32 minDifficulty = req->_6[0];
                    if (type != -1 && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED &&
                        type == 0x3A && lbl_2_bss_1A8248->_43C2[target] == 1 &&
                        lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                        pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                    }
                }
            }
        }
    }
}

void fn_2_44184(void) {
    s32 count = 0;
    s32 k;
    for (k = 0; k < 9; k++) {
        if (lbl_2_bss_1A8248->savedLineup[k].charID == 0xC) {
            count++;
        }
    }
    if (count == 0) {
        *((u8 *)lbl_2_bss_1A8248 + 0x44F7) = 1;
    }
}

BOOL fn_2_44238(int charID) {
    return savedLineupCountOf(charID) != 0;
}

BOOL fn_2_442E8(void) {
    s32 count = 0;
    s32 k;
    for (k = 0; k < 9; k++) {
        s16 id = lbl_2_bss_1A8248->savedLineup[k].charID;
        if (id == 0 || id == 1) {
            count++;
        }
    }
    return count == 2;
}

BOOL fn_2_44368(void) {
    s32 count = 0;
    s32 k;
    for (k = 0; k < 9; k++) {
        s16 id = lbl_2_bss_1A8248->savedLineup[k].charID;
        if (id == 0xD || (id >= 0x1D && id <= 0x1F) || id == 0x20) {
            count++;
        }
    }
    return count >= 5;
}

int fn_2_44E2C(int charIdx) {
    CharStaticIndex *cs = &characterStaticIndexes[charIdx];
    s32 count = 0;
    s32 j;
    if (cs->hasOwnStarMissions != 1) {
        return 0;
    }
    for (j = 0; j < 10; j++) {
        if (starMissionRequirementsTable[cs->requirementRow][j].type != -1) {
            count++;
        }
    }
    cs->requirementRow = cs->requirementRow;
    return count;
}

// Insertion sort of entries[1..54] by key; entries[0] is scratch and serves as the sentinel.
void fn_2_44414(SortEntry *entries) {
    s32 i;
    for (i = 1; i <= 54; i++) {
        SortEntry tmp = entries[i];
        s32 j = i - 1;
        entries[0] = tmp;
        while (tmp.key < entries[j].key) {
            entries[j + 1] = entries[j];
            j--;
        }
        entries[j + 1] = tmp;
    }
}

void fn_2_4358C(void) {
    return;
}

void fn_2_439D0(void) {
    return;
}

void fn_2_44504(void) {
    return;
}
