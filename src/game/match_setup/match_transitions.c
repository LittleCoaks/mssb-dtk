#define SQRT2_LINKAGE static
#include "game/match_setup/match_transitions.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 animRelated[0x124];
extern u8 hugeAnimStruct[0x3154];
extern u8 characterStaticIndexes[0x144];
extern u8 constantList[0x1C];
extern BOOL practice_loadAllGraphics(int team);
extern void fn_8001196C(void);
extern void fn_80011A60(void);
extern void fn_80011BE4(int arg0);
extern void fn_800BDE8C(int arg0);
extern void* fn_800111D8(void* obj);
extern int fn_80016344(int a, int b, int c, int d);
extern int fn_8001500C(int a, int b);

// .text:0x0006BD6C size:0x138
BOOL championshipScreenGraphics(void) {
    int team;
    int slot;

    if (animRelated[0x9B] == 0) {
        fn_8001196C();
    }
    animRelated[0x9B] = 1;
    hugeAnimStruct[0x2D77] = 0;
    hugeAnimStruct[0x2D7B] = 0;
    hugeAnimStruct[0x2D7C] = 0;

    if (g_GameLogic.gameStatus == 9) {
        hugeAnimStruct[0x2D7C] = 1;
        for (team = 0; team < 2; team++) {
            for (slot = 0; slot < 9; slot++) {
                u8* entry = (u8*)&inMemRoster[team][slot];
                s16 charID = *(s16*)(entry + 0x24);
                if (characterStaticIndexes[charID * 6 + 2] == 0x19) {
                    entry[0x26] = 0;
                    entry[0x27] = 1;
                }
            }
        }
    }
    return practice_loadAllGraphics(g_GameLogic.teamFielding) != FALSE;
}

// .text:0x0006BA64 size:0x308
BOOL loadRunnerActors(void) {
    int mode;
    int next;
    int cur;

    if (animRelated[0x9A] == 0) {
        hugeAnimStruct[0x2D7A] = 0;
        hugeAnimStruct[0x2D77] = 0;
        animRelated[0x9A] = 1;
    }

    do {
        int runner = 3 - hugeAnimStruct[0x2D7A];
        if (g_Runners[runner].rosterID >= 0) {
            if (fn_8001500C(g_GameLogic.teamBatting, runner + 9) == 0) {
                return FALSE;
            }
        }
        hugeAnimStruct[0x2D7A]++;
    } while ((u8)hugeAnimStruct[0x2D7A] < 4);

    mode = g_d_GameSettings.GameModeSelected;

    if (mode == 0 || mode == 4 || mode == 5 || (mode == 2 && g_GameLogic.secondaryGameMode == 0x10)) {
        *(s16*)&animRelated[0x9E] = g_Runners[0].charID;
    } else if (mode == 2 && g_GameLogic.secondaryGameMode == 0xF) {
        *(s16*)&animRelated[0x9E] = constantList[g_Practice.rosterID];
    }

    if (mode == 0 || mode == 4 || mode == 5 || (mode == 2 && g_GameLogic.secondaryGameMode == 0x10)) {
        cur = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam];
        next = cur + 1;
        if (next > 9) {
            next = 1;
        }
        *(s16*)&animRelated[0xA0] = *(s16*)((u8*)&inMemRoster[g_GameLogic.teamBatting][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][next][0]] + 0x24);
    } else if (mode == 2 && g_GameLogic.secondaryGameMode == 0xF) {
        cur = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam];
        *(s16*)&animRelated[0xA0] = *(s16*)((u8*)&inMemRoster[g_GameLogic.teamBatting][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][cur][0]] + 0x24);
    }

    if (mode == 0 || mode == 5 || mode == 4) {
        cur = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam];
        next = cur + 1;
        if (next > 9) {
            next = 1;
        }
        *(s16*)&animRelated[0xA2] = *(s16*)((u8*)&inMemRoster[g_GameLogic.teamBatting][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][next][0]] + 0x24);
    }
    return TRUE;
}

