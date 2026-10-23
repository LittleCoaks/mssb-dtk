#include "menus/text_4B1AC.h"

#include "game/challenge/challenge_state.h"
#include "challenge/challenge_progress.h"
#include "static/UnknownHomes_Static.h"

extern u8 superstarUnlocked[0x130];
extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A823C;
extern u8 *lbl_2_bss_1A8244;
extern ChallengeState *lbl_2_bss_1A8248;
extern s16 lbl_2_data_3ED4[];
extern s16 lbl_2_data_3EC8[];
extern s16 lbl_2_data_373C[];
extern u8 lbl_2_data_2E64[];
extern u8 lbl_2_data_3CC0[];
extern u8 challengeCaptainCharIDs[];
int rand(void);
s8 fn_2_68690(s32 idx);

#define WORK_BASE() (lbl_2_bss_1A824C + 0x190000)

// .text:0x0004B1AC size:0x124 mapped:0x8068A240
void fn_2_4B1AC(void) {
    s8 flag;
    s32 delta;
    s16 v;

    fn_2_4B2D0();

    flag = *(s8 *)(WORK_BASE() + 0x7843);
    if (flag == 0) {
        *(s16 *)(WORK_BASE() + 0x7778) = 0;
        *(s16 *)(WORK_BASE() + 0x7798) = 0;
    } else if (flag == 1) {
        u8 *ch = (u8 *)lbl_2_bss_1A8248;
        v = *(s16 *)(ch + 0x43BC);
        if (v == 1) {
            delta = -1;
        } else {
            delta = -v / 2;
        }
        *(s16 *)(ch + 0x43BE) = v;
        *(s16 *)((u8 *)lbl_2_bss_1A8248 + 0x43BC) += delta;
        if (*(s16 *)((u8 *)lbl_2_bss_1A8248 + 0x43BC) > 999) {
            *(s16 *)((u8 *)lbl_2_bss_1A8248 + 0x43BC) = 999;
        }
        if (*(s16 *)((u8 *)lbl_2_bss_1A8248 + 0x43BC) < 0) {
            *(s16 *)((u8 *)lbl_2_bss_1A8248 + 0x43BC) = 0;
        }
        *(s16 *)(WORK_BASE() + 0x777A) = delta;
        *(s16 *)(WORK_BASE() + 0x7798) = delta;
    } else if (flag == 2) {
        *(s16 *)(WORK_BASE() + 0x7796) = 0;
        *(s16 *)(WORK_BASE() + 0x7798) = 0;
    }

    challenge_leftoverTeammatesJoinBowserJr();
}

static inline void restoreChallengeProgress(void) {
    s32 character;
    int mission;

    for (character = 0; character < NUM_CHOOSABLE_CHARACTERS; character++) {
        lbl_2_bss_1A8248->characters[character].scoutFlagsAchieved = lbl_2_bss_1A8248->characters[character]._7;
    }
    for (character = 0; character < NUM_CHOOSABLE_CHARACTERS; character++) {
        ChallengeTrackingStruct *record = &lbl_2_bss_1A8248->characters[character];
        for (mission = 0; mission < STAR_MISSIONS_PER_CHARACTER; mission++) {
            record->inGameMissionTracker[mission].starMissionStatus = record->saveFileMissionTracker[mission].starMissionStatus;
            record->inGameMissionTracker[mission].shownOnPauseMenu = record->saveFileMissionTracker[mission].shownOnPauseMenu;
        }
    }
}

