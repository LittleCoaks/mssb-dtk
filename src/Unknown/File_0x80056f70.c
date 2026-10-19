#define AIPOSSWAPINPUTS_LOCAL_VIEW
#include "Unknown/File_0x80056f70.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/challenge/challenge_state.h"
#include "game/challenge/star_mission_data.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/orderchange.h"
#include "Unknown/sub.h"

// The team-management state this unit touches; see AIPOSSWAPINPUTS_LOCAL_VIEW
// for why the full-size type is not used.
extern struct {
    /* 0x0000 */ u8 _0000[0xCF7C];
    /* 0xCF7C */ u8 unkCF7C;                 // text block handed to text_setPtrToWhereCharsAreStored
    /* 0xCF7D */ u8 _CF7D[0xCF92 - 0xCF7D];
    /* 0xCF92 */ u8 challengeCheckStarsMenuSceneLoadingNumber;
    /* 0xCF93 */ u8 challengeCheckStarsMenuLoadingInd;
    /* 0xCF94 */ u8 _CF94[0xCF98 - 0xCF94];
    /* 0xCF98 */ s8 checkStarsMenuStarIndex;
    /* 0xCF99 */ u8 _CF99[0xCF9A - 0xCF99];
    /* 0xCF9A */ u8 numberOfChallengeStarsForPlayer;
    /* 0xCF9B */ u8 _CF9B;
    /* 0xCF9C */ s16 playerIndexNoVariants;
} aiPosSwapInputs;

#define SCENE_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)

void someChallengeStarFunction(MenuScene* scene) {
    s16 requirementRow;
    s16 textID;
    int i;

    if (aiPosSwapInputs.challengeCheckStarsMenuLoadingInd == 0) {
        requirementRow = characterStaticIndexes[aiPosSwapInputs.playerIndexNoVariants].requirementRow;

        SCENE_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;

        for (i = 0; i < aiPosSwapInputs.numberOfChallengeStarsForPlayer; i++) {
            SCENE_RECORD(scene, i + 0x31)->flags &= ~2;
            SCENE_RECORD(scene, i + 0x45)->frame = 0;
            SCENE_RECORD(scene, i + 0x45)->flags &= ~2;
        }

        SCENE_RECORD(scene, 35)->flags &= ~2;
        if (challengeStarRelatedInd(aiPosSwapInputs.playerIndexNoVariants, aiPosSwapInputs.checkStarsMenuStarIndex)) {
            SCENE_RECORD(scene, 35)->flags |= 2;
            SCENE_RECORD(scene, 35)->frame = 0;
            SCENE_RECORD(scene, 35)->playMode = UI_PLAY_FORWARD;

            SCENE_RECORD(scene, aiPosSwapInputs.checkStarsMenuStarIndex + 0x31)->flags |= 2;
            SCENE_RECORD(scene, aiPosSwapInputs.checkStarsMenuStarIndex + 0x31)->frame = 0;
            SCENE_RECORD(scene, aiPosSwapInputs.checkStarsMenuStarIndex + 0x31)->playMode = UI_PLAY_FORWARD;

            SCENE_RECORD(scene, aiPosSwapInputs.checkStarsMenuStarIndex + 0x45)->frame = 0x10000;
        }

        if ((s8)g_Challenge.characters[aiPosSwapInputs.playerIndexNoVariants].inGameMissionTracker[aiPosSwapInputs.checkStarsMenuStarIndex].shownOnPauseMenu != 0) {
            textID = starMissionDisplayRules[requirementRow][aiPosSwapInputs.checkStarsMenuStarIndex].textID;
        } else if (challengeStarRelatedInd(aiPosSwapInputs.playerIndexNoVariants, aiPosSwapInputs.checkStarsMenuStarIndex)) {
            textID = starMissionDisplayRules[requirementRow][aiPosSwapInputs.checkStarsMenuStarIndex].textID;
        } else {
            if (starMissionDisplayRules[requirementRow][aiPosSwapInputs.checkStarsMenuStarIndex].minScoutRow <= g_Challenge.difficulty) {
                textID = 0x1C5;
            } else {
                textID = 0x1C6;
            }
        }

        text_setPtrToWhereCharsAreStored(aiPosSwapInputs.unkCF7C, 0, textID);
        aiPosSwapInputs.challengeCheckStarsMenuLoadingInd = 1;
    }

    if (aiPosSwapInputs.challengeCheckStarsMenuLoadingInd != 0) {
        BOOL reset = maybeCheckAndResetGrapicsElement(scene, 1, 10) != FALSE;
        if (reset == TRUE) {
            aiPosSwapInputs.challengeCheckStarsMenuLoadingInd = 0;
            aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_NONE;
        }
    }
}
