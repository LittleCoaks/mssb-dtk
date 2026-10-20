#include "menus/text_194BC.h"

#include "Dolphin/GX/GXFrameBuffer.h"
#include "game/UnknownHomes_Game.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x80062a50.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_80366158[0x30];
extern s32 lbl_2_bss_1598[2];
extern GXColor lbl_2_data_2E3C;
extern u8 *lbl_2_bss_1A823C;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_800EFBA4[];
extern u8 lbl_8037169C[];
extern u8 cardCheck[];
extern u8 gameSetUpStep[];
extern u8 menuNumber[];
extern int menuCursors[0x16];
extern u8 hugeAnimStruct[];
extern void startMenuMusic(void);
extern void setLITLightPtr(void *light);
extern void fn_80021204(void);
extern void fn_80021228(int arg0);
extern int fn_8003AE70(int arg0);
extern void fn_800A97EC(int arg0, int arg1, int arg2);
extern void fn_8003BF54(int, int, int, int, int, int, int, int, int);
extern void fn_2_96D20(void);
extern void fn_2_4AB1C(void);
extern BOOL fn_2_46D00(void);
extern void updateCharacterSelectProcessCode(int port, u8 process);
extern void changeScreenVariables(u16 screen);
extern void *memset(void *dst, int c, u32 n);

static void syncSettingsFromAudio(void) {
    lbl_2_bss_1033C.flag06 = audioFileDescriptors.enableMusic;
    lbl_2_bss_1033C.flag08 = lbl_80366158[0x1F];
    lbl_2_bss_1033C.flag07 = audioFileDescriptors.soundMode;
}

static void resetAnimPrimary(void) {
    s32 i;
    *(u32 *)(hugeAnimStruct + 0) = 0;
    *(u32 *)(hugeAnimStruct + 0x2D9C) = 0;
    for (i = 0; i < 0xB4; i++) {
        *(u32 *)(hugeAnimStruct + i * 4 + 0x2DA0) = 0;
    }
}

static void resetAnimHeader(void) {
    s32 i;
    *(u32 *)(hugeAnimStruct + 8) = 0;
    for (i = 0; i < 0x15; i++) {
        *(u32 *)(hugeAnimStruct + i * 4 + 0xC) = 0;
    }
}

static void resetAnimSecondary(void) {
    s32 i;
    *(u32 *)(hugeAnimStruct + 0x60) = 0;
    *(u32 *)(hugeAnimStruct + 0x64) = 0;
    *(u32 *)(hugeAnimStruct + 0x68) = 0;
    *(u32 *)(hugeAnimStruct + 0x6C) = 0;
    *(u32 *)(hugeAnimStruct + 0x70) = 0;
    *(u32 *)(hugeAnimStruct + 0x74) = 0;
    *(u32 *)(hugeAnimStruct + 0x78) = 0;
    *(u32 *)(hugeAnimStruct + 0xAC) = 0;
    *(u32 *)(hugeAnimStruct + 0xB0) = 0;
    *(u32 *)(hugeAnimStruct + 0xB4) = 0;
    *(u32 *)(hugeAnimStruct + 0xB8) = 0;
    for (i = 0; i < 0x15; i++) {
        *(u32 *)(hugeAnimStruct + i * 4 + 0xBC) = 0;
    }
}

static void resetAnimTail(void) {
    s32 i;
    *(u32 *)(hugeAnimStruct + 0x2C84) = 0;
    *(u32 *)(hugeAnimStruct + 0x2C88) = 0;
    *(u32 *)(hugeAnimStruct + 0x2C8C) = 0;
    for (i = 0; i < 0x10; i++) {
        *(u32 *)(hugeAnimStruct + i * 4 + 0x2CAC) = 0;
    }
}

static void resetAnimFinal(void) {
    *(u32 *)(hugeAnimStruct + 0x2D90) = 0;
    *(u32 *)(hugeAnimStruct + 0x2D94) = 0;
    *(u32 *)(hugeAnimStruct + 0x2D98) = 0;
    *(u32 *)(hugeAnimStruct + 0x3070) = 0;
    *(u32 *)(hugeAnimStruct + 0x3074) = 0;
}

void fn_2_194BC(void *self) {
    void *light = *(void **)((u8 *)self + 0x70);
    if (light != NULL) {
        setLITLightPtr(light);
    }
}

