#include "menus/text_7E380.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80062674.h"
#include "text/text.h"

extern u8 gameSetUpStep[0x64];
extern u8 lbl_2_bss_F468[];
extern u8 Static_Stats_Tables[];
extern u8 g_d_GameSettings[];
void gfx_cssCharStatBars_and_sthgElse(MenuScene *scene, s32 channel);
BOOL maybeCheckAndResetGrapicsElement(MenuScene *scene, int handle, int frame);
void updateCharacterSelectProcessCode(int port, u8 process);

#define SCENE_OBJECT(scene, n) (graphicsRelatedArray[(scene)->firstHandle + (n)].object)

// .text:0x000805DC size:0x250 mapped:0x806BF670
void fn_2_805DC(void) {
    return;
}

// .text:0x00080500 size:0xDC mapped:0x806BF594
void fn_2_80500(MenuScene *scene, s32 channel) {
    u8 *step = &gameSetUpStep[channel + 0xD];

    if (*step == 0) {
        u8 isZero = *(s8 *)(Static_Stats_Tables + 0x46F8) == 0;

        *(u32 *)((u8 *)SCENE_OBJECT(scene, 0x7B) + 0x5C) = isZero << 16;
        *(u32 *)((u8 *)SCENE_OBJECT(scene, 0x19) + 0x5C) = (isZero + 4) << 16;
        makeCursorUnmovable(channel);
        *step = 1;
    }
    if (*step == 1) {
        makeCursorMovable(channel);
        *step = 2;
        g_d_GameSettings[0x10] = 0;
    }
}

// .text:0x000802EC size:0x214 mapped:0x806BF380
void fn_2_802EC(void) {
    return;
}

// .text:0x000800B0 size:0x23C mapped:0x806BF144
void captainSelectUnloadCSSLoadRelated(void) {
    return;
}

// .text:0x0007FAFC size:0x5B4 mapped:0x806BEB90
void fn_2_7FAFC(void) {
    return;
}

// .text:0x0007F8BC size:0x240 mapped:0x806BE950
void cssSelectCharacter(void) {
    return;
}

// .text:0x0007F714 size:0x1A8 mapped:0x806BE7A8
void fn_2_7F714(void) {
    return;
}

// .text:0x0007F2BC size:0x458 mapped:0x806BE350
void cssRemoveCharacter1(void) {
    return;
}

// .text:0x0007F030 size:0x28C mapped:0x806BE0C4
void cssRemoveCharacter2(void) {
    return;
}

// .text:0x0007EF68 size:0xC8 mapped:0x806BDFFC
void fn_2_7EF68(MenuScene *scene, s32 channel) {
    s32 k;

    for (k = 0; k < 9; k++) {
        if (k == ((s32 *)lbl_2_bss_F468)[channel]) {
            SCENE_OBJECT(scene, k + channel * 9 + 0x22)->flags |= 2;
        }
    }
}

// .text:0x0007EE7C size:0xEC mapped:0x806BDF10
void fn_2_7EE7C(MenuScene *scene, s32 channel) {
    s32 k = ((s32 *)lbl_2_bss_F468)[channel];

    if (lbl_2_bss_F468[channel + 0x41]) {
        SCENE_OBJECT(scene, k + channel * 9 + 0x22)->flags &= ~2;
    } else {
        SCENE_OBJECT(scene, k + channel * 9 + 0x22)->flags |= 2;
    }
    gfx_cssCharStatBars_and_sthgElse(scene, channel);
    gameSetUpStep[channel + 0x5D] = 0;
    if (lbl_2_bss_F468[channel + 0x59]) {
        updateCharacterSelectProcessCode(channel, 0x1A);
    }
}

// .text:0x0007E974 size:0x508 mapped:0x806BDA08
void cssReady(void) {
    return;
}

// .text:0x0007E860 size:0x114 mapped:0x806BD8F4
void fn_2_7E860(MenuScene *scene, s32 channel) {
    if (gameSetUpStep[channel + 0xD] == 1) {
        s32 ready;

        ready = maybeCheckAndResetGrapicsElement(scene, channel + 0xC, 0xA) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, channel + 0xE, 0xE) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x12, 0xA) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x1C, 0x14) != 0;
        ready += maybeCheckAndResetGrapicsElement(scene, channel + 0x6A, 0x1E) != 0;
        if (ready == 5) {
            makeCursorMovable(channel);
            gameSetUpStep[channel + 0xD] = 2;
        }
    }
}

// .text:0x0007E380 size:0x4E0 mapped:0x806BD414
void cssUnready(void) {
    return;
}
