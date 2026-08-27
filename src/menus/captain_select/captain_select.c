#include "menus/captain_select/captain_select.h"
#include "menus/yd_step.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800bd300.h"
#include "Unknown/File_0x80052968.h"
#include "dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "musyx/musyx.h"

typedef struct {
    /* 0x0000 */ u8 _pad0a[0x46E0];
    /* 0x46E0 */ int unk46E0[4];
    /* 0x46F0 */ u8 _pad0b[0x46F8 - 0x46F0];
    /* 0x46F8 */ s8 playerNumberByPort[4];
    /* 0x46FC */ s8 portsActiveInMatch[4];
    /* 0x4700 */ u8 _pad1a[0x4704 - 0x4700];
    /* 0x4704 */ u8 unk4704;
    /* 0x4705 */ u8 _pad1b[0x4729 - 0x4705];
    /* 0x4729 */ u8 player2Ind;
    /* 0x472A */ u8 _pad2[0x2];
    /* 0x472C */ controllerInputStruct controllerInputs[4];
    /* 0x4744 */ u8 _pad3a[0x4757 - 0x4744];
    /* 0x4757 */ u8 unk4757[0x20];
    /* 0x4777 */ u8 _pad3b[0x5240 - 0x4777];
} Static_MSSB_Data; // size: 0x5240

extern Static_MSSB_Data Static_Stats_Tables;
extern u8 lbl_2_bss_100B8[0x54];
extern u8 lbl_2_data_1DD4[0x318];
extern u8 captainIDOrderedOnCapSS[12];
extern int lbl_2_bss_F410[0x16];
extern u8 lbl_803C5EA4[0x3C];
extern u8 cursorPositions[0x5C];

void AnimateCharacter(u8 charId, int animId, int a2, int a3, int a4, int a5, int a6, int a7);
void QueueCharacterAnimation(u8 charId, int animId, int a2, int a3, int a4, int a5, int a6);
int stadiumRandomizer(int min, int max);
void set807518de(u8 port, int arg1);
void add_or_RemoveCharToATeam(int arg0, int arg1, int arg2);

void fn_2_1A88(void);
void *fn_8001CB10(void *arg0, int arg1);
void fn_8001CCC8(void *arg0);

