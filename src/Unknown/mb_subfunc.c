/* The shared header declares starMissionCompletionTracker as a ChallengeTrackingStruct[54]; this file
 * needs it as the whole ChallengeTrackerBlock (below). Rename the header declaration out of the way
 * here and redeclare the symbol with the struct type after the block is defined: a cast view of the
 * array does not compile the same (MWCC treats accesses through it as pointer accesses). */
#define starMissionCompletionTracker starMissionCompletionTracker_asArray
#include "Unknown/mb_subfunc.h"
#include "Unknown/orderchange.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x80062a94.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "text/text_channel.h"

/* Byte view of a 9-wide CharacterStats table; the chemistry row starts at byte 0x3B of each entry. */
typedef u8 CharacterStatsBytes[9][sizeof(CharacterStats)];
#define CHEMISTRY_OFFSET 0x3B

/* Saved Challenge-mode lineup slot. */
typedef struct {
    /* 0x0 */ s16 charID;
    /* 0x2 */ u8 battingOrder;
    /* 0x3 */ u8 fieldingPosition;
    /* 0x4 */ u8 handedness; // FieldingArm * 2 + BattingStance
    /* 0x5 */ u8 _5;
} SavedChallengeSlot; // size: 0x6

/* The whole 0x4508-byte starMissionCompletionTracker block. */
typedef struct {
    /* 0x0000 */ ChallengeTrackingStruct characters[54];
    /* 0x0AF8 */ u8 _0AF8[0x40B8 - 0xAF8];
    /* 0x40B8 */ SavedChallengeSlot savedLineup[9];
    /* 0x40EE */ u8 _40EE[0x441D - 0x40EE];
    /* 0x441D */ u8 captain;
    /* 0x441E */ u8 _441E;
    /* 0x441F */ s8 opponentCaptain;
    /* 0x4420 */ u8 _4420[0x4445 - 0x4420];
    /* 0x4445 */ u8 resumeSavedTeams;
    /* 0x4446 */ u8 _4446[0x4508 - 0x4446];
} ChallengeTrackerBlock; // size: 0x4508

#undef starMissionCompletionTracker
extern ChallengeTrackerBlock starMissionCompletionTracker;
#define CHALLENGE_TRACKER starMissionCompletionTracker

extern u8 superstarUnlocked[0x130];
extern u8 lineUpInfoStruct[2][9][4];
extern u8 lbl_802E4CE8[][0x50];
extern u8 lbl_800E88A4[][2];
extern u8 jukeboxWork[][0x50];
extern u16 lbl_803CBD24;
extern u8 lbl_803CBD18;
extern u8 lbl_803CBD19;
extern u16 lbl_803CBD1A;
extern u8 lbl_803CBD1C;
extern u8 lbl_803CBD1D;
extern u8 lbl_803CBD1E;
extern u8 lbl_803CBD1F;
extern u8 lbl_803CBD20;

extern void fn_800A8B78(void* stream);
extern u16 fn_800A8864(void);
extern void fn_800A8878(u32 left, u32 right);
extern void fn_800A8AB0(u32 mode);
extern void fn_800A8E30(StreamDescriptor* desc, void* work, u32 arg2, u32 arg3);
extern void fn_800111B4(TextBank* bank);

u8 lbl_803CB8D0[3] = { 3, 2, 1 };

u8 mainCharArray[33] = {
    CHAR_ID_MARIO, CHAR_ID_LUIGI, CHAR_ID_DK, CHAR_ID_DIDDY,
    CHAR_ID_PEACH, CHAR_ID_DAISY, CHAR_ID_YOSHI, CHAR_ID_BABYMARIO,
    CHAR_ID_BABYLUIGI, CHAR_ID_BOWSER, CHAR_ID_WARIO, CHAR_ID_WALUIGI,
    CHAR_ID_KOOPA_GREEN, CHAR_ID_TOAD_RED, CHAR_ID_BOO, CHAR_ID_TOADETTE,
    CHAR_ID_SHYGUY_RED, CHAR_ID_BIRDO, CHAR_ID_MONTY, CHAR_ID_BOWSERJR,
    CHAR_ID_PARATROOPA_RED, CHAR_ID_PIANTA_BLUE, CHAR_ID_NOKI_BLUE, CHAR_ID_BRO_HAMMER,
    CHAR_ID_TOADSWORTH, CHAR_ID_MAGIKOOPA_BLUE, CHAR_ID_KINGBOO, CHAR_ID_PETEY,
    CHAR_ID_DIXIE, CHAR_ID_GOOMBA, CHAR_ID_PARAGOOMBA, CHAR_ID_DRYBONES_GRAY,
    CHAR_ID_BIRDO,
};

u8 secondaryCharacterArray[22] = {
    CHAR_ID_PIANTA_RED, CHAR_ID_PIANTA_YELLOW, CHAR_ID_NOKI_RED, CHAR_ID_NOKI_GREEN,
    CHAR_ID_TOAD_BLUE, CHAR_ID_TOAD_YELLOW, CHAR_ID_TOAD_GREEN, CHAR_ID_TOAD_PURPLE,
    CHAR_ID_MAGIKOOPA_RED, CHAR_ID_MAGIKOOPA_GREEN, CHAR_ID_MAGIKOOPA_YELLOW, CHAR_ID_KOOPA_RED,
    CHAR_ID_PARATROOPA_GREEN, CHAR_ID_SHYGUY_BLUE, CHAR_ID_SHYGUY_YELLOW, CHAR_ID_SHYGUY_GREEN,
    CHAR_ID_SHYGUY_BLACK, CHAR_ID_DRYBONES_GREEN, CHAR_ID_DRYBONES_RED, CHAR_ID_DRYBONES_BLUE,
    CHAR_ID_BRO_FIRE, CHAR_ID_BRO_BOOMERANG,
};

u16 lbl_80108DF4[33] = {
    0x01C4, 0x01C5, 0x01CA, 0x01CB, 0x01C6, 0x01C7, 0x01CC, 0x01DE, 0x01DF, 0x01CE, 0x01C8,
    0x01C9, 0x01DB, 0x01D4, 0x01D6, 0x01D5, 0x01DD, 0x01CD, 0x01D0, 0x01CF, 0x01DC, 0x01D1,
    0x01D2, 0x01E1, 0x01D3, 0x01E3, 0x01D7, 0x01D8, 0x01E2, 0x01D9, 0x01DA, 0x01E0, 0x01E5,
};

u16 lbl_80108E38[69] = {
    0x0284, 0x0285, 0x0286, 0x0287, 0x0288, 0x0289, 0x028A, 0x028B, 0x028C, 0x028D,
    0x028E, 0x028F, 0x0290, 0x0291, 0x0292, 0x0293, 0x0294, 0x0295, 0x0296, 0x0297,
    0x0298, 0x0299, 0x029A, 0x029B, 0x029C, 0x029D, 0x029E, 0x029F, 0x02A0, 0x02A1,
    0x02A2, 0x02A3, 0x02A4, 0x02A5, 0x02A6, 0x02A7, 0x02A8, 0x02A9, 0x02AA, 0x02AB,
    0x02AC, 0x02AD, 0x02AE, 0x02AF, 0x02B0, 0x02B1, 0x02B2, 0x02B3, 0x02B4, 0x02B5,
    0x02B6, 0x02B7, 0x02B8, 0x02B9, 0x02BA, 0x02BB, 0x02BC, 0x02BD, 0x02BE, 0x02BF,
    0x02C0, 0x02C1, 0x02C2, 0x02C3, 0x02C4, 0x02C5, 0x02C6, 0x02C7, 0x02C8,
};

u8 captainIDOrderedOnCapSS[12] = {
    CHAR_ID_MARIO, CHAR_ID_PEACH, CHAR_ID_WARIO, CHAR_ID_DK,
    CHAR_ID_YOSHI, CHAR_ID_BOWSER, CHAR_ID_LUIGI, CHAR_ID_DAISY,
    CHAR_ID_WALUIGI, CHAR_ID_DIDDY, CHAR_ID_BIRDO, CHAR_ID_BOWSERJR,
};

