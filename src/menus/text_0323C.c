#include "menus/text_0323C.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "menus/yd_step.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "musyx/musyx.h"

void updateCharacterSelectProcessCode(int arg0, int arg1);
void sndFXRelated(int id);
void challenge_setTransitionScreenCharacterPortrait(int arg0, int arg1);
void fn_2_16A74(int idx, int flag);
s32 randRange_FUN_80042bf0(s32 min, s32 max);
void addOrRemoveCharacterToTeam(s32 add, s32 charID, s32 flag);
s32 addRemoveCharVariantRelated(s32 port, s32 charID, s32 flag);
void teamLogoDetermination(s32 team);
s32 fn_80067AC8(s32 charID, s32 flag);
void cssLoadingRelated_1(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void fn_8004D0F0(void);
s32 exitMenu(s32 arg0);
void set803c5f77(void);
void loadDemoMatch(s32 arg0, s32 arg1, s32 arg2);
void changeScene(s32 arg0, s32 arg1);
void cursorSndFx(s32 id);
s32 stadiumRandomizer(s32 min, s32 max);
void fn_2_1D54(s32 *cursor, u8 port, s32 count);
void fn_2_87A8(void);
void fn_800216F8(s32 arg0, void (*func)(void));
void fn_8006285C(void);
void initializeUnknown(void);
s32 fn_800697B0(void);
s32 diskReadRelated(void *arg0, s32 arg1);
void unsure_FillRosterPositions(int team);
void setPortOfEachPlayer(void);
void relatedToTeamSelection4(void);
void relatedToReturningToPracticeMenu(void);
extern u8 superstarUnlocked[0x130];
extern u8 lbl_2_data_720[0x744];

extern u8 lbl_2_bss_3A0[0x8];
extern u8 lbl_2_bss_3A8[0x38];
extern u8 lbl_2_bss_E8CC[0xB44];
extern u8 lbl_2_bss_DCE8[0xBE4];
void fn_80066EAC(s32 team);
extern u8 captainIDOrderedOnCapSS[];
extern u8 characterIconsOnCSS[];
extern u8 gameSetUpStep[];
extern u8 lbl_803CBD24[];
extern u8 lbl_803CB8D0[];

extern s16 variantPairs[][5];
extern u8 lbl_2_bss_F410[0x58];
extern u8 lbl_2_bss_F468[0xC4C];
extern u8 lbl_2_bss_100B4;
extern u8 lbl_2_bss_100B8[0x54];
extern u8 lbl_2_data_3CE0[0x8];
extern u8 starMissionCompletionTracker[0x4508];
extern u8 lbl_8037169C[0x1C];
extern u8 inMemRoster[0xB40];
extern u8 lineUpInfoStruct[0x48];
extern u8 lbl_8010902C[0x18];
extern u8 characterStaticIndexes[0x144];
extern u8 unlockableCharacter_noDupeNoGapCharID[0x8];
extern menuControlStruct *menuControlVariables;
extern u8 lbl_2_bss_3E0[4];
extern u8 menuNumber[0x28];
extern u8 lbl_800EFBA4[0x10];
extern s8 mainCharArray[];
extern u8 lbl_2_bss_3E4[0x24];
void fn_2_9ACC(u16 team);
void css_initValues(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
void cssCheckSomethingAboutCharacters(void);
extern u8 charSelectStruct[0x94];

s32 noActiveProcessInd(void);
s32 fn_80050F78(s32 arg0);
void fn_80021AC0(s32 arg0, s32 arg1);
void settingValuesTo0(void);
void fn_80062A74(void);
void maybeLoadsGameSoundFiles(void);
void unregisterObjectByID(s32 id);
void fn_800AD038(s32 arg0);

// .text:0x0000323C size:0x180 mapped:0x806422D0
void cssTransitionToNewScreen_maybe(void) {
    switch (lbl_2_bss_3A0[0]) {
    case 0:
        insertGraphicDrawingFunction(fn_8004D0F0, 0x3000);
        lbl_2_bss_3A0[0]++;
        break;
    case 1:
        switch (exitMenu(*(u16 *)&((u8 *)&Static_Stats_Tables)[lbl_803CBD24[4] * 6 + 0x472E])) {
        case 0:
            break;
        case 1:
        case 2:
            set803c5f77();
            break;
        case 3:
            loadDemoMatch(0xA, 1, 1);
            lbl_803CBD24[4] = 0;
            updateCharacterSelectProcessCode(0, 0x13);
            updateCharacterSelectProcessCode(1, 0x13);
            changeScene(0xF, 6);
            lbl_2_bss_3A0[0] = 0;
            lbl_2_bss_F468[0x2E] = 0;
            lbl_2_bss_100B4 = 1;
            menuControlVariables->currentState = 8;
            break;
        case 4:
            lbl_2_bss_3A0[0] = 0;
            lbl_803CBD24[4] = 0;
            ((u8 *)&aiPosSwapInputs)[0xCF5F] = 0;
            menuControlVariables->currentState = 2;
            break;
        }
        break;
    }
}

// .text:0x000033BC size:0xD0 mapped:0x80642450
s32 fn_2_33BC(void) {
    u8 *p = starMissionCompletionTracker;
    s8 val = (s8)p[0x40BB];
    s32 result = 1;

    if (val == (s8)p[0x40C1]) {
        result = 0;
    }
    p += 0xC;
    if (val == (s8)p[0x40BB]) {
        result = 0;
    }
    p += 6;
    if (val == (s8)p[0x40C1]) {
        result = 0;
    }
    p += 6;
    if (val == (s8)p[0x40C1]) {
        result = 0;
    }
    p += 6;
    if (val == (s8)p[0x40C1]) {
        result = 0;
    }
    p += 6;
    if (val == (s8)p[0x40C1]) {
        result = 0;
    }
    p += 6;
    if (val == (s8)p[0x40C1]) {
        result = 0;
    }
    return result;
}

// .text:0x0000348C size:0x144 mapped:0x80642520
void fn_2_348C(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        s32 flag = !((u8 *)&g_d_GameSettings)[0x1A + i];
        u8 target = unlockableCharacter_noDupeNoGapCharID[i];
        s32 rec;

        for (rec = 0; rec < 54; rec++) {
            if (characterStaticIndexes[rec * 6 + 2] == target) {
                ((u8 *)&Static_Stats_Tables)[0x4757 + rec] = flag;
            }
        }

        unlockableCharacter_noDupeNoGapCharID[i] = target;
    }
}

// .text:0x000035D0 size:0x54 mapped:0x80642664
bool stopShowingCaptainProfile(u8 port) {
    if (lbl_2_bss_F468[port + 0x45] != 0) {
        lbl_2_bss_F468[port + 0x45] = 0;
        sndFXRelated(0x200);
        return true;
    }
    return false;
}

// .text:0x00003624 size:0x134C mapped:0x806426B8
void fn_2_3624(void) {
    return;
}

// .text:0x00004970 size:0x814 mapped:0x80643A04
void fn_2_4970(u8 team, s32 charID) {
    u8 *cur = (u8 *)&cursorPositions + team * 9;
    u8 *rosterBase = (u8 *)&cursorPositions + 2 + team * 9;
    u8 *rosterBase0 = (u8 *)&cursorPositions + 2;
    s32 *countPtr = (s32 *)&lbl_2_bss_F468[team * 4];
    s32 cnt = *countPtr;
    s32 slotIndex;
    s8 matchedCharID;
    s32 conflict = 0;
    s8 foundRow = 0;

    if ((s8)cur[0x14 + 0] == cnt) slotIndex = 0;
    if ((s8)cur[0x14 + 1] == cnt) slotIndex = 1;
    if ((s8)cur[0x14 + 2] == cnt) slotIndex = 2;
    if ((s8)cur[0x14 + 3] == cnt) slotIndex = 3;
    if ((s8)cur[0x14 + 4] == cnt) slotIndex = 4;
    if ((s8)cur[0x14 + 5] == cnt) slotIndex = 5;
    if ((s8)cur[0x14 + 6] == cnt) slotIndex = 6;
    if ((s8)cur[0x14 + 7] == cnt) slotIndex = 7;
    if ((s8)cur[0x14 + 8] == cnt) slotIndex = 8;

    matchedCharID = (s8)rosterBase[slotIndex];

    if (matchedCharID == charID) {
        (*countPtr)--;
        if (*countPtr < 0) {
            *countPtr = 8;
        }
        goto L_END;
    }

    if (lbl_2_bss_F468[team + 0x37] == 0 && lbl_2_bss_F468[team + 0x3D] == 0) {
        *(s32 *)&lbl_2_bss_F468[team * 4 + 8] = cnt;
        (*countPtr)--;
        if (*countPtr < 0) {
            *countPtr = 8;
        }

        if (matchedCharID == -1 || matchedCharID == 0x36) {
            goto L_TAIL;
        }

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            s8 addChar = (s8)rosterBase0[slotIndex];
            addOrRemoveCharacterToTeam(0, addChar, 1);
            Static_Stats_Tables.charOnCharacterGridSelected[addChar] = 1;
            addRemoveCharVariantRelated(team, (u8)addChar, 1);
        } else {
            u8 p2cpu = g_d_GameSettings.p2_CPU_match_code;
            s8 addChar = (s8)rosterBase[slotIndex];
            Static_Stats_Tables.charOnCharacterGridSelected[addChar] = 1;
            if (p2cpu == 0 && team != 0) {
                if ((s8)Static_Stats_Tables.playerNumberByPort[0] != 0) {
                    addOrRemoveCharacterToTeam(0, addChar, 1);
                } else {
                    addOrRemoveCharacterToTeam(1, addChar, 1);
                }
            } else {
                addOrRemoveCharacterToTeam((s8)Static_Stats_Tables.playerNumberByPort[team], addChar, 1);
            }
            addRemoveCharVariantRelated(team, (u8)addChar, 1);
        }

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            s32 ret = addRemoveCharVariantRelated(team, matchedCharID, 2);
            if ((u8)ret != 0) {
                s32 row, i, k;
                for (row = 0; row < 9; row++) {
                    s8 v = (s8)rosterBase[slotIndex];
                    if (v == variantPairs[row][0]) { foundRow = (s8)row; goto L_FOUND_ROW_A; }
                    if (v == variantPairs[row][1]) { foundRow = (s8)row; goto L_FOUND_ROW_A; }
                    if (v == variantPairs[row][2]) { foundRow = (s8)row; goto L_FOUND_ROW_A; }
                    if (v == variantPairs[row][3]) { foundRow = (s8)row; goto L_FOUND_ROW_A; }
                    if (v == variantPairs[row][4]) { foundRow = (s8)row; goto L_FOUND_ROW_A; }
                }
            L_FOUND_ROW_A:
                for (i = 0; i < 9; i++) {
                    for (k = 0; k < 5; k++) {
                        s8 candidate = (s8)rosterBase[i];
                        s16 pairVal = variantPairs[foundRow][k];
                        if (candidate == pairVal && pairVal != -1 && candidate != (s8)rosterBase[slotIndex]) {
                            conflict = 1;
                        }
                    }
                }
                if (conflict == 0) {
                    s32 pairedCharId = fn_80067AC8((s8)rosterBase[slotIndex], 0);
                    addOrRemoveCharacterToTeam(team, (s16)pairedCharId, 0);
                    pairedCharId = fn_80067AC8((s8)rosterBase[slotIndex], 0);
                    Static_Stats_Tables.charOnCharacterGridSelected[(s16)pairedCharId] = 0;
                }
            } else {
                s8 mc = (s8)rosterBase[slotIndex];
                addOrRemoveCharacterToTeam(team, mc, 0);
                Static_Stats_Tables.charOnCharacterGridSelected[mc] = 0;
            }
        } else {
            s8 mc = (s8)rosterBase[slotIndex];
            addOrRemoveCharacterToTeam(team, mc, 0);
            mc = (s8)rosterBase[slotIndex];
            addRemoveCharVariantRelated(team, mc, 0);
            mc = (s8)rosterBase[slotIndex];
            Static_Stats_Tables.charOnCharacterGridSelected[mc] = 0;
        }

        cur[0x26 + slotIndex] = 0;
        rosterBase[slotIndex] = (u8)-1;
        cur[0x4a + slotIndex] = 0;
        goto L_TAIL;

    } else {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            s8 addChar = (s8)rosterBase0[slotIndex];
            addOrRemoveCharacterToTeam(0, addChar, 1);
            Static_Stats_Tables.charOnCharacterGridSelected[addChar] = 1;
            addRemoveCharVariantRelated(team, (u8)addChar, 1);
        } else {
            u8 p2cpu = g_d_GameSettings.p2_CPU_match_code;
            s8 addChar = (s8)rosterBase[slotIndex];
            Static_Stats_Tables.charOnCharacterGridSelected[addChar] = 1;
            if (p2cpu == 0 && team != 0) {
                if ((s8)Static_Stats_Tables.playerNumberByPort[0] != 0) {
                    addOrRemoveCharacterToTeam(0, addChar, 1);
                } else {
                    addOrRemoveCharacterToTeam(1, addChar, 1);
                }
            } else {
                addOrRemoveCharacterToTeam((s8)Static_Stats_Tables.playerNumberByPort[team], addChar, 1);
            }
            addRemoveCharVariantRelated(team, (u8)addChar, 1);
        }

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            s32 ret = addRemoveCharVariantRelated(team, matchedCharID, 2);
            if ((u8)ret != 0) {
                s32 row, i, k;
                for (row = 0; row < 9; row++) {
                    s8 v = (s8)rosterBase[slotIndex];
                    if (v == variantPairs[row][0]) { foundRow = (s8)row; goto L_FOUND_ROW_B; }
                    if (v == variantPairs[row][1]) { foundRow = (s8)row; goto L_FOUND_ROW_B; }
                    if (v == variantPairs[row][2]) { foundRow = (s8)row; goto L_FOUND_ROW_B; }
                    if (v == variantPairs[row][3]) { foundRow = (s8)row; goto L_FOUND_ROW_B; }
                    if (v == variantPairs[row][4]) { foundRow = (s8)row; goto L_FOUND_ROW_B; }
                }
            L_FOUND_ROW_B:
                for (i = 0; i < 9; i++) {
                    for (k = 0; k < 5; k++) {
                        s8 candidate = (s8)rosterBase[i];
                        s16 pairVal = variantPairs[foundRow][k];
                        if (candidate == pairVal && pairVal != -1 && candidate != (s8)rosterBase[slotIndex]) {
                            conflict = 1;
                        }
                    }
                }
                if (conflict == 0) {
                    s32 pairedCharId = fn_80067AC8((s8)rosterBase[slotIndex], 0);
                    addOrRemoveCharacterToTeam(team, (s16)pairedCharId, 0);
                    pairedCharId = fn_80067AC8((s8)rosterBase[slotIndex], 0);
                    Static_Stats_Tables.charOnCharacterGridSelected[(s16)pairedCharId] = 0;
                }
            } else {
                s8 mc = (s8)rosterBase[slotIndex];
                addOrRemoveCharacterToTeam(team, mc, 0);
                Static_Stats_Tables.charOnCharacterGridSelected[mc] = 0;
            }
        } else {
            s8 mc = (s8)rosterBase[slotIndex];
            addOrRemoveCharacterToTeam(team, mc, 0);
            mc = (s8)rosterBase[slotIndex];
            addRemoveCharVariantRelated(team, mc, 0);
            mc = (s8)rosterBase[slotIndex];
            Static_Stats_Tables.charOnCharacterGridSelected[mc] = 0;
        }

        cur[0x26 + slotIndex] = 0;
        rosterBase[slotIndex] = (u8)-1;
        lbl_2_bss_F468[team + 0x3D] = 0;
        cur[0x4a + slotIndex] = 0;
    }

L_TAIL:
    lbl_2_bss_F468[team + 0x37] = 0;

L_END:
    updateCharacterSelectProcessCode(team, 0x10);
}

// .text:0x00005184 size:0x148 mapped:0x80644218
void fn_2_5184(void) {
    return;
}

// .text:0x000052CC size:0x178 mapped:0x80644360
void fn_2_52CC(void) {
    s32 i;

    lbl_2_bss_100B8[0x2E] = 1;
    gameSetUpStep[0x59] = 1;
    ((s32 *)lbl_2_bss_F468)[1] = 0xA;
    ((u8 *)&g_MatchInfo)[0xE] = 1;

    if (((u8 *)&Static_Stats_Tables)[0x4757 + *(s32 *)&lbl_2_bss_F410[0x24]] != 0) {
        for (i = 0; i < 32; i++) {
            if (((u8 *)&Static_Stats_Tables)[0x4757 + characterIconsOnCSS[i]] == 0) {
                *(s32 *)&lbl_2_bss_F410[0x24] = characterIconsOnCSS[i];
                break;
            }
        }
    }

    switch ((s8)Static_Stats_Tables.playerNumberByPort[1]) {
    case 0:
        cssLoadingRelated_1(1, *(s32 *)&lbl_2_bss_F410[0x24], -1, -1, -1, 0);
        break;
    case 1:
        cssLoadingRelated_1(1, -1, *(s32 *)&lbl_2_bss_F410[0x24], -1, -1, 0);
        break;
    case 2:
        cssLoadingRelated_1(1, -1, -1, *(s32 *)&lbl_2_bss_F410[0x24], -1, 0);
        break;
    case 3:
        cssLoadingRelated_1(1, -1, -1, -1, *(s32 *)&lbl_2_bss_F410[0x24], 0);
        break;
    }
}

