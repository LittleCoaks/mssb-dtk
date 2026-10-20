#include "menus/text_1B1BC.h"
#include "Unknown/File_0x800b0a14.h"
#include "menus/text_4D960.h"
#include "menus/text_4078C.h"
#include "menus/text_53408.h"
#include "menus/rep_0B08.h"
#include "menus/rep_0F60.h"

extern u8 lbl_2_bss_1034C[];
extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A823C;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_bss_1A8250[];
extern u8 *lbl_2_data_4BA0;
extern u8 lbl_803C6CF8[];
extern u8 teamStarModelFileDescriptorMenus[];
extern u8 Static_Stats_Tables[];
extern u8 g_d_GameSettings[];
extern u8 screenTextArray[];
extern u8 audioFileDescriptors[];
extern u8 AtBat_ButtonInput1[];
extern u8 g_Challenge[];
extern u8 inningSetting[];
extern u8 superstarUnlocked[];
extern u8 hugeAnimStruct[];
extern u8 *lbl_2_bss_1A8230;
extern u8 *lbl_2_bss_1A8238;
extern u8 *lbl_2_bss_1A8244;
extern u8 *lbl_2_bss_340140;
extern u8 lbl_2_data_4BA8[];
extern u8 challengeCaptainCharIDs[];
extern u8 characterStaticIndexes[];
extern u8 starMissionRequirementsTable[];

void *memset(void *dst, s32 c, u32 n);
void *ARAMTransfer(void *file, s32 arg1, s32 arg2, s32 arg3);
void convertTextureHeader(void *tex);
void fn_8004B1B8(void *p);
void fn_80068720(u8 index);
void fn_800ACFB0(void *block);
void resetGameStadiumStateOnExit(void);
BOOL maybeLoadsGameSoundFiles(void);
void fn_2_1C33C_tail(void);
void fn_2_47CFC(void);
void fn_2_46D94(s16 *a, s16 *b, s16 c, s32 d, s32 e);
int fn_8006CDC0(int charID);
void fn_8006C488(void);
void fn_8000F4B8(void);
void fn_2_4AB1C(void);
s32 fn_2_46D00(void);
void fn_2_20328(void);
void fn_2_46418(void);
void fn_2_468DC(void);
void fn_2_466AC(void);
void fn_2_467FC(void);
void fn_2_454E8(void);
void fn_2_207FC(void);
void fn_2_2460C(void);
s32 fn_2_20CB0(s32 x);
void fn_2_37460(void);
void fn_2_37D98(void);
void fn_2_40A9C(void);
void fn_2_379D0(void);
void fn_800627F8(void);
void fn_2_20D08(void);
void fn_800216F8(s32 id, void (*func)(void));
void playStream(s32 id);
void changeScene(s32 a, s32 b);
void GXSetCopyClear(u32 color, u32 z);
s32 fn_2_44E2C(s32 v);
void fn_2_8AEE0(void);
void fn_2_8ACB0(s32 idx, s32 val);

#define DRAW_STATE(node) (*(s8 *)&(node)->unk_28)
#define SCENE_STATE (*(s16 *)&lbl_2_bss_1A823C[0x32])
#define AT_BAT_BUTTON(off, idx) (*(u16 *)(AtBat_ButtonInput1 + (off) + ((idx) << 5)))