u8 captainIDMappings[12] = {
    CHAR_ID_MARIO, CHAR_ID_LUIGI, CHAR_ID_PEACH, CHAR_ID_DAISY,
    CHAR_ID_YOSHI, CHAR_ID_BIRDO, CHAR_ID_WARIO, CHAR_ID_WALUIGI,
    CHAR_ID_DK, CHAR_ID_DIDDY, CHAR_ID_BOWSER, CHAR_ID_BOWSERJR,
};

s16 variantPairs[][5] = {
    { CHAR_ID_KOOPA_GREEN, CHAR_ID_KOOPA_RED, CHAR_ID_NONE, CHAR_ID_NONE, CHAR_ID_NONE },
    { CHAR_ID_TOAD_RED, CHAR_ID_TOAD_BLUE, CHAR_ID_TOAD_YELLOW, CHAR_ID_TOAD_GREEN, CHAR_ID_TOAD_PURPLE },
    { CHAR_ID_PARATROOPA_RED, CHAR_ID_PARATROOPA_GREEN, CHAR_ID_NONE, CHAR_ID_NONE, CHAR_ID_NONE },
    { CHAR_ID_SHYGUY_RED, CHAR_ID_SHYGUY_BLUE, CHAR_ID_SHYGUY_YELLOW, CHAR_ID_SHYGUY_GREEN, CHAR_ID_SHYGUY_BLACK },
    { CHAR_ID_PIANTA_BLUE, CHAR_ID_PIANTA_RED, CHAR_ID_PIANTA_YELLOW, CHAR_ID_NONE, CHAR_ID_NONE },
    { CHAR_ID_NOKI_BLUE, CHAR_ID_NOKI_RED, CHAR_ID_NOKI_GREEN, CHAR_ID_NONE, CHAR_ID_NONE },
    { CHAR_ID_MAGIKOOPA_BLUE, CHAR_ID_MAGIKOOPA_RED, CHAR_ID_MAGIKOOPA_GREEN, CHAR_ID_MAGIKOOPA_YELLOW, CHAR_ID_NONE },
    { CHAR_ID_DRYBONES_GRAY, CHAR_ID_DRYBONES_GREEN, CHAR_ID_DRYBONES_RED, CHAR_ID_DRYBONES_BLUE, CHAR_ID_NONE },
    { CHAR_ID_BRO_HAMMER, CHAR_ID_BRO_FIRE, CHAR_ID_BRO_BOOMERANG, CHAR_ID_NONE, CHAR_ID_NONE },
};

static u16 lbl_80108F38[24][4] = {
    { CHAR_ID_LUIGI, CHAR_ID_MONTY, CHAR_ID_PIANTA_BLUE, CHAR_ID_NOKI_BLUE },
    { CHAR_ID_PEACH, CHAR_ID_YOSHI, CHAR_ID_BOWSER, CHAR_ID_DK },
    { CHAR_ID_DAISY, CHAR_ID_DIDDY, CHAR_ID_WALUIGI, CHAR_ID_BABYLUIGI },
    { CHAR_ID_BOWSER, CHAR_ID_TOAD_RED, CHAR_ID_BOO, CHAR_ID_KINGBOO },
    { CHAR_ID_DAISY, CHAR_ID_TOAD_RED, CHAR_ID_TOADETTE, CHAR_ID_TOADSWORTH },
    { CHAR_ID_MARIO, CHAR_ID_BABYMARIO, CHAR_ID_BOWSER, CHAR_ID_BOWSERJR },
    { CHAR_ID_PEACH, CHAR_ID_TOADETTE, CHAR_ID_NOKI_BLUE, CHAR_ID_DIXIE },
    { CHAR_ID_WARIO, CHAR_ID_BIRDO, CHAR_ID_PETEY, CHAR_ID_DIXIE },
    { CHAR_ID_BIRDO, CHAR_ID_SHYGUY_RED, CHAR_ID_BABYMARIO, CHAR_ID_BABYLUIGI },
    { CHAR_ID_BOO, CHAR_ID_KINGBOO, CHAR_ID_PARATROOPA_RED, CHAR_ID_PARAGOOMBA },
    { CHAR_ID_YOSHI, CHAR_ID_SHYGUY_RED, CHAR_ID_KOOPA_GREEN, CHAR_ID_GOOMBA },
    { CHAR_ID_MARIO, CHAR_ID_LUIGI, CHAR_ID_PEACH, CHAR_ID_TOAD_RED },
    { CHAR_ID_WALUIGI, CHAR_ID_MAGIKOOPA_BLUE, CHAR_ID_KINGBOO, CHAR_ID_PETEY },
    { CHAR_ID_BOWSER, CHAR_ID_DK, CHAR_ID_BOWSERJR, CHAR_ID_BRO_HAMMER },
    { CHAR_ID_WARIO, CHAR_ID_KINGBOO, CHAR_ID_MAGIKOOPA_BLUE, CHAR_ID_DRYBONES_GRAY },
    { CHAR_ID_MARIO, CHAR_ID_LUIGI, CHAR_ID_WARIO, CHAR_ID_TOADSWORTH },
    { CHAR_ID_DIDDY, CHAR_ID_DIXIE, CHAR_ID_GOOMBA, CHAR_ID_KOOPA_GREEN },
    { CHAR_ID_YOSHI, CHAR_ID_BOWSER, CHAR_ID_PETEY, CHAR_ID_MONTY },
    { CHAR_ID_DIXIE, CHAR_ID_YOSHI, CHAR_ID_BIRDO, CHAR_ID_BOO },
    { CHAR_ID_MARIO, CHAR_ID_BIRDO, CHAR_ID_BABYMARIO, CHAR_ID_TOADETTE },
    { CHAR_ID_BOWSERJR, CHAR_ID_DRYBONES_GRAY, CHAR_ID_BRO_HAMMER, CHAR_ID_BRO_HAMMER },
    { CHAR_ID_WARIO, CHAR_ID_WALUIGI, CHAR_ID_BRO_HAMMER, CHAR_ID_PETEY },
    { CHAR_ID_DIDDY, CHAR_ID_GOOMBA, CHAR_ID_SHYGUY_RED, CHAR_ID_BOO },
    { CHAR_ID_DIDDY, CHAR_ID_DIXIE, CHAR_ID_BABYMARIO, CHAR_ID_BABYLUIGI },
};

u8 lbl_80108FF8[10][5] = {
    { CHAR_ID_PIANTA_BLUE, CHAR_ID_PIANTA_RED, CHAR_ID_PIANTA_YELLOW, CHAR_ID_NONE, CHAR_ID_NONE },
    { CHAR_ID_NOKI_BLUE, CHAR_ID_NOKI_RED, CHAR_ID_NOKI_GREEN, CHAR_ID_NONE, CHAR_ID_NONE },
    { CHAR_ID_TOAD_RED, CHAR_ID_TOAD_BLUE, CHAR_ID_TOAD_YELLOW, CHAR_ID_TOAD_GREEN, CHAR_ID_TOAD_PURPLE },
    { CHAR_ID_MAGIKOOPA_BLUE, CHAR_ID_MAGIKOOPA_RED, CHAR_ID_MAGIKOOPA_GREEN, CHAR_ID_MAGIKOOPA_YELLOW, CHAR_ID_NONE },
    { CHAR_ID_KOOPA_GREEN, CHAR_ID_KOOPA_RED, CHAR_ID_NONE, CHAR_ID_NONE, CHAR_ID_NONE },
    { CHAR_ID_PARATROOPA_RED, CHAR_ID_PARATROOPA_GREEN, CHAR_ID_NONE, CHAR_ID_NONE, CHAR_ID_NONE },
    { CHAR_ID_SHYGUY_RED, CHAR_ID_SHYGUY_BLUE, CHAR_ID_SHYGUY_YELLOW, CHAR_ID_SHYGUY_GREEN, CHAR_ID_SHYGUY_BLACK },
    { CHAR_ID_BOO, CHAR_ID_NONE, CHAR_ID_NONE, CHAR_ID_NONE, CHAR_ID_NONE },
    { CHAR_ID_GOOMBA, CHAR_ID_NONE, CHAR_ID_NONE, CHAR_ID_NONE, CHAR_ID_NONE },
    { CHAR_ID_PARAGOOMBA, CHAR_ID_NONE, CHAR_ID_NONE, CHAR_ID_NONE, CHAR_ID_NONE },
};

