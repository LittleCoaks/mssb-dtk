#include "menus/text_4B1AC.h"

#include "game/challenge/challenge_state.h"
#include "challenge/challenge_progress.h"
#include "static/UnknownHomes_Static.h"

extern u8 superstarUnlocked[0x130];
extern u8 *lbl_2_bss_1A824C;
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

// .text:0x0004B2D0 size:0x1044 mapped:0x8068A364
void fn_2_4B2D0(void) {
    return;
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

// .text:0x0004C6A8 size:0x174 mapped:0x8068B73C
void fn_2_4C6A8(void) {
    s16 *tab = lbl_2_data_373C;
    s32 i;
    s32 j;

    for (i = 0; i < 20; i++) {
        ((u8 *)&g_d_GameSettings)[0x3C + i] = 0;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (tab[i * 5 + j] == 0 && *((u8 *)lbl_2_bss_1A8248 + 0x43C2 + i * 5 + j) != 0) {
                ((u8 *)&g_d_GameSettings)[0x3C + i * 5 + j] = 1;
            }
        }
    }

    {
        s8 slot = *((s8 *)lbl_2_bss_1A8248 + 0x444B);
        if (slot != -1) {
            ((u8 *)&g_d_GameSettings)[0x3C + slot] = 1;
        }
    }
}

// .text:0x0004C81C size:0x1A8 mapped:0x8068B8B0
void fn_2_4C81C(void) {
    s32 i;
    s32 j;
    s16 *tab = lbl_2_data_373C;

    ((u8 *)&g_d_GameSettings)[0x7] = 6;
    ((u8 *)&g_d_GameSettings)[0x8] = 0;
    ((u8 *)&g_d_GameSettings)[0xE] = 0;
    ((u8 *)&g_d_GameSettings)[0x32] = *((u8 *)lbl_2_bss_1A8248 + 0x4418);
    ((u8 *)&g_d_GameSettings)[0x36] = lbl_2_bss_1A8248->captainCharID;
    ((u8 *)&g_d_GameSettings)[0x37] = lbl_2_bss_1A8248->difficulty;
    ((u8 *)&g_d_GameSettings)[0x39] = 0;

    for (i = 0; i < 20; i++) {
        ((u8 *)&g_d_GameSettings)[0x3C + i] = 0;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (tab[i * 5 + j] == 0 && *((u8 *)lbl_2_bss_1A8248 + 0x43C2 + i * 5 + j) != 0) {
                ((u8 *)&g_d_GameSettings)[0x3C + i * 5 + j] = 1;
            }
        }
    }

    {
        s8 slot = *((s8 *)lbl_2_bss_1A8248 + 0x444B);
        if (slot != -1) {
            ((u8 *)&g_d_GameSettings)[0x3C + slot] = 1;
        }
    }
}

// .text:0x0004C9C4 size:0x1D0 mapped:0x8068BA58
void fn_2_4C9C4(void) {
    s32 i;
    s32 j;
    s16 *tab = lbl_2_data_373C;

    ((u8 *)&g_d_GameSettings)[0x7] = 7;
    ((u8 *)&g_d_GameSettings)[0x8] = 0;
    ((u8 *)&g_d_GameSettings)[0x35] = 0;
    ((u8 *)&g_d_GameSettings)[0x33] = lbl_2_data_2E64[*((u8 *)lbl_2_bss_1A8248 + 0x4420)];
    ((u8 *)&g_d_GameSettings)[0x36] = lbl_2_bss_1A8248->captainCharID;
    ((u8 *)&g_d_GameSettings)[0x37] = lbl_2_bss_1A8248->difficulty;
    ((u8 *)&g_d_GameSettings)[0x32] = *((u8 *)lbl_2_bss_1A8248 + 0x4418);
    ((u8 *)&g_d_GameSettings)[0x3A] = *(u8 *)(WORK_BASE() + 0x78F1);

    for (i = 0; i < 20; i++) {
        ((u8 *)&g_d_GameSettings)[0x3C + i] = 0;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (tab[i * 5 + j] == 0 && *((u8 *)lbl_2_bss_1A8248 + 0x43C2 + i * 5 + j) != 0) {
                ((u8 *)&g_d_GameSettings)[0x3C + i * 5 + j] = 1;
            }
        }
    }

    {
        s8 slot = *((s8 *)lbl_2_bss_1A8248 + 0x444B);
        if (slot != -1) {
            ((u8 *)&g_d_GameSettings)[0x3C + slot] = 1;
        }
    }
}