// .text:0x0001CF94 size:0x4AC mapped:0x8065C028
void fn_2_1CF94(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    u8 *p;
    u8 *q;
    u8 *e;
    u8 *tbl;
    u16 btn;
    s32 idx;
    s32 k;
    s32 j;
    s32 cnt;
    s32 v;

    switch (DRAW_STATE(node)) {
    case 0:
        p = lbl_2_bss_1A824C;
        *(s16 *)&p[0x19771A] = 0;
        *(s16 *)&p[0x19771C] = 0;
        *(s16 *)&p[0x19771E] = 0x36;
        DRAW_STATE(node) = 1;
        break;
    case 1:
        p = lbl_2_bss_1A824C;
        idx = (s8)p[0x197863];
        btn = AT_BAT_BUTTON(4, idx);
        if (btn == 8 || btn == 4) {
            fn_2_46D94((s16 *)&p[0x19771A], (s16 *)&p[0x19771C], *(s16 *)&p[0x19771E], 10, 9);
        }
        *(s16 *)&p[0x197716] = *(s16 *)&p[0x19771A] + *(s16 *)&p[0x19771C];

        q = lbl_2_bss_1A8248;
        e = q + 0x34 * *(s16 *)&p[0x197716];
        idx = (s8)lbl_2_bss_1A824C[0x197863];
        btn = AT_BAT_BUTTON(4, idx);
        tbl = *(u8 **)e;
        if (btn & 1) {
            cnt = (s8)e[6];
            if (cnt > 0 && cnt != (s8)tbl[6 * q[0x4415] + q[0x441C] + 4]) {
                e[6] = cnt - 1;
            }
        } else if (btn & 2) {
            cnt = (s8)e[6];
            if (cnt < (s8)tbl[6 * q[0x4415] + q[0x441C] + 4]) {
                e[6] = cnt + 1;
            }
        }

        btn = AT_BAT_BUTTON(2, idx);
        if (btn & 0x300) {
            *(u16 *)((u8 *)node + 0x14) = 0x10;
            DRAW_STATE(node) = 2;
        }
        if (btn & 0x40) {
            q = lbl_2_bss_1A8248;
            for (k = 0; k < 0x36; k++) {
                e = q + 0x34 * k;
                for (j = 0; j < 8; j++) {
                    tbl = *(u8 **)e;
                    if (tbl[6 * q[0x4415] + q[0x441C] + 4] != 0) {
                        e[6] = 0;
                    }
                }
                q[0x444D + k] = 0;
                e[0x31] = 0;
            }
        }
        if (btn & 0x20) {
            q = lbl_2_bss_1A8248;
            for (k = 0; k < 0x36; k++) {
                e = q + 0x34 * k;
                for (j = 0; j < 8; j++) {
                    tbl = *(u8 **)e;
                    v = tbl[6 * q[0x4415] + q[0x441C] + 4];
                    if (v != 0) {
                        e[6] = v;
                    }
                }
            }
        }
        break;
    case 2:
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
        break;
    }
}

