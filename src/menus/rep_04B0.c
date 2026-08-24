#include "menus/rep_04B0.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800bd300.h"

typedef struct {
    /* 0x0 */ u16 currentHeldInput;
    /* 0x2 */ u16 newInput;
    /* 0x4 */ u16 processedInput;
} controllerInputStruct; // size: 0x6

typedef struct {
    /* 0x0000 */ u8 _pad0[0x46FC];
    /* 0x46FC */ s8 portsActiveInMatch[4];
    /* 0x4700 */ u8 _pad1[0x29];
    /* 0x4729 */ u8 player2Ind;
    /* 0x472A */ u8 _pad2[0x2];
    /* 0x472C */ controllerInputStruct controllerInputs[4];
    /* 0x4744 */ u8 _pad3[0x5240 - 0x4744];
} Static_MSSB_Data; // size: 0x5240

extern Static_MSSB_Data Static_Stats_Tables;
extern u8 lbl_2_bss_100B8[0x54];
extern u8 lbl_2_data_1DD4[0x318];
extern u8 captainIDOrderedOnCapSS[12];
extern int lbl_2_bss_F410[0x16];

void AnimateCharacter(u8 charId, int animId, int a2, int a3, int a4, int a5, int a6, int a7);
void QueueCharacterAnimation(u8 charId, int animId, int a2, int a3, int a4, int a5, int a6);
int stadiumRandomizer(int min, int max);
void set807518de(u8 port, int arg1);

void fn_2_1A88(void);
void *fn_8001CB10(void *arg0, int arg1);
void fn_8001CCC8(void *arg0);

typedef struct {
    /* 0x0000 */ u8 _pad0[0xAC];
    /* 0x00AC */ void *_AC[4];
    /* 0x00BC */ u8 _pad1[0x3154 - 0xBC];
} HugeAnimStruct; // size: 0x3154

extern HugeAnimStruct hugeAnimStruct;
extern u8 lbl_2_bss_10164[0x48];

// .text:0x00014574 size:0x21C mapped:0x80653608
void fn_2_14574(void) {
    return;
}

// .text:0x00014790 size:0x428 mapped:0x80653824
void checkForNewPlayer(void) {
    return;
}

// .text:0x00014BB8 size:0xE8 mapped:0x80653C4C
void fn_2_14BB8(int port, int state) {
    switch (state) {
    case 0: {
        u8 c = port;
        AnimateCharacter(c, 0x6A, 0, 1, 1, 0, 0, -1);
        QueueCharacterAnimation(c, 0x6B, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8[0x40 + c] = 0;
        break;
    }
    case 1:
        AnimateCharacter(port, 0x69, 1, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8[0x40 + (u8)port] = 1;
        break;
    }
}

// .text:0x00014CA0 size:0x318 mapped:0x80653D34
void captainSelect_handleCursor(void) {
    return;
}

// .text:0x00014FB8 size:0x118 mapped:0x8065404C
void fn_2_14FB8(int port) {
    int chosen[2];
    int i;

    chosen[0] = captainIDOrderedOnCapSS[lbl_2_bss_F410[4]];
    chosen[1] = captainIDOrderedOnCapSS[lbl_2_bss_F410[5]];
    do {
        chosen[port] = stadiumRandomizer(0, 0x13);
        for (i = 0; i < 12; i++) {
            if (captainIDOrderedOnCapSS[i] == chosen[port]) {
                break;
            }
        }
    } while (i == 12 || chosen[0] == chosen[1]);
    lbl_2_bss_F410[4 + port] = i;
}

// .text:0x000150D0 size:0x34 mapped:0x80654164
void fn_2_150D0(u8 idx) {
    if (lbl_2_bss_100B8[0x14 + idx] == 0) {
        lbl_2_bss_100B8[0x14 + idx] = 1;
        lbl_2_bss_100B8[0x1C + idx] = 0;
    }
}

// .text:0x00015104 size:0xB8 mapped:0x80654198
BOOL loadNewCaptainModelOnCapSelectScreen(int currentCharId, int newCharId, u8 port, int arg3) {
    if (newCharId != currentCharId) {
        lbl_2_bss_100B8[0x1C + port] = 1;
    } else if (lbl_2_bss_100B8[0x1C + port] != 0) {
        lbl_2_bss_100B8[0x1C + port]++;
        if (lbl_2_bss_100B8[0x1C + port] >= 0xF) {
            lbl_2_bss_100B8[0x14 + port] = 1;
            lbl_2_bss_100B8[0x1C + port] = 0;
            set807518de(port, arg3);
        }
    }
    return lbl_2_bss_100B8[0x1C + port] == 0;
}

// .text:0x000151BC size:0x450 mapped:0x80654250
void captainSelect_BPress(void) {
    return;
}

// .text:0x0001560C size:0x484 mapped:0x806546A0
void captainSelect_APress(void) {
    return;
}

// .text:0x00015A90 size:0x6C mapped:0x80654B24
void fn_2_15A90(int *value, u8 port, int max) {
    u16 input = Static_Stats_Tables.controllerInputs[port].processedInput;
    if (input & 1) {
        (*value)--;
        if (*value < 0) {
            *value = max;
        }
    } else if (input & 2) {
        (*value)++;
        if (*value > max) {
            *value = 0;
        }
    }
}

// .text:0x00015AFC size:0x384 mapped:0x80654B90
void captainSelectScreenInputs(void) {
    return;
}

// .text:0x00015E80 size:0x59C mapped:0x80654F14
void captainSelect_handleInputs(void) {
    return;
}

// .text:0x0001641C size:0x44 mapped:0x806554B0
void onlySetPort1ToActiveOnInitialCapSSLoad(void) {
    fn_2_1A88();
    Static_Stats_Tables.portsActiveInMatch[0] = 0;
    Static_Stats_Tables.portsActiveInMatch[1] = -1;
    Static_Stats_Tables.portsActiveInMatch[2] = -1;
    Static_Stats_Tables.portsActiveInMatch[3] = -1;
    Static_Stats_Tables.player2Ind = 0;
}

// .text:0x00016460 size:0x204 mapped:0x806554F4
void fn_2_16460(void) {
    return;
}

// .text:0x00016664 size:0x68 mapped:0x806556F8
void fn_2_16664(void) {
    int i;
    for (i = 0; i < 4; i++) {
        LITXForm(hugeAnimStruct._AC[i], &lbl_2_bss_10164[0x14]);
    }
}

// .text:0x000166CC size:0x58 mapped:0x80655760
void fn_2_166CC(void) {
    E(u8, STADIUM_ID) savedStadium = g_d_GameSettings.StadiumID;
    g_d_GameSettings.StadiumID = STADIUM_ID_MARIO_STADIUM;
    fn_8001CCC8(fn_8001CB10(lbl_2_data_1DD4, 4));
    g_d_GameSettings.StadiumID = savedStadium;
}

// .text:0x00016724 size:0x14C mapped:0x806557B8
void fn_2_16724(void) {
    return;
}