// .text:0x0004CB94 size:0x19C mapped:0x8068BC28
void fn_2_4CB94(void) {
    s32 i;
    s32 j;
    s16 *tab = lbl_2_data_373C;

    ((u8 *)&g_d_GameSettings)[0x7] = 6;
    ((u8 *)&g_d_GameSettings)[0x8] = 0;
    ((u8 *)&g_d_GameSettings)[0x36] = lbl_2_bss_1A8248->captainCharID;
    ((u8 *)&g_d_GameSettings)[0x39] = 1;
    ((u8 *)&g_d_GameSettings)[0x32] = *((u8 *)lbl_2_bss_1A8248 + 0x4418);

    for (i = 0; i < 20; i++) {
        ((u8 *)&g_d_GameSettings)[0x3C + i] = 0;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (tab[i * 5 + j] == 0 && *((u8 *)lbl_2_bss_1A8248 + 0x43C2 + i * 5 + j) != 0) {
                ((u8 *)&g_d_GameSettings)[0x3C + i * 5 + j] = 1;
            }
        }
    }

    {
        s8 slot = *((s8 *)lbl_2_bss_1A8248 + 0x444B);
        if (slot != -1) {
            ((u8 *)&g_d_GameSettings)[0x3C + slot] = 1;
        }
    }
}

// .text:0x0004CD30 size:0x1B0 mapped:0x8068BDC4
void fn_2_4CD30(void) {
    s32 i;
    s32 j;
    s16 *tab = lbl_2_data_373C;

    ((u8 *)&g_d_GameSettings)[0x7] = 7;
    ((u8 *)&g_d_GameSettings)[0x8] = 0;
    ((u8 *)&g_d_GameSettings)[0x33] = 6;
    ((u8 *)&g_d_GameSettings)[0x35] = 0;
    ((u8 *)&g_d_GameSettings)[0x36] = lbl_2_bss_1A8248->captainCharID;
    ((u8 *)&g_d_GameSettings)[0x37] = lbl_2_bss_1A8248->difficulty;
    ((u8 *)&g_d_GameSettings)[0x39] = 1;
    ((u8 *)&g_d_GameSettings)[0x32] = *((u8 *)lbl_2_bss_1A8248 + 0x4418);

    for (i = 0; i < 20; i++) {
        ((u8 *)&g_d_GameSettings)[0x3C + i] = 0;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (tab[i * 5 + j] == 0 && *((u8 *)lbl_2_bss_1A8248 + 0x43C2 + i * 5 + j) != 0) {
                ((u8 *)&g_d_GameSettings)[0x3C + i * 5 + j] = 1;
            }
        }
    }

    {
        s8 slot = *((s8 *)lbl_2_bss_1A8248 + 0x444B);
        if (slot != -1) {
            ((u8 *)&g_d_GameSettings)[0x3C + slot] = 1;
        }
    }
}

// .text:0x0004CEE0 size:0x2B4 mapped:0x8068BF74
void fn_2_4CEE0(void) {
    s32 i;
    s32 j;
    s32 r;
    s32 sign;
    s32 a;
    s16 *tab = lbl_2_data_373C;

    ((u8 *)&g_d_GameSettings)[0x8] = 0;
    ((u8 *)&g_d_GameSettings)[0x39] = 1;

    r = rand();
    sign = (u32)r >> 31;
    ((u8 *)&g_d_GameSettings)[0xE] = ((r & 1) ^ sign) - sign;

    ((u8 *)&g_d_GameSettings)[0x32] = *((u8 *)lbl_2_bss_1A8248 + 0x4418);
    ((u8 *)&g_d_GameSettings)[0x37] = lbl_2_bss_1A8248->difficulty;

    for (i = 0; i < 20; i++) {
        ((u8 *)&g_d_GameSettings)[0x3C + i] = 0;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (tab[i * 5 + j] == 0 && *((u8 *)lbl_2_bss_1A8248 + 0x43C2 + i * 5 + j) != 0) {
                ((u8 *)&g_d_GameSettings)[0x3C + i * 5 + j] = 1;
            }
        }
    }

    {
        s8 slot = *((s8 *)lbl_2_bss_1A8248 + 0x444B);
        if (slot != -1) {
            ((u8 *)&g_d_GameSettings)[0x3C + slot] = 1;
        }
    }

    a = *((u8 *)lbl_2_bss_1A8248 + 0x40F0 + lbl_2_bss_1A8248->_16C2 * 10);
    if (a < 6) {
        ((u8 *)&g_d_GameSettings)[0x9] = lbl_2_data_3CC0[a];
        ((u8 *)&g_d_GameSettings)[0xA] = 0;
    } else if (lbl_2_bss_1A8248->_16C0 == 3) {
        if (a == 0) {
            ((u8 *)&g_d_GameSettings)[0x9] = 0;
        } else if (a == 1) {
            ((u8 *)&g_d_GameSettings)[0x9] = 1;
        } else {
            ((u8 *)&g_d_GameSettings)[0x9] = 4;
        }
        ((u8 *)&g_d_GameSettings)[0xA] = 0;
    } else {
        if (a == 2) {
            ((u8 *)&g_d_GameSettings)[0x9] = 2;
        } else if (a == 3) {
            ((u8 *)&g_d_GameSettings)[0x9] = 3;
        } else {
            ((u8 *)&g_d_GameSettings)[0x9] = 5;
        }
        ((u8 *)&g_d_GameSettings)[0xA] = 0;
    }
}