// .text:0x00005444 size:0x3A4 mapped:0x806444D8
void teamReady1(u8 port) {
    s32 i;
    s32 mode;
    s32 val;

    lbl_2_bss_F468[port + 0x3d] = 0;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        s32 idx;
        u8 *cursor = (u8 *)&cursorPositions;
        u8 *roster = inMemRoster;
        u8 *tracker = starMissionCompletionTracker;
        u8 *lineUp = lineUpInfoStruct;

        for (idx = 0; idx < 9; idx++) {
            *(s16 *)&tracker[0x40B8] = (s8)cursor[2];
            tracker[0x40BA] = idx;
            tracker[0x40BB] = cursor[0x14];
            *(s16 *)&roster[0x24] = (s8)cursor[2];
            lineUp[2] = cursor[0x14];
            cursor++;
            roster += 0xA0;
            tracker += 6;
            lineUp += 4;
        }
        updateCharacterSelectProcessCode(0, 0x13);
        updateCharacterSelectProcessCode(1, 0x13);
        lbl_2_bss_F468[0x2e] = 0;
        lbl_2_bss_100B4 = 1;
        menuControlVariables->currentState = 8;
        return;
    }

    mode = ((u8 *)&g_d_GameSettings)[0x10];
    if (mode == 0 && lbl_2_bss_100B8[0x2e] != 0) {
        updateCharacterSelectProcessCode(1, 0x11);
        ((u8 *)&Static_Stats_Tables)[0x472a] = 0xff;
        lbl_2_bss_F468[0x36] = 0x1e;
        menuControlVariables->currentState = 3;
        return;
    }
    if (mode != 0) goto other;

    lbl_2_bss_100B8[0x2e] = 1;
    gameSetUpStep[0x59] = 1;
    *(u32 *)&lbl_2_bss_F468[4] = 0xa;
    ((u8 *)&g_MatchInfo)[0xE] = 1;

    val = *(s32 *)&lbl_2_bss_F410[0x24];
    if (((u8 *)&Static_Stats_Tables)[0x4757 + val] != 0) {
        for (i = 0; i < 32; i++) {
            if (((u8 *)&Static_Stats_Tables)[0x4757 + characterIconsOnCSS[i]] == 0) {
                *(s32 *)&lbl_2_bss_F410[0x24] = characterIconsOnCSS[i];
                break;
            }
        }
    }
    switch ((s8)((u8 *)&Static_Stats_Tables)[0x46f9]) {
    case 0:
        cssLoadingRelated_1(1, *(s32 *)&lbl_2_bss_F410[0x24], -1, -1, -1, 0);
        break;
    case 1:
        cssLoadingRelated_1(1, -1, *(s32 *)&lbl_2_bss_F410[0x24], -1, -1, 0);
        break;
    case 2:
        cssLoadingRelated_1(1, -1, -1, *(s32 *)&lbl_2_bss_F410[0x24], -1, 0);
        break;
    case 3:
        cssLoadingRelated_1(1, -1, -1, -1, *(s32 *)&lbl_2_bss_F410[0x24], 0);
        break;
    }
    updateCharacterSelectProcessCode(0, 0x11);
    return;

other:
    if (mode != 1) return;
    lbl_2_bss_100B8[0x2e + port] = 1;
    updateCharacterSelectProcessCode(port, 0x11);
    if (lbl_2_bss_100B8[0x2e] == 0) return;
    if (lbl_2_bss_100B8[0x2f] == 0) return;
    lbl_2_bss_F468[0x4f] = 1;
    lbl_2_bss_F468[0x36] = 0x1e;
    menuControlVariables->currentState = 7;
}

// .text:0x000057E8 size:0x8 mapped:0x8064487C
s32 fn_2_57E8(s32 arg0, s32 arg1) {
    return (s8)arg1;
}

// .text:0x000057F0 size:0x790 mapped:0x80644884
void fn_2_57F0(u8 playerIndex, s32 unused, u16 flagsA, u16 flagsB) {
    s32 oldState = *(s32 *)&lbl_2_bss_F468[playerIndex * 4];
    s32 state;

    *(s32 *)&lbl_2_bss_F468[playerIndex * 4 + 8] = oldState;

    if ((flagsB & 8) != 0 || (flagsA & 8) != 0) {
        state = *(s32 *)&lbl_2_bss_F468[playerIndex * 4];

        if (state == 9) {
            *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 2;
            updateCharacterSelectProcessCode(playerIndex, 0xe);
            sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
            return;
        }
        if (state == 10) {
            if (lbl_2_bss_F468[playerIndex + 0x37] != 0) {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 9;
                updateCharacterSelectProcessCode(playerIndex, 0x18);
            } else {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 2;
                updateCharacterSelectProcessCode(playerIndex, 0xe);
            }
            sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
            return;
        }

        switch (state) {
        case 0: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 5; break;
        case 1: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 0; break;
        case 2: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 8; break;
        case 3: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 7; break;
        case 4: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 6; break;
        case 5: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 7; break;
        case 6: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 4; break;
        case 7:
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 0xa;
            } else if (lbl_2_bss_F468[playerIndex + 0x37] != 0) {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 9;
            } else {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 2;
            }
            break;
        case 8:
            *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 1;
            break;
        }

        if (oldState != *(s32 *)&lbl_2_bss_F468[playerIndex * 4]) {
            updateCharacterSelectProcessCode(playerIndex, 0xe);
        }
        sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
        return;
    }

    if ((flagsB & 4) != 0 || (flagsA & 4) != 0) {
        state = *(s32 *)&lbl_2_bss_F468[playerIndex * 4];

        if (state == 9) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 8;
                updateCharacterSelectProcessCode(playerIndex, 0xe);
            } else {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 0xa;
                updateCharacterSelectProcessCode(playerIndex, 0x18);
            }
            sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
            return;
        }
        if (state == 10) {
            *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 8;
            updateCharacterSelectProcessCode(playerIndex, 0xe);
            sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
            return;
        }

        switch (state) {
        case 0: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 1; break;
        case 1: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 7; break;
        case 2:
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                if (lbl_2_bss_F468[playerIndex + 0x37] != 0) {
                    *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 9;
                } else {
                    *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 8;
                }
            } else {
                if (lbl_2_bss_F468[playerIndex + 0x37] != 0) {
                    *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 9;
                } else {
                    *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 0xa;
                }
            }
            break;
        case 3: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 0; break;
        case 4: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 6; break;
        case 5: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 0; break;
        case 6: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 4; break;
        case 7: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 5; break;
        case 8: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 2; break;
        }

        if (oldState != *(s32 *)&lbl_2_bss_F468[playerIndex * 4]) {
            updateCharacterSelectProcessCode(playerIndex, 0xe);
        }
        sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
        return;
    }

    if ((flagsB & 1) != 0 || (flagsA & 1) != 0) {
        state = *(s32 *)&lbl_2_bss_F468[playerIndex * 4];

        if (state == 9) {
            *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 0;
            updateCharacterSelectProcessCode(playerIndex, 0xe);
            sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
            return;
        }
        if (state == 10) {
            *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 1;
            updateCharacterSelectProcessCode(playerIndex, 0xe);
            sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
            return;
        }

        switch (state) {
        case 0: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 4; break;
        case 1:
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 0xa;
            } else {
                if (lbl_2_bss_F468[playerIndex + 0x37] == 0) {
                    return;
                }
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 9;
            }
            break;
        case 2: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 3; break;
        case 3: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 5; break;
        case 4: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 2; break;
        case 5: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 4; break;
        case 6: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 8; break;
        case 7: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 6; break;
        case 8: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 7; break;
        case 9: break;
        case 10: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 1; break;
        }

        if (oldState != *(s32 *)&lbl_2_bss_F468[playerIndex * 4]) {
            updateCharacterSelectProcessCode(playerIndex, 0xe);
        }
        sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
        return;
    }

    if ((flagsB & 2) != 0 || (flagsA & 2) != 0) {
        state = *(s32 *)&lbl_2_bss_F468[playerIndex * 4];

        if (state == 9) {
            *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 0;
            updateCharacterSelectProcessCode(playerIndex, 0xe);
            sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
            return;
        }
        if (state == 10) {
            if (lbl_2_bss_F468[playerIndex + 0x37] != 0) {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 9;
                updateCharacterSelectProcessCode(playerIndex, 0x18);
            } else {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 1;
                updateCharacterSelectProcessCode(playerIndex, 0xe);
            }
            sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
            return;
        }

        switch (state) {
        case 0:
            if (lbl_2_bss_F468[playerIndex + 0x37] != 0) {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 9;
                updateCharacterSelectProcessCode(playerIndex, 0x18);
            } else {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 2;
                updateCharacterSelectProcessCode(playerIndex, 0xe);
            }
            break;
        case 1:
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 0xa;
            } else {
                if (lbl_2_bss_F468[playerIndex + 0x37] == 0) {
                    return;
                }
                *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 9;
            }
            break;
        case 2: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 4; break;
        case 3: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 2; break;
        case 4: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 5; break;
        case 5: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 3; break;
        case 6: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 7; break;
        case 7: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 8; break;
        case 8: *(s32 *)&lbl_2_bss_F468[playerIndex * 4] = 6; break;
        }

        if (oldState != *(s32 *)&lbl_2_bss_F468[playerIndex * 4]) {
            updateCharacterSelectProcessCode(playerIndex, 0xe);
        }
        sndFXStartEx(0x1b7, lbl_800EFBA4[0], 0x3f, 0);
        return;
    }
}

// .text:0x00005F80 size:0x118 mapped:0x80645014
void fn_2_5F80(void) {
    u8 *lineUp = lineUpInfoStruct;
    u8 *cursor = (u8 *)&cursorPositions;
    u8 *roster = inMemRoster;
    s32 team;

    for (team = 0; team < 2; team++) {
        u8 *lineUpPlayer = lineUp;
        u8 *cursorPlayer = cursor;
        s32 player;

        for (player = 0; player < 9; player++) {
            s8 target = (s8)lineUpPlayer[2];
            u8 *dest = cursorPlayer + 2;
            u8 *rec = lineUp;
            u8 *rosterRec = roster;
            s32 g;

            for (g = 0; g < 3; g++) {
                bool match;

                match = (target == (s8)rec[2]);
                if (match) {
                    *dest = (u8) * (s16 *)&rosterRec[0x24];
                }

                match = (target == (s8)rec[6]);
                rec += 4;
                rosterRec += 0xA0;
                if (match) {
                    *dest = (u8) * (s16 *)&rosterRec[0x24];
                }

                match = (target == (s8)rec[6]);
                rec += 4;
                rosterRec += 0xA0;
                if (match) {
                    *dest = (u8) * (s16 *)&rosterRec[0x24];
                }

                rec += 4;
                rosterRec += 0xA0;
            }

            cursorPlayer[0x14] = player;
            cursorPlayer++;
            lineUpPlayer += 4;
        }

        lineUp += 0x24;
        cursor += 9;
        roster += 0x5A0;
    }
}

// .text:0x00006098 size:0x3C mapped:0x8064512C
void fn_2_6098(u8 port) {
    *(s32 *)&lbl_2_bss_F468[port * 4] = 9;
    updateCharacterSelectProcessCode(port, 0x17);
}

// .text:0x000060D4 size:0x64 mapped:0x80645168
s32 fn_2_60D4(u8 port) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        return ((s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0])[port];
    }
    if (port != 0) {
        return ((s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0])[port];
    }
    return ((s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0])[port];
}

// .text:0x00006138 size:0x68 mapped:0x806451CC
void fn_2_6138(void) {
    updateCharacterSelectProcessCode(0, 0x13);
    updateCharacterSelectProcessCode(1, 0x13);
    lbl_2_bss_F468[0x4F] = 0;
    lbl_2_bss_F468[0x2E] = 0;
    lbl_2_bss_100B4 = 1;
    menuControlVariables->currentState = 8;
}

// .text:0x000061A0 size:0x2E4 mapped:0x80645234
void cssChangeScreens(void) {
    u8 *p;
    s32 i;

    if (noActiveProcessInd() == 0) goto tail;

    p = lbl_2_bss_F468;
    if (p[0x2E] == 0) {
        if (fn_80050F78(0) == 0) {
            gameSetUpStep[0x56] = 1;
            gameSetUpStep[0x55] = 1;
            goto tail;
        }
    } else {
        if (fn_80050F78(2) == 0) {
            gameSetUpStep[0x56] = 1;
            gameSetUpStep[0x55] = 1;
            goto tail;
        }
    }

    if ((s8)p[0x36] > 0) {
        p[0x36] = (s8)p[0x36] - 1;
        goto tail;
    }

    {
        u8 flag = p[0x2E];
        gameSetUpStep[0x56] = 0;
        gameSetUpStep[0x55] = 0;
        if (flag != 0) goto screen_reset;

        if (((u8 *)&aiPosSwapInputs)[0xCF5F] != 0) {
            settingValuesTo0();
            ((u8 *)&Static_Stats_Tables)[0x48AD] = 1;
            gameSetUpStep[0] = 0;
            memset(&gameSetUpStep[1], 0, 6);
            ((u8 *)&Static_Stats_Tables)[0x4755] = 3;
            fn_80062A74();
            maybeLoadsGameSoundFiles();
            unregisterObjectByID(0xF);
            unregisterObjectByID(0x12);
            unregisterObjectByID(0x9);
            unregisterObjectByID(0x6);
            ((u8 *)&Static_Stats_Tables)[0x48AF] = 1;
            ((u8 *)&Static_Stats_Tables)[0x48B1] = 1;
            menuNumber[0x26] = 1;
            ((u8 *)&aiPosSwapInputs)[0xCF5F] = 0;
            changeScreenVariables(4);
            goto join;
        } else {
            p[0x28] = 0;
            p[0x29] = 0;
            p[0x2A] = 0;
            p[0x2B] = 0;
            p[0x2C] = 0;
            copyInfoToInMemRoster();
            fn_2_AEE8();
            gameSetUpStep[0] = 0;
            memset(&gameSetUpStep[1], 0, 6);
            ((u8 *)&Static_Stats_Tables)[0x48B1] = 1;
            changeScreenVariables(0xB);
            for (i = 1; i < 9; i++) {
                fn_80021AC0(0, i);
                fn_80021AC0(1, i);
            }
            goto join;
        }
    }

screen_reset:
    if (menuNumber[0x24] != 0) goto tail;

    p[0x42] = 0;
    p[0x41] = 0;
    p[0x38] = 0;
    p[0x37] = 0;

    for (i = 0; i < 9; i++) {
        ((u8 *)&cursorPositions)[0x4A + i] = 0;
    }
    for (i = 0; i < 9; i++) {
        ((u8 *)&cursorPositions)[0x53 + i] = 0;
    }

    changeScreenVariables(9);
    menuControlVariables->previousState = 0;

join:
    fn_800AD038(*(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E8]);
    ((u8 *)&Static_Stats_Tables)[0x4755] = 3;
    ((u8 *)&Static_Stats_Tables)[0x472A] = 0;
    ((u8 *)&Static_Stats_Tables)[0x48AD] = 1;

tail:
    ;
}

// .text:0x00006484 size:0x184 mapped:0x80645518
void cssSelectCPUDifficulty(void) {
    switch (lbl_2_bss_F468[0x33]) {
    case 0:
        if (gameSetUpStep[0x5D] != 0 && gameSetUpStep[0x5E] != 0) {
            return;
        }
        if (lbl_2_bss_F468[0x34] == 0) {
            updateCharacterSelectProcessCode(0, 0x1E);
            lbl_2_bss_F468[0x34] = 1;
        }
        lbl_2_bss_F468[0x33] = 1;
        break;
    case 1:
        if (gameSetUpStep[0x5D] != 0 && gameSetUpStep[0x5E] != 0) {
            return;
        }
        fn_2_87A8();
        break;
    case 2:
        if (gameSetUpStep[0x5D] != 0 && gameSetUpStep[0x5E] != 0) {
            return;
        }
        ((u8 *)&Static_Stats_Tables)[0x472A] = 1;
        if (lbl_2_bss_F468[0x35] == 0) {
            lbl_2_bss_F468[0x2E] = 0;
            lbl_2_bss_100B4 = 1;
            menuControlVariables->currentState = 8;
            updateCharacterSelectProcessCode(0, 0x13);
            updateCharacterSelectProcessCode(1, 0x13);
        } else {
            updateCharacterSelectProcessCode(1, 0x12);
            menuControlVariables->currentState = 2;
        }
        lbl_2_bss_F468[0x35] = 0;
        lbl_2_bss_F468[0x33] = 0;
        break;
    }
}

// .text:0x00006608 size:0x17C mapped:0x8064569C
void characterSelectScreenControlable(void) {
    return;
}

// .text:0x00006784 size:0x100 mapped:0x80645818
void fn_2_6784(void) {
    u8 *slot = (u8 *)&cursorPositions;
    u8 *info = lineUpInfoStruct;
    s32 i;

    for (i = 0; i < 9; i++) {
        if (i == 0) {
            *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E4] = 0;
            ((u8 *)&cursorPositions)[0xB] = 0;
            ((u8 *)&cursorPositions)[0x53] = 1;
            ((u8 *)&Static_Stats_Tables)[0x4757] = 1;
        } else {
            u8 picked;
            bool found;

            do {
                u8 *table;
                u8 *ptr;
                s32 k;

                found = FALSE;
                table = &lbl_8010902C[0xC];
                picked = table[(s16)randRange_FUN_80042bf0(0, 9)];
                ptr = slot;
                for (k = 0; k < i; k++) {
                    if ((s8)ptr[0xB] == picked) {
                        found = TRUE;
                    }
                    ptr++;
                }
            } while (found);

            slot[0xB] = picked;
            ((u8 *)&Static_Stats_Tables)[0x4757 + picked] = 1;
            slot[0x53] = 1;
        }

        info[0x24] = i;
        slot++;
        info[0x26] = i;
        info[0x25] = i;
        info += 4;
    }
}

// .text:0x00006884 size:0x270 mapped:0x80645918
void fn_2_6884(void) {
    s32 i;
    s32 rec;
    s32 k;
    s32 slot;
    s32 found;
    s8 result;
    s16 v;
    s16 id;
    u8 key;

    for (i = 0; i < 9; i++) {
        id = *(s16 *)&starMissionCompletionTracker[i * 6 + 0x40B8];
        key = id;

        lineUpInfoStruct[i * 4 + 1] = starMissionCompletionTracker[i * 6 + 0x40BA];
        ((u8 *)&cursorPositions)[i + 2] = id;
        lineUpInfoStruct[i * 4] = i;
        ((u8 *)&cursorPositions)[i + 0x4A] = 1;
        lineUpInfoStruct[i * 4 + 2] = i;
        ((u8 *)&Static_Stats_Tables)[0x4757 + key] = 1;

        found = -1;
        for (rec = 0; rec < 9; rec++) {
            for (k = 0; k < 5; k++) {
                if (key == variantPairs[rec][k]) {
                    found = rec;
                    goto searched;
                }
            }
        }
    searched:
        if (found == -1) {
            result = found;
            goto done;
        }

        for (slot = 0; slot < 9; slot++) {
            v = *(s16 *)&inMemRoster[slot * 0xA0 + 0x24];
            for (k = 0; k < 5; k++) {
                if (v == variantPairs[found][k] && v != key) {
                    result = found;
                    goto done;
                }
            }
        }
        result = -1;

    done:
        if (result != -1) {
            for (k = 0; k < 5; k++) {
                if (variantPairs[result][k] != -1) {
                    ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[result][k]] = 1;
                }
            }
        }
    }
}

// .text:0x00006AF4 size:0x248 mapped:0x80645B88
void fn_2_6AF4(void) {
    s32 i;
    s32 j;
    u8 found;
    s8 target = (s8)starMissionCompletionTracker[0x441F];

    for (i = 0; i < 12; i++) {
        if (target == captainIDOrderedOnCapSS[i]) {
            found = i;
            break;
        }
    }

    for (j = 0; j < 9; j++) {
        u8 x = ((u8 *)&Static_Stats_Tables)[found * 0x48 + 0x4380 + j];

        lineUpInfoStruct[j * 4 + 0x24] = j;
        lineUpInfoStruct[j * 4 + 0x26] = j;
        lineUpInfoStruct[j * 4 + 0x25] = j;
        ((u8 *)&cursorPositions)[j + 0xB] =
            *(s16 *)&((u8 *)&Static_Stats_Tables)[(u8)(x / 9) * 0x5A0 + (u8)(x % 9) * 0xA0 + 0x24];
        ((u8 *)&cursorPositions)[j + 0x53] = 1;
    }

    *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0] = starMissionCompletionTracker[0x441D];
    *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E4] = (s8)starMissionCompletionTracker[0x441F];

    for (j = 0; j < 9; j++) {
        if ((s8)starMissionCompletionTracker[(s8)((u8 *)&cursorPositions)[j + 0xB] * 0x34 + 0x31] == 1) {
            ((u8 *)&cursorPositions)[j + 0xB] = 0x36;
        }
    }
}