typedef struct {
    /* 0x0000 */ u8 _pad0[0xAC];
    /* 0x00AC */ void *_AC[4];
    /* 0x00BC */ u8 _pad1[0x2C50 - 0xBC];
    /* 0x2C50 */ void *_2C50[4];
    /* 0x2C60 */ u8 _pad2[0x3154 - 0x2C60];
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

extern s8 charSelectStruct[0x94];
extern u8 superstarUnlocked[0x130];
extern u8 challengeCaptainCharIDArray[0xC];
extern u8 mapCaptainCursorPositionToCharID[0x350];

int challengeCaptainSelect_returnsCharID(u16 currentHeldInput, u16 newInput, u16 processedInput);
int captainSelect_processCursorMovement_getCharID(int captainIdx, u16 currentHeldInput, u16 newInput, u16 processedInput);
void storeCursorLocOrCharIDs(int arg0, int arg1, int arg2, int arg3, int arg4);

typedef struct {
    /* 0x00 */ u8 _pad0a[0xE];
    /* 0x0E */ u8 unk0E;
    /* 0x0F */ u8 _pad0b[0x55 - 0xF];
    /* 0x55 */ u8 unk55[4];
    /* 0x59 */ u8 portCaptainSlot[4];
    /* 0x5D */ u8 _pad1[0x64 - 0x5D];
} gameSetUpStruct_t; // size: 0x64

extern gameSetUpStruct_t gameSetUpStep;
extern u8 aiPosSwapInputs[0x24C98];
extern u8 lbl_800EFBA4[0x10];
extern u8 lbl_803CBBC2[0xA];
extern u8 lbl_803CBCD0[0x18];
extern u8 lbl_2_bss_F468[0xC4C];
extern u8 lbl_2_bss_100B4;

extern menuControlStruct *menuControlVariables;

void fn_2_16A74(int idx, int flag);
void cursorSndFx(int arg0);

bool stopShowingCaptainProfile(void);
void updateCharacterSelectProcessCode(int arg0, int arg1);
void challengeCaptainRelated(void);

void fn_2_14220(controllerInputStruct *input);

void fn_8004D4F0(int captainIdx);

extern u8 lbl_2_data_19E8[];

void fn_80052D70(void);
void makeLookAtMatrix(Mtx viewMtx, Vec *eye, Vec *up, Vec *at);

extern float lbl_2_data_20EC[3];

void fn_800B806C(int arg0, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7);

// .text:0x00016724 size:0x14C mapped:0x806557B8
void captainSelect_setupCameraProjection(void) {
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

// .text:0x000166CC size:0x58 mapped:0x80655760
void fn_2_166CC(void) {
    E(u8, STADIUM_ID) savedStadium = g_d_GameSettings.StadiumID;
    g_d_GameSettings.StadiumID = STADIUM_ID_MARIO_STADIUM;
    fn_8001CCC8(fn_8001CB10(lbl_2_data_1DD4, 4));
    g_d_GameSettings.StadiumID = savedStadium;
}

// .text:0x00016664 size:0x68 mapped:0x806556F8
void fn_2_16664(void) {
    int i;
    for (i = 0; i < 4; i++) {
        LITXForm(hugeAnimStruct._AC[i], &lbl_2_bss_10164[0x14]);
    }
}

// .text:0x00016460 size:0x204 mapped:0x806554F4
void fn_2_16460(void) {
    /* The leading -1 reproduces an unused 4-byte literal-pool entry present in
       the original binary's .rodata; removing it shifts every later pool
       constant and breaks the byte match. */
    static const struct { s32 sentinel; Vec v; } kOffsetVec = { -1, { 0.0f, 0.0f, 100.0f } };
    Vec rot;
    Vec offset = kOffsetVec.v;
    Mtx mtxX, mtxY, mtxConcat;
    float cosY, sinY;
    float rx, rz, dx, dz;
    camera_803c639c_s *cam;
    const f32 *table;
    Vec *at;
    Vec *eye;

    rot.x = lbl_2_bss_1010C.unk30;
    rot.y = lbl_2_bss_1010C.unk32;
    rot.z = 0.0f;
    PSVECScale(&rot, 0.0000958738f, &rot);

    PSMTXRotRad(mtxX, 'X', rot.x);
    PSMTXRotRad(mtxY, 'Y', rot.y);
    sinY = mtxY[0][2];
    cosY = mtxY[0][0];
    PSMTXConcat(mtxY, mtxX, mtxConcat);
    at = (Vec *)&lbl_2_bss_1010C.unk3C;
    PSMTXMultVec(mtxConcat, &offset, at);

    eye = (Vec *)&lbl_2_bss_1010C.unk48;
    rx = lbl_2_bss_1010C.unk34;
    rz = lbl_2_bss_1010C.unk38;
    dx = rz * sinY - rx * cosY;
    dz = rz * cosY + rx * sinY;
    lbl_2_bss_1010C.unk48 += dx;
    lbl_2_bss_1010C.unk50 += dz;
    at->x += lbl_2_bss_1010C.unk48;
    lbl_2_bss_1010C.unk40 += lbl_2_bss_1010C.unk4C;
    lbl_2_bss_1010C.unk44 += lbl_2_bss_1010C.unk50;

    fn_80052D70();

    table = (const f32 *)lbl_2_data_19E8;
    cam = fn_80052768_getCamera(0);
    cam->eye.x = table[0x418 / 4];
    cam->eye.y = table[0x41C / 4];
    cam->eye.z = table[0x420 / 4];
    cam->target.x = table[0x424 / 4];
    cam->target.y = table[0x428 / 4];
    cam->target.z = table[0x42C / 4];

    graphics_relatedToVsScreen();

    makeLookAtMatrix(lbl_2_bss_1010C.viewMtx, eye, (Vec *)&table[0x430 / 4], at);
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

// .text:0x00015E80 size:0x59C mapped:0x80654F14
void captainSelect_handleInputs(int port) {
    int cIdx4 = Static_Stats_Tables.playerNumberByPort[(u8)port] + 4;
    u8 slot = gameSetUpStep.portCaptainSlot[(u8)port];
    u8 p = (u8)port;
    controllerInputStruct input;

    if (lbl_2_bss_100B8[0x19] == 0 || lbl_2_bss_100B8[0x1A] != 0 ||
        gameSetUpStep.unk55[p] != 0 ||
        aiPosSwapInputs[0xCF5D + slot] != 0) {
        input.processedInput = 0;
        input.newInput = 0;
        input.currentHeldInput = 0;
        goto commonTail;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && lbl_803CBBC2[5] == 1) {
        input.processedInput = 0;
        input.newInput = 0;
        input.currentHeldInput = 0;
        goto commonTail;
    }

    if (lbl_2_bss_100B8[0x10 + slot] != 0) {
        input.currentHeldInput = Static_Stats_Tables.controllerInputs[p].currentHeldInput & 0x200;
        input.newInput = Static_Stats_Tables.controllerInputs[p].newInput & 0x200;
        input.processedInput = Static_Stats_Tables.controllerInputs[p].processedInput & 0x200;
        goto callScreenInputs;
    }

    if (lbl_2_bss_F468[0x45 + slot] != 0) {
        u16 newI = Static_Stats_Tables.controllerInputs[p].newInput;
        if (newI & 0x2) {
            if (lbl_2_bss_F468[0x47 + slot] == 0) {
                lbl_2_bss_F468[0x47 + slot] = 1;
                lbl_2_bss_F468[0x49 + slot] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            input.currentHeldInput = 0;
            input.newInput = 0;
            input.processedInput = 0;
        } else if (newI & 0x1) {
            if (lbl_2_bss_F468[0x47 + slot] == 1) {
                lbl_2_bss_F468[0x47 + slot] = 0;
                lbl_2_bss_F468[0x49 + slot] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            input.currentHeldInput = 0;
            input.newInput = 0;
            input.processedInput = 0;
        } else {
            if (newI != 0 && !(newI & 8) && !(newI & 4)) {
                lbl_2_bss_F468[0x45 + slot] = 0;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
            input.currentHeldInput = 0;
            input.newInput = 0;
            input.processedInput = 0;
        }
    } else {
        input.currentHeldInput = Static_Stats_Tables.controllerInputs[p].currentHeldInput;
        input.newInput = Static_Stats_Tables.controllerInputs[p].newInput;
        input.processedInput = Static_Stats_Tables.controllerInputs[p].processedInput;
    }

commonTail:
    lbl_2_bss_100B8[0x4A] = 0;
    lbl_2_bss_100B8[0x4B] = 0;

    if (lbl_2_bss_100B8[0x4A] != 0) {
        if (lbl_2_bss_100B8[0x4A] != 0) {
            lbl_2_bss_100B8[0x4A] = 0;
            return;
        }
        fn_2_14574(&input);
        return;
    }
    if (lbl_2_bss_100B8[0x4A] != 0) {
        fn_2_14220(&input);
        return;
    }

    if (menuControlVariables->previousScreen == 0xA &&
        Static_Stats_Tables.unk46E0[p] != -1 &&
        g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        int i;
        add_or_RemoveCharToATeam(0, mapCaptainCursorPositionToCharID[lbl_2_bss_F410[4]], 1);
        for (i = 0; i < 2; i++) {
            s8 cIdx = Static_Stats_Tables.playerNumberByPort[i];
            switch (cIdx) {
            case 0:
                storeCursorLocOrCharIDs(0, lbl_2_bss_F410[4 + i], -1, -1, -1);
                break;
            case 1:
                storeCursorLocOrCharIDs(0, -1, lbl_2_bss_F410[4 + i], -1, -1);
                break;
            case 2:
                storeCursorLocOrCharIDs(0, -1, -1, lbl_2_bss_F410[4 + i], -1);
                break;
            case 3:
                storeCursorLocOrCharIDs(0, -1, -1, -1, lbl_2_bss_F410[4 + i]);
                break;
            }
        }
    }

    if (lbl_2_bss_100B8[0x10 + slot] != 0 && input.currentHeldInput == 0 && input.newInput == 0) {
        goto callScreenInputs;
    }

    {
        int *cur = &lbl_2_bss_F410[slot];
        cursorPositions[p] = cur[4];
    }
    {
        int origVal = lbl_2_bss_F410[cIdx4];
        int prevVal, curVal, mappedID;
        do {
            prevVal = lbl_2_bss_F410[cIdx4];
            captainSelect_handleCursor(slot, &input);
            curVal = lbl_2_bss_F410[cIdx4];
            mappedID = mapCaptainCursorPositionToCharID[curVal];
        } while (Static_Stats_Tables.unk4757[mappedID] != 0 && origVal != curVal && prevVal != curVal);
    }

    if (lbl_2_bss_F410[4 + (u8)port] == lbl_2_bss_F410[4 + ((u8)port ^ 1)]) {
        if (lbl_803C5EA4[5] != 0) {
            lbl_2_bss_F410[cIdx4]++;
            if (lbl_2_bss_F410[cIdx4] >= 0xC) {
                lbl_2_bss_F410[cIdx4] = 0;
            }
            return;
        }
    }

    if ((input.processedInput & 0xF) == 0 || (input.processedInput & 0x20) != 0) {
    callScreenInputs:
        captainSelectScreenInputs((u8)port, input.currentHeldInput, input.newInput, input.processedInput);
        return;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (input.processedInput & 0x3) {
            challengeCaptainRelated();
            updateCharacterSelectProcessCode(0, 3);
            lbl_803CBBC2[2] = 3;
        }
        return;
    }
    if (input.newInput & 0x1000) {
        return;
    }
    if (input.processedInput & 0xF) {
        updateCharacterSelectProcessCode(slot, 3);
    }
}

// .text:0x00015AFC size:0x384 mapped:0x80654B90
void captainSelectScreenInputs(int port, u16 currentHeldInput, u16 newInput, u16 processedInput) {
    if (Static_Stats_Tables.playerNumberByPort[port] == -1) {
        return;
    }

    if (aiPosSwapInputs[0xCF5D + gameSetUpStep.portCaptainSlot[port]] != 0) {
        s8 capIdx;
        int charID;
        int val;
        int i;
        u8 tmpCapIdx[4];
        u8 idxVal = gameSetUpStep.portCaptainSlot[port];

        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && gameSetUpStep.portCaptainSlot[0] == 1) {
            tmpCapIdx[idxVal] = gameSetUpStep.portCaptainSlot[0];
        } else {
            tmpCapIdx[idxVal] = Static_Stats_Tables.playerNumberByPort[idxVal];
        }
        capIdx = tmpCapIdx[idxVal];

        if ((u32)charSelectStruct[0x7F + capIdx] >> 31) {
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                charID = captainSelect_processCursorMovement_getCharID(capIdx, currentHeldInput, newInput, processedInput);
                val = charID;
                for (i = 0; i < 12; i++) {
                    if (mapCaptainCursorPositionToCharID[i] == charID) {
                        val = i;
                        break;
                    }
                }
                lbl_2_bss_F410[4 + gameSetUpStep.portCaptainSlot[port]] = val;
                updateCharacterSelectProcessCode(gameSetUpStep.portCaptainSlot[port], 3);
            } else {
                u8 *table;
                charID = challengeCaptainSelect_returnsCharID(currentHeldInput, newInput, processedInput);
                table = &challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6];
                val = charID;
                for (i = 0; i < 6; i++) {
                    if (charID == *table) {
                        val = i;
                        break;
                    }
                    table++;
                }
                lbl_2_bss_F410[4] = val;
                challengeCaptainRelated();
                lbl_803CBBC2[2] = 3;
            }
            aiPosSwapInputs[0xCF5D + gameSetUpStep.portCaptainSlot[port]] = 0;
        }
        return;
    }

    if (aiPosSwapInputs[0xCF5D + gameSetUpStep.portCaptainSlot[port]] != 0) {
        return;
    }

    if (newInput & 0x100) {
        if (!stopShowingCaptainProfile()) {
            captainSelect_APress(gameSetUpStep.portCaptainSlot[port]);
        }
        return;
    }
    if (newInput & 0x200) {
        if (!stopShowingCaptainProfile()) {
            captainSelect_BPress(gameSetUpStep.portCaptainSlot[port]);
        }
        return;
    }
    if (newInput & 0x20) {
        if (!stopShowingCaptainProfile()) {
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                aiPosSwapInputs[0xCF5D + gameSetUpStep.portCaptainSlot[port]] = 1;
            }
        }
        return;
    }
    if (newInput & 0x10) {
        if (!stopShowingCaptainProfile()) {
            if (lbl_2_bss_100B8[gameSetUpStep.portCaptainSlot[port] + 0x10] == 0) {
                lbl_2_bss_F468[gameSetUpStep.portCaptainSlot[port] + 0x45] = 1;
                lbl_2_bss_F468[gameSetUpStep.portCaptainSlot[port] + 0x4B] = 1;
                lbl_2_bss_F468[gameSetUpStep.portCaptainSlot[port] + 0x47] = 0;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
            }
        }
    }
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

// .text:0x0001560C size:0x484 mapped:0x806546A0
void captainSelect_APress(int idx) {
    int charID;
    int val;
    u8 c;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (lbl_2_bss_100B8[0x1C] != 0 || lbl_2_bss_100B8[0x42] != 0) {
            return;
        }

        charID = challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6 + lbl_2_bss_F410[4]];
        lbl_2_bss_100B8[0x10] = 1;
        Static_Stats_Tables.unk46E0[0] = charID;
        lbl_2_bss_100B8[0x12] = 1;
        fn_8004D4F0(Static_Stats_Tables.playerNumberByPort[0]);
        AnimateCharacter(0, 0x6A, 0, 1, 1, 0, 0, -1);
        QueueCharacterAnimation(0, 0x6B, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8[0x40] = 0;
        menuControlVariables->currentState = 4;
        return;
    }

    c = idx;

    if (lbl_2_bss_100B8[0x1C + c] != 0 || lbl_2_bss_100B8[0x42 + c] != 0) {
        return;
    }

    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        void *model = hugeAnimStruct._2C50[c];
        if (*((u8 *)model + 0x25D) == 0 && c != 0) {
            return;
        }
    }

    {
        u8 a = idx;
        AnimateCharacter(a, 0x6A, 0, 1, 1, 0, 0, -1);
        QueueCharacterAnimation(a, 0x6B, 1, 1, 0, 0, -1);
    }
    lbl_2_bss_100B8[0x40 + c] = 0;
    if (lbl_2_bss_100B8[0x10 + c] != 0) {
        return;
    }

    charID = mapCaptainCursorPositionToCharID[lbl_2_bss_F410[4 + (u8)idx]];
    Static_Stats_Tables.unk46E0[c] = charID;

    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && (u8)idx != 0) {
        if (Static_Stats_Tables.playerNumberByPort[0] == 0) {
            add_or_RemoveCharToATeam(1, Static_Stats_Tables.unk46E0[c], 1);
        } else {
            add_or_RemoveCharToATeam(0, Static_Stats_Tables.unk46E0[c], 1);
        }
    } else {
        add_or_RemoveCharToATeam(Static_Stats_Tables.playerNumberByPort[c], Static_Stats_Tables.unk46E0[c], 1);
    }

    charID = mapCaptainCursorPositionToCharID[lbl_2_bss_F410[4 + (u8)idx]];
    lbl_2_bss_100B8[0x10 + c] = 1;
    lbl_2_bss_100B8[0x12 + c] = 1;
    Static_Stats_Tables.unk4757[charID] = 1;

    if ((u8)idx != 0) {
        return;
    }
    if (g_d_GameSettings.p2_CPU_match_code != P2_CPU_CODE_1_PLAYER_GAME) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        return;
    }

    {
        int captainIdx;

        updateCharacterSelectProcessCode(1, 6);

        captainIdx = (Static_Stats_Tables.playerNumberByPort[0] == 0);
        gameSetUpStep.portCaptainSlot[c] = 1;
        charSelectStruct[0x74 + captainIdx] = 1;

        if (lbl_2_bss_F410[4] == 0) {
            lbl_2_bss_F410[5] = 1;
        } else {
            lbl_2_bss_F410[5] = 0;
        }

        switch (captainIdx) {
        case 0:
            val = lbl_2_bss_F410[5];
            storeCursorLocOrCharIDs(0, val, -1, -1, -1);
            break;
        case 1:
            val = lbl_2_bss_F410[5];
            storeCursorLocOrCharIDs(0, -1, val, -1, -1);
            break;
        case 2:
            val = lbl_2_bss_F410[5];
            storeCursorLocOrCharIDs(0, -1, -1, val, -1);
            break;
        case 3:
            val = lbl_2_bss_F410[5];
            storeCursorLocOrCharIDs(0, -1, -1, -1, val);
            break;
        }
    }

    val = lbl_2_bss_F410[5];
    cursorPositions[1] = val;
    if (val != -1) {
        lbl_2_bss_100B8[0x1D] = 1;
        return;
    }
    if (lbl_2_bss_100B8[0x1D] != 0) {
        int t = lbl_2_bss_100B8[0x1D] + 1;
        lbl_2_bss_100B8[0x1D] = t;
        if ((u8)t >= 0xF) {
            lbl_2_bss_100B8[0x15] = 1;
            lbl_2_bss_100B8[0x1D] = 0;
            set807518de(1, 1);
        }
    }
}