// .text:0x0004D194 size:0x1E4 mapped:0x8068C228
void fn_2_4D194(void) {
    s32 i;
    s32 j;
    s16 *tab = lbl_2_data_373C;

    ((u8 *)&g_d_GameSettings)[0x8] = 0;
    ((u8 *)&g_d_GameSettings)[0x39] = 0;
    ((u8 *)&g_d_GameSettings)[0xA] = 0;
    ((u8 *)&g_d_GameSettings)[0x37] = lbl_2_bss_1A8248->difficulty;

    if (lbl_2_bss_1A8248->_44EF == 1) {
        ((u8 *)&g_d_GameSettings)[0xE] = 0;
        ((u8 *)&g_d_GameSettings)[0x9] = 1;
    } else {
        ((u8 *)&g_d_GameSettings)[0xE] = 0;
        ((u8 *)&g_d_GameSettings)[0x9] = lbl_2_data_3CC0[lbl_2_bss_1A8248->opponentCaptain];
    }

    ((u8 *)&g_d_GameSettings)[0x32] = *((u8 *)lbl_2_bss_1A8248 + 0x4418);

    for (i = 0; i < 20; i++) {
        ((u8 *)&g_d_GameSettings)[0x3C + i] = 0;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (tab[i * 5 + j] == 0 && *((u8 *)lbl_2_bss_1A8248 + 0x43C2 + i * 5 + j) != 0) {
                ((u8 *)&g_d_GameSettings)[0x3C + i * 5 + j] = 1;
            }
        }
    }

    {
        s8 slot = *((s8 *)lbl_2_bss_1A8248 + 0x444B);
        if (slot != -1) {
            ((u8 *)&g_d_GameSettings)[0x3C + slot] = 1;
        }
    }
}

// .text:0x0004D378 size:0x304 mapped:0x8068C40C
void fn_2_4D378(void) {
    s32 i;
    s32 j;
    ChallengeState *ch;

    *(s8 *)(lbl_2_bss_1A824C + 0x190000 + 0x7843) = -1;

    ch = lbl_2_bss_1A8248;
    ch->opponentCaptain = *((u8 *)ch + 0x40F3 + ch->_16C2 * 10);
    ch->opponentCaptainCharID = challengeCaptainCharIDs[ch->opponentCaptain];

    fn_2_4C3EC();

    for (i = 0; i < 54; i++) {
        ch->characters[i]._7 = ch->characters[i].scoutFlagsAchieved;
    }

    for (i = 0; i < 54; i++) {
        for (j = 0; j < 20; j++) {
            *((u8 *)&ch->characters[i] + 0x1D + j) = *((u8 *)&ch->characters[i] + 0x9 + j);
        }
    }
}

// .text:0x0004D67C size:0x2E4 mapped:0x8068C710
void fn_2_4D67C(void) {
    s32 i;
    s32 j;
    s8 pick;
    ChallengeState *ch;

    *(s8 *)(lbl_2_bss_1A824C + 0x190000 + 0x7843) = -1;

    pick = fn_2_68690(0);
    ch = lbl_2_bss_1A8248;
    ch->opponentCaptain = pick;
    *((u8 *)ch + 0x4420) = pick - 2;

    for (i = 0; i < 54; i++) {
        ch->characters[i]._7 = ch->characters[i].scoutFlagsAchieved;
    }

    for (i = 0; i < 54; i++) {
        for (j = 0; j < 20; j++) {
            *((u8 *)&ch->characters[i] + 0x1D + j) = *((u8 *)&ch->characters[i] + 0x9 + j);
        }
    }
}
