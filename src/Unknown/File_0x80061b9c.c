#define AIPOSSWAPINPUTS_LOCAL_VIEW
#include "Unknown/File_0x80061b9c.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/team_management_screens.h"
#include "game/UnknownHomes_Game.h"
#include "game/challenge/challenge_state.h"
#include "static/UnknownHomes_Static.h"
#include "text/text.h"

// Only the team-management state this unit touches; see
// AIPOSSWAPINPUTS_LOCAL_VIEW for why the full-size type is not used.
extern struct {
    /* 0x0000 */ u8 _0000[0xCF3B];
    /* 0xCF3B */ s8 playerWhoPaused;
    /* 0xCF3C */ u8 _CF3C[0xCF45 - 0xCF3C];
    /* 0xCF45 */ u8 removeSceneRequested;
    /* 0xCF46 */ u8 _CF46[0xCFA2 - 0xCF46];
    /* 0xCFA2 */ u8 teamMenuType[4];
} aiPosSwapInputs;

extern u8 lineUpInfoStruct[];
extern UIRecordDescriptor lbl_801000A8[];
extern UIRecordDescriptor lbl_801041C8[];

typedef struct {
    /* 0x00 */ u8 _00[0x14];
    /* 0x14 */ u16 firstHandle;
} TeamManagementScene;

// The scene's records are graphicsRelatedArray[firstHandle + k].
#define RECORD(k) ((UIRecord*)graphicsRelatedArray[((TeamManagementScene*)scene)->firstHandle + (k)].object)

void teamManagementGraphics_initialLoad(void) {
    DrawingSceneStruct* scene = currentDrawingItem;
    s8 playerWho;
    s32 frameIndex;
    s32 i;
    BOOL cond;

    aiPosSwapInputs.removeSceneRequested = 0;
    playerWho = aiPosSwapInputs.playerWhoPaused;

    if (g_d_GameSettings._06 != 2) {
        addGraphicsElementToScene(scene, lbl_801000A8);
        RECORD(16)->frame = Static_Stats_Tables.playerNumberByPort[0] << 16;

        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
            RECORD(17)->frame = ((Static_Stats_Tables.playerNumberByPort[0] == 0) + 4) << 16;
        } else {
            RECORD(17)->frame = Static_Stats_Tables.playerNumberByPort[1] << 16;
        }

        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            for (i = 0; i < 9; i += 3) {
                RECORD(i + 0x164)->flags &= ~UI_FLAG_VISIBLE;
                RECORD(i + 0x165)->flags &= ~UI_FLAG_VISIBLE;
                RECORD(i + 0x166)->flags &= ~UI_FLAG_VISIBLE;
            }
            RECORD(0x1D2)->flags &= ~UI_FLAG_VISIBLE;
            teamManagementGraphics_battingOrderInfo((MenuScene*)scene);
            teamManagementGraphics_fieldingAlignmentInfo((MenuScene*)scene);
        } else {
            RECORD(0x1D2)->flags &= ~UI_FLAG_VISIBLE;
            challengeTeamManagementRelated((MenuScene*)scene);

            for (i = 0; i < 9; i++) {
                s8 lineupSlot = (s8)lineUpInfoStruct[i * 4 + 2];
                s16 charID = inMemRoster[0][i].stats.CharID;
                BOOL starred;

                load_Icon(scene, 0x10A + lineupSlot, 1, 0x83, charID);
                RECORD(i + 0xE6)->flags &= ~UI_FLAG_VISIBLE;

                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                    starred = g_Challenge.charIsSuperstar[charID];
                } else {
                    starred = Static_Stats_Tables.charIsStarred[0][i];
                }

                if (starred != 0) {
                    RECORD(lineupSlot + 0x140)->playMode = 1;
                    RECORD(lineupSlot + 0x152)->flags |= UI_FLAG_VISIBLE;
                    RECORD(lineupSlot + 0x152)->frame = 0;
                    RECORD(lineupSlot + 0x152)->playMode = 1;
                } else {
                    RECORD(lineupSlot + 0x152)->flags &= ~UI_FLAG_VISIBLE;
                }

                RECORD(i + 0x12E)->flags &= ~UI_FLAG_VISIBLE;
                RECORD(i + 0xF8)->elementIndex = Static_Stats_Tables.playerNumberByPort[0] + 0x1E;
            }

            RECORD(23)->flags &= ~UI_FLAG_VISIBLE;
        }
    } else {
        addGraphicsElementToScene(scene, lbl_801041C8);

        if (g_d_GameSettings.home_AwaySetting != 0) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE &&
                g_Challenge.opponentCaptainCharID == 0x13) {
                cond = playerWho != 0;
            } else {
                cond = playerWho == 0;
            }
        } else {
            cond = playerWho != 0;
        }

        if (cond) {
            RECORD(6)->flags &= ~UI_FLAG_VISIBLE;
            RECORD(9)->flags &= ~UI_FLAG_VISIBLE;
            RECORD(7)->frame = (Static_Stats_Tables.teamName[playerWho] & 3) << 16;
            RECORD(10)->frame = (Static_Stats_Tables.teamName[playerWho] & 3) << 16;
        } else {
            RECORD(7)->flags &= ~UI_FLAG_VISIBLE;
            RECORD(10)->flags &= ~UI_FLAG_VISIBLE;
            RECORD(6)->frame = (Static_Stats_Tables.teamName[playerWho] & 3) << 16;
            RECORD(9)->frame = (Static_Stats_Tables.teamName[playerWho] & 3) << 16;
        }

        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && playerWho != 0) {
            frameIndex = Static_Stats_Tables.playerNumberByPort[playerWho];
            if (frameIndex == -1) {
                frameIndex = (playerWho != 0) + 4;
            } else {
                frameIndex += 4;
            }
        } else {
            frameIndex = Static_Stats_Tables.playerNumberByPort[playerWho];
        }

        RECORD(12)->frame = frameIndex << 16;
        RECORD(2)->frame = 0x140000;
        RECORD(2)->playMode = 0;
        RECORD(4)->frame = 0x140000;
        RECORD(4)->playMode = 0;
        RECORD(5)->frame = 0x180000;
        RECORD(5)->playMode = 0;
        RECORD(8)->frame = 0xA0000;
        RECORD(8)->playMode = 0;

        if (aiPosSwapInputs.teamMenuType[playerWho] == 1) {
            RECORD(80)->elementIndex = 0x28;
            RECORD(1)->elementIndex = 0x47;
            RECORD(1)->frame = 0x140000;
            RECORD(1)->playMode = 0;
        }

        teamManagementGraphics_battingOrderScreen((MenuScene*)scene);
        teamManagementGraphics_fieldingAlignmentScreen((MenuScene*)scene);
    }

    currentDrawingItem->func = teamManagementGraphics_steadyState;
}