// .text:0x0004B2D0 size:0x1044 mapped:0x8068A364
void fn_2_4B2D0(void) {
    u8 result;
    s16 kind;
    u8 homeAway;
    u8 winner;
    GameInitVariables *settings = &g_d_GameSettings;

    *(s8 *)(WORK_BASE() + 0x7843) = 1;
    homeAway = settings->home_AwaySetting;
    winner = StatsScreenScores.winnerSlot;
    *((u8 *)lbl_2_bss_1A8248 + 0x4418) = settings->bJMatchRelated;
    if (homeAway == 0 && winner == 0) {
        result = 0;
    } else if (homeAway == 1 && winner == 0) {
        result = 0;
    } else if (homeAway == 0 && winner == 1) {
        result = 1;
    } else if (homeAway == 1 && winner == 1) {
        result = 1;
    } else {
        result = 2;
    }
    kind = *(s16 *)(lbl_2_bss_1A823C + 0x30);
    if (kind == 3) {
        if (settings->_13 != 0) {
            *(s8 *)(WORK_BASE() + 0x7843) = 1;
            WORK_BASE()[0x785B] = 1;
            WORK_BASE()[0x78F7] = 2;
            restoreChallengeProgress();
        } else {
            if (result == 0) {
                *(s8 *)(WORK_BASE() + 0x7843) = 0;
                WORK_BASE()[0x785B] = 0;
                WORK_BASE()[0x78F7] = 0;
            } else if (result == 1) {
                *(s8 *)(WORK_BASE() + 0x7843) = 1;
                WORK_BASE()[0x785B] = 1;
                WORK_BASE()[0x78F7] = 0;
            } else {
                *(s8 *)(WORK_BASE() + 0x7843) = 2;
                WORK_BASE()[0x785B] = 2;
                WORK_BASE()[0x78F7] = 0;
            }
            (*(u32 *)((u8 *)lbl_2_bss_1A8248 + 0x42EC))++;
        }
    } else if (kind == 5) {
        if (settings->_13 != 0) {
            *(s8 *)(WORK_BASE() + 0x7843) = 1;
            WORK_BASE()[0x785B] = 4;
            restoreChallengeProgress();
            WORK_BASE()[0x78F7] = 2;
        } else if (lbl_2_bss_1A8248->_4420[0] == 0 || lbl_2_bss_1A8248->_4420[0] == 3) {
            if (settings->_38 == 1) {
                *(s8 *)(WORK_BASE() + 0x7843) = 0;
                WORK_BASE()[0x785B] = 3;
                WORK_BASE()[0x78F7] = 1;
            } else {
                *(s8 *)(WORK_BASE() + 0x7843) = 1;
                WORK_BASE()[0x785B] = 4;
                WORK_BASE()[0x78F7] = 1;
            }
        } else {
            if (settings->_38 == 1) {
                *(s8 *)(WORK_BASE() + 0x7843) = 0;
                WORK_BASE()[0x785B] = 3;
                WORK_BASE()[0x78F7] = 1;
            } else if (settings->_38 == 0) {
                *(s8 *)(WORK_BASE() + 0x7843) = 2;
                WORK_BASE()[0x785B] = 5;
                WORK_BASE()[0x78F7] = 1;
            } else {
                *(s8 *)(WORK_BASE() + 0x7843) = 1;
                WORK_BASE()[0x785B] = 4;
                WORK_BASE()[0x78F7] = 1;
            }
        }
    } else if (kind == 4) {
        if (settings->_13 != 0) {
            *(s8 *)(WORK_BASE() + 0x7843) = 1;
            WORK_BASE()[0x785B] = 7;
            restoreChallengeProgress();
            WORK_BASE()[0x78F7] = 2;
        } else {
            if (result == 0) {
                *(s8 *)(WORK_BASE() + 0x7843) = 0;
                WORK_BASE()[0x785B] = 6;
                WORK_BASE()[0x78F7] = 0;
            } else if (result == 1) {
                *(s8 *)(WORK_BASE() + 0x7843) = 1;
                WORK_BASE()[0x785B] = 7;
                WORK_BASE()[0x78F7] = 1;
            } else if (result == 2) {
                *(s8 *)(WORK_BASE() + 0x7843) = 2;
                WORK_BASE()[0x785B] = 8;
                WORK_BASE()[0x78F7] = 1;
            }
            (*(u32 *)((u8 *)lbl_2_bss_1A8248 + 0x42EC))++;
        }
    } else {
        if (settings->_13 != 0) {
            *(s8 *)(WORK_BASE() + 0x7843) = 1;
            WORK_BASE()[0x785B] = 10;
            restoreChallengeProgress();
            WORK_BASE()[0x78F7] = 2;
        } else if (settings->_38 == 1) {
            *(s8 *)(WORK_BASE() + 0x7843) = 0;
            WORK_BASE()[0x78F7] = 1;
            WORK_BASE()[0x785B] = 9;
        } else if (settings->_38 == 0) {
            *(s8 *)(WORK_BASE() + 0x7843) = 2;
            WORK_BASE()[0x78F7] = 1;
            WORK_BASE()[0x785B] = 11;
        } else {
            *(s8 *)(WORK_BASE() + 0x7843) = 1;
            WORK_BASE()[0x78F7] = 1;
            WORK_BASE()[0x785B] = 10;
        }
    }
    if (*(s8 *)(WORK_BASE() + 0x7843) == 1 || *(s8 *)(WORK_BASE() + 0x7843) == 2) {
        *((u8 *)lbl_2_bss_1A8248 + 0x44F6) = TRUE;
    }
}