void fn_2_194E8(void) {
    fn_80021204();
    *((u8 *)&inningSetting + 0x25) = lbl_80366158[0x1F];
}

void fn_2_19520(void) {
    syncSettingsFromAudio();
}

s8 fn_2_19554(void) {
    BOOL changed = FALSE;
    if (audioFileDescriptors.enableMusic != fn_8003AE70(0) ||
        audioFileDescriptors._397 != fn_8003AE70(1) ||
        lbl_80366158[0x1F] != fn_8003AE70(2)) {
        changed = 1;
    }
    return changed;
}

void fn_2_195D8(void) {
}

void fn_2_195DC(void) {
    SettingsScreenState *s = &lbl_2_bss_1033C;

    switch (s->cursor) {
    case 0:
        if (s->flag06 != 0 && audioFileDescriptors.enableMusic == 0) {
            initializeUnknown();
            insertGraphicDrawingFunction(startMenuMusic, 0x1000);
        } else if (s->flag06 == 0 && audioFileDescriptors.enableMusic != 0) {
            fn_80062A74();
        }
        audioFileDescriptors.enableMusic = s->flag06;
        s->flag0D = s->flag06;
        break;
    case 1:
        if (s->flag07 != audioFileDescriptors.soundMode) {
            fn_80062A74();
            if (s->flag07 == 1) {
                audioFileDescriptors.soundMode = 1;
            } else if (s->flag07 == 0) {
                audioFileDescriptors.soundMode = 0;
            } else {
                audioFileDescriptors.soundMode = 2;
            }
            fn_80021228(audioFileDescriptors.soundMode);
            insertGraphicDrawingFunction(startMenuMusic, 0x1000);
            audioFileDescriptors.soundMode = s->flag07;
        }
        break;
    case 2:
        if (s->flag08 != 0) {
            lbl_80366158[0x1F] = 1;
            fn_800A97EC(0, 0x32, 1);
        } else {
            lbl_80366158[0x1F] = 0;
        }
        break;
    }
    lbl_2_bss_1033C.active = 0;
}

void fn_2_19778(void) {
    syncSettingsFromAudio();
}