// .text:0x000151BC size:0x450 mapped:0x80654250
void captainSelect_BPress(int idx) {
    u8 c = idx;

    if (lbl_2_bss_100B8[0x10 + c] != 0) {
        lbl_2_bss_100B8[0x10 + c] = 0;
        lbl_2_bss_100B8[0x12 + c] = 0;
        Static_Stats_Tables.unk4757[Static_Stats_Tables.unk46E0[c]] = 0;
        add_or_RemoveCharToATeam((u8)idx, Static_Stats_Tables.unk46E0[c], 0);
        goto exit;
    }

    if (c != 0) {
        if (aiPosSwapInputs[0xCF5D + c] != 0) {
            aiPosSwapInputs[0xCF5D + c] = 0;
        }

        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
            int other;

            fn_2_16A74((u8)idx, 0);
            charSelectStruct[0x7F + Static_Stats_Tables.playerNumberByPort[gameSetUpStep.portCaptainSlot[0]]] = -1;
            Static_Stats_Tables.unk4757[Static_Stats_Tables.unk46E0[0]] = 0;
            lbl_2_bss_100B8[0x10] = 0;
            lbl_2_bss_100B8[0x12] = 0;
            gameSetUpStep.portCaptainSlot[0] = 0;
            add_or_RemoveCharToATeam(0, Static_Stats_Tables.unk46E0[0], 0);
            Static_Stats_Tables.unk46E0[0] = -1;
            Static_Stats_Tables.unk46E0[1] = -1;
            updateCharacterSelectProcessCode(0, 4);

            other = (u8)idx ^ 1;
            AnimateCharacter(other, 0x69, 1, 1, 1, 0, 0, -1);
            lbl_2_bss_100B8[0x40 + (u8)other] = 1;
        } else {
            u8 v10 = lbl_2_bss_100B8[0x10];

            Static_Stats_Tables.portsActiveInMatch[Static_Stats_Tables.playerNumberByPort[1]] = 1;
            if (v10 != 0) {
                gameSetUpStep.portCaptainSlot[1] = 1;
                gameSetUpStep.portCaptainSlot[0] = 1;
            } else {
                gameSetUpStep.portCaptainSlot[1] = 0;
                gameSetUpStep.portCaptainSlot[0] = 0;
            }

            lbl_803C5EA4[5] = 0;
            charSelectStruct[0x7F + Static_Stats_Tables.playerNumberByPort[gameSetUpStep.portCaptainSlot[c]]] = -1;

            if (menuControlVariables->previousScreen == 0xa && v10 == 0) {
                Static_Stats_Tables.unk4757[Static_Stats_Tables.unk46E0[0]] = 0;
                add_or_RemoveCharToATeam(0, Static_Stats_Tables.unk46E0[0], 0);
                Static_Stats_Tables.unk46E0[0] = -1;
                Static_Stats_Tables.unk46E0[1] = -1;
            }

            lbl_2_bss_100B8[0x10 + c] = 0;
            lbl_2_bss_100B8[0x12 + c] = 0;
            gameSetUpStep.portCaptainSlot[c] = 0;

            if (lbl_2_bss_100B8[0x10] != 0) {
                updateCharacterSelectProcessCode((u8)idx, 5);
            } else {
                updateCharacterSelectProcessCode((u8)idx, 4);
            }
        }
        goto exit;
    }

    charSelectStruct[0x7F + Static_Stats_Tables.playerNumberByPort[0]] = -1;
    if (Static_Stats_Tables.playerNumberByPort[1] != -1) {
        charSelectStruct[0x7F + Static_Stats_Tables.playerNumberByPort[1]] = -1;
    }

    aiPosSwapInputs[0xCF5E] = 0;
    aiPosSwapInputs[0xCF5D] = 0;
    lbl_2_bss_100B4 = 1;

    {
        int i;
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            fn_2_16A74(i, 0);
        }
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        lbl_803CBBC2[2] = 2;
    } else {
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
            updateCharacterSelectProcessCode(0, 2);
            updateCharacterSelectProcessCode(1, 2);
        } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_2_PLAYER_GAME) {
            updateCharacterSelectProcessCode(0, 2);
            updateCharacterSelectProcessCode(1, 2);
        }
        lbl_803CBCD0[0xA] = 0x14;
    }

    lbl_2_bss_F468[0x46] = 0;
    lbl_2_bss_F468[0x45] = 0;
    menuControlVariables->currentState = 8;

