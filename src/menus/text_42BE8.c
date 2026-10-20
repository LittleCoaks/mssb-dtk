#include "menus/text_42BE8.h"
#include "game/challenge/challenge_state.h"
#include "game/challenge/star_mission_data.h"
#include "challenge/challenge_progress.h"

extern ChallengeState *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A823C;
extern u8 g_d_GameSettings[];
extern u8 challengeCaptainCharIDs[];

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
        if (lbl_2_bss_1A8248->savedLineup[k].charID == CHAR_ID_KOOPA_GREEN) {
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
                    if (type != -1 && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED) {
                        s32 mode = *(s16 *)(lbl_2_bss_1A823C + 0x30);
                        if (mode == 3) {
                            if (type == 0x49) {
                                if (lbl_2_bss_1A824C[0x197843] == 0 &&
                                    lbl_2_bss_1A8248->opponentCaptain == target &&
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty &&
                                    savedLineupCountOf(i) > 0) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                            } else if (type == 0x42) {
                                s32 count = 0;
                                s32 k;
                                for (k = 0; k < 9; k++) {
                                    if (lbl_2_bss_1A8248->savedLineup[k].charID == 0xC &&
                                        lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                        count++;
                                    }
                                }
                                if (count == 0) {
                                    *((u8 *)lbl_2_bss_1A8248 + 0x44F7) = 1;
                                }
                            }
                        } else if (mode == 5) {
                            if (type == 0x41 && g_d_GameSettings[0x36] == i &&
                                lbl_2_bss_1A824C[0x197843] == 0 &&
                                lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                u8 bit = (u8)(1 << *((u8 *)lbl_2_bss_1A8248 + 0x4420));
                                if ((tr->_8 & bit) == 0) {
                                    tr->_8 |= bit;
                                }
                                if (tr->_8 == 0x1F) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                            }
                        } else if (mode == 4) {
                            if (type == 0x48 && lbl_2_bss_1A824C[0x197843] == 0 &&
                                lbl_2_bss_1A8248->difficulty >= minDifficulty &&
                                challenge_isCharRecruited(0x13) == 0 &&
                                savedLineupCountOf(i) > 0) {
                                pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                            }
                        }
                        if (type == 0x47 && challenge_hasRecruitedEnoughNonBowserCharacters() == 1 &&
                            lbl_2_bss_1A8248->difficulty >= minDifficulty && lbl_2_bss_1A8248->captain == target) {
                            pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                        }
                    }
                }
            }
        }
    }
    lbl_2_bss_1A824C[0x1978F4] = 0;
}

