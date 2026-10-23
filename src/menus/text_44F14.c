#include "menus/text_44F14.h"
#include "game/challenge/star_mission_data.h"
#include "challenge/challenge_progress.h"
#include "Unknown/File_0x8004c094.h"

extern ChallengeState *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A8244;
extern u8 *lbl_2_bss_1A824C;
extern u8 challengeCaptainCharIDs[6];
extern ParticleBurstParams *lbl_2_data_13374;
void *memcpy(void *dst, const void *src, u32 n);

static inline s32 readChallengeSignedByte(s32 offset) {
    return ((s8 *)lbl_2_bss_1A8248)[offset];
}

// .text:0x00046C2C size:0x5C mapped:0x80685CC0
void fn_2_46C2C(s32 unused, Vec *pos) {
    Vec v;
    v.x = pos->x;
    v.y = pos->y;
    v.z = pos->z;
    lbl_2_data_13374->texture = lbl_803CBD0C;
    fn_80031CA4(&v, lbl_2_data_13374);
}

// .text:0x00046C24 size:0x8 mapped:0x80685CB8
BOOL fn_2_46C24(void) {
    return FALSE;
}

// .text:0x00046ADC size:0x148 mapped:0x80685B70
void fn_2_46ADC(void) {
    s32 i;
    s32 k;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *c = &lbl_2_bss_1A8248->characters[i];
        ScoutFlagTable *table = &scoutFlagTables[i];
        c->scoutFlagPointer = table;
        c->challengeCaptain = c->scoutFlagPointer->challengeCaptain;
        c->variantClassification = c->scoutFlagPointer->variantClassification;
        c->_7 = 0;
        c->scoutFlagsAchieved = 0;
        c->_8 = 0;
        for (k = 0; k < 40; k++) {
            ((u8 *)c->inGameMissionTracker)[k] = 0;
        }
        if ((s8)c->challengeCaptain == lbl_2_bss_1A8248->captain &&
            (s8)c->variantClassification <= CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_VARIANT) {
            c->recruitmentStatus = CHALLENGE_RECRUITMENT_CD_RECRUITED;
        } else {
            c->recruitmentStatus = CHALLENGE_RECRUITMENT_CD_NOT_RECRUITED;
        }
    }
}

// .text:0x000468DC size:0x200 mapped:0x80685970
void fn_2_468DC(void) {
    s32 i;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *c = &lbl_2_bss_1A8248->characters[i];
        ScoutFlagTable *table = &scoutFlagTables[i];
        c->scoutFlagPointer = table;
        c->challengeCaptain = c->scoutFlagPointer->challengeCaptain;
        c->variantClassification = c->scoutFlagPointer->variantClassification;
    }
}

// .text:0x000467FC size:0xE0 mapped:0x80685890
void fn_2_467FC(void) {
    s32 i;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *c = &lbl_2_bss_1A8248->characters[i];
        if ((s8)c->challengeCaptain == lbl_2_bss_1A8248->captain &&
            (s8)c->variantClassification <= CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_VARIANT) {
            c->recruitmentStatus = CHALLENGE_RECRUITMENT_CD_RECRUITED;
        } else {
            c->recruitmentStatus = CHALLENGE_RECRUITMENT_CD_NOT_RECRUITED;
        }
    }
}

