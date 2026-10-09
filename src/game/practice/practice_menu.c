#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_practiceMenu
#include "game/practice/practice_menu.h"
#include "header_rep_data.h"
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

extern u8 hugeAnimStruct[];
extern u8 lbl_80354768[];
extern u8 lbl_800EFBA4[];
extern u8 lbl_8037169C[];
extern u8 lbl_803C6CF8[];
extern u8 screenTextArray[];
extern u8 PracticeScreenFiles[];
extern u8 lbl_80366158[];
extern u8 practice_subMenu_length[][5];
extern u8 practiceMenu_typeIconOrder[];
extern u8 animRelated[];
extern void pitchingPracticeControl(void);
extern u8 practiceMenu_baserunningPreviewChars[];
extern BOOL practice_loadAllGraphics(int arg);
extern u8 characterStaticIndexes[];
extern u8 constantList[];
extern u8 lineUpInfoStruct[2][9][4];
extern void fn_3_6AEC0(void);
extern void fn_3_90AB0(int character);
extern BOOL fn_3_90B14(int first, int second);
extern void resetInMemFielders(void);
extern void possiblyTransitionBlackScreen(void);
extern void drawStadium(void);
extern void fn_80011BE4(int character);
extern void adjustBallSoundEffectBasedOnHeight(void);
extern void practicePauseRelated(void);
extern void baseRunningPracticeControl(void);
extern void freeFieldingPracticeControl(void);
extern BOOL loadSomethingFromDiskAtBeginningOfAB1(int index);
extern void css_initValues(int a, int b, int c, int d);
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
extern void fn_800111B4(void* arg);
extern void fn_8000F4B8(int a, int b, int c, int d);
extern BOOL fn_3_90C14(int arg);
extern void* ARAMTransfer(void* file, s32 arg1, s32 arg2, s32 arg3);
extern void SetGameStatus(int status);