void fn_2_197AC(u8 slot) {
    u8 *entry;
    u16 input[3];
    u32 buttons;
    u32 dpad;
    s8 changed = 0;

    if ((s8)((u8 *)&Static_Stats_Tables)[0x46F8 + slot] == -1) {
        return;
    }

    memset(input, 0, sizeof(input));
    entry = (u8 *)&Static_Stats_Tables + slot * 6;
    input[0] = *(u16 *)(entry + 0x472C);
    input[1] = *(u16 *)(entry + 0x472E);
    input[2] = *(u16 *)(entry + 0x4730);
    buttons = input[1];
    dpad = input[2];

    if (buttons & 0x100) {
        if (lbl_2_bss_1033C.active) {
            fn_2_195DC();
        } else {
            lbl_2_bss_1033C.active = 1;
        }
        updateCharacterSelectProcessCode(0, 0x5C);
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        return;
    }

    if (buttons & 0x200) {
        if (lbl_2_bss_1033C.active != 0) {
            lbl_2_bss_1033C.active = 0;
            updateCharacterSelectProcessCode(0, 0x5C);
            syncSettingsFromAudio();
        } else if (cardCheck[0x47] != 0) {
            fn_80021204();
            *((u8 *)&inningSetting + 0x25) = lbl_80366158[0x1F];
            updateCharacterSelectProcessCode(0, 0x5A);
            lbl_2_bss_1033C.mode = 4;
        } else {
            changed = 0;
            if (audioFileDescriptors.enableMusic != fn_8003AE70(0) ||
                audioFileDescriptors._397 != fn_8003AE70(1) ||
                lbl_80366158[0x1F] != fn_8003AE70(2)) {
                changed = 1;
            }
            if (changed) {
                lbl_2_bss_1033C.mode = 5;
            } else {
                updateCharacterSelectProcessCode(0, 0x5A);
                lbl_2_bss_1033C.mode = 4;
            }
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        return;
    }

    if (dpad & 0x8) {
        if (!lbl_2_bss_1033C.active) {
            lbl_2_bss_1033C.prevCursor = lbl_2_bss_1033C.cursor;
            lbl_2_bss_1033C.cursor--;
            if (lbl_2_bss_1033C.cursor < 0) {
                lbl_2_bss_1033C.cursor = 2;
            } else if (lbl_2_bss_1033C.flag06 == 0 && lbl_2_bss_1033C.cursor == 1) {
                lbl_2_bss_1033C.cursor--;
            }
            updateCharacterSelectProcessCode(0, 0x5B);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        return;
    }

    if (dpad & 0x4) {
        if (!lbl_2_bss_1033C.active) {
            lbl_2_bss_1033C.prevCursor = lbl_2_bss_1033C.cursor;
            lbl_2_bss_1033C.cursor++;
            if (lbl_2_bss_1033C.cursor == 3) {
                lbl_2_bss_1033C.cursor = 0;
            } else if (lbl_2_bss_1033C.flag06 == 0 && lbl_2_bss_1033C.cursor == 1) {
                lbl_2_bss_1033C.cursor++;
            }
            updateCharacterSelectProcessCode(0, 0x5B);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        return;
    }

    if (buttons & 0x1) {
        u8 old;
        if (lbl_2_bss_1033C.active == 0) {
            return;
        }
        if (lbl_2_bss_1033C.cursor == 0) {
            old = lbl_2_bss_1033C.flag06;
            lbl_2_bss_1033C.flag06 = 1;
            lbl_2_bss_1033C.flag0A = 0;
            changed = (old == 0);
        } else if (lbl_2_bss_1033C.cursor == 1) {
            lbl_2_bss_1033C.flag09 = lbl_2_bss_1033C.flag07;
            if (lbl_2_bss_1033C.flag07 > 0) {
                lbl_2_bss_1033C.flag07--;
                changed = 1;
            }
        } else if (lbl_2_bss_1033C.cursor == 2) {
            old = lbl_2_bss_1033C.flag08;
            lbl_2_bss_1033C.flag08 = 1;
            changed = (old == 0);
        }
        if (changed) {
            updateCharacterSelectProcessCode(0, 0x5B);
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }

    if (buttons & 0x2) {
        u8 old;
        if (lbl_2_bss_1033C.active == 0) {
            return;
        }
        if (lbl_2_bss_1033C.cursor == 0) {
            old = lbl_2_bss_1033C.flag06;
            lbl_2_bss_1033C.flag06 = 0;
            lbl_2_bss_1033C.flag0A = 0;
            changed = (old != 0);
        } else if (lbl_2_bss_1033C.cursor == 1) {
            u8 next;
            old = lbl_2_bss_1033C.flag07;
            lbl_2_bss_1033C.flag09 = old;
            next = old + 1;
            lbl_2_bss_1033C.flag07 = next;
            if ((s8)next == 3) {
                lbl_2_bss_1033C.flag07 = 2;
            }
            changed = (old != (u8)lbl_2_bss_1033C.flag07);
        } else if (lbl_2_bss_1033C.cursor == 2) {
            old = lbl_2_bss_1033C.flag08;
            lbl_2_bss_1033C.flag08 = 0;
            changed = (old != 0);
        }
        if (changed) {
            updateCharacterSelectProcessCode(0, 0x5B);
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

void optionsScreen(void) {
    switch (lbl_2_bss_1033C.mode) {
    case 0:
        if (lbl_8037169C[0x13] == 0) {
            return;
        }
        lbl_2_bss_1033C.mode = 1;
        /* fall through */
    case 1:
        changeScene(1, 6);
        menuCursors[2] = 0;
        menuCursors[3] = 0;
        fn_2_96D20();
        updateCharacterSelectProcessCode(0, 0x59);
        lbl_2_bss_1033C.prevCursor = 0;
        lbl_2_bss_1033C.cursor = 0;
        lbl_2_bss_1033C.active = 0;
        lbl_2_bss_1033C.flag06 = audioFileDescriptors.enableMusic;
        lbl_2_bss_1033C.flag08 = lbl_80366158[0x1F];
        lbl_2_bss_1033C.flag07 = audioFileDescriptors.soundMode;
        lbl_2_bss_1033C.flag0D = (s8)audioFileDescriptors.enableMusic != 0;
        lbl_2_bss_1033C.mode = 2;
        break;
    case 2:
        if (gameSetUpStep[0x5D] != 0) {
            return;
        }
        lbl_2_bss_1033C.mode = 3;
        break;
    case 3:
        fn_2_197AC(*((u8 *)&Static_Stats_Tables + 0x46F8));
        break;
    case 5:
        fn_80021204();
        *((u8 *)&inningSetting + 0x25) = lbl_80366158[0x1F];
        fn_8003BF54(0, 0, 0, 0, 1, 4, 1, 0, 4);
        currentDrawingItem->state = 0;
        lbl_2_bss_1033C.mode = 6;
        break;
    case 6: {
        s16 st = currentDrawingItem->state;
        if (st == 0) {
            return;
        }
        switch (st) {
        case 0xB:
        case 1:
            updateCharacterSelectProcessCode(0, 0x5A);
            lbl_2_bss_1033C.mode = 4;
            break;
        default:
            lbl_2_bss_1033C.mode = 5;
            break;
        }
        break;
    }
    case 4:
        if (gameSetUpStep[0x55] != 0) {
            return;
        }
        lbl_2_bss_1033C.flag0F = 1;
        lbl_2_bss_1033C.mode = 0;
        menuNumber[0x26] = 1;
        changeScreenVariables(5);
        break;
    }
}

#pragma dont_inline on
void settingValuesTo0(void) {
    s32 k;
    resetAnimPrimary();
    resetAnimHeader();
    resetAnimSecondary();
    *(u32 *)(hugeAnimStruct + 0x110) = 0;
    for (k = 0; k < 13; k++) {
        memset(hugeAnimStruct + 0xC04 + k * 0x27C, 0, 0x27C);
    }
    resetAnimTail();
    resetAnimFinal();
}
#pragma dont_inline reset

void challengeFileSelect(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    switch (lbl_2_bss_1598[0]) {
    case 0:
        settingValuesTo0();
        item->state = 0;
        GXSetCopyClear(lbl_2_data_2E3C, 0x00FFFFFF);
        lbl_2_bss_1598[0] = 1;
        break;
    case 1:
        sndVolume(0x7F, 10, 0xFF);
        lbl_2_bss_1598[0] = 4;
        break;
    case 2:
        lbl_2_bss_1598[0] = 4;
        break;
    case 4:
        changeScene(3, 6);
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            changeScreenVariables(5);
        } else {
            changeScreenVariables(0x10);
        }
        break;
    }
}

void fn_2_1A2AC(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 state = *(s8 *)((u8 *)item + 0x28);

    switch (state) {
    case 0:
        *(u8 *)(lbl_2_bss_1A824C + 0x190000 + 0x783E) = 0;
        changeScene(1, 6);
        *((u8 *)item + 0x28) = 1;
        break;
    case 1:
        if (lbl_8037169C[0x12] != 0) {
            *((u8 *)item + 0x28) = 2;
        }
        break;
    case 2: {
        s8 idx = *(s8 *)(lbl_2_bss_1A824C + 0x190000 + 0x7863);
        if (*(u16 *)((u8 *)&AtBat_ButtonInput1 + idx * 0x20 + 2) & INPUT_BUTTON_A) {
            changeScene(3, 6);
            *((u8 *)item + 0x28) = 3;
        }
        break;
    }
    case 3:
        if (lbl_8037169C[0x13] != 0) {
            *((u8 *)item + 0x28) = 4;
        }
        break;
    case 4:
        item->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        *((u8 *)item + 0x28) = 0;
        break;
    }

    if (*(u8 *)(lbl_2_bss_1A824C + 0x190000 + 0x783F) == 1) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        *((u8 *)item + 0x28) = 0;
    }
}

BOOL fn_2_1A420(void) {
    BOOL result = FALSE;

    if (*(s16 *)(lbl_2_bss_1A823C + 0x30) == 3) {
        fn_2_4AB1C();
        if (*(s8 *)(lbl_2_bss_1A824C + 0x190000 + 0x7843) == 0) {
            if (lbl_2_bss_1A8248[0x441C] == 5) {
                if (fn_2_46D00() != 0) {
                    result = TRUE;
                }
            } else if (lbl_2_bss_1A8248[0x4426] & 0x20) {
                result = TRUE;
            }
        }
    }
    return result != 0;
}