// .text:0x0001C860 size:0x734 mapped:0x8065B8F4
void fn_2_1C860(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    u8 *p;
    u8 *q;
    u8 *e;
    u8 *chars;
    u8 *row;
    u16 btn;
    s32 idx;
    s32 k;
    s32 n;
    s32 m;
    s32 v;
    s32 w;
    s32 ret0;
    s32 ret1;
    s32 state;

    state = DRAW_STATE(node);
    if (state == 0) {
        p = lbl_2_bss_1A824C;
        *(s16 *)&p[0x19771A] = 0;
        *(s16 *)&p[0x19771C] = 0;
        *(s16 *)&p[0x197720] = 0;
        *(s16 *)&p[0x197722] = 0;
        *(s16 *)&p[0x19771E] = 0x36;
        *(s16 *)&p[0x197724] = 10;
        DRAW_STATE(node) = 1;
    } else if (state == 1) {
        p = lbl_2_bss_1A824C;
        idx = (s8)p[0x197863];
        btn = AT_BAT_BUTTON(4, idx);
        if (btn == 8 || btn == 4) {
            fn_2_46D94((s16 *)&p[0x19771A], (s16 *)&p[0x19771C], *(s16 *)&p[0x19771E], 10, 9);
        }
        *(s16 *)&p[0x197716] = *(s16 *)&p[0x19771A] + *(s16 *)&p[0x19771C];

        btn = AT_BAT_BUTTON(2, idx);
        if (btn & 0x100) {
            DRAW_STATE(node) = 2;
        } else if (btn & 0x200) {
            DRAW_STATE(node) = 3;
        }

        btn = AT_BAT_BUTTON(2, idx);
        if (btn & 0x40) {
            q = lbl_2_bss_1A8248;
            for (k = 0; k < 0x36; k++) {
                chars = characterStaticIndexes + 6 * k;
                if (chars[3] == 1) {
                    e = q + 0x34 * k;
                    row = starMissionRequirementsTable + 100 * chars[2];
                    for (n = 0; n < 10; n++) {
                        if (*(s16 *)&row[10 * n] != -1) {
                            e[9 + 2 * (n % 5) + 10 * (n / 5)] = 0;
                        }
                    }
                }
            }
        } else if (btn & 0x20) {
            q = lbl_2_bss_1A8248;
            for (k = 0; k < 0x36; k++) {
                chars = characterStaticIndexes + 6 * k;
                if (chars[3] == 1) {
                    e = q + 0x34 * k;
                    row = starMissionRequirementsTable + 100 * chars[2];
                    for (n = 0; n < 10; n++) {
                        if (*(s16 *)&row[10 * n] != -1) {
                            e[9 + 2 * (n % 5) + 10 * (n / 5)] = -2;
                        }
                    }
                }
            }
        }
    } else if (state == 2) {
        p = lbl_2_bss_1A824C;
        idx = (s8)p[0x197863];
        btn = AT_BAT_BUTTON(4, idx);
        if (btn == 8 || btn == 4) {
            fn_2_46D94((s16 *)&p[0x197720], (s16 *)&p[0x197722], *(s16 *)&p[0x197724], 10, 9);
        }
        *(s16 *)&p[0x197718] = *(s16 *)&p[0x197720] + *(s16 *)&p[0x197722];
        ret0 = fn_8006CDC0(*(s16 *)&p[0x197716]);
        ret1 = fn_2_44E2C(*(s16 *)&p[0x197716]);

        btn = AT_BAT_BUTTON(2, idx);
        q = lbl_2_bss_1A8248;
        v = *(s16 *)&p[0x197716];
        e = q + 0x34 * v;
        if ((btn & 0x103) && ret0 != ret1) {
            chars = characterStaticIndexes + 6 * v;
            if (chars[3] == 1) {
                row = starMissionRequirementsTable + 100 * chars[2];
                w = *(s16 *)&p[0x197718];
                if (*(s16 *)&row[10 * w] != -1) {
                    e[2 * w + 9] = ((s8)e[2 * w + 9] >= 0) ? -2 : 0;
                    fn_8006CDC0(*(s16 *)&p[0x197716]);
                }
            }
        }

        if (btn & 0x200) {
            DRAW_STATE(node) = 1;
        }

        btn = AT_BAT_BUTTON(2, idx);
        if (btn & 0x40) {
            v = *(s16 *)&p[0x197716];
            e = q + 0x34 * v;
            for (n = 0; n < 5; n++) {
                for (m = 0; m < 2; m++) {
                    chars = characterStaticIndexes + 6 * v;
                    if (chars[3] == 1) {
                        row = starMissionRequirementsTable + 100 * chars[2];
                        if (*(s16 *)&row[10 * (2 * n + m)] != -1) {
                            e[4 * n + 9 + 2 * m] = 0;
                        }
                    }
                }
            }
        } else if (btn & 0x20) {
            v = *(s16 *)&p[0x197716];
            e = q + 0x34 * v;
            for (n = 0; n < 5; n++) {
                for (m = 0; m < 2; m++) {
                    chars = characterStaticIndexes + 6 * v;
                    if (chars[3] == 1) {
                        row = starMissionRequirementsTable + 100 * chars[2];
                        if (*(s16 *)&row[10 * (2 * n + m)] != -1) {
                            e[4 * n + 9 + 2 * m] = -2;
                        }
                    }
                }
            }
        }
    } else if (state == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
    }
}

// .text:0x0001C714 size:0x14C mapped:0x8065B7A8
void fn_2_1C714(s32 idx) {
    u8 *q;
    u8 *e;
    s32 i;
    u32 mask;

    q = lbl_2_bss_1A8248;
    e = q + 0x40F0;
    for (i = 0; i < 0x33; i++, e += 0xA) {
        if (idx == e[0] && (e[1] == 0 || e[1] == 1)) {
            if (e[2] != 0) {
                e[1] = 0;
            } else if (q[0x441C] == idx) {
                e[1] = 0;
            } else if (q[0x441C] == 5) {
                e[1] = 3;
            } else {
                e[1] = 0;
            }
            if (e[2] == 2) {
                e[1] = 0;
            }
        }
        if (e[0] == 6 || e[0] == 7 || e[0] == 8) {
            e[1] = 0;
            q[0x4412] = 1;
            q[0x4413] = 1;
            q[0x4414] = 1;
        }
    }
    q[0x440C + idx] = 1;
    if (q[0x441C] == idx) {
        return;
    }
    mask = 1 << idx;
    if (q[0x4426] & mask) {
        return;
    }
    q[0x4422]++;
    q[0x4426] |= mask;
}

