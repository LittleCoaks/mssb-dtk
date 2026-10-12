#define SQRT2_LINKAGE static
#include "game/practice/practice_menu.h"
#include "game/UnknownHomes_Game.h"
#include "game/practice/guided_practice.h"
#include "game/practice/batting_fielding_practice.h"
#include "game/practice/practice_scene.h"
#include "game/match_setup/roster_init.h"
#include "game/match_setup/pause_menu.h"
#include "game/sound/m_sound.h"
#include "static/UnknownHomes_Static.h"
#include "stl/stdlib.h"
#include "Dolphin/stl.h"
#include "musyx/musyx.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80014f40.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80062a94.h"
#include "text/text_channel.h"

extern u8 hugeAnimStruct[];
extern u8 lbl_800EFBA4[];
extern u8 lbl_8037169C[];
extern u8 lbl_80366158[];
extern u8 practice_subMenu_length[][5];
extern u8 practiceMenu_typeIconOrder[];
extern u8 animRelated[];
extern u8 practiceMenu_baserunningPreviewChars[];
extern BOOL practice_loadAllGraphics(int arg);
extern void css_initValues(int a, int b, int c, int d, int e, int f);
extern void cssLoadingRelated_1(int a, int b, int c, int d, int e, int f);
extern int cssCursorOnBottomControl_maybe(int team, int buttons, int newButtons, int other, int extra);
extern u8 charSelectStruct[];
extern void minigameCharLoadQueueUpdate(void);
extern void addOrRemoveCharacterToTeam(int team, int charID, BOOL add);
extern void playPlayerSelectedSound(int charID);
extern int fn_8004FD64(int team);
extern void fn_80062A74(void);
extern void fn_3_5B408(void);
extern void fn_3_5B368(void);
extern int fn_3_5B220(int arg0);
extern int exitMenu_main(int buttons);
extern void fn_8004CC18(void);

#define ANIM_BYTE(offset) (hugeAnimStruct[(offset)])
#define CHAR_STATS(charID) (((CharacterStats*)&Static_Stats_Tables)[(charID)])
#define PLAYER_KEY(charID) (CHAR_STATS(charID).stats.FieldingArm * 2 + CHAR_STATS(charID).stats.BattingStance)

#pragma dont_inline on
// .text:0x000B5D78 size:0x104
void practiceMenu(void) {
    if (g_Practice.returnToPracticeMenuState != 0) {
        switch (g_Practice.returnToPracticeMenuState) {
        case 1:
            stadiumMusic(-1);
            g_Practice.returnToPracticeMenuState = 2;
            sound_crowd_EffectsStruct._2C = 0;
            sound_crowd_EffectsStruct._2A = 1;
            sound_crowd_EffectsStruct._24 = 1;
            /* fallthrough */
        case 2:
            g_Practice.returnToPracticeMenuState = 3;
            break;
        default:
            insertGraphicDrawingFunction(startMenuMusic, 1);
            g_Practice.returnToPracticeMenuState = 0;
            break;
        }
    } else {
        if (g_Practice.practiceMenu_framesOnCurrMenuScreen < 0xFFFE) {
            g_Practice.practiceMenu_framesOnCurrMenuScreen++;
        } else {
            g_Practice.practiceMenu_framesOnCurrMenuScreen = 0xFFFF;
        }
        switch (g_Practice.practiceType_1) {
        case 0:
            practice_mainMenu_stateHandling();
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            practice_subMenu_stateHandling();
            break;
        case 6:
            practiceRelatedMenu();
            break;
        }
    }
}
#pragma dont_inline reset

// .text:0x000B5D4C size:0x2C
void practiceMenu_setScreen(int screen) {
    g_Practice.practiceType_1 = screen;
    g_Practice.practiceState = PRACTICE_STATE_0;
    pauseControl.state = 0;
    g_Practice.practiceMenu_framesOnCurrMenuScreen = 0;
    g_Practice.framesInCurrTransitionState = 0;
}

