#include "menus/text_3E38C.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/mb_subfunc.h"
#include "game/challenge/challenge_state.h"
#include "menus/text_1B1BC.h"
#include "menus/text_94854.h"
#include "menus/rep_10C0.h"
#include "menus/rep_1028.h"
#include "menus/text_92394.h"
#include "menus/text_44F14.h"
#include "menus/text_71EC4.h"
#include "menus/rep_0F60.h"
#include "static/UnknownHomes_Static.h"

extern ChallengeState *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_data_3198[];
extern s16 lbl_2_data_3CE8[];

#define WORK_U8(off) (*(u8 *)(lbl_2_bss_1A824C + 0x190000 + (off)))
#define WORK_S16(off) (*(s16 *)(lbl_2_bss_1A824C + 0x190000 + (off)))
#define WORK_S8(off) (*(s8 *)(lbl_2_bss_1A824C + 0x190000 + (off)))
#define WORK_U32(off) (*(u32 *)(lbl_2_bss_1A824C + 0x190000 + (off)))
#define ATBAT_BUTTON_INPUT(idx) ((lbl_803C77B8_s *)((u8 *)&AtBat_ButtonInput1 + (idx) * 0x20))

u32 fn_80062890(u32 id);

typedef struct TextSceneNode {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ struct DrawingSceneStruct *prev;
    /* 0x08 */ struct DrawingSceneStruct *next;
    /* 0x0C */ struct DrawingSceneStruct *currentDrawingItem;
    /* 0x10 */ s16 state;
    /* 0x14 */ s16 timer;
    /* 0x16 */ s16 frame;
    /* 0x28 */ s8 phase;
} TextSceneNode;