// .text:0x000466AC size:0x150 mapped:0x80685740
void fn_2_466AC(void) {
    s32 i;
    s32 k;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *entry = &characterStaticIndexes[i];
        ChallengeTrackingStruct *c = &lbl_2_bss_1A8248->characters[i];
        for (k = 0; k < STAR_MISSIONS_PER_CHARACTER; k++) {
            StarMissionDisplayRule *rule = &starMissionDisplayRules[entry->requirementRow][k];
            StarMissionRequirement *req = &starMissionRequirementsTable[entry->requirementRow][k];
            starMissionTrackingPair *pair = &c->inGameMissionTracker[k];
            s32 mode = rule->mode;
            s32 requirementType = req->type;
            s32 minStars = rule->minStars;
            s32 minScoutRow = rule->minScoutRow;

            if (mode == 0) {
                pair->shownOnPauseMenu = TRUE;
            }
            if (mode == 1) {
                if (fn_8006CDC0(i) >= minStars && lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                    pair->shownOnPauseMenu = TRUE;
                } else {
                    pair->shownOnPauseMenu = FALSE;
                }
            }
            if (mode == 19) {
                if (lbl_2_bss_1A8248->captain == minStars && lbl_2_bss_1A8248->difficulty >= minScoutRow) {
                    pair->shownOnPauseMenu = TRUE;
                }
            }
            if (requirementType != STAR_MISSION_TYPE_NONE && pair->starMissionStatus < 0) {
                pair->shownOnPauseMenu = TRUE;
            }
        }
    }
}

// .text:0x0004668C size:0x20 mapped:0x80685720
void fn_2_4668C(s32 charID) {
    lbl_2_bss_1A8248->characters[charID].recruitmentStatus = CHALLENGE_RECRUITMENT_CD_RECRUITED;
}

// .text:0x00046418 size:0x274 mapped:0x806854AC
void fn_2_46418(void) {
    s32 i;
    memcpy(lbl_2_bss_1A8248, &lbl_2_bss_1A8248->_0AF8,
           sizeof(lbl_2_bss_1A8248->characters));
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        lbl_2_bss_1A8248->characters[i]._7 = 0;
        lbl_2_bss_1A8248->characters[i].scoutFlagsAchieved = 0;
        lbl_2_bss_1A8248->characters[i]._8 = 0;
        lbl_2_bss_1A8248->characters[i].recruitmentStatus = CHALLENGE_RECRUITMENT_CD_NOT_RECRUITED;
    }
    ((u8 *)lbl_2_bss_1A8248)[0x442A] = ((u8 *)lbl_2_bss_1A8248)[0x15F0];
}

// .text:0x000460F8 size:0x320 mapped:0x8068518C
void fn_2_460F8(void) {
    s32 i;
    s32 k;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        lbl_2_bss_1A8248->characters[i]._7 = 0;
        lbl_2_bss_1A8248->characters[i].scoutFlagsAchieved = 0;
        lbl_2_bss_1A8248->characters[i]._8 = 0;
        lbl_2_bss_1A8248->characters[i].recruitmentStatus = CHALLENGE_RECRUITMENT_CD_NOT_RECRUITED;
    }
    memcpy(&lbl_2_bss_1A8248->_0AF8, lbl_2_bss_1A8248,
           sizeof(lbl_2_bss_1A8248->characters));
    ((u8 *)lbl_2_bss_1A8248)[0x15F0] = ((u8 *)lbl_2_bss_1A8248)[0x442A];
    for (k = 0; k < (s32)sizeof(lbl_2_bss_1A8248->_43C2); k++) {
        u8 *slot = (u8 *)lbl_2_bss_1A8248 + k;
        if ((s8)slot[0x15F1] == 0) {
            slot[0x15F1] = slot[CHALLENGE_STATE_OFFSET(_43C2)];
        }
    }
}

// .text:0x000460F4 size:0x4 mapped:0x80685188
void fn_2_460F4(void) {
    return;
}

// .text:0x000460F0 size:0x4 mapped:0x80685184
void fn_2_460F0(void) {
    return;
}

// .text:0x000460EC size:0x4 mapped:0x80685180
void fn_2_460EC(void) {
    return;
}

// .text:0x00045FDC size:0x110 mapped:0x80685070
void fn_2_45FDC(void) {
    s32 i;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *c = &lbl_2_bss_1A8248->characters[i];
        c->_7 = c->scoutFlagsAchieved;
    }
}

