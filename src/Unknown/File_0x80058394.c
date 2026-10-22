#include "Unknown/File_0x80058394.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "game/challenge/challenge_state.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/mb_subfunc.h"

#define MENU_RECORD(scene, slot) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (slot)].object)

void zMenuLoadGraphics(MenuScene* scene) {
    u8* loadedFlags;
    u8 pw;
    u8 captainPitch;
    u8 swingArg;
    u8 pitchArg;
    u8 swingResult;
    u8 pitchResult;
    s8 cursor;
    s32 charID;
    s32 hitIndex;
    CharacterStats* row;
    UIRecord* rec;

    loadedFlags = aiPosSwapInputs.zMenuPageLoaded;
    if (loadedFlags[aiPosSwapInputs.playerWhoPaused] != 0) {
        return;
    }

    rec = MENU_RECORD(scene, 302);
    rec->flags &= ~UI_FLAG_VISIBLE;
    rec->playMode = UI_PLAY_STOP;
    MENU_RECORD(scene, 281)->playMode = UI_PLAY_BACKWARD;
    MENU_RECORD(scene, 289)->playMode = UI_PLAY_BACKWARD;

    pw = aiPosSwapInputs.playerWhoPaused;
    cursor = (s8)aiPosSwapInputs.teamManagement_cursorPos[pw];
    charID = inMemRoster[pw][cursor - 1].stats.CharID;
    row = &Static_Stats_Tables.characterStats[charID / 9][charID % 9];

    captainPitch = row->stats.CaptainStarHitPitch;
    if (captainPitch == 0) {
        swingArg = row->stats.NonCaptainStarSwing + 11;
        pitchArg = row->stats.NonCaptainStarPitch + 11;
    } else if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        pitchArg = captainPitch - 1;
        swingArg = pitchArg;
    } else {
        pitchArg = captainPitch - 1;
        hitIndex = (s8)translateStarPitchHitIndex(pitchArg);
        if (hitIndex != -1 && g_Challenge._43C2[hitIndex] == 0) {
            swingArg = row->stats.NonCaptainStarSwing + 11;
            pitchArg = row->stats.NonCaptainStarPitch + 11;
        } else {
            swingArg = pitchArg;
        }
    }

    swingResult = translateStarSwing(swingArg);
    pitchResult = translateStarPitch(pitchArg);

    rec = MENU_RECORD(scene, 305);
    rec->elementIndex = swingResult;
    rec->frame = 0;
    rec->playMode = UI_PLAY_FORWARD;

    rec = MENU_RECORD(scene, 306);
    rec->elementIndex = pitchResult;
    rec->frame = 0;
    rec->playMode = UI_PLAY_FORWARD;

    rec = MENU_RECORD(scene, 307);
    rec->flags |= UI_FLAG_VISIBLE;
    rec->playMode = UI_PLAY_FORWARD;

    MENU_RECORD(scene, 303)->playMode = UI_PLAY_FORWARD;

    loadedFlags[pw] = 1;
}