exit:
    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_2_PLAYER_GAME) {
        AnimateCharacter((u8)idx, 0x69, 1, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8[0x40 + c] = 1;
    }
    cursorSndFx(0x200);
}

// .text:0x00015104 size:0xB8 mapped:0x80654198
BOOL loadNewCaptainModelOnCapSelectScreen(int currentCharId, int newCharId, int port, int arg3) {
    if (newCharId != currentCharId) {
        lbl_2_bss_100B8[0x1C + (u8)port] = 1;
    } else if (lbl_2_bss_100B8[0x1C + (u8)port] != 0) {
        if (++lbl_2_bss_100B8[0x1C + (u8)port] >= 0xF) {
            lbl_2_bss_100B8[0x14 + (u8)port] = 1;
            lbl_2_bss_100B8[0x1C + (u8)port] = 0;
            set807518de((u8)port, arg3);
        }
    }
    return lbl_2_bss_100B8[0x1C + (u8)port] == 0;
}

// .text:0x000150D0 size:0x34 mapped:0x80654164
void fn_2_150D0(u8 idx) {
    if (lbl_2_bss_100B8[0x14 + idx] == 0) {
        lbl_2_bss_100B8[0x14 + idx] = 1;
        lbl_2_bss_100B8[0x1C + idx] = 0;
    }
}

