#define TEAM_MANAGEMENT_LOCAL_VIEW
#include "Unknown/File_0x800572c0.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/challenge/challenge_state.h"
#include "game/challenge/star_mission_data.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/sub.h"

// The check-stars menu state this unit touches; see TEAM_MANAGEMENT_LOCAL_VIEW
// for why the full-size type is not used.
extern struct {
    /* 0x0000 */ u8 _0000[0xCF7A];
    /* 0xCF7A */ u8 textBlocks[3];
    /* 0xCF7D */ u8 _CF7D[0xCF92 - 0xCF7D];
    /* 0xCF92 */ u8 challengeCheckStarsMenuSceneLoadingNumber;
    /* 0xCF93 */ u8 challengeCheckStarsMenuLoadingInd;
    /* 0xCF94 */ u8 _CF94[0xCF97 - 0xCF94];
    /* 0xCF97 */ s8 checkStarsMenuPrevStarIndex;
    /* 0xCF98 */ s8 checkStarsMenuStarIndex;
    /* 0xCF99 */ u8 _CF99[0xCF9C - 0xCF99];
    /* 0xCF9C */ s16 playerIndexNoVariants;
} g_TeamManagement;

#define SCENE_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)

void someChallengeStarFunction2(MenuScene* scene) {
    u8 requirementRow;
    u16 textID;

    if (g_TeamManagement.challengeCheckStarsMenuLoadingInd == 0) {
        requirementRow = characterStaticIndexes[g_TeamManagement.playerIndexNoVariants].requirementRow;

        if (challengeStarRelatedInd(g_TeamManagement.playerIndexNoVariants, g_TeamManagement.checkStarsMenuStarIndex)) {
            SCENE_RECORD(scene, 35)->flags |= 2;
            SCENE_RECORD(scene, 35)->frame = 0;
            SCENE_RECORD(scene, 35)->playMode = UI_PLAY_FORWARD;

            SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuStarIndex + 0x31)->flags |= 2;
            SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuStarIndex + 0x31)->frame = 0;
            SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuStarIndex + 0x31)->playMode = UI_PLAY_FORWARD;

            SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuStarIndex + 0x45)->frame = 0x10000;
        } else {
            SCENE_RECORD(scene, 35)->flags &= ~2;
            SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuStarIndex + 0x31)->flags &= ~2;
            SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuStarIndex + 0x45)->frame = 0;
        }

        SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuStarIndex + 0x45)->flags |= 2;
        SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuStarIndex + 0x45)->playMode = UI_PLAY_FORWARD;

        if (challengeStarRelatedInd(g_TeamManagement.playerIndexNoVariants, g_TeamManagement.checkStarsMenuPrevStarIndex)) {
            SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuPrevStarIndex + 0x31)->flags &= ~2;
            SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuPrevStarIndex + 0x27)->frame = 0;
        } else {
            SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuPrevStarIndex + 0x27)->frame = 0;
        }

        SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuPrevStarIndex + 0x45)->flags &= ~2;
        SCENE_RECORD(scene, g_TeamManagement.checkStarsMenuPrevStarIndex + 0x45)->playMode = UI_PLAY_FORWARD;

        if ((s8)g_Challenge.characters[g_TeamManagement.playerIndexNoVariants].inGameMissionTracker[g_TeamManagement.checkStarsMenuStarIndex].shownOnPauseMenu != 0) {
            textID = starMissionDisplayRules[requirementRow][g_TeamManagement.checkStarsMenuStarIndex].textID;
        } else if (challengeStarRelatedInd(g_TeamManagement.playerIndexNoVariants, g_TeamManagement.checkStarsMenuStarIndex)) {
            textID = starMissionDisplayRules[requirementRow][g_TeamManagement.checkStarsMenuStarIndex].textID;
        } else {
            if (starMissionDisplayRules[requirementRow][g_TeamManagement.checkStarsMenuStarIndex].minScoutRow <= g_Challenge.difficulty) {
                textID = 0x1C5;
            } else {
                textID = 0x1C6;
            }
        }

        text_setPtrToWhereCharsAreStored(g_TeamManagement.textBlocks[2], 0, textID);
        g_TeamManagement.challengeCheckStarsMenuLoadingInd = 1;
    }

    if (g_TeamManagement.challengeCheckStarsMenuLoadingInd != 0) {
        g_TeamManagement.challengeCheckStarsMenuLoadingInd = 0;
        g_TeamManagement.challengeCheckStarsMenuSceneLoadingNumber = 0;
    }
}