u8 lbl_8010902C[0x15] = {
    CHARACTER_CLASS_BALANCED, CHARACTER_CLASS_BALANCED, CHARACTER_CLASS_TECHNIQUE, CHARACTER_CLASS_BALANCED,
    CHARACTER_CLASS_SPEED, CHARACTER_CLASS_BALANCED, CHARACTER_CLASS_POWER, CHARACTER_CLASS_TECHNIQUE,
    CHARACTER_CLASS_POWER, CHARACTER_CLASS_SPEED, CHARACTER_CLASS_POWER, CHARACTER_CLASS_POWER,
    CHAR_ID_LUIGI, CHAR_ID_DK, CHAR_ID_DIDDY,
    CHAR_ID_PEACH, CHAR_ID_DAISY, CHAR_ID_YOSHI,
    CHAR_ID_WARIO, CHAR_ID_WALUIGI, CHAR_ID_BIRDO,
};

u32 testTextFileDescriptor[4] = { 0x00000000, 0x000000B4, 0x08E98000, 0x000000B4 };

u8 battingOrderPriorityPositions[2][4][5] = {
    {
        { 0x02, 0x05, 0x04, 0x03, 0x08 },
        { 0x03, 0x04, 0x05, 0x02, 0x06 },
        { 0x00, 0x01, 0x08, 0x06, 0x07 },
        { 0x01, 0x02, 0x00, 0x07, 0x04 },
    },
    {
        { 0x04, 0x03, 0x01, 0x02, 0x05 },
        { 0x01, 0x02, 0x04, 0x06, 0x08 },
        { 0x07, 0x06, 0x08, 0x05, 0x03 },
        { 0x03, 0x05, 0x07, 0x04, 0x06 },
    },
};

int findCharacterID(int charID) {
    int i;

    for (i = 0; i < 32; i++) {
        if (mainCharArray[i] == charID) {
            if (i == 17 && Static_Stats_Tables.unk48AE) {
                i = 32;
            }
            Static_Stats_Tables.unk48AE = 0;
            return i;
        }
    }

    if (i == 32) {
        for (i = 0; i < 22; i++) {
            if (secondaryCharacterArray[i] == charID) {
                switch (i) {
                case 0:
                case 1:
                    charID = 21;
                    break;
                case 2:
                case 3:
                    charID = 22;
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                    charID = 13;
                    break;
                case 8:
                case 9:
                case 10:
                    charID = 25;
                    break;
                case 11:
                    charID = 12;
                    break;
                case 12:
                    charID = 20;
                    break;
                case 13:
                case 14:
                case 15:
                case 16:
                    charID = 16;
                    break;
                case 17:
                case 18:
                case 19:
                    charID = 31;
                    break;
                case 20:
                case 21:
                    charID = 23;
                    break;
                }
                Static_Stats_Tables.unk48AE = 0;
                return charID;
            }
        }
        if (i == 22) {
            OSPanic("mb_subfunc.c", 149, "The character doesn't exist");
        }
    }
    /* Shift-JIS: "//OZ modorichi ga arimasen" (no return value) */
    OSPanic("mb_subfunc.c", 153, "//OZ \x96\xdf\x82\xe8\x92\x6c\x82\xaa\x82\xa0\x82\xe8\x82\xdc\x82\xb9\x82\xf1\n");
    return 0;
}

void setCaptainLocInRoster(void) {
    int team;
    int i;

    for (team = 0; team < TEAMS_PER_GAME; team++) {
        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            if (Static_Stats_Tables.captainSelectedID[team] == inMemRoster[team][i].stats.CharID) {
                Static_Stats_Tables.capLocationInOrder[team] = i;
            }
        }
    }
}

BOOL fn_800697B0(void) {
    switch (lbl_803CBD24) {
    case 0:
        screenTextArray.textBanks[1] = ARAMTransfer(testTextFileDescriptor, 0, 1, 0);
        lbl_803CBD24++;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            fn_800111B4(screenTextArray.textBanks[1]);
            lbl_803CBD24 = 0;
            return FALSE;
        }
        break;
    }
    return TRUE;
}

static inline void copyCharacterStats(CharacterStats* dst, CharacterStats* src) {
    memcpy(dst, src, 0x1E);
    dst->stats.CharID = src->stats.CharID;
    dst->stats.FieldingArm = src->stats.FieldingArm;
    dst->stats.BattingStance = src->stats.BattingStance;
    memcpy(&dst->stats.SlapContactSize, &src->stats.SlapContactSize, 2);
    memcpy(&dst->stats.SlapHitPower, &src->stats.SlapHitPower, 2);
    dst->stats.BuntingContactSize = src->stats.BuntingContactSize;
    dst->stats.HitTrajectoryPushPull = src->stats.HitTrajectoryPushPull;
    dst->stats.HitTrajectoryHighLow = src->stats.HitTrajectoryHighLow;
    dst->stats.Speed = src->stats.Speed;
    dst->stats.ThrowingArm = src->stats.ThrowingArm;
    dst->stats.CharacterClass = src->stats.CharacterClass;
    dst->stats.Weight = src->stats.Weight;
    dst->stats.Captain = src->stats.Captain;
    dst->stats.CaptainStarHitPitch = src->stats.CaptainStarHitPitch;
    memcpy(&dst->stats.NonCaptainStarSwing, &src->stats.NonCaptainStarSwing, 2);
    dst->stats.FieldingStats = src->stats.FieldingStats;
    memcpy(&dst->stats.BattingStatBar, &src->stats.BattingStatBar, 4);
    memcpy(&dst->chemistry, &src->chemistry, sizeof(ChemistryTable));
    dst->BytesAfterChemistry[0] = src->BytesAfterChemistry[0];
    dst->UnusedShorts[0] = src->UnusedShorts[0];
    dst->UnusedShorts[1] = src->UnusedShorts[1];
    dst->UnusedShorts[2] = src->UnusedShorts[2];
    dst->UnusedShorts[3] = src->UnusedShorts[3];
    dst->UnusedShorts[4] = src->UnusedShorts[4];
    dst->UnusedShorts[5] = src->UnusedShorts[5];
    dst->UnusedShorts[6] = src->UnusedShorts[6];
    dst->UnusedShorts[7] = src->UnusedShorts[7];
    dst->UnusedShorts[8] = src->UnusedShorts[8];
    dst->UnusedShorts[9] = src->UnusedShorts[9];
    dst->UnusedShorts[10] = src->UnusedShorts[10];
    dst->UnusedShorts[11] = src->UnusedShorts[11];
    dst->UnusedShorts[12] = src->UnusedShorts[12];
    dst->UnusedShorts[13] = src->UnusedShorts[13];
    dst->UnusedShorts[14] = src->UnusedShorts[14];
    dst->UnusedShorts[15] = src->UnusedShorts[15];
    dst->UnusedShorts[16] = src->UnusedShorts[16];
    dst->UnusedShorts[17] = src->UnusedShorts[17];
    dst->UnusedShorts[18] = src->UnusedShorts[18];
    dst->UnusedShorts[19] = src->UnusedShorts[19];
    dst->UnusedShorts[20] = src->UnusedShorts[20];
}