// .text:0x00006D3C size:0x7C8 mapped:0x80645DD0
void cssUnloadScreen(void) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (((u8 *)&g_MatchInfo)[0x11] == 0) {
            if (lbl_2_bss_F468[0x2C] == 0) {
                if (lbl_2_bss_F468[0x2D] == 0) {
                    fn_800216F8(0x25, fn_8006285C);
                    lbl_2_bss_F468[0x2D] = 1;
                    goto END;
                } else if (lbl_2_bss_F468[0x2D] == 1) {
                    if (currentDrawingItem->state != 0) {
                        currentDrawingItem->state = 0;
                        initializeUnknown();
                        insertGraphicDrawingFunction(relatedToReturningToPracticeMenu, 0x1000);
                        lbl_2_bss_F468[0x2D] = 0;
                    } else {
                        goto END;
                    }
                }
            }
            lbl_2_bss_F468[0x2C] = 1;

            if (lbl_2_bss_F468[0x28] == 0) {
                if (fn_800697B0() != 0) {
                    goto END;
                }
            }
            lbl_2_bss_F468[0x28] = 1;

            if (lbl_2_bss_F468[0x29] == 0) {
                if (diskReadRelated(&lbl_2_data_720[0x5F4], 6) == 0) {
                    goto END;
                }
            }
            lbl_2_bss_F468[0x29] = 1;

            if (lbl_2_bss_F468[0x2A] == 0) {
                if (diskReadRelated(&lbl_2_data_720[0x604], 9) == 0) {
                    goto END;
                }
            }
            lbl_2_bss_F468[0x2A] = 1;

            if (lbl_2_bss_F468[0x2B] == 0) {
                if (diskReadRelated(&lbl_2_data_720[0x624], 0xF) == 0) {
                    goto END;
                }
            }
            lbl_2_bss_F468[0x2B] = 1;
        }
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (starMissionCompletionTracker[0x4445] != 0) {
            starMissionCompletionTracker[0x4445] = 0;
            ((u8 *)&aiPosSwapInputs)[0xCFA1] = 1;
            if (((u8 *)&superstarUnlocked)[0xE4] != 0) {
                ((u8 *)&aiPosSwapInputs)[0xCF70] = 0;
            } else {
                ((u8 *)&aiPosSwapInputs)[0xCF70] = 1;
            }
            challengeSetRoster();
            unsure_FillRosterPositions(1);
            goto TAIL;
        }
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (starMissionCompletionTracker[0x4445] == 0) {
            s32 i;

            if (starMissionCompletionTracker[0x441D] == 9 && (s8)starMissionCompletionTracker[0x44EF] != 0) {
                u8 *cur = (u8 *)&cursorPositions;
                u8 *info = lineUpInfoStruct;

                for (i = 0; i < 9; i++) {
                    if (i == 0) {
                        *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E4] = 0;
                        cur[0xB] = 0;
                        cur[0x53] = 1;
                        ((u8 *)&Static_Stats_Tables)[0x4757] = 1;
                    } else {
                        u8 *table = &lbl_8010902C[0xC];
                        u8 picked;
                        bool found;

                        do {
                            s32 k;

                            found = FALSE;
                            picked = table[(s16)randRange_FUN_80042bf0(0, 9)];
                            for (k = 0; k < i; k++) {
                                if ((s8)((u8 *)&cursorPositions)[0xB + k] == picked) {
                                    found = TRUE;
                                }
                            }
                        } while (found);

                        cur[0xB] = picked;
                        cur[0x53] = 1;
                        ((u8 *)&Static_Stats_Tables)[0x4757 + picked] = 1;
                    }

                    info[0x24] = i;
                    info[0x26] = i;
                    info[0x25] = i;
                    cur++;
                    info += 4;
                }
            } else {
                s32 j;
                u8 found;
                s8 target = (s8)starMissionCompletionTracker[0x441F];

                for (j = 0; j < 12; j++) {
                    if (target == captainIDOrderedOnCapSS[j]) {
                        found = j;
                        break;
                    }
                }

                for (j = 0; j < 9; j++) {
                    u8 x = ((u8 *)&Static_Stats_Tables)[found * 0x48 + 0x4380 + j];

                    lineUpInfoStruct[j * 4 + 0x24] = j;
                    lineUpInfoStruct[j * 4 + 0x26] = j;
                    lineUpInfoStruct[j * 4 + 0x25] = j;
                    ((u8 *)&cursorPositions)[j + 0xB] =
                        *(s16 *)&((u8 *)&Static_Stats_Tables)[(u8)(x / 9) * 0x5A0 + (u8)(x % 9) * 0xA0 + 0x24];
                    ((u8 *)&cursorPositions)[j + 0x53] = 1;
                }

                *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0] = starMissionCompletionTracker[0x441D];
                *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E4] = (s8)starMissionCompletionTracker[0x441F];

                for (j = 0; j < 9; j++) {
                    if ((s8)starMissionCompletionTracker[(s8)((u8 *)&cursorPositions)[j + 0xB] * 0x34 + 0x31] == 1) {
                        ((u8 *)&cursorPositions)[j + 0xB] = 0x36;
                    }
                }
            }

            for (i = 0; i < 9; i++) {
                s16 id = *(s16 *)&starMissionCompletionTracker[i * 6 + 0x40B8];
                u8 byteB = starMissionCompletionTracker[i * 6 + 0x40BA];
                u8 key = (u8)id;
                s32 rec;
                s32 k;

                lineUpInfoStruct[i * 4 + 1] = byteB;
                ((u8 *)&cursorPositions)[i + 2] = (u8)id;
                lineUpInfoStruct[i * 4] = i;
                ((u8 *)&cursorPositions)[i + 0x4A] = 1;
                lineUpInfoStruct[i * 4 + 2] = i;
                ((u8 *)&Static_Stats_Tables)[0x4757 + key] = 1;

                rec = -1;
                for (k = 0; k < 9; k++) {
                    if (key == variantPairs[k][0]) { rec = k; goto found_row; }
                    if (key == variantPairs[k][1]) { rec = k; goto found_row; }
                    if (key == variantPairs[k][2]) { rec = k; goto found_row; }
                    if (key == variantPairs[k][3]) { rec = k; goto found_row; }
                    if (key == variantPairs[k][4]) { rec = k; goto found_row; }
                }
            found_row:
                if (rec == -1) {
                    goto mark_done;
                }

                for (k = 0; k < 9; k++) {
                    s16 v = *(s16 *)&inMemRoster[k * 0xA0 + 0x24];
                    if (v == variantPairs[rec][0] && v != key) goto mark;
                    if (v == variantPairs[rec][1] && v != key) goto mark;
                    if (v == variantPairs[rec][2] && v != key) goto mark;
                    if (v == variantPairs[rec][3] && v != key) goto mark;
                    if (v == variantPairs[rec][4] && v != key) goto mark;
                }
                rec = -1;
                goto mark_done;
            mark:
                goto mark_done;
            mark_done:
                if (rec != -1) {
                    if (variantPairs[rec][0] != -1) ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[rec][0]] = 1;
                    if (variantPairs[rec][1] != -1) ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[rec][1]] = 1;
                    if (variantPairs[rec][2] != -1) ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[rec][2]] = 1;
                    if (variantPairs[rec][3] != -1) ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[rec][3]] = 1;
                    if (variantPairs[rec][4] != -1) ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[rec][4]] = 1;
                }
            }

            ((u8 *)&aiPosSwapInputs)[0xCFA1] = 0;
        }
    }

TAIL:
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        setPortOfEachPlayer();
    }
    relatedToTeamSelection4();
    menuControlVariables->currentState = 1;

END:
    return;
}

// .text:0x00007504 size:0x840 mapped:0x80646598
void cssResetRosterStruct(void) {
    s32 team;
    s32 k;

    lbl_803CBD24[2] = 0;
    lbl_803CBD24[3] = 0xff;
    lbl_2_bss_F468[0x62] = -1;
    lbl_2_bss_F468[0x61] = -1;
    lbl_2_bss_F468[0x66] = 0;
    lbl_2_bss_F468[0x65] = 0;

    if (menuControlVariables->previousScreen == 9) {
        for (team = 0; team < 2; team++) {
            u8 *row = (u8 *)&cursorPositions + team * 9;
            s32 j;

            for (j = 0; j < 9; j++) {
                row[0x14 + j] = (u8)j;
                row[0x4a + j] = 0;
                row[0x26 + j] = 0;
                if (j == 0) {
                    row[2 + j] = (u8)-1;
                }
            }
        }
        goto TAIL;
    }

    if (g_d_GameSettings.p2_CPU_match_code != 0 || g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        lbl_2_bss_100B8[0x2e] = 0;
        lbl_2_bss_100B8[0x2f] = 0;
    } else {
        lbl_2_bss_100B8[0x2e] = 1;
        lbl_2_bss_100B8[0x2f] = 1;
    }

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        goto TAIL;
    }

    {
    u8 *cur = (u8 *)&cursorPositions;
    for (team = 0; team < 2; team++) {
        u8 *trkP = starMissionCompletionTracker;
        s32 discriminator;
        s32 allDifferent;
        u8 flagCF;
        s32 i;
        s32 j;

        if (team == 0) {
            s8 base = (s8)trkP[0x40bb];
            allDifferent = 1;

            discriminator = trkP[0x441d];

            if (base == (s8)trkP[0x40c1]) allDifferent = 0;
            trkP += 0xc;
            if (base == (s8)trkP[0x40bb]) allDifferent = 0;
            trkP += 6;
            if (base == (s8)trkP[0x40c1]) allDifferent = 0;
            trkP += 6;
            if (base == (s8)trkP[0x40c1]) allDifferent = 0;
            trkP += 6;
            if (base == (s8)trkP[0x40c1]) allDifferent = 0;
            trkP += 6;
            if (base == (s8)trkP[0x40c1]) allDifferent = 0;
            trkP += 6;
            if (base == (s8)trkP[0x40c1]) allDifferent = 0;
            trkP += 6;
            if (base == (s8)trkP[0x40c1]) allDifferent = 0;
        } else {
            discriminator = (s8)starMissionCompletionTracker[0x441f];
        }

        flagCF = ((u8 *)&aiPosSwapInputs)[0xCFA1];
        trkP = starMissionCompletionTracker;

        for (i = 0, j = 0; i < 9; i++, j++) {
            s8 charID = (s8)cur[2 + i];

            if (team == 0 && (flagCF == 0 || allDifferent != 0)) {
                cur[0x14 + i] = trkP[0x40bb];
            } else {
                cur[0x14 + i] = (u8)j;
            }
            trkP += 6;

            cur[0x26 + i] = ((u8 *)&Static_Stats_Tables)[discriminator + (charID / 9) * 0x5A0 + (charID % 9) * 0xA0 + 0x3B];
        }

        cur += 9;
    }
    }

    for (k = 0; k < 54; k++) {
        u8 b0 = ((u8 *)&Static_Stats_Tables)[(k / 9) * 0x5A0 + (k % 9) * 0xA0 + 0x26];
        u8 b1 = ((u8 *)&Static_Stats_Tables)[(k / 9) * 0x5A0 + (k % 9) * 0xA0 + 0x27];
        lbl_2_bss_3A8[k] = b0 * 2 + b1;
    }

    if (menuControlVariables->previousScreen == 11) {
        goto TAIL;
    }
    if (((u8 *)&aiPosSwapInputs)[0xCFA1] != 0) {
        goto TAIL;
    }
    if (0 >= 9) {
        goto TAIL;
    }

    lbl_2_bss_3A8[*(u16 *)&starMissionCompletionTracker[0x40b8]] = starMissionCompletionTracker[0x40bc];
    lbl_2_bss_3A8[*(u16 *)&starMissionCompletionTracker[0x40be]] = starMissionCompletionTracker[0x40c2];
    lbl_2_bss_3A8[*(u16 *)&starMissionCompletionTracker[0x40c4]] = starMissionCompletionTracker[0x40c8];
    lbl_2_bss_3A8[*(u16 *)&starMissionCompletionTracker[0x40ca]] = starMissionCompletionTracker[0x40ce];
    lbl_2_bss_3A8[*(u16 *)&starMissionCompletionTracker[0x40d0]] = starMissionCompletionTracker[0x40d4];
    lbl_2_bss_3A8[*(u16 *)&starMissionCompletionTracker[0x40d6]] = starMissionCompletionTracker[0x40da];
    lbl_2_bss_3A8[*(u16 *)&starMissionCompletionTracker[0x40dc]] = starMissionCompletionTracker[0x40e0];
    lbl_2_bss_3A8[*(u16 *)&starMissionCompletionTracker[0x40e2]] = starMissionCompletionTracker[0x40e6];
    lbl_2_bss_3A8[*(u16 *)&starMissionCompletionTracker[0x40e8]] = starMissionCompletionTracker[0x40ec];

TAIL:
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        for (team = 0; team < 2; team++) {
            teamLogoDetermination(team);
        }
    }

    ((u8 *)&Static_Stats_Tables)[0x4702] = 1;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        s32 zeroCharCount = 0;

        for (k = 0; k < 54; k++) {
            if (Static_Stats_Tables.charOnCharacterGridSelected[k] == 0) {
                zeroCharCount++;
            }
        }
        if (zeroCharCount != 0) {
            lbl_2_bss_F468[0x3f] = 1;
            lbl_2_bss_F468[0x37] = 1;
            *(u32 *)&lbl_2_bss_F468[0] = 9;
        } else {
            lbl_2_bss_F468[0x3f] = 0;
        }
    }
}

// .text:0x00007D44 size:0x98 mapped:0x80646DD8
void fn_2_7D44(void) {
    if (menuControlVariables->previousScreen == 9) {
        memset(lbl_2_bss_100B8, 0, 0x54);
    }
    ((u8 *)&Static_Stats_Tables)[0x4755] = 1;
    lbl_2_bss_100B8[0x2D] = 4;
    fn_2_16A74(0, 0);
    fn_2_16A74(1, 0);
    fn_2_16A74(2, 0);
    fn_2_16A74(3, 0);
}

// .text:0x00007DDC size:0x910 mapped:0x80646E70
void cssLoadingScreenRelated(void) {
    u8 local[4];
    s32 i, team, port, k;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        memset(&Static_Stats_Tables.charOnCharacterGridSelected, 0, 0x36);
    }

    ((u8 *)&Static_Stats_Tables)[0x48AD] = 0;
    gameSetUpStep[0] = 2;

    memset(local, 0xFF, 4);

    if (menuControlVariables->previousScreen == 9) {
        gameSetUpStep[0x59] = 0;
        gameSetUpStep[0x5A] = 1;
    } else {
        if (g_d_GameSettings.p2_CPU_match_code != 0 || g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            gameSetUpStep[0x59] = 0;
        } else {
            gameSetUpStep[0x59] = 1;
        }
        gameSetUpStep[0x5A] = 1;
    }

    memset(local, 0, 4);

    if (g_d_GameSettings.p2_CPU_match_code == 0) {
        s8 p0 = Static_Stats_Tables.playerNumberByPort[0];
        local[p0] = 1;
        if (p0 != 0) {
            local[1] = 2;
        } else {
            local[0] = 2;
        }
    } else {
        s8 p1 = Static_Stats_Tables.playerNumberByPort[1];
        s8 p0 = Static_Stats_Tables.playerNumberByPort[0];
        local[p1] = 1;
        local[p0] = 1;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        css_initValues(local[0], local[1], local[2], local[3], 0, 0);
    } else {
        css_initValues(local[0], local[1], local[2], local[3], 0, 1);
    }

    cssCheckSomethingAboutCharacters();

    ((u8 *)&Static_Stats_Tables)[0x472A] = 0xFF;

    if (menuControlVariables->previousScreen == 0xB || g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        *(s32 *)&lbl_2_bss_F468[4] = 9;
    } else {
        *(s32 *)&lbl_2_bss_F468[4] = 0xA;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        for (i = 0; i < 54; i++) {
            if (starMissionCompletionTracker[i * 0x34 + 0x31] == 1) {
                Static_Stats_Tables.charOnCharacterGridSelected[i] = 0;
                addOrRemoveCharacterToTeam(0, i, 0);
            } else {
                s16 partner;
                Static_Stats_Tables.charOnCharacterGridSelected[i] = 1;
                partner = (s16)fn_80067AC8(i, 0);
                if (partner == -1) {
                    addOrRemoveCharacterToTeam(0, i, 1);
                } else if (starMissionCompletionTracker[partner * 0x34 + 0x31] == 1) {
                    addOrRemoveCharacterToTeam(0, i, 0);
                } else {
                    addOrRemoveCharacterToTeam(0, i, 1);
                }
            }
        }
        lbl_2_bss_F468[0x37] = 1;
    } else {
        for (k = 0; k < 6; k++) {
            s32 flag = !((u8 *)&g_d_GameSettings)[0x1A + k];
            u8 target = unlockableCharacter_noDupeNoGapCharID[k];
            s32 rec;
            for (rec = 0; rec < 54; rec++) {
                if (characterStaticIndexes[rec * 6 + 2] == target) {
                    Static_Stats_Tables.charOnCharacterGridSelected[rec] = flag;
                }
            }
            unlockableCharacter_noDupeNoGapCharID[k] = target;
        }

        for (team = 0; team < 2; team++) {
            for (i = 0; i < 9; i++) {
                s8 charID = (s8)((u8 *)&cursorPositions)[team * 9 + i + 2];
                if (charID == -1) continue;
                Static_Stats_Tables.charOnCharacterGridSelected[charID] = 1;

                if (g_d_GameSettings.p2_CPU_match_code == 0 && team != 0) {
                    if ((s8)Static_Stats_Tables.playerNumberByPort[0] != 0) {
                        addOrRemoveCharacterToTeam(0, charID, 1);
                    } else {
                        addOrRemoveCharacterToTeam(1, charID, 1);
                    }
                } else {
                    addOrRemoveCharacterToTeam((s8)((u8 *)&Static_Stats_Tables)[0x46F8 + team], charID, 1);
                }
                addRemoveCharVariantRelated((u8)team, charID, 1);
            }
        }
    }

    for (port = 0; port < 2; port++) {
        if (g_d_GameSettings.p2_CPU_match_code == 0 && port != 0) {
            s8 pn = Static_Stats_Tables.playerNumberByPort[port];
            ((u8 *)&charSelectStruct)[pn + 0x74] = 1;
        } else {
            s8 pn = Static_Stats_Tables.playerNumberByPort[port];
            ((u8 *)&charSelectStruct)[pn + 0x74] = 0;
        }

        if (port != 0) {
            *(s32 *)&lbl_2_bss_F410[port * 4 + 0x20] = 9;
        } else {
            *(s32 *)&lbl_2_bss_F410[port * 4 + 0x20] = 0;
        }

        if (Static_Stats_Tables.charOnCharacterGridSelected[*(s32 *)&lbl_2_bss_F410[port * 4 + 0x20]] == 0) {
            for (k = 0; k < 8; k++) {
                if (Static_Stats_Tables.charOnCharacterGridSelected[characterIconsOnCSS[k]] == 0
                    && characterIconsOnCSS[k] != 0xFF) {
                    *(s32 *)&lbl_2_bss_F410[port * 4 + 0x20] = characterIconsOnCSS[k];
                    break;
                }
            }
        }

        switch ((s8)Static_Stats_Tables.playerNumberByPort[port]) {
        case 0:
            cssLoadingRelated_1(1, *(s32 *)&lbl_2_bss_F410[port * 4 + 0x20], -1, -1, -1, 0);
            break;
        case 1:
            cssLoadingRelated_1(1, -1, *(s32 *)&lbl_2_bss_F410[port * 4 + 0x20], -1, -1, 0);
            break;
        case 2:
            cssLoadingRelated_1(1, -1, -1, *(s32 *)&lbl_2_bss_F410[port * 4 + 0x20], -1, 0);
            break;
        case 3:
            cssLoadingRelated_1(1, -1, -1, -1, *(s32 *)&lbl_2_bss_F410[port * 4 + 0x20], 0);
            break;
        }
    }

    if (menuControlVariables->previousScreen == 9) {
        updateCharacterSelectProcessCode(0, 0xA);
        updateCharacterSelectProcessCode(1, 0xA);
    } else if (menuControlVariables->previousScreen != 0xB && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        updateCharacterSelectProcessCode(0, 0xA);
        updateCharacterSelectProcessCode(1, 0xA);
    } else {
        updateCharacterSelectProcessCode(0, 9);
        updateCharacterSelectProcessCode(1, 9);
    }

    gameSetUpStep[0] = 2;
}

