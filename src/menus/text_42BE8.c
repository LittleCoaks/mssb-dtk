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
static inline s32 savedLineupCountOf(s32 charID) {
    s32 count = 0;
    s32 k;
    for (k = 0; k < (s32)ARRAY_COUNT(lbl_2_bss_1A8248->savedLineup); k++) {
        if (lbl_2_bss_1A8248->savedLineup[k].charID == charID) {
            count++;
        }
    }
    return count;
}

#define STAR_SCRATCH_SENTINEL 0x2710

// Signed halfword / word views into the scratch area behind lbl_2_bss_1A824C. Offsets are the full byte offsets.
#define SCRATCH_S16(off) (*(s16 *)(lbl_2_bss_1A824C + (off)))
#define SCRATCH_S32(off) (*(s32 *)(lbl_2_bss_1A824C + (off)))

int fn_2_44E2C(int charIdx) {
    CharStaticIndex *cs = &characterStaticIndexes[charIdx];
    if (cs->hasOwnStarMissions == TRUE) {
        u8 row = cs->requirementRow;
        StarMissionRequirement *req = starMissionRequirementsTable[row];
        s32 count = 0;
        s32 j;
        for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++, req++) {
            if (req->type != STAR_MISSION_TYPE_NONE) {
                count++;
            }
        }
        cs->requirementRow = row;
        return count;
    }
    return 0;
}

void fn_2_44504(void) {
    s32 i;
    s32 j;
    s32 k = 0;
    s32 m;
    s32 n;
    s32 appended = 0;

    // Phase 1: list A (u16 @ 0x1977A2, 54 entries) = sentinel.
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        SCRATCH_S16(0x1977A2 + 2 * i) = STAR_SCRATCH_SENTINEL;
    }
    for (i = 0; i < 5; i++) {
        SCRATCH_S16(0x19780E + 2 * i) = CHAR_ID_NONE;
        SCRATCH_S16(0x197818 + 2 * i) = CHAR_ID_NONE;
    }
    // Phase 3: recruited characters (except the captain's character) go into list A.
    n = challenge_countRecruitedCharacters();
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        if (lbl_2_bss_1A8248->characters[i].recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED &&
            i != challengeCaptainCharIDs[lbl_2_bss_1A8248->captain]) {
            SCRATCH_S16(0x1977A2 + 2 * k) = i;
            k++;
        }
    }
    // Phase 4: saved lineup characters with secondary variant classification are appended to list A.
    for (j = 0; j < (s32)ARRAY_COUNT(lbl_2_bss_1A8248->savedLineup); j++) {
        if (n + appended < 0x20) {
            s16 charID = lbl_2_bss_1A8248->savedLineup[j].charID;
            if (lbl_2_bss_1A8248->characters[charID].variantClassification == CHARACTER_VARIANT_CLASSIFICATION_SECONDARY_VARIANT) {
                SCRATCH_S16(0x1977A2 + 2 * k) = charID;
                k++;
                appended++;
            }
        }
    }
    // Phase 5: list A entries whose scout flags have _2 == 4 move to the 0x197818 list.
    m = 0;
    for (i = 0; i < k; i++) {
        s16 v = SCRATCH_S16(0x1977A2 + 2 * i);
        if (v != STAR_SCRATCH_SENTINEL && lbl_2_bss_1A8248->characters[v].scoutFlagPointer->_2 == 4) {
            SCRATCH_S16(0x197818 + 2 * m) = v;
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
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS + 1; i++) {
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
            SCRATCH_S32(0x197458 + 8 * m) = (s8)lbl_2_bss_1A8248->characters[v].scoutFlagPointer->_2;
            SCRATCH_S32(0x19745C + 8 * m) = v;
        }
        m++;
    }
    // Phase 9: insertion sort of the pairs at 0x197450 (slot 0 is scratch) by first word.
    fn_2_44414((SortEntry *)(lbl_2_bss_1A824C + 0x197450));
    // Phase 10: list A = -1.
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        SCRATCH_S16(0x1977A2 + 2 * i) = -1;
    }
    // Phase 11: second words of the sorted pairs (non-sentinel) go back into list A.
    k = 0;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        s32 v = SCRATCH_S32(0x19745C + 8 * i);
        if (v != STAR_SCRATCH_SENTINEL) {
            SCRATCH_S16(0x1977A2 + 2 * k) = v;
            k++;
        }
    }
    // Place Petey at index 2 of the secondary list.
    for (i = 0; i < 5; i++) {
        if (SCRATCH_S16(0x197818 + 2 * i) == CHAR_ID_PETEY) {
            s16 tmp = SCRATCH_S16(0x19781C);
            SCRATCH_S16(0x19781C) = CHAR_ID_PETEY;
            SCRATCH_S16(0x197818 + 2 * i) = tmp;
        }
    }
}