// .text:0x0001C5C8 size:0x14C mapped:0x8065B65C
void fn_2_1C5C8(s32 idx) {
    u8 *q;
    u8 *e;
    s32 i;
    u32 mask;

    q = lbl_2_bss_1A8248;
    e = q + 0x40F0;
    for (i = 0; i < 0x33; i++, e += 0xA) {
        if (idx == e[0] && (e[1] == 0 || e[1] == 1)) {
            if (e[2] != 0) {
                e[1] = 0;
            } else if (q[0x441C] == idx) {
                e[1] = 0;
            } else if (q[0x441C] == 5) {
                e[1] = 3;
            } else {
                e[1] = 2;
            }
            if (e[2] == 2) {
                e[1] = 0;
            }
        }
        if (e[0] == 6 || e[0] == 7 || e[0] == 8) {
            e[1] = 0;
            q[0x4412] = 1;
            q[0x4413] = 1;
            q[0x4414] = 1;
        }
    }
    q[0x440C + idx] = 1;
    if (q[0x441C] == idx) {
        return;
    }
    mask = 1 << idx;
    if (q[0x4426] & mask) {
        return;
    }
    q[0x4422]++;
    q[0x4426] |= mask;
}

// .text:0x0001C504 size:0xC4 mapped:0x8065B598
void fn_2_1C504(s32 idx) {
    u8 *q;
    u8 *e;
    s32 i;
    u32 mask;

    q = lbl_2_bss_1A8248;
    e = q + 0x40F0;
    for (i = 0; i < 0x33; i++, e += 0xA) {
        if (idx == e[0]) {
            if (e[1] == 1) {
                e[1] = 0;
            } else if (e[1] == 0) {
                if (q[0x441C] == 5 && e[2] == 1) {
                    e[1] = 3;
                } else {
                    e[1] = 0;
                }
            }
        }
    }
    q[0x440C + idx] = 1;
    mask = 1 << idx;
    if (q[0x4428] & mask) {
        return;
    }
    q[0x4423]++;
    q[0x4428] |= mask;
}

// .text:0x0001C490 size:0x74 mapped:0x8065B524
void fn_2_1C490(void) {
    lbl_2_bss_1A8234[0x162841] = 1;
    lbl_2_bss_1A8234[0x162860] = 1;
    lbl_2_bss_1A8234[0x162861] = 1;
    lbl_2_bss_1A8234[0x162862] = 1;
    lbl_2_bss_1A8234[0x162657] = 0;
    lbl_2_bss_1A8234[0x162676] = 0;
    lbl_2_bss_1A8234[0x162677] = 0;
    lbl_2_bss_1A8234[0x162678] = 0;
}

// .text:0x0001C41C size:0x74 mapped:0x8065B4B0
void fn_2_1C41C(void) {
    lbl_2_bss_1A8234[0x162657] = 1;
    lbl_2_bss_1A8234[0x162676] = 1;
    lbl_2_bss_1A8234[0x162677] = 1;
    lbl_2_bss_1A8234[0x162678] = 1;
    lbl_2_bss_1A8234[0x162841] = 0;
    lbl_2_bss_1A8234[0x162860] = 0;
    lbl_2_bss_1A8234[0x162861] = 0;
    lbl_2_bss_1A8234[0x162862] = 0;
}

// .text:0x0001C3A8 size:0x74 mapped:0x8065B43C
void fn_2_1C3A8(void) {
    if (lbl_2_bss_1A824C[0x1978FB] == 1) {
        lbl_2_bss_1A8234[0x16268A] = 1;
        lbl_2_bss_1A8234[0x162874] = 0;
    } else {
        lbl_2_bss_1A8234[0x162874] = 1;
        lbl_2_bss_1A8234[0x16268A] = 0;
    }
}

// .text:0x0001C3A4 size:0x4 mapped:0x8065B438
void fn_2_1C3A4(void) {
    return;
}

