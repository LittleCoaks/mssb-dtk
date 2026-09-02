#include "menus/text_0323C.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "menus/yd_step.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

void updateCharacterSelectProcessCode(int arg0, int arg1);
void sndFXRelated(int id);
void challenge_setTransitionScreenCharacterPortrait(int arg0, int arg1);
void fn_2_16A74(int idx, int flag);
s32 randRange_FUN_80042bf0(s32 min, s32 max);
void addOrRemoveCharacterToTeam(s32 add, s32 charID, s32 flag);
void addRemoveCharVariantRelated(s32 port, s32 charID, s32 flag);
void cssLoadingRelated_1(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

extern s16 variantPairs[][5];
extern u8 lbl_2_bss_F410[0x58];
extern u8 lbl_803C5EA4[0x3C];
extern u8 lbl_2_bss_F468[0xC4C];
extern u8 lbl_2_bss_100B4;
extern u8 lbl_2_bss_100B8[0x54];
extern u8 lbl_2_data_3CE0[0x8];
extern u8 Static_Stats_Tables[0x5240];
extern u8 starMissionCompletionTracker[0x4508];
extern u8 lbl_8037169C[0x1C];
extern u8 cursorPositions[0x5C];
extern u8 inMemRoster[0xB40];
extern u8 lineUpInfoStruct[0x48];
extern u8 lbl_8010902C[0x18];
extern u8 characterStaticIndexes[0x144];
extern u8 unlockableCharacter_noDupeNoGapCharID[0x8];
extern menuControlStruct *menuControlVariables;

// .text:0x0000323C size:0x180 mapped:0x806422D0
void cssTransitionToNewScreen_maybe(void) {
    return;
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
                Static_Stats_Tables[0x4757 + rec] = flag;
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
void fn_2_4970(void) {
    return;
}

// .text:0x00005184 size:0x148 mapped:0x80644218
void fn_2_5184(void) {
    return;
}

// .text:0x000052CC size:0x178 mapped:0x80644360
void fn_2_52CC(void) {
    return;
}

// .text:0x00005444 size:0x3A4 mapped:0x806444D8
void teamReady1(void) {
    return;
}

// .text:0x000057E8 size:0x8 mapped:0x8064487C
s32 fn_2_57E8(s32 arg0, s32 arg1) {
    return (s8)arg1;
}

// .text:0x000057F0 size:0x790 mapped:0x80644884
void fn_2_57F0(void) {
    return;
}

// .text:0x00005F80 size:0x118 mapped:0x80645014
void fn_2_5F80(void) {
    u8 *lineUp = lineUpInfoStruct;
    u8 *cursor = cursorPositions;
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
        return ((s32 *)&Static_Stats_Tables[0x46E0])[port];
    }
    if (port != 0) {
        return ((s32 *)&Static_Stats_Tables[0x46E0])[port];
    }
    return ((s32 *)&Static_Stats_Tables[0x46E0])[port];
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
    return;
}

// .text:0x00006484 size:0x184 mapped:0x80645518
void cssSelectCPUDifficulty(void) {
    return;
}

// .text:0x00006608 size:0x17C mapped:0x8064569C
void characterSelectScreenControlable(void) {
    return;
}

// .text:0x00006784 size:0x100 mapped:0x80645818
void fn_2_6784(void) {
    u8 *slot = cursorPositions;
    u8 *info = lineUpInfoStruct;
    s32 i;

    for (i = 0; i < 9; i++) {
        if (i == 0) {
            *(s32 *)&Static_Stats_Tables[0x46E4] = 0;
            cursorPositions[0xB] = 0;
            cursorPositions[0x53] = 1;
            Static_Stats_Tables[0x4757] = 1;
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
            Static_Stats_Tables[0x4757 + picked] = 1;
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
    return;
}

// .text:0x00006AF4 size:0x248 mapped:0x80645B88
void fn_2_6AF4(void) {
    return;
}

// .text:0x00006D3C size:0x7C8 mapped:0x80645DD0
void cssUnloadScreen(void) {
    return;
}

// .text:0x00007504 size:0x840 mapped:0x80646598
void cssResetRosterStruct(void) {
    return;
}

// .text:0x00007D44 size:0x98 mapped:0x80646DD8
void fn_2_7D44(void) {
    if (menuControlVariables->previousScreen == 9) {
        memset(lbl_2_bss_100B8, 0, 0x54);
    }
    Static_Stats_Tables[0x4755] = 1;
    lbl_2_bss_100B8[0x2D] = 4;
    fn_2_16A74(0, 0);
    fn_2_16A74(1, 0);
    fn_2_16A74(2, 0);
    fn_2_16A74(3, 0);
}

// .text:0x00007DDC size:0x910 mapped:0x80646E70
void cssLoadingScreenRelated(void) {
    return;
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
    return;
}

// .text:0x0000893C size:0x4 mapped:0x806479D0
void fn_2_893C(void) {
    return;
}

// .text:0x00008940 size:0x3B8 mapped:0x806479D4
void copyInfoToInMemRoster(void) {
    return;
}

// .text:0x00008CF8 size:0x8E0 mapped:0x80647D8C
void fn_2_8CF8(void) {
    return;
}

// .text:0x000095D8 size:0x4F4 mapped:0x8064866C
void fn_2_95D8(void) {
    return;
}

// .text:0x00009ACC size:0x4A4 mapped:0x80648B60
void fn_2_9ACC(void) {
    return;
}

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
            if ((s8)cursorPositions[i * 9 + j + 2] == target) {
                return;
            }
        }
    }

    cursorPositions[y * 9 + x + 2] = target;
    return;

fallback:
    cursorPositions[y * 9 + x + 2] = pair[0];
}