// .text:0x00045E48 size:0x194 mapped:0x80684EDC
void fn_2_45E48(void) {
    s32 i;
    s32 k;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *c = &lbl_2_bss_1A8248->characters[i];
        for (k = 0; k < STAR_MISSIONS_PER_CHARACTER; k++) {
            c->saveFileMissionTracker[k].starMissionStatus = c->inGameMissionTracker[k].starMissionStatus;
            c->saveFileMissionTracker[k].shownOnPauseMenu = c->inGameMissionTracker[k].shownOnPauseMenu;
        }
    }
}

// .text:0x00045D38 size:0x110 mapped:0x80684DCC
void fn_2_45D38(void) {
    s32 i;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *c = &lbl_2_bss_1A8248->characters[i];
        c->scoutFlagsAchieved = c->_7;
    }
}

// .text:0x00045BA4 size:0x194 mapped:0x80684C38
void fn_2_45BA4(void) {
    s32 i;
    s32 k;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *c = &lbl_2_bss_1A8248->characters[i];
        for (k = 0; k < STAR_MISSIONS_PER_CHARACTER; k++) {
            c->inGameMissionTracker[k].starMissionStatus = c->saveFileMissionTracker[k].starMissionStatus;
            c->inGameMissionTracker[k].shownOnPauseMenu = c->saveFileMissionTracker[k].shownOnPauseMenu;
        }
    }
}

// .text:0x00045A84 size:0x120 mapped:0x80684B18
BOOL fn_2_45A84(void) {
    s32 i;
    s32 k;
    BOOL found = FALSE;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *c = &lbl_2_bss_1A8248->characters[i];
        for (k = 0; k < STAR_MISSIONS_PER_CHARACTER; k++) {
            if (c->saveFileMissionTracker[k].starMissionStatus >= 0 &&
                c->inGameMissionTracker[k].starMissionStatus < 0) {
                found = TRUE;
                lbl_2_bss_1A8248->_4483[NUM_CHOOSABLE_CHARACTERS + i] = TRUE;
            }
        }
    }
    return found == TRUE;
}

// .text:0x00045978 size:0x10C mapped:0x80684A0C
void fn_2_45978(void) {
    s32 i;
    s32 k;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *c = &lbl_2_bss_1A8248->characters[i];
        c->_7 = c->scoutFlagsAchieved;
        for (k = 0; k < STAR_MISSIONS_PER_CHARACTER; k++) {
            c->saveFileMissionTracker[k].starMissionStatus = c->inGameMissionTracker[k].starMissionStatus;
            c->saveFileMissionTracker[k].shownOnPauseMenu = c->inGameMissionTracker[k].shownOnPauseMenu;
        }
        lbl_2_bss_1A8248->recruitedChar[i] = FALSE;
        lbl_2_bss_1A8248->_4483[i] = FALSE;
        lbl_2_bss_1A8248->_4483[NUM_CHOOSABLE_CHARACTERS + i] = FALSE;
    }
}

// .text:0x00045938 size:0x40 mapped:0x806849CC
BOOL fn_2_45938(s32 charIdx) {
    u8 *base = (u8 *)lbl_2_bss_1A8248;
    u8 captain = base[0x40F3 + charIdx * 10];
    u8 charID = challengeCaptainCharIDs[captain];
    return readChallengeSignedByte(charID * sizeof(ChallengeTrackingStruct) +
                         CHALLENGE_STATE_OFFSET(characters[0].recruitmentStatus)) ==
           CHALLENGE_RECRUITMENT_CD_NOT_RECRUITED;
}

// .text:0x00045810 size:0x128 mapped:0x806848A4
void fn_2_45810(void) {
    s32 i;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        lbl_2_bss_1A8248->charIsSuperstar[i] = FALSE;
    }
}

