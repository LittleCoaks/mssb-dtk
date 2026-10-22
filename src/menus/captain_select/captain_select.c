#include "menus/captain_select/captain_select.h"
#include "menus/yd_step.h"
#include "menus/debug_menu_text.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "C3/light/light.h"
#include "Unknown/File_0x80052968.h"
#include "dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "musyx/musyx.h"
#include "Unknown/File_0x800625a4.h"
#include "menus/text_0323C.h"

#define DPAD_MASK (INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT | INPUT_BUTTON_DOWN | INPUT_BUTTON_UP)

extern u8 lbl_2_bss_100B8[0x54];
extern u8 captainIDOrderedOnCapSS[12];
extern int menuCursors[0x16];

void AnimateCharacter(u8 charId, int animId, int a2, int a3, int a4, int a5, int a6, int a7);
void QueueCharacterAnimation(u8 charId, int animId, int a2, int a3, int a4, int a5, int a6);
int stadiumRandomizer(int min, int max);
void set807518de(u8 port, int arg1);
void add_or_RemoveCharToATeam(int team, int charID, BOOL add);

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
extern u8 lbl_800EFBA4[0x10];
extern u8 lbl_803CBBC4[8];
extern u8 lbl_803CBCD8[0x8];
extern u8 lbl_2_bss_F468[0xC4C];
extern u8 lbl_2_bss_100B4;

extern menuControlStruct *menuControlVariables;

void fn_2_16A74(u32 idx, int flag);
void cursorSndFx(int arg0);

void challengeCaptainRelated(void);

void fn_2_14220(controllerInputStruct *input);

void fn_8004D4F0(int team, int charID, BOOL add);


void fn_80052D70(void);
void makeLookAtMatrix(Mtx viewMtx, Vec *eye, Vec *up, Vec *at);

extern float lbl_2_data_20EC[3];

void fn_800B806C(int arg0, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7);

const s32 lbl_2_rodata_500 = -1;


DebugMenuText lbl_2_data_19E8 = {
    { "BAT FIRST", "BAT LAST" },
    "FL",
    "PC",
    { "RR", "RL", "LR", "LL" },
    { "OFF", "ON" },
    { "SELECT DEBUG MENU", "HIDE CHARA SET", "STAR PLAYER SET", "KOOPA STA FLAG SET", "CHALLE LEVEL FREE SET" },
    { "1P >", "COM1>", "2P >", "COM2>", "3P >", "COM3>", "4P >", "COM4>" },
    { 0x0000FF0F, 0x0000880F, 0x00000FFF, 0x0000088F, 0x0000F0FF, 0x0000808F, 0x0000F00F, 0x0000800F },
    { 0, 4, 10, 6, 2, 9, 1, 5, 11, 17, 3, 19 },
    { 0, 2, 6, 8, 4, 10, 1, 3, 7, 5, 9, 11 },
    { 0, 0, 6, 2, 8, 4, 10, 5, 11, 3, 9, 1, 7, 0, 0, 0 },
};

u8 lbl_2_data_1CAC[0x28] = {
    2, 5, 4, 3, 8, 3, 4, 5, 2, 6,
    0, 1, 8, 6, 7, 1, 2, 0, 7, 4,
    4, 3, 1, 2, 5, 1, 2, 4, 6, 8,
    7, 6, 8, 5, 3, 3, 5, 7, 4, 6,
};