// .text:0x000B5CB4 size:0x98
void unused_MaybePractice(void) {
    switch (g_Practice.returnToPracticeMenuState) {
    case 1:
        stadiumMusic(-1);
        g_Practice.returnToPracticeMenuState = 2;
        sound_crowd_EffectsStruct._2C = 0;
        sound_crowd_EffectsStruct._2A = 1;
        sound_crowd_EffectsStruct._24 = 1;
        /* fallthrough */
    case 2:
        g_Practice.returnToPracticeMenuState = 3;
        break;
    default:
        insertGraphicDrawingFunction(startMenuMusic, 1);
        g_Practice.returnToPracticeMenuState = 0;
        break;
    }
}

// .text:0x000B5818 size:0x49C
void practice_mainMenu_stateHandling(void) {
    switch (g_Practice.practiceState) {
    case PRACTICE_STATE_0:
        g_Practice.subMenuCursor = 0;
        g_Practice.framesSincePracticeMenuDefaultTransition = 0;
        practice_loadCharacterData();
        if (g_Practice.showMenuIntro != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_1);
        } else {
            updatePracticeTransitionState(PRACTICE_STATE_2);
        }
        g_Practice.showMenuIntro = FALSE;
        break;
    case PRACTICE_STATE_1:
        if (ANIM_BYTE(0x2D7B) >= 10) {
            updatePracticeTransitionState(PRACTICE_STATE_2);
        }
        break;
    case PRACTICE_STATE_2:
        changeScene(6, 6);
        updatePracticeTransitionState(PRACTICE_STATE_3);
        break;
    case PRACTICE_STATE_3:
        if (g_Practice.framesSincePracticeMenuDefaultTransition > 30) {
            updatePracticeTransitionState(PRACTICE_STATE_4);
        }
        break;
    case PRACTICE_STATE_4: {
        InputStruct* input = &g_Controls[g_Practice.homeAway];
        int practiceType;

        if (animRelated[0xBB] == 0) {
            if (input->newButtonInput & INPUT_BUTTON_A) {
                updatePracticeTransitionState(PRACTICE_STATE_5);
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, SND_STUDIO_DEFAULT);
            } else if (input->newButtonInput & INPUT_BUTTON_B) {
                fn_3_5B408();
                updatePracticeTransitionState(PRACTICE_STATE_7);
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
            } else if (input->_08 & INPUT_BUTTON_LEFT) {
                if (g_Practice.practiceType != PRACTICE_TYPE_PITCHING) {
                    g_Practice.practiceType--;
                } else {
                    g_Practice.practiceType = PRACTICE_TYPE_FREEPLAY;
                }
                animRelated[0xBD] = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            } else if (input->_08 & INPUT_BUTTON_RIGHT) {
                g_Practice.practiceType++;
                if (g_Practice.practiceType >= 5) {
                    g_Practice.practiceType = PRACTICE_TYPE_PITCHING;
                }
                animRelated[0xBD] = 2;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            }
        }
        practiceType = g_Practice.practiceType;
        g_Practice.framesSincePracticeMenuDefaultTransition = 0;
        g_Practice.practiceType_2 = practiceMenu_typeIconOrder[practiceType];
        animRelated[0xB9] = practiceType;
        break;
    }
    case PRACTICE_STATE_5:
        if (g_Practice.menuGraphicsLoaded != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_6);
        }
        break;
    case PRACTICE_STATE_6:
        if (animRelated[0xBB] != 0) {
            break;
        }
        switch (g_Practice.practiceType_2) {
        case PRACTICE_TYPE_PITCHING:
            practiceMenu_setScreen(1);
            break;
        case PRACTICE_TYPE_BATTING:
            practiceMenu_setScreen(2);
            break;
        case PRACTICE_TYPE_FIELDING:
            practiceMenu_setScreen(3);
            break;
        case PRACTICE_TYPE_BASERUNNING:
            practiceMenu_setScreen(4);
            break;
        case PRACTICE_TYPE_FREEPLAY:
            practiceMenu_setScreen(5);
            break;
        }
        break;
    case PRACTICE_STATE_7: {
        int result = exitMenu_main(g_Controls[lbl_80366158[0x27]].newButtonInput);

        switch (result) {
        case 1:
            if (g_Practice.progressNeedsSave != 0) {
                fn_8004CC18();
                fn_3_5B368();
            } else {
                changeScene(4, 6);
            }
            updatePracticeTransitionState(PRACTICE_STATE_8);
            break;
        case 2:
            updatePracticeTransitionState(PRACTICE_STATE_4);
            break;
        }
        break;
    }
    case PRACTICE_STATE_8:
        if (g_Practice.menuGraphicsLoaded == 0) {
            break;
        }
        if (g_Practice.progressNeedsSave != 0) {
            if (fn_3_5B220(3) != 0) {
                changeScene(4, 6);
                g_Practice.progressNeedsSave = FALSE;
            }
        } else if (lbl_8037169C[0x13] != 0) {
            fn_80062A74();
            fn_8004CC18();
            switchSecondaryGameMode(0x11);
            ANIM_BYTE(0x307A) = FALSE;
        }
        break;
    default:
        break;
    }

    if (g_Practice.menuGraphicsLoaded == 0) {
        if (practice_loadAllGraphics(g_GameLogic.teamFielding)) {
            g_Practice.menuGraphicsLoaded = TRUE;
        }
    }
}

