#include "Unknown/File_0x80056ae4.h"
#include "challenge/challenge_progress.h"

#include "Unknown/sub.h"
#include "game/UnknownHomes_Game.h"
#include "game/character_stats.h"
#include "game/challenge/challenge_state.h"
#include "game/challenge/star_mission_data.h"
#include "static/UnknownHomes_Static.h"
#include "text/text.h"

s16 challenge_getStarRank(int charID);

#define REC(scene, k) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (k)].object)

void drawStarProgressionMenu(MenuScene* scene) {
    CharacterStats* rosterRow;
    CharStaticIndex* staticIdx;
    s16 charID;
    s32 variantClass;
    s32 starClass;
    u8 fieldValue;
    u16 descTextID;
    s32 rank;
    s32 i;

    rosterRow = &((CharacterStats*)inMemRoster)[aiPosSwapInputs.checkStarsMenuCharIndex];
    charID = *(s16*)((u8*)rosterRow + 0x24);
    staticIdx = &characterStaticIndexes[charID];
    aiPosSwapInputs.playerIndexNoVariants = staticIdx->trackerIdx;

    variantClass = g_Challenge.characters[aiPosSwapInputs.playerIndexNoVariants].variantClassification;
    fieldValue = ((u8*)&Static_Stats_Tables.characterStats[charID / 9][charID % 9])[0x31];

    starClass = variantClass;
    switch (variantClass) {
    case CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_CAPTAIN:
        aiPosSwapInputs.numberOfChallengeStarsForPlayer = 10;
        starClass = 3;
        break;
    case CHARACTER_VARIANT_CLASSIFICATION_SECONDARY_CAPTAIN:
        aiPosSwapInputs.numberOfChallengeStarsForPlayer = 8;
        starClass = 2;
        break;
    case CHARACTER_VARIANT_CLASSIFICATION_UNIQUE_NON_CAPTAIN:
        aiPosSwapInputs.numberOfChallengeStarsForPlayer = 6;
        starClass = 1;
        break;
    case CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_VARIANT:
        aiPosSwapInputs.numberOfChallengeStarsForPlayer = 4;
        starClass = 0;
        break;
    }

    REC(scene, 31)->frame = starClass << 16;
    REC(scene, 32)->playMode = 1;
    REC(scene, 36)->frame = fieldValue << 16;
    REC(scene, 37)->frame = charID << 16;
    REC(scene, 38)->frame = (4 - determineIfMissionDescriptionIsShown(charID)) << 16;

    if ((s8)g_Challenge.characters[aiPosSwapInputs.playerIndexNoVariants].inGameMissionTracker[0].shownOnPauseMenu != 0) {
        descTextID = starMissionDisplayRules[staticIdx->requirementRow][0].textID;
    } else {
        if (starMissionDisplayRules[staticIdx->requirementRow][0].minScoutRow > g_Challenge.difficulty) {
            descTextID = 0x1C6;
        } else {
            descTextID = 0x1C5;
        }
    }

    if (aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber == CHECK_STARS_SCENE_LOAD) {
        aiPosSwapInputs._CF77[3] = text_initializeNewChannel((UnkText988Arg*)scene, 0x4F, 0, 0, charID + 8, 0);
        rank = challenge_getStarRank(aiPosSwapInputs.playerIndexNoVariants);
        aiPosSwapInputs._CF77[4] = text_initializeNewChannel(
            (UnkText988Arg*)scene, 0x50, 1, 0, (s16)starRankTextIDs[staticIdx->requirementRow] + rank, 0);
        aiPosSwapInputs._CF77[5] = text_initializeNewChannel((UnkText988Arg*)scene, 0x51, 0, 0, descTextID, 0);
        screenTextArray.blocks[aiPosSwapInputs._CF77[5]].justify = 1;
    } else {
        text_setPtrToWhereCharsAreStored(aiPosSwapInputs._CF77[3], 0, charID + 8);
        rank = challenge_getStarRank(aiPosSwapInputs.playerIndexNoVariants);
        text_setPtrToWhereCharsAreStored(aiPosSwapInputs._CF77[4], 0, (s16)starRankTextIDs[staticIdx->requirementRow] + rank);
        text_setPtrToWhereCharsAreStored(aiPosSwapInputs._CF77[5], 0, descTextID);
    }

    for (i = 0; i < aiPosSwapInputs.numberOfChallengeStarsForPlayer; i++) {
        if (challengeStarRelatedInd(aiPosSwapInputs.playerIndexNoVariants, i)) {
            REC(scene, 0x3B + i)->flags |= UI_FLAG_VISIBLE;
            REC(scene, 0x3B + i)->playMode = 1;
        } else {
            REC(scene, 0x3B + i)->flags &= ~UI_FLAG_VISIBLE;
        }
        REC(scene, 0x45 + i)->flags &= ~UI_FLAG_VISIBLE;
        REC(scene, 0x31 + i)->flags &= ~UI_FLAG_VISIBLE;
        REC(scene, 0x45 + i)->frame = 0;
    }
}