u32 MenuCommonTexFiles_captainSelect[0x100 / 4] = {
    0x0000040B, 0x4037CF5C, 0x18B3A800, 0x00208AF0,
    0x0000040B, 0x400ADFFC, 0x18AEE800, 0x0004BAB0,
    0x0000040B, 0x400193E8, 0x191B8800, 0x000089D8,
    0x0000040B, 0x4010E5A0, 0x0E97A800, 0x0009BCAC,
    0x0000040B, 0x40016980, 0x0EA16800, 0x0000D6C4,
    0x0000040B, 0x40016980, 0x0EA24000, 0x0000C944,
    0x0000040B, 0x40016980, 0x0EA31000, 0x0000E700,
    0x0000040B, 0x40016980, 0x0EA3F800, 0x0000D64C,
    0x0000040B, 0x40016980, 0x0EA4D000, 0x0000C900,
    0x0000040B, 0x40016980, 0x0EA5A000, 0x0000CFFC,
    0x0000040B, 0x40016980, 0x0EA67000, 0x0000D720,
    0x0000040B, 0x40016980, 0x0EA74800, 0x0000D6CC,
    0x0000040B, 0x40016980, 0x0EA82000, 0x0000D21C,
    0x0000040B, 0x40016980, 0x0EA8F800, 0x0000D0BC,
    0x0000040B, 0x40016980, 0x0EA9D000, 0x0000B544,
    0x0000040B, 0x40016980, 0x0EAA8800, 0x0000C4F8
};

u8 lbl_2_data_1DD4[0x2C] = {
    0x00, 0xC8, 0x06, 0xEF, 0x0E, 0x87, 0xFF, 0xFF, 0xE4, 0x00, 0x00, 0xC8,
    0x05, 0x23, 0x02, 0x86, 0x96, 0x8C, 0x82, 0x00, 0x00, 0xC8, 0x04, 0x4A,
    0x0A, 0x44, 0x58, 0x58, 0x58, 0x00, 0x00, 0xC8, 0x01, 0x53, 0x06, 0x01,
    0x21, 0x42, 0x2D, 0x00, 0x64, 0x72, 0x6C, 0xFF
};