static inline void sortHighChemTeammates(int team, CharacterStats* roster) {
    u8* chemRow;
    int j;
    int i;
    int k;
    s8 list[10];
    s8 tmp;

    for (j = 0; j < 9; j++) {
        chemRow = (u8*)&roster[j].chemistry;
        for (i = 0; i < 9; i++) {
            if (chemRow[inMemRoster[team][i].stats.CharID] < 90 ||
                chemRow[inMemRoster[team][i].stats.CharID] == 100) {
                list[i] = CHAR_ID_NONE;
            } else {
                list[i] = inMemRoster[team][i].stats.CharID;
            }
        }
        for (i = 0; i < 9; i++) {
            for (k = 0; k < 10; k++) {
                if (list[i] > list[k]) {
                    tmp = list[i];
                    list[i] = list[k];
                    list[k] = tmp;
                }
            }
        }
        memcpy(Static_Stats_Tables.highChemTeammates[team][j], list, 9);
    }
}

static inline void tryAddRecruit(s8* avail, u8* count, s32 i) {
    int row;

    if ((int)CHALLENGE_TRACKER.characters[i]._31 == CHALLENGE_RECRUITMENT_CD_ON_BJ_TEAM) {
        if (addRemoveCharVariantRelated(0, i, 1)) {
            s16 (*pair)[5] = variantPairs;

            for (row = 0; row < 9; row++, pair++) {
                if (i == (*pair)[0]) {
                    break;
                }
            }
            if (row == 9) {
                return;
            }
        }
        avail[(*count)++] = i;
    }
}

void unknownSettingTeamValues(void) {
    s8 avail[54];
    u8 count;
    s32 i;
    s32 team;
    u8 statCol;
    u8 n;
    u8 statRow;
    s32 slot;
    u8 index;
    int k;
    int m;
    s8 tmp;
    s16 charID;
    u8 captainIndex;
    int handedness;

    count = 0;
    memset(avail, CHAR_ID_NONE, sizeof(avail));
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        tryAddRecruit(avail, &count, i);
    }
    Static_Stats_Tables.captainSelectedID[1] = CHAR_ID_BOWSERJR;
    if (CHALLENGE_TRACKER.resumeSavedTeams) {
        for (i = 0; i < 12; i++) {
            if (CHALLENGE_TRACKER.captain == captainIDOrderedOnCapSS[i]) {
                captainIndex = i;
                break;
            }
        }
        for (team = 0; team < TEAMS_PER_GAME; team++) {
            for (slot = 0; slot < PLAYERS_PER_TEAM; slot++) {
                if (team == 0) {
                    charID = Static_Stats_Tables.challengeRosters[captainIndex].charID[slot];
                } else {
                    charID = Static_Stats_Tables.challengeRosters[11].charID[slot];
                }
                statRow = charID / 9;
                statCol = charID % 9;
                copyCharacterStats(&inMemRoster[team][slot], &Static_Stats_Tables.characterStats[statRow][statCol]);
                cursorPositions.roster.rosterCharID[team][slot] = charID;
            }
        }
        fn_80067C48(0);
        fn_80067C48(1);
        unsure_FillRosterPositions(1);
        characterSelectScreen(1);
        for (slot = 0; slot < PLAYERS_PER_TEAM; slot++) {
            CHALLENGE_TRACKER.savedLineup[slot].charID = inMemRoster[0][slot].stats.CharID;
            CHALLENGE_TRACKER.savedLineup[slot].battingOrder = lineUpInfoStruct[0][slot][1];
            CHALLENGE_TRACKER.savedLineup[slot].fieldingPosition = lineUpInfoStruct[0][slot][2];
            CHALLENGE_TRACKER.savedLineup[slot].handedness = inMemRoster[0][slot].stats.BattingStance + inMemRoster[0][slot].stats.FieldingArm * 2;
        }
    } else {
        for (team = 0; team < TEAMS_PER_GAME; team++) {
            for (slot = 0; slot < PLAYERS_PER_TEAM; slot++) {
                if (team == 0) {
                    charID = CHALLENGE_TRACKER.savedLineup[slot].charID;
                } else {
                    charID = Static_Stats_Tables.challengeRosters[11].charID[slot];
                    if (charID != CHAR_ID_BOWSERJR && (n = count) != 0) {
                        do {
                            index = randRange_FUN_80042bf0(0, n - 1);
                            charID = avail[index];
                        } while (charID == CHAR_ID_NONE);
                        avail[index] = CHAR_ID_NONE;
                        Static_Stats_Tables.charOnCharacterGridSelected[charID] = 1;
                        for (k = 0; k < n - 1; k++) {
                            for (m = k + 1; m < n; m++) {
                                if (avail[k] == CHAR_ID_NONE) {
                                    tmp = avail[k];
                                    avail[k] = avail[m];
                                    avail[m] = tmp;
                                }
                            }
                        }
                        count--;
                    }
                }
                statRow = charID / 9;
                statCol = charID % 9;
                copyCharacterStats(&inMemRoster[team][slot], &Static_Stats_Tables.characterStats[statRow][statCol]);
                if (team == 0) {
                    handedness = CHALLENGE_TRACKER.savedLineup[slot].handedness;
                    lineUpInfoStruct[team][slot][0] = slot;
                    lineUpInfoStruct[team][slot][1] = CHALLENGE_TRACKER.savedLineup[slot].battingOrder;
                    lineUpInfoStruct[team][slot][2] = CHALLENGE_TRACKER.savedLineup[slot].fieldingPosition;
                    inMemRoster[team][slot].stats.FieldingArm = handedness / 2U;
                    inMemRoster[team][slot].stats.BattingStance = handedness % 2;
                }
                cursorPositions.roster.rosterCharID[team][slot] = charID;
            }
            if (team != 0) {
                unsure_FillRosterPositions(1);
                characterSelectScreen(1);
            }
        }
        fn_80067C48(0);
        fn_80067C48(1);
    }
    sortHighChemTeammates(0, (CharacterStats*)inMemRoster);
    setCaptainLocInRoster();
    setPortOfEachPlayer();
    setCaptainLocInRoster();
    teamLogoDetermination(0);
    teamLogoDetermination(1);
}

void playStream(u8 streamId) {
    u8 id;

    if (audioFileDescriptors.enableMusic) {
        id = streamId;
        fn_800A8878(lbl_800E88A4[id][0], lbl_800E88A4[id][0]);
        if (id == 12) {
            fn_800A8AB0(0);
        } else {
            fn_800A8AB0(2);
        }
        fn_800A8E30(&streamDescriptors[id], jukeboxWork[id], 0, 0);
        jukeboxCmd(4);
        jukeboxCmd(1);
    }
}

void fn_80068720(u8 index) {
    if (audioFileDescriptors.enableMusic) {
        jukeboxCmd(3);
        fn_800A8B78(lbl_802E4CE8[index]);
    }
}

BOOL fn_8006862C(u32 frames, u32 target) {
    u32 volume = (u8)(fn_800A8864() >> 8);

    if (lbl_803CBD18 == 0) {
        lbl_803CBD20 = volume / (frames / 60);
        if (lbl_803CBD20 > 60) {
            lbl_803CBD20 = 60;
        }
        lbl_803CBD18 = 1;
    }
    if (lbl_803CBD19 % (60 / lbl_803CBD20) == 0) {
        volume--;
        lbl_803CBD19 = 0;
    }
    if ((u8)volume <= (u8)target || frames == 1) {
        lbl_803CBD19 = 0;
        lbl_803CBD1A = 0;
        lbl_803CBD20 = 0;
        lbl_803CBD18 = 0;
        return FALSE;
    }
    fn_800A8878(volume, volume);
    lbl_803CBD19++;
    return TRUE;
}