// .text:0x000B5694 size:0x184
void notReferenced(void) {
    InputStruct* input = &g_Controls[g_Practice.homeAway];
    int practiceType;

    if (animRelated[0xBB] == 0) {
        if (input->newButtonInput & INPUT_BUTTON_A) {
            updatePracticeTransitionState(PRACTICE_STATE_5);
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, SND_STUDIO_DEFAULT);
        } else if (input->newButtonInput & INPUT_BUTTON_B) {
            fn_3_5B408();
            updatePracticeTransitionState(PRACTICE_STATE_7);
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
        } else if (input->_08 & INPUT_BUTTON_LEFT) {
            if (g_Practice.practiceType != PRACTICE_TYPE_PITCHING) {
                g_Practice.practiceType--;
            } else {
                g_Practice.practiceType = PRACTICE_TYPE_FREEPLAY;
            }
            animRelated[0xBD] = 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        } else if (input->_08 & INPUT_BUTTON_RIGHT) {
            g_Practice.practiceType++;
            if (g_Practice.practiceType >= 5) {
                g_Practice.practiceType = PRACTICE_TYPE_PITCHING;
            }
            animRelated[0xBD] = 2;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        }
    }
    practiceType = g_Practice.practiceType;
    g_Practice.practiceType_2 = practiceMenu_typeIconOrder[practiceType];
    animRelated[0xB9] = practiceType;
}