// .text:0x0004C314 size:0x58 mapped:0x8068B3A8
void fn_2_4C314(void) {
    u8 *flags = lbl_2_bss_1A8244;
    u8 *p = flags;
    BOOL allSet = TRUE;
    u8 i;

    for (i = 5; i > 0; i--) {
        if (p[0xC6] == 0) {
            allSet = FALSE;
        }
        if (p[0xC7] == 0) {
            allSet = FALSE;
        }
        if (p[0xC8] == 0) {
            allSet = FALSE;
        }
        p += 4;
    }
    flags[0xF4] = allSet;
}

// .text:0x0004C36C size:0x58 mapped:0x8068B400
void fn_2_4C36C(void) {
    s32 captain;
    s32 difficulty;
    u8 *p;

    ((u8 *)lbl_2_bss_1A8248)[0x4424] = TRUE;
    ((u8 *)lbl_2_bss_1A8248)[0x4425] = TRUE;
    ((u8 *)lbl_2_bss_1A8248)[0x441B] = FALSE;

    captain = ((u8 *)lbl_2_bss_1A8248)[0x441C];
    difficulty = ((u8 *)lbl_2_bss_1A8248)[0x4415];
    p = lbl_2_bss_1A8244 + captain * 4 + difficulty;
    p[0xC6] = TRUE;

    ((u8 *)lbl_2_bss_1A8248)[0x1606] = TRUE;
}

// .text:0x0004C3C4 size:0x14 mapped:0x8068B458
s16 fn_2_4C3C4(s32 index) {
    return lbl_2_data_3ED4[index];
}

// .text:0x0004C3D8 size:0x14 mapped:0x8068B46C
s16 fn_2_4C3D8(s32 index) {
    return lbl_2_data_3EC8[index];
}

#pragma dont_inline on
// .text:0x0004C3EC size:0x2BC mapped:0x8068B480
void fn_2_4C3EC(void) {
    s32 rosterUsed[6];
    u8 *superstar = superstarUnlocked + 0xF8;
    ChallengeState *challenge;
    s32 e;
    s32 k;
    s32 i;

    for (e = 0; e < 6; e++) {
        rosterUsed[e] = 0;
    }
    for (i = 0; i < 54; i++) {
        superstar[i] = 0;
    }

    for (e = 0; e < 6; e++) {
        if (rosterUsed[e] != 0) {
            for (k = 0; k < 9; k++) {
                superstar[Static_Stats_Tables.challengeRosters[e].charID[k]] = 1;
            }
        }
    }

    challenge = lbl_2_bss_1A8248;
    for (i = 0; i < 54; i++) {
        if (challenge->characters[i].variantClassification <= CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_VARIANT &&
            challenge->characters[i].recruitmentStatus == CHALLENGE_RECRUITMENT_CD_RECRUITED) {
            superstar[i] = 1;
        }
    }
}

#pragma dont_inline reset

static inline void configureChallengeShopItems(void) {
    GameInitVariables *settings = &g_d_GameSettings;
    s32 i;
    s32 j;
    s32 item;
    s16 *tab;
    ChallengeState *challenge;

    for (i = 0; i < CHALLENGE_SHOP_ITEM_COUNT; i++) {
        settings->challengeShopItemActive[i] = FALSE;
    }

    tab = lbl_2_data_373C;
    challenge = lbl_2_bss_1A8248;
    item = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (*tab == 0 && challenge->_43C2[item] != 0) {
                settings->challengeShopItemActive[item] = TRUE;
            }
            tab++;
            item++;
        }
    }

    {
        s8 slot = *((s8 *)lbl_2_bss_1A8248 + 0x444B);
        if (slot != -1) {
            settings->challengeShopItemActive[slot] = TRUE;
        }
    }
}