// .text:0x0001C33C size:0x68 mapped:0x8065B3D0
void fn_2_1C33C(void) {
    u8 *p = lbl_2_bss_1A8248;
    s16 v;

    if (p[0x441C] >= 6) {
        fn_2_1C33C_tail();
        return;
    }
    if (p[0x4415] >= 4) {
        fn_2_1C33C_tail();
        return;
    }
    v = *(s16 *)&p[0x43BC];
    if (v < 0 || v > 999) {
        fn_2_1C33C_tail();
        return;
    }
    if (*(s16 *)&lbl_2_bss_1A823C[0x30] != 5) {
        return;
    }
    if (p[0x4420] < 5) {
        return;
    }
    fn_2_1C33C_tail();
}

// .text:0x0001C244 size:0xF8 mapped:0x8065B2D8
void fn_2_1C244(void) {
    u8 *rowBase;
    u8 *p;
    s32 row;
    s32 entry;
    s32 field;
    s32 n;

    rowBase = lbl_2_bss_1A8234;
    for (row = 0; row < 0x46; row++) {
        p = rowBase;
        n = 0;
        for (entry = 0; entry < 0x90; entry++) {
            for (field = 0; field < 6; field++) {
                if (row >= 0x23 && n >= 0x64 && *(u32 *)(p + field * 0x18) != 0) {
                    return;
                }
                n++;
            }
            p += 0x90;
        }
        rowBase += 0x5100;
    }
}

// .text:0x0001C21C size:0x28 mapped:0x8065B2B0
void fn_2_1C21C(void) {
    u8 buf[0x18];
    fn_2_68DAC(0, buf);
}

// .text:0x0001C0D4 size:0x148 mapped:0x8065B168
void fn_2_1C0D4(void) {
    lbl_2_bss_1A823C[0x34] = 1;
    memset(lbl_2_bss_1A8250, 0, 0x1978FC);
    *(s16 *)&lbl_2_bss_1A824C[0x197756] = -1;
    *(s16 *)&lbl_2_bss_1A824C[0x197758] = -1;
    *(s16 *)&lbl_2_bss_1A824C[0x19775A] = -1;
    *(s16 *)&lbl_2_bss_1A824C[0x19775C] = -1;
    *(s16 *)&lbl_2_bss_1A824C[0x19775E] = -1;
    *(s16 *)&lbl_2_bss_1A824C[0x197760] = -1;
    *(s16 *)&lbl_2_bss_1A824C[0x197762] = -1;
    *(s16 *)&lbl_2_bss_1A824C[0x197764] = -1;
    fn_2_54474();
    lbl_2_bss_1A8248[0x44F2] = 0;
    *(s16 *)&lbl_2_bss_1A824C[0x1976D6] = 0;
    lbl_2_bss_1A824C[0x197833] = 0;
    lbl_2_bss_1A8234[0x162992] = 0;
    lbl_2_bss_1A824C[0x197838] = 0;
    lbl_2_bss_1A824C[0x197835] = 0;
    g_d_GameSettings[9] = 0;
    lbl_2_bss_1A824C[0x197863] = Static_Stats_Tables[0x46F8];
    lbl_2_bss_1A824C[0x197848] = 0;
}

// .text:0x0001BFD0 size:0x104 mapped:0x8065B064
void fn_2_1BFD0(void) {
    fn_80068720(0xA);
    lbl_2_bss_1A824C[0x1972BC] = 1;
    lbl_2_bss_1A824C[0x1972C0] = 1;
    *(s16 *)&lbl_2_bss_1A824C[0x1976D6] = 0;
    lbl_2_bss_1A8248[0x44F2] = 0;
    if (lbl_2_bss_1A824C[0x197864] == 0) {
        fn_2_4E7EC();
        resetGameStadiumStateOnExit();
        maybeLoadsGameSoundFiles();
        fn_800ACFB0(*(void **)&audioFileDescriptors[0x9C]);
    }
    if (lbl_2_bss_1A8248[0x44F4] != 0) {
        fn_2_4E8BC();
        fn_2_4E904();
        fn_2_4E928();
    } else {
        fn_2_4E928();
        fn_2_4E94C();
    }
    if (*(void **)&screenTextArray[0x7A8] != NULL) {
        fn_800ACFB0(*(void **)&screenTextArray[0x7A8]);
        *(void **)&screenTextArray[0x7A8] = NULL;
    }
    lbl_2_bss_1A823C[0x34] = 0;
}

