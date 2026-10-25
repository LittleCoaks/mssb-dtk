#include "menus/text_8ED4C.h"
#include "menus/main_menu.h"
#include "menus/yd_step.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x8004a2bc.h"
#include "Dolphin/os.h"

typedef struct TitleScreenWork {
    u8 unk0[0x10];
    u16 state;
    u8 unk12[6];
    u16 cardStep;
} TitleScreenWork;

typedef struct TitlePrompt {
    u8 unk0[0x3B];
    u8 result;
} TitlePrompt;

extern TitleScreenWork lbl_2_bss_340234;
extern TitlePrompt *lbl_2_bss_B2C0;
extern menuControlStruct *menuControlVariables;
extern u8 cardCheck[];
extern u8 lbl_80366158[];

void fn_8004A0FC(void);
void fn_80062764(void *item);
TitlePrompt *fn_8006C0D0(void);
void startMemoryCardCheck(void);
void fn_80021228(s32 mode);
void changeScene(u8 scene, u16 priority);

// .text:0x0008EEC8 size:0x22C mapped:0x806CDF5C
void titleScreen(void) {
    TitleScreenWork *work = &lbl_2_bss_340234;
    switch (work->state) {
    case 0:
        if (menuControlVariables->previousScreen != 5) {
            fn_80062764(currentDrawingItem);
        }
        lbl_2_bss_B2C0 = fn_8006C0D0();
        work->state = 1;
        break;
    case 1:
        switch (lbl_2_bss_B2C0->result) {
        case 0:
        case 1:
            break;
        case 2:
            lbl_2_bss_B2C0->result = 0;
            work->state = 2;
            break;
        case 3:
            lbl_2_bss_B2C0->result = 0;
            work->state = 3;
            break;
        }
        break;
    case 2:
        fn_2_8EDC4();
        break;
    case 3:
        fn_2_8ED4C();
        changeScene(4, 6);
        changeScreenVariables(4);
        break;
    }
}
// .text:0x0008EDC4 size:0x104 mapped:0x806CDE58
void fn_2_8EDC4(void) {
    TitleScreenWork *work = &lbl_2_bss_340234;
    switch (work->cardStep) {
    case 0:
        if (cardCheck[0] == 0) {
            lbl_80366158[0x1F] = TRUE;
            startMemoryCardCheck();
            work->cardStep++;
            break;
        }
        // Fall through.
    case 1:
        if (cardCheck[0] == 0) {
            s16 state = currentDrawingItem->state;
            if (state == 1 || state == 0xB) {
                if (state != 1) {
                    fn_80021228((u8)OSGetSoundMode());
                }
                cardCheck[0] = TRUE;
                work->cardStep++;
            }
            break;
        }
        // Fall through.
    case 2:
        work->cardStep = 0;
        lbl_2_bss_340234.state = 0;
        changeScreenVariables(5);
        break;
    }
}

// .text:0x0008ED4C size:0x78 mapped:0x806CDDE0
void fn_2_8ED4C(void) {
    g_d_GameSettings.p2_CPU_match_code = P2_CPU_CODE_CPU_VS_CPU;
    g_d_GameSettings.home_AwaySetting = 0;
    loadDemoMatch(9, FALSE, TRUE);
    fn_8004A0FC();
    gameSettings.unk33[0x3E - 0x33] = 0;
    fn_8004A0FC();
    inningSetting.inningCount = 3;
    g_d_GameSettings.GameModeSelected = GAME_TYPE_DEMO;
}