// .text:0x000B51E4 size:0x4B0
void practice_subMenu_stateHandling(void) {
    switch (g_Practice.practiceState) {
    case PRACTICE_STATE_0:
        g_Practice.subMenuGraphicsLoaded = FALSE;
        ANIM_BYTE(0x2D77) = FALSE;
        ANIM_BYTE(0x2D7B) = FALSE;
        ANIM_BYTE(0x2D7C) = FALSE;
        practice_loadCharacterData();
        if (g_Practice.practiceType_2 == PRACTICE_TYPE_PITCHING) {
            practice_loadCharacter(0, 0, 0, -1);
        } else if (g_Practice.practiceType_2 == PRACTICE_TYPE_BATTING) {
            practice_loadCharacter(0, 0, 1, -1);
            practice_loadCharacter(1, 0, 0, -1);
        } else if (g_Practice.practiceType_2 == PRACTICE_TYPE_FIELDING) {
            practice_loadCharacter(0, 0, 0, -1);
            practice_loadCharacter(1, 0, 1, -1);
        } else if (g_Practice.practiceType_2 == PRACTICE_TYPE_BASERUNNING) {
            practice_loadCharacter(1, 0, practiceMenu_baserunningPreviewChars[1], -1);
            practice_loadCharacter(1, 1, practiceMenu_baserunningPreviewChars[2], -1);
            practice_loadCharacter(1, 2, practiceMenu_baserunningPreviewChars[3], -1);
        }
        g_Practice.framesSincePracticeMenuDefaultTransition = 0;
        updatePracticeTransitionState(PRACTICE_STATE_1);
        break;
    case PRACTICE_STATE_1:
        if (g_Practice.menuGraphicsLoaded != 0 && g_Practice.framesSincePracticeMenuDefaultTransition > 30) {
            updatePracticeTransitionState(PRACTICE_STATE_2);
        }
        break;
    case PRACTICE_STATE_2: {
        InputStruct* input = &g_Controls[g_Practice.homeAway];
        int count = practice_subMenu_length[g_Practice.practiceType_2][0];

        if (input->newButtonInput & INPUT_BUTTON_A) {
            g_Practice.practiceLevel = practice_subMenu_length[g_Practice.practiceType_2][g_Practice.subMenuCursor + 1];
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, SND_STUDIO_DEFAULT);
            updatePracticeTransitionState(PRACTICE_STATE_3);
        } else if (input->newButtonInput & INPUT_BUTTON_B) {
            updatePracticeTransitionState(PRACTICE_STATE_5);
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
        } else if (input->_08 & INPUT_BUTTON_UP) {
            if (g_Practice.subMenuCursor != 0) {
                g_Practice.subMenuCursor--;
            } else {
                g_Practice.subMenuCursor = count - 1;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        } else if (input->_08 & INPUT_BUTTON_DOWN) {
            g_Practice.subMenuCursor++;
            if (g_Practice.subMenuCursor >= count) {
                g_Practice.subMenuCursor = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        }
        break;
    }
    case PRACTICE_STATE_3:
        g_Practice.framesSincePracticeMenuDefaultTransition = 0;
        updatePracticeTransitionState(PRACTICE_STATE_4);
        break;
    case PRACTICE_STATE_4:
        if (g_Practice.subMenuGraphicsLoaded == 0) {
            g_Practice.framesSincePracticeMenuDefaultTransition = 0;
            break;
        }
        if (g_Practice.framesSincePracticeMenuDefaultTransition < 30) {
            break;
        }
        if (g_Practice.framesSincePracticeMenuDefaultTransition == 30) {
            if (g_Practice.practiceType_2 != PRACTICE_TYPE_FREEPLAY) {
                changeScene(3, 6);
            }
            break;
        }
        if (lbl_8037169C[0x13] == 0 && g_Practice.practiceType_2 != PRACTICE_TYPE_FREEPLAY) {
            break;
        }
        switch (g_Practice.practiceType_2) {
        case PRACTICE_TYPE_PITCHING:
            switchSecondaryGameMode(0xB);
            break;
        case PRACTICE_TYPE_BATTING:
            switchSecondaryGameMode(0xC);
            break;
        case PRACTICE_TYPE_FIELDING:
            switchSecondaryGameMode(0xD);
            break;
        case PRACTICE_TYPE_BASERUNNING:
            switchSecondaryGameMode(0xE);
            break;
        case PRACTICE_TYPE_FREEPLAY:
            practiceMenu_setScreen(6);
            break;
        }
        if (g_Practice.practiceType_2 != PRACTICE_TYPE_FREEPLAY) {
            fn_80062A74();
        }
        setTutorialState(TUTORIAL_STATE_0);
        break;
    case PRACTICE_STATE_5:
        if (g_Practice.subMenuGraphicsLoaded != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_6);
        }
        break;
    case PRACTICE_STATE_6:
        g_Practice.framesSincePracticeMenuDefaultTransition = 0;
        updatePracticeTransitionState(PRACTICE_STATE_7);
        break;
    case PRACTICE_STATE_7:
        if (g_Practice.framesSincePracticeMenuDefaultTransition >= 15) {
            practiceMenu_setScreen(0);
        }
        break;
    default:
        break;
    }

    if (g_Practice.menuGraphicsLoaded == 0) {
        if (practice_loadAllGraphics(g_GameLogic.teamFielding)) {
            g_Practice.menuGraphicsLoaded = TRUE;
        }
    } else if (g_Practice.subMenuGraphicsLoaded == 0) {
        if (practice_loadAllGraphics(g_GameLogic.teamFielding)) {
            g_Practice.subMenuGraphicsLoaded = TRUE;
        }
    }
}