// .text:0x0004C6A8 size:0x174 mapped:0x8068B73C
void fn_2_4C6A8(void) {
    configureChallengeShopItems();
}

// .text:0x0004C81C size:0x1A8 mapped:0x8068B8B0
void fn_2_4C81C(void) {
    GameInitVariables *settings = &g_d_GameSettings;

    settings->GameModeSelected = GAME_TYPE_TOY_FIELD;
    settings->exhibitionMatchInd = FALSE;
    settings->_36 = lbl_2_bss_1A8248->captainCharID;
    settings->bJMatchInd = FALSE;
    settings->home_AwaySetting = 0;
    settings->challengeDifficulty = lbl_2_bss_1A8248->difficulty;
    settings->bJMatchRelated = *((u8 *)lbl_2_bss_1A8248 + 0x4418);

    configureChallengeShopItems();
}

// .text:0x0004C9C4 size:0x1D0 mapped:0x8068BA58
void fn_2_4C9C4(void) {
    GameInitVariables *settings = &g_d_GameSettings;

    settings->GameModeSelected = GAME_TYPE_MINIGAMES;
    settings->exhibitionMatchInd = FALSE;
    settings->_35 = 0;
    settings->_33 = lbl_2_data_2E64[*((u8 *)lbl_2_bss_1A8248 + 0x4420)];
    settings->_36 = lbl_2_bss_1A8248->captainCharID;
    settings->challengeDifficulty = lbl_2_bss_1A8248->difficulty;
    settings->bJMatchRelated = *((u8 *)lbl_2_bss_1A8248 + 0x4418);
    settings->_3A = *(u8 *)(WORK_BASE() + 0x78F1);

    configureChallengeShopItems();
}

// .text:0x0004CB94 size:0x19C mapped:0x8068BC28
void fn_2_4CB94(void) {
    GameInitVariables *settings = &g_d_GameSettings;

    settings->GameModeSelected = GAME_TYPE_TOY_FIELD;
    settings->exhibitionMatchInd = FALSE;
    settings->_36 = lbl_2_bss_1A8248->captainCharID;
    settings->bJMatchInd = TRUE;
    settings->bJMatchRelated = *((u8 *)lbl_2_bss_1A8248 + 0x4418);

    configureChallengeShopItems();
}

// .text:0x0004CD30 size:0x1B0 mapped:0x8068BDC4
void fn_2_4CD30(void) {
    GameInitVariables *settings = &g_d_GameSettings;

    settings->GameModeSelected = GAME_TYPE_MINIGAMES;
    settings->exhibitionMatchInd = FALSE;
    settings->_33 = 6;
    settings->_35 = 0;
    settings->_36 = lbl_2_bss_1A8248->captainCharID;
    settings->challengeDifficulty = lbl_2_bss_1A8248->difficulty;
    settings->bJMatchInd = TRUE;
    settings->bJMatchRelated = *((u8 *)lbl_2_bss_1A8248 + 0x4418);

    configureChallengeShopItems();
}