void fn_2_44414(SortEntry *entries) {
    s32 i;
    for (i = 1; i <= NUM_CHOOSABLE_CHARACTERS; i++) {
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

BOOL fn_2_44368(void) {
    s32 count = 0;
    s32 k;
    for (k = 0; k < (s32)ARRAY_COUNT(lbl_2_bss_1A8248->savedLineup); k++) {
        s32 id = lbl_2_bss_1A8248->savedLineup[k].charID;
        if (id == CHAR_ID_TOAD_RED || (u32)(id - CHAR_ID_TOAD_BLUE) <= CHAR_ID_TOAD_GREEN - CHAR_ID_TOAD_BLUE || id == CHAR_ID_TOAD_PURPLE) {
            count++;
        }
    }
    return count >= 5;
}

BOOL fn_2_442E8(void) {
    s32 count = 0;
    s32 k;
    for (k = 0; k < (s32)ARRAY_COUNT(lbl_2_bss_1A8248->savedLineup); k++) {
        s32 id = lbl_2_bss_1A8248->savedLineup[k].charID;
        if (id == CHAR_ID_MARIO || id == CHAR_ID_LUIGI) {
            count++;
        }
    }
    return count == 2;
}

BOOL fn_2_44238(int charID) {
    return savedLineupCountOf(charID) != 0;
}

void fn_2_44184(void) {
    s32 count = 0;
    s32 k;
    for (k = 0; k < (s32)ARRAY_COUNT(lbl_2_bss_1A8248->savedLineup); k++) {
        if (lbl_2_bss_1A8248->savedLineup[k].charID == CHAR_ID_KOOPA_GREEN) {
            count++;
        }
    }
    if (count == 0) {
        *((u8 *)lbl_2_bss_1A8248 + 0x44F7) = 1;
    }
}

void fn_2_44014(void) {
    s32 i;
    s32 j;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 target = req->target;
                    s32 minDifficulty = req->_6[0];
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED &&
                        type == STAR_MISSION_TYPE_UNK_58 && lbl_2_bss_1A8248->_43C2[target] == 1 &&
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
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 minDifficulty = req->_6[0];
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED &&
                        type == STAR_MISSION_TYPE_UNK_59 && lbl_2_bss_1A824C[0x1978F4] == 1 &&
                        lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                        pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
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
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 target = req->target;
                    s32 flags = req->flags;
                    s32 minDifficulty = req->_6[0];
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED) {
                        switch (type) {
                            case 61:
                                if (lbl_2_bss_1A8248->captain == flags &&
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 60:
                                if (lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 69:
                                if (lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                    case 66:
                                if (*((u8 *)lbl_2_bss_1A8248 + 0x44F7) == 0) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 62:
                                if (fn_2_44368() == TRUE && lbl_2_bss_1A8248->difficulty >= minDifficulty) {
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
                                if (fn_2_442E8() == TRUE && lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 67:
                                if (fn_2_44238(i) == TRUE &&
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 68:
                                if (fn_2_44238(i) == TRUE &&
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                        }
                                break;
                        }
                    }
                }
            }
        }
    }
}

void fn_2_4358C(void) {
    s32 i;
    s32 j;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 target = req->target;
                    s32 minDifficulty = req->_6[0];
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED) {
                        s32 mode = *(s16 *)(lbl_2_bss_1A823C + 0x30);
                        if (mode == 3) {
                            if (type == STAR_MISSION_TYPE_UNK_73) {
                                if (lbl_2_bss_1A824C[0x197843] == 0 &&
                                    lbl_2_bss_1A8248->opponentCaptain == target &&
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty &&
                                    savedLineupCountOf(i) > 0) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                            } else if (type == 0x42) {
                                s32 count = 0;
                                s32 k;
                                for (k = 0; k < (s32)ARRAY_COUNT(lbl_2_bss_1A8248->savedLineup); k++) {
                                    if (lbl_2_bss_1A8248->savedLineup[k].charID == CHAR_ID_KOOPA_GREEN &&
                                        lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                        count++;
                                    }
                                }
                                if (count == 0) {
                                    *((u8 *)lbl_2_bss_1A8248 + 0x44F7) = 1;
                                }
                            }
                        } else if (mode == 5) {
                            if (type == STAR_MISSION_TYPE_UNK_65 && g_d_GameSettings[0x36] == i &&
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
                            if (type == STAR_MISSION_TYPE_UNK_72 && lbl_2_bss_1A824C[0x197843] == 0 &&
                                lbl_2_bss_1A8248->difficulty >= minDifficulty &&
                                challenge_isCharRecruited(CHAR_ID_BOWSERJR) == 0 &&
                                savedLineupCountOf(i) > 0) {
                                pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                            }
                        }
                        if (type == STAR_MISSION_TYPE_UNK_71 && challenge_hasRecruitedEnoughNonBowserCharacters() == 1 &&
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

void fn_2_43404(void) {
    s32 i;
    s32 j;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 target = req->target;
                    s32 minDifficulty = req->_6[0];
                    s32 minPoints = req->_6[1];
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED &&
                        type == STAR_MISSION_TYPE_UNK_70 && lbl_2_bss_1A8248->captain == target &&
                        *(s16 *)((u8 *)lbl_2_bss_1A8248 + 0x43BC) >= minPoints * 100 &&
                        lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                        pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                    }
                }
            }
        }
    }
}

void fn_2_432EC(void) {
    s32 i;
    s32 j;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[cs->requirementRow][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 mode = rule->mode;
                    s32 type = req->type;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus < 0) {
                        pair->shownOnPauseMenu = TRUE;
                    }
                    if (mode == 1 && fn_8006CDC0(i) >= minStars &&
                        lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                        pair->shownOnPauseMenu = TRUE;
                    }
                }
            }
        }
    }
}