// .text:0x000B5090 size:0x154
void unref(void) {
    InputStruct* input = &g_Controls[g_Practice.homeAway];
    int count = practice_subMenu_length[g_Practice.practiceType_2][0];

    if (input->newButtonInput & INPUT_BUTTON_A) {
        g_Practice.practiceLevel = practice_subMenu_length[g_Practice.practiceType_2][g_Practice.subMenuCursor + 1];
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, SND_STUDIO_DEFAULT);
        updatePracticeTransitionState(PRACTICE_STATE_3);
    } else if (input->newButtonInput & INPUT_BUTTON_B) {
        updatePracticeTransitionState(PRACTICE_STATE_5);
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
    } else if (input->_08 & INPUT_BUTTON_UP) {
        if (g_Practice.subMenuCursor != 0) {
            g_Practice.subMenuCursor--;
        } else {
            g_Practice.subMenuCursor = count - 1;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
    } else if (input->_08 & INPUT_BUTTON_DOWN) {
        g_Practice.subMenuCursor++;
        if (g_Practice.subMenuCursor >= count) {
            g_Practice.subMenuCursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
    }
}

// .text:0x000B4C40 size:0x450
void practiceRelatedMenu(void) {
    if (g_GameLogic._125 <= 2) {
        g_Minigame.selectSlots[0].charReadyPrevInd = g_Minigame.selectSlots[0].charReadyInd;
        g_Minigame.selectSlots[0].charReadyInd = TRUE;
        g_Minigame.selectSlots[1].charReadyPrevInd = g_Minigame.selectSlots[1].charReadyInd;
        g_Minigame.selectSlots[1].charReadyInd = TRUE;
        g_Minigame.selectSlots[2].charReadyPrevInd = g_Minigame.selectSlots[2].charReadyInd;
        g_Minigame.selectSlots[2].charReadyInd = TRUE;
        g_Minigame.selectSlots[3].charReadyPrevInd = g_Minigame.selectSlots[3].charReadyInd;
        g_Minigame.selectSlots[3].charReadyInd = TRUE;
    }

    switch (g_Practice.practiceState) {
    case PRACTICE_STATE_0: {
        int slots[4];

        slots[0] = FALSE;
        slots[1] = FALSE;
        slots[2] = FALSE;
        slots[3] = FALSE;
        slots[g_Practice.homeAway] = TRUE;
        css_initValues(slots[0], slots[1], slots[2], slots[3], TRUE, TRUE);
        cssLoadingRelated_1(0, 0, 0, 0, 0, 0);
        g_Minigame.selectSlots[0].loadedCharID = CHAR_ID_NONE;
        g_Minigame.battingHandedness[0] = PLAYER_KEY(g_Minigame.selectSlots[0].charID);
        g_Minigame.selectSlots[0].confirmedInd = 0;
        g_Minigame.charChangeFrames[0] = 20;
        g_Minigame.selectSlots[1].loadedCharID = CHAR_ID_NONE;
        g_Minigame.selectSlots[1].confirmedInd = 0;
        g_Minigame.charChangeFrames[1] = 20;
        g_Minigame.battingHandedness[1] = PLAYER_KEY(g_Minigame.selectSlots[1].charID);
        g_Minigame.selectSlots[2].loadedCharID = CHAR_ID_NONE;
        g_Minigame.selectSlots[2].confirmedInd = 0;
        g_Minigame.charChangeFrames[2] = 20;
        g_Minigame.battingHandedness[2] = PLAYER_KEY(g_Minigame.selectSlots[2].charID);
        g_Minigame.selectSlots[3].loadedCharID = CHAR_ID_NONE;
        g_Minigame.selectSlots[3].confirmedInd = 0;
        g_Minigame.charChangeFrames[3] = 20;
        g_Minigame.battingHandedness[3] = PLAYER_KEY(g_Minigame.selectSlots[3].charID);
        ANIM_BYTE(0x2D77) = FALSE;
        ANIM_BYTE(0x307A) = 5;
        g_Minigame.charLoadSlot = -1;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_Practice.characterLoadStarted = FALSE;
        g_Practice.practiceState++;
        g_Minigame.charLoadPending[0] = TRUE;
        g_Minigame.charLoadPending[1] = TRUE;
        g_Minigame.charLoadPending[2] = TRUE;
        g_Minigame.charLoadPending[3] = TRUE;
        break;
    }
    case PRACTICE_STATE_1: {
        changeScene(1, 6);
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            InputStruct* input = &g_Controls[g_Practice.homeAway];
            int sel = cssCursorOnBottomControl_maybe(g_Practice.homeAway, input->buttonInput, input->newButtonInput, input->_08, 0);

            g_Minigame.selectSlots[g_Practice.homeAway].charID = sel;
            g_Minigame.battingHandedness[g_Practice.homeAway] = PLAYER_KEY(g_Minigame.selectSlots[g_Practice.homeAway].charID);
        }
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 30) {
            g_Minigame.charSelectState = 0;
            g_Practice.practiceState++;
        }
        break;
    }
    case PRACTICE_STATE_2:
        fn_3_B49D4();
        practice_loadCharacter(0, 0, g_Minigame.selectSlots[g_Practice.homeAway].charID, g_Minigame.battingHandedness[g_Practice.homeAway]);
        sound_crowd_EffectsStruct._2C = 0;
        break;
    case PRACTICE_STATE_3:
        if (!practice_relatedToSettingCharacters()) {
            break;
        }
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 0x5A) {
            changeScene(3, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            g_Practice.practiceState++;
        }
        break;
    case PRACTICE_STATE_4:
        if (g_Practice.practiceLevel == 4) {
            switchSecondaryGameMode(0xC);
        } else if (g_Practice.practiceLevel == 5) {
            switchSecondaryGameMode(0xB);
        } else if (g_Practice.practiceLevel == 6) {
            switchSecondaryGameMode(0xF);
        } else {
            switchSecondaryGameMode(0x10);
        }
        fn_80062A74();
        setTutorialState(TUTORIAL_STATE_0);
        break;
    case PRACTICE_STATE_5:
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_Practice.practiceState++;
        break;
    case PRACTICE_STATE_6:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 15) {
            practiceMenu_setScreen(5);
        }
        break;
    }

    if (g_Practice.practiceState >= 2) {
        minigameCharLoadQueueUpdate();
    }
}

