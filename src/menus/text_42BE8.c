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

// Character lists and (key, charID) sort pairs in the menus work area behind lbl_2_bss_1A824C
// (full byte offsets). The sort pairs start at 0x197450; entry 0 is the insertion sort's scratch slot.
#define LIST_A(i) (((s16 *)lbl_2_bss_1A824C)[0x1977A2 / 2 + (i)])
#define LIST_B(i) (((s16 *)lbl_2_bss_1A824C)[0x19780E / 2 + (i)])
#define LIST_C(i) (((s16 *)lbl_2_bss_1A824C)[0x197818 / 2 + (i)])
#define PAIR_KEY(i) (((s32 *)lbl_2_bss_1A824C)[0x197450 / 4 + 2 * (i)])
#define PAIR_VALUE(i) (((s32 *)lbl_2_bss_1A824C)[0x197454 / 4 + 2 * (i)])
#define SORTED_KEY(i) (((s32 *)lbl_2_bss_1A824C)[0x197458 / 4 + 2 * (i)]) /* PAIR_KEY(i + 1) */
#define SORTED_VALUE(i) (((s32 *)lbl_2_bss_1A824C)[0x19745C / 4 + 2 * (i)])

int fn_2_44E2C(int charIdx) {
    CharStaticIndex *cs = &characterStaticIndexes[charIdx];
    if (cs->hasOwnStarMissions == TRUE) {
        u8 row;
        u8 *rowPtr = &cs->requirementRow;
        StarMissionRequirement *req;
        s32 count = 0;
        s32 j;

        row = *rowPtr;
        req = starMissionRequirementsTable[row];
        for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++, req++) {
            if (req->type != STAR_MISSION_TYPE_NONE) {
                count++;
            }
        }
        *rowPtr = row; /* the original writes the row back unchanged */
        return count;
    }
    return 0;
}

