#include "menus/text_76874.h"

extern u8 gameSetUpStep[0x64];

// .text:0x00076874 size:0x57C mapped:0x806B5908
void fn_2_76874(void) {
    return;
}

// .text:0x00076DF0 size:0x8B0 mapped:0x806B5E84
void fn_2_76DF0(void) {
    return;
}

// .text:0x000776A0 size:0x994 mapped:0x806B6734
void removeAllPlayersFromTeam(void) {
    return;
}

// .text:0x00078034 size:0x28 mapped:0x806B70C8
void fn_2_78034(int unused, int channel) {
    u8 *flag = gameSetUpStep + channel + 0xD;

    if (*flag == 0) {
        *flag = 1;
    }
}

// .text:0x0007805C size:0x310 mapped:0x806B70F0
void cssAction_0x1d(void) {
    return;
}

// .text:0x0007836C size:0x754 mapped:0x806B7400
void cssAction_0x1c(void) {
    return;
}

// .text:0x00078AC0 size:0x4B8 mapped:0x806B7B54
void cssAction_0x1b(void) {
    return;
}