void fn_2_430F4(void) {
    s32 i;
    s32 j;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[cs->requirementRow][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 mode = rule->mode;
                    s32 type = req->type;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (mode != -1 && pair->shownOnPauseMenu == FALSE) {
                        if (mode == 0x15) {
                            if (savedLineupCountOf(minStars) != 0 &&
                                lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                                pair->shownOnPauseMenu = TRUE;
                            }
                        } else if (mode == 2) {
                            if (lbl_2_bss_1A8248->difficulty >= minStars) {
                                pair->shownOnPauseMenu = TRUE;
                            }
                        }
                    }
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus < 0) {
                        pair->shownOnPauseMenu = TRUE;
                    }
                }
            }
        }
    }
}

void fn_2_42FC8(void) {
    s32 i;
    s32 j;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[cs->requirementRow][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 mode = rule->mode;
                    s32 type = req->type;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (mode != -1 && pair->shownOnPauseMenu == FALSE && mode == 1 &&
                        fn_8006CDC0(i) >= minStars && lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                        pair->shownOnPauseMenu = TRUE;
                    }
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus < 0) {
                        pair->shownOnPauseMenu = TRUE;
                    }
                }
            }
        }
    }
}

void fn_2_42EB0(void) {
    s32 i;
    s32 j;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[cs->requirementRow][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 mode = rule->mode;
                    s32 type = req->type;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (mode != -1 && pair->shownOnPauseMenu == FALSE && mode == 0x12 &&
                        lbl_2_bss_1A8248->difficulty >= minStars &&
                        *((u8 *)lbl_2_bss_1A8248 + 0x442A) == 1) {
                        pair->shownOnPauseMenu = TRUE;
                    }
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus < 0) {
                        pair->shownOnPauseMenu = TRUE;
                    }
                }
            }
        }
    }
}

void fn_2_42BE8(void) {
    s32 i;
    s32 j;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if (tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[cs->requirementRow][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[cs->requirementRow][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 mode = rule->mode;
                    s32 type = req->type;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (mode != -1 && pair->shownOnPauseMenu == FALSE) {
                        switch (mode) {
                            case 1:
                                if (fn_8006CDC0(i) >= minStars && lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                                    pair->shownOnPauseMenu = TRUE;
                                }
                                break;
                            case 22:
                                if (challenge_isCharRecruited(minStars) == 1 &&
                                    lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                                    pair->shownOnPauseMenu = TRUE;
                                }
                                break;
                            case 24:
                                if (*((u8 *)lbl_2_bss_1A8248 + 0x4426) != 0 && lbl_2_bss_1A8248->captain == minStars &&
                                    lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                                    pair->shownOnPauseMenu = TRUE;
                                }
                                break;
                            case 25:
                                if ((*((u8 *)lbl_2_bss_1A8248 + 0x4426) & (1 << minScoutRow)) != 0 &&
                                    lbl_2_bss_1A8248->captain == minStars &&
                                    lbl_2_bss_1A8248->difficulty >= rule->_8) {
                                    pair->shownOnPauseMenu = TRUE;
                                }
                                break;
                            case 26:
                                if (savedLineupCountOf(minStars) != 0 &&
                                    lbl_2_bss_1A8248->opponentCaptain == minScoutRow &&
                                    lbl_2_bss_1A8248->difficulty >= rule->_8) {
                                    pair->shownOnPauseMenu = TRUE;
                                }
                                break;
                        }
                    }
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus < 0) {
                        pair->shownOnPauseMenu = TRUE;
                    }
                }
            }
        }
    }
}
