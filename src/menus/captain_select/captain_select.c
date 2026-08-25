#include "menus/captain_select/captain_select.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800bd300.h"
#include "Unknown/File_0x80052968.h"
#include "dolphin/mtx.h"
#include "Dolphin/gx.h"

typedef struct {
    /* 0x0000 */ u8 _pad0[0x46F8];
    /* 0x46F8 */ s8 playerNumberByPort[4];
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

typedef struct {
    /* 0x00 */ Mtx viewMtx;
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ float unk40;
    /* 0x44 */ float unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ float unk50;
    /* 0x54 */ int unk54;
} lbl_2_bss_1010C_t; // size: 0x58

extern lbl_2_bss_1010C_t lbl_2_bss_1010C;
extern float lbl_2_data_20F8[];

extern u8 charSelectStruct[0x94];
extern u8 superstarUnlocked[0x130];
extern u8 challengeCaptainCharIDArray[0xC];
extern u8 mapCaptainCursorPositionToCharID[0x350];

int challengeCaptainSelect_returnsCharID(u16 currentHeldInput, u16 newInput, u16 processedInput);
int captainSelect_processCursorMovement_getCharID(int captainIdx, u16 currentHeldInput, u16 newInput, u16 processedInput);
void storeCursorLocOrCharIDs(int arg0, int arg1, int arg2, int arg3, int arg4);

// .text:0x00014574 size:0x21C mapped:0x80653608
void fn_2_14574(controllerInputStruct *input) {
    if (input->processedInput & 8) {
        if (input->currentHeldInput & 0x200) {
            lbl_2_bss_1010C.unk48 += 0.1f;
        } else if (input->currentHeldInput & 0x100) {
            lbl_2_bss_1010C.unk4C += 1.0f;
        } else if (input->currentHeldInput & 0x400) {
            lbl_2_bss_1010C.unk50 += 0.1f;
        }
        return;
    }
    if (input->processedInput & 4) {
        if (input->currentHeldInput & 0x200) {
            lbl_2_bss_1010C.unk48 -= 0.1f;
        } else if (input->currentHeldInput & 0x100) {
            lbl_2_bss_1010C.unk4C -= 1.0f;
        } else if (input->currentHeldInput & 0x400) {
            lbl_2_bss_1010C.unk50 -= 0.1f;
        }
        return;
    }
    if (input->processedInput & 1) {
        if (input->currentHeldInput & 0x200) {
            lbl_2_data_20F8[0] = (float)((double)(320.0f + lbl_2_data_20F8[0]) - 0.1) - 320.0f;
        } else if (input->currentHeldInput & 0x100) {
            lbl_2_data_20F8[1] = (float)((double)(320.0f + lbl_2_data_20F8[1]) - 0.1) - 320.0f;
        }
        return;
    }
    if (input->processedInput & 2) {
        if (input->currentHeldInput & 0x200) {
            lbl_2_data_20F8[0] = (float)((double)(320.0f + lbl_2_data_20F8[0]) + 0.1) - 320.0f;
        } else if (input->currentHeldInput & 0x100) {
            lbl_2_data_20F8[1] = (float)((double)(320.0f + lbl_2_data_20F8[1]) + 0.1) - 320.0f;
        }
    }
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
void captainSelect_handleCursor(u8 port, controllerInputStruct *input) {
    s8 captainIdx;
    int val;
    int charID;
    int i;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && (u8)port != 0) {
            captainIdx = (Static_Stats_Tables.playerNumberByPort[0] == 0);
            charSelectStruct[0x74 + captainIdx] = 1;
        } else {
            captainIdx = Static_Stats_Tables.playerNumberByPort[(u8)port];
            charSelectStruct[0x74 + captainIdx] = 0;
        }

        switch (captainIdx) {
        case 0:
            val = lbl_2_bss_F410[4 + port];
            storeCursorLocOrCharIDs(0, val, -1, -1, -1);
            break;
        case 1:
            val = lbl_2_bss_F410[4 + port];
            storeCursorLocOrCharIDs(0, -1, val, -1, -1);
            break;
        case 2:
            val = lbl_2_bss_F410[4 + port];
            storeCursorLocOrCharIDs(0, -1, -1, val, -1);
            break;
        case 3:
            val = lbl_2_bss_F410[4 + port];
            storeCursorLocOrCharIDs(0, -1, -1, -1, val);
            break;
        }

        charID = captainSelect_processCursorMovement_getCharID(captainIdx, input->currentHeldInput, input->newInput, input->processedInput);

        val = charID;
        for (i = 0; i < 12; i++) {
            if (mapCaptainCursorPositionToCharID[i] == charID) {
                val = i;
                break;
            }
        }
        lbl_2_bss_F410[4 + port] = val;
    } else {
        u8 *table;
        charID = challengeCaptainSelect_returnsCharID(input->currentHeldInput, input->newInput, input->processedInput);
        table = &challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6];
        val = charID;
        for (i = 0; i < 6; i++) {
            if (*table == charID) {
                val = i;
                break;
            }
            table++;
        }
        lbl_2_bss_F410[4 + port] = val;
    }
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
        int t = lbl_2_bss_100B8[0x1C + port] + 1;
        lbl_2_bss_100B8[0x1C + port] = t;
        if ((u8)t >= 0xF) {
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

extern u8 lbl_2_data_19E8[];

void fn_80052D70(void);
void makeLookAtMatrix(Mtx viewMtx, Vec *eye, Vec *up, Vec *at);

// .text:0x00016460 size:0x204 mapped:0x806554F4
void fn_2_16460(void) {
    static const Vec kOffsetVec = { 0.0f, 0.0f, 100.0f };
    Vec offset = kOffsetVec;
    Vec rot;
    Mtx mtxX, mtxY, mtxConcat;
    float cosY, sinY;
    float rx, rz, dx, dz;
    camera_803c639c_s *cam;
    u8 *table;
    Vec *at;
    Vec *eye;

    rot.x = lbl_2_bss_1010C.unk30;
    rot.y = lbl_2_bss_1010C.unk32;
    rot.z = 0.0f;
    PSVECScale(&rot, 0.0000958738f, &rot);

    PSMTXRotRad(mtxX, 'X', rot.x);
    PSMTXRotRad(mtxY, 'Y', rot.y);
    cosY = mtxY[0][0];
    sinY = mtxY[0][2];
    PSMTXConcat(mtxY, mtxX, mtxConcat);
    at = (Vec *)&lbl_2_bss_1010C.unk3C;
    PSMTXMultVec(mtxConcat, &offset, at);

    eye = (Vec *)&lbl_2_bss_1010C.unk48;
    rx = lbl_2_bss_1010C.unk34;
    rz = lbl_2_bss_1010C.unk38;
    dx = rz * sinY - rx * cosY;
    dz = rz * cosY + rx * sinY;
    eye->x += dx;
    eye->z += dz;
    at->x += dx;
    at->y += eye->y;
    at->z += dz;

    fn_80052D70();

    table = lbl_2_data_19E8;
    cam = fn_80052768_getCamera(0);
    cam->eye.x = *(f32 *)(table + 0x418);
    cam->eye.y = *(f32 *)(table + 0x41C);
    cam->eye.z = *(f32 *)(table + 0x420);
    cam->target.x = *(f32 *)(table + 0x424);
    cam->target.y = *(f32 *)(table + 0x428);
    cam->target.z = *(f32 *)(table + 0x42C);

    graphics_relatedToVsScreen();

    makeLookAtMatrix(lbl_2_bss_1010C.viewMtx, eye, (Vec *)(table + 0x430), at);
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

extern float lbl_2_data_20EC[3];

void fn_800B806C(int arg0, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7);

// .text:0x00016724 size:0x14C mapped:0x806557B8
void fn_2_16724(void) {
    Mtx44 frustum;

    lbl_2_bss_1010C.unk48 = lbl_2_data_20EC[0];
    lbl_2_bss_1010C.unk4C = lbl_2_data_20EC[1];
    lbl_2_bss_1010C.unk50 = lbl_2_data_20EC[2];
    lbl_2_bss_1010C.unk3C = 0.0f;
    lbl_2_bss_1010C.unk40 = 0.0f;
    lbl_2_bss_1010C.unk44 = 10.0f;

    C_MTXFrustum(frustum, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(frustum, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -1.0f, 1280.0f);

    lbl_2_bss_1010C.unk54 = 0;
    lbl_2_bss_1010C.unk38 = 0.0f;
    lbl_2_bss_1010C.unk30 = 0;
    lbl_2_bss_1010C.unk32 = 0;
}