// .text:0x000086EC size:0x94 mapped:0x80647780
void fn_2_86EC(void) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && lbl_8037169C[0x12] == 0) {
        challenge_setTransitionScreenCharacterPortrait(10, (s8)lbl_2_data_3CE0[starMissionCompletionTracker[0x441E]]);
    }
    cssLoadingScreenRelated();
    cssResetRosterStruct();
    lbl_2_bss_F468[0x56] = 0;
    menuControlVariables->currentState = 2;
}

// .text:0x00008780 size:0x14 mapped:0x80647814
s32 fn_2_8780(s32 arg0) {
    if (arg0 != 0) {
        return 0x13;
    }
    return 9;
}

// .text:0x00008794 size:0x14 mapped:0x80647828
s32 fn_2_8794(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        arg1 += 10;
    }
    return arg1;
}

// .text:0x000087A8 size:0x194 mapped:0x8064783C
void fn_2_87A8(void) {
    s32 v = *(s32 *)&lbl_2_bss_F410[0x4C];
    u8 *pad;
    u16 held;

    if (gameSetUpStep[0x55] != 0 || gameSetUpStep[0x56] != 0) {
        return;
    }

    pad = (u8 *)&AtBat_ButtonInput1 + (s8)Static_Stats_Tables.playerNumberByPort[0] * 0x20;
    held = *(u16 *)(pad + 4);
    if (held & 8) {
        *(s32 *)&lbl_2_bss_F410[0x4C] = v - 1;
        if (*(s32 *)&lbl_2_bss_F410[0x4C] < 0) {
            *(s32 *)&lbl_2_bss_F410[0x4C] = 3;
        }
        if (v != *(s32 *)&lbl_2_bss_F410[0x4C]) {
            updateCharacterSelectProcessCode(0, 0x20);
        }
        cursorSndFx(8);
    } else if (held & 4) {
        *(s32 *)&lbl_2_bss_F410[0x4C] = v + 1;
        if (*(s32 *)&lbl_2_bss_F410[0x4C] == 4) {
            *(s32 *)&lbl_2_bss_F410[0x4C] = 0;
        }
        if (v != *(s32 *)&lbl_2_bss_F410[0x4C]) {
            updateCharacterSelectProcessCode(0, 0x20);
        }
        cursorSndFx(4);
    } else if (*(u16 *)(pad + 2) & 0x200) {
        lbl_2_bss_F468[0x33] = 2;
        lbl_2_bss_F468[0x34] = 0;
        lbl_2_bss_F468[0x35] = 1;
        ((u8 *)&g_MatchInfo)[0xE] = 1;
        updateCharacterSelectProcessCode(1, 0x1F);
        cursorSndFx(0x200);
    } else if (*(u16 *)(pad + 2) & 0x100) {
        ((u8 *)&inningSetting)[3] = lbl_803CB8D0[v];
        updateCharacterSelectProcessCode(0, 0x21);
        lbl_2_bss_F468[0x33] = 2;
        lbl_2_bss_F468[0x34] = 0;
        lbl_2_bss_F468[0x35] = 0;
        cursorSndFx(0x100);
    }
}

// .text:0x0000893C size:0x4 mapped:0x806479D0
void fn_2_893C(void) {
    return;
}

// .text:0x00008940 size:0x3B8 mapped:0x806479D4
void copyInfoToInMemRoster(void) {
    u8 *cursorOrig = (u8 *)&cursorPositions;
    u8 *cursorWalk = cursorOrig;
    u8 *rosterBase = inMemRoster;
    u8 *lineupBase = lineUpInfoStruct;
    s32 team;
    s32 player;
    s32 charId;

    for (team = 0; team < 2; team++) {
        u8 *cur = cursorWalk;
        u8 *dst = rosterBase;
        u8 *lineup = lineupBase;
        u8 *track = starMissionCompletionTracker;

        for (player = 0; player < 9; player++) {
            u8 *src;

            charId = (s8)cur[2];
            src = &((u8 *)&Static_Stats_Tables)[(charId / 9) * 0x5A0] + (charId % 9) * 0xA0;

            memcpy(dst + 0x00, src + 0x00, 0x1e);
            *(s16 *)(dst + 0x24) = *(s16 *)(src + 0x24);
            dst[0x26] = src[0x26];
            dst[0x27] = src[0x27];
            memcpy(dst + 0x28, src + 0x28, 2);
            memcpy(dst + 0x2a, src + 0x2a, 2);
            dst[0x2c] = src[0x2c];
            dst[0x2d] = src[0x2d];
            dst[0x2e] = src[0x2e];
            dst[0x2f] = src[0x2f];
            dst[0x30] = src[0x30];
            dst[0x31] = src[0x31];
            dst[0x32] = src[0x32];
            dst[0x33] = src[0x33];
            dst[0x34] = src[0x34];
            memcpy(dst + 0x35, src + 0x35, 2);
            *(u32 *)(dst + 0x20) = *(u32 *)(src + 0x20);
            memcpy(dst + 0x37, src + 0x37, 4);
            memcpy(dst + 0x3b, src + 0x3b, 0x36);
            dst[0x71] = src[0x71];
            *(u16 *)(dst + 0x74) = *(u16 *)(src + 0x74);
            *(u16 *)(dst + 0x76) = *(u16 *)(src + 0x76);
            *(u16 *)(dst + 0x78) = *(u16 *)(src + 0x78);
            *(u16 *)(dst + 0x7a) = *(u16 *)(src + 0x7a);
            *(u16 *)(dst + 0x7c) = *(u16 *)(src + 0x7c);
            *(u16 *)(dst + 0x7e) = *(u16 *)(src + 0x7e);
            *(u16 *)(dst + 0x80) = *(u16 *)(src + 0x80);
            *(u16 *)(dst + 0x82) = *(u16 *)(src + 0x82);
            *(u16 *)(dst + 0x84) = *(u16 *)(src + 0x84);
            *(u16 *)(dst + 0x86) = *(u16 *)(src + 0x86);
            *(u16 *)(dst + 0x88) = *(u16 *)(src + 0x88);
            *(u16 *)(dst + 0x8a) = *(u16 *)(src + 0x8a);
            *(u16 *)(dst + 0x8c) = *(u16 *)(src + 0x8c);
            *(u16 *)(dst + 0x8e) = *(u16 *)(src + 0x8e);
            *(u16 *)(dst + 0x90) = *(u16 *)(src + 0x90);
            *(u16 *)(dst + 0x92) = *(u16 *)(src + 0x92);
            *(u16 *)(dst + 0x94) = *(u16 *)(src + 0x94);
            *(u16 *)(dst + 0x96) = *(u16 *)(src + 0x96);
            *(u16 *)(dst + 0x98) = *(u16 *)(src + 0x98);
            *(u16 *)(dst + 0x9a) = *(u16 *)(src + 0x9a);
            *(u16 *)(dst + 0x9c) = *(u16 *)(src + 0x9c);

            lineup[2] = cur[0x14];

            if (team == 0) {
                if (((u8 *)&g_d_GameSettings)[7] == 5) {
                    u8 packed = lbl_2_bss_3A8[*(s16 *)&track[0x40b8]];
                    dst[0x26] = packed / 2;
                    dst[0x27] = packed % 2;
                }
            }

            dst += 0xa0;
            lineup += 4;
            track += 6;
            cur += 1;
        }
        rosterBase += 0x5a0;
        lineupBase += 0x24;
        cursorWalk += 9;
    }

    {
        u8 *cp = cursorOrig;
        s16 *mi = (s16 *)((u8 *)&g_MatchInfo + 0x12);

        mi[0] = (s8)cp[2];
        mi[1] = (s8)cp[3];
        mi[2] = (s8)cp[4];
        mi[3] = (s8)cp[5];
        mi[4] = (s8)cp[6];
        mi[5] = (s8)cp[7];
        mi[6] = (s8)cp[8];
        mi[7] = (s8)cp[9];
        mi[8] = (s8)cp[0xa];

        mi = (s16 *)((u8 *)&g_MatchInfo + 0x24);
        cp = cursorOrig + 9;

        mi[0] = (s8)cp[2];
        mi[1] = (s8)cp[3];
        mi[2] = (s8)cp[4];
        mi[3] = (s8)cp[5];
        mi[4] = (s8)cp[6];
        mi[5] = (s8)cp[7];
        mi[6] = (s8)cp[8];
        mi[7] = (s8)cp[9];
        mi[8] = (s8)cp[0xa];
    }

    fn_80066EAC(0);
    fn_80066EAC(1);
}

// .text:0x00008CF8 size:0x8E0 mapped:0x80647D8C
void fn_2_8CF8(u16 team) {
    s32 i;
    s32 t;

    if (lbl_2_bss_100B8[team + 0x30] != 0) {
        if (((u8 *)&g_d_GameSettings)[0x10] == 1) {
            u8 *dst = &lbl_2_bss_E8CC[team * 0x5a0];
            u8 *src = &inMemRoster[team * 0x5a0];
            u8 *ldst = &lbl_2_bss_DCE8[team * 0x24];
            u8 *lsrc = &lineUpInfoStruct[team * 0x24];
            u8 *snap = &lbl_2_bss_3E4[team * 0x12];

            for (i = 0; i < 9; i++) {
                u8 lineup0 = lsrc[0];

                memcpy(dst + 0x00, src + 0x00, 0x1e);
                *(s16 *)(dst + 0x24) = *(s16 *)(src + 0x24);
                dst[0x26] = src[0x26];
                dst[0x27] = src[0x27];
                memcpy(dst + 0x28, src + 0x28, 2);
                memcpy(dst + 0x2a, src + 0x2a, 2);
                dst[0x2c] = src[0x2c];
                dst[0x2d] = src[0x2d];
                dst[0x2e] = src[0x2e];
                dst[0x2f] = src[0x2f];
                dst[0x30] = src[0x30];
                dst[0x31] = src[0x31];
                dst[0x32] = src[0x32];
                dst[0x33] = src[0x33];
                dst[0x34] = src[0x34];
                memcpy(dst + 0x35, src + 0x35, 2);
                *(u32 *)(dst + 0x20) = *(u32 *)(src + 0x20);
                memcpy(dst + 0x37, src + 0x37, 4);
                memcpy(dst + 0x3b, src + 0x3b, 0x36);
                dst[0x71] = src[0x71];
                *(u16 *)(dst + 0x74) = *(u16 *)(src + 0x74);
                *(u16 *)(dst + 0x76) = *(u16 *)(src + 0x76);
                *(u16 *)(dst + 0x78) = *(u16 *)(src + 0x78);
                *(u16 *)(dst + 0x7a) = *(u16 *)(src + 0x7a);
                *(u16 *)(dst + 0x7c) = *(u16 *)(src + 0x7c);
                *(u16 *)(dst + 0x7e) = *(u16 *)(src + 0x7e);
                *(u16 *)(dst + 0x80) = *(u16 *)(src + 0x80);
                *(u16 *)(dst + 0x82) = *(u16 *)(src + 0x82);
                *(u16 *)(dst + 0x84) = *(u16 *)(src + 0x84);
                *(u16 *)(dst + 0x86) = *(u16 *)(src + 0x86);
                *(u16 *)(dst + 0x88) = *(u16 *)(src + 0x88);
                *(u16 *)(dst + 0x8a) = *(u16 *)(src + 0x8a);
                *(u16 *)(dst + 0x8c) = *(u16 *)(src + 0x8c);
                *(u16 *)(dst + 0x8e) = *(u16 *)(src + 0x8e);
                *(u16 *)(dst + 0x90) = *(u16 *)(src + 0x90);
                *(u16 *)(dst + 0x92) = *(u16 *)(src + 0x92);
                *(u16 *)(dst + 0x94) = *(u16 *)(src + 0x94);
                *(u16 *)(dst + 0x96) = *(u16 *)(src + 0x96);
                *(u16 *)(dst + 0x98) = *(u16 *)(src + 0x98);

                ldst[0] = lineup0;
                ldst[1] = lsrc[1];

                *(u16 *)(dst + 0x9a) = *(u16 *)(src + 0x9a);
                *(u16 *)(dst + 0x9c) = *(u16 *)(src + 0x9c);

                ldst[2] = lsrc[2];
                ldst[3] = lsrc[3];

                *(u16 *)snap = lineup0;

                dst += 0xa0;
                src += 0xa0;
                ldst += 4;
                lsrc += 4;
                snap += 2;
            }
        } else {
            for (t = 0; t < 2; t++) {
                u8 *dst = &lbl_2_bss_E8CC[t * 0x5a0];
                u8 *src = &inMemRoster[t * 0x5a0];
                u8 *ldst = &lbl_2_bss_DCE8[t * 0x24];
                u8 *lsrc = &lineUpInfoStruct[t * 0x24];
                u8 *snap = &lbl_2_bss_3E4[t * 0x12];

                for (i = 0; i < 9; i++) {
                    u8 lineup0 = lsrc[0];

                    memcpy(dst + 0x00, src + 0x00, 0x1e);
                    *(s16 *)(dst + 0x24) = *(s16 *)(src + 0x24);
                    dst[0x26] = src[0x26];
                    dst[0x27] = src[0x27];
                    memcpy(dst + 0x28, src + 0x28, 2);
                    memcpy(dst + 0x2a, src + 0x2a, 2);
                    dst[0x2c] = src[0x2c];
                    dst[0x2d] = src[0x2d];
                    dst[0x2e] = src[0x2e];
                    dst[0x2f] = src[0x2f];
                    dst[0x30] = src[0x30];
                    dst[0x31] = src[0x31];
                    dst[0x32] = src[0x32];
                    dst[0x33] = src[0x33];
                    dst[0x34] = src[0x34];
                    memcpy(dst + 0x35, src + 0x35, 2);
                    *(u32 *)(dst + 0x20) = *(u32 *)(src + 0x20);
                    memcpy(dst + 0x37, src + 0x37, 4);
                    memcpy(dst + 0x3b, src + 0x3b, 0x36);
                    dst[0x71] = src[0x71];
                    *(u16 *)(dst + 0x74) = *(u16 *)(src + 0x74);
                    *(u16 *)(dst + 0x76) = *(u16 *)(src + 0x76);
                    *(u16 *)(dst + 0x78) = *(u16 *)(src + 0x78);
                    *(u16 *)(dst + 0x7a) = *(u16 *)(src + 0x7a);
                    *(u16 *)(dst + 0x7c) = *(u16 *)(src + 0x7c);
                    *(u16 *)(dst + 0x7e) = *(u16 *)(src + 0x7e);
                    *(u16 *)(dst + 0x80) = *(u16 *)(src + 0x80);
                    *(u16 *)(dst + 0x82) = *(u16 *)(src + 0x82);
                    *(u16 *)(dst + 0x84) = *(u16 *)(src + 0x84);
                    *(u16 *)(dst + 0x86) = *(u16 *)(src + 0x86);
                    *(u16 *)(dst + 0x88) = *(u16 *)(src + 0x88);
                    *(u16 *)(dst + 0x8a) = *(u16 *)(src + 0x8a);
                    *(u16 *)(dst + 0x8c) = *(u16 *)(src + 0x8c);
                    *(u16 *)(dst + 0x8e) = *(u16 *)(src + 0x8e);
                    *(u16 *)(dst + 0x90) = *(u16 *)(src + 0x90);
                    *(u16 *)(dst + 0x92) = *(u16 *)(src + 0x92);
                    *(u16 *)(dst + 0x94) = *(u16 *)(src + 0x94);
                    *(u16 *)(dst + 0x96) = *(u16 *)(src + 0x96);
                    *(u16 *)(dst + 0x98) = *(u16 *)(src + 0x98);

                    ldst[0] = lineup0;
                    ldst[1] = lsrc[1];

                    *(u16 *)(dst + 0x9a) = *(u16 *)(src + 0x9a);
                    *(u16 *)(dst + 0x9c) = *(u16 *)(src + 0x9c);

                    ldst[2] = lsrc[2];
                    ldst[3] = lsrc[3];

                    *(u16 *)snap = lineup0;

                    dst += 0xa0;
                    src += 0xa0;
                    ldst += 4;
                    lsrc += 4;
                    snap += 2;
                }
            }
        }

        fn_2_9ACC(team);
        return;
    } else {
        if (((u8 *)&g_d_GameSettings)[0x10] == 1) {
            u8 *src = &lbl_2_bss_E8CC[team * 0x5a0];
            u8 *dst = &inMemRoster[team * 0x5a0];
            u8 *lsrc = &lbl_2_bss_DCE8[team * 0x24];
            u8 *ldst = &lineUpInfoStruct[team * 0x24];
            u8 *snap = &lbl_2_bss_3E4[team * 0x12];

            for (i = 0; i < 9; i++) {
                memcpy(dst + 0x00, src + 0x00, 0x1e);
                *(s16 *)(dst + 0x24) = *(s16 *)(src + 0x24);
                dst[0x26] = src[0x26];
                dst[0x27] = src[0x27];
                memcpy(dst + 0x28, src + 0x28, 2);
                memcpy(dst + 0x2a, src + 0x2a, 2);
                dst[0x2c] = src[0x2c];
                dst[0x2d] = src[0x2d];
                dst[0x2e] = src[0x2e];
                dst[0x2f] = src[0x2f];
                dst[0x30] = src[0x30];
                dst[0x31] = src[0x31];
                dst[0x32] = src[0x32];
                dst[0x33] = src[0x33];
                dst[0x34] = src[0x34];
                memcpy(dst + 0x35, src + 0x35, 2);
                *(u32 *)(dst + 0x20) = *(u32 *)(src + 0x20);
                memcpy(dst + 0x37, src + 0x37, 4);
                memcpy(dst + 0x3b, src + 0x3b, 0x36);
                dst[0x71] = src[0x71];
                *(u16 *)(dst + 0x74) = *(u16 *)(src + 0x74);
                *(u16 *)(dst + 0x76) = *(u16 *)(src + 0x76);
                *(u16 *)(dst + 0x78) = *(u16 *)(src + 0x78);
                *(u16 *)(dst + 0x7a) = *(u16 *)(src + 0x7a);
                *(u16 *)(dst + 0x7c) = *(u16 *)(src + 0x7c);
                *(u16 *)(dst + 0x7e) = *(u16 *)(src + 0x7e);
                *(u16 *)(dst + 0x80) = *(u16 *)(src + 0x80);
                *(u16 *)(dst + 0x82) = *(u16 *)(src + 0x82);
                *(u16 *)(dst + 0x84) = *(u16 *)(src + 0x84);
                *(u16 *)(dst + 0x86) = *(u16 *)(src + 0x86);
                *(u16 *)(dst + 0x88) = *(u16 *)(src + 0x88);
                *(u16 *)(dst + 0x8a) = *(u16 *)(src + 0x8a);
                *(u16 *)(dst + 0x8c) = *(u16 *)(src + 0x8c);
                *(u16 *)(dst + 0x8e) = *(u16 *)(src + 0x8e);
                *(u16 *)(dst + 0x90) = *(u16 *)(src + 0x90);
                *(u16 *)(dst + 0x92) = *(u16 *)(src + 0x92);
                *(u16 *)(dst + 0x94) = *(u16 *)(src + 0x94);
                *(u16 *)(dst + 0x96) = *(u16 *)(src + 0x96);
                *(u16 *)(dst + 0x98) = *(u16 *)(src + 0x98);

                ldst[0] = lsrc[0];
                ldst[1] = lsrc[1];

                *(u16 *)(dst + 0x9a) = *(u16 *)(src + 0x9a);
                *(u16 *)(dst + 0x9c) = *(u16 *)(src + 0x9c);

                ldst[2] = lsrc[2];

                *(s16 *)(dst + 0x24) = *(s16 *)snap;

                ldst[3] = lsrc[3];

                dst += 0xa0;
                src += 0xa0;
                ldst += 4;
                lsrc += 4;
                snap += 2;
            }
        } else {
            for (t = 0; t < 2; t++) {
                u8 *src = &lbl_2_bss_E8CC[t * 0x5a0];
                u8 *dst = &inMemRoster[t * 0x5a0];
                u8 *lsrc = &lbl_2_bss_DCE8[t * 0x24];
                u8 *ldst = &lineUpInfoStruct[t * 0x24];
                u8 *snap = &lbl_2_bss_3E4[t * 0x12];

                for (i = 0; i < 9; i++) {
                    memcpy(dst + 0x00, src + 0x00, 0x1e);
                    *(s16 *)(dst + 0x24) = *(s16 *)(src + 0x24);
                    dst[0x26] = src[0x26];
                    dst[0x27] = src[0x27];
                    memcpy(dst + 0x28, src + 0x28, 2);
                    memcpy(dst + 0x2a, src + 0x2a, 2);
                    dst[0x2c] = src[0x2c];
                    dst[0x2d] = src[0x2d];
                    dst[0x2e] = src[0x2e];
                    dst[0x2f] = src[0x2f];
                    dst[0x30] = src[0x30];
                    dst[0x31] = src[0x31];
                    dst[0x32] = src[0x32];
                    dst[0x33] = src[0x33];
                    dst[0x34] = src[0x34];
                    memcpy(dst + 0x35, src + 0x35, 2);
                    *(u32 *)(dst + 0x20) = *(u32 *)(src + 0x20);
                    memcpy(dst + 0x37, src + 0x37, 4);
                    memcpy(dst + 0x3b, src + 0x3b, 0x36);
                    dst[0x71] = src[0x71];
                    *(u16 *)(dst + 0x74) = *(u16 *)(src + 0x74);
                    *(u16 *)(dst + 0x76) = *(u16 *)(src + 0x76);
                    *(u16 *)(dst + 0x78) = *(u16 *)(src + 0x78);
                    *(u16 *)(dst + 0x7a) = *(u16 *)(src + 0x7a);
                    *(u16 *)(dst + 0x7c) = *(u16 *)(src + 0x7c);
                    *(u16 *)(dst + 0x7e) = *(u16 *)(src + 0x7e);
                    *(u16 *)(dst + 0x80) = *(u16 *)(src + 0x80);
                    *(u16 *)(dst + 0x82) = *(u16 *)(src + 0x82);
                    *(u16 *)(dst + 0x84) = *(u16 *)(src + 0x84);
                    *(u16 *)(dst + 0x86) = *(u16 *)(src + 0x86);
                    *(u16 *)(dst + 0x88) = *(u16 *)(src + 0x88);
                    *(u16 *)(dst + 0x8a) = *(u16 *)(src + 0x8a);
                    *(u16 *)(dst + 0x8c) = *(u16 *)(src + 0x8c);
                    *(u16 *)(dst + 0x8e) = *(u16 *)(src + 0x8e);
                    *(u16 *)(dst + 0x90) = *(u16 *)(src + 0x90);
                    *(u16 *)(dst + 0x92) = *(u16 *)(src + 0x92);
                    *(u16 *)(dst + 0x94) = *(u16 *)(src + 0x94);
                    *(u16 *)(dst + 0x96) = *(u16 *)(src + 0x96);
                    *(u16 *)(dst + 0x98) = *(u16 *)(src + 0x98);

                    ldst[0] = lsrc[0];
                    ldst[1] = lsrc[1];

                    *(u16 *)(dst + 0x9a) = *(u16 *)(src + 0x9a);
                    *(u16 *)(dst + 0x9c) = *(u16 *)(src + 0x9c);

                    ldst[2] = lsrc[2];

                    *(s16 *)(dst + 0x24) = *(s16 *)snap;

                    ldst[3] = lsrc[3];

                    dst += 0xa0;
                    src += 0xa0;
                    ldst += 4;
                    lsrc += 4;
                    snap += 2;
                }
            }
        }
    }
}