// .text:0x0001BF50 size:0x80 mapped:0x8065AFE4
void fn_2_1BF50(void) {
    fn_80068720(0xD);
    lbl_2_bss_1A824C[0x1972BC] = 1;
    lbl_2_bss_1A824C[0x1972C0] = 1;
    *(s16 *)&lbl_2_bss_1A824C[0x1976D6] = 0;
    lbl_2_bss_1A8248[0x44F2] = 0;
    fn_2_4E898();
    lbl_2_bss_1A823C[0x34] = 0;
}

// .text:0x0001B7B4 size:0x79C mapped:0x8065A848
void fn_2_1B7B4(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    DrawingSceneStruct *fresh;
    u8 *q;
    u8 *p;
    s32 r22;

    lbl_2_bss_1A8248 = g_Challenge;
    lbl_2_bss_1A824C = lbl_2_bss_1A8250;
    lbl_2_bss_1A8238 = g_Challenge + 0x1610;
    lbl_2_bss_1A8244 = superstarUnlocked;
    lbl_2_bss_1A823C = inningSetting + 0x28;
    lbl_2_bss_1A8234 = lbl_2_bss_1A8250;
    lbl_2_bss_1A8230 = lbl_2_bss_1A8250 + 0x162998;
    lbl_2_bss_340140 = hugeAnimStruct;

    switch (SCENE_STATE) {
    case 0:
        fn_8006C488();
        resetGameStadiumStateOnExit();
        lbl_2_bss_1A823C[0x34] = 1;
        memset(lbl_2_bss_1A8250, 0, 0x1978FC);
        p = lbl_2_bss_1A824C;
        *(s16 *)&p[0x197756] = -1;
        *(s16 *)&p[0x197758] = -1;
        *(s16 *)&p[0x19775A] = -1;
        *(s16 *)&p[0x19775C] = -1;
        *(s16 *)&p[0x19775E] = -1;
        *(s16 *)&p[0x197760] = -1;
        *(s16 *)&p[0x197762] = -1;
        *(s16 *)&p[0x197764] = -1;
        fn_2_54474();
        q = lbl_2_bss_1A8248;
        q[0x44F2] = 0;
        *(s16 *)&p[0x1976D6] = 0;
        p[0x197833] = 0;
        lbl_2_bss_1A8234[0x162992] = 0;
        p[0x197838] = 0;
        p[0x197835] = 0;
        g_d_GameSettings[9] = 0;
        p[0x197863] = Static_Stats_Tables[0x46F8];
        p[0x197848] = 0;
        fn_8000F4B8();
        SCENE_STATE = 2;
        break;
    case 1:
        if (node->state == 1) {
            SCENE_STATE = 2;
        }
        break;
    case 2:
        SCENE_STATE = 3;
        break;
    case 3:
        SCENE_STATE = 4;
        break;
    case 4:
        r22 = 0;
        if (*(s16 *)&lbl_2_bss_1A823C[0x30] == 3) {
            fn_2_4AB1C();
            if (lbl_2_bss_1A824C[0x197843] == 0) {
                q = lbl_2_bss_1A8248;
                if (q[0x441C] == 5) {
                    if (fn_2_46D00() != 0) {
                        r22 = 1;
                    }
                } else if (q[0x4426] & 0x20) {
                    r22 = 1;
                }
            }
        }
        q = lbl_2_bss_1A8248;
        q[0x44F4] = (r22 != 0);
        if (q[0x44F4] == 0) {
            SCENE_STATE = 0xC;
        } else {
            GXSetCopyClear(*(u32 *)lbl_2_data_4BA8, 0xFFFFFF);
            changeScene(1, 6);
            if (q[0x4415] < 3) {
                SCENE_STATE = 0xC;
            } else if (fn_2_4E970() == 1) {
                SCENE_STATE = 5;
            }
        }
        break;
    case 5:
        fresh = insertGraphicDrawingFunction(fn_2_37460, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 6;
        break;
    case 6:
        if (node->state == 1) {
            SCENE_STATE = 7;
        }
        break;
    case 7:
        lbl_2_bss_1A8250[0x162992] = 0;
        lbl_2_bss_1A8230[0x32A86] = 0;
        fn_2_54474();
        fn_2_2460C();
        SCENE_STATE = 8;
        break;
    case 8:
        playStream(0xD);
        fresh = insertGraphicDrawingFunction(fn_2_37D98, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 9;
        break;
    case 9:
        if (node->state == 1) {
            SCENE_STATE = 0xA;
        }
        break;
    case 10:
        fresh = insertGraphicDrawingFunction(fn_2_40A9C, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 0xB;
        break;
    case 11:
        if (node->state == 1) {
            SCENE_STATE = 0xC;
        }
        break;
    case 12:
        if (lbl_2_bss_1A8248[0x44F4] == 0) {
            fresh = insertGraphicDrawingFunction(fn_2_1B6CC, 2);
        } else {
            fresh = insertGraphicDrawingFunction(fn_2_1B5C0, 2);
        }
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 0xD;
        break;
    case 13:
        if (node->state == 1) {
            SCENE_STATE = 0xE;
        }
        break;
    case 14:
        fn_800216F8(0x26, fn_800627F8);
        node->state = 0;
        SCENE_STATE = 0xF;
        break;
    case 15:
        if (node->state == 1) {
            SCENE_STATE = 0x12;
        }
        break;
    case 18:
        switch (*(s16 *)&lbl_2_bss_1A823C[0x30]) {
        case 1:
            fn_2_468DC();
            SCENE_STATE = 0x17;
            break;
        case 0:
            q = lbl_2_bss_1A8248;
            q[0x441C] = fn_2_20CB0(*(u32 *)&Static_Stats_Tables[0x46E0]);
            q[0x441D] = challengeCaptainCharIDs[q[0x441C]];
            if (q[0x1606] != 0) {
                fn_2_20328();
                fn_2_46418();
                fn_2_468DC();
                fn_2_466AC();
                fn_2_467FC();
                fn_2_454E8();
            } else {
                q[0x1605] = 0;
                fn_2_207FC();
                fn_2_466AC();
            }
            fresh = insertGraphicDrawingFunction(fn_2_379D0, 2);
            DRAW_STATE(fresh) = 0;
            node->state = 0;
            SCENE_STATE = 0x13;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            lbl_2_bss_1A8248[0x44F2] = 0;
            SCENE_STATE = 0x17;
            break;
        }
        break;
    case 19:
        if (node->state == 1) {
            SCENE_STATE = 0x17;
        }
        break;
    case 20:
        *(s16 *)&lbl_2_bss_1A824C[0x197746] = 7;
        fresh = insertGraphicDrawingFunction(fn_2_1B314, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 0x15;
        break;
    case 21:
        if (node->state == 1) {
            SCENE_STATE = 0x16;
        }
        break;
    case 22:
        fresh = insertGraphicDrawingFunction(fn_2_1B1BC, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        SCENE_STATE = 0x17;
        break;
    case 23:
        if (node->state == 1) {
            node->state = 0;
            node->func = fn_2_20D08;
            SCENE_STATE = 0;
        }
        break;
    }

    *(u16 *)&g_d_GameSettings[4] += 1;
    *(u32 *)&lbl_2_bss_1A824C[0x1976C0] += 1;
}

// .text:0x0001B6CC size:0xE8 mapped:0x8065A760
void fn_2_1B6CC(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    DrawingSceneStruct *fresh;
    s8 state = DRAW_STATE(node);

    if (state == 0) {
        fresh = insertGraphicDrawingFunction(fn_2_409CC, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        DRAW_STATE(node) = 1;
    } else if (state == 1) {
        if (node->state == 1) {
            DRAW_STATE(node) = 2;
        }
    } else if (state == 2) {
        if (fn_2_4EB64() == 1) {
            DRAW_STATE(node) = 3;
        }
    } else if (state == 3) {
        if (fn_2_4EB2C() == 1) {
            DRAW_STATE(node) = 4;
        }
    } else if (state == 4) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
    }
}

// .text:0x0001B5C0 size:0x10C mapped:0x8065A654
void fn_2_1B5C0(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    DrawingSceneStruct *fresh;

    switch (DRAW_STATE(node)) {
    case 0:
        fresh = insertGraphicDrawingFunction(fn_2_409CC, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        DRAW_STATE(node) = 1;
        break;
    case 1:
        if (node->state == 1) {
            DRAW_STATE(node) = 2;
        }
        break;
    case 2:
        if (fn_2_4EB64() == 1) {
            DRAW_STATE(node) = 3;
        }
        break;
    case 3:
        if (fn_2_4EB2C() == 1) {
            DRAW_STATE(node) = 4;
        }
        break;
    case 4:
        if (fn_2_4EAF4() == 1) {
            DRAW_STATE(node) = 5;
        }
        break;
    case 5:
        if (fn_2_4E9A8() == 1) {
            DRAW_STATE(node) = 6;
        }
        break;
    case 6:
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
        break;
    }
}

// .text:0x0001B52C size:0x94 mapped:0x8065A5C0
void fn_2_1B52C(void) {
    DrawingSceneStruct *node = currentDrawingItem;

    if (DRAW_STATE(node) == 1) {
        DRAW_STATE(node) = 6;
    } else if (DRAW_STATE(node) > 1) {
        if (DRAW_STATE(node) == 6) {
            node->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
            DRAW_STATE(node) = 0;
        }
    } else if (DRAW_STATE(node) >= 0) {
        if (fn_2_4E970() == 1) {
            DRAW_STATE(node) = 1;
        }
    }
}

// .text:0x0001B314 size:0x218 mapped:0x8065A3A8
void fn_2_1B314(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    DrawingSceneStruct *fresh;
    s32 i;

    switch (DRAW_STATE(node)) {
    case 0:
        *(s16 *)&lbl_2_bss_1A824C[0x197746] = 7;
        fresh = insertGraphicDrawingFunction(fn_2_8EA80, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        DRAW_STATE(node) = 1;
        break;
    case 1:
        if (node->state == 1) {
            DRAW_STATE(node) = 2;
        }
        break;
    case 2:
        fresh = insertGraphicDrawingFunction(fn_2_8E478, 2);
        DRAW_STATE(fresh) = 0;
        node->state = 0;
        DRAW_STATE(node) = 3;
        break;
    case 3:
        if (node->state == 1) {
            DRAW_STATE(node) = 12;
        }
        break;
    case 4:
        for (i = 0; i < *(s16 *)&lbl_2_bss_1A824C[0x197746]; i++) {
            fn_2_8CCAC(i, 1);
            fn_2_68FBC(i, 1);
        }
        DRAW_STATE(node) = 5;
        break;
    case 5:
        fn_2_47CFC();
        DRAW_STATE(node) = 6;
        break;
    case 6:
        for (i = 0; i < *(s16 *)&lbl_2_bss_1A824C[0x197746]; i++) {
            fn_2_8CCAC(i, 0);
        }
        fn_2_47CFC();
        DRAW_STATE(node) = 7;
        break;
    case 7:
        fn_2_47CFC();
        DRAW_STATE(node) = 8;
        break;
    case 8:
        DRAW_STATE(node) = 9;
        break;
    case 9:
        fn_2_8AEE0();
        DRAW_STATE(node) = 10;
        break;
    case 10:
        for (i = 0; i < 0x1D; i++) {
            fn_2_8ACB0(i, 0);
        }
        fn_2_8AEE0();
        DRAW_STATE(node) = 11;
        break;
    case 11:
        fn_2_8AEE0();
        DRAW_STATE(node) = 12;
        break;
    case 12:
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
        break;
    }
}

// .text:0x0001B1BC size:0x158 mapped:0x8065A250
void fn_2_1B1BC(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    s8 state = DRAW_STATE(node);

    if (state == 0) {
        lbl_2_data_4BA0 = lbl_2_bss_1034C;
        *(void **)(lbl_2_data_4BA0 + 8) = ARAMTransfer(teamStarModelFileDescriptorMenus, 0, 0, 0);
        DRAW_STATE(node) = 1;
    } else if (state == 1) {
        if (lbl_803C6CF8[0x715] == 1) {
            DRAW_STATE(node) = 2;
        }
    } else if (state == 2) {
        u32 *tbl = *(u32 **)(lbl_2_data_4BA0 + 8);
        tbl[0] += (u32)tbl;
        convertTextureHeader((void *)tbl[0]);
        *(u32 *)(lbl_2_data_4BA0 + 4) = tbl[0];
        fn_8004B1B8(*(void **)(lbl_2_data_4BA0 + 4));
        DRAW_STATE(node) = 3;
    } else if (state == 3) {
        node->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        DRAW_STATE(node) = 0;
    }
}