// .text:0x0000A1A0 size:0xE8 mapped:0x80649234
void fn_2_A1A0(u8 arg0, u8 arg1) {
    u8 flag7 = Static_Stats_Tables[0x4757];
    u8 flag6 = g_d_GameSettings.p2_CPU_match_code;
    u8 flag5 = lbl_2_bss_100B8[0x2E];
    s32 idx = arg1 * 9;
    u8 *base8 = &cursorPositions[idx];
    s32 a = arg0;
    u8 *ptr10;
    s32 j;

restart:
    while (flag7 != 0) {
    }

    ptr10 = cursorPositions;
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

    cursorPositions[idx + a + 2] = 0;
}

// .text:0x0000A288 size:0x284 mapped:0x8064931C
void fn_2_A288(void) {
    return;
}

// .text:0x0000A50C size:0x120 mapped:0x806495A0
s32 fn_2_A50C(void) {
    s32 i;
    s32 j;
    s8 val;
    u8 *inner;

    for (i = 0; i < 9; i++) {
        inner = cursorPositions;

        val = (s8)cursorPositions[i + 2];
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
        inner = cursorPositions;

        val = (s8)cursorPositions[i + 2];
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
    return;
}

// .text:0x0000ABC0 size:0x328 mapped:0x80649C54
void fn_2_ABC0(void) {
    return;
}

// .text:0x0000AEE8 size:0x43C mapped:0x80649F7C
void fn_2_AEE8(void) {
    return;
}

// .text:0x0000B324 size:0x1E4 mapped:0x8064A3B8
void fn_2_B324(void) {
    return;
}

// .text:0x0000B508 size:0x164 mapped:0x8064A59C
void fn_2_B508(void) {
    s32 i, j;

    for (i = 0; i < 0x36; i++) {
        for (j = 1; j < 9; j++) {
            if ((s8)cursorPositions[j + 0xb] == i) {
                Static_Stats_Tables[i + 0x4757] = 0;
                addOrRemoveCharacterToTeam((s8)Static_Stats_Tables[0x46F9], i, 0);
                addRemoveCharVariantRelated(1, i, 0);
            }
        }
    }

    lineUpInfoStruct[0x2A] = 1;
    Static_Stats_Tables[0x51F8 + 0x2A] = 1;
    cursorPositions[0x0C] = 0x36;
    cursorPositions[0x54] = 0;

    lineUpInfoStruct[0x2E] = 2;
    Static_Stats_Tables[0x51F8 + 0x2E] = 2;
    cursorPositions[0x0D] = 0x36;
    cursorPositions[0x55] = 0;

    lineUpInfoStruct[0x32] = 3;
    Static_Stats_Tables[0x51F8 + 0x32] = 3;
    cursorPositions[0x0E] = 0x36;
    cursorPositions[0x56] = 0;

    lineUpInfoStruct[0x36] = 4;
    Static_Stats_Tables[0x51F8 + 0x36] = 4;
    cursorPositions[0x0F] = 0x36;
    cursorPositions[0x57] = 0;

    lineUpInfoStruct[0x3A] = 5;
    Static_Stats_Tables[0x51F8 + 0x3A] = 5;
    cursorPositions[0x10] = 0x36;
    cursorPositions[0x58] = 0;

    lineUpInfoStruct[0x3E] = 6;
    Static_Stats_Tables[0x51F8 + 0x3E] = 6;
    cursorPositions[0x11] = 0x36;
    cursorPositions[0x59] = 0;

    lineUpInfoStruct[0x42] = 7;
    Static_Stats_Tables[0x51F8 + 0x42] = 7;
    cursorPositions[0x12] = 0x36;
    cursorPositions[0x5A] = 0;

    lineUpInfoStruct[0x46] = 8;
    Static_Stats_Tables[0x51F8 + 0x46] = 8;
    cursorPositions[0x13] = 0x36;
    cursorPositions[0x5B] = 0;
}

// .text:0x0000B66C size:0x2B4 mapped:0x8064A700
void fn_2_B66C(void) {
    return;
}

// .text:0x0000B920 size:0x670 mapped:0x8064A9B4
void fn_2_B920(void) {
    return;
}

// .text:0x0000BF90 size:0x394 mapped:0x8064B024
void challengeSetRoster(void) {
    return;
}

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
void fn_2_C484(void) {
    return;
}

// .text:0x0000C698 size:0x144 mapped:0x8064B72C
void fn_2_C698(s32 idx, u8 port) {
    s8 charID;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        goto challenge;
    }

    charID = (s8)cursorPositions[port * 9 + idx + 2];
    Static_Stats_Tables[0x4757 + charID] = 1;

    if (g_d_GameSettings.p2_CPU_match_code != 0) {
        goto common_call;
    }
    if (port == 0) {
        goto common_call;
    }
    if (Static_Stats_Tables[0x46F8] == 0) {
        addOrRemoveCharacterToTeam(1, charID, 1);
    } else {
        addOrRemoveCharacterToTeam(0, charID, 1);
    }
    goto variant_call;

common_call:
    addOrRemoveCharacterToTeam((s8)Static_Stats_Tables[0x46F8 + port], charID, 1);

variant_call:
    addRemoveCharVariantRelated(port, charID, 1);
    return;

challenge:
    charID = (s8)cursorPositions[idx + 2];
    addOrRemoveCharacterToTeam(0, charID, 1);
    Static_Stats_Tables[0x4757 + charID] = 1;
    addRemoveCharVariantRelated(port, charID, 1);
}

// .text:0x0000C7DC size:0x284 mapped:0x8064B870
void fn_2_C7DC(void) {
    return;
}

// .text:0x0000CA60 size:0x25C mapped:0x8064BAF4
void fn_2_CA60(void) {
    return;
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
        s8 v = (s8)cursorPositions[port * 9 + count + 2];
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
        *(s32 *)&lbl_2_bss_F468[port * 4] = (s8)cursorPositions[port * 9 + count + 0x14];
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
    return;
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

    cursor = cursorPositions;
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
void randCharBasedOnClass(void) {
    return;
}

// .text:0x0000FAA0 size:0x214 mapped:0x8064EB34
void randCharacter1(void) {
    return;
}

// .text:0x0000FCB4 size:0x614 mapped:0x8064ED48
void randCharAlgo2(void) {
    return;
}

// .text:0x000102C8 size:0x234 mapped:0x8064F35C
void starHitSetting_Unused_maybe(void) {
    return;
}

// .text:0x000104FC size:0xBB4 mapped:0x8064F590
void characterSelectControls(void) {
    return;
}

