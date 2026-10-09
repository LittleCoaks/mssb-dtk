#define SQRT2_LINKAGE static
#include "game/match_setup/character_loading.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8003649c.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/mb_subfunc.h"

extern u8 characterStaticIndexes[0x144];
extern u8 unkCharacterArray[32];
extern u8 lbl_3_data_81D4[8];

void fn_800214D0(void);
void fn_800216F8(s32 id, int (*callback)(void));
void fn_80021518(int id, void *block);
void fn_8006285C(void);

#define MINIGAME_U8(off) (((u8 *)&g_Minigame)[(off)])
#define MINIGAME_S8(off) (((s8 *)&g_Minigame)[(off)])
#define CHAR_SLOT_STRIDE 6

// .text:0x000910AC size:0x48
int fn_3_910AC(void) {
    fn_80021518(0x1C, audioFileDescriptors.files[0x08 / 4]);
    fn_80021518(0x1D, audioFileDescriptors.files[0x08 / 4]);
    return 0;
}

// .text:0x00091064 size:0x48
int fn_3_91064(void) {
    fn_80021518(0x1C, audioFileDescriptors.files[0x10 / 4]);
    fn_80021518(0x36, audioFileDescriptors.files[0x10 / 4]);
    return 0;
}

// .text:0x00090F48 size:0x11C
int fn_3_90F48(void) {
    s32 charId;
    s32 id;
    void **files;
    u8 mode = g_d_GameSettings.GameModeSelected;

    if (mode == GAME_TYPE_PRACTICE) {
        charId = sound_crowd_EffectsStruct._2D;
    } else if (mode == GAME_TYPE_MINIGAMES || mode == GAME_TYPE_TOY_FIELD) {
        u32 st = sound_crowd_EffectsStruct._2C;

        charId = MINIGAME_U8(0x18D0 + (st >> 1));
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME) {
        charId = sound_crowd_EffectsStruct._2D;
    } else {
        s32 n = audioFileDescriptors._399[1];
        charId = inMemRoster[n / 9][n % 9].stats.CharID;
    }

    id = findCharacterID(charId);
    files = &audioFileDescriptors.files[id + 5];
    fn_80021518(unkCharacterArray[id], *++files);
    return 0;
}

