#include "Unknown/File_0x80058050.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "game/challenge/challenge_state.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800363d8.h"

#define MENU_RECORD(scene, slot) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (slot)].object)

#define SCOUT_SHOW_RECORD(slot)                                              \
    do {                                                                     \
        UIRecord* rec = MENU_RECORD(scene, slot);                            \
        rec->flags |= UI_FLAG_VISIBLE;                                       \
        rec->frame = (Static_Stats_Tables.teamName[1] % 4) << 16;           \
    } while (0)

void scoutFlagMenu(void) {
    MenuScene* scene;
    s16 charID;
    s32 i;
    s32 j;
    s32 opponentCharID;
    u8* flags;
    ScoutFlagTable* table;

    addGraphicsElementToScene(currentDrawingItem, lbl_80107688);
    scene = (MenuScene*)currentDrawingItem;
    flags = (u8*)&aiPosSwapInputs;

    for (i = 0; i < 9; i++) {
        charID = inMemRoster[1][i].stats.CharID;

        table = g_Challenge.characters[charID].scoutFlagPointer;
        flags[0xCF80 + i] = table->flagsRequired[g_Challenge.difficulty][g_Challenge.captain];
        flags[0xCF89 + i] = g_Challenge.characters[charID].scoutFlagsAchieved;

        for (j = 0; j < 5; j++) {
            if (j < (s8)flags[0xCF80 + i]) {
                if ((s8)flags[0xCF80 + i] - (s8)flags[0xCF89 + i] > j) {
                    MENU_RECORD(scene, 32 + 5 * i + j)->frame = 0;
                }
            } else {
                MENU_RECORD(scene, 32 + 5 * i + j)->flags &= ~UI_FLAG_VISIBLE;
            }
        }

        MENU_RECORD(scene, 5 + i)->frame = i << 16;
        load_Icon(scene, i + 0xE, 1, 0x83, charID);
    }

    MENU_RECORD(scene, 4)->frame = 0x50000;

    opponentCharID = g_Challenge.opponentCaptainCharID;
    if (opponentCharID == CHAR_ID_BOWSERJR) {
        if (g_d_GameSettings.home_AwaySetting == 1) {
            SCOUT_SHOW_RECORD(3);
        } else {
            SCOUT_SHOW_RECORD(2);
        }
    } else {
        if (g_d_GameSettings.home_AwaySetting == 0) {
            SCOUT_SHOW_RECORD(3);
        } else {
            SCOUT_SHOW_RECORD(2);
        }
    }

    currentDrawingItem->func = fn_80057CAC;
}