// .text:0x000095D8 size:0x4F4 mapped:0x8064866C
void fn_2_95D8(void) {
    s32 team;
    s32 j;
    s32 k;
    s32 lim;
    s32 lastVal;
    s32 base;
    s32 sel;
    s32 status[2];
    s8 picks[18];
    s8 taken[0x36];
    s32 r;
    s32 mode;
    s32 counter;
    s32 i;
    u8 *cursorBase;
    u8 *statsBase;

    {
        u16 state = menuControlVariables->currentState;

        if (state >= 4) {
            goto tail;
        }

        cursorBase = (u8 *)&cursorPositions;
        statsBase = (u8 *)&Static_Stats_Tables;

        {
            u8 *cursorTeam = cursorBase;
            u8 *lineUpTeam = lineUpInfoStruct;
            s32 *limPtr = (s32 *)lbl_2_bss_F468;
            s32 *statusPtr = status;
            s32 *capIdPtr = (s32 *)(statsBase + 0x46E0);

            for (team = 0; team < 2; team++) {
                u8 *selWalk = cursorTeam;

                lim = *limPtr;
                if (team != 0) {
                    lim -= 10;
                }

                *statusPtr = (team == 0) ? 0xFF0F : 0xF00F;

                lastVal = (s8)starMissionCompletionTracker[0x441F];

                for (j = 0; j < 9; j++) {
                    for (k = 0; k < 9; k++) {
                        if (j == (s8)lineUpTeam[1 + k * 4]) {
                            break;
                        }
                    }

                    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                        base = *capIdPtr;
                    } else if (team == 0) {
                        base = *capIdPtr;
                    } else {
                        base = lastVal;
                    }

                    sel = (s8)selWalk[2];
                    if (sel == base) {
                        *statusPtr = 0x88FF;
                    } else if (j == lim) {
                        *statusPtr = 0xFF0F;
                    } else {
                        *statusPtr = 0xFFFF;
                    }

                    selWalk += 1;
                }

                cursorTeam += 9;
                statusPtr += 1;
                lineUpTeam += 0x24;
                capIdPtr += 1;
                limPtr += 1;
            }
        }

        counter = 5;

        for (i = 0; i < 9; i++) {
            picks[i] = -1;
        }
        for (i = 0; i < 9; i++) {
            picks[9 + i] = -1;
        }
        for (i = 0; i < 0x36; i++) {
            taken[i] = -1;
        }

        mode = ((u8 *)&g_d_GameSettings)[0x10];

        {
            s8 *takenPtr = taken;
            u8 *charGridPtr = statsBase + 0x4757;

            for (r = 0; r < 0x36; r++) {
                if (r == *(s32 *)&lbl_2_bss_F410[0x20]) {
                    status[0] = 0xFFF;
                } else if (r == *(s32 *)&lbl_2_bss_F410[0x24]) {
                    status[0] = 0xF0FF;
                } else {
                    status[0] = 0xFFFF;
                }

                {
                    u8 *cursorTeam2 = cursorBase;
                    s8 *pickTeam = picks;

                    for (team = 0; team < 2; team++) {
                        u8 *cursorWalk = cursorTeam2;
                        s8 *pickWalk = pickTeam;

                        for (j = 0; j < 9; j++) {
                            sel = (s8)cursorWalk[2];
                            if (r == sel && team == 0 && status[0] != 0xFFF) {
                                *takenPtr = r;
                                status[0] = 0x88F;
                                *pickWalk = r;
                            } else if (r == sel && team != 0 && status[0] != 0xFFF) {
                                *takenPtr = r;
                                status[0] = 0x808F;
                                *pickWalk = r;
                            }
                            cursorWalk += 1;
                            pickWalk += 1;
                        }

                        cursorTeam2 += 9;
                        pickTeam += 9;
                    }
                }

                if (*charGridPtr != 0 && *takenPtr == -1) {
                    status[0] = 0x888F;
                }

                if (mode != 1 || r != *(s32 *)&lbl_2_bss_F410[0x24]) {
                    counter++;
                }
                if (counter == 0x1a) {
                    counter = 6;
                }

                takenPtr += 1;
                charGridPtr += 1;
            }
        }
    }

tail:
    {
        u16 state = menuControlVariables->currentState;

        if (state < 2 || state >= 4) {
            if (state == 9 || state == 0x13 || state == 4) {
            }
        }
    }
}

// .text:0x00009ACC size:0x4A4 mapped:0x80648B60
#pragma dont_inline on
void fn_2_9ACC(u16 team) {
    s32 i;
    s32 t;

    if (((u8 *)&g_d_GameSettings)[0x10] == 1) {
        u8 *src = &lbl_2_bss_E8CC[team * 0x5a0];
        u8 *dst = &inMemRoster[team * 0x5a0];
        u8 *lsrc = &lbl_2_bss_DCE8[team * 0x24];
        u8 *lineup = &lineUpInfoStruct[team * 0x24];

        for (i = 0; i < 9; i++) {
            if (lbl_2_bss_100B8[team + 0x30] != 0) {
                memcpy(dst + 0x00, src + 0x00, 0x1e);
                *(s16 *)(dst + 0x24) = *(s16 *)(src + 0x24);
                dst[0x26] = src[0x26];
                dst[0x27] = src[0x27];
                memcpy(dst + 0x28, src + 0x28, 2);
                memcpy(dst + 0x2a, src + 0x2a, 2);
                dst[0x2c] = src[0x2c];
                dst[0x2d] = src[0x2d];
                dst[0x2e] = src[0x2e];
                dst[0x2f] = src[0x2f];
                dst[0x30] = src[0x30];
                dst[0x31] = src[0x31];
                dst[0x32] = src[0x32];
                dst[0x33] = src[0x33];
                dst[0x34] = src[0x34];
                memcpy(dst + 0x35, src + 0x35, 2);
                *(u32 *)(dst + 0x20) = *(u32 *)(src + 0x20);
                memcpy(dst + 0x37, src + 0x37, 4);
                memcpy(dst + 0x3b, src + 0x3b, 0x36);
                dst[0x71] = src[0x71];
                *(u16 *)(dst + 0x74) = *(u16 *)(src + 0x74);
                *(u16 *)(dst + 0x76) = *(u16 *)(src + 0x76);
                *(u16 *)(dst + 0x78) = *(u16 *)(src + 0x78);
                *(u16 *)(dst + 0x7a) = *(u16 *)(src + 0x7a);
                *(u16 *)(dst + 0x7c) = *(u16 *)(src + 0x7c);
                *(u16 *)(dst + 0x7e) = *(u16 *)(src + 0x7e);
                *(u16 *)(dst + 0x80) = *(u16 *)(src + 0x80);
                *(u16 *)(dst + 0x82) = *(u16 *)(src + 0x82);
                *(u16 *)(dst + 0x84) = *(u16 *)(src + 0x84);
                *(u16 *)(dst + 0x86) = *(u16 *)(src + 0x86);
                *(u16 *)(dst + 0x88) = *(u16 *)(src + 0x88);
                *(u16 *)(dst + 0x8a) = *(u16 *)(src + 0x8a);
                *(u16 *)(dst + 0x8c) = *(u16 *)(src + 0x8c);
                *(u16 *)(dst + 0x8e) = *(u16 *)(src + 0x8e);
                *(u16 *)(dst + 0x90) = *(u16 *)(src + 0x90);
                *(u16 *)(dst + 0x92) = *(u16 *)(src + 0x92);
                *(u16 *)(dst + 0x94) = *(u16 *)(src + 0x94);
                *(u16 *)(dst + 0x96) = *(u16 *)(src + 0x96);
                *(u16 *)(dst + 0x98) = *(u16 *)(src + 0x98);
                lineup[0] = lsrc[0];
                lineup[1] = lsrc[1];
                *(u16 *)(dst + 0x9a) = *(u16 *)(src + 0x9a);
                *(u16 *)(dst + 0x9c) = *(u16 *)(src + 0x9c);
                lineup[2] = lsrc[2];
                *(s16 *)(dst + 0x24) = Static_Stats_Tables.captainSelectedID[team];
                lineup[3] = lsrc[3];
            }
            dst += 0xa0;
            src += 0xa0;
            lineup += 4;
            lsrc += 4;
        }
        return;
    }

    for (t = 0; t < 2; t++) {
        u8 *src = &lbl_2_bss_E8CC[t * 0x5a0];
        u8 *dst = &inMemRoster[t * 0x5a0];
        u8 *lsrc = &lbl_2_bss_DCE8[t * 0x24];
        u8 *lineup = &lineUpInfoStruct[t * 0x24];

        for (i = 0; i < 9; i++) {
            if (lbl_2_bss_100B8[t + 0x30] != 0) {
                memcpy(dst + 0x00, src + 0x00, 0x1e);
                *(s16 *)(dst + 0x24) = *(s16 *)(src + 0x24);
                dst[0x26] = src[0x26];
                dst[0x27] = src[0x27];
                memcpy(dst + 0x28, src + 0x28, 2);
                memcpy(dst + 0x2a, src + 0x2a, 2);
                dst[0x2c] = src[0x2c];
                dst[0x2d] = src[0x2d];
                dst[0x2e] = src[0x2e];
                dst[0x2f] = src[0x2f];
                dst[0x30] = src[0x30];
                dst[0x31] = src[0x31];
                dst[0x32] = src[0x32];
                dst[0x33] = src[0x33];
                dst[0x34] = src[0x34];
                memcpy(dst + 0x35, src + 0x35, 2);
                *(u32 *)(dst + 0x20) = *(u32 *)(src + 0x20);
                memcpy(dst + 0x37, src + 0x37, 4);
                memcpy(dst + 0x3b, src + 0x3b, 0x36);
                dst[0x71] = src[0x71];
                *(u16 *)(dst + 0x74) = *(u16 *)(src + 0x74);
                *(u16 *)(dst + 0x76) = *(u16 *)(src + 0x76);
                *(u16 *)(dst + 0x78) = *(u16 *)(src + 0x78);
                *(u16 *)(dst + 0x7a) = *(u16 *)(src + 0x7a);
                *(u16 *)(dst + 0x7c) = *(u16 *)(src + 0x7c);
                *(u16 *)(dst + 0x7e) = *(u16 *)(src + 0x7e);
                *(u16 *)(dst + 0x80) = *(u16 *)(src + 0x80);
                *(u16 *)(dst + 0x82) = *(u16 *)(src + 0x82);
                *(u16 *)(dst + 0x84) = *(u16 *)(src + 0x84);
                *(u16 *)(dst + 0x86) = *(u16 *)(src + 0x86);
                *(u16 *)(dst + 0x88) = *(u16 *)(src + 0x88);
                *(u16 *)(dst + 0x8a) = *(u16 *)(src + 0x8a);
                *(u16 *)(dst + 0x8c) = *(u16 *)(src + 0x8c);
                *(u16 *)(dst + 0x8e) = *(u16 *)(src + 0x8e);
                *(u16 *)(dst + 0x90) = *(u16 *)(src + 0x90);
                *(u16 *)(dst + 0x92) = *(u16 *)(src + 0x92);
                *(u16 *)(dst + 0x94) = *(u16 *)(src + 0x94);
                *(u16 *)(dst + 0x96) = *(u16 *)(src + 0x96);
                *(u16 *)(dst + 0x98) = *(u16 *)(src + 0x98);
                lineup[0] = lsrc[0];
                lineup[1] = lsrc[1];
                *(u16 *)(dst + 0x9a) = *(u16 *)(src + 0x9a);
                *(u16 *)(dst + 0x9c) = *(u16 *)(src + 0x9c);
                lineup[2] = lsrc[2];
                *(s16 *)(dst + 0x24) = Static_Stats_Tables.captainSelectedID[t];
                lineup[3] = lsrc[3];
            }
            dst += 0xa0;
            src += 0xa0;
            lineup += 4;
            lsrc += 4;
        }
    }
}
#pragma dont_inline reset