void fn_2_439D0(void) {
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
                    s32 flags = req->flags;
                    s32 minDifficulty = req->_6[0];
                    if (type != -1 && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED) {
                        switch (type) {
                            case 60:
                                if (lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 61:
                                if (lbl_2_bss_1A8248->captain == flags &&
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 62:
                                if (fn_2_44368() && lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 63:
                                if (lbl_2_bss_1A8248->captain == target &&
                                    *((u8 *)lbl_2_bss_1A8248 + 0x44F6) == 0 &&
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 64:
                                if (fn_2_442E8() && lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 66:
                                if (*((u8 *)lbl_2_bss_1A8248 + 0x44F7) == 0) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 67:
                            case 68:
                                if (savedLineupCountOf(i) != 0 &&
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 69:
                                if (lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                        }
                    }
                }
            }
        }
    }
}

#define STAR_SCRATCH_SENTINEL 0x2710

// Raw u16 / u32 views into the scratch area behind lbl_2_bss_1A824C. Offsets are the full byte offsets.
#define SCRATCH_S16(off) (*(s16 *)(lbl_2_bss_1A824C + (off)))
#define SCRATCH_S32(off) (*(s32 *)(lbl_2_bss_1A824C + (off)))

void fn_2_44504(void) {
    s32 i;
    s32 j;
    s32 k = 0;
    s32 m;
    s32 n;

    // Phase 1: list A (u16 @ 0x1977A2, 54 entries) = sentinel.
    for (i = 0; i < 54; i++) {
        SCRATCH_S16(0x1977A2 + 2 * i) = STAR_SCRATCH_SENTINEL;
    }
    // Phase 2: 10 u16 slots @ 0x19780E = -1.
    for (i = 0; i < 10; i++) {
        SCRATCH_S16(0x19780E + 2 * i) = -1;
    }
    // Phase 3: recruited characters (except the captain's character) go into list A.
    n = challenge_countRecruitedCharacters();
    for (i = 0; i < 18; i++) {
        if (lbl_2_bss_1A8248->characters[i].recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED &&
            i != challengeCaptainCharIDs[lbl_2_bss_1A8248->captain]) {
            SCRATCH_S16(0x1977A2 + 2 * k) = i;
            k++;
        }
    }
    // Phase 4: saved lineup characters with variantClassification 4 are appended to list A.
    for (j = 0; j < 9; j++) {
        if (n + j < 0x20) {
            s16 charID = lbl_2_bss_1A8248->savedLineup[j].charID;
            if (lbl_2_bss_1A8248->characters[charID].variantClassification == 4) {
                SCRATCH_S16(0x1977A2 + 2 * k) = charID;
                k++;
            }
        }
    }
    // Phase 5: list A entries whose scout flags have _2 == 4 move to the 0x197818 list.
    m = 0;
    for (i = 0; i < k; i++) {
        s16 v = SCRATCH_S16(0x1977A2 + 2 * i);
        if (v != STAR_SCRATCH_SENTINEL && lbl_2_bss_1A8248->characters[v].scoutFlagPointer->_2 == 4) {
            SCRATCH_S16(0x197818 + 2 * (k + m)) = v;
            m++;
            SCRATCH_S16(0x1977A2 + 2 * i) = STAR_SCRATCH_SENTINEL;
        }
    }
    // Phase 6: when at least 10 characters are recruited, entries with _3 == 1 move to the 0x19780E list.
    if (n >= 10) {
        m = 0;
        for (i = 0; i < k; i++) {
            s16 v = SCRATCH_S16(0x1977A2 + 2 * i);
            if (v != STAR_SCRATCH_SENTINEL && lbl_2_bss_1A8248->characters[v].scoutFlagPointer->_3 == 1) {
                SCRATCH_S16(0x19780E + 2 * m) = v;
                m++;
                SCRATCH_S16(0x1977A2 + 2 * i) = STAR_SCRATCH_SENTINEL;
            }
        }
    }
    // Phase 7: sort entries, 8 bytes each, at 0x197450: all 55 slots = sentinel pairs.
    for (i = 0; i < 55; i++) {
        SCRATCH_S32(0x197450 + 8 * i) = STAR_SCRATCH_SENTINEL;
        SCRATCH_S32(0x197454 + 8 * i) = STAR_SCRATCH_SENTINEL;
    }
    // Phase 8: pair (scout _2, charID) for each list A entry, written from slot 1 on.
    m = 0;
    for (i = 0; i <= k; i++) {
        s16 v = SCRATCH_S16(0x1977A2 + 2 * i);
        if (v == STAR_SCRATCH_SENTINEL) {
            SCRATCH_S32(0x197458 + 8 * m) = STAR_SCRATCH_SENTINEL;
            SCRATCH_S32(0x19745C + 8 * m) = STAR_SCRATCH_SENTINEL;
        } else {
            SCRATCH_S32(0x197458 + 8 * m) = lbl_2_bss_1A8248->characters[v].scoutFlagPointer->_2;
            SCRATCH_S32(0x19745C + 8 * m) = v;
        }
        m++;
    }
    // Phase 9: insertion sort of the pairs at 0x197450 (slot 0 is scratch) by first word.
    fn_2_44414((SortEntry *)(lbl_2_bss_1A824C + 0x197450));
    // Phase 10: list A = -1.
    for (i = 0; i < 54; i++) {
        SCRATCH_S16(0x1977A2 + 2 * i) = -1;
    }
    // Phase 11: second words of the sorted pairs (non-sentinel) go back into list A.
    k = 0;
    for (i = 0; i < 36; i++) {
        s32 v = SCRATCH_S32(0x19745C + 8 * i);
        if (v != STAR_SCRATCH_SENTINEL) {
            SCRATCH_S16(0x1977A2 + 2 * k) = v;
            k++;
        }
    }
    // Phase 12: bubble any 0x26 in the 0x197818 list one step forward, five times.
    for (i = 0; i < 5; i++) {
        if (SCRATCH_S16(0x197818 + 2 * i) == 0x26) {
            s16 tmp = SCRATCH_S16(0x19781C);
            SCRATCH_S16(0x19781C) = 0x26;
            SCRATCH_S16(0x197818 + 2 * i) = tmp;
        }
    }
}