// .text:0x000B49D4 size:0x26C
void fn_3_B49D4(void) {
    int i;

    for (i = 0; i < 4; i++) {
        InputStruct* input;

        if (i != g_Practice.homeAway) {
            continue;
        }
        if (g_Minigame.charChangeFrames[i] < 0xFFFE) {
            g_Minigame.charChangeFrames[i]++;
        } else {
            g_Minigame.charChangeFrames[i] = 0xFFFF;
        }
        input = &g_Controls[i];

        if ((input->newButtonInput & INPUT_BUTTON_A) && g_Minigame.selectSlots[i].charID >= 0 &&
            g_Minigame.selectSlots[i].onBottomControlInd == 0) {
            if ((s8)charSelectStruct[0x7F + i] < 0 && g_Minigame.selectSlots[i].charID == g_Minigame.selectSlots[i].loadedCharID &&
                g_Minigame.selectSlots[i].loadedHandedness == g_Minigame.selectSlots[i].wantedHandedness &&
                g_Minigame.selectSlots[i].charReadyInd != 0 && g_Minigame.selectSlots[i].charReadyPrevInd != 0) {
                g_Minigame.selectSlots[i].confirmedInd = TRUE;
                addOrRemoveCharacterToTeam(i, g_Minigame.selectSlots[i].charID, TRUE);
                playPlayerSelectedSound(g_Minigame.selectSlots[i].charID);
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_Practice.practiceState = PRACTICE_STATE_3;
            }
        } else if (input->newButtonInput & INPUT_BUTTON_B) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_Practice.practiceState = PRACTICE_STATE_5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
            break;
        } else {
            int prevChar = g_Minigame.selectSlots[i].charID;
            int sel = cssCursorOnBottomControl_maybe(i, input->buttonInput, input->newButtonInput, input->_08, 0);

            if (sel >= 0) {
                g_Minigame.selectSlots[i].charID = sel;
                if (prevChar != g_Minigame.selectSlots[i].charID) {
                    g_Minigame.charChangeFrames[i] = 0;
                    g_Minigame.battingHandedness[i] = PLAYER_KEY(g_Minigame.selectSlots[i].charID);
                }
                g_Minigame.selectSlots[i].onBottomControlInd = FALSE;
            } else {
                g_Minigame.selectSlots[i].charID = fn_8004FD64(i);
                g_Minigame.selectSlots[i].onBottomControlInd = TRUE;
                g_Minigame.selectSlots[i].charReadyInd = FALSE;
            }
        }

        if (input->newButtonInput & INPUT_BUTTON_X) {
            g_Minigame.battingHandedness[i] = g_Minigame.battingHandedness[i] + 1;
            if (g_Minigame.battingHandedness[i] > 3) {
                g_Minigame.battingHandedness[i] = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        }
    }
}