void fn_2_3E38C(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;

    if ((u32)phase > 14) {
        /* out of range: skip the state machine */
    } else if (phase == 0) {
        fn_2_1C490();
        node->timer = 30;
        challenge = lbl_2_bss_1A8248;
        if (challenge->stage >= 4 && challenge->_4446[0] == 0 && challenge->captain != CHALLENGE_CAPTAIN_BOWSER) {
            challenge->_4446[0] = 1;
            node->phase = 1;
        } else {
            node->phase = 14;
        }
    } else if (phase == 1) {
        if (!fn_8006862C(0x78, 0)) {
            lbl_2_bss_1A8248->_44F2 = 4;
            fn_2_94854(0xb);
            fn_2_9461C(0xc);
            fn_2_94604(1);
            fn_2_94634(1);
            node->timer = 60;
            node->phase = 2;
            fn_2_8F758(0x18, 2);
        }
    } else if (phase == 2) {
        if (node->timer-- == 0) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        lbl_2_bss_1A8234[0x162679] = 1;
        node->timer = 200;
        node->phase = 4;
    } else if (phase == 4) {
        if (node->timer-- == 0) {
            node->phase = 5;
        }
    } else if (phase == 5) {
        node->timer = 8;
        node->phase = 6;
    } else if (phase == 6) {
        if (node->timer-- == 0) {
            node->phase = 7;
        }
    } else if (phase == 7) {
        challenge = lbl_2_bss_1A8248;
        challenge->_4423[0x4439 - 0x4423] = 0;
        fn_2_92654(8, 0);
        fn_2_90428(9);
        fn_2_92654(9, 0xb);
        fn_2_46C2C(0, (Vec *)(lbl_2_data_3198 + 0xb4));
        challenge->_4416[0x441A - 0x4416] = 0;
        challenge->_40EE[0x428E - 0x40EE] = 0;
        fn_80062890(5);
        node->timer = 80;
        node->phase = 8;
    } else if (phase == 8) {
        if (node->timer == 70) {
            fn_2_46C2C(0, (Vec *)(lbl_2_data_3198 + 0xb4));
        }
        if (node->timer-- == 0) {
            node->phase = 9;
        }
    } else if (phase == 9) {
        fn_2_92654(0x18, 0xf);
        node->timer = 200;
        node->phase = 10;
    } else if (phase == 10) {
        if (node->timer-- == 0) {
            node->phase = 11;
        }
    } else if (phase == 11) {
        if (!fn_80068514(0x78, 0x7f)) {
            node->phase = 12;
        }
    } else if (phase == 12) {
        fn_2_94854(0xb);
        fn_2_9461C(0);
        fn_2_94604(1);
        fn_2_94634(1);
        node->timer = 60;
        node->phase = 13;
    } else if (phase == 13) {
        if (node->timer-- == 0) {
            lbl_2_bss_1A8248->_44F2 = 0;
            node->phase = 14;
        }
    } else if (phase == 14) {
        fn_2_1C41C();
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    node->frame++;
    if (node->frame == 0xA6) {
        *(u32 *)(lbl_2_bss_1A824C + 0x1976A8) = fn_80062890(0x3A);
    } else if (node->frame == 0xF6) {
        *(u32 *)(lbl_2_bss_1A824C + 0x1976A8) = fn_80062890(0x3B);
    } else if (node->frame == 0x146) {
        *(u32 *)(lbl_2_bss_1A824C + 0x1976A8) = fn_80062890(0x3E);
    } else if (node->frame == 0x150 || node->frame == 0x204) {
        /* nothing */
    } else if (node->frame == 0x13C) {
        *(u32 *)(lbl_2_bss_1A824C + 0x1976A8) = fn_80062890(0x3C);
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003E7EC size:0x12C mapped:0x8067D880
void fn_2_3E7EC(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 1;
        node->phase = 1;
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->timer = 60;
            fn_2_72054(0, 10);
            challenge = lbl_2_bss_1A8248;
            fn_2_72054(challenge->opponentCaptain, 9);
            node->phase = 2;
        }
    } else if (phase == 2) {
        if (fn_2_8CC88(0)) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003E918 size:0x12C mapped:0x8067D9AC
void fn_2_3E918(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 1;
        node->phase = 1;
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->timer = 60;
            fn_2_72054(0, 11);
            challenge = lbl_2_bss_1A8248;
            fn_2_72054(challenge->opponentCaptain, 11);
            node->phase = 2;
        }
    } else if (phase == 2) {
        if (fn_2_8CC88(0)) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003EA44 size:0x164 mapped:0x8067DAD8
void fn_2_3EA44(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 1;
        node->phase = 1;
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->timer = 360;
            fn_2_72054(0, 9);
            challenge = lbl_2_bss_1A8248;
            fn_2_72054(challenge->opponentCaptain, 10);
            node->phase = 2;
        }
    } else if (phase == 2) {
        if (fn_2_8CC88(0)) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        challenge = lbl_2_bss_1A8248;
        if (challenge->captain == CHALLENGE_CAPTAIN_BOWSER) {
            *(u8 *)((u8 *)challenge + challenge->_16C2 * 10 + 0x40F1) = 3;
        }
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003EBA8 size:0x118 mapped:0x8067DC3C
void fn_2_3EBA8(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 1;
        node->phase = 1;
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->timer = 60;
            fn_2_72054(0, 10);
            node->phase = 2;
        }
    } else if (phase == 2) {
        if (node->timer-- == 0) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003ECC0 size:0x118 mapped:0x8067DD54
void fn_2_3ECC0(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 1;
        node->phase = 1;
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->timer = 60;
            fn_2_72054(0, 10);
            node->phase = 2;
        }
    } else if (phase == 2) {
        if (node->timer-- == 0) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003EDD8 size:0x118 mapped:0x8067DE6C
void fn_2_3EDD8(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 1;
        node->phase = 1;
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->timer = 60;
            fn_2_72054(0, 9);
            node->phase = 2;
        }
    } else if (phase == 2) {
        if (node->timer-- == 0) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003EEF0 size:0x114 mapped:0x8067DF84
void fn_2_3EEF0(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 1;
        node->phase = 1;
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->timer = 60;
            fn_2_72054(0, 11);
            node->phase = 2;
        }
    } else if (phase == 2) {
        if (fn_2_8CC88(0)) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003F004 size:0x184 mapped:0x8067E098
void fn_2_3F004(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 1;
        node->phase = 1;
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->timer = 80;
            fn_2_72054(0, 10);
            node->phase = 2;
        }
    } else if (phase == 2) {
        challenge = lbl_2_bss_1A8248;
        if ((challenge->captain == CHALLENGE_CAPTAIN_DK && challenge->opponentCaptain == CHALLENGE_CAPTAIN_PEACH && challenge->_16C2 == 0xB)
            || (challenge->captain == CHALLENGE_CAPTAIN_DK && challenge->opponentCaptain == CHALLENGE_CAPTAIN_BOWSER && challenge->_16C2 == 0x2A)) {
            if (node->timer-- == 0) {
                node->phase = 3;
            }
        } else if (fn_2_8CC88(0)) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003F188 size:0x114 mapped:0x8067E21C
void fn_2_3F188(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 1;
        node->phase = 1;
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->timer = 60;
            fn_2_72054(0, 9);
            node->phase = 2;
        }
    } else if (phase == 2) {
        if (fn_2_8CC88(0)) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003F29C size:0x1B0 mapped:0x8067E330
void fn_2_3F29C(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;

    if (phase == 0) {
        lbl_2_bss_1A8234[0x1627B9] = 1;
        node->timer = 10;
        node->phase = 1;
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            challenge = lbl_2_bss_1A8248;
            challenge->_4423[0x4439 - 0x4423] = 0;
            fn_2_92654(8, 0);
            fn_2_90428(9);
            fn_2_92654(9, 0xb);
            fn_2_46C2C(0, (Vec *)(lbl_2_data_3198 + 0xb4));
            challenge->_4416[0x441A - 0x4416] = 0;
            challenge->_40EE[0x428E - 0x40EE] = 0;
            fn_80062890(5);
            node->timer = 80;
            node->phase = 2;
        }
    } else if (phase == 2) {
        if (node->timer == 70) {
            fn_2_46C2C(0, (Vec *)(lbl_2_data_3198 + 0xb4));
        }
        if (node->timer-- == 0) {
            node->phase = 3;
        }
    } else if (phase == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003F44C size:0x110 mapped:0x8067E4E0
void fn_2_3F44C(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 40;
        challenge = lbl_2_bss_1A8248;
        if (challenge->_4416[0x4418 - 0x4416] != 0) {
            fn_80062890(8);
            node->phase = 1;
        } else {
            node->phase = 2;
        }
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->phase = 2;
        }
    } else if (phase == 2) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003F55C size:0x110 mapped:0x8067E5F0
void fn_2_3F55C(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;

    if (phase == 0) {
        node->timer = 40;
        challenge = lbl_2_bss_1A8248;
        if (challenge->_4416[0x4418 - 0x4416] >= 5) {
            node->phase = 2;
        } else {
            fn_80062890(7);
            node->phase = 1;
        }
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->phase = 2;
        }
    } else if (phase == 2) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003F66C size:0x3A8 mapped:0x8067E700
void fn_2_3F66C(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;
    s16 v;

    if (phase == 0) {
        challenge = lbl_2_bss_1A8248;
        WORK_S16(0x7740) = 0;
        WORK_S16(0x7734) = *(s16 *)((u8 *)challenge + 0x43BC);
        v = *(s16 *)((u8 *)challenge + 0x43BE);
        WORK_S16(0x773C) = v;
        WORK_S16(0x7736) = v;
        WORK_S16(0x773A) = 0;
        WORK_S16(0x7738) = WORK_S16(0x7734) + (WORK_S16(0x7736) - WORK_S16(0x7734)) / 2;
        node->phase = 1;
    } else if (phase == 1) {
        WORK_S16(0x773A) = WORK_S16(0x773A) << 1;
        if (WORK_S16(0x773A) == 0) {
            WORK_S16(0x773A) = WORK_S16(0x773A) + 1;
        }
        WORK_S16(0x7736) = WORK_S16(0x7736) - WORK_S16(0x773A);
        WORK_S16(0x773A) = WORK_S16(0x773A) + 1;
        lbl_2_bss_1A8234[0x16281B] = 1;
        WORK_U32(0x76A8) = fn_80062890(0x37);

        v = WORK_S16(0x7736);
        if (v > WORK_S16(0x7734)) {
            if (v <= WORK_S16(0x7738)) {
                WORK_S16(0x7736) = WORK_S16(0x7738);
                node->phase = 2;
            }
        } else {
            WORK_S16(0x7736) = WORK_S16(0x7734);
            node->phase = 4;
        }
        if (ATBAT_BUTTON_INPUT((s8)WORK_U8(0x7863))->_02 & 0x100) {
            WORK_S16(0x7736) = WORK_S16(0x7734);
            node->phase = 4;
        }
    } else if (phase == 2) {
        WORK_S16(0x7736) = WORK_S16(0x7736) + (WORK_S16(0x7734) - WORK_S16(0x7736)) / 40;
        WORK_S16(0x7736) = WORK_S16(0x7736) - 1;
        WORK_U32(0x76A8) = fn_80062890(0x37);
        lbl_2_bss_1A8234[0x16281B] = 1;

        v = WORK_S16(0x7736);
        if (v > WORK_S16(0x7734)) {
            if (ATBAT_BUTTON_INPUT((s8)WORK_U8(0x7863))->_02 & 0x100) {
                WORK_S16(0x7736) = WORK_S16(0x7734);
                node->phase = 4;
            }
        } else {
            WORK_S16(0x7736) = WORK_S16(0x7734);
            node->phase = 4;
        }
    } else if (phase == 4) {
        node->timer = 10;
        node->phase = 5;
    } else if (phase == 5) {
        if (node->timer-- == 0) {
            WORK_S16(0x7740) = 1;
            WORK_S16(0x773E) = 0;
            node->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
            node->phase = 0;
        }
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003FA14 size:0x3CC mapped:0x8067EAA8
void fn_2_3FA14(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;
    s16 v;

    if (phase == 0) {
        challenge = lbl_2_bss_1A8248;
        WORK_S16(0x7740) = 0;
        WORK_S16(0x7734) = *(s16 *)((u8 *)challenge + 0x43BC);
        v = *(s16 *)((u8 *)challenge + 0x43BE);
        WORK_S16(0x773C) = v;
        WORK_S16(0x7736) = v;
        WORK_S16(0x773A) = 0;
        WORK_S16(0x7738) = WORK_S16(0x7734) / 2;
        node->phase = 1;
    } else if (phase == 1) {
        WORK_S16(0x773A) = WORK_S16(0x773A) << 1;
        if (WORK_S16(0x773A) == 0) {
            WORK_S16(0x773A) = WORK_S16(0x773A) + 1;
        }
        WORK_S16(0x7736) = WORK_S16(0x7736) + WORK_S16(0x773A);
        WORK_S16(0x773A) = WORK_S16(0x773A) + 1;
        lbl_2_bss_1A8234[0x1627D5] = 1;
        WORK_U32(0x76A8) = fn_80062890(0x37);

        v = WORK_S16(0x7736);
        if (v >= WORK_S16(0x7738) || v >= WORK_S16(0x7734)) {
            if (v >= WORK_S16(0x7734)) {
                WORK_S16(0x7736) = WORK_S16(0x7736) - WORK_S16(0x773A);
                if (WORK_S16(0x7736) < 1) {
                    WORK_S16(0x7736) = 1;
                }
            }
            node->phase = 2;
        }
        if (ATBAT_BUTTON_INPUT((s8)WORK_U8(0x7863))->_02 & 0x100) {
            WORK_S16(0x7736) = WORK_S16(0x7734);
            node->phase = 4;
        }
    } else if (phase == 2) {
        v = WORK_S16(0x7736);
        if (v >= WORK_S16(0x7734)) {
            WORK_S16(0x7736) = WORK_S16(0x7734);
            node->phase = 4;
        } else {
            WORK_S16(0x7736) = WORK_S16(0x7736) + (WORK_S16(0x7734) - WORK_S16(0x7736)) / 40;
            WORK_S16(0x7736) = WORK_S16(0x7736) + 1;
            lbl_2_bss_1A8234[0x1627D5] = 1;
            WORK_U32(0x76A8) = fn_80062890(0x37);
            if (ATBAT_BUTTON_INPUT((s8)WORK_U8(0x7863))->_02 & 0x100) {
                WORK_S16(0x7736) = WORK_S16(0x7734);
                node->phase = 4;
            }
        }
    } else if (phase == 4) {
        node->timer = 10;
        node->phase = 5;
    } else if (phase == 5) {
        if (node->timer-- == 0) {
            WORK_S16(0x7740) = 1;
            WORK_S16(0x773E) = 0;
            node->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
            node->phase = 0;
        }
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0003FDE0 size:0x63C mapped:0x8067EE74
void fn_2_3FDE0(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;
    s16 *row;
    s16 val;
    s32 i;
    u8 *rec;

    if (phase == 0) {
        node->timer = 70;
        challenge = lbl_2_bss_1A8248;
        WORK_S8(0x7851) = -1;
        row = (s16 *)((u8 *)lbl_2_data_3CE8 + challenge->captain * 12);
        val = row[challenge->stage + 1];
        if (row[challenge->stage] != 5) {
            for (i = 0; i < 51; i++) {
                rec = (u8 *)challenge + 0x40F0 + i * 10;
                if (rec[0] == val && rec[1] == 1) {
                    rec[1] = 0;
                    WORK_S8(0x7851) = val;
                }
            }
        }
        if (WORK_S8(0x7851) == -1) {
            node->phase = 4;
        } else {
            challenge->_440C[WORK_S8(0x7851)] = 1;
            if (challenge->captain <= 1) {
                if (WORK_S8(0x7851) == 3) {
                    for (i = 0; i < 51; i++) {
                        rec = (u8 *)challenge + 0x40F0 + i * 10;
                        if ((rec[0] == 6 || rec[0] == 8) && rec[1] == 1) {
                            rec[1] = 0;
                        }
                    }
                }
            } else if (challenge->captain == 2) {
                if (WORK_S8(0x7851) == 1) {
                    for (i = 0; i < 51; i++) {
                        rec = (u8 *)challenge + 0x40F0 + i * 10;
                        if ((rec[0] == 6 || rec[0] == 7) && rec[1] == 1) {
                            rec[1] = 0;
                        }
                    }
                }
            }
            lbl_2_bss_1A8234[0x1626E5] = 1;
            fn_80062890(4);
            node->phase = 1;
        }
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            fn_2_92654((s8)WORK_S8(0x7851) + 1, 7);
            if (WORK_S8(0x7851) == 2) {
                fn_2_92654(7, 7);
            }
            node->timer = 60;
            node->phase = 2;
        }
    } else if (phase == 2) {
        if (node->timer-- == 0) {
            if (WORK_S8(0x7851) == 5) {
                lbl_2_bss_1A8234[0x1626E7] = 1;
                node->timer = 16;
                node->phase = 3;
            } else {
                node->phase = 4;
            }
        }
    } else if (phase == 3) {
        if (node->timer-- == 0) {
            lbl_2_bss_1A8248->_4416[0x441A - 0x4416] = 1;
            node->phase = 4;
        }
    } else if (phase == 4) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x0004041C size:0x198 mapped:0x8067F4B0
void fn_2_4041C(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;

    if (phase == 0) {
        challenge = lbl_2_bss_1A8248;
        if (fn_2_45938(challenge->_16C2) == 0) {
            node->timer = 180;
            *((u8 *)challenge + challenge->_16C2 * 10 + 0x40F1) = 2;
            WORK_S8(0x7854) = *((u8 *)challenge + challenge->_16C2 * 10 + 0x40F3);
            lbl_2_bss_1A8234[0x1627C1] = 1;
            fn_80062890(3);
            node->phase = 1;
        } else {
            node->phase = 2;
        }
    } else if (phase == 1) {
        if (node->timer-- == 0) {
            node->phase = 2;
        }
    } else if (phase == 2) {
        challenge = lbl_2_bss_1A8248;
        *((u8 *)challenge + challenge->_16C2 * 10 + 0x40F1) = 3;
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}

// .text:0x000405B4 size:0x1D8 mapped:0x8067F648
void fn_2_405B4(void) {
    TextSceneNode *node = (TextSceneNode *)currentDrawingItem;
    ChallengeState *challenge;
    s8 phase = node->phase;

    if (phase == 0) {
        challenge = lbl_2_bss_1A8248;
        if (fn_2_45938(challenge->_16C2) == 0) {
            node->timer = 180;
            *((u8 *)challenge + challenge->_16C2 * 10 + 0x40F1) = 2;
            WORK_S8(0x7854) = *((u8 *)challenge + challenge->_16C2 * 10 + 0x40F3);
            fn_2_90428(WORK_S8(0x7854) + 10);
            fn_2_90428(WORK_S8(0x7854) + 16);
            fn_2_92654(WORK_S8(0x7854) + 10, 0xC);
            lbl_2_bss_1A8234[0x1627C1] = 1;
            node->phase = 1;
        } else {
            node->phase = 2;
        }
    } else if (phase == 1) {
        if (node->timer == 150) {
            fn_80062890(0x41);
        }
        if (node->timer-- == 0) {
            node->phase = 2;
        }
    } else if (phase == 2) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }

    if (lbl_2_bss_1A824C[0x19783F] == 1) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        node->phase = 0;
    }
}