// .text:0x00009F70 size:0xD0 mapped:0x80649004
s32 fn_2_9F70(s8 port) {
    s8 otherPort = port ^ 1;
    s32 result = port;
    s8 portSlot = (s8)lbl_2_bss_F468[0x2F + port];
    u8 otherPortSlotRaw = lbl_2_bss_F468[0x2F + otherPort];
    s32 state = *(s32 *)(lbl_2_bss_F468 + portSlot * 4 + 0x10);
    u8 *rec;
    u8 *walk;
    s32 i;

    if (state == 2) {
        goto case_eq2;
    }
    if (state >= 2) {
        goto ge2;
    }
    if (state >= 1) {
        goto case_eq1;
    }
    goto after_switch;

ge2:
    if (state >= 4) {
        goto after_switch;
    }
    goto case_eq3;

case_eq1:
    result = 2;
    goto after_switch;

case_eq2:
    result = 1;
    goto after_switch;

case_eq3:
    result = 1;

after_switch:
    rec = &inMemRoster[(s8)otherPortSlotRaw * 0x5A0];
restart:
    for (i = 0, walk = rec; i < 9; i++, walk += 0xA0) {
        u8 masked = (u8) * (s16 *)&walk[0x24];
        s32 k;

        for (k = 0; k < 9; k++) {
            if (masked != 0) {
                continue;
            }
            if (result == 1 || result == 2) {
                return 3;
            }
            result = 2;
            goto restart;
        }
    }
    return result;
}

// .text:0x0000A040 size:0x160 mapped:0x806490D4
void fn_2_A040(s32 row, s32 slot, u8 y, u8 x) {
    s32 i, j;
    s16 target;
    s16 *pair = variantPairs[row];

    if (pair[slot] == -1 || slot >= 4) {
        goto fallback;
    }

    slot++;
    if (slot == 5 || pair[slot] == -1) {
        slot = 0;
    }

    for (i = 0; i < 2; i++) {
        target = pair[slot];
        for (j = 0; j < 9; j++) {
            if ((s8)((u8 *)&cursorPositions)[i * 9 + j + 2] == target) {
                return;
            }
        }
    }

    ((u8 *)&cursorPositions)[y * 9 + x + 2] = target;
    return;

fallback:
    ((u8 *)&cursorPositions)[y * 9 + x + 2] = pair[0];
}

// .text:0x0000A1A0 size:0xE8 mapped:0x80649234
void fn_2_A1A0(u8 arg0, u8 arg1) {
    u8 flag7 = ((u8 *)&Static_Stats_Tables)[0x4757];
    u8 flag6 = g_d_GameSettings.p2_CPU_match_code;
    u8 flag5 = lbl_2_bss_100B8[0x2E];
    s32 idx = arg1 * 9;
    u8 *base8 = &((u8 *)&cursorPositions)[idx];
    s32 a = arg0;
    u8 *ptr10;
    s32 j;

restart:
    while (flag7 != 0) {
    }

    ptr10 = (u8 *)&cursorPositions;
    for (j = 0; j < a; j++) {
        s32 off = j + 2;
        s32 val;

        if (flag6 == 0 && flag5 != 0) {
            val = (s8)ptr10[2];
        } else {
            val = (s8)base8[off];
        }
        if (val == 0) {
            goto restart;
        }

        if (flag6 == 0 && flag5 != 0) {
            val = (s8)ptr10[0xB];
        } else {
            val = (s8)base8[off];
        }
        if (val == 0) {
            goto restart;
        }
        ptr10++;
    }

    ((u8 *)&cursorPositions)[idx + a + 2] = 0;
}

// .text:0x0000A288 size:0x284 mapped:0x8064931C
void fn_2_A288(void) {
    s32 i;
    s32 m;
    u8 found;
    u8 count;
    u8 c;
    u8 x;
    s32 target;

    count = 0;

    for (i = 0; i < 12; i++) {
        c = captainIDOrderedOnCapSS[i];
        if (c == *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0]) {
            ((u8 *)&Static_Stats_Tables)[0x470B] = i;
            found = i;
        } else if (c == *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E4]) {
            ((u8 *)&Static_Stats_Tables)[0x470C] = i;
        }
    }

    target = *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E4];

    for (m = 0; m < 2; m++) {
        x = ((u8 *)&Static_Stats_Tables)[found * 0x48 + 0x4393 + m * 0x12 + 0];
        if (x == target && x != 0xFF) {
            lbl_2_bss_3E0[m] = -1;
        }
        x = ((u8 *)&Static_Stats_Tables)[found * 0x48 + 0x4393 + m * 0x12 + 1];
        if (x == target && x != 0xFF) {
            lbl_2_bss_3E0[m] = -1;
        }
        x = ((u8 *)&Static_Stats_Tables)[found * 0x48 + 0x4393 + m * 0x12 + 2];
        if (x == target && x != 0xFF) {
            lbl_2_bss_3E0[m] = -1;
        }
        x = ((u8 *)&Static_Stats_Tables)[found * 0x48 + 0x4393 + m * 0x12 + 3];
        if (x == target && x != 0xFF) {
            lbl_2_bss_3E0[m] = -1;
        }
        x = ((u8 *)&Static_Stats_Tables)[found * 0x48 + 0x4393 + m * 0x12 + 4];
        if (x == target && x != 0xFF) {
            lbl_2_bss_3E0[m] = -1;
        }
        x = ((u8 *)&Static_Stats_Tables)[found * 0x48 + 0x4393 + m * 0x12 + 5];
        if (x == target && x != 0xFF) {
            lbl_2_bss_3E0[m] = -1;
        }
        x = ((u8 *)&Static_Stats_Tables)[found * 0x48 + 0x4393 + m * 0x12 + 6];
        if (x == target && x != 0xFF) {
            lbl_2_bss_3E0[m] = -1;
        }
        x = ((u8 *)&Static_Stats_Tables)[found * 0x48 + 0x4393 + m * 0x12 + 7];
        if (x == target && x != 0xFF) {
            lbl_2_bss_3E0[m] = -1;
        }
        if ((s8)lbl_2_bss_3E0[m] == -1) {
            lbl_2_bss_3E0[m] = 0;
        } else {
            lbl_2_bss_3E0[m] = 1;
        }
    }

    if ((s8)lbl_2_bss_3E0[1] == 0) {
        count++;
    }
    if ((s8)lbl_2_bss_3E0[2] == 0) {
        count++;
    }
    if (count == 2) {
        lbl_2_bss_3E0[0] = -1;
    }
}

// .text:0x0000A50C size:0x120 mapped:0x806495A0
s32 fn_2_A50C(void) {
    s32 i;
    s32 j;
    s8 val;
    u8 *inner;

    for (i = 0; i < 9; i++) {
        inner = (u8 *)&cursorPositions;

        val = (s8)((u8 *)&cursorPositions)[i + 2];
        for (j = 0; j < 9; inner++, j++) {
            if (val == (s8)inner[0xB]) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x0000A62C size:0xB4 mapped:0x806496C0
s32 fn_2_A62C(void) {
    s32 i;
    s32 j;
    s8 val;
    u8 *inner;

    for (i = 0; i < 9; i++) {
        inner = (u8 *)&cursorPositions;

        val = (s8)((u8 *)&cursorPositions)[i + 2];
        for (j = 0; j < 9; inner++, j++) {
            s8 other = (s8)inner[0xB];
            if (val == other && val != 0xFF) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x0000A6E0 size:0x4E0 mapped:0x80649774
void fn_2_A6E0(void) {
    s32 i;
    s32 j;
    s32 t;
    s8 c;
    u8 found;
    u8 count;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) return;

    if (lbl_2_bss_100B8[0x2e] != 0 && ((u8 *)&g_d_GameSettings)[0x10] == 0) {
        found = 0;
        for (i = 0; i < 9; i++) {
            c = (s8)((u8 *)&cursorPositions)[i + 2];
            if (c == (s8)((u8 *)&cursorPositions)[0xB]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0xC]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0xD]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0xE]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0xF]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0x10]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0x11]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0x12]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0x13]) { found = 1; break; }
        }
        lbl_2_bss_3E0[1] = !found;

        found = 0;
        for (i = 0; i < 9; i++) {
            c = (s8)((u8 *)&cursorPositions)[i + 2];
            if (c == (s8)((u8 *)&cursorPositions)[0xB]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0xC]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0xD]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0xE]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0xF]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0x10]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0x11]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0x12]) { found = 1; break; }
            if (c == (s8)((u8 *)&cursorPositions)[0x13]) { found = 1; break; }
        }
        lbl_2_bss_3E0[2] = !found;

        if (lbl_2_bss_3E0[1] != 0) return;
        if (lbl_2_bss_3E0[2] != 0) return;
        lbl_2_bss_3E0[0] = 0xff;
        return;
    }

    for (t = 0; t < 2; t++) {
        found = 0;
        for (j = 0; j < 9; j++) {
            c = (s8)((u8 *)&cursorPositions)[j + 2];
            for (i = 0; i < 9; i++) {
                if (c == (s8)((u8 *)&cursorPositions)[i + 0xB] && c != (s8)0xFF) {
                    found = 1;
                    break;
                }
            }
            if (found) break;
        }
        lbl_2_bss_3E0[t] = !found;

        found = 0;
        for (j = 0; j < 9; j++) {
            c = (s8)((u8 *)&cursorPositions)[j + 2];
            for (i = 0; i < 9; i++) {
                if (c == (s8)((u8 *)&cursorPositions)[i + 0xB] && c != (s8)0xFF) {
                    found = 1;
                    break;
                }
            }
            if (found) break;
        }
        lbl_2_bss_3E0[t + 2] = !found;
    }

    count = ((s8)lbl_2_bss_3E0[0] == 0);
    if ((s8)lbl_2_bss_3E0[1] == 0) count++;
    if ((s8)lbl_2_bss_3E0[2] == 0) count++;
    if ((s8)lbl_2_bss_3E0[3] == 0) count++;
    if (count == 4) lbl_2_bss_3E0[0] = 0xff;
}

// .text:0x0000ABC0 size:0x328 mapped:0x80649C54
#pragma dont_inline on
void fn_2_ABC0(s32 port) {
    u8 order[54];
    u8 vals[54];
    s32 i;
    s32 j;
    u8 t;
    u8 t2;
    s32 base;
    u8 *src;

    base = ((s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0])[(u8)port];
    src = &((u8 *)&Static_Stats_Tables)[(base / 9) * 0x5A0 + (base % 9) * 0xA0];

    for (i = 0; i < 54; i++) {
        order[i] = i;
        vals[i] = src[i + 0x3B];
    }

    for (i = 0; i < 54; i++) {
        for (j = i + 1; j < 54; j++) {
            if (vals[i] < vals[j]) {
                t = vals[i];
                t2 = order[i];
                vals[i] = vals[j];
                order[i] = order[j];
                vals[j] = t;
                order[j] = t2;
            }
        }
    }

    for (i = 0; i < 54; i++) {
        ((u8 *)&Static_Stats_Tables)[(u8)port * 0x36 + 0x478D + i] = order[i];
    }
}
#pragma dont_inline reset

// .text:0x0000AEE8 size:0x43C mapped:0x80649F7C
void fn_2_AEE8(void) {
    u8 scratch[54];
    u8 order[2][54];
    s32 team;
    s32 i;
    s32 j;
    s32 base;
    u8 *src;
    u8 t;
    u8 t2;

    for (team = 0; team < 2; team++) {
        for (i = 0; i < 54; i++) {
            order[team][i] = i;
        }
    }

    for (team = 0; team < 2; team++) {
        base = ((s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0])[team];
        src = &((u8 *)&Static_Stats_Tables)[(base / 9) * 0x5A0 + (base % 9) * 0xA0];

        for (i = 0; i < 54; i++) {
            scratch[i] = src[i + 0x3B];
        }

        for (i = 0; i < 54; i++) {
            for (j = i + 1; j < 54; j++) {
                if (scratch[i] < scratch[j]) {
                    t = scratch[i];
                    t2 = order[team][i];
                    scratch[i] = scratch[j];
                    order[team][i] = order[team][j];
                    scratch[j] = t;
                    order[team][j] = t2;
                }
            }
        }
    }

    for (team = 0; team < 2; team++) {
        for (i = 0; i < 54; i++) {
            ((u8 *)&Static_Stats_Tables)[0x478D + team * 0x36 + i] = order[team][i];
        }
    }
}

// .text:0x0000B324 size:0x1E4 mapped:0x8064A3B8
void fn_2_B324(void) {
    s32 i;
    s32 a = *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0];
    s32 b = *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46E4];

    for (i = 0; i < 9; i++) {
        lineUpInfoStruct[i * 4 + 0x24] = i;
        lineUpInfoStruct[i * 4 + 0x00] = i;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x24] = i;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x00] = i;
        lineUpInfoStruct[i * 4 + 0x25] = i;
        lineUpInfoStruct[i * 4 + 0x01] = i;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x25] = i;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x01] = i;
        lineUpInfoStruct[i * 4 + 0x26] = i;
        lineUpInfoStruct[i * 4 + 0x02] = i;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x26] = i;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x02] = i;
        lineUpInfoStruct[i * 4 + 0x27] = 1;
        lineUpInfoStruct[i * 4 + 0x03] = 1;
        *(s16 *)&inMemRoster[i * 0xA0 + 0x24] = a + i;
        *(s16 *)&inMemRoster[i * 0xA0 + 0x5C4] = b + i;
    }

    for (; i < 9; i++) {
        lineUpInfoStruct[i * 4 + 0x24] = i;
        lineUpInfoStruct[i * 4 + 0x00] = i;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x24] = i;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x00] = i;
        lineUpInfoStruct[i * 4 + 0x25] = -1;
        lineUpInfoStruct[i * 4 + 0x01] = -1;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x25] = -1;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x01] = -1;
        lineUpInfoStruct[i * 4 + 0x26] = -1;
        lineUpInfoStruct[i * 4 + 0x02] = -1;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x26] = -1;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + i * 4 + 0x02] = -1;
        lineUpInfoStruct[i * 4 + 0x27] = -1;
        lineUpInfoStruct[i * 4 + 0x03] = -1;
        *(s16 *)&inMemRoster[i * 0xA0 + 0x24] = 0;
        *(s16 *)&inMemRoster[i * 0xA0 + 0x5C4] = 0;
    }
}

// .text:0x0000B508 size:0x164 mapped:0x8064A59C
void fn_2_B508(void) {
    s32 i, j;

    for (i = 0; i < 0x36; i++) {
        for (j = 1; j < 9; j++) {
            if ((s8)((u8 *)&cursorPositions)[j + 0xb] == i) {
                ((u8 *)&Static_Stats_Tables)[i + 0x4757] = 0;
                addOrRemoveCharacterToTeam((s8)Static_Stats_Tables.playerNumberByPort[1], i, 0);
                addRemoveCharVariantRelated(1, i, 0);
            }
        }
    }

    lineUpInfoStruct[0x2A] = 1;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + 0x2A] = 1;
    ((u8 *)&cursorPositions)[0x0C] = 0x36;
    ((u8 *)&cursorPositions)[0x54] = 0;

    lineUpInfoStruct[0x2E] = 2;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + 0x2E] = 2;
    ((u8 *)&cursorPositions)[0x0D] = 0x36;
    ((u8 *)&cursorPositions)[0x55] = 0;

    lineUpInfoStruct[0x32] = 3;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + 0x32] = 3;
    ((u8 *)&cursorPositions)[0x0E] = 0x36;
    ((u8 *)&cursorPositions)[0x56] = 0;

    lineUpInfoStruct[0x36] = 4;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + 0x36] = 4;
    ((u8 *)&cursorPositions)[0x0F] = 0x36;
    ((u8 *)&cursorPositions)[0x57] = 0;

    lineUpInfoStruct[0x3A] = 5;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + 0x3A] = 5;
    ((u8 *)&cursorPositions)[0x10] = 0x36;
    ((u8 *)&cursorPositions)[0x58] = 0;

    lineUpInfoStruct[0x3E] = 6;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + 0x3E] = 6;
    ((u8 *)&cursorPositions)[0x11] = 0x36;
    ((u8 *)&cursorPositions)[0x59] = 0;

    lineUpInfoStruct[0x42] = 7;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + 0x42] = 7;
    ((u8 *)&cursorPositions)[0x12] = 0x36;
    ((u8 *)&cursorPositions)[0x5A] = 0;

    lineUpInfoStruct[0x46] = 8;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + 0x46] = 8;
    ((u8 *)&cursorPositions)[0x13] = 0x36;
    ((u8 *)&cursorPositions)[0x5B] = 0;
}

// .text:0x0000B66C size:0x2B4 mapped:0x8064A700
void fn_2_B66C(void) {
    s32 i;
    s8 result;

    fn_2_A6E0();

    if ((s8)lbl_2_bss_3E0[0] != -1) {
        s32 r;
        do {
            r = stadiumRandomizer(1, 2);
        } while ((s8)lbl_2_bss_3E0[r] == 0);
        result = (s8)r;
    } else {
        result = -1;
    }

    switch (result) {
    case -1:
        *(s32 *)&lbl_2_bss_F468[0x14] = 3;
        break;
    case 1:
        *(s32 *)&lbl_2_bss_F468[0x14] = 2;
        break;
    case 0:
        *(s32 *)&lbl_2_bss_F468[0x14] = 1;
        break;
    }

    fn_2_ABC0(1);

    for (i = 0; i < 9; i++) {
        u8 *p = &((u8 *)&cursorPositions)[i + 0xB];
        s8 id = (s8)*p;

        if (id == -1 || id == 0x36) {
            u8 waitFlag = ((u8 *)&Static_Stats_Tables)[0x4757];
            u32 n = (u32)i;
            u8 gsFlag = g_d_GameSettings.p2_CPU_match_code;
            u8 lbFlag = lbl_2_bss_100B8[0x2e];
        restart:
            while (waitFlag != 0) {
            }
            {
                u8 *q = (u8 *)&cursorPositions;
                if ((s32)n > 0) {
                    u32 k;
                    for (k = n; k != 0; k--) {
                        if (((gsFlag != 0 && lbFlag != 0) ? (s8)q[2] : (s8)q[0xB]) == 0) {
                            goto restart;
                        }
                        if (((gsFlag != 0 && lbFlag != 0) ? (s8)q[0xB] : (s8)q[9]) == 0) {
                            goto restart;
                        }
                        q++;
                    }
                }
            }
            *p = 0;
        } else {
            lineUpInfoStruct[i * 4 + 0x25] = (u8)i;
            lineUpInfoStruct[i * 4 + 0x24] = (u8)i;
            *(s16 *)&inMemRoster[1 * 0x5A0 + i * 0xA0 + 0x24] = id;
        }

        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            s8 charID = (s8)*p;
            ((u8 *)&Static_Stats_Tables)[0x4757 + charID] = 1;
            if (g_d_GameSettings.p2_CPU_match_code == 0) {
                addOrRemoveCharacterToTeam(
                    (s8)((u8 *)&Static_Stats_Tables)[0x46f8] == 0 ? 1 : 0, charID, 1);
            } else {
                addOrRemoveCharacterToTeam((s8)((u8 *)&Static_Stats_Tables)[0x46f9], charID, 1);
            }
            addRemoveCharVariantRelated(1, (u8)charID, 1);
        } else {
            s8 charID = (s8)((u8 *)&cursorPositions)[i + 2];
            addOrRemoveCharacterToTeam(0, charID, 1);
            ((u8 *)&Static_Stats_Tables)[0x4757 + charID] = 1;
            addRemoveCharVariantRelated(1, (u8)charID, 1);
        }
    }
}