// .text:0x0004CEE0 size:0x2B4 mapped:0x8068BF74
void fn_2_4CEE0(void) {
    GameInitVariables *settings = &g_d_GameSettings;
    s32 r;
    s32 sign;
    s32 a;

    settings->exhibitionMatchInd = FALSE;
    settings->bJMatchInd = TRUE;

    r = rand();
    sign = (u32)r >> 31;
    settings->home_AwaySetting = ((r & 1) ^ sign) - sign;

    settings->bJMatchRelated = *((u8 *)lbl_2_bss_1A8248 + 0x4418);
    settings->challengeDifficulty = lbl_2_bss_1A8248->difficulty;

    configureChallengeShopItems();

    a = *((u8 *)lbl_2_bss_1A8248 + 0x40F0 + lbl_2_bss_1A8248->_16C2 * 10);
    if (a < 6) {
        settings->StadiumID = lbl_2_data_3CC0[a];
        settings->miniGameStadiumIndicator = 0;
    } else if (lbl_2_bss_1A8248->_16C0 == 3) {
        if (a == 0) {
            settings->StadiumID = STADIUM_ID_MARIO_STADIUM;
        } else if (a == 1) {
            settings->StadiumID = STADIUM_ID_BOWSERS_CASTLE;
        } else {
            settings->StadiumID = STADIUM_ID_PEACH_GARDEN;
        }
        settings->miniGameStadiumIndicator = 0;
    } else {
        if (a == 2) {
            settings->StadiumID = STADIUM_ID_WARIO_PALACE;
        } else if (a == 3) {
            settings->StadiumID = STADIUM_ID_YOHSI_PARK;
        } else {
            settings->StadiumID = STADIUM_ID_DK_JUNGLE;
        }
        settings->miniGameStadiumIndicator = 0;
    }
}

// .text:0x0004D194 size:0x1E4 mapped:0x8068C228
void fn_2_4D194(void) {
    GameInitVariables *settings = &g_d_GameSettings;

    settings->exhibitionMatchInd = FALSE;
    settings->bJMatchInd = FALSE;
    settings->miniGameStadiumIndicator = 0;
    settings->challengeDifficulty = lbl_2_bss_1A8248->difficulty;

    if (lbl_2_bss_1A8248->_44EF == 1) {
        settings->home_AwaySetting = 0;
        settings->StadiumID = STADIUM_ID_BOWSERS_CASTLE;
    } else {
        settings->home_AwaySetting = 0;
        settings->StadiumID = lbl_2_data_3CC0[lbl_2_bss_1A8248->opponentCaptain];
    }

    settings->bJMatchRelated = *((u8 *)lbl_2_bss_1A8248 + 0x4418);

    configureChallengeShopItems();
}

// .text:0x0004D378 size:0x304 mapped:0x8068C40C
void fn_2_4D378(void) {
    s32 i;
    s32 j;

    *(s8 *)(lbl_2_bss_1A824C + 0x190000 + 0x7843) = -1;

    lbl_2_bss_1A8248->opponentCaptain = *((u8 *)lbl_2_bss_1A8248 + 0x40F3 + lbl_2_bss_1A8248->_16C2 * 10);
    lbl_2_bss_1A8248->opponentCaptainCharID = challengeCaptainCharIDs[lbl_2_bss_1A8248->opponentCaptain];

    fn_2_4C3EC();

    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        lbl_2_bss_1A8248->characters[i]._7 = lbl_2_bss_1A8248->characters[i].scoutFlagsAchieved;
    }

    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *record = &lbl_2_bss_1A8248->characters[i];
        for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
            record->saveFileMissionTracker[j].starMissionStatus = record->inGameMissionTracker[j].starMissionStatus;
            record->saveFileMissionTracker[j].shownOnPauseMenu = record->inGameMissionTracker[j].shownOnPauseMenu;
        }
    }
}

// .text:0x0004D67C size:0x2E4 mapped:0x8068C710
void fn_2_4D67C(void) {
    s32 i;
    s32 j;
    s8 pick;

    *(s8 *)(lbl_2_bss_1A824C + 0x190000 + 0x7843) = -1;

    pick = fn_2_68690(0);
    lbl_2_bss_1A8248->opponentCaptain = pick;
    *((u8 *)lbl_2_bss_1A8248 + 0x4420) = pick - 2;

    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        lbl_2_bss_1A8248->characters[i]._7 = lbl_2_bss_1A8248->characters[i].scoutFlagsAchieved;
    }

    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        ChallengeTrackingStruct *record = &lbl_2_bss_1A8248->characters[i];
        for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
            record->saveFileMissionTracker[j].starMissionStatus = record->inGameMissionTracker[j].starMissionStatus;
            record->saveFileMissionTracker[j].shownOnPauseMenu = record->inGameMissionTracker[j].shownOnPauseMenu;
        }
    }
}