void fn_2_44504(void) {
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 n;
    s32 appended;

    // List A: every candidate character, STAR_SCRATCH_SENTINEL for an empty slot.
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        LIST_A(i) = STAR_SCRATCH_SENTINEL;
    }
    for (i = 0; i < 5; i++) {
        LIST_B(i) = CHAR_ID_NONE;
        LIST_C(i) = CHAR_ID_NONE;
    }
    // Recruited characters other than the captain's character.
    n = challenge_countRecruitedCharacters();
    k = 0;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        if ((s32)(&lbl_2_bss_1A8248->characters[i])->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED &&
            i != challengeCaptainCharIDs[lbl_2_bss_1A8248->captain]) {
            LIST_A(k) = i;
            k++;
        }
    }
    // Saved lineup characters that are secondary variants, while there is room.
    appended = 0;
    for (j = 0; j < (s32)ARRAY_COUNT(lbl_2_bss_1A8248->savedLineup); j++) {
        if (n + appended < 0x20) {
            s16 charID = lbl_2_bss_1A8248->savedLineup[j].charID;
            if (lbl_2_bss_1A8248->characters[charID].variantClassification == CHARACTER_VARIANT_CLASSIFICATION_SECONDARY_VARIANT) {
                LIST_A(k) = charID;
                k++;
                appended++;
            }
        }
    }
    // Entries whose scout flag record has _2 == 4 move to list C.
    m = 0;
    for (i = 0; i < k; i++) {
        s16 v = LIST_A(i);
        if (v != STAR_SCRATCH_SENTINEL && (s32)lbl_2_bss_1A8248->characters[v].scoutFlagPointer->_2 == 4) {
            LIST_C(m) = v;
            m++;
            LIST_A(i) = STAR_SCRATCH_SENTINEL;
        }
    }
    // With at least 10 recruits, entries whose record has _3 == 1 move to list B.
    if (n >= 10) {
        m = 0;
        for (i = 0; i < k; i++) {
            s16 v = LIST_A(i);
            if (v != STAR_SCRATCH_SENTINEL && (s32)lbl_2_bss_1A8248->characters[v].scoutFlagPointer->_3 == 1) {
                LIST_B(m) = v;
                m++;
                LIST_A(i) = STAR_SCRATCH_SENTINEL;
            }
        }
    }
    // Sort pairs (scout _2, charID); slot 0 is the insertion sort's scratch slot.
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS + 1; i++) {
        PAIR_KEY(i) = STAR_SCRATCH_SENTINEL;
        PAIR_VALUE(i) = STAR_SCRATCH_SENTINEL;
    }
    m = 0;
    for (i = 0; i < k + 1; i++) {
        if (LIST_A(i) != STAR_SCRATCH_SENTINEL) {
            SORTED_KEY(m) = (s8)lbl_2_bss_1A8248->characters[LIST_A(i)].scoutFlagPointer->_2;
            SORTED_VALUE(m) = LIST_A(i);
        } else {
            SORTED_KEY(m) = STAR_SCRATCH_SENTINEL;
            SORTED_VALUE(m) = STAR_SCRATCH_SENTINEL;
        }
        m++;
    }
    fn_2_44414((SortEntry *)(lbl_2_bss_1A824C + 0x197450));
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        LIST_A(i) = CHAR_ID_NONE;
    }
    // List A = the sorted characters.
    k = 0;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        if (SORTED_VALUE(i) != STAR_SCRATCH_SENTINEL) {
            LIST_A(k) = SORTED_VALUE(i);
            k++;
        }
    }
    // Petey always takes slot 2 of list C.
    for (i = 0; i < 5; i++) {
        if (LIST_C(i) == CHAR_ID_PETEY) {
            s16 tmp = LIST_C(2);
            LIST_C(2) = LIST_C(i);
            LIST_C(i) = tmp;
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
    return (count >= 5) ? TRUE : FALSE;
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
    return (count == 2) ? TRUE : FALSE;
}

BOOL fn_2_44238(int charID) {
    return (savedLineupCountOf(charID) != 0) ? TRUE : FALSE;
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
            if ((s32)tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                u8 *row = &cs->requirementRow;
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[*row][j];
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
    CharStaticIndex *cs = characterStaticIndexes;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++, cs++) {
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if ((s32)tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                u8 *row = &cs->requirementRow;
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[*row][j];
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
            if ((s32)tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                u8 *row = &cs->requirementRow;
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[*row][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 target = req->target;
                    s32 flags = req->flags;
                    s32 minDifficulty = req->_6[0];
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED) {
                        switch (type) {
                        case 61:
                            if (lbl_2_bss_1A8248->captain == flags && lbl_2_bss_1A8248->difficulty >= minDifficulty) {
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
                            }
                            break;
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
                            if (lbl_2_bss_1A8248->captain == target && *((u8 *)lbl_2_bss_1A8248 + 0x44F6) == 0 && lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                            }
                            break;
                        case 64:
                            if (fn_2_442E8() == TRUE && lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                            }
                            break;
                        case 67:
                            if (fn_2_44238(i) == TRUE && lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                            }
                            break;
                        case 68:
                            if (fn_2_44238(i) == TRUE && lbl_2_bss_1A8248->difficulty >= minDifficulty) {
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

void fn_2_4358C(void) {
    s32 i;
    s32 j;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if ((s32)tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                u8 *row = &cs->requirementRow;
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[*row][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 target = req->target;
                    s32 minDifficulty = req->_6[0];
                    if (type != STAR_MISSION_TYPE_NONE && pair->starMissionStatus == STAR_MISSION_TRACKING_NOT_COMPLETED) {
                        s32 mode = *(s16 *)(lbl_2_bss_1A823C + 0x30);
                        if (mode == 3) {
                            switch (type) {
                            case STAR_MISSION_TYPE_UNK_73:
                                if ((s8)lbl_2_bss_1A824C[0x197843] == 0 &&
                                    lbl_2_bss_1A8248->opponentCaptain == target &&
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty &&
                                    savedLineupCountOf(i) > 0) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                                break;
                            case 0x42: {
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
                                break;
                            }
                            }
                        } else if (mode == 5) {
                            if (type == STAR_MISSION_TYPE_UNK_65 && (s8)lbl_2_bss_1A824C[0x197843] == 0 &&
                                g_d_GameSettings[0x36] == i &&
                                lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                s32 bit = 1 << *((u8 *)lbl_2_bss_1A8248 + 0x4420);
                                if ((tr->_8 & bit) == 0) {
                                    tr->_8 |= bit;
                                }
                                if (tr->_8 == 0x1F) {
                                    pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                                }
                            }
                        } else if (mode == 4) {
                            if (type == STAR_MISSION_TYPE_UNK_72 && (s8)lbl_2_bss_1A824C[0x197843] == 0 &&
                                lbl_2_bss_1A8248->difficulty >= minDifficulty &&
                                challenge_isCharRecruited(CHAR_ID_BOWSERJR) == 0 &&
                                savedLineupCountOf(i) > 0) {
                                pair->starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
                            }
                        }
                        if (type == STAR_MISSION_TYPE_UNK_71 && challenge_hasRecruitedEnoughNonBowserCharacters() == 1 &&
                            lbl_2_bss_1A8248->difficulty >= minDifficulty && target == lbl_2_bss_1A8248->captain) {
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
            if ((s32)tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                u8 *row = &cs->requirementRow;
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionRequirement *req = &starMissionRequirementsTable[*row][j];
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
            if ((s32)tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                u8 *row = &cs->requirementRow;
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[*row][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[*row][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 mode = rule->mode;
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
            if ((s32)tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                u8 *row = &cs->requirementRow;
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[*row][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[*row][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 mode = rule->mode;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (mode != -1 && (s8)pair->shownOnPauseMenu == FALSE) {
                        switch (mode) {
                        case 2:
                            if (lbl_2_bss_1A8248->difficulty >= minStars) {
                                pair->shownOnPauseMenu = TRUE;
                            }
                            break;
                        case 0x15:
                            if (fn_2_44238(minStars) == TRUE && lbl_2_bss_1A8248->difficulty >= minScoutRow) {
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

void fn_2_42FC8(void) {
    s32 i;
    s32 j;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *cs = &characterStaticIndexes[i];
        if (cs->hasOwnStarMissions == 1) {
            ChallengeTrackingStruct *tr = &lbl_2_bss_1A8248->characters[i];
            if ((s32)tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                u8 *row = &cs->requirementRow;
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[*row][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[*row][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 mode = rule->mode;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    if (mode != -1 && (s8)pair->shownOnPauseMenu == FALSE && mode == 1 &&
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
            if ((s32)tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                u8 *row = &cs->requirementRow;
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[*row][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[*row][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 mode = rule->mode;
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
            if ((s32)tr->recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                u8 *row = &cs->requirementRow;
                for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
                    StarMissionDisplayRule *rule = &starMissionDisplayRules[*row][j];
                    StarMissionRequirement *req = &starMissionRequirementsTable[*row][j];
                    starMissionTrackingPair *pair = &tr->inGameMissionTracker[j];
                    s32 type = req->type;
                    s32 mode = rule->mode;
                    s32 minStars = rule->minStars;
                    s32 minScoutRow = rule->minScoutRow;
                    s32 minDifficulty = rule->_8;
                    if (mode != -1 && (s8)pair->shownOnPauseMenu == FALSE) {
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
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty) {
                                    pair->shownOnPauseMenu = TRUE;
                                }
                                break;
                            case 26:
                                if (fn_2_44238(minStars) == TRUE &&
                                    lbl_2_bss_1A8248->opponentCaptain == minScoutRow &&
                                    lbl_2_bss_1A8248->difficulty >= minDifficulty) {
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
