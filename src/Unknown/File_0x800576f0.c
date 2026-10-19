#define AIPOSSWAPINPUTS_LOCAL_VIEW
#include "Unknown/File_0x800576f0.h"
#include "static/UnknownHomes_Static.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80056ae4.h"
#include "Unknown/File_0x80056f70.h"
#include "Unknown/File_0x800572c0.h"
#include "Unknown/orderchange.h"
#include "Unknown/sub.h"
#include "challenge/challenge_progress.h"

// The team-management state this unit touches; see AIPOSSWAPINPUTS_LOCAL_VIEW
// for why the full-size type is not used.
extern struct {
    /* 0x0000 */ u8 _0000[0xCF7A];
    /* 0xCF7A */ u8 textBlocks[3];          // freed with text_freeBlock on scene reset
    /* 0xCF7D */ u8 _CF7D[0xCF92 - 0xCF7D];
    /* 0xCF92 */ E(u8, CHECK_STARS_SCENE) challengeCheckStarsMenuSceneLoadingNumber;
    /* 0xCF93 */ u8 challengeCheckStarsMenuLoadingInd;
    /* 0xCF94 */ u8 unkCF94;                // set on scene reset; the exit path frees the scene
    /* 0xCF95 */ s8 checkStarsMenuPrevCharIndex;
    /* 0xCF96 */ s8 checkStarsMenuCharIndex;
    /* 0xCF97 */ s8 checkStarsMenuPrevStarIndex;
    /* 0xCF98 */ s8 checkStarsMenuStarIndex;
    /* 0xCF99 */ u8 _CF99[0xCF9C - 0xCF99];
    /* 0xCF9C */ s16 playerIndexNoVariants;
} aiPosSwapInputs;

#define SCENE_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)

void challengeCheckStarsMenuLoading(void) {
    MenuScene *scene = (MenuScene *)currentDrawingItem;
    int i;

    switch (aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber) {
    case CHECK_STARS_SCENE_LOAD:
        if (aiPosSwapInputs.challengeCheckStarsMenuLoadingInd == 0) {
            SCENE_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, 30)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
            challengeDrawStarsOnMissionMenu();
            drawStarProgressionMenu(scene);
            if (challengeStarRelatedInd(aiPosSwapInputs.playerIndexNoVariants, aiPosSwapInputs.checkStarsMenuStarIndex) != 0) {
                SCENE_RECORD(scene, 35)->flags |= UI_FLAG_VISIBLE;
                SCENE_RECORD(scene, 35)->frame = 0;
                SCENE_RECORD(scene, 35)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, 69)->frame = 0x10000;
            }
            aiPosSwapInputs.challengeCheckStarsMenuLoadingInd = TRUE;
        }
        if (aiPosSwapInputs.challengeCheckStarsMenuLoadingInd != 0) {
            if (maybeCheckAndResetGrapicsElement(scene, 1, 0x0A) != FALSE) {
                aiPosSwapInputs.challengeCheckStarsMenuLoadingInd = FALSE;
                aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_NONE;
            }
        }
        break;

    case CHECK_STARS_SCENE_EXIT:
        if (aiPosSwapInputs.challengeCheckStarsMenuLoadingInd == 0) {
            SCENE_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
            SCENE_RECORD(scene, 30)->playMode = UI_PLAY_BACKWARD;
            aiPosSwapInputs.challengeCheckStarsMenuLoadingInd = TRUE;
        }
        if (aiPosSwapInputs.challengeCheckStarsMenuLoadingInd != 0) {
            int a = maybeCheckAndResetGrapicsElement(scene, 1, 0) != FALSE;
            int b = maybeCheckAndResetGrapicsElement(scene, 0x1E, 0) != FALSE;

            if (a + b == 2) {
                aiPosSwapInputs.unkCF94 = TRUE;
                aiPosSwapInputs.challengeCheckStarsMenuLoadingInd = FALSE;
                aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_NONE;
                for (i = 0; i < 3; i++) {
                    text_freeBlock(aiPosSwapInputs.textBlocks[i]);
                }
                fn_8000F8F4(scene);
            }
        }
        break;

    case CHECK_STARS_SCENE_MOVE_IN_CHAR_LIST:
        if (aiPosSwapInputs.challengeCheckStarsMenuLoadingInd == 0) {
            SCENE_RECORD(scene, aiPosSwapInputs.checkStarsMenuCharIndex + 3)->frame = 0;
            SCENE_RECORD(scene, aiPosSwapInputs.checkStarsMenuCharIndex + 3)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, aiPosSwapInputs.checkStarsMenuPrevCharIndex + 3)->frame = 0x000A0000;
            SCENE_RECORD(scene, aiPosSwapInputs.checkStarsMenuPrevCharIndex + 3)->playMode = UI_PLAY_BACKWARD;
            drawStarProgressionMenu(scene);
            if (challengeStarRelatedInd(aiPosSwapInputs.playerIndexNoVariants, aiPosSwapInputs.checkStarsMenuStarIndex) != 0) {
                SCENE_RECORD(scene, 35)->flags |= UI_FLAG_VISIBLE;
                SCENE_RECORD(scene, 35)->frame = 0;
                SCENE_RECORD(scene, 35)->playMode = UI_PLAY_FORWARD;
                SCENE_RECORD(scene, 69)->frame = 0x10000;
            } else {
                SCENE_RECORD(scene, 35)->flags &= ~UI_FLAG_VISIBLE;
                SCENE_RECORD(scene, 69)->frame = 0;
            }
            aiPosSwapInputs.challengeCheckStarsMenuLoadingInd = TRUE;
        }
        if (aiPosSwapInputs.challengeCheckStarsMenuLoadingInd != 0) {
            aiPosSwapInputs.challengeCheckStarsMenuLoadingInd = FALSE;
            aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_NONE;
        }
        break;

    case CHECK_STARS_SCENE_MOVE_IN_STAR_LIST:
        someChallengeStarFunction2(scene);
        break;

    case CHECK_STARS_SCENE_LOAD_CHAR_VIEW:
        if (aiPosSwapInputs.challengeCheckStarsMenuLoadingInd == 0) {
            SCENE_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, 69)->flags |= UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 69)->playMode = UI_PLAY_FORWARD;
            aiPosSwapInputs.challengeCheckStarsMenuLoadingInd = TRUE;
        }
        if (aiPosSwapInputs.challengeCheckStarsMenuLoadingInd != 0) {
            if (maybeCheckAndResetGrapicsElement(scene, 1, 0x14) != FALSE) {
                aiPosSwapInputs.challengeCheckStarsMenuLoadingInd = FALSE;
                aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_NONE;
            }
        }
        break;

    case CHECK_STARS_SCENE_EXIT_CHAR_VIEW:
        someChallengeStarFunction(scene);
        break;

    default:
        break;
    }

    if (aiPosSwapInputs.unkCF94 != 0) {
        aiPosSwapInputs.unkCF94 = FALSE;
        removeGraphicsElementFromScene((DrawingSceneStruct *)scene);
        removeCurrentDrawingItem();
    }
}