// .text:0x00090DD8 size:0x170
BOOL fn_3_90DD8(void) {
    DrawingSceneStruct *cur = currentDrawingItem;
    u8 st = sound_crowd_EffectsStruct._2C;
    s32 idx = (st >> 1) & 0x7F;

    if (st == 0 || st == 2 || st == 4 || st == 6) {
        s32 m;
        s32 target;
        u8 *slotChar;

        if (MINIGAME_S8(0x18CC + idx) < 0) {
            sound_crowd_EffectsStruct._2C += 2;
            return FALSE;
        }
        target = characterStaticIndexes[MINIGAME_U8(0x18D0 + idx) * CHAR_SLOT_STRIDE + 1];
        slotChar = (u8 *)&g_Minigame;
        for (m = 0; m < idx; m++, slotChar++) {
            if (target == characterStaticIndexes[slotChar[0x18D0] * CHAR_SLOT_STRIDE + 1]) {
                sound_crowd_EffectsStruct._2C += 2;
                if (sound_crowd_EffectsStruct._2C >= 8) {
                    g_Minigame._19AB = TRUE;
                    return TRUE;
                }
                return FALSE;
            }
        }
        fn_800216F8((u8)(findCharacterID(target) + 5), fn_3_90F48);
        sound_crowd_EffectsStruct._2C++;
    } else if (cur->state != 0) {
        sound_crowd_EffectsStruct._2C = st + 1;
        if ((u8)(st + 1) >= 8) {
            g_Minigame._19AB = TRUE;
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x00090CB0 size:0x128
void cleanupCharacters(void) {
    s32 slot;

    if (g_Minigame._19AB == FALSE) {
        return;
    }
    for (slot = 3; slot >= 0; slot--) {
        CharacterStats *entry = &inMemRoster[0][0] + slot;
        s32 j;

        for (j = 0; j < 4; j++) {
            if (MINIGAME_S8(0x18CC + j) == slot) {
                BOOL dup = FALSE;
                s32 m;

                for (m = 0; m < j; m++) {
                    if (characterStaticIndexes[MINIGAME_U8(0x18D0 + j) * CHAR_SLOT_STRIDE + 1] ==
                        characterStaticIndexes[MINIGAME_U8(0x18D0 + m) * CHAR_SLOT_STRIDE + 1]) {
                        dup = TRUE;
                        break;
                    }
                }
                if (!dup) {
                    break;
                }
            }
        }
        if (j < 4) {
            void **files = &audioFileDescriptors.files[findCharacterID(entry->stats.CharID) + 5];

            if (*++files != NULL) {
                fn_800214D0();
                fn_800ACFB0(*files);
                *files = NULL;
            }
        }
    }
}

// .text:0x00090C14 size:0x9C
BOOL fn_3_90C14(int arg) {
    DrawingSceneStruct *cur = currentDrawingItem;

    if (sound_crowd_EffectsStruct._2C == 0) {
        s32 id;

        sound_crowd_EffectsStruct._2D = arg;
        id = findCharacterID(arg);
        cur->state = 0;
        fn_800216F8((u8)(id + 5), fn_3_90F48);
        sound_crowd_EffectsStruct._2C++;
    } else if (cur->state != 0) {
        sound_crowd_EffectsStruct._2C++;
        return TRUE;
    }
    return FALSE;
}

// .text:0x00090B14 size:0x100
BOOL fn_3_90B14(int first, int second) {
    DrawingSceneStruct *cur = currentDrawingItem;
    u8 st;

    if (sound_crowd_EffectsStruct._2C == 0) {
        sound_crowd_EffectsStruct._2C = 1;
    }
    st = sound_crowd_EffectsStruct._2C;
    if (st == 1 || st == 3) {
        s32 id;

        if (st == 1) {
            sound_crowd_EffectsStruct._2D = first;
        } else {
            if (second < 0) {
                return TRUE;
            }
            sound_crowd_EffectsStruct._2D = second;
        }
        id = findCharacterID(sound_crowd_EffectsStruct._2D);
        cur->state = 0;
        fn_800216F8((u8)(id + 5), fn_3_90F48);
        sound_crowd_EffectsStruct._2C++;
        return FALSE;
    }
    if (cur->state != 0) {
        sound_crowd_EffectsStruct._2C = st + 1;
        if ((u8)(st + 1) == 5) {
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x00090AB0 size:0x64
void fn_3_90AB0(int charID) {
    if (charID >= 0) {
        void **files = &audioFileDescriptors.files[findCharacterID(charID) + 5];

        if (*++files != NULL) {
            fn_800214D0();
            fn_800ACFB0(*files);
            *files = NULL;
        }
    }
}

// .text:0x00090A18 size:0x98
BOOL fn_3_90A18(void) {
    DrawingSceneStruct *cur = currentDrawingItem;

    if (sound_crowd_EffectsStruct._2C == 0) {
        fn_800216F8((u8)(g_d_GameSettings.StadiumID + 0x27), fn_3_90798);
        cur->state = 0;
        sound_crowd_EffectsStruct._2C++;
    } else if (cur->state != 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000909B0 size:0x68
void fn_3_909B0(void) {
    s32 slot;
    void **files;

    fn_800214D0();
    slot = STADIUM_ID_TOY_FIELD;
    if (g_d_GameSettings.StadiumID != STADIUM_ID_TOY_FIELD) {
        slot = g_d_GameSettings.StadiumID;
    }
    files = &audioFileDescriptors.files[slot + 0x27];
    fn_800ACFB0(*++files);
    *files = NULL;
}

// .text:0x00090928 size:0x88
BOOL fn_3_90928(void) {
    DrawingSceneStruct *cur = currentDrawingItem;

    if (sound_crowd_EffectsStruct._2C == 0) {
        fn_800216F8(0x25, (int (*)(void))fn_8006285C);
        cur->state = 0;
        sound_crowd_EffectsStruct._2C++;
    } else if (cur->state != 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000908E8 size:0x40
void fn_3_908E8(void) {
    fn_800214D0();
    fn_800ACFB0(audioFileDescriptors.files[0x98 / 4]);
    audioFileDescriptors.files[0x98 / 4] = NULL;
}

// .text:0x00090860 size:0x88
BOOL fn_3_90860(void) {
    DrawingSceneStruct *cur = currentDrawingItem;

    if (sound_crowd_EffectsStruct._2C == 0) {
        fn_800216F8(1, fn_3_910AC);
        cur->state = 0;
        sound_crowd_EffectsStruct._2C++;
    } else if (cur->state != 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x0009081C size:0x44
void fn_3_9081C(void) {
    fn_800214D0();
    fn_800214D0();
    fn_800ACFB0(audioFileDescriptors.files[0x08 / 4]);
    audioFileDescriptors.files[0x08 / 4] = NULL;
}

// .text:0x00090798 size:0x84
int fn_3_90798(void) {
    s32 idx = ((g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) ? STADIUM_ID_TOY_FIELD : g_d_GameSettings.StadiumID) + 0x27;
    s32 slot = (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) ? STADIUM_ID_TOY_FIELD : g_d_GameSettings.StadiumID;

    fn_80021518(lbl_3_data_81D4[slot], audioFileDescriptors.files[idx + 1]);
    return 0;
}

// .text:0x00090764 size:0x34
int fn_3_90764(void) {
    fn_80021518(0x33, audioFileDescriptors.files[0xBC / 4]);
    return 0;
}

// .text:0x00090754 size:0x10
void fn_3_90754(u8 *base, u8 a, u8 b) {
    base[0x11820] = a;
    base[0x11821] = b;
}