// .text:0x0000B920 size:0x670 mapped:0x8064A9B4
void fn_2_B920(void) {
    u8 matchIdx0 = 0;
    u8 matchIdx1 = 0;
    s32 i;
    s32 k;
    s8 result;

    memset(&((u8 *)&Static_Stats_Tables)[0x4757], 0, 0x36);

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        for (k = 0; k < 12; k++) {
            u8 v = captainIDOrderedOnCapSS[k];
            if ((s32)v == *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46e0]) {
                ((u8 *)&Static_Stats_Tables)[0x470b] = (u8)k;
                matchIdx0 = (u8)k;
            } else if ((s32)v == *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46e4]) {
                ((u8 *)&Static_Stats_Tables)[0x470c] = (u8)k;
                matchIdx1 = (u8)k;
            }
        }
    } else {
        u8 y = starMissionCompletionTracker[0x441d];
        s8 x = (s8)starMissionCompletionTracker[0x441f];
        for (k = 0; k < 12; k++) {
            u8 v = captainIDOrderedOnCapSS[k];
            if (v == y) {
                ((u8 *)&Static_Stats_Tables)[0x470b] = (u8)k;
            } else if ((s8)v == x) {
                ((u8 *)&Static_Stats_Tables)[0x470c] = (u8)k;
            }
        }
    }

    fn_2_A288();

    if ((s8)lbl_2_bss_3E0[0] != -1) {
        s32 r;
        do {
            r = stadiumRandomizer(1, 2);
        } while ((s8)lbl_2_bss_3E0[r] == 0);
        result = (s8)r;
    } else {
        result = -1;
    }

    switch (result) {
    case -1:
        *(s32 *)&lbl_2_bss_F468[0x10] = 3;
        break;
    case 1:
        *(s32 *)&lbl_2_bss_F468[0x10] = 2;
        break;
    case 0:
        *(s32 *)&lbl_2_bss_F468[0x10] = 1;
        break;
    }

    *(s32 *)&lbl_2_bss_F468[0x14] = 3;

    {
        s32 idx;
        s32 val = *(s32 *)&lbl_2_bss_F468[0x10];
        s32 base = matchIdx0 * 0x48 + val * 0x12 + 0x4380;
        for (idx = 0; idx < 9; idx++) {
            ((u8 *)&cursorPositions)[2 + idx] = ((u8 *)&Static_Stats_Tables)[base + idx];
        }
    }

    {
        s32 idx;
        s32 val = *(s32 *)&lbl_2_bss_F468[0x14];
        s32 base = matchIdx1 * 0x48 + val * 0x12 + 0x4380;
        for (idx = 0; idx < 9; idx++) {
            ((u8 *)&cursorPositions)[0xB + idx] = ((u8 *)&Static_Stats_Tables)[base + idx];
        }
        *(s32 *)&lbl_2_bss_F468[0x14] = val;
    }

    fn_2_ABC0(0);

    ((u8 *)&Static_Stats_Tables)[0x4757 + *(s32 *)&((u8 *)&Static_Stats_Tables)[0x46e4]] = 1;

    for (i = 0; i < 9; i++) {
        u8 *p = &((u8 *)&cursorPositions)[i + 2];
        s8 id = (s8)*p;

        if (id == -1 || id == 0x36) {
            u8 waitFlag = ((u8 *)&Static_Stats_Tables)[0x4757];
            u32 n = (u32)i;
            u8 gsFlag = g_d_GameSettings.p2_CPU_match_code;
            u8 lbFlag = lbl_2_bss_100B8[0x2e];
        restart:
            while (waitFlag != 0) {
            }
            {
                u8 *q = (u8 *)&cursorPositions;
                if ((s32)n > 0) {
                    u32 kk;
                    for (kk = n; kk != 0; kk--) {
                        if (((gsFlag != 0 && lbFlag != 0) ? (s8)q[2] : (s8)q[2]) == 0) {
                            goto restart;
                        }
                        if (((gsFlag != 0 && lbFlag != 0) ? (s8)q[0xB] : (s8)q[2]) == 0) {
                            goto restart;
                        }
                        q++;
                    }
                }
            }
            *p = 0;
        } else {
            lineUpInfoStruct[i * 4 + 1] = (u8)i;
            lineUpInfoStruct[i * 4 + 0] = (u8)i;
            *(s16 *)&inMemRoster[i * 0xA0 + 0x24] = id;
        }

        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            s8 charID = (s8)*p;
            ((u8 *)&Static_Stats_Tables)[0x4757 + charID] = 1;
            addOrRemoveCharacterToTeam((s8)((u8 *)&Static_Stats_Tables)[0x46f8], charID, 1);
            addRemoveCharVariantRelated(0, (u8)charID, 1);
        } else {
            s8 charID = (s8)*p;
            addOrRemoveCharacterToTeam(0, charID, 1);
            ((u8 *)&Static_Stats_Tables)[0x4757 + charID] = 1;
            addRemoveCharVariantRelated(0, (u8)charID, 1);
        }
    }

    for (k = 0; k < 9; k++) {
        lineUpInfoStruct[k * 4 + 0x24 + 2] = (u8)k;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + 0x24 + k * 4 + 2] = (u8)k;
        if (k == 0) {
            ((u8 *)&cursorPositions)[0xB] = (u8)*(s32 *)&((u8 *)&Static_Stats_Tables)[0x46e4];
            ((u8 *)&cursorPositions)[0x53] = 1;
        } else {
            ((u8 *)&cursorPositions)[0xB + k] = 0x36;
            ((u8 *)&cursorPositions)[0x53 + k] = 0;
        }
    }
}

// .text:0x0000BF90 size:0x394 mapped:0x8064B024
#pragma dont_inline on
void challengeSetRoster(void) {
    s32 i;
    s32 j;
    s32 k;
    s8 target;
    u8 last;
    s8 v;
    s8 sel;
    u8 flag;
    u8 mode;
    u8 sub;

    memset(&((u8 *)&Static_Stats_Tables)[0x4757], 0, 0x36);

    last = -1;
    target = (s8)starMissionCompletionTracker[0x441F];
    for (i = 0; i < 12; i++) {
        if (captainIDOrderedOnCapSS[i] == target) {
            ((u8 *)&Static_Stats_Tables)[0x470C] = i;
            last = i;
        }
    }

    *(s32 *)&lbl_2_bss_F468[0x14] = 0;
    *(s32 *)&lbl_2_bss_F468[0x10] = 0;

    for (k = 0; k < 9; k++) {
        ((u8 *)&cursorPositions)[k + 0xB] = ((u8 *)&Static_Stats_Tables)[last * 0x48 + 0x4380 + k];
    }

    for (i = 0; i < 9; i++) {
        v = (s8)((u8 *)&cursorPositions)[(u8)i + 0xB];
        if (v != -1 && v != 0x36) {
            lineUpInfoStruct[(u8)i * 4 + 0x25] = (u8)i;
            lineUpInfoStruct[(u8)i * 4 + 0x24] = (u8)i;
            *(s16 *)&inMemRoster[(u8)i * 0xA0 + 0x5C4] = v;
        } else {
            flag = ((u8 *)&Static_Stats_Tables)[0x4757];
            mode = ((u8 *)&g_d_GameSettings)[0x10];
            sub = lbl_2_bss_100B8[0x2E];
        restart:
            while (flag != 0) {
            }
            for (j = 0; j < (u8)i; j++) {
                if (mode == 0 && sub != 0) {
                    sel = (s8)((u8 *)&cursorPositions)[j + 2];
                } else {
                    sel = (s8)((u8 *)&cursorPositions)[j + 0xB];
                }
                if (sel == 0) {
                    goto restart;
                }
                if (mode == 0 && sub != 0) {
                    sel = (s8)((u8 *)&cursorPositions)[j + 0xB];
                } else {
                    sel = (s8)((u8 *)&cursorPositions)[j + 0xB];
                }
                if (sel == 0) {
                    goto restart;
                }
            }
            ((u8 *)&cursorPositions)[(u8)i + 0xB] = 0;
        }

        if (((u8 *)&g_d_GameSettings)[7] != 5) {
            sel = (s8)((u8 *)&cursorPositions)[(u8)i + 0xB];
            ((u8 *)&Static_Stats_Tables)[0x4757 + sel] = 1;
            if (((u8 *)&g_d_GameSettings)[0x10] == 0) {
                if ((s8)Static_Stats_Tables.playerNumberByPort[0] == 0) {
                    addOrRemoveCharacterToTeam(1, sel, 1);
                } else {
                    addOrRemoveCharacterToTeam(0, sel, 1);
                }
            } else {
                addOrRemoveCharacterToTeam((s8)Static_Stats_Tables.playerNumberByPort[1], sel, 1);
            }
            addRemoveCharVariantRelated(1, (u8)sel, 1);
        } else {
            sel = (s8)((u8 *)&cursorPositions)[(u8)i + 2];
            addOrRemoveCharacterToTeam(0, sel, 1);
            ((u8 *)&Static_Stats_Tables)[0x4757 + sel] = 1;
            addRemoveCharVariantRelated(1, (u8)sel, 1);
        }
    }
}
#pragma dont_inline reset

// .text:0x0000C324 size:0x160 mapped:0x8064B3B8
s8 fn_2_C324(s32 id) {
    s32 found = -1;
    s32 i, j;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 5; j++) {
            if (id == variantPairs[i][j]) {
                found = i;
                goto done;
            }
        }
    }

done:
    if (found == -1) {
        return (s8)found;
    }

    {
        u8 *entry = inMemRoster;

        for (i = 0; i < 9; i++) {
            s16 charID = *(s16 *)(entry + 0x24);
            for (j = 0; j < 5; j++) {
                if (charID == variantPairs[found][j] && charID != id) {
                    return found;
                }
            }
            entry += 0xA0;
        }
    }

    return -1;
}

// .text:0x0000C484 size:0x214 mapped:0x8064B518
void fn_2_C484(s32 charId, s16 target) {
    s32 i;
    s32 rec;
    s32 k;
    s32 slot;
    s32 found;
    s8 result;
    s16 v;

    for (i = 0; i < 54; i++) {
        if (i != target) {
            continue;
        }

        ((u8 *)&Static_Stats_Tables)[0x4757 + i] = 0;
        if (((u8 *)&g_d_GameSettings)[7] == 5) {
            found = -1;
            for (rec = 0; rec < 9; rec++) {
                for (k = 0; k < 5; k++) {
                    if (i == variantPairs[rec][k]) {
                        found = rec;
                        goto searched;
                    }
                }
            }
        searched:
            if (found == -1) {
                result = found;
                goto done;
            }

            for (slot = 0; slot < 9; slot++) {
                v = *(s16 *)&inMemRoster[slot * 0xA0 + 0x24];
                for (k = 0; k < 5; k++) {
                    if (v == variantPairs[found][k] && v != i) {
                        result = found;
                        goto done;
                    }
                }
            }
            result = -1;

        done:
            if (result == -1) {
                addOrRemoveCharacterToTeam((u8)charId, i, 0);
            }
            return;
        }

        addOrRemoveCharacterToTeam((u8)charId, i, 0);
        addRemoveCharVariantRelated(charId, (u8)i, 0);
        return;
    }
}

// .text:0x0000C698 size:0x144 mapped:0x8064B72C
void fn_2_C698(s32 idx, u8 port) {
    s8 charID;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        goto challenge;
    }

    charID = (s8)((u8 *)&cursorPositions)[port * 9 + idx + 2];
    ((u8 *)&Static_Stats_Tables)[0x4757 + charID] = 1;

    if (g_d_GameSettings.p2_CPU_match_code != 0) {
        goto common_call;
    }
    if (port == 0) {
        goto common_call;
    }
    if (Static_Stats_Tables.playerNumberByPort[0] == 0) {
        addOrRemoveCharacterToTeam(1, charID, 1);
    } else {
        addOrRemoveCharacterToTeam(0, charID, 1);
    }
    goto variant_call;

common_call:
    addOrRemoveCharacterToTeam((s8)((u8 *)&Static_Stats_Tables)[0x46F8 + port], charID, 1);

variant_call:
    addRemoveCharVariantRelated(port, charID, 1);
    return;

challenge:
    charID = (s8)((u8 *)&cursorPositions)[idx + 2];
    addOrRemoveCharacterToTeam(0, charID, 1);
    ((u8 *)&Static_Stats_Tables)[0x4757 + charID] = 1;
    addRemoveCharVariantRelated(port, charID, 1);
}

// .text:0x0000C7DC size:0x284 mapped:0x8064B870
void fn_2_C7DC(s32 a, s32 b) {
    s32 pick;
    s32 j;
    s8 sel;

restart:
    if ((u8)a == 0) {
        lineUpInfoStruct[(u8)b * 0x24 + (u8)a * 4 + 1] = a;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + (u8)b * 0x24 + (u8)a * 4 + 1] = a;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + (u8)b * 0x24 + (u8)a * 4] = a;
        lineUpInfoStruct[(u8)b * 0x24 + (u8)a * 4] = a;
        lineUpInfoStruct[(u8)b * 0x24 + (u8)a * 4 + 2] = a;
        ((u8 *)&Static_Stats_Tables)[0x51F8 + (u8)b * 0x24 + (u8)a * 4 + 2] = a;
        *(s16 *)&inMemRoster[(u8)b * 0x5A0 + (u8)a * 0xA0 + 0x24] =
            ((s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0])[(u8)b];
        return;
    }

    do {
        pick = stadiumRandomizer(0, 0x35);
    } while (((u8 *)&Static_Stats_Tables)[0x4757 + characterIconsOnCSS[pick]] != 0);

    for (j = 0; j < (u8)a; j++) {
        if (*(s16 *)&inMemRoster[j * 0xA0 + 0x24] == pick) {
            goto restart;
        }
        if (*(s16 *)&inMemRoster[j * 0xA0 + 0x5C4] == pick) {
            goto restart;
        }
    }

    lineUpInfoStruct[(u8)b * 0x24 + (u8)a * 4 + 1] = a;
    lineUpInfoStruct[(u8)b * 0x24 + (u8)a * 4] = a;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + (u8)b * 0x24 + (u8)a * 4 + 1] = a;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + (u8)b * 0x24 + (u8)a * 4] = a;
    lineUpInfoStruct[(u8)b * 0x24 + (u8)a * 4 + 2] = a;
    ((u8 *)&Static_Stats_Tables)[0x51F8 + (u8)b * 0x24 + (u8)a * 4 + 2] = a;
    *(s16 *)&inMemRoster[(u8)b * 0x5A0 + (u8)a * 0xA0 + 0x24] = pick;

    if (((u8 *)&g_d_GameSettings)[7] != 5) {
        sel = (s8)((u8 *)&cursorPositions)[(u8)b * 9 + (u8)a + 2];
        ((u8 *)&Static_Stats_Tables)[0x4757 + sel] = 1;
        if (((u8 *)&g_d_GameSettings)[0x10] == 0 && (u8)b != 0) {
            if ((s8)Static_Stats_Tables.playerNumberByPort[0] == 0) {
                addOrRemoveCharacterToTeam(1, sel, 1);
            } else {
                addOrRemoveCharacterToTeam(0, sel, 1);
            }
        } else {
            addOrRemoveCharacterToTeam((s8)((u8 *)&Static_Stats_Tables)[0x46F8 + (u8)b], sel, 1);
        }
        addRemoveCharVariantRelated(b, (u8)sel, 1);
    } else {
        sel = (s8)((u8 *)&cursorPositions)[(u8)a + 2];
        addOrRemoveCharacterToTeam(0, sel, 1);
        ((u8 *)&Static_Stats_Tables)[0x4757 + sel] = 1;
        addRemoveCharVariantRelated(b, (u8)sel, 1);
    }
}

// .text:0x0000CA60 size:0x25C mapped:0x8064BAF4
void fn_2_CA60(s32 a, s32 b) {
    s32 k;
    s8 v;
    s8 p;
    s8 charId;
    u8 flag;
    u8 mode;
    u8 sub;

    v = (s8)((u8 *)&cursorPositions)[(u8)b * 9 + (u8)a + 2];
    if (v != -1 && v != 0x36) {
        lineUpInfoStruct[(u8)b * 0x24 + (u8)a * 4 + 1] = a;
        lineUpInfoStruct[(u8)b * 0x24 + (u8)a * 4] = a;
        *(s16 *)&inMemRoster[(u8)b * 0x5A0 + (u8)a * 0xA0 + 0x24] = v;
    } else {
        flag = ((u8 *)&Static_Stats_Tables)[0x4757];
        mode = ((u8 *)&g_d_GameSettings)[0x10];
        sub = lbl_2_bss_100B8[0x2E];
    restart:
        while (flag != 0) {
        }
        for (k = 0; k < (u8)a; k++) {
            if (mode == 0 && sub != 0) {
                p = (s8)((u8 *)&cursorPositions)[k + 2];
            } else {
                p = (s8)((u8 *)&cursorPositions)[(u8)b * 9 + k + 2];
            }
            if (p == 0) {
                goto restart;
            }
            if (mode == 0 && sub != 0) {
                p = (s8)((u8 *)&cursorPositions)[k + 0xB];
            } else {
                p = (s8)((u8 *)&cursorPositions)[(u8)b * 9 + k + 2];
            }
            if (p == 0) {
                goto restart;
            }
        }
        ((u8 *)&cursorPositions)[(u8)b * 9 + (u8)a + 2] = 0;
    }

    if (((u8 *)&g_d_GameSettings)[7] != 5) {
        charId = (s8)((u8 *)&cursorPositions)[(u8)b * 9 + (u8)a + 2];
        ((u8 *)&Static_Stats_Tables)[0x4757 + charId] = 1;
        if (((u8 *)&g_d_GameSettings)[0x10] == 0 && (u8)b != 0) {
            if ((s8)Static_Stats_Tables.playerNumberByPort[0] == 0) {
                addOrRemoveCharacterToTeam(1, charId, 1);
            } else {
                addOrRemoveCharacterToTeam(0, charId, 1);
            }
        } else {
            addOrRemoveCharacterToTeam((s8)((u8 *)&Static_Stats_Tables)[0x46F8 + (u8)b], charId, 1);
        }
        addRemoveCharVariantRelated(b, (u8)charId, 1);
    } else {
        charId = (s8)((u8 *)&cursorPositions)[(u8)a + 2];
        addOrRemoveCharacterToTeam(0, charId, 1);
        ((u8 *)&Static_Stats_Tables)[0x4757 + charId] = 1;
        addRemoveCharVariantRelated(b, (u8)charId, 1);
    }
}