BOOL fn_80068514(u32 frames, u32 target) {
    u8 volume = fn_800A8864() >> 8;

    lbl_803CBD1F = volume;
    if (volume >= (u8)target) {
        lbl_803CBD1F = target;
        return FALSE;
    }
    if (lbl_803CBD1C == 0) {
        lbl_803CBD1E = (u8)target / (frames / 60);
        if (lbl_803CBD1E > 60) {
            lbl_803CBD1E = 60;
        }
        lbl_803CBD1C = 1;
    }
    if (lbl_803CBD1D % (60 / lbl_803CBD1E) == 0) {
        lbl_803CBD1D = 0;
        lbl_803CBD1F++;
    }
    if (lbl_803CBD1F >= (u8)target) {
        lbl_803CBD1D = 0;
        lbl_803CBD1E = 0;
        lbl_803CBD1C = 0;
        fn_800A8878(target, target);
        return FALSE;
    }
    fn_800A8878(lbl_803CBD1F, lbl_803CBD1F);
    lbl_803CBD1D++;
    return TRUE;
}

void fn_800684A4(void) {
    int* ids = Static_Stats_Tables.captainSelectedID;

    ids[0] = captainIDOrderedOnCapSS[randRange_FUN_80042bf0(0, 12)];
    do {
        ids[1] = captainIDOrderedOnCapSS[randRange_FUN_80042bf0(0, 12)];
    } while (ids[0] == ids[1]);
}

void DraftRandomTeamDemo(u8 team) {
    s8 avail[54];
    s8 tmp;
    int i;
    int j;
    s32 slot;
    s8 index;
    s8 pick;
    int row;
    int col;
    int k;
    s16 variant;
    int captain;

    captain = Static_Stats_Tables.captainSelectedID[team];
    cursorPositions.roster.rosterCharID[team][0] = captain;
    fn_80067C48(team);
    memset(avail, -1, sizeof(avail));
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        if (Static_Stats_Tables.charOnCharacterGridSelected[Static_Stats_Tables.captainChemistryOrder[team][i]] == 0) {
            avail[i] = Static_Stats_Tables.captainChemistryOrder[team][i];
        }
    }
    for (slot = 1; slot < 9; slot++) {
        for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
            for (j = i; j < NUM_CHOOSABLE_CHARACTERS; j++) {
                if (avail[i] == -1 && avail[j] != -1) {
                    tmp = avail[i];
                    avail[i] = avail[j];
                    avail[j] = tmp;
                    break;
                }
            }
        }
        do {
            index = randRange_FUN_80042bf0(0, 19);
            pick = avail[index];
        } while (pick == -1);
        avail[index] = -1;
        Static_Stats_Tables.charOnCharacterGridSelected[pick] = 1;
        addRemoveCharVariantRelated(team, pick, 1);
        for (row = 0; row < 9; row++) {
            for (col = 0; col < 5; col++) {
                if (pick == variantPairs[row][col]) {
                    pick = variantPairs[row][0];
                    for (k = 0; k < 5; k++) {
                        variant = variantPairs[row][k];
                        if (variant != -1) {
                            for (j = 0; j < NUM_CHOOSABLE_CHARACTERS; j++) {
                                if (avail[j] == variant) {
                                    avail[j] = -1;
                                }
                            }
                        }
                    }
                    goto found;
                }
            }
        }
    found:
        cursorPositions.roster.rosterCharID[team][slot] = pick;
        cursorPositions.roster.chemWCaptain[team][slot] =
            ((CharacterStatsBytes*)Static_Stats_Tables.characterStats)[pick / 9][pick % 9][CHEMISTRY_OFFSET + captain];
    }
    for (slot = 0; slot < 9; slot++) {
        lineUpInfoStruct[team][slot][0] = lineUpInfoStruct[team][slot][1] = lineUpInfoStruct[team][slot][2] = slot;
    }
    fn_800670A0(team);
}

void fn_80067C48(u8 team) {
    u8 ids[54];
    u8 chem[54];
    int captain;
    int row;
    int col;
    s32 i;
    int k;
    u8 best;
    u8 tmpID;
    u8 tmpChem;

    captain = Static_Stats_Tables.captainSelectedID[team];
    col = captain % 9;
    row = captain / 9;
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        chem[i] = ((u8*)&Static_Stats_Tables.characterStats[row][col])[i + CHEMISTRY_OFFSET];
        ids[i] = i;
    }
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        best = chem[i];
        for (k = i + 1; k < NUM_CHOOSABLE_CHARACTERS; k++) {
            if (best < chem[k]) {
                tmpChem = chem[i];
                best = chem[k];
                tmpID = ids[i];
                chem[i] = chem[k];
                ids[i] = ids[k];
                chem[k] = tmpChem;
                ids[k] = tmpID;
            }
        }
    }
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        Static_Stats_Tables.captainChemistryOrder[team][i] = ids[i];
    }
}

u8 addRemoveCharVariantRelated(u8 port, u8 charID, u8 flag) {
    int row;
    int i;
    int k;

    if (charID == -1) {
        return FALSE;
    }
    for (row = 0; row < 9; row++) {
        for (i = 0; i < 5; i++) {
            if (charID == variantPairs[row][i]) {
                for (k = 0; k < 5; k++) {
                    if (variantPairs[row][k] != -1 && flag != 2) {
                        Static_Stats_Tables.charOnCharacterGridSelected[variantPairs[row][k]] = flag;
                    }
                }
                return TRUE;
            }
        }
    }
    return FALSE;
}

s16 fn_80067AC8(s16 charID, s8 col) {
    int row;
    int i;

    for (row = 0; row < 9; row++) {
        for (i = 0; i < 5; i++) {
            if (charID == variantPairs[row][i]) {
                if (col == -1) {
                    return charID;
                }
                return variantPairs[row][col];
            }
            if (variantPairs[row][i] == -1) {
                break;
            }
        }
    }
    return -1;
}

void teamLogoDetermination(int team) {
    int captain;
    int i;
    s8 group = -1;
    u8 logo;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (team == 0) {
            captain = Static_Stats_Tables.captainSelectedID[team] = ((u8*)&starMissionCompletionTracker)[0x441D];
        } else {
            captain = Static_Stats_Tables.captainSelectedID[team] = ((s8*)&starMissionCompletionTracker)[0x441F];
        }
    } else {
        captain = Static_Stats_Tables.captainSelectedID[team];
    }
    for (i = 0; i < 12; i++) {
        if (captain == captainIDMappings[i]) {
            group = i;
            break;
        }
    }
    logo = teamCompositionLogos(team, captain);
    if (logo == 0) {
        logo = teamClassTypeLogos(team, captain);
        if (logo != 0) {
            Static_Stats_Tables.teamName[team] = logo - 1 + group * 4;
        } else {
            Static_Stats_Tables.teamName[team] = (group + 1) * 4 - 1;
        }
    } else {
        Static_Stats_Tables.teamName[team] = logo - 1 + group * 4;
    }
}

static inline int findVariantRow(int charID) {
    int row;
    int col;

    for (row = 0; row < 9; row++) {
        for (col = 0; col < 5; col++) {
            if (charID == variantPairs[row][col]) {
                return row;
            }
        }
    }
    return -1;
}

u8 teamCompositionLogos(int team, int captain) {
    BOOL found[4];
    int m;
    int i;
    int set;
    int group;
    int v;
    int count;
    int row;
    int k;

    group = -1;
    count = 0;
    for (i = 0; i < 4; i++) {
        found[i] = FALSE;
    }
    for (i = 0; i < 12; i++) {
        if (captain == captainIDMappings[i]) {
            group = i;
            break;
        }
    }
    for (set = 0; set < 2; set++) {
        for (m = 0; m < 4; m++) {
            for (k = 0; k < 9; k++) {
                if (cursorPositions.roster.rosterCharID[team][k] == lbl_80108F38[group * 2 + set][m]) {
                    found[m] = TRUE;
                    count++;
                }
            }
            /* redundant self-store; present in the original code */
            lbl_80108F38[group * 2 + set][m] = lbl_80108F38[group * 2 + set][m];
        }
        if (count == 4) {
            return set + 1;
        }
        for (m = 0; m < 4; m++) {
            if (found[m] != TRUE) {
                row = findVariantRow(lbl_80108F38[group * 2 + set][m]);
                if (row != -1) {
                    for (v = 1; v < 5; v++) {
                        for (k = 0; k < 9; k++) {
                            if (cursorPositions.roster.rosterCharID[team][k] == variantPairs[row][v]) {
                                count++;
                                found[m] = TRUE;
                                if (count == 4) {
                                    return set + 1;
                                }
                                goto next;
                            }
                        }
                    }
                }
            }
        next:;
        }
        for (i = 0; i < 4; i++) {
            found[i] = FALSE;
        }
        count = 0;
    }
    return 0;
}