static Vec captainSelect_cameraEye = { 0.0f, 0.0f, -16.5f };
static Vec captainSelect_cameraTarget = { 0.0f, 0.0f, 0.0f };
static Vec captainSelect_cameraUp = { 0.0f, 1.0f, 0.0f };

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
    Vec rot;
    Vec offset = { 0.0f, 0.0f, 100.0f };
    Mtx mtxX, mtxY, mtxConcat;
    float cosY, sinY;
    float rx, rz, dx, dz;
    camera_803c639c_s *cam;
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

    cam = fn_80052768_getCamera(0);
    cam->eye.x = captainSelect_cameraEye.x;
    cam->eye.y = captainSelect_cameraEye.y;
    cam->eye.z = captainSelect_cameraEye.z;
    cam->target.x = captainSelect_cameraTarget.x;
    cam->target.y = captainSelect_cameraTarget.y;
    cam->target.z = captainSelect_cameraTarget.z;

    graphics_relatedToVsScreen();

    makeLookAtMatrix(lbl_2_bss_1010C.viewMtx, eye, &captainSelect_cameraUp, at);
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
    int slot = gameSetUpStep.portCaptainSlot[(u8)port];
    u8 p = (u8)port;
    controllerInputStruct input;

    if (lbl_2_bss_100B8[0x19] == 0 || lbl_2_bss_100B8[0x1A] != 0 ||
        gameSetUpStep.unk55[p] != 0 ||
        aiPosSwapInputs.capSS_isRandomizingCursor[slot] != 0) {
        input.processedInput = 0;
        input.newInput = 0;
        input.currentHeldInput = 0;
        goto commonTail;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && lbl_803CBBC4[3] == 1) {
        input.processedInput = 0;
        input.newInput = 0;
        input.currentHeldInput = 0;
        goto commonTail;
    }

    if (lbl_2_bss_100B8[0x10 + slot] != 0) {
        input.currentHeldInput = Static_Stats_Tables.controllerInputs[p].currentHeldInput & INPUT_BUTTON_B;
        input.newInput = Static_Stats_Tables.controllerInputs[p].newInput & INPUT_BUTTON_B;
        input.processedInput = Static_Stats_Tables.controllerInputs[p].processedInput & INPUT_BUTTON_B;
        goto callScreenInputs;
    }

    if (lbl_2_bss_F468[0x45 + slot] != 0) {
        u16 newI = Static_Stats_Tables.controllerInputs[p].newInput;
        if (newI & INPUT_BUTTON_RIGHT) {
            if (lbl_2_bss_F468[0x47 + slot] == 0) {
                lbl_2_bss_F468[0x47 + slot] = 1;
                lbl_2_bss_F468[0x49 + slot] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            input.currentHeldInput = 0;
            input.newInput = 0;
            input.processedInput = 0;
        } else if (newI & INPUT_BUTTON_LEFT) {
            if (lbl_2_bss_F468[0x47 + slot] == 1) {
                lbl_2_bss_F468[0x47 + slot] = 0;
                lbl_2_bss_F468[0x49 + slot] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            input.currentHeldInput = 0;
            input.newInput = 0;
            input.processedInput = 0;
        } else {
            if (newI != 0 && !(newI & INPUT_BUTTON_UP) && !(newI & INPUT_BUTTON_DOWN)) {
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
        Static_Stats_Tables.captainSelectedID[(u8)port] != CHAR_ID_NONE &&
        g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        int i;
        add_or_RemoveCharToATeam(0, mapCaptainCursorPositionToCharID[menuCursors[4]], TRUE);
        for (i = 0; i < 2; i++) {
            s8 cIdx = Static_Stats_Tables.playerNumberByPort[i];
            switch (cIdx) {
            case 0:
                storeCursorLocOrCharIDs(0, menuCursors[4 + i], -1, -1, -1);
                break;
            case 1:
                storeCursorLocOrCharIDs(0, -1, menuCursors[4 + i], -1, -1);
                break;
            case 2:
                storeCursorLocOrCharIDs(0, -1, -1, menuCursors[4 + i], -1);
                break;
            case 3:
                storeCursorLocOrCharIDs(0, -1, -1, -1, menuCursors[4 + i]);
                break;
            }
        }
    }

    if (lbl_2_bss_100B8[0x10 + slot] != 0 && input.currentHeldInput == 0 && input.newInput == 0) {
        goto callScreenInputs;
    }

    {
        int *cur = &menuCursors[slot];
        cursorPositions.cursor[p] = cur[4];
    }
    {
        int prevVal, curVal, mappedID;
        int origVal = menuCursors[cIdx4];
        do {
            prevVal = menuCursors[cIdx4];
            captainSelect_handleCursor(slot, &input);
            curVal = menuCursors[cIdx4];
            mappedID = mapCaptainCursorPositionToCharID[curVal];
        } while (Static_Stats_Tables.charOnCharacterGridSelected[mappedID] != 0 && origVal != curVal && prevVal != curVal);
    }

    if (menuCursors[4 + (u8)port] == menuCursors[4 + ((u8)port ^ 1)]) {
        if (g_MatchInfo.player2Ind2 != 0) {
            menuCursors[cIdx4]++;
            if (menuCursors[cIdx4] >= 0xC) {
                menuCursors[cIdx4] = 0;
            }
            return;
        }
    }

    if ((input.processedInput & DPAD_MASK) == 0 || (input.processedInput & INPUT_TRIGGER_R) != 0) {
    callScreenInputs:
        captainSelectScreenInputs((u8)port, input.currentHeldInput, input.newInput, input.processedInput);
        return;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (input.processedInput & (INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT)) {
            challengeCaptainRelated();
            updateCharacterSelectProcessCode(0, 3);
            lbl_803CBBC4[0] = 3;
        }
        return;
    }
    if (input.newInput & INPUT_BUTTON_START) {
        return;
    }
    if (input.processedInput & DPAD_MASK) {
        updateCharacterSelectProcessCode(slot, 3);
    }
}

// .text:0x00015AFC size:0x384 mapped:0x80654B90
void captainSelectScreenInputs(int port, u16 currentHeldInput, u16 newInput, u16 processedInput) {
    if (Static_Stats_Tables.playerNumberByPort[port] == -1) {
        return;
    }

    if (aiPosSwapInputs.capSS_isRandomizingCursor[gameSetUpStep.portCaptainSlot[port]] != 0) {
        s8 capIdx;
        int charID;
        int val;
        int i;
        s8 tmpCapIdx[4];
        u8 idxVal = gameSetUpStep.portCaptainSlot[port];

        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && gameSetUpStep.portCaptainSlot[0] == 1) {
            tmpCapIdx[idxVal] = gameSetUpStep.portCaptainSlot[0];
        } else {
            tmpCapIdx[idxVal] = Static_Stats_Tables.playerNumberByPort[idxVal];
        }
        capIdx = tmpCapIdx[idxVal];

        if ((u32)charSelectStruct[0x7F + capIdx] >> 31) {
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                val = captainSelect_processCursorMovement_getCharID(capIdx, currentHeldInput, newInput, processedInput);
                for (i = 0; i < 12; i++) {
                    if (mapCaptainCursorPositionToCharID[i] == val) {
                        val = i;
                        break;
                    }
                }
                menuCursors[4 + (u8)gameSetUpStep.portCaptainSlot[port]] = val;
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
                menuCursors[4] = val;
                challengeCaptainRelated();
                lbl_803CBBC4[0] = 3;
            }
            aiPosSwapInputs.capSS_isRandomizingCursor[gameSetUpStep.portCaptainSlot[port]] = FALSE;
        }
        return;
    }

    if (aiPosSwapInputs.capSS_isRandomizingCursor[gameSetUpStep.portCaptainSlot[port]] != 0) {
        return;
    }

    if (newInput & INPUT_BUTTON_A) {
        if (!stopShowingCaptainProfile(gameSetUpStep.portCaptainSlot[port])) {
            captainSelect_APress(gameSetUpStep.portCaptainSlot[port]);
        }
        return;
    }
    if (newInput & INPUT_BUTTON_B) {
        if (!stopShowingCaptainProfile(gameSetUpStep.portCaptainSlot[port])) {
            captainSelect_BPress(gameSetUpStep.portCaptainSlot[port]);
        }
        return;
    }
    if (newInput & INPUT_TRIGGER_R) {
        if (!stopShowingCaptainProfile(gameSetUpStep.portCaptainSlot[port])) {
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                aiPosSwapInputs.capSS_isRandomizingCursor[gameSetUpStep.portCaptainSlot[port]] = TRUE;
            }
        }
        return;
    }
    if (newInput & INPUT_TRIGGER_Z) {
        if (!stopShowingCaptainProfile(gameSetUpStep.portCaptainSlot[port])) {
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
    if (input & INPUT_BUTTON_LEFT) {
        (*value)--;
        if (*value < 0) {
            *value = max;
        }
    } else if (input & INPUT_BUTTON_RIGHT) {
        (*value)++;
        if (*value > max) {
            *value = 0;
        }
    }
}

// .text:0x0001560C size:0x484 mapped:0x806546A0
void captainSelect_APress(int idx) {
    u32 c;
    int charID;
    int val;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (lbl_2_bss_100B8[0x1C] != 0 || lbl_2_bss_100B8[0x42] != 0) {
            return;
        }

        charID = (&challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6])[menuCursors[4]];
        lbl_2_bss_100B8[0x10] = 1;
        Static_Stats_Tables.captainSelectedID[0] = charID;
        lbl_2_bss_100B8[0x12] = 1;
        fn_8004D4F0(Static_Stats_Tables.playerNumberByPort[0], charID, TRUE);
        AnimateCharacter(0, 0x6A, 0, 1, 1, 0, 0, -1);
        QueueCharacterAnimation(0, 0x6B, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8[0x40] = 0;
        menuControlVariables->currentState = 4;
        return;
    }

    c = (u8)idx;

    if (lbl_2_bss_100B8[0x1C + c] != 0 || lbl_2_bss_100B8[0x42 + c] != 0) {
        return;
    }

    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && *((u8 *)hugeAnimStruct._2C50[c] + 0x25D) == 0 && c != 0) {
        return;
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

    Static_Stats_Tables.captainSelectedID[c] = mapCaptainCursorPositionToCharID[menuCursors[4 + (u8)idx]];

    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && (u8)idx != 0) {
        if (Static_Stats_Tables.playerNumberByPort[0] == 0) {
            add_or_RemoveCharToATeam(1, Static_Stats_Tables.captainSelectedID[c], TRUE);
        } else {
            add_or_RemoveCharToATeam(0, Static_Stats_Tables.captainSelectedID[c], TRUE);
        }
    } else {
        add_or_RemoveCharToATeam(Static_Stats_Tables.playerNumberByPort[c], Static_Stats_Tables.captainSelectedID[c], TRUE);
    }

    lbl_2_bss_100B8[0x10 + c] = 1;
    lbl_2_bss_100B8[0x12 + c] = 1;
    Static_Stats_Tables.charOnCharacterGridSelected[mapCaptainCursorPositionToCharID[menuCursors[4 + (u8)idx]]] = TRUE;

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

        gameSetUpStep.portCaptainSlot[c] = 1;
        captainIdx = (Static_Stats_Tables.playerNumberByPort[0] == 0);
        charSelectStruct[0x74 + captainIdx] = 1;

        if (menuCursors[4] == 0) {
            menuCursors[5] = 1;
        } else {
            menuCursors[5] = 0;
        }

        switch (captainIdx) {
        case 0:
            val = menuCursors[5];
            storeCursorLocOrCharIDs(0, val, -1, -1, -1);
            break;
        case 1:
            val = menuCursors[5];
            storeCursorLocOrCharIDs(0, -1, val, -1, -1);
            break;
        case 2:
            val = menuCursors[5];
            storeCursorLocOrCharIDs(0, -1, -1, val, -1);
            break;
        case 3:
            val = menuCursors[5];
            storeCursorLocOrCharIDs(0, -1, -1, -1, val);
            break;
        }
    }

    val = menuCursors[5];
    cursorPositions.cursor[1] = val;
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
    int c = (u8)idx;

    if (lbl_2_bss_100B8[0x10 + c] != 0) {
        lbl_2_bss_100B8[0x10 + c] = 0;
        lbl_2_bss_100B8[0x12 + c] = 0;
        Static_Stats_Tables.charOnCharacterGridSelected[Static_Stats_Tables.captainSelectedID[c]] = FALSE;
        add_or_RemoveCharToATeam((u8)idx, Static_Stats_Tables.captainSelectedID[c], FALSE);
        goto exit;
    }

    if ((u8)idx != 0) {
        if (aiPosSwapInputs.capSS_isRandomizingCursor[c] != 0) {
            aiPosSwapInputs.capSS_isRandomizingCursor[c] = 0;
        }

        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
            int other;

            fn_2_16A74((u8)idx, 0);
            charSelectStruct[0x7F + Static_Stats_Tables.playerNumberByPort[gameSetUpStep.portCaptainSlot[0]]] = -1;
            Static_Stats_Tables.charOnCharacterGridSelected[Static_Stats_Tables.captainSelectedID[0]] = FALSE;
            lbl_2_bss_100B8[0x10] = 0;
            lbl_2_bss_100B8[0x12] = 0;
            gameSetUpStep.portCaptainSlot[0] = 0;
            add_or_RemoveCharToATeam(0, Static_Stats_Tables.captainSelectedID[0], FALSE);
            Static_Stats_Tables.captainSelectedID[0] = CHAR_ID_NONE;
            Static_Stats_Tables.captainSelectedID[1] = CHAR_ID_NONE;
            updateCharacterSelectProcessCode(0, 4);

            other = (idx & 0xFF) ^ 1;
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

            g_MatchInfo.player2Ind2 = 0;
            charSelectStruct[0x7F + Static_Stats_Tables.playerNumberByPort[gameSetUpStep.portCaptainSlot[c]]] = -1;

            if (menuControlVariables->previousScreen == 0xa && v10 == 0) {
                Static_Stats_Tables.charOnCharacterGridSelected[Static_Stats_Tables.captainSelectedID[0]] = FALSE;
                add_or_RemoveCharToATeam(0, Static_Stats_Tables.captainSelectedID[0], FALSE);
                Static_Stats_Tables.captainSelectedID[0] = CHAR_ID_NONE;
                Static_Stats_Tables.captainSelectedID[1] = CHAR_ID_NONE;
            }

            lbl_2_bss_100B8[0x10 + c] = 0;
            lbl_2_bss_100B8[0x12 + c] = 0;
            gameSetUpStep.portCaptainSlot[c] = 0;

            if (lbl_2_bss_100B8[0x10] != 0) {
                updateCharacterSelectProcessCode(idx & 0xFF, 5);
            } else {
                updateCharacterSelectProcessCode(idx & 0xFF, 4);
            }
        }
        goto exit;
    }

    charSelectStruct[0x7F + Static_Stats_Tables.playerNumberByPort[0]] = -1;
    if (Static_Stats_Tables.playerNumberByPort[1] != -1) {
        charSelectStruct[0x7F + Static_Stats_Tables.playerNumberByPort[1]] = -1;
    }

    aiPosSwapInputs.capSS_isRandomizingCursor[1] = 0;
    aiPosSwapInputs.capSS_isRandomizingCursor[0] = 0;
    lbl_2_bss_100B4 = 1;

    {
        int i;
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            fn_2_16A74(i, 0);
        }
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        lbl_803CBBC4[0] = 2;
    } else {
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
            updateCharacterSelectProcessCode(0, 2);
            updateCharacterSelectProcessCode(1, 2);
        } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_2_PLAYER_GAME) {
            updateCharacterSelectProcessCode(0, 2);
            updateCharacterSelectProcessCode(1, 2);
        }
        lbl_803CBCD8[2] = 0x14;
    }

    lbl_2_bss_F468[0x46] = 0;
    lbl_2_bss_F468[0x45] = 0;
    menuControlVariables->currentState = 8;

