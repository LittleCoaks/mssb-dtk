#include "menus/challenge_file_select.h"
#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_menus_challenge_file_select
#include "header_rep_data.h"
#include "menus/debug_menu_text.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "musyx/musyx.h"
#include "Dolphin/gx.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800b0a14.h"

/* The drawing task that runs the challenge file-select screen; only the step
 * counter and the owning scene node are used. */
typedef struct {
    /* 0x00 */ u8 _00[0xC];
    /* 0x0C */ DrawingSceneStruct *scene;
    /* 0x10 */ u8 _10[0x28 - 0x10];
    /* 0x28 */ s8 step;
} ChallengeFileTask;

enum {
    FILE_SELECT_STEP_RESET = 0,
    FILE_SELECT_STEP_FADE_IN = 1,
    FILE_SELECT_STEP_DONE = 4,
};

enum {
    FILE_TASK_STEP_START = 0,
    FILE_TASK_STEP_WAIT_SCENE = 1,
    FILE_TASK_STEP_WAIT_A = 2,
    FILE_TASK_STEP_WAIT_EXIT = 3,
    FILE_TASK_STEP_FINISH = 4,
};

extern int lbl_2_bss_1598;
extern u8 *lbl_2_bss_1A823C;
extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8248;
extern u8 lbl_8037169C[0x1C];

void settingValuesTo0(void);
void changeScreenVariables(u16 screen);
void fn_2_4AB1C(void);
int fn_2_46D00(void);

#define WB(off) (lbl_2_bss_1A824C[(off)])
#define PADH(i, off) (*(u16 *)((u8 *)&AtBat_ButtonInput1 + (i) * 0x20 + (off)))

DebugMenuText lbl_2_data_2B78 = {
    { "BAT FIRST", "BAT LAST" },
    "FL",
    "PC",
    { "RR", "RL", "LR", "LL" },
    { "OFF", "ON" },
    { "SELECT DEBUG MENU", "HIDE CHARA SET", "STAR PLAYER SET", "KOOPA STA FLAG SET", "CHALLE LEVEL FREE SET" },
    { "1P >", "COM1>", "2P >", "COM2>", "3P >", "COM3>", "4P >", "COM4>" },
    { 0x0000FF0F, 0x0000880F, 0x00000FFF, 0x0000088F, 0x0000F0FF, 0x0000808F, 0x0000F00F, 0x0000800F },
    { 0, 4, 10, 6, 2, 9, 1, 5, 11, 17, 3, 19 },
    { 0, 2, 6, 8, 4, 10, 1, 3, 7, 5, 9, 11 },
    { 0, 0, 6, 2, 8, 4, 10, 5, 11, 3, 9, 1, 7, 0, 0, 0 },
};

GXColor lbl_2_data_2E3C = { 0, 0, 0, 0 };

// .text:0x0001A1B4 size:0xF8 mapped:0x80659248
void challengeFileSelect(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    switch (lbl_2_bss_1598) {
    case FILE_SELECT_STEP_RESET:
        settingValuesTo0();
        item->state = 0;
        GXSetCopyClear(lbl_2_data_2E3C, 0xFFFFFF);
        lbl_2_bss_1598 = FILE_SELECT_STEP_FADE_IN;
        break;
    case FILE_SELECT_STEP_FADE_IN:
        sndVolume(0x7F, 0xA, 0xFF);
        lbl_2_bss_1598 = FILE_SELECT_STEP_DONE;
        break;
    case 2:
        lbl_2_bss_1598 = FILE_SELECT_STEP_DONE;
        break;
    case FILE_SELECT_STEP_DONE:
        changeScene(3, 6);
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            changeScreenVariables(5);
        } else {
            changeScreenVariables(0x10);
        }
        break;
    }
}

// .text:0x0001A2AC size:0x174 mapped:0x80659340
void fn_2_1A2AC(void) {
    ChallengeFileTask *task = (ChallengeFileTask *)currentDrawingItem;

    switch (task->step) {
    case FILE_TASK_STEP_START:
        WB(0x19783E) = 0;
        changeScene(1, 6);
        task->step = FILE_TASK_STEP_WAIT_SCENE;
        break;
    case FILE_TASK_STEP_WAIT_SCENE:
        if (lbl_8037169C[0x12] != 0) {
            task->step = FILE_TASK_STEP_WAIT_A;
        }
        break;
    case FILE_TASK_STEP_WAIT_A:
        if (PADH((s8)WB(0x197863), 0x2) & INPUT_BUTTON_A) {
            changeScene(3, 6);
            task->step = FILE_TASK_STEP_WAIT_EXIT;
        }
        break;
    case FILE_TASK_STEP_WAIT_EXIT:
        if (lbl_8037169C[0x13] != 0) {
            task->step = FILE_TASK_STEP_FINISH;
        }
        break;
    case FILE_TASK_STEP_FINISH:
        task->scene->state = 1;
        removeCurrentDrawingItem();
        task->step = FILE_TASK_STEP_START;
        break;
    }
    if (WB(0x19783F) == 1) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        task->step = FILE_TASK_STEP_START;
    }
}

// .text:0x0001A420 size:0xA8 mapped:0x806594B4
BOOL fn_2_1A420(void) {
    BOOL found = FALSE;

    if (*(s16 *)(lbl_2_bss_1A823C + 0x30) == 3) {
        fn_2_4AB1C();
        if ((s8)WB(0x197843) == 0) {
            if (lbl_2_bss_1A8248[0x441C] == 5) {
                if (fn_2_46D00() != 0) {
                    found = TRUE;
                }
            } else if (lbl_2_bss_1A8248[0x4426] & 0x20) {
                found = TRUE;
            }
        }
    }
    return found != 0;
}