u8 teamClassTypeLogos(int team, int captain) {
    int classCount[4];
    int classes[2][9];
    int i;
    s32 j;
    int k;
    int favored;
    u8 charClass;

    for (i = 0; i < 4; i++) {
        classCount[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        classes[team][i] = 0;
        /* flat signed view of rosterCharID[team][i] */
        charClass = Static_Stats_Tables.characterStats
                        [((s8*)&cursorPositions)[team * PLAYERS_PER_TEAM + i + (int)sizeof(cursorPositions.cursor)] / 9]
                        [((s8*)&cursorPositions)[team * PLAYERS_PER_TEAM + i + (int)sizeof(cursorPositions.cursor)] % 9]
                            .stats.CharacterClass;
        classes[team][i] = charClass;
    }
    for (i = 0; i < 12; i++) {
        if (captain == captainIDMappings[i]) {
            favored = lbl_8010902C[i];
            break;
        }
    }
    for (j = 0; j < 9; j++) {
        classCount[classes[team][j]]++;
    }
    for (k = 0; k < 4; k++) {
        if (classCount[favored] <= classCount[k] && k != favored) {
            return 0;
        }
    }
    for (k = 0; k < 4; k++) {
        if (classCount[k] >= 3 && k == favored) {
            return 3;
        }
    }
    return 0;
}

void selectRandomStadium(void) {
    u8 stadium;

    if (superstarUnlocked[0xF5]) {
        stadium = randRange_FUN_80042bf0(STADIUM_ID_MARIO_STADIUM, STADIUM_ID_DK_JUNGLE);
    } else {
        do {
            stadium = randRange_FUN_80042bf0(STADIUM_ID_MARIO_STADIUM, STADIUM_ID_DK_JUNGLE);
        } while (stadium == STADIUM_ID_BOWSERS_CASTLE);
    }
    g_d_GameSettings.StadiumID = stadium;
}

void fn_800670A0(u8 team) {
    int i;
    int sum = 0;
    int average = 0;
    int count = 0;
    u8 stars = 0;

    for (i = 0; i < 9; i++) {
        if (cursorPositions.roster.chemWCaptain[team][i] != 0 &&
            cursorPositions.roster.rosterCharID[team][i] != Static_Stats_Tables.captainSelectedID[team]) {
            sum += cursorPositions.roster.chemWCaptain[team][i];
            count++;
        }
    }
    if (count != 0) {
        average = sum / count;
    }
    if (average >= 70) {
        stars = 5;
    } else if (average <= 69 && average >= 55) {
        stars = 4;
    } else if (average <= 54 && average >= 35) {
        stars = 3;
    } else if (average <= 34 && average >= 15) {
        stars = 2;
    } else if (average <= 14 && average > 0) {
        stars = 1;
    }
    Static_Stats_Tables.startingChemStars[team] = stars;
}

static inline void buildHighChemLists(int team, CharacterStats* player, int j) {
    s8 list[10];
    s8 tmp;
    int i;
    int k;

    for (i = 0; i < 9; i++) {
        if (((u8*)player)[inMemRoster[team][i].stats.CharID + CHEMISTRY_OFFSET] < 90 ||
            ((u8*)player)[inMemRoster[team][i].stats.CharID + CHEMISTRY_OFFSET] == 100) {
            list[i] = CHAR_ID_NONE;
        } else {
            list[i] = inMemRoster[team][i].stats.CharID;
        }
    }
    for (i = 0; i < 9; i++) {
        for (k = 0; k < 10; k++) {
            if (list[i] > list[k]) {
                tmp = list[i];
                list[i] = list[k];
                list[k] = tmp;
            }
        }
    }
    memcpy(Static_Stats_Tables.highChemTeammates[team][j], list, 9);
}

void fn_80066EAC(u8 team) {
    int j;

    for (j = 0; j < 9; j++) {
        buildHighChemLists(team, &inMemRoster[team][j], j);
    }
}

void characterSelectScreen(u8 team) {
    s16 ids[9];
    s8 order[9];
    s8 captains[9];
    s16 charID;
    u8 position;
    s32 i;
    int j;
    int k;
    int r;
    u8 count;
    u8 otherCount;
    u8 slot;
    int rankA;
    int rankB;
    int tmp;
    u8 statRow;
    u8 statCol;
    u8 charClass;
    u8 isCaptain;
    s8 others[9];
    s8 key;
    int captainKey;
    s8 other;
    u8 positions[9];

    for (i = 0; i < 9; i++) {
        others[i] = CHAR_ID_NONE;
        captains[i] = CHAR_ID_NONE;
        order[i] = CHAR_ID_NONE;
        ids[i] = inMemRoster[team][i].stats.CharID;
        positions[i] = cursorPositions.roster.positionSwapMapping[team][i];
    }
    order[battingOrderPriorityPositions[0][inMemRoster[team][0].stats.CharacterClass][0]] = inMemRoster[team][0].stats.CharID;
    count = 0;
    for (j = 1; j < 9; j++) {
        for (k = 0; k < 12; k++) {
            if (captainIDOrderedOnCapSS[k] == inMemRoster[team][j].stats.CharID) {
                captains[count++] = inMemRoster[team][j].stats.CharID;
            }
        }
    }
    if (captains[0] != CHAR_ID_NONE) {
        if (captains[1] == CHAR_ID_NONE) {
            statRow = captains[0] / 9;
            statCol = captains[0] % 9;
            charClass = Static_Stats_Tables.characterStats[statRow][statCol].stats.CharacterClass;
            for (k = 0; k < 5; k++) {
                position = battingOrderPriorityPositions[0][charClass][k];
                if (order[position] == CHAR_ID_NONE) {
                    order[position] = captains[0];
                    break;
                }
            }
            if (k == 5) {
                do {
                    slot = randRange_FUN_80042bf0(0, 8);
                } while (order[slot] != CHAR_ID_NONE);
                order[slot] = captains[0];
            }
        } else {
            for (j = 0; j < 8; j++) {
                if (captains[j] == CHAR_ID_NONE) {
                    break;
                }
                captainKey = inMemRoster[team][captains[j]].stats.CharID;
                for (r = 0; r < NUM_CHOOSABLE_CHARACTERS; r++) {
                    if (Static_Stats_Tables.captainChemistryOrder[team][r] == captainKey) {
                        rankA = r;
                        break;
                    }
                }
                for (k = j + 1; k < 9; k++) {
                    if ((other = captains[k]) == CHAR_ID_NONE) {
                        break;
                    }
                    for (r = 0; r < NUM_CHOOSABLE_CHARACTERS; r++) {
                        if (Static_Stats_Tables.captainChemistryOrder[team][r] == other) {
                            rankB = r;
                            break;
                        }
                    }
                    if (rankA > rankB) {
                        tmp = other;
                        captains[k] = captains[j];
                        captains[j] = tmp;
                    }
                }
            }
            for (j = 0; j < 9; j++) {
                if (captains[j] == CHAR_ID_NONE) {
                    break;
                }
                statRow = captains[j] / 9;
                statCol = captains[j] % 9;
                charClass = Static_Stats_Tables.characterStats[statRow][statCol].stats.CharacterClass;
                for (k = 0; k < 5; k++) {
                    position = battingOrderPriorityPositions[0][charClass][k];
                    if (order[position] == CHAR_ID_NONE) {
                        order[position] = captains[j];
                        break;
                    }
                }
                if (k == 5) {
                    do {
                        slot = randRange_FUN_80042bf0(0, 8);
                    } while (order[slot] != CHAR_ID_NONE);
                    order[slot] = captains[j];
                }
            }
        }
    }
    otherCount = 0;
    for (j = 1; j < 9; j++) {
        isCaptain = FALSE;
        for (k = 0; k < 12; k++) {
            if (captainIDOrderedOnCapSS[k] == inMemRoster[team][j].stats.CharID) {
                isCaptain = TRUE;
            }
        }
        /* redundant self-store; present in the original code */
        inMemRoster[team][j].stats.CharID = inMemRoster[team][j].stats.CharID;
        if (!isCaptain) {
            others[otherCount++] = inMemRoster[team][j].stats.CharID;
        }
    }
    for (j = 0; j < 8; j++) {
        if ((key = others[j]) == CHAR_ID_NONE) {
            break;
        }
        for (r = 0; r < NUM_CHOOSABLE_CHARACTERS; r++) {
            if (Static_Stats_Tables.captainChemistryOrder[team][r] == key) {
                rankA = r;
                break;
            }
        }
        for (k = j + 1; k < 9; k++) {
            if ((other = others[k]) == CHAR_ID_NONE) {
                break;
            }
            for (r = 0; r < NUM_CHOOSABLE_CHARACTERS; r++) {
                if (Static_Stats_Tables.captainChemistryOrder[team][r] == other) {
                    rankB = r;
                    break;
                }
            }
            if (rankA > rankB) {
                tmp = other;
                others[k] = others[j];
                others[j] = tmp;
            }
        }
    }
    for (j = 0; j < 9; j++) {
        if (others[j] == CHAR_ID_NONE) {
            break;
        }
        charClass = Static_Stats_Tables.characterStats[others[j] / 9][others[j] % 9].stats.CharacterClass;
        for (k = 0; k < 5; k++) {
            position = battingOrderPriorityPositions[0][charClass][k];
            if (order[position] == CHAR_ID_NONE) {
                order[position] = others[j];
                break;
            }
        }
        if (k == 5) {
            do {
                slot = randRange_FUN_80042bf0(0, 8);
            } while (order[slot] != CHAR_ID_NONE);
            order[slot] = others[j];
        }
    }
    for (j = 0; j < 9; j++) {
        copyCharacterStats(&inMemRoster[team][j], &Static_Stats_Tables.characterStats[order[j] / 9][order[j] % 9]);
        sortHighChemTeammates(team, inMemRoster[team]);
        lineUpInfoStruct[team][j][0] = j;
        lineUpInfoStruct[team][j][1] = j;
        for (k = 0; k < 9; k++) {
            if (order[j] == ids[k] && ids[k] != CHAR_ID_NONE) {
                ids[k] = CHAR_ID_NONE;
                break;
            }
        }
        lineUpInfoStruct[team][j][2] = positions[k];
    }
}

void unsure_FillRosterPositions(u8 team) {
    s8 positions[9];
    s8 captains[9];
    s8 others[9];
    s32 i;
    s32 t;
    u8 otherCount;
    int m;
    s32 s;
    int tmp;
    int r;
    s32 j;
    int k;
    u8 ok = FALSE;
    u8 okOther;
    u8 isCaptain;
    u8 position;
    u8 randomPosition;
    u8 statRow;
    u8 statCol;
    u8 charClass;
    s8 key;
    s8 other;
    u8 count;
    int rankA;
    int captain;
    int rankB;
    int captainKey;

    for (i = 0; i < 9; i++) {
        others[i] = CHAR_ID_NONE;
        captains[i] = CHAR_ID_NONE;
        positions[i] = FIELDING_POSITION_NONE;
    }
    captain = Static_Stats_Tables.captainSelectedID[team];
    position = FIELDING_POSITION_PITCHER;
    for (i = 0; i < 9; i++) {
        if (cursorPositions.roster.rosterCharID[team][i] == captain) {
            positions[i] = position;
        }
    }
    count = 0;
    for (j = 0; j < 9; j++) {
        for (k = 0; k < 12; k++) {
            if (cursorPositions.roster.rosterCharID[team][j] == captainIDOrderedOnCapSS[k] &&
                captain != cursorPositions.roster.rosterCharID[team][j]) {
                captains[count++] = cursorPositions.roster.rosterCharID[team][j];
            }
        }
    }
    if (captains[0] != CHAR_ID_NONE) {
        if (captains[1] == CHAR_ID_NONE) {
            statRow = captains[0] / 9;
            statCol = captains[0] % 9;
            charClass = Static_Stats_Tables.characterStats[statRow][statCol].stats.CharacterClass;
            for (j = 0; j < 5; j++) {
                position = battingOrderPriorityPositions[1][charClass][j];
                for (m = 0; m < 9; m++) {
                    if (positions[m] == position) {
                        break;
                    }
                }
                if (m == 9) {
                    for (s = 0; s < 9; s++) {
                        if (captains[0] == cursorPositions.roster.rosterCharID[team][s] && positions[s] == FIELDING_POSITION_NONE) {
                            positions[s] = position;
                            goto placedCaptain;
                        }
                    }
                }
            }
            if (j == 5) {
                do {
                    randomPosition = randRange_FUN_80042bf0(FIELDING_POSITION_PITCHER, FIELDING_POSITION_RIGHT_FIELD);
                    for (m = 0; m < 9; m++) {
                        if (positions[m] == randomPosition) {
                            ok = FALSE;
                            break;
                        }
                    }
                    if (m == 9) {
                        ok = TRUE;
                    }
                } while (!ok);
                for (s = 0; s < 9; s++) {
                    if (captains[0] == cursorPositions.roster.rosterCharID[team][s]) {
                        positions[s] = randomPosition;
                        goto placedCaptain;
                    }
                }
            }
        } else {
            for (j = 0; j < 8; j++) {
                if (captains[j] == CHAR_ID_NONE) {
                    break;
                }
                captainKey = cursorPositions.roster.rosterCharID[team][j];
                for (r = 0; r < NUM_CHOOSABLE_CHARACTERS; r++) {
                    if (Static_Stats_Tables.captainChemistryOrder[team][r] == captainKey) {
                        rankA = r;
                        break;
                    }
                }
                for (t = j + 1; t < 9; t++) {
                    if ((other = captains[t]) == CHAR_ID_NONE) {
                        break;
                    }
                    for (r = 0; r < NUM_CHOOSABLE_CHARACTERS; r++) {
                        if (Static_Stats_Tables.captainChemistryOrder[team][r] == other) {
                            rankB = r;
                            break;
                        }
                    }
                    if (rankA > rankB) {
                        tmp = other;
                        captains[t] = captains[j];
                        captains[j] = tmp;
                    }
                }
            }
            for (j = 0; j < 9; j++) {
                if (captains[j] == CHAR_ID_NONE) {
                    break;
                }
                statRow = captains[j] / 9;
                statCol = captains[j] % 9;
                charClass = Static_Stats_Tables.characterStats[statRow][statCol].stats.CharacterClass;
                for (k = 0; k < 5; k++) {
                    position = battingOrderPriorityPositions[1][charClass][k];
                    for (m = 0; m < 9; m++) {
                        if (positions[m] == position) {
                            break;
                        }
                    }
                    if (m == 9) {
                        for (i = 0; i < 9; i++) {
                            if (captains[j] == cursorPositions.roster.rosterCharID[team][i] && positions[i] == FIELDING_POSITION_NONE) {
                                positions[i] = position;
                                goto placedCaptain;
                            }
                        }
                    }
                }
                if (k == 5) {
                    do {
                        randomPosition = randRange_FUN_80042bf0(FIELDING_POSITION_PITCHER, FIELDING_POSITION_RIGHT_FIELD);
                        for (m = 0; m < 9; m++) {
                            if (positions[m] == randomPosition) {
                                ok = FALSE;
                                break;
                            }
                        }
                        if (m == 9) {
                            ok = TRUE;
                        }
                    } while (!ok);
                    for (s = 0; s < 9; s++) {
                        if (captains[j] == cursorPositions.roster.rosterCharID[team][s]) {
                            positions[s] = randomPosition;
                            break;
                        }
                    }
                }
            placedCaptain:;
            }
        }
    }
    otherCount = 0;
    for (j = 0; j < 9; j++) {
        isCaptain = FALSE;
        for (k = 0; k < 12; k++) {
            if (cursorPositions.roster.rosterCharID[team][j] == captainIDOrderedOnCapSS[k]) {
                isCaptain = TRUE;
            }
        }
        /* redundant self-store; present in the original code */
        cursorPositions.roster.rosterCharID[team][j] = cursorPositions.roster.rosterCharID[team][j];
        if (!isCaptain) {
            others[otherCount++] = cursorPositions.roster.rosterCharID[team][j];
        }
    }
    for (j = 0; j < 8; j++) {
        if ((key = others[j]) == CHAR_ID_NONE) {
            break;
        }
        for (r = 0; r < NUM_CHOOSABLE_CHARACTERS; r++) {
            if (Static_Stats_Tables.captainChemistryOrder[team][r] == key) {
                rankA = r;
                break;
            }
        }
        for (t = j + 1; t < 9; t++) {
            if ((other = others[t]) == CHAR_ID_NONE) {
                break;
            }
            for (r = 0; r < NUM_CHOOSABLE_CHARACTERS; r++) {
                if (Static_Stats_Tables.captainChemistryOrder[team][r] == other) {
                    rankB = r;
                    break;
                }
            }
            if (rankA > rankB) {
                tmp = other;
                others[t] = others[j];
                others[j] = tmp;
            }
        }
    }
    for (j = 0; j < 9; j++) {
        if (others[j] == CHAR_ID_NONE) {
            break;
        }
        charClass = Static_Stats_Tables.characterStats[others[j] / 9][others[j] % 9].stats.CharacterClass;
        for (k = 0; k < 5; k++) {
            position = battingOrderPriorityPositions[1][charClass][k];
            for (m = 0; m < 9; m++) {
                if (positions[m] == position) {
                    break;
                }
            }
            if (m == 9) {
                for (s = 0; s < 9; s++) {
                    if (others[j] == cursorPositions.roster.rosterCharID[team][s] && positions[s] == FIELDING_POSITION_NONE) {
                        positions[s] = position;
                        goto placedOther;
                    }
                }
            }
        }
        if (k == 5) {
            do {
                randomPosition = randRange_FUN_80042bf0(FIELDING_POSITION_PITCHER, FIELDING_POSITION_RIGHT_FIELD);
                okOther = TRUE;
                for (m = 0; m < 9; m++) {
                    if (positions[m] == randomPosition) {
                        okOther = FALSE;
                        break;
                    }
                }
            } while (!okOther);
            for (t = 0; t < 9; t++) {
                if (others[j] == cursorPositions.roster.rosterCharID[team][t] && positions[t] == FIELDING_POSITION_NONE) {
                    positions[t] = randomPosition;
                    break;
                }
            }
        }
    placedOther:;
    }
    for (i = 0; i < 9; i++) {
        cursorPositions.roster.positionSwapMapping[team][i] = positions[i];
    }
}

void fn_800649BC(void) {
    g_d_GameSettings.home_AwaySetting = randRange_FUN_80042bf0(0, 1);
    inningSetting.inningCount = 3;
    inningSetting.aiDifficulty = lbl_803CB8D0[0];
}

void setPortOfEachPlayer(void) {
    g_d_GameSettings.PlayerPorts[0] = Static_Stats_Tables.playerNumberByPort[0];
    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        if (g_d_GameSettings.PlayerPorts[0] == 0) {
            g_d_GameSettings.PlayerPorts[1] = 5;
        } else {
            g_d_GameSettings.PlayerPorts[1] = 4;
        }
    } else {
        g_d_GameSettings.PlayerPorts[1] = Static_Stats_Tables.playerNumberByPort[1];
    }
}