exit:
    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_2_PLAYER_GAME) {
        AnimateCharacter((u8)idx, 0x69, 1, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8[0x40 + c] = 1;
    }
    cursorSndFx(INPUT_BUTTON_B);
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

    chosen[0] = captainIDOrderedOnCapSS[menuCursors[4]];
    chosen[1] = captainIDOrderedOnCapSS[menuCursors[5]];
    do {
        chosen[slot] = stadiumRandomizer(0, 0x13);
        for (i = 0; i < 12; i++) {
            if (captainIDOrderedOnCapSS[i] == chosen[slot]) {
                break;
            }
        }
    } while (i == 12 || chosen[0] == chosen[1]);
    {
        int *entry = &menuCursors[slot];
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
            val = menuCursors[4 + port];
            storeCursorLocOrCharIDs(0, val, -1, -1, -1);
            break;
        case 1:
            val = menuCursors[4 + port];
            storeCursorLocOrCharIDs(0, -1, val, -1, -1);
            break;
        case 2:
            val = menuCursors[4 + port];
            storeCursorLocOrCharIDs(0, -1, -1, val, -1);
            break;
        case 3:
            val = menuCursors[4 + port];
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
        menuCursors[4 + port] = val;
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
        menuCursors[4] = val;
    }
}

// .text:0x00014BB8 size:0xE8 mapped:0x80653C4C
void fn_2_14BB8(int port, int state) {
    switch (state) {
    case 0: {
        u8 a = port;
        AnimateCharacter(a, 0x6A, 0, 1, 1, 0, 0, -1);
        QueueCharacterAnimation(a, 0x6B, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8[0x40 + (u8)port] = 0;
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

    if (lbl_2_bss_100B8[0x19] == 0 || lbl_2_bss_100B8[0x1a] != 0 || g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
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

    if (g_MatchInfo.player2Ind2 != 0) {
        return;
    }

    if (lbl_2_bss_100B8[0x11] != 0) {
        lbl_2_bss_100B8[0x11] = 0;
        lbl_2_bss_100B8[0x13] = 0;
        add_or_RemoveCharToATeam(1, Static_Stats_Tables.captainSelectedID[1], FALSE);
        Static_Stats_Tables.charOnCharacterGridSelected[Static_Stats_Tables.captainSelectedID[1]] = FALSE;
        Static_Stats_Tables.captainSelectedID[1] = CHAR_ID_NONE;
    }

    Static_Stats_Tables.portsActiveInMatch[newPlayerPort] = 0;
    Static_Stats_Tables.playerNumberByPort[newPlayerPort] = Static_Stats_Tables.playerNumberByPort[1];
    g_MatchInfo.player2Ind2 = 1;
    Static_Stats_Tables.playerNumberByPort[1] = newPlayerPort;
    gameSetUpStep.portCaptainSlot[0] = 0;
    gameSetUpStep.portCaptainSlot[1] = 1;

    if (Static_Stats_Tables.charOnCharacterGridSelected[0] != 0 || menuCursors[4] == 0) {
        cursorPositions.cursor[1] = 1;
    } else {
        cursorPositions.cursor[1] = 0;
    }

    charSelectStruct[0x74 + Static_Stats_Tables.playerNumberByPort[1]] = 0;
    updateCharacterSelectProcessCode(1, 1);

    g_d_GameSettings.p2_CPU_match_code = P2_CPU_CODE_2_PLAYER_GAME;
    aiPosSwapInputs.capSS_isRandomizingCursor[1] = 0;
    charSelectStruct[0x80] = -1;
    if (menuCursors[4] == 0) {
        menuCursors[5] = 1;
    } else {
        menuCursors[5] = 0;
    }

    captainIdx = Static_Stats_Tables.playerNumberByPort[1];
    charSelectStruct[0x74 + captainIdx] = 0;
    switch (captainIdx) {
    case 0:
        val = menuCursors[5];
        storeCursorLocOrCharIDs(0, val, -1, -1, -1);
        break;
    case 1:
        val = menuCursors[5];
        storeCursorLocOrCharIDs(0, -1, val, -1, -1);
        break;
    case 2:
        val = menuCursors[5];
        storeCursorLocOrCharIDs(0, -1, -1, val, -1);
        break;
    case 3:
        val = menuCursors[5];
        storeCursorLocOrCharIDs(0, -1, -1, -1, val);
        break;
    }

    prevID = -1;
    while (!loadNewCaptainModelOnCapSelectScreen(menuCursors[5], prevID, 1, 1)) {
        prevID = menuCursors[5];
    }

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
    f32 t = 320.0f + v;
    t -= 0.1;
    return t - 320.0f;
}

static f32 stepValueUp(f32 v) {
    f32 t = 320.0f + v;
    t += 0.1;
    return t - 320.0f;
}

// .text:0x00014574 size:0x21C mapped:0x80653608
void fn_2_14574(controllerInputStruct *input) {
    if (input->processedInput & INPUT_BUTTON_UP) {
        if (input->currentHeldInput & INPUT_BUTTON_B) {
            lbl_2_bss_1010C.unk48 += 0.1f;
        } else if (input->currentHeldInput & INPUT_BUTTON_A) {
            lbl_2_bss_1010C.unk4C += 1.0f;
        } else if (input->currentHeldInput & INPUT_BUTTON_X) {
            lbl_2_bss_1010C.unk50 += 0.1f;
        }
        return;
    }
    if (input->processedInput & INPUT_BUTTON_DOWN) {
        if (input->currentHeldInput & INPUT_BUTTON_B) {
            lbl_2_bss_1010C.unk48 -= 0.1f;
        } else if (input->currentHeldInput & INPUT_BUTTON_A) {
            lbl_2_bss_1010C.unk4C -= 0.1f;
        } else if (input->currentHeldInput & INPUT_BUTTON_X) {
            lbl_2_bss_1010C.unk50 -= 0.1f;
        }
        return;
    }
    if (input->processedInput & INPUT_BUTTON_LEFT) {
        if (input->currentHeldInput & INPUT_BUTTON_B) {
            lbl_2_data_20F8[0] = stepValueDown(lbl_2_data_20F8[0]);
        } else if (input->currentHeldInput & INPUT_BUTTON_A) {
            lbl_2_data_20F8[1] = stepValueDown(lbl_2_data_20F8[1]);
        }
        return;
    }
    if (input->processedInput & INPUT_BUTTON_RIGHT) {
        if (input->currentHeldInput & INPUT_BUTTON_B) {
            lbl_2_data_20F8[0] = stepValueUp(lbl_2_data_20F8[0]);
        } else if (input->currentHeldInput & INPUT_BUTTON_A) {
            lbl_2_data_20F8[1] = stepValueUp(lbl_2_data_20F8[1]);
        }
    }
}