// .text:0x0000CCBC size:0x24 mapped:0x8064BD50
void fn_2_CCBC(void) {
    cssLoadingScreenRelated();
    cssResetRosterStruct();
}

// .text:0x0000CCE0 size:0x164 mapped:0x8064BD74
void fn_2_CCE0(u8 port) {
    s32 count;

    if (lbl_2_bss_F468[port + 0x37] != 0) {
        return;
    }

    for (count = 0; count < 9; count++) {
        s8 v = (s8)((u8 *)&cursorPositions)[port * 9 + count + 2];
        if (v == -1 || v == 0x36) {
            break;
        }
    }

    if (count == 9) {
        lbl_2_bss_F468[port + 0x37] = 1;
        *(s32 *)&lbl_2_bss_F468[port * 4 + 8] = *(s32 *)&lbl_2_bss_F468[port * 4];
        *(s32 *)&lbl_2_bss_F468[port * 4] = 9;
        lbl_2_bss_F468[port + 0x41] = 0;
        updateCharacterSelectProcessCode(port, 0x14);
        cssLoadingRelated_1(1, -1, -1, -1, -1, 0);
    } else {
        *(s32 *)&lbl_2_bss_F468[port * 4 + 8] = *(s32 *)&lbl_2_bss_F468[port * 4];
        *(s32 *)&lbl_2_bss_F468[port * 4] = (s8)((u8 *)&cursorPositions)[port * 9 + count + 0x14];
        updateCharacterSelectProcessCode(port, 0xe);
    }
}

// .text:0x0000CE44 size:0x1168 mapped:0x8064BED8
void cssReturnToCapSelect_maybe(void) {
    return;
}

// .text:0x0000DFAC size:0xB34 mapped:0x8064D040
void characterSelectAPress(void) {
    return;
}

// .text:0x0000EAE0 size:0x154 mapped:0x8064DB74
void fn_2_EAE0(void) {
    s32 i;
    s32 flag;

    for (i = 0; i < (g_d_GameSettings.p2_CPU_match_code == 1) + 1; i++) {
        if (((u8 *)&g_MatchInfo)[i + 8] == 0) {
            continue;
        }

        if (((u8 *)&Static_Stats_Tables)[0x4757 + characterIconsOnCSS[*(s32 *)&lbl_2_bss_F410[i * 4 + 0x20]]] != 0) {
            s32 *p = (s32 *)&lbl_2_bss_F410[i * 4 + 0x20];

            do {
                *p = *p + 1;
                if (*p == 0x36) {
                    *p = 0;
                }
            } while (((u8 *)&Static_Stats_Tables)[0x4757 + characterIconsOnCSS[*p]] != 0 ||
                     *(s32 *)&lbl_2_bss_F410[0x20] == *(s32 *)&lbl_2_bss_F410[0x24]);
        }

        while (1) {
            if ((s8)((u8 *)&Static_Stats_Tables)[0x46FC + (s8)((u8 *)&Static_Stats_Tables)[0x46F8 + i]] != 0) {
                flag = ((s8)Static_Stats_Tables.playerNumberByPort[0] == 0);
            }
            fn_2_1D54((s32 *)&lbl_2_bss_F410[(i + 8) * 4], flag, 0x36);
        }
    }
}

// .text:0x0000EC34 size:0x20 mapped:0x8064DCC8
void fn_2_EC34(void) {
    if (lbl_2_bss_F468[0x56] == 0) {
        lbl_2_bss_F468[0x56] = 1;
    }
}

// .text:0x0000EC54 size:0x140 mapped:0x8064DCE8
void fn_2_EC54(s32 port) {
    s32 i;
    u8 *cursor;
    u8 *bss;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        return;
    }

    if (g_d_GameSettings.p2_CPU_match_code == 1) {
        lbl_2_bss_100B8[0x2F] = 0;
        lbl_2_bss_100B8[0x2E] = 0;
    } else {
        lbl_2_bss_100B8[port + 0x2E] = 0;
    }

    cursor = (u8 *)&cursorPositions;
    bss = lbl_2_bss_F468;

    for (i = 0; i < 2; i++) {
        s32 zero = 0;

        if (zero < 9) {
            cursor[0x26] = 0;
            cursor[0x27] = 0;
            cursor[0x28] = 0;
            cursor[0x29] = 0;
            cursor[0x2A] = 0;
            cursor[0x2B] = 0;
            cursor[0x2C] = 0;
            cursor[0x2D] = 0;
            cursor[0x2E] = 0;
        }

        if (bss[0x45] != 0) {
            bss[0x45] = 0;
        }

        cursor += 9;
        bss += 1;
    }

    if (lbl_2_bss_F468[0x56] == 0) {
        lbl_2_bss_F468[0x56] = 1;
    }

    lbl_2_bss_F468[0x2E] = 1;
    lbl_2_bss_100B4 = 1;
    menuControlVariables->currentState = 8;
}

// .text:0x0000ED94 size:0x46C mapped:0x8064DE28
void characterSelectABDirectionInputs(void) {
    return;
}

// .text:0x0000F200 size:0x8A0 mapped:0x8064E294
void randCharBasedOnClass(s32 port) {
    u8 portU8 = (u8)port;
    s32 teamBase = ((s32 *)&((u8 *)&Static_Stats_Tables)[0x46e0])[portU8];
    u8 classBuf[9];
    u8 candBuf[8];
    u8 *cursor = &((u8 *)&cursorPositions)[portU8 * 9];
    s32 count0 = 0, count1 = 0, count2 = 0, count3 = 0;
    s32 full0 = 0, full1 = 0, full2 = 0, full3 = 0;
    s32 i;
    s16 pick;

    memset(classBuf, -1, 9);

    for (i = 0; i < 9; i++) {
        s8 v = (s8)cursor[i + 2];
        u8 cls;
        if (v == -1 || v == 0x36) continue;
        cls = ((u8 *)&Static_Stats_Tables)[(v / 9) * 0x5A0 + (v % 9) * 0xA0 + 0x31];
        classBuf[i] = cls;
        switch (cls) {
        case 2:
            count2++;
            if ((u8)count2 >= 2) full2 = 1;
            break;
        case 0:
            count0++;
            if ((u8)count0 >= 2) full0 = 1;
            break;
        case 1:
            count1++;
            if ((u8)count1 >= 2) full1 = 1;
            break;
        case 3:
            count3++;
            if ((u8)count3 >= 2) full3 = 1;
            break;
        default:
            break;
        }
    }

    for (i = 0; i < 9; i++) {
        s8 v = (s8)cursor[i + 2];
        s32 j, count;

        if (v != -1 && v != 0x36) continue;

        memset(candBuf, -1, 8);

        if (!full0) {
            count = 0;
            for (j = 0; j < 0x20; j++) {
                s8 raw = mainCharArray[j];
                s16 id = (s16)raw;
                u8 cls = ((u8 *)&Static_Stats_Tables)[(id / 9) * 0x5A0 + (id % 9) * 0xA0 + 0x31];
                if (cls == 0 && Static_Stats_Tables.charOnCharacterGridSelected[id] == 0) {
                    candBuf[count] = (u8)raw;
                    count++;
                }
            }
            if ((s8)candBuf[0] == -1) goto fallback;
            pick = (s8)candBuf[randRange_FUN_80042bf0(0, count)];
            count0++;
            if ((u8)count0 >= 2) full0 = 1;
            goto tail;
        } else if (!full1) {
            count = 0;
            for (j = 0; j < 0x20; j++) {
                s8 raw = mainCharArray[j];
                s16 id = (s16)raw;
                u8 cls = ((u8 *)&Static_Stats_Tables)[(id / 9) * 0x5A0 + (id % 9) * 0xA0 + 0x31];
                if (cls == 1 && Static_Stats_Tables.charOnCharacterGridSelected[id] == 0) {
                    candBuf[count] = (u8)raw;
                    count++;
                }
            }
            if ((s8)candBuf[0] == -1) goto fallback;
            pick = (s8)candBuf[randRange_FUN_80042bf0(0, count)];
            count1++;
            if ((u8)count1 >= 2) full1 = 1;
            goto tail;
        } else if (!full2) {
            count = 0;
            for (j = 0; j < 0x20; j++) {
                s8 raw = mainCharArray[j];
                s16 id = (s16)raw;
                u8 cls = ((u8 *)&Static_Stats_Tables)[(id / 9) * 0x5A0 + (id % 9) * 0xA0 + 0x31];
                if (cls == 2 && Static_Stats_Tables.charOnCharacterGridSelected[id] == 0) {
                    candBuf[count] = (u8)raw;
                    count++;
                }
            }
            if ((s8)candBuf[0] == -1) goto fallback;
            pick = (s8)candBuf[randRange_FUN_80042bf0(0, count)];
            count2++;
            if ((u8)count2 >= 2) full2 = 1;
            goto tail;
        } else if (!full3) {
            count = 0;
            for (j = 0; j < 0x20; j++) {
                s8 raw = mainCharArray[j];
                s16 id = (s16)raw;
                u8 cls = ((u8 *)&Static_Stats_Tables)[(id / 9) * 0x5A0 + (id % 9) * 0xA0 + 0x31];
                if (cls == 3 && Static_Stats_Tables.charOnCharacterGridSelected[id] == 0) {
                    candBuf[count] = (u8)raw;
                    count++;
                }
            }
            if ((s8)candBuf[0] == -1) goto fallback;
            pick = (s8)candBuf[randRange_FUN_80042bf0(0, count)];
            count3++;
            if ((u8)count3 >= 2) full3 = 1;
            goto tail;
        } else {
            goto fallback;
        }

    fallback:
        do {
            pick = (s16)randRange_FUN_80042bf0(0, 0x35);
        } while (Static_Stats_Tables.charOnCharacterGridSelected[pick] != 0);

    tail:
        addRemoveCharVariantRelated(port, (u8)pick, 1);

        {
            s32 row, col;
            for (row = 0; row < 9; row++) {
                for (col = 0; col < 5; col++) {
                    if ((s32)pick == variantPairs[row][col]) goto matched;
                }
            }
            goto commonCode;
        matched:
            ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[row][1]] = 1;
            ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[row][2]] = 1;
            ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[row][3]] = 1;
            ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[row][4]] = 1;
            pick = variantPairs[row][0];
        }

    commonCode:
        if (((u8 *)&g_d_GameSettings)[0x10] == 0 && portU8 != 0) {
            if ((s8)Static_Stats_Tables.playerNumberByPort[0] == 0) {
                addOrRemoveCharacterToTeam(1, pick, 1);
            } else {
                addOrRemoveCharacterToTeam(1, pick, 1);
            }
        } else {
            addOrRemoveCharacterToTeam((s8)((u8 *)&Static_Stats_Tables)[0x46F8 + portU8], pick, 1);
        }

        cursor[i + 2] = (u8)pick;
        Static_Stats_Tables.charOnCharacterGridSelected[pick] = 1;
        cursor[i + 0x26] =
            ((u8 *)&Static_Stats_Tables)[teamBase + (pick / 9) * 0x5A0 + (pick % 9) * 0xA0 + 0x3B];
    }
}

// .text:0x0000FAA0 size:0x214 mapped:0x8064EB34
void randCharacter1(s32 port) {
    s32 i;
    s16 pick;
    s32 rec;
    s32 k;
    s8 v;

    for (i = 0; i < 9; i++) {
        v = (s8)((u8 *)&cursorPositions)[(u8)port * 9 + i + 2];
        if (v == -1 || v == 0x36) {
            do {
                pick = (s16)randRange_FUN_80042bf0(0, 0x35);
            } while (((u8 *)&Static_Stats_Tables)[0x4757 + pick] != 0);

            addRemoveCharVariantRelated(port, (u8)pick, 1);

            for (rec = 0; rec < 9; rec++) {
                for (k = 0; k < 5; k++) {
                    if (pick == variantPairs[rec][k]) {
                        ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[rec][1]] = 1;
                        ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[rec][2]] = 1;
                        ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[rec][3]] = 1;
                        ((u8 *)&Static_Stats_Tables)[0x4757 + variantPairs[rec][4]] = 1;
                        pick = variantPairs[rec][0];
                        goto matched;
                    }
                }
            }
        matched:
            if (((u8 *)&g_d_GameSettings)[0x10] == 0 && (u8)port != 0) {
                if ((s8)Static_Stats_Tables.playerNumberByPort[0] == 0) {
                    addOrRemoveCharacterToTeam(1, pick, 1);
                } else {
                    addOrRemoveCharacterToTeam(1, pick, 1);
                }
            } else {
                addOrRemoveCharacterToTeam((s8)((u8 *)&Static_Stats_Tables)[0x46F8 + (u8)port], pick, 1);
            }

            ((u8 *)&cursorPositions)[(u8)port * 9 + i + 2] = (u8)pick;
            ((u8 *)&Static_Stats_Tables)[0x4757 + pick] = 1;
            ((u8 *)&cursorPositions)[(u8)port * 9 + i + 0x26] =
                ((u8 *)&Static_Stats_Tables)[((s32 *)&((u8 *)&Static_Stats_Tables)[0x46E0])[(u8)port] +
                                    (pick / 9) * 0x5A0 + (pick % 9) * 0xA0 + 0x3B];
        }
    }
}

// .text:0x0000FCB4 size:0x614 mapped:0x8064ED48
void randCharAlgo2(s32 port) {
    u8 buf[0x36];
    s32 teamBase = ((s32 *)&((u8 *)&Static_Stats_Tables)[0x46e0])[(u8)port];
    s32 i;
    s32 count;
    s32 player;

    memset(buf, -1, 0x36);

    for (i = 0; i < 0x36; i++) {
        u8 orderByte = ((u8 *)&Static_Stats_Tables)[(u8)port * 0x36 + 0x478D + i];
        s32 j;

        for (j = 0; j < 9; j++) {
            if ((s32)orderByte == variantPairs[j][1]) {
                ((u8 *)&Static_Stats_Tables)[0x4757 + orderByte] = 1;
            }
            if ((s32)orderByte == variantPairs[j][2]) {
                ((u8 *)&Static_Stats_Tables)[0x4757 + orderByte] = 1;
            }
            if ((s32)orderByte == variantPairs[j][3]) {
                ((u8 *)&Static_Stats_Tables)[0x4757 + orderByte] = 1;
            }
            if ((s32)orderByte == variantPairs[j][4]) {
                ((u8 *)&Static_Stats_Tables)[0x4757 + orderByte] = 1;
            }
        }

        if (((u8 *)&Static_Stats_Tables)[0x4757 + orderByte] == 0) {
            buf[i] = orderByte;
        }
    }

    for (i = 0; i < 0x36; i++) {
        s32 k;
        for (k = i; k < 0x36; k++) {
            if (buf[i] == (u8)-1 && buf[k] != (u8)-1) {
                u8 tmp = buf[k];
                buf[k] = buf[i];
                buf[i] = tmp;
            }
        }
    }

    count = 0;
    for (player = 0; player < 9; player++) {
        s8 v = (s8)((u8 *)&cursorPositions)[port * 9 + player + 2];
        if (v == -1 || v == 0x36) {
            count++;
        }
    }

    for (player = 0; player < 9; player++) {
        s32 slot = port * 9 + player;
        s8 pickedSlot = (s8)((u8 *)&cursorPositions)[slot + 2];
        s8 picked;
        u8 max;

        if (pickedSlot != -1 && pickedSlot != 0x36) {
            continue;
        }

        max = (u8)(count + 11);

    retry:
        {
            s32 idx = stadiumRandomizer(0, max);
            picked = (s8)buf[idx];
            if (picked == -1) {
                goto retry;
            }
            if (((u8 *)&Static_Stats_Tables)[0x4757 + picked] == 1) {
                goto retry;
            }
            buf[idx] = (u8)-1;
            ((u8 *)&Static_Stats_Tables)[0x4757 + picked] = 1;
        }

        if (g_d_GameSettings.p2_CPU_match_code == 0 && port != 0) {
            if ((s8)Static_Stats_Tables.playerNumberByPort[0] == 0) {
                addOrRemoveCharacterToTeam(1, picked, 1);
            } else {
                addOrRemoveCharacterToTeam(1, picked, 1);
            }
        } else {
            addOrRemoveCharacterToTeam((s8)Static_Stats_Tables.playerNumberByPort[port], picked, 1);
        }

        addRemoveCharVariantRelated(port, picked, 1);

        {
            s32 row;
            s32 col;

            for (row = 0; row < 9; row++) {
                for (col = 0; col < 5; col++) {
                    if ((s32)picked == variantPairs[row][col]) {
                        goto found_row;
                    }
                }
            }
            goto post_sweep;

        found_row:
            picked = (s8)variantPairs[row][0];

            for (col = 0; col < 5; col++) {
                s16 val = variantPairs[row][col];
                if (val != -1) {
                    s32 b;
                    for (b = 0; b < 0x36; b++) {
                        if ((s8)buf[b] == (s8)val) {
                            buf[b] = (u8)-1;
                        }
                    }
                }
            }
        }

    post_sweep:
        ((u8 *)&cursorPositions)[slot + 2] = (u8)picked;
        count--;
        ((u8 *)&cursorPositions)[slot + 0x26] = ((u8 *)&Static_Stats_Tables)[teamBase + (picked / 9) * 0x5A0 + (picked % 9) * 0xA0 + 0x3B];
    }

    {
        s32 row;
        s32 col;
        for (row = 0; row < 9; row++) {
            for (col = 0; col < 5; col++) {
                s16 v = variantPairs[row][col];
                ((u8 *)&Static_Stats_Tables)[0x4757 + v] = 0;
            }
        }
    }

    {
        u8 other = (u8)port ^ 1;
        for (player = 0; player < 9; player++) {
            addRemoveCharVariantRelated(other, ((u8 *)&cursorPositions)[other * 9 + player + 2], 1);
            addRemoveCharVariantRelated(port, ((u8 *)&cursorPositions)[port * 9 + player + 2], 1);
        }
    }

    if (((u8 *)&g_d_GameSettings)[0x1f] == 0) {
        ((u8 *)&Static_Stats_Tables)[0x478c] = 1;
        ((u8 *)&Static_Stats_Tables)[0x478b] = 1;
        ((u8 *)&Static_Stats_Tables)[0x4772] = 1;
    }
}

// .text:0x000102C8 size:0x234 mapped:0x8064F35C
void starHitSetting_Unused_maybe(void) {
    return;
}

// .text:0x000104FC size:0xBB4 mapped:0x8064F590
void characterSelectControls(void) {
    return;
}