// .text:0x00014FB8 size:0x118 mapped:0x8065404C
void captainSelect_randomizeCaptainForSlot(int slot) {
    int chosen[2];
    int i;

    chosen[0] = captainIDOrderedOnCapSS[lbl_2_bss_F410[4]];
    chosen[1] = captainIDOrderedOnCapSS[lbl_2_bss_F410[5]];
    do {
        chosen[slot] = stadiumRandomizer(0, 0x13);
        for (i = 0; i < 12; i++) {
            if (captainIDOrderedOnCapSS[i] == chosen[slot]) {
                break;
            }
        }
    } while (i == 12 || chosen[0] == chosen[1]);
    {
        int *entry = &lbl_2_bss_F410[slot];
        entry[4] = i;
    }
}

// .text:0x00014CA0 size:0x318 mapped:0x80653D34
void captainSelect_handleCursor(u8 port, controllerInputStruct *input) {
    int captainIdx;
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
            if (charID == *table) {
                val = i;
                break;
            }
            table++;
        }
        lbl_2_bss_F410[4] = val;
    }
}

// .text:0x00014BB8 size:0xE8 mapped:0x80653C4C
void fn_2_14BB8(int port, int state) {
    switch (state) {
    case 0: {
        u8 c = port;
        AnimateCharacter((u8)port, 0x6A, 0, 1, 1, 0, 0, -1);
        QueueCharacterAnimation((u8)port, 0x6B, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8[0x40 + c] = 0;
        break;
    }
    case 1:
        AnimateCharacter(port, 0x69, 1, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8[0x40 + (u8)port] = 1;
        break;
    }
}

// .text:0x00014790 size:0x428 mapped:0x80653824
void checkForNewPlayer(void) {
    s8 newPlayerPort;
    s8 captainIdx;
    int prevID;
    int val;

    newPlayerPort = -1;

    if (lbl_2_bss_100B8[0x19] == 0) {
        return;
    }
    if (lbl_2_bss_100B8[0x1a] != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        return;
    }
    if (gameSetUpStep.unk0E == 1) {
        return;
    }

    {
        const u8 *inputBase = (const u8 *)&AtBat_ButtonInput1;
        int i;
        for (i = 1; i < 4; i++) {
            if (Static_Stats_Tables.portsActiveInMatch[i] &&
                (*(const u16 *)(inputBase + i * 0x20 + 2) & 0x100)) {
                newPlayerPort = i;
                break;
            }
        }
    }
    if (newPlayerPort == -1) {
        return;
    }

    if (lbl_803C5EA4[5] != 0) {
        return;
    }

    if (lbl_2_bss_100B8[0x11] != 0) {
        lbl_2_bss_100B8[0x11] = 0;
        lbl_2_bss_100B8[0x13] = 0;
        add_or_RemoveCharToATeam(1, Static_Stats_Tables.unk46E0[1], 0);
        Static_Stats_Tables.unk4757[Static_Stats_Tables.unk46E0[1]] = 0;
        Static_Stats_Tables.unk46E0[1] = -1;
    }

    Static_Stats_Tables.portsActiveInMatch[newPlayerPort] = 0;
    Static_Stats_Tables.playerNumberByPort[newPlayerPort] = Static_Stats_Tables.playerNumberByPort[1];
    lbl_803C5EA4[5] = 1;
    Static_Stats_Tables.playerNumberByPort[1] = newPlayerPort;
    gameSetUpStep.portCaptainSlot[0] = 0;
    gameSetUpStep.portCaptainSlot[1] = 1;

    if (Static_Stats_Tables.unk4757[0] != 0 || lbl_2_bss_F410[4] == 0) {
        cursorPositions[1] = 1;
    } else {
        cursorPositions[1] = 0;
    }

    charSelectStruct[0x74 + Static_Stats_Tables.playerNumberByPort[1]] = 0;
    updateCharacterSelectProcessCode(1, 1);

    charSelectStruct[0x80] = -1;
    g_d_GameSettings.p2_CPU_match_code = P2_CPU_CODE_2_PLAYER_GAME;
    aiPosSwapInputs[0xCF5E] = 0;
    if (lbl_2_bss_F410[4] == 0) {
        lbl_2_bss_F410[5] = 1;
    } else {
        lbl_2_bss_F410[5] = 0;
    }

    captainIdx = Static_Stats_Tables.playerNumberByPort[1];
    charSelectStruct[0x74 + captainIdx] = 0;
    switch (captainIdx) {
    case 0:
        val = lbl_2_bss_F410[5];
        storeCursorLocOrCharIDs(0, val, -1, -1, -1);
        break;
    case 1:
        val = lbl_2_bss_F410[5];
        storeCursorLocOrCharIDs(0, -1, val, -1, -1);
        break;
    case 2:
        val = lbl_2_bss_F410[5];
        storeCursorLocOrCharIDs(0, -1, -1, val, -1);
        break;
    case 3:
        val = lbl_2_bss_F410[5];
        storeCursorLocOrCharIDs(0, -1, -1, -1, val);
        break;
    }

    prevID = -1;
    goto checkForNewPlayer_loopTest;
    do {
        prevID = lbl_2_bss_F410[5];
checkForNewPlayer_loopTest:
        if (prevID != lbl_2_bss_F410[5]) {
            lbl_2_bss_100B8[0x1D] = 1;
        } else if (lbl_2_bss_100B8[0x1D] != 0) {
            int t = lbl_2_bss_100B8[0x1D] + 1;
            lbl_2_bss_100B8[0x1D] = t;
            if ((u8)t >= 0xF) {
                lbl_2_bss_100B8[0x15] = 1;
                lbl_2_bss_100B8[0x1D] = 0;
                set807518de(1, 1);
            }
        }
    } while (lbl_2_bss_100B8[0x1D] != 0);

    Static_Stats_Tables.unk4704 = 0;
    if (lbl_2_bss_F468[0x46] != 0) {
        lbl_2_bss_F468[0x46] = 0;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    }
    Static_Stats_Tables.controllerInputs[1].processedInput = 0;
    Static_Stats_Tables.controllerInputs[1].newInput = 0;
    Static_Stats_Tables.controllerInputs[1].currentHeldInput = 0;
    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
}

static f32 stepValueDown(f32 v) {
    return (f32)((f64)(320.0f + v) - 0.1) - 320.0f;
}

static f32 stepValueUp(f32 v) {
    return (f32)((f64)(320.0f + v) + 0.1) - 320.0f;
}

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
            lbl_2_bss_1010C.unk4C -= 0.1f;
        } else if (input->currentHeldInput & 0x400) {
            lbl_2_bss_1010C.unk50 -= 0.1f;
        }
        return;
    }
    if (input->processedInput & 1) {
        if (input->currentHeldInput & 0x200) {
            lbl_2_data_20F8[0] = stepValueDown(lbl_2_data_20F8[0]);
        } else if (input->currentHeldInput & 0x100) {
            lbl_2_data_20F8[1] = stepValueDown(lbl_2_data_20F8[1]);
        }
        return;
    }
    if (input->processedInput & 2) {
        if (input->currentHeldInput & 0x200) {
            lbl_2_data_20F8[0] = stepValueUp(lbl_2_data_20F8[0]);
        } else if (input->currentHeldInput & 0x100) {
            lbl_2_data_20F8[1] = stepValueUp(lbl_2_data_20F8[1]);
        }
    }
}