// .text:0x000454E8 size:0x328 mapped:0x8068457C
void fn_2_454E8(void) {
    s32 i;
    s32 n;
    s32 k;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        lbl_2_bss_1A8248->charIsSuperstar[i] = FALSE;
    }
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        CharStaticIndex *entry = &characterStaticIndexes[i];
        s32 count = 0;
        if (entry->hasOwnStarMissions == 1) {
            u8 row = entry->requirementRow;
            for (k = 0; k < STAR_MISSIONS_PER_CHARACTER; k++) {
                if (starMissionRequirementsTable[row][k].type != STAR_MISSION_TYPE_NONE) {
                    count++;
                }
            }
            entry->requirementRow = row;
        }
        if (fn_8006CDC0(i) == count && count != 0) {
            lbl_2_bss_1A8248->charIsSuperstar[i] = TRUE;
            for (n = 0; n < NUM_CHOOSABLE_CHARACTERS; n++) {
                if (characterStaticIndexes[n].trackerIdx == i) {
                    lbl_2_bss_1A8248->charIsSuperstar[n] = TRUE;
                }
            }
        }
    }
}

// .text:0x00045354 size:0x194 mapped:0x806843E8
void fn_2_45354(void) {
    s32 i;
    lbl_2_bss_1A824C[0x190000 + 0x7866] = 0;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        lbl_2_bss_1A824C[0x190000 + 0x7868 + i] = CHAR_ID_NONE;
    }
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        if ((s8)lbl_2_bss_1A8248->_4483[i] == 1) {
            lbl_2_bss_1A824C[0x190000 + 0x7868 + (s8)lbl_2_bss_1A824C[0x190000 + 0x7866]] = i;
            lbl_2_bss_1A824C[0x190000 + 0x7866]++;
        }
    }
}

// .text:0x00045204 size:0x150 mapped:0x80684298
void fn_2_45204(void) {
    s32 i;
    s32 k;
    CharStaticIndex *entry = characterStaticIndexes;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++, entry++) {
        s32 ret = fn_8006CDC0(i);
        s32 count = 0;
        if (entry->hasOwnStarMissions == 1) {
            u8 row = entry->requirementRow;
            count = 0;
            for (k = 0; k < STAR_MISSIONS_PER_CHARACTER; k++) {
                if (starMissionRequirementsTable[row][k].type != STAR_MISSION_TYPE_NONE) {
                    count++;
                }
            }
            entry->requirementRow = row;
        }
        if (ret == count && count != 0) {
            if (lbl_2_bss_1A8248->charIsSuperstar[i] == 0) {
                lbl_2_bss_1A8248->_4483[i] = TRUE;
            }
        }
    }
}

// .text:0x000450E4 size:0x120 mapped:0x80684178
void fn_2_450E4(void) {
    s32 i;
    s32 n;
    for (i = 0; i < (s8)lbl_2_bss_1A824C[0x190000 + 0x7866]; i++) {
        s8 charID = lbl_2_bss_1A824C[0x190000 + 0x7868 + i];
        lbl_2_bss_1A8248->charIsSuperstar[charID] = TRUE;
        for (n = 0; n < NUM_CHOOSABLE_CHARACTERS; n++) {
            if (characterStaticIndexes[n].trackerIdx == charID) {
                lbl_2_bss_1A8248->charIsSuperstar[n] = TRUE;
            }
        }
    }
}

// .text:0x00044F64 size:0x180 mapped:0x80683FF8
void fn_2_44F64(void) {
    s32 i;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        lbl_2_bss_1A8244[i] |= lbl_2_bss_1A8248->charIsSuperstar[i];
    }
}

// .text:0x00044F34 size:0x30 mapped:0x80683FC8
BOOL fn_2_44F34(s32 charID) {
    return readChallengeSignedByte(charID * sizeof(ChallengeTrackingStruct) +
                         CHALLENGE_STATE_OFFSET(characters[0].variantClassification)) <=
           CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_VARIANT;
}

// .text:0x00044F14 size:0x20 mapped:0x80683FA8
s8 fn_2_44F14(s32 charID) {
    u8 *base = (u8 *)lbl_2_bss_1A8248;
    return (s8)base[charID * sizeof(ChallengeTrackingStruct) +
                    CHALLENGE_STATE_OFFSET(characters[0].variantClassification)];
}
