#include "menus/text_4B1AC.h"

#include "game/challenge/challenge_state.h"
#include "challenge/challenge_progress.h"

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8244;
extern ChallengeState *lbl_2_bss_1A8248;
extern s16 lbl_2_data_3ED4[];
extern s16 lbl_2_data_3EC8[];

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
        v = *(s16 *)((u8 *)lbl_2_bss_1A8248 + 0x43BC);
        if (v == 1) {
            delta = -1;
        } else {
            delta = -v / 2;
        }
        *(s16 *)((u8 *)lbl_2_bss_1A8248 + 0x43BE) = v;
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

// .text:0x0004C3EC size:0x2BC mapped:0x8068B480
void fn_2_4C3EC(void) {
    return;
}

// .text:0x0004C6A8 size:0x174 mapped:0x8068B73C
void fn_2_4C6A8(void) {
    return;
}

// .text:0x0004C81C size:0x1A8 mapped:0x8068B8B0
void fn_2_4C81C(void) {
    return;
}

// .text:0x0004C9C4 size:0x1D0 mapped:0x8068BA58
void fn_2_4C9C4(void) {
    return;
}

// .text:0x0004CB94 size:0x19C mapped:0x8068BC28
void fn_2_4CB94(void) {
    return;
}

// .text:0x0004CD30 size:0x1B0 mapped:0x8068BDC4
void fn_2_4CD30(void) {
    return;
}

// .text:0x0004CEE0 size:0x2B4 mapped:0x8068BF74
void fn_2_4CEE0(void) {
    return;
}

// .text:0x0004D194 size:0x1E4 mapped:0x8068C228
void fn_2_4D194(void) {
    return;
}

// .text:0x0004D378 size:0x304 mapped:0x8068C40C
void fn_2_4D378(void) {
    return;
}

// .text:0x0004D67C size:0x2E4 mapped:0x8068C710
void fn_2_4D67C(void) {
    return;
}