// .text:0x0006B870 size:0x1F4
void matchTransitionFunction2(void) {
    int i;

    if (g_Strikes.outs >= 3) {
        for (i = 0; i < 4; i++) {
            if (!(g_d_GameSettings.GameModeSelected == 2 && g_GameLogic.secondaryGameMode == 0xF && i == 0)) {
                fn_80011BE4(i + 9);
            }
        }
    } else if (g_GameLogic.gameStatus == 0xA) {
        for (i = 1; i < 4; i++) {
            if (g_RunningLogic.runnerTransferIndex[i] == -1) {
                fn_80011BE4(i + 9);
            }
        }
    } else {
        for (i = 1; i < 4; i++) {
            if (g_RunningLogic.runnerTransferIndex[i] == -1) {
                fn_80011BE4(i + 9);
            }
        }
        if (!(g_d_GameSettings.GameModeSelected == 2 && g_GameLogic.secondaryGameMode == 0xF)) {
            fn_80011BE4(9);
        }
    }

    for (i = 9; i < 13; i++) {
        if (!(g_d_GameSettings.GameModeSelected == 2 && g_GameLogic.secondaryGameMode == 0xF && i == 9)) {
            *(void**)&hugeAnimStruct[0x2C50 + i * 4] = NULL;
        }
    }
}

// .text:0x0006B674 size:0x1FC
void animateShadows_nonBall(void) {
    int i;
    int shadowOn;
    int miniGameMode;
    u8* obj;
    u8* state;

    if (g_d_GameSettings.minigamesEnabled != 0 && g_Minigame.GameMode_MiniGame != 0) {
        miniGameMode = g_Minigame.GameMode_MiniGame;
        if (miniGameMode == 1 || miniGameMode == 3) {
            fn_800BDE8C(2);
        } else if (miniGameMode >= 2 && miniGameMode <= 6) {
            fn_800BDE8C(1);
        }
    } else {
        if (g_GameLogic.sceneID == 1) {
            fn_800BDE8C(2);
        } else {
            fn_800BDE8C(1);
        }
    }

    for (i = 0; i < 13; i++) {
        obj = ((u8**)&hugeAnimStruct[0x2C50])[i];
        if (obj == NULL) {
            continue;
        }
        state = fn_800111D8(obj);
        if (*(void**)state == NULL) {
            continue;
        }

        shadowOn = 1;
        if (g_d_GameSettings.minigamesEnabled != 0) {
            if (g_GameLogic.gameStatus == 0x1C || g_GameLogic.gameStatus == 0x1D ||
                g_GameLogic.gameStatus == 0x1E || g_GameLogic.gameStatus == 0x1F) {
                if (g_GameLogic.gameStatus == 0x1F) {
                    shadowOn = 0;
                }
            }
            if (g_d_GameSettings.GameModeSelected == 6 && g_GameLogic.sceneID == 1 &&
                ((s8)((u8*)&g_Minigame)[0x18F8 + i]) >= 1) {
                shadowOn = 0;
            }
        } else {
            if (g_GameLogic.secondaryGameMode != 0xE && g_Stats.replayInd == 0 && i != 0 && i != 9 &&
                g_GameLogic.sceneID == 1) {
                shadowOn = 0;
            }
        }
        if (obj[0x25D] == 2) {
            shadowOn = 0;
        }

        state = fn_800111D8(obj);
        if (shadowOn != 0) {
            ((u8*)*(void**)state)[0x98] |= 4;
        } else {
            ((u8*)*(void**)state)[0x98] &= 0xFB;
        }
    }
}

// .text:0x0006B5D8 size:0x9C
BOOL loadMVPMaybe(void) {
    switch (animRelated[0x9A]) {
    case 0:
        hugeAnimStruct[0x2D77] = 0;
        sound_crowd_EffectsStruct._2C = 0;
        animRelated[0x9A] = 1;
        break;
    case 1:
        if (fn_80016344((s8)StatsScreenScores.mvpCharID, 9, 0, 0) != 0) {
            return TRUE;
        }
        break;
    }
    return FALSE;
}

// .text:0x0006B4C8 size:0x110
BOOL fn_3_6B4C8(void) {
    int team;
    int i;
    s32 value;

    if (animRelated[0x9A] == 0) {
        fn_80011A60();
        hugeAnimStruct[0x2D77] = 0;
        animRelated[0x9A] = 1;
    }

    team = g_d_GameSettings.humanTeamNumber;
    value = *(s32*)((u8*)&Static_Stats_Tables + team * 4 + 0x46E0);
    if (fn_80016344(value, 12, 1, ((u8*)&Static_Stats_Tables)[team + 0x4709]) != 0) {
        for (i = 0; i < 9; i++) {
            u8* obj = ((u8**)&hugeAnimStruct[0x2C50])[i];
            if ((s8)obj[0x252] == *(s32*)((u8*)&Static_Stats_Tables + g_d_GameSettings.humanTeamNumber * 4 + 0x46E0)) {
                *(u8**)&hugeAnimStruct[0x2C50 + i * 4] = &hugeAnimStruct[0x29D4];
                *(s32*)&hugeAnimStruct[0x2C80] = 0;
                break;
            }
        }
        return TRUE;
    }
    return FALSE;
}