#define PRACTICE_BYTE(offset) (*((u8*)&g_Practice + (offset)))
#define GAME_BYTE(offset) (*((u8*)&g_GameLogic + (offset)))
#define ANIM_BYTE(offset) (hugeAnimStruct[(offset)])
#define MINI_BYTE(offset) (*((u8*)&g_Minigame + (offset)))
#define MINI_SBYTE(offset) (*((s8*)&g_Minigame + (offset)))
#define MINI_HALF(offset) (*(s16*)((u8*)&g_Minigame + (offset)))
#define ANIM_HALF(offset) (*(s16*)&animRelated[(offset)])
#define MINI_U16(offset) (*(u16*)((u8*)&g_Minigame + (offset)))
#define GAME_HALF(offset) (*(u16*)((u8*)&g_GameLogic + (offset)))
#define PLAYER_KEY(charIdx) (((u8*)&Static_Stats_Tables)[(charIdx) * 0xA0 + 0x26] * 2 + ((u8*)&Static_Stats_Tables)[(charIdx) * 0xA0 + 0x27])

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
        if ((u16)g_Practice.practiceMenu_framesOnCurrMenuScreen < 0xFFFE) {
            g_Practice.practiceMenu_framesOnCurrMenuScreen++;
        } else {
            g_Practice.practiceMenu_framesOnCurrMenuScreen = 0x10000 - 1;
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
        if (PRACTICE_BYTE(0x1DA) != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_1);
        } else {
            updatePracticeTransitionState(PRACTICE_STATE_2);
        }
        PRACTICE_BYTE(0x1DA) = FALSE;
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
        animRelated[0xB9] = practiceType;
        g_Practice.practiceType_2 = practiceMenu_typeIconOrder[practiceType];
        break;
    }
    case PRACTICE_STATE_5:
        if (PRACTICE_BYTE(0x19C) != 0) {
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
        case 2:
            updatePracticeTransitionState(PRACTICE_STATE_4);
            break;
        case 1:
            if (g_Practice.progressNeedsSave != 0) {
                fn_8004CC18();
                fn_3_5B368();
            } else {
                changeScene(4, 6);
            }
            updatePracticeTransitionState(PRACTICE_STATE_8);
            break;
        }
        break;
    }
    case PRACTICE_STATE_8:
        if (PRACTICE_BYTE(0x19C) == 0) {
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

    if (PRACTICE_BYTE(0x19C) == 0) {
        if (practice_loadAllGraphics(g_GameLogic.teamFielding)) {
            PRACTICE_BYTE(0x19C) = TRUE;
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
    animRelated[0xB9] = practiceType;
    g_Practice.practiceType_2 = practiceMenu_typeIconOrder[practiceType];
}

// .text:0x000B51E4 size:0x4B0
void practice_subMenu_stateHandling(void) {
    switch (g_Practice.practiceState) {
    case PRACTICE_STATE_0:
        PRACTICE_BYTE(0x19D) = FALSE;
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
        if (PRACTICE_BYTE(0x19C) != 0 && g_Practice.framesSincePracticeMenuDefaultTransition > 30) {
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
        if (PRACTICE_BYTE(0x19D) == 0) {
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
        if (PRACTICE_BYTE(0x19D) != 0) {
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

    if (PRACTICE_BYTE(0x19C) == 0) {
        if (practice_loadAllGraphics(g_GameLogic.teamFielding)) {
            PRACTICE_BYTE(0x19C) = TRUE;
        }
    } else if (PRACTICE_BYTE(0x19D) == 0) {
        if (practice_loadAllGraphics(g_GameLogic.teamFielding)) {
            PRACTICE_BYTE(0x19D) = TRUE;
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
    if (GAME_BYTE(0x125) <= 2) {
        MINI_BYTE(0x19F0) = MINI_BYTE(0x19EF);
        MINI_BYTE(0x19EF) = TRUE;
        MINI_BYTE(0x19F9) = MINI_BYTE(0x19F8);
        MINI_BYTE(0x19F8) = TRUE;
        MINI_BYTE(0x1A02) = MINI_BYTE(0x1A01);
        MINI_BYTE(0x1A01) = TRUE;
        MINI_BYTE(0x1A0B) = MINI_BYTE(0x1A0A);
        MINI_BYTE(0x1A0A) = TRUE;
    }

    switch (g_Practice.practiceState) {
    case PRACTICE_STATE_0: {
        int slots[4];

        slots[0] = FALSE;
        slots[1] = FALSE;
        slots[2] = FALSE;
        slots[3] = FALSE;
        slots[g_Practice.homeAway] = TRUE;
        css_initValues(slots[0], slots[1], slots[2], slots[3]);
        cssLoadingRelated_1(0, 0, 0, 0, 0, 0);
        MINI_SBYTE(0x19EA) = -1;
        MINI_BYTE(0x1A17) = PLAYER_KEY((s8)MINI_BYTE(0x19E8));
        MINI_BYTE(0x19E9) = 0;
        MINI_HALF(0x19D2) = 20;
        MINI_BYTE(0x19F3) = -1;
        MINI_BYTE(0x19F2) = 0;
        MINI_HALF(0x19D4) = 20;
        MINI_BYTE(0x1A18) = PLAYER_KEY((s8)MINI_BYTE(0x19F1));
        MINI_BYTE(0x19FC) = -1;
        MINI_BYTE(0x19FB) = 0;
        MINI_HALF(0x19D6) = 20;
        MINI_BYTE(0x1A19) = PLAYER_KEY((s8)MINI_BYTE(0x19FA));
        MINI_BYTE(0x1A05) = -1;
        MINI_BYTE(0x1A04) = 0;
        MINI_HALF(0x19D8) = 20;
        MINI_BYTE(0x1A1A) = PLAYER_KEY((s8)MINI_BYTE(0x1A03));
        ANIM_BYTE(0x2D77) = FALSE;
        ANIM_BYTE(0x307A) = 5;
        MINI_BYTE(0x1A0C) = -1;
        GAME_HALF(0xFE) = 0;
        PRACTICE_BYTE(0x1D9) = FALSE;
        g_Practice.practiceState++;
        MINI_BYTE(0x1A13) = TRUE;
        MINI_BYTE(0x1A14) = TRUE;
        MINI_BYTE(0x1A15) = TRUE;
        MINI_BYTE(0x1A16) = TRUE;
        break;
    }
    case PRACTICE_STATE_1: {
        InputStruct* input = &g_Controls[g_Practice.homeAway];

        changeScene(1, 6);
        if (GAME_HALF(0xFE) == 1) {
            int sel = cssCursorOnBottomControl_maybe(g_Practice.homeAway, input->buttonInput, input->newButtonInput, input->_08, 0);

            MINI_BYTE(0x19E8 + g_Practice.homeAway * 9) = sel;
            MINI_BYTE(0x1A17 + g_Practice.homeAway) = PLAYER_KEY((s8)MINI_BYTE(0x19E8 + g_Practice.homeAway * 9));
        }
        if (GAME_HALF(0xFE) > 30) {
            MINI_BYTE(0x19DE) = 0;
            g_Practice.practiceState++;
        }
        break;
    }
    case PRACTICE_STATE_2:
        fn_3_B49D4();
        practice_loadCharacter(0, 0, (s8)MINI_BYTE(0x19E8 + g_Practice.homeAway * 9), MINI_BYTE(0x1A17 + g_Practice.homeAway));
        sound_crowd_EffectsStruct._2C = 0;
        break;
    case PRACTICE_STATE_3:
        if (!practice_relatedToSettingCharacters()) {
            break;
        }
        if (GAME_HALF(0xFE) >= 0x5A) {
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
        GAME_HALF(0xFE) = 0;
        g_Practice.practiceState++;
        break;
    case PRACTICE_STATE_6:
        if (GAME_HALF(0xFE) >= 15) {
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
        InputStruct* input = &g_Controls[i];
        u8* slot = (u8*)&g_Minigame + i * 9;
        u8* cursor = (u8*)&g_Minigame + i;
        u16* frames = (u16*)((u8*)&g_Minigame + i * 2 + 0x19D2);

        if (i != g_Practice.homeAway) {
            continue;
        }
        if (*frames < 0xFFFE) {
            (*frames)++;
        } else {
            *frames = 0x10000 - 1;
        }

        if ((input->newButtonInput & INPUT_BUTTON_A) && (s8)slot[0x19E8] >= 0 && slot[0x19EE] == 0) {
            if ((s8)charSelectStruct[0x7F + i] < 0 && (s8)slot[0x19E8] == (s8)slot[0x19EA] &&
                (s8)slot[0x19EC] == (s8)slot[0x19ED] && slot[0x19EF] != 0 && slot[0x19F0] != 0) {
                slot[0x19E9] = TRUE;
                addOrRemoveCharacterToTeam(i, (s8)slot[0x19E8], TRUE);
                playPlayerSelectedSound((s8)slot[0x19E8]);
                GAME_HALF(0xFE) = 0;
                g_Practice.practiceState = PRACTICE_STATE_3;
            }
        } else if (input->newButtonInput & INPUT_BUTTON_B) {
            GAME_HALF(0xFE) = 0;
            g_Practice.practiceState = PRACTICE_STATE_5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
            break;
        } else {
            int prevChar = (s8)slot[0x19E8];
            int sel = cssCursorOnBottomControl_maybe(i, input->buttonInput, input->newButtonInput, input->_08, 0);

            if (sel < 0) {
                slot[0x19E8] = fn_8004FD64(i);
                slot[0x19EE] = TRUE;
                slot[0x19EF] = FALSE;
            } else {
                slot[0x19E8] = sel;
                if (prevChar != (s8)slot[0x19E8]) {
                    *frames = 0;
                    cursor[0x1A17] = PLAYER_KEY((s8)slot[0x19E8]);
                }
                slot[0x19EE] = FALSE;
            }
        }

        if (input->newButtonInput & INPUT_BUTTON_X) {
            cursor[0x1A17] = cursor[0x1A17] + 1;
            if (cursor[0x1A17] > 3) {
                cursor[0x1A17] = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        }
    }
}

// .text:0x000B482C size:0x1A8
void practiceSimulation(void) {
    g_Practice.readyToMoveToNextInstruction = FALSE;
    if (g_Practice.pauseMenuActive != 0) {
        practicePauseRelated();
        adjustBallSoundEffectBasedOnHeight();
        return;
    }

    if ((u16)g_Practice.framesInCurrTransitionState < 0xFFFE) {
        g_Practice.framesInCurrTransitionState++;
    } else {
        g_Practice.framesInCurrTransitionState = 0x10000 - 1;
    }
    if ((u16)g_Practice.framesSincePracticeMenuDefaultTransition < 0xFFFE) {
        g_Practice.framesSincePracticeMenuDefaultTransition++;
    } else {
        g_Practice.framesSincePracticeMenuDefaultTransition = 0x10000 - 1;
    }
    if ((u16)g_Practice.totalFrames < 0xFFFE) {
        g_Practice.totalFrames++;
    } else {
        g_Practice.totalFrames = 0x10000 - 1;
    }

    switch (g_GameLogic.secondaryGameMode) {
    case SECONDARY_GAME_MODE_PRACTICE_MENU:
        practiceMenu();
        break;
    case SECONDARY_GAME_MODE_PRACTICE_PITCHING:
        pitchingPracticeControl();
        break;
    case SECONDARY_GAME_MODE_PRACTICE_BATTING:
        battingPracticeControl();
        break;
    case SECONDARY_GAME_MODE_PRACTICE_FIELDING:
        fieldingPracticeControl();
        break;
    case SECONDARY_GAME_MODE_PRACTICE_BASERUNNING:
        baseRunningPracticeControl();
        break;
    case SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING:
    case SECONDARY_GAME_MODE_FREE_FIELDING:
        freeFieldingPracticeControl();
        break;
    case SECONDARY_GAME_MODE_RETURN_TO_MENU:
        fn_3_B3C64();
        break;
    case SECONDARY_GAME_MODE_LOAD_PRACTICE_SCREEN:
        loadPracticeScreen();
        break;
    }

    adjustBallSoundEffectBasedOnHeight();
    if (GAME_BYTE(0x11E) == 1 || GAME_BYTE(0x11E) == 2) {
        if (ANIM_HALF(0x9E) >= 0 && loadBatterModelFromDisk(ANIM_HALF(0x9E))) {
            ANIM_HALF(0x9E) = -1;
        }
        if (ANIM_HALF(0xA0) >= 0 && loadSomethingFromDiskAtBeginningOfAB1(ANIM_HALF(0xA0))) {
            ANIM_HALF(0xA0) = -1;
        }
    }
}

#pragma dont_inline on
// .text:0x000B43E8 size:0x444
void loadPracticeScreen(void) {
    int i;
    int team;
    int slot;
    int row;
    int col;

    switch (GAME_BYTE(0x125)) {
    case 0:
        *(int*)((u8*)&g_GameLogic + 0x3C) = constantList[0];
        *(int*)((u8*)&g_GameLogic + 0x8C) = constantList[0];
        for (team = 0; team < 2; team++) {
            u8* lineUp = (u8*)lineUpInfoStruct + team * 0x24;
            u8* game = (u8*)&g_GameLogic + team * 0x50 + 0x44;
            u8* values = constantList;

            for (i = 0; i < 3; i++) {
                lineUp[0] = 3 * i;
                lineUp[1] = 3 * i;
                lineUp[2] = 3 * i;
                lineUp[4] = 3 * i + 1;
                lineUp[5] = 3 * i + 1;
                lineUp[6] = 3 * i + 1;
                lineUp[8] = 3 * i + 2;
                lineUp[9] = 3 * i + 2;
                lineUp[10] = 3 * i + 2;
                *(int*)(game + 0x00) = values[9];
                *(int*)(game + 0x04) = values[9];
                *(int*)(game + 0x08) = values[10];
                *(int*)(game + 0x0C) = values[10];
                *(int*)(game + 0x10) = values[11];
                *(int*)(game + 0x14) = values[11];
                lineUp += 12;
                game += 0x18;
                values += 3;
            }
        }
        for (team = 0; team < 2; team++) {
            for (slot = 0; slot < 9; slot++) {
                int character = *(int*)((u8*)&g_GameLogic + team * 0x50 + slot * 8 + 0x44);
                memcpy((u8*)inMemRoster + team * 0x5A0 + slot * 0xA0, (u8*)&Static_Stats_Tables + character * 0xA0, 0xA0);
            }
        }
        g_Practice.homeAway = lbl_80366158[0x27];
        g_Practice.homeAwayByte = lbl_80366158[0x27];
        g_GameLogic.homeTeamInd = 0;
        g_GameLogic.teamBatting = 1;
        g_GameLogic.teamFielding = 0;
        g_GameLogic.homeTeamBattingInd_fieldingTeam = 1;
        g_GameLogic.awayTeamBattingInd_battingTeam = 0;
        *(int*)((u8*)&g_GameLogic + 0xEC) = lbl_80366158[0x27];
        *(int*)((u8*)&g_GameLogic + 0xF0) = lbl_80366158[0x27];
        *(int*)((u8*)&g_GameLogic + 0xF4) = 0;
        *(int*)((u8*)&g_GameLogic + 0xF8) = 0;
        GAME_BYTE(0x125) = GAME_BYTE(0x125) + 1;
        break;
    case 1:
        *(void**)(screenTextArray + 0x7AC) = ARAMTransfer(PracticeScreenFiles, 0, 1, 0);
        GAME_BYTE(0x125) = GAME_BYTE(0x125) + 1;
        break;
    case 2:
        if (lbl_803C6CF8[0x715] == 1) {
            fn_800111B4(*(void**)(screenTextArray + 0x7AC));
            sound_crowd_EffectsStruct._2C = 0;
            GAME_BYTE(0x125) = GAME_BYTE(0x125) + 1;
            fn_8000F4B8(g_Practice.homeAwayByte, -1, -1, -1);
        }
        break;
    case 3:
        if (fn_3_90C14(0)) {
            GAME_BYTE(0x125) = GAME_BYTE(0x125) + 1;
            sound_crowd_EffectsStruct._2C = 0;
        }
        break;
    case 4:
    default:
        PRACTICE_BYTE(0x19C) = FALSE;
        ANIM_BYTE(0x2D77) = FALSE;
        ANIM_BYTE(0x2D7B) = FALSE;
        ANIM_BYTE(0x2D7C) = FALSE;
        practice_loadAllGraphics(g_GameLogic.teamFielding);
        g_Practice.lakituTextIndex = -1;
        PRACTICE_BYTE(0x1AF) = 1;
        g_Practice.someCharID1 = -1;
        g_Practice.someCharID2 = -1;
        PRACTICE_BYTE(0x1B1) = FALSE;
        PRACTICE_BYTE(0x1DA) = TRUE;
        SetGameStatus(5);
        g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_PRACTICE_MENU;
        g_Practice.totalFrames = 0;
        g_Practice.framesInCurrTransitionState = 0;
        g_Practice.practiceState = PRACTICE_STATE_0;
        practiceMenu_setScreen(0);
        insertGraphicDrawingFunction(possiblyTransitionBlackScreen, 2);
        insertGraphicDrawingFunction(drawStadium, 4);
        ANIM_BYTE(0x307E) = FALSE;
        g_Practice.practiceType = PRACTICE_TYPE_PITCHING;
        PRACTICE_BYTE(0x1AB) = FALSE;
        PRACTICE_BYTE(0x1AC) = FALSE;
        PRACTICE_BYTE(0x1AD) = FALSE;
        PRACTICE_BYTE(0x1A6) = FALSE;
        PRACTICE_BYTE(0x1A8) = FALSE;
        PRACTICE_BYTE(0x1A9) = FALSE;
        PRACTICE_BYTE(0x19F) = FALSE;
        PRACTICE_BYTE(0x1A1) = FALSE;
        PRACTICE_BYTE(0x1A2) = FALSE;
        PRACTICE_BYTE(0x1A3) = FALSE;
        PRACTICE_BYTE(0x1A4) = FALSE;
        g_Practice.instructionNumber = -1;
        PRACTICE_BYTE(0x1AA) = FALSE;
        PRACTICE_BYTE(0x1D4) = FALSE;
        PRACTICE_BYTE(0x1D5) = FALSE;
        for (row = 0; row < 4; row++) {
            for (col = 0; col < 4; col++) {
                g_Practice.levelCompleted[row][col] = lbl_80354768[0xCF4E + row * 4 + col];
            }
        }
        break;
    }
}
#pragma dont_inline reset

#pragma dont_inline on
void practice_loadCharacterData(void) {
    int team, slot, i;

    *(int*)((u8*)&g_GameLogic + 0x3C) = constantList[0];
    *(int*)((u8*)&g_GameLogic + 0x8C) = constantList[0];
    for (team = 0; team < 2; team++) {
        u8* lineUp = (u8*)lineUpInfoStruct + team * 0x24;
        u8* game = (u8*)&g_GameLogic + team * 0x50 + 0x44;

        for (i = 0; i < 3; i++) {
            lineUp[0] = 3 * i;
            lineUp[1] = 3 * i;
            lineUp[2] = 3 * i;
            lineUp[4] = 3 * i + 1;
            lineUp[5] = 3 * i + 1;
            lineUp[6] = 3 * i + 1;
            lineUp[8] = 3 * i + 2;
            lineUp[9] = 3 * i + 2;
            lineUp[10] = 3 * i + 2;
            *(int*)(game + 0x00) = constantList[9 + 3 * i];
            *(int*)(game + 0x04) = constantList[9 + 3 * i];
            *(int*)(game + 0x08) = constantList[10 + 3 * i];
            *(int*)(game + 0x0C) = constantList[10 + 3 * i];
            *(int*)(game + 0x10) = constantList[11 + 3 * i];
            *(int*)(game + 0x14) = constantList[11 + 3 * i];
            lineUp += 12;
            game += 0x18;
        }
    }
    for (team = 0; team < 2; team++) {
        for (slot = 0; slot < 9; slot++) {
            int character = *(int*)((u8*)&g_GameLogic + team * 0x50 + slot * 8 + 0x44);
            memcpy((u8*)inMemRoster + team * 0x5A0 + slot * 0xA0, (u8*)&Static_Stats_Tables + character * 0xA0, 0xA0);
        }
    }
}
#pragma dont_inline reset

#pragma dont_inline on
void practice_loadCharacter(int team, int slot, int character, int flags) {
    if (team == 0 && slot == 0) {
        *(int*)((u8*)&g_GameLogic + team * 0x50 + 0x3C) = slot;
    }
    lineUpInfoStruct[team][slot][0] = slot;
    lineUpInfoStruct[team][slot][1] = slot;
    lineUpInfoStruct[team][slot][2] = slot;
    *(int*)((u8*)&g_GameLogic + team * 0x50 + slot * 8 + 0x44) = slot;
    *(int*)((u8*)&g_GameLogic + team * 0x50 + slot * 8 + 0x48) = slot;
    if (slot >= 0 && slot <= 8) {
        fn_80011BE4(slot);
    }
    memcpy((u8*)inMemRoster + team * 0x5A0 + slot * 0xA0, (u8*)&Static_Stats_Tables + character * 0xA0, 0xA0);
    if (flags >= 0) {
        if (flags == 0 || flags == 1) {
            *((u8*)inMemRoster + team * 0x5A0 + slot * 0xA0 + 0x26) = 0;
        } else {
            *((u8*)inMemRoster + team * 0x5A0 + slot * 0xA0 + 0x26) = 1;
        }
        if (flags == 0 || flags == 2) {
            *((u8*)inMemRoster + team * 0x5A0 + slot * 0xA0 + 0x27) = 0;
        } else {
            *((u8*)inMemRoster + team * 0x5A0 + slot * 0xA0 + 0x27) = 1;
        }
    }
}
#pragma dont_inline reset

void practiceLoadingRelatedMaybe(void) {
    int row;
    int col;
    insertGraphicDrawingFunction(possiblyTransitionBlackScreen, 2);
    insertGraphicDrawingFunction(drawStadium, 4);
    ANIM_BYTE(0x307E) = FALSE;
    g_Practice.practiceType = PRACTICE_TYPE_PITCHING;
    g_Practice.baserunningActiveRunners[0] = FALSE;
    g_Practice.baserunningActiveRunners[1] = FALSE;
    g_Practice.baserunningActiveRunners[2] = FALSE;
    PRACTICE_BYTE(0x1A6) = FALSE;
    PRACTICE_BYTE(0x1A8) = FALSE;
    PRACTICE_BYTE(0x1A9) = FALSE;
    g_Practice.pauseMenuActive = FALSE;
    g_Practice.aIEnabled = FALSE;
    g_Practice.practiceBatterHandedness = FALSE;
    g_Practice.freePracticeInd_writeOnly = FALSE;
    g_Practice.freeFieldingInd_writeOnly = FALSE;
    g_Practice.instructionNumber = -1;
    g_Practice.transitioningIndicator = FALSE;
    g_Practice.loadingGuidedPractice = FALSE;
    g_Practice.guidedMessageSceneStarted = FALSE;
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            g_Practice.levelCompleted[row][col] = lbl_80354768[0xCF4E + row * 4 + col];
        }
    }
}

BOOL practice_relatedToSettingCharacters(void) {
    int primary = 0;
    int secondary = -1;
    int previous;

    if (!g_Practice.characterLoadStarted) {
        g_Practice.characterLoadStarted = TRUE;
        g_Practice.someCharID3 = -1;
        g_Practice.someCharID4 = -1;
        switch (g_Practice.practiceType_2) {
        case PRACTICE_TYPE_BATTING:
        case PRACTICE_TYPE_FIELDING:
            secondary = 1;
            break;
        case PRACTICE_TYPE_BASERUNNING:
            return TRUE;
        case PRACTICE_TYPE_FREEPLAY:
            primary = (s8)MINI_BYTE(0x19E8 + g_Practice.homeAway * 9);
            break;
        case PRACTICE_TYPE_PITCHING:
        default:
            break;
        }
        if (primary == 0) primary = -1;
        if (secondary == 0) secondary = -1;
        if (primary < 0) {
            primary = secondary;
            secondary = -1;
        }
        if (primary < 0) return TRUE;
        if (secondary >= 0 && characterStaticIndexes[primary * 6 + 2] == characterStaticIndexes[secondary * 6 + 2]) {
            secondary = -1;
        }
        if (secondary < 0) {
            previous = g_Practice.someCharID1;
            if (previous >= 0 && characterStaticIndexes[previous * 6 + 2] == characterStaticIndexes[primary * 6 + 2]) return TRUE;
            previous = g_Practice.someCharID2;
            if (previous >= 0 && characterStaticIndexes[previous * 6 + 2] == characterStaticIndexes[primary * 6 + 2]) return TRUE;
            if (previous >= 0) {
                fn_3_90AB0(characterStaticIndexes[previous * 6 + 1]);
                g_Practice.someCharID2 = characterStaticIndexes[primary * 6 + 1];
            } else if (g_Practice.someCharID1 < 0) {
                g_Practice.someCharID1 = characterStaticIndexes[primary * 6 + 1];
            } else {
                g_Practice.someCharID2 = characterStaticIndexes[primary * 6 + 1];
            }
            g_Practice.someCharID3 = characterStaticIndexes[primary * 6 + 1];
        } else if (g_Practice.someCharID1 >= 0) {
            previous = g_Practice.someCharID1;
            if (characterStaticIndexes[previous * 6 + 1] != characterStaticIndexes[secondary * 6 + 1] &&
                characterStaticIndexes[previous * 6 + 1] != characterStaticIndexes[primary * 6 + 1]) {
                fn_3_90AB0(characterStaticIndexes[previous * 6 + 1]);
                fn_3_90AB0(characterStaticIndexes[g_Practice.someCharID2 * 6 + 1]);
                g_Practice.someCharID3 = characterStaticIndexes[primary * 6 + 1];
                g_Practice.someCharID4 = characterStaticIndexes[secondary * 6 + 1];
                g_Practice.someCharID1 = characterStaticIndexes[primary * 6 + 1];
                g_Practice.someCharID2 = characterStaticIndexes[secondary * 6 + 1];
            } else {
                if (characterStaticIndexes[previous * 6 + 1] != characterStaticIndexes[secondary * 6 + 1]) {
                    primary = secondary;
                }
                previous = g_Practice.someCharID2;
                if (characterStaticIndexes[previous * 6 + 1] != characterStaticIndexes[primary * 6 + 1]) {
                    fn_3_90AB0(characterStaticIndexes[previous * 6 + 1]);
                    g_Practice.someCharID3 = characterStaticIndexes[primary * 6 + 1];
                    g_Practice.someCharID2 = characterStaticIndexes[primary * 6 + 1];
                }
            }
        }
    }
    if (g_Practice.someCharID3 >= 0 && !fn_3_90B14(g_Practice.someCharID3, g_Practice.someCharID4)) return FALSE;
    return TRUE;
}

#pragma dont_inline on
void switchSecondaryGameMode(int mode) {
    g_GameLogic.secondaryGameMode = mode;
    g_Practice.totalFrames = 0;
    g_Practice.framesInCurrTransitionState = 0;
    g_Practice.practiceState = PRACTICE_STATE_0;
}
#pragma dont_inline reset

#pragma dont_inline on
void updatePracticeTransitionState(int state) {
    g_Practice.practiceState = state;
    g_Practice.framesInCurrTransitionState = 0;
}
#pragma dont_inline reset

#pragma dont_inline on
void setTutorialState(int state) {
    g_Practice.practiceState = PRACTICE_STATE_0;
    g_Practice.tutorialState = state;
    g_Practice.framesSincePracticeMenuDefaultTransition = 0;
}
#pragma dont_inline reset

#pragma dont_inline on
void fn_3_B3C64(void) {
    g_GameLogic.framesOfExitingToMenu = TRUE;
}
#pragma dont_inline reset

void baserunningPracticeRelated(void) {
    int i;
    for (i = 0; i < 4; i++) {
        if (g_Practice.baserunningActiveRunners[i] != 0) {
            if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING) {
                initializeInMemRunner(i - 1, i);
            }
            g_Runners[i].runnerOnFieldOrOutOrScored = RUNNER_STATUS_ON_FIELD;
        } else {
            g_Runners[i].runnerOnFieldOrOutOrScored = RUNNER_STATUS_NONE;
            g_Runners[i].rosterID = -1;
        }
    }
}

void practiceRelatedReset(void) {
    g_GameLogic.freeFieldingPracticeInd = FALSE;
    g_Practice.instructionNumber = -1;
    g_Practice.transitioningIndicator = FALSE;
    ANIM_BYTE(0x307E) = TRUE;
    ANIM_BYTE(0x307A) = TRUE;
    fn_3_6AEC0();
    fn_3_8F1C8();
    resetInMemFielders();
}