int fn_80064918(s16 charID) {
    switch (charID) {
    case CHAR_ID_MARIO:
    case CHAR_ID_LUIGI:
        return 4;
    case CHAR_ID_PEACH:
    case CHAR_ID_DAISY:
    case CHAR_ID_WALUIGI:
    case CHAR_ID_BOO:
        return 1;
    case CHAR_ID_DIDDY:
    case CHAR_ID_TOADSWORTH:
    case CHAR_ID_MAGIKOOPA_BLUE:
    case CHAR_ID_MAGIKOOPA_RED:
    case CHAR_ID_MAGIKOOPA_GREEN:
    case CHAR_ID_MAGIKOOPA_YELLOW:
    case CHAR_ID_DIXIE:
    case CHAR_ID_SHYGUY_BLACK:
        return 2;
    case CHAR_ID_KOOPA_GREEN:
    case CHAR_ID_SHYGUY_RED:
    case CHAR_ID_TOAD_PURPLE:
    case CHAR_ID_GOOMBA:
    case CHAR_ID_SHYGUY_BLUE:
    case CHAR_ID_SHYGUY_YELLOW:
    case CHAR_ID_SHYGUY_GREEN:
    case CHAR_ID_DRYBONES_GRAY:
    case CHAR_ID_DRYBONES_BLUE:
        return 5;
    case CHAR_ID_YOSHI:
    case CHAR_ID_BABYMARIO:
    case CHAR_ID_BABYLUIGI:
    case CHAR_ID_TOAD_RED:
    case CHAR_ID_TOADETTE:
    case CHAR_ID_MONTY:
    case CHAR_ID_PARATROOPA_RED:
    case CHAR_ID_NOKI_BLUE:
    case CHAR_ID_NOKI_RED:
    case CHAR_ID_NOKI_GREEN:
    case CHAR_ID_TOAD_BLUE:
    case CHAR_ID_TOAD_YELLOW:
    case CHAR_ID_TOAD_GREEN:
    case CHAR_ID_PARAGOOMBA:
    case CHAR_ID_PARATROOPA_GREEN:
        return 3;
    default:
        return 0;
    }
}

u8 translateStarSwing(u8 starSwing) {
    switch (starSwing) {
    case 0:
        return 0x84;
    case 1:
        return 0x86;
    case 2:
        return 0x90;
    case 3:
        return 0x92;
    case 4:
        return 0x98;
    case 5:
        return 0x9A;
    case 6:
        return 0x8C;
    case 7:
        return 0x8E;
    case 8:
        return 0x88;
    case 9:
        return 0x8A;
    case 10:
        return 0x94;
    case 11:
        return 0x96;
    case 12:
        return 0x9D;
    case 13:
        return 0x9E;
    case 14:
        return 0x9F;
    }
    return starSwing;
}

u8 translateStarPitch(u8 starPitch) {
    switch (starPitch) {
    case 0:
        return 0x85;
    case 1:
        return 0x87;
    case 2:
        return 0x91;
    case 3:
        return 0x93;
    case 4:
        return 0x99;
    case 5:
        return 0x9B;
    case 6:
        return 0x8D;
    case 7:
        return 0x8F;
    case 8:
        return 0x89;
    case 9:
        return 0x8B;
    case 10:
        return 0x95;
    case 11:
        return 0x97;
    case 12:
        return 0xA1;
    case 13:
        return 0xA0;
    case 14:
        return 0xA2;
    }
    return starPitch;
}

int translateStarPitchHitIndex(u8 starHitType) {
    switch (starHitType) {
    case 0:
        return 6;
    case 1:
        return 7;
    case 2:
        return 10;
    case 3:
        return 11;
    case 4:
        return 14;
    case 5:
        return 15;
    case 6:
        return 16;
    case 7:
        return 17;
    case 8:
        return 12;
    case 9:
        return 13;
    case 10:
        return 8;
    case 11:
        return 9;
    default:
        return -1;
    }
}
